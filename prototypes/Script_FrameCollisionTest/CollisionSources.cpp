#include "CollisionSources.h"

namespace FrameCollision::CollisionSources
{
EquippedCollisionSources GetEquippedCollisionSources(Entity &actor)
{
    EquippedCollisionSources result = {};
    Entity right = actor.Inventory.GetItemFromSlot(gESlot_RightHand);
    Entity left = actor.Inventory.GetItemFromSlot(gESlot_LeftHand);
    result.rightInstance = right != None ? right.GetInstance() : nullptr;
    result.leftInstance = left != None ? left.GetInstance() : nullptr;
    return result;
}

bool HasRequiredCollisionSources(
    EquippedCollisionSources const &sources, unsigned int requiredMask)
{
    if ((requiredMask & SourceMask_Right) != 0 && sources.rightInstance == nullptr)
        return false;
    if ((requiredMask & SourceMask_Left) != 0 && sources.leftInstance == nullptr)
        return false;
    return true;
}

gEUseType GetCollisionSourceUseType(Entity &source)
{
    eCEntity *instance = source.GetInstance();
    return instance != nullptr ? gCEntity::GetUseType(instance) : gEUseType_None;
}
}
