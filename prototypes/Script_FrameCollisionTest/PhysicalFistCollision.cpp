#include "PhysicalFistCollision.h"

#include "CollisionLifecycleGuard.h"
#include "CollisionSourceOperations.h"
#include "CollisionSources.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"

#include <cstdio>
#endif

#include <cmath>
#include <string>
#include <unordered_map>
#include <windows.h>

namespace FrameCollision::PhysicalFistCollision
{
struct PhysicalFistExecution
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    AttackFamily originFamily;
    std::string animationName;
    GEInt authoredFistCount;
    GEInt acceptedFistCount;
    bool earlyOpeningSuppressed;
    GEInt firstMarkerStatePosition;
    bool normalNativeClearSuppressed;
    bool lastAcceptedDispatchValid;
    GEFloat lastAcceptedStateTime;
    double lastAcceptedElapsedMs;
};

struct EligibilityFacts
{
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    CollisionLifecycleGuard::GenerationToken generation;
    EquippedCollisionSources sources;
    CurrentMotionMarkerResult decision;
    AttackFamily currentFamily;
    std::string animationName;
};

static thread_local std::unordered_map<eCEntity *, PhysicalFistExecution>
    g_Executions;
static thread_local NativeCallbackScope *g_pCurrentCallbackScope = nullptr;

static bool IsSupportedFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Quick
        || family == AttackFamily_Power
        || family == AttackFamily_Sprint;
}

static bool IsExactPhysicalFistSource(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return false;
    Entity source(sourceInstance);
    return source != None
        && CollisionSources::GetCollisionSourceUseType(source)
            == gEUseType_PhysicalFist;
}

static bool IsExactFistOnlyDecision(
    CurrentMotionMarkerResult const &decision)
{
    GEInt const fistCount = decision.markerCounts[MarkerOpcode_Fist];
    return decision.foundMatchingMotion
        && decision.scanValid
        && decision.markerPresent
        && decision.hasFistMarkers
        && (fistCount == 1 || fistCount == 2)
        && decision.markerCounts[MarkerOpcode_Right] == 0
        && decision.markerCounts[MarkerOpcode_Left] == 0
        && decision.markerCounts[MarkerOpcode_Both] == 0
        && decision.markerCounts[MarkerOpcode_Off] == 0
        && decision.requiredSourceMask == SourceMask_None;
}

static bool TryResolveEligibility(
    Entity &actor, AttackFamily currentFamily,
    CurrentMotionMarkerResult const &decision,
    EquippedCollisionSources const &sources,
    EligibilityFacts &facts)
{
    facts = {};
    if (actor == None || actor.GetInstance() == nullptr
        || !IsSupportedFamily(currentFamily)
        || !FrameCollisionMarkers::IsAttackHit(actor, currentFamily)
        || !IsExactFistOnlyDecision(decision)
        || CollisionSources::ResolveFistCollisionSource(actor) != nullptr
        || !IsExactPhysicalFistSource(sources.rightInstance))
    {
        return false;
    }

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            actor.GetInstance());
    if (!generation.valid
        || generation.actorInstance != actor.GetInstance())
    {
        return false;
    }

    bCString const animation = actor.NPC.GetCurrentMovementAni();
    facts.actorInstance = actor.GetInstance();
    facts.rightSourceInstance = sources.rightInstance;
    facts.generation = generation;
    facts.sources = sources;
    facts.decision = decision;
    facts.currentFamily = currentFamily;
    facts.animationName = animation.GetText() != nullptr
        ? animation.GetText() : "";
    return true;
}

static bool IsAllowedOriginContinuation(
    AttackFamily originFamily, AttackFamily currentFamily)
{
    return originFamily == currentFamily
        || (originFamily == AttackFamily_Sprint
            && currentFamily == AttackFamily_Power);
}

