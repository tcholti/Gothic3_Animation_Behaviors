# RAW55 Quick Repeated-FIST Rearm Probe

**Status:** FROZEN DIAGNOSTICS-ONLY CAUSAL PROBE — REVISED AFTER SOURCE CONTRADICTION  
**Date:** 2026-09-13  
**Branch:** `docs/collision-source-evidence`

## 1. Single causal question

With EV-269 already proving that the first authored Quick FIST can open/rearm the exact RIGHT `TrollFist` / PhysicalFist/raw55 source and leave it naturally in group7 until Gothic cleanup, is **one later FIST dispatch in the same controlled two-FIST actor/source/C1 fixture** sufficient to create a second contact opportunity by calling `TouchDamage.ClearTriggeredList()` exactly once **without another collision-group request**?

This probe answers only that causal question.

---

## 2. Evidence boundary

Closed facts:

```text
EV-267
    raw55 Quick 5 -> 7 alone is insufficient for delayed authored damage
    one ClearTriggeredList after successful opening restores contact damage

EV-269
    first frame-1 FIST may arrive at StatePosition 0
    exact RIGHT raw55 5 -> 7 + one clear succeeds
    later untouched native Quick naturally performs 7 -> 7
    native StatePosition 0 -> 1 survives
    damage occurs on contact
    native cleanup 7 -> 5 remains healthy

EV-270
    a later FIST event is delivered in the same Quick C1
    the temporary probe currently blocks a second intervention by policy
    this is not evidence that Gothic cannot rearm raw55 again

EV-271
    established marker mechanisms honor literal early marker frames
    repeated authored marker semantics remain part of the project authoring contract
```

### Source contradiction discovered by Work

The first frozen version incorrectly required these `MarkerProcessResult` facts:

```text
authoredMarkerCount == 2
acceptedMarkerCountBefore == 1
acceptedMarkerCountAfter == 2
executionBudgetReset == false
```

That identity is **not available for raw55 FIST** in the current stable marker engine.

`FrameCollisionMarkers::ProcessMarker()` resolves raw8 FIST before C1 capture / duplicate handling / generic occurrence-budget consumption. For raw55, `ResolveFistCollisionSource(actor)` returns null, so the function returns `MarkerResult_UnsupportedMissingSource` before those occurrence fields are populated.

Therefore:

```text
raw55 FIST reaches scanned decision facts
raw55 FIST does NOT reach stable generic occurrence consumption
```

Do not reorder or modify stable `FrameCollisionMarkers` in this causal probe.

---

## 3. Diagnostic-only occurrence boundary

For this probe only, `PhysicalFistProbe` may maintain the **smallest temporary sequential dispatch observation** needed to distinguish:

```text
first proven pre-state FIST intervention
first later exact raw55 FIST dispatch in the same actor/source/C1
```

This is diagnostic scaffolding only. It is **not** production marker occurrence semantics and must not be generalized or promoted into permanent `PhysicalFistCollision` bookkeeping.

The stable authoring contract remains that repeated authored markers are occurrence-scoped. A later production architecture task must reconcile raw55 with generic marker occurrence identity rather than retain this temporary observer.

No frame-number, StateTime-delta, wall-clock, motion-change, action-change, phase-change, callback-rollback, species/name, or source-name heuristic may be added.

The controlled fixture itself provides the bounded sequence identity:

```text
exactly two authored FIST markers in the resolved Quick Hit decision
first FIST already proved by the EV-269 pre-state intervention record
then the first later eligible raw55 FIST dispatch in that same actor/source/C1
```

If unexpected extra FIST dispatches make the sequence ambiguous, log/stop the causal interpretation rather than adding another heuristic.

---

## 4. Exact fixture

Use the existing diagnostic Quick raw55 fixture only:

```text
Family: Quick Hit
Marker vocabulary: FIST only
resolved decision has exactly two authored FIST markers
RIGHT source: factual equipped source
RIGHT UseType: gEUseType_PhysicalFist / raw55
first authored FIST: already handled by EV-269 pre-state path
later FIST: controlled second-dispatch candidate in the same C1
```

No species/name gate.

Do not generalize this probe to Normal, Power, Sprint, raw8, equipped weapon markers, or more than the controlled two-FIST Quick fixture.

---

## 5. Frozen eligibility for the later-FIST intervention

The new later-FIST path may run only when all of the following are true:

```text
diagnostics build
actor valid
current C1 generation valid and actor-matched
markerOpcode == FIST
result.opcode == FIST
result.code == UNSUPPORTED_MISSING_SOURCE
current family == Quick Hit
matching motion found
marker scan valid
marker present
hasFistMarkers == true
decision.markerCounts[FIST] == 2
decision.markerCounts[RIGHT] == 0
decision.markerCounts[LEFT] == 0
decision.markerCounts[BOTH] == 0
decision.markerCounts[OFF] == 0
requiredSourceMask == None
raw8 Fist resolver absent
current factual RIGHT source exists
result RIGHT source == current factual RIGHT source
RIGHT UseType == PhysicalFist/raw55
RIGHT collision group == Item_Attack/group7
StatePosition == 1
```

