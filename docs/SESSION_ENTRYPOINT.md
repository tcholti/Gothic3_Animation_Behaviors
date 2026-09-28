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
first Speed production build/deploy/startup = PASS
first Speed behavior check = FAIL BEFORE COMPOSITION
profile identity mismatch cause = CLOSED
runtime family-source probe = CLOSED/PASS (Hero + Sabretooth)
generic profile calibration refactor = IMPLEMENTED / STATIC REVIEW PASS
CURRENT = local production build gate
RAISE = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION.md`

## Runtime profile identity — CLOSED

The final family-source evidence established:

```text
Hero:
  Animation.GetSkeletonName(...) = Hero
  Entity.GetSkeletonName()       = Hero

Sabretooth:
  Animation.GetSkeletonName(...) = Sabretooth
  Entity.GetSkeletonName()       = Sabretooth
```

Resource identities were different (`G3_Hero_Skeleton`, `G3_Sabertooth_Body_01`) and are not used as the author-facing family token.

`CurrentMovementAni()` may still be the outgoing/current motion while Gothic is already requesting a new Hit. Preserve the pre-collision request-semantics architecture:

```text
requested gEAction + requested gEPhase = Gothic request authority
Animation.GetSkeletonName(...)         = stable AnimationFamily
left/right UseTypes                     = stable equipment facts
CurrentMovementAni                      = observational context only
```

Closed result:

`docs/archive/investigations/SPEED_RUNTIME_FAMILY_SOURCE_PROBE_RESULT.md`

Processed logs:

```text
research/archive/2026.09.28_SpeedIdentityProbetest_2.log
research/archive/2026.09.28_SpeedIdentityProbetest_sabertooth.log
```

## Generic Speed profile implementation — STATIC PASS

Production changes are bounded to:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Implemented behavior:

```text
AnimationFamily -> Animation.GetSkeletonName(...), fail closed
ReferenceHitBaseSpeed -> parsed from matching profile
BaseSpeed -> desired configured base
AttackSpeed -> compatibleSpeed * (BaseSpeed / ReferenceHitBaseSpeed)
missing/invalid calibration -> compatible result unchanged
```

The transitional Hero/weapon hard-coded reference-base table is removed. The six caller-side hooks, `EngineBridge`, collision behavior, and Raise behavior are unchanged. The S-01 finite composed-output fallback remains present.

ADR-0007 profile shape:

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.60
BaseSpeed=0.40
RaiseOverride=Off
```

Quick uses factual reference `1.00` for the existing Hero/None/1H fixture. `ReferenceRaiseBaseSpeed` and `RaiseOverride=On` are parsed/reserved only; Raise behavior remains paused. Recover remains derived from effective Hit with no independent key/reference/hook.

## Immediate route

On the local build PC:

```powershell
cmake --build build --config Release --target Script_G3AnimationBehaviors
```

Do not deploy/run until the build passes.

After build PASS:

1. deploy/hash the production DLL;
2. update the live INI to the ADR-0007 Normal + Quick test profiles with `ReferenceHitBaseSpeed`;
3. repeat the small human None+1H Normal/Quick behavior test;
4. if visible Speed control works, continue New Balance compatibility acceptance;
5. close Speed completely;
6. only then begin Raise.

## Read next

- exact continuation -> `BETWEEN_CHATS.md`
- active implementation/build gate -> `work/active/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION.md`
- family-source closure -> `archive/investigations/SPEED_RUNTIME_FAMILY_SOURCE_PROBE_RESULT.md`
- profile/request-semantics authority -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- Speed architecture -> ADR-0004 + ADR-0005 + ADR-0006

## Still paused

```text
NO Raise implementation while Speed is open
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