static PhysicalFistExecution *ResolveExecution(
    EligibilityFacts const &facts, bool &created,
    bool &identityContradiction)
{
    created = false;
    identityContradiction = false;
    auto found = g_Executions.find(facts.actorInstance);
    if (found != g_Executions.end()
        && found->second.c1Generation != facts.generation.generation)
    {
        g_Executions.erase(found);
        found = g_Executions.end();
    }

    if (found == g_Executions.end())
    {
        PhysicalFistExecution execution = {};
        execution.actorInstance = facts.actorInstance;
        execution.rightSourceInstance = facts.rightSourceInstance;
        execution.c1Generation = facts.generation.generation;
        execution.originFamily = facts.currentFamily;
        execution.animationName = facts.animationName;
        execution.authoredFistCount =
            facts.decision.markerCounts[MarkerOpcode_Fist];
        execution.firstMarkerStatePosition = -1;
        found = g_Executions.emplace(
            facts.actorInstance, execution).first;
        created = true;
        return &found->second;
    }

    PhysicalFistExecution &execution = found->second;
    bool const identityMatches =
        execution.actorInstance == facts.actorInstance
        && execution.rightSourceInstance == facts.rightSourceInstance
        && execution.animationName == facts.animationName
        && execution.authoredFistCount
            == facts.decision.markerCounts[MarkerOpcode_Fist]
        && IsAllowedOriginContinuation(
            execution.originFamily, facts.currentFamily);
    if (!identityMatches)
    {
        identityContradiction = true;
        return nullptr;
    }
    return &execution;
}

static PhysicalFistExecution *FindScopeExecution(
    NativeCallbackScope const &scope)
{
    auto found = g_Executions.find(scope.actorInstance);
    if (found == g_Executions.end())
        return nullptr;
    PhysicalFistExecution &execution = found->second;
    return execution.actorInstance == scope.actorInstance
            && execution.rightSourceInstance == scope.rightSourceInstance
            && execution.c1Generation == scope.c1Generation
        ? &execution : nullptr;
}

#ifdef FRAME_COLLISION_DIAGNOSTICS
static char const *FamilyName(AttackFamily family)
{
    switch (family)
    {
        case AttackFamily_Normal: return "NORMAL";
        case AttackFamily_Quick: return "QUICK";
        case AttackFamily_Power: return "POWER";
        case AttackFamily_Sprint: return "SPRINT";
        default: return "UNSUPPORTED";
    }
}

static void LogCallbackIdentityContradiction(EligibilityFacts const &facts)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;
    auto const found = g_Executions.find(facts.actorInstance);
    if (found == g_Executions.end())
        return;
    PhysicalFistExecution const &stored = found->second;
    std::fprintf(
        log,
        "CORE RAW55_PHYSICAL_FIST_IDENTITY_CONTRADICTION Actor=%p C1=%llu StoredOriginFamily=%s CallbackFamily=%s StoredRight=%p CurrentRight=%p StoredMotion=%s CurrentMotion=%s StoredAuthoredFistCount=%d CurrentAuthoredFistCount=%d Rejected=1\n",
        static_cast<void *>(facts.actorInstance),
        static_cast<unsigned long long>(facts.generation.generation),
        FamilyName(stored.originFamily), FamilyName(facts.currentFamily),
        static_cast<void *>(stored.rightSourceInstance),
        static_cast<void *>(facts.rightSourceInstance),
        stored.animationName.c_str(), facts.animationName.c_str(),
        stored.authoredFistCount,
        facts.decision.markerCounts[MarkerOpcode_Fist]);
    std::fflush(log);
}

