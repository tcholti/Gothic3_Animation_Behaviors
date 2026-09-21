#include "Raw8FistCollision.h"

#include "CollisionSources.h"
#include "FrameCollisionMarkers.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"
#endif

#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <windows.h>

namespace FrameCollision::Raw8FistCollision
{
struct Raw8FistMarkerExecution
{
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    gCScriptProcessingUnit *spu;
    std::uint64_t c1Generation;
    std::uint64_t opportunityOrdinal;
    eCWrapper_emfx2Actor *timingAnimationActor;
    eCWrapper_emfx2Actor::eEMotionType timingMotionType;
    GEDouble forcedPlayTime;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    GEDouble maxTime;
    GEDouble nativeThresholdConstant;
    GEDouble computedThreshold;
#endif
    bool timingActive;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    bool timingApplicationLogged;
#endif
    bool opportunityPending;
};

struct Raw8FistPrimaryTiming
{
    eCWrapper_emfx2Actor *animationActor;
    bool available;
    GEDouble playTime;
    GEDouble maxTime;
};

using ExecutionMap =
    std::unordered_map<eCEntity *, Raw8FistMarkerExecution>;

static thread_local ExecutionMap g_Raw8FistMarkerExecutions;
static thread_local InvocationScope *g_pCurrentInvocation = nullptr;
static thread_local std::uint64_t g_NextOpportunityOrdinal = 1;

bool IsSupportedFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Power
        || family == AttackFamily_Quick
        || family == AttackFamily_Sprint;
}

static Raw8FistPrimaryTiming CaptureRaw8FistPrimaryTiming(Entity &actor)
{
    Raw8FistPrimaryTiming result = {};
    result.playTime = -1.0;
    result.maxTime = -1.0;
    if (!actor.Animation.IsValid())
        return result;

    eCVisualAnimation_PS *animationPS =
        static_cast<eCVisualAnimation_PS *>(
            actor.Animation.m_pEngineEntityPropertySet);
    if (animationPS == nullptr || !animationPS->HasActor())
        return result;

    result.animationActor = animationPS->GetActor();
    if (result.animationActor == nullptr)
        return result;

    auto const primaryMotion =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    if (!result.animationActor->HasMotionInstance(primaryMotion))
        return result;

    result.playTime = result.animationActor->GetPlayTime(primaryMotion);
    result.maxTime = result.animationActor->GetMaxTime(primaryMotion);
    result.available = true;
    return result;
}

static bool ReadRaw8FistNativeTimingConstant(GEDouble &value)
{
    constexpr std::uintptr_t NativeThresholdConstantRVA = 0x00308308;
    HMODULE const gameModule = ::GetModuleHandleA("Game.dll");
    if (gameModule == nullptr)
        return false;

    std::uintptr_t const constantAddress =
        reinterpret_cast<std::uintptr_t>(gameModule)
        + NativeThresholdConstantRVA;
    std::memcpy(
        &value, reinterpret_cast<void const *>(constantAddress),
        sizeof(value));
    return true;
}

static bool IsExactRaw8FistSource(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return false;
    Entity source(sourceInstance);
    return source != None
        && CollisionSources::GetCollisionSourceUseType(source)
            == gEUseType_Fist;
}

static bool ResolveExactLiveTransport(
    Raw8FistMarkerExecution const &state, Entity &actor)
{
    actor.AttachTo(state.actorInstance);
    if (actor == None)
        return false;

    gCScriptRoutine_PS *const routinePS =
        static_cast<gCScriptRoutine_PS *>(
            actor.Routine.m_pEngineEntityPropertySet);
    if (routinePS == nullptr || &routinePS->GetSPU() != state.spu)
        return false;
    if (state.spu == nullptr
        || state.spu->GetSelfEntity() != state.actorInstance)
    {
        return false;
    }
    if (CollisionSources::ResolveFistCollisionSource(actor)
        != state.fistSourceInstance)
    {
        return false;
    }
    return IsExactRaw8FistSource(state.fistSourceInstance);
}

static bool MatchesExactExecution(Raw8FistMarkerExecution const &state)
{
    Entity actor;
    if (!ResolveExactLiveTransport(state, actor))
        return false;
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            state.actorInstance);
    return generation.valid
        && generation.actorInstance == state.actorInstance
        && generation.generation == state.c1Generation;
}

static bool MatchesPendingOpportunity(
    Raw8FistMarkerExecution const &state)
{
    return state.opportunityPending && MatchesExactExecution(state);
}

