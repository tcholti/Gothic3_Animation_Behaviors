#include "AttackRaise.h"
#include "BehaviorProfiles.h"

#include <map>
#include <memory>

namespace G3AB::AttackRaise
{
namespace
{
using CombatMoveArgs = gCScriptProcessingUnit::sAICombatMoveInstr_Args;

bool ShouldAddRaise(Entity const &actor, gEAction action)
{
    BehaviorProfiles::AttackType attackType;
    switch (action)
    {
        case gEAction_Attack:
            attackType = BehaviorProfiles::AttackType::Normal;
            break;
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
            attackType = BehaviorProfiles::AttackType::Quick;
            break;
        case gEAction_WhirlAttack:
            attackType = BehaviorProfiles::AttackType::Whirl;
            break;
        default:
            return false;
    }

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

struct RaiseContinuation
{
    CombatMoveArgs hit;
    bool raisePending = true;
    bool directionCaptured = false;
    gEDirection capturedDirection = gEDirection_None;
    bCString capturedDirectionName;

    explicit RaiseContinuation(CombatMoveArgs const &request) : hit(request)
    {}
};

using RaiseState = std::shared_ptr<RaiseContinuation>;
std::map<gCScriptProcessingUnit *, RaiseState> g_RaiseContinuations;

bool IsSameRequest(CombatMoveArgs const &left, CombatMoveArgs const &right)
{
    return left.SelfEntity == right.SelfEntity
        && left.TargetEntity == right.TargetEntity
        && left.Action == right.Action
        && left.PhaseName == right.PhaseName
        && left.AniSpeedScale == right.AniSpeedScale;
}

bool IsCurrent(gCScriptProcessingUnit *spu, RaiseState const &state)
{
    auto const current = g_RaiseContinuations.find(spu);
    return current != g_RaiseContinuations.end() && current->second == state;
}

GEBool CompleteRaiseInvocation(
    gCScriptProcessingUnit *spu, RaiseState const &state,
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
        g_RaiseContinuations.erase(spu);
    return result;
}
}

GEBool RunCombatMove(
    GELPVoid args, gCScriptProcessingUnit *spu, GEBool fullStop,
    gEAction persistedAction, CombatMoveTransport transport)
{
    if (fullStop == GETrue || spu == nullptr)
    {
        CancelRaiseContinuation(spu);
        return transport(args, spu, fullStop);
    }

    auto const pending = g_RaiseContinuations.find(spu);
    if (pending != g_RaiseContinuations.end())
    {
        RaiseState const state = pending->second;
        if (spu->GetSelfEntity() != state->hit.SelfEntity
            || (args == nullptr && persistedAction != state->hit.Action)
            || (args != nullptr
                && !IsSameRequest(*static_cast<CombatMoveArgs *>(args),
                                  state->hit)))
        {
            CancelRaiseContinuation(spu);
            return transport(args, spu, fullStop);
        }

        // A persisted instruction is resumed with null args. Even if the same
        // request is repeated, never restart Raise or an already-started Hit.
        return CompleteRaiseInvocation(
            spu, state, transport(nullptr, spu, fullStop), transport);
    }

    if (args == nullptr)
        return transport(args, spu, fullStop);

    CombatMoveArgs const &request = *static_cast<CombatMoveArgs *>(args);
    if (request.PhaseName != bCString("Hit")
        || !ShouldAddRaise(Entity(request.SelfEntity), request.Action))
    {
        return transport(args, spu, fullStop);
    }

    RaiseState const state = std::make_shared<RaiseContinuation>(request);
    g_RaiseContinuations.emplace(spu, state);
    CombatMoveArgs raise(
        request.SelfEntity, request.TargetEntity, request.Action,
        bCString("Raise"), request.AniSpeedScale);
    return CompleteRaiseInvocation(
        spu, state, transport(&raise, spu, GEFalse), transport);
}

void PreserveNormalContinuationDirection(
    gCScriptProcessingUnit *spu, eCEntity *actor, gEAction action,
    bCString const &phaseName, bCString &directionName)
{
    if (spu == nullptr || actor == nullptr || action != gEAction_Attack)
        return;

    auto const pending = g_RaiseContinuations.find(spu);
    if (pending == g_RaiseContinuations.end())
        return;

    RaiseState const state = pending->second;
    if (state->hit.Action != gEAction_Attack
        || state->hit.SelfEntity != actor)
    {
        return;
    }

    Entity actorEntity(actor);
    if (phaseName == bCString("Raise"))
    {
        state->capturedDirectionName = directionName;
        state->capturedDirection = actorEntity.GetCurrentAniDirection();
        state->directionCaptured = true;
        return;
    }

    if (phaseName != bCString("Hit") || !state->directionCaptured)
        return;

    actorEntity.SetCurrentAniDirection(state->capturedDirection);
    directionName = state->capturedDirectionName;
    state->directionCaptured = false;
}

void CancelRaiseContinuation(gCScriptProcessingUnit *spu)
{
    g_RaiseContinuations.erase(spu);
}
}