The execution must also have the already-proven first pre-state FIST intervention for the **same actor + exact RIGHT source + C1 generation**.

The temporary observer must identify this as the **first later eligible FIST dispatch after that proven first intervention**. The later-FIST intervention is one-shot for that actor/source/C1.

Do not require or read the unavailable generic fields:

```text
authoredMarkerCount
acceptedMarkerCountBefore
acceptedMarkerCountAfter
executionBudgetReset
```

---

## 6. Exact intervention

For the exact eligible later FIST only:

```text
mark later-FIST rearm intervention used for this actor/source/C1

verify exact RIGHT source is still Item_Attack/group7

rightSource.TouchDamage.ClearTriggeredList()
    exactly once
```

That is the entire causal intervention.

### Explicitly forbidden

Do **not** call:

```text
SetCollisionGroup(...)
CollisionSourceOperations::ActivateOrRearm(...)
TriggerTarget(...)
OnDamage(...)
```

Do not issue any second `7 -> 7` or other collision-group request from the authored later FIST.

---

## 7. Preserve unchanged

Preserve unchanged:

```text
EV-269 first pre-state FIST eligibility and 5 -> 7 + clear
original Quick callback execution exactly once
later native Quick 7 -> 7 request
native StatePosition progression
EV-265 selective 5 -> 7 suppression behavior where applicable
existing post-state EV-267 path for its old fixture
native 7 -> 5 cleanup
C1 lifecycle accounting/finalization
stable FrameCollisionMarkers occurrence/dedupe behavior
Raw8FistCollision
equipped marker behavior
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
EngineBridge hook ownership / RVAs
CMake/build separation
```

Do not change Normal/Sprint raw55 temporary behavior and do not add Power support in this task.

---

## 8. Diagnostics

Add one concise CORE record for the exact later-FIST intervention:

```text
CORE RAW55_QUICK_REPEAT_FIST_REARM_PROBE
```

Log at minimum:

```text
Actor
C1
Action
StatePosition
StateTime
Right
RightUseType
RightGroup
DecisionFistCount=2
FirstPreStateProof=1
LaterDispatchOrdinal=2
ClearTriggeredList=1|0
REPEAT_FIST_REARM=1
```

`LaterDispatchOrdinal=2` means only: first proven EV-269 pre-state FIST + first later eligible FIST dispatch in this bounded two-marker diagnostic fixture. It is not a stable generic occurrence ordinal.

`ClearTriggeredList=1` only when the exact source is verified group7 and the clear actually executes.

---

## 9. Runtime interpretation after implementation review/build

### A — repeated rearm PASS

A decisive positive execution contains:

```text
first FIST -> EV-269 5 -> 7 + clear
native Quick 7 -> 7 / StatePosition progression
first OnDamage on contact
later FIST -> exact repeat-rearm log, NO group request
second OnDamage after later FIST when contact occurs again
native 7 -> 5 cleanup
clean C1 finalization
```

This proves that, in the controlled two-FIST raw55 Quick fixture, an already-open source can create another contact opportunity using only `ClearTriggeredList()`.

It does **not** prove final production occurrence bookkeeping and does not authorize Power/Normal/Sprint generalization or permanent `PhysicalFistCollision` promotion.

### B — later clear executes but no second contact damage

If a genuine first hit occurs, the exact later FIST clears the triggered list, and repeated observed contact after it still cannot damage in representative executions:

```text
repeated ClearTriggeredList alone is insufficient
```

Stop and return to Normal Chat.

### C — source/lifecycle diverges

Any unexpected group mutation, lost native `7 -> 5` cleanup, repair, lifecycle issue, state-progression change, or duplicate clear is a contradiction. Stop.

### D — dispatch sequence is ambiguous

If the controlled two-marker fixture produces unexpected extra qualifying FIST dispatches such that the temporary first/later sequence cannot be interpreted cleanly, stop and report the contradiction. Do not add another heuristic.

---

## 10. Production architecture consequence — NOT THIS TASK

The source contradiction establishes a later design requirement:

```text
production raw55 repeated-marker support cannot depend on the current
post-raw8-source-resolution occurrence-consumption position
```

A future architecture task must provide raw55 a factual generic occurrence identity without duplicating permanent counters in `PhysicalFistCollision` and without regressing raw8/equipped behavior.

That future task is explicitly out of scope here.

---

## 11. Work implementation boundary

Expected source change:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

A smallest diagnostics-only header change is allowed only if directly necessary.

Do not modify:

```text
FrameCollisionMarkers.cpp/.h
FrameCollisionShared.h
Raw8FistCollision
CollisionLifecycleGuard
CollisionSources
CollisionSourceOperations
EngineBridge
CMake
```

Build execution is NOT authorized for Work.

Work must source/static audit, commit, push, report and STOP.
