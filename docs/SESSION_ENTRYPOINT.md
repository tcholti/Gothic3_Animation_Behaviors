# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-29

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
initial Speed v2 Normal/Quick runtime proof = PASS through EV-395
expanded Speed product scope = Normal, Quick, Power, Pierce, Hack, SimpleWhirl, Whirl
expanded grouped-profile source implementation = STATIC REVIEW PASS
production source under next build gate = 642c88a4e6244ae7377ba835507750af7914e2f5
CURRENT = LOCAL BUILD / DEPLOY of expanded Speed source
Sprint / Action9 Speed = NOT IMPLEMENTED; factual transport remains unproven
Raise behavior = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`

## Frozen grouped profile rule

One profile section represents one animation-family/loadout identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Attack settings live inside that loadout:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Example shape:

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
```

Section suffix is label-only; runtime identity comes from the explicit fields.

## Frozen composition rule

```text
requested factual gEAction + gEPhase = Gothic request authority
Animation.GetSkeletonName(...)         = runtime AnimationFamily
left/right UseTypes                     = normalized loadout facts
CurrentMovementAni                      = observational context only

compatible = B * M
configured = compatible * (BaseSpeed / ReferenceHitBaseSpeed)
           = C * M
```

No New Balance multiplier policy is copied into G3AB.

## Expanded static PASS

Current implementation statically passes the bounded acceptance contract:

```text
grouped loadout parser                         PASS
seven independent attack settings             PASS
Action1/2/4/5/6/10/11/14 mapping             PASS
Action3 generic Quick remains non-playback     PASS
Action9/Sprint remains fail-closed             PASS
missing/invalid calibration fallback           PASS
finite composed-output guard                   PASS
original six Normal/Quick caller hooks         unchanged
nine proven new Hit caller hooks               added
Power Raise +0x47D51                           not hooked
live +0x42A0 compatible-owner call             preserved exactly once
collision / Raise behavior                     no bounded drift found
shipped INI                                    grouped/commented
```

Production implementation lineage:

```text
61e805ea9eaf0cbb2e0765fe65df97252c46a554
8c8ebe37ccd66a9e8317ded611418b6b0f1f881d
1ed68e8ae8867c6f7f8be63050aad9a185188e48
ad3e5e01fc581dc36dc4d0b6e33a0e46d2a19156
642c88a4e6244ae7377ba835507750af7914e2f5
```

## Immediate route

When the User is back at the local build PC:

```text
sync development
-> build Script_G3AnimationBehaviors Release
-> deploy sole production DLL as usual
-> verify built/live SHA match
-> startup smoke
-> then run the small expanded-Speed runtime matrix
```

Runtime matrix after successful build/deploy:

```text
Normal + Quick regression control
Power configured-speed control
Pierce / Hack configured controls where visually practical
SimpleWhirl / Whirl configured controls where visually practical
unconfigured/fail-closed fallback
New Balance compatibility sanity
```

Sprint remains outside this runtime acceptance until a separate factual Speed transport route is proven.

## Still paused

```text
NO Raise implementation while expanded Speed is open
NO speculative Sprint hook
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
