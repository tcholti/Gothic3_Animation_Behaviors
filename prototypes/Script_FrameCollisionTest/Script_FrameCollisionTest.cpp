#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/ge_resourceanimationmotion_ps.h>
#include <g3sdk/Game/ge_effectsystem.h>
#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>
#include <g3sdk/util/ScriptUtil.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

#include <windows.h>

static mCFunctionHook Hook_StartEffect;
static mCFunctionHook Hook_OnAI_Attack;
static mCFunctionHook Hook_OnAI_QuickAttack;
static mCFunctionHook Hook_SetCollisionGroup;

static FILE *g_pLog = nullptr;
static LARGE_INTEGER g_StartCounter = {};
static LARGE_INTEGER g_Frequency = {};

// Last animation name logged per actor.
// Diagnostic only; it prevents the v0.5 per-frame suppression spam.
static std::unordered_map<eCEntity *, std::string> g_LastLoggedAni;

// Marker-presence cache by exact animation filename.
// Marker ownership belongs to the animation resource, so it does not need to
// be rescanned every callback once resolved.
struct CachedMarkerInfo
{
    bool foundMatchingMotion;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt markerFrame;
};

static std::unordered_map<std::string, CachedMarkerInfo> g_MarkerCache;

// -----------------------------------------------------------------------------
// Results
// -----------------------------------------------------------------------------

struct FrameEffectScanResult
{
    bool layoutLookedValid;
    bool foundMarker;
    GEInt count;
    GEInt markerFrame;
};

struct CurrentMotionMarkerResult
{
    bool foundMatchingMotion;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt markerFrame;
};

// -----------------------------------------------------------------------------
// General helpers
// -----------------------------------------------------------------------------

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

    return (static_cast<double>(now.QuadPart - g_StartCounter.QuadPart) * 1000.0)
         / static_cast<double>(g_Frequency.QuadPart);
}

static void OpenLog()
{
    ::QueryPerformanceFrequency(&g_Frequency);
    ::QueryPerformanceCounter(&g_StartCounter);

    std::string logPath = GetGameDirectory() + "\\Script_FrameCollisionTest.log";

    g_pLog = std::fopen(logPath.c_str(), "w");

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "Script_FrameCollisionTest v0.9 loaded.\n");

        std::fprintf(g_pLog, "GENERALIZED ACTOR / WEAPON-SLOT PROTOTYPE.\n");

        std::fprintf(g_pLog, "NO IsPlayer restriction.\n");

        std::fprintf(g_pLog, "NO 2H / Staff / 1H use-type restriction.\n");

        std::fprintf(g_pLog, "NO P0/P1/P2 restriction.\n");

        std::fprintf(g_pLog, "Normal eligibility: current animation contains _Attack_Hit_ and G3AB_COL_TEST.\n");

        std::fprintf(g_pLog, "Quick eligibility: OnAI_QuickAttack + exact Quick/QuickR/QuickL action + Hit phase + G3AB_COL_TEST.\n");

        std::fprintf(g_pLog, "Accepted Quick marker completes one-shot callback bookkeeping: StatePosition -> 1.\n");

        std::fprintf(g_pLog, "FIST CAUSAL TEST: raw Fist/PhysicalFist skips SetCollisionGroup(Item_Attack).\n");

        std::fprintf(g_pLog, "FIST CAUSAL TEST: ClearTriggeredList remains active.\n");

        std::fprintf(g_pLog, "Prototype source resolver: current actor RIGHT-HAND equipped item.\n");

        std::fprintf(g_pLog, "If a marked animation has no right-hand item, its original attack callback is NOT suppressed.\n");

        std::fprintf(g_pLog, "This protects unarmed/monster attacks until body-source resolution is implemented.\n");

        std::fprintf(g_pLog, "Marker action: non-Fist -> Item_Attack + ClearTriggeredList; Fist -> ClearTriggeredList only.\n");

        std::fprintf(g_pLog, "No custom collision-OFF cleanup; Gothic 3 owns Hit->Recover reset.\n");

        std::fprintf(g_pLog, "Known collision groups: Item_Equipped=5, Item_Attack=7.\n\n");

        std::fflush(g_pLog);
    }
}

static bool Contains(char const *text, char const *token)
{
    return text != nullptr && token != nullptr && std::strstr(text, token) != nullptr;
}

