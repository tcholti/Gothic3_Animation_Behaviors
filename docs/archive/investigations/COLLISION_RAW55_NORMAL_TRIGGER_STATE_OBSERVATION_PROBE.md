# Gothic 3 Animation Behaviors — RAW55 Normal Trigger-State Observation Probe

**Status:** FROZEN DIAGNOSTIC OBSERVATION CONTRACT  
**Date:** 2026-09-16  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Close the next Normal second-contact ownership question after EV-288 without introducing another behavioral mutation.

EV-288 rejects the hypothesis that Gothic's later exact RIGHT native `Item_Attack/group7 -> Item_Attack/group7` setter request is required for the observed second same-C1 damage opportunity. With that exact setter request suppressed, the original `_AI_Attack` callback still advances `StatePosition 0 -> 1`, frame-15 FIST remains observational, and a second native damage event can still occur.

The remaining mechanism may therefore live in ordinary trigger/touch bookkeeping rather than in the collision-group setter itself.

The official SDK exposes the relevant read-only trigger state on `eCTrigger_PS`:

```text
EntitiesVisited
EntitiesVisitedCount
```

and the exact raw55 `gCTouchDamage_PS` exposes:

```text
ResetOnUntouch
```

This probe observes that state for the exact current RIGHT PhysicalFist/raw55 source across the already-proven Normal two-contact execution.

This is observation only. It must not add a new collision/contact intervention.

---

## Single Question

With the EV-288 environment preserved:

```text
frame-1 FIST at SP0
-> exact RIGHT 5 -> 7
-> exact RIGHT ClearTriggeredList()
-> first damage opportunity

later native exact RIGHT 7 -> 7 request
-> still suppressed once by the existing EV-288 diagnostic path
-> original _AI_Attack still advances SP0 -> 1

frame-15 FIST
-> observational only
```

what happens to the exact RIGHT source's trigger bookkeeping between the first and second damaging contacts?

In particular:

```text
Does PC_Hero enter EntitiesVisited after hit 1?
Does that PC_Hero entry/count later disappear or reset before hit 2?
Is ResetOnUntouch enabled on the exact source?
```

If the player is naturally removed/reset between contacts while no explicit marker-2 clear occurs, that identifies ordinary trigger/touch bookkeeping as the next causal route.

Do not infer the cause of a removal merely from observing it. A later causal probe may test `ResetOnUntouch` or another exact mechanism if needed.

---

## Required Execution Anchor

Reuse the existing exact Normal research identity already present in `PhysicalFistProbe`:

```text
factual Action == gEAction_Attack / 1
Family NORMAL / Hit eligible
valid current C1 generation
same actor
same exact current RIGHT source
RIGHT UseType == gEUseType_PhysicalFist / raw55
matching NormalPreStateFistIntervention
preStateRearmProven == true
```

The observation must remain scoped to that exact actor + C1 generation + RIGHT source.

Do not add species, actor-name, animation-prefix, timer, or filename policy.

---

## Read-Only State

For the exact RIGHT source, resolve its `gCTouchDamage_PS` / inherited `eCTrigger_PS` and read only:

```text
ResetOnUntouch
EntitiesVisited size/count
EntitiesVisitedCount size/count
whether the current player entity is present in EntitiesVisited
if present, the matching visited-count value when safely available
```

Use the official SDK declarations. Do not hard-code private trigger offsets when public SDK accessors/properties are available.

The observation may resolve `eCEntityProxy` entries through the SDK's public proxy API in order to identify `PC_Hero` / current player identity.

Do not mutate either array.

---

## Required Observation Boundaries

Record compact factual snapshots at these boundaries when applicable:

### A. Immediately after proven frame-1 rearm

After exact RIGHT `5 -> 7` has succeeded and the existing marker-owned `ClearTriggeredList()` has actually executed:

```text
Boundary=POST_PRESTATE_REARM
```

This establishes the starting trigger state.

### B. Change-only observation while the same Normal C1 remains active

At the already-existing Normal callback observation path, sample the exact RIGHT trigger state and emit a record only when the relevant trigger-state fingerprint changes.

A relevant change includes at minimum:

```text
EntitiesVisited size changed
EntitiesVisitedCount size changed
player-present changed
player visited-count changed
```

This change-only route is intended to capture player insertion after hit 1 and any later natural removal/reset without flooding the log every callback.

Do not add polling outside the existing Normal callback path.

### C. Immediately before the already-existing native 7 -> 7 suppression

When the EV-288 `RAW55_NORMAL_NATIVE_REARM_SUPPRESSION_PROBE` is about to suppress the exact native `7 -> 7` request, record:

```text
Boundary=NATIVE_7TO7_SUPPRESS_PRE
```

Then preserve the existing suppression behavior unchanged.

