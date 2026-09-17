# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-293 CLOSED; SPRINT-ORIGIN REPEATED-FIST IMPLEMENTED + SOURCE-REVIEW PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-293**. No permanent raw55 implementation is authorized.

Latest canonical evidence:

`docs/EVIDENCE_LEDGER_291_ONWARD.md` — EV-293

Current frozen diagnostic contract:

`docs/COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md`

## Closed Power checkpoint — EV-293

True Power repeated-FIST contact rearm is causally closed for the tested raw55 route:

```text
first authored Power FIST at SP1 -> exact RIGHT 5 -> 7, ClearTriggeredList=0, first damage
second authored Power FIST in same C1/source -> PRE PC_Hero visited -> one ClearTriggeredList -> POST absent -> second damage
native 7 -> 5 cleanup -> clean C1
```

Power marker1 owns the single physical opening; marker2 owns contact-bookkeeping clear only.

## Sprint-origin causal boundary

Canonical Sprint evidence remains:

```text
EV-281
Action9 / Family SPRINT early exact RIGHT raw55 5 -> 7 is selectively suppressed
original _AI_PowerAttack still advances StatePosition 0 -> 1
RIGHT remains group5

EV-282
first authored Sprint FIST under Action9 / Sprint / SP1
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=0
-> native first damage

EV-283
same C1 / same exact RIGHT continues
-> factual Action9 -> Action2 transition
-> later second authored FIST arrives under current Action2 / Family POWER
-> RIGHT remains group7
```

The second marker therefore remains owned by the factual Sprint-origin actor/source/C1 proof, not by visual animation identity or current Action2 alone.

## Current implementation under local validation

Implementation commit:

```text
32dc52dcba327e74436dcd76b70b21251e06565c
```

Frozen base:

```text
aedc129a09f0eebc4d00c55106848f21f5d8c147
```

Normal Chat independent source review: **PASS**.

The implementation is exactly one source commit over the frozen base and changes only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Review confirms:

- EV-281 Sprint early selective suppression is unchanged;
- EV-282 first authored Sprint activation remains Action9/SP1 `5 -> 7` with `ClearTriggeredList=0`;
- native Action9 -> Action2 progression is not modified;
- EV-293 true-Power repeated-FIST behavior is preserved;
- `SprintEarlySuppressionProof` gains one bounded `repeatFistRearmUsed` flag retained only for matching actor/C1/source identity;
- later eligibility is anchored to that Sprint proof while requiring current factual Action2 / Family POWER Hit;
- same current C1 and exact current RIGHT source are required;
- exactly two FIST markers, zero RIGHT/LEFT/BOTH/OFF, no raw8 resolver, SP1 and RIGHT raw55 group7 are required;
- a matching same-C1 true-Power proof is treated as ambiguous and performs no mutation;
- eligible intervention requires aligned trigger arrays with `PC_Hero` resolved, present exactly once and visit count >=1;
- intervention performs exactly one current-RIGHT `TouchDamage.ClearTriggeredList()` and captures POST state;
- no second collision-group request, Action/StatePosition/SPU write, direct damage, trigger target, manual visited mutation or cleanup compensation was added;
- no hook/RVA/header/CMake/production/stable marker/lifecycle/source change occurred.

`OnMarkerProcessed` ordering preserves ownership:

```text
first Action9 marker -> existing Sprint activation succeeds/returns
later Action2 marker -> Sprint activation fails -> Sprint-origin repeat path evaluates preserved origin proof
true-Power repeat handling remains available only when Sprint-origin path does not own the marker
```

Work build status: **NOT ATTEMPTED — correctly prohibited**.

No material source contradiction found.

## Immediate next responsibility — LOCAL BUILD ONLY

Do not launch another Work task.

1. User syncs GitHub Desktop: **Fetch origin -> Pull origin -> Fetch origin**.
2. Confirm branch `docs/collision-source-evidence` is current and `Changes = 0 changed files`.
3. Build only:

```powershell
cmake --build build --config Release --target Script_FrameCollisionTest
```

4. STOP on build result.
5. If PASS, Normal Chat continues with normal POP-03 deploy/hash/twin verification and POP-04 startup gate before runtime.

Frozen runtime interpretation:

```text
Route A:
Action9 first activation/damage
+ same C1/source becomes Action2 before marker2
+ PRE player visited
+ one Sprint-origin clear
+ POST player absent
+ later second damage
+ native 7 -> 5 cleanup / clean C1
=> Sprint-origin repeated-FIST ownership/rearm PASS

Route B:
clear succeeds but second damage absent
=> ClearTriggeredList alone insufficient

Route C:
first damage exists but player already absent before marker2
=> native between-contact reset exists; isolate

Route D:
matching same-C1 true-Power proof or ownership/transition ambiguity
=> preserve contradiction; no mutation

Route E:
source/state/cleanup/C1 diverges
=> preserve and isolate
```

## Remaining collision order

```text
Sprint-origin repeated-FIST runtime closure
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
