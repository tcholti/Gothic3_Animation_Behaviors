#include "AttackSpeed.h"

#include "BehaviorProfiles.h"

#include <cmath>

namespace G3AB::AttackSpeed
{
namespace
{
bool TryGetActionProfile(
    gEAction action,
    BehaviorProfiles::ActionProfile &actionProfile)
{
    switch (action)
    {
        case gEAction_Attack:
            actionProfile = BehaviorProfiles::ActionProfile::Normal;
            return true;
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
            actionProfile = BehaviorProfiles::ActionProfile::Quick;
            return true;
        default:
            return false;
    }
}
}

GEFloat ComposeCompatibleSpeed(
    Entity const &entity,
    gEAction action,
    gEPhase phase,
    GEFloat compatibleSpeed)
{
    if (phase != gEPhase_Hit || entity == None)
        return compatibleSpeed;

    BehaviorProfiles::ActionProfile actionProfile;
    if (!TryGetActionProfile(action, actionProfile))
        return compatibleSpeed;

    BehaviorProfiles::ProfileKey key;
    gEUseType rawLeftUseType = gEUseType_None;
    gEUseType rawRightUseType = gEUseType_None;
    if (!BehaviorProfiles::TryBuildRuntimeKey(
            entity, actionProfile, key,
            rawLeftUseType, rawRightUseType))
    {
        return compatibleSpeed;
    }

    BehaviorProfiles::Profile const *profile = BehaviorProfiles::Find(key);
    if (profile == nullptr
        || !profile->hasBaseSpeed
        || !profile->hasReferenceHitBaseSpeed)
    {
        return compatibleSpeed;
    }

    GEFloat const referenceBase = profile->referenceHitBaseSpeed;
    if (!(referenceBase > 0.0f)
        || !std::isfinite(referenceBase)
        || !std::isfinite(compatibleSpeed))
    {
        return compatibleSpeed;
    }

    GEFloat const composedSpeed =
        compatibleSpeed * (profile->baseSpeed / referenceBase);
    if (!std::isfinite(composedSpeed))
        return compatibleSpeed;

    return composedSpeed;
}
}
