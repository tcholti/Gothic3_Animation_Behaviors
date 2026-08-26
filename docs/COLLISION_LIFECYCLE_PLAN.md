# Collision Lifecycle Plan

**Status:** Working design / research target, not yet implemented  
**Updated:** 2026-08-26

## Goal

Replace accumulated cleanup/interruption contingencies with the smallest authoritative lifecycle rule the engine evidence supports.

> For every real attack-Hit execution that requests offensive collision, proper native cleanup must have occurred by the time that exact Hit execution actually ends or is replaced. If Gothic 3 already cleaned it, do nothing. If it did not, invoke the native cleanup Gothic 3 should have performed.

How the Hit ends is intentionally irrelevant to production cleanup unless evidence proves otherwise. Normal completion, block timeout, damage interruption, terrain interruption, skipped Recover, or another genuine replacement should become test cases for one rule rather than separate cleanup branches.

The exact flow models are kept separately in `docs/COLLISION_LIFECYCLE_MODELS.md` so coding sessions can inspect them directly without expanding this plan.

## Preferred System — Execution-Level Guard

**System 1 is preferred.**

1. Acquire a real attack-Hit execution using Gothic 3's native callback/action/phase semantics where available.
2. Capture the exact actual motion execution.
3. If the exact motion contains reserved collision markers, suppress native timed activation and let markers control activation/rearm timing.
4. If the motion is unmarked, leave Gothic 3's native activation behavior untouched.
5. If that execution requests offensive collision, remember the execution-level fact `collision requested`.
6. Follow the exact actual Hit execution rather than continuing to treat action/phase as lifetime authority.
7. When that Hit actually ends/replaces, determine whether Gothic 3 performed the proper native cleanup.
8. If cleanup already happened, do nothing.
9. If cleanup did not happen, invoke the native cleanup Gothic 3 should have performed.

A request counts even when the collision source was already `Item_Attack` (`7 -> 7`). We care that the execution requested offensive collision, not only whether a numerical group transition occurred.

Preferred minimal state, if engine research permits it:

```text
Execution X
    exact actual Hit execution
    collisionRequested = true/false
    nativeCleanupObserved = true/false
```

Preferred implementation is event-driven. The v0.20 Script `OnTick` probe is diagnostic and too coarse to become the production mechanism.

## Fallback System — Source-Aware Guard

**System 2 is a fallback, not a parallel implementation.**

Use per-source ownership only if research proves at least one of these:

- Gothic 3 has no usable attack-wide native cleanup operation;
- cleanup is genuinely source-specific;
- one physical source can clean successfully while another independently remains attack-active.

If required, associate the exact Hit execution with each physical source on which offensive collision was requested, including `7 -> 7`, and verify/repair those sources independently at execution end.

Do not implement this extra bookkeeping merely because v0.20 already has RIGHT/LEFT source masks.

## Marker Rule While the Hit Is Alive

Marker behavior is separate from end-of-Hit cleanup.

The marker commands define the complete desired offensive collision set:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

The conceptual operation is:

> Make the offensive collision state equal to the currently authored desired set.

This naturally covers LEFT -> RIGHT, RIGHT -> BOTH, BOTH -> LEFT, OFF, and other valid transitions without a matrix of previous-marker-specific rules.

`G3AB_COL_OFF` remains optional authored early shutoff inside a still-live Hit. It is not the general lifecycle safety mechanism.

If Gothic 3 exposes a safe native collision-only deactivation operation, prefer it for intra-Hit source-set changes. Do not assume a whole-attack finalization routine is safe inside a live Hit.

## Working Hypotheses

These remain hypotheses until the next research phase completes:

