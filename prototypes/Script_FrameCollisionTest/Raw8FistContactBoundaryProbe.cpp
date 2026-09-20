#include "Raw8FistContactBoundaryProbe.h"

#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"
#include "RuntimeClock.h"

#include <cstdio>

namespace FrameCollision::Raw8FistContactBoundaryProbe
{
static thread_local InvocationScope *g_pCurrentInvocation = nullptr;

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

static EntityVisitSnapshot CaptureEntityVisit(
    bTObjArray<eCEntityProxy> const &entitiesVisited,
    bTValArray<GEU16> const &entitiesVisitedCount,
    eCEntity *entityArgument)
{
    EntityVisitSnapshot result = {};
    result.index = -1;
    result.count = -1;
    if (entityArgument == nullptr)
        return result;

    GEInt const visitedSize = entitiesVisited.GetCount();
    GEInt const countSize = entitiesVisitedCount.GetCount();
    for (GEInt index = 0; index < visitedSize; ++index)
    {
        if (entitiesVisited[index].GetEntity() != entityArgument)
            continue;
        result.present = true;
        result.index = index;
        if (index < countSize)
        {
            result.countAvailable = true;
            result.count = static_cast<GEInt>(entitiesVisitedCount[index]);
        }
        break;
    }
    return result;
}

static VisitedSnapshot CaptureVisitedSnapshot(
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument1,
    eCEntity *entityArgument2)
{
    VisitedSnapshot result = {};
    result.entitiesVisitedSize = -1;
    result.entitiesVisitedCountSize = -1;
    result.argument1.index = -1;
    result.argument1.count = -1;
    result.argument2.index = -1;
    result.argument2.count = -1;
    if (touchDamagePS == nullptr)
        return result;

    bTObjArray<eCEntityProxy> const &entitiesVisited =
        touchDamagePS->GetEntitiesVisited();
    bTValArray<GEU16> const &entitiesVisitedCount =
        touchDamagePS->GetEntitiesVisitedCount();
    result.entitiesVisitedSize = entitiesVisited.GetCount();
    result.entitiesVisitedCountSize = entitiesVisitedCount.GetCount();
    result.argument1 = CaptureEntityVisit(
        entitiesVisited, entitiesVisitedCount, entityArgument1);
    result.argument2 = CaptureEntityVisit(
        entitiesVisited, entitiesVisitedCount, entityArgument2);
    return result;
}

static bool MatchesCurrentInvocation(gCTouchDamage_PS *touchDamagePS)
{
    InvocationScope const *const scope = g_pCurrentInvocation;
    if (scope == nullptr || !scope->eligible
        || scope->touchDamagePS != touchDamagePS
        || scope->spu == nullptr
        || scope->spu->GetSelfEntity() != scope->actorInstance)
    {
        return false;
    }

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope->actorInstance);
    if (!generation.valid || generation.generation != scope->c1Generation)
        return false;

    Entity actor(scope->actorInstance);
    if (actor == None)
        return false;
    eCEntity *const currentSource =
        CollisionSources::ResolveFistCollisionSource(actor);
    if (currentSource != scope->fistSourceInstance)
        return false;

    Entity source(currentSource);
    return source != None
        && CollisionSources::GetCollisionSourceUseType(source)
            == gEUseType_Fist
        && source.TouchDamage.m_pEngineEntityPropertySet == touchDamagePS;
}

static void LogInvocationIdentity(
    FILE *log, InvocationScope const &scope)
{
    std::fprintf(
        log,
        " Actor=%s ActorAddress=%p SPUAddress=%p C1=%llu Action=%d "
        "Motion=%s Raw8Fist=%s Raw8FistAddress=%p Raw8UseType=%d "
        "TouchDamageAddress=%p",
        scope.actorName.c_str(), static_cast<void *>(scope.actorInstance),
        static_cast<void *>(scope.spu),
        static_cast<unsigned long long>(scope.c1Generation), scope.action,
        scope.animationName.c_str(), scope.sourceName.c_str(),
        static_cast<void *>(scope.fistSourceInstance), scope.sourceUseType,
        static_cast<void *>(scope.touchDamagePS));
}

