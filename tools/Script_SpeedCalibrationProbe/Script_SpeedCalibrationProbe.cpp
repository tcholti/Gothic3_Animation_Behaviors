#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>

#include <windows.h>

#include <cmath>
#include <cstdio>
#include <map>
#include <string>
#include <tuple>

namespace
{
static mCCallHook Hook_SpeedModifierCall_383F0;
static mCCallHook Hook_SpeedModifierCall_38E9D;
static mCCallHook Hook_SpeedModifierCall_38F22;
static mCCallHook Hook_SpeedModifierCall_3937D;
static mCCallHook Hook_SpeedModifierCall_39402;
static mCCallHook Hook_SpeedModifierCall_48677;
static mCCallHook Hook_SpeedModifierCall_41551;
static mCCallHook Hook_SpeedModifierCall_41680;
static mCCallHook Hook_SpeedModifierCall_417F0;
static mCCallHook Hook_SpeedModifierCall_42FF4;
static mCCallHook Hook_SpeedModifierCall_431B4;
static mCCallHook Hook_SpeedModifierCall_432EB;
static mCCallHook Hook_SpeedModifierCall_47328;
static mCCallHook Hook_SpeedModifierCall_4770F;
static mCCallHook Hook_SpeedModifierCall_4786F;
static mCCallHook Hook_SpeedModifierCall_47D51;
static mCCallHook Hook_SpeedModifierCall_47F6C;
static mCCallHook Hook_SpeedModifierCall_4C6FA;
static mCCallHook Hook_SpeedModifierCall_4DF1F;
static mCCaller Call_GetAnimationSpeedModifier;

static FILE *g_pLogFile = nullptr;
static GEU32 g_TotalInterceptedCalls = 0;
static GEU32 g_DroppedUniqueObservations = 0;
static bool g_ProductionConflictWarningWritten = false;
static GEU32 const UniqueObservationCap = 2048;

using mFGetAnimationSpeedModifier = GEFloat (GE_STDCALL *)(Entity, gEPhase);

struct ObservationKey
{
    std::string animationFamily;
    GEInt rawLeftUseType;
    GEInt rawRightUseType;
    GEInt passedAction;
    GEInt currentActionBefore;
    GEInt currentActionAfter;
    GEInt phase;
    long long speedMicros;
    bool newBalanceLoaded;
    bool productionG3ABLoaded;
};

struct ObservationKeyLess
{
    bool operator()(ObservationKey const &left, ObservationKey const &right) const
    {
        return std::tie(
                   left.animationFamily,
                   left.rawLeftUseType,
                   left.rawRightUseType,
                   left.passedAction,
                   left.currentActionBefore,
                   left.currentActionAfter,
                   left.phase,
                   left.speedMicros,
                   left.newBalanceLoaded,
                   left.productionG3ABLoaded)
            < std::tie(
                   right.animationFamily,
                   right.rawLeftUseType,
                   right.rawRightUseType,
                   right.passedAction,
                   right.currentActionBefore,
                   right.currentActionAfter,
                   right.phase,
                   right.speedMicros,
                   right.newBalanceLoaded,
                   right.productionG3ABLoaded);
    }
};

struct ObservationValue
{
    GEU32 count;
    GEU32 playerSamples;
    GEU32 npcSamples;
    std::string sampleEntity;
    std::string sampleMovementAni;
};

using ObservationMap =
    std::map<ObservationKey, ObservationValue, ObservationKeyLess>;

static ObservationMap g_Observations;

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

char const *GetPhaseName(gEPhase phase)
{
    switch (phase)
    {
        case gEPhase_Raise:   return "Raise";
        case gEPhase_Hit:     return "Hit";
        case gEPhase_Aim:     return "Aim";
        case gEPhase_Recover: return "Recover";
        case gEPhase_Begin:   return "Begin";
        case gEPhase_Loop:    return "Loop";
        case gEPhase_End:     return "End";
        default:              return "Other";
    }
}

char const *GetActionName(gEAction action)
{
    switch (action)
    {
        case gEAction_Attack:       return "Normal";
        case gEAction_PowerAttack:  return "Power";
        case gEAction_QuickAttack:  return "QuickSelector";
        case gEAction_QuickAttackR: return "QuickR";
        case gEAction_QuickAttackL: return "QuickL";
        case gEAction_SimpleWhirl:  return "SimpleWhirl";
        case gEAction_SprintAttack: return "Sprint";
        case gEAction_WhirlAttack:  return "Whirl";
        case gEAction_PierceAttack: return "Pierce";
        case gEAction_HackAttack:   return "Hack";
        case gEAction_FinishingAttack: return "FinishingAttack";
        case gEAction_None:         return "None";
        default:                    return "Other";
    }
}

char const *GetRawUseTypeName(gEUseType useType)
{
    switch (useType)
    {
        case gEUseType_None:         return "None";
        case gEUseType_1H:           return "1H";
        case gEUseType_2H:           return "2H";
        case gEUseType_Fist:         return "Fist";
        case gEUseType_Shield:       return "Shield";
        case gEUseType_Staff:        return "Staff";
        case gEUseType_Torch:        return "Torch";
        case gEUseType_Broom:        return "Broom";
        case gEUseType_Rake:         return "Rake";
        case gEUseType_Shovel:       return "Shovel";
        case gEUseType_Fan:          return "Fan";
        case gEUseType_Pickaxe:      return "Pickaxe";
        case gEUseType_Axe:          return "Axe";
        case gEUseType_Halberd:      return "Halberd";
        case gEUseType_PhysicalFist: return "PhysicalFist";
        default:                     return "Unknown";
    }
}

char const *GetNormalizedUseTypeToken(gEUseType useType)
{
    switch (useType)
    {
        case gEUseType_None:         return "none";
        case gEUseType_1H:           return "1h";
        case gEUseType_2H:           return "2h";
        case gEUseType_Fist:         return "fist";
        case gEUseType_Shield:       return "shield";
        case gEUseType_Staff:        return "staff";
        case gEUseType_Torch:        return "torch";
        case gEUseType_Broom:        return "staff";
        case gEUseType_Rake:         return "staff";
        case gEUseType_Shovel:       return "staff";
        case gEUseType_Fan:          return "staff";
        case gEUseType_Pickaxe:      return "2h";
        case gEUseType_Axe:          return "2h";
        case gEUseType_Halberd:      return "staff";
        case gEUseType_PhysicalFist: return "fist";
        default:                     return "unsupported";
    }
}

gEUseType GetHandUseType(Entity const &entity, gESlot slot)
{
    if (entity == None)
        return gEUseType_None;

    Entity item = entity.Inventory.GetItemFromSlot(slot);
    return item == None ? gEUseType_None : item.Interaction.GetUseType();
}

std::string GetAnimationFamily(Entity const &entity)
{
    if (entity == None)
        return "<none>";

    bCString skeletonName;
    if (!entity.Animation.GetSkeletonName(skeletonName))
        return "<unknown>";

    char const *text = skeletonName.GetText();
    return text != nullptr && *text != '\0' ? text : "<unknown>";
}

long long QuantizeSpeed(GEFloat speed)
{
    return static_cast<long long>(std::llround(
        static_cast<double>(speed) * 1000000.0));
}

void WriteObservationLine(
    char const *prefix,
    ObservationKey const &key,
    ObservationValue const &value)
{
    if (g_pLogFile == nullptr)
        return;

    gEUseType const rawLeft = static_cast<gEUseType>(key.rawLeftUseType);
    gEUseType const rawRight = static_cast<gEUseType>(key.rawRightUseType);
    double const speed = static_cast<double>(key.speedMicros) / 1000000.0;

    std::fprintf(
        g_pLogFile,
        "%s|Family=%s|LeftRaw=%s(%d)|LeftToken=%s|RightRaw=%s(%d)|RightToken=%s|"
        "PassedAction=%s(%d)|CurrentBefore=%s(%d)|CurrentAfter=%s(%d)|"
        "Phase=%s(%d)|Speed=%.6f|NewBalance=%s|G3AB=%s|Count=%u|Player=%u|NPC=%u|"
        "SampleEntity=%s|SampleAni=%s\n",
        prefix,
        key.animationFamily.c_str(),
        GetRawUseTypeName(rawLeft), key.rawLeftUseType,
        GetNormalizedUseTypeToken(rawLeft),
        GetRawUseTypeName(rawRight), key.rawRightUseType,
        GetNormalizedUseTypeToken(rawRight),
        GetActionName(static_cast<gEAction>(key.passedAction)), key.passedAction,
        GetActionName(static_cast<gEAction>(key.currentActionBefore)), key.currentActionBefore,
        GetActionName(static_cast<gEAction>(key.currentActionAfter)), key.currentActionAfter,
        GetPhaseName(static_cast<gEPhase>(key.phase)), key.phase,
        speed,
        key.newBalanceLoaded ? "true" : "false",
        key.productionG3ABLoaded ? "true" : "false",
        static_cast<unsigned>(value.count),
        static_cast<unsigned>(value.playerSamples),
        static_cast<unsigned>(value.npcSamples),
        value.sampleEntity.c_str(),
        value.sampleMovementAni.c_str());
}

void RecordObservation(
    gEAction passedAction,
    Entity const &entity,
    gEPhase phase,
    gEAction currentActionBefore,
    gEAction currentActionAfter,
    GEFloat compatibleSpeed)
{
    if (g_pLogFile == nullptr || entity == None)
        return;

    if (!std::isfinite(compatibleSpeed))
    {
        std::fprintf(
            g_pLogFile,
            "ANOMALY|NonFiniteSpeed|Entity=%s|PassedAction=%d|Phase=%d\n",
            entity.GetName().GetText(),
            static_cast<GEInt>(passedAction),
            static_cast<GEInt>(phase));
        std::fflush(g_pLogFile);
        return;
    }

    bool const newBalanceLoaded =
        ::GetModuleHandleA("Script_NewBalance.dll") != nullptr;
    bool const productionG3ABLoaded =
        ::GetModuleHandleA("Script_G3AnimationBehaviors.dll") != nullptr;

    if (productionG3ABLoaded && !g_ProductionConflictWarningWritten)
    {
        g_ProductionConflictWarningWritten = true;
        std::fprintf(
            g_pLogFile,
            "WARNING|Script_G3AnimationBehaviors.dll is loaded while the calibration probe is active. "
            "Both may target the same caller sites; this run is not valid calibration evidence.\n");
        std::fflush(g_pLogFile);
    }

    gEUseType const rawLeft = GetHandUseType(entity, gESlot_LeftHand);
    gEUseType const rawRight = GetHandUseType(entity, gESlot_RightHand);

    ObservationKey key = {
        GetAnimationFamily(entity),
        static_cast<GEInt>(rawLeft),
        static_cast<GEInt>(rawRight),
        static_cast<GEInt>(passedAction),
        static_cast<GEInt>(currentActionBefore),
        static_cast<GEInt>(currentActionAfter),
        static_cast<GEInt>(phase),
        QuantizeSpeed(compatibleSpeed),
        newBalanceLoaded,
        productionG3ABLoaded};

    ObservationMap::iterator found = g_Observations.find(key);
    bool const isPlayer = entity == Entity::GetPlayer();

    if (found != g_Observations.end())
    {
        ++found->second.count;
        if (isPlayer)
            ++found->second.playerSamples;
        else
            ++found->second.npcSamples;
        return;
    }

    if (g_Observations.size() >= UniqueObservationCap)
    {
        ++g_DroppedUniqueObservations;
        return;
    }

    bCString const movementAni = entity.NPC.GetCurrentMovementAni();
    bCString const entityName = entity.GetName();

    ObservationValue value = {
        1,
        isPlayer ? 1u : 0u,
        isPlayer ? 0u : 1u,
        entityName.GetText() != nullptr ? entityName.GetText() : "<unknown>",
        movementAni.GetText() != nullptr ? movementAni.GetText() : "<unknown>"};

    auto const inserted = g_Observations.emplace(key, value);
    if (inserted.second)
    {
        WriteObservationLine("NEW", inserted.first->first, inserted.first->second);
        std::fflush(g_pLogFile);
    }
}

GEFloat GE_STDCALL SpeedCalibrationProbe(
    gEAction passedAction,
    Entity entity,
    gEPhase phase)
{
    ++g_TotalInterceptedCalls;

    gEAction currentActionBefore = gEAction_None;
    if (entity != None)
    {
        currentActionBefore =
            entity.Routine.GetProperty<PSRoutine::PropertyAction>();
    }

    Call_GetAnimationSpeedModifier.SetImmEax(passedAction);
    GEFloat const compatibleSpeed =
        Call_GetAnimationSpeedModifier
            .GetFunction<mFGetAnimationSpeedModifier>()(
                entity, phase);

    gEAction currentActionAfter = gEAction_None;
    if (entity != None)
    {
        currentActionAfter =
            entity.Routine.GetProperty<PSRoutine::PropertyAction>();
    }

    RecordObservation(
        passedAction,
        entity,
        phase,
        currentActionBefore,
        currentActionAfter,
        compatibleSpeed);

    return compatibleSpeed;
}

void InstallSpeedCallHook(mCCallHook &hook, GEU32 rva)
{
    hook.Prepare(RVA_ScriptGame(rva), &SpeedCalibrationProbe)
        .AddRegArg(mERegisterType_Eax)
        .Hook();
}

void WriteFinalSummary()
{
    if (g_pLogFile == nullptr)
        return;

    std::fprintf(g_pLogFile, "\n===== FINAL SUMMARY =====\n");
    std::fprintf(
        g_pLogFile,
        "InterceptedCalls=%u\nUniqueObservations=%u\nDroppedUniqueObservations=%u\n",
        static_cast<unsigned>(g_TotalInterceptedCalls),
        static_cast<unsigned>(g_Observations.size()),
        static_cast<unsigned>(g_DroppedUniqueObservations));

    for (ObservationMap::const_iterator it = g_Observations.begin();
         it != g_Observations.end();
         ++it)
    {
        WriteObservationLine("ROW", it->first, it->second);
    }

    std::fprintf(g_pLogFile, "===== END SUMMARY =====\n");
    std::fflush(g_pLogFile);
}
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    g_pLogFile = std::fopen("SpeedCalibrationProbe.log", "w");
    if (g_pLogFile != nullptr)
    {
        std::fprintf(
            g_pLogFile,
            "Script_SpeedCalibrationProbe loaded. Diagnostics only; returned speeds are unchanged.\n");
        std::fprintf(
            g_pLogFile,
            "Unique observations are deduplicated and capped at %u. NEW rows are flushed immediately; ROW rows form the final summary.\n",
            static_cast<unsigned>(UniqueObservationCap));
        std::fprintf(
            g_pLogFile,
            "IMPORTANT: Script_G3AnimationBehaviors.dll must be absent during calibration because it may hook the same caller sites.\n\n");
        std::fflush(g_pLogFile);
    }

    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    Call_GetAnimationSpeedModifier.Init(
        mCCaller::GetCallerParams(
            RVA_ScriptGame(0x42A0), mERegisterType_Eax));

