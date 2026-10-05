#pragma once

#include <g3sdk/Script.h>

namespace G3AB::AttackRaise
{
using CombatMoveTransport = GEBool (GE_STDCALL *)(
    GELPVoid, gCScriptProcessingUnit *, GEBool);

GEBool RunCombatMove(
    GELPVoid args, gCScriptProcessingUnit *spu, GEBool fullStop,
    gEAction persistedAction, CombatMoveTransport transport);
void PreserveNormalContinuationDirection(
    gCScriptProcessingUnit *spu, eCEntity *actor, gEAction action,
    bCString const &phaseName, bCString &directionName);
void CancelRaiseContinuation(gCScriptProcessingUnit *spu);
}
