# Gothic 3 Animation Behaviors — RAW55 Normal Native Rearm-Source Probe

**Status:** FROZEN DIAGNOSTIC CONTRACT  
**Date:** 2026-09-15  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Close the remaining Normal second-contact ownership question exposed by EV-287 before any permanent raw55 architecture is frozen.

EV-287 proves that the frame-1 Normal `G3AB_COL_FIST` can own an early physical opening and contact rearm:

```text
SP0 FIST
-> exact current RIGHT PhysicalFist/raw55 5 -> 7
-> exact RIGHT TouchDamage.ClearTriggeredList()
-> native ONDAMAGE while StatePosition is still 0
```

The original `_AI_Attack` callback then later reaches its ordinary Normal threshold, requests the already-open exact RIGHT source `7 -> 7`, and advances `StatePosition 0 -> 1`. The frame-15 FIST is subsequently delivered while RIGHT remains group7. Current Normal probe code performs no intervention for that second marker, yet the same C1 can produce a second native damage event.

Therefore the second damage opportunity is real, but it is not yet proven to be authored-marker-owned. The strongest remaining candidate is the intervening native exact-source `7 -> 7` setter request.

This probe tests only whether that native `7 -> 7` request is the source of the later contact rearm.

This is a temporary diagnostic experiment only. It does not authorize permanent raw55 behavior.

---

## Single Causal Question

After a factual marked raw55 Normal execution has successfully completed its proven SP0 marker intervention:

```text
frame-1 FIST
-> exact RIGHT 5 -> 7
-> ClearTriggeredList()
-> first native damage can occur while SP0
```

is Gothic's later native exact RIGHT:

```text
7 -> 7
```

collision-group request what creates the later second-contact opportunity?

Change one variable only:

```text
suppress that one factual native Normal 7 -> 7 setter request
```

while preserving the original `_AI_Attack` callback and its `StatePosition 0 -> 1` progression.

Do not add any intervention to the frame-15 marker in this probe.

---

## Required Proven Anchor

The new suppression may exist only for an execution where the current Normal SP0 intervention has actually succeeded.

The probe must distinguish a mere attempted pre-state intervention from a proven one. Extend the temporary `NormalPreStateFistIntervention` research state only as needed so it can factually record that:

```text
same actor
same C1 generation
same exact RIGHT source
SP0 FIST opening reached group7
ClearTriggeredList() actually executed
```

A suitable diagnostic-only boolean such as `preStateRearmProven` is allowed. Set it only after verified group7 and the exact triggered-list clear.

The new native-7->7 suppression must also be one-shot for that exact actor + C1 + RIGHT source. A diagnostic-only one-shot field is allowed for this purpose.

Do not promote this temporary bookkeeping into production architecture.

---

## Exact Native Request Eligibility

Use the existing collision-group delegation seam and keep the decision in `PhysicalFistProbe`.

Suppress only when all of the following are factual at the nested setter request:

```text
diagnostics build
active Normal callback observation scope
scope ActionBefore == gEAction_Attack / 1
current factual Action == gEAction_Attack / 1
Family NORMAL / Hit eligible
sourceInstance == scope exact RIGHT source
sourceInstance == current equipped RIGHT source
RIGHT UseType == PhysicalFist/raw55
valid current C1
same actor as callback scope
same C1 generation as callback scope
matching proven NormalPreStateFistIntervention exists
same actor + C1 + exact RIGHT source as that intervention
pre-state rearm proven
this native-rearm suppression not previously used
requestedGroup == Item_Attack / 7
beforeGroup == Item_Attack / 7
current RIGHT group == Item_Attack / 7
StatePosition == 0
```

Do not use a timer threshold as policy. The factual nested native `7 -> 7` request inside the active Normal callback is the event under test.

Do not add species/name/motion-prefix policy.

---

## Exact Intervention

For the one eligible request only:

```text
return suppression decision = true
```

so the underlying `SetCollisionGroup(Item_Attack)` call is not executed for that one native `7 -> 7` request.

Nothing else is changed.

In particular:

```text
DO NOT suppress the _AI_Attack callback
DO NOT suppress the original earlier 5 -> 7 rule differently
DO NOT write StatePosition
DO NOT clear the triggered list here
DO NOT call damage / TriggerTarget / OnDamage
DO NOT perform cleanup or repair
```

