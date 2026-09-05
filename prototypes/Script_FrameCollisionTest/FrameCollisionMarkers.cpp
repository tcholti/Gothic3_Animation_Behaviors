#include "FrameCollisionMarkers.h"

#include "CollisionLifecycleGuard.h"
#include "CollisionSourceOperations.h"
#include "CollisionSources.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/ge_resourceanimationmotion_ps.h>

#include <cstring>
#include <unordered_map>

namespace FrameCollision::FrameCollisionMarkers
{
struct CachedMarkerInfo
{
    bool foundMatchingMotion;
    bool scanValid;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
    bool requiresFistSource;
};

struct LastAcceptedMarkerDispatch
{
    std::uint64_t c1Generation;
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string animationName;
    std::string markerName;
    GEInt action;
    GEInt phase;
    GEFloat stateTime;
    double elapsedMs;
};

struct MarkerExecutionBudget
{
    std::uint64_t c1Generation;
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string animationName;
    GEInt action;
    GEInt phase;
    GEInt authoredCounts[MarkerOpcode_Count];
    GEInt acceptedCounts[MarkerOpcode_Count];
    GEFloat lastMarkerStateTime;
};

struct MarkerOwnedCollisionWindow
{
    std::uint64_t c1Generation;
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    unsigned int activeSourceMask;
    std::string animationName;
    GEInt action;
    GEInt phase;
};

struct FrameEffectScanResult
{
    bool layoutLookedValid;
    bool foundMarker;
    GEInt count;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
    bool requiresFistSource;
};

static std::unordered_map<std::string, CachedMarkerInfo> g_MarkerCache;
static std::unordered_map<eCEntity *, LastAcceptedMarkerDispatch>
    g_LastAcceptedMarkerDispatchByActor;
static std::unordered_map<eCEntity *, MarkerExecutionBudget>
    g_MarkerExecutionBudgetByActor;
static std::unordered_map<eCEntity *, MarkerOwnedCollisionWindow>
    g_MarkerOwnedWindowByActor;

static bool Contains(char const *text, char const *token)
{
    return text != nullptr && token != nullptr
        && std::strstr(text, token) != nullptr;
}

MarkerOpcode GetMarkerOpcode(char const *effectName)
{
    if (effectName == nullptr)
        return MarkerOpcode_Invalid;
    if (std::strcmp(effectName, CollisionRightMarker) == 0)
        return MarkerOpcode_Right;
    if (std::strcmp(effectName, CollisionLeftMarker) == 0)
        return MarkerOpcode_Left;
    if (std::strcmp(effectName, CollisionBothMarker) == 0)
        return MarkerOpcode_Both;
    if (std::strcmp(effectName, CollisionOffMarker) == 0)
        return MarkerOpcode_Off;
    if (std::strcmp(effectName, CollisionFistMarker) == 0)
        return MarkerOpcode_Fist;
    return MarkerOpcode_Invalid;
}

char const *GetMarkerOpcodeName(MarkerOpcode opcode)
{
    switch (opcode)
    {
        case MarkerOpcode_Right: return "RIGHT";
        case MarkerOpcode_Left: return "LEFT";
        case MarkerOpcode_Both: return "BOTH";
        case MarkerOpcode_Off: return "OFF";
        case MarkerOpcode_Fist: return "FIST";
        default: return "INVALID";
    }
}

static unsigned int GetMarkerDesiredSourceMask(MarkerOpcode opcode)
{
    switch (opcode)
    {
        case MarkerOpcode_Right: return SourceMask_Right;
        case MarkerOpcode_Left: return SourceMask_Left;
        case MarkerOpcode_Both: return SourceMask_Both;
        default: return SourceMask_None;
    }
}

static bool IsSourceMarker(MarkerOpcode opcode)
{
    return opcode == MarkerOpcode_Right
        || opcode == MarkerOpcode_Left
        || opcode == MarkerOpcode_Both;
}

static GEInt GetAuthoredMarkerCount(
    CurrentMotionMarkerResult const &decision, MarkerOpcode opcode)
{
    return opcode >= 0 && opcode < MarkerOpcode_Count
        ? decision.markerCounts[opcode] : 0;
}

GEInt GetFirstAuthoredMarkerFrame(
    CurrentMotionMarkerResult const &decision, MarkerOpcode opcode)
{
    return opcode >= 0 && opcode < MarkerOpcode_Count
        ? decision.firstMarkerFrames[opcode] : -1;
}

static char const *BaseName(char const *path)
{
    if (path == nullptr)
        return "";
    char const *slash1 = std::strrchr(path, '\\');
    char const *slash2 = std::strrchr(path, '/');
    char const *last = slash1;
    if (slash2 != nullptr && (last == nullptr || slash2 > last))
        last = slash2;
    return last != nullptr ? last + 1 : path;
}

static bool SameFileName(char const *a, char const *b)
{
    return a != nullptr && b != nullptr
        && _stricmp(BaseName(a), BaseName(b)) == 0;
}

static GEFloat AbsoluteFloat(GEFloat value)
{
    return value < 0.0f ? -value : value;
}

static bool IsDuplicateSameUpdateMarker(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    EquippedCollisionSources const &sources,
    char const *animationName, char const *markerName,
    GEInt action, GEInt phase, GEFloat stateTime,
    double elapsedMs, GEFloat &stateTimeDelta, double &elapsedMsDelta)
{
    stateTimeDelta = 0.0f;
    elapsedMsDelta = 0.0;
    auto found = g_LastAcceptedMarkerDispatchByActor.find(actorInstance);
    if (found == g_LastAcceptedMarkerDispatchByActor.end())
        return false;

    LastAcceptedMarkerDispatch const &previous = found->second;
    stateTimeDelta = AbsoluteFloat(stateTime - previous.stateTime);
    elapsedMsDelta = elapsedMs - previous.elapsedMs;
    return previous.c1Generation == c1Generation
        && previous.rightSourceInstance == sources.rightInstance
        && previous.leftSourceInstance == sources.leftInstance
        && SameFileName(previous.animationName.c_str(), animationName)
        && previous.markerName == (markerName != nullptr ? markerName : "")
        && previous.action == action
        && previous.phase == phase
        && stateTimeDelta <= 0.000001f
        && elapsedMsDelta >= 0.0
        && elapsedMsDelta <= 5.0;
}

static void RememberAcceptedMarker(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    EquippedCollisionSources const &sources,
    char const *animationName, char const *markerName,
    GEInt action, GEInt phase, GEFloat stateTime, double elapsedMs)
{
    LastAcceptedMarkerDispatch record = {};
    record.c1Generation = c1Generation;
    record.rightSourceInstance = sources.rightInstance;
    record.leftSourceInstance = sources.leftInstance;
    record.animationName = animationName != nullptr ? animationName : "";
    record.markerName = markerName != nullptr ? markerName : "";
    record.action = action;
    record.phase = phase;
    record.stateTime = stateTime;
    record.elapsedMs = elapsedMs;
    g_LastAcceptedMarkerDispatchByActor[actorInstance] = record;
}

enum MarkerOccurrenceConsumption
{
    MarkerOccurrenceConsumption_Accepted,
    MarkerOccurrenceConsumption_BudgetExhausted,
    MarkerOccurrenceConsumption_GenerationInconsistent
};

static MarkerOccurrenceConsumption TryConsumeAuthoredMarkerOccurrence(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    EquippedCollisionSources const &sources,
    char const *animationName, GEInt action, GEInt phase, GEFloat stateTime,
    MarkerOpcode opcode, CurrentMotionMarkerResult const &decision,
    GEInt &authoredCount, GEInt &acceptedBefore, GEInt &acceptedAfter,
    bool &executionReset)
{
    authoredCount = GetAuthoredMarkerCount(decision, opcode);
    acceptedBefore = 0;
    acceptedAfter = 0;
    executionReset = false;
    auto found = g_MarkerExecutionBudgetByActor.find(actorInstance);
    bool const startsNewExecution =
        found == g_MarkerExecutionBudgetByActor.end()
        || found->second.c1Generation != c1Generation;

    if (!startsNewExecution)
    {
        MarkerExecutionBudget const &previous = found->second;
        bool identityConsistent =
            previous.rightSourceInstance == sources.rightInstance
            && previous.leftSourceInstance == sources.leftInstance
            && SameFileName(
                   previous.animationName.c_str(), animationName)
            && previous.action == action
            && previous.phase == phase
            && stateTime + 0.000001f >= previous.lastMarkerStateTime;
        for (GEInt i = 0;
             identityConsistent && i < MarkerOpcode_Count; ++i)
        {
            identityConsistent =
                previous.authoredCounts[i] == decision.markerCounts[i];
        }
        if (!identityConsistent)
            return MarkerOccurrenceConsumption_GenerationInconsistent;
    }

    if (startsNewExecution)
    {
        MarkerExecutionBudget record = {};
        record.c1Generation = c1Generation;
        record.rightSourceInstance = sources.rightInstance;
        record.leftSourceInstance = sources.leftInstance;
        record.animationName = animationName != nullptr ? animationName : "";
        record.action = action;
        record.phase = phase;
        for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
        {
            record.authoredCounts[i] = decision.markerCounts[i];
            record.acceptedCounts[i] = 0;
        }
        record.lastMarkerStateTime = stateTime;
        g_MarkerExecutionBudgetByActor[actorInstance] = record;
        found = g_MarkerExecutionBudgetByActor.find(actorInstance);
        executionReset = true;
    }

    MarkerExecutionBudget &record = found->second;
    if (opcode < 0 || opcode >= MarkerOpcode_Count)
        return MarkerOccurrenceConsumption_GenerationInconsistent;
    GEInt &acceptedCount = record.acceptedCounts[opcode];
    acceptedBefore = acceptedCount;
    acceptedAfter = acceptedCount;
    if (authoredCount <= 0 || acceptedCount >= authoredCount)
        return MarkerOccurrenceConsumption_BudgetExhausted;
    ++acceptedCount;
    record.lastMarkerStateTime = stateTime;
    acceptedAfter = acceptedCount;
    return MarkerOccurrenceConsumption_Accepted;
}

static void RememberMarkerOwnedWindow(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    EquippedCollisionSources const &sources,
    unsigned int activeSourceMask, char const *animationName,
    GEInt action, GEInt phase)
{
    MarkerOwnedCollisionWindow record = {};
    record.c1Generation = c1Generation;
    record.rightSourceInstance = sources.rightInstance;
    record.leftSourceInstance = sources.leftInstance;
    record.activeSourceMask = activeSourceMask;
    record.animationName = animationName != nullptr ? animationName : "";
    record.action = action;
    record.phase = phase;
    g_MarkerOwnedWindowByActor[actorInstance] = record;
}

static MarkerOwnedCollisionWindow *FindMatchingMarkerOwnedWindow(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    EquippedCollisionSources const &sources,
    char const *animationName, GEInt action, GEInt phase)
{
    auto found = g_MarkerOwnedWindowByActor.find(actorInstance);
    if (found == g_MarkerOwnedWindowByActor.end())
        return nullptr;
    MarkerOwnedCollisionWindow &record = found->second;
    bool matches = record.c1Generation == c1Generation
                && record.rightSourceInstance == sources.rightInstance
                && record.leftSourceInstance == sources.leftInstance
                && SameFileName(record.animationName.c_str(), animationName)
                && record.action == action
                && record.phase == phase;
    return matches ? &record : nullptr;
}

static void ForgetMarkerOwnedWindowForActor(eCEntity *actorInstance)
{
    if (actorInstance != nullptr)
        g_MarkerOwnedWindowByActor.erase(actorInstance);
}

static bool MarkerOwnedWindowIdentityIsConsistent(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    EquippedCollisionSources const &sources,
    char const *animationName, GEInt action, GEInt phase)
{
    auto found = g_MarkerOwnedWindowByActor.find(actorInstance);
    if (found == g_MarkerOwnedWindowByActor.end())
        return true;
    MarkerOwnedCollisionWindow const &record = found->second;
    return record.c1Generation == c1Generation
        && record.rightSourceInstance == sources.rightInstance
        && record.leftSourceInstance == sources.leftInstance
        && SameFileName(record.animationName.c_str(), animationName)
        && record.action == action
        && record.phase == phase;
}

GEInt RetireMarkerOwnedSource(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return 0;
    GEInt retiredSourceBitCount = 0;
    for (auto entry = g_MarkerOwnedWindowByActor.begin();
         entry != g_MarkerOwnedWindowByActor.end();)
    {
        MarkerOwnedCollisionWindow &record = entry->second;
        bool retiredSource = false;
        if ((record.activeSourceMask & SourceMask_Right) != 0
            && record.rightSourceInstance == sourceInstance)
        {
            record.activeSourceMask &= ~SourceMask_Right;
            retiredSource = true;
            ++retiredSourceBitCount;
        }
        if ((record.activeSourceMask & SourceMask_Left) != 0
            && record.leftSourceInstance == sourceInstance)
        {
            record.activeSourceMask &= ~SourceMask_Left;
            retiredSource = true;
            ++retiredSourceBitCount;
        }
        if (retiredSource)
        {
            if (record.activeSourceMask == SourceMask_None)
                entry = g_MarkerOwnedWindowByActor.erase(entry);
            else
                ++entry;
        }
        else
        {
            ++entry;
        }
    }
    return retiredSourceBitCount;
}

static bool TryGetCurrentAttackHitFamily(
    Entity &actor, AttackFamily &family)
{
    if (actor.GetCurrentAniPhase() != gEPhase_Hit)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    switch (action)
    {
        case gEAction_Attack:
        {
            bCString const animation = actor.NPC.GetCurrentMovementAni();
            if (!Contains(animation.GetText(), "_Attack_Hit_"))
                return false;
            family = AttackFamily_Normal;
            return true;
        }
        case gEAction_PowerAttack:
            family = AttackFamily_Power;
            return true;
        case gEAction_QuickAttack:
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
            family = AttackFamily_Quick;
            return true;
        case gEAction_SimpleWhirl:
            family = AttackFamily_SimpleWhirl;
            return true;
        case gEAction_WhirlAttack:
            family = AttackFamily_Whirl;
            return true;
        case gEAction_PierceAttack:
            family = AttackFamily_Pierce;
            return true;
        case gEAction_HackAttack:
            family = AttackFamily_Hack;
            return true;
        default:
            return false;
    }
}

bool IsAttackHit(Entity &actor, AttackFamily family)
{
    AttackFamily currentFamily = AttackFamily_Normal;
    return TryGetCurrentAttackHitFamily(actor, currentFamily)
        && currentFamily == family;
}

static bool IsOneHandedSource(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return false;
    Entity source(sourceInstance);
    return source != None
        && CollisionSources::GetCollisionSourceUseType(source)
            == gEUseType_1H;
}

static GEInt GetMarkerOwnedStatePosition(
    AttackFamily family, EquippedCollisionSources const &sources)
{
    switch (family)
    {
        case AttackFamily_Power:
            return IsOneHandedSource(sources.rightInstance)
                    && IsOneHandedSource(sources.leftInstance)
                ? 2 : 1;
        case AttackFamily_Quick:
        case AttackFamily_SimpleWhirl:
        case AttackFamily_Whirl:
        case AttackFamily_Pierce:
        case AttackFamily_Hack:
            return 1;
        default:
            return -1;
    }
}

static eCEntity *GetSourceInstance(
    EquippedCollisionSources const &sources, unsigned int sourceMask)
{
    if (sourceMask == SourceMask_Right)
        return sources.rightInstance;
    if (sourceMask == SourceMask_Left)
        return sources.leftInstance;
    return nullptr;
}

// Confirmed v0.20 runtime layout: frame-effect data at +0x4C, count at
// +0x50, and 8-byte entries containing frame/effect-name at +0x00/+0x04.
static FrameEffectScanResult ScanFrameEffects(
    eCResourceAnimationMotion_PS const *motion)
{
    FrameEffectScanResult result = {};
    result.requiredSourceMask = SourceMask_None;
    for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
        result.firstMarkerFrames[i] = -1;
    if (motion == nullptr)
        return result;
    unsigned char const *base =
        reinterpret_cast<unsigned char const *>(motion);
    unsigned char const *data =
        *reinterpret_cast<unsigned char const *const *>(base + 0x4C);
    GEInt count = *reinterpret_cast<GEInt const *>(base + 0x50);
    result.count = count;
    if (count < 0 || count > 256 || (count > 0 && data == nullptr))
        return result;
    result.layoutLookedValid = true;
    for (GEInt i = 0; i < count; ++i)
    {
        unsigned char const *entry = data + (i * 8);
        GEU16 authoredFrame =
            *reinterpret_cast<GEU16 const *>(entry + 0x00);
        bCString const *effectString =
            reinterpret_cast<bCString const *>(entry + 0x04);
        MarkerOpcode opcode = GetMarkerOpcode(effectString->GetText());
        if (opcode == MarkerOpcode_Invalid)
            continue;
        ++result.markerCounts[opcode];
        if (result.firstMarkerFrames[opcode] < 0)
        {
            result.firstMarkerFrames[opcode] =
                static_cast<GEInt>(authoredFrame);
        }
        if (IsSourceMarker(opcode))
        {
            result.foundMarker = true;
            result.requiredSourceMask |= GetMarkerDesiredSourceMask(opcode);
        }
        else if (opcode == MarkerOpcode_Fist)
        {
            result.foundMarker = true;
            result.requiresFistSource = true;
        }
    }
    return result;
}

static CurrentMotionMarkerResult ScanCurrentMotionForMarker(Entity &actor)
{
    CurrentMotionMarkerResult result = {};
    result.requiredSourceMask = SourceMask_None;
    for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
        result.firstMarkerFrames[i] = -1;
    eCEntity *instance = actor.GetInstance();
    if (instance == nullptr)
        return result;
    eCEntityPropertySet *propertySet =
        instance->GetPropertySet(eEPropertySetType_Animation);
    if (propertySet == nullptr)
        return result;
    eCVisualAnimation_PS *visualAnimation =
        static_cast<eCVisualAnimation_PS *>(propertySet);
    bCString currentAni = actor.NPC.GetCurrentMovementAni();
    for (GEInt i = 0; i < 4; ++i)
    {
        auto type = static_cast<eCWrapper_emfx2Actor::eEMotionType>(i);
        eCVisualAnimation_PS::eSMotionDesc const &desc =
            visualAnimation->GetMotionDesc(type);
        if (desc.IsValid() == GEFalse
            || !SameFileName(
                   desc.GetMotionFilename().GetText(), currentAni.GetText()))
        {
            continue;
        }

        result.foundMatchingMotion = true;
        FrameEffectScanResult scan = ScanFrameEffects(desc.GetMotion());
        result.scanValid = scan.layoutLookedValid;
        result.frameEffectCount = scan.count;
        result.markerPresent = scan.layoutLookedValid && scan.foundMarker;
        result.requiredSourceMask = scan.requiredSourceMask;
        result.requiresFistSource = scan.requiresFistSource;
        for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
        {
            result.firstMarkerFrames[opcode] = scan.firstMarkerFrames[opcode];
            result.markerCounts[opcode] = scan.markerCounts[opcode];
        }
        return result;
    }
    return result;
}

CurrentMotionMarkerResult GetCurrentMarkerDecision(Entity &actor)
{
    bCString currentAni = actor.NPC.GetCurrentMovementAni();
    std::string currentName = currentAni.GetText() != nullptr
        ? currentAni.GetText() : "";
    auto found = g_MarkerCache.find(currentName);
    if (found != g_MarkerCache.end())
    {
        CurrentMotionMarkerResult result = {};
        result.foundMatchingMotion = found->second.foundMatchingMotion;
        result.scanValid = found->second.scanValid;
        result.markerPresent = found->second.markerPresent;
        result.frameEffectCount = found->second.frameEffectCount;
        result.requiredSourceMask = found->second.requiredSourceMask;
        result.requiresFistSource = found->second.requiresFistSource;
        for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
        {
            result.firstMarkerFrames[opcode] =
                found->second.firstMarkerFrames[opcode];
            result.markerCounts[opcode] =
                found->second.markerCounts[opcode];
        }
        return result;
    }

    CurrentMotionMarkerResult scanned = ScanCurrentMotionForMarker(actor);
    if (!scanned.foundMatchingMotion || !scanned.scanValid)
        return scanned;

    CachedMarkerInfo cached = {};
    cached.foundMatchingMotion = scanned.foundMatchingMotion;
    cached.scanValid = scanned.scanValid;
    cached.markerPresent = scanned.markerPresent;
    cached.frameEffectCount = scanned.frameEffectCount;
    cached.requiredSourceMask = scanned.requiredSourceMask;
    cached.requiresFistSource = scanned.requiresFistSource;
    for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
    {
        cached.firstMarkerFrames[opcode] = scanned.firstMarkerFrames[opcode];
        cached.markerCounts[opcode] = scanned.markerCounts[opcode];
    }
    g_MarkerCache[currentName] = cached;
    return scanned;
}

AttackCallbackOwnershipResult EvaluateAttackCallbackOwnership(
    Entity &actor, AttackFamily family)
{
    AttackCallbackOwnershipResult result = {};
    result.attackHitEligible = IsAttackHit(actor, family);
    if (!result.attackHitEligible)
        return result;

    result.decision = GetCurrentMarkerDecision(actor);
    result.sources = CollisionSources::GetEquippedCollisionSources(actor);
    if (result.decision.requiresFistSource)
    {
        result.fistSourceInstance =
            CollisionSources::ResolveFistCollisionSource(actor);
    }
    result.suppressNativeCallback =
        result.decision.foundMatchingMotion
        && result.decision.scanValid
        && result.decision.markerPresent
        && CollisionSources::HasRequiredCollisionSources(
            result.sources, result.decision.requiredSourceMask)
        && (!result.decision.requiresFistSource
            || result.fistSourceInstance != nullptr);
    return result;
}

static MarkerProcessResult MakeMarkerResult(
    EquippedCollisionSources const &sources, MarkerOpcode opcode,
    char const *effectName, double elapsedMs)
{
    MarkerProcessResult result = {};
    result.opcode = opcode;
    result.markerName = effectName != nullptr ? effectName : "";
    result.sources = sources;
    result.markerElapsedMs = elapsedMs;
    result.quickStatePositionBeforeMarker = -1;
    result.quickStatePositionAfterMarker = -1;
    result.whirlStatePositionBeforeMarker = -1;
    result.whirlStatePositionAfterMarker = -1;
    result.fistSourceGroupBefore = -1;
    result.fistSourceGroupAfter = -1;
    result.fistSourceUseType = -1;
    for (GEInt i = 0; i < 2; ++i)
    {
        result.sourceGroupBefore[i] = -1;
        result.sourceGroupAfter[i] = -1;
        result.sourceUseTypes[i] = -1;
    }
    return result;
}

MarkerProcessResult ProcessMarker(
    Entity &actor, MarkerOpcode markerOpcode, char const *effectName,
    double elapsedMs)
{
    EquippedCollisionSources const sources =
        CollisionSources::GetEquippedCollisionSources(actor);
    MarkerProcessResult result =
        MakeMarkerResult(sources, markerOpcode, effectName, elapsedMs);
    AttackFamily family = AttackFamily_Normal;
    if (!TryGetCurrentAttackHitFamily(actor, family))
    {
        result.code = MarkerResult_RejectedUnsupportedHit;
        return result;
    }

    result.decision = GetCurrentMarkerDecision(actor);
    if (!result.decision.foundMatchingMotion
        || !result.decision.scanValid
        || !result.decision.markerPresent
        || GetAuthoredMarkerCount(result.decision, markerOpcode) <= 0)
    {
        result.code = MarkerResult_RejectedMotionOwnership;
        return result;
    }
    if (!CollisionSources::HasRequiredCollisionSources(
            result.sources, result.decision.requiredSourceMask))
    {
        result.code = MarkerResult_UnsupportedMissingSource;
        return result;
    }
    if (result.decision.requiresFistSource)
    {
        result.fistSourceInstance =
            CollisionSources::ResolveFistCollisionSource(actor);
        if (result.fistSourceInstance == nullptr)
        {
            result.code = MarkerResult_UnsupportedMissingSource;
            return result;
        }
    }

    bCString currentAnimation = actor.NPC.GetCurrentMovementAni();
    result.currentAnimation = currentAnimation.GetText() != nullptr
        ? currentAnimation.GetText() : "";
    result.markerAction = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    result.markerPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    result.markerStateTime = actor.Routine.GetStateTime();

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actor.GetInstance());
    result.c1GenerationValid = generation.valid;
    result.c1Generation = generation.generation;
    if (!generation.valid)
    {
        result.code = MarkerResult_RejectedNoGeneration;
        return result;
    }

