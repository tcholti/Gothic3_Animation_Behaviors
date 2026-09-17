#include "PhysicalFistProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"

#include <cstdio>
#include <cstring>
#include <unordered_map>

#include <windows.h>

namespace FrameCollision::PhysicalFistProbe
{
struct QuickEarlySuppressionProof
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    gEUseType rightUseType;
    bool earlySuppressionProven;
    bool activationUsed;
};

struct QuickPreStateFistIntervention
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    bool interventionUsed;
    bool preStateFistProven;
    bool laterFistRearmUsed;
};

struct PowerEarlySuppressionProof
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    gEUseType rightUseType;
    bool earlySuppressionProven;
    bool activationUsed;
    bool repeatFistRearmUsed;
};

struct NormalEarlySuppressionProof
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    gEUseType rightUseType;
    bool earlySuppressionProven;
    bool activationUsed;
};

struct NormalTriggerStateSnapshot
{
    GEInt resetOnUntouch;
    GEInt visitedSize;
    GEInt visitedCountSize;
    GEInt playerResolved;
    GEInt playerPresent;
    GEInt playerEntryCount;
    GEInt playerVisitCount;
    GEInt countsAligned;
};

struct NormalPreStateFistIntervention
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    bool preStateRearmProven;
    bool nativeRearmSuppressionUsed;
    bool nativeTriggerClearSuppressionUsed;
    bool triggerStateInitialized;
    bool marker2ReplacementClearUsed;
    NormalTriggerStateSnapshot lastTriggerState;
};

struct SprintEarlySuppressionProof
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    gEUseType rightUseType;
    bool earlySuppressionProven;
    bool activationUsed;
};

static thread_local QuickCallbackObservation *g_pCurrentQuickCallbackScope =
    nullptr;
static thread_local NormalCallbackObservation *g_pCurrentNormalCallbackScope =
    nullptr;
static thread_local PowerCallbackObservation *g_pCurrentPowerCallbackScope =
    nullptr;
static thread_local SprintCallbackObservation *g_pCurrentSprintCallbackScope =
    nullptr;
static thread_local std::unordered_map<eCEntity *, QuickEarlySuppressionProof>
    g_QuickEarlySuppressionProofs;
static thread_local std::unordered_map<eCEntity *, PowerEarlySuppressionProof>
    g_PowerEarlySuppressionProofs;
static thread_local std::unordered_map<eCEntity *, NormalEarlySuppressionProof>
    g_NormalEarlySuppressionProofs;
static thread_local
    std::unordered_map<eCEntity *, NormalPreStateFistIntervention>
        g_NormalPreStateFistInterventions;
static thread_local std::unordered_map<eCEntity *, SprintEarlySuppressionProof>
    g_SprintEarlySuppressionProofs;
static thread_local
    std::unordered_map<eCEntity *, QuickPreStateFistIntervention>
        g_QuickPreStateFistInterventions;

static bool IsRaw55ProbeFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Quick
        || family == AttackFamily_Power
        || family == AttackFamily_Sprint;
}

static bool IsSuppressionFamily(AttackFamily)
{
    return false;
}

static char const *ProbeFamilyName(AttackFamily family)
{
    switch (family)
    {
        case AttackFamily_Normal: return "NORMAL";
        case AttackFamily_Quick: return "QUICK";
        case AttackFamily_Sprint: return "SPRINT";
        default: return "UNSUPPORTED";
    }
}

