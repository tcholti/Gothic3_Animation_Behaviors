# RAW55 Quick Repeated-FIST Eligibility Observability Probe

**Status:** FROZEN DIAGNOSTICS-ONLY OBSERVABILITY PROBE  
**Date:** 2026-09-13  
**Branch:** `docs/collision-source-evidence`

## 1. Single question

Why does the later authored raw55 Quick FIST, which is visibly delivered in the same C1 at `StatePosition=1` while the exact RIGHT PhysicalFist/raw55 source is still group7, fail to enter the revised repeated-FIST rearm intervention?

This task observes only the eligibility boundary. It must not change collision behavior.

---

## 2. Evidence boundary

Closed facts:

```text
EV-269
    first frame-1 FIST at StatePosition 0
    exact RIGHT raw55 5 -> 7
    one ClearTriggeredList
    later native 7 -> 7
    StatePosition 0 -> 1
    damage on contact
    native cleanup 7 -> 5

EV-270
    later FIST is delivered in the same Quick C1

EV-272
    revised repeated-FIST implementation exists
    later FIST is again delivered at StatePosition 1
    RIGHT raw55 remains group7
    but CORE RAW55_QUICK_REPEAT_FIST_REARM_PROBE never appears
    therefore the second ClearTriggeredList never executes
    repeated rearm primitive remains untested
```

Do not interpret the User's one-hit-per-Quick observation as failure of `ClearTriggeredList()` rearm. The intervention was not reached.

---

## 3. Exact scope

Diagnostics build only.

Expected source change:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

A smallest diagnostics-only header change is allowed only if directly necessary.

No stable module change is expected or authorized.

---

## 4. Frozen observability boundary

At `PhysicalFistProbe::OnMarkerProcessed()` / the repeated-FIST helper, when a raw55 Quick FIST reaches the probe after an actor has an existing `QuickPreStateFistIntervention` record, emit one concise CORE eligibility record before the repeated-FIST intervention returns for a failed predicate.

The diagnostic must expose factual values only; it must not mutate them.

Log:

```text
CORE RAW55_QUICK_REPEAT_FIST_ELIGIBILITY
```

Minimum fields:

```text
Actor
Action
StatePosition
StateTime
MarkerOpcode
ResultCode

CurrentC1Valid
CurrentC1
StoredC1
SameC1=1|0

CurrentRight
StoredRight
SameRight=1|0
ResultRightMatchesStored=1|0
RightUseType
RightGroup

InterventionUsed=1|0
PreStateFistProven=1|0
LaterFistRearmUsed=1|0

DecisionFoundMotion=1|0
DecisionScanValid=1|0
DecisionMarkerPresent=1|0
DecisionHasFist=1|0
DecisionFistCount
DecisionRightCount
DecisionLeftCount
DecisionBothCount
DecisionOffCount
RequiredSourceMask
Raw8ResolverAbsent=1|0
QuickHit=1|0

Eligible=1|0
FirstFailedGate=<stable concise token>
```

Use stable concise gate tokens, for example:

```text
NONE
NO_CURRENT_C1
C1_MISMATCH
SOURCE_MISMATCH
FIRST_INTERVENTION_UNUSED
FIRST_PROOF_MISSING
LATER_ALREADY_USED
WRONG_OPCODE
WRONG_RESULT
NOT_QUICK_HIT
MOTION_NOT_FOUND
SCAN_INVALID
MARKER_NOT_PRESENT
NO_FIST
FIST_COUNT_NOT_TWO
MIXED_MARKERS
REQUIRED_MASK_NONZERO
RAW8_PRESENT
RESULT_RIGHT_MISMATCH
RIGHT_INVALID
RIGHT_NOT_RAW55
RIGHT_NOT_GROUP7
STATEPOSITION_NOT_ONE
```

The exact implementation may use equivalent stable tokens if they preserve one-to-one meaning.

### Logging cadence

Do not spam every Quick callback.

Emit this record only for actual `FIST` dispatches that reach `OnMarkerProcessed()` when an existing pre-state intervention record is present for that actor.

A first-FIST dispatch may therefore produce an eligibility record if the record already exists by the time this diagnostic point is reached, but the primary runtime target is the later frame-15 FIST. Keep output bounded to marker dispatches, not frames/callbacks.

---

## 5. Absolutely no behavior change

This probe is observability-only.

Do not alter:

```text
first EV-269 FIST behavior
revised repeated-FIST intervention eligibility
ClearTriggeredList calls
SetCollisionGroup calls
native Quick callback
native 7 -> 7
StatePosition progression
native 7 -> 5 cleanup
CollisionLifecycleGuard
FrameCollisionMarkers
Raw8FistCollision
CollisionSources
CollisionSourceOperations
EngineBridge
CMake
Normal/Sprint/Power temporary raw55 behavior
```

Do not add:

```text
new collision-group request
new ClearTriggeredList call
custom/direct damage
TriggerTarget / OnDamage
StatePosition/SPU write
manual cleanup
new occurrence counter
frame/time dedupe heuristic
new hook/RVA/timer/polling
species/name/source-name policy
```

---

## 6. Runtime interpretation

### A — scanned FIST count blocks eligibility

If the later FIST shows all important actor/source/C1/state/group facts matching but:

```text
DecisionFistCount != 2
FirstFailedGate=FIST_COUNT_NOT_TWO
```

then the next Normal Chat responsibility is to reconcile scanner-visible authored count with observed runtime delivery of two FIST dispatches. Do not relax the gate automatically.

### B — stored proof/source/C1 blocks eligibility

If a stored identity/proof gate fails, isolate that factual lifetime/bookkeeping mismatch next. Do not compensate with frame/time heuristics.

### C — another explicit gate blocks eligibility

Freeze the smallest causal question for that exact gate only.

### D — Eligible=1 but intervention log still absent

That is an implementation/control-flow contradiction. Stop and inspect source; do not add another intervention.

---

## 7. Work boundary

Build execution is NOT authorized for Work.

Work must:

```text
source/static audit
implement only bounded CORE eligibility logging
commit
push
report final remote SHA / changed files / result / build status / contradiction
STOP
```
