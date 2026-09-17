# Gothic 3 Animation Behaviors — RAW55 Sprint-Origin Repeated-FIST Rearm Probe

**Status:** FROZEN DIAGNOSTIC CAUSAL-PROBE CONTRACT  
**Date:** 2026-09-17  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Test the final family-specific repeated-contact boundary before permanent raw55 architecture is designed.

Closed facts:

```text
EV-281
factual Action9 / Family=SPRINT native early RIGHT raw55 5 -> requested7
can be selectively suppressed while the original _AI_PowerAttack callback
still advances StatePosition 0 -> 1 and RIGHT remains group5

EV-282
first authored Sprint FIST arrives while the same C1 is still factual Action9
at StatePosition1
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=0
-> native first damage
-> native cleanup remains healthy

EV-283
in the controlled two-FIST Sprint-origin fixture:
first FIST is delivered under Action9 / Sprint and opens the source
native first damage follows
then the SAME C1 / SAME source / SAME PowerAttack-named motion transitions
from factual Action9 to factual Action2 before the later second authored FIST
RIGHT remains group7
second FIST is delivered under current Action2
existing Sprint activationUsed one-shot policy performs no second intervention
and the separate true-Power proof does not own that Sprint-origin occurrence

EV-293
for factual true Power / Action2, an already-open raw55 source can create a
second same-C1 contact opportunity using only one later-FIST
TouchDamage.ClearTriggeredList(), with no second group request
```

The unresolved Sprint question is therefore both contact rearm and ownership continuity across a factual same-C1 `Action9 -> Action2` transition.

This is a temporary causal probe, not production behavior.

---

## Single Question

In an exact controlled two-FIST execution that is already proven to have originated as Sprint by the EV-281/EV-282 Sprint proof:

```text
first authored FIST
-> factual Action9 / Family SPRINT
-> exact RIGHT raw55 5 -> 7
-> no probe ClearTriggeredList
-> native first damage

same C1 continues
-> Action9 -> Action2
-> same exact RIGHT source remains group7

later second authored FIST
-> current factual Action2 / Family POWER
-> same actor / same C1 / same exact RIGHT source
-> Sprint-origin proof still identifies the execution
```

is exactly one:

```text
RIGHT TouchDamage.ClearTriggeredList()
```

at that later authored FIST sufficient to create a second same-C1 damage opportunity, without another collision-group request?

The current Action2 label must NOT erase the factual Sprint origin of the C1.

---

## Required Existing Environment

Preserve unchanged:

```text
EV-281 Sprint selective native group5 -> requested7 suppression
original _AI_PowerAttack callback exactly once
native Sprint StatePosition 0 -> 1 progression
EV-282 first authored Sprint FIST activation
first authored exact RIGHT raw55 5 -> 7 through ordinary setter/lifecycle path
first authored Sprint FIST ClearTriggeredList=0
native first-contact damage ownership
same-C1 native Action9 -> Action2 transition
native final exact RIGHT 7 -> 5 cleanup
EV-293 true-Power repeated-FIST behavior
```

Do not convert the Sprint-origin execution into true-Power ownership merely because current Action is 2 at marker2.

---

## Sprint-Origin Identity

The governing origin identity for this probe is the existing `SprintEarlySuppressionProof` created only by the factual Action9 Sprint early-suppression path and consumed by the EV-282 first authored Sprint activation.

The later marker is eligible only if that exact proof still matches:

```text
actor instance
exact RIGHT source instance
C1 generation
earlySuppressionProven == true
activationUsed == true
```

Add one per-proof/C1 `repeatFistRearmUsed` flag so the later intervention can execute at most once.

If a matching true-Power early-suppression proof somehow also exists for the same actor + exact RIGHT source + same C1, treat ownership as ambiguous and perform no mutation. Preserve/log the contradiction rather than guessing which family owns marker2.

Do not use animation filename or visual attack identity as ownership evidence.

---

## Exact Later-FIST Eligibility

The Sprint-origin repeated-contact intervention may execute only when all of the following are factually true at marker dispatch:

