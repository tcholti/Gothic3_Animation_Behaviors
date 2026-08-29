#pragma once

#include "FrameCollisionShared.h"

#include <cstddef>
#include <cstdint>
#include <string>

namespace FrameCollision::CollisionLifecycleGuard
{
struct GenerationToken
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    bool valid;
    bool combatMoveCandidate;
};

struct ScriptFunctionDispatchToken
{
    gCScriptProcessingUnit *spu;
    eCEntity *actorInstance;
    gScrArgument *arguments;
    std::string scriptName;
    std::size_t dispatchDepth;
    bool hasLiveCorrelator;
};

ScriptFunctionDispatchToken BeginScriptFunctionDispatch(
    bCString const &scriptName,
    bTObjStack<gScriptRunTimeSingleState> &stateStack,
    gCScriptProcessingUnit *spu);
void EndScriptFunctionDispatch(
    ScriptFunctionDispatchToken const &token, GEBool originalResult);
void InvalidateScriptFunctionDispatchAfterAISetState(
    eCEntity *actorInstance);
GenerationToken BeginCombatMove(
    Entity &actor, EquippedCollisionSources const &sources,
    gCScriptProcessingUnit *spu);
void CompleteCombatMoveCandidate(
    GenerationToken const &token, GEBool originalResult);
void ObserveCollisionGroupResult(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup resultingGroup);
GenerationToken CaptureFinalizationToken(eCEntity *actorInstance);
void FinalizeAfterAISetState(GenerationToken const &token);
}
