# Speed Expanded Attack Scope and Grouped Profile Implementation

**Status:** SOURCE IMPLEMENTED / INTERNAL STATIC PASS / INDEPENDENT REVIEW BLOCKED ON SPRINT ISOLATION / BUILD PENDING  
**Task class:** Bounded production source extension + static/runtime acceptance  
**Branch:** `development`

## Purpose

Extend the runtime-proven Speed v2 mechanism from Normal/Quick to additional factual Hit-speed routes while replacing the one-section-per-attack INI layout with grouped loadout profiles.

The compatible-composition architecture remains frozen:

```text
compatible = B * M
configured = compatible * (C / B) = C * M
```

Production source under acceptance remains:

```text
642c88a4e6244ae7377ba835507750af7914e2f5
```

## Grouped profile schema

One section represents:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Each supported attack owns independent optional settings inside that loadout:

```text
<Attack>_ReferenceHitBaseSpeed
<Attack>_BaseSpeed
<Attack>_RaiseOverride
```

Supported Speed attack types in this source:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Sprint remains intentionally absent from the public profile schema until its transport is proven.

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

Generic Quick Action3 is not treated as factual playback Quick.

## Caller-side transport

Existing Normal/Quick six-site set remains unchanged.

Newly added Hit consumers:

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

Power Raise at `Script_Game+0x47D51` remains evidence only and is not hooked.

## Internal static result

The implementation passed the original bounded internal static checklist:

```text
grouped identity family+left+right                 PASS
seven independent attack settings                  PASS
Action1/2/4/5/6/10/11/14 mapping                  PASS
Action3 non-playback selector                       PASS
missing/invalid calibration fallback                PASS
finite composed-output guard                        PASS
original Normal/Quick hooks unchanged               PASS
nine intended new Hit call sites added              PASS
Power Raise +0x47D51 not hooked                     PASS
common live +0x42A0 call exactly once               PASS
no bounded collision/Raise drift                    PASS
shipped INI grouped/commented                       PASS
```

## Independent review blocker

The later independent read-only review found one material non-interference question at the new Power Hit caller `Script_Game+0x47F6C`.

Pinned Script_Game evidence:

```text
+0x47CE2  reads current PropertyAction
+0x47CE8  compares with Action9 / Sprint
+0x47CEB  Action9 remains on the shared continuation at +0x47D02

+0x47F67  mov eax,2
+0x47F6C  call +0x42A0
```

Native `+0x42A0` separately reads current PropertyAction and contains an Action9 branch at `+0x431D..+0x4329`.

Therefore the shared routine may reach the hooked Hit caller with:

```text
passed action = Power / 2
factual current actor action = Sprint / 9
```

The current expanded G3AB thunk receives passed EAX=2 and therefore maps it to configured Power. If current Action9 is still present at the Hit call, configured Power could compose Sprint and violate the intended unsupported-Sprint fallback.

The independent review classified Sprint transport as:

```text
PLAUSIBLE BUT UNPROVEN
```

This is a pre-build blocker, not a proven runtime regression and not a rejection of the broader Speed design.

Archived independent review result:

`docs/archive/investigations/SPEED_EXPANDED_SCOPE_LIGHT_INDEPENDENT_REVIEW_AND_SPRINT_RESEARCH_RESULT.md`

## Current gate

Resolve only the Sprint-vs-Power discrimination question through:

`docs/work/active/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE.md`

A standalone diagnostics-only tool observes `Script_Game+0x47F6C` and returns the live compatible speed unchanged.

Do **not** build/deploy the expanded production source until that probe resolves whether factual Sprint reaches `+0x47F6C` with current Action9.

## Decision after probe

If actual Sprint produces:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
```

then implement only the smallest Sprint non-interference correction before production build. Preserve the original caller EAX when invoking the live compatible owner; do not rewrite New Balance/native policy speculatively.

If factual Sprint does not reach this caller with current Action9, the independent blocker is not reproduced and the expanded source can proceed to build/runtime acceptance.

## Protected boundaries

Do not:

```text
hook Script_Game+0x42A0 entry
copy New Balance multiplier policy
hard-replace final compatible speed
begin Raise behavior
change collision behavior
promote to main
add Sprint authoring support without factual transport proof
```

Raise remains paused until expanded Speed closes.