    if (!MarkerOwnedWindowIdentityIsConsistent(
            actor.GetInstance(), generation.generation,
            result.sources, result.currentAnimation.c_str(),
            result.markerAction, result.markerPhase))
    {
        result.code = MarkerResult_RejectedGenerationInconsistency;
        return result;
    }

    if (IsDuplicateSameUpdateMarker(
            actor.GetInstance(), generation.generation, result.sources,
            result.currentAnimation.c_str(), effectName,
            result.markerAction, result.markerPhase,
            result.markerStateTime, elapsedMs,
            result.duplicateStateTimeDelta,
            result.duplicateElapsedMsDelta))
    {
        result.code = MarkerResult_DuplicateIgnored;
        return result;
    }

    MarkerOccurrenceConsumption const occurrence =
        TryConsumeAuthoredMarkerOccurrence(
            actor.GetInstance(), generation.generation, result.sources,
            result.currentAnimation.c_str(),
            result.markerAction, result.markerPhase, result.markerStateTime,
            markerOpcode, result.decision, result.authoredMarkerCount,
            result.acceptedMarkerCountBefore,
            result.acceptedMarkerCountAfter,
            result.executionBudgetReset);
    if (occurrence != MarkerOccurrenceConsumption_Accepted)
    {
        result.code =
            occurrence
                == MarkerOccurrenceConsumption_GenerationInconsistent
            ? MarkerResult_RejectedGenerationInconsistency
            : MarkerResult_BudgetIgnored;
        return result;
    }

