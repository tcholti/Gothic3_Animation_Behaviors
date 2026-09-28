# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-28

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
Speed v2 caller-side mechanism/caller set = CLOSED STATIC through EV-391/EV-392
Speed deep independent static audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
production build/deploy/startup = PASS
first Speed behavior check = FAIL BEFORE COMPOSITION
first profile identity probe = CLOSED / mismatch proven before AttackSpeed
EV-393 Hero family-source control = PASS
ADR-0007 generic Speed/Raise profile contract = REVISED/ACCEPTED
CURRENT = one non-Hero family-source control only
RAISE = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`

## Preserved request-semantics rule

The successful pre-collision prototypes already established the intended architecture:

```text
Speed:
Gothic factual requested gEAction
+ Gothic factual requested gEPhase
+ stable actor/equipment facts
-> profile/behavior decision

Raise later:
matching profile
-> explicitly request factual Action + Raise through CombatMove
-> Gothic resolves concrete P0/P1/etc. animation
```

Do **not** infer the requested attack/phase from `CurrentMovementAni()`.

EV-393 observed that `CurrentMovementAni()` can still be the outgoing/current motion while the new Hit request is already factual. That is expected request-boundary behavior, not a broken observation point.

## EV-393 Hero family-source result

Refreshed standalone probe deployed with matching built/live SHA256:

`DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`

Human right-hand 1H / empty-left Normal + Quick observations consistently showed:

```text
RequestedPhaseName=Hit
AnimationResourceName=G3_Hero_Skeleton
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Hero
EntitySkeletonName=Hero
RawLeftUseType=None
RawRightUseType=1H
Normal Action=1
Quick Action=4/5
```

Therefore:

```text
requested attack/phase authority = factual Gothic Action + Phase
Animation.GetSkeletonName(...)   = preferred stable family-source candidate
Entity.GetSkeletonName()         = corroborating family source
Animation.GetResourceName()      = rejected as author-facing family source
CurrentMovementAni               = observational context only
```

One non-Hero control remains before generic production adoption.

Processed log:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

## Generic profile contract

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

Later Raise-enabled profiles may additionally use:

```ini
ReferenceRaiseBaseSpeed=1.00
RaiseOverride=On
```

Semantics:

```text
AnimationFamily         = stable actor/animation family component
ActionProfile           = mapped from factual requested gEAction
factual gEPhase         = runtime behavior gate
CurrentMovementAni      = NOT request identity
ReferenceHitBaseSpeed   = factual Hit reference B
ReferenceRaiseBaseSpeed = factual Raise reference B when later needed
BaseSpeed               = one desired authored C
Recover                 = follows effective Hit; no separate key/reference/hook
```

The later generic production refactor must remove the transitional Hero-only reference-base table from `AttackSpeed` and consume profile calibration data instead.

## Immediate route

No rebuild or source change is required for the remaining control.

```text
1. keep the currently deployed Script_SpeedIdentityProbe.dll
2. transform player into Sabretooth
3. perform several ordinary Normal attacks
4. perform several Quick attacks if that transformed route offers them
5. exit normally
6. push SpeedIdentityProbe.log to research/raw/
7. inspect whether Animation.GetSkeletonName / Entity.GetSkeletonName return one stable non-Hero family token
8. if yes: close family-source probe
9. then implement generic BehaviorProfiles + profile-calibrated AttackSpeed
10. rebuild/deploy production and resume Speed runtime acceptance
```

No Sabretooth INI profile is needed.

Primary runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
Script_SpeedIdentityProbe.dll   # diagnostic only for current bounded control
```

## Read next

- exact continuation -> `BETWEEN_CHATS.md`
- active probe -> `work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`
- schema/request-semantics decision -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- Speed architecture -> ADR-0004 + ADR-0005 + ADR-0006
- static caller proof -> EV-391 + EV-392

## Still paused

```text
NO Raise implementation while Speed is open
NO production family-source change before the final non-Hero control
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