static char const *BaseName(char const *path)
{
    if (path == nullptr)
        return "";

    char const *slash1 = std::strrchr(path, '\\');

    char const *slash2 = std::strrchr(path, '/');

    char const *last = slash1;

    if (slash2 != nullptr && (last == nullptr || slash2 > last))
    {
        last = slash2;
    }

    return last != nullptr ? last + 1 : path;
}

static bool SameFileName(char const *a, char const *b)
{
    if (a == nullptr || b == nullptr)
        return false;

    return _stricmp(BaseName(a), BaseName(b)) == 0;
}

static bool IsAttackHit(Entity &actor)
{
    bCString ani = actor.NPC.GetCurrentMovementAni();

    return Contains(ani.GetText(), "_Attack_Hit_");
}

static bool IsQuickAttackAction(gEAction action)
{
    return action == gEAction_QuickAttack || action == gEAction_QuickAttackR || action == gEAction_QuickAttackL;
}

static bool IsQuickAttackHit(Entity &actor)
{
    gEAction action = actor.Routine.GetProperty<PSRoutine::PropertyAction>();

    return IsQuickAttackAction(action) && actor.GetCurrentAniPhase() == gEPhase_Hit;
}

static Entity GetPrototypeCollisionSource(Entity &actor)
{
    // The prototype intentionally supports all actors/weapon types but only
    // one source-resolution rule:
    //
    //     G3AB_COL_TEST -> actor's current right-hand equipped item.
    //
    // This covers the human melee weapon families we can immediately test
    // (2H, Staff, 1H, etc.) without pretending that monster body attacks
    // are already solved.
    return actor.Inventory.GetItemFromSlot(gESlot_RightHand);
}

static gEUseType GetCollisionSourceUseType(Entity &source)
{
    eCEntity *instance = source.GetInstance();

    return instance != nullptr ? instance->GetUseType() : gEUseType_None;
}

static bool IsFistCollisionSource(Entity &source)
{
    if (source == None)
        return false;

    gEUseType useType = GetCollisionSourceUseType(source);

    return useType == gEUseType_Fist || useType == gEUseType_PhysicalFist;
}

// -----------------------------------------------------------------------------
// Frame-effect scan
//
// CONFIRMED runtime layout:
//
// eCResourceAnimationMotion_PS
//     +0x4C = frame-effect array data pointer
//     +0x50 = frame-effect count
//
// eSFrameEffect
//     +0x00 = GEU16 authored frame
//     +0x04 = bCString effect name
//     stride = 8 bytes
// -----------------------------------------------------------------------------

static FrameEffectScanResult ScanFrameEffects(eCResourceAnimationMotion_PS const *motion)
{
    FrameEffectScanResult result = {};

    result.layoutLookedValid = false;
    result.foundMarker = false;
    result.count = 0;
    result.markerFrame = -1;

    if (motion == nullptr)
        return result;

    unsigned char const *base = reinterpret_cast<unsigned char const *>(motion);

    unsigned char const *data = *reinterpret_cast<unsigned char const *const *>(base + 0x4C);

    GEInt count = *reinterpret_cast<GEInt const *>(base + 0x50);

    result.count = count;

    if (count < 0 || count > 256)
        return result;

    if (count > 0 && data == nullptr)
        return result;

    result.layoutLookedValid = true;

    for (GEInt i = 0; i < count; ++i)
    {
        unsigned char const *entry = data + (i * 8);

        GEU16 authoredFrame = *reinterpret_cast<GEU16 const *>(entry + 0x00);

        bCString const *effectString = reinterpret_cast<bCString const *>(entry + 0x04);

        char const *effectName = effectString->GetText();

        if (effectName != nullptr && std::strcmp(effectName, "G3AB_COL_TEST") == 0)
        {
            result.foundMarker = true;

            result.markerFrame = static_cast<GEInt>(authoredFrame);

            break;
        }
    }

    return result;
}

