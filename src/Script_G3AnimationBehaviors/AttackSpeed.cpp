#include "AttackSpeed.h"
#include "SharedConfig.h"

#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>

static mCFunctionHook Hook_GetAnimationSpeedModifier;

static GEBool IsPlayerUsingTwoHandedWeapon(Entity &a_Entity)
{
    if (a_Entity != Entity::GetPlayer())
        return GEFalse;

    gEUseType leftUseType =
        a_Entity.Inventory.GetItemFromSlot(gESlot_LeftHand)
            .Interaction.GetUseType();

    gEUseType rightUseType =
        a_Entity.Inventory.GetItemFromSlot(gESlot_RightHand)
            .Interaction.GetUseType();

    return leftUseType == gEUseType_None
        && rightUseType == gEUseType_2H;
}

GEFloat GE_STDCALL GetAnimationSpeedModifier_G3AB(
    Entity a_Entity,
    gEPhase a_Phase)
{
    // Gothic 3 supplies Action through EAX at this function.
    gEAction action =
        Hook_GetAnimationSpeedModifier.GetImmEax<gEAction>();

    // Preserve Gothic 3's original calculation first.
    GEFloat originalSpeed =
        Hook_GetAnimationSpeedModifier
            .GetOriginalFunction(&GetAnimationSpeedModifier_G3AB)(
                a_Entity,
                a_Phase);

    if (a_Entity == None)
        return originalSpeed;

    // v0.1: player only.
    if (!IsPlayerUsingTwoHandedWeapon(a_Entity))
        return originalSpeed;

    // v0.1: normal Attack only.
    if (action != gEAction_Attack)
        return originalSpeed;

    // v0.1: Hit only.
    // Automatic Recover is deliberately left to Gothic 3.
    if (a_Phase != gEPhase_Hit)
        return originalSpeed;

    return G3ABConfig::TwoHandedNormalAttackSpeed;
}

void InstallAttackSpeedHook()
{
    Hook_GetAnimationSpeedModifier
        .Prepare(
            RVA_ScriptGame(0x42A0),
            &GetAnimationSpeedModifier_G3AB,
            mCBaseHook::mEHookType_Mixed,
            mERegisterType_Eax)
        .Hook();
}
