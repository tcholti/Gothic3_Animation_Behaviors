# Gothic 3 — New Balance raw55 Sprint Second-FIST SP2 Compatibility Correction

**Status:** ACTIVE — IMPLEMENTED / INDEPENDENT REVIEW PASS / RUNTIME ACCEPTANCE PENDING  
**Frozen:** 2026-09-26  
**Updated:** 2026-09-26  
**Task type:** BOUNDED PRODUCTION-BEHAVIOR CORRECTION  
**Work build execution:** **PROHIBITED**  
**Permanent owner:** `PhysicalFistCollision`

## Purpose

Implement and runtime-validate the smallest evidence-backed correction for the remaining New Balance raw55 Sprint-origin second-FIST incompatibility established by EV-380.

This is **not** a new collision design task and **not** a general raw55 StatePosition widening.

## Exact source baseline

Target source:

`prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`

Frozen source blob at task creation:

`3f7eb717253f26cff3d37b23cf143f4416c034d3`

Frozen parent HEAD:

`4f52f5e7cc586a5847c2f4200fc6911765a4cc7c`

The pre-correction predicate was:

```cpp
case AttackFamily_Sprint:
    return currentFamily == AttackFamily_Power
        && (statePosition == 1 || statePosition == 2);
```

inside `IsSecondFistAllowed(...)`.

## Authoritative evidence

EV-380 maps the tested New Balance BlackTroll Sprint-origin second-FIST envelope:

```text
current POWER  / Action2 / SP2
-> legitimate
-> already accepted

current SPRINT / Action9 / SP2
-> legitimate
-> pre-correction source rejected

current SPRINT / Action9 / SP1
-> not observed
-> deliberate earliest frame1/3 fixture could not reach it because marker1 was already SP2
```

The frame8 fixture can place the **same authored marker2** on either side of the native Action9 -> Action2 transition:

```text
SPRINT/SP2  OR  POWER/SP2
```

Therefore marker2 must not require that the native transition to current POWER has already happened.

## Frozen responsibility

Modify **only** Sprint-origin second-FIST state acceptance so that the exact same owned Sprint-origin execution accepts:

```text
current POWER:
  explicit SP1 OR SP2   [preserve existing behavior]

current SPRINT:
  explicit SP2 ONLY     [new evidence-backed arm]
```

Required semantic result:

```cpp
case AttackFamily_Sprint:
    return (currentFamily == AttackFamily_Power
            && (statePosition == 1 || statePosition == 2))
        || (currentFamily == AttackFamily_Sprint
            && statePosition == 2);
```

## Published implementation

Implementation commit:

`4c85193f4efd31e789bc07d7e3c71d31a9b5326e`

Work handoff HEAD:

`9f30af5ac9c51758023d95cc8a7e16d7f07a220d`

Independent Normal Chat review result:

```text
PASS
```

Verified against frozen parent:

```text
one commit ahead
one production file changed
PhysicalFistCollision.cpp only
4 additions / 2 deletions
exact Sprint-origin second-FIST branch only
```

The published diff exactly implements the required asymmetric predicate. No helper, refactor, hook, state, diagnostic, lifecycle, raw8, equipped, Normal, Quick, true-Power, or first-FIST change is present.

This review is **source/static acceptance only**. Runtime acceptance is still required before this task closes.

## Protected behavior — MUST NOT CHANGE

Do not change:

```text
IsFirstFistAllowed(...)
Quick second-FIST predicate
Normal second-FIST predicate
true-Power second-FIST predicate
raw55 execution identity / immutable origin logic
IsAllowedOriginContinuation(...)
earlyOpeningSuppressed behavior
first-FIST physical 5 -> 7 activation
second-FIST clear-only/rearm behavior
Normal native-clear suppression
C1 lifecycle / terminal repair
native cleanup
raw8 behavior
generic equipped behavior
EquippedSprintCollision
AttackMotionRouting
diagnostics semantics / log format
hook set
```

In particular, EV-380's separate early Normal `NORMAL/SP0` discovery is **out of scope** for this task.

## Hard exclusions

Do **not** introduce:

```text
StatePosition >= 1
current SPRINT/SP1 second-FIST acceptance
(SPRINT || POWER) && {SP1,SP2} generic widening
family-independent SP2 acceptance
authored-count-specific workaround
species/name gates
animation filename inference
New Balance/DLL/version detection
new hook
new module
new persistent state
timer/polling
custom target/contact/damage behavior
refactor/cleanup unrelated to the one predicate
```

## Why the asymmetric rule is intentional

The current-Power arm already has direct SP1/SP2 compatibility evidence from EV-378/EV-379.

The current-Sprint arm has direct evidence only for SP2 from EV-379/EV-380.

Therefore the correct evidence-bounded rule is intentionally asymmetric:

```text
POWER  -> SP1 or SP2
SPRINT -> SP2 only
```

Do not simplify this asymmetry away.

## Work execution result

Work completed the bounded source responsibility and reported:

```text
implementation commit = 4c85193f4efd31e789bc07d7e3c71d31a9b5326e
required parent       = 4f52f5e7cc586a5847c2f4200fc6911765a4cc7c
final handoff HEAD     = 9f30af5ac9c51758023d95cc8a7e16d7f07a220d
git diff --check      = PASS
Build                  = NOT ATTEMPTED — Work build execution was not authorized for this task.
```

No contradiction was encountered.

## Post-implementation runtime acceptance — CURRENT NEXT STEP

After local build/deployment of the current diagnostic twin, test:

```text
1. frame1 + frame3 BlackTroll Sprint
   marker1 current SPRINT/SP2 -> accepted/open
   marker2 current SPRINT/SP2 -> MUST accept
   marker2 -> clear-only/rearm; no second physical group opening

2. frame1 + frame8 BlackTroll Sprint
   transition-race fixture
   marker2 SPRINT/SP2 -> MUST accept
   marker2 POWER/SP2  -> MUST remain accepted

3. frame1 + frame15 BlackTroll Sprint
   marker2 POWER/SP2 -> unchanged accepted/rearm

4. representative single-FIST Sprint control
   first-FIST behavior unchanged

5. true-Power double-FIST control
   existing POWER {SP1,SP2} behavior unchanged

6. representative raw55 Normal + Quick controls
   behavior unchanged
```

Then investigate the separate sheath-before-Sprint observation using marked vs unmarked/native Sprint with and without sheathing as defined in `COLLISION_TEST_PLAN.md`.

## Closure condition

Archive this task only after the exact corrected predicate passes runtime acceptance and reusable conclusions are promoted to the current raw55/reference/test authorities.

Runtime evidence interpretation, Normal/SP0 research, sheath/contact diagnosis, broader New Balance certification, standalone sentinel, production migration and speed-control work remain outside the bounded source implementation responsibility.