static void LogMarkerResult(
    Entity &actor, PhysicalFistExecution const &execution,
    AttackFamily currentFamily, MarkerProcessResult const &result,
    bool groupRequested, bool contactsCleared)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;
    std::fprintf(
        log,
        "CORE RAW55_PHYSICAL_FIST_MARKER Actor=%s C1=%llu OriginFamily=%s CurrentFamily=%s Action=%d StatePosition=%d StateTime=%.6f Right=%s RightUseType=%d GroupBefore=%d GroupAfter=%d AuthoredFistCount=%d AcceptedFistCount=%d EarlyOpeningSuppressed=%d FirstMarkerStatePosition=%d NormalNativeClearSuppressed=%d GroupRequested=%d ClearTriggeredList=%d Result=%d\n",
        actor.GetName().GetText(),
        static_cast<unsigned long long>(execution.c1Generation),
        FamilyName(execution.originFamily), FamilyName(currentFamily),
        result.markerAction,
        static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>()),
        static_cast<double>(result.markerStateTime),
        Entity(execution.rightSourceInstance).GetName().GetText(),
        result.fistSourceUseType, result.fistSourceGroupBefore,
        result.fistSourceGroupAfter, execution.authoredFistCount,
        execution.acceptedFistCount,
        execution.earlyOpeningSuppressed ? 1 : 0,
        execution.firstMarkerStatePosition,
        execution.normalNativeClearSuppressed ? 1 : 0,
        groupRequested ? 1 : 0, contactsCleared ? 1 : 0,
        static_cast<GEInt>(result.code));
    std::fflush(log);
}

static void LogPrematureOpeningSuppressed(
    PhysicalFistExecution const &execution, AttackFamily callbackFamily)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;
    std::fprintf(
        log,
        "CORE RAW55_PHYSICAL_FIST_NATIVE_OPEN_SUPPRESSED Actor=%p C1=%llu OriginFamily=%s CallbackFamily=%s Right=%p BeforeGroup=%d RequestedGroup=%d SUPPRESS_GROUP=1\n",
        static_cast<void *>(execution.actorInstance),
        static_cast<unsigned long long>(execution.c1Generation),
        FamilyName(execution.originFamily), FamilyName(callbackFamily),
        static_cast<void *>(execution.rightSourceInstance),
        static_cast<GEInt>(eECollisionGroup_Item_Equipped),
        static_cast<GEInt>(eECollisionGroup_Item_Attack));
    std::fflush(log);
}

static void LogNormalNativeClearSuppressed(
    PhysicalFistExecution const &execution)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;
    std::fprintf(
        log,
        "CORE RAW55_PHYSICAL_FIST_NORMAL_NATIVE_CLEAR_SUPPRESSED Actor=%p C1=%llu Right=%p CallerModule=Script_Game.dll CallerRVA=0x000386C6 SUPPRESS_CLEAR=1\n",
        static_cast<void *>(execution.actorInstance),
        static_cast<unsigned long long>(execution.c1Generation),
        static_cast<void *>(execution.rightSourceInstance));
    std::fflush(log);
}
#endif

void BeginNativeCallbackScope(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu, NativeCallbackScope &scope)
{
    scope = {};
    scope.previousScope = g_pCurrentCallbackScope;
    g_pCurrentCallbackScope = &scope;
    if (actor == None || actor.GetInstance() == nullptr
        || spu == nullptr || spu->GetSelfEntity() != actor.GetInstance()
        || !ownership.attackHitEligible)
    {
        return;
    }

    EligibilityFacts facts = {};
    if (!TryResolveEligibility(
            actor, family, ownership.decision, ownership.sources, facts))
    {
        return;
    }

    bool created = false;
    bool identityContradiction = false;
    PhysicalFistExecution *const execution = ResolveExecution(
        facts, created, identityContradiction);
#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (identityContradiction)
        LogCallbackIdentityContradiction(facts);
#endif
    if (execution == nullptr || identityContradiction)
        return;

    scope.active = true;
    scope.actorInstance = facts.actorInstance;
    scope.rightSourceInstance = facts.rightSourceInstance;
    scope.c1Generation = facts.generation.generation;
    scope.family = family;
}

void EndNativeCallbackScope(NativeCallbackScope &scope)
{
    if (g_pCurrentCallbackScope == &scope)
        g_pCurrentCallbackScope = scope.previousScope;
    scope.active = false;
}