static volatile GEU8 *ResolveExactLiveLatch(
    Raw8FistMarkerExecution const &state)
{
    Entity actor;
    if (!ResolveExactLiveTransport(state, actor))
        return nullptr;
    return reinterpret_cast<volatile GEU8 *>(state.spu) + 0x164;
}

static void RetireRaw8FistTimingPermission(
    Raw8FistMarkerExecution &state, char const *reason)
{
#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (state.timingActive)
    {
        CollisionDiagnostics::LogRaw8FistTimingPermissionRetired(
            state.actorInstance, state.c1Generation, state.spu,
            static_cast<void *>(state.timingAnimationActor), reason);
    }
#else
    (void) reason;
#endif
    state.timingActive = false;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    state.timingApplicationLogged = false;
#endif
    state.timingAnimationActor = nullptr;
    state.forcedPlayTime = 0.0;
}

static void CloseAndEraseExecution(
    ExecutionMap::iterator found, char const *reason,
    bool forcePendingLatchClosed)
{
    Raw8FistMarkerExecution &state = found->second;
    bool const wasPending = state.opportunityPending;
    GEInt latchBefore = -1;
    GEInt latchAfter = -1;
    bool writeAttempted = false;
    bool writeConfirmed = false;
    if (forcePendingLatchClosed && wasPending)
    {
        volatile GEU8 *const latch = ResolveExactLiveLatch(state);
        if (latch != nullptr)
        {
            latchBefore = static_cast<GEInt>(*latch);
            writeAttempted = true;
            *latch = 1;
            latchAfter = static_cast<GEInt>(*latch);
            writeConfirmed = latchAfter == 1;
        }
    }

    RetireRaw8FistTimingPermission(state, reason);
#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (wasPending)
    {
        CollisionDiagnostics::LogRaw8FistOpportunityClose(
            state.actorInstance, state.fistSourceInstance,
            state.c1Generation, state.opportunityOrdinal, reason,
            latchBefore, latchAfter, writeAttempted, writeConfirmed);
    }
#else
    (void) latchBefore;
    (void) latchAfter;
    (void) writeAttempted;
    (void) writeConfirmed;
#endif
    state.opportunityPending = false;
    g_Raw8FistMarkerExecutions.erase(found);
}

void UpdateMarkerOwnership(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu)
{
    if (actor == None)
        return;

    eCEntity *const actorInstance = actor.GetInstance();
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    auto existing = g_Raw8FistMarkerExecutions.find(actorInstance);
    if (existing != g_Raw8FistMarkerExecutions.end()
        && (!generation.valid
            || existing->second.c1Generation != generation.generation))
    {
        // A replacement generation must not inherit or be overwritten by
        // stale raw8 state observed at callback ownership time.
        CloseAndEraseExecution(
            existing, "C1_GENERATION_CHANGED", false);
        existing = g_Raw8FistMarkerExecutions.end();
    }

    bool const exactMarkedRaw8FistExecution =
        ownership.attackHitEligible
        && IsSupportedFamily(family)
        && ownership.decision.foundMatchingMotion
        && ownership.decision.scanValid
        && ownership.decision.markerPresent
        && ownership.decision.hasFistMarkers
        && ownership.decision.markerCounts[MarkerOpcode_Fist] > 0
        && IsExactRaw8FistSource(ownership.fistSourceInstance)
        && generation.valid
        && spu != nullptr
        && spu->GetSelfEntity() == actorInstance;
    if (!exactMarkedRaw8FistExecution)
        return;

    if (existing != g_Raw8FistMarkerExecutions.end())
    {
        // C1 is the execution identity. Action/family/phase/motion changes do
        // not create a new raw8 execution or repeat its initial close.
        return;
    }

    volatile GEU8 *const latchByte =
        reinterpret_cast<volatile GEU8 *>(spu) + 0x164;
    GEInt const latchBefore = static_cast<GEInt>(*latchByte);
    *latchByte = 1;
    GEInt const latchAfter = static_cast<GEInt>(*latchByte);
    bool const writeConfirmed = latchAfter == 1;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    Raw8FistPrimaryTiming const timing =
        CaptureRaw8FistPrimaryTiming(actor);
    CollisionDiagnostics::LogRaw8FistMarkerOwnership(
        actor, family, generation.generation,
        ownership.fistSourceInstance, spu,
        static_cast<void *>(timing.animationActor), latchBefore,
        latchAfter, writeConfirmed);
#else
    (void) latchBefore;
#endif
    if (!writeConfirmed)
        return;

    Raw8FistMarkerExecution state = {};
    state.actorInstance = actorInstance;
    state.fistSourceInstance = ownership.fistSourceInstance;
    state.spu = spu;
    state.c1Generation = generation.generation;
    g_Raw8FistMarkerExecutions[actorInstance] = state;
}

void ApplyAcceptedMarkerLatch(
    Entity &actor, MarkerProcessResult &result)
{
    Entity fistSource(result.fistSourceInstance);
    result.fistSourceGroupBefore = static_cast<GEInt>(
        fistSource.GetCollisionGroup());
    result.fistSourceGroupAfter = result.fistSourceGroupBefore;
    result.fistSourceUseType = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(fistSource));

    gCScriptRoutine_PS *routinePS = static_cast<gCScriptRoutine_PS *>(
        actor.Routine.m_pEngineEntityPropertySet);
    result.fistSPU =
        routinePS != nullptr ? &routinePS->GetSPU() : nullptr;
    if (result.fistSPU != nullptr)
    {
        volatile GEU8 *latchByte =
            reinterpret_cast<volatile GEU8 *>(result.fistSPU) + 0x164;
        result.fistLatchBefore = static_cast<GEInt>(*latchByte);
        result.fistLatchWriteAttempted = true;
        *latchByte = 0;
        result.fistLatchAfter = static_cast<GEInt>(*latchByte);
        result.fistLatchWriteConfirmed = result.fistLatchAfter == 0;
    }
}

void UpdateTimingPermissionFromMarker(
    Entity &actor, MarkerProcessResult const &result)
{
    if (actor == None
        || result.code != MarkerResult_Accepted
        || result.opcode != MarkerOpcode_Fist
        || result.fistSourceUseType != static_cast<GEInt>(gEUseType_Fist)
        || !result.c1GenerationValid
        || !result.fistLatchWriteAttempted
        || !result.fistLatchWriteConfirmed
        || result.fistLatchAfter != 0)
    {
        return;
    }

    eCEntity *const actorInstance = actor.GetInstance();
    auto execution = g_Raw8FistMarkerExecutions.find(actorInstance);
    if (execution == g_Raw8FistMarkerExecutions.end())
        return;

    Raw8FistMarkerExecution &state = execution->second;
    bool const ownershipMatched =
        state.c1Generation == result.c1Generation
        && state.fistSourceInstance == result.fistSourceInstance
        && state.spu == result.fistSPU
        && MatchesExactExecution(state);
    if (!ownershipMatched)
        return;

    RetireRaw8FistTimingPermission(
        state, "SUPERSEDED_BY_ACCEPTED_FIST");
    state.opportunityOrdinal = g_NextOpportunityOrdinal++;
    state.opportunityPending = true;

    Raw8FistPrimaryTiming const timing =
        CaptureRaw8FistPrimaryTiming(actor);
    GEDouble nativeThresholdConstant = -1.0;
    bool const thresholdAvailable =
        timing.available
        && ReadRaw8FistNativeTimingConstant(nativeThresholdConstant);
    GEDouble computedThreshold = -1.0;
    bool realBelowThreshold = false;
    if (thresholdAvailable)
    {
        computedThreshold = timing.maxTime * nativeThresholdConstant;
        realBelowThreshold = timing.playTime < computedThreshold;
    }

    auto const primaryMotion =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    if (thresholdAvailable && realBelowThreshold)
    {
        state.timingAnimationActor = timing.animationActor;
        state.timingMotionType = primaryMotion;
        state.forcedPlayTime = computedThreshold + 0.001;
        if (state.forcedPlayTime > timing.maxTime)
            state.forcedPlayTime = timing.maxTime;
#ifdef FRAME_COLLISION_DIAGNOSTICS
        state.maxTime = timing.maxTime;
        state.nativeThresholdConstant = nativeThresholdConstant;
        state.computedThreshold = computedThreshold;
#endif
        state.timingActive = true;
    }

    // A FIST may open/refresh the opportunity inside the native invocation
    // that will immediately attempt contact. Bind that live scope exactly.
    if (g_pCurrentInvocation != nullptr
        && g_pCurrentInvocation->actorInstance == actorInstance
        && g_pCurrentInvocation->spu == result.fistSPU)
    {
        g_pCurrentInvocation->fistSourceInstance =
            state.fistSourceInstance;
        g_pCurrentInvocation->c1Generation = state.c1Generation;
        g_pCurrentInvocation->opportunityOrdinal =
            state.opportunityOrdinal;
        g_pCurrentInvocation->contactConsumed = false;
        g_pCurrentInvocation->active = true;
    }

#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogRaw8FistMarkerOpportunity(
        actor, result, static_cast<void *>(timing.animationActor),
        timing.available, timing.playTime, timing.maxTime,
        nativeThresholdConstant, computedThreshold, realBelowThreshold,
        true, state.timingActive);
    CollisionDiagnostics::LogRaw8FistOpportunityOpen(
        state.actorInstance, state.fistSourceInstance,
        state.c1Generation, state.opportunityOrdinal,
        result, state.timingActive);
