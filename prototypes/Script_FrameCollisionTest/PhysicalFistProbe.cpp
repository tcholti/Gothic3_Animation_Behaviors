#include "PhysicalFistProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"

#include <cstdio>

namespace FrameCollision::PhysicalFistProbe
{
static bool IsProbeFamily(AttackFamily family)
{
    return family == AttackFamily_Normal
        || family == AttackFamily_Quick
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

bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu)
{
    if (actor == None || actor.GetInstance() == nullptr)
        return false;

    eCEntity *const actorInstance = actor.GetInstance();
    if (spu == nullptr || spu->GetSelfEntity() != actorInstance)
        return false;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    if (!generation.valid || !ownership.attackHitEligible
        || !IsProbeFamily(family))
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

    eCEntity *const rightInstance = ownership.sources.rightInstance;
    Entity rightSource(rightInstance);
    if (rightSource == None
        || CollisionSources::GetCollisionSourceUseType(rightSource)
            != gEUseType_PhysicalFist
        || rightSource.GetCollisionGroup()
            != eECollisionGroup_Item_Equipped)
    {
        return false;
    }

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
}