    if (markerOpcode == MarkerOpcode_Off)
    {
        MarkerOwnedCollisionWindow *window = FindMatchingMarkerOwnedWindow(
            actor.GetInstance(), generation.generation, result.sources,
            result.currentAnimation.c_str(),
            result.markerAction, result.markerPhase);
        result.ownedMask = window != nullptr
            ? window->activeSourceMask : SourceMask_None;
        if (window != nullptr)
            window->activeSourceMask = SourceMask_None;

        unsigned int sourceMasks[2] =
            { SourceMask_Right, SourceMask_Left };
        for (GEInt i = 0; i < 2; ++i)
        {
            unsigned int sourceMask = sourceMasks[i];
            if ((result.ownedMask & sourceMask) == 0)
                continue;
            eCEntity *sourceInstance =
                GetSourceInstance(result.sources, sourceMask);
            CollisionSourceOperations::SourceOperationResult operation =
                CollisionSourceOperations::DeactivateOwnedAttackSource(
                    sourceInstance);
            if (operation.groupRequested)
                ++result.deactivatedSourceCount;
        }
        if (window != nullptr)
        {
            ForgetMarkerOwnedWindowForActor(actor.GetInstance());
            result.markerOwnedWindowRemoved = true;
        }
        RememberAcceptedMarker(
            actor.GetInstance(), generation.generation, result.sources,
            result.currentAnimation.c_str(), effectName,
            result.markerAction, result.markerPhase,
            result.markerStateTime, elapsedMs);
        result.code = result.ownedMask != SourceMask_None
            ? MarkerResult_OffAccepted : MarkerResult_OffNoWindow;
        return result;
    }

