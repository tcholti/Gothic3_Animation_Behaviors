# Speed Expanded Attack Scope and Grouped Profile Implementation

**Status:** ACTIVE — FINALIZATION GATE: ADR-0010 RAW-USETYPE IDENTITY + FULL INI + RUNTIME ACCEPTANCE
**Task class:** Bounded production source extension + runtime acceptance  
**Branch:** `development`

## Purpose

Extend the runtime-proven Speed v2 mechanism from Normal/Quick to additional factual Hit-speed routes while using grouped loadout profiles.

The compatible-composition architecture remains frozen:

```text
compatible = B * M
configured = compatible * (C / B) = C * M
```

Production source under acceptance remains:

```text
642c88a4e6244ae7377ba835507750af7914e2f5
```

## Calibration semantics

For this downstream caller-side mechanism:

```text
B = native Gothic Hit base for the exact route
C = configured authored BaseSpeed
compatible = live result from the current +0x42A0 owner
```

`ReferenceHitBaseSpeed` is therefore a native Gothic calibration fact, not a New Balance value and not a gameplay tuning value. Compatible relative changes already present in the live result are preserved by the `C/B` composition.

A native-only Troll control on the shared Power/Sprint route proved `B=1.0`; the previously observed New Balance result was `1.5`. This directly demonstrates why the reference must remain native while the third-party increase stays in the live compatible result.

Before expanded production deployment, the User chose to establish a broader native calibration catalogue using the reusable diagnostics-only task:

`docs/work/active/SPEED_NATIVE_CALIBRATION_PROBE.md`

This is a calibration/configuration sub-gate, not a production mechanism redesign.

## Grouped profile schema

One section represents:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Each supported attack owns independent optional settings:

```text
<Attack>_ReferenceHitBaseSpeed
<Attack>_BaseSpeed
<Attack>_RaiseOverride
```

User-facing Speed attack prefixes:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Sprint has no separate prefix. ADR-0009 establishes that factual Sprint/Action9 inherits the Power timing profile on its proven shared Hit-speed route.

## Factual action mapping

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

Generic Quick Action3 remains a selector and is not treated as factual playback Quick.

Sprint remains factual Action9 in actor state but the proven Hit-speed caller supplies Action2; no Action9 mapping is required in `AttackSpeed`.

## Caller-side transport

Existing Normal/Quick six-site set remains unchanged.

New Hit consumers:

```text
Power / shared Sprint-Power:
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

Power Raise at `Script_Game+0x47D51` remains evidence/observation only and is not hooked by production Speed.

## Static review result

```text
grouped identity family+left+right                 PASS
seven independent attack settings                  PASS
Action1/2/4/5/6/10/11/14 mapping                  PASS
Action3 non-playback selector                       PASS
missing/invalid calibration fallback                PASS
finite composed-output guard                        PASS
original Normal/Quick hooks unchanged               PASS
nine intended new Hit call sites added              PASS
Power Raise +0x47D51 not hooked by production       PASS
common live +0x42A0 call exactly once               PASS
no bounded collision/Raise drift                    PASS
shipped INI grouped/commented                       PASS
```

The independent review found one material Sprint/Power question at `+0x47F6C`. That question is runtime-resolved rather than suppressed.

## Sprint causal closure

The diagnostics-only `Script_SpeedSprintProbe` proved on Goblin, Troll and Sabertooth that actual Sprint reaches `Script_Game+0x47F6C` with:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
CurrentActionAfter=9
PowerAttack-named motion
```

The New Balance test environment showed matching live compatible results between ordinary Power and Sprint within each tested family. Native-only Troll later established the shared native Power/Sprint Hit base as `1.0` while New Balance returned `1.5` on that route.

Therefore configured Power timing intentionally governs Sprint on this shared route. Do not add Sprint-specific INI keys or Action9 policy mapping absent contradictory evidence.

Authority:

`docs/decisions/ADR-0009-sprint-inherits-power-speed-profile.md`

Probe result:

`docs/archive/investigations/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE_RESULT.md`

