#include "Raw8FistPersistentOpportunityProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionSources.h"
#include "FrameCollisionMarkers.h"

#include <cstdio>
#include <string>
#include <unordered_map>
#include <windows.h>

namespace FrameCollision::Raw8FistPersistentOpportunityProbe
{
struct OpportunityToken
{
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    gCScriptProcessingUnit *spu;
    std::uint64_t c1Generation;
    std::uint64_t ordinal;
    eCWrapper_emfx2Actor *timingAnimationActor;
    eCWrapper_emfx2Actor::eEMotionType timingMotionType;
    GEDouble forcedPlayTime;
    bool timingActive;
    bool pending;
};

struct ObservationContext
{
    std::string actorName;
    std::string sourceName;
    std::string motionName;
    GEInt action;
    GEInt family;
};

static thread_local std::unordered_map<eCEntity *, OpportunityToken>
    g_OpportunityTokens;
static thread_local InvocationScope *g_pCurrentInvocation = nullptr;
static thread_local std::uint64_t g_NextTokenOrdinal = 1;

static std::string EntityName(eCEntity *instance)
{
    if (instance == nullptr)
        return "<null>";
    Entity entity(instance);
    if (entity == None)
        return "<unavailable>";
    char const *const name = entity.GetName().GetText();
    return name != nullptr ? name : "<unavailable>";
}

static ObservationContext CaptureObservationContext(
    OpportunityToken const &token)
{
    ObservationContext context = {};
    context.actorName = EntityName(token.actorInstance);
    context.sourceName = "<unavailable>";
    context.action = -1;
    context.family = -1;

    Entity actor(token.actorInstance);
    if (actor == None)
        return context;

    eCEntity *const currentSource =
        CollisionSources::ResolveFistCollisionSource(actor);
    if (currentSource == token.fistSourceInstance)
        context.sourceName = EntityName(currentSource);

    context.action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    AttackFamily family = AttackFamily_Normal;
    if (FrameCollisionMarkers::TryGetCurrentAttackHitFamily(actor, family))
        context.family = static_cast<GEInt>(family);
    bCString const motion = actor.NPC.GetCurrentMovementAni();
    char const *const motionText = motion.GetText();
    context.motionName = motionText != nullptr ? motionText : "";
    return context;
}

static void LogIdentity(
    FILE *log, OpportunityToken const &token,
    ObservationContext const &context)
{
    std::fprintf(
        log,
        " Actor=%s ActorAddress=%p C1=%llu Raw8Fist=%s "
        "Raw8FistAddress=%p SPUAddress=%p TokenOrdinal=%llu "
        "Action=%d Family=%d Motion=%s",
        context.actorName.c_str(), static_cast<void *>(token.actorInstance),
        static_cast<unsigned long long>(token.c1Generation),
        context.sourceName.c_str(),
        static_cast<void *>(token.fistSourceInstance),
        static_cast<void *>(token.spu),
        static_cast<unsigned long long>(token.ordinal),
        context.action, context.family, context.motionName.c_str());
}

static bool ResolveExactLiveTransport(
    OpportunityToken const &token, Entity &actor)
{
    actor.AttachTo(token.actorInstance);
    if (actor == None)
        return false;

    gCScriptRoutine_PS *const routinePS =
        static_cast<gCScriptRoutine_PS *>(
            actor.Routine.m_pEngineEntityPropertySet);
    if (routinePS == nullptr || &routinePS->GetSPU() != token.spu)
        return false;
    if (token.spu == nullptr
        || token.spu->GetSelfEntity() != token.actorInstance)
    {
        return false;
    }

    eCEntity *const currentSource =
        CollisionSources::ResolveFistCollisionSource(actor);
    if (currentSource != token.fistSourceInstance)
        return false;
    Entity source(currentSource);
    return source != None
        && CollisionSources::GetCollisionSourceUseType(source)
            == gEUseType_Fist;
}

static bool MatchesExactExecution(OpportunityToken const &token)
{
    if (!token.pending)
        return false;
    Entity actor;
    if (!ResolveExactLiveTransport(token, actor))
        return false;
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            token.actorInstance);
    return generation.valid
        && generation.generation == token.c1Generation;
}

static volatile GEU8 *ResolveExactLiveLatch(OpportunityToken const &token)
{
    Entity actor;
    if (!ResolveExactLiveTransport(token, actor))
        return nullptr;
    return reinterpret_cast<volatile GEU8 *>(token.spu) + 0x164;
}

static void RetireTiming(OpportunityToken &token)
{
    token.timingActive = false;
    token.timingAnimationActor = nullptr;
    token.forcedPlayTime = 0.0;
}

static void LogCloseAndErase(
    std::unordered_map<eCEntity *, OpportunityToken>::iterator found,
    char const *reason, bool forceLatchClosed)
{
    OpportunityToken &token = found->second;
    ObservationContext const context = CaptureObservationContext(token);
    GEInt latchBefore = -1;
    GEInt latchAfter = -1;
    bool writeAttempted = false;
    bool writeConfirmed = false;
    if (forceLatchClosed)
    {
        volatile GEU8 *const latch = ResolveExactLiveLatch(token);
        if (latch != nullptr)
        {
            latchBefore = static_cast<GEInt>(*latch);
            writeAttempted = true;
            *latch = 1;
            latchAfter = static_cast<GEInt>(*latch);
            writeConfirmed = latchAfter == 1;
        }
    }

    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(log, "CORE RAW8_OPPORTUNITY_CLOSE");
        LogIdentity(log, token, context);
        std::fprintf(
            log,
            " Reason=%s LatchBefore=%d LatchAfter=%d "
            "LatchWriteAttempted=%d LatchWriteConfirmed=%d\n",
            reason, latchBefore, latchAfter,
            writeAttempted ? 1 : 0, writeConfirmed ? 1 : 0);
        std::fflush(log);
    }

    token.pending = false;
    RetireTiming(token);
    g_OpportunityTokens.erase(found);
}

void ObserveAcceptedMarker(
    Entity &actor, MarkerProcessResult const &result)
{
    if (actor == None
        || result.code != MarkerResult_Accepted
        || result.opcode != MarkerOpcode_Fist
        || !result.c1GenerationValid
        || result.fistSourceInstance == nullptr
        || result.fistSourceUseType != static_cast<GEInt>(gEUseType_Fist)
        || result.fistSPU == nullptr
        || !result.fistLatchWriteAttempted
        || !result.fistLatchWriteConfirmed
        || result.fistLatchAfter != 0)
    {
        return;
    }

    eCEntity *const actorInstance = actor.GetInstance();
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    if (!generation.valid
        || generation.generation != result.c1Generation)
    {
        return;
    }

    gCScriptRoutine_PS *const routinePS =
        static_cast<gCScriptRoutine_PS *>(
            actor.Routine.m_pEngineEntityPropertySet);
    if (routinePS == nullptr
        || &routinePS->GetSPU() != result.fistSPU
        || result.fistSPU->GetSelfEntity() != actorInstance
        || CollisionSources::ResolveFistCollisionSource(actor)
            != result.fistSourceInstance)
    {
        return;
    }
    Entity source(result.fistSourceInstance);
    if (source == None
        || CollisionSources::GetCollisionSourceUseType(source)
            != gEUseType_Fist)
    {
        return;
    }

    auto existing = g_OpportunityTokens.find(actorInstance);
    if (existing != g_OpportunityTokens.end()
        && existing->second.c1Generation != result.c1Generation)
    {
        // The accepted new-generation FIST has already opened its latch.
        // Retire the stale logical token without overwriting that exact write.
        LogCloseAndErase(
            existing, "REPLACED_BY_EXACT_NEW_FIST", false);
    }

    OpportunityToken token = {};
    token.actorInstance = actorInstance;
    token.fistSourceInstance = result.fistSourceInstance;
    token.spu = result.fistSPU;
    token.c1Generation = result.c1Generation;
    token.ordinal = g_NextTokenOrdinal++;
    token.pending = true;
    g_OpportunityTokens[actorInstance] = token;

    // FIST may open the token inside the combat-move invocation whose native
    // attempt follows the marker. Bind that already-live scope so the same
    // invocation can consume or miss-rearm this exact token.
    if (g_pCurrentInvocation != nullptr
        && g_pCurrentInvocation->actorInstance == actorInstance
        && g_pCurrentInvocation->spu == result.fistSPU)
    {
        g_pCurrentInvocation->fistSourceInstance =
            token.fistSourceInstance;
        g_pCurrentInvocation->c1Generation = token.c1Generation;
        g_pCurrentInvocation->tokenOrdinal = token.ordinal;
        g_pCurrentInvocation->contactConsumed = false;
        g_pCurrentInvocation->active = true;
    }

    ObservationContext const context = CaptureObservationContext(token);
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(log, "CORE RAW8_OPPORTUNITY_OPEN");
        LogIdentity(log, token, context);
        std::fprintf(
            log,
            " Reason=ACCEPTED_FIST LatchBefore=%d LatchAfter=%d "
            "LatchWriteAttempted=1 LatchWriteConfirmed=1\n",
            result.fistLatchBefore, result.fistLatchAfter);
        std::fflush(log);
    }
}

