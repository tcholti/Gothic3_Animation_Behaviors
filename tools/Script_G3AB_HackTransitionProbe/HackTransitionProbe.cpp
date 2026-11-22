#include "HackTransitionProbe.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/animation/ge_wrapper_emfx2actor.h>
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

void Initialize()
{
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (g_log != nullptr)
        return;
    if (fopen_s(&g_log, "G3AB_HackTransitionProbe.log", "w") != 0)
        return;
    std::fprintf(g_log,
        "G3AB HACK TRANSITION DIAGNOSTIC — full production source plus "
        "observation-only hooks, build 1\n");
    std::fflush(g_log);
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
