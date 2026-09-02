#include "EngineBridge.h"
#include "RuntimeClock.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"

#include <cstdint>
#endif

#include <g3sdk/Script.h>

#include <windows.h>

using namespace FrameCollision;
#ifdef FRAME_COLLISION_DIAGNOSTICS
static void ProbeHackCallbackIdentity()
{
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    constexpr std::uintptr_t TargetRva = 0x433D0;
    HMODULE const scriptGameModule = ::GetModuleHandleA("Script_Game.dll");
    if (scriptGameModule == nullptr)
    {
        std::fprintf(log,
                     "HACK_CALLBACK_IDENTITY TargetRVA=0x433D0 ExactlyOne=0 "
                     "Status=FAIL Reason=SCRIPT_GAME_NOT_LOADED\n");
        std::fflush(log);
        return;
    }

    FARPROC const scriptInitAddress =
        ::GetProcAddress(scriptGameModule, "_ScriptInit@0");
    if (scriptInitAddress == nullptr)
    {
        std::fprintf(log,
                     "HACK_CALLBACK_IDENTITY TargetRVA=0x433D0 ExactlyOne=0 "
                     "Status=FAIL Reason=EXPORT_NOT_RESOLVED\n");
        std::fflush(log);
        return;
    }

    gFScriptInit const scriptInit =
        reinterpret_cast<gFScriptInit>(scriptInitAddress);
    gSScriptInit const *const registration = scriptInit();
    if (registration == nullptr)
    {
        std::fprintf(log,
                     "HACK_CALLBACK_IDENTITY TargetRVA=0x433D0 ExactlyOne=0 "
                     "Status=FAIL Reason=NULL_SCRIPT_INIT_RESULT\n");
        std::fflush(log);
        return;
    }

    gFScriptAICallback const targetCallback =
        reinterpret_cast<gFScriptAICallback>(
            reinterpret_cast<std::uintptr_t>(scriptGameModule) + TargetRva);
    GEInt matchCount = 0;
    gSScriptAICallback const *match = nullptr;
    auto const &callbacks = registration->m_arrScriptAICallbacks;
    for (GEInt index = 0; index < callbacks.GetCount(); ++index)
    {
        gSScriptAICallback const &callback = callbacks.GetAt(index);
        if (callback.m_funcScriptAICallback != targetCallback)
            continue;
        ++matchCount;
        match = &callback;
    }

    if (matchCount == 1)
    {
        std::fprintf(log,
                     "HACK_CALLBACK_IDENTITY TargetRVA=0x433D0 ExactlyOne=1 "
                     "MatchCount=1 Name=%s Source=%s\n",
                     match->m_strName.GetText(), match->m_strSource.GetText());
    }
    else
    {
        std::fprintf(log,
                     "HACK_CALLBACK_IDENTITY TargetRVA=0x433D0 ExactlyOne=0 "
                     "MatchCount=%d Status=FAIL Reason=%s\n",
                     matchCount,
                     matchCount == 0 ? "NO_MATCH" : "MULTIPLE_MATCHES");
    }
    std::fflush(log);
}
#endif

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    RuntimeClock::InitializeClock();
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::OpenLog();
    ProbeHackCallbackIdentity();
    if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(CollisionDiagnostics::GetLog(),
                     "Installing behavior hooks...\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }
#endif

    EngineBridge::InstallHooks();

#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(CollisionDiagnostics::GetLog(), "Hooks installed.\n\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }
#endif
    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hModule);
            break;
        case DLL_PROCESS_DETACH:
#ifdef FRAME_COLLISION_DIAGNOSTICS
            CollisionDiagnostics::CloseLog();
#endif
            break;
    }
    return TRUE;
}
