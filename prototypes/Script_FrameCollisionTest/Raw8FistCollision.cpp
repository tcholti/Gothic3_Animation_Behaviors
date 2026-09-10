#include "Raw8FistCollision.h"

#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"
#include "FrameCollisionMarkers.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"
#endif

#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>
#include <windows.h>

namespace FrameCollision::Raw8FistCollision
{
struct Raw8FistMarkerExecution
{
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    gCScriptProcessingUnit *spu;
    eCWrapper_emfx2Actor *animationActor;
    std::uint64_t c1Generation;
    std::string animationName;
    bool timingPermissionArmed;
    GEDouble maxTime;
    GEDouble nativeThresholdConstant;
    GEDouble computedThreshold;
};

struct Raw8FistPrimaryTiming
{
    eCWrapper_emfx2Actor *animationActor;
    bool available;
    GEDouble playTime;
    GEDouble maxTime;
};

static thread_local std::unordered_map<eCEntity *, Raw8FistMarkerExecution>
    g_Raw8FistMarkerExecutions;

bool IsSupportedFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Power
        || family == AttackFamily_Quick;
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

static void RetireRaw8FistTimingPermission(
    Raw8FistMarkerExecution &state, char const *reason)
{
#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (state.timingPermissionArmed)
    {
        CollisionDiagnostics::LogRaw8FistTimingPermissionRetired(
            state.actorInstance, state.c1Generation, state.spu,
            static_cast<void *>(state.animationActor), reason);
    }
#else
    (void) reason;
#endif
    state.timingPermissionArmed = false;
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
        RetireRaw8FistTimingPermission(
            existing->second, "C1_GENERATION_CHANGED");
        g_Raw8FistMarkerExecutions.erase(existing);
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
        // The C1 generation is the factual execution identity. Never repeat
        // the initial close inside the same generation.
        return;
    }

    volatile GEU8 *const latchByte =
        reinterpret_cast<volatile GEU8 *>(spu) + 0x164;
    GEInt const latchBefore = static_cast<GEInt>(*latchByte);
    *latchByte = 1;
    GEInt const latchAfter = static_cast<GEInt>(*latchByte);
    bool const writeConfirmed = latchAfter == 1;
    Raw8FistPrimaryTiming const timing =
        CaptureRaw8FistPrimaryTiming(actor);
#ifdef FRAME_COLLISION_DIAGNOSTICS
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

    bCString const animation = actor.NPC.GetCurrentMovementAni();
    Raw8FistMarkerExecution state = {};
    state.actorInstance = actorInstance;
    state.fistSourceInstance = ownership.fistSourceInstance;
    state.spu = spu;
    state.animationActor = timing.animationActor;
    state.c1Generation = generation.generation;
    state.animationName = animation.GetText() != nullptr
        ? animation.GetText() : "";
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
        || !result.fistLatchWriteConfirmed)
    {
        return;
    }

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

    eCEntity *const actorInstance = actor.GetInstance();
    auto execution = g_Raw8FistMarkerExecutions.find(actorInstance);
    bool ownershipMatched = false;
    if (execution != g_Raw8FistMarkerExecutions.end())
    {
        Raw8FistMarkerExecution &state = execution->second;
        ownershipMatched =
            state.c1Generation == result.c1Generation
            && state.fistSourceInstance == result.fistSourceInstance
            && state.spu == result.fistSPU
            && state.animationActor == timing.animationActor
            && state.animationName == result.currentAnimation;
        RetireRaw8FistTimingPermission(
            state, "SUPERSEDED_BY_ACCEPTED_FIST");
        if (ownershipMatched && thresholdAvailable && realBelowThreshold)
        {
            state.timingPermissionArmed = true;
            state.maxTime = timing.maxTime;
            state.nativeThresholdConstant = nativeThresholdConstant;
            state.computedThreshold = computedThreshold;
        }
    }

#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogRaw8FistMarkerOpportunity(
        actor, result, static_cast<void *>(timing.animationActor),
        timing.available, timing.playTime, timing.maxTime,
        nativeThresholdConstant, computedThreshold, realBelowThreshold,
        ownershipMatched,
        ownershipMatched && thresholdAvailable && realBelowThreshold);
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
        RetireRaw8FistTimingPermission(state, "C1_GENERATION_CHANGED");
        g_Raw8FistMarkerExecutions.erase(execution);
        return realPlayTime;
    }

    if (!state.timingPermissionArmed)
        return realPlayTime;

    auto const primaryMotion =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    bool const exactArmedCall =
        spu == state.spu
        && animationActor == state.animationActor
        && motionType == primaryMotion;
    if (!exactArmedCall)
    {
        RetireRaw8FistTimingPermission(state, "CALL_IDENTITY_CHANGED");
        return realPlayTime;
    }

    Entity actor(state.actorInstance);
    if (actor == None)
    {
        RetireRaw8FistTimingPermission(state, "ACTOR_IDENTITY_INVALID");
        return realPlayTime;
    }
    if (CollisionSources::ResolveFistCollisionSource(actor)
        != state.fistSourceInstance)
    {
        RetireRaw8FistTimingPermission(state, "FIST_SOURCE_CHANGED");
        return realPlayTime;
    }
    bCString const currentAnimation = actor.NPC.GetCurrentMovementAni();
    char const *currentAnimationText = currentAnimation.GetText();
    if (currentAnimationText == nullptr
        || state.animationName != currentAnimationText)
    {
        RetireRaw8FistTimingPermission(
            state, "ANIMATION_IDENTITY_CHANGED");
        return realPlayTime;
    }

    bool const realBelowThreshold =
        realPlayTime < state.computedThreshold;
    GEDouble returnedPlayTime = realPlayTime;
    bool syntheticApplied = false;
    if (realBelowThreshold)
    {
        returnedPlayTime = state.computedThreshold + 0.001;
        if (returnedPlayTime > state.maxTime)
            returnedPlayTime = state.maxTime;
        syntheticApplied = true;
    }

#ifdef FRAME_COLLISION_DIAGNOSTICS
    std::uint64_t const c1Generation = state.c1Generation;
    GEDouble const maxTime = state.maxTime;
    GEDouble const nativeThresholdConstant = state.nativeThresholdConstant;
    GEDouble const computedThreshold = state.computedThreshold;
#endif
    state.timingPermissionArmed = false;

#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogRaw8FistTimingPermissionConsumed(
        actorInstance, c1Generation, spu,
        static_cast<void *>(animationActor),
        static_cast<GEInt>(motionType), realPlayTime, maxTime,
        nativeThresholdConstant, computedThreshold, returnedPlayTime,
        syntheticApplied);
#endif
    return returnedPlayTime;
}
}
