# Collision Lifecycle Plan

**Status:** Working design / research target, not yet implemented  
**Updated:** 2026-08-26

## Goal

Replace accumulated cleanup/interruption contingencies with the smallest authoritative lifecycle rule the engine evidence supports.

> For every real attack-Hit execution that requests offensive collision, proper native cleanup must have occurred by the time that exact Hit execution actually ends or is replaced. If Gothic 3 already cleaned it, do nothing. If it did not, invoke the native cleanup Gothic 3 should have performed.

How the Hit ends is intentionally irrelevant to production cleanup unless evidence proves otherwise. Normal completion, block timeout, damage interruption, terrain interruption, skipped Recover, or another genuine replacement should become test cases for one rule rather than separate cleanup branches.

## Preferred System — Execution-Level Native Cleanup Guard

**System 1 is preferred.**

```text
REAL ATTACK-HIT EXECUTION X BEGINS
        ↓
Capture the exact actual motion execution
        ↓
Does this execution contain our collision markers?
        ↓
        ┌───────────────────────┬───────────────────────┐
        │ MARKED                │ NATIVE                │
        │                       │                       │
        │ Suppress native       │ Leave Gothic 3's     │
        │ collision timing      │ collision behavior   │
        │                       │ completely untouched │
        │ Markers control       │                       │
        │ collision timing      │ Native code controls │
        │                       │ collision timing     │
        └───────────┬───────────┴───────────┬───────────┘
                    │                       │
                    └───────────┬───────────┘
                                ↓
             Did this Hit execution request
                  offensive collision?
                                ↓
                         NO → nothing
                                ↓
                         YES → remember:
                       "collision requested"
                                ↓
              Continue following the exact
                  actual Hit execution
                                ↓
           Hit finishes OR is genuinely replaced
           OR interrupted — reason does not matter
                                ↓
             Did Gothic 3 perform the proper
                    native attack cleanup?
                                ↓
                    ┌───────────┴───────────┐
                    │                       │
                   YES                     NO
                    │                       │
               DO NOTHING           INVOKE GOTHIC 3'S
                                    NATIVE CLEANUP
```

### Preferred implementation rule

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

## Fallback System — Source-Aware Cleanup Guard

**System 2 is a fallback, not a parallel implementation.**

Use per-source ownership only if research proves at least one of these:

- Gothic 3 has no usable attack-wide native cleanup operation;
- cleanup is genuinely source-specific;
- one physical source can clean successfully while another independently remains attack-active.

```text
REAL ATTACK-HIT EXECUTION X BEGINS
        ↓
Capture the exact actual motion execution
        ↓
Marked or native collision behaves
according to the same activation policy
described in System 1
        ↓
Observe offensive collision requests
during execution X
        ↓
Record which physical sources were requested

Example:
RIGHT requested Item_Attack → X owns RIGHT
LEFT requested Item_Attack  → X owns LEFT

A request counts even if:
7 → 7
        ↓
Continue following the exact
actual Hit execution
        ↓
Hit finishes / is replaced / interrupted
        ↓
Check each offensive source associated with X
        ↓
        RIGHT clean?          LEFT clean?
           ↓                     ↓
      YES → nothing         YES → nothing
      NO  → native          NO  → native
             source                 source
             cleanup                cleanup
```

The fallback preserves the same principle as System 1; it merely verifies cleanup at source level because the engine evidence would require it.

Do not implement this extra bookkeeping merely because v0.20 already has RIGHT/LEFT source masks.

## Marker Rule While the Hit Is Alive

Marker behavior is separate from end-of-Hit cleanup.

The marker commands define the complete desired offensive collision set:

```text
RIGHT = desired offensive collision set {RIGHT}
LEFT  = desired offensive collision set {LEFT}
BOTH  = desired offensive collision set {RIGHT, LEFT}
OFF   = desired offensive collision set {}
```

Examples:

```text
RIGHT → LEFT
{RIGHT} → {LEFT}
```