bool ShouldSuppressCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
    NativeCallbackScope *const scope = g_pCurrentCallbackScope;
    if (scope == nullptr || !scope->active
        || sourceInstance == nullptr
        || sourceInstance != scope->rightSourceInstance
        || requestedGroup != eECollisionGroup_Item_Attack
        || beforeGroup != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

    PhysicalFistExecution *const execution = FindScopeExecution(*scope);
    if (execution == nullptr || execution->acceptedFistCount != 0)
        return false;

    Entity actor(scope->actorInstance);
    Entity rightSource(sourceInstance);
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (actor == None || rightSource == None
        || !generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation
        || currentSources.rightInstance != sourceInstance
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist)
    {
        return false;
    }

    execution->earlyOpeningSuppressed = true;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    LogPrematureOpeningSuppressed(*execution, scope->family);
#endif
    return true;
}

static void PopulateMarkerFacts(
    Entity &actor, EligibilityFacts const &facts,
    char const *effectName, double elapsedMs,
    MarkerProcessResult &result)
{
    result = FrameCollisionMarkers::CreateMarkerResult(
        facts.sources, MarkerOpcode_Fist, effectName, elapsedMs);
    result.decision = facts.decision;
    result.fistSourceInstance = facts.rightSourceInstance;
    result.currentAnimation = facts.animationName;
    result.markerAction = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    result.markerPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    result.markerStateTime = actor.Routine.GetStateTime();
    result.c1GenerationValid = true;
    result.c1Generation = facts.generation.generation;
    Entity rightSource(facts.rightSourceInstance);
    result.fistSourceGroupBefore = static_cast<GEInt>(
        rightSource.GetCollisionGroup());
    result.fistSourceGroupAfter = result.fistSourceGroupBefore;
    result.fistSourceUseType = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(rightSource));
}

static bool IsDuplicateDispatch(
    PhysicalFistExecution const &execution, GEFloat stateTime,
    double elapsedMs, GEFloat &stateTimeDelta, double &elapsedMsDelta)
{
    stateTimeDelta = 0.0f;
    elapsedMsDelta = 0.0;
    if (!execution.lastAcceptedDispatchValid)
        return false;
    stateTimeDelta = static_cast<GEFloat>(
        std::fabs(static_cast<double>(
            stateTime - execution.lastAcceptedStateTime)));
    elapsedMsDelta = elapsedMs - execution.lastAcceptedElapsedMs;
    return stateTimeDelta <= 0.000001f
        && elapsedMsDelta >= 0.0
        && elapsedMsDelta <= 5.0;
}

static bool IsFirstFistAllowed(
    PhysicalFistExecution const &execution,
    AttackFamily currentFamily, GEInt statePosition)
{
    switch (execution.originFamily)
    {
        case AttackFamily_Quick:
            return currentFamily == AttackFamily_Quick
                && (statePosition == 0
                    || (statePosition == 1
                        && execution.earlyOpeningSuppressed));
        case AttackFamily_Normal:
            return currentFamily == AttackFamily_Normal
                && (statePosition == 0
                    || (statePosition == 1
                        && execution.earlyOpeningSuppressed));
        case AttackFamily_Power:
            return currentFamily == AttackFamily_Power
                && (statePosition == 1 || statePosition == 2)
                && execution.earlyOpeningSuppressed;
        case AttackFamily_Sprint:
            return currentFamily == AttackFamily_Sprint
                && statePosition == 1
                && execution.earlyOpeningSuppressed;
        default:
            return false;
    }
}

static bool IsSecondFistAllowed(
    PhysicalFistExecution const &execution,
    AttackFamily currentFamily, GEInt statePosition)
{
    switch (execution.originFamily)
    {
        case AttackFamily_Quick:
            return currentFamily == AttackFamily_Quick;
        case AttackFamily_Normal:
            return currentFamily == AttackFamily_Normal
                && statePosition == 1;
        case AttackFamily_Power:
            return currentFamily == AttackFamily_Power
                && (statePosition == 1 || statePosition == 2);
        case AttackFamily_Sprint:
            return currentFamily == AttackFamily_Power
                && (statePosition == 1 || statePosition == 2);
        default:
            return false;
    }
}