static bool TryResolveRaw55ProbeFixture(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu, bool requireEquippedGroup,
    CollisionLifecycleGuard::GenerationToken &generation,
    eCEntity *&rightInstance)
{
    generation = {};
    rightInstance = nullptr;

    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    if (spu == nullptr || spu->GetSelfEntity() != actorInstance)
        return false;

    generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    if (!generation.valid || !ownership.attackHitEligible
        || !IsRaw55ProbeFamily(family))
    {
        return false;
    }

    CurrentMotionMarkerResult const &decision = ownership.decision;
    if (!decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr)
    {
        return false;
    }

    rightInstance = ownership.sources.rightInstance;
    Entity rightSource(rightInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    if (requireEquippedGroup
        && rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    return true;
}

static bool TryResolveProvenNormalPreStateIntervention(
    Entity &actor, eCEntity *rightSourceInstance,
    std::uint64_t c1Generation,
    NormalPreStateFistIntervention *&intervention)
{
    intervention = nullptr;
    if (actor == None || actor.GetInstance() == nullptr
        || rightSourceInstance == nullptr
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_Attack
        || !FrameCollisionMarkers::IsAttackHit(
            actor, AttackFamily_Normal))
    {
        return false;
    }

    eCEntity *const actorInstance = actor.GetInstance();
    auto interventionIt =
        g_NormalPreStateFistInterventions.find(actorInstance);
    if (interventionIt == g_NormalPreStateFistInterventions.end())
        return false;

    NormalPreStateFistIntervention &candidate = interventionIt->second;
    if (candidate.actorInstance != actorInstance
        || candidate.rightSourceInstance != rightSourceInstance
        || candidate.c1Generation != c1Generation
        || !candidate.preStateRearmProven)
    {
        return false;
    }

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    Entity rightSource(rightSourceInstance);
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != c1Generation
        || currentSources.rightInstance != rightSourceInstance
        || rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    intervention = &candidate;
    return true;
}

static bool TryCaptureTriggerState(
    eCEntity *rightSourceInstance,
    NormalTriggerStateSnapshot &snapshot)
{
    snapshot = {};
    snapshot.playerVisitCount = -1;

    Entity rightSource(rightSourceInstance);
    if (rightSource == None)
        return false;

    gCTouchDamage_PS const *const touchDamage =
        static_cast<gCTouchDamage_PS const *>(
            rightSource.TouchDamage.m_pEngineEntityPropertySet);
    if (touchDamage == nullptr)
        return false;

    bTObjArray<eCEntityProxy> const &visited =
        touchDamage->GetEntitiesVisited();
    bTValArray<GEU16> const &visitedCounts =
        touchDamage->GetEntitiesVisitedCount();
    snapshot.resetOnUntouch = static_cast<GEInt>(
        touchDamage->GetResetOnUntouch());
    snapshot.visitedSize = visited.GetCount();
    snapshot.visitedCountSize = visitedCounts.GetCount();
    snapshot.countsAligned =
        snapshot.visitedSize == snapshot.visitedCountSize ? 1 : 0;

    Entity player = Entity::GetPlayer();
    eCEntity *const playerInstance =
        player != None ? player.GetInstance() : nullptr;
    snapshot.playerResolved = playerInstance != nullptr ? 1 : 0;
    GEInt playerIndex = -1;
    if (playerInstance != nullptr)
    {
        for (GEInt i = 0; i < snapshot.visitedSize; ++i)
        {
            eCEntity const *const visitedEntity =
                visited.GetAt(i).GetEntity();
            if (visitedEntity == playerInstance)
            {
                ++snapshot.playerEntryCount;
                playerIndex = i;
            }
        }
    }

    snapshot.playerPresent = snapshot.playerEntryCount > 0 ? 1 : 0;
    if (snapshot.countsAligned && snapshot.playerEntryCount == 1
        && playerIndex >= 0)
    {
        snapshot.playerVisitCount = static_cast<GEInt>(
            visitedCounts.GetAt(playerIndex));
    }

    return true;
}

static bool TryCaptureNormalTriggerState(
    NormalPreStateFistIntervention const &intervention,
    NormalTriggerStateSnapshot &snapshot)
{
    return TryCaptureTriggerState(
        intervention.rightSourceInstance, snapshot);
}

static bool TryResolveNormalTriggerClearIntervention(
    eCTrigger_PS *trigger,
    NormalPreStateFistIntervention *&intervention)
{
    intervention = nullptr;
    if (trigger == nullptr)
        return false;

    for (auto &entry : g_NormalPreStateFistInterventions)
    {
        NormalPreStateFistIntervention &candidate = entry.second;
        if (candidate.actorInstance == nullptr
            || entry.first != candidate.actorInstance
            || candidate.rightSourceInstance == nullptr)
        {
            continue;
        }

        Entity actor(candidate.actorInstance);
        Entity rightSource(candidate.rightSourceInstance);
        if (actor == None || rightSource == None
            || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
                != gEAction_Attack
            || !FrameCollisionMarkers::IsAttackHit(
                actor, AttackFamily_Normal)
            || CollisionSources::GetCollisionSourceUseType(rightSource)
                != gEUseType_PhysicalFist
            || static_cast<eCTrigger_PS *>(
                rightSource.TouchDamage.m_pEngineEntityPropertySet)
                != trigger)
        {
            continue;
        }

        CollisionLifecycleGuard::GenerationToken const generation =
            CollisionLifecycleGuard::CaptureCurrentGenerationToken(
                candidate.actorInstance);
        EquippedCollisionSources const currentSources =
            CollisionSources::GetEquippedCollisionSources(actor);
        if (!generation.valid
            || generation.actorInstance != candidate.actorInstance
            || generation.generation != candidate.c1Generation
            || currentSources.rightInstance
                != candidate.rightSourceInstance)
        {
            continue;
        }

        intervention = &candidate;
        return true;
    }

    return false;
}

static char const *TriggerClearBaseName(char const *path)
{
    if (path == nullptr)
        return "";
    char const *const backslash = std::strrchr(path, '\\');
    char const *const slash = std::strrchr(path, '/');
    char const *last = backslash;
    if (slash != nullptr && (last == nullptr || slash > last))
        last = slash;
    return last != nullptr ? last + 1 : path;
}

static char const *TriggerClearKindName(TriggerClearKind clearKind)
{
    return clearKind == TriggerClearKind_Entity ? "ENTITY" : "ALL";
}

static char const *TriggerClearBoundaryName(
    TriggerClearBoundary boundary)
{
    return boundary == TriggerClearBoundary_Post ? "POST" : "PRE";
}

struct TriggerClearCallerIdentity
{
    bool resolved;
    HMODULE module;
    char modulePath[MAX_PATH];
    DWORD pathLength;
    std::uintptr_t rva;
};

static TriggerClearCallerIdentity ResolveTriggerClearCaller(
    void *callerAddress)
{
    TriggerClearCallerIdentity identity = {};
    identity.resolved = callerAddress != nullptr
        && ::GetModuleHandleExA(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCSTR>(callerAddress),
            &identity.module) != FALSE;
    identity.pathLength = identity.resolved
        ? ::GetModuleFileNameA(
            identity.module, identity.modulePath, MAX_PATH) : 0;
    if (identity.resolved)
    {
        identity.rva = reinterpret_cast<std::uintptr_t>(callerAddress)
            - reinterpret_cast<std::uintptr_t>(identity.module);
    }
    return identity;
}

void ObserveTriggerClear(
    eCTrigger_PS *trigger, eCEntity *argumentEntity,
    TriggerClearKind clearKind, TriggerClearBoundary boundary,
    void *callerAddress)
{
    NormalPreStateFistIntervention *intervention = nullptr;
    if (!TryResolveNormalTriggerClearIntervention(
            trigger, intervention))
    {
        return;
    }

    NormalTriggerStateSnapshot snapshot = {};
    if (!TryCaptureNormalTriggerState(*intervention, snapshot))
        return;

    Entity actor(intervention->actorInstance);
    Entity rightSource(intervention->rightSourceInstance);
    if (actor == None || rightSource == None)
        return;

    Entity player = Entity::GetPlayer();
    eCEntity *const playerInstance =
        player != None ? player.GetInstance() : nullptr;
    GEInt const argumentIsPlayer = argumentEntity != nullptr
        && argumentEntity == playerInstance ? 1 : 0;
    Entity argument(argumentEntity);
    std::string argumentName = "<none>";
    if (clearKind == TriggerClearKind_Entity)
    {
        argumentName = argumentEntity == nullptr
            ? "<null>"
            : argument != None
                ? argument.GetName().GetText()
                : "<unavailable>";
    }

    TriggerClearCallerIdentity const caller =
        ResolveTriggerClearCaller(callerAddress);
    char callerRva[32] = {};
    if (caller.resolved)
    {
        std::snprintf(
            callerRva, sizeof(callerRva), "0x%08lX",
            static_cast<unsigned long>(caller.rva));
    }
    else
    {
        std::snprintf(
            callerRva, sizeof(callerRva), "<unresolved>");
    }

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    GEInt const action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    GEFloat const stateTime = actor.Routine.GetStateTime();
    std::fprintf(
        log,
        "CORE RAW55_NORMAL_TRIGGER_CLEAR_OBSERVATION Boundary=%s ClearKind=%s Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d PreStateRearmProven=%d Native7To7SuppressionUsed=%d NativeClearSuppressionUsed=%d TriggerIdentityMatch=1 ResetOnUntouch=%d VisitedSize=%d VisitedCountSize=%d PlayerResolved=%d PlayerPresent=%d PlayerEntryCount=%d PlayerVisitCount=%d CountsAligned=%d Argument=%s ArgumentAddress=%p ArgumentIsPlayer=%d CallerResolved=%d CallerModule=%s CallerRVA=%s CallerAddress=%p\n",
        TriggerClearBoundaryName(boundary),
        TriggerClearKindName(clearKind),
        actor.GetName().GetText(),
        static_cast<unsigned long long>(intervention->c1Generation),
        action, statePosition, static_cast<double>(stateTime),
        rightSource.GetName().GetText(),
        static_cast<GEInt>(
            CollisionSources::GetCollisionSourceUseType(rightSource)),
        static_cast<GEInt>(rightSource.GetCollisionGroup()),
        intervention->preStateRearmProven ? 1 : 0,
        intervention->nativeRearmSuppressionUsed ? 1 : 0,
        intervention->nativeTriggerClearSuppressionUsed ? 1 : 0,
        snapshot.resetOnUntouch, snapshot.visitedSize,
        snapshot.visitedCountSize, snapshot.playerResolved,
        snapshot.playerPresent, snapshot.playerEntryCount,
        snapshot.playerVisitCount, snapshot.countsAligned,
        argumentName.c_str(), static_cast<void *>(argumentEntity),
        argumentIsPlayer, caller.resolved ? 1 : 0,
        caller.pathLength > 0
            ? TriggerClearBaseName(caller.modulePath)
            : caller.resolved ? "<path-unavailable>" : "<unresolved>",
        callerRva, callerAddress);
    std::fflush(log);
}

bool ShouldSuppressTriggerClear(
    eCTrigger_PS *trigger, TriggerClearKind clearKind,
    void *callerAddress)
{
    if (clearKind != TriggerClearKind_All)
        return false;

    NormalPreStateFistIntervention *intervention = nullptr;
    if (!TryResolveNormalTriggerClearIntervention(
            trigger, intervention)
        || !intervention->preStateRearmProven
        || !intervention->nativeRearmSuppressionUsed
        || intervention->nativeTriggerClearSuppressionUsed)
    {
        return false;
    }

    Entity actor(intervention->actorInstance);
    Entity rightSource(intervention->rightSourceInstance);
    if (actor == None || rightSource == None)
        return false;

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Attack
        || statePosition != 0)
    {
        return false;
    }

    NormalTriggerStateSnapshot snapshot = {};
    if (!TryCaptureNormalTriggerState(*intervention, snapshot)
        || snapshot.countsAligned != 1
        || snapshot.playerResolved != 1
        || snapshot.playerPresent != 1
        || snapshot.playerEntryCount != 1
        || snapshot.playerVisitCount < 1)
    {
        return false;
    }

    TriggerClearCallerIdentity const caller =
        ResolveTriggerClearCaller(callerAddress);
    HMODULE const scriptGameModule =
        ::GetModuleHandleA("Script_Game.dll");
    if (!caller.resolved || scriptGameModule == nullptr
        || caller.module != scriptGameModule
        || caller.rva != 0x000386C6)
    {
        return false;
    }

    intervention->nativeTriggerClearSuppressionUsed = true;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        gEAction const action =
            actor.Routine.GetProperty<PSRoutine::PropertyAction>();
        GEFloat const stateTime = actor.Routine.GetStateTime();
        std::fprintf(
            log,
            "CORE RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d PreStateRearmProven=1 Native7To7SuppressionUsed=1 PlayerPresent=%d PlayerEntryCount=%d PlayerVisitCount=%d CountsAligned=%d CallerModule=%s CallerRVA=0x%08lX SUPPRESS_CLEAR=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(
                intervention->c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(rightSource.GetCollisionGroup()),
            snapshot.playerPresent, snapshot.playerEntryCount,
            snapshot.playerVisitCount, snapshot.countsAligned,
            "Script_Game.dll",
            static_cast<unsigned long>(caller.rva));
        std::fflush(log);
    }

    return true;
}

static bool TriggerStateFingerprintChanged(
    NormalTriggerStateSnapshot const &before,
    NormalTriggerStateSnapshot const &after)
{
    return before.resetOnUntouch != after.resetOnUntouch
        || before.visitedSize != after.visitedSize
        || before.visitedCountSize != after.visitedCountSize
        || before.playerResolved != after.playerResolved
        || before.playerPresent != after.playerPresent
        || before.playerEntryCount != after.playerEntryCount
        || before.playerVisitCount != after.playerVisitCount
        || before.countsAligned != after.countsAligned;
}

static void AppendTriggerStateChangeReason(
    std::string &reason, char const *component)
{
    if (!reason.empty())
        reason += '|';
    reason += component;
}

static std::string BuildTriggerStateChangeReason(
    NormalTriggerStateSnapshot const &before,
    NormalTriggerStateSnapshot const &after)
{
    std::string reason;
    if (before.resetOnUntouch != after.resetOnUntouch)
        AppendTriggerStateChangeReason(reason, "RESET_ON_UNTOUCH");
    if (before.visitedSize != after.visitedSize)
        AppendTriggerStateChangeReason(reason, "VISITED_SIZE");
    if (before.visitedCountSize != after.visitedCountSize)
        AppendTriggerStateChangeReason(reason, "VISITED_COUNT_SIZE");
    if (before.playerResolved != after.playerResolved)
        AppendTriggerStateChangeReason(reason, "PLAYER_RESOLVED");
    if (before.playerPresent != after.playerPresent)
        AppendTriggerStateChangeReason(reason, "PLAYER_PRESENT");
    if (before.playerEntryCount != after.playerEntryCount)
        AppendTriggerStateChangeReason(reason, "PLAYER_ENTRY_COUNT");
    if (before.playerVisitCount != after.playerVisitCount)
        AppendTriggerStateChangeReason(reason, "PLAYER_VISIT_COUNT");
    if (before.countsAligned != after.countsAligned)
        AppendTriggerStateChangeReason(reason, "ARRAY_ALIGNMENT");
    return reason;
}

