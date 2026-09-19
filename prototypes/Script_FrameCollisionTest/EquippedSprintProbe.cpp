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
    eCEntity *rightSourceInstance;
    std::string motionName;
};

static std::unordered_map<eCEntity *, BoundSprintExecution>
    g_BoundSprintExecutionByActor;

static std::string GetMotionName(Entity &actor)
{
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    return motion.GetText() != nullptr ? motion.GetText() : "";
}

static bool HasExactRightMarkerShape(
    CurrentMotionMarkerResult const &decision)
{
    // OFF is not part of the source shape and never receives probe permission.
    return decision.foundMatchingMotion
        && decision.scanValid
        && decision.markerPresent
        && decision.requiredSourceMask == SourceMask_Right
        && !decision.hasFistMarkers
        && decision.markerCounts[MarkerOpcode_Right] > 0
        && decision.markerCounts[MarkerOpcode_Left] == 0
        && decision.markerCounts[MarkerOpcode_Both] == 0
        && decision.markerCounts[MarkerOpcode_Fist] == 0;
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
    Entity &actor, MarkerOpcode markerOpcode,
    CollisionLifecycleGuard::GenerationToken const &generation,
    eCEntity *rightSourceInstance, char const *motionName)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;
    std::fprintf(
        log,
        "CORE EQUIPPED_SPRINT_RIGHT_RAW2_PROBE Boundary=%s Decision=%s "
        "Reason=%s Actor=%s ActorAddress=%p Action=%d Phase=%d "
        "C1Valid=%d C1Generation=%llu RightAddress=%p RightUseType=%d "
        "Marker=%s Motion=%s ElapsedMs=%.3f\n",
        boundary, decision, reason, actor.GetName().GetText(),
        static_cast<void *>(actor.GetInstance()),
        static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyAction>()),
        static_cast<GEInt>(actor.GetCurrentAniPhase()),
        generation.valid ? 1 : 0,
        static_cast<unsigned long long>(generation.generation),
        static_cast<void *>(rightSourceInstance),
        GetUseType(rightSourceInstance),
        FrameCollisionMarkers::GetMarkerOpcodeName(markerOpcode),
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

    if (family != AttackFamily_Sprint)
    {
        g_BoundSprintExecutionByActor.erase(actorInstance);
        return false;
    }

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    std::string const motionName = GetMotionName(actor);
    char const *reason = "ELIGIBLE";
    bool eligible = ownership.attackHitEligible
        && actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            == gEAction_SprintAttack;
    if (!eligible)
        reason = "NOT_FACTUAL_SPRINT_HIT";
    else if (!HasExactRightMarkerShape(ownership.decision))
    {
        eligible = false;
        reason = "NOT_EXACT_RIGHT_ONLY_MARKER_SHAPE";
    }
    else if (ownership.sources.rightInstance == nullptr)
    {
        eligible = false;
        reason = "RIGHT_SOURCE_MISSING";
    }
    else if (GetUseType(ownership.sources.rightInstance)
             != static_cast<GEInt>(gEUseType_1H))
    {
        eligible = false;
        reason = "RIGHT_SOURCE_NOT_RAW2";
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
            MarkerOpcode_Invalid, generation,
            ownership.sources.rightInstance, motionName.c_str());
        return false;
    }

    BoundSprintExecution binding = {};
    binding.c1Generation = generation.generation;
    binding.rightSourceInstance = ownership.sources.rightInstance;
    binding.motionName = motionName;
    g_BoundSprintExecutionByActor[actorInstance] = binding;
    LogDecision(
        "CALLBACK", "SUPPRESS_NATIVE", "ELIGIBLE", actor,
        MarkerOpcode_Invalid, generation,
        ownership.sources.rightInstance, motionName.c_str());
    return true;
}

bool AuthorizeRightMarker(Entity &actor, MarkerOpcode markerOpcode)
{
    eCEntity *const actorInstance = actor != None
        ? actor.GetInstance() : nullptr;
    if (actorInstance == nullptr || markerOpcode != MarkerOpcode_Right)
        return false;

    auto const found = g_BoundSprintExecutionByActor.find(actorInstance);
    if (found == g_BoundSprintExecutionByActor.end())
        return false;

    BoundSprintExecution const binding = found->second;
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
    else if (sources.rightInstance != binding.rightSourceInstance)
    {
        authorized = false;
        reason = "RIGHT_SOURCE_MISMATCH";
    }
    else if (GetUseType(sources.rightInstance)
             != static_cast<GEInt>(gEUseType_1H))
    {
        authorized = false;
        reason = "RIGHT_SOURCE_NOT_RAW2";
    }
    else if (binding.motionName != motionName)
    {
        authorized = false;
        reason = "MOTION_IDENTITY_MISMATCH";
    }
    else if (!HasExactRightMarkerShape(decision))
    {
        authorized = false;
        reason = "MARKER_SHAPE_MISMATCH";
    }

    LogDecision(
        "MARKER", authorized ? "AUTHORIZE_GENERIC_RIGHT"
                             : "DENY_GENERIC_RIGHT",
        reason, actor, markerOpcode, generation,
        sources.rightInstance, motionName.c_str());
    if (!authorized)
        g_BoundSprintExecutionByActor.erase(actorInstance);
    return authorized;
}
}
