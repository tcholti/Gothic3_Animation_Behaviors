#include "EquippedSprintCollision.h"

#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"
#include "RuntimeClock.h"

#include <cstdio>
#endif

#include <cstdint>
#include <string>
#include <unordered_map>

namespace FrameCollision::EquippedSprintCollision
{
struct BoundSprintExecution
{
    std::uint64_t c1Generation;
    unsigned int requiredSourceMask;
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string motionName;
};

enum DecisionReason
{
    DecisionReason_None,
    DecisionReason_Eligible,
    DecisionReason_BoundExecutionMatched,
    DecisionReason_BoundSprintOriginPowerContinuation,
    DecisionReason_NotFactualSprintHit,
    DecisionReason_MatchingMotionMissing,
    DecisionReason_MotionScanInvalid,
    DecisionReason_MarkerMissing,
    DecisionReason_FistMarkerPresent,
    DecisionReason_NoActivatingEquippedMarker,
    DecisionReason_RequiredEquippedSourceMissing,
    DecisionReason_NoCurrentC1Generation,
    DecisionReason_MotionIdentityMissing,
    DecisionReason_C1GenerationMismatch,
    DecisionReason_MotionIdentityMismatch,
    DecisionReason_MarkedMotionNoLongerValid,
    DecisionReason_RequiredSourceMaskMismatch,
    DecisionReason_RequiredSourceIdentityMismatch,
    DecisionReason_NoBoundExecution,
    DecisionReason_NoBoundSprintOrigin,
    DecisionReason_NotSprintOrPowerHit
};

static std::unordered_map<eCEntity *, BoundSprintExecution>
    g_BoundSprintExecutionByActor;

static std::string GetMotionName(Entity &actor)
{
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    return motion.GetText() != nullptr ? motion.GetText() : "";
}

static bool IsGenericEquippedMarker(MarkerOpcode markerOpcode)
{
    return markerOpcode == MarkerOpcode_Right
        || markerOpcode == MarkerOpcode_Left
        || markerOpcode == MarkerOpcode_Both
        || markerOpcode == MarkerOpcode_Off;
}

#ifdef FRAME_COLLISION_DIAGNOSTICS
static char const *GetDecisionReasonName(DecisionReason reason)
{
    switch (reason)
    {
        case DecisionReason_Eligible:
            return "ELIGIBLE";
        case DecisionReason_BoundExecutionMatched:
            return "BOUND_EXECUTION_MATCHED";
        case DecisionReason_BoundSprintOriginPowerContinuation:
            return "BOUND_SPRINT_ORIGIN_POWER_CONTINUATION";
        case DecisionReason_NotFactualSprintHit:
            return "NOT_FACTUAL_SPRINT_HIT";
        case DecisionReason_MatchingMotionMissing:
            return "MATCHING_MOTION_MISSING";
        case DecisionReason_MotionScanInvalid:
            return "MOTION_SCAN_INVALID";
        case DecisionReason_MarkerMissing:
            return "MARKER_MISSING";
        case DecisionReason_FistMarkerPresent:
            return "FIST_MARKER_PRESENT";
        case DecisionReason_NoActivatingEquippedMarker:
            return "NO_ACTIVATING_EQUIPPED_MARKER";
        case DecisionReason_RequiredEquippedSourceMissing:
            return "REQUIRED_EQUIPPED_SOURCE_MISSING";
        case DecisionReason_NoCurrentC1Generation:
            return "NO_CURRENT_C1_GENERATION";
        case DecisionReason_MotionIdentityMissing:
            return "MOTION_IDENTITY_MISSING";
        case DecisionReason_C1GenerationMismatch:
            return "C1_GENERATION_MISMATCH";
        case DecisionReason_MotionIdentityMismatch:
            return "MOTION_IDENTITY_MISMATCH";
        case DecisionReason_MarkedMotionNoLongerValid:
            return "MARKED_MOTION_NO_LONGER_VALID";
        case DecisionReason_RequiredSourceMaskMismatch:
            return "REQUIRED_SOURCE_MASK_MISMATCH";
        case DecisionReason_RequiredSourceIdentityMismatch:
            return "REQUIRED_SOURCE_IDENTITY_MISMATCH";
        case DecisionReason_NoBoundExecution:
            return "NO_BOUND_EXECUTION";
        case DecisionReason_NoBoundSprintOrigin:
            return "NO_BOUND_SPRINT_ORIGIN";
        case DecisionReason_NotSprintOrPowerHit:
            return "NOT_SPRINT_OR_POWER_HIT";
        default:
            return "NONE";
    }
}

static GEInt GetUseType(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return static_cast<GEInt>(gEUseType_None);
    Entity source(sourceInstance);
    return source != None
        ? static_cast<GEInt>(
              CollisionSources::GetCollisionSourceUseType(source))
        : static_cast<GEInt>(gEUseType_None);
}

static void LogDecision(
    char const *boundary, char const *decision, DecisionReason reason,
    Entity &actor, AttackFamily family, MarkerOpcode markerOpcode,
    CollisionLifecycleGuard::GenerationToken const &generation,
    CurrentMotionMarkerResult const &motionDecision,
    EquippedCollisionSources const &sources, char const *motionName,
    GEInt boundIdentityMatch)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;
    std::fprintf(
        log,
        "CORE EQUIPPED_SPRINT_COLLISION Boundary=%s Decision=%s "
        "Reason=%s Actor=%s ActorAddress=%p Action=%d Phase=%d "
        "Family=%d C1Valid=%d C1Generation=%llu RequiredSourceMask=%u "
        "RightAddress=%p RightUseType=%d LeftAddress=%p LeftUseType=%d "
        "Marker=%s BoundIdentityMatch=%d Motion=%s ElapsedMs=%.3f\n",
        boundary, decision, GetDecisionReasonName(reason),
        actor.GetName().GetText(),
        static_cast<void *>(actor.GetInstance()),
        static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyAction>()),
        static_cast<GEInt>(actor.GetCurrentAniPhase()),
        static_cast<GEInt>(family),
        generation.valid ? 1 : 0,
        static_cast<unsigned long long>(generation.generation),
        motionDecision.requiredSourceMask,
        static_cast<void *>(sources.rightInstance),
        GetUseType(sources.rightInstance),
        static_cast<void *>(sources.leftInstance),
        GetUseType(sources.leftInstance),
        FrameCollisionMarkers::GetMarkerOpcodeName(markerOpcode),
        boundIdentityMatch,
        motionName != nullptr ? motionName : "",
        RuntimeClock::GetElapsedMilliseconds());
    std::fflush(log);
}

