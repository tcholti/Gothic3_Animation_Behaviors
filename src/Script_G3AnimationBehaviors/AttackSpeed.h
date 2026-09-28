#pragma once

#include <g3sdk/Script.h>

namespace G3AB::AttackSpeed
{
GEFloat ComposeCompatibleSpeed(
    Entity const &entity,
    gEAction action,
    gEPhase phase,
    GEFloat compatibleSpeed);
}