### D. Immediately after the same callback advances SP0 -> 1

In the existing Normal callback end observation, when the exact same actor/C1/RIGHT callback factually transitions:

```text
StatePosition 0 -> 1
```

record:

```text
Boundary=SP0_TO1_POST_CALLBACK
```

This lets the log compare trigger state immediately before and after the native callback transition while the group setter remains suppressed.

### E. Later authored FIST in the same C1

When the later frame-15 FIST is transported for the same proven Normal C1 after the first intervention, record:

```text
Boundary=LATER_FIST
```

but perform **no** marker-2 clear, group request, or other contact intervention.

---

## Suggested Compact Diagnostic

Use one compact record family, for example:

```text
CORE RAW55_NORMAL_TRIGGER_STATE_OBSERVATION
```

Include enough factual fields to reconstruct the sequence:

```text
Boundary
Actor
C1
Action
StatePosition
StateTime
Right
RightUseType
RightGroup
ResetOnUntouch
VisitedSize
VisitedCountSize
PlayerPresent
PlayerVisitCount
ChangeReason   // for change-only records; NONE at fixed boundaries is fine
```

If a visited-count cannot safely be associated with the player entry because the arrays are inconsistent or differently sized, log that fact rather than guessing.

Do not dump raw object memory or unbounded arrays.

---

## Existing Behavior Must Remain Unchanged

Preserve the complete EV-288 diagnostic behavior exactly:

```text
Normal frame-1 SP0 5 -> 7 opening
verified group7
exact RIGHT ClearTriggeredList once
preStateRearmProven bookkeeping
one-shot exact native Normal 7 -> 7 suppression at SP0
original _AI_Attack callback
native SP0 -> 1 progression
frame-15 FIST observational only
native final cleanup
```

This probe adds observation only.

Do not remove the EV-288 suppression in the same task; keeping the setter absent ensures any observed trigger-state reset is independent of that setter call.

---

## Protected Boundaries

Do NOT:

```text
call ClearTriggeredList anywhere new
clear/rewrite EntitiesVisited
clear/rewrite EntitiesVisitedCount
change ResetOnUntouch
add marker-2 rearm
add another collision-group request/suppression
write StatePosition
call damage / TriggerTarget / OnDamage
change cleanup/repair
add a new hook or RVA
modify EngineBridge
add per-frame/global polling
add species/name/filename policy
change Quick/Power/Sprint/raw8 behavior
change FrameCollisionMarkers semantics
change CollisionLifecycleGuard semantics
change CollisionSources semantics
implement permanent PhysicalFistCollision
perform New Balance work
perform Raise/speed work
```

If accurate observation materially requires a new EngineBridge hook/interface, stop and report the contradiction instead of broadening automatically.

---

## Expected Source Scope

Expected change:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h`, `EngineBridge.cpp`, CMake, and production modules are not expected to change.

Work may inspect the pinned official SDK declarations needed to use:

```text
eCTrigger_PS::EntitiesVisited
eCTrigger_PS::EntitiesVisitedCount
eCEntityProxy
gCTouchDamage_PS::ResetOnUntouch
```

and only the smallest current source needed to integrate the observation into existing Normal callback/marker paths.

---

## Runtime Interpretation

### Route 1 — natural trigger-state reset observed

If the log shows a sequence such as:

```text
POST_PRESTATE_REARM: player absent
first ONDAMAGE
change-only: player becomes present
...
change-only: player becomes absent/reset again
LATER_FIST: player absent
second ONDAMAGE
```

while no new explicit clear occurs:

> The second opportunity is enabled by native trigger/touch bookkeeping that removes or resets the prior player visit independently of the suppressed `7 -> 7` setter.

If `ResetOnUntouch=1`, that is a strong candidate mechanism but is not by itself causal proof that `OnUntouch` caused the reset. Freeze a later one-variable causal test only if needed.

### Route 2 — player remains visited through the second hit

If the player remains present with unchanged visited count through marker 2 and the second damage:

> `EntitiesVisited` membership alone does not explain the second opportunity; inspect the paired count/trigger semantics or another native contact mechanism.

### Route 3 — state changes only across SP0 -> 1

If trigger bookkeeping changes across the original callback even with `7 -> 7` suppressed:

> another operation inside the native callback/state transition mutates trigger eligibility; isolate that operation next without attributing it to StatePosition itself.

### Stop condition

If observation cannot safely identify the exact RIGHT TouchDamage state, array access is inconsistent, or source/C1 identity diverges, stop and report rather than adding a compensating behavior.

---

## Build Policy

Work build execution is not authorized by this contract.

Work performs source/static audit only, publishes the bounded diagnostics-only implementation, reports the remote commit, and stops. Normal Chat independently reviews it before User-local build/deploy/runtime validation.
