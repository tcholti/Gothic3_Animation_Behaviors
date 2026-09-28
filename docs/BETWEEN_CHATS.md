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
EV-391/EV-392 Speed caller-side mechanism + six-site caller set = CLOSED STATIC
EV-393 Hero runtime animation-family source = PASS/RECORDED
Speed deep independent audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
production build/deploy/startup = PASS
first Speed behavior check = FAIL before composition
ADR-0007 profile schema/request semantics = REVISED/ACCEPTED
production behavior source = pre-alias tested content
CURRENT = one non-Hero family-source runtime control
RAISE = PAUSED until Speed closes
```

## Preserved rule

Do not classify the requested attack from `CurrentMovementAni()`.

```text
requested gEAction + requested gEPhase = Gothic request authority
AnimationFamily + left/right UseTypes  = stable actor/equipment profile facts
CurrentMovementAni                     = observational context only
```

This preserves the successful pre-collision architecture: old Speed used factual Action/Phase directly; old Raise explicitly requested Action + Raise through CombatMove and let Gothic resolve the concrete P0/P1/etc. animation.

EV-393 showed that the current motion may still be an outgoing motion while a new Hit is already being requested. That is expected at the request boundary.

## EV-393 Hero result

Refreshed probe SHA256:

`DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`

Human Normal + Quick consistently produced:

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

Preferred family-source candidate:

`Animation.GetSkeletonName(...)`

One non-Hero control remains before production adoption.

Processed evidence:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

Active task:

`docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`

## Profile contract

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

Later Raise-enabled profile may additionally use `ReferenceRaiseBaseSpeed` + `RaiseOverride=On`. Recover remains derived from effective Hit with no independent key/reference/hook.

## Next

No rebuild is needed.

```text
sync development
-> keep current Script_SpeedIdentityProbe.dll deployed
-> transform player into Sabretooth
-> perform several Normal attacks
-> perform several Quick attacks if available
-> exit normally
-> push SpeedIdentityProbe.log to research/raw/
```

No Sabretooth INI profile is required.

Acceptance:

```text
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=<stable non-Hero family token>
EntitySkeletonName=<same stable family token>
```

If that passes:

```text
close family-source probe
-> adopt Animation.GetSkeletonName(...) for AnimationFamily
-> implement generic profile calibration fields
-> remove Hero-only reference-base table from AttackSpeed
-> rebuild/deploy production
-> resume Speed runtime acceptance
```
