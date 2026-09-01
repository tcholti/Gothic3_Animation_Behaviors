#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::CollisionSourceOperations
{
struct SourceOperationResult
{
    GEInt groupBefore;
    GEInt groupAfter;
    GEInt useType;
    bool skippedGroupForFist;
    bool groupRequested;
    bool triggeredListCleared;
};

bool IsFistCollisionSource(Entity &source);
SourceOperationResult ActivateOrRearm(eCEntity *sourceInstance);
SourceOperationResult DeactivateOwnedAttackSource(eCEntity *sourceInstance);
}
