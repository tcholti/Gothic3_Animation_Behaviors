#include "PhysicalFistProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"

#include <cstdio>

namespace FrameCollision::PhysicalFistProbe
{
static thread_local QuickCallbackObservation *g_pCurrentQuickCallbackScope =
    nullptr;

static bool IsRaw55ProbeFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Quick
        || family == AttackFamily_Sprint;
}

static bool IsSuppressionFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Sprint;
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

bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu)
{
    // Quick is deliberately observation-only in the follow-up causal probe.
    // Its native callback must run so the probe can bracket the original call.
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

bool ShouldSuppressCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup)
{
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
}
