#pragma once

#include "FrameCollisionShared.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

namespace FrameCollision::FrameCollisionMarkers
{
struct AttackCallbackOwnershipResult;
}

namespace FrameCollision::Raw8FistCollision
{
bool IsSupportedFamily(AttackFamily family);

void UpdateMarkerOwnership(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu);
void ApplyAcceptedMarkerLatch(
    Entity &actor, MarkerProcessResult &result);
void UpdateTimingPermissionFromMarker(
    Entity &actor, MarkerProcessResult const &result);
GEDouble ApplyTimingPermission(
    gCScriptProcessingUnit *spu,
    eCWrapper_emfx2Actor *animationActor,
    eCWrapper_emfx2Actor::eEMotionType motionType,
    GEDouble realPlayTime);
}