#endif
}

GEDouble ApplyTimingPermission(
    gCScriptProcessingUnit *spu,
    eCWrapper_emfx2Actor *animationActor,
    eCWrapper_emfx2Actor::eEMotionType motionType,
    GEDouble realPlayTime)
{
    eCEntity *const actorInstance =
        spu != nullptr ? spu->GetSelfEntity() : nullptr;
    auto execution = g_Raw8FistMarkerExecutions.find(actorInstance);
    if (execution == g_Raw8FistMarkerExecutions.end())
        return realPlayTime;

    Raw8FistMarkerExecution &state = execution->second;
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            state.actorInstance);
    if (!generation.valid || generation.generation != state.c1Generation)
    {
        CloseAndEraseExecution(
            execution, "C1_GENERATION_CHANGED", false);
        return realPlayTime;
    }

    if (!state.opportunityPending || !state.timingActive)
        return realPlayTime;
    if (!MatchesExactExecution(state) || spu != state.spu)
    {
        RetireRaw8FistTimingPermission(
            state, "EXECUTION_IDENTITY_CHANGED");
        return realPlayTime;
    }

    bool const exactTimingCall =
        animationActor == state.timingAnimationActor
        && motionType == state.timingMotionType;
    if (!exactTimingCall)
    {
        RetireRaw8FistTimingPermission(
            state, "TIMING_IDENTITY_CHANGED");
        return realPlayTime;
    }
    if (realPlayTime >= state.forcedPlayTime)
    {
        RetireRaw8FistTimingPermission(
            state, "REAL_TIME_REACHED_FORCED_VALUE");
        return realPlayTime;
    }

    GEDouble const returnedPlayTime = state.forcedPlayTime;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (!state.timingApplicationLogged)
    {
        CollisionDiagnostics::LogRaw8FistTimingPermissionApplied(
            actorInstance, state.c1Generation, spu,
            static_cast<void *>(animationActor),
            static_cast<GEInt>(motionType), realPlayTime, state.maxTime,
            state.nativeThresholdConstant, state.computedThreshold,
            returnedPlayTime, true);
        state.timingApplicationLogged = true;
    }
#endif
    return returnedPlayTime;
}

void BeginCombatMoveInvocation(
    gCScriptProcessingUnit *spu, GEBool fullStop,
    InvocationScope &scope)
{
    scope = InvocationScope{};
    scope.previous = g_pCurrentInvocation;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    scope.fullStop = fullStop == GETrue;
#else
    (void) fullStop;
#endif
    g_pCurrentInvocation = &scope;
    if (spu == nullptr)
        return;

    eCEntity *const actorInstance = spu->GetSelfEntity();
    scope.actorInstance = actorInstance;
    scope.spu = spu;
    auto found = g_Raw8FistMarkerExecutions.find(actorInstance);
    if (found == g_Raw8FistMarkerExecutions.end())
        return;

    Raw8FistMarkerExecution const &state = found->second;
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    if (generation.valid
        && generation.generation != state.c1Generation)
    {
        CloseAndEraseExecution(
            found, "C1_GENERATION_REPLACED", true);
        return;
    }
    if (!MatchesPendingOpportunity(state) || state.spu != spu)
        return;

    scope.actorInstance = state.actorInstance;
    scope.fistSourceInstance = state.fistSourceInstance;
    scope.spu = state.spu;
    scope.c1Generation = state.c1Generation;
    scope.opportunityOrdinal = state.opportunityOrdinal;
    scope.active = true;
}

