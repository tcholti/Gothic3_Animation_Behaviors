#include "AttackSpeed.h"

#include "BehaviorProfiles.h"

#include <cmath>

namespace G3AB::AttackSpeed
{
namespace
{
struct NormalReferenceBaseFact
{
    gEUseType leftUseType;
    gEUseType rightUseType;
    GEFloat baseSpeed;
};

NormalReferenceBaseFact const NormalReferenceBaseFacts[] = {
    {gEUseType_None,   gEUseType_1H,      0.6f},
    {gEUseType_Shield, gEUseType_1H,      0.6f},
    {gEUseType_Torch,  gEUseType_1H,      0.6f},
    {gEUseType_1H,     gEUseType_1H,      0.6f},
    {gEUseType_None,   gEUseType_2H,      0.7f},
    {gEUseType_None,   gEUseType_Axe,     0.7f},
    {gEUseType_None,   gEUseType_Staff,   0.7f},
    {gEUseType_None,   gEUseType_Halberd, 0.7f},
};

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

bool TryGetReferenceBase(
    BehaviorProfiles::ProfileKey const &key,
    gEUseType rawLeftUseType,
    gEUseType rawRightUseType,
    gEAction action,
    GEFloat &referenceBase)
{
    // EV-392 freezes the initial technical base facts to the proven Hero routes.
    if (key.animationFamily != "hero")
        return false;

    if (action == gEAction_QuickAttackR
        || action == gEAction_QuickAttackL)
    {
        referenceBase = 1.0f;
        return true;
    }

    if (action != gEAction_Attack)
        return false;

    for (NormalReferenceBaseFact const &fact : NormalReferenceBaseFacts)
    {
        if (fact.leftUseType == rawLeftUseType
            && fact.rightUseType == rawRightUseType)
        {
            referenceBase = fact.baseSpeed;
            return true;
        }
    }

    return false;
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
    if (profile == nullptr || !profile->hasBaseSpeed)
        return compatibleSpeed;

    GEFloat referenceBase = 0.0f;
    if (!TryGetReferenceBase(
            key, rawLeftUseType, rawRightUseType,
            action, referenceBase))
    {
        return compatibleSpeed;
    }

    if (!(referenceBase > 0.0f)
        || !std::isfinite(referenceBase)
        || !std::isfinite(compatibleSpeed))
    {
        return compatibleSpeed;
    }

    return compatibleSpeed * (profile->baseSpeed / referenceBase);
}
}
