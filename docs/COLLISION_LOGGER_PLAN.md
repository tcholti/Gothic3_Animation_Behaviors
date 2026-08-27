# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-08-27

## Purpose

Define the smallest observational instrumentation needed to answer collision-lifecycle questions without turning diagnostics into a second behavior/lifecycle system.

The logger measures the architecture. It does not define it.

Detailed probe history is preserved through the evidence ledgers, raw logs, and the pre-information-architecture snapshot:

`docs/archive/technical_2026-08-27/COLLISION_LOGGER_PLAN_pre_ia.md`

---

## 1. Three Roles

### Production/release behavior

- no research log dependency;
- no diagnostic state required for correctness;
- no polling retained merely because it helped investigation;
- only the minimum event/state machinery required by the proven design.

### Retained diagnostic build/tool

- preserves useful lifecycle/collision probes for controlled reproduction and future bug reports;
- may be more verbose than release behavior;
- must remain removable without changing behavior.

### General combat diagnostics

`tools/Script_CombatMoveLogger` remains a separate proven combat-move/speed tool. Only observations with continuing general value should later be copied there.

Do not merge every temporary collision probe into the general logger.

---

## 2. One Hook Owner

While collision behavior and diagnostics need overlapping Gothic hooks, keep one research DLL with one owner per engine hook.

Current responsibility boundary:

```text
Script_FrameCollisionTest.dll
│
├─ Main / Hook Bridge
│    installs/owns Gothic hooks once
│    captures factual engine events
│
├─ CollisionControl
│    marker/source behavior
│    future lifecycle behavior after proof
│
└─ CollisionDiagnostics
     observation/logging only
```

Dependency rule:

```text
Hook Bridge
   ├──> Collision Control
   └──> Collision Diagnostics
```

Avoid diagnostic state feeding behavior decisions.

---

## 3. Diagnostic Questions

Every retained field/probe should answer at least one of these:

1. Did a real attack-Hit execution request offensive collision?
2. What exact actual motion execution owned that request?
3. When did that exact Hit end, restart, or get replaced?
4. Did Gothic perform the corresponding legitimate cleanup?
5. What native/script execution context surrounded the end/replacement and cleanup opportunity?
6. If block/parade semantics later matter, did defender equipment enter a collision state that changes cleanup assumptions?

If a field does not help answer a current/reusable diagnostic question, do not add it casually.

---

## 4. Preferred Event Model

Prefer narrow event records over continuous state dumps.

Conceptual events:

```text
ATTACK_HIT_ACQUIRED
OFFENSIVE_COLLISION_REQUESTED
NATIVE_CLEANUP_OBSERVED
PRIMARY_HIT_REPLACED_OR_RESTARTED
MARKER_COMMAND_ACCEPTED / REJECTED
BLOCK_OR_REACTION_TRANSITION   (only when specifically needed)
```

One engine hook may feed both behavior and diagnostics, but the factual event should be captured once.

---

## 5. Common Event Context

Useful shared fields when available:

- high-resolution elapsed time;
- actor identity/address;
- exact PrimaryFirst motion name;
- motion play time / max time / running state;
- current movement animation;
- native action and phase **as context**;
- event type.

Collision-request fields:

- changed source entity/address;
- left/right equipped-slot match;
- raw UseType when useful;
- requested group;
- group before/after;
- whether the request is `Item_Attack` even if it is `7 -> 7`.

Do not treat action/phase or filename alone as the continuing physical-execution key after exact Hit acquisition.

---

## 6. Current Probe Inventory

### Existing `SetCollisionGroup` observation

Purpose:

- record offensive requests and cleanup requests/consequences;
- identify exact equipped source;
- preserve B4/B5 native cleanup call-site/stack evidence.

The B4/B5 special record is gated to exact tested player-equipped `7 -> 5` cleanup and remains diagnostic-only.

### Existing type-0 `PlayMotion` observation

Purpose:

- observe PrimaryFirst acquisition/replacement with immediate timing;
- compare before/after motion snapshots;
- support exact replacement/restart detection.

B1 proved the event is earlier and more precise than the old Script `OnTick` comparator.

### B6 replacement-stack probe — current active diagnostic

The B6 probe reuses the existing player/type-0 `PlayMotion` hook.

Rules:

1. while an outgoing attack-Hit PrimaryFirst exists, capture pre-call stack/context;
2. call original `PlayMotion` exactly once and unchanged;
3. use existing before/after PrimaryFirst evidence to prove an actual replacement/restart;
4. emit `HIT REPLACEMENT STACK` only after replacement/restart is demonstrated;
5. keep the opaque incoming motion descriptor opaque; its raw address may be logged, but no guessed layout is read;
6. add no persistent lifecycle ownership state and no cleanup behavior.

Current purpose:

> Compare clean Hit -> Recover, legitimate damage/reaction, and bad block-skip direct replacement stacks to determine whether a useful shared SPU / `ProcessScript()` context surrounds the replacement event.

### B3 StartRecover probe

Retain as historical/supporting diagnostic reference, but it is not the current lifecycle boundary: Step B3 proved it returns before native cleanup and can be bypassed.

### Old Script `OnTick` lifetime comparator

Retain only while it has comparison value. It is too coarse for production-style lifetime authority and should not survive merely because it already exists.

---

## 7. Cleanup Observation Semantics

Do not define cleanup as “the group is currently not 7.”

Prefer observing the legitimate cleanup request/operation for the exact owned offensive source/execution.

Current research uses `SetCollisionGroup` request + before/after state because that path is directly observable and has mapped native call sites.

A future production guard may reuse native cleanup semantics more directly if a suitable operation is proven.

Keep attack-wide vs source-specific cleanup an evidence question; do not create per-source lifecycle tables without a demonstrated need.

---

## 8. Execution Identity

Do not use action/phase alone as an execution key.

Desired identity should be based on the exact actual PrimaryFirst Hit execution, using the lightest stable facts the engine exposes. Supporting facts can include:

- motion instance identity if safely accessible;
- exact motion resource/name;
- replacement/restart event;
- play-time rollback for repeated same-name executions.

Filename identity is useful but not sufficient by itself to define behavioral ownership.

---

## 9. Block / Parade Diagnostics

Do not instrument defender collision broadly until a concrete architecture question requires it.

If the final cleanup design risks disturbing defensive collision state, the minimum controlled block test should observe:

- attacker offensive source request/cleanup;
- defender weapon/shield group requests;
- attacker reaction transition;
- defender Parade/ParadeStumble transition.

Visible weapon bounce is not sufficient evidence of weapon-to-weapon physical collision.

---

## 10. What Not to Add Without a New Question

Do not add:

- production cleanup merely to make logs cleaner;
- block-timeout/Staff/Quick/Whirl-specific repair logging branches;
- broad per-frame actor/world scans;
- duplicate hooks when the current owner can forward the factual event;
- full damage/health instrumentation unless source/group evidence cannot answer a specific test;
- a second lifecycle classifier inside diagnostics;
- guessed binary layouts when an SDK-supported or raw opaque representation is sufficient.

---

## 11. B6 Acceptance Criteria

Before using B6 evidence architecturally:

1. DLL builds and loads;
2. `CaptureStackBackTrace`/module resolution returns interpretable frames;
3. clean Hit -> Recover replacement emits a confirmed replacement record;
4. legitimate damage/reaction replacement emits a confirmed replacement record;
5. bad block-skip direct replacement emits a confirmed replacement record while native cleanup is absent;
6. B4/B5 cleanup records remain unchanged and can be correlated by time;
7. no collision/marker behavior changes are introduced by the diagnostic.

If the stack cannot answer the current boundary question, refine only the observation needed for that question.

---

## 12. Release Extraction Rule

When collision behavior is stable:

1. keep the production behavior modules and required hook ownership;
2. omit verbose research diagnostics from the release build;
3. retain a diagnostic build/tool for future controlled reproduction;
4. selectively migrate only generally useful observations to the combat logger;
5. preserve raw logs/evidence IDs so removed instrumentation does not erase what it taught us.
