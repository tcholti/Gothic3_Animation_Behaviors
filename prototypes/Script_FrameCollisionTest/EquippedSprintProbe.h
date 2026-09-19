#pragma once

#include "FrameCollisionMarkers.h"

namespace FrameCollision::EquippedSprintProbe
{
bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership);
bool AuthorizeRightMarker(Entity &actor, MarkerOpcode markerOpcode);
}