static bool ObserveNormalTriggerState(
    char const *boundary, Entity &actor, eCEntity *rightSourceInstance,
    std::uint64_t c1Generation, bool changeOnly)
{
    NormalPreStateFistIntervention *intervention = nullptr;
    if (!TryResolveProvenNormalPreStateIntervention(
            actor, rightSourceInstance, c1Generation, intervention))
    {
        return false;
    }

    NormalTriggerStateSnapshot snapshot = {};
    if (!TryCaptureNormalTriggerState(*intervention, snapshot))
        return false;

    if (changeOnly && (!intervention->triggerStateInitialized
        || !TriggerStateFingerprintChanged(
            intervention->lastTriggerState, snapshot)))
    {
        intervention->lastTriggerState = snapshot;
        intervention->triggerStateInitialized = true;
        return false;
    }

    std::string changeReason;
    if (changeOnly)
    {
        changeReason = BuildTriggerStateChangeReason(
            intervention->lastTriggerState, snapshot);
    }
    if (!snapshot.countsAligned)
        AppendTriggerStateChangeReason(
            changeReason, "ARRAY_SIZE_MISMATCH");
    if (snapshot.playerEntryCount > 1)
        AppendTriggerStateChangeReason(
            changeReason, "MULTIPLE_PLAYER_ENTRIES");
    if (changeReason.empty())
        changeReason = "NONE";

    intervention->lastTriggerState = snapshot;
    intervention->triggerStateInitialized = true;

    Entity rightSource(rightSourceInstance);
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return false;

    GEInt const action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    GEFloat const stateTime = actor.Routine.GetStateTime();
    std::fprintf(
        log,
        "CORE RAW55_NORMAL_TRIGGER_STATE_OBSERVATION Boundary=%s Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d ResetOnUntouch=%d VisitedSize=%d VisitedCountSize=%d PlayerResolved=%d PlayerPresent=%d PlayerEntryCount=%d PlayerVisitCount=%d CountsAligned=%d ChangeReason=%s\n",
        boundary != nullptr ? boundary : "<null>",
        actor.GetName().GetText(),
        static_cast<unsigned long long>(c1Generation), action,
        statePosition, static_cast<double>(stateTime),
        rightSource.GetName().GetText(),
        static_cast<GEInt>(
            CollisionSources::GetCollisionSourceUseType(rightSource)),
        static_cast<GEInt>(rightSource.GetCollisionGroup()),
        snapshot.resetOnUntouch, snapshot.visitedSize,
        snapshot.visitedCountSize, snapshot.playerResolved,
        snapshot.playerPresent, snapshot.playerEntryCount,
        snapshot.playerVisitCount, snapshot.countsAligned,
        changeReason.c_str());
    std::fflush(log);
    return true;
}

bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu)
{
    // All current raw55 family probes keep their native callbacks enabled.
    if (!IsSuppressionFamily(family))
        return false;

    CollisionLifecycleGuard::GenerationToken generation = {};
    eCEntity *rightInstance = nullptr;
    if (!TryResolveRaw55ProbeFixture(
            actor, family, ownership, spu, true,
            generation, rightInstance))
    {
        return false;
    }

    Entity rightSource(rightInstance);
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        gEAction const action =
            actor.Routine.GetProperty<PSRoutine::PropertyAction>();
        bCString const motion = actor.NPC.GetCurrentMovementAni();
        Entity leftSource(ownership.sources.leftInstance);
        GEInt const leftUseType = leftSource != None
            ? static_cast<GEInt>(
                  CollisionSources::GetCollisionSourceUseType(leftSource))
            : -1;
        GEInt const leftGroup = leftSource != None
            ? static_cast<GEInt>(leftSource.GetCollisionGroup()) : -1;
        std::fprintf(
            log,
            "CORE RAW55_CALLBACK_SUPPRESSION_PROBE Actor=%s Family=%s Action=%d Motion=%s C1=%llu Right=%s RightUseType=%d RightGroup=%d Left=%s LeftUseType=%d LeftGroup=%d SUPPRESS_NATIVE=1\n",
            actor.GetName().GetText(), ProbeFamilyName(family),
            static_cast<GEInt>(action),
            motion.GetText() != nullptr ? motion.GetText() : "<unavailable>",
            static_cast<unsigned long long>(generation.generation),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(rightSource.GetCollisionGroup()),
            leftSource != None ? leftSource.GetName().GetText() : "<none>",
            leftUseType, leftGroup);
        std::fflush(log);
    }

    return true;
}

void BeginQuickCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    QuickCallbackObservation &observation)
{
    observation = {};
    observation.previousScope = g_pCurrentQuickCallbackScope;
    g_pCurrentQuickCallbackScope = &observation;

    FrameCollisionMarkers::AttackCallbackOwnershipResult const ownership =
        FrameCollisionMarkers::EvaluateAttackCallbackOwnership(
            actor, AttackFamily_Quick);
    CollisionLifecycleGuard::GenerationToken generation = {};
    eCEntity *rightInstance = nullptr;
    if (!TryResolveRaw55ProbeFixture(
            actor, AttackFamily_Quick, ownership, spu, false,
            generation, rightInstance))
    {
        return;
    }

    Entity rightSource(rightInstance);
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    observation.active = true;
    observation.actorInstance = actor.GetInstance();
    observation.rightSourceInstance = rightInstance;
    observation.c1Generation = generation.generation;
    observation.actionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    observation.phaseBefore = static_cast<GEInt>(actor.GetCurrentAniPhase());
    observation.stateTimeBefore = actor.Routine.GetStateTime();
    observation.statePositionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    observation.rightGroupBefore = static_cast<GEInt>(
        rightSource.GetCollisionGroup());
    observation.motionBefore = motion.GetText() != nullptr
        ? motion.GetText() : "<unavailable>";
}

void BeginNormalCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    NormalCallbackObservation &observation)
{
    observation = {};
    observation.previousScope = g_pCurrentNormalCallbackScope;
    g_pCurrentNormalCallbackScope = &observation;

    FrameCollisionMarkers::AttackCallbackOwnershipResult const ownership =
        FrameCollisionMarkers::EvaluateAttackCallbackOwnership(
            actor, AttackFamily_Normal);
    CollisionLifecycleGuard::GenerationToken generation = {};
    eCEntity *rightInstance = nullptr;
    if (!TryResolveRaw55ProbeFixture(
            actor, AttackFamily_Normal, ownership, spu, false,
            generation, rightInstance))
    {
        return;
    }

    Entity rightSource(rightInstance);
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    observation.active = true;
    observation.actorInstance = actor.GetInstance();
    observation.rightSourceInstance = rightInstance;
    observation.c1Generation = generation.generation;
    observation.actionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    observation.phaseBefore = static_cast<GEInt>(actor.GetCurrentAniPhase());
    observation.stateTimeBefore = actor.Routine.GetStateTime();
    observation.statePositionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    observation.rightUseTypeBefore = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(rightSource));
    observation.rightGroupBefore = static_cast<GEInt>(
        rightSource.GetCollisionGroup());
    observation.motionBefore = motion.GetText() != nullptr
        ? motion.GetText() : "<unavailable>";
    observation.rightNameBefore = rightSource.GetName().GetText();

    ObserveNormalTriggerState(
        "CALLBACK_CHANGE", actor, rightInstance,
        generation.generation, true);
}

void BeginPowerCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    PowerCallbackObservation &observation)
{
    observation = {};
    observation.previousScope = g_pCurrentPowerCallbackScope;
    g_pCurrentPowerCallbackScope = &observation;

    if (actor == None || actor.GetInstance() == nullptr
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_PowerAttack)
    {
        return;
    }

    FrameCollisionMarkers::AttackCallbackOwnershipResult const ownership =
        FrameCollisionMarkers::EvaluateAttackCallbackOwnership(
            actor, AttackFamily_Power);
    CollisionLifecycleGuard::GenerationToken generation = {};
    eCEntity *rightInstance = nullptr;
    if (!TryResolveRaw55ProbeFixture(
            actor, AttackFamily_Power, ownership, spu, false,
            generation, rightInstance))
    {
        return;
    }

    Entity rightSource(rightInstance);
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    observation.active = true;
    observation.actorInstance = actor.GetInstance();
    observation.rightSourceInstance = rightInstance;
    observation.c1Generation = generation.generation;
    observation.actionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    observation.phaseBefore = static_cast<GEInt>(actor.GetCurrentAniPhase());
    observation.stateTimeBefore = actor.Routine.GetStateTime();
    observation.statePositionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    observation.rightUseTypeBefore = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(rightSource));
    observation.rightGroupBefore = static_cast<GEInt>(
        rightSource.GetCollisionGroup());
    observation.motionBefore = motion.GetText() != nullptr
        ? motion.GetText() : "<unavailable>";
    observation.rightNameBefore = rightSource.GetName().GetText();
}

void BeginSprintCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    SprintCallbackObservation &observation)
{
    observation = {};
    observation.previousScope = g_pCurrentSprintCallbackScope;
    g_pCurrentSprintCallbackScope = &observation;

    if (actor == None || actor.GetInstance() == nullptr
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_SprintAttack)
    {
        return;
    }

    FrameCollisionMarkers::AttackCallbackOwnershipResult const ownership =
        FrameCollisionMarkers::EvaluateAttackCallbackOwnership(
            actor, AttackFamily_Sprint);
    CollisionLifecycleGuard::GenerationToken generation = {};
    eCEntity *rightInstance = nullptr;
    if (!TryResolveRaw55ProbeFixture(
            actor, AttackFamily_Sprint, ownership, spu, false,
            generation, rightInstance))
    {
        return;
    }

    Entity rightSource(rightInstance);
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    observation.active = true;
    observation.actorInstance = actor.GetInstance();
    observation.rightSourceInstance = rightInstance;
    observation.c1Generation = generation.generation;
    observation.actionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    observation.phaseBefore = static_cast<GEInt>(actor.GetCurrentAniPhase());
    observation.stateTimeBefore = actor.Routine.GetStateTime();
    observation.statePositionBefore = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    observation.rightUseTypeBefore = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(rightSource));
    observation.rightGroupBefore = static_cast<GEInt>(
        rightSource.GetCollisionGroup());
    observation.motionBefore = motion.GetText() != nullptr
        ? motion.GetText() : "<unavailable>";
    observation.rightNameBefore = rightSource.GetName().GetText();
}