## Build state

Expanded `Script_G3AnimationBehaviors.dll` Release build completed successfully on the local build PC after the Sprint blocker closed. Deployment was deliberately deferred when the native-reference calibration requirement was clarified.

No production source correction is currently indicated.

## Current finalization gate — EV-404 / EV-405 / ADR-0010

Broad native catalogue calibration is no longer required before Speed closure. EV-397–EV-404 establish enough native references for the initial human-weapon profiles and selected creatures.

### Raw UseType profile identity

Implement ADR-0010 in `BehaviorProfiles`. Profile matching must use canonical raw `gEUseType` tokens, not serialized animation aliases.

Minimum required distinct tokens:

```text
None, 1H, 2H, Axe, Staff, Halberd,
Fist, PhysicalFist, Pickaxe, Broom, Rake, Shovel, Fan
```

Other already-supported raw UseTypes should likewise retain stable distinct raw tokens.

Prefer renaming `TryGetAnimationUseTypeToken` to profile/raw-UseType terminology so future contributors do not confuse profile identity with `ANIMATION_RULES.md` filename normalization.

Do not inspect `CurrentMovementAni()`, add weapon-specific `AttackSpeed` branches, add automatic filename-based profile inheritance, or change collision behavior.

### Full active shipping INI

Use `BaseSpeed=1.00` as the initial authored default. Include only calibrated attack blocks.

```text
Hero + None + 1H:
  Normal .60, Quick 1.00, Power 1.00, Pierce 1.00

Hero + Shield + 1H:
  same

Hero + Torch + 1H:
  same

Hero + 1H + 1H:
  Normal .60, Quick 1.00, Power .90, Pierce 1.00, SimpleWhirl 1.30

Hero + None + 2H:
  Normal .70, Quick 1.00, Power 1.00, Hack 1.00, Whirl 1.00

Hero + None + Axe:
  same initial values as 2H, DISTINCT raw profile

Hero + None + Staff:
  Normal .70, Quick 1.00, Power 1.00, Hack 1.00, Whirl 1.00

Hero + None + Halberd:
  same initial values as Staff, DISTINCT raw profile

Sabertooth + None + Fist:
  Normal 1.00, Quick 1.00, Power 1.00

Troll + PhysicalFist + PhysicalFist:
  Normal 1.00, Quick 1.00, Power 1.00
```

Sprint remains absent and inherits Power under ADR-0009.

Do not add Finishing keys, Sprint keys, uncalibrated work-tool profiles, or active Raise behavior. Human bare Fist remains a separate calibration choice if desired.

### Post-implementation sequence

```text
bounded source/static review
-> local Release build
-> POP-03 built/live identity
-> intended compatible stack + full INI
-> Axe Separation positive control + expanded Speed runtime acceptance
-> close Speed
-> Raise afterward
```

EV-395 already proves New Balance multiplier preservation for the mechanism; no broad New Balance calibration-probe campaign is required.

## Runtime acceptance matrix after calibration

Use representative tests rather than exhaustive repetition:

```text
Normal + Quick regression control across representative human profiles
Power configured-speed control
Sprint control demonstrating inherited Power authoring while preserving a live differential
Pierce configured control
Hack configured control + Finishing remains independent
SimpleWhirl configured dual-1H control
Whirl configured 2H/Staff control
Axe and 2H raw-profile independence using Axe Separation
Halberd and Staff raw-profile independence sanity where practical
unconfigured Pickaxe/tool raw profile remains fail-closed
Sabertooth or Troll configured creature control
unconfigured/fail-closed fallback
New Balance intended-stack compatibility sanity
```

## Protected boundaries

Do not:

```text
hook Script_Game+0x42A0 entry
rewrite the live compatible owner's EAX input
copy New Balance multiplier policy
hard-replace final compatible speed
use New Balance results as native ReferenceHitBaseSpeed values
add Sprint-specific speed keys without contradictory evidence
begin Raise behavior before Speed acceptance closes
change collision behavior
promote to main
```

Raise remains paused until expanded Speed closes.
