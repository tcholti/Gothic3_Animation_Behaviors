# Gothic 3 Animation Behaviors — RAW55 Power Repeated-FIST Rearm Probe

**Status:** FROZEN DIAGNOSTIC CAUSAL-PROBE CONTRACT  
**Date:** 2026-09-17  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Test the remaining repeated-contact question for factual raw55 true Power after EV-274 through EV-276 and EV-283.

Closed facts:

```text
EV-275
native true-Power callback remains required for StatePosition 0 -> 1
exact premature RIGHT raw55 5 -> 7 can be selectively suppressed
RIGHT remains group5

EV-276
first authored Power FIST arrives at StatePosition1
same exact RIGHT raw55 source is group5
probe requests one real 5 -> 7 opening
ClearTriggeredList=0
native first-contact damage occurs
native 7 -> 5 cleanup remains healthy

EV-283
in a controlled two-FIST Power fixture, a later second authored FIST is delivered
in the same C1 after the first authored FIST has already opened RIGHT raw55
and produced native damage
RIGHT is still group7 at the later FIST
existing one-shot activationUsed policy prevents any second intervention
absence of a second hit is therefore inconclusive
```

The unresolved question is purely contact rearm for an already-open exact RIGHT raw55 source.

This is a temporary causal probe, not production behavior.

---

## Single Question

In an exact controlled two-FIST true-Power execution that has already passed the EV-275 early suppression and EV-276 first authored activation in the same actor/source/C1:

```text
first authored FIST
-> exact RIGHT raw55 5 -> 7
-> no probe ClearTriggeredList
-> native first damage
-> player becomes factually visited

later second authored FIST
-> same actor / same C1 / same exact RIGHT raw55 source
-> RIGHT still group7
```

is exactly one:

```text
RIGHT TouchDamage.ClearTriggeredList()
```

at the later authored FIST sufficient to create a second same-C1 damage opportunity, without another collision-group request?

---

## Required Existing Environment

Preserve unchanged:

```text
EV-275 true-Power selective native group5 -> requested7 suppression
original _AI_PowerAttack callback exactly once
native StatePosition 0 -> 1 progression
EV-276 first authored Power FIST activation
first authored exact RIGHT raw55 5 -> 7 through ordinary setter/lifecycle path
first authored FIST ClearTriggeredList=0
native damage/contact ownership
native final exact RIGHT 7 -> 5 cleanup
```

Do not copy Normal's EV-288/EV-291 native suppression mechanisms into Power. They are Normal-specific evidence and are not part of this probe.

---

## Exact Later-FIST Eligibility

The repeated-contact intervention may execute only when all of the following are factually true at the authored marker dispatch:

```text
diagnostics build
actor valid
current C1 generation valid and actor-matched
markerOpcode == FIST
result.opcode == FIST
result.code == UnsupportedMissingSource
factual Action == gEAction_PowerAttack / 2
Family == POWER / Hit eligible
matching current motion found
marker scan valid
marker present
has FIST markers
exactly two authored FIST markers in the current motion
RIGHT / LEFT / BOTH / OFF authored marker counts == 0
requiredSourceMask == none
raw8 Fist resolver absent
existing Power early-suppression proof exists
same actor as that proof
same current C1 generation as that proof
same exact current RIGHT source as that proof
result RIGHT == exact stored/current RIGHT source
RIGHT UseType == PhysicalFist/raw55
RIGHT collision group == Item_Attack / 7
StatePosition == 1
earlySuppressionProven == true
activationUsed == true
repeat-FIST rearm not already used for this actor/source/C1
```

`activationUsed == true` is the factual anchor that the EV-276 first authored Power FIST already occurred in this exact C1. In the controlled exactly-two-FIST fixture, the first later eligible FIST after that activation is the second authored occurrence.

Do not add frame-number, StateTime-range, wall-clock, actor/species/name, filename-token or motion-change heuristics.

If unexpected extra qualifying FIST dispatches make this bounded two-marker sequence ambiguous, preserve the contradiction and stop rather than adding another heuristic.

---

## Required Pre-Clear Contact Gate

Immediately before any repeated-FIST mutation, capture the exact current RIGHT TouchDamage trigger state and require:

```text
CountsAligned == 1
PlayerResolved == 1
PlayerPresent == 1
PlayerEntryCount == 1
PlayerVisitCount >= 1
```

This is mandatory. It proves the first contact is still represented in the exact trigger bookkeeping at the second authored FIST.

If the player is not factually present exactly once, perform no clear. Emit only the smallest exact-candidate observation needed to preserve the factual result; do not compensate with another mutation.

The runtime interpretation must also correlate a genuine first `ONDAMAGE Target=PC_Hero` before the second authored FIST before claiming repeated-contact causality.

---

## Exact Intervention

For one eligible later authored Power FIST per actor/source/C1:

```text
capture PRE factual trigger state
-> mark repeat-FIST rearm used for this exact actor/source/C1
-> call exact current RIGHT TouchDamage.ClearTriggeredList() once
-> allow existing Engine +0x7DDA0 clear hook/observation to observe the diagnostic call normally
-> capture POST factual trigger state
-> emit one compact Power repeated-FIST rearm record
```

Expected immediate factual effect:

```text
PRE  PlayerPresent=1 / PlayerVisitCount>=1
POST PlayerPresent=0
```