static CurrentMotionMarkerResult ScanCurrentMotionForMarker(Entity &actor)
{
    CurrentMotionMarkerResult result = {};

    result.foundMatchingMotion = false;
    result.markerPresent = false;
    result.frameEffectCount = 0;
    result.markerFrame = -1;

    eCEntity *instance = actor.GetInstance();

    if (instance == nullptr)
        return result;

    eCEntityPropertySet *propertySet = instance->GetPropertySet(eEPropertySetType_Animation);

    if (propertySet == nullptr)
        return result;

    eCVisualAnimation_PS *visualAnimation = static_cast<eCVisualAnimation_PS *>(propertySet);

    bCString currentAni = actor.NPC.GetCurrentMovementAni();

    char const *currentAniName = currentAni.GetText();

    for (GEInt i = 0; i < 4; ++i)
    {
        eCWrapper_emfx2Actor::eEMotionType type = static_cast<eCWrapper_emfx2Actor::eEMotionType>(i);

        eCVisualAnimation_PS::eSMotionDesc const &desc = visualAnimation->GetMotionDesc(type);

        if (desc.IsValid() == GEFalse)
            continue;

        bCString const &motionFilename = desc.GetMotionFilename();

        if (!SameFileName(motionFilename.GetText(), currentAniName))
        {
            continue;
        }

        result.foundMatchingMotion = true;

        eCResourceAnimationMotion_PS const *motion = desc.GetMotion();

        FrameEffectScanResult scan = ScanFrameEffects(motion);

        result.frameEffectCount = scan.count;

        result.markerPresent = scan.layoutLookedValid && scan.foundMarker;

        result.markerFrame = scan.markerFrame;

        return result;
    }

    return result;
}

static CurrentMotionMarkerResult GetCurrentMarkerDecision(Entity &actor)
{
    bCString currentAni = actor.NPC.GetCurrentMovementAni();

    std::string currentName = currentAni.GetText() != nullptr ? currentAni.GetText() : "";

    auto found = g_MarkerCache.find(currentName);

    if (found != g_MarkerCache.end())
    {
        CurrentMotionMarkerResult result = {};

        result.foundMatchingMotion = found->second.foundMatchingMotion;

        result.markerPresent = found->second.markerPresent;

        result.frameEffectCount = found->second.frameEffectCount;

        result.markerFrame = found->second.markerFrame;

        return result;
    }

    CurrentMotionMarkerResult scanned = ScanCurrentMotionForMarker(actor);

    CachedMarkerInfo cached = {};

    cached.foundMatchingMotion = scanned.foundMatchingMotion;

    cached.markerPresent = scanned.markerPresent;

    cached.frameEffectCount = scanned.frameEffectCount;

    cached.markerFrame = scanned.markerFrame;

    g_MarkerCache[currentName] = cached;

    return scanned;
}

// -----------------------------------------------------------------------------
// Diagnostic helpers
// -----------------------------------------------------------------------------

static bool ShouldLogOwnership(Entity &actor)
{
    eCEntity *instance = actor.GetInstance();

    if (instance == nullptr)
        return true;

    bCString ani = actor.NPC.GetCurrentMovementAni();

    std::string currentName = ani.GetText() != nullptr ? ani.GetText() : "";

    auto found = g_LastLoggedAni.find(instance);

    if (found != g_LastLoggedAni.end() && found->second == currentName)
    {
        return false;
    }

    g_LastLoggedAni[instance] = currentName;

    return true;
}

static void LogOwnershipDecision(Entity &actor, CurrentMotionMarkerResult const &decision, Entity &source,
                                 bool willSuppress)
{
    if (g_pLog == nullptr)
        return;

    bCString ani = actor.NPC.GetCurrentMovementAni();

    std::fprintf(g_pLog, "===== MARKER OWNERSHIP DECISION =====\n");

    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", GetElapsedMilliseconds());

    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());

    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());

    std::fprintf(g_pLog, "MatchingMotionFound: %d\n", decision.foundMatchingMotion ? 1 : 0);

    std::fprintf(g_pLog, "FrameEffectCount: %d\n", decision.frameEffectCount);

    std::fprintf(g_pLog, "Contains_G3AB_COL_TEST: %d\n", decision.markerPresent ? 1 : 0);

    std::fprintf(g_pLog, "MarkerFrame: %d\n", decision.markerFrame);

    std::fprintf(g_pLog, "RightHandSourceResolved: %d\n", source != None ? 1 : 0);

    if (source != None)
    {
        std::fprintf(g_pLog, "ResolvedSource: %s\n", source.GetName().GetText());

        std::fprintf(g_pLog, "ResolvedSourceUseType: %d\n", static_cast<GEInt>(GetCollisionSourceUseType(source)));

        std::fprintf(g_pLog, "ResolvedSourceCollisionGroup: %d\n", static_cast<GEInt>(source.GetCollisionGroup()));
    }

    std::fprintf(g_pLog, "Decision: %s\n",
                 willSuppress ? "FRAME-CONTROLLED - suppress original timer callback"
                              : "LEGACY/NATIVE - call original timer callback");

    if (decision.markerPresent && source == None)
    {
        std::fprintf(g_pLog, "Reason: marker exists but the prototype has no valid right-hand item source.\n");
    }

    std::fprintf(g_pLog, "=====================================\n\n");

    std::fflush(g_pLog);
}

