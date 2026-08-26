#include "CollisionControl.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/ge_resourceanimationmotion_ps.h>

#include <cstring>
#include <unordered_map>

namespace FrameCollision::CollisionControl
{
struct CachedMarkerInfo
{
    bool foundMatchingMotion;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
};

struct LastAcceptedMarkerDispatch
{
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
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string animationName;
    GEInt action;
    GEInt phase;
    GEInt authoredCounts[MarkerOpcode_Count];
    GEInt acceptedCounts[MarkerOpcode_Count];
    GEFloat lastMarkerStateTime;
    GEFloat lastControlledCallbackStateTime;
};

struct MarkerOwnedCollisionWindow
{
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
};

static std::unordered_map<std::string, CachedMarkerInfo> g_MarkerCache;
static std::unordered_map<eCEntity *, LastAcceptedMarkerDispatch> g_LastAcceptedMarkerDispatchByActor;
static std::unordered_map<eCEntity *, MarkerExecutionBudget> g_MarkerExecutionBudgetByActor;
static std::unordered_map<eCEntity *, MarkerOwnedCollisionWindow> g_MarkerOwnedWindowByActor;

static bool Contains(char const *text, char const *token)
{
    return text != nullptr && token != nullptr && std::strstr(text, token) != nullptr;
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
    return opcode == MarkerOpcode_Right || opcode == MarkerOpcode_Left || opcode == MarkerOpcode_Both;
}

static GEInt GetAuthoredMarkerCount(CurrentMotionMarkerResult const &decision, MarkerOpcode opcode)
{
    return opcode >= 0 && opcode < MarkerOpcode_Count ? decision.markerCounts[opcode] : 0;
}

GEInt GetFirstAuthoredMarkerFrame(CurrentMotionMarkerResult const &decision, MarkerOpcode opcode)
{
    return opcode >= 0 && opcode < MarkerOpcode_Count ? decision.firstMarkerFrames[opcode] : -1;
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
    return a != nullptr && b != nullptr && _stricmp(BaseName(a), BaseName(b)) == 0;
}

static GEFloat AbsoluteFloat(GEFloat value)
{
    return value < 0.0f ? -value : value;
}

static bool IsDuplicateSameUpdateMarker(eCEntity *actorInstance,
                                        EquippedCollisionSources const &sources,
                                        char const *animationName, char const *markerName,
                                        GEInt action, GEInt phase, GEFloat stateTime,
                                        double elapsedMs, GEFloat &stateTimeDelta,
                                        double &elapsedMsDelta)
{
    stateTimeDelta = 0.0f;
    elapsedMsDelta = 0.0;
    auto found = g_LastAcceptedMarkerDispatchByActor.find(actorInstance);
    if (found == g_LastAcceptedMarkerDispatchByActor.end())
        return false;

    LastAcceptedMarkerDispatch const &previous = found->second;
    stateTimeDelta = AbsoluteFloat(stateTime - previous.stateTime);
    elapsedMsDelta = elapsedMs - previous.elapsedMs;
    return previous.rightSourceInstance == sources.rightInstance
        && previous.leftSourceInstance == sources.leftInstance
        && SameFileName(previous.animationName.c_str(), animationName)
        && previous.markerName == (markerName != nullptr ? markerName : "")
        && previous.action == action
        && previous.phase == phase
        && stateTimeDelta <= 0.000001f
        && elapsedMsDelta >= 0.0
        && elapsedMsDelta <= 5.0;
}

static void RememberAcceptedMarker(eCEntity *actorInstance,
                                   EquippedCollisionSources const &sources,
                                   char const *animationName, char const *markerName,
                                   GEInt action, GEInt phase, GEFloat stateTime,
                                   double elapsedMs)
{
    LastAcceptedMarkerDispatch record = {};
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

static void ForgetMarkerExecutionForActor(eCEntity *actorInstance)
{
    if (actorInstance == nullptr)
        return;
    g_MarkerExecutionBudgetByActor.erase(actorInstance);
    g_LastAcceptedMarkerDispatchByActor.erase(actorInstance);
}

static bool TryConsumeAuthoredMarkerOccurrence(
    eCEntity *actorInstance, EquippedCollisionSources const &sources,
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
    bool startsNewExecution = found == g_MarkerExecutionBudgetByActor.end();

    if (!startsNewExecution)
    {
        MarkerExecutionBudget const &previous = found->second;
        startsNewExecution = previous.rightSourceInstance != sources.rightInstance
                          || previous.leftSourceInstance != sources.leftInstance
                          || !SameFileName(previous.animationName.c_str(), animationName)
                          || previous.action != action
                          || previous.phase != phase
                          || stateTime + 0.000001f < previous.lastMarkerStateTime;
        for (GEInt i = 0; !startsNewExecution && i < MarkerOpcode_Count; ++i)
            startsNewExecution = previous.authoredCounts[i] != decision.markerCounts[i];
    }

    if (startsNewExecution)
    {
        MarkerExecutionBudget record = {};
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
        record.lastControlledCallbackStateTime = stateTime;
        g_MarkerExecutionBudgetByActor[actorInstance] = record;
        found = g_MarkerExecutionBudgetByActor.find(actorInstance);
        executionReset = true;
    }

    MarkerExecutionBudget &record = found->second;
    if (opcode < 0 || opcode >= MarkerOpcode_Count)
        return false;
    GEInt &acceptedCount = record.acceptedCounts[opcode];
    acceptedBefore = acceptedCount;
    acceptedAfter = acceptedCount;
    if (authoredCount <= 0 || acceptedCount >= authoredCount)
        return false;
    ++acceptedCount;
    record.lastMarkerStateTime = stateTime;
    acceptedAfter = acceptedCount;
    return true;
}

ControlledCallbackObservation ObserveControlledAttackCallback(
    Entity &actor, EquippedCollisionSources const &sources)
{
    ControlledCallbackObservation result = {};
    eCEntity *actorInstance = actor.GetInstance();
    if (actorInstance == nullptr)
        return result;
    auto found = g_MarkerExecutionBudgetByActor.find(actorInstance);
    if (found == g_MarkerExecutionBudgetByActor.end())
        return result;

    result.currentAnimation = actor.NPC.GetCurrentMovementAni();
    result.currentAction = static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    result.currentPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    result.currentStateTime = actor.Routine.GetStateTime();
    MarkerExecutionBudget &previous = found->second;
    result.previousStateTime = previous.lastControlledCallbackStateTime;
    result.keyChanged = previous.rightSourceInstance != sources.rightInstance
                     || previous.leftSourceInstance != sources.leftInstance
                     || !SameFileName(previous.animationName.c_str(), result.currentAnimation.GetText())
                     || previous.action != result.currentAction
                     || previous.phase != result.currentPhase;
    result.stateTimeRolledBack =
        result.currentStateTime + 0.000001f < previous.lastControlledCallbackStateTime;

    if (result.keyChanged || result.stateTimeRolledBack)
    {
        ForgetMarkerExecutionForActor(actorInstance);
        result.executionRetired = true;
        return result;
    }

    previous.lastControlledCallbackStateTime = result.currentStateTime;
    return result;
}

static void RememberMarkerOwnedWindow(eCEntity *actorInstance,
                                      EquippedCollisionSources const &sources,
                                      unsigned int activeSourceMask,
                                      char const *animationName, GEInt action, GEInt phase)
{
    MarkerOwnedCollisionWindow record = {};
    record.rightSourceInstance = sources.rightInstance;
    record.leftSourceInstance = sources.leftInstance;
    record.activeSourceMask = activeSourceMask;
    record.animationName = animationName != nullptr ? animationName : "";
    record.action = action;
    record.phase = phase;
    g_MarkerOwnedWindowByActor[actorInstance] = record;
}

static MarkerOwnedCollisionWindow *FindMatchingMarkerOwnedWindow(
    eCEntity *actorInstance, EquippedCollisionSources const &sources,
    char const *animationName, GEInt action, GEInt phase)
{
    auto found = g_MarkerOwnedWindowByActor.find(actorInstance);
    if (found == g_MarkerOwnedWindowByActor.end())
        return nullptr;
    MarkerOwnedCollisionWindow &record = found->second;
    bool matches = record.rightSourceInstance == sources.rightInstance
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

static bool MarkerWindowStillMatchesActorExecution(
    eCEntity *actorInstance, MarkerOwnedCollisionWindow const &record)
{
    if (actorInstance == nullptr)
        return false;
    Entity actor(actorInstance);
    bCString currentAnimation = actor.NPC.GetCurrentMovementAni();
    GEInt currentAction = static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt currentPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    bool semanticIdentityMatches = SameFileName(record.animationName.c_str(), currentAnimation.GetText())
                                && record.action == currentAction
                                && record.phase == currentPhase;
    if (!semanticIdentityMatches)
        return false;
    auto budget = g_MarkerExecutionBudgetByActor.find(actorInstance);
    if (budget == g_MarkerExecutionBudgetByActor.end())
        return true;
    GEFloat currentStateTime = actor.Routine.GetStateTime();
    return currentStateTime + 0.000001f >= budget->second.lastMarkerStateTime;
}

GEInt RetireMarkerOwnedSource(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return 0;
    GEInt retiredExecutionCount = 0;
    for (auto entry = g_MarkerOwnedWindowByActor.begin(); entry != g_MarkerOwnedWindowByActor.end();)
    {
        MarkerOwnedCollisionWindow &record = entry->second;
        bool retiredSource = false;
        if ((record.activeSourceMask & SourceMask_Right) != 0
            && record.rightSourceInstance == sourceInstance)
        {
            record.activeSourceMask &= ~SourceMask_Right;
            retiredSource = true;
        }
        if ((record.activeSourceMask & SourceMask_Left) != 0
            && record.leftSourceInstance == sourceInstance)
        {
            record.activeSourceMask &= ~SourceMask_Left;
            retiredSource = true;
        }
        if (retiredSource)
        {
            if (!MarkerWindowStillMatchesActorExecution(entry->first, record))
            {
                ForgetMarkerExecutionForActor(entry->first);
                ++retiredExecutionCount;
            }
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
    return retiredExecutionCount;
}

static bool IsNormalAttackHit(Entity &actor)
{
    bCString ani = actor.NPC.GetCurrentMovementAni();
    gEAction action = actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    return action == gEAction_Attack
        && actor.GetCurrentAniPhase() == gEPhase_Hit
        && Contains(ani.GetText(), "_Attack_Hit_");
}

static bool IsQuickAttackAction(gEAction action)
{
    return action == gEAction_QuickAttack || action == gEAction_QuickAttackR
        || action == gEAction_QuickAttackL;
}

static bool IsQuickAttackHit(Entity &actor)
{
    gEAction action = actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    return IsQuickAttackAction(action) && actor.GetCurrentAniPhase() == gEPhase_Hit;
}

static bool IsWhirlAttackHit(Entity &actor)
{
    gEAction action = actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    return action == gEAction_WhirlAttack && actor.GetCurrentAniPhase() == gEPhase_Hit;
}

bool IsAttackHit(Entity &actor, AttackFamily family)
{
    switch (family)
    {
        case AttackFamily_Normal: return IsNormalAttackHit(actor);
        case AttackFamily_Quick: return IsQuickAttackHit(actor);
        case AttackFamily_Whirl: return IsWhirlAttackHit(actor);
        default: return false;
    }
}

EquippedCollisionSources GetEquippedCollisionSources(Entity &actor)
{
    EquippedCollisionSources result = {};
    Entity right = actor.Inventory.GetItemFromSlot(gESlot_RightHand);
    Entity left = actor.Inventory.GetItemFromSlot(gESlot_LeftHand);
    result.rightInstance = right != None ? right.GetInstance() : nullptr;
    result.leftInstance = left != None ? left.GetInstance() : nullptr;
    return result;
}

bool HasRequiredCollisionSources(EquippedCollisionSources const &sources, unsigned int requiredMask)
{
    if ((requiredMask & SourceMask_Right) != 0 && sources.rightInstance == nullptr)
        return false;
    if ((requiredMask & SourceMask_Left) != 0 && sources.leftInstance == nullptr)
        return false;
    return true;
}

static eCEntity *GetSourceInstance(EquippedCollisionSources const &sources, unsigned int sourceMask)
{
    if (sourceMask == SourceMask_Right)
        return sources.rightInstance;
    if (sourceMask == SourceMask_Left)
        return sources.leftInstance;
    return nullptr;
}

gEUseType GetCollisionSourceUseType(Entity &source)
{
    eCEntity *instance = source.GetInstance();
    return instance != nullptr ? gCEntity::GetUseType(instance) : gEUseType_None;
}

static bool IsFistCollisionSource(Entity &source)
{
    if (source == None)
        return false;
    gEUseType useType = GetCollisionSourceUseType(source);
    return useType == gEUseType_Fist || useType == gEUseType_PhysicalFist;
}

// Confirmed v0.20 runtime layout: frame-effect data at +0x4C, count at
// +0x50, and 8-byte entries containing frame/effect-name at +0x00/+0x04.
static FrameEffectScanResult ScanFrameEffects(eCResourceAnimationMotion_PS const *motion)
{
    FrameEffectScanResult result = {};
    result.requiredSourceMask = SourceMask_None;
    for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
        result.firstMarkerFrames[i] = -1;
    if (motion == nullptr)
        return result;
    unsigned char const *base = reinterpret_cast<unsigned char const *>(motion);
    unsigned char const *data = *reinterpret_cast<unsigned char const *const *>(base + 0x4C);
    GEInt count = *reinterpret_cast<GEInt const *>(base + 0x50);
    result.count = count;
    if (count < 0 || count > 256 || (count > 0 && data == nullptr))
        return result;
    result.layoutLookedValid = true;
    for (GEInt i = 0; i < count; ++i)
    {
        unsigned char const *entry = data + (i * 8);
        GEU16 authoredFrame = *reinterpret_cast<GEU16 const *>(entry + 0x00);
        bCString const *effectString = reinterpret_cast<bCString const *>(entry + 0x04);
        MarkerOpcode opcode = GetMarkerOpcode(effectString->GetText());
        if (opcode == MarkerOpcode_Invalid)
            continue;
        ++result.markerCounts[opcode];
        if (result.firstMarkerFrames[opcode] < 0)
            result.firstMarkerFrames[opcode] = static_cast<GEInt>(authoredFrame);
        if (IsSourceMarker(opcode))
        {
            result.foundMarker = true;
            result.requiredSourceMask |= GetMarkerDesiredSourceMask(opcode);
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
    eCEntityPropertySet *propertySet = instance->GetPropertySet(eEPropertySetType_Animation);
    if (propertySet == nullptr)
        return result;
    eCVisualAnimation_PS *visualAnimation = static_cast<eCVisualAnimation_PS *>(propertySet);
    bCString currentAni = actor.NPC.GetCurrentMovementAni();
    for (GEInt i = 0; i < 4; ++i)
    {
        auto type = static_cast<eCWrapper_emfx2Actor::eEMotionType>(i);
        eCVisualAnimation_PS::eSMotionDesc const &desc = visualAnimation->GetMotionDesc(type);
        if (desc.IsValid() == GEFalse
            || !SameFileName(desc.GetMotionFilename().GetText(), currentAni.GetText()))
            continue;
        result.foundMatchingMotion = true;
        FrameEffectScanResult scan = ScanFrameEffects(desc.GetMotion());
        result.frameEffectCount = scan.count;
        result.markerPresent = scan.layoutLookedValid && scan.foundMarker;
        result.requiredSourceMask = scan.requiredSourceMask;
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
    std::string currentName = currentAni.GetText() != nullptr ? currentAni.GetText() : "";
    auto found = g_MarkerCache.find(currentName);
    if (found != g_MarkerCache.end())
    {
        CurrentMotionMarkerResult result = {};
        result.foundMatchingMotion = found->second.foundMatchingMotion;
        result.markerPresent = found->second.markerPresent;
        result.frameEffectCount = found->second.frameEffectCount;
        result.requiredSourceMask = found->second.requiredSourceMask;
        for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
        {
            result.firstMarkerFrames[opcode] = found->second.firstMarkerFrames[opcode];
            result.markerCounts[opcode] = found->second.markerCounts[opcode];
        }
        return result;
    }
    CurrentMotionMarkerResult scanned = ScanCurrentMotionForMarker(actor);
    CachedMarkerInfo cached = {};
    cached.foundMatchingMotion = scanned.foundMatchingMotion;
    cached.markerPresent = scanned.markerPresent;
    cached.frameEffectCount = scanned.frameEffectCount;
    cached.requiredSourceMask = scanned.requiredSourceMask;
    for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
    {
        cached.firstMarkerFrames[opcode] = scanned.firstMarkerFrames[opcode];
        cached.markerCounts[opcode] = scanned.markerCounts[opcode];
    }
    g_MarkerCache[currentName] = cached;
    return scanned;
}

static MarkerProcessResult MakeMarkerResult(EquippedCollisionSources const &sources,
                                             MarkerOpcode opcode, char const *effectName,
                                             double elapsedMs)
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
    for (GEInt i = 0; i < 2; ++i)
    {
        result.sourceGroupBefore[i] = -1;
        result.sourceGroupAfter[i] = -1;
        result.sourceUseTypes[i] = -1;
    }
    return result;
}

MarkerProcessResult ProcessMarker(Entity &actor, EquippedCollisionSources const &sources,
                                  MarkerOpcode markerOpcode, char const *effectName,
                                  double elapsedMs)
{
    MarkerProcessResult result = MakeMarkerResult(sources, markerOpcode, effectName, elapsedMs);
    bool isNormalAttackHit = IsNormalAttackHit(actor);
    bool isQuickAttackHit = IsQuickAttackHit(actor);
    bool isWhirlAttackHit = IsWhirlAttackHit(actor);
    if (!isNormalAttackHit && !isQuickAttackHit && !isWhirlAttackHit)
    {
        result.code = MarkerResult_RejectedUnsupportedHit;
        return result;
    }

    result.decision = GetCurrentMarkerDecision(actor);
    if (!result.decision.foundMatchingMotion || !result.decision.markerPresent
        || GetAuthoredMarkerCount(result.decision, markerOpcode) <= 0)
    {
        result.code = MarkerResult_RejectedMotionOwnership;
        return result;
    }
    if (!HasRequiredCollisionSources(result.sources, result.decision.requiredSourceMask))
    {
        result.code = MarkerResult_UnsupportedMissingSource;
        return result;
    }

    bCString currentAnimation = actor.NPC.GetCurrentMovementAni();
    result.currentAnimation = currentAnimation.GetText() != nullptr ? currentAnimation.GetText() : "";
    result.markerAction = static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    result.markerPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    result.markerStateTime = actor.Routine.GetStateTime();

    if (IsDuplicateSameUpdateMarker(actor.GetInstance(), result.sources,
                                    result.currentAnimation.c_str(), effectName,
                                    result.markerAction, result.markerPhase,
                                    result.markerStateTime, elapsedMs,
                                    result.duplicateStateTimeDelta,
                                    result.duplicateElapsedMsDelta))
    {
        result.code = MarkerResult_DuplicateIgnored;
        return result;
    }

    bool occurrenceAccepted = TryConsumeAuthoredMarkerOccurrence(
        actor.GetInstance(), result.sources, result.currentAnimation.c_str(),
        result.markerAction, result.markerPhase, result.markerStateTime,
        markerOpcode, result.decision, result.authoredMarkerCount,
        result.acceptedMarkerCountBefore, result.acceptedMarkerCountAfter,
        result.executionBudgetReset);
    if (!occurrenceAccepted)
    {
        result.code = MarkerResult_BudgetIgnored;
        return result;
    }

    if (markerOpcode == MarkerOpcode_Off)
    {
        MarkerOwnedCollisionWindow *window = FindMatchingMarkerOwnedWindow(
            actor.GetInstance(), result.sources, result.currentAnimation.c_str(),
            result.markerAction, result.markerPhase);
        result.ownedMask = window != nullptr ? window->activeSourceMask : SourceMask_None;
        if (window != nullptr)
            window->activeSourceMask = SourceMask_None;
        unsigned int sourceMasks[2] = { SourceMask_Right, SourceMask_Left };
        for (GEInt i = 0; i < 2; ++i)
        {
            unsigned int sourceMask = sourceMasks[i];
            if ((result.ownedMask & sourceMask) == 0)
                continue;
            eCEntity *sourceInstance = GetSourceInstance(result.sources, sourceMask);
            if (sourceInstance == nullptr)
                continue;
            Entity source(sourceInstance);
            if (!IsFistCollisionSource(source)
                && source.GetCollisionGroup() == eECollisionGroup_Item_Attack)
            {
                source.SetCollisionGroup(eECollisionGroup_Item_Equipped);
                ++result.deactivatedSourceCount;
            }
        }
        if (window != nullptr)
        {
            ForgetMarkerOwnedWindowForActor(actor.GetInstance());
            result.markerOwnedWindowRemoved = true;
        }
        RememberAcceptedMarker(actor.GetInstance(), result.sources,
                               result.currentAnimation.c_str(), effectName,
                               result.markerAction, result.markerPhase,
                               result.markerStateTime, elapsedMs);
        result.code = result.ownedMask != SourceMask_None
                    ? MarkerResult_OffAccepted : MarkerResult_OffNoWindow;
        return result;
    }

    result.desiredSourceMask = GetMarkerDesiredSourceMask(markerOpcode);
    if (result.desiredSourceMask == SourceMask_None)
    {
        result.code = MarkerResult_RejectedEmptySourceSet;
        return result;
    }
    for (GEInt i = 0; i < 2; ++i)
    {
        unsigned int sourceMask = i == 0 ? SourceMask_Right : SourceMask_Left;
        if ((result.desiredSourceMask & sourceMask) != 0
            && GetSourceInstance(result.sources, sourceMask) == nullptr)
        {
            result.missingSourceMask = sourceMask;
            result.code = MarkerResult_RejectedIncompleteActivation;
            return result;
        }
    }

    MarkerOwnedCollisionWindow *previousWindow = FindMatchingMarkerOwnedWindow(
        actor.GetInstance(), result.sources, result.currentAnimation.c_str(),
        result.markerAction, result.markerPhase);
    result.previousSourceMask = previousWindow != nullptr
                              ? previousWindow->activeSourceMask : SourceMask_None;
    result.retiredSourceMask = result.previousSourceMask & ~result.desiredSourceMask;
    RememberMarkerOwnedWindow(actor.GetInstance(), result.sources,
                              result.desiredSourceMask, result.currentAnimation.c_str(),
                              result.markerAction, result.markerPhase);

    unsigned int sourceMasks[2] = { SourceMask_Right, SourceMask_Left };
    for (GEInt i = 0; i < 2; ++i)
    {
        unsigned int sourceMask = sourceMasks[i];
        if ((result.retiredSourceMask & sourceMask) == 0)
            continue;
        eCEntity *sourceInstance = GetSourceInstance(result.sources, sourceMask);
        if (sourceInstance == nullptr)
            continue;
        Entity retiredSource(sourceInstance);
        if (!IsFistCollisionSource(retiredSource)
            && retiredSource.GetCollisionGroup() == eECollisionGroup_Item_Attack)
        {
            retiredSource.SetCollisionGroup(eECollisionGroup_Item_Equipped);
            ++result.retiredSourceCount;
        }
    }

    for (GEInt i = 0; i < 2; ++i)
    {
        unsigned int sourceMask = sourceMasks[i];
        if ((result.desiredSourceMask & sourceMask) == 0)
            continue;
        eCEntity *sourceInstance = GetSourceInstance(result.sources, sourceMask);
        Entity selectedSource(sourceInstance);
        result.sourceGroupBefore[i] = static_cast<GEInt>(selectedSource.GetCollisionGroup());
        result.sourceUseTypes[i] = static_cast<GEInt>(GetCollisionSourceUseType(selectedSource));
        result.sourceSkippedGroupForFist[i] = IsFistCollisionSource(selectedSource);
        if (!result.sourceSkippedGroupForFist[i])
        {
            selectedSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
            result.sourceGroupRequested[i] = true;
            ++result.collisionGroupRequestCount;
            if (selectedSource.GetCollisionGroup() == eECollisionGroup_Item_Attack)
                result.markerOwnedWeaponMask |= sourceMask;
        }
        else
        {
            ++result.fistSourceCount;
        }
        selectedSource.TouchDamage.ClearTriggeredList();
        result.sourceListCleared[i] = true;
        ++result.triggeredListClearCount;
        ++result.activatedSourceCount;
        result.sourceGroupAfter[i] = static_cast<GEInt>(selectedSource.GetCollisionGroup());
    }

    if (result.markerOwnedWeaponMask != SourceMask_None)
    {
        RememberMarkerOwnedWindow(actor.GetInstance(), result.sources,
                                  result.markerOwnedWeaponMask,
                                  result.currentAnimation.c_str(), result.markerAction,
                                  result.markerPhase);
    }
    else
    {
        ForgetMarkerOwnedWindowForActor(actor.GetInstance());
    }

    if (isQuickAttackHit || isWhirlAttackHit)
    {
        GEInt statePositionBeforeMarker = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        actor.Routine.AccessProperty<PSRoutine::PropertyStatePosition>() = 1;
        GEInt statePositionAfterMarker = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        if (isQuickAttackHit)
        {
            result.quickStatePositionBeforeMarker = statePositionBeforeMarker;
            result.quickStatePositionAfterMarker = statePositionAfterMarker;
        }
        else
        {
            result.whirlStatePositionBeforeMarker = statePositionBeforeMarker;
            result.whirlStatePositionAfterMarker = statePositionAfterMarker;
        }
    }

    RememberAcceptedMarker(actor.GetInstance(), result.sources,
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

bool TryGetMarkerOwnedWindow(eCEntity *actorInstance, MarkerOwnedWindowView &view)
{
    auto found = g_MarkerOwnedWindowByActor.find(actorInstance);
    if (found == g_MarkerOwnedWindowByActor.end())
        return false;
    view.activeSourceMask = found->second.activeSourceMask;
    view.animationName = found->second.animationName;
    view.action = found->second.action;
    view.phase = found->second.phase;
    return true;
}
}