The original `_AI_Attack` callback must continue after the nested setter is suppressed so we can observe whether Gothic still advances `StatePosition 0 -> 1`.

---

## First Marker Must Remain Proven

Preserve the EV-287 first-marker path unchanged:

```text
frame-1 FIST at SP0
-> exact RIGHT 5 -> 7
-> verify group7
-> exact RIGHT ClearTriggeredList() once
-> early first native damage opportunity
```

Do not remove or alter the SP0 clear in this probe.

The test is meaningful only if the first damage opportunity remains healthy before the later native request under investigation.

---

## Second Marker Must Remain Observational

The Troll fixture has FIST markers at frames 1 and 15.

The later frame-15 FIST remains observational only:

```text
no Normal marker-2 ClearTriggeredList()
no marker-2 group request
no Normal repeat-rearm implementation
```

This probe is not the final repeated-marker feature. It isolates the source of the currently observed second opportunity.

---

## Diagnostic Logging

Keep existing marker/group/callback/lifecycle diagnostics.

Add one compact factual record when the new suppression actually occurs, for example:

```text
CORE RAW55_NORMAL_NATIVE_REARM_SUPPRESSION_PROBE
```

with at minimum:

```text
Actor
C1
Action
StatePosition
StateTime
Right
RightUseType
RequestedGroup=7
BeforeGroup=7
PreStateRearmProven=1
NATIVE_7TO7_SUPPRESS=1
```

The existing Normal SP0 record must continue to show:

```text
ClearTriggeredList=1
PRESTATE_REARM=1
```

Do not modify ordinary logging to imply that the suppressed request physically changed the group.

---

## Decisive Runtime Interpretation

Use the same Normal two-swing Troll fixture.

### Causal PASS for the hypothesis

```text
frame-1 SP0 FIST -> exact RIGHT 5 -> 7 + ClearTriggeredList
first ONDAMAGE occurs while SP0
later factual native Normal 7 -> 7 request is suppressed
original callback still advances SP0 -> 1
frame-15 FIST is delivered with no Normal repeat intervention
NO second ONDAMAGE follows
native final 7 -> 5 cleanup remains healthy
C1 finalizes cleanly
```

Interpretation:

> The native Normal `7 -> 7` setter request is causally required for the currently observed second-contact opportunity.

That would justify a later separate probe in which authored marker 2 explicitly performs the rearm instead.

### Hypothesis rejected

If the first hit remains healthy, the native `7 -> 7` request is suppressed, `SP0 -> 1` still occurs, and a second native damage event still occurs without any marker-2 intervention:

> The native group setter request itself is not the source of the second rearm. Another callback/state/contact mechanism must be isolated.

### Stop condition

If suppressing the nested `7 -> 7` request prevents `StatePosition 0 -> 1`, breaks first-contact behavior, causes cleanup divergence, or otherwise changes more than the intended setter side effect, stop and return the contradiction. Do not compensate inside the same probe.

---

## Protected Boundaries

Preserve unchanged:

```text
Normal SP0 marker 5 -> 7 + ClearTriggeredList path
Normal existing selective early 5 -> 7 suppression
Normal existing SP1 activation path
original _AI_Attack callback
Quick raw55 behavior/research state
Power raw55 behavior/research state
Sprint raw55 behavior/research state
raw8 FIST
FrameCollisionMarkers semantics
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations semantics
equipped RIGHT / LEFT / BOTH / OFF marker behavior
native final cleanup
```

Do not add:

```text
Normal marker-2 rearm
Power marker-2 rearm
Sprint marker-2 rearm
Sprint Action9 -> Action2 production policy
custom/direct damage
manual cleanup/repair
new hook/RVA/timer/polling/per-frame scan
species/name/filename policy
permanent PhysicalFistCollision
New Balance compatibility changes
Raise/speed work
```

---

## Expected Source Scope

Expected change:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h` is not expected to require a change because the existing public collision-group delegation seam is sufficient. If implementation discovers that a header/bridge/API change is materially necessary, stop and report the contradiction rather than broadening automatically.

`EngineBridge` must remain unchanged.

No CMake change is expected.

---

## Build Policy

Work build execution is not authorized by this contract.

Work performs source/static audit only, publishes the bounded implementation, reports the remote commit, and stops. Normal Chat then independently reviews before User-local build/deploy/runtime validation.
