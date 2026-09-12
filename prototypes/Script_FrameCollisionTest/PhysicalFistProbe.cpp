#include "PhysicalFistProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"

#include <cstdio>
#include <unordered_map>

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
};

static thread_local QuickCallbackObservation *g_pCurrentQuickCallbackScope =
    nullptr;
static thread_local std::unordered_map<eCEntity *, QuickEarlySuppressionProof>
    g_QuickEarlySuppressionProofs;
static thread_local
    std::unordered_map<eCEntity *, QuickPreStateFistIntervention>
        g_QuickPreStateFistInterventions;

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

void OnMarkerProcessed(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return;

    if (TryApplyPreStateFistProbe(actor, markerOpcode, result))
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
}
