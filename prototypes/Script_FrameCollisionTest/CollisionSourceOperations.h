#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::CollisionSourceOperations
{
struct SourceOperationResult
{
    GEInt groupBefore;
    GEInt groupAfter;
    GEInt useType;
    bool groupRequested;
    bool triggeredListCleared;
};

struct FistSourceOperationResult
{
    GEInt groupBefore;
    GEInt groupAfter;
    GEInt useType;
    bool triggeredListCleared;
};

SourceOperationResult ActivateOrRearm(eCEntity *sourceInstance);
SourceOperationResult DeactivateOwnedAttackSource(eCEntity *sourceInstance);
FistSourceOperationResult RearmFistSource(eCEntity *sourceInstance);
}