static void LogMarkerContext(Entity &actor, Entity &source)
{
    if (g_pLog == nullptr)
        return;

    bCString ani = actor.NPC.GetCurrentMovementAni();

    std::fprintf(g_pLog, "===== G3AB_COL_TEST RECEIVED =====\n");

    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", GetElapsedMilliseconds());

    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());

    std::fprintf(g_pLog, "Action: %d\n", static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>()));

    std::fprintf(g_pLog, "AniPhase: %d\n", static_cast<GEInt>(actor.GetCurrentAniPhase()));

    std::fprintf(g_pLog, "StateTime: %.6f\n", actor.Routine.GetStateTime());

    std::fprintf(g_pLog, "StatePosition: %d\n",
                 static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>()));

    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());

    std::fprintf(g_pLog, "RightHandSourceResolved: %d\n", source != None ? 1 : 0);

    if (source != None)
    {
        std::fprintf(g_pLog, "ResolvedSource: %s\n", source.GetName().GetText());

        std::fprintf(g_pLog, "ResolvedSourceUseType: %d\n", static_cast<GEInt>(GetCollisionSourceUseType(source)));

        std::fprintf(g_pLog, "ResolvedSourceCollisionGroup: %d\n", static_cast<GEInt>(source.GetCollisionGroup()));
    }
}

// -----------------------------------------------------------------------------
// Engine eCEntity::SetCollisionGroup logger
//
// v0.6 no longer filters to the player's weapon.
// It logs ANY entity transition involving Item_Attack so NPC/staff activation
// and natural reset are directly visible.
// -----------------------------------------------------------------------------

static void GE_STDCALL SetCollisionGroup_FrameCollisionTest(eECollisionGroup a_Group)
{
    eCEntity *pThis = Hook_SetCollisionGroup.GetSelf<eCEntity *>();

    eECollisionGroup beforeGroup = pThis != nullptr ? pThis->GetCollisionGroup() : static_cast<eECollisionGroup>(-1);

    Hook_SetCollisionGroup.GetOriginalFunction (&SetCollisionGroup_FrameCollisionTest)(a_Group);

    if (pThis == nullptr || g_pLog == nullptr)
    {
        return;
    }

    eECollisionGroup afterGroup = pThis->GetCollisionGroup();

    bool involvesAttack = a_Group == eECollisionGroup_Item_Attack || beforeGroup == eECollisionGroup_Item_Attack
                       || afterGroup == eECollisionGroup_Item_Attack;

    if (!involvesAttack)
        return;

    Entity changedEntity(pThis);

    std::fprintf(g_pLog, "===== ENGINE SetCollisionGroup =====\n");

    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", GetElapsedMilliseconds());

    std::fprintf(g_pLog, "Entity: %s\n", changedEntity.GetName().GetText());

    std::fprintf(g_pLog, "RequestedGroup: %d\n", static_cast<GEInt>(a_Group));

    std::fprintf(g_pLog, "BeforeGroup: %d\n", static_cast<GEInt>(beforeGroup));

    std::fprintf(g_pLog, "AfterGroup: %d\n", static_cast<GEInt>(afterGroup));

    std::fprintf(g_pLog, "Item_EquippedValue: %d\n", static_cast<GEInt>(eECollisionGroup_Item_Equipped));

    std::fprintf(g_pLog, "Item_AttackValue: %d\n", static_cast<GEInt>(eECollisionGroup_Item_Attack));

    std::fprintf(g_pLog, "====================================\n\n");

    std::fflush(g_pLog);
}

// -----------------------------------------------------------------------------
// OnAI_Attack
//
// v0.6:
//     ANY actor.
//     ANY weapon/use type.
//     ANY P-position.
//
// A marked Attack_Hit is controlled only when the provisional right-hand
// source resolver succeeds.
//
// If source cannot be resolved, original callback remains untouched.
// -----------------------------------------------------------------------------

