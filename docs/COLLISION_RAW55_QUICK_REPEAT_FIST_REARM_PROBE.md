# RAW55 Quick Repeated-FIST Rearm Probe

**Status:** FROZEN DIAGNOSTICS-ONLY CAUSAL PROBE  
**Date:** 2026-09-13  
**Branch:** `docs/collision-source-evidence`

## 1. Single causal question

With EV-269 already proving that the first authored Quick FIST can open/rearm the exact RIGHT `TrollFist` / PhysicalFist/raw55 source and leave it naturally in group7 until Gothic cleanup, is **one later legitimate authored FIST occurrence in the same actor/source/C1** sufficient to create a second contact opportunity by calling `TouchDamage.ClearTriggeredList()` exactly once **without another collision-group request**?

This probe answers only that question.

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

The stable marker engine already provides factual occurrence identity in `MarkerProcessResult`:

```text
authoredMarkerCount
acceptedMarkerCountBefore
acceptedMarkerCountAfter
executionBudgetReset
```

Its same-update duplicate/budget logic remains authoritative and must not be replaced by new raw55-local timing guesses.

---

## 3. Exact fixture

Use the existing diagnostic Quick raw55 fixture only:

```text
Actor: Troll / BlackTroll factual behavior, but NO species/name gate
Family: Quick Hit
Marker vocabulary: FIST only
RIGHT source: factual equipped source
RIGHT UseType: gEUseType_PhysicalFist / raw55
first authored FIST: already handled by EV-269 pre-state path
later authored FIST: exact second accepted FIST occurrence in the same C1
```

The intended runtime animation fixture has exactly two authored FIST markers, e.g. the already-used early + later Quick test.

Do not generalize this probe to Normal, Power, Sprint, raw8, equipped weapon markers, or more than the exact second FIST occurrence.

---

## 4. Frozen eligibility for the second-FIST intervention

The new second-FIST path may run only when all of the following are true:

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
FIST markers present
no RIGHT / LEFT / BOTH / OFF markers
requiredSourceMask == None
raw8 Fist resolver absent
current factual RIGHT source exists
result RIGHT source == current factual RIGHT source
RIGHT UseType == PhysicalFist/raw55
RIGHT collision group == Item_Attack/group7
StatePosition == 1
```

The execution must also have the already-proven first pre-state FIST intervention for the **same actor + exact RIGHT source + C1 generation**.

Occurrence identity must be exact:

```text
authoredMarkerCount == 2
acceptedMarkerCountBefore == 1
acceptedMarkerCountAfter == 2
executionBudgetReset == false
```

Those existing generic marker facts distinguish the real second authored occurrence from a same-update duplicate. Do not add a new time-delta/frame-number/source-motion heuristic.

The second-FIST intervention is one-shot for that actor/source/C1. A repeated callback/duplicate must not clear again.

---

## 5. Exact intervention

For the exact eligible second FIST only:

```text
mark second-FIST rearm intervention used for this actor/source/C1

assert/read exact RIGHT source is still Item_Attack/group7

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

Do not issue any second `7 -> 7` or other collision-group request from the authored second FIST.

---

## 6. Preserve unchanged

The following behavior must remain byte-for-behavior equivalent except for the new second-FIST clear:

```text
EV-269 first pre-state FIST eligibility and 5 -> 7 + clear
original Quick callback execution exactly once
later native Quick 7 -> 7 request
native StatePosition progression
EV-265 selective 5 -> 7 suppression behavior for executions where it is still applicable
existing post-state EV-267 path for its old fixture
native 7 -> 5 cleanup
C1 lifecycle accounting/finalization
stable marker occurrence/dedupe bookkeeping
Raw8FistCollision
equipped FrameCollisionMarkers behavior
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
EngineBridge hook ownership / RVAs
CMake/build separation
```

Do not change Normal/Sprint raw55 temporary behavior and do not add Power support in this task.

---

## 7. Diagnostics

Add one concise CORE record for the exact second-FIST intervention:

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
AuthoredFistCount
AcceptedFistBefore
AcceptedFistAfter
FirstPreStateProof=1
ClearTriggeredList=1|0
REPEAT_FIST_REARM=1
```

`ClearTriggeredList=1` only when the exact source is verified group7 and the clear actually executes.

No verbose/deep-only logger is required for this bounded probe.

---

## 8. Runtime interpretation after implementation review/build

### A — repeated rearm PASS

A decisive positive execution contains:

```text
first authored FIST -> EV-269 5 -> 7 + clear
native Quick 7 -> 7 / StatePosition progression
first OnDamage on contact
second accepted FIST -> exact repeat-rearm log, NO group request
second OnDamage after the second FIST when contact occurs again
native 7 -> 5 cleanup
clean C1 finalization
```

This proves that an already-open raw55 Quick source can author another same-execution contact opportunity using only `ClearTriggeredList()`.

It does **not** yet authorize Power/Normal/Sprint generalization or permanent `PhysicalFistCollision` promotion.

### B — second clear executes but no second contact damage

If a genuine first hit occurs, the exact second FIST clears the triggered list, and repeated observed contact after that second FIST still cannot damage in representative executions:

```text
repeated ClearTriggeredList alone is insufficient
```

Stop and return to Normal Chat. Do not add a second intervention in the same task.

### C — source/lifecycle diverges

Any unexpected group mutation, lost native `7 -> 5` cleanup, repair, lifecycle issue, state-progression change, or duplicate clear is a contradiction. Stop.

### D — exact second occurrence identity cannot be observed

If the existing `MarkerProcessResult` occurrence facts do not identify the second authored FIST as frozen above, stop and report the contradiction. Do not invent alternate timing/dedupe bookkeeping.

---

## 9. Work implementation boundary

Expected source change:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

A smallest diagnostics-only header change is allowed only if directly necessary. No stable module/CMake/bridge change is expected.

Build execution is NOT authorized for Work.

Work must source/static audit, commit, push, report and STOP.
