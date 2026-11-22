#pragma once
#include <g3sdk/Script.h>

class eCEntity;
class eCVisualAnimation_PS;

namespace G3AB::HackMissingRecoverProbe
{
// This experiment is player/2H-only, and never compiled into production.
// Recover ownership is observed from the actual outgoing Hack Hit.
class RecoverScope
{
  public:
    RecoverScope(gCScriptProcessingUnit *spu, eCEntity *actor, bool factualHackPlayer);
    ~RecoverScope();
    RecoverScope(RecoverScope const &) = delete;
    RecoverScope &operator=(RecoverScope const &) = delete;
    friend bool SuppressFirstFinishing(eCVisualAnimation_PS *, GEInt);

  private:
    RecoverScope *m_previous;
    eCEntity *m_actor;
    bool m_armed;
    bool m_firstPrimarySeen;
    bool m_suppressed;
};

bool SuppressFirstFinishing(eCVisualAnimation_PS *animation, GEInt motionSlot);
// Consume and match only the first exact Recover resource request of the
// same real custom-Hack-Hit execution. The caller decides how to resolve it.
bool ConsumeOwnedRecoverRequest(gCScriptProcessingUnit *spu, eCEntity *actor,
                                gEAction factualAction, bCString const &resourceName);
} // namespace G3AB::HackMissingRecoverProbe
