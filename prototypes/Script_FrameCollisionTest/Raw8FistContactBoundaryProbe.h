#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::Raw8FistContactBoundaryProbe
{
struct EntityVisitSnapshot
{
    GEInt index;
    GEInt count;
    bool present;
    bool countAvailable;
};

struct VisitedSnapshot
{
    GEInt entitiesVisitedSize;
    GEInt entitiesVisitedCountSize;
    EntityVisitSnapshot argument1;
    EntityVisitSnapshot argument2;
};

struct InvocationScope
{
    InvocationScope *previous;
    gCScriptProcessingUnit *spu;
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    gCTouchDamage_PS *touchDamagePS;
    std::uint64_t c1Generation;
    std::string actorName;
    std::string sourceName;
    std::string animationName;
    GEInt action;
    GEInt sourceUseType;
    GEU32 contactEventOrdinal;
    GEU32 contactGateOrdinal;
    GEU32 contactTargetOrdinal;
    bool eligible;
};

struct ContactGateObservation
{
    InvocationScope *invocation;
    eCEntity *entityArgument;
    std::string entityArgumentName;
    void *contactIteratorAddress;
    VisitedSnapshot before;
    double beforeElapsedMs;
    GEU32 eventOrdinal;
    GEU32 gateOrdinal;
    bool active;
};

struct ContactTargetObservation
{
    InvocationScope *invocation;
    eCEntity *entityArgument1;
    eCEntity *entityArgument2;
    std::string entityArgument1Name;
    std::string entityArgument2Name;
    void *contactIteratorAddress;
    VisitedSnapshot before;
    double beforeElapsedMs;
    GEU32 eventOrdinal;
    GEU32 targetOrdinal;
    bool active;
};

void BeginInvocation(
    gCScriptProcessingUnit *spu, InvocationScope &scope);
void CompleteInvocation(InvocationScope &scope);

void BeginContactGateObservation(
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument,
    void *contactIteratorAddress, ContactGateObservation &observation);
void CompleteContactGateObservation(
    ContactGateObservation &observation, GEBool nativeResult);

void BeginContactTargetObservation(
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument1,
    eCEntity *entityArgument2, void *contactIteratorAddress,
    ContactTargetObservation &observation);
void CompleteContactTargetObservation(
    ContactTargetObservation &observation);
}
