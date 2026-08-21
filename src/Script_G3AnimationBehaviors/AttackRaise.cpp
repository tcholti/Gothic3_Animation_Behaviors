#include "AttackRaise.h"
#include "SharedConfig.h"

#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>

static mCFunctionHook Hook_PS_Melee_Attack;

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

DECLARE_SCRIPT_STATE(PS_Melee_Attack)
{
    INIT_SCRIPT_STATE();

    if (G3ABConfig::EnableTwoHandedNormalRaise
        && IsPlayerUsingTwoHandedWeapon(SelfEntity))
    {
        PREPEND_BREAK_BLOCK_BEGIN
        {
            gCScriptProcessingUnit::sAICombatMoveInstr_Args InstrArgs(
                SelfEntity.GetInstance(),
                TargetEntity.GetInstance(),
                gEAction_Attack,
                bCString("Raise"),
                1.0f);

            if (!gCScriptProcessingUnit::sAICombatMoveInstr(
                    &InstrArgs,
                    a_pSPU,
                    GEFalse))
            {
                return GEFalse;
            }
        }
        PREPEND_BREAK_BLOCK_END
    }

    return Hook_PS_Melee_Attack
        .GetOriginalFunction(&PS_Melee_Attack)(
            a_rRunTimeStack,
            a_pSPU);
}

void InstallAttackRaiseHook()
{
    Hook_PS_Melee_Attack.Hook(
        GetScriptAdminExt()
            .GetScriptAIState("PS_Melee_Attack")
            ->m_funcScriptAIState,
        &PS_Melee_Attack);
}
