#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::CollisionSources
{
EquippedCollisionSources GetEquippedCollisionSources(Entity &actor);
eCEntity *ResolveFistCollisionSource(Entity &actor);
gEUseType GetCollisionSourceUseType(Entity &source);
bool HasRequiredCollisionSources(
    EquippedCollisionSources const &sources, unsigned int requiredMask);
}
