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
3. What CombatMove/routine/instruction bookkeeping surrounded acquisition, activation and terminal handling?
4. When did that exact Hit end, restart, or get replaced?
5. Did Gothic perform the corresponding legitimate cleanup?
6. What differs structurally between clean completion, legitimate reaction and bad skip?
7. If block/parade semantics later matter, did defender equipment enter a collision state that changes cleanup assumptions?

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
COMBATMOVE_BOUNDARY_OBSERVED
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
- Routine StateTime / StatePosition when exposed through supported APIs;
- event type.

Collision-request fields:

- changed source entity/address;
- left/right equipped-slot match;
- raw UseType when useful;
- requested group;
- group before/after;
- whether the request is `Item_Attack` even if it is `7 -> 7`.

Do not treat action/phase, StateTime/StatePosition, or filename alone as the continuing physical-execution key after exact Hit acquisition.

---

## 6. Current Probe Inventory

### Existing `SetCollisionGroup` observation

Purpose:

- record offensive requests and cleanup requests/consequences;
- identify exact equipped source;
- preserve B4/B5 native cleanup call-site/stack evidence.

Current source captures a short stack for exact tested player-equipped `7 -> 5` cleanup. It already logs factual context for offensive requests, including `5 -> 7` and `7 -> 7`, but does **not** yet capture their full caller stacks.

B7 may extend this **same existing hook** to capture offensive-request stacks if static reconstruction leaves the timer/callback activation path ambiguous. That is preferred over adding another Gothic hook merely to observe activation.

### Existing type-0 `PlayMotion` observation

Purpose:

- observe PrimaryFirst acquisition/replacement with immediate timing;
- compare before/after motion snapshots;
- support exact direct replacement/restart detection when the outgoing Primary remains present at PlayMotion entry;
- retain the factual ungated empty-Primary successor stack introduced for B6-C3.

B1 proved the event is earlier and more precise than the old Script `OnTick` comparator.

### Existing type-0 `StopMotion` observation

Purpose:

- observe explicit PrimaryFirst stop requests and their immediate before/after snapshots;
- retain supporting timing context.

EV-174/EV-175 proved the clean Hit can already be absent at StopMotion-hook entry. StopMotion is therefore a nearby factual request, **not a proven removal event**.

### Existing StartRecover-BEGIN stack probe

Retain as a clean-path factual reference.

EV-176 established:

```text
diagnostic
→ sAICombatMoveInstr
→ ProcessScript()
```

while the outgoing Hit was still Primary and the weapon still group 7.

StartRecover is not a production boundary: it is too early and bad skips can bypass it.

### B6 empty-Primary successor stack — retained, no longer the current gate

B6-C3 successfully captured factual Stumble/KnockDown successors. EV-179 establishes legitimate reaction successor installation inside reaction Script_Game/ScriptAdmin context.

B6-D then captured armed bad Whirl replacement to Ambient with an observed stack containing only:

```text
diagnostic
→ Game +0xD9CB3
```

while the weapon remained group 7. EV-180/EV-181 therefore reject the earlier replacement-triggered deferred-ProcessScript candidate in its present form.

Keep the B6 probe available for reproduction/comparison, but do not keep refining it simply to force all paths into one script-context model.

### Old Script `OnTick` lifetime comparator

Retain only while it has comparison value. It is too coarse for production-style lifetime authority and should not survive merely because it already exists.

---

## 7. Current Diagnostic Question — B7 Bookkeeping / Activation Path

Before adding another runtime probe, statically reconstruct the smallest authoritative control flow around:

- `sAICombatMoveStart`;
- `sAICombatMoveItlLoop`;
- `sAICombatMoveInstr` and exposed active instruction/callback state;
- Routine StateTime / StatePosition progression/reset;
- action-specific continuation after CombatMove;
- reaction state/reset path leading to `Script_Game +0x24AFF`.

If one exact fact remains missing, prefer the smallest existing-hook extension.

