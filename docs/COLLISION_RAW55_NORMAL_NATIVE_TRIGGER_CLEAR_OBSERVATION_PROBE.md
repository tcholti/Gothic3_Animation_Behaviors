# Gothic 3 Animation Behaviors — RAW55 Normal Native Trigger-Clear Observation Probe

**Status:** FROZEN DIAGNOSTIC OBSERVATION CONTRACT  
**Date:** 2026-09-16  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Identify whether either public `eCTrigger_PS::ClearTriggeredList` API is the native operation that resets the exact RIGHT PhysicalFist/raw55 trigger bookkeeping during the proven Normal `StatePosition 0 -> 1` callback transition.

EV-289 proves the reset itself:

```text
marker-1 authored rearm
-> first ONDAMAGE
-> PC_Hero enters exact RIGHT EntitiesVisited
-> PC_Hero is still present immediately before EV-288 native 7 -> 7 suppression
-> native 7 -> 7 setter remains suppressed
-> same original _AI_Attack invocation advances SP0 -> 1
-> exact RIGHT visited arrays are now empty
-> marker 2 arrives later with PC_Hero already absent
-> second ONDAMAGE can occur and PC_Hero is inserted again
```

`ResetOnUntouch=0` throughout the decisive sequence. Marker 2 performs no Normal repeat intervention. Therefore neither marker 2, the suppressed group setter, nor observed ResetOnUntouch behavior explains the reset.

This probe observes exact public trigger-clear calls only. It must not suppress, replace, add, or redirect any clear operation.

---

## Static anchors

Tested binary/source evidence establishes:

```text
Script_Game.dll imports:
    PSTouchDamage::ClearTriggeredList()

Script.dll:
    PSTouchDamage::ClearTriggeredList() = Script + 0x13720
```

The tested Script wrapper is a thin wrapper that resolves the underlying engine property set and tail-jumps to the engine clear implementation.

Tested Engine exports:

```text
eCTrigger_PS::ClearTriggeredList()          Engine + 0x7DDA0
eCTrigger_PS::ClearTriggeredList(eCEntity*) Engine + 0x7DDF0
```

These RVAs are build-specific and are authorized only for the current tested diagnostic binary environment. Reuse the project's existing RVA helpers and tested hook transport conventions.

---

## Single Question

During the exact EV-289 Normal execution, after the marker-1 authored rearm has been established and before/during the native `SP0 -> 1` transition:

> Does Gothic call either exact public `eCTrigger_PS::ClearTriggeredList` overload on the exact current RIGHT PhysicalFist/raw55 TouchDamage trigger, and if so, does that call factually remove the prior `PC_Hero` visited state?

The answer must come from direct call observation, not from another inferred timing/state correlation.

---

## Existing environment to preserve

Preserve the full EV-289 diagnostic environment unchanged:

```text
Normal frame-1 SP0 FIST
-> exact RIGHT raw55 5 -> 7
-> marker-owned exact RIGHT ClearTriggeredList once
-> first damage opportunity

existing EV-288 one-shot native exact RIGHT 7 -> 7 suppression
-> original _AI_Attack callback remains enabled
-> native SP0 -> 1 progression remains enabled

existing EV-289 read-only trigger-state snapshots
frame-15 FIST remains observational only
native final cleanup remains untouched
```

Do not remove the existing setter suppression. It is part of the causal control proving that any observed native clear is independent of the `7 -> 7` group setter.

---

## Hook ownership and transport

`EngineBridge` remains the sole physical hook owner.

Add diagnostics-only observation hooks for exactly:

```text
Engine + 0x7DDA0  eCTrigger_PS::ClearTriggeredList()
Engine + 0x7DDF0  eCTrigger_PS::ClearTriggeredList(eCEntity*)
```

Use the already-proven explicit per-invocation `.ThisCall()` transport pattern. Do not use shared implicit `GetSelf` state for these hooks.

The bridge must:

```text
capture the actual eCTrigger_PS * invocation identity
capture the actual entity argument for the entity-specific overload
capture the call-site return address before delegating
pass only those factual transport values to PhysicalFistProbe
call the original function exactly once
return normally
```

The bridge does not own eligibility, Normal-family policy, C1 matching, source resolution, interpretation, or logging policy.

These hooks exist only under `FRAME_COLLISION_DIAGNOSTICS`; they must not enter the diagnostics-free behavior target or production architecture.

---

## PhysicalFistProbe eligibility

`PhysicalFistProbe` owns all filtering and observation semantics.

A clear-call record is relevant only when the invoked `eCTrigger_PS *` is factually the TouchDamage property set of the exact current RIGHT source belonging to the current Normal pre-state intervention.

Require as much factual identity as is safely available at the invocation:

```text
current actor identity from stored NormalPreStateFistIntervention
valid current C1 generation
same actor as stored intervention
same C1 generation as stored intervention
same exact current equipped RIGHT source
RIGHT UseType == gEUseType_PhysicalFist / raw55
invoked eCTrigger_PS * == exact RIGHT TouchDamage engine property-set pointer
Action == gEAction_Attack / 1
Normal Hit eligible
```

Do not use species, actor name, animation filename/prefix, elapsed wallclock, or guessed timer thresholds as policy.

### Marker-owned control call

