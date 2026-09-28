# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-28

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 collision production integration = CLOSED/PASS
EV-391 Speed caller-side mechanism = RECORDED
EV-392 Quick provenance + exact six-site caller set = PASS/RECORDED
Speed deep independent audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
production build/deploy/startup = PASS
first Speed behavior check = FAIL before composition
first Speed identity probe = CLOSED / causal result captured
factual tested resource = G3_Hero_Skeleton
profile mismatch = confirmed before AttackSpeed composition
ADR-0007 profile schema = REVISED/ACCEPTED
interim g3_hero_skeleton -> hero production alias = SUPERSEDED/REVERTED
CURRENT = diagnostics-only animation-family source probe
RAISE = PAUSED until Speed closes
```

The first probe proved:

```text
AnimationResourceName=G3_Hero_Skeleton
left=none
right=1h
Normal Action=1 Hit
Quick Action=4/5 Hit
runtime family=g3_hero_skeleton
ProfileMatch=false
```

Do not treat that resource string as the canonical family yet. Canonical animation naming defines the first animation-name token as family (`Hero`, `Demon`, `Goblin`, etc.), and SDK/runtime exposes multiple identity surfaces.

The narrow resource alias was reverted before a new production build. Production behavior source is back to the pre-alias tested content.

## Revised profile contract

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.60
BaseSpeed=0.80
RaiseOverride=Off
```

Later Raise-enabled profile may additionally use:

```ini
ReferenceRaiseBaseSpeed=1.00
RaiseOverride=On
```

Meaning:

```text
ReferenceHitBaseSpeed   = factual Hit B
ReferenceRaiseBaseSpeed = factual Raise B when later needed
BaseSpeed               = one desired authored C
RaiseOverride           = G3AB Raise ownership On/Off
Recover                 = derived from effective Hit; no separate key/reference/hook
```

The eventual generic production refactor must remove the transitional Hero-only reference-base policy table from C++ and use profile calibration data instead.

## Active probe

`docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`

The refreshed standalone probe now logs together:

```text
CurrentMovementAni
AnimationResourceName
AnimationSkeletonName
EntitySkeletonName
action / requested phase
raw left/right UseTypes
existing production key/match result
```

## Next

On the local build/game PC:

```text
sync development
-> rebuild Script_SpeedIdentityProbe
-> deploy/hash refreshed probe
-> run several human 1H Normal + Quick attacks
-> inspect family-source facts
-> choose factual generic AnimationFamily extraction
-> then implement generic profile calibration + Speed refactor
-> rebuild/deploy production
-> resume New Balance Speed acceptance
```

Primary runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

`Script_SpeedIdentityProbe.dll` may coexist only for this bounded diagnostic run.
