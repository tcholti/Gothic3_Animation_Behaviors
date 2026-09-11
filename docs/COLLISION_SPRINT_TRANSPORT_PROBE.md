# Gothic 3 Animation Behaviors — SprintAttack Transport Observability Probe

**Status:** FROZEN DIAGNOSTIC-ONLY WORK CONTRACT  
**Date:** 2026-09-11  
**Scope:** one bounded read-only probe; no Sprint behavior implementation

## 1. Purpose

Resolve the one remaining transport fact that cannot be closed from the current static/runtime evidence:

> When Gothic invokes the existing `OnAI_PowerAttack` script callback for an execution that later has factual `gEAction_SprintAttack` / Action `9`, is Action `9` already factual at callback entry, or does the Power callback/native transport establish Action `9` only during/after the original callback?

This fact must be known before any first-class Sprint marker ownership can be designed, because raw8 authored FIST requires initial permission ownership before the first authored marker/native leak opportunity.

This task is observability only. It must not implement SprintAttack.

---

## 2. Existing evidence boundary

Current evidence already establishes:

```text
gEAction_SprintAttack = 9
observed actor = native Sabretooth
observed marker-time phase = 1
observed marker-time StatePosition = 1
observed source = Fist / gEUseType_Fist / raw8 / group0
observed motion = Sabretooth ... PowerAttack_Hit ...
C1 transport binding = _AI_PowerAttack
current marker result = REJECTED_UNSUPPORTED_HIT
```

The PowerAttack-named motion is not family authority. Factual action identity is authoritative.

Pinned SDK/source search exposes `gEAction_SprintAttack = 9` but no dedicated `OnAI_Sprint...` callback symbol. This absence supports, but by itself does not prove, Power callback transport.

The current `FrameCollisionMarkers::EvaluateAttackCallbackOwnership()` is intentionally family-factual: `OnAI_PowerAttack` evaluated as `AttackFamily_Power` is not eligible when the actor's factual action is `9`. Therefore current unsupported Sprint does not accidentally enter Power marker/raw8 ownership.

Stage-B CORE currently suppresses `LogAttackCallbackOwnership()` when `attackHitEligible == false`, so the existing Action-9 runtime log cannot tell us what action was visible at physical Power callback entry.

The tested Game binary generic combat loop also strongly supports raw8 Sprint using the same relevant native mechanism: the nearby special action branch is action `0x39`, not action `9`; the generic route then checks `SPU+0x164`, performs the `GetMaxTime(0)` / threshold / `GetPlayTime(0)` comparison at Game `+0x16E160..+0x16E190`, closes the latch at `+0x16E1A3`, and later reaches the native Fist damage path returning at `+0x16E348`. This remains static mechanism evidence until the Sprint transport boundary is closed.

Existing Demon 2H/raw3, Goblin 1H/raw2 and Ogre Axe/raw52 controls contain no Action-9 occurrence. Current evidence therefore does not establish equipped Sprint, but does not prove it impossible.

---

## 3. Exact frozen implementation responsibility

Modify diagnostic observability only in the existing diagnostic source path.

### A. Existing physical hook only

Use the already-installed `Hook_OnAI_PowerAttack` / `OnAI_PowerAttack_FrameCollisionTest` wrapper.

Do **not** add any new hook, callback target, RVA, or calling convention.

### B. Add one compact CORE transport record

Under `FRAME_COLLISION_DIAGNOSTICS`, add a compact logger dedicated to this temporary Sprint transport question.

For each physical `OnAI_PowerAttack` invocation, log at:

```text
Boundary=ENTRY
Boundary=AFTER_ORIGINAL
```

The record must contain at least:

```text
elapsed time
boundary
actor name
SPU factual action read from the already-established SPU+0x154 field
actor factual routine action
actor animation phase
current movement animation
```

The AFTER_ORIGINAL record must additionally include the native callback return value.

Suggested stable shape:

```text
CORE SPRINT_TRANSPORT ElapsedMs=... Boundary=ENTRY Actor=... SPUAction=... ActorAction=... Phase=... Motion=...
CORE SPRINT_TRANSPORT ElapsedMs=... Boundary=AFTER_ORIGINAL Actor=... SPUAction=... ActorAction=... Phase=... Motion=... NativeResult=...
```