bool TryProcessMarker(
    Entity &actor, MarkerOpcode markerOpcode, char const *effectName,
    double elapsedMs, MarkerProcessResult &result)
{
    if (markerOpcode != MarkerOpcode_Fist)
        return false;

    AttackFamily currentFamily = AttackFamily_Normal;
    if (!FrameCollisionMarkers::TryGetCurrentAttackHitFamily(
            actor, currentFamily))
    {
        return false;
    }

    EquippedCollisionSources const sources =
        CollisionSources::GetEquippedCollisionSources(actor);
    CurrentMotionMarkerResult const decision =
        FrameCollisionMarkers::GetCurrentMarkerDecision(actor);
    EligibilityFacts facts = {};
    if (!TryResolveEligibility(
            actor, currentFamily, decision, sources, facts))
    {
        return false;
    }

    PopulateMarkerFacts(actor, facts, effectName, elapsedMs, result);
    bool created = false;
    bool identityContradiction = false;
    PhysicalFistExecution *const execution = ResolveExecution(
        facts, created, identityContradiction);
    if (execution == nullptr || identityContradiction)
    {
        result.code = MarkerResult_RejectedGenerationInconsistency;
        return true;
    }

    result.executionBudgetReset = created;
    result.authoredMarkerCount = execution->authoredFistCount;
    result.acceptedMarkerCountBefore = execution->acceptedFistCount;
    result.acceptedMarkerCountAfter = execution->acceptedFistCount;

    if (IsDuplicateDispatch(
            *execution, result.markerStateTime, elapsedMs,
            result.duplicateStateTimeDelta,
            result.duplicateElapsedMsDelta))
    {
        result.code = MarkerResult_DuplicateIgnored;
#ifdef FRAME_COLLISION_DIAGNOSTICS
        LogMarkerResult(
            actor, *execution, currentFamily, result, false, false);
#endif
        return true;
    }

    if (execution->acceptedFistCount >= execution->authoredFistCount)
    {
        result.code = MarkerResult_BudgetIgnored;
#ifdef FRAME_COLLISION_DIAGNOSTICS
        LogMarkerResult(
            actor, *execution, currentFamily, result, false, false);
#endif
        return true;
    }

    Entity rightSource(execution->rightSourceInstance);
    GEInt const statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    bool groupRequested = false;
    bool contactsCleared = false;
    if (execution->acceptedFistCount == 0)
    {
        if (!IsFirstFistAllowed(
                *execution, currentFamily, statePosition)
            || rightSource.GetCollisionGroup()
                != eECollisionGroup_Item_Equipped)
        {
            result.code = MarkerResult_RejectedUnsupportedHit;
#ifdef FRAME_COLLISION_DIAGNOSTICS
            LogMarkerResult(
                actor, *execution, currentFamily, result, false, false);
#endif
            return true;
        }

        CollisionSourceOperations::SourceOperationResult const activation =
            CollisionSourceOperations::ActivateAttackSource(
                execution->rightSourceInstance);
        groupRequested = activation.groupRequested;
        result.fistSourceGroupBefore = activation.groupBefore;
        result.fistSourceGroupAfter = activation.groupAfter;
        result.fistSourceUseType = activation.useType;
        if (activation.groupRequested)
        {
            ++result.collisionGroupRequestCount;
            ++result.activatedSourceCount;
        }
        if (activation.groupAfter
            != static_cast<GEInt>(eECollisionGroup_Item_Attack))
        {
            result.code = MarkerResult_RejectedIncompleteActivation;
#ifdef FRAME_COLLISION_DIAGNOSTICS
            LogMarkerResult(
                actor, *execution, currentFamily, result,
                groupRequested, false);
#endif
            return true;
        }

        bool const clearFirstContacts =
            execution->originFamily == AttackFamily_Quick
            || (execution->originFamily == AttackFamily_Normal
                && statePosition == 0);
        if (clearFirstContacts)
        {
            CollisionSourceOperations::SourceOperationResult const rearm =
                CollisionSourceOperations::RearmTriggeredContacts(
                    execution->rightSourceInstance);
            contactsCleared = rearm.triggeredListCleared;
            result.fistSourceGroupAfter = rearm.groupAfter;
            if (rearm.triggeredListCleared)
                ++result.triggeredListClearCount;
        }
        execution->firstMarkerStatePosition = statePosition;
    }
    else
    {
        if (execution->authoredFistCount != 2
            || execution->acceptedFistCount != 1
            || !IsSecondFistAllowed(
                *execution, currentFamily, statePosition)
            || rightSource.GetCollisionGroup()
                != eECollisionGroup_Item_Attack)
        {
            result.code = MarkerResult_RejectedUnsupportedHit;
#ifdef FRAME_COLLISION_DIAGNOSTICS
            LogMarkerResult(
                actor, *execution, currentFamily, result, false, false);
#endif
            return true;
        }

        CollisionSourceOperations::SourceOperationResult const rearm =
            CollisionSourceOperations::RearmTriggeredContacts(
                execution->rightSourceInstance);
        contactsCleared = rearm.triggeredListCleared;
        result.fistSourceGroupBefore = rearm.groupBefore;
        result.fistSourceGroupAfter = rearm.groupAfter;
        result.fistSourceUseType = rearm.useType;
        if (rearm.triggeredListCleared)
            ++result.triggeredListClearCount;
    }

    ++execution->acceptedFistCount;
    execution->lastAcceptedDispatchValid = true;
    execution->lastAcceptedStateTime = result.markerStateTime;
    execution->lastAcceptedElapsedMs = elapsedMs;
    result.acceptedMarkerCountAfter = execution->acceptedFistCount;
    result.code = MarkerResult_Accepted;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    LogMarkerResult(
        actor, *execution, currentFamily, result,
        groupRequested, contactsCleared);
#endif
    return true;
}