static bool ShouldSuppressSprintCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
    SprintCallbackObservation *const scope =
        g_pCurrentSprintCallbackScope;
    if (scope == nullptr || !scope->active
        || scope->actionBefore != static_cast<GEInt>(gEAction_SprintAttack)
        || sourceInstance == nullptr
        || sourceInstance != scope->rightSourceInstance
        || requestedGroup != eECollisionGroup_Item_Attack
        || beforeGroup != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    Entity actor(scope->actorInstance);
    Entity rightSource(sourceInstance);
    if (actor == None || actor.GetInstance() != scope->actorInstance)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    if (action != gEAction_SprintAttack
        || static_cast<GEInt>(action) != scope->actionBefore
        || !FrameCollisionMarkers::IsAttackHit(
            actor, AttackFamily_Sprint)
        || rightSource == None
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (currentSources.rightInstance != sourceInstance)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    if (!generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation)
    {
        return false;
    }

    bool activationUsed = false;
    auto const existingProof =
        g_SprintEarlySuppressionProofs.find(scope->actorInstance);
    if (existingProof != g_SprintEarlySuppressionProofs.end()
        && existingProof->second.c1Generation == scope->c1Generation
        && existingProof->second.rightSourceInstance == sourceInstance)
    {
        activationUsed = existingProof->second.activationUsed;
    }

    SprintEarlySuppressionProof proof = {};
    proof.actorInstance = scope->actorInstance;
    proof.rightSourceInstance = sourceInstance;
    proof.c1Generation = scope->c1Generation;
    proof.rightUseType = gEUseType_PhysicalFist;
    proof.earlySuppressionProven = true;
    proof.activationUsed = activationUsed;
    g_SprintEarlySuppressionProofs[scope->actorInstance] = proof;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        GEInt const statePosition = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        GEFloat const stateTime = actor.Routine.GetStateTime();
        std::fprintf(
            log,
            "CORE RAW55_SPRINT_GROUP_SUPPRESSION Actor=%s C1=%llu Action=%d Right=%s RightUseType=%d RequestedGroup=%d BeforeGroup=%d StatePosition=%d StateTime=%.6f SUPPRESS_GROUP=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(scope->c1Generation),
            static_cast<GEInt>(action),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(requestedGroup),
            static_cast<GEInt>(beforeGroup), statePosition,
            static_cast<double>(stateTime));
        std::fflush(log);
    }

    return true;
}

static bool ShouldSuppressNormalCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
    NormalCallbackObservation *const scope =
        g_pCurrentNormalCallbackScope;
    if (scope == nullptr || !scope->active
        || scope->actionBefore != static_cast<GEInt>(gEAction_Attack)
        || sourceInstance == nullptr
        || sourceInstance != scope->rightSourceInstance
        || requestedGroup != eECollisionGroup_Item_Attack
        || beforeGroup != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    Entity actor(scope->actorInstance);
    Entity rightSource(sourceInstance);
    if (actor == None || actor.GetInstance() != scope->actorInstance)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    if (action != gEAction_Attack
        || static_cast<GEInt>(action) != scope->actionBefore
        || !FrameCollisionMarkers::IsAttackHit(
            actor, AttackFamily_Normal)
        || rightSource == None
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (currentSources.rightInstance != sourceInstance)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    if (!generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation)
    {
        return false;
    }

    bool activationUsed = false;
    auto const existingProof =
        g_NormalEarlySuppressionProofs.find(scope->actorInstance);
    if (existingProof != g_NormalEarlySuppressionProofs.end()
        && existingProof->second.c1Generation == scope->c1Generation
        && existingProof->second.rightSourceInstance == sourceInstance)
    {
        activationUsed = existingProof->second.activationUsed;
    }

    NormalEarlySuppressionProof proof = {};
    proof.actorInstance = scope->actorInstance;
    proof.rightSourceInstance = sourceInstance;
    proof.c1Generation = scope->c1Generation;
    proof.rightUseType = gEUseType_PhysicalFist;
    proof.earlySuppressionProven = true;
    proof.activationUsed = activationUsed;
    g_NormalEarlySuppressionProofs[scope->actorInstance] = proof;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        GEInt const statePosition = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        GEFloat const stateTime = actor.Routine.GetStateTime();
        std::fprintf(
            log,
            "CORE RAW55_NORMAL_GROUP_SUPPRESSION Actor=%s C1=%llu Action=%d Right=%s RightUseType=%d RequestedGroup=%d BeforeGroup=%d StatePosition=%d StateTime=%.6f SUPPRESS_GROUP=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(scope->c1Generation),
            static_cast<GEInt>(action),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(requestedGroup),
            static_cast<GEInt>(beforeGroup), statePosition,
            static_cast<double>(stateTime));
        std::fflush(log);
    }

    return true;
}

static bool ShouldSuppressNormalNativeRearmRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
    NormalCallbackObservation *const scope =
        g_pCurrentNormalCallbackScope;
    if (scope == nullptr || !scope->active
        || scope->actionBefore != static_cast<GEInt>(gEAction_Attack)
        || sourceInstance == nullptr
        || sourceInstance != scope->rightSourceInstance
        || requestedGroup != eECollisionGroup_Item_Attack
        || beforeGroup != eECollisionGroup_Item_Attack)
    {
        return false;
    }

    Entity actor(scope->actorInstance);
    Entity rightSource(sourceInstance);
    if (actor == None || actor.GetInstance() != scope->actorInstance)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    if (action != gEAction_Attack
        || static_cast<GEInt>(action) != scope->actionBefore
        || !FrameCollisionMarkers::IsAttackHit(
            actor, AttackFamily_Normal)
        || rightSource == None
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Attack
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (currentSources.rightInstance != sourceInstance)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    if (!generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation)
    {
        return false;
    }

    auto interventionIt =
        g_NormalPreStateFistInterventions.find(scope->actorInstance);
    if (interventionIt == g_NormalPreStateFistInterventions.end())
        return false;

    NormalPreStateFistIntervention &intervention = interventionIt->second;
    if (intervention.actorInstance != scope->actorInstance
        || intervention.rightSourceInstance != sourceInstance
        || intervention.c1Generation != scope->c1Generation
        || !intervention.preStateRearmProven
        || intervention.nativeRearmSuppressionUsed)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 0)
        return false;

    ObserveNormalTriggerState(
        "NATIVE_7TO7_SUPPRESS_PRE", actor, sourceInstance,
        scope->c1Generation, false);

    intervention.nativeRearmSuppressionUsed = true;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        GEFloat const stateTime = actor.Routine.GetStateTime();
        std::fprintf(
            log,
            "CORE RAW55_NORMAL_NATIVE_REARM_SUPPRESSION_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RequestedGroup=%d BeforeGroup=%d PreStateRearmProven=1 NATIVE_7TO7_SUPPRESS=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(scope->c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(requestedGroup),
            static_cast<GEInt>(beforeGroup));
        std::fflush(log);
    }

    return true;
}

static bool ShouldSuppressPowerCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
    PowerCallbackObservation *const scope =
        g_pCurrentPowerCallbackScope;
    if (scope == nullptr || !scope->active
        || scope->actionBefore != static_cast<GEInt>(gEAction_PowerAttack)
        || sourceInstance == nullptr
        || sourceInstance != scope->rightSourceInstance
        || requestedGroup != eECollisionGroup_Item_Attack
        || beforeGroup != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    Entity actor(scope->actorInstance);
    Entity rightSource(sourceInstance);
    if (actor == None || actor.GetInstance() != scope->actorInstance
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_PowerAttack
        || rightSource == None
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (currentSources.rightInstance != sourceInstance)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    if (!generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation)
    {
        return false;
    }

    bool activationUsed = false;
    bool repeatFistRearmUsed = false;
    auto const existingProof =
        g_PowerEarlySuppressionProofs.find(scope->actorInstance);
    if (existingProof != g_PowerEarlySuppressionProofs.end()
        && existingProof->second.c1Generation == scope->c1Generation
        && existingProof->second.rightSourceInstance == sourceInstance)
    {
        activationUsed = existingProof->second.activationUsed;
        repeatFistRearmUsed =
            existingProof->second.repeatFistRearmUsed;
    }

    PowerEarlySuppressionProof proof = {};
    proof.actorInstance = scope->actorInstance;
    proof.rightSourceInstance = sourceInstance;
    proof.c1Generation = scope->c1Generation;
    proof.rightUseType = gEUseType_PhysicalFist;
    proof.earlySuppressionProven = true;
    proof.activationUsed = activationUsed;
    proof.repeatFistRearmUsed = repeatFistRearmUsed;
    g_PowerEarlySuppressionProofs[scope->actorInstance] = proof;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        GEInt const statePosition = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        GEFloat const stateTime = actor.Routine.GetStateTime();
        std::fprintf(
            log,
            "CORE RAW55_POWER_GROUP_SUPPRESSION Actor=%s C1=%llu Action=%d Right=%s RightUseType=%d RequestedGroup=%d BeforeGroup=%d StatePosition=%d StateTime=%.6f SUPPRESS_GROUP=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(scope->c1Generation),
            static_cast<GEInt>(gEAction_PowerAttack),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(requestedGroup),
            static_cast<GEInt>(beforeGroup), statePosition,
            static_cast<double>(stateTime));
        std::fflush(log);
    }

    return true;
}