```text
BOTH → RIGHT
{RIGHT, LEFT} → {RIGHT}
```

```text
OFF
{}
```

The conceptual operation is:

> Make the offensive collision state equal to the currently authored desired set.

This naturally covers LEFT -> RIGHT, RIGHT -> BOTH, BOTH -> LEFT, OFF, and other valid transitions without a matrix of previous-marker-specific rules.

`G3AB_COL_OFF` remains optional authored early shutoff inside a still-live Hit. It is not the general lifecycle safety mechanism.

If Gothic 3 exposes a safe native collision-only deactivation operation, prefer it for intra-Hit source-set changes. Do not assume a whole-attack finalization routine is safe inside a live Hit.

## Two Governing Rules

```text
WHILE THE HIT IS ALIVE:
Markers define the desired offensive collision set.
```

```text
WHEN THE HIT IS OVER:
Offensive attack collision must be clean.
If Gothic 3 already cleaned it → do nothing.
If Gothic 3 failed → invoke the proper native cleanup.
```

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

## Research DLL / Diagnostics Decision

Collision behavior and collision-lifecycle diagnostics should remain in **one research DLL while they need overlapping Gothic 3 hooks**.

Do not create a second independent logger DLL that competes for the same hook addresses unless explicit hook-chaining safety is later proven.

Target structure:

```text
Main / Hook Bridge
    installs each engine hook once
        ├──> Collision Control
        └──> Collision Diagnostics
```

- Main / Hook Bridge owns hook installation and dispatch.
- `CollisionControl.cpp` owns collision behavior.
- `CollisionDiagnostics.cpp` owns observational logging only.
- shared headers/interfaces should contain only facts genuinely needed by both.
- collision behavior must not depend on diagnostics.

The first implementation step is therefore **modularization with v0.20 behavior parity**, not new cleanup behavior.

Detailed diagnostic/module plan: `docs/COLLISION_LOGGER_PLAN.md`.

`Script_CombatMoveLogger v0.4` remains a separate proven combat-move/speed tool and should not be expanded automatically into collision-lifecycle logging.

## Test Decision

The staged research sequence is documented in `docs/COLLISION_TEST_PLAN.md`.

Order:

1. modularize v0.20 and prove behavior/diagnostic parity;
2. add only the lifecycle diagnostics needed by the current questions;
3. validate that the redesigned diagnostics can express one normal lifecycle and one stale-collision lifecycle unambiguously;
4. test whether legitimate native collision ever survives one physical Hit into the next;
5. compare normal completion and several interruption causes against the same actual-motion boundary;
6. investigate block/parade/defensive collision behavior;
7. compare marked and native activation under the same end rule;
8. validate desired marker-set semantics;
9. choose System 1 or fall back to System 2 from evidence;
10. only then run the broad weapon/action/player/NPC regression matrix.

## Implementation Sequence

For the current coding phase:

1. read `docs/SESSION_ENTRYPOINT.md`;
2. follow `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
3. use this document as the collision architecture authority;
4. modularize the existing research DLL without changing v0.20 behavior;
5. keep every overlapping Gothic 3 hook owned once;
6. prove structural parity before adding new lifecycle diagnostics;
7. do not implement production cleanup yet.

After the research gates are complete:

1. choose System 1 or System 2 from evidence;
2. implement the smallest version of the chosen rule;
3. remove or replace obsolete v0.20 cleanup/lifetime scaffolding rather than layering the final system over it;
4. preserve unrelated proven marker behavior;
5. build and retest before broadening;
6. when stable, extract the production collision DLL without the diagnostic module.

If implementation reveals a conceptual contradiction, return that contradiction to research/design rather than silently adding compensating branches.

## Preference Order

1. **Preferred:** execution-level guard using Gothic 3's native attack cleanup.
2. **Fallback:** source-aware guard only if engine evidence requires independent source tracking/cleanup.
3. Avoid interruption-specific cleanup branches unless a real case is proven unable to follow either general model.
