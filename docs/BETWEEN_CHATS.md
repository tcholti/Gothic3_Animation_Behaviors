# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-293 CLOSED; SPRINT-ORIGIN REPEATED-FIST PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-293**. No permanent raw55 implementation is authorized.

Latest canonical evidence:

`docs/EVIDENCE_LEDGER_291_ONWARD.md` — EV-293

Current frozen diagnostic contract:

`docs/COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md`

## Closed Power checkpoint — EV-293

True Power repeated-FIST contact rearm is causally closed for the tested raw55 route.

Representative factual Power C1=6:

```text
EV-275 early native 5 -> 7 suppression
-> original _AI_PowerAttack preserves SP0 -> 1
-> RIGHT remains group5

first authored Power FIST at SP1
-> exact RIGHT 5 -> 7
-> ClearTriggeredList=0
-> first ONDAMAGE
-> PC_Hero visited/count1

second authored Power FIST in same C1/source
-> current Action2 / Family POWER
-> RIGHT already group7
-> PRE PC_Hero present exactly once / count1
-> one ClearTriggeredList()
-> POST PC_Hero absent / aligned arrays
-> later second ONDAMAGE

native 7 -> 5 cleanup
-> outstanding=0
-> clean C1 finalization
```

Independent factual Power C1=52 repeats the same route.

Power conclusion:

```text
marker1 = physical opening only
marker2 = contact-bookkeeping clear only
no second group request required
```

Runtime identity:

```text
implementation:
d3388d5c38c29ea4453259e9efb3fd67916d865e

built/live DLL SHA256:
1EAD1E361755368DF9DAC5C8A068549CFC63BDD95381247F41F1B4BA68693B7E

canonical source:
research/archive/2026.09.17_troll_raw55_power_repeat_fist_rearm.log

source SHA256:
61F572B13D78C25A7363FC85076AEC7FAEC48CD8A51EC540F012D7541D1C42D5

source Git blob:
ffa3777e9a9311afc77af2ffff4e84eb05fa6cdc

source upload + derived package commit:
44abff33303662e7620b5bb961758b9f0a8bedfc

byte-identical archive commit:
5c5617cfdb38f45fb06d326cad722fb6e8a123a7
```

The User visually observed at least two attacks using the shared Power/Sprint animation in which both swings damaged. Because Power and Sprint share the same animation, factual Action2 records — not visual appearance — establish the Power result.

## Sprint-origin causal boundary

### EV-281 — selective early gate

For factual Sprint:

```text
Action9 / Family SPRINT
exact native RIGHT raw55 5 -> requested7 suppressed
original _AI_PowerAttack still advances StatePosition 0 -> 1
RIGHT remains group5
```

### EV-282 — first authored Sprint FIST

```text
same Sprint-origin actor/source/C1
current Action9 / Family SPRINT
StatePosition1
RIGHT group5
-> one real exact RIGHT 5 -> 7 request
-> ClearTriggeredList=0
-> native first damage
```

### EV-283 — same C1 changes label before marker2

Controlled two-FIST Sprint-origin executions prove:

```text
first authored FIST opens RIGHT group7 under Action9
first damage occurs
same C1 / same RIGHT continues
factual Action changes Action9 -> Action2
second authored FIST is delivered under current Action2 / Family POWER
RIGHT remains group7
existing one-shot Sprint activation proof does not act again
separate true-Power proof does not own the Sprint-origin occurrence
```

This transition is the key ownership boundary. Do not use the shared PowerAttack animation name as family identity and do not transfer the second marker to true-Power ownership merely because current Action is 2.

## Frozen next causal question

For the exact later authored FIST in a proven Sprint-origin C1:

```text
SprintEarlySuppressionProof exists
same actor / same exact RIGHT / same current C1
Sprint earlySuppressionProven=1
Sprint activationUsed=1
Sprint repeat rearm not already used
no matching true-Power proof for same actor/source/C1

current factual Action=2 / Family=POWER Hit
StatePosition=1
exactly two authored FIST markers
RIGHT PhysicalFist/raw55 already group7
```

Immediately before intervention require:

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

Capture POST trigger state and correlate with genuine first Sprint-origin `ONDAMAGE`, later second `ONDAMAGE`, native `7 -> 5` cleanup and clean same-C1 finalization.

## Frozen implementation responsibility

Implement ONLY:

`docs/COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md`

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Expected implementation shape:

```text
one per-Sprint-proof/C1 repeatFistRearmUsed flag
+ preserve it only for exact matching Sprint proof refresh
+ reuse existing generic read-only trigger-state capture
+ later-FIST eligibility anchored to Sprint-origin proof
+ current marker factual Action2 / Power Hit
+ same C1/source identity preserved across Action9 -> Action2
+ reject ambiguous matching true-Power proof
+ factual PRE player-visit gate
+ one exact current RIGHT TouchDamage.ClearTriggeredList()
+ factual POST capture/log
```

Preserve EV-281/EV-282/EV-293 unchanged. No second group request. No Action/StatePosition writes. No direct damage. No new hook/RVA. No stable marker/lifecycle/source change. No production raw55 architecture in this task.

Work build execution is prohibited. Work source/static audits, commits/pushes, reports and stops. Normal Chat independently reviews before User-local build.

## Remaining collision order

```text
Sprint-origin repeated-FIST rearm
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
NO permanent raw55 architecture until Sprint repeated-contact closes
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