DECLARE_SCRIPT_CALLBACK(OnAI_Attack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()

    if (!IsAttackHit(SelfEntity))
    {
        return Hook_OnAI_Attack.GetOriginalFunction(&OnAI_Attack_FrameCollisionTest)(a_pSPU);
    }

    CurrentMotionMarkerResult decision = GetCurrentMarkerDecision(SelfEntity);

    Entity source = GetPrototypeCollisionSource(SelfEntity);

    bool willSuppress = decision.foundMatchingMotion && decision.markerPresent && source != None;

    if (ShouldLogOwnership(SelfEntity))
    {
        LogOwnershipDecision(SelfEntity, decision, source, willSuppress);
    }

    if (willSuppress)
    {
        return GETrue;
    }

    return Hook_OnAI_Attack.GetOriginalFunction(&OnAI_Attack_FrameCollisionTest)(a_pSPU);
}

// -----------------------------------------------------------------------------
// OnAI_QuickAttack
//
// v0.7 adds only the native Quick callback family.
//
// Exact Quick/QuickR/QuickL action and Hit phase replace filename-family
// parsing for this path. Marker ownership and right-hand source resolution
// remain identical to the proven Normal prototype behavior.
// -----------------------------------------------------------------------------

DECLARE_SCRIPT_CALLBACK(OnAI_QuickAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()

    if (!IsQuickAttackHit(SelfEntity))
    {
        return Hook_OnAI_QuickAttack.GetOriginalFunction(&OnAI_QuickAttack_FrameCollisionTest)(a_pSPU);
    }

    CurrentMotionMarkerResult decision = GetCurrentMarkerDecision(SelfEntity);

    Entity source = GetPrototypeCollisionSource(SelfEntity);

    bool willSuppress = decision.foundMatchingMotion && decision.markerPresent && source != None;

    if (ShouldLogOwnership(SelfEntity))
    {
        LogOwnershipDecision(SelfEntity, decision, source, willSuppress);
    }

    if (willSuppress)
    {
        return GETrue;
    }

    return Hook_OnAI_QuickAttack.GetOriginalFunction(&OnAI_QuickAttack_FrameCollisionTest)(a_pSPU);
}

// -----------------------------------------------------------------------------
// StartEffect
//
// G3AB_COL_TEST remains a PROTOTYPE marker.
// In v0.7 its meaning is:
//
//     activate current actor's right-hand equipped item.
//
// It is deliberately NOT yet the final PRIMARY/SECONDARY/ALL vocabulary.
// -----------------------------------------------------------------------------