#define EQUIPPED_SPRINT_LOG(...) LogDecision(__VA_ARGS__)
#else
#define EQUIPPED_SPRINT_LOG(...) ((void)0)
#endif

static bool RequiredSourceIdentityMatches(
    BoundSprintExecution const &binding,
    EquippedCollisionSources const &sources)
{
    if ((binding.requiredSourceMask & SourceMask_Right) != 0
        && sources.rightInstance != binding.rightSourceInstance)
    {
        return false;
    }
    if ((binding.requiredSourceMask & SourceMask_Left) != 0
        && sources.leftInstance != binding.leftSourceInstance)
    {
        return false;
    }
    return true;
}

static DecisionReason GetBoundExecutionIdentityMismatchReason(
    BoundSprintExecution const &binding,
    CollisionLifecycleGuard::GenerationToken const &generation,
    std::string const &motionName,
    CurrentMotionMarkerResult const &decision,
    EquippedCollisionSources const &sources)
{
    if (!generation.valid
        || generation.generation != binding.c1Generation)
    {
        return DecisionReason_C1GenerationMismatch;
    }
    if (binding.motionName != motionName)
        return DecisionReason_MotionIdentityMismatch;
    if (!decision.foundMatchingMotion
        || !decision.scanValid
        || !decision.markerPresent)
    {
        return DecisionReason_MarkedMotionNoLongerValid;
    }
    if (decision.hasFistMarkers)
        return DecisionReason_FistMarkerPresent;
    if (decision.requiredSourceMask == SourceMask_None)
        return DecisionReason_NoActivatingEquippedMarker;
    if (decision.requiredSourceMask != binding.requiredSourceMask)
        return DecisionReason_RequiredSourceMaskMismatch;
    if (!CollisionSources::HasRequiredCollisionSources(
            sources, decision.requiredSourceMask))
    {
        return DecisionReason_RequiredEquippedSourceMissing;
    }
    if (!RequiredSourceIdentityMatches(binding, sources))
        return DecisionReason_RequiredSourceIdentityMismatch;
    return DecisionReason_None;
}

bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership)
{
    eCEntity *const actorInstance = actor != None
        ? actor.GetInstance() : nullptr;
    if (actorInstance == nullptr)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    std::string const motionName = GetMotionName(actor);
    if (family != AttackFamily_Sprint)
    {
        auto const found =
            g_BoundSprintExecutionByActor.find(actorInstance);
        bool const factualPowerHit = family == AttackFamily_Power
            && ownership.attackHitEligible
            && actor.Routine.GetProperty<PSRoutine::PropertyAction>()
                == gEAction_PowerAttack;
        if (found != g_BoundSprintExecutionByActor.end()
            && factualPowerHit)
        {
            DecisionReason const mismatchReason =
                GetBoundExecutionIdentityMismatchReason(
                    found->second, generation, motionName,
                    ownership.decision, ownership.sources);
            if (mismatchReason == DecisionReason_None)
            {
                EQUIPPED_SPRINT_LOG(
                    "CALLBACK", "DELEGATE_NATIVE",
                    DecisionReason_BoundSprintOriginPowerContinuation,
                    actor, family, MarkerOpcode_Invalid, generation,
                    ownership.decision, ownership.sources,
                    motionName.c_str(), 1);
                return false;
            }
            g_BoundSprintExecutionByActor.erase(found);
            EQUIPPED_SPRINT_LOG(
                "CALLBACK", "DELEGATE_NATIVE", mismatchReason, actor,
                family, MarkerOpcode_Invalid, generation,
                ownership.decision, ownership.sources,
                motionName.c_str(), 0);
            return false;
        }

        g_BoundSprintExecutionByActor.erase(actorInstance);
        EQUIPPED_SPRINT_LOG(
            "CALLBACK", "DELEGATE_NATIVE",
            factualPowerHit ? DecisionReason_NoBoundSprintOrigin
                            : DecisionReason_NotSprintOrPowerHit,
            actor, family, MarkerOpcode_Invalid, generation,
            ownership.decision, ownership.sources,
            motionName.c_str(), -1);
        return false;
    }

    DecisionReason reason = DecisionReason_Eligible;
    bool eligible = ownership.attackHitEligible
        && actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            == gEAction_SprintAttack;
    if (!eligible)
        reason = DecisionReason_NotFactualSprintHit;
    else if (!ownership.decision.foundMatchingMotion)
    {
        eligible = false;
        reason = DecisionReason_MatchingMotionMissing;
    }
    else if (!ownership.decision.scanValid)
    {
        eligible = false;
        reason = DecisionReason_MotionScanInvalid;
    }
    else if (!ownership.decision.markerPresent)
    {
        eligible = false;
        reason = DecisionReason_MarkerMissing;
    }
    else if (ownership.decision.hasFistMarkers)
    {
        eligible = false;
        reason = DecisionReason_FistMarkerPresent;
    }
    else if (ownership.decision.requiredSourceMask == SourceMask_None)
    {
        eligible = false;
        reason = DecisionReason_NoActivatingEquippedMarker;
    }
    else if (!CollisionSources::HasRequiredCollisionSources(
                 ownership.sources,
                 ownership.decision.requiredSourceMask))
    {
        eligible = false;
        reason = DecisionReason_RequiredEquippedSourceMissing;
    }
    else if (!generation.valid)
    {
        eligible = false;
        reason = DecisionReason_NoCurrentC1Generation;
    }
    else if (motionName.empty())
    {
        eligible = false;
        reason = DecisionReason_MotionIdentityMissing;
    }

    if (!eligible)
    {
        g_BoundSprintExecutionByActor.erase(actorInstance);
        EQUIPPED_SPRINT_LOG(
            "CALLBACK", "DELEGATE_NATIVE", reason, actor,
            family, MarkerOpcode_Invalid, generation, ownership.decision,
            ownership.sources, motionName.c_str(), -1);
        return false;
    }

    BoundSprintExecution binding = {};
    binding.c1Generation = generation.generation;
    binding.requiredSourceMask = ownership.decision.requiredSourceMask;
    binding.rightSourceInstance = ownership.sources.rightInstance;
    binding.leftSourceInstance = ownership.sources.leftInstance;
    binding.motionName = motionName;
    g_BoundSprintExecutionByActor[actorInstance] = binding;
    EQUIPPED_SPRINT_LOG(
        "CALLBACK", "SUPPRESS_NATIVE", DecisionReason_Eligible, actor,
        family, MarkerOpcode_Invalid, generation, ownership.decision,
        ownership.sources, motionName.c_str(), 1);
    return true;
}

