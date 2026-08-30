#include "CollisionDiagnostics.h"
#include "EngineBridge.h"
#include "HookBridgeRuntime.h"

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
    HookBridgeRuntime::InitializeClock();
    CollisionDiagnostics::OpenLog();
    if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(
            CollisionDiagnostics::GetLog(),
            "STEP C1-R1 PHYSICAL REPAIR: exact live/equipped outstanding Item_Attack source resets to Item_Equipped at destructive AISetState finalization; native cleanup/no-op paths unchanged; no ClearTriggeredList.\n");
        std::fprintf(CollisionDiagnostics::GetLog(), "Installing hooks...\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }
    EngineBridge::InstallHooks();
    if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(CollisionDiagnostics::GetLog(), "Hooks installed.\n\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }
    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: ::DisableThreadLibraryCalls(hModule); break;
        case DLL_PROCESS_DETACH: CollisionDiagnostics::CloseLog(); break;
    }
    return TRUE;
}
