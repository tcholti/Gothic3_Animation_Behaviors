# Gothic 3 — raw55 Normal Second-FIST SP0 Compatibility Correction

**Status:** ACTIVE — FROZEN IMPLEMENTATION TASK  
**Opened:** 2026-09-26  
**Task type:** BOUNDED PRODUCTION-BEHAVIOR IMPLEMENTATION  
**Work build execution:** PROHIBITED  
**Owner:** `PhysicalFistCollision`

## Purpose

Remove the remaining evidence-unnecessary StatePosition restriction on a legitimate second authored Normal raw55 FIST while preserving every established Normal contact-rearm and native-cleanup invariant.

This task is deliberately narrow. It does **not** redesign Normal raw55 behavior.

## Required base

Branch:

`docs/collision-source-evidence`

Frozen task base HEAD:

`5f50cbef0ebd37f1fbee0ef74c293fd15950325b`

Frozen production source blob:

`prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`

Git blob:

`de175bb504c3abe13ad1c0bb9cda54997c9e3a26`

If the source no longer matches this responsibility, STOP and report the contradiction rather than adapting the task.

## Evidence basis

The older Normal causal chain already established:

```text
EV-286
  first Normal FIST may legitimately arrive at SP0 and own exact RIGHT raw55 5 -> 7 opening

EV-287
  marker-owned ClearTriggeredList() at that SP0 first FIST is sufficient to create hit1 before Gothic's SP0 -> SP1 transition

EV-290 / EV-291
  Gothic's exact native between-contact ClearTriggeredList() from Script_Game.dll+0x386C6 creates the implicit second-contact opportunity
  permanent marked-Normal behavior suppresses that native clear so it does not silently substitute for authored marker2 ownership

EV-292
  later authored Normal marker2 can replace the suppressed native clear with one exact current-RIGHT ClearTriggeredList()
  no second physical collision-group opening is needed
```

Those experiments used a later marker2 at SP1. They prove SP1 is sufficient, not that SP1 is necessary.

The later New Balance timing sweep supplies the missing authoring-boundary evidence.

In `research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_8.log`, factual Normal executions repeatedly show:

```text
marker1:
  NORMAL / Action1 / SP0
  exact RIGHT raw55 5 -> 7
  ClearTriggeredList=1
  ACCEPTED

native hit1:
  ONDAMAGE Target=PC_Hero

marker2:
  still NORMAL / Action1 / SP0
  RIGHT already group7
  AuthoredFistCount=2
  AcceptedFistCount still 1
  current code rejects solely through IsSecondFistAllowed Normal state gate
```

Representative C1=1:

```text
marker1 StateTime=0.025186 SP0 -> accepted/open+clear
hit1 -> ONDAMAGE
marker2 StateTime=0.241280 SP0 -> REJECTED_UNSUPPORTED_HIT
RIGHT remains group7
```

Representative C1=3 repeats the same class:

```text
marker1 StateTime=0.033333 SP0 -> accepted/open+clear
hit1 -> ONDAMAGE
marker2 StateTime=0.246752 SP0 -> REJECTED_UNSUPPORTED_HIT
```

Therefore a legitimate authored second-contact marker can occur at SP0 **after a prior native contact has already happened**.

The current SP1-only second-FIST Normal predicate is an evidence guard, not a proven native prerequisite.

## Current source

Inside `IsSecondFistAllowed(...)`:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && statePosition == 1;
```

## Frozen responsibility

Change **only** the Normal second-FIST state-position acceptance so explicit SP0 and SP1 are accepted:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

Equivalent locally clear syntax is acceptable only if semantics are exactly identical.

## Behavioral meaning

This change does **not** introduce a new rearm mechanism.

The existing second-FIST path already requires:

```text
exact same owned execution
AuthoredFistCount == 2
AcceptedFistCount == 1
current exact RIGHT source still group7
IsSecondFistAllowed(...) == true
```

and then performs the established marker2 operation:

```text
ClearTriggeredList()
no second physical group request
AcceptedFistCount -> 2
```

The only change is that a factual Normal second FIST is no longer required to wait for Gothic to reach SP1.

## Important timing semantics

An early marker2 may occur before hit1.

Example: the `1+3` fixture commonly places marker2 at SP0 before first native contact.

Accepting such a marker is still the intended marker-authoring semantic:

```text
second FIST before any prior contact
-> ClearTriggeredList() may clear an already-empty visited set
-> no artificial damage guarantee
-> later native contact may still occur once
```

Therefore runtime acceptance must **not** require two damage events from the `1+3` fixture.

The decisive functional control is `1+8`, where the existing evidence demonstrates hit1 before marker2 while marker2 is still SP0.

## Runtime acceptance after implementation

Use the same three already-established double-FIST fixtures:

### 1+3 — very early control

Expected:

```text
marker1 NORMAL/SP0 -> accepted/open+initial clear
marker2 NORMAL/SP0 -> accepted/clear-only rearm
no second 5 -> 7 request
native cleanup -> group5
```

Two damage events are **not required** because marker2 may occur before hit1.

### 1+8 — decisive SP0-after-hit1 route

Require at least representative factual executions showing:

```text
marker1 NORMAL/SP0 -> accepted/open+initial clear
hit1 occurs before marker2
marker2 NORMAL/SP0 -> ACCEPTED
marker2 ClearTriggeredList=1
marker2 GroupRequested=0
RIGHT remains group7
later second native contact/damage is possible when geometry/target state permits
native cleanup -> 7 -> 5
final outstanding = 0
```

The collision correctness requirement is marker2 acceptance + clear-only rearm + healthy cleanup. Native damage remains Gothic-owned and is supporting evidence rather than a guaranteed result on every attack.

### 1+15 — established SP1 positive control

Expected unchanged:

```text
marker2 NORMAL/SP1 -> accepted/clear-only rearm
no second physical opening
healthy cleanup
```

Also retain representative Quick / Power / Sprint controls from the same mixed-attack logs.

## Protected behavior

Do NOT change:

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

## Hard exclusions

Do NOT add:

```text
StatePosition >= 0 or other generic comparison
family-independent SP0 acceptance
new visited-target requirement
player-specific target logic
"hit1 happened" persistent flag solely to authorize marker2
marker timing delay/queue
new timer/polling
new hook/module/state machine
second physical 5 -> 7 request
authored-count special case beyond the existing exact two-FIST gate
custom damage/contact
species/name gates
animation filename inference
New Balance/DLL/version detection
unrelated refactor
```

The marker is allowed to author a rearm even when the visited list happens to be empty. G3AB must not turn marker acceptance into target-specific damage prediction.

## Allowed files

Implementation:

`prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`

Required handoff:

`docs/BETWEEN_CHATS.md`

No other file should change unless a direct contradiction prevents faithful implementation.

## Work validation

Perform static/source validation only:

```text
verify required base HEAD/source blob
inspect exact diff
confirm only Normal branch of IsSecondFistAllowed changed
confirm explicit SP0 || SP1, not a generic range/generalization
confirm marker2 operation itself is untouched
confirm Quick/Power/Sprint/first-FIST/native-clear/lifecycle/hooks unchanged
git diff --check
```

DO NOT build or run Gothic 3.

After implementation:

```text
commit + push to same branch
update docs/BETWEEN_CHATS.md concisely with result + SHA
report implementation SHA + final remote HEAD
stop for independent Normal Chat review
```

Required build statement:

`Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`
