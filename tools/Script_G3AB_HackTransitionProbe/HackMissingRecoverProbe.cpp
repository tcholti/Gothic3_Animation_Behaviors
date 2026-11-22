#include "HackMissingRecoverProbe.h"
#include "HackTransitionProbe.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/animation/ge_wrapper_emfx2actor.h>

#include <cstring>

namespace G3AB::HackMissingRecoverProbe
{
namespace
{
static char const kHit[] =
    "Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P1_100.xmot";
static char const kFirstRecover[] =
    "Hero_Parade_None_2H_P1_FinishingAttack_Recover_N_Fwd_00_%_00_P0_0.xmot";
static char const kNativeRecoverResource[] =
    "Hero_Parade_None_2H_P1_FinishingAttack_Recover_N_Fwd_00_.fxm";

struct PendingRecover
{
    gCScriptProcessingUnit *spu = nullptr;
    eCEntity *actor = nullptr;
    bool firstSuppressed = false;
};

// Deliberately only one pending player fixture on the current thread.
// A new Recover entry resets it; one exact Recover request consumes it.
thread_local PendingRecover g_pending;
thread_local RecoverScope *g_recoverScope = nullptr;

eCVisualAnimation_PS *PlayerAnimation(eCEntity *actor)
{
    Entity player = Entity::GetPlayer();
    if (player == None || player.GetInstance() != actor
        || !player.Animation.IsValid())
        return nullptr;
    return static_cast<eCVisualAnimation_PS *>(
        player.Animation.m_pEngineEntityPropertySet);
}
} // namespace

RecoverScope::RecoverScope(gCScriptProcessingUnit *spu, eCEntity *actor,
                           bool factualHackPlayer)
    : m_previous(g_recoverScope), m_actor(actor), m_armed(false),
      m_firstPrimarySeen(false), m_suppressed(false)
{
    g_recoverScope = this;
    // A prior Recover that never reached resource lookup cannot authorize
    // a later unrelated attack.
    g_pending = {};
    if (!factualHackPlayer || spu == nullptr || actor == nullptr)
        return;
    eCVisualAnimation_PS *const animation = PlayerAnimation(actor);
    if (animation == nullptr || !animation->HasActor())
        return;
    auto const primary =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    if (!animation->GetActor()->HasMotionInstance(primary))
        return;
    char const *const currentHit =
        animation->GetMotionDesc(primary).GetMotionFilename().GetText();
    if (currentHit == nullptr || std::strcmp(currentHit, kHit) != 0)
    {
        HackTransitionProbe::LogResearchEvent(
            "MISSING_PROBE_NOT_OWNED", currentHit != nullptr ? currentHit : "<null>");
        return;
    }
    m_armed = true;
    g_pending.spu = spu;
    g_pending.actor = actor;
    HackTransitionProbe::LogResearchEvent("MISSING_PROBE_OWNED_HACK_HIT", currentHit);
}

RecoverScope::~RecoverScope()
{
    if (!m_suppressed)
        g_pending = {};
    g_recoverScope = m_previous;
}

bool SuppressFirstFinishing(eCVisualAnimation_PS *animation, GEInt motionSlot)
{
    RecoverScope *const scope = g_recoverScope;
    if (scope == nullptr || !scope->m_armed || scope->m_firstPrimarySeen
        || motionSlot != 0 || animation == nullptr
        || animation->GetEntity() != scope->m_actor)
        return false;
    scope->m_firstPrimarySeen = true;
    auto const primary =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    char const *const incoming =
        animation->GetMotionDesc(primary).GetMotionFilename().GetText();
    if (incoming == nullptr || std::strcmp(incoming, kFirstRecover) != 0)
    {
        HackTransitionProbe::LogResearchEvent(
            "MISSING_PROBE_FIRST_MISMATCH", incoming != nullptr ? incoming : "<null>");
        return false;
    }
    scope->m_suppressed = true;
    g_pending.firstSuppressed = true;
    HackTransitionProbe::LogResearchEvent(
        "MISSING_PROBE_SUPPRESS_FIRST_FINISHING", incoming);
    return true;
}

bool ForceMissingRecover(gCScriptProcessingUnit *spu, eCEntity *actor,
                         gEAction factualAction, bCString const &resourceName)
{
    if (g_pending.spu == nullptr || !g_pending.firstSuppressed)
        return false;
    if (spu != g_pending.spu || actor != g_pending.actor
        || factualAction != gEAction_HackAttack)
        return false;
    char const *const name = resourceName.GetText();
    if (name == nullptr || std::strcmp(name, kNativeRecoverResource) != 0)
    {
        // A new Raise or Hit for the same actor invalidates any abandoned token.
        if (name != nullptr && (std::strstr(name, "_Raise_") != nullptr
                              || std::strstr(name, "_Hit_") != nullptr))
            g_pending = {};
        return false;
    }
    // Consume before the native continuation; a reentrant query must never
    // receive a second synthetic missing-resource answer.
    g_pending = {};
    HackTransitionProbe::LogResearchEvent(
        "MISSING_PROBE_FORCE_NULL_RECOVER_RESOURCE", name);
    return true;
}
} // namespace G3AB::HackMissingRecoverProbe
