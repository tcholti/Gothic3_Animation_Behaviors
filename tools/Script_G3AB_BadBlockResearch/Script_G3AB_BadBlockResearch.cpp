#include <g3sdk/Script.h>

#include <cstdio>

#include <windows.h>

namespace
{
FILE *g_pLog = nullptr;

void OpenLog()
{
    g_pLog = std::fopen("G3AB_BadBlockResearch.log", "w");
    if (g_pLog == nullptr)
        return;

    std::fprintf(
        g_pLog,
        "Script_G3AB_BadBlockResearch loaded.\n"
        "Research target only: no bad-block hooks installed yet.\n"
        "Production Script_G3AnimationBehaviors.dll is intentionally independent.\n");
    std::fflush(g_pLog);
}

void CloseLog()
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "Script_G3AB_BadBlockResearch unloading.\n");
    std::fflush(g_pLog);
    std::fclose(g_pLog);
    g_pLog = nullptr;
}
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    OpenLog();
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
            CloseLog();
            break;
    }
    return TRUE;
}
