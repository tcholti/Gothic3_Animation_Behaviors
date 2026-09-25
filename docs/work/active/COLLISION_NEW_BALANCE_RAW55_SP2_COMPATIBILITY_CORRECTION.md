# Gothic 3 — New Balance raw55 SP2 Compatibility Correction

**Status:** ACTIVE  
**Opened:** 2026-09-25  
**Task type:** BOUNDED PRODUCTION IMPLEMENTATION  
**Work build execution:** PROHIBITED  
**Owner:** `PhysicalFistCollision`

## Purpose

Implement only the smallest evidence-backed compatibility correction required by EV-376, with EV-377 as the cross-mechanism Sprint control.

This is **not a redesign** and **not a new feature mechanism**. Research has already established that the existing permanent raw55 owner, execution identity, native-opening suppression and Sprint-origin continuity are correct. New Balance / AttackCollision only changes the factual Power callback progression so a valid already-owned raw55 FIST may arrive at `StatePosition=2`.

Work must preserve the existing architecture and express only that compatibility fact.

## Required read order

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this task
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/FEATURE_DEVELOPMENT_METHOD.md`
6. `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
7. `docs/COLLISION_TEST_PLAN.md` §4.4
8. only the exact source required by this task

Use EV-376 only when exact failure proof is needed. EV-377 establishes that equipped Sprint and raw8 Sprint remain healthy under New Balance and must not be altered.

## Frozen factual basis

EV-376 establishes:

```text
true Power raw55, single FIST
  exact owned execution survives
  early native opening was suppressed
  sole authored FIST may arrive at SP2
  current SP1-only first-FIST gate rejects it

true Power raw55, double FIST
  marker1 arrives at SP1 and is accepted
  marker2 in the same C1 may arrive at SP2
  current SP1-only second-FIST gate rejects it

Sprint-origin raw55, double FIST
  marker1 = factual Action9 / SPRINT / SP1 and is accepted
  same C1 continues to factual Action2 / POWER
  marker2 may arrive at SP2
  immutable origin remains Sprint
  current SP1-only continuation gate rejects it
```

EV-377 establishes that the New Balance environment does not require redesign of neighboring mechanisms:

```text
equipped Sprint = healthy
raw8 Sprint = healthy
raw8 persistent opportunity = healthy
same-C1 Action9 -> Action2 transition = legitimate native behavior
```

## Responsibility

Modify only the existing raw55 first/second FIST state acceptance necessary to recognize explicit Power `StatePosition` values `{1,2}` inside an already-matched exact `PhysicalFistCollision` execution.

Required semantic result:

```text
TRUE POWER origin — first FIST
current family must still be POWER
StatePosition 1 remains accepted
StatePosition 2 additionally accepted
existing earlyOpeningSuppressed requirement remains mandatory

TRUE POWER origin — second FIST
current family must still be POWER
StatePosition 1 remains accepted
StatePosition 2 additionally accepted

SPRINT origin — first FIST
UNCHANGED:
current family must be SPRINT
StatePosition must be 1
existing earlyOpeningSuppressed requirement remains mandatory

SPRINT origin — later/second FIST after same-C1 continuation
current family must still be POWER
StatePosition 1 remains accepted
StatePosition 2 additionally accepted
```

Use explicit equality for the proven set `{1,2}`. Do **not** generalize to `StatePosition >= 1` or another open-ended range.

## Expected source scope

Expected production source change:

```text
MODIFY prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

No other production source file is expected.

A tiny local expression/helper inside `PhysicalFistCollision.cpp` is permitted only if it makes the exact `{1,2}` rule clearer without adding state, policy, abstraction or future-generalization machinery. Prefer the smallest readable direct change.

If faithful implementation requires another production module, another hook/interface, new persistent state, or broader source scope, **STOP and report the contradiction**.

## Protected behavior — MUST remain unchanged

Do not change:

```text
PhysicalFistExecution identity/state layout
actor identity
exact RIGHT source identity
C1 generation identity
animation identity
FIST authored/accepted budgets
origin-family ownership
IsAllowedOriginContinuation semantics
premature native raw55 5 -> 7 suppression
native callback/state progression
first-FIST physical 5 -> 7 operation
second-FIST clear-only rearm semantics
Normal family behavior
Quick family behavior
Sprint-origin first-FIST rule
Normal exact native-clear suppression
native final 7 -> 5 cleanup
CollisionLifecycleGuard behavior
raw8 behavior or timing/opportunity logic
generic equipped marker behavior
EquippedSprintCollision behavior
EngineBridge hook/callback ownership
AttackMotionRouting
unmarked raw55 native fallback
diagnostic/release parity model
```

Do not add:

```text
new hook
new module
New Balance / DLL-name or version detection
AttackCollision detection
species/name gate
animation-filename family inference
polling or timer
custom damage/contact logic
new cleanup path
new fallback taxonomy
generic SP2 policy
refactor/cleanup unrelated to the exact predicate correction
```

## Design principle

Modularity here means **the existing permanent owner owns its own tiny compatibility rule**. It does not mean creating another module or abstraction.

The animator-authored marker system remains authoritative for precise authored collision timing while Gothic remains authoritative for native target/contact/damage and ordinary state progression. This correction must not move responsibility back toward one global attack-family timer.

## Static implementation audit

Before publishing, verify all of the following:

1. production source scope is only `PhysicalFistCollision.cpp`;
2. true-Power first FIST accepts explicit SP1 or SP2 and still requires `earlyOpeningSuppressed`;
3. true-Power second FIST accepts explicit SP1 or SP2;
4. Sprint-origin first FIST remains exact Sprint/SP1 + `earlyOpeningSuppressed`;
5. Sprint-origin later current-Power FIST accepts explicit SP1 or SP2;
6. Normal and Quick predicate text/semantics are unchanged;
7. no execution state/helper policy beyond the exact local condition was added;
8. no hook/interface/module/CMake change occurred;
9. no diagnostic-only dependency was introduced;
10. `git diff --check` passes.

If the resulting diff cannot be explained as the direct local expression of the frozen `{SP1, SP2}` Power compatibility rule, STOP instead of broadening.

## Build / runtime

Work build execution is PROHIBITED.

Work must not invoke, configure, probe or troubleshoot any build tool or dependency.

After independent Normal Chat diff review, the User will build/deploy locally and perform focused runtime acceptance.

Focused runtime acceptance is owned by `COLLISION_TEST_PLAN.md` §4.4:

```text
1. single-FIST true Power raw55 late/SP2 marker
2. double-FIST true Power: marker1 activation + marker2 SP2 rearm
3. Sprint-origin: marker1 Action9/SP1 + same-C1 marker2 current Power/SP2
4. Normal/Quick raw55 controls
5. representative equipped/raw8 controls
6. only then resume broader New Balance full-stack coverage
```

## Publication

This task authorizes publication only to:

```text
repository: tcholti/Gothic3_Animation_Behaviors
branch: docs/collision-source-evidence
```

The launcher message will provide the exact required remote HEAD. Work must verify that base before editing.

After implementation and static audit:

- commit and push/publish the bounded result;
- update `docs/BETWEEN_CHATS.md` with the implementation result and final remote SHA if required by the current protocol;
- do **not** archive this task document;
- stop for independent Normal Chat review.

## Required Work report

Report:

- final remote commit SHA and parent SHA;
- exact changed files;
- exact predicate changes made;
- confirmation that all protected neighboring mechanisms remained untouched;
- static checks performed;
- any source contradiction;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`

Then STOP.
