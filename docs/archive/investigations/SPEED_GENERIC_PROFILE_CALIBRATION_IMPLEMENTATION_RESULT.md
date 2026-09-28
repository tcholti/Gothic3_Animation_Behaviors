# Speed Generic Profile Calibration Implementation — Result

**Status:** CLOSED / PASS  
**Closed:** 2026-09-28  
**Branch:** `development`

## Responsibility

Implement and validate the generic profile/calibration architecture frozen by ADR-0007 without changing the six caller-side Speed transport hooks, collision behavior, Raise behavior, or Recover semantics.

## Production result

`BehaviorProfiles` now:

- obtains runtime `AnimationFamily` from successful `entity.Animation.GetSkeletonName(...)`;
- fails closed when the skeleton-family token is unavailable or empty;
- preserves normalized left/right animation UseType handling;
- parses profile-owned `ReferenceHitBaseSpeed`, `BaseSpeed`, reserved `ReferenceRaiseBaseSpeed`, and `RaiseOverride=Off|On`.

`AttackSpeed` now:

- keeps factual Normal/Quick action mapping and factual Hit-phase gating;
- contains no Hero-only or weapon-specific reference-base table;
- requires both configured `BaseSpeed` and factual `ReferenceHitBaseSpeed`;
- composes the live compatible result as:

```text
compatibleSpeed * (BaseSpeed / ReferenceHitBaseSpeed)
```

- preserves all finite/positive fail-closed checks, including the S-01 composed-output finite guard.

Protected boundaries remained unchanged:

```text
EngineBridge Speed hook addresses / caller transport
Script_Game+0x42A0 ownership policy
collision behavior
AttackRaise behavior
Recover behavior
Normal/Quick ActionProfile scope
```

## Family-source evidence

The preceding closed probe established:

```text
Hero       -> Animation.GetSkeletonName(...) = Hero
Sabretooth -> Animation.GetSkeletonName(...) = Sabretooth
```

`Animation.GetResourceName()` returned implementation-resource identities instead (`G3_Hero_Skeleton`, `G3_Sabertooth_Body_01`). `CurrentMovementAni()` can remain the outgoing/current motion while Gothic is already requesting a new Hit, so factual requested Action/Phase remain authoritative for the attack request.

## Build / deploy

Production target built successfully and was deployed as the live G3AB DLL.

Built/live SHA256 matched exactly:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

The temporary `Script_SpeedIdentityProbe.dll` was removed before production behavior testing.

Primary tested stack:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

## Runtime acceptance

### Generic configured behavior

Hero / empty-left / right-hand 1H profiles with deliberately obvious `BaseSpeed=0.40` showed visible configured Speed behavior across multiple Normal and Quick attack variants. No P0/P1/P2/P3-specific profile split was required.

This closes the original runtime failure where the profile never matched because the old key used `G3_Hero_Skeleton` instead of the author-facing `Hero` family token.

### New Balance contextual multiplier preservation

The User then used a representative Hero / empty-left / right-hand 2H Normal profile with:

```ini
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=2H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.70
BaseSpeed=1.00
RaiseOverride=Off
```

The 2H animations were authored for the neutral `1.0` playback baseline, making the comparison visually clear. At full stamina the configured attack used the intended faster base. At depleted/zero stamina the same configured 2H attack visibly slowed.

This is the key runtime invariant from ADR-0004:

```text
compatible = B * M
configured = (B * M) * (C / B) = C * M
```

The configured base remains effective while New Balance's stamina/context multiplier also remains effective.

Staff was also observed to retain stamina slowdown, but the 2H control is the clearer acceptance fixture and is the basis for closure.

## Disposition

**PASS — generic profile calibration implementation is complete.**

**PASS — configured Normal/Quick Speed behavior works for the tested Hero profiles.**

**PASS — the key New Balance contextual-multiplier-preservation invariant is validated on a configured 2H Normal control.**

This closes the implementation/refactor responsibility. Remaining work is final Speed runtime acceptance/fallback coverage, not redesign of the proven mechanism.

Raise remains paused until Speed is completely closed.
