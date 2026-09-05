#include "CollisionSourceOperations.h"

#include "CollisionSources.h"

namespace FrameCollision::CollisionSourceOperations
{
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
    source.SetCollisionGroup(eECollisionGroup_Item_Attack);
    result.groupRequested = true;
    source.TouchDamage.ClearTriggeredList();
    result.triggeredListCleared = true;
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
    if (source.GetCollisionGroup() == eECollisionGroup_Item_Attack)
    {
        source.SetCollisionGroup(eECollisionGroup_Item_Equipped);
        result.groupRequested = true;
    }
    result.groupAfter = static_cast<GEInt>(source.GetCollisionGroup());
    return result;
}

FistSourceOperationResult RearmFistSource(eCEntity *sourceInstance)
{
    FistSourceOperationResult result = {};
    result.groupBefore = -1;
    result.groupAfter = -1;
    result.useType = -1;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    result.damageDisabledBefore = -1;
    result.damageDisabledAfter = -1;
#endif
    if (sourceInstance == nullptr)
        return result;

    Entity source(sourceInstance);
    if (source == None)
        return result;

    gEUseType const useType =
        CollisionSources::GetCollisionSourceUseType(source);
    if (useType != gEUseType_Fist)
        return result;

    result.groupBefore = static_cast<GEInt>(source.GetCollisionGroup());
    result.useType = static_cast<GEInt>(useType);
    source.TouchDamage.ClearTriggeredList();
    result.triggeredListCleared = true;
    // TEMPORARY CAUSAL PROBE: test DamageDisabled on the proven FIST route.
    gCTouchDamage_PS *touchDamagePS = static_cast<gCTouchDamage_PS *>(
        source.TouchDamage.m_pEngineEntityPropertySet);
    if (touchDamagePS != nullptr)
    {
#ifdef FRAME_COLLISION_DIAGNOSTICS
        result.damageDisabledBefore = static_cast<GEInt>(
            touchDamagePS->GetDamageDisabled());
#endif
        touchDamagePS->SetDamageDisabled(GETrue);
#ifdef FRAME_COLLISION_DIAGNOSTICS
        result.damageDisabledAfter = static_cast<GEInt>(
            touchDamagePS->GetDamageDisabled());
#endif
    }
    result.groupAfter = static_cast<GEInt>(source.GetCollisionGroup());
    return result;
}
}
