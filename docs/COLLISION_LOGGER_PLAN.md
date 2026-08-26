# Collision Lifecycle Logger Plan

**Status:** Proposed diagnostic redesign / not yet implemented  
**Updated:** 2026-08-26

## Purpose

Design the smallest observational logger that can answer the current collision-lifecycle questions without turning the diagnostic tool into another complex subsystem.

The logger must measure the proposed architecture. It must not quietly become the architecture itself.

## Current Logger Assessment

### `tools/Script_CombatMoveLogger` v0.4

Current strengths:

- proven CombatMove hook;
- proven AnimationSpeedModifier hook;
- useful action/phase/current movement context;
- PrimaryFirst play-speed access is already proven;
- intentionally read-only.

Current limitation for this research:

- it is primarily a combat-move/speed logger;
- it does not observe `SetCollisionGroup` attack activation/cleanup requests;
- it does not identify actual PrimaryFirst motion lifetime/end/replacement;
- it is player-only;
- it does not correlate attacker and defender equipment during block/parade cases.

Conclusion: preserve v0.4 as a useful existing tool. Do not overload it automatically with the entire collision-lifecycle investigation.

### `prototypes/Script_FrameCollisionTest` v0.20 diagnostics

Current strengths:

- global `SetCollisionGroup` observation involving `Item_Attack`;
- marker activation/rearm logging;
- equipped LEFT/RIGHT identity diagnostics;
- read-only PrimaryFirst lifetime snapshot while a marker-owned window exists;
- proved action/phase can drift while the exact Hit motion survives.

Current limitations:

- lifetime observation is tied to marker-owned prototype state, so native/unmarked executions are not tracked as equivalent first-class lifecycles;
- Script `OnTick` sampling is too coarse for the intended production boundary and can miss exact ordering;
- behavior-control code and diagnostics are interwoven, which makes broad native tests harder to interpret;
- current lifetime state carries source mask/action/phase assumptions that the new architecture is explicitly questioning;
- it does not identify whether a higher-level native attack-cleanup routine exists; it only observes collision-group consequences;
- it is not designed around attacker/defender block/parade correlation.

Conclusion: v0.20 remains valuable evidence/prototype code, but should not simply be expanded indefinitely into the new general logger.

## Preferred Direction

Create a focused standalone diagnostic tool, provisionally named:

`tools/Script_CollisionLifecycleLogger`

Preserve `Script_CombatMoveLogger v0.4` and `Script_FrameCollisionTest v0.20` as historical/proven references.

The new logger should be observational only.

## Questions the Logger Must Answer

The logger exists to answer five questions:

1. Did a real attack-Hit execution request offensive collision?
2. What exact actual motion execution owned the time interval in which that request happened?
3. When did that exact motion execution actually end, restart, or get replaced?
4. Did Gothic 3 perform the corresponding native cleanup before/by that boundary?
5. During successful block/parade behavior, do attacker/defender weapons or shields enter any special collision state that changes our cleanup assumptions?

If a field does not help answer one of these questions, do not add it without a separate reason.

## Preferred Event Model

The logger should prefer event records over continuous full-state dumps.

Conceptual event types:

```text
ATTACK_HIT_ACQUIRED
OFFENSIVE_COLLISION_REQUESTED
NATIVE_CLEANUP_REQUESTED_OR_OBSERVED
PRIMARY_MOTION_ENDED_OR_REPLACED
PRIMARY_MOTION_RESTARTED
BLOCK/PARADE_RELEVANT_TRANSITION
```

Each event should include enough context to correlate it with one execution, but avoid treating diagnostic context as lifetime authority.

## Minimal Context Per Event

Preferred common fields:

- elapsed/high-resolution timestamp;
- actor identity/address;
- exact current movement animation;
- PrimaryFirst motion name if available;
- PrimaryFirst play time / max time / running state if available;
- current action and phase as context;
- event type.

For collision requests additionally record:

- changed entity identity/address;
- requested collision group;
- before group;
- after group;
- whether the entity matches actor LEFT/RIGHT equipped slot where resolvable;
- raw UseType where useful.

A request to `Item_Attack` counts even if the state is already `Item_Attack` (`7 -> 7`). The logger must record the request, not only state changes.

## Execution Identity

Do not use action/phase alone as the execution key.

The logger should correlate events with the exact actual PrimaryFirst Hit execution where possible. Research must determine the lightest stable identity/boundary signal, potentially using:

- motion instance identity if accessible;
- motion start/end/replacement callback/hook;
- play-time rollback/restart as supporting evidence for repeated same-name executions;
- exact motion filename only as part of identity, not sufficient by itself.

Until the native motion-lifecycle hook is located, any temporary sampling used for diagnosis must be explicitly marked provisional.

## Cleanup Observation

Preferred goal:

- hook/observe the actual native attack-cleanup operation if one exists;
- distinguish a true cleanup request from merely noticing that a collision group is no longer 7.

Fallback diagnostic:

- continue observing `SetCollisionGroup` requests and resulting groups;
- correlate them with the active Hit execution;
- determine whether cleanup is attack-wide or per-source from repeated tests/source inspection.

Do not hard-code `7 -> 5` as the definition of cleanup until research proves the correct native semantic operation/state for all relevant equipment transitions.

## Block / Parade Observation

For block tests, the logger should be able to observe both participants when relevant rather than being permanently player-only.

Needed evidence:

- attacker attack-collision request;
- defender right/left/shield collision-group requests/transitions;
- attacker action/motion reaction after successful block;
- defender Parade/ParadeStumble motion/action transition;
- whether any defensive item enters `Item_Attack` or another special group.

Do not assume visual weapon bounce means weapon-to-weapon physical collision.

## What Not to Add Yet

Do not add:

- production cleanup behavior;
- block-timeout-specific logic;
- Staff/Quick/Whirl-specific cleanup branches;
- per-source ownership tables unless a test specifically requires them;
- full per-frame actor/world scans;
- broad damage/health instrumentation unless collision-state evidence proves insufficient;
- duplicate copies of fields already available in a single authoritative event.

## Proposed Implementation Stages

### Stage L1 — Standalone observational skeleton

- separate logger DLL/tool;
- high-resolution timestamps;
- global offensive `SetCollisionGroup` request logging including `7 -> 7`;
- actor/equipped-slot association where resolvable;
- no behavior changes.

### Stage L2 — Exact motion-lifecycle observation

After source/SDK research identifies the best hook:

- log real PrimaryFirst Hit acquisition/start;
- log actual end/replacement/restart;
- correlate collision requests to that execution;
- avoid Script `OnTick` as the normal production-style diagnostic path if a direct event exists.

### Stage L3 — Native cleanup observation

- hook/log the native cleanup operation if identified;
- otherwise keep the narrow `SetCollisionGroup` fallback and document that cleanup identity remains inferred.

### Stage L4 — Block/parade correlation

- allow relevant attacker/defender actors to be tracked for controlled tests;
- add only the minimal equipment/state context necessary to answer whether block uses defensive collision states.

## Acceptance Criteria for the Logger

Before broad tests, the logger should demonstrate on a small known-good sequence that it can print an unambiguous timeline equivalent to:

```text
Execution X acquired
X requested offensive collision
X actual Hit ended/replaced
native cleanup observed before/by end
```

and on a known stale-collision reproduction:

```text
Execution Y acquired
Y requested offensive collision
Y actual Hit ended/replaced
no corresponding cleanup observed
collision remained attack-active
```

If the log requires extensive manual reconstruction from unrelated dumps to answer those questions, the logger design is still too indirect.
