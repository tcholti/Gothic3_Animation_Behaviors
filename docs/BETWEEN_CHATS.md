# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-29

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 collision production integration = CLOSED/PASS
EV-391/EV-392 original Speed Normal/Quick transport = CLOSED STATIC
EV-393/EV-394 family-source evidence = PASS
EV-395 configured Speed + New Balance stamina multiplier preservation = PASS

expanded grouped Speed source = IMPLEMENTED
production source frozen = 642c88a4e6244ae7377ba835507750af7914e2f5
internal expanded-source review = PASS
Sprint/Power blocker = CLOSED by runtime causal evidence
Sprint Speed model = inherits Power profile; no separate Sprint prefix
expanded production Release build = PASS locally; deployment deferred
Speed calibration probe build = PASS
first native calibration control = PASS
CURRENT = broad native Speed calibration
Raise = PAUSED
```

## Calibration model

```text
B = native Gothic ReferenceHitBaseSpeed
compatible = B * M
configured = compatible * (C / B) = C * M
```

New Balance values are compatibility observations, not native reference values.

The validated `Script_SpeedCalibrationProbe.dll` observes the 15 proven Hit callers plus Power Raise, returns live speeds unchanged and deduplicates repeated factual rows.

First native Hero 1H + Troll control:

```text
55 intercepted calls -> 12 unique rows -> 0 dropped
Hero None+1H Normal Hit 0.6
Hero None+1H Quick R/L Hit 1.0
Hero Power Raise 1.5 / Hit 1.0
Troll PhysicalFist Normal/Quick/Power Hit 1.0
Troll Power Raise 1.0
Troll factual Sprint Raise/Hit through passed Action2 = 1.0
```

## Critical DLL-loader rule

Renaming a DLL while leaving it inside Gothic's `scripts` folder does **not** reliably disable it; Gothic may still load it.

For any bounded fixture, excluded DLLs must be physically moved or removed completely from `scripts` before launch.

The first clean native control removed:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_NewMagicforNPCs.dll
Script_AttackCollision.dll
```

and left only the calibration probe from this project active.

## Next at local build PC

Keep the clean native fixture and perform broad practical calibration runs across:

```text
human weapon/loadout combinations intended for release profiles
supported attacks naturally available for each loadout
representative NPC users
representative nonhuman families
```

Push each resulting `SpeedCalibrationProbe.log` under a descriptive filename. Broad runs are preferred because repeated identical observations are deduplicated.

If one factual route reports multiple native speeds, preserve all values and investigate before choosing a reference.

After sufficient native coverage, restore the intended New Balance stack and perform comparable compatibility runs. Do not begin Raise or deploy the expanded production DLL until calibration closes and the common reference values are settled.