bool ShouldSuppressCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
    if (ShouldSuppressPowerCollisionGroupRequest(
            sourceInstance, requestedGroup, beforeGroup))
    {
        return true;
    }

    if (ShouldSuppressSprintCollisionGroupRequest(
            sourceInstance, requestedGroup, beforeGroup))
    {
        return true;
    }

    if (ShouldSuppressNormalCollisionGroupRequest(
            sourceInstance, requestedGroup, beforeGroup))
    {
        return true;
    }

    if (ShouldSuppressNormalNativeRearmRequest(
            sourceInstance, requestedGroup, beforeGroup))
    {
        return true;
    }

    QuickCallbackObservation *const scope =
        g_pCurrentQuickCallbackScope;
    if (scope == nullptr || !scope->active
        || sourceInstance == nullptr
        || sourceInstance != scope->rightSourceInstance
        || requestedGroup != eECollisionGroup_Item_Attack
        || beforeGroup != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    Entity actor(scope->actorInstance);
    Entity rightSource(sourceInstance);
    if (actor == None || actor.GetInstance() != scope->actorInstance
        || rightSource == None
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (currentSources.rightInstance != sourceInstance)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    if (!generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation)
    {
        return false;
    }

    bool activationUsed = false;
    auto const existingProof =
        g_QuickEarlySuppressionProofs.find(scope->actorInstance);
    if (existingProof != g_QuickEarlySuppressionProofs.end()
        && existingProof->second.c1Generation == scope->c1Generation
        && existingProof->second.rightSourceInstance == sourceInstance)
    {
        activationUsed = existingProof->second.activationUsed;
    }

    QuickEarlySuppressionProof proof = {};
    proof.actorInstance = scope->actorInstance;
    proof.rightSourceInstance = sourceInstance;
    proof.c1Generation = scope->c1Generation;
    proof.rightUseType = gEUseType_PhysicalFist;
    proof.earlySuppressionProven = true;
    proof.activationUsed = activationUsed;
    g_QuickEarlySuppressionProofs[scope->actorInstance] = proof;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        GEInt const statePosition = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        GEFloat const stateTime = actor.Routine.GetStateTime();
        std::fprintf(
            log,
            "CORE RAW55_QUICK_GROUP_SUPPRESSION Actor=%s C1=%llu Right=%s RightUseType=%d RequestedGroup=%d BeforeGroup=%d StatePosition=%d StateTime=%.6f SUPPRESS_GROUP=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(scope->c1Generation),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(requestedGroup),
            static_cast<GEInt>(beforeGroup), statePosition,
            static_cast<double>(stateTime));
        std::fflush(log);
    }

    return true;
}

static bool WasPreStateFistInterventionUsed(
    eCEntity *actorInstance, eCEntity *rightSourceInstance,
    std::uint64_t c1Generation)
{
    auto const found =
        g_QuickPreStateFistInterventions.find(actorInstance);
    return found != g_QuickPreStateFistInterventions.end()
        && found->second.actorInstance == actorInstance
        && found->second.rightSourceInstance == rightSourceInstance
        && found->second.c1Generation == c1Generation
        && found->second.interventionUsed;
}

static bool TryApplyPreStateFistProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Quick)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || currentSources.rightInstance == nullptr
        || result.sources.rightInstance != currentSources.rightInstance)
    {
        return false;
    }

    Entity rightSource(currentSources.rightInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 0
        || WasPreStateFistInterventionUsed(
            actorInstance, currentSources.rightInstance,
            generation.generation))
    {
        return false;
    }

    QuickPreStateFistIntervention intervention = {};
    intervention.actorInstance = actorInstance;
    intervention.rightSourceInstance = currentSources.rightInstance;
    intervention.c1Generation = generation.generation;
    intervention.interventionUsed = true;
    g_QuickPreStateFistInterventions[actorInstance] = intervention;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const groupBefore = rightSource.GetCollisionGroup();
    rightSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
    eECollisionGroup const groupAfter = rightSource.GetCollisionGroup();
    bool triggeredListCleared = false;
    if (groupAfter == eECollisionGroup_Item_Attack)
    {
        rightSource.TouchDamage.ClearTriggeredList();
        triggeredListCleared = true;
        g_QuickPreStateFistInterventions[actorInstance]
            .preStateFistProven = true;
    }

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_QUICK_PRESTATE_FIST_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d RequestedGroup=%d GroupAfter=%d ClearTriggeredList=%d PRESTATE_FIST=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(generation.generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(groupBefore),
            static_cast<GEInt>(eECollisionGroup_Item_Attack),
            static_cast<GEInt>(groupAfter),
            triggeredListCleared ? 1 : 0);
        std::fflush(log);
    }

    return true;
}

static void LogRepeatFistEligibility(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return;

    eCEntity *const actorInstance = actor.GetInstance();
    auto interventionIt =
        g_QuickPreStateFistInterventions.find(actorInstance);
    if (interventionIt == g_QuickPreStateFistInterventions.end())
        return;

    // Keep this diagnostic bounded to authored FIST marker dispatches. The
    // existing intervention record is the factual first-FIST sequence anchor.
    if (markerOpcode != MarkerOpcode_Fist)
        return;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    QuickPreStateFistIntervention const &intervention =
        interventionIt->second;
    CurrentMotionMarkerResult const &decision = result.decision;
    bool const currentC1Valid = generation.valid;
    bool const currentC1ActorMatches =
        generation.actorInstance == actorInstance;
    bool const sameC1 = currentC1Valid && currentC1ActorMatches
        && generation.generation == intervention.c1Generation;
    bool const storedActorMatches =
        intervention.actorInstance == actorInstance;
    bool const sameRight =
        currentSources.rightInstance == intervention.rightSourceInstance;
    bool const resultRightMatchesStored =
        result.sources.rightInstance == intervention.rightSourceInstance;
    bool const quickHit =
        FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Quick);
    bool const raw8ResolverAbsent =
        CollisionSources::ResolveFistCollisionSource(actor) == nullptr;
    Entity rightSource(currentSources.rightInstance);
    bool const rightValid = rightSource != None;
    GEInt const rightUseType = rightValid
        ? static_cast<GEInt>(
              CollisionSources::GetCollisionSourceUseType(rightSource))
        : -1;
    GEInt const rightGroup = rightValid
        ? static_cast<GEInt>(rightSource.GetCollisionGroup()) : -1;
    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    GEInt const action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEFloat const stateTime = actor.Routine.GetStateTime();
    bool const mixedMarkers =
        decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0;

    char const *firstFailedGate = "NONE";
    bool eligible = false;
    if (!currentC1Valid)
        firstFailedGate = "NO_CURRENT_C1";
    else if (!currentC1ActorMatches)
        firstFailedGate = "CURRENT_C1_ACTOR_MISMATCH";
    else if (!sameC1)
        firstFailedGate = "C1_MISMATCH";
    else if (!storedActorMatches)
        firstFailedGate = "STORED_ACTOR_MISMATCH";
    else if (!sameRight)
        firstFailedGate = "SOURCE_MISMATCH";
    else if (!intervention.interventionUsed)
        firstFailedGate = "FIRST_INTERVENTION_UNUSED";
    else if (!intervention.preStateFistProven)
        firstFailedGate = "FIRST_PROOF_MISSING";
    else if (intervention.laterFistRearmUsed)
        firstFailedGate = "LATER_ALREADY_USED";
    else if (result.opcode != MarkerOpcode_Fist)
        firstFailedGate = "WRONG_OPCODE";
    else if (result.code != MarkerResult_UnsupportedMissingSource)
        firstFailedGate = "WRONG_RESULT";
    else if (!quickHit)
        firstFailedGate = "NOT_QUICK_HIT";
    else if (!decision.foundMatchingMotion)
        firstFailedGate = "MOTION_NOT_FOUND";
    else if (!decision.scanValid)
        firstFailedGate = "SCAN_INVALID";
    else if (!decision.markerPresent)
        firstFailedGate = "MARKER_NOT_PRESENT";
    else if (!decision.hasFistMarkers)
        firstFailedGate = "NO_FIST";
    else if (decision.markerCounts[MarkerOpcode_Fist] != 2)
        firstFailedGate = "FIST_COUNT_NOT_TWO";
    else if (mixedMarkers)
        firstFailedGate = "MIXED_MARKERS";
    else if (decision.requiredSourceMask != SourceMask_None)
        firstFailedGate = "REQUIRED_MASK_NONZERO";
    else if (!raw8ResolverAbsent)
        firstFailedGate = "RAW8_PRESENT";
    else if (!resultRightMatchesStored)
        firstFailedGate = "RESULT_RIGHT_MISMATCH";
    else if (!rightValid)
        firstFailedGate = "RIGHT_INVALID";
    else if (rightUseType != static_cast<GEInt>(gEUseType_PhysicalFist))
        firstFailedGate = "RIGHT_NOT_RAW55";
    else if (rightGroup != static_cast<GEInt>(eECollisionGroup_Item_Attack))
        firstFailedGate = "RIGHT_NOT_GROUP7";
    else if (statePosition != 1)
        firstFailedGate = "STATEPOSITION_NOT_ONE";
    else
        eligible = true;

    FILE *const eligibilityLog = CollisionDiagnostics::GetLog();
    if (eligibilityLog != nullptr)
    {
        std::fprintf(
            eligibilityLog,
            "CORE RAW55_QUICK_REPEAT_FIST_ELIGIBILITY Actor=%s Action=%d StatePosition=%d StateTime=%.6f MarkerOpcode=%d ResultOpcode=%d ResultCode=%d CurrentC1Valid=%d CurrentC1=%llu StoredC1=%llu SameC1=%d CurrentRight=%p StoredRight=%p SameRight=%d ResultRightMatchesStored=%d RightUseType=%d RightGroup=%d InterventionUsed=%d PreStateFistProven=%d LaterFistRearmUsed=%d DecisionFoundMotion=%d DecisionScanValid=%d DecisionMarkerPresent=%d DecisionHasFist=%d DecisionFistCount=%d DecisionRightCount=%d DecisionLeftCount=%d DecisionBothCount=%d DecisionOffCount=%d RequiredSourceMask=%u Raw8ResolverAbsent=%d QuickHit=%d Eligible=%d FirstFailedGate=%s\n",
            actor.GetName().GetText(), action, statePosition,
            static_cast<double>(stateTime),
            static_cast<GEInt>(markerOpcode),
            static_cast<GEInt>(result.opcode),
            static_cast<GEInt>(result.code), currentC1Valid ? 1 : 0,
            static_cast<unsigned long long>(generation.generation),
            static_cast<unsigned long long>(intervention.c1Generation),
            sameC1 ? 1 : 0,
            static_cast<void *>(currentSources.rightInstance),
            static_cast<void *>(intervention.rightSourceInstance),
            sameRight ? 1 : 0, resultRightMatchesStored ? 1 : 0,
            rightUseType, rightGroup,
            intervention.interventionUsed ? 1 : 0,
            intervention.preStateFistProven ? 1 : 0,
            intervention.laterFistRearmUsed ? 1 : 0,
            decision.foundMatchingMotion ? 1 : 0,
            decision.scanValid ? 1 : 0,
            decision.markerPresent ? 1 : 0,
            decision.hasFistMarkers ? 1 : 0,
            decision.markerCounts[MarkerOpcode_Fist],
            decision.markerCounts[MarkerOpcode_Right],
            decision.markerCounts[MarkerOpcode_Left],
            decision.markerCounts[MarkerOpcode_Both],
            decision.markerCounts[MarkerOpcode_Off],
            static_cast<unsigned int>(decision.requiredSourceMask),
            raw8ResolverAbsent ? 1 : 0, quickHit ? 1 : 0,
            eligible ? 1 : 0, firstFailedGate);
        std::fflush(eligibilityLog);
    }
}

static bool TryApplyRepeatFistRearmProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    auto interventionIt =
        g_QuickPreStateFistInterventions.find(actorInstance);
    if (interventionIt == g_QuickPreStateFistInterventions.end())
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    QuickPreStateFistIntervention &intervention = interventionIt->second;
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != intervention.c1Generation
        || intervention.actorInstance != actorInstance
        || currentSources.rightInstance != intervention.rightSourceInstance
        || !intervention.interventionUsed
        || !intervention.preStateFistProven
        || intervention.laterFistRearmUsed
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Quick)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] != 2
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || result.sources.rightInstance != intervention.rightSourceInstance)
    {
        return false;
    }

    Entity rightSource(intervention.rightSourceInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Attack)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 1)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const rightGroup = rightSource.GetCollisionGroup();
    intervention.laterFistRearmUsed = true;
    rightSource.TouchDamage.ClearTriggeredList();

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_QUICK_REPEAT_FIST_REARM_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d DecisionFistCount=%d FirstPreStateProof=1 LaterDispatchOrdinal=2 ClearTriggeredList=1 REPEAT_FIST_REARM=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(generation.generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(rightGroup),
            decision.markerCounts[MarkerOpcode_Fist]);
        std::fflush(log);
    }

    return true;
}

static bool TryApplyNormalFistActivationProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    auto proofIt = g_NormalEarlySuppressionProofs.find(actorInstance);
    if (proofIt == g_NormalEarlySuppressionProofs.end())
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    NormalEarlySuppressionProof &proof = proofIt->second;
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != proof.c1Generation
        || proof.actorInstance != actorInstance
        || currentSources.rightInstance != proof.rightSourceInstance
        || !proof.earlySuppressionProven || proof.activationUsed
        || proof.rightUseType != gEUseType_PhysicalFist
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_Attack
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Normal)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr)
    {
        return false;
    }

    Entity rightSource(proof.rightSourceInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 1)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const groupBefore = rightSource.GetCollisionGroup();
    proof.activationUsed = true;
    rightSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
    eECollisionGroup const groupAfter = rightSource.GetCollisionGroup();

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_NORMAL_FIST_ACTIVATION_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d RequestedGroup=%d GroupAfter=%d EarlySuppressionProof=1 ClearTriggeredList=0 ACTIVATE_FIST=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(proof.c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(groupBefore),
            static_cast<GEInt>(eECollisionGroup_Item_Attack),
            static_cast<GEInt>(groupAfter));
        std::fflush(log);
    }

    return true;
}

static bool WasNormalPreStateFistInterventionUsed(
    eCEntity *actorInstance, eCEntity *rightSourceInstance,
    std::uint64_t c1Generation)
{
    auto const found =
        g_NormalPreStateFistInterventions.find(actorInstance);
    return found != g_NormalPreStateFistInterventions.end()
        && found->second.actorInstance == actorInstance
        && found->second.rightSourceInstance == rightSourceInstance
        && found->second.c1Generation == c1Generation;
}

static bool TryApplyNormalPreStateFistProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_Attack
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Normal)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || currentSources.rightInstance == nullptr
        || result.sources.rightInstance != currentSources.rightInstance)
    {
        return false;
    }

    Entity rightSource(currentSources.rightInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 0
        || WasNormalPreStateFistInterventionUsed(
            actorInstance, currentSources.rightInstance,
            generation.generation))
    {
        return false;
    }

    NormalPreStateFistIntervention intervention = {};
    intervention.actorInstance = actorInstance;
    intervention.rightSourceInstance = currentSources.rightInstance;
    intervention.c1Generation = generation.generation;
    g_NormalPreStateFistInterventions[actorInstance] = intervention;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const groupBefore = rightSource.GetCollisionGroup();
    rightSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
    eECollisionGroup const groupAfter = rightSource.GetCollisionGroup();
    bool triggeredListCleared = false;
    if (groupAfter == eECollisionGroup_Item_Attack)
    {
        rightSource.TouchDamage.ClearTriggeredList();
        triggeredListCleared = true;
        g_NormalPreStateFistInterventions[actorInstance]
            .preStateRearmProven = true;
        ObserveNormalTriggerState(
            "POST_PRESTATE_REARM", actor,
            currentSources.rightInstance, generation.generation, false);
    }

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_NORMAL_PRESTATE_FIST_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d RequestedGroup=%d GroupAfter=%d ClearTriggeredList=%d PRESTATE_FIST=1 PRESTATE_REARM=%d\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(generation.generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(groupBefore),
            static_cast<GEInt>(eECollisionGroup_Item_Attack),
            static_cast<GEInt>(groupAfter),
            triggeredListCleared ? 1 : 0,
            triggeredListCleared ? 1 : 0);
        std::fflush(log);
    }

    return true;
}

static bool TryApplyPowerFistActivationProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    auto proofIt = g_PowerEarlySuppressionProofs.find(actorInstance);
    if (proofIt == g_PowerEarlySuppressionProofs.end())
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    PowerEarlySuppressionProof &proof = proofIt->second;
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != proof.c1Generation
        || proof.actorInstance != actorInstance
        || currentSources.rightInstance != proof.rightSourceInstance
        || !proof.earlySuppressionProven || proof.activationUsed
        || proof.rightUseType != gEUseType_PhysicalFist
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_PowerAttack
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Power)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || result.sources.rightInstance != proof.rightSourceInstance)
    {
        return false;
    }

    Entity rightSource(proof.rightSourceInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 1)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const groupBefore = rightSource.GetCollisionGroup();
    proof.activationUsed = true;
    rightSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
    eECollisionGroup const groupAfter = rightSource.GetCollisionGroup();

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_POWER_FIST_ACTIVATION_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d RequestedGroup=%d GroupAfter=%d EarlySuppressionProof=1 ClearTriggeredList=0 ACTIVATE_FIST=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(proof.c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(groupBefore),
            static_cast<GEInt>(eECollisionGroup_Item_Attack),
            static_cast<GEInt>(groupAfter));
        std::fflush(log);
    }

    return true;
}

static bool TryApplyPowerRepeatFistRearmProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    auto proofIt = g_PowerEarlySuppressionProofs.find(actorInstance);
    if (proofIt == g_PowerEarlySuppressionProofs.end())
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    PowerEarlySuppressionProof &proof = proofIt->second;
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != proof.c1Generation
        || proof.actorInstance != actorInstance
        || currentSources.rightInstance != proof.rightSourceInstance
        || !proof.earlySuppressionProven || !proof.activationUsed
        || proof.repeatFistRearmUsed
        || proof.rightUseType != gEUseType_PhysicalFist
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_PowerAttack
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Power)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] != 2
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || result.sources.rightInstance != proof.rightSourceInstance)
    {
        return false;
    }

    Entity rightSource(proof.rightSourceInstance);
    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Attack
        || statePosition != 1)
    {
        return false;
    }

    NormalTriggerStateSnapshot before = {};
    bool const preStateCaptured = TryCaptureTriggerState(
        proof.rightSourceInstance, before);
    bool const preClearContactProven = preStateCaptured
        && before.countsAligned == 1
        && before.playerResolved == 1
        && before.playerPresent == 1
        && before.playerEntryCount == 1
        && before.playerVisitCount >= 1;
    if (!preClearContactProven)
    {
        FILE *const log = CollisionDiagnostics::GetLog();
        if (log != nullptr)
        {
            std::fprintf(
                log,
                "CORE RAW55_POWER_REPEAT_FIST_REARM_CANDIDATE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d DecisionFistCount=%d EarlySuppressionProof=1 FirstActivationUsed=1 PreStateCaptured=%d PlayerResolvedBefore=%d PlayerPresentBefore=%d PlayerEntryCountBefore=%d PlayerVisitCountBefore=%d CountsAlignedBefore=%d ClearTriggeredList=0 REPEAT_FIST_REARM=0\n",
                actor.GetName().GetText(),
                static_cast<unsigned long long>(proof.c1Generation),
                static_cast<GEInt>(gEAction_PowerAttack), statePosition,
                static_cast<double>(actor.Routine.GetStateTime()),
                rightSource.GetName().GetText(),
                static_cast<GEInt>(
                    CollisionSources::GetCollisionSourceUseType(
                        rightSource)),
                static_cast<GEInt>(rightSource.GetCollisionGroup()),
                decision.markerCounts[MarkerOpcode_Fist],
                preStateCaptured ? 1 : 0, before.playerResolved,
                before.playerPresent, before.playerEntryCount,
                before.playerVisitCount, before.countsAligned);
            std::fflush(log);
        }
        return false;
    }

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    gEUseType const rightUseType =
        CollisionSources::GetCollisionSourceUseType(rightSource);
    eECollisionGroup const rightGroup = rightSource.GetCollisionGroup();

    proof.repeatFistRearmUsed = true;
    rightSource.TouchDamage.ClearTriggeredList();

    NormalTriggerStateSnapshot after = {};
    after.playerVisitCount = -1;
    bool const postStateCaptured = TryCaptureTriggerState(
        proof.rightSourceInstance, after);

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_POWER_REPEAT_FIST_REARM_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d DecisionFistCount=%d EarlySuppressionProof=1 FirstActivationUsed=1 PlayerPresentBefore=%d PlayerEntryCountBefore=%d PlayerVisitCountBefore=%d CountsAlignedBefore=%d PostStateCaptured=%d PlayerPresentAfter=%d PlayerEntryCountAfter=%d PlayerVisitCountAfter=%d CountsAlignedAfter=%d ClearTriggeredList=1 REPEAT_FIST_REARM=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(proof.c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(rightUseType),
            static_cast<GEInt>(rightGroup),
            decision.markerCounts[MarkerOpcode_Fist],
            before.playerPresent, before.playerEntryCount,
            before.playerVisitCount, before.countsAligned,
            postStateCaptured ? 1 : 0,
            after.playerPresent, after.playerEntryCount,
            after.playerVisitCount, after.countsAligned);
        std::fflush(log);
    }

    return true;
}

static bool TryApplySprintFistActivationProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    auto proofIt = g_SprintEarlySuppressionProofs.find(actorInstance);
    if (proofIt == g_SprintEarlySuppressionProofs.end())
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    SprintEarlySuppressionProof &proof = proofIt->second;
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != proof.c1Generation
        || proof.actorInstance != actorInstance
        || currentSources.rightInstance != proof.rightSourceInstance
        || !proof.earlySuppressionProven || proof.activationUsed
        || proof.rightUseType != gEUseType_PhysicalFist
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_SprintAttack
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Sprint)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr)
    {
        return false;
    }

    Entity rightSource(proof.rightSourceInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 1)
        return false;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const groupBefore = rightSource.GetCollisionGroup();
    proof.activationUsed = true;
    rightSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
    eECollisionGroup const groupAfter = rightSource.GetCollisionGroup();

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d RequestedGroup=%d GroupAfter=%d EarlySuppressionProof=1 ClearTriggeredList=0 ACTIVATE_FIST=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(proof.c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(groupBefore),
            static_cast<GEInt>(eECollisionGroup_Item_Attack),
            static_cast<GEInt>(groupAfter));
        std::fflush(log);
    }

    return true;
}

static void TryApplyNormalMarker2ReplacementClearProbe(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return;

    eCEntity *const actorInstance = actor.GetInstance();
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    CurrentMotionMarkerResult const &decision = result.decision;
    if (!generation.valid || generation.actorInstance != actorInstance
        || markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            != gEAction_Attack
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Normal)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] != 2
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || currentSources.rightInstance == nullptr
        || result.sources.rightInstance != currentSources.rightInstance)
    {
        return;
    }

    Entity rightSource(currentSources.rightInstance);
    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Attack
        || statePosition != 1)
    {
        return;
    }

    NormalPreStateFistIntervention *intervention = nullptr;
    if (!TryResolveProvenNormalPreStateIntervention(
            actor, currentSources.rightInstance, generation.generation,
            intervention)
        || !intervention->preStateRearmProven
        || !intervention->nativeRearmSuppressionUsed
        || !intervention->nativeTriggerClearSuppressionUsed
        || intervention->marker2ReplacementClearUsed)
    {
        return;
    }

    NormalTriggerStateSnapshot before = {};
    if (!TryCaptureNormalTriggerState(*intervention, before)
        || before.countsAligned != 1
        || before.playerResolved != 1
        || before.playerPresent != 1
        || before.playerEntryCount != 1
        || before.playerVisitCount < 1)
    {
        return;
    }

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    gEUseType const rightUseType =
        CollisionSources::GetCollisionSourceUseType(rightSource);
    eECollisionGroup const rightGroup = rightSource.GetCollisionGroup();

    intervention->marker2ReplacementClearUsed = true;
    rightSource.TouchDamage.ClearTriggeredList();

    NormalTriggerStateSnapshot after = {};
    after.playerVisitCount = -1;
    bool const postStateCaptured =
        TryCaptureNormalTriggerState(*intervention, after);

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d RightGroup=%d PreStateRearmProven=1 Native7To7SuppressionUsed=1 NativeClearSuppressionUsed=1 PlayerPresentBefore=%d PlayerEntryCountBefore=%d PlayerVisitCountBefore=%d CountsAlignedBefore=%d PostStateCaptured=%d PlayerPresentAfter=%d PlayerEntryCountAfter=%d PlayerVisitCountAfter=%d CountsAlignedAfter=%d DecisionFistCount=%d MARKER2_REPLACEMENT_CLEAR=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(generation.generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(rightUseType),
            static_cast<GEInt>(rightGroup),
            before.playerPresent, before.playerEntryCount,
            before.playerVisitCount, before.countsAligned,
            postStateCaptured ? 1 : 0,
            after.playerPresent, after.playerEntryCount,
            after.playerVisitCount, after.countsAligned,
            decision.markerCounts[MarkerOpcode_Fist]);
        std::fflush(log);
    }
}

void OnMarkerProcessed(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return;

    TryApplyNormalMarker2ReplacementClearProbe(
        actor, markerOpcode, result);

    if (TryApplyNormalFistActivationProbe(actor, markerOpcode, result))
        return;

    if (TryApplyNormalPreStateFistProbe(actor, markerOpcode, result))
        return;

    if (TryApplyPowerFistActivationProbe(actor, markerOpcode, result))
        return;

    if (TryApplyPowerRepeatFistRearmProbe(
            actor, markerOpcode, result))
    {
        return;
    }

    if (TryApplySprintFistActivationProbe(actor, markerOpcode, result))
        return;

    if (TryApplyPreStateFistProbe(actor, markerOpcode, result))
        return;

    LogRepeatFistEligibility(actor, markerOpcode, result);

    if (TryApplyRepeatFistRearmProbe(actor, markerOpcode, result))
        return;

    eCEntity *const actorInstance = actor.GetInstance();
    auto proofIt = g_QuickEarlySuppressionProofs.find(actorInstance);
    if (proofIt == g_QuickEarlySuppressionProofs.end())
        return;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    QuickEarlySuppressionProof &proof = proofIt->second;
    if (!generation.valid || generation.actorInstance != actorInstance
        || generation.generation != proof.c1Generation
        || proof.actorInstance != actorInstance
        || currentSources.rightInstance != proof.rightSourceInstance)
    {
        g_QuickEarlySuppressionProofs.erase(proofIt);
        return;
    }

    if (WasPreStateFistInterventionUsed(
            actorInstance, proof.rightSourceInstance,
            proof.c1Generation))
    {
        return;
    }

    CurrentMotionMarkerResult const &decision = result.decision;
    if (markerOpcode != MarkerOpcode_Fist
        || result.opcode != MarkerOpcode_Fist
        || result.code != MarkerResult_UnsupportedMissingSource
        || !FrameCollisionMarkers::IsAttackHit(actor, AttackFamily_Quick)
        || !decision.foundMatchingMotion || !decision.scanValid
        || !decision.markerPresent || !decision.hasFistMarkers
        || decision.markerCounts[MarkerOpcode_Fist] <= 0
        || decision.markerCounts[MarkerOpcode_Right] != 0
        || decision.markerCounts[MarkerOpcode_Left] != 0
        || decision.markerCounts[MarkerOpcode_Both] != 0
        || decision.markerCounts[MarkerOpcode_Off] != 0
        || decision.requiredSourceMask != SourceMask_None
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || result.sources.rightInstance != proof.rightSourceInstance
        || !proof.earlySuppressionProven || proof.activationUsed
        || proof.rightUseType != gEUseType_PhysicalFist)
    {
        return;
    }

    Entity rightSource(proof.rightSourceInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return;
    }

    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    if (statePosition != 1)
        return;

    gEAction const action =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    GEFloat const stateTime = actor.Routine.GetStateTime();
    eECollisionGroup const groupBefore = rightSource.GetCollisionGroup();
    proof.activationUsed = true;
    rightSource.SetCollisionGroup(eECollisionGroup_Item_Attack);
    eECollisionGroup const groupAfter = rightSource.GetCollisionGroup();
    bool triggeredListCleared = false;
    if (groupAfter == eECollisionGroup_Item_Attack)
    {
        rightSource.TouchDamage.ClearTriggeredList();
        triggeredListCleared = true;
    }

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(
            log,
            "CORE RAW55_QUICK_FIST_REARM_PROBE Actor=%s C1=%llu Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d RequestedGroup=%d GroupAfter=%d EarlySuppressionProof=1 ClearTriggeredList=%d REARM_PROBE=1\n",
            actor.GetName().GetText(),
            static_cast<unsigned long long>(proof.c1Generation),
            static_cast<GEInt>(action), statePosition,
            static_cast<double>(stateTime),
            rightSource.GetName().GetText(),
            static_cast<GEInt>(
                CollisionSources::GetCollisionSourceUseType(rightSource)),
            static_cast<GEInt>(groupBefore),
            static_cast<GEInt>(eECollisionGroup_Item_Attack),
            static_cast<GEInt>(groupAfter),
            triggeredListCleared ? 1 : 0);
        std::fflush(log);
    }
}

