# Gothic 3 — New Balance raw55 Sprint-First SP2 Compatibility Correction

**Status:** ACTIVE — FROZEN FOR BOUNDED IMPLEMENTATION  
**Opened:** 2026-09-25  
**Task type:** BOUNDED PRODUCTION IMPLEMENTATION  
**Work build execution:** PROHIBITED  
**Owner:** `PhysicalFistCollision`

## Purpose

Implement only the smallest follow-up compatibility correction established by EV-378.

The previous bounded raw55 SP2 correction is closed and archived. Runtime confirmed every predicate changed by that task. EV-378 then exposed one additional factual New Balance state that was outside the previous task's frozen evidence basis: a valid already-owned Sprint-origin **first/only** FIST can remain factual `Action9 / SPRINT` while arriving at `StatePosition=2`.

This task must express only that new fact. It is not a redesign and does not reopen the previous Power/SP2 correction.

## Required read order

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this task
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/FEATURE_DEVELOPMENT_METHOD.md`
6. `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
7. `docs/COLLISION_TEST_PLAN.md` §4.4
8. only the exact source required by this task

Use EV-378 only when exact runtime proof is needed. Do not reinterpret older evidence into broader scope.

## Frozen factual basis

EV-378 runtime confirms the previous correction is working:

```text
true Power single-FIST first/only marker at SP2
  -> ACCEPTED
  -> exact RIGHT raw55 5 -> 7
  -> native cleanup

true Power double-FIST
  marker1 SP1 -> ACCEPTED/open
  marker2 SP2 -> ACCEPTED/clear-only rearm

Sprint-origin double-FIST
  marker1 factual Action9 / SPRINT / SP1 -> ACCEPTED/open
  same C1 continues to Action2 / POWER
  marker2 SP2 -> ACCEPTED/clear-only rearm

Normal / Quick raw55 controls
  -> healthy
```

EV-378 additionally establishes the new reduced contradiction:

```text
Sprint-origin single-FIST raw55
  exact owned execution remains valid
  current factual family = SPRINT
  factual Action = 9
  premature native opening was suppressed
  earlyOpeningSuppressed = true
  first/only authored FIST can arrive at StatePosition=2
  exact RIGHT raw55 source is still group5
  current Sprint-first SP1-only gate rejects the marker
```

The reviewed single-marker anomalies are the same exact Sprint-first/SP2 class. The double-marker log contains no CORE marker anomaly.

## Current source fact

At the task-freeze baseline, `PhysicalFistCollision.cpp` contains:

```cpp
case AttackFamily_Sprint:
    return currentFamily == AttackFamily_Sprint
        && statePosition == 1
        && execution.earlyOpeningSuppressed;
```

inside `IsFirstFistAllowed(...)`.

The previously corrected predicates already remain:

```text
true-Power first FIST       -> explicit SP1 or SP2 + earlyOpeningSuppressed
true-Power second FIST      -> explicit SP1 or SP2
Sprint-origin later FIST    -> current POWER + explicit SP1 or SP2
```

Those predicates are runtime-confirmed and are protected unchanged by this task.

## Responsibility

Modify only the existing `AttackFamily_Sprint` branch of `IsFirstFistAllowed(...)` so an already-matched exact raw55 Sprint-origin first FIST accepts the explicit proven state set `{1,2}` while retaining every existing ownership/safety requirement.

Required semantic result:

```text
SPRINT origin — first FIST
current family must still be SPRINT
StatePosition 1 remains accepted
StatePosition 2 additionally accepted
earlyOpeningSuppressed remains mandatory
```

Expected direct expression:

```cpp
case AttackFamily_Sprint:
    return currentFamily == AttackFamily_Sprint
        && (statePosition == 1 || statePosition == 2)
        && execution.earlyOpeningSuppressed;
```

Equivalent formatting is acceptable. Do **not** generalize to `StatePosition >= 1` or another open-ended range.

## Expected source scope

Expected production source change:

```text
MODIFY prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

Expected semantic production diff:

```text
one predicate substitution only
Sprint-origin first-FIST state acceptance:
  SP1 -> explicit {SP1, SP2}
```

No helper, abstraction, new state or second production file is expected or authorized.

If faithful implementation appears to require another production module, another hook/interface, persistent state, authored-marker-count branching, or broader source scope, **STOP and report the contradiction instead of expanding the task**.

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
true-Power first-FIST predicate
true-Power second-FIST predicate
Sprint-origin later/current-Power predicate
Normal family behavior
Quick family behavior
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
StatePosition >= 1
marker-count-dependent Sprint policy
new hook
new module
new persistent state
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

## Why authored-count branching is prohibited

EV-378 discovered the SP2 first-marker state with the single-FIST fixture, but the evidence does not establish that authored FIST count is the causal rule. Marker location/timing determines which native StatePosition is factual when the marker fires.

Therefore do not encode:

```text
if authoredFistCount == 1 -> allow SP2
if authoredFistCount == 2 -> SP1 only
```

The compatibility fact belongs to the exact Sprint-origin first-FIST state predicate, not to an animation-authoring-count special case.

## Static implementation audit

Before publishing, verify all of the following:

1. production source scope is only `PhysicalFistCollision.cpp`;
2. only the Sprint-origin branch of `IsFirstFistAllowed(...)` changes semantically;
3. `currentFamily == AttackFamily_Sprint` remains mandatory;
4. accepted StatePosition set is exactly `{1,2}`;
5. `execution.earlyOpeningSuppressed` remains mandatory;
6. true-Power first/second predicates are unchanged;
7. Sprint-origin second/later current-Power predicate is unchanged;
8. Normal and Quick predicates are unchanged;
9. no helper/state/module/hook/interface/CMake/diagnostic dependency is added;
10. `git diff --check` passes.

The resulting production diff should be explainable as exactly one evidence-backed predicate widening. If it is not, STOP.

## Build / runtime

Work build execution is PROHIBITED.

Work must not invoke, configure, probe or troubleshoot any build tool, Gothic 3 runtime, SDK dependency or local deployment.

After independent Normal Chat diff review, the User will build/deploy locally.

Focused runtime acceptance is owned by `docs/COLLISION_TEST_PLAN.md` §4.4:

```text
1. single-FIST Sprint-origin Action9/SP2 first/only marker
   -> must be accepted
   -> exact RIGHT raw55 5 -> 7
   -> cleanup returns to 5 / zero outstanding

2. double-FIST Sprint-origin
   -> marker1 Action9/SP1 remains accepted/open
   -> same-C1 marker2 current Power/SP2 remains accepted/clear-only rearm

3. representative true-Power single/double control
   -> remains accepted

4. Normal/Quick raw55 controls

5. representative equipped/raw8 controls

6. only then resume broader New Balance full-stack coverage
```

Do not require physical damage from every accepted marker; marker acceptance/rearm/cleanup correctness is primary and Gothic remains authoritative for target/contact/damage.

## Publication

This task authorizes publication only to:

```text
repository: tcholti/Gothic3_Animation_Behaviors
branch: docs/collision-source-evidence
```

The launcher message will provide the exact required remote HEAD. Work must verify that exact base before editing.

After implementation and static audit:

- commit and push/publish the bounded result;
- update `docs/BETWEEN_CHATS.md` with implementation result and final remote SHA as required by the current protocol;
- do **not** archive this task document;
- stop for independent Normal Chat review;
- do not build or run.

## Required Work report

Report:

- final remote commit SHA and parent SHA;
- exact changed files;
- exact predicate change made;
- confirmation that all protected neighboring mechanisms remained untouched;
- static checks performed;
- any source contradiction;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`

Then STOP.