The intervention must issue **no collision-group request**. RIGHT must already be group7.

Do not call `CollisionSourceOperations::ActivateOrRearm()` because that would combine responsibilities.

---

## Diagnostic Record

Use:

```text
CORE RAW55_POWER_REPEAT_FIST_REARM_PROBE
```

Include enough facts to reconstruct the intervention:

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
EarlySuppressionProof=1
FirstActivationUsed=1
PlayerPresentBefore
PlayerEntryCountBefore
PlayerVisitCountBefore
CountsAlignedBefore
PostStateCaptured
PlayerPresentAfter
PlayerEntryCountAfter
PlayerVisitCountAfter
CountsAlignedAfter
ClearTriggeredList=1
REPEAT_FIST_REARM=1
```

A compact candidate/non-eligibility record is allowed only if necessary to show why the exact second FIST did not mutate. Do not add broad per-frame logging or raw-array dumps.

---

## Protected Controls / Forbidden Changes

Do NOT:

```text
change EV-275 Power early selective group suppression
change EV-276 first authored Power activation
change the first Power FIST to call ClearTriggeredList
issue any second 7 -> 7 or other collision-group request
suppress another native callback/group request
write StatePosition
write SPU+0x164
call TriggerTarget / OnDamage / direct damage
manually edit EntitiesVisited or EntitiesVisitedCount
change ResetOnUntouch
change native final 7 -> 5 cleanup
change lifecycle/repair policy
change Quick/Normal/Sprint/raw8 behavior
change FrameCollisionMarkers semantics
change CollisionSources semantics
change CollisionSourceOperations semantics
change CollisionLifecycleGuard semantics
add a hook, RVA, timer or polling path
add actor/species/name/filename policy
implement permanent PhysicalFistCollision
promote/copy PhysicalFistProbe into production architecture
perform Sprint repeated-FIST work
perform New Balance regression
perform Raise/speed work
perform AttackContinuationProtection work
```

If exact trigger-state capture cannot be reused/extracted safely inside the diagnostic module without changing stable behavior, stop and report the contradiction rather than broadening.

---

## Smallest Implementation Responsibility

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

The current source already provides:

- `PowerEarlySuppressionProof` with exact actor/source/C1 identity, `earlySuppressionProven`, and `activationUsed`;
- exact Power first-FIST activation eligibility;
- the reserved-marker `OnMarkerProcessed` seam;
- the shared Engine ALL-clear observation hook;
- existing read-only trigger-state capture logic inside the same diagnostic module for Normal.

Expected implementation shape:

```text
add one per-proof/C1 Power repeated-FIST rearm-used flag
+ reuse/extract the smallest read-only exact-trigger state capture needed for Power
  while preserving existing Normal behavior unchanged
+ add exact later-Power-FIST eligibility for the controlled two-FIST fixture
+ require factual PRE player visit
+ one exact current RIGHT TouchDamage.ClearTriggeredList()
+ factual POST capture/log
```

No `EngineBridge.cpp` change is expected.  
No `PhysicalFistProbe.h` API change is expected.  
No new hook/RVA/CMake/production change is expected.

If implementation requires broader source scope or another mutation, STOP and report the contradiction.

---

## Runtime Result Routes

### Route A — repeated rearm / second damage restored

Required facts in one factual true-Power C1:

```text
EV-275 early native 5 -> 7 suppression
native StatePosition 0 -> 1 survives
first authored Power FIST performs real 5 -> 7 with ClearTriggeredList=0
first ONDAMAGE Target=PC_Hero
player becomes visited
second authored Power FIST arrives same C1/source while RIGHT group7
PRE player visited exactly once
one repeat-FIST ClearTriggeredList executes
POST player absent
later second ONDAMAGE Target=PC_Hero when contact occurs
native 7 -> 5 cleanup
clean C1 finalization
```

Conclusion:

> For the tested controlled two-FIST raw55 true-Power route, an already-open exact RIGHT source can create the authored second contact opportunity using only one `ClearTriggeredList()` at the second FIST; no second physical group request is required.

This closes Power repeated-FIST contact rearm, but does not authorize permanent raw55 architecture until Sprint repeated-contact work also closes.

### Route B — clear succeeds, second damage absent

If factual first damage/visit exists, the exact second-FIST clear executes and removes the player visit, but representative repeated contact still cannot produce a second damage:

> Power repeated `ClearTriggeredList()` alone is insufficient; another eligibility mechanism remains.

Do not broaden the intervention in the same probe.

### Route C — player already absent before second FIST

If the exact second authored FIST arrives after genuine first damage but PRE state already has no player visit:

> Power has a native between-contact reset mechanism in the tested route. The direct authored-clear causal question is not yet isolated.

Do not clear redundantly. Preserve the observation and isolate the native reset first.

### Route D — structural contradiction

If source state, StatePosition progression, cleanup, C1 identity/finalization or family behavior diverges materially:

> Preserve the contradiction and isolate it before permanent design.

---

## Build Policy

Work build execution is **not authorized** by this contract.

Work performs source/static audit only, publishes the smallest diagnostics-only implementation on the active branch, reports final remote commit SHA + changed files + concise result + build status + any material contradiction, and stops.

Normal Chat independently reviews the published diff before any User-local build/deploy/runtime validation.