### Likely bounded B7 runtime extension

Use the current `SetCollisionGroup` hook to stack-capture actual player equipped-source offensive requests:

```text
5 -> 7
7 -> 7
```

Why include `7 -> 7`:

EV-181 proved a broken Whirl can leave the weapon stale at 7, and the next independent Normal execution can make a real offensive request while the numeric group remains 7. An activation diagnostic that watches only 5 -> 7 would miss that execution's collision obligation.

Desired factual record:

- source/address/slot;
- requested/before/after group;
- action/phase;
- StateTime;
- StatePosition;
- current movement;
- caller module/RVA;
- short stack.

No persistent diagnostic state is required merely to capture this event.

Do not add:

- a new attack-family classifier;
- successor-name gating;
- family-specific cleanup logic;
- a ProcessScript behavior hook;
- polling/timers/per-frame scans;
- guessed layouts.

---

## 8. Cleanup Observation Semantics

Do not define cleanup as “the group is currently not 7.”

Prefer observing the legitimate cleanup request/operation for the exact owned offensive source/execution.

Current research uses `SetCollisionGroup` request + before/after state because that path is directly observable and has mapped native call sites.

A future production guard may reuse native cleanup semantics more directly if a suitable operation is proven.

Keep attack-wide vs source-specific cleanup an evidence question; do not create per-source lifecycle tables without a demonstrated need.

---

## 9. Execution Identity

Do not use action/phase alone as an execution key.

Desired identity should be based on the exact actual PrimaryFirst Hit execution, using the lightest stable facts the engine exposes. Supporting facts can include:

- motion instance identity if safely accessible;
- exact motion resource/name;
- stop/replacement/restart event;
- play-time rollback for repeated same-name executions;
- offensive-request observation tied to the execution.

Filename identity is useful but not sufficient by itself to define behavioral ownership.

B7 may reveal native instruction/routine bookkeeping that provides a better exact-execution boundary; do not assume that result in advance.

---

## 10. Block / Parade Diagnostics

Do not instrument defender collision broadly until a concrete architecture question requires it.

If the final cleanup design risks disturbing defensive collision state, the minimum controlled block test should observe:

- attacker offensive source request/cleanup;
- defender weapon/shield group requests;
- attacker reaction transition;
- defender Parade/ParadeStumble transition.

Visible weapon bounce is not sufficient evidence of weapon-to-weapon physical collision.

---

## 11. What Not to Add Without a New Question

Do not add:

- production cleanup merely to make logs cleaner;
- block-timeout/Staff/Quick/Whirl-specific repair logging branches;
- broad per-frame actor/world scans;
- duplicate hooks when the current owner can forward the factual event;
- full damage/health instrumentation unless source/group evidence cannot answer a specific test;
- a second lifecycle classifier inside diagnostics;
- guessed binary layouts when an SDK-supported or raw opaque representation is sufficient;
- repeated B6 probe refinements after its architecture question has already been answered negatively.

---

## 12. B7 Acceptance Criteria for Any New Diagnostic

Before adding B7 runtime instrumentation:

1. static/source inspection must identify the exact missing factual question;
2. reuse an existing hook when it already observes the relevant event;
3. capture only factual caller/context data needed for the comparison;
4. preserve original behavior exactly once and unchanged;
5. no diagnostic state may feed collision/marker behavior;
6. compare clean Normal/Quick/Whirl, legitimate interruption, and bad Whirl as lifecycle mechanisms rather than production branch candidates;
7. if a diagnostic cannot distinguish the bookkeeping/control-flow question, revise the observation rather than infer from absence.

---

## 13. Release Extraction Rule

When collision behavior is stable:

1. keep the production behavior modules and required hook ownership;
2. omit verbose research diagnostics from the release build;
3. retain a diagnostic build/tool for future controlled reproduction;
4. selectively migrate only generally useful observations to the combat logger;
5. preserve raw logs/evidence IDs so removed instrumentation does not erase what it taught us.
