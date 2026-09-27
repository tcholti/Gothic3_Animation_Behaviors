#include "BehaviorProfiles.h"
#include "EngineBridge.h"
#include "RuntimeClock.h"

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
    G3AB::BehaviorProfiles::Load();
    EngineBridge::InstallHooks();
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
            break;
    }
    return TRUE;
}
