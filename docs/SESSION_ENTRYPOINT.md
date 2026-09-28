# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-28

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
Speed v2 caller-side mechanism/caller set = CLOSED STATIC through EV-391/EV-392
Speed deep independent static audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
runtime family-source probe = CLOSED/PASS on Hero + Sabretooth
generic profile calibration refactor = IMPLEMENTED / STATIC REVIEW PASS
production build/deploy = PASS
initial generic Hero None+1H Normal/Quick behavior = PASS at BaseSpeed 0.40
CURRENT = New Balance contextual-modifier preservation runtime gate
RAISE = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION.md`

## Frozen runtime/profile rule

```text
requested gEAction + requested gEPhase = Gothic request authority
Animation.GetSkeletonName(...)         = runtime AnimationFamily
left/right UseTypes                     = normalized equipment profile facts
CurrentMovementAni                      = observational context only
```

Family-source evidence:

```text
Hero       -> Hero
Sabretooth -> Sabretooth
```

Closed result:

`docs/archive/investigations/SPEED_RUNTIME_FAMILY_SOURCE_PROBE_RESULT.md`

## Generic Speed implementation — runtime PASS so far

Production uses profile-owned calibration:

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.60
BaseSpeed=0.40
RaiseOverride=Off

[Profile.Hero_None_1H_Quick]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Quick
ReferenceHitBaseSpeed=1.00
BaseSpeed=0.40
RaiseOverride=Off
```

`AttackSpeed` no longer contains a Hero/weapon reference-base table. It composes the live compatible result with the matched profile's `BaseSpeed / ReferenceHitBaseSpeed` ratio and retains the S-01 finite-output fallback.

Production built/live SHA256:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

The diagnostic identity probe was removed before the behavior run.

User runtime result:

```text
multiple Hero None+1H Normal variants = configured slow speed works
multiple Hero None+1H Quick variants  = configured slow speed works
```

Therefore the earlier profile-match failure is closed for the tested profiles.

## Immediate route

Do **not** deploy the historical `Script_CombatMoveLogger` unchanged; it also hooks `Script_Game+0x42A0` and would contaminate the caller-side/New Balance compatibility architecture.

Keep the current production DLL and INI unchanged.

Using the same Hero / right-hand 1H / empty-left-hand setup:

```text
1. with stamina available, perform Normal + Quick and note the current configured 0.40 feel
2. deplete stamina until New Balance's low/depleted-stamina slowdown is active
3. immediately repeat the same Normal + Quick attacks while still depleted
4. compare depleted vs full-stamina configured attacks
```

Acceptance:

```text
depleted configured attacks remain slower than full-stamina configured attacks
```

If PASS, the key ADR-0004 runtime invariant is validated: G3AB authors base speed while New Balance contextual multipliers remain effective.

Then continue the smallest remaining Speed compatibility/fallback gates, close Speed, and only then begin Raise.

## Still paused

```text
NO Raise implementation while Speed is open
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
