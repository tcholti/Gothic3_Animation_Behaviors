# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-08-28

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
PRIMARY_HIT_DISAPPEARED
PRIMARY_HIT_STOP_REQUESTED
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
- support exact direct replacement/restart detection when the outgoing Primary remains present at PlayMotion entry.

B1 proved the event is earlier and more precise than the old Script `OnTick` comparator.

### Existing type-0 `StopMotion` observation

Purpose:

- observe explicit PrimaryFirst stop requests and their immediate before/after snapshots;
- provide caller timing/context when the stop request occurs;
- support B6 only on paths where the outgoing Hit is still observable at StopMotion entry, or where another independent factual context can correlate that StopMotion with the just-observed Hit transition.

EV-174/EV-175 corrected the earlier assumption that this hook necessarily preserves the outgoing motion before Gothic removes it. In three clean 2H Normal transitions, `StartRecover BEGIN` still saw the Hit Primary, but the PrimaryFirst snapshot was already empty by entry to the StopMotion hook.

Therefore the StopMotion call is currently a nearby factual request, **not a proven removal event**.

### B6 StartRecover / replacement / empty-Primary probes — current active diagnostic

B6 uses only hooks already owned by `Script_FrameCollisionTest`. No new Gothic hook is justified yet.

The observation sequence has now produced two important diagnostic limits:

1. EV-174/EV-175: the clean-path StopMotion before-snapshot is already empty, so a stop-stack gate requiring a visible outgoing Hit cannot capture clean disappearance;
2. EV-177/EV-178: legitimate reaction cleanup is followed by empty-Primary StopMotion and reaction PlayMotion, but both the direct-replacement gate and the first empty-Primary refinement miss the reaction successor. The latter was gated by `CollisionControl::IsAttackHit(actor, AttackFamily_Normal)` and instead fired on fresh Normal `Attack_Hit` installations from empty Primary. By the time Stumble/KnockDown is requested, the old Normal semantic gate has expired.

Current rules:

1. retain the existing direct PlayMotion replacement-stack probe unchanged for paths where the outgoing attack-Hit remains visible at PlayMotion entry and before/after evidence proves direct replacement/restart;
2. retain the existing StopMotion before/after record unchanged and do not claim that StopMotion removed an outgoing Hit when its own before-snapshot is already empty;
3. retain the StartRecover-BEGIN stack probe as the established clean-path caller-context observation; EV-176 already proves the tested clean path enters through `sAICombatMoveInstr -> ProcessScript()`;
4. replace/refine only the B6-C empty-Primary correlation branch so that its **pre-original capture gate** requires factual player/type-0 PlayMotion plus an available Primary snapshot with no motion instance — not old attack family/action/phase, StateTime, StatePosition, collision group, successor name or reaction classification;
5. capture the short caller stack and factual pre-original context before calling original PlayMotion;
6. call original PlayMotion exactly once with unchanged arguments;
7. emit the empty-Primary diagnostic record only after original returns and an actual successor Primary motion instance is installed;
8. log the installed successor motion name factually so the controlled test can identify Stumble/KnockDown **post hoc**; the source must not classify the successor as a reaction or use its name as a capture gate;
9. accept that the broader diagnostic will also log unrelated empty-Primary player/type-0 successor installations during the short controlled run; offline correlation, not source logic, separates the target case;
10. keep opaque motion descriptors opaque; raw addresses may be logged, but no guessed layout is read;
11. add no production cleanup, lifecycle ownership/pending-finalization state, persistent diagnostic state, polling, timer, per-frame scan, cache, family-specific repair rule, reaction classifier or fallback behavior merely to make B6 observable.

Current purpose:

> Capture the actual legitimate reaction successor caller stack without relying on semantic state that has already been reset, then compare that factual caller/SPU context with EV-176's clean `sAICombatMoveInstr -> ProcessScript()` context and later the B6-D bad direct-replacement context.

The broader empty-Primary capture is diagnostic instrumentation only. It is **not** a claim that every empty-Primary PlayMotion is an attack-lifecycle boundary.

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
- stop/replacement/restart event;
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

1. DLL builds and loads in the isolated authoritative live script environment;
2. `CaptureStackBackTrace`/module resolution returns interpretable frames for the relevant observed boundary;
3. clean Hit -> Recover reconstructs `StartRecover BEGIN` with Hit still Primary, the subsequent PrimaryFirst disappearance/StopMotion context, successor Recover PlayMotion, and later native cleanup without falsely assigning disappearance to StopMotion;
4. legitimate damage/reaction correlates its established `+0x24AFF` cleanup and empty-Primary transition with an **actual captured caller stack for the installed Stumble/KnockDown successor**, identified post hoc from the factual successor record rather than a reaction-specific source gate;
5. bad block-skip direct replacement emits the existing confirmed direct PlayMotion replacement stack or another supported factual teardown/disappearance record while native cleanup is absent;
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