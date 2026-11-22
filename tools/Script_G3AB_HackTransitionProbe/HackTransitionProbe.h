#pragma once
#include <g3sdk/Script.h>

class eCEntity;
class eCVisualAnimation_PS;
class eCResourceDataEntity;
class eCAnimationAdmin;

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

#ifdef G3AB_HACK_RECOVER_CAUSAL_PROBE
void RememberHackAnimationAdmin(eCAnimationAdmin *admin, GEInt cacheBehavior,
                                bool factualHackPlayer);
// Scoped strictly to the native StartRecover call on the current thread.
// Only used by a research DLL, not by production or the observation-only twin.
class ScopedRecoverCausalProbe
{
  public:
    ScopedRecoverCausalProbe(eCEntity *actor, bool factualHack);
    ~ScopedRecoverCausalProbe();
    ScopedRecoverCausalProbe(ScopedRecoverCausalProbe const &) = delete;
    ScopedRecoverCausalProbe &operator=(ScopedRecoverCausalProbe const &) = delete;
    friend bool SuppressFirstNativeFinishingRecover(
        eCVisualAnimation_PS *animation, GEInt motionSlot);

  private:
    eCEntity *m_actor;
    bool m_factualHack;
    bool m_firstPrimarySeen;
    ScopedRecoverCausalProbe *m_previous;
};

bool SuppressFirstNativeFinishingRecover(
    eCVisualAnimation_PS *animation, GEInt motionSlot);
#endif
}
