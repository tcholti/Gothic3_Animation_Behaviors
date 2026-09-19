# Gothic 3 Animation Behaviors — RAW55 Normal Native Trigger-Clear Suppression Probe

**Status:** FROZEN DIAGNOSTIC CAUSAL-PROBE CONTRACT  
**Date:** 2026-09-16  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Test whether the exact native public trigger clear identified in EV-290 is causally required for Normal's implicit second same-C1 damage opportunity.

EV-290 identifies the factual reset operation:

```text
first authored FIST at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList()
-> first damage
-> PC_Hero becomes visited/count1

later native Normal transition
-> existing EV-288 exact RIGHT 7 -> 7 setter suppression fires
-> Gothic calls exact RIGHT eCTrigger_PS::ClearTriggeredList() ALL
   caller = Script_Game.dll + 0x386C6
   PRE:  PlayerPresent=1 / PlayerVisitCount=1
   POST: PlayerPresent=0 / visited arrays empty
-> original _AI_Attack continues SP0 -> 1

later authored FIST
-> observational only
-> second damage can occur
```

The public ALL clear is therefore the factual operation that performs the EV-289 bookkeeping reset. This probe changes only that one operation in the exact proven execution and asks whether the second contact survives.

This is a temporary causal probe, not production behavior.

---

## Single Question

With the complete EV-290 environment preserved, if the exact post-hit-1 native:

```text
eCTrigger_PS::ClearTriggeredList()
caller = Script_Game.dll + 0x386C6
```

is suppressed once for the exact current RIGHT raw55 trigger, while marker 2 remains observational, does Normal still produce the second same-C1 damage opportunity?

### Interpretation

If:

```text
first damage survives
+ native clear suppression factually fires
+ player remains visited through SP0 -> 1 and marker 2
+ second damage disappears
+ native cleanup remains healthy
```

then the identified native public ALL clear is causally required for the implicit second-contact opportunity.

If second damage still occurs despite the exact clear being suppressed and the player remaining visited, another trigger/contact mechanism remains causal.

Do not add authored marker-2 rearm in this same probe. Restoration by marker 2 is a later one-variable test only after necessity is settled.

---

## Required Existing Environment

Preserve the complete already-proven Normal diagnostic route:

```text
frame-1 FIST at SP0
-> exact RIGHT 5 -> 7
-> existing marker-owned ClearTriggeredList()
-> preStateRearmProven = true

first native damage opportunity

existing EV-288 exact native RIGHT 7 -> 7 setter suppression
-> original _AI_Attack continues

native SP0 -> 1 progression

frame-15 FIST
-> observational only

native final exact RIGHT 7 -> 5 cleanup
```

Preserve the EV-289 read-only trigger-state observations and EV-290 clear PRE/POST observations unless the smallest implementation requires a compact factual `Suppressed` field or a separate suppression record.

---

## Exact Suppression Target

Suppress only the no-argument public Engine overload:

```text
eCTrigger_PS::ClearTriggeredList()
Engine + 0x7DDA0
```

Do **not** suppress:

```text
eCTrigger_PS::ClearTriggeredList(eCEntity*)
Engine + 0x7DDF0
```

The suppression is eligible only when all required factual gates below are true.

### Required identity gates

```text
clear kind == ALL
actual hook this == exact current RIGHT TouchDamage/eCTrigger_PS
factual Action == gEAction_Attack / 1
Family NORMAL / Hit eligible
valid current C1 generation
same actor
same exact current RIGHT source
RIGHT UseType == PhysicalFist/raw55
RIGHT collision group == Item_Attack / 7
matching NormalPreStateFistIntervention
preStateRearmProven == true
nativeRearmSuppressionUsed == true
native trigger-clear suppression not yet used for this C1
StatePosition == 0 at the clear call
```

### Required factual contact gate

Immediately before deciding suppression, read the same exact trigger state used by EV-289/EV-290 and require a safe factual player visit:

```text
CountsAligned == 1
PlayerResolved == 1
PlayerPresent == 1
PlayerEntryCount == 1
PlayerVisitCount >= 1
```

This prevents the causal mutation from firing in executions where hit #1 did not factually establish the player visit.

### Required caller gate

The return/caller identity must resolve exactly to:

```text
CallerModule == Script_Game.dll
CallerRVA    == 0x000386C6
```

Do not generalize to another Script_Game caller, another module, another timer, or another state-time range.

The tested static binary reference shows the corresponding indirect call at:

```text
Script_Game.dll + 0x386C0
```

with return at `+0x386C6`.

---

## Suppression Behavior

For one eligible exact native ALL clear per C1:

```text
observe/log PRE factual state
-> PhysicalFistProbe returns exact suppression decision
-> EngineBridge skips the original ALL clear exactly once
-> mark suppression used for that exact Normal intervention/C1
-> record POST-equivalent factual state after the skipped call boundary
```

The underlying trigger arrays must not be directly edited. The probe suppresses the native function call; it does not manually recreate, clear or rewrite its storage.

The hook remains void-compatible. Do not fabricate another return semantic.

For every non-eligible call, including marker 1's existing clear, call the original exactly once as before.

---

## Marker-1 Control Must Remain Untouched

The existing authored frame-1 clear is a protected control.

It is currently observed with facts such as:

```text
CallerModule=Script_FrameCollisionTest.dll
PreStateRearmProven=0
```

It must continue to execute exactly once and normally.

Do not suppress it even if the trigger identity matches the same RIGHT raw55 source.

---

## Suggested Diagnostic

Use a compact record family such as:

```text
CORE RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE
```

Include enough factual fields to reconstruct the decision:

```text
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
PlayerPresent
PlayerEntryCount
PlayerVisitCount
CountsAligned
CallerModule
CallerRVA
SUPPRESS_CLEAR=1
```

Existing `RAW55_NORMAL_TRIGGER_CLEAR_OBSERVATION` PRE/POST records may remain the primary before/after state record. If the POST record follows a skipped original call, add an explicit factual field or separate suppression record so later evidence cannot mistake the unchanged state for an executed clear.

Do not dump stacks or raw arrays.

---

## Protected Boundaries

Do NOT:

```text
suppress marker-1 ClearTriggeredList
suppress the entity-specific ClearTriggeredList(eCEntity*) overload
suppress another ALL-clear caller
suppress a clear when PC_Hero is not factually visited
add any new ClearTriggeredList call
manually mutate EntitiesVisited
manually mutate EntitiesVisitedCount
change ResetOnUntouch
remove/change EV-288 native 7 -> 7 setter suppression
add marker-2 rearm
add another collision-group request/suppression
write StatePosition
call TriggerTarget / OnDamage / direct damage
change cleanup/repair
add another hook or RVA
add polling
add species/name/animation/timer policy
change Quick/Power/Sprint/raw8 behavior
change FrameCollisionMarkers
change CollisionLifecycleGuard
change CollisionSources
implement permanent PhysicalFistCollision
perform New Balance work
perform Raise/speed work
```

If the exact caller cannot be resolved safely at runtime, the intervention must fail closed and let the original clear execute.

If suppressing the exact call prevents the original `_AI_Attack` callback from completing or produces an unexpected structural contradiction, preserve the evidence and stop; do not compensate with another mutation in the same probe.

---

## Expected Source Scope

Expected diagnostics-only changes:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

No new hook is required. Reuse the already-installed `Engine + 0x7DDA0` observation hook.

No CMake change is expected.
No production module is expected to change.

`EngineBridge` remains sole hook/transport owner. `PhysicalFistProbe` owns eligibility, one-shot bookkeeping, caller/contact gating, suppression decision and diagnostic interpretation.

---

## Runtime Result Routes

### Route A — second hit disappears

Required facts:

```text
first hit confirmed
exact native ALL clear eligible
SUPPRESS_CLEAR=1
original ALL clear skipped
player remains visited after skipped boundary
SP0 -> 1 still completes
marker 2 arrives with player still visited
no second ONDAMAGE
native 7 -> 5 cleanup / clean C1
```

Conclusion:

> The exact native public ALL clear from `Script_Game.dll+0x386C6` is causally required for Normal's implicit second-contact opportunity in the tested route.

Next test:

Keep that native clear suppressed and add exactly one authored marker-2 clear. If the second hit returns, marker-2 ownership is proven.

### Route B — second hit persists

If the exact native ALL clear is suppressed, the player remains visited, and a second damage still occurs:

> The public clear performs the observed bookkeeping reset but is not causally required for the second hit; another trigger/contact mechanism permits it.

Do not add marker-2 behavior until that mechanism is understood enough to avoid false ownership.

### Route C — progression/cleanup contradiction

If exact clear suppression causes callback progression, source state, or cleanup to diverge materially:

> The native clear has additional relevant semantics in this callback path. Preserve that contradiction as evidence and isolate it before authored replacement work.

---

## Build Policy

Work build execution is **not authorized** by this contract.

Work performs source/static audit only, publishes the bounded diagnostics-only implementation, reports the remote commit, and stops. Normal Chat independently reviews it before User-local build/deploy/runtime validation.