```text
diagnostics build
actor valid
current C1 generation valid and actor-matched
existing SprintEarlySuppressionProof exists
same actor as Sprint proof
same current C1 generation as Sprint proof
same exact current RIGHT source as Sprint proof
Sprint proof earlySuppressionProven == true
Sprint proof activationUsed == true
Sprint proof repeatFistRearmUsed == false
no matching true-Power proof for same actor/source/C1

markerOpcode == FIST
result.opcode == FIST
result.code == UnsupportedMissingSource

current factual Action == gEAction_PowerAttack / 2
current attack ownership == Family POWER / Hit eligible
StatePosition == 1

matching current motion found
marker scan valid
marker present
has FIST markers
exactly two authored FIST markers in the current motion
RIGHT / LEFT / BOTH / OFF authored marker counts == 0
requiredSourceMask == none
raw8 Fist resolver absent

exact current RIGHT source exists
result RIGHT == exact stored/current RIGHT source
RIGHT UseType == PhysicalFist/raw55
RIGHT collision group == Item_Attack / 7
```

The unusual combination is intentional:

```text
origin proof = Sprint / Action9
current marker state = Power / Action2
C1 + source identity = unchanged
```

That is the EV-283 boundary being tested.

Do not require current Action9 at marker2; doing so would erase the known same-C1 transition and make the probe incapable of testing the established Sprint route.

Do not add frame-number, StateTime-range, wall-clock, actor/species/name, filename-token, or motion-change heuristics.

---

## Required Pre-Clear Contact Gate

Immediately before any mutation, capture the exact current RIGHT TouchDamage trigger state using the existing diagnostic read-only trigger-state capture helper and require:

```text
CountsAligned == 1
PlayerResolved == 1
PlayerPresent == 1
PlayerEntryCount == 1
PlayerVisitCount >= 1
```

This proves that the first Sprint-origin contact is still represented in the exact trigger bookkeeping at the later Action2 FIST.

If the player is not factually present exactly once, perform no clear. Emit only the smallest exact-candidate observation needed to preserve the result.

Runtime interpretation must also correlate a genuine first `ONDAMAGE Target=PC_Hero` after the Action9 first-FIST activation and before marker2 before claiming repeated-contact causality.

---

## Exact Intervention

For one eligible later authored FIST per Sprint-origin actor/source/C1:

```text
capture PRE factual trigger state
-> mark Sprint proof repeat-FIST rearm used
-> call exact current RIGHT TouchDamage.ClearTriggeredList() once
-> capture POST factual trigger state
-> emit one compact Sprint-origin repeated-FIST record
```

Expected immediate effect:

```text
PRE  PlayerPresent=1 / PlayerVisitCount>=1
POST PlayerPresent=0
```

The intervention must issue **no collision-group request**. RIGHT must already be group7 from the first Sprint FIST.

Do not call `CollisionSourceOperations::ActivateOrRearm()`.

---

## Diagnostic Record

Use:

```text
CORE RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE
```

Include enough facts to reconstruct the cross-action ownership:

```text
Actor
C1
CurrentAction=2
CurrentFamily=POWER
StatePosition
StateTime
Right
RightUseType
RightGroup
DecisionFistCount=2
SprintOriginProof=1
FirstSprintActivationUsed=1
SameC1=1
SameRight=1
MatchingPowerProof=0
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

A compact candidate/non-eligibility record is allowed only for the exact controlled later-FIST candidate when necessary to show why no mutation occurred.

Do not add broad per-frame logging or raw-array dumps.

---

## Protected Controls / Forbidden Changes

Do NOT:

```text
change EV-281 Sprint early selective suppression
change EV-282 first authored Sprint activation
change the first Sprint FIST to call ClearTriggeredList
change native Action9 -> Action2 progression
write Action or force family identity
issue any second 7 -> 7 or other collision-group request
change EV-293 true-Power repeated-FIST behavior
let the true-Power proof claim a Sprint-origin marker2
suppress another native callback/group request
write StatePosition
write SPU+0x164
call TriggerTarget / OnDamage / direct damage
manually edit EntitiesVisited or EntitiesVisitedCount
change ResetOnUntouch
change native final 7 -> 5 cleanup
change lifecycle/repair policy
change Quick/Normal/raw8 behavior
change FrameCollisionMarkers semantics
change CollisionSources semantics
change CollisionSourceOperations semantics
change CollisionLifecycleGuard semantics
add a hook, RVA, timer or polling path
add actor/species/name/filename policy
implement permanent PhysicalFistCollision
promote/copy PhysicalFistProbe into production architecture
perform New Balance regression
perform Raise/speed work
perform AttackContinuationProtection work
```

---

## Smallest Implementation Responsibility

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

The current source already provides:

- `SprintEarlySuppressionProof` with exact actor/source/C1 identity, `earlySuppressionProven`, and `activationUsed`;
- EV-282 first Sprint FIST activation eligibility;
- EV-293 generic read-only exact-trigger state capture helper;
- the reserved-marker `OnMarkerProcessed` seam;
- current exact Power repeated-FIST probe, which must remain unchanged.

Expected implementation shape:

```text
add one per-Sprint-proof/C1 repeatFistRearmUsed flag
+ preserve that flag when the exact same Sprint proof is refreshed
+ add exact Sprint-origin / current-Action2 later-FIST eligibility
+ reject ambiguous matching true-Power proof for same actor/source/C1
+ require factual PRE player visit
+ one exact current RIGHT TouchDamage.ClearTriggeredList()
+ factual POST capture/log
```

Ordering in `OnMarkerProcessed` must preserve EV-282 first activation unchanged. A natural bounded shape is:

```text
TryApplySprintFistActivationProbe(...)
-> on first Action9 FIST it succeeds/returns
-> on later Action2 FIST it fails by current Action
TryApplySprintOriginRepeatFistRearmProbe(...)
-> may then evaluate the same Sprint proof across Action9 -> Action2
```

No `EngineBridge.cpp` change is expected.  
No `PhysicalFistProbe.h` API change is expected.  
No new hook/RVA/CMake/production change is expected.

If implementation requires broader source scope or another mutation, STOP and report the contradiction.

---

## Runtime Result Routes

### Route A — Sprint-origin repeated rearm / second damage restored

Required facts in one factual Sprint-origin C1:

```text
EV-281 Action9 early native 5 -> 7 suppression
native StatePosition 0 -> 1 survives
first authored Sprint FIST under Action9 performs real 5 -> 7
first Sprint FIST ClearTriggeredList=0
first ONDAMAGE Target=PC_Hero
same C1 / same RIGHT later transitions Action9 -> Action2
second authored FIST arrives under current Action2 while RIGHT remains group7
Sprint-origin proof still matches same actor/source/C1
PRE player visited exactly once
one Sprint-origin repeat-FIST ClearTriggeredList executes
POST player absent
later second ONDAMAGE Target=PC_Hero when contact occurs
native 7 -> 5 cleanup
clean C1 finalization
```

Conclusion:

> For the tested controlled two-FIST Sprint-origin raw55 route, authored repeated-marker ownership survives the same-C1 Action9 -> Action2 transition. The already-open exact RIGHT source can create the second contact opportunity using only one `ClearTriggeredList()` at marker2; no second physical group request is required.

This closes the final family-specific repeated-contact question and returns responsibility to Normal Chat permanent raw55 architecture synthesis.

### Route B — clear succeeds, second damage absent

If factual first damage/visit exists, marker2 clear executes and removes the visit, but representative repeated contact still cannot damage:

> Sprint-origin repeated `ClearTriggeredList()` alone is insufficient; another eligibility mechanism remains.

Do not broaden the intervention in the same probe.

### Route C — player already absent before marker2

If genuine first damage exists but PRE marker2 state already has no player visit:

> Sprint-origin route has a native between-contact reset before the second marker. Direct authored-clear causality is not isolated.

Do not clear redundantly; preserve and isolate the reset.

### Route D — origin/transition contradiction

If the controlled Sprint-origin execution loses C1/source identity, never reaches factual Action2 at marker2, unexpectedly acquires a matching true-Power proof in the same C1, or otherwise makes ownership ambiguous:

> Preserve the contradiction and isolate the transition/ownership boundary. Do not infer ownership from the animation name.

### Route E — lifecycle contradiction

If source state, cleanup, C1 finalization, or another family diverges materially, preserve and isolate before permanent design.

---

## Local Runtime Artifact

After independent Normal Chat source review and normal local build/deploy/startup gates, use the same controlled two-FIST Troll fixture.

Frozen source filename:

```text
research/raw/2026.09.17_troll_raw55_sprint_origin_repeat_fist_rearm.log
```

The user does not need to identify Sprint visually. Power and Sprint use the same animation in this fixture; factual Action9 origin + same-C1 Action2 marker2 records are authoritative.

---

## Build Policy

Work build execution is **not authorized** by this contract.

Work performs source/static audit only, publishes the smallest diagnostics-only implementation on the active branch, reports final remote commit SHA + changed files + concise result + build status + any material contradiction, and stops.

Normal Chat independently reviews the published diff before any User-local build/deploy/runtime validation.