Exact whitespace is not important; factual fields are.

### C. Preserve callback semantics exactly

The current order must remain semantically:

```text
INIT_SCRIPT_CALLBACK
-> evaluate existing Power marker ownership
-> if existing ownership suppresses native callback, return GETrue exactly as today
-> otherwise call original OnAI_PowerAttack exactly once
-> return the original result unchanged
```

The ENTRY diagnostic may observe before the existing ownership evaluation.

The AFTER_ORIGINAL diagnostic exists only on the path where the original callback was actually called.

Storing the original return in a local solely so it can be logged before returning is allowed.

### D. Reuse the established factual action source

Do not invent a second action offset or infer Sprint from the motion name.

Reuse the existing `GetCombatMoveFactualAction(gCScriptProcessingUnit const *)` / SPU `+0x154` factual action source. A forward declaration or non-semantic relocation of that existing helper is allowed if needed to make it available to the callback wrapper.

Actor action must remain the factual routine action (`PSRoutine::PropertyAction`), not a filename inference.

### E. Diagnostic source boundary

The new transport record must be mechanically absent from the behavior-only product through the existing diagnostic compile definition.

No new source file is required. Prefer the existing `CollisionDiagnostics.h/.cpp` + `EngineBridge.cpp` diagnostic path.

---

## 4. Explicit non-responsibilities

Do NOT:

```text
add AttackFamily_Sprint
accept Action 9 in FrameCollisionMarkers
add Sprint to Raw8FistCollision::IsSupportedFamily
write SPU+0x164 for Sprint
arm or consume a Sprint timing permission
change marker vocabulary
change StatePosition semantics
change C1 behavior
change equipped collision behavior
change Hack routing
add a Sprint-specific physical hook
alias Sprint to Power
add a Sabretooth/species/name special case
add raw55 behavior
add direct/custom damage
change Game hook RVAs or calling conventions
change the existing OnAI_PowerAttack native call count or return semantics
broaden into Goblin/Demon/Ogre testing
```

No diagnostic cleanup outside the exact new transport record is part of this task.

---

## 5. Required static audit

Before publication, verify:

```text
one existing OnAI_PowerAttack physical hook only
no new hook/RVA/calling-convention change
no AttackFamily enum change
no Sprint marker acceptance
no Raw8FistCollision behavior change
no SPU latch/timing write added
original OnAI_PowerAttack call count/return semantics preserved
new logging compiled only with FRAME_COLLISION_DIAGNOSTICS
git diff --check PASS
```

BUILD EXECUTION / BUILD TOOLING PROBING IS PROHIBITED in Work for this task.

---

## 6. Runtime decision table for Normal Chat

After local build/deploy, one short native-Sabretooth run that captures Action 9 is enough to classify transport.

### Result A — Action 9 already factual at ENTRY

Example:

```text
ENTRY SPUAction=9 ActorAction=9
```

Consequence:

```text
existing OnAI_PowerAttack physical hook is early enough to route a first-class Sprint family without a new physical hook
```

Normal Chat may then freeze a bounded first-class Sprint implementation, subject to the remaining source/mechanism evidence boundary.

### Result B — ENTRY is Power/other; AFTER_ORIGINAL becomes 9

Example:

```text
ENTRY SPUAction=2 ActorAction=2
AFTER_ORIGINAL SPUAction=9 ActorAction=9
```

Consequence:

```text
existing callback entry is too early to identify Sprint by factual action; do not route Sprint there blindly
```

Normal Chat must identify the next existing factual boundary that occurs early enough for raw8 initial-close ownership before implementation.

### Result C — SPU action and actor action disagree materially

Consequence:

```text
stop and investigate the disagreement before Sprint implementation
```

### Result D — no Action 9 captured

Consequence:

```text
no conclusion; repeat only the same bounded fixture until an Action-9 execution is observed
```

---

## 7. Stop condition

Work stops after source edit, static audit, commit and push.

Normal Chat stops the remote-only phase after independent source review of the probe. The next required step is then the User's local diagnostic build/deploy/run; do not infer the transport result without that runtime evidence.
