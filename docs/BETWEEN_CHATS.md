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
EV-393 Hero runtime animation-family source = PASS/RECORDED
Speed deep independent audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
production build/deploy/startup = PASS
first Speed behavior check = FAIL before composition
ADR-0007 profile schema = REVISED/ACCEPTED
interim g3_hero_skeleton -> hero production alias = SUPERSEDED/REVERTED
production behavior source = pre-alias tested content
CURRENT = one non-Hero family-source runtime control
RAISE = PAUSED until Speed closes
```

## EV-393 human result

Refreshed `Script_SpeedIdentityProbe.dll` built/deployed with matching SHA256:

`DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`

Human right-hand 1H / empty-left Normal + Quick observations established:

```text
AnimationResourceName=G3_Hero_Skeleton
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Hero
EntitySkeletonName=Hero
raw left=None
raw right=1H
Normal Action1 / Hit
Quick Action4/5 / Hit
```

`CurrentMovementAni()` was stale relative to the requested Hit and could still report HoldRight_End, Attack_Recover, Ambient_Loop or Parade_Begin. Therefore current-motion filename parsing is rejected as the Speed family source at this hook.

`Animation.GetSkeletonName(...)` is the preferred family source because it returns the exact ADR-0007 token `Hero`, belongs to the animation property set and exposes explicit success/failure for fail-closed handling. `Entity.GetSkeletonName()` independently corroborates `Hero`.

Processed evidence:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

Active task:

`docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`

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

## Next

No rebuild is needed. The current deployed probe is sufficient.

```text
sync development first
-> transform player into Sabretooth
-> perform several Normal attacks
-> perform several Quick attacks if available
-> exit normally
-> push the new SpeedIdentityProbe.log to research/raw/
```

No Sabretooth INI profile is required. The only acceptance facts are:

```text
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=<stable non-Hero family token>
EntitySkeletonName=<same stable family token>
```

If that passes:

```text
close family-source probe
-> use Animation.GetSkeletonName(...) for runtime AnimationFamily
-> implement generic profile calibration fields
-> remove Hero-only reference-base table from AttackSpeed
-> rebuild/deploy production
-> resume Speed runtime acceptance
```

Primary runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
Script_SpeedIdentityProbe.dll   ; diagnostics only for current bounded probe
```
