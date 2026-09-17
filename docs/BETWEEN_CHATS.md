# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-292 CLOSED; POWER REPEATED-FIST REARM PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-292**. No permanent raw55 implementation is authorized.

Latest canonical evidence:

`docs/EVIDENCE_LEDGER_291_ONWARD.md` — EV-292

Current frozen diagnostic contract:

`docs/COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md`

## Closed Normal checkpoint — EV-292

Normal repeated-FIST contact rearm is causally closed for the tested raw55 route:

```text
marker1 owns physical opening + hit1 contact reset
marker2 owns hit2 contact reset
no second marker2 group request
native hidden between-contact clear is unnecessary when authored marker2 owns rearm
native 7 -> 5 cleanup remains healthy
```

Do not generalize Normal's exact state/timing route to other families.

## Reconstructed Power causal boundary

### EV-275 — early physical opening separated from native state progression

For factual `Action=2 / Family=POWER`:

```text
exact native RIGHT raw55 group5 -> requested7 suppressed
original _AI_PowerAttack runs normally
StatePosition 0 -> 1 survives
RIGHT remains group5
```

### EV-276 — first authored FIST activation

At the first authored Power FIST:

```text
same factual actor/source/C1
StatePosition=1
RIGHT PhysicalFist/raw55 group5
-> one ordinary 5 -> 7 request
-> ClearTriggeredList=0
-> native first damage occurs
-> native cleanup later 7 -> 5
-> clean C1
```

Thus first-contact Power does not need a probe-issued clear.

### EV-283 — second authored FIST exists but current policy is one-shot

In the controlled two-FIST Power fixture:

```text
first authored FIST already opened RIGHT raw55 and produced native damage
later second authored FIST is transported in the same C1
RIGHT remains group7
Power proof activationUsed is already true
current one-shot activation probe performs no second intervention
```

Therefore absence of a second hit in that old fixture is not evidence that Power cannot double-hit. The remaining unknown is exactly what contact reset, if any, is needed at the second authored FIST.

## Frozen next causal question

For the exact later authored Power FIST only:

```text
controlled decision has exactly two FIST markers
same actor / same current C1 / same exact RIGHT as EV-275/276 proof
Action=2 / Family=POWER Hit
StatePosition=1
RIGHT PhysicalFist/raw55 already group7
earlySuppressionProven=1
activationUsed=1
repeat rearm not already used
```

Immediately before intervention require factual exact-trigger state:

```text
CountsAligned=1
PlayerResolved=1
PlayerPresent=1
PlayerEntryCount=1
PlayerVisitCount>=1
```

Then perform exactly:

```text
RIGHT TouchDamage.ClearTriggeredList()
```

once, with no collision-group request.

Capture POST trigger state and correlate runtime with genuine first `ONDAMAGE`, later second `ONDAMAGE`, native `7 -> 5` cleanup and clean C1 finalization.

Interpretation:

```text
PRE visited
+ clear once
+ POST absent
+ later second damage
+ cleanup healthy
    => Power repeated-FIST contact rearm PASS

PRE visited
+ clear succeeds
+ repeated contact still cannot damage
    => ClearTriggeredList alone insufficient

first damage exists but PRE player already absent before marker2
    => Power has a native between-contact reset; isolate before authored-clear causality

source/state/cleanup/C1 diverges
    => preserve contradiction and isolate
```

## Frozen implementation responsibility

Implement ONLY:

`docs/COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md`

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Expected implementation shape:

```text
one per-proof/C1 repeat-FIST-rearm-used flag
+ smallest internal read-only exact-trigger state capture reuse/extraction
+ exact controlled second-Power-FIST gating
+ factual PRE player-visit gate
+ one exact current RIGHT TouchDamage.ClearTriggeredList()
+ factual POST capture/log
```

No `EngineBridge.cpp` change expected.  
No header API change expected.  
No new hook/RVA/CMake/production change expected.

Do not change EV-275 early suppression or EV-276 first-FIST activation. Do not add a second group request. Do not touch Quick/Normal/Sprint/raw8 behavior.

If broader source scope or another mutation is required, STOP and report the contradiction.

Work build execution is prohibited. Work source/static audits, commits/pushes, reports and stops. Normal Chat independently reviews before User-local build.

## Remaining collision order

```text
Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO Sprint repeated-FIST intervention yet
NO permanent raw55 architecture until Power + Sprint close
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
