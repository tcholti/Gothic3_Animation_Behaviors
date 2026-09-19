#include "EquippedSprintProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"
#include "RuntimeClock.h"

#include <cstdio>
#include <string>
#include <unordered_map>

namespace FrameCollision::EquippedSprintProbe
{
struct BoundSprintExecution
{
    std::uint64_t c1Generation;
    unsigned int requiredSourceMask;
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string motionName;
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
    char const *boundary, char const *decision, char const *reason,
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
        "CORE EQUIPPED_SPRINT_PROBE Boundary=%s Decision=%s "
        "Reason=%s Actor=%s ActorAddress=%p Action=%d Phase=%d "
        "Family=%d C1Valid=%d C1Generation=%llu RequiredSourceMask=%u "
        "RightAddress=%p RightUseType=%d LeftAddress=%p LeftUseType=%d "
        "Marker=%s BoundIdentityMatch=%d Motion=%s ElapsedMs=%.3f\n",
        boundary, decision, reason, actor.GetName().GetText(),
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
        g_BoundSprintExecutionByActor.erase(actorInstance);
        LogDecision(
            "CALLBACK", "DELEGATE_NATIVE", "NOT_SPRINT_FAMILY", actor,
            family, MarkerOpcode_Invalid, generation, ownership.decision,
            ownership.sources, motionName.c_str(), -1);
        return false;
    }

    char const *reason = "ELIGIBLE";
    bool eligible = ownership.attackHitEligible
        && actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            == gEAction_SprintAttack;
    if (!eligible)
        reason = "NOT_FACTUAL_SPRINT_HIT";
    else if (!ownership.decision.foundMatchingMotion)
    {
        eligible = false;
        reason = "MATCHING_MOTION_MISSING";
    }
    else if (!ownership.decision.scanValid)
    {
        eligible = false;
        reason = "MOTION_SCAN_INVALID";
    }
    else if (!ownership.decision.markerPresent)
    {
        eligible = false;
        reason = "MARKER_MISSING";
    }
    else if (ownership.decision.hasFistMarkers)
    {
        eligible = false;
        reason = "FIST_MARKER_PRESENT";
    }
    else if (ownership.decision.requiredSourceMask == SourceMask_None)
    {
        eligible = false;
        reason = "NO_ACTIVATING_EQUIPPED_MARKER";
    }
    else if (!CollisionSources::HasRequiredCollisionSources(
                 ownership.sources,
                 ownership.decision.requiredSourceMask))
    {
        eligible = false;
        reason = "REQUIRED_EQUIPPED_SOURCE_MISSING";
    }
    else if (!generation.valid)
    {
        eligible = false;
        reason = "NO_CURRENT_C1_GENERATION";
    }
    else if (motionName.empty())
    {
        eligible = false;
        reason = "MOTION_IDENTITY_MISSING";
    }

    if (!eligible)
    {
        g_BoundSprintExecutionByActor.erase(actorInstance);
        LogDecision(
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
    LogDecision(
        "CALLBACK", "SUPPRESS_NATIVE", "ELIGIBLE", actor,
        family, MarkerOpcode_Invalid, generation, ownership.decision,
        ownership.sources, motionName.c_str(), 1);
    return true;
}

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
    bool const factualSprintHit =
        FrameCollisionMarkers::TryGetCurrentAttackHitFamily(
            actor, currentFamily)
        && currentFamily == AttackFamily_Sprint
        && actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            == gEAction_SprintAttack;

    auto const found = g_BoundSprintExecutionByActor.find(actorInstance);
    if (found == g_BoundSprintExecutionByActor.end())
    {
        if (factualSprintHit)
        {
            LogDecision(
                "MARKER", "DENY_GENERIC_EQUIPPED",
                "NO_BOUND_EXECUTION", actor, currentFamily, markerOpcode,
                generation, decision, sources, motionName.c_str(), 0);
        }
        return false;
    }

    BoundSprintExecution const binding = found->second;
    char const *reason = "BOUND_EXECUTION_MATCHED";
    bool authorized = factualSprintHit;
    if (!authorized)
        reason = "NOT_FACTUAL_SPRINT_HIT";
    else if (!generation.valid
             || generation.generation != binding.c1Generation)
    {
        authorized = false;
        reason = "C1_GENERATION_MISMATCH";
    }
    else if (binding.motionName != motionName)
    {
        authorized = false;
        reason = "MOTION_IDENTITY_MISMATCH";
    }
    else if (!decision.foundMatchingMotion
             || !decision.scanValid
             || !decision.markerPresent)
    {
        authorized = false;
        reason = "MARKED_MOTION_NO_LONGER_VALID";
    }
    else if (decision.hasFistMarkers)
    {
        authorized = false;
        reason = "FIST_MARKER_PRESENT";
    }
    else if (decision.requiredSourceMask == SourceMask_None)
    {
        authorized = false;
        reason = "NO_ACTIVATING_EQUIPPED_MARKER";
    }
    else if (decision.requiredSourceMask != binding.requiredSourceMask)
    {
        authorized = false;
        reason = "REQUIRED_SOURCE_MASK_MISMATCH";
    }
    else if (!CollisionSources::HasRequiredCollisionSources(
                 sources, decision.requiredSourceMask))
    {
        authorized = false;
        reason = "REQUIRED_EQUIPPED_SOURCE_MISSING";
    }
    else if (!RequiredSourceIdentityMatches(binding, sources))
    {
        authorized = false;
        reason = "REQUIRED_SOURCE_IDENTITY_MISMATCH";
    }

    LogDecision(
        "MARKER", authorized ? "AUTHORIZE_GENERIC_EQUIPPED"
                             : "DENY_GENERIC_EQUIPPED",
        reason, actor, currentFamily, markerOpcode, generation,
        decision, sources, motionName.c_str(), authorized ? 1 : 0);
    if (!authorized)
        g_BoundSprintExecutionByActor.erase(actorInstance);
    return authorized;
}
}
