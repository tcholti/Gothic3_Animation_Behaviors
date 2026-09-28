# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-28

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 collision production integration = CLOSED/PASS
EV-391/EV-392 Speed caller-side mechanism + six-site caller set = CLOSED STATIC
family-source probe = CLOSED/PASS on Hero + Sabretooth
ADR-0007 generic profile/request semantics = ACCEPTED
generic profile calibration refactor = IMPLEMENTED / STATIC REVIEW PASS
production build/deploy = PASS
built/live SHA = 6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
Hero None+1H Normal + Quick BaseSpeed=0.40 behavior = PASS across multiple variants
CURRENT = New Balance low/depleted-stamina modifier-preservation gate
RAISE = PAUSED until Speed closes
```

## Frozen rule

```text
requested gEAction + requested gEPhase = Gothic request authority
Animation.GetSkeletonName(...)         = runtime AnimationFamily
left/right UseTypes                     = normalized equipment profile facts
CurrentMovementAni                      = observational context only
```

## Current live profiles

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

The original profile-match failure is closed for these profiles. `AttackSpeed` now uses profile-owned `ReferenceHitBaseSpeed`; no Hero/weapon base table remains in behavior C++.

Do not deploy the historical `Script_CombatMoveLogger` unchanged because it also hooks `Script_Game+0x42A0` and would contaminate the exact compatibility architecture under test.

## Next

Keep DLL and INI unchanged:

```text
full/available stamina -> perform Normal + Quick and note configured 0.40 feel
-> deplete stamina until New Balance slowdown is active
-> immediately repeat same Normal + Quick while depleted
-> compare
```

Acceptance:

```text
depleted configured attacks are slower than full-stamina configured attacks
```

PASS means the key Speed v2 invariant is working at runtime: G3AB changes the base while New Balance's contextual multiplier still applies.

Active task:

`docs/work/active/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION.md`