void EndQuickCallbackObservation(
    Entity &actor, QuickCallbackObservation &observation,
    GEBool nativeResult)
{
    if (g_pCurrentQuickCallbackScope == &observation)
        g_pCurrentQuickCallbackScope = observation.previousScope;

    if (!observation.active || actor == None
        || actor.GetInstance() != observation.actorInstance)
    {
        return;
    }

    Entity rightSource(observation.rightSourceInstance);
    GEInt const rightUseType = rightSource != None
        ? static_cast<GEInt>(
              CollisionSources::GetCollisionSourceUseType(rightSource))
        : -1;
    GEInt const rightGroupAfter = rightSource != None
        ? static_cast<GEInt>(rightSource.GetCollisionGroup()) : -1;
    GEInt const actionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt const phaseAfter = static_cast<GEInt>(actor.GetCurrentAniPhase());
    GEFloat const stateTimeAfter = actor.Routine.GetStateTime();
    GEInt const statePositionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    bCString const motionAfter = actor.NPC.GetCurrentMovementAni();

    CollisionLifecycleGuard::GenerationToken const generationAfter =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actor.GetInstance());
    bool const sameGeneration = generationAfter.valid
        && generationAfter.generation == observation.c1Generation;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(
        log,
        "CORE RAW55_QUICK_CALLBACK_BOUNDARY Actor=%s C1=%llu SameC1=%d Action=%d->%d Phase=%d->%d StateTime=%.6f->%.6f StatePosition=%d->%d MotionBefore=%s MotionAfter=%s Right=%s RightUseType=%d RightGroup=%d->%d NativeResult=%d OBSERVE_NATIVE=1\n",
        actor.GetName().GetText(),
        static_cast<unsigned long long>(observation.c1Generation),
        sameGeneration ? 1 : 0,
        observation.actionBefore, actionAfter,
        observation.phaseBefore, phaseAfter,
        static_cast<double>(observation.stateTimeBefore),
        static_cast<double>(stateTimeAfter),
        observation.statePositionBefore, statePositionAfter,
        observation.motionBefore.c_str(),
        motionAfter.GetText() != nullptr
            ? motionAfter.GetText() : "<unavailable>",
        rightSource != None ? rightSource.GetName().GetText() : "<none>",
        rightUseType, observation.rightGroupBefore, rightGroupAfter,
        static_cast<GEInt>(nativeResult));
    std::fflush(log);
}

void EndNormalCallbackObservation(
    Entity &actor, NormalCallbackObservation &observation,
    GEBool nativeResult)
{
    if (g_pCurrentNormalCallbackScope == &observation)
        g_pCurrentNormalCallbackScope = observation.previousScope;

    if (!observation.active || actor == None
        || actor.GetInstance() != observation.actorInstance)
    {
        return;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    bool const sameRight = currentSources.rightInstance
        == observation.rightSourceInstance;
    Entity rightSource(observation.rightSourceInstance);
    GEInt const rightGroupAfter = rightSource != None
        ? static_cast<GEInt>(rightSource.GetCollisionGroup()) : -1;
    GEInt const actionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt const phaseAfter = static_cast<GEInt>(actor.GetCurrentAniPhase());
    GEFloat const stateTimeAfter = actor.Routine.GetStateTime();
    GEInt const statePositionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    bCString const motionAfter = actor.NPC.GetCurrentMovementAni();

    CollisionLifecycleGuard::GenerationToken const generationAfter =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actor.GetInstance());
    bool const sameGeneration = generationAfter.valid
        && generationAfter.generation == observation.c1Generation;

    if (sameGeneration && sameRight)
    {
        if (observation.statePositionBefore == 0
            && statePositionAfter == 1)
        {
            ObserveNormalTriggerState(
                "SP0_TO1_POST_CALLBACK", actor,
                observation.rightSourceInstance,
                observation.c1Generation, false);
        }
        else
        {
            ObserveNormalTriggerState(
                "CALLBACK_CHANGE", actor,
                observation.rightSourceInstance,
                observation.c1Generation, true);
        }
    }

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(
        log,
        "CORE RAW55_NORMAL_CALLBACK_BOUNDARY Actor=%s C1=%llu SameC1=%d SameRight=%d Action=%d->%d Phase=%d->%d StateTime=%.6f->%.6f StatePosition=%d->%d MotionBefore=%s MotionAfter=%s Right=%s RightUseType=%d RightGroup=%d->%d NativeResult=%d OBSERVE_NATIVE=1\n",
        actor.GetName().GetText(),
        static_cast<unsigned long long>(observation.c1Generation),
        sameGeneration ? 1 : 0, sameRight ? 1 : 0,
        observation.actionBefore, actionAfter,
        observation.phaseBefore, phaseAfter,
        static_cast<double>(observation.stateTimeBefore),
        static_cast<double>(stateTimeAfter),
        observation.statePositionBefore, statePositionAfter,
        observation.motionBefore.c_str(),
        motionAfter.GetText() != nullptr
            ? motionAfter.GetText() : "<unavailable>",
        observation.rightNameBefore.c_str(),
        observation.rightUseTypeBefore,
        observation.rightGroupBefore, rightGroupAfter,
        static_cast<GEInt>(nativeResult));
    std::fflush(log);
}

void EndPowerCallbackObservation(
    Entity &actor, PowerCallbackObservation &observation,
    GEBool nativeResult)
{
    if (g_pCurrentPowerCallbackScope == &observation)
        g_pCurrentPowerCallbackScope = observation.previousScope;

    if (!observation.active || actor == None
        || actor.GetInstance() != observation.actorInstance)
    {
        return;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    bool const sameRight = currentSources.rightInstance
        == observation.rightSourceInstance;
    Entity rightSource(observation.rightSourceInstance);
    GEInt const rightGroupAfter = rightSource != None
        ? static_cast<GEInt>(rightSource.GetCollisionGroup()) : -1;
    GEInt const actionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt const phaseAfter = static_cast<GEInt>(actor.GetCurrentAniPhase());
    GEFloat const stateTimeAfter = actor.Routine.GetStateTime();
    GEInt const statePositionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    bCString const motionAfter = actor.NPC.GetCurrentMovementAni();

    CollisionLifecycleGuard::GenerationToken const generationAfter =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actor.GetInstance());
    bool const sameGeneration = generationAfter.valid
        && generationAfter.generation == observation.c1Generation;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(
        log,
        "CORE RAW55_POWER_CALLBACK_BOUNDARY Actor=%s C1=%llu SameC1=%d SameRight=%d Action=%d->%d Phase=%d->%d StateTime=%.6f->%.6f StatePosition=%d->%d MotionBefore=%s MotionAfter=%s Right=%s RightUseType=%d RightGroup=%d->%d NativeResult=%d OBSERVE_NATIVE=1\n",
        actor.GetName().GetText(),
        static_cast<unsigned long long>(observation.c1Generation),
        sameGeneration ? 1 : 0, sameRight ? 1 : 0,
        observation.actionBefore, actionAfter,
        observation.phaseBefore, phaseAfter,
        static_cast<double>(observation.stateTimeBefore),
        static_cast<double>(stateTimeAfter),
        observation.statePositionBefore, statePositionAfter,
        observation.motionBefore.c_str(),
        motionAfter.GetText() != nullptr
            ? motionAfter.GetText() : "<unavailable>",
        observation.rightNameBefore.c_str(),
        observation.rightUseTypeBefore,
        observation.rightGroupBefore, rightGroupAfter,
        static_cast<GEInt>(nativeResult));
    std::fflush(log);
}

void EndSprintCallbackObservation(
    Entity &actor, SprintCallbackObservation &observation,
    GEBool nativeResult)
{
    if (g_pCurrentSprintCallbackScope == &observation)
        g_pCurrentSprintCallbackScope = observation.previousScope;

    if (!observation.active || actor == None
        || actor.GetInstance() != observation.actorInstance)
    {
        return;
    }

    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    bool const sameRight = currentSources.rightInstance
        == observation.rightSourceInstance;
    Entity rightSource(observation.rightSourceInstance);
    GEInt const rightGroupAfter = rightSource != None
        ? static_cast<GEInt>(rightSource.GetCollisionGroup()) : -1;
    GEInt const actionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt const phaseAfter = static_cast<GEInt>(actor.GetCurrentAniPhase());
    GEFloat const stateTimeAfter = actor.Routine.GetStateTime();
    GEInt const statePositionAfter = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    bCString const motionAfter = actor.NPC.GetCurrentMovementAni();

    CollisionLifecycleGuard::GenerationToken const generationAfter =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actor.GetInstance());
    bool const sameGeneration = generationAfter.valid
        && generationAfter.generation == observation.c1Generation;

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(
        log,
        "CORE RAW55_SPRINT_CALLBACK_BOUNDARY Actor=%s C1=%llu SameC1=%d SameRight=%d Action=%d->%d Phase=%d->%d StateTime=%.6f->%.6f StatePosition=%d->%d MotionBefore=%s MotionAfter=%s Right=%s RightUseType=%d RightGroup=%d->%d NativeResult=%d OBSERVE_NATIVE=1\n",
        actor.GetName().GetText(),
        static_cast<unsigned long long>(observation.c1Generation),
        sameGeneration ? 1 : 0, sameRight ? 1 : 0,
        observation.actionBefore, actionAfter,
        observation.phaseBefore, phaseAfter,
        static_cast<double>(observation.stateTimeBefore),
        static_cast<double>(stateTimeAfter),
        observation.statePositionBefore, statePositionAfter,
        observation.motionBefore.c_str(),
        motionAfter.GetText() != nullptr
            ? motionAfter.GetText() : "<unavailable>",
        observation.rightNameBefore.c_str(),
        observation.rightUseTypeBefore,
        observation.rightGroupBefore, rightGroupAfter,
        static_cast<GEInt>(nativeResult));
    std::fflush(log);
}
}
