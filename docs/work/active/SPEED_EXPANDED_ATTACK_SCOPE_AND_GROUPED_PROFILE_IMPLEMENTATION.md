# Speed Expanded Attack Scope and Grouped Profile Implementation

**Status:** SOURCE IMPLEMENTED / STATIC REVIEW PASS / BUILD+RUNTIME PENDING  
**Task class:** Bounded production source extension + static review; build/runtime remain later gates  
**Branch:** `development`

## Purpose

Extend the already-runtime-proven Speed v2 mechanism from Normal/Quick to the additional factual Hit-speed routes accepted by ADR-0008, while replacing the one-section-per-attack INI layout with the grouped loadout layout.

This task is an explicit product-scope expansion after the initial Normal/Quick runtime proof. It does not invalidate that proof and must not redesign the already-accepted compatible composition mechanism.

## Frozen baseline

Already proven in production/runtime:

```text
AnimationFamily = Animation.GetSkeletonName(...)
left/right UseTypes = normalized loadout facts
factual requested gEAction + gEPhase = request authority
CurrentMovementAni = observational only

compatible = B * M
configured = compatible * (C / B) = C * M
```

Production built/live baseline SHA256:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

Runtime baseline:

```text
Hero None+1H Normal BaseSpeed=0.40 = PASS
Hero None+1H Quick  BaseSpeed=0.40 = PASS
Hero None+2H configured Speed preserves New Balance depleted-stamina slowdown = PASS
```

## Frozen grouped profile schema

One section represents:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Example:

```ini
[Profile.Hero_None_1H]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H

Normal_ReferenceHitBaseSpeed=0.60
Normal_BaseSpeed=1.00
Normal_RaiseOverride=On

Quick_ReferenceHitBaseSpeed=1.00
Quick_BaseSpeed=1.00
Quick_RaiseOverride=On

Power_ReferenceHitBaseSpeed=1.00
Power_BaseSpeed=1.00
Power_RaiseOverride=Off

Pierce_ReferenceHitBaseSpeed=1.00
Pierce_BaseSpeed=1.00
Pierce_RaiseOverride=Off
```

Section suffix is label-only. Do not parse identity from the section name.

## Supported attack scope for this implementation

Implement Hit Speed only for:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Factual action mapping:

```text
Action1  -> Normal
Action4  -> Quick
Action5  -> Quick
Action2  -> Power
Action11 -> Pierce
Action14 -> Hack
Action6  -> SimpleWhirl
Action10 -> Whirl
```

Generic Quick Action3 remains a selector/request that resolves to factual Action4/5 on the proven playback route; do not add Action3 as a separate playback-speed profile.

## Caller-side transport extension

Preserve the existing six Normal/Quick hooks exactly.

Add only the proven Hit consumers:

```text
Power:
  Script_Game+0x47F6C

Pierce:
  Script_Game+0x47328
  Script_Game+0x4770F
  Script_Game+0x4786F

Hack:
  Script_Game+0x42FF4
  Script_Game+0x431B4
  Script_Game+0x432EB

SimpleWhirl:
  Script_Game+0x4C6FA

Whirl:
  Script_Game+0x4DF1F
```

All are `gEPhase_Hit` routes on the tested build.

Power Raise at `Script_Game+0x47D51` is evidence only. Do not hook or implement Raise behavior in this task.

## Sprint exclusion

Do not implement `Sprint` / Action9 Speed in this task.

The exhaustive direct-caller analysis did not establish a distinct Action9 `+0x42A0` Hit consumer. Action9 appears in combat pose/request checks, and observed Sprint behavior may reuse Power-named animations, but neither fact proves a safe Speed transport/profile mapping.

Sprint must remain live-compatible/native until separately proven.

## BehaviorProfiles responsibility

Refactor profile storage from one record per loadout+ActionProfile to one record per loadout containing independent attack settings.

Conceptual shape:

```text
LoadoutProfile
  key:
    animationFamily
    leftAnimationUseType
    rightAnimationUseType

  attack settings:
    Normal
    Quick
    Power
    Pierce
    Hack
    SimpleWhirl
    Whirl
```

