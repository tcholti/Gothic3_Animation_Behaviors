# Speed Runtime Hero Family Normalization Correction

**Status:** ACTIVE  
**Task class:** Bounded production correction / source-only  
**Branch:** `development`

## Purpose

Correct only the factual runtime family-normalization mismatch proven by the completed Speed identity probe.

Runtime evidence established:

```text
Entity.Animation.GetResourceName() = G3_Hero_Skeleton
current normalized runtime key      = g3_hero_skeleton
ADR-0007 user-facing family token   = Hero -> hero
```

This caused exact otherwise-valid Hero/None/1H Normal and Quick profiles to fail lookup before Speed composition could run.

## Frozen correction

Preserve ADR-0007's user-facing configuration contract:

```ini
AnimationFamily=Hero
```

Do not change the INI schema to require raw skeleton resource names.

In `BehaviorProfiles::TryBuildRuntimeKey()`, after normalizing the factual animation resource name, map only the exact evidence-backed resource identity:

```text
g3_hero_skeleton -> hero
```

Unknown/unproven runtime family strings remain unchanged and therefore fail closed unless independently supported by future evidence.

## Allowed production file

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
```

No other production source may change.

## Protected boundaries

Do not change:

- `AttackSpeed.cpp/.h` composition policy or technical base facts;
- any of the six Speed caller hooks or addresses;
- `EngineBridge.cpp/.h`;
- INI schema or accepted `AnimationFamily=Hero` author-facing token;
- collision behavior;
- Raise behavior;
- New Balance compatibility policy;
- diagnostics behavior.

## Static acceptance

Before runtime:

1. exact `G3_Hero_Skeleton` normalization yields runtime key family `hero`;
2. other runtime resource strings are not generalized or guessed;
3. existing UseType normalization and ActionProfile handling are unchanged;
4. production Speed transport/composition source is untouched;
5. collision and Raise source are untouched.

## Runtime gate

After source review/build/deploy:

- keep the existing Hero/None/1H Normal and Quick INI profiles;
- first re-run the identity probe or equivalent bounded check to confirm `ProfileMatch=true` and parsed `BaseSpeed`;
- then repeat the small Normal/Quick Speed behavior test before moving to wider New Balance acceptance.