The known frame-1 marker-owned `ClearTriggeredList()` may occur before `preStateRearmProven` becomes true. It is useful as a transport/control observation and may be logged if the exact intervention identity already exists.

Record factual `PreStateRearmProven=0/1` rather than excluding the known marker-owned call solely because the proof flag has not yet been set.

This lets runtime distinguish:

```text
known marker-owned initial clear
vs
any later native clear after first-contact proof
```

Do not classify a call as native or marker-owned merely from the flag. Caller module/RVA and surrounding factual state are the authority.

---

## Required pre/post observation

For each relevant exact clear invocation, observe trigger state immediately before and immediately after the original call.

Use the same safe read-only trigger-state concepts already proven in EV-289:

```text
ResetOnUntouch
VisitedSize
VisitedCountSize
PlayerResolved
PlayerPresent
PlayerEntryCount
PlayerVisitCount
CountsAligned
```

For the entity-specific overload also record:

```text
Argument entity identity/name when safely resolvable
ArgumentIsPlayer
```

Do not infer array index associations when sizes are inconsistent.

The hook must never mutate the arrays except through Gothic's original function itself. The diagnostic code performs no extra clear.

---

## Caller identity

For every relevant clear call, resolve/log the factual caller return address with at least:

```text
CallerModule
CallerRVA
```

If resolution fails, log the raw return address and resolution failure rather than guessing.

The Script wrapper's tested tail-jump means a call routed from Script_Game through `PSTouchDamage::ClearTriggeredList()` may preserve the original Script_Game return address, but this is an expectation to verify at runtime, not a required assumed result.

---

## Suggested compact diagnostic

Use one compact family, for example:

```text
CORE RAW55_NORMAL_TRIGGER_CLEAR_OBSERVATION
```

Required factual fields:

```text
Boundary=PRE|POST
ClearKind=ALL|ENTITY
Actor
C1
Action
StatePosition
StateTime
Right
RightUseType
RightGroup
PreStateRearmProven
Native7To7SuppressionUsed
TriggerIdentityMatch
ResetOnUntouch
VisitedSize
VisitedCountSize
PlayerPresent
PlayerEntryCount
PlayerVisitCount
CountsAligned
Argument=<none>|<entity>
ArgumentIsPlayer
CallerModule
CallerRVA
```

A bounded raw caller address may also be logged.

Do not dump full stacks, raw object memory, or unbounded arrays.

---

## Protected boundaries

This task is OBSERVATION ONLY.

Do NOT:

```text
suppress either ClearTriggeredList call
skip either original function
call either ClearTriggeredList overload anywhere new
change the existing marker-1 clear
change the existing native 7 -> 7 suppression
add marker-2 rearm
mutate EntitiesVisited / EntitiesVisitedCount
change ResetOnUntouch
change collision groups beyond existing probe behavior
write StatePosition
call TriggerTarget / OnDamage / custom damage
change cleanup/repair
add polling
add any hook other than the two exact clear-function observation hooks
hook the Script wrapper separately when the exact Engine clear hooks already cover it
change Quick/Power/Sprint/raw8 behavior
change FrameCollisionMarkers semantics
change CollisionLifecycleGuard semantics
implement permanent PhysicalFistCollision
perform New Balance work
perform Raise/speed work
```

If exact hooking of either frozen engine export is materially inconsistent with the pinned SDK/tested binary or cannot preserve original semantics, STOP and report the contradiction. Do not substitute a broader trigger hook.

---

## Expected source scope

Expected diagnostics-only changes:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

No CMake change is expected.

No production module is expected to change.

The header change is allowed only for the smallest factual delegation seam from EngineBridge to PhysicalFistProbe.

---

## Decisive runtime interpretation

### Route A — exact public clear source identified

If after first damage the log shows a relevant exact RIGHT clear call such that:

```text
PRE:  PC_Hero present in visited state
original clear executes
POST: PC_Hero absent/reset
caller module/RVA is factual
```

and the already-existing EV-289 `SP0_TO1_POST_CALLBACK` snapshot agrees:

> The observed public clear call is the factual native operation resetting prior player-contact bookkeeping for the current implicit second Normal opportunity.

Do not yet suppress it in this observation probe. Freeze a separate one-variable causal probe if authored marker-2 ownership still requires proving necessity.

### Route B — entity-specific clear identified

If `ClearTriggeredList(eCEntity*)` is called with `PC_Hero` and removes the player entry while preserving other entries:

> The entity-specific public clear is the factual reset operation for the player contact.

Again, no suppression belongs in this task.

### Route C — no post-first-hit public clear call

If the known marker-owned initial clear is observed but neither public clear overload is called on the exact RIGHT trigger after first contact, while the existing EV-289 snapshots still prove the visited state resets during `SP0 -> 1`:

> The two public `ClearTriggeredList` APIs are ruled out as the native reset source. Continue into lower/private trigger internals; do not attribute the reset to StatePosition itself.

### Stop condition

If the new hook changes first damage, `SP0 -> 1`, second damage, native cleanup, or C1 finalization, stop and analyze transport before drawing causal conclusions.

---

## Build policy

Work build execution is **not authorized**.

Work performs source/static audit only, publishes the bounded diagnostic implementation, reports the remote commit, and stops. Normal Chat independently reviews the commit before User-local build/deploy/runtime validation.
