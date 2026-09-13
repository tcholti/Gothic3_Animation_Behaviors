# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-13

## Current Bridge — RAW55 QUICK REPEATED-FIST REARM WORK TASK

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

The earlier pre-StatePosition probe is complete/runtime-validated. The old early-window-control probe remains superseded and must not be implemented.

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

## Frozen Next Causal Question

Authority:

```text
docs/COLLISION_RAW55_QUICK_REPEAT_FIST_REARM_PROBE.md
```

Question:

> With the first authored FIST already opening/rearming exact RIGHT raw55 and the source still naturally group7, can the exact second legitimate FIST in the same actor/source/C1 author a second contact opportunity using only one `TouchDamage.ClearTriggeredList()` and **no new collision-group request**?

The existing generic `MarkerProcessResult` occurrence facts are the required identity:

```text
authoredMarkerCount == 2
acceptedMarkerCountBefore == 1
acceptedMarkerCountAfter == 2
executionBudgetReset == false
```

Do not invent raw55-local frame/time dedupe rules.

---

## Exact Work Responsibility

Starting remote HEAD for Work:

```text
93245c8a7545804e8780615213ee076277c026e7
```

Implement only the diagnostics-only second-FIST path in `PhysicalFistProbe.cpp`.

Eligibility must preserve the frozen exact Quick/raw55 fixture and additionally require:

```text
same actor + exact RIGHT source + C1 as the already-used EV-269 pre-state FIST
RIGHT PhysicalFist/raw55
RIGHT already Item_Attack/group7
StatePosition == 1
exact second accepted FIST occurrence (1 -> 2 of exactly two authored FISTs)
```

Intervention:

```text
rightSource.TouchDamage.ClearTriggeredList()
exactly once
```

Do NOT call `SetCollisionGroup()` or `CollisionSourceOperations::ActivateOrRearm()` for the second FIST.

Add:

```text
CORE RAW55_QUICK_REPEAT_FIST_REARM_PROBE
```

with the fields frozen in the contract.

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
stable marker occurrence/dedupe bookkeeping
Raw8FistCollision
CollisionLifecycleGuard
CollisionSources
CollisionSourceOperations
EngineBridge hook ownership / RVAs
CMake/build separation
Normal/Sprint temporary behavior
```

Do not add in this task:

```text
Power raw55 support
permanent PhysicalFistCollision
custom/direct damage
TriggerTarget / OnDamage
StatePosition/SPU writes
manual cleanup
another group request
new hook/RVA/timer/polling
new timing/dedupe heuristic
```

Build execution is NOT authorized for Work.

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
permanent PhysicalFistCollision design/promotion
```
