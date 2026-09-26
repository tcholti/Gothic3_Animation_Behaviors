# Gothic 3 — New Balance raw55 Sprint Second-FIST SP2 Compatibility Correction

**Status:** CLOSED/PASS — IMPLEMENTED / INDEPENDENT REVIEW PASS / RUNTIME ACCEPTANCE PASS EV-381  
**Frozen:** 2026-09-26  
**Closed:** 2026-09-26  
**Task type:** BOUNDED PRODUCTION-BEHAVIOR CORRECTION  
**Work build execution:** **PROHIBITED**  
**Permanent owner:** `PhysicalFistCollision`

## Purpose

Implement and runtime-validate the smallest evidence-backed correction for the remaining New Balance raw55 Sprint-origin second-FIST incompatibility established by EV-380.

This was **not** a new collision design task and **not** a general raw55 StatePosition widening.

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

EV-380 mapped the tested New Balance BlackTroll Sprint-origin second-FIST envelope:

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

Independent Normal Chat source/static review:

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

No helper, refactor, hook, state, diagnostic, lifecycle, raw8, equipped, Normal, Quick, true-Power, or first-FIST change was present.

## Runtime acceptance — EV-381

Deployed diagnostic:

`B4161D74DD849F4B7B67D9ACCFC42A8D8784F7EF19FB968F2E44D67ED57BD689`

Built/live hashes matched exactly.

Runtime result:

```text
frame1+3:
  marker1 SPRINT/SP2 -> accepted/open 5->7
  marker2 SPRINT/SP2 -> ACCEPTED
  marker2 ClearTriggeredList=1
  marker2 GroupRequested=0
  native cleanup 7->5

frame1+8:
  corrected build preserves accepted POWER/SP2 continuation
  EV-380 establishes same authored timing can also remain SPRINT/SP2
  corrected frame1+3 directly validates the new SPRINT/SP2 arm

frame1+15:
  SPRINT/SP2 first -> POWER/SP2 second
  both accepted
  zero CORE marker anomalies in the full corrected log

true-Power control:
  first SP2 opens
  second SP2 clear-only rearms
  cleanup remains native
```

The exact bounded correction is therefore runtime accepted.

The batch also confirmed that accepted/open/rearmed raw55 opportunities may legitimately produce no `ONDAMAGE`: true-Power examples C1=9, C1=27 and C1=40 had correct marker mechanics but no native contact callback. The unmarked/native control likewise contains native raw55 windows that open and clean without damage. This separates downstream native contact/target/geometry outcomes from authored-marker correctness.

The User's sheath/draw-associated missing-contact observation is therefore not a collision-marker blocker on current evidence. The native control does not isolate a native Sprint-after-sheath miss specifically, so that narrow subtype remains non-blocking/qualitative rather than a claimed proven Sprint rule.

## Protected behavior — VERIFIED UNCHANGED

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

EV-380/EV-381's separate early Normal `NORMAL/SP0` second-marker discovery remains **out of scope and deferred**.

## Hard exclusions preserved

No:

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
unrelated refactor/cleanup
```

## Closure

Disposition:

```text
CLOSED/PASS EV-381
```

Reusable conclusions are promoted to the current evidence/reference/test/current-state owners. This task should live under `docs/archive/investigations/` after closure.

Broader New Balance certification, the standalone/no-New-Balance post-compat sentinel, the separate Normal/SP0 authoring-boundary question, production migration and speed-control work remain separate responsibilities.