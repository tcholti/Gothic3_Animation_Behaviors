#include "Raw8FistWindowProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"
#include "RuntimeClock.h"

#include <cstdint>
#include <cstdio>
#include <windows.h>

namespace FrameCollision::Raw8FistWindowProbe
{
static std::uintptr_t const ExactRaw8DamageCallerRVA = 0x0016E348;
static thread_local InvocationScope *g_pCurrentInvocation = nullptr;

static char const *EntityName(eCEntity *instance)
{
    if (instance == nullptr)
        return "<null>";
    Entity entity(instance);
    return entity != None ? entity.GetName().GetText() : "<unavailable>";
}

static void *GetExactRaw8DamageCaller()
{
    HMODULE const gameModule = ::GetModuleHandleA("Game.dll");
    if (gameModule == nullptr)
        return nullptr;
    return reinterpret_cast<void *>(
        reinterpret_cast<std::uintptr_t>(gameModule)
        + ExactRaw8DamageCallerRVA);
}

static bool IsRaw8Source(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return false;
    Entity source(sourceInstance);
    return source != None
        && CollisionSources::GetCollisionSourceUseType(source)
            == gEUseType_Fist;
}

static void LogDecision(
    InvocationScope const &scope, GEBool combatMoveResult,
    GEInt postAttemptLatchBefore, bool rearmRequested,
    GEInt postAttemptLatchAfter, bool writeConfirmed,
    bool damageCallerIdentityAvailable, bool spuActorMatch,
    CollisionLifecycleGuard::GenerationToken const &currentGeneration,
    bool currentGenerationMatch, bool currentSourceMatch,
    bool currentMotionMatch, bool currentActionMatch,
    char const *decision)
{
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    Entity fistSource(scope.fistSourceInstance);
    GEInt const raw8UseType = fistSource != None
        ? static_cast<GEInt>(
              CollisionSources::GetCollisionSourceUseType(fistSource))
        : -1;
    std::fprintf(
        log,
        "CORE RAW8_FIST_WINDOW_PROBE ElapsedMs=%.3f Actor=%s "
        "ActorAddress=%p SPUAddress=%p Action=%d Family=POWER Motion=%s "
        "C1=%llu Raw8Fist=%s Raw8FistAddress=%p Raw8UseType=%d "
        "SyntheticApplied=1 ExactNativeDamageObserved=%d "
        "ExactNativeDamageOrdinal=%u PostAttemptLatchBefore=%d "
        "RearmRequested=%d PostAttemptLatchAfter=%d WriteConfirmed=%d "
        "CombatMoveResult=%d DamageCallerIdentityAvailable=%d "
        "SPUActorMatch=%d CurrentC1Valid=%d CurrentC1=%llu C1Match=%d "
        "SourceMatch=%d MotionMatch=%d ActionMatch=%d Decision=%s\n",
        RuntimeClock::GetElapsedMilliseconds(),
        EntityName(scope.actorInstance),
        static_cast<void *>(scope.actorInstance),
        static_cast<void *>(scope.spu), scope.action,
        scope.animationName.c_str(),
        static_cast<unsigned long long>(scope.c1Generation),
        EntityName(scope.fistSourceInstance),
        static_cast<void *>(scope.fistSourceInstance), raw8UseType,
        scope.exactNativeDamageObserved ? 1 : 0,
        static_cast<unsigned int>(scope.exactNativeDamageOrdinal),
        postAttemptLatchBefore, rearmRequested ? 1 : 0,
        postAttemptLatchAfter, writeConfirmed ? 1 : 0,
        static_cast<GEInt>(combatMoveResult),
        damageCallerIdentityAvailable ? 1 : 0,
        spuActorMatch ? 1 : 0, currentGeneration.valid ? 1 : 0,
        static_cast<unsigned long long>(currentGeneration.generation),
        currentGenerationMatch ? 1 : 0,
        currentSourceMatch ? 1 : 0, currentMotionMatch ? 1 : 0,
        currentActionMatch ? 1 : 0,
        decision != nullptr ? decision : "<null>");
    std::fflush(log);
}

void BeginInvocation(
    gCScriptProcessingUnit *spu, InvocationScope &scope)
{
    scope = InvocationScope{};
    scope.previous = g_pCurrentInvocation;
    scope.spu = spu;
    g_pCurrentInvocation = &scope;
}

void ObserveTimingResult(
    gCScriptProcessingUnit *spu, GEDouble realPlayTime,
    GEDouble returnedPlayTime)
{
    InvocationScope *const scope = g_pCurrentInvocation;
    if (scope == nullptr
        || scope->spu != spu
        || scope->syntheticAttemptObserved
        || returnedPlayTime <= realPlayTime)
    {
        return;
    }

    scope->syntheticAttemptObserved = true;
    scope->actorInstance = spu != nullptr ? spu->GetSelfEntity() : nullptr;
    Entity actor(scope->actorInstance);
    if (actor == None)
        return;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    scope->c1GenerationValid = generation.valid;
    scope->c1Generation = generation.generation;
    scope->fistSourceInstance =
        CollisionSources::ResolveFistCollisionSource(actor);
    scope->originSourceIsRaw8 = IsRaw8Source(scope->fistSourceInstance);
    scope->action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    bCString const animation = actor.NPC.GetCurrentMovementAni();
    scope->animationName = animation.GetText() != nullptr
        ? animation.GetText() : "";
}

void ObserveOnDamage(
    GEU32 ordinal, void *callerAddress,
    eCEntity *entityArgument1, eCEntity *entityArgument2)
{
    InvocationScope *const scope = g_pCurrentInvocation;
    if (scope == nullptr
        || !scope->syntheticAttemptObserved
        || scope->exactNativeDamageObserved)
    {
        return;
    }

    void *const exactCaller = GetExactRaw8DamageCaller();
    if (exactCaller != nullptr
        && callerAddress == exactCaller
        && entityArgument1 == scope->fistSourceInstance
        && entityArgument2 == scope->actorInstance)
    {
        scope->exactNativeDamageObserved = true;
        scope->exactNativeDamageOrdinal = ordinal;
    }
}

void CompleteInvocation(
    InvocationScope &scope, GEBool combatMoveResult)
{
    if (g_pCurrentInvocation != &scope)
        return;
    g_pCurrentInvocation = scope.previous;
    if (!scope.syntheticAttemptObserved
        || scope.action != static_cast<GEInt>(gEAction_PowerAttack))
    {
        return;
    }

    bool const damageCallerIdentityAvailable =
        GetExactRaw8DamageCaller() != nullptr;
    eCEntity *const currentSPUActor = scope.spu != nullptr
        ? scope.spu->GetSelfEntity() : nullptr;
    bool const spuActorMatch = currentSPUActor == scope.actorInstance;

    CollisionLifecycleGuard::GenerationToken const currentGeneration =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope.actorInstance);
    bool const currentGenerationMatch = currentGeneration.valid
        && scope.c1GenerationValid
        && currentGeneration.generation == scope.c1Generation;

