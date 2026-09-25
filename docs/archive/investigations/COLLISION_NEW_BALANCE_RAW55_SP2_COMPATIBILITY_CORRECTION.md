# Gothic 3 — New Balance raw55 SP2 Compatibility Correction

**Status:** CLOSED — IMPLEMENTED / STATIC REVIEW PASS / RUNTIME PARTIAL PASS; NEW SPRINT-FIRST SP2 FACT DEFERRED TO FOLLOW-UP  
**Opened:** 2026-09-25  
**Closed:** 2026-09-25  
**Task type:** BOUNDED PRODUCTION IMPLEMENTATION  
**Work build execution:** PROHIBITED  
**Owner:** `PhysicalFistCollision`

## Purpose

Implement only the smallest evidence-backed compatibility correction required by EV-376, with EV-377 as the cross-mechanism Sprint control.

This is **not a redesign** and **not a new feature mechanism**. Research established that the existing permanent raw55 owner, execution identity, native-opening suppression and Sprint-origin continuity are correct. New Balance / AttackCollision changes factual Power callback progression so a valid already-owned raw55 FIST may arrive at `StatePosition=2`.

## Frozen factual basis at task opening

EV-376 established:

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

EV-377 established healthy neighboring controls:

```text
equipped Sprint = healthy
raw8 Sprint = healthy
raw8 persistent opportunity = healthy
same-C1 Action9 -> Action2 transition = legitimate native behavior
```

## Frozen responsibility

Modify only the existing raw55 first/second FIST state acceptance necessary to recognize explicit Power `StatePosition` values `{1,2}` inside an already-matched exact `PhysicalFistCollision` execution.

Required semantic result:

```text
TRUE POWER origin — first FIST
current family must still be POWER
StatePosition 1 remains accepted
StatePosition 2 additionally accepted
earlyOpeningSuppressed remains mandatory

TRUE POWER origin — second FIST
current family must still be POWER
StatePosition 1 remains accepted
StatePosition 2 additionally accepted

SPRINT origin — first FIST
UNCHANGED by this task:
current family must be SPRINT
StatePosition must be 1
earlyOpeningSuppressed remains mandatory

SPRINT origin — later/second FIST after same-C1 continuation
current family must still be POWER
StatePosition 1 remains accepted
StatePosition 2 additionally accepted
```

Use explicit equality for `{1,2}`. Do not generalize to `StatePosition >= 1`.

## Expected source scope

```text
MODIFY prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

No other production source file was authorized. No new module, hook/interface, persistent state or broader mechanism was authorized.

## Protected behavior

The task protected unchanged:

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

Explicitly prohibited:

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
unrelated refactor/cleanup
```

## Design principle

Modularity here means **the existing permanent owner owns its own tiny compatibility rule**. It does not mean creating another module or abstraction.

The animator-authored marker system remains authoritative for precise authored collision timing while Gothic remains authoritative for native target/contact/damage and ordinary state progression.

## Implementation checkpoint — 2026-09-25

Implemented in:

`6eb3e3ca96da55e89127c24d5f656e05610d315f`

Parent:

`8f1e3e3d3b74f7d780cfacd5a96d2b3d6346290a`

Exact production diff:

```text
PhysicalFistCollision.cpp only
3 predicate substitutions
+3 / -3 lines
```

Independent Normal Chat diff-against-contract review: **PASS**.

Verified published result:

```text
true-Power first FIST:
  POWER && (SP1 || SP2) && earlyOpeningSuppressed

true-Power second FIST:
  POWER && (SP1 || SP2)

Sprint-origin later FIST:
  current POWER && (SP1 || SP2)

Sprint-origin first FIST:
  unchanged exact SPRINT / SP1 / earlyOpeningSuppressed

Normal / Quick:
  unchanged
```

No new helper, state, module, hook, interface, lifecycle behavior, diagnostic dependency, CMake change or neighboring feature change was present in the commit diff.

## Runtime disposition — EV-378

The User built and deployed the diagnostic twin from the reviewed candidate lineage. Built and live hashes matched:

`E11D680590D2F9D87A50EAF64B642F70C8CECA019ABB651DC48B00AF01F37C74`

Focused runtime evidence produced a **partial PASS for this task's exact responsibility**:

```text
single-FIST true Power:
  late SP2 first/only FIST ACCEPTED
  exact RIGHT raw55 5 -> 7
  native damage observed when contact connected
  native cleanup 7 -> 5 / outstanding zero

double-FIST true Power:
  marker1 SP1 ACCEPTED / physical opening
  marker2 SP2 ACCEPTED / clear-only rearm
  no second physical opening
  two native contacts/damage observed in representative executions
  clean native cleanup

Sprint-origin double-FIST:
  marker1 Action9 / SPRINT / SP1 ACCEPTED / physical opening
  same C1 continues to Action2 / POWER
  marker2 SP2 ACCEPTED / clear-only rearm
  clean native cleanup

Normal / Quick controls:
  healthy
```

The same batch exposed one **new factual case outside this task's frozen evidence basis**:

```text
Sprint-origin single-FIST:
  exact owned execution
  factual Action9 / SPRINT
  earlyOpeningSuppressed = true
  first/only FIST may arrive at SP2 around StateTime ~= 1.58
  group remains 5 because the intentionally unchanged Sprint-first SP1-only predicate rejects it
```

The single-marker log repeatedly reproduces only this new anomaly class. The double-marker log contains no CORE marker anomaly and demonstrates the task's three changed predicates behaving as intended.

This new finding does not invalidate the implementation. It supersedes the EV-376/EV-377 assumption that all observed Sprint-origin first FIST markers arrive at SP1 and therefore requires a separate follow-up disposition rather than silent scope expansion.

## Closure

This bounded implementation responsibility is **COMPLETE and CLOSED**:

- source implementation matched the frozen contract exactly;
- independent static review PASS;
- runtime confirms every changed predicate works as intended;
- runtime discovered one additional Sprint-first/SP2 compatibility fact that was explicitly outside this task's frozen scope;
- no neighboring redesign is justified.

The follow-up question is narrow: whether exact already-owned Sprint-origin **first** FIST acceptance should preserve SP1 and additionally accept explicit SP2 while retaining current Sprint identity and mandatory `earlyOpeningSuppressed`.

Build by Work: NOT ATTEMPTED — Work build execution was not authorized for this task.
