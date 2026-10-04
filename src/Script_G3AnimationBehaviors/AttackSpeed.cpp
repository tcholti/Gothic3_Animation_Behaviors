#include "AttackSpeed.h"

#include "BehaviorProfiles.h"

#include <cmath>

namespace G3AB::AttackSpeed
{
namespace
{
bool TryGetAttackType(
    gEAction action,
    BehaviorProfiles::AttackType &attackType)
{
    switch (action)
    {
        case gEAction_Attack:
            attackType = BehaviorProfiles::AttackType::Normal;
            return true;
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
            attackType = BehaviorProfiles::AttackType::Quick;
            return true;
        case gEAction_PowerAttack:
            attackType = BehaviorProfiles::AttackType::Power;
            return true;
        case gEAction_PierceAttack:
            attackType = BehaviorProfiles::AttackType::Pierce;
            return true;
        case gEAction_HackAttack:
            attackType = BehaviorProfiles::AttackType::Hack;
            return true;
        case gEAction_SimpleWhirl:
            attackType = BehaviorProfiles::AttackType::SimpleWhirl;
            return true;
        case gEAction_WhirlAttack:
            attackType = BehaviorProfiles::AttackType::Whirl;
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
    bool const isPowerRaise =
        phase == gEPhase_Raise && action == gEAction_PowerAttack;
    if ((phase != gEPhase_Hit && !isPowerRaise) || entity == None)
        return compatibleSpeed;

    BehaviorProfiles::AttackType attackType;
    if (!TryGetAttackType(action, attackType))
        return compatibleSpeed;

    BehaviorProfiles::ProfileKey key;
    // Raise shares the Power Hit profile; its distinct live phase speed stays
    // in compatibleSpeed and receives the same authoring ratio below.
    if (!BehaviorProfiles::TryBuildRuntimeKey(entity, action, gEPhase_Hit, key))
        return compatibleSpeed;

    BehaviorProfiles::Profile const *profile = BehaviorProfiles::Find(key);
    if (profile == nullptr)
        return compatibleSpeed;

    BehaviorProfiles::AttackSettings const *settings =
        BehaviorProfiles::GetAttackSettings(*profile, attackType);
    if (settings == nullptr
        || !settings->hasBaseSpeed
        || !settings->hasReferenceHitBaseSpeed)
    {
        return compatibleSpeed;
    }

    GEFloat const referenceBase = settings->referenceHitBaseSpeed;
    if (!(referenceBase > 0.0f)
        || !std::isfinite(referenceBase)
        || !std::isfinite(compatibleSpeed))
    {
        return compatibleSpeed;
    }

    GEFloat const composedSpeed =
        compatibleSpeed * (settings->baseSpeed / referenceBase);
    if (!std::isfinite(composedSpeed))
        return compatibleSpeed;

    return composedSpeed;
}
}
