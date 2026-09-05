#include "CollisionSourceOperations.h"

#include "CollisionSources.h"

namespace FrameCollision::CollisionSourceOperations
{
bool IsFistCollisionSource(Entity &source)
{
    if (source == None)
        return false;
    gEUseType const useType = CollisionSources::GetCollisionSourceUseType(source);
    return useType == gEUseType_Fist || useType == gEUseType_PhysicalFist;
}

SourceOperationResult ActivateOrRearm(eCEntity *sourceInstance)
{
    SourceOperationResult result = {};
    result.groupBefore = -1;
    result.groupAfter = -1;
    result.useType = -1;
    if (sourceInstance == nullptr)
        return result;

    Entity source(sourceInstance);
    if (source == None)
        return result;

    result.groupBefore = static_cast<GEInt>(source.GetCollisionGroup());
    result.useType = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(source));
    result.skippedGroupForFist = IsFistCollisionSource(source);
    if (!result.skippedGroupForFist)
    {
        source.SetCollisionGroup(eECollisionGroup_Item_Attack);
        result.groupRequested = true;
    }
    source.TouchDamage.ClearTriggeredList();
    result.triggeredListCleared = true;
    // TEMPORARY CAUSAL PROBE: isolate whether TouchDamage.DamageDisabled
    // suppresses logical Fist/body-contact damage without weapon-group mutation.
    if (result.skippedGroupForFist)
        source.TouchDamage.SetDamageDisabled(GETrue);
    result.groupAfter = static_cast<GEInt>(source.GetCollisionGroup());
    return result;
}

SourceOperationResult DeactivateOwnedAttackSource(eCEntity *sourceInstance)
{
    SourceOperationResult result = {};
    result.groupBefore = -1;
    result.groupAfter = -1;
    result.useType = -1;
    if (sourceInstance == nullptr)
        return result;

    Entity source(sourceInstance);
    if (source == None)
        return result;

    result.groupBefore = static_cast<GEInt>(source.GetCollisionGroup());
    result.useType = static_cast<GEInt>(
        CollisionSources::GetCollisionSourceUseType(source));
    result.skippedGroupForFist = IsFistCollisionSource(source);
    if (!result.skippedGroupForFist
        && source.GetCollisionGroup() == eECollisionGroup_Item_Attack)
    {
        source.SetCollisionGroup(eECollisionGroup_Item_Equipped);
        result.groupRequested = true;
    }
    result.groupAfter = static_cast<GEInt>(source.GetCollisionGroup());
    return result;
}
}