static void LogVisitedSizes(
    FILE *log, char const *prefix, VisitedSnapshot const &snapshot)
{
    std::fprintf(
        log, " %sEntitiesVisitedSize=%d %sEntitiesVisitedCountSize=%d",
        prefix, snapshot.entitiesVisitedSize,
        prefix, snapshot.entitiesVisitedCountSize);
}

static void LogEntityVisit(
    FILE *log, char const *prefix, EntityVisitSnapshot const &snapshot)
{
    std::fprintf(
        log,
        " %sPresent=%d %sIndex=%d %sCountAvailable=%d %sCount=%d",
        prefix, snapshot.present ? 1 : 0,
        prefix, snapshot.index,
        prefix, snapshot.countAvailable ? 1 : 0,
        prefix, snapshot.count);
}

void BeginInvocation(
    gCScriptProcessingUnit *spu, InvocationScope &scope)
{
    scope = InvocationScope{};
    scope.previous = g_pCurrentInvocation;
    scope.spu = spu;
    g_pCurrentInvocation = &scope;
    if (spu == nullptr)
        return;

    scope.actorInstance = spu->GetSelfEntity();
    Entity actor(scope.actorInstance);
    if (actor == None)
        return;

    CollisionLifecycleGuard::GenerationToken const generation =
        CollisionLifecycleGuard::CaptureCurrentGenerationToken(
            scope.actorInstance);
    if (!generation.valid)
        return;

    scope.fistSourceInstance =
        CollisionSources::ResolveFistCollisionSource(actor);
    Entity source(scope.fistSourceInstance);
    if (source == None)
        return;

    gEUseType const useType =
        CollisionSources::GetCollisionSourceUseType(source);
    if (useType != gEUseType_Fist)
        return;

    scope.touchDamagePS = static_cast<gCTouchDamage_PS *>(
        source.TouchDamage.m_pEngineEntityPropertySet);
    if (scope.touchDamagePS == nullptr)
        return;

    scope.c1Generation = generation.generation;
    scope.actorName = EntityName(scope.actorInstance);
    scope.sourceName = EntityName(scope.fistSourceInstance);
    scope.action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    scope.sourceUseType = static_cast<GEInt>(useType);
    bCString const animation = actor.NPC.GetCurrentMovementAni();
    char const *const animationText = animation.GetText();
    scope.animationName = animationText != nullptr ? animationText : "";
    scope.eligible = true;
}

void CompleteInvocation(InvocationScope &scope)
{
    if (g_pCurrentInvocation == &scope)
        g_pCurrentInvocation = scope.previous;
}

void BeginContactGateObservation(
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument,
    void *contactIteratorAddress, ContactGateObservation &observation)
{
    observation = ContactGateObservation{};
    if (!MatchesCurrentInvocation(touchDamagePS))
        return;

    InvocationScope *const invocation = g_pCurrentInvocation;
    observation.invocation = invocation;
    observation.entityArgument = entityArgument;
    observation.entityArgumentName = EntityName(entityArgument);
    observation.contactIteratorAddress = contactIteratorAddress;
    observation.before = CaptureVisitedSnapshot(
        touchDamagePS, entityArgument, nullptr);
    observation.beforeElapsedMs = RuntimeClock::GetElapsedMilliseconds();
    observation.eventOrdinal = ++invocation->contactEventOrdinal;
    observation.gateOrdinal = ++invocation->contactGateOrdinal;
    observation.active = true;
}

