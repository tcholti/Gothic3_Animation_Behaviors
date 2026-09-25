# Gothic 3 — New Balance raw55 Sprint-First SP2 Compatibility Correction

**Status:** CLOSED — IMPLEMENTED / STATIC REVIEW PASS / EXACT RUNTIME PREDICATE PASS / FOLLOW-UP SPLIT TO SEPARATE INVESTIGATION  
**Opened:** 2026-09-25  
**Closed:** 2026-09-25  
**Task type:** BOUNDED PRODUCTION IMPLEMENTATION  
**Work build execution:** PROHIBITED  
**Owner:** `PhysicalFistCollision`

## Purpose

Implement only the smallest follow-up compatibility correction established by EV-378.

The previous bounded raw55 SP2 correction was already closed and archived. Runtime confirmed every predicate changed by that task. EV-378 then exposed one additional factual New Balance state outside the previous task's frozen basis: a valid already-owned Sprint-origin **first/only** FIST can remain factual `Action9 / SPRINT` while arriving at `StatePosition=2`.

This task expressed only that fact. It was not a redesign and did not reopen the previous Power/SP2 correction.

## Frozen responsibility

Modify only the existing `AttackFamily_Sprint` branch of `IsFirstFistAllowed(...)` so an already-matched exact raw55 Sprint-origin first FIST accepts the explicit proven state set `{1,2}` while retaining every existing ownership/safety requirement.

Required expression:

```cpp
case AttackFamily_Sprint:
    return currentFamily == AttackFamily_Sprint
        && (statePosition == 1 || statePosition == 2)
        && execution.earlyOpeningSuppressed;
```

Do not generalize to `StatePosition >= 1`.

## Authorized source scope

```text
MODIFY prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

Expected semantic production diff:

```text
one predicate substitution only
Sprint-origin first-FIST state acceptance:
  SP1 -> explicit {SP1, SP2}
```

No helper, abstraction, new state or second production file was authorized.

## Protected behavior

Unchanged:

```text
PhysicalFistExecution identity/state layout
actor / exact RIGHT source / C1 / animation identity
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
Normal / Quick
Normal exact native-clear suppression
native final 7 -> 5 cleanup
CollisionLifecycleGuard
raw8 timing/opportunity behavior
generic equipped markers
EquippedSprintCollision
EngineBridge hook/callback ownership
AttackMotionRouting
unmarked raw55 native fallback
diagnostic/release parity
```

Prohibited:

```text
StatePosition >= 1
marker-count-dependent Sprint policy
new hook/module/state/helper
New Balance / DLL/version detection
AttackCollision detection
species/name gate
animation-filename family inference
polling/timer
custom damage/contact
new cleanup path/fallback taxonomy
generic SP2 policy
unrelated refactor
```

## Implementation checkpoint

Implementation commit:

`ce59e5a2bad564652eaba970e959bdef0b479d82`

Implementation parent:

`932f38d744853f4cd9f6f1ee78c929bb2916d57f`

Independent Normal Chat diff review: **PASS**.

Verified production diff:

```text
PhysicalFistCollision.cpp only
IsFirstFistAllowed(...) / AttackFamily_Sprint only

- && statePosition == 1
+ && (statePosition == 1 || statePosition == 2)
```

`currentFamily == AttackFamily_Sprint` remained mandatory. `execution.earlyOpeningSuppressed` remained mandatory. No other production predicate or neighboring mechanism changed.

## Runtime disposition — EV-379

Local build/deployment:

```text
Built SHA256: 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
Live  SHA256: 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
DIAGNOSTIC DEPLOYMENT PASS
```

The exact changed predicate is **RUNTIME PASS**.

Repeated single-FIST Sprint-origin executions show:

```text
current SPRINT / Action9 / SP2
EarlyOpeningSuppressed=1
RIGHT raw55 5 -> 7
FIST ACCEPTED
native damage when contact connects
native cleanup 7 -> 5
```

The reviewed single-marker log contains no marker anomaly.

The broader focused run found one separate second-FIST continuation case:

```text
origin Sprint
marker1 current SPRINT/SP1 -> ACCEPTED/open
marker2 current SPRINT/SP2 -> REJECTED_UNSUPPORTED_HIT
```

Other executions retain the previously established route:

```text
origin Sprint
marker1 current SPRINT/SP1 -> ACCEPTED/open
marker2 current POWER/SP2  -> ACCEPTED/clear-only rearm
```

This is a new second-FIST timing question, not a failure of the Sprint-first predicate changed by this task.

## Closure

The exact bounded correction owned by this task is validated and closed. It must not be silently expanded to fix the newly observed second-FIST case.

The follow-up responsibility is now separated into:

`docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_STATE_INVESTIGATION.md`

That investigation must map the legitimate second-FIST state envelope—especially whether a deliberately earlier marker2 can arrive at `current SPRINT / SP1`—before any further production implementation is frozen.

After the full New Balance compatibility issue is eventually resolved, `docs/COLLISION_TEST_PLAN.md` §4.5 still requires the bounded standalone/no-New-Balance raw55 sentinel before final source certification.
