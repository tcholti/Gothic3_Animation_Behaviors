# Speed Native/Compatible Calibration Probe

**Status:** ACTIVE  
**Task class:** Bounded diagnostics-only calibration tool  
**Branch:** `development`

## Purpose

Create a reusable diagnostics-only probe that records the speed values returned by the live `Script_Game+0x42A0 GetAnimationSpeedModifier` owner at the proven Speed caller sites, without changing gameplay behavior.

Primary goals:

1. establish native Gothic `ReferenceHitBaseSpeed` calibration facts for common animation-family/loadout/attack routes;
2. compare the same routes with New Balance loaded without treating New Balance values as native references;
3. provide a compact tool suitable for broad runtime sampling and, later, optional public release for advanced profile calibration.

## Frozen semantic model

For production Speed composition:

```text
B = native Gothic reference base for the exact route
C = configured BaseSpeed
compatibleSpeed = live result returned by the current +0x42A0 owner
configured = compatibleSpeed * (C / B)
```

`ReferenceHitBaseSpeed` remains native Gothic calibration. New Balance or other compatible relative changes belong to `compatibleSpeed`; they do not replace `B`.

## Probe responsibility

The probe must:

- be a standalone DLL named `Script_SpeedCalibrationProbe.dll`;
- install call-site hooks only at already-proven speed-consumer calls;
- call the live `Script_Game+0x42A0` owner exactly once with the original caller EAX/action;
- return that value unchanged;
- perform no production G3AB composition;
- perform no collision, Raise, animation-routing, movement, or state mutation;
- collect compact deduplicated observations instead of logging every repeated call;
- write each newly discovered unique observation immediately and write a counted summary on normal unload.

## Observation identity

A unique calibration observation is keyed by enough factual data to distinguish route changes without exploding the log:

```text
AnimationFamily
raw left-hand UseType
raw right-hand UseType
passed caller action
factual current actor action before the live call
requested phase
returned live compatible speed (quantized to 1e-6 for grouping)
New Balance loaded state
G3AnimationBehaviors loaded state
```

For readability, each observation also records:

```text
normalized left/right INI tokens when known
sample entity name
sample current movement animation
player/NPC sample counts
```

Raw UseTypes are retained because several raw types normalize to the same INI token and future calibration may reveal materially different native policy.

## Hook scope

Proven Hit callers:

```text
Normal
  Script_Game+0x383F0

Quick
  Script_Game+0x38E9D
  Script_Game+0x38F22
  Script_Game+0x3937D
  Script_Game+0x39402
  Script_Game+0x48677

Hack
  Script_Game+0x42FF4
  Script_Game+0x431B4
  Script_Game+0x432EB

Pierce
  Script_Game+0x47328
  Script_Game+0x4770F
  Script_Game+0x4786F

Power / shared Sprint-Power
  Script_Game+0x47F6C

SimpleWhirl
  Script_Game+0x4C6FA

Whirl
  Script_Game+0x4DF1F
```

Also observe the already-proven Power Raise speed caller:

```text
Script_Game+0x47D51
```

This is observation only. It does not authorize Raise behavior.

## Runtime discipline

The calibration probe must **not** coexist with `Script_G3AnimationBehaviors.dll` during calibration because both may own the same caller-site hooks. Runtime instructions must temporarily remove/disable the production DLL while the probe is active.

Two useful environments:

```text
Native calibration:
  Script_G3AnimationBehaviors.dll absent
  Script_NewBalance.dll absent
  Script_SpeedCalibrationProbe.dll present

New Balance comparison:
  Script_G3AnimationBehaviors.dll absent
  Script_NewBalance.dll present
  Script_SpeedCalibrationProbe.dll present
```

The native run establishes `B`. The New Balance run is compatibility evidence only.

## Log design

Output:

```text
SpeedCalibrationProbe.log
```

Requirements:

- bounded unique-observation table (target cap 2048);
- no per-frame spam;
- first occurrence of each unique observation flushed immediately;
- final summary sorted by observation key and including counts;
- explicit warning in the log if `Script_G3AnimationBehaviors.dll` is observed loaded while calibration calls occur.

## Protected boundaries

Do not:

```text
hook the +0x42A0 entry
change the caller action/EAX seen by the live owner
compose configured speeds
hard-code New Balance policy
infer native B from a New Balance-only run
start Raise behavior
change production source behavior
change collision behavior
```

## Acceptance

Source acceptance:

```text
builds as standalone Release tool
all hooks are proven caller sites only
live +0x42A0 called exactly once per intercepted call
returned value unchanged
unique aggregation bounded
production DLL untouched
```

Runtime acceptance:

```text
native control produces plausible known values (e.g. tested 1H Normal / Troll Power)
broad native runs remain compact
New Balance comparison records changed live values without changing behavior
no startup/runtime regression attributable to the probe
```

After calibration, promote native reference facts into current reference/release calibration material and archive this active task only when the reusable tool/design is settled.