    if (markerOpcode == MarkerOpcode_Fist)
    {
        CollisionSourceOperations::FistSourceOperationResult operation =
            CollisionSourceOperations::RearmFistSource(
                result.fistSourceInstance);
        result.fistSourceGroupBefore = operation.groupBefore;
        result.fistSourceGroupAfter = operation.groupAfter;
        result.fistSourceUseType = operation.useType;
        result.fistSourceListCleared = operation.triggeredListCleared;
        if (operation.triggeredListCleared)
            ++result.triggeredListClearCount;
    }
    else
    {
        result.desiredSourceMask = GetMarkerDesiredSourceMask(markerOpcode);
        if (result.desiredSourceMask == SourceMask_None)
        {
            result.code = MarkerResult_RejectedEmptySourceSet;
            return result;
        }
        for (GEInt i = 0; i < 2; ++i)
        {
            unsigned int sourceMask =
                i == 0 ? SourceMask_Right : SourceMask_Left;
            if ((result.desiredSourceMask & sourceMask) != 0
                && GetSourceInstance(result.sources, sourceMask) == nullptr)
            {
                result.missingSourceMask = sourceMask;
                result.code = MarkerResult_RejectedIncompleteActivation;
                return result;
            }
        }

        MarkerOwnedCollisionWindow *previousWindow =
            FindMatchingMarkerOwnedWindow(
                actor.GetInstance(), generation.generation, result.sources,
                result.currentAnimation.c_str(),
                result.markerAction, result.markerPhase);
        result.previousSourceMask = previousWindow != nullptr
            ? previousWindow->activeSourceMask : SourceMask_None;
        result.retiredSourceMask =
            result.previousSourceMask & ~result.desiredSourceMask;
        RememberMarkerOwnedWindow(
            actor.GetInstance(), generation.generation, result.sources,
            result.desiredSourceMask,
            result.currentAnimation.c_str(),
            result.markerAction, result.markerPhase);

        unsigned int sourceMasks[2] =
            { SourceMask_Right, SourceMask_Left };
        for (GEInt i = 0; i < 2; ++i)
        {
            unsigned int sourceMask = sourceMasks[i];
            if ((result.retiredSourceMask & sourceMask) == 0)
                continue;
            eCEntity *sourceInstance =
                GetSourceInstance(result.sources, sourceMask);
            CollisionSourceOperations::SourceOperationResult operation =
                CollisionSourceOperations::DeactivateOwnedAttackSource(
                    sourceInstance);
            if (operation.groupRequested)
                ++result.retiredSourceCount;
        }

        for (GEInt i = 0; i < 2; ++i)
        {
            unsigned int sourceMask = sourceMasks[i];
            if ((result.desiredSourceMask & sourceMask) == 0)
                continue;
            eCEntity *sourceInstance =
                GetSourceInstance(result.sources, sourceMask);
            CollisionSourceOperations::SourceOperationResult operation =
                CollisionSourceOperations::ActivateOrRearm(sourceInstance);
            result.sourceGroupBefore[i] = operation.groupBefore;
            result.sourceGroupAfter[i] = operation.groupAfter;
            result.sourceUseTypes[i] = operation.useType;
            result.sourceGroupRequested[i] = operation.groupRequested;
            result.sourceListCleared[i] = operation.triggeredListCleared;
            if (operation.groupRequested)
                ++result.collisionGroupRequestCount;
            if (operation.groupAfter
                == static_cast<GEInt>(eECollisionGroup_Item_Attack))
            {
                result.markerOwnedWeaponMask |= sourceMask;
            }
            if (operation.triggeredListCleared)
                ++result.triggeredListClearCount;
            ++result.activatedSourceCount;
        }

        if (result.markerOwnedWeaponMask != SourceMask_None)
        {
            RememberMarkerOwnedWindow(
                actor.GetInstance(), generation.generation, result.sources,
                result.markerOwnedWeaponMask,
                result.currentAnimation.c_str(),
                result.markerAction, result.markerPhase);
        }
        else
        {
            ForgetMarkerOwnedWindowForActor(actor.GetInstance());
        }
    }

    GEInt const markerOwnedStatePosition =
        GetMarkerOwnedStatePosition(family, result.sources);
    if (markerOwnedStatePosition >= 0)
    {
        GEInt statePositionBeforeMarker = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        actor.Routine.AccessProperty<PSRoutine::PropertyStatePosition>() =
            markerOwnedStatePosition;
        GEInt statePositionAfterMarker = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        if (family == AttackFamily_Quick)
        {
            result.quickStatePositionBeforeMarker =
                statePositionBeforeMarker;
            result.quickStatePositionAfterMarker =
                statePositionAfterMarker;
        }
        else if (family == AttackFamily_Whirl)
        {
            result.whirlStatePositionBeforeMarker =
                statePositionBeforeMarker;
            result.whirlStatePositionAfterMarker =
                statePositionAfterMarker;
        }
    }

    RememberAcceptedMarker(
        actor.GetInstance(), generation.generation, result.sources,
        result.currentAnimation.c_str(), effectName,
        result.markerAction, result.markerPhase,
        result.markerStateTime, elapsedMs);
    result.code = MarkerResult_Accepted;
    return result;
}

bool HasMarkerOwnedWindows()
{
    return !g_MarkerOwnedWindowByActor.empty();
}

bool TryGetMarkerOwnedWindow(
    eCEntity *actorInstance, MarkerOwnedWindowView &view)
{
    auto found = g_MarkerOwnedWindowByActor.find(actorInstance);
    if (found == g_MarkerOwnedWindowByActor.end())
        return false;
    view.c1Generation = found->second.c1Generation;
    view.activeSourceMask = found->second.activeSourceMask;
    view.animationName = found->second.animationName;
    view.action = found->second.action;
    view.phase = found->second.phase;
    return true;
}
}
