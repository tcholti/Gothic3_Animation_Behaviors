#pragma once

#include "FrameCollisionMarkers.h"

namespace FrameCollision::PhysicalFistProbe
{
bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu);
}
