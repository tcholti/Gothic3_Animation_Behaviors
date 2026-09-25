# Gothic 3 — New Balance raw55 Sprint-First SP2 Compatibility Correction

**Status:** ACTIVE — IMPLEMENTED / STATIC REVIEW PASS / EXACT RUNTIME PREDICATE PASS / FOCUSED ACCEPTANCE PARTIAL  
**Opened:** 2026-09-25  
**Task type:** BOUNDED PRODUCTION IMPLEMENTATION  
**Work build execution:** PROHIBITED  
**Owner:** `PhysicalFistCollision`

## Purpose

Implement only the smallest follow-up compatibility correction established by EV-378.

The previous bounded raw55 SP2 correction is closed and archived. Runtime confirmed every predicate changed by that task. EV-378 then exposed one additional factual New Balance state outside the previous task's frozen basis: a valid already-owned Sprint-origin **first/only** FIST can remain factual `Action9 / SPRINT` while arriving at `StatePosition=2`.

This task expresses only that fact. It is not a redesign and does not reopen the previous Power/SP2 correction.

## Frozen factual basis

EV-378 confirms:

```text
true Power single-FIST SP2                -> ACCEPTED/open/cleanup
true Power double-FIST marker2 SP2        -> ACCEPTED/clear-only rearm
Sprint-origin double marker1 Sprint/SP1   -> ACCEPTED/open
same-C1 marker2 current Power/SP2         -> ACCEPTED/clear-only rearm
Normal / Quick raw55                      -> healthy
```

EV-378 additionally establishes:

```text
Sprint-origin single-FIST raw55
  exact owned execution remains valid
  current factual family = SPRINT
  factual Action = 9
  premature native opening suppressed
  earlyOpeningSuppressed = true
  first/only FIST can arrive at StatePosition=2
  exact RIGHT raw55 remains group5
  previous Sprint-first SP1-only gate rejects it
```

The reviewed single-marker anomalies are this same Sprint-first/SP2 class. The double-marker log contains no CORE marker anomaly.

## Frozen responsibility

Modify only the existing `AttackFamily_Sprint` branch of `IsFirstFistAllowed(...)` so an already-matched exact raw55 Sprint-origin first FIST accepts the explicit proven state set `{1,2}` while retaining every existing ownership/safety requirement.

Required semantics:

```text
current family must remain SPRINT
SP1 remains accepted
SP2 additionally accepted
earlyOpeningSuppressed remains mandatory
```

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

No helper, abstraction, new state or second production file is authorized.

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

## Why authored-count branching is prohibited

EV-378 exposed SP2 with the single-FIST fixture, but authored FIST count is not established as the causal rule. Marker timing determines the factual native StatePosition when the marker fires. The compatibility fact belongs to Sprint-origin first-FIST state acceptance, not to an animation-count special case.

## Implementation checkpoint — 2026-09-25

Implementation commit:

`ce59e5a2bad564652eaba970e959bdef0b479d82`

Implementation parent:

`932f38d744853f4cd9f6f1ee78c929bb2916d57f`

Post-publication handoff HEAD:

`858d5ca173c03c7149594b3da946594c97a13be5`

Independent Normal Chat diff review: **PASS**.

Verified production diff:

```text
PhysicalFistCollision.cpp only
IsFirstFistAllowed(...) / AttackFamily_Sprint only

- && statePosition == 1
+ && (statePosition == 1 || statePosition == 2)
```

`currentFamily == AttackFamily_Sprint` remains mandatory. `execution.earlyOpeningSuppressed` remains mandatory. No other production predicate or neighboring mechanism changed.

## Runtime checkpoint — EV-379

Local build/deployment:

```text
Built SHA256: 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
Live  SHA256: 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
DIAGNOSTIC DEPLOYMENT PASS
```

Exact changed predicate: **RUNTIME PASS**.

Repeated single-FIST Sprint-origin executions now show:

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

Other executions still show the previously established route:

```text
origin Sprint
marker1 current SPRINT/SP1 -> ACCEPTED/open
marker2 current POWER/SP2  -> ACCEPTED/clear-only rearm
```

This is a new second-FIST timing question, not a failure of the Sprint-first predicate changed by this task.

## Boundary after EV-379

**Do not expand this implementation task to patch the new second-FIST case.**

Before any follow-up source change, map the legitimate second-FIST state envelope. The immediate diagnostic probe is to move marker2 earlier and determine whether a valid second FIST can also arrive at `current SPRINT / SP1`.

Known legitimate/observed states so far:

```text
second FIST, origin Sprint:
  current POWER / SP2  -> proven legitimate, accepted
  current SPRINT / SP2 -> proven legitimate arrival, currently rejected
  current SPRINT / SP1 -> not yet deliberately tested
```

Do not infer `>=1`, do not add authored-count policy, and do not alter neighboring systems.

## Build / runtime acceptance disposition

The exact correction owned by this task is validated. The full New Balance compatibility gate remains open because focused regression exposed the separate second-FIST timing state documented by EV-379.

After that next issue is resolved, `docs/COLLISION_TEST_PLAN.md` §4.5 still requires a small standalone/no-New-Balance raw55 sentinel before final source certification. This proves New Balance support is additive rather than required. Do not reopen the broad standalone campaign unless that sentinel contradicts established behavior.

Do not require physical damage from every accepted marker; marker acceptance/rearm/cleanup is primary and Gothic remains authoritative for contact/damage.

## Closure rule

This task must not receive further production scope. It may be archived once the EV-379 conclusions and the next bounded investigation responsibility are durably represented in the current-state handoff. The follow-up second-FIST issue requires its own frozen responsibility before any implementation.
