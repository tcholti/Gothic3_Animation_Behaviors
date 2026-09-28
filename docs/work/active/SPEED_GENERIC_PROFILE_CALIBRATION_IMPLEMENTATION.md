# Speed Generic Profile Calibration Implementation

**Status:** IMPLEMENTED / STATIC REVIEW PASS / BUILD PENDING  
**Task class:** Bounded production source correction/refactor  
**Branch:** `development`

## Purpose

Implement only the generic profile/calibration architecture already frozen by ADR-0007 and the completed runtime family-source probe.

This task does **not** redesign Speed transport. The six existing caller-side Speed hooks and live `Script_Game+0x42A0` compatible-result call remain unchanged.

## Proven runtime identity

The closed family-source probe established:

```text
Hero       -> Animation.GetSkeletonName(...) = Hero
Sabretooth -> Animation.GetSkeletonName(...) = Sabretooth
```

`Animation.GetResourceName()` returned resource identities instead (`G3_Hero_Skeleton`, `G3_Sabertooth_Body_01`). `CurrentMovementAni()` could remain stale relative to the requested Hit. Therefore runtime profile identity uses stable skeleton-family identity plus factual request action/phase and equipped UseTypes.

## Frozen production correction

### BehaviorProfiles

1. Replace `Animation.GetResourceName()` family extraction with `Animation.GetSkeletonName(...)`.
2. Fail closed if the skeleton name is unavailable or empty.
3. Preserve normalized left/right animation UseType handling and ActionProfile handling.
4. Extend profile data to parse/store independently:

```text
ReferenceHitBaseSpeed=<positive finite float>
BaseSpeed=<positive finite float>
ReferenceRaiseBaseSpeed=<positive finite float>   ; reserved for later Raise
RaiseOverride=Off|On                              ; parsed/stored only while Raise remains paused
```

5. Missing/invalid optional values disable only the relevant feature/calibration fact where practical.

### AttackSpeed

1. Keep factual action mapping and Hit-only gate unchanged.
2. Keep profile lookup unchanged in concept.
3. Remove the transitional Hero-only hard-coded reference-base table and raw-UseType reference lookup.
4. Require both:

```text
profile.hasBaseSpeed
profile.hasReferenceHitBaseSpeed
```

5. Use:

```text
referenceBase = profile.referenceHitBaseSpeed
composed = compatibleSpeed * (profile.baseSpeed / referenceBase)
```

6. Preserve all existing finite/positive fail-closed guards, including the S-01 composed-output finite guard.

### INI template

Update only the shipped template to ADR-0007 syntax and examples. The template remains commented/neutral.

## Allowed production files

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Documentation/evidence maintenance may update task/current-state files.

## Protected boundaries

Do not change:

- any Speed hook address or caller transport in `EngineBridge`;
- `Script_Game+0x42A0` ownership policy;
- collision source/marker/lifecycle behavior;
- `AttackRaise` behavior or add Raise hooks;
- New Balance compatibility algebra;
- Recover behavior;
- Normal/Quick ActionProfile scope.

## Static acceptance result — PASS

Implemented source satisfies the frozen checks:

1. runtime family now uses successful `Animation.GetSkeletonName(...)` only;
2. resource-name aliases are absent;
3. no current-motion filename parsing is introduced;
4. profile parser accepts positive finite `ReferenceHitBaseSpeed`, `BaseSpeed`, and reserved `ReferenceRaiseBaseSpeed` independently;
5. `RaiseOverride` defaults `Off` and accepts `On` without activating Raise behavior;
6. `AttackSpeed` contains no Hero-only family/base table and no weapon-specific reference lookup;
7. missing/invalid `ReferenceHitBaseSpeed` returns compatible speed unchanged;
8. the S-01 composed non-finite output guard remains present;
9. compare from the user-pushed Sabretooth evidence checkpoint `f2d40c89cda314b98c640f956af003168ab7abec` shows no `EngineBridge`, collision, or Raise behavior source change.

Production files changed are exactly:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

## Next gate — local build

Build only the production target from current `development`:

```powershell
cmake --build build --config Release --target Script_G3AnimationBehaviors
```

Do not deploy or run until the build passes.

After build/deploy, the first behavior test must use an ADR-0007 profile containing both `ReferenceHitBaseSpeed` and `BaseSpeed`. For Hero + None + 1H:

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

Raise remains paused until Speed is completely closed.
