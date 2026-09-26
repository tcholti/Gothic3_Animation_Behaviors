# Gothic 3 — raw55 Normal Second-FIST SP0 Compatibility Correction

**Status:** ACTIVE — IMPLEMENTED + INDEPENDENT REVIEW PASS / RUNTIME ACCEPTANCE PENDING  
**Opened:** 2026-09-26  
**Updated:** 2026-09-26  
**Task type:** BOUNDED PRODUCTION-BEHAVIOR IMPLEMENTATION + RUNTIME ACCEPTANCE  
**Owner:** `PhysicalFistCollision`

## Purpose

Remove the remaining evidence-unnecessary StatePosition restriction on a legitimate second authored Normal raw55 FIST while preserving every established Normal contact-rearm and native-cleanup invariant.

This task is deliberately narrow. It does **not** redesign Normal raw55 behavior.

## Frozen implementation basis

Branch:

`docs/collision-source-evidence`

Frozen implementation parent:

`396c7b8b0886174860cc452176a2ed57bf530784`

Frozen production source blob before implementation:

`de175bb504c3abe13ad1c0bb9cda54997c9e3a26`

Published implementation:

`a31c66b97e45c27d0739b7df51252d33f490e7e1`

Work handoff HEAD:

`8353c997332cc2bd88d1d1c546e287cf0e99001d`

Independent Normal Chat static review: **PASS**.

The production diff changes only the Normal branch of `IsSecondFistAllowed(...)`:

```cpp
// before
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && statePosition == 1;

// candidate
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

Quick, Power, Sprint, all first-FIST predicates, the existing second-FIST clear-only operation, Normal native-clear suppression, lifecycle, hooks and diagnostics are unchanged.

## Evidence basis

The older Normal causal chain established:

```text
EV-286
  first Normal FIST may legitimately arrive at SP0 and own exact RIGHT raw55 5 -> 7 opening

EV-287
  marker-owned ClearTriggeredList() at that SP0 first FIST is sufficient to create hit1 before Gothic's SP0 -> SP1 transition

EV-290 / EV-291
  Gothic's exact native between-contact ClearTriggeredList() from Script_Game.dll+0x386C6 creates the implicit second-contact opportunity
  permanent marked-Normal behavior suppresses that native clear so it cannot silently substitute for authored marker2 ownership

EV-292
  later authored Normal marker2 can replace the suppressed native clear with one exact current-RIGHT ClearTriggeredList()
  no second physical collision-group opening is needed
```

Those experiments used marker2 at SP1. They prove SP1 is sufficient, not necessary.

The later archived `1+8` New Balance fixture supplies the missing authoring-boundary evidence. Factual Normal executions repeatedly show:

```text
marker1 NORMAL/SP0
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=1
-> ACCEPTED

native hit1
-> ONDAMAGE Target=PC_Hero

marker2 still NORMAL/SP0
-> RIGHT already group7
-> AuthoredFistCount=2
-> AcceptedFistCount=1
-> old source rejects through the SP1-only IsSecondFistAllowed gate
```

Representative C1=1:

```text
marker1 StateTime=0.025186 SP0 -> accepted/open+clear
hit1 -> ONDAMAGE
marker2 StateTime=0.241280 SP0 -> REJECTED_UNSUPPORTED_HIT
```

Representative C1=3 repeats the same class at marker2 StateTime `0.246752`.

Therefore a legitimate authored second-contact marker can occur at SP0 after a prior native contact has already happened.

## Behavioral meaning

No rearm mechanism was added.

The existing second-FIST path still requires:

```text
exact same owned execution
AuthoredFistCount == 2
AcceptedFistCount == 1
exact current RIGHT source still group7
IsSecondFistAllowed(...) == true
```

and then performs:

```text
ClearTriggeredList()
no second physical group request
AcceptedFistCount -> 2
```

Only the Normal StatePosition acceptance changed from explicit SP1 to explicit `{SP0, SP1}`.

An early marker2 may occur before hit1. In the `1+3` fixture this is common. Accepting that marker is still correct marker-authoring semantics: clearing an already-empty visited set is harmless and does not create an artificial damage guarantee.

## Runtime acceptance — current responsibility

Build/deploy the current reviewed diagnostic candidate and reuse the established mixed double-FIST fixtures.

### 1+3 — very early control

Require:

```text
marker1 NORMAL/SP0 -> accepted/open+initial clear
marker2 NORMAL/SP0 -> ACCEPTED
marker2 -> ClearTriggeredList=1
marker2 -> GroupRequested=0
RIGHT remains group7
native cleanup -> group5 / outstanding0
```

Two damage events are **not required** because marker2 may occur before hit1.

### 1+8 — decisive SP0-after-hit1 route

Find representative factual Normal executions where hit1 precedes marker2 while marker2 is still SP0.

Require:

```text
marker1 NORMAL/SP0 -> accepted/open+initial clear
hit1 occurs before marker2
marker2 NORMAL/SP0 -> ACCEPTED
marker2 ClearTriggeredList=1
marker2 GroupRequested=0
RIGHT remains group7
later native contact/damage may occur when geometry/target state permits
native cleanup -> 7 -> 5
final outstanding = 0
```

Collision correctness is marker2 acceptance + clear-only rearm + healthy cleanup. Native damage remains Gothic-owned.

### 1+15 — established SP1 positive control

Require unchanged behavior:

```text
marker2 NORMAL/SP1 -> accepted/clear-only rearm
no second physical opening
healthy cleanup
```

Also retain representative Quick / Power / Sprint controls from the same mixed-attack logs.

## Protected behavior

Do not change:

```text
IsFirstFistAllowed(...)
Quick second-FIST predicate
Power second-FIST predicate
Sprint-origin second-FIST predicate
Normal first-FIST behavior
Normal exact native-clear suppression caller/gate
first-FIST 5 -> 7 activation
second-FIST clear-only implementation
execution identity / C1 ownership
native cleanup
CollisionLifecycleGuard
raw8 behavior
equipped behavior
EquippedSprintCollision
AttackMotionRouting
hook set
diagnostic format
```

Do not add generic StatePosition ranges, visited-target requirements, hit1 flags, delays/queues/timers, new hooks/state, second physical openings, custom damage/contact, species/name/filename rules, or New Balance/DLL detection.

## Closure rule

Do not archive this task until runtime acceptance closes.

If the 1+3, decisive 1+8 and 1+15 routes satisfy the contract and Quick/Power/Sprint controls remain healthy:

```text
-> record new EV evidence
-> promote accepted Normal {SP0,SP1} second-FIST semantics to current raw55 reference/architecture
-> archive this task
-> treat focused raw55 behavior as closed before broader New Balance full-stack regression
```
