#pragma once

#include <g3sdk/Script.h>

namespace G3AB::AttackMovement
{
void Compose(
    gCScriptProcessingUnit::sAICombatMoveInstr_Args const *request,
    gCScriptProcessingUnit *spu,
    bCVector &movement);
}