static GELPVoid StartEffect_FrameCollisionTest(bCString const &a_EffectName, eCEntity *a_pEntity1, eCEntity *a_pEntity2,
                                               bCMatrix const *a_pMatrix, GEBool a_bUnknown)
{
    GELPCChar effectName = a_EffectName.GetText();

    if (effectName == nullptr || std::strcmp(effectName, "G3AB_COL_TEST") != 0)
    {
        return Hook_StartEffect.GetOriginalFunction(&StartEffect_FrameCollisionTest)(a_EffectName, a_pEntity1,
                                                                                     a_pEntity2, a_pMatrix, a_bUnknown);
    }

    // Reserved test marker is consumed even if the actor/source cannot be
    // resolved, so the engine never tries to find a real effect resource
    // named G3AB_COL_TEST.
    if (a_pEntity1 == nullptr)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "===== G3AB_COL_TEST RECEIVED =====\n");

            std::fprintf(g_pLog, "MarkerAction: REJECTED - Entity1 == NULL\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    Entity actor(a_pEntity1);

    Entity source = GetPrototypeCollisionSource(actor);

    LogMarkerContext(actor, source);

    bool isNormalAttackHit = IsAttackHit(actor);

    bool isQuickAttackHit = IsQuickAttackHit(actor);

    if (!isNormalAttackHit && !isQuickAttackHit)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: REJECTED - unsupported Normal/Quick Hit context\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    CurrentMotionMarkerResult decision = GetCurrentMarkerDecision(actor);

    if (!decision.foundMatchingMotion || !decision.markerPresent)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: REJECTED - current matching motion does not own marker\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    if (source == None)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(
                g_pLog,
                "MarkerAction: UNSUPPORTED SOURCE - no right-hand item; original attack-family callback was left active\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    GEInt beforeGroup = static_cast<GEInt>(source.GetCollisionGroup());

    GEInt sourceUseType = static_cast<GEInt>(GetCollisionSourceUseType(source));

    bool skipCollisionGroupForFist = IsFistCollisionSource(source);

    GEInt quickStatePositionBeforeMarker = -1;

    GEInt quickStatePositionAfterMarker = -1;

    if (isQuickAttackHit)
    {
        quickStatePositionBeforeMarker =
            static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    }

    // v0.9 causal isolation:
    // keep ownership, native suppression, marker timing, source resolution,
    // and triggered-list rearming unchanged. Skip only the weapon-style group
    // request when the resolved raw source is Fist/PhysicalFist.
    if (!skipCollisionGroupForFist)
    {
        source.SetCollisionGroup(eECollisionGroup_Item_Attack);
    }

    source.TouchDamage.ClearTriggeredList();

    // Reference Quick callback implementations use StatePosition as their
    // one-shot collision activation gate and set it to 1 after activating.
    // v0.7 runtime left this gate at 0, after which the original callback
    // reactivated collision following Gothic 3's natural reset. Complete that
    // bookkeeping here when the accepted Quick marker owns activation.
    //
    // Keep the proven Normal path unchanged.
    if (isQuickAttackHit)
    {
        actor.Routine.AccessProperty<PSRoutine::PropertyStatePosition>() = 1;

        quickStatePositionAfterMarker =
            static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    }

    GEInt afterGroup = static_cast<GEInt>(source.GetCollisionGroup());

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "MarkerAction: ACCEPTED\n");

        std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n", decision.markerFrame);

        std::fprintf(g_pLog, "CollisionGroupBeforeMarker: %d\n", beforeGroup);

        std::fprintf(g_pLog, "CollisionGroupAfterMarker: %d\n", afterGroup);

        std::fprintf(g_pLog, "ResolvedSourceUseTypeAtMarker: %d\n", sourceUseType);

        std::fprintf(g_pLog, "SetCollisionGroupAction: %s\n",
                     skipCollisionGroupForFist ? "SKIPPED_FOR_FIST_CAUSAL_TEST"
                                               : "REQUESTED_ITEM_ATTACK");

        std::fprintf(g_pLog, "TriggeredDamageList: CLEARED\n");

        if (isQuickAttackHit)
        {
            std::fprintf(g_pLog, "QuickStatePositionBeforeMarker: %d\n", quickStatePositionBeforeMarker);

            std::fprintf(g_pLog, "QuickStatePositionAfterMarker: %d\n", quickStatePositionAfterMarker);
        }

        std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");

        std::fprintf(g_pLog, "=================================\n\n");

        std::fflush(g_pLog);
    }

    return nullptr;
}

// -----------------------------------------------------------------------------
// Install
// -----------------------------------------------------------------------------

static void InstallHooks()
{
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    Hook_OnAI_Attack.Hook(GetScriptAdminExt().GetScriptAICallback("OnAI_Attack")->m_funcScriptAICallback,
                          &OnAI_Attack_FrameCollisionTest);

    Hook_OnAI_QuickAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_QuickAttack")->m_funcScriptAICallback,
        &OnAI_QuickAttack_FrameCollisionTest);

    Hook_StartEffect.Prepare(RVA_Game(0x60850), &StartEffect_FrameCollisionTest, mCBaseHook::mEHookType_ThisCall)
        .Hook();

    Hook_SetCollisionGroup
        .Prepare(RVA_Engine(0x225660), &SetCollisionGroup_FrameCollisionTest, mCBaseHook::mEHookType_ThisCall)
        .Hook();
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    OpenLog();

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "Installing hooks...\n");

        std::fflush(g_pLog);
    }

    InstallHooks();

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "Hooks installed.\n\n");

        std::fflush(g_pLog);
    }

    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: ::DisableThreadLibraryCalls(hModule); break;

        case DLL_PROCESS_DETACH:
            if (g_pLog != nullptr)
            {
                std::fprintf(g_pLog, "Script_FrameCollisionTest unloading.\n");

                std::fflush(g_pLog);
                std::fclose(g_pLog);
                g_pLog = nullptr;
            }
            break;
    }

    return TRUE;
}