    Entity actor(scope.actorInstance);
    eCEntity *const currentFistSource = actor != None
        ? CollisionSources::ResolveFistCollisionSource(actor) : nullptr;
    bool const currentSourceMatch = scope.originSourceIsRaw8
        && currentFistSource == scope.fistSourceInstance
        && IsRaw8Source(currentFistSource);
    bCString const currentAnimation = actor != None
        ? actor.NPC.GetCurrentMovementAni() : bCString();
    char const *const currentAnimationText = currentAnimation.GetText();
    bool const currentMotionMatch = currentAnimationText != nullptr
        && !scope.animationName.empty()
        && scope.animationName == currentAnimationText;
    bool const currentActionMatch = actor != None
        && actor.Routine.GetProperty<PSRoutine::PropertyAction>()
            == gEAction_PowerAttack;

    GEInt postAttemptLatchBefore = -1;
    GEInt postAttemptLatchAfter = -1;
    if (scope.spu != nullptr)
    {
        volatile GEU8 *const latchByte =
            reinterpret_cast<volatile GEU8 *>(scope.spu) + 0x164;
        postAttemptLatchBefore = static_cast<GEInt>(*latchByte);
        postAttemptLatchAfter = postAttemptLatchBefore;
    }

    bool const identityMatched = damageCallerIdentityAvailable
        && spuActorMatch
        && currentGenerationMatch
        && currentSourceMatch
        && currentMotionMatch
        && currentActionMatch;
    bool const rearmRequested = !scope.exactNativeDamageObserved
        && identityMatched
        && postAttemptLatchBefore == 1;
    bool writeConfirmed = false;
    if (rearmRequested)
    {
        volatile GEU8 *const latchByte =
            reinterpret_cast<volatile GEU8 *>(scope.spu) + 0x164;
        *latchByte = 0;
        postAttemptLatchAfter = static_cast<GEInt>(*latchByte);
        writeConfirmed = postAttemptLatchAfter == 0;
    }

    char const *decision = "POST_MISS_REARM_FAILED";
    if (scope.exactNativeDamageObserved)
        decision = "EXACT_NATIVE_DAMAGE_OBSERVED";
    else if (!damageCallerIdentityAvailable)
        decision = "DAMAGE_CALLER_IDENTITY_UNAVAILABLE";
    else if (!spuActorMatch)
        decision = "SPU_ACTOR_IDENTITY_MISMATCH";
    else if (!currentGenerationMatch)
        decision = "C1_GENERATION_MISMATCH";
    else if (!currentSourceMatch)
        decision = "RAW8_SOURCE_IDENTITY_MISMATCH";
    else if (!currentMotionMatch)
        decision = "MOTION_IDENTITY_MISMATCH";
    else if (!currentActionMatch)
        decision = "ACTION_IDENTITY_MISMATCH";
    else if (postAttemptLatchBefore != 1)
        decision = "POST_ATTEMPT_LATCH_NOT_ONE";
    else if (writeConfirmed)
        decision = "POST_MISS_REARM_CONFIRMED";

    LogDecision(
        scope, combatMoveResult, postAttemptLatchBefore, rearmRequested,
        postAttemptLatchAfter, writeConfirmed,
        damageCallerIdentityAvailable, spuActorMatch, currentGeneration,
        currentGenerationMatch, currentSourceMatch, currentMotionMatch,
        currentActionMatch, decision);
}
}
