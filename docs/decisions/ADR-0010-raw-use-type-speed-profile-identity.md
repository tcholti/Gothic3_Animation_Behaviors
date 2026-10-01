# ADR-0010 — Raw UseType Identity for Speed/Raise Profiles

**Status:** Superseded by ADR-0011
**Date:** 2026-10-01
**Related:** ADR-0004, ADR-0005, ADR-0007, ADR-0008, ADR-0009, `docs/ANIMATION_RULES.md`, EV-397, EV-404–EV-405

## Context

The shared Speed/Raise profile schema originally reused the normalized UseType tokens used to describe Gothic animation filenames. Several raw `gEUseType` values serialize through another animation category:

```text
Axe -> 2H
Halberd -> Staff
Pickaxe -> 2H
Broom/Rake/Shovel/Fan -> Staff
PhysicalFist -> Fist
```

Runtime calibration established that vanilla Axe currently uses the same sampled Speed values as 2H and Halberd the same sampled values as Staff. Separately, a mod may intentionally give one raw UseType distinct animation assets while leaving its factual raw UseType unchanged.

Speed should not make such separation impossible to configure merely because vanilla assets share a serialized animation token. The request-boundary architecture also rejects `CurrentMovementAni()` as profile identity because it may still name the outgoing motion.

## Decision

### 1. Keep the grouped profile key shape

The profile key remains:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Attack type remains an attack-specific key prefix inside the grouped section under ADR-0008.

### 2. Use canonical raw gEUseType identity

For Speed/Raise profile matching, `LeftAnimationUseType` and `RightAnimationUseType` identify factual raw `gEUseType`, represented by stable case-insensitive canonical tokens.

Examples:

```text
None
1H
2H
Axe
Staff
Halberd
Fist
PhysicalFist
Pickaxe
Broom
Rake
Shovel
Fan
```

Distinct raw UseTypes remain distinct profile identities even when Gothic serializes them through the same animation filename token.

### 3. Animation filename normalization remains separate

`ANIMATION_RULES.md` continues to own raw-UseType -> serialized-animation-token mapping for filenames/resources.

Both statements can therefore be true:

```text
raw Axe profile identity = Axe
serialized vanilla animation token = 2H

raw Halberd profile identity = Halberd
serialized vanilla animation token = Staff
```

Do not reuse filename normalization as profile normalization.

### 4. Shared vanilla animations may share values, not identity

When vanilla routes share animations and calibrated Speed values, the shipped INI may contain separate raw profiles with identical values. This duplication is intentional data, not duplicated C++ policy.

### 5. Separation mods become configuration-only

If an animation separation mod gives Axe unique assets while raw UseType remains Axe, `Hero_None_Axe` can be tuned independently from `Hero_None_2H`. No new Speed hook, filename parser or weapon-specific C++ branch is required.

### 6. Unknown/unconfigured raw types fail closed

A raw UseType with no matching profile receives no G3AB Speed intervention. Uncalibrated work-tool or modded combat routes can be added later through profile data after factual calibration.

### 7. Fist and PhysicalFist remain distinct

Although both serialize as `Fist`, raw8 Fist and raw55 PhysicalFist remain distinct profile identities, matching their factual runtime distinction.

## Supersession

EV-406 proved that raw UseType is not sufficient profile identity: Rapier Separation kept factual raw `1H` while Gothic resolved `Hero_..._Rapier_...`. ADR-0011 therefore supersedes this decision with resolved animation-set identity. The evidence here remains useful in showing that raw UseType and serialized animation tokens are distinct facts.

## Consequences

- ADR-0007's normalized-animation-token semantics for profile UseTypes are superseded.
- ADR-0008's grouped loadout shape remains unchanged; only the meaning of its left/right UseType fields is refined.
- `ANIMATION_RULES.md` filename normalization remains authoritative for asset naming and animation interpretation.
- The active Speed INI should include separate calibrated raw sections for 2H/Axe and Staff/Halberd.
- Pickaxe/Broom/Rake/Shovel/Fan remain absent from the initial active Speed INI unless separately calibrated.
- Runtime acceptance should include the User's Axe Separation mod as a raw-profile independence positive control.