Each attack setting owns, independently:

```text
hasReferenceHitBaseSpeed
referenceHitBaseSpeed
hasBaseSpeed
baseSpeed
raiseOverride   # parsed/stored only; no Raise behavior in this task
```

Do not add user-facing or internal Raise-speed calibration fields unless later Raise runtime evidence requires them.

Parser requirements:

- positive finite floats only for reference/base speed;
- `RaiseOverride=On` only for normalized literal `on`, otherwise Off/fail-safe;
- missing attack block = inactive for that attack;
- duplicate normalized loadout identity = ambiguous/fail-closed;
- unknown attack-prefixed keys may be ignored for forward compatibility;
- retain the existing normalized family/use-type semantics and generic family source.

## AttackSpeed responsibility

Keep `AttackSpeed` stateless and generic.

Runtime:

```text
factual gEAction
-> supported AttackType
-> build normalized loadout key
-> find grouped loadout profile
-> select matching attack settings
-> require valid BaseSpeed + ReferenceHitBaseSpeed
-> compose live compatible result by BaseSpeed / ReferenceHitBaseSpeed
-> finite-output guard
-> otherwise return compatible result unchanged
```

No weapon/family-specific C++ base table.
No New Balance multiplier replication.
No current-motion parsing.
No final-speed hard replacement.

## EngineBridge responsibility

`EngineBridge` remains the sole low-level hook owner.

Reuse the existing common composed-speed thunk/caller mechanism. Do not create per-attack policy thunks when the common factual-action transport already suffices.

Do not hook the `Script_Game+0x42A0` entry.

## Protected boundaries

Do not change:

```text
collision behavior/source
+0x42A0 ownership policy
compatible C/B algebra
Animation.GetSkeletonName family source
CurrentMovementAni exclusion
Recover behavior
AttackRaise behavior/hooks
main branch
```

Do not begin Raise implementation.

## Source scope

Expected production files:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Touch another production file only if a concrete compile/API dependency requires it; document why before widening scope.

## Static review result

Reviewed current source through production HEAD `642c88a4e6244ae7377ba835507750af7914e2f5`.

```text
[x] grouped section identity is family + left + right only
[x] seven attack settings are independently parsed/stored
[x] Action1/2/4/5/6/10/11/14 map correctly
[x] Action3 is not treated as factual playback Quick
[x] Action9/Sprint remains unsupported/fail-closed
[x] missing/invalid per-attack calibration returns compatible unchanged
[x] S-01 finite composed-output guard remains
[x] existing six Normal/Quick hooks remain unchanged
[x] only nine newly proven Hit call sites are added
[x] Power Raise +0x47D51 is not hooked
[x] common thunk still calls live +0x42A0 exactly once
[x] no collision or Raise behavior drift found in the bounded implementation lineage
[x] shipped INI uses grouped neutral/commented examples
```

Implementation lineage is bounded to the expected five production files:

```text
61e805ea9eaf0cbb2e0765fe65df97252c46a554  Group behavior profiles by loadout
8c8ebe37ccd66a9e8317ded611418b6b0f1f881d  Parse grouped attack settings
1ed68e8ae8867c6f7f8be63050aad9a185188e48  Map expanded factual attack speed profiles
ad3e5e01fc581dc36dc4d0b6e33a0e46d2a19156  Group Speed INI settings by loadout
642c88a4e6244ae7377ba835507750af7914e2f5  Extend Speed transport to proven attack callers
```

Static verdict: **PASS**. No further production-source change is justified before local build/deploy.

## Build/runtime boundary

The User is currently away from the local build PC.

**NEXT GATE = local build/deploy.** Do not claim build or runtime acceptance before the User performs it.

## Later runtime acceptance

After a successful local build/deploy, use a small representative matrix rather than exhaustive repetition. At minimum validate:

- already-proven Normal/Quick did not regress;
- one visible Power configured-speed control;
- Pierce/Hack and Whirl/SimpleWhirl representative configured controls where the animation set makes visual comparison practical;
- unconfigured/fail-closed fallback;
- New Balance compatibility remains intact.

Sprint remains outside acceptance until separately proven.