GEDouble ApplyTimingPersistence(
    gCScriptProcessingUnit *spu,
    eCWrapper_emfx2Actor *animationActor,
    eCWrapper_emfx2Actor::eEMotionType motionType,
    GEDouble realPlayTime, GEDouble permanentPlayTime)
{
    eCEntity *const actorInstance =
        spu != nullptr ? spu->GetSelfEntity() : nullptr;
    auto found = g_OpportunityTokens.find(actorInstance);
    if (found == g_OpportunityTokens.end())
        return permanentPlayTime;

    OpportunityToken &token = found->second;
    if (!MatchesExactExecution(token) || token.spu != spu)
    {
        RetireTiming(token);
        return permanentPlayTime;
    }

    bool const permanentSynthetic = permanentPlayTime > realPlayTime;
    if (permanentSynthetic && !token.timingActive)
    {
        token.timingAnimationActor = animationActor;
        token.timingMotionType = motionType;
        token.forcedPlayTime = permanentPlayTime;
        token.timingActive = true;
    }

    if (!token.timingActive)
        return permanentPlayTime;
    if (token.timingAnimationActor != animationActor
        || token.timingMotionType != motionType)
    {
        RetireTiming(token);
        return permanentPlayTime;
    }
    if (realPlayTime >= token.forcedPlayTime)
    {
        RetireTiming(token);
        return permanentPlayTime;
    }

    GEDouble const returnedPlayTime = token.forcedPlayTime;
    ObservationContext const context = CaptureObservationContext(token);
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(log, "CORE RAW8_OPPORTUNITY_TIMING_HOLD");
        LogIdentity(log, token, context);
        std::fprintf(
            log,
            " RealPlayTime=%.9f PermanentPlayTime=%.9f "
            "ForcedPlayTime=%.9f ReturnedPlayTime=%.9f "
            "PermanentSynthetic=%d\n",
            realPlayTime, permanentPlayTime, token.forcedPlayTime,
            returnedPlayTime, permanentSynthetic ? 1 : 0);
        std::fflush(log);
    }
    return returnedPlayTime;
}

void BeginCombatMoveInvocation(
    gCScriptProcessingUnit *spu, GEBool fullStop,
    InvocationScope &scope)
{
    scope = InvocationScope{};
    scope.previous = g_pCurrentInvocation;
    scope.fullStop = fullStop == GETrue;
    g_pCurrentInvocation = &scope;
    if (spu == nullptr)
        return;

    eCEntity *const actorInstance = spu->GetSelfEntity();
    scope.actorInstance = actorInstance;
    scope.spu = spu;
    auto found = g_OpportunityTokens.find(actorInstance);
    if (found == g_OpportunityTokens.end())
        return;

    OpportunityToken const &token = found->second;
    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(actorInstance);
    if (generation.valid
        && generation.generation != token.c1Generation)
    {
        LogCloseAndErase(found, "C1_GENERATION_REPLACED", true);
        return;
    }
    if (!MatchesExactExecution(token) || token.spu != spu)
        return;

    scope.actorInstance = token.actorInstance;
    scope.fistSourceInstance = token.fistSourceInstance;
    scope.spu = token.spu;
    scope.c1Generation = token.c1Generation;
    scope.tokenOrdinal = token.ordinal;
    scope.active = true;
}

