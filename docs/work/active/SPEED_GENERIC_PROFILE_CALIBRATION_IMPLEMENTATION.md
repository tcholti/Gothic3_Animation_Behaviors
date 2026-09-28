# Speed Generic Profile Calibration Implementation

**Status:** IMPLEMENTED / STATIC REVIEW PASS / BUILD+DEPLOY PASS / INITIAL BEHAVIOR PASS  
**Task class:** Bounded production source correction/refactor + runtime acceptance  
**Branch:** `development`

## Purpose

Implement and validate only the generic profile/calibration architecture frozen by ADR-0007 and the completed runtime family-source probe.

This task does **not** redesign Speed transport. The six existing caller-side Speed hooks and live `Script_Game+0x42A0` compatible-result call remain unchanged.

## Proven runtime identity

The closed family-source probe established:

```text
Hero       -> Animation.GetSkeletonName(...) = Hero
Sabretooth -> Animation.GetSkeletonName(...) = Sabretooth
```

`Animation.GetResourceName()` returned resource identities instead (`G3_Hero_Skeleton`, `G3_Sabertooth_Body_01`). `CurrentMovementAni()` may remain the outgoing/current motion while a new Hit is already requested. Runtime profile identity therefore uses stable skeleton-family identity + factual Gothic Action/Phase request + normalized left/right UseTypes.

## Implemented production correction

### BehaviorProfiles

- runtime `AnimationFamily` uses `Animation.GetSkeletonName(...)` and fails closed if unavailable/empty;
- normalized left/right animation UseType handling and ActionProfile handling are preserved;
- profile data parses/stores independently:

```text
ReferenceHitBaseSpeed=<positive finite float>
BaseSpeed=<positive finite float>
ReferenceRaiseBaseSpeed=<positive finite float>   ; reserved for later Raise
RaiseOverride=Off|On                              ; parsed/stored only while Raise remains paused
```

### AttackSpeed

- factual ActionProfile mapping and Hit-only gate remain unchanged;
- the transitional Hero-only hard-coded reference-base table and raw-UseType reference lookup are removed;
- Speed requires both `profile.hasBaseSpeed` and `profile.hasReferenceHitBaseSpeed`;
- composition is:

```text
compatibleSpeed * (BaseSpeed / ReferenceHitBaseSpeed)
```

- all finite/positive fail-closed guards remain, including the S-01 composed-output finite guard.

### Protected boundaries

No change to:

- Speed hook addresses or caller transport in `EngineBridge`;
- `Script_Game+0x42A0` ownership policy;
- collision source/marker/lifecycle behavior;
- `AttackRaise` behavior or Raise hooks;
- Recover behavior;
- Normal/Quick ActionProfile scope.

## Static acceptance — PASS

Production source changes are exactly:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Compare from the user-pushed Sabretooth evidence checkpoint `f2d40c89cda314b98c640f956af003168ab7abec` showed no `EngineBridge`, collision, or Raise behavior source changes.

## Build/deploy gate — PASS

Production target built successfully.

Built/live production SHA256 matched exactly:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

The completed `Script_SpeedIdentityProbe.dll` was removed before the production behavior run.

Primary runtime stack:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

## Initial generic runtime behavior — PASS

Live INI:

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

User runtime result on 2026-09-28:

- visible configured Speed behavior works;
- multiple 1H Normal attack variants obey the configured slow speed;
- multiple 1H Quick attack variants obey the configured slow speed;
- no P0/P1/P2/P3-specific configuration or code is required.

Disposition:

**PASS — original profile-match/runtime-control failure is closed for the tested Hero + None + 1H Normal/Quick profiles.**

No additional logger is required for this basic behavior gate. The existing historical `Script_CombatMoveLogger` is not suitable unchanged because it also takes a function hook on `Script_Game+0x42A0`, which would contaminate the current New Balance-compatible caller-side architecture.

## Current gate — New Balance contextual-modifier preservation

Keep the current production DLL and the current `BaseSpeed=0.40` INI unchanged.

Test the architectural invariant from ADR-0004:

```text
configured full-stamina attack = C * M_full
configured depleted-stamina attack = C * M_depleted
```

The old prototype failed this kind of gate because configured speed could replace the final effective result and erase the low-stamina slowdown.

### Runtime test

Using the same ordinary Hero / right-hand 1H / empty-left-hand setup:

1. with stamina comfortably available, perform several Normal and Quick attacks and note the established configured 0.40 feel;
2. deplete stamina through ordinary gameplay until the New Balance low/depleted-stamina slowdown condition is active;
3. immediately repeat the same Normal and Quick attacks while still depleted;
4. report whether the depleted attacks are visibly slower than the full-stamina configured attacks.

Acceptance:

```text
depleted configured attacks are still slowed relative to full-stamina configured attacks
```

That result would prove the key runtime reason for Speed v2: G3AB changes the base while preserving New Balance's contextual multiplier chain.

Do not deploy the old `Script_CombatMoveLogger` for this gate. Raise remains paused until Speed is completely closed.
