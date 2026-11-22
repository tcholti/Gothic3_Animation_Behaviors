#pragma once
#include <g3sdk/Script.h>

class eCEntity;
class eCVisualAnimation_PS;
class eCResourceDataEntity;

namespace G3AB::HackTransitionProbe
{
void Initialize();
void ObserveResourceQuery(GEInt factualAction, char const *requestedName,
                          bool hackResourceSelected,
                          eCResourceDataEntity const *resource, bool isPlayer);
void ObserveMotion(char const *event, eCVisualAnimation_PS *animation,
                   GEInt requestedSlot, GEFloat blendTime = -1.0f);
void ObserveRecoverBoundary(char const *event, eCEntity *actor);
void ObserveTick();
bool IsTracking();
}
