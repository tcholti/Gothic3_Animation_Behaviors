#include <g3sdk/Script.h>
#include <g3sdk/Game/ge_effectsystem.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>

#include <windows.h>

#include <cstring>
#include <fstream>
#include <string>

static mCFunctionHook Hook_StartEffect;
static std::ofstream g_Log;

static LARGE_INTEGER g_StartCounter = {};
static LARGE_INTEGER g_Frequency = {};

static std::string GetGameDirectory()
{
    char path[MAX_PATH] = {};
    ::GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string result(path);
    std::string::size_type separator = result.find_last_of("\\/");

    if (separator != std::string::npos)
        result.resize(separator);

    return result;
}

static double GetElapsedMilliseconds()
{
    LARGE_INTEGER now = {};
    ::QueryPerformanceCounter(&now);

    if (g_Frequency.QuadPart == 0)
        return 0.0;

    return
        (static_cast<double>(now.QuadPart - g_StartCounter.QuadPart) * 1000.0)
        / static_cast<double>(g_Frequency.QuadPart);
}

static void OpenLog()
{
    ::QueryPerformanceFrequency(&g_Frequency);
    ::QueryPerformanceCounter(&g_StartCounter);

    std::string logPath =
        GetGameDirectory() + "\\Script_FrameEffectLogger.log";

    g_Log.open(logPath.c_str(), std::ios::out | std::ios::trunc);

    if (g_Log.is_open())
    {
        g_Log << "Script_FrameEffectLogger v0.2 loaded.\n";
        g_Log << "Hook target: Game.dll + 0x60850 "
                 "(gCEffectSystem::StartEffect)\n";
        g_Log << "Custom marker: G3AB_COL_TEST\n";
        g_Log << "Custom marker is CONSUMED and is NOT passed to Gothic 3.\n";
        g_Log << "Whoosh effects are logged and passed through unchanged.\n\n";
        g_Log.flush();
    }
}

static void LogEffect(
    char const *a_pKind,
    char const *a_pEffectName,
    eCEntity *a_pEntity1,
    eCEntity *a_pEntity2,
    bCMatrix const *a_pMatrix,
    GEBool a_bUnknown)
{
    if (!g_Log.is_open())
        return;

    g_Log << "===== " << a_pKind << " =====\n";
    g_Log << "ElapsedMs: " << GetElapsedMilliseconds() << "\n";
    g_Log << "Effect: " << a_pEffectName << "\n";
    g_Log << "Entity1: " << a_pEntity1 << "\n";
    g_Log << "Entity2: " << a_pEntity2 << "\n";
    g_Log << "Matrix: " << a_pMatrix << "\n";
    g_Log << "BoolArg: " << (a_bUnknown ? 1 : 0) << "\n";
    g_Log << "============================\n\n";
    g_Log.flush();
}

static GELPVoid StartEffect_FrameEffectLogger(
    bCString const &a_EffectName,
    eCEntity *a_pEntity1,
    eCEntity *a_pEntity2,
    bCMatrix const *a_pMatrix,
    GEBool a_bUnknown)
{
    GELPCChar effectName = a_EffectName.GetText();

    if (effectName != NULL)
    {
        if (std::strcmp(effectName, "G3AB_COL_TEST") == 0)
        {
            LogEffect(
                "CUSTOM FRAME MARKER",
                effectName,
                a_pEntity1,
                a_pEntity2,
                a_pMatrix,
                a_bUnknown);

            // Deliberately consume the diagnostic marker.
            // Gothic 3 never tries to resolve it as a real visual/audio effect.
            return NULL;
        }

        if (std::strstr(effectName, "Whoosh") != NULL)
        {
            LogEffect(
                "WHOOSH FRAME EFFECT",
                effectName,
                a_pEntity1,
                a_pEntity2,
                a_pMatrix,
                a_bUnknown);
        }
    }

    return Hook_StartEffect
        .GetOriginalFunction(&StartEffect_FrameEffectLogger)(
            a_EffectName,
            a_pEntity1,
            a_pEntity2,
            a_pMatrix,
            a_bUnknown);
}

static void InstallStartEffectHook()
{
    Hook_StartEffect
        .Prepare(
            RVA_Game(0x60850),
            &StartEffect_FrameEffectLogger,
            mCBaseHook::mEHookType_ThisCall)
        .Hook();
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport)
gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    OpenLog();

    if (g_Log.is_open())
    {
        g_Log << "Installing StartEffect hook...\n";
        g_Log.flush();
    }

    InstallStartEffectHook();

    if (g_Log.is_open())
    {
        g_Log << "StartEffect hook installed.\n\n";
        g_Log.flush();
    }

    return &GetScriptInit();
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD dwReason,
    LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hModule);
            break;

        case DLL_PROCESS_DETACH:
            if (g_Log.is_open())
            {
                g_Log << "Script_FrameEffectLogger unloading.\n";
                g_Log.flush();
                g_Log.close();
            }
            break;
    }

    return TRUE;
}