void CompleteCombatMoveInvocation(InvocationScope &scope)
{
    if (scope.active && !scope.contactConsumed)
    {
        auto found = g_OpportunityTokens.find(scope.actorInstance);
        if (found != g_OpportunityTokens.end())
        {
            OpportunityToken &token = found->second;
            bool const sameToken = token.pending
                && token.ordinal == scope.tokenOrdinal
                && token.c1Generation == scope.c1Generation
                && token.fistSourceInstance == scope.fistSourceInstance
                && token.spu == scope.spu;
            if (sameToken && MatchesExactExecution(token))
            {
                volatile GEU8 *const latch = ResolveExactLiveLatch(token);
                if (latch != nullptr && *latch == 1)
                {
                    GEInt const latchBefore = static_cast<GEInt>(*latch);
                    *latch = 0;
                    GEInt const latchAfter = static_cast<GEInt>(*latch);
                    bool const writeConfirmed = latchAfter == 0;
                    ObservationContext const context =
                        CaptureObservationContext(token);
                    FILE *const log = CollisionDiagnostics::GetLog();
                    if (log != nullptr)
                    {
                        std::fprintf(
                            log, "CORE RAW8_OPPORTUNITY_MISS_REARM");
                        LogIdentity(log, token, context);
                        std::fprintf(
                            log,
                            " Reason=NO_CONTACT_DISPATCH FullStop=%d "
                            "LatchBefore=%d LatchAfter=%d "
                            "LatchWriteAttempted=1 "
                            "LatchWriteConfirmed=%d\n",
                            scope.fullStop ? 1 : 0, latchBefore, latchAfter,
                            writeConfirmed ? 1 : 0);
                        std::fflush(log);
                    }
                }
            }
        }
    }

    if (g_pCurrentInvocation == &scope)
        g_pCurrentInvocation = scope.previous;
}

void ObserveContactResolutionDispatch(
    void *callerAddress, eCEntity *entityArgument1,
    eCEntity *entityArgument2)
{
    HMODULE const gameModule = ::GetModuleHandleA("Game.dll");
    if (gameModule == nullptr
        || callerAddress
            != reinterpret_cast<void *>(
                reinterpret_cast<std::uintptr_t>(gameModule)
                + 0x0016E348))
    {
        return;
    }

    InvocationScope *const invocation = g_pCurrentInvocation;
    if (invocation == nullptr || !invocation->active)
        return;
    auto found = g_OpportunityTokens.find(entityArgument2);
    if (found == g_OpportunityTokens.end())
        return;

    OpportunityToken &token = found->second;
    bool const exactInvocation = token.pending
        && token.actorInstance == entityArgument2
        && token.fistSourceInstance == entityArgument1
        && token.actorInstance == invocation->actorInstance
        && token.fistSourceInstance == invocation->fistSourceInstance
        && token.spu == invocation->spu
        && token.c1Generation == invocation->c1Generation
        && token.ordinal == invocation->tokenOrdinal;
    if (!exactInvocation || !MatchesExactExecution(token))
        return;

    Entity source(entityArgument1);
    if (source == None
        || CollisionSources::GetCollisionSourceUseType(source)
            != gEUseType_Fist)
    {
        return;
    }

    ObservationContext const context = CaptureObservationContext(token);
    volatile GEU8 *const latch = ResolveExactLiveLatch(token);
    GEInt const latchValue =
        latch != nullptr ? static_cast<GEInt>(*latch) : -1;
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log != nullptr)
    {
        std::fprintf(log, "CORE RAW8_OPPORTUNITY_CONTACT_CONSUMED");
        LogIdentity(log, token, context);
        std::fprintf(
            log,
            " Reason=EXACT_NATIVE_CONTACT_DISPATCH "
            "CallerAddress=%p Arg1Address=%p Arg2Address=%p "
            "LatchValue=%d\n",
            callerAddress, static_cast<void *>(entityArgument1),
            static_cast<void *>(entityArgument2), latchValue);
        std::fflush(log);
    }

    invocation->contactConsumed = true;
    token.pending = false;
    RetireTiming(token);
    g_OpportunityTokens.erase(found);
}

void CloseForFinalization(
    CollisionLifecycleGuard::GenerationToken const &generation)
{
    if (!generation.valid)
        return;
    auto found = g_OpportunityTokens.find(generation.actorInstance);
    if (found == g_OpportunityTokens.end()
        || found->second.c1Generation != generation.generation)
    {
        return;
    }
    LogCloseAndErase(found, "C1_FINALIZED", true);
}
}
