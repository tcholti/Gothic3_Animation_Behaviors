# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-13

## Current Bridge — RAW55 QUICK REPEATED-FIST REARM WORK TASK, REVISION 2

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-271**.

No permanent raw55 implementation is authorized yet.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_REPEAT_FIST_REARM_PROBE.md
4. EVIDENCE_LEDGER_269_ONWARD.md EV-269–EV-271
5. WORK_IMPLEMENTATION_PROTOCOL.md
6. only exact source/API needed for this bounded implementation
```

---

## Closed Evidence

### EV-269 — first early raw55 Quick FIST PASS

```text
frame-1 FIST arrives at StatePosition 0
RIGHT TrollFist/raw55 5 -> 7
one ClearTriggeredList
later untouched native Quick 7 -> 7
StatePosition 0 -> 1
OnDamage on contact
native cleanup 7 -> 5
clean C1 finalization
```

### EV-270 — later FIST transport exists; temporary probe blocks it

```text
later authored FIST reaches the same Quick C1
current PhysicalFistProbe one-shot policy refuses a second intervention
therefore repeated raw55 rearm remains untested
```

### EV-271 — frame 0 / frame 1 authoring closure

```text
2H equipped RIGHT works at frame 0 and frame 1
raw8 Sabretooth FIST works at frame 0 and frame 1
no global frame-1 minimum
```

User clarification: the extra Sabretooth frame-0 misses occurred only while the spawned NPC attacked `PC_Hero`; the User's transformed-player frame-0 Quick attacks hit the spawned Sabretooth every time. Treat the NPC misses as contact/timing variation, not marker unreliability.

---

## Work Attempt 1 — Correctly Stopped on Source Contradiction

Work made no changes and left remote HEAD unchanged at:

```text
ec2cb73cebb91b4e92db8d4e49441acf40d08fe2
```

Contradiction:

`FrameCollisionMarkers::ProcessMarker()` returns raw55 FIST as `MarkerResult_UnsupportedMissingSource` immediately after the raw8 FIST resolver fails. That return happens before:

```text
C1 capture
generic same-update duplicate handling
TryConsumeAuthoredMarkerOccurrence(...)
authoredMarkerCount
acceptedMarkerCountBefore
acceptedMarkerCountAfter
executionBudgetReset
```

Therefore the original frozen requirement:

```text
2 authored / accepted 1 -> 2 / reset=false
```

cannot exist in the raw55 `MarkerProcessResult`.

This was an architecture/specification contradiction, not a Work failure.

Do NOT modify/reorder stable `FrameCollisionMarkers` merely to satisfy the probe.

---

## Revised Frozen Causal Question

Authority:

```text
docs/COLLISION_RAW55_QUICK_REPEAT_FIST_REARM_PROBE.md
```

Question:

> With the first authored FIST already opening/rearming exact RIGHT raw55 and the source still naturally group7, can the first later eligible FIST dispatch in the same controlled two-FIST actor/source/C1 create a second contact opportunity using only one `TouchDamage.ClearTriggeredList()` and no new collision-group request?

For this diagnostics-only probe, `PhysicalFistProbe` may maintain the smallest temporary sequence observation required to distinguish:

```text
1. the already-proven EV-269 pre-state FIST intervention
2. the first later eligible FIST dispatch in the same actor/source/C1
```

This temporary sequence observation is NOT production occurrence identity.

Do not add frame/time/source-name/species/motion-change/action-change/phase-change/callback-rollback heuristics.

The controlled fixture must have exactly two authored FIST markers according to the already-available scanned decision:

```text
decision.markerCounts[FIST] == 2
```

---

## Exact Work Responsibility — Revision 2

Expected source change:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Implement only the diagnostics-only later-FIST rearm path.

Eligibility must preserve the exact Quick/raw55 fixture and require:

```text
same actor + exact RIGHT source + C1 as the already-used EV-269 pre-state FIST
result.code == UNSUPPORTED_MISSING_SOURCE
Quick Hit
exactly two FIST markers in decision
no RIGHT / LEFT / BOTH / OFF markers
raw8 resolver absent
RIGHT PhysicalFist/raw55
RIGHT already Item_Attack/group7
StatePosition == 1
first later eligible FIST dispatch after the proven pre-state FIST
later-FIST rearm not already used
```

Intervention:

```text
rightSource.TouchDamage.ClearTriggeredList()
exactly once
```

Do NOT call `SetCollisionGroup()` or `CollisionSourceOperations::ActivateOrRearm()` for the later FIST.

Add:

```text
CORE RAW55_QUICK_REPEAT_FIST_REARM_PROBE
```

with the fields frozen in the revised contract.

---

## Preserve / Forbid

Preserve unchanged:

```text
EV-269 first FIST 5 -> 7 + clear
original Quick callback exactly once
native 7 -> 7
StatePosition progression
native 7 -> 5 cleanup
EV-265 suppression semantics where applicable
EV-267 old post-state fixture behavior
stable FrameCollisionMarkers behavior
Raw8FistCollision
CollisionLifecycleGuard
CollisionSources
CollisionSourceOperations
EngineBridge hook ownership / RVAs
CMake/build separation
Normal/Sprint temporary behavior
Power temporary behavior
```

Do not add in this task:

```text
stable marker-engine changes
permanent raw55 occurrence bookkeeping
Power raw55 support
permanent PhysicalFistCollision
custom/direct damage
TriggerTarget / OnDamage
StatePosition/SPU writes
manual cleanup
another collision-group request
new hook/RVA/timer/polling
frame/time dedupe heuristic
```

Build execution is NOT authorized for Work.

---

## Production Architecture Consequence — Later, Not This Task

The contradiction proves that production raw55 repeated-marker support cannot simply consume the current generic occurrence fields, because those are reached only after raw8 FIST source resolution succeeds.

Future production design must provide raw55 factual generic occurrence identity without permanently duplicating a second occurrence engine inside `PhysicalFistCollision` and without regressing raw8/equipped behavior.

Do not solve that architecture question inside this causal probe.

---

## Work Report

Static/source audit, commit and push, then report:

```text
final remote commit SHA
changed files
concise implementation result
build status
material contradiction, if any
```

Then STOP.

Normal Chat reviews the exact diff before User build/runtime.

---

## Later Raw55 Responsibilities — NOT THIS TASK

After repeated Quick rearm is closed:

```text
Power family ownership — marked raw55 Power currently leaks native collision
Normal/Sprint — still carry older whole-callback temporary experiments
production generic occurrence integration
permanent PhysicalFistCollision design/promotion
```
