# Speed Runtime Animation-Family Source Probe — Result

**Status:** CLOSED / PASS  
**Date:** 2026-09-28  
**Branch:** `development`

## Question

Which factual runtime API should provide the user-facing `AnimationFamily` token used by Speed/Raise profile identity?

## Human control

The refreshed standalone `Script_SpeedIdentityProbe.dll` was deployed with matching built/live SHA256:

`DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`

Human Normal/Quick CombatMove observations consistently produced:

```text
RequestedPhaseName=Hit
AnimationResourceName=G3_Hero_Skeleton
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Hero
EntitySkeletonName=Hero
RawLeftUseType=None
RawRightUseType=1H
Normal Action1
Quick Action4/5
```

`CurrentMovementAni()` could still name prior/current motions such as HoldRight_End, Attack_Recover, Ambient_Loop or Parade_Begin while the factual new request was already Normal/Quick Hit.

Therefore current-motion filename parsing is not the production Speed request identity source.

Processed evidence:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

## Non-Hero control

Transformed-player Sabretooth Normal/Quick observations consistently produced:

```text
RequestedPhaseName=Hit
AnimationResourceName=G3_Sabertooth_Body_01
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Sabertooth
EntitySkeletonName=Sabertooth
RawLeftUseType=None
RawRightUseType=Fist/raw8
Normal Action1
Quick Action4/5
```

Again `CurrentMovementAni()` remained on an Ambient_Loop while the factual request was Hit.

Processed evidence:

`research/archive/2026.09.28_SpeedIdentityProbetest_sabertooth.log`

## Decision

Use:

```cpp
entity.Animation.GetSkeletonName(...)
```

as the generic runtime source for profile `AnimationFamily`.

Reason:

- it returns the exact author-facing family tokens proven for two distinct families (`Hero`, `Sabertooth`);
- it belongs directly to the animation property set;
- it provides explicit success/failure, so runtime key construction can fail closed;
- it avoids resource-name aliases such as `G3_Hero_Skeleton -> Hero`;
- it is independent of whether the newly requested attack motion has become the current motion yet.

`Entity.GetSkeletonName()` is corroborating evidence, not the selected primary source.

## Request-semantics rule recovered from the pre-collision prototype

Speed/Raise profile selection must separate stable actor identity from Gothic's factual request identity:

```text
stable actor facts:
  AnimationFamily from Animation.GetSkeletonName(...)
  left/right normalized animation UseTypes

request facts:
  factual gEAction
  factual gEPhase
```

Do not infer the requested attack family/phase from `CurrentMovementAni()`.

This preserves the successful pre-collision architecture:

- old Speed used factual action from EAX plus factual phase argument;
- old Raise explicitly requested `Action + Raise` and let Gothic resolve the concrete P0/P1/etc. animation.

## Disposition

**PASS — GENERIC RUNTIME ANIMATION-FAMILY SOURCE CLOSED.**

Next bounded production responsibility:

- use `Animation.GetSkeletonName(...)` in `BehaviorProfiles`;
- parse profile-owned `ReferenceHitBaseSpeed`;
- remove the transitional Hero-only reference-base table from `AttackSpeed`;
- preserve the existing six caller-side Speed hooks and compatible `B*M -> C*M` composition;
- update the shipped INI template to the accepted ADR-0007 schema;
- do not implement Raise behavior yet.
