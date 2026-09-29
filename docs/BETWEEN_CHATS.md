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
internal expanded-source static review = PASS
production source frozen for review/build = 642c88a4e6244ae7377ba835507750af7914e2f5

CURRENT = light independent read-only review + focused Sprint/Action9 research
NEXT if accepted = local build/deploy gate
Sprint / Action9 Speed = unsupported until factual transport is proven
Raise behavior = PAUSED until Speed closes
```

## Current review task

`docs/work/active/SPEED_EXPANDED_SCOPE_LIGHT_INDEPENDENT_REVIEW_AND_SPRINT_RESEARCH.md`

The review is intentionally lighter than the prior deep Speed audit. It must independently verify the grouped-profile implementation, factual action mapping, old and newly added caller hooks, fail-closed behavior, common compatible-owner composition, and absence of Raise/collision drift.

It must separately research Sprint / Action9 and classify it as one of:

```text
PROVEN SAFE ROUTE
PLAUSIBLE BUT UNPROVEN
NO DISTINCT ROUTE FOUND / REMAINS UNPROVEN
```

No implementation is allowed in the review task.

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

Supported attack prefixes currently implemented:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

No separate Raise speed setting. When Raise work begins, first test whether inserted Raise naturally follows the attack's BaseSpeed; add extra code/config only if runtime evidence requires it.

## Composition

```text
compatible = B * M
configured = (B * M) * (C / B) = C * M
```

The live compatible owner, including New Balance, is still invoked first. G3AB does not copy multiplier policy.

## After independent review

If no blocking source defect is found:

```text
sync development at build PC
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

Sprint is added only if the review proves a safe factual route and the normal engineering chat accepts the result. Do not begin Raise before expanded Speed closes.
