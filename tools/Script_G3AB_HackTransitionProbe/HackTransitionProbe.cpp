#include "HackTransitionProbe.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/animation/ge_wrapper_emfx2actor.h>
#ifdef G3AB_HACK_RECOVER_CAUSAL_PROBE
#include <g3sdk/Engine/animation/ge_animationadmin.h>
#endif
#include <windows.h>

#include <atomic>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <mutex>

namespace G3AB::HackTransitionProbe
{
namespace
{
std::FILE *g_log = nullptr;
std::mutex g_logMutex;
std::atomic<DWORD> g_captureUntil{0};
std::atomic<DWORD> g_lastTick{0};
#ifdef G3AB_HACK_RECOVER_CAUSAL_PROBE
// The engine owner for the regular Hack Raise/Hit resource queries, retained
// only on the same thread until the immediately following Recover.
thread_local eCAnimationAdmin *g_hackAnimationAdmin = nullptr;
thread_local eEResourceCacheBehavior g_hackCacheBehavior =
    eEResourceCacheBehavior_Immediate;
thread_local ScopedRecoverCausalProbe *g_activeRecoverScope = nullptr;
#endif

void Log(char const *format, ...)
{
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (g_log == nullptr)
        return;
    std::va_list args;
    va_start(args, format);
    std::vfprintf(g_log, format, args);
    va_end(args);
    std::fputc('\n', g_log);
    std::fflush(g_log);
}

void Arm()
{
    g_captureUntil.store(::GetTickCount() + 3000);
}

void Snapshot(char const *event, eCVisualAnimation_PS *animation,
              GEInt requestedSlot, GEFloat blendTime)
{
    DWORD const tick = ::GetTickCount();
    if (animation == nullptr || !animation->HasActor())
    {
        Log("%lu %s requestedSlot=%d blend=%.4f actor=missing",
            static_cast<unsigned long>(tick), event,
            static_cast<int>(requestedSlot), static_cast<double>(blendTime));
        return;
    }
    eCWrapper_emfx2Actor *const actor = animation->GetActor();
    if (actor == nullptr)
        return;

    bool found = false;
    // Alfinos identifies five motion slots: Primary, Secondary, Third,
    // Fourth and Overlay. Never probe beyond these known slots.
    for (GEInt slot = 0; slot != 5; ++slot)
    {
        auto const type =
            static_cast<eCWrapper_emfx2Actor::eEMotionType>(slot);
        if (!actor->HasMotionInstance(type))
            continue;
        found = true;
        char const *const name =
            animation->GetMotionDesc(type).GetMotionFilename().GetText();
        Log("%lu %s reqSlot=%d blend=%.4f slot=%d "
            "name=%s running=%d time=%.4f max=%.4f speed=%.4f "
            "weight=%.4f blendMode=%d intro=%.4f extro=%.4f",
            static_cast<unsigned long>(tick), event,
            static_cast<int>(requestedSlot), static_cast<double>(blendTime),
            static_cast<int>(slot), name != nullptr ? name : "<null>",
            static_cast<int>(actor->IsMotionRunning(type)),
            static_cast<double>(actor->GetPlayTime(type)),
            static_cast<double>(actor->GetMaxTime(type)),
            static_cast<double>(actor->GetPlaySpeed(type)),
            static_cast<double>(actor->GetTargetWeight(type)),
            static_cast<int>(actor->GetBlendMode(type)),
            static_cast<double>(actor->GetIntroBlending(type)),
            static_cast<double>(actor->GetExtroBlending(type)));
    }
    if (!found)
        Log("%lu %s requestedSlot=%d blend=%.4f no-active-motions",
            static_cast<unsigned long>(tick), event,
            static_cast<int>(requestedSlot), static_cast<double>(blendTime));
}

eCVisualAnimation_PS *PlayerAnimation()
{
    Entity player = Entity::GetPlayer();
    if (player == None || !player.Animation.IsValid())
        return nullptr;
    return static_cast<eCVisualAnimation_PS *>(
        player.Animation.m_pEngineEntityPropertySet);
}
} // namespace

#ifdef G3AB_HACK_RECOVER_CAUSAL_PROBE
void RememberHackAnimationAdmin(eCAnimationAdmin *admin, GEInt cacheBehavior,
                                bool factualHackPlayer)
{
    if (!factualHackPlayer || admin == nullptr)
        return;
    g_hackAnimationAdmin = admin;
    g_hackCacheBehavior =
        static_cast<eEResourceCacheBehavior>(cacheBehavior);
}

ScopedRecoverCausalProbe::ScopedRecoverCausalProbe(
    eCEntity *actor, bool factualHack)
    : m_actor(actor), m_factualHack(factualHack && actor != nullptr),
      m_firstPrimarySeen(false), m_previous(g_activeRecoverScope)
{
    g_activeRecoverScope = this;
}

ScopedRecoverCausalProbe::~ScopedRecoverCausalProbe()
{
    g_activeRecoverScope = m_previous;
}

bool SuppressFirstNativeFinishingRecover(
    eCVisualAnimation_PS *animation, GEInt motionSlot)
{
    ScopedRecoverCausalProbe *const scope = g_activeRecoverScope;
    if (scope == nullptr || !scope->m_factualHack
        || scope->m_firstPrimarySeen || motionSlot != 0
        || animation == nullptr || animation->GetEntity() != scope->m_actor)
        return false;

    // Even a rejected first PlayMotion consumes this scope. A later unrelated
    // call must never become an accidental suppression candidate.
    scope->m_firstPrimarySeen = true;
    static char const expectedFirstMotion[] =
        "Hero_Parade_None_2H_P1_FinishingAttack_Recover_N_Fwd_00_%_00_P0_0.xmot";
    static char const expectedHackResource[] =
        "Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_.fxm";

    auto const primarySlot =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    char const *const descriptorName =
        animation->GetMotionDesc(primarySlot).GetMotionFilename().GetText();
    if (descriptorName == nullptr
        || std::strcmp(descriptorName, expectedFirstMotion) != 0)
    {
        Log("%lu CAUSAL_FALLBACK reason=first_motion_mismatch actual=%s",
            static_cast<unsigned long>(::GetTickCount()),
            descriptorName != nullptr ? descriptorName : "<null>");
        return false;
    }
    if (g_hackAnimationAdmin == nullptr)
    {
        Log("%lu CAUSAL_FALLBACK reason=no_animation_admin",
            static_cast<unsigned long>(::GetTickCount()));
        return false;
    }

    // Positive engine resource lookup is mandatory. If Hack Recover is not
    // available, let the first native Finishing Recover play normally.
    // The later production routing lookup remains unchanged.
    bCString const candidate(expectedHackResource);
    eCResourceDataEntity *const resource =
        g_hackAnimationAdmin->QueryMotionDataEntity(
            candidate, g_hackCacheBehavior);
    if (resource == nullptr)
    {
        Log("%lu CAUSAL_FALLBACK reason=hack_recover_unavailable",
            static_cast<unsigned long>(::GetTickCount()));
        return false;
    }

    Log("%lu CAUSAL_SUPPRESS_FIRST_NATIVE_FINISHING "
        "action=14 motion=%s candidate=%s resource=%p",
        static_cast<unsigned long>(::GetTickCount()),
        descriptorName, expectedHackResource,
        static_cast<void *>(resource));
    return true;
}
#endif

void Initialize()
{
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (g_log != nullptr)
        return;
    if (fopen_s(&g_log, "G3AB_HackTransitionProbe.log", "w") != 0)
        return;
#ifdef G3AB_HACK_RECOVER_REAL_ASSET_PROBE
    std::fprintf(g_log,
        "G3AB HACK RECOVER REAL ASSET PROBE - custom Hack Hit, native Hack "
        "resource lookup, first wrong Finishing suppression, build 1\n");
#elif defined(G3AB_HACK_MISSING_RECOVER_PROBE)
    std::fprintf(g_log,
        "G3AB HACK MISSING RECOVER CAUSAL PROBE - owned custom Hack Hit, "
        "suppress first Finishing and force null Recover resource, build 1\n");
#elif defined(G3AB_HACK_RECOVER_CAUSAL_PROBE)
    std::fprintf(g_log,
        "G3AB HACK RECOVER CAUSAL PROBE - 2H fixture first native "
        "Finishing Recover suppression, build 1\n");
#else
    std::fprintf(g_log,
        "G3AB HACK TRANSITION DIAGNOSTIC — full production source plus "
        "observation-only hooks, build 1\n");
#endif
    std::fflush(g_log);
}

void LogResearchEvent(char const *event, char const *detail)
{
    Log("%lu %s detail=%s", static_cast<unsigned long>(::GetTickCount()),
        event != nullptr ? event : "<null>",
        detail != nullptr ? detail : "<null>");
}

bool IsTracking()
{
    DWORD const limit = g_captureUntil.load();
    return limit != 0
        && static_cast<std::int32_t>(limit - ::GetTickCount()) > 0;
}

void ObserveResourceQuery(GEInt factualAction, char const *requestedName,
                          bool hackResourceSelected,
                          eCResourceDataEntity const *resource, bool isPlayer)
{
    // Hack=14, true Finishing=15. Ignore all other actors and actions.
    if (!isPlayer || (factualAction != 14 && factualAction != 15))
        return;
    Arm();
    Log("%lu RESOURCE action=%d requested=%s selected=%s resource=%p",
        static_cast<unsigned long>(::GetTickCount()),
        static_cast<int>(factualAction),
        requestedName != nullptr ? requestedName : "<null>",
        hackResourceSelected ? "HACK" : "NATIVE",
        static_cast<void const *>(resource));
    Snapshot("QUERY_STATE", PlayerAnimation(), -1, -1.0f);
}

void ObserveMotion(char const *event, eCVisualAnimation_PS *animation,
                   GEInt requestedSlot, GEFloat blendTime)
{
    if (!IsTracking())
        return;
    Snapshot(event, animation, requestedSlot, blendTime);
}

void ObserveRecoverBoundary(char const *event, eCEntity *actor)
{
    if (!IsTracking() || actor == nullptr)
        return;
    Arm();
    Log("%lu RECOVER_BOUNDARY %s", static_cast<unsigned long>(::GetTickCount()), event);
    Snapshot(event, PlayerAnimation(), -1, -1.0f);
}

void ObserveTick()
{
    if (!IsTracking())
        return;
    DWORD const now = ::GetTickCount();
    if (g_lastTick.exchange(now) == now)
        return;
    Snapshot("TICK", PlayerAnimation(), -1, -1.0f);
}
} // namespace G3AB::HackTransitionProbe