bool ShouldSuppressNormalNativeTriggerClear(
    eCTrigger_PS *trigger, void *callerAddress)
{
    NativeCallbackScope *const scope = g_pCurrentCallbackScope;
    if (scope == nullptr || !scope->active
        || scope->family != AttackFamily_Normal
        || trigger == nullptr || callerAddress == nullptr)
    {
        return false;
    }

    PhysicalFistExecution *const execution = FindScopeExecution(*scope);
    if (execution == nullptr
        || execution->originFamily != AttackFamily_Normal
        || execution->acceptedFistCount < 1
        || execution->firstMarkerStatePosition != 0
        || execution->normalNativeClearSuppressed)
    {
        return false;
    }

    Entity actor(scope->actorInstance);
    Entity rightSource(execution->rightSourceInstance);
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    EquippedCollisionSources const currentSources =
        CollisionSources::GetEquippedCollisionSources(actor);
    if (actor == None || actor.GetInstance() != scope->actorInstance
        || rightSource == None
        || !generation.valid
        || generation.actorInstance != scope->actorInstance
        || generation.generation != scope->c1Generation
        || currentSources.rightInstance != execution->rightSourceInstance
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || static_cast<eCTrigger_PS *>(
            rightSource.TouchDamage.m_pEngineEntityPropertySet) != trigger)
    {
        return false;
    }

    HMODULE const scriptGameModule =
        ::GetModuleHandleA("Script_Game.dll");
    if (scriptGameModule == nullptr)
        return false;
    std::uintptr_t const callerRva =
        reinterpret_cast<std::uintptr_t>(callerAddress)
        - reinterpret_cast<std::uintptr_t>(scriptGameModule);
    if (callerRva != 0x000386C6)
        return false;

    execution->normalNativeClearSuppressed = true;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    LogNormalNativeClearSuppressed(*execution);
#endif
    return true;
}

void RetireFinalizedGeneration(
    eCEntity *actorInstance, std::uint64_t c1Generation)
{
    auto found = g_Executions.find(actorInstance);
    if (found != g_Executions.end()
        && found->second.c1Generation == c1Generation)
    {
        g_Executions.erase(found);
    }
}
}
