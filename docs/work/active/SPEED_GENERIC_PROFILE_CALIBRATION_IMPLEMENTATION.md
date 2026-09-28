# Speed Generic Profile Calibration Implementation

**Status:** ACTIVE  
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

## Static acceptance

1. runtime family uses successful `Animation.GetSkeletonName(...)` only;
2. resource-name aliases are absent;
3. no current-motion filename parsing is introduced;
4. profile parser accepts positive finite Hit/Raise reference values and desired BaseSpeed;
5. `RaiseOverride` defaults Off and accepts On without activating Raise behavior;
6. `AttackSpeed` contains no Hero-only family/base table;
7. missing/invalid `ReferenceHitBaseSpeed` returns compatible speed unchanged;
8. composed non-finite output still returns compatible speed unchanged;
9. no `EngineBridge`, collision, or Raise source changes.

## Runtime gate after source review/build/deploy

First use only the existing human Hero/None/1H profiles with deliberately visible values and known factual reference bases. Confirm exact profile match and visible Speed behavior before widening acceptance.

Raise remains paused until Speed is completely closed.
