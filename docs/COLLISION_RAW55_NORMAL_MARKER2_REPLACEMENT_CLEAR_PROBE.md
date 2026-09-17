# Gothic 3 Animation Behaviors — RAW55 Normal Marker-2 Replacement-Clear Probe

**Status:** FROZEN DIAGNOSTIC CAUSAL-PROBE CONTRACT  
**Date:** 2026-09-17  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Test whether the later authored Normal `G3AB_COL_FIST` can own the second same-C1 contact rearm by replacing the exact native between-contact `ClearTriggeredList()` whose causal necessity was proven by EV-291.

EV-291 established the causal baseline:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList()
-> first damage
-> PC_Hero becomes visited/count1

native Normal transition
-> exact native 7 -> 7 setter suppression fires
-> exact native ALL ClearTriggeredList from Script_Game.dll +0x386C6 arrives
-> suppression fires
-> native clear is skipped
-> PC_Hero remains visited/count1
-> original _AI_Attack completes SP0 -> 1

marker2 later
-> observational only
-> PC_Hero still visited/count1
-> second damage disappears

native exact RIGHT 7 -> 5 cleanup
-> clean C1 finalization
```

This probe changes exactly one thing relative to EV-291: at the factual later authored FIST, perform one replacement `ClearTriggeredList()` on the exact current RIGHT raw55 trigger.

This is a temporary causal probe, not production behavior.

---

## Single Question

With EV-291's exact native clear suppression preserved, does one authored marker-2 replacement `ClearTriggeredList()` restore Normal's second same-C1 damage opportunity?

### Interpretation

If:

```text
hit1 survives
+ exact native ALL clear remains suppressed
+ player remains visited through SP0 -> 1
+ marker2 arrives in same C1 on exact current RIGHT raw55 group7
+ player is factually still visited immediately before marker2 intervention
+ marker2 replacement ClearTriggeredList executes once
+ player is absent from visited state afterward
+ hit2 returns
+ native 7 -> 5 cleanup / clean C1 remain healthy
```

then authored Normal marker2 triggered-list rearm ownership is causally proven for the tested route.

If the replacement clear executes and factually clears the player visit but hit2 still does not occur, another Normal eligibility mechanism remains necessary; preserve that contradiction and continue causal isolation.

If source/progression/cleanup diverges materially, stop and preserve the contradiction rather than compensating with another mutation.

---

## Required Existing Environment

Preserve the complete tested EV-291 route unchanged:

```text
frame-1 FIST at SP0
-> exact RIGHT raw55 5 -> 7
-> existing marker-owned ClearTriggeredList()
-> preStateRearmProven = true

first native damage opportunity
-> PC_Hero factually enters visited/count arrays

existing EV-288 exact native RIGHT 7 -> 7 setter suppression

existing EV-291 exact native ALL-clear suppression
-> Engine +0x7DDA0
-> caller Script_Game.dll +0x386C6
-> player factually visited
-> SUPPRESS_CLEAR=1
-> original clear skipped

original _AI_Attack continues SP0 -> 1
-> exact RIGHT remains group7
-> player remains visited

later authored FIST
-> this probe's only new intervention point

native final exact RIGHT 7 -> 5 cleanup
```

Do not weaken, remove or broaden either existing native suppression.

---

## Exact Marker-2 Eligibility

The replacement clear may execute only when all of the following are factually true at the later marker dispatch:

```text
markerOpcode == FIST
result.opcode == FIST
result.code == UnsupportedMissingSource
factual Action == gEAction_Attack / 1
Family == NORMAL / Hit eligible
valid current C1 generation
same actor as NormalPreStateFistIntervention
same exact current RIGHT source as stored intervention
RIGHT UseType == PhysicalFist/raw55
RIGHT collision group == Item_Attack / 7
StatePosition == 1
preStateRearmProven == true
nativeRearmSuppressionUsed == true
nativeTriggerClearSuppressionUsed == true
replacement clear not already used for this C1
matching current motion found
marker scan valid
marker present
has FIST markers
exactly two authored FIST markers in the current motion
RIGHT/LEFT/BOTH/OFF authored marker counts == 0
requiredSourceMask == none
raw8 Fist resolver absent
result RIGHT == exact stored/current RIGHT source
```

This must be the same factual C1 and source identity established by the first-FIST intervention and the EV-291 suppression path. Do not use animation name, species, timer range or approximate ordering as identity.

---

## Required Pre-Clear Contact Gate

Immediately before the marker-2 replacement clear, capture the existing exact Normal trigger state and require:

```text
CountsAligned == 1
PlayerResolved == 1
PlayerPresent == 1
PlayerEntryCount == 1
PlayerVisitCount >= 1
```

This proves that the replacement operation is actually rearming the contact state left intentionally uncleared by EV-291.

If these facts are not present, do not clear and do not compensate. Log/retain the factual non-eligibility only if existing diagnostics already make it visible; otherwise fail closed.

---

## Replacement Behavior

For one eligible later authored FIST per C1:

```text
observe/capture PRE factual trigger state
-> mark replacement-clear intervention used for this exact C1
-> call exact current RIGHT TouchDamage.ClearTriggeredList() once
-> allow the existing Engine +0x7DDA0 hook to observe the diagnostic clear normally
-> capture/verify POST factual trigger state
-> emit one compact marker2 replacement-clear diagnostic record
```

Expected immediate factual effect:

```text
PRE  PlayerPresent=1 / PlayerVisitCount>=1
POST PlayerPresent=0
```

The replacement clear must execute normally. The existing EV-291 native-clear suppression gate is caller-specific to `Script_Game.dll +0x386C6`; it must not suppress this diagnostic authored clear from `Script_FrameCollisionTest.dll`.

Do not directly edit `EntitiesVisited` or `EntitiesVisitedCount`.

---

## Suggested Diagnostic

Use a compact record family such as:

```text
CORE RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE
```

Include enough factual fields to reconstruct the intervention:

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
NativeClearSuppressionUsed
PlayerPresentBefore
PlayerEntryCountBefore
PlayerVisitCountBefore
CountsAlignedBefore
PlayerPresentAfter
PlayerEntryCountAfter
PlayerVisitCountAfter
CountsAlignedAfter
DecisionFistCount
MARKER2_REPLACEMENT_CLEAR=1
```

