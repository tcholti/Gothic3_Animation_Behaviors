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
#ifdef FRAME_COLLISION_DIAGNOSTICS
    GEInt damageDisabledBefore;
    GEInt damageDisabledAfter;
#endif
};

SourceOperationResult ActivateOrRearm(eCEntity *sourceInstance);
SourceOperationResult DeactivateOwnedAttackSource(eCEntity *sourceInstance);
FistSourceOperationResult RearmFistSource(eCEntity *sourceInstance);
}
