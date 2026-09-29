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

expanded Speed scope = Normal, Quick, Power, Pierce, Hack, SimpleWhirl, Whirl
grouped loadout INI/profile architecture = IMPLEMENTED
expanded attack mapping = IMPLEMENTED
nine additional proven Hit caller hooks = IMPLEMENTED
expanded source static review = PASS
production source frozen for build = 642c88a4e6244ae7377ba835507750af7914e2f5

Sprint / Action9 Speed = deliberately unsupported until factual transport is proven
Raise behavior = PAUSED until Speed closes
CURRENT = local build/deploy gate
```

## Grouped profile shape

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

Supported attack prefixes:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

No separate Raise speed setting. When Raise work begins, first test whether the inserted Raise naturally follows the attack's BaseSpeed; add extra code/config only if runtime evidence requires it.

## Composition

```text
compatible = B * M
configured = (B * M) * (C / B) = C * M
```

The live compatible owner, including New Balance, is still invoked first. G3AB does not copy multiplier policy.

## Next

Active task:

`docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`

When back at the build PC:

```text
sync development
-> build Script_G3AnimationBehaviors Release
-> deploy as usual
-> verify built/live SHA equality
-> startup smoke
-> run small runtime matrix:
   Normal/Quick regression
   Power
   Pierce/Hack where visually practical
   SimpleWhirl/Whirl where visually practical
   unconfigured fallback
   New Balance compatibility sanity
```

Do not add Sprint or begin Raise before this expanded Speed runtime gate closes.