Existing `RAW55_NORMAL_TRIGGER_CLEAR_OBSERVATION` PRE/POST records from the shared hook remain useful evidence for the actual call. Do not add stack dumps or broad array dumps.

---

## Protected Controls / Boundaries

Do NOT:

```text
change marker1 behavior
remove/change EV-288 native 7 -> 7 suppression
remove/change EV-291 native ALL-clear suppression
allow the native Script_Game.dll +0x386C6 clear to execute
perform marker2 replacement clear before factual marker2 dispatch
perform more than one marker2 replacement clear in one C1
clear when PC_Hero is not factually present exactly once
request another collision-group transition
write StatePosition
call TriggerTarget / OnDamage / direct damage
manually mutate trigger visited arrays/counts
change ResetOnUntouch
change native final 7 -> 5 cleanup
change lifecycle repair
add a hook or RVA
add polling
add species/name/timer policy
change Quick/Power/Sprint/raw8 behavior
change FrameCollisionMarkers
change CollisionLifecycleGuard
change CollisionSources
implement permanent PhysicalFistCollision
promote/copy PhysicalFistProbe into production architecture
perform Power/Sprint repeated-FIST work
perform New Balance work
perform Raise/speed work
perform AttackContinuationProtection work
```

If the exact marker2 identity or pre-clear player-visit facts cannot be established safely, the probe must fail closed and perform no replacement clear.

---

## Smallest Implementation Responsibility

The current source already provides:

- the `NormalPreStateFistIntervention` same-C1/source anchor;
- `preStateRearmProven`;
- `nativeRearmSuppressionUsed`;
- `nativeTriggerClearSuppressionUsed`;
- read-only Normal trigger-state capture;
- exact later-Normal-FIST observation in `OnMarkerProcessed`;
- the shared `Engine +0x7DDA0` clear hook and PRE/POST observation.

Therefore the expected change is only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Expected internal change:

```text
add one per-C1 marker2 replacement-clear used flag/state
+ strengthen/convert the existing later-Normal-FIST observation seam into the exact bounded replacement-clear intervention
+ log PRE/result/POST facts
```

No `EngineBridge.cpp` change is expected.
No `PhysicalFistProbe.h` API change is expected.
No new hook is expected.
No CMake change is expected.
No production source is expected to change.

If implementation appears to require broader source scope, a new hook, or another mutation, STOP and report the contradiction rather than broadening the task.

---

## Runtime Result Routes

### Route A — hit2 restored

Required facts:

```text
hit1 confirmed
native Script_Game +0x386C6 ALL clear suppressed
player remains visited through SP0 -> 1
marker2 same-C1/source eligibility passes
marker2 PRE player visited/count1+
replacement clear executes once
marker2 POST player absent
hit2 returns
native 7 -> 5 cleanup / clean C1
```

Conclusion:

> Authored Normal marker2 `ClearTriggeredList()` is sufficient to replace Gothic's native between-contact clear and owns the second contact rearm in the tested route.

Only after this proof may Normal's repeated-FIST behavior be treated as causally understood enough for later permanent raw55 design.

### Route B — clear succeeds, hit2 absent

If marker2 factually clears the player visit state but hit2 still does not occur:

> Triggered-list rearm is necessary but not sufficient at authored marker2 timing; another Normal eligibility mechanism remains.

Do not broaden marker2 behavior in the same probe.

### Route C — structural contradiction

If marker2 replacement clear changes callback progression, exact-source state, cleanup or C1 finalization unexpectedly:

> Preserve the contradiction as evidence and isolate it before permanent design.

---

## Build Policy

Work build execution is **not authorized** by this contract.

Work performs source/static audit only, publishes the smallest diagnostics-only implementation on the active branch, reports final remote commit SHA + changed files + concise result + build status + any material contradiction, and stops.

Normal Chat independently reviews the published diff before any User-local build/deploy/runtime validation.
