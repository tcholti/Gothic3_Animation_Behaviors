# Speed Expanded Attack Scope and Grouped Profile Implementation

**Status:** ACTIVE — FINALIZATION GATE: ADR-0011 RESOLVED ANIMATION-SET IDENTITY + FULL INI + RUNTIME ACCEPTANCE
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

One section represents the resolved animation set:

```text
AnimationFamily
+ LeftAnimationToken
+ RightAnimationToken
```

The left/right tokens come from the exact request-time animation returned by `Entity.GetAni(factualAction, factualPhase)`, not from raw equipped UseType normalization. Factual action still selects the attack prefix independently.

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

## Current finalization gate — EV-406 / ADR-0011

Separation identity research is closed. Production may now be finalized.

### Resolved animation-set profile identity

Implement ADR-0011 in `BehaviorProfiles` and the Speed lookup path.

Required runtime sequence:

```text
factual action + factual phase already known at caller
-> AnimationFamily from Animation.GetSkeletonName(...)
-> resolved request = Entity.GetAni(action, phase)
-> parse canonical resolved LeftAnimationToken / RightAnimationToken
-> construct profile key
-> factual action maps to Normal/Quick/Power/Pierce/Hack/SimpleWhirl/Whirl
-> compose live compatible result with C/B
```

Rename the public/internal profile identity fields from:

```text
LeftAnimationUseType
RightAnimationUseType
```

to:

```text
LeftAnimationToken
RightAnimationToken
```

before the finalized shipping INI.

Do not use raw inventory `gEUseType` to choose the Speed profile. Do not use `CurrentMovementAni()`. Do not hard-code Axe, Rapier, Zombie or any mod name.

Fail closed to the live compatible speed if `GetAni` is empty or the canonical minimum structure cannot be parsed.

### Full active shipping INI

Use `BaseSpeed=1.00` as the initial authored default. Include only calibrated attack blocks.

Required core profiles:

```text
Hero + None + 1H:
  Normal B=.60, Quick B=1.00, Power B=1.00, Pierce B=1.00

Hero + Shield + 1H:
  same

Hero + Torch + 1H:
  same

Hero + 1H + 1H:
  Normal B=.60, Quick B=1.00, Power B=.90, Pierce B=1.00, SimpleWhirl B=1.30

Hero + None + 2H:
  Normal B=.70, Quick B=1.00, Power B=1.00, Hack B=1.00, Whirl B=1.00
  native Axe/Pickaxe-style routes share this ONLY when Gothic actually resolves token 2H

Hero + None + Staff:
  Normal B=.70, Quick B=1.00, Power B=1.00, Hack B=1.00, Whirl B=1.00
  native Halberd/tool routes share this ONLY when Gothic actually resolves token Staff

Hero + None + Fist:
  Normal B=1.00, Power B=1.00
  Quick omitted by design: native human Fist has no Quick attack animation family
  a future custom human-Fist Quick set requires its own resolved-animation calibration before configuration

Sabertooth + None + Fist:
  Normal B=1.00, Quick B=1.00, Power B=1.00

Troll + Fist + Fist:
  Normal B=1.00, Quick B=1.00, Power B=1.00
```

Required tested separation-mod profiles may be shipped as active compatibility profiles because they are inert when those resolved animation sets do not exist:

```text
Hero + None + Axe:
  Normal B=.70, Quick B=1.00, Power B=1.00, Hack B=1.00, Whirl B=1.00

Hero + None + Rapier:
  Normal B=.60, Quick B=1.00, Power B=1.00, Pierce B=1.00
```

Zombie Separation should be documented with example sections rather than exhaustively pre-populated. Demonstrate:

```text
Zombie + Shield + 1H
Zombie + None + 2H
Zombie + None + Staff
Zombie + None + Axe   ; combined Zombie+Axe separation
```

The examples may use EV-406 reference values for the sampled routes, but documentation must state that profiles are selected by resolved animation family/tokens, not by mod name.

Sprint remains absent and inherits Power under ADR-0009. Finishing remains unsupported as a Speed profile. Raise remains inactive.

### Post-implementation sequence

```text
bounded source/static review
-> local Release build
-> POP-03 built/live identity
-> deploy finalized INI
-> native/shared profile control including human Fist
-> Axe Separation independent profile control
-> Rapier Separation independent profile control
-> Zombie family profile control
-> Zombie+Axe composed profile control
-> intended New Balance compatibility sanity
-> close Speed
-> Raise afterward
```

No further broad native calibration is required.

## Runtime acceptance matrix after calibration

Use representative tests rather than exhaustive repetition:

```text
Normal + Quick regression across representative Hero profiles
Power configured-speed control
Sprint inherits Power while preserving live differential
Pierce configured control
Hack configured control + Finishing remains independent
SimpleWhirl dual-1H control
Whirl 2H/Staff control
human Hero Fist Normal/Power control
native shared Axe -> resolved 2H profile control
Axe Separation -> resolved Axe profile independence
Rapier Separation -> raw 1H but resolved Rapier profile independence
Zombie Separation -> AnimationFamily=Zombie profile independence
Zombie+Axe -> Zombie + Axe composed profile
Sabertooth or Troll configured creature control
malformed/unconfigured resolved identity fail-closed
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
