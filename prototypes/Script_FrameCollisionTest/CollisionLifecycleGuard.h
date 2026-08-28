#pragma once

#include "FrameCollisionShared.h"

#include <cstdint>

namespace FrameCollision::CollisionLifecycleGuard
{
struct GenerationToken
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    bool valid;
};

GenerationToken BeginCombatMove(
    Entity &actor, EquippedCollisionSources const &sources);
void CompleteCombatMoveCandidate(
    GenerationToken const &token, GEBool originalResult);
void ObserveCollisionGroupResult(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup resultingGroup);
GenerationToken CaptureFinalizationToken(eCEntity *actorInstance);
void FinalizeAfterAISetState(GenerationToken const &token);
}
