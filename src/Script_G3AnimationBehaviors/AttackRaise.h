#pragma once

#include <g3sdk/Script.h>

namespace G3AB::AttackRaise
{
using MeleeStateTransport = GEBool (GE_STDCALL *)(
    bTObjStack<gScriptRunTimeSingleState> &, gCScriptProcessingUnit *);
using CombatMoveTransport = GEBool (GE_STDCALL *)(
    GELPVoid, gCScriptProcessingUnit *, GEBool);

GEBool RunNormalState(
    bTObjStack<gScriptRunTimeSingleState> &a_rRunTimeStack,
    gCScriptProcessingUnit *a_pSPU, MeleeStateTransport original);
GEBool RunWhirlState(
    bTObjStack<gScriptRunTimeSingleState> &a_rRunTimeStack,
    gCScriptProcessingUnit *a_pSPU, MeleeStateTransport original);
GEBool RunCombatMove(
    GELPVoid args, gCScriptProcessingUnit *spu, GEBool fullStop,
    gEAction persistedAction, CombatMoveTransport transport);
void CancelQuickContinuation(gCScriptProcessingUnit *spu);
}
