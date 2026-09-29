# Speed Native/Compatible Calibration Probe

**Status:** ACTIVE — PROBE BUILD/RUNTIME VALIDATED; BROAD CALIBRATION ACTIVE  
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
factual current actor action after the live call
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

Gothic's script loader may still load renamed DLLs that remain inside the game `scripts` folder. Therefore **renaming a DLL in place is not a valid disable method** for calibration.

Any DLL that must be excluded from a test must be physically removed or moved completely outside the `scripts` folder before Gothic starts.

The calibration probe must not coexist with `Script_G3AnimationBehaviors.dll` because both may own the same caller-site hooks.

Two useful environments:

```text
Native calibration:
  Script_G3AnimationBehaviors.dll physically outside scripts
  Script_NewBalance.dll physically outside scripts
  other optional combat/gameplay script mods that could affect the measurement removed for the clean fixture
  Script_SpeedCalibrationProbe.dll present

New Balance comparison:
  Script_G3AnimationBehaviors.dll physically outside scripts
  intended New Balance stack restored
  Script_SpeedCalibrationProbe.dll present
```

For the first clean native control the User removed:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_NewMagicforNPCs.dll
Script_AttackCollision.dll
```

The native run establishes `B`. The New Balance run is compatibility evidence only.

## Log design

Output:

```text
SpeedCalibrationProbe.log
```

Requirements:

- bounded unique-observation table (cap 2048);
- no per-frame spam;
- first occurrence of each unique observation flushed immediately;
- final summary sorted by observation key and including counts;
- explicit loaded-state fields for New Balance and production G3AB.

The loaded-state fields are supporting diagnostics, not a substitute for the physical-removal rule above.

## First runtime validation — PASS

Built Release probe SHA256:

```text
4140867626119632929D2286A173E97B3A4ACE6EDBCA4E2DBFE30AC28FE28E82
```

Native-only control log:

```text
research/raw/2026.09.29_speed calibration_1h_troll.log
```

The run intercepted 55 calls but reduced them to 12 unique observations with zero dropped rows.

Known controls matched exactly:

```text
Hero / None+1H / Normal Hit       0.600000
Hero / None+1H / QuickR Hit       1.000000
Hero / None+1H / QuickL Hit       1.000000
Hero / None+1H / Power Raise      1.500000
Hero / None+1H / Power Hit        1.000000

Troll / PhysicalFist+PhysicalFist / Normal Hit       1.000000
Troll / PhysicalFist+PhysicalFist / QuickR Hit       1.000000
Troll / PhysicalFist+PhysicalFist / QuickL Hit       1.000000
Troll / PhysicalFist+PhysicalFist / Power Raise      1.000000
Troll / PhysicalFist+PhysicalFist / Power Hit        1.000000
Troll / PhysicalFist+PhysicalFist / Sprint Raise via passed Power  1.000000
Troll / PhysicalFist+PhysicalFist / Sprint Hit via passed Power    1.000000
```

The Sprint rows retained factual Action9 before and after the shared Power calls while the caller passed Action2, independently reconfirming the shared Power/Sprint transport.

The Power Raise observation also shows factual Troll Sprint reaching the shared Power Raise speed caller with native `1.0`; preserve this as evidence for later Raise research without beginning Raise implementation now.

Disposition:

```text
probe build = PASS
small native runtime control = PASS
aggregation compactness = PASS on first control
known base values = PASS
NEXT = broad native calibration sampling
```

## Broad native calibration gate

Use several practical runs rather than trying to exercise everything in one session. Prioritize:

```text
human weapon/loadout combinations intended for the shipped INI
all supported attack types that are naturally available for each loadout
representative NPC users of the same loadouts
representative nonhuman families
```

Repeated calls are cheap because the final report deduplicates by factual route/speed. If one nominal route produces more than one speed under the clean native fixture, preserve all rows rather than assuming one is the base; investigate the contextual difference before promoting a reference value.

After native calibration is sufficiently broad, run a comparable New Balance environment to confirm compatible changes remain observable. New Balance values remain compatibility observations, never native `ReferenceHitBaseSpeed` values.

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
small native known-value control PASS
broad native runs remain compact
common release-profile native values are established with sufficient coverage
New Balance comparison records changed live values without changing behavior
no startup/runtime regression attributable to the probe
```

After calibration, promote native reference facts into current reference/release calibration material and archive this active task only when the reusable tool/design is settled.