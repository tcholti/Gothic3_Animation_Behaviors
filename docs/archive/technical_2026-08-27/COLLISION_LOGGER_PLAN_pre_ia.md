# Collision Lifecycle Logger Plan

**Status:** Proposed integrated diagnostic redesign / not yet implemented  
**Updated:** 2026-08-26

## Purpose

Design the smallest observational logger that can answer the current collision-lifecycle questions without creating a second competing hook owner or turning diagnostics into another complex subsystem.

The logger must measure the proposed architecture. It must not quietly become the architecture itself.

## Research, Diagnostic, and Release Roles

The current large research log is intentionally temporary instrumentation. It may be broad or verbose when a controlled experiment requires that visibility, but its cost must be justified by a concrete research question.

The finished collision behavior should have three clearly separated forms/responsibilities:

1. **Production/release behavior**
   - no research log output;
   - no diagnostic state required for behavior;
   - no polling or scanning retained merely because it was useful during investigation;
   - only the minimum event/state machinery required for correct collision behavior.

2. **Retained diagnostic build/tool**
   - preserve useful lifecycle/collision probes for future bug reports and controlled reproduction;
   - may contain richer logging than the release build;
   - should remain optional and removable without changing production behavior.

3. **General combat diagnostics**
   - after the collision system is complete, useful reusable observations may be selectively copied into `tools/Script_CombatMoveLogger` or a later diagnostic successor;
   - do not merge research probes into the combat logger automatically merely because they exist;
   - add only diagnostics that have continuing value outside the collision-development experiment.

Large logs also have an analysis/context cost. A probe that produces megabytes of unrelated actor/motion output can make both human review and model-assisted analysis harder even when runtime performance is acceptable. Prefer narrow event correlation whenever the research question allows it.

The desired final lifecycle style is **event/report driven rather than repeated polling** wherever Gothic 3 exposes a usable boundary event:

```text
Hit execution acquires a cleanup obligation
        ↓
relevant engine/callback event reports execution completion/replacement
        ↓
native cleanup observed?
   YES -> retire obligation
   NO  -> repair missing cleanup
```

Temporary polling is acceptable only as a comparator or fallback while proving the direct event path. It should not survive into production merely because it was useful for research.

## Runtime Ownership Decision

The collision behavior and lifecycle diagnostics should remain in **one research DLL while they need overlapping Gothic 3 hooks**.

Reason:

- `Script_FrameCollisionTest` already owns hooks such as `SetCollisionGroup`, attack callbacks, `StartEffect`, and diagnostic lifetime paths;
- a second DLL independently hooking the same engine function can create hook/load-order/chaining conflicts unless the hook framework and exact hook combination are explicitly proven safe;
- diagnostics should not become another owner competing with the system they are observing.

Therefore the earlier idea of a standalone `Script_CollisionLifecycleLogger.dll` is withdrawn as the default research architecture.

Use **one DLL / one owner per engine hook**, but split the source by responsibility so diagnostics can later be removed cleanly.

## Proposed Research-DLL Structure

The exact filenames may change during implementation, but the intended responsibility boundary is:

```text
Script_FrameCollisionTest.dll
│
├─ Main / Hook Bridge
│    - ScriptInit / shutdown
│    - installs each Gothic 3 hook once
│    - receives engine events
│    - forwards only the necessary event/context to behavior and diagnostics
│
├─ CollisionControl.cpp
│    - marker ownership / activation policy
│    - desired offensive collision-set behavior
│    - future execution-level cleanup guard after research proves it
│    - must not depend on diagnostics to function
│
└─ CollisionDiagnostics.cpp
     - observational logging only
     - lifecycle event correlation
     - block/parade diagnostic output
     - must never decide collision behavior
```

A small shared header/event model may be used when needed, but it should contain only facts both modules genuinely require.

### Dependency rule

Prefer:

```text
Engine Hook Bridge
      ├──> Collision Control
      └──> Collision Diagnostics
```

Avoid:

```text
Collision Control ──> Logger ──> behavior decision
```

Removing `CollisionDiagnostics.cpp` from the future build must not change collision behavior.

## Future Extraction Goal

When collision behavior is fully researched and validated:

1. keep the stable behavior module(s);
2. omit the diagnostic module(s);
3. create the production DLL/project, provisionally named something like `Script_FrameBasedCollision` or another final name chosen later;
4. preserve the same hook/behavior boundaries rather than rewriting the subsystem merely to remove logging;
5. retain a diagnostic build/tool separately for future troubleshooting;
6. review the diagnostic probes and selectively move only generally useful observations into the combat logger.

The research structure should therefore be designed around the future separation boundary from the beginning.

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

Conclusion: preserve v0.4 as a separate proven tool. Do not overload it automatically with the collision-lifecycle investigation.

### `prototypes/Script_FrameCollisionTest` v0.20 diagnostics

Current strengths:

- global `SetCollisionGroup` observation involving `Item_Attack`;
- marker activation/rearm logging;
- equipped LEFT/RIGHT identity diagnostics;
- read-only PrimaryFirst lifetime snapshot while a marker-owned window exists;
- proved action/phase can drift while the exact Hit motion survives.

Current limitations:

- current research output contains accumulated historical/prototype explanations that are useful only during development, not as runtime diagnostics;
- Step B1 global PrimaryFirst event logging is intentionally broad and can record unrelated actors/motions, producing very large logs;
- lifetime observation is tied to marker-owned prototype state, so native/unmarked executions are not tracked as equivalent first-class lifecycles;
- Script `OnTick` sampling is too coarse for the intended production boundary and can miss exact ordering;
- current lifetime state carries source mask/action/phase assumptions that the new architecture is explicitly questioning;
- it does not identify whether a higher-level native attack-cleanup routine exists; it only observes collision-group consequences;
- it is not designed around attacker/defender block/parade correlation.

Conclusion: keep the same research DLL/hook ownership, but continue moving toward **narrow event-driven diagnostics**. Broad global probes and the old `OnTick` comparator are temporary research machinery and should be removed once the direct lifecycle event chain is proven.

## Questions the Diagnostics Must Answer

The diagnostic module exists to answer five questions:

1. Did a real attack-Hit execution request offensive collision?
2. What exact actual motion execution owned the time interval in which that request happened?
3. When did that exact motion execution actually end, restart, or get replaced?
4. Did Gothic 3 perform the corresponding native cleanup before/by that boundary?
5. During successful block/parade behavior, do attacker/defender weapons or shields enter any special collision state that changes our cleanup assumptions?

If a field does not help answer one of these questions, do not add it without a separate reason.

## Preferred Event Model

The diagnostic module should prefer event records over continuous full-state dumps.

Conceptual event types:

```text
ATTACK_HIT_ACQUIRED
OFFENSIVE_COLLISION_REQUESTED
NATIVE_CLEANUP_REQUESTED_OR_OBSERVED
PRIMARY_MOTION_ENDED_OR_REPLACED
PRIMARY_MOTION_RESTARTED
BLOCK/PARADE_RELEVANT_TRANSITION
```

The hook bridge should capture an engine event once. Behavior and diagnostics may consume the same factual event without installing competing hooks for the same purpose.

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

A request to `Item_Attack` counts even if the state is already `Item_Attack` (`7 -> 7`). Diagnostics must record the request, not only state changes.

## Execution Identity

Do not use action/phase alone as the execution key.

Diagnostics should correlate events with the exact actual PrimaryFirst Hit execution where possible. Research must determine the lightest stable identity/boundary signal, potentially using:

- motion instance identity if accessible;
- motion start/end/replacement callback/hook;
- play-time rollback/restart as supporting evidence for repeated same-name executions;
- exact motion filename only as part of identity, not sufficient by itself.

Until the native motion-lifecycle hook is located, any temporary sampling used for diagnosis must be explicitly marked provisional.

## Cleanup Observation

Preferred goal:

- hook/observe the actual native attack-cleanup operation if one exists;
- distinguish a true cleanup request from merely noticing that a collision group is no longer 7.

If this cleanup operation is already needed by collision behavior, the research DLL should install/own that hook once and expose its occurrence to diagnostics rather than creating a second diagnostic hook on the same address.

Fallback diagnostic:

- continue observing `SetCollisionGroup` requests and resulting groups;
- correlate them with the active Hit execution;
- determine whether cleanup is attack-wide or per-source from repeated tests/source inspection.

Do not hard-code `7 -> 5` as the definition of cleanup until research proves the correct native semantic operation/state for all relevant equipment transitions.

## Block / Parade Observation

For block tests, diagnostics should be able to observe both participants when relevant rather than being permanently player-only.

Needed evidence:

- attacker attack-collision request;
- defender right/left/shield collision-group requests/transitions;
- attacker action/motion reaction after successful block;
- defender Parade/ParadeStumble motion/action transition;
- whether any defensive item enters `Item_Attack` or another special group.

Do not assume visual weapon bounce means weapon-to-weapon physical collision.

## What Not to Add Yet

Do not add:

- production cleanup behavior merely for logging;
- block-timeout-specific logic;
- Staff/Quick/Whirl-specific cleanup branches;
- per-source ownership tables unless a test specifically requires them;
- full per-frame actor/world scans;
- broad damage/health instrumentation unless collision-state evidence proves insufficient;
- duplicate hooks when an existing hook can forward the required event to diagnostics;
- duplicate copies of fields already available in a single authoritative event.

## Proposed Implementation Stages

### Stage L1 — Modularize the existing research DLL

- keep `Script_FrameCollisionTest` as one DLL;
- split hook/bootstrap, collision behavior, and diagnostics into separate source modules;
- install every overlapping engine hook only once;
- preserve current v0.20 behavior while moving code so the structural change itself does not change semantics;
- confirm build/runtime parity before adding new diagnostic behavior.

### Stage L2 — Lifecycle diagnostic events

- add high-resolution event output around existing collision requests, including `7 -> 7`;
- make native/unmarked and marked attack executions observable as equivalent lifecycle candidates;
- keep diagnostics read-only.

### Stage L3 — Exact motion-lifecycle observation

After source/SDK research identifies the best hook:

- log real PrimaryFirst Hit acquisition/start;
- log actual end/replacement/restart;
- correlate collision requests to that execution;
- avoid Script `OnTick` as the normal production-style diagnostic path if a direct event exists.

### Stage L4 — Native cleanup observation

- hook/log the native cleanup operation if identified;
- reuse the shared research-DLL hook if collision behavior later needs the same operation;
- otherwise keep the narrow `SetCollisionGroup` fallback and document that cleanup identity remains inferred.

### Stage L5 — Block/parade correlation

- allow relevant attacker/defender actors to be tracked for controlled tests;
- add only the minimal equipment/state context necessary to answer whether block uses defensive collision states.

## Acceptance Criteria for the Modular Research DLL

Before broad tests:

1. removing/disabling the diagnostic module must not alter collision behavior;
2. collision behavior must not depend on log output or diagnostic state;
3. each low-level engine hook needed by both responsibilities has one authoritative installation/owner;
4. a small known-good sequence must produce an unambiguous timeline equivalent to:

```text
Execution X acquired
X requested offensive collision
native cleanup observed
X actual Hit ended/replaced
```

5. a known stale-collision reproduction should be expressible as:

```text
Execution Y acquired
Y requested offensive collision
Y actual Hit ended/replaced
no corresponding cleanup observed
collision remained attack-active
```

If the log requires extensive manual reconstruction from unrelated dumps to answer those questions, the diagnostic design is still too indirect.