1. Offensive collision is intended to belong to a physical attack-Hit execution and is not intentionally carried beyond that execution into the next Hit.
2. The actual PrimaryFirst Hit execution can provide a more authoritative lifetime boundary than action/phase after acquisition.
3. Gothic 3 has a native cleanup operation or semantic path that should be reused rather than manually hard-coding `Item_Attack -> Item_Equipped`.
4. Native and marked attacks can share the same end-of-Hit cleanup guard; only their activation policy needs to differ.
5. Defensive block/parade behavior may or may not use special weapon/shield collision states and must be measured before "clean all offensive collision" is implemented broadly.
6. An event-driven motion-lifecycle hook should be lighter and more stable than Script `OnTick` polling if one can be identified.

## v0.20 Cleanup/Lifetime Scaffolding to Revisit

The following mechanisms are useful prototype safeguards but are **not presumed production architecture**. Do not remove them until the replacement is proven, but do not automatically preserve them in the next implementation.

1. `MarkerOwnedCollisionWindow` as lifetime owner.
2. `FindMatchingMarkerOwnedWindow(...)` strict source + animation + action + phase identity.
3. `MarkerWindowStillMatchesActorExecution(...)` using action/phase/state-time to infer lifetime.
4. `RetireMarkerOwnedSource(...)` as source-by-source lifetime retirement from `SetCollisionGroup` changes.
5. Action/phase as a continuing marker-time veto after ownership has already been acquired.
6. Any new block-timeout, Recover, Staff, Quick, Whirl, damage, or terrain-specific cleanup contingency.

### Keep Unless Separate Evidence Says Otherwise

These solve distinct authored-marker problems and are not currently targeted for removal:

- RIGHT/LEFT/BOTH source-explicit marker vocabulary;
- desired/exact-set switching within a live Hit;
- repeated source markers and `ClearTriggeredList()` rearm for later authored contacts;
- optional `G3AB_COL_OFF`;
- duplicate same-update marker suppression;
- authored-occurrence budgets that reject Gothic 3's replay/interleaving behavior;
- native callback suppression only for exact marked motions whose required sources can be resolved.

Execution identity may later simplify some of this bookkeeping, but cleanup simplification alone does not prove those mechanisms obsolete.

## Logger Decision

Do not simply expand every existing logger/prototype.

Current assessment is documented in `docs/COLLISION_LOGGER_PLAN.md`:

- keep `Script_CombatMoveLogger v0.4` as the proven combat-move/speed logger;
- keep `Script_FrameCollisionTest v0.20` as the current prototype/evidence source;
- prefer a focused standalone `Script_CollisionLifecycleLogger` for the next research phase;
- keep it observational and event-oriented;
- it must record offensive collision requests including `7 -> 7`, exact actual motion lifetime/end/replacement, corresponding native cleanup, and block/parade equipment state where needed.

Do not implement production cleanup in the diagnostic logger.

## Test Decision

The staged research sequence is documented in `docs/COLLISION_TEST_PLAN.md`.

Order:

1. validate that the new logger can express one normal lifecycle and one stale-collision lifecycle unambiguously;
2. test whether legitimate native collision ever survives one physical Hit into the next;
3. compare normal completion and several interruption causes against the same actual-motion boundary;
4. investigate block/parade/defensive collision behavior;
5. compare marked and native activation under the same end rule;
6. validate desired marker-set semantics;
7. choose System 1 or fall back to System 2 from evidence;
8. only then run the broad weapon/action/player/NPC regression matrix.

## Implementation Sequence After Research

Do not ask Work to invent the architecture while coding. When the research gates are complete:

1. provide Work with `SESSION_ENTRYPOINT.md`;
2. read `COLLISION_LIFECYCLE_PLAN.md`;
3. read `COLLISION_LIFECYCLE_MODELS.md`;
4. read the final logger/test findings relevant to the chosen system;
5. inspect `Script_FrameCollisionTest.cpp` and native/reference source;
6. challenge the design if engine/API evidence contradicts it;
7. if the design remains valid, implement the smallest version of the chosen rule;
8. remove or replace obsolete v0.20 cleanup/lifetime scaffolding rather than layering the new system over it;
9. preserve unrelated proven marker behavior;
10. build and retest before broadening.

If implementation reveals a conceptual contradiction, return that contradiction to research/design rather than silently adding compensating branches.
