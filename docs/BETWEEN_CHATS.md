# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-292 CLOSED; POWER REPEATED-FIST PROBE IMPLEMENTED + SOURCE-REVIEW PASS

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

## Power causal boundary

Canonical Power evidence remains:

```text
EV-275
exact premature native RIGHT raw55 5 -> 7 suppressed
original _AI_PowerAttack still advances StatePosition 0 -> 1
RIGHT remains group5

EV-276
first authored Power FIST at StatePosition1
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=0
-> native first damage
-> native final 7 -> 5 cleanup remains healthy

EV-283
controlled two-FIST Power fixture transports a later second authored FIST
in the same C1 after first authored activation/damage
RIGHT remains group7
existing activationUsed one-shot prevented any second intervention
```

Thus the remaining Power question is contact rearm only.

## Current implementation under local validation

Implementation commit:

```text
d3388d5c38c29ea4453259e9efb3fd67916d865e
```

Frozen base:

```text
f5559a38866a7781be3de4e8ac8847b1a1f531c7
```

Normal Chat independent source review: **PASS**.

The implementation is exactly one source commit over the frozen base and changes only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Review confirms:

- existing EV-275 Power early selective `5 -> 7` suppression is preserved;
- original `_AI_PowerAttack` callback and native `StatePosition 0 -> 1` progression are untouched;
- existing EV-276 first authored Power activation remains `5 -> 7` with `ClearTriggeredList=0`;
- `PowerEarlySuppressionProof` gains one bounded `repeatFistRearmUsed` flag preserved only for matching actor/C1/source identity;
- existing Normal trigger-state capture is safely factored through a generic read-only helper while the old Normal wrapper and callers remain intact;
- later Power intervention requires exact current actor/C1/current RIGHT/source identity, Action2/Power Hit, exactly two FIST markers, group7, StatePosition1, prior suppression proof and first activation proof;
- intervention also requires exact PRE trigger state with aligned arrays, `PC_Hero` resolved and present exactly once, and visit count >=1;
- failed exact candidate emits observation only and performs no mutation;
- eligible intervention marks the exact proof one-shot, performs exactly one `RIGHT TouchDamage.ClearTriggeredList()`, captures POST state and logs one compact Power repeat-FIST record;
- no second `SetCollisionGroup` request exists in the new path;
- no direct damage, TriggerTarget, StatePosition/SPU mutation, manual visited-array mutation or cleanup compensation was added;
- `EngineBridge`, headers, hooks/RVAs, CMake, production modules, Quick, Sprint and stable marker/lifecycle modules are unchanged.

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

Frozen runtime question after deployment:

```text
first Power authored FIST -> real 5 -> 7 / no probe clear / first damage
later second Power authored FIST -> same C1/source, RIGHT group7
PRE PC_Hero still visited exactly once
-> one ClearTriggeredList only
-> POST player absent

Does a later second ONDAMAGE return while native 7 -> 5 cleanup and clean C1 finalization remain healthy?
```

Interpretation remains exactly the frozen contract:

```text
Route A: clear removes visit + hit2 returns + cleanup healthy
    => Power repeated-FIST contact rearm PASS

Route B: clear removes visit but hit2 remains absent
    => ClearTriggeredList alone insufficient

Route C: genuine hit1 exists but player already absent before marker2
    => native Power between-contact reset exists; isolate first

Route D: source/state/cleanup/C1 diverges
    => preserve contradiction and isolate
```

## Remaining collision order

```text
Power repeated-FIST runtime closure
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