    InstallSpeedCallHook(Hook_SpeedModifierCall_383F0, 0x383F0);
    InstallSpeedCallHook(Hook_SpeedModifierCall_38E9D, 0x38E9D);
    InstallSpeedCallHook(Hook_SpeedModifierCall_38F22, 0x38F22);
    InstallSpeedCallHook(Hook_SpeedModifierCall_3937D, 0x3937D);
    InstallSpeedCallHook(Hook_SpeedModifierCall_39402, 0x39402);
    InstallSpeedCallHook(Hook_SpeedModifierCall_48677, 0x48677);
    InstallSpeedCallHook(Hook_SpeedModifierCall_41551, 0x41551);
    InstallSpeedCallHook(Hook_SpeedModifierCall_41680, 0x41680);
    InstallSpeedCallHook(Hook_SpeedModifierCall_417F0, 0x417F0);
    InstallSpeedCallHook(Hook_SpeedModifierCall_42FF4, 0x42FF4);
    InstallSpeedCallHook(Hook_SpeedModifierCall_431B4, 0x431B4);
    InstallSpeedCallHook(Hook_SpeedModifierCall_432EB, 0x432EB);
    InstallSpeedCallHook(Hook_SpeedModifierCall_47328, 0x47328);
    InstallSpeedCallHook(Hook_SpeedModifierCall_4770F, 0x4770F);
    InstallSpeedCallHook(Hook_SpeedModifierCall_4786F, 0x4786F);
    InstallSpeedCallHook(Hook_SpeedModifierCall_47D51, 0x47D51);
    InstallSpeedCallHook(Hook_SpeedModifierCall_47F6C, 0x47F6C);
    InstallSpeedCallHook(Hook_SpeedModifierCall_4C6FA, 0x4C6FA);
    InstallSpeedCallHook(Hook_SpeedModifierCall_4DF1F, 0x4DF1F);

    if (g_pLogFile != nullptr)
    {
        std::fprintf(
            g_pLogFile,
            "Installed 18 proven Hit caller hooks (including 3 Finishing/Action15 sites) plus the proven Power Raise observation hook.\n\n");
        std::fflush(g_pLogFile);
    }

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
            if (g_pLogFile != nullptr)
            {
                WriteFinalSummary();
                std::fclose(g_pLogFile);
                g_pLogFile = nullptr;
            }
            break;
    }

    return TRUE;
}
