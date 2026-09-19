#pragma once

#include "FrameCollisionMarkers.h"

namespace FrameCollision::EquippedSprintCollision
{
bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership);
bool AuthorizeGenericEquippedMarker(
    Entity &actor, MarkerOpcode markerOpcode);
}
