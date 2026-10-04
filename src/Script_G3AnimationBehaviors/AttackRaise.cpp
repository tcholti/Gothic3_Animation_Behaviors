#include "AttackRaise.h"
#include "BehaviorProfiles.h"

#include <map>
#include <memory>

namespace G3AB::AttackRaise
{
namespace
{
using CombatMoveArgs = gCScriptProcessingUnit::sAICombatMoveInstr_Args;

bool ShouldAddRaise(Entity const &actor, gEAction action,
                    BehaviorProfiles::AttackType attackType)
{
    BehaviorProfiles::ProfileKey key;
    if (!BehaviorProfiles::TryBuildRuntimeKey(actor, action, gEPhase_Hit, key))
        return false;

    BehaviorProfiles::Profile const *profile = BehaviorProfiles::Find(key);
    if (profile == nullptr)
        return false;

    BehaviorProfiles::AttackSettings const *settings =
        BehaviorProfiles::GetAttackSettings(*profile, attackType);
    return settings != nullptr
        && settings->raiseOverride == BehaviorProfiles::RaiseOverride::On;
}

struct QuickContinuation
{
    CombatMoveArgs hit;
    bool raisePending = true;

    explicit QuickContinuation(CombatMoveArgs const &request) : hit(request)
    {}
};

using QuickState = std::shared_ptr<QuickContinuation>;
std::map<gCScriptProcessingUnit *, QuickState> g_QuickContinuations;

bool IsSameRequest(CombatMoveArgs const &left, CombatMoveArgs const &right)
{
    return left.SelfEntity == right.SelfEntity
        && left.TargetEntity == right.TargetEntity
        && left.Action == right.Action
        && left.PhaseName == right.PhaseName
        && left.AniSpeedScale == right.AniSpeedScale;
}

bool IsCurrent(gCScriptProcessingUnit *spu, QuickState const &state)
{
    auto const current = g_QuickContinuations.find(spu);
    return current != g_QuickContinuations.end() && current->second == state;
}

GEBool CompleteQuickInvocation(
    gCScriptProcessingUnit *spu, QuickState const &state,
    GEBool result, CombatMoveTransport transport)
{
    // Native callbacks may replace the state/FullStop inside transport.
    // Holding this invocation's state keeps its request alive, but cancellation
    // must prevent that request from being started after native returns.
    if (!IsCurrent(spu, state) || result == GEFalse)
        return result;

    if (state->raisePending)
    {
        state->raisePending = false;
        result = transport(&state->hit, spu, GEFalse);
    }

    if (result != GEFalse && IsCurrent(spu, state))
        g_QuickContinuations.erase(spu);
    return result;
}
}

GEBool RunNormalState(
    bTObjStack<gScriptRunTimeSingleState> &a_rRunTimeStack,
    gCScriptProcessingUnit *a_pSPU, MeleeStateTransport original)
{
    INIT_SCRIPT_STATE();

    if (ShouldAddRaise(SelfEntity, gEAction_Attack,
                       BehaviorProfiles::AttackType::Normal))
    {
        PREPEND_BREAK_BLOCK_BEGIN
        {
            CombatMoveArgs raise(
                SelfEntity.GetInstance(), TargetEntity.GetInstance(),
                gEAction_Attack, bCString("Raise"), 1.0f);
            if (!gCScriptProcessingUnit::sAICombatMoveInstr(
                    &raise, a_pSPU, GEFalse))
                return GEFalse;
        }
        PREPEND_BREAK_BLOCK_END
    }

    return original(a_rRunTimeStack, a_pSPU);
}

GEBool RunWhirlState(
    bTObjStack<gScriptRunTimeSingleState> &a_rRunTimeStack,
    gCScriptProcessingUnit *a_pSPU, MeleeStateTransport original)
{
    INIT_SCRIPT_STATE();

    if (ShouldAddRaise(SelfEntity, gEAction_WhirlAttack,
                       BehaviorProfiles::AttackType::Whirl))
    {
        PREPEND_BREAK_BLOCK_BEGIN
        {
            CombatMoveArgs raise(
                SelfEntity.GetInstance(), TargetEntity.GetInstance(),
                gEAction_WhirlAttack, bCString("Raise"), 1.0f);
            if (!gCScriptProcessingUnit::sAICombatMoveInstr(
                    &raise, a_pSPU, GEFalse))
                return GEFalse;
        }
        PREPEND_BREAK_BLOCK_END
    }

    return original(a_rRunTimeStack, a_pSPU);
}

GEBool RunCombatMove(
    GELPVoid args, gCScriptProcessingUnit *spu, GEBool fullStop,
    gEAction persistedAction, CombatMoveTransport transport)
{
    if (fullStop == GETrue || spu == nullptr)
    {
        CancelQuickContinuation(spu);
        return transport(args, spu, fullStop);
    }

    auto const pending = g_QuickContinuations.find(spu);
    if (pending != g_QuickContinuations.end())
    {
        QuickState const state = pending->second;
        if (spu->GetSelfEntity() != state->hit.SelfEntity
            || (args == nullptr && persistedAction != state->hit.Action)
            || (args != nullptr
                && !IsSameRequest(*static_cast<CombatMoveArgs *>(args),
                                  state->hit)))
        {
            CancelQuickContinuation(spu);
            return transport(args, spu, fullStop);
        }

        // A persisted instruction is resumed with null args. Even if the same
        // request is repeated, never restart Raise or an already-started Hit.
        return CompleteQuickInvocation(
            spu, state, transport(nullptr, spu, fullStop), transport);
    }

    if (args == nullptr)
        return transport(args, spu, fullStop);

    CombatMoveArgs const &request = *static_cast<CombatMoveArgs *>(args);
    if ((request.Action != gEAction_QuickAttackR
         && request.Action != gEAction_QuickAttackL)
        || request.PhaseName != bCString("Hit")
        || !ShouldAddRaise(Entity(request.SelfEntity), request.Action,
                           BehaviorProfiles::AttackType::Quick))
    {
        return transport(args, spu, fullStop);
    }

    QuickState const state = std::make_shared<QuickContinuation>(request);
    g_QuickContinuations.emplace(spu, state);
    CombatMoveArgs raise(
        request.SelfEntity, request.TargetEntity, request.Action,
        bCString("Raise"), 1.0f);
    return CompleteQuickInvocation(
        spu, state, transport(&raise, spu, GEFalse), transport);
}

void CancelQuickContinuation(gCScriptProcessingUnit *spu)
{
    g_QuickContinuations.erase(spu);
}
}
