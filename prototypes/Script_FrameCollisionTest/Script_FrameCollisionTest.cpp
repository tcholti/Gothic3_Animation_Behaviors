#include "EngineBridge.h"
#include "RuntimeClock.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"
#endif

#include <g3sdk/Script.h>

#include <windows.h>

using namespace FrameCollision;

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