void CompleteContactGateObservation(
    ContactGateObservation &observation, GEBool nativeResult)
{
    if (!observation.active || observation.invocation == nullptr)
        return;

    InvocationScope const &invocation = *observation.invocation;
    VisitedSnapshot const after = CaptureVisitedSnapshot(
        invocation.touchDamagePS, observation.entityArgument, nullptr);
    double const afterElapsedMs = RuntimeClock::GetElapsedMilliseconds();
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(
        log,
        "CORE RAW8_CONTACT_GATE BeforeElapsedMs=%.3f AfterElapsedMs=%.3f "
        "EventOrdinal=%u GateOrdinal=%u",
        observation.beforeElapsedMs, afterElapsedMs,
        static_cast<unsigned int>(observation.eventOrdinal),
        static_cast<unsigned int>(observation.gateOrdinal));
    LogInvocationIdentity(log, invocation);
    std::fprintf(
        log,
        " EntityArg=%s EntityArgAddress=%p ContactIteratorAddress=%p "
        "NativeResult=%d",
        observation.entityArgumentName.c_str(),
        static_cast<void *>(observation.entityArgument),
        observation.contactIteratorAddress, static_cast<GEInt>(nativeResult));
    LogVisitedSizes(log, "Before", observation.before);
    LogEntityVisit(log, "BeforeArg", observation.before.argument1);
    LogVisitedSizes(log, "After", after);
    LogEntityVisit(log, "AfterArg", after.argument1);
    std::fprintf(log, "\n");
    std::fflush(log);
}

void BeginContactTargetObservation(
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument1,
    eCEntity *entityArgument2, void *contactIteratorAddress,
    ContactTargetObservation &observation)
{
    observation = ContactTargetObservation{};
    if (!MatchesCurrentInvocation(touchDamagePS))
        return;

    InvocationScope *const invocation = g_pCurrentInvocation;
    observation.invocation = invocation;
    observation.entityArgument1 = entityArgument1;
    observation.entityArgument2 = entityArgument2;
    observation.entityArgument1Name = EntityName(entityArgument1);
    observation.entityArgument2Name = EntityName(entityArgument2);
    observation.contactIteratorAddress = contactIteratorAddress;
    observation.before = CaptureVisitedSnapshot(
        touchDamagePS, entityArgument1, entityArgument2);
    observation.beforeElapsedMs = RuntimeClock::GetElapsedMilliseconds();
    observation.eventOrdinal = ++invocation->contactEventOrdinal;
    observation.targetOrdinal = ++invocation->contactTargetOrdinal;
    observation.active = true;
}

void CompleteContactTargetObservation(
    ContactTargetObservation &observation)
{
    if (!observation.active || observation.invocation == nullptr)
        return;

    InvocationScope const &invocation = *observation.invocation;
    VisitedSnapshot const after = CaptureVisitedSnapshot(
        invocation.touchDamagePS, observation.entityArgument1,
        observation.entityArgument2);
    double const afterElapsedMs = RuntimeClock::GetElapsedMilliseconds();
    FILE *const log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(
        log,
        "CORE RAW8_CONTACT_TARGET BeforeElapsedMs=%.3f AfterElapsedMs=%.3f "
        "EventOrdinal=%u TargetOrdinal=%u",
        observation.beforeElapsedMs, afterElapsedMs,
        static_cast<unsigned int>(observation.eventOrdinal),
        static_cast<unsigned int>(observation.targetOrdinal));
    LogInvocationIdentity(log, invocation);
    std::fprintf(
        log,
        " EntityArg1=%s EntityArg1Address=%p EntityArg2=%s "
        "EntityArg2Address=%p ContactIteratorAddress=%p",
        observation.entityArgument1Name.c_str(),
        static_cast<void *>(observation.entityArgument1),
        observation.entityArgument2Name.c_str(),
        static_cast<void *>(observation.entityArgument2),
        observation.contactIteratorAddress);
    LogVisitedSizes(log, "Before", observation.before);
    LogEntityVisit(log, "BeforeArg1", observation.before.argument1);
    LogEntityVisit(log, "BeforeArg2", observation.before.argument2);
    LogVisitedSizes(log, "After", after);
    LogEntityVisit(log, "AfterArg1", after.argument1);
    LogEntityVisit(log, "AfterArg2", after.argument2);
    std::fprintf(log, "\n");
    std::fflush(log);
}
}
