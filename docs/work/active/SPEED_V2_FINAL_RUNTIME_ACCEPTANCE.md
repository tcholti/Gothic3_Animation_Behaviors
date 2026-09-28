# Speed v2 Final Runtime Acceptance

**Status:** ACTIVE  
**Task class:** Bounded runtime acceptance / no redesign  
**Branch:** `development`

## Purpose

Close the remaining runtime acceptance gates for the already-implemented Speed v2 architecture.

The generic profile/calibration implementation is complete and archived at:

`docs/archive/investigations/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION_RESULT.md`

This task must not redesign transport or reopen settled family/profile architecture unless contradictory evidence appears.

## Proven production state

Production built/live SHA256:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

Primary intended stack:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Proven runtime identity and composition:

```text
AnimationFamily = Animation.GetSkeletonName(...)
factual requested gEAction + gEPhase = request authority
left/right UseTypes = normalized profile identity facts
CurrentMovementAni = observational only

compatible result = B * M
configured result = (B * M) * (C / B) = C * M
```

## Runtime evidence already passed

### Configured behavior

Hero / empty-left / right-hand 1H:

- multiple Normal variants visibly obeyed configured `BaseSpeed=0.40`;
- multiple Quick variants visibly obeyed configured `BaseSpeed=0.40`;
- no pose-specific P0/P1/P2/P3 configuration was needed.

### New Balance multiplier preservation

Hero / empty-left / right-hand 2H Normal:

```ini
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=2H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.70
BaseSpeed=1.00
RaiseOverride=Off
```

The configured 2H attack visibly slowed when stamina reached zero/depleted state. This validates the core ADR-0004 invariant that G3AB authors the base while the compatible New Balance contextual multiplier remains effective.

## Remaining acceptance scope

Keep the remaining work small and evidence-driven. Do not repeat already-closed family-source, static caller-set, or deep-audit work.

Tomorrow, first review the already-proven matrix and run only the smallest remaining runtime controls needed to close Speed, expected to include:

1. **unconfigured fallback control** — a representative profile absent from the INI remains native/New-Balance behavior;
2. **configured representative coverage** — enough Normal/Quick/use-type coverage to show the generic profile path is not accidentally limited to the first 1H fixture;
3. **native-only sanity/fallback** if still required by ADR-0004/accepted runtime plan, after the New Balance intended-stack path is considered closed;
4. any additional contextual-modifier control only if existing evidence leaves a real ambiguity.

Do not add a logger merely for reassurance. The historical `Script_CombatMoveLogger` hooks `Script_Game+0x42A0` and is not suitable unchanged for compatibility acceptance.

## Protected boundaries

No source change unless runtime evidence contradicts the accepted mechanism.

Do not change:

```text
six Speed caller hooks
+0x42A0 ownership policy
profile identity
C/B composition algebra
collision behavior
Raise behavior
Recover behavior
```

## Completion condition

Speed closes when the smallest representative runtime matrix confirms:

```text
configured Normal/Quick behavior works
dynamic New Balance multiplier preservation works
unconfigured/unsupported routes preserve compatible fallback
native-only sanity is acceptable where required
no contradictory regression appears
```

Only after Speed closes may Raise become the active feature under ADR-0006.
