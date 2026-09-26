# Gothic 3 — New Balance raw55 Sprint Second-FIST SP2 Compatibility Correction

**Status:** ACTIVE — FROZEN BOUNDED IMPLEMENTATION TASK  
**Frozen:** 2026-09-26  
**Task type:** BOUNDED PRODUCTION-BEHAVIOR CORRECTION  
**Work build execution:** **PROHIBITED**  
**Permanent owner:** `PhysicalFistCollision`

## Purpose

Implement the smallest evidence-backed correction for the remaining New Balance raw55 Sprint-origin second-FIST incompatibility established by EV-380.

This is **not** a new collision design task and **not** a general raw55 StatePosition widening.

## Exact source baseline

Target source:

`prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`

Frozen source blob at task creation:

`3f7eb717253f26cff3d37b23cf143f4416c034d3`

The relevant current predicate is:

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
-> currently rejected

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

Conceptually the resulting Sprint-origin branch is:

```cpp
case AttackFamily_Sprint:
    return (currentFamily == AttackFamily_Power
            && (statePosition == 1 || statePosition == 2))
        || (currentFamily == AttackFamily_Sprint
            && statePosition == 2);
```

Equivalent locally clear syntax is allowed only if semantics are exactly identical.

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

## Allowed files

Implementation source:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

Handoff/current-state update after implementation:

```text
docs/BETWEEN_CHATS.md
```

No other file should change unless a concrete source contradiction makes the task impossible; in that case STOP and report the contradiction instead of broadening.

## Work execution sequence

1. Read:
   - `docs/SESSION_ENTRYPOINT.md`
   - `docs/BETWEEN_CHATS.md`
   - this frozen task
   - `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
   - `docs/FEATURE_DEVELOPMENT_METHOD.md`
2. Inspect only the exact `PhysicalFistCollision.cpp` predicate needed for this responsibility.
3. Implement the one bounded Sprint-origin second-FIST extension.
4. Perform source/static review only:
   - exact diff/scope inspection;
   - confirm only intended predicate behavior changed;
   - `git diff --check` if available without build/tool probing;
   - verify no protected predicate or hook changed.
5. **Do not build or run.**
6. Update `docs/BETWEEN_CHATS.md` concisely with:
   - implementation result;
   - commit SHA;
   - `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`
   - next step = Normal Chat review + User local build/runtime.
7. Commit and push to `docs/collision-source-evidence`.
8. STOP.

## Required Work handoff

Report:

```text
implementation commit SHA
files changed
exact predicate before/after
protected-behavior audit result
static checks performed
Build: NOT ATTEMPTED — Work build execution was not authorized for this task.
```

Do not interpret runtime behavior from source alone.

## Post-implementation runtime acceptance — Normal Chat + User

After independent source review and local deployment, use the corrected build to test:

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

## Stop condition

This Work task ends after the bounded source edit, static audit, commit/push and concise handoff.

Runtime acceptance, evidence interpretation, Normal/SP0 research, sheath/contact diagnosis, broader New Balance certification, standalone sentinel, production migration and speed-control work are all outside this Work task.