void CompleteCombatMoveInvocation(InvocationScope &scope)
{
    if (scope.active && !scope.contactConsumed)
    {
        auto found = g_Raw8FistMarkerExecutions.find(scope.actorInstance);
        if (found != g_Raw8FistMarkerExecutions.end())
        {
            Raw8FistMarkerExecution &state = found->second;
            bool const sameOpportunity = state.opportunityPending
                && state.opportunityOrdinal == scope.opportunityOrdinal
                && state.c1Generation == scope.c1Generation
                && state.fistSourceInstance == scope.fistSourceInstance
                && state.spu == scope.spu;
            if (sameOpportunity && MatchesPendingOpportunity(state))
            {
                volatile GEU8 *const latch =
                    ResolveExactLiveLatch(state);
                if (latch != nullptr && *latch == 1)
                {
                    GEInt const latchBefore = static_cast<GEInt>(*latch);
                    *latch = 0;
                    GEInt const latchAfter = static_cast<GEInt>(*latch);
                    bool const writeConfirmed = latchAfter == 0;
#ifdef FRAME_COLLISION_DIAGNOSTICS
                    CollisionDiagnostics::LogRaw8FistOpportunityMissRearm(
                        state.actorInstance, state.fistSourceInstance,
                        state.c1Generation, state.opportunityOrdinal,
                        scope.fullStop,
                        latchBefore, latchAfter, writeConfirmed);
#else
                    (void) latchBefore;
                    (void) latchAfter;
                    (void) writeConfirmed;
#endif
                }
            }
        }
    }

    if (g_pCurrentInvocation == &scope)
        g_pCurrentInvocation = scope.previous;
}

void ObserveContactResolutionDispatch(
    void *callerAddress, eCEntity *entityArgument1,
    eCEntity *entityArgument2)
{
    HMODULE const gameModule = ::GetModuleHandleA("Game.dll");
    if (gameModule == nullptr
        || callerAddress
            != reinterpret_cast<void *>(
                reinterpret_cast<std::uintptr_t>(gameModule)
                + 0x0016E348))
    {
        return;
    }

    InvocationScope *const invocation = g_pCurrentInvocation;
    if (invocation == nullptr || !invocation->active)
        return;
    auto found = g_Raw8FistMarkerExecutions.find(entityArgument2);
    if (found == g_Raw8FistMarkerExecutions.end())
        return;

    Raw8FistMarkerExecution &state = found->second;
    bool const exactInvocation = state.opportunityPending
        && state.actorInstance == entityArgument2
        && state.fistSourceInstance == entityArgument1
        && state.actorInstance == invocation->actorInstance
        && state.fistSourceInstance == invocation->fistSourceInstance
        && state.spu == invocation->spu
        && state.c1Generation == invocation->c1Generation
        && state.opportunityOrdinal == invocation->opportunityOrdinal;
    if (!exactInvocation || !MatchesPendingOpportunity(state))
        return;

    volatile GEU8 *const latch = ResolveExactLiveLatch(state);
    GEInt const latchValue =
        latch != nullptr ? static_cast<GEInt>(*latch) : -1;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogRaw8FistOpportunityContactConsumed(
        state.actorInstance, state.fistSourceInstance,
        state.c1Generation, state.opportunityOrdinal, latchValue);
#else
    (void) latchValue;
#endif

    invocation->contactConsumed = true;
    state.opportunityPending = false;
    RetireRaw8FistTimingPermission(state, "CONTACT_CONSUMED");
    // Keep the exact C1 execution record so a later accepted FIST in this
    // generation can reopen a fresh opportunity.
}

void CloseForFinalization(
    CollisionLifecycleGuard::GenerationToken const &generation)
{
    if (!generation.valid)
        return;
    auto found = g_Raw8FistMarkerExecutions.find(
        generation.actorInstance);
    if (found == g_Raw8FistMarkerExecutions.end()
        || found->second.c1Generation != generation.generation)
    {
        return;
    }

    CollisionLifecycleGuard::GenerationToken const currentGeneration =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            generation.actorInstance);
    bool const sameGeneration = currentGeneration.valid
        && currentGeneration.actorInstance == generation.actorInstance
        && currentGeneration.generation == generation.generation;
    if (!sameGeneration)
    {
        CloseAndEraseExecution(
            found,
            "FINALIZATION_GENERATION_CHANGED_NO_LATCH_WRITE", false);
        return;
    }
    CloseAndEraseExecution(found, "C1_FINALIZED", true);
}
}