bool AuthorizeGenericEquippedMarker(
    Entity &actor, MarkerOpcode markerOpcode)
{
    eCEntity *const actorInstance = actor != None
        ? actor.GetInstance() : nullptr;
    if (actorInstance == nullptr || !IsGenericEquippedMarker(markerOpcode))
        return false;

    EquippedCollisionSources const sources =
        CollisionSources::GetEquippedCollisionSources(actor);
    CurrentMotionMarkerResult const decision =
        FrameCollisionMarkers::GetCurrentMarkerDecision(actor);
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    std::string const motionName = GetMotionName(actor);
    AttackFamily currentFamily = AttackFamily_Normal;
    bool const attackHit =
        FrameCollisionMarkers::TryGetCurrentAttackHitFamily(
            actor, currentFamily);
    gEAction const currentAction =
        actor.Routine.GetProperty<PSRoutine::PropertyAction>();
    bool const factualSprintHit = attackHit
        && currentFamily == AttackFamily_Sprint
        && currentAction == gEAction_SprintAttack;
    bool const factualPowerHit = attackHit
        && currentFamily == AttackFamily_Power
        && currentAction == gEAction_PowerAttack;

    auto const found = g_BoundSprintExecutionByActor.find(actorInstance);
    if (found == g_BoundSprintExecutionByActor.end())
    {
        if (factualSprintHit)
        {
            EQUIPPED_SPRINT_LOG(
                "MARKER", "DENY_GENERIC_EQUIPPED",
                DecisionReason_NoBoundExecution, actor, currentFamily,
                markerOpcode, generation, decision, sources,
                motionName.c_str(), 0);
        }
        return false;
    }

    BoundSprintExecution const binding = found->second;
    DecisionReason reason = DecisionReason_None;
    bool authorized = factualSprintHit || factualPowerHit;
    if (!authorized)
        reason = DecisionReason_NotSprintOrPowerHit;
    else
    {
        reason = GetBoundExecutionIdentityMismatchReason(
            binding, generation, motionName, decision, sources);
        authorized = reason == DecisionReason_None;
    }

    if (authorized)
    {
        reason = factualPowerHit
            ? DecisionReason_BoundSprintOriginPowerContinuation
            : DecisionReason_BoundExecutionMatched;
    }

    EQUIPPED_SPRINT_LOG(
        "MARKER", authorized ? "AUTHORIZE_GENERIC_EQUIPPED"
                             : "DENY_GENERIC_EQUIPPED",
        reason, actor, currentFamily, markerOpcode, generation,
        decision, sources, motionName.c_str(), authorized ? 1 : 0);
    if (!authorized)
        g_BoundSprintExecutionByActor.erase(actorInstance);
    return authorized;
}

void RetireFinalizedGeneration(
    eCEntity *actorInstance, std::uint64_t c1Generation)
{
    auto found = g_BoundSprintExecutionByActor.find(actorInstance);
    if (found != g_BoundSprintExecutionByActor.end()
        && found->second.c1Generation == c1Generation)
    {
        g_BoundSprintExecutionByActor.erase(found);
    }
}

#undef EQUIPPED_SPRINT_LOG
}
