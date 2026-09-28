# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-28

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
Speed v2 mechanism proof = EV-391
Quick/caller-set static closure = EV-392
Hero runtime animation-family source = EV-393 PASS
Speed deep independent audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
corrected production build/deploy/startup = PASS
first Speed behavior check = FAIL BEFORE COMPOSITION
ADR-0007 shared profile schema = REVISED/ACCEPTED 2026-09-28
interim g3_hero_skeleton -> hero production alias = SUPERSEDED/REVERTED
production behavior source = pre-alias tested content
CURRENT = one bounded non-Hero family-source runtime control
RAISE = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`

## Speed runtime causal state

The first production Speed behavior test showed no visible change with active Hero/None/1H Normal + Quick profiles, even at extreme `BaseSpeed=2.0` and `0.4`. The INI path/name/content were confirmed correct.

The first identity probe then proved the failure occurs before `AttackSpeed` composition because production `BehaviorProfiles` derives family from:

```text
Animation.GetResourceName() = G3_Hero_Skeleton
-> normalized key = g3_hero_skeleton
```

while ADR-0007 uses the author-facing family token `Hero`.

A temporary exact alias was deliberately reverted before another production build so the project could establish the correct generic family source rather than encode a one-off Hero fix.

## EV-393 — Hero family-source result

The refreshed standalone `Script_SpeedIdentityProbe.dll` built/deployed with matching SHA256:

`DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`

The human right-hand 1H / empty-left Normal + Quick run established consistently:

```text
AnimationResourceName=G3_Hero_Skeleton
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Hero
EntitySkeletonName=Hero
RawLeftUseType=None
RawRightUseType=1H
Normal Action1 / Hit
Quick Action4/5 / Hit
```

`NPC.GetCurrentMovementAni()` is not suitable as the production family source at this observation point. It could still report prior/current motions such as HoldRight_End, Attack_Recover, Ambient_Loop or Parade_Begin while the new CombatMove request was already Normal/Quick Hit.

Therefore:

```text
CurrentMovementAni filename parsing = rejected at this hook
Animation.GetResourceName()          = rejected as user-facing family source
Animation.GetSkeletonName(...)       = preferred generic candidate
Entity.GetSkeletonName()             = corroborating candidate
```

`Animation.GetSkeletonName(...)` is preferred because it is owned by the animation property set, returns the exact schema token `Hero`, and exposes explicit success/failure for fail-closed runtime-key construction.

EV-393 remains deliberately Hero-scoped. One non-Hero runtime control is required before generic production adoption.

Processed log:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

## Revised generic profile contract

ADR-0007 now freezes:

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

For a later G3AB-inserted Raise:

```ini
ReferenceRaiseBaseSpeed=1.00
RaiseOverride=On
```

Semantics:

```text
ReferenceHitBaseSpeed   = factual Hit reference B
ReferenceRaiseBaseSpeed = factual Raise reference B when later needed
BaseSpeed               = single desired authored base C
RaiseOverride=Off       = no G3AB Raise intervention
RaiseOverride=On        = later request G3AB Raise handling
Recover                 = follows effective Hit; NO independent INI key/reference/hook
```

The later generic production refactor must remove the transitional Hero-only reference-base policy table from `AttackSpeed` and consume factual reference calibration from profile data instead.

## Frozen Speed transport remains unchanged

```text
six caller hooks:
+0x383F0
+0x38E9D
+0x38F22
+0x3937D
+0x39402
+0x48677

caller -> factual EAX action
-> invoke LIVE Script_Game+0x42A0 once
-> compatible B*M
-> generic configured C/B composition
-> finite C*M
```

Hard exclusions remain:

```text
NO hook/ownership of +0x42A0 entry
NO +0x38A8B StateTime-as-action site
NO copied New Balance multiplier policy
NO global playback-speed override
NO final-result replacement
```

## Immediate route

No probe rebuild is required. First sync `development` because repository evidence/maintenance moved after the last user push.

Then on the local game PC:

```text
1. keep the currently deployed Script_SpeedIdentityProbe.dll
2. transform player into Sabretooth
3. perform several ordinary Normal attacks
4. perform several Quick attacks if available on that transformed route
5. exit normally
6. push the resulting SpeedIdentityProbe.log to research/raw/
```

No Sabretooth INI profile is required.

Acceptance is only:

```text
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=<stable non-Hero family token>
EntitySkeletonName=<same stable family token>
```

If that passes:

```text
close family-source probe
-> freeze Animation.GetSkeletonName(...) as generic AnimationFamily source
-> implement generic BehaviorProfiles calibration fields
-> remove Hero-only reference-base table from AttackSpeed
-> rebuild/deploy production
-> resume New Balance Speed runtime acceptance
-> close Speed
-> only then begin Raise
```

Primary runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
Script_SpeedIdentityProbe.dll   ; diagnostics only for current bounded probe
```

## Read next

- exact continuation -> `BETWEEN_CHATS.md`
- active probe -> `work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`
- revised schema -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- EV-393 -> `EVIDENCE_LEDGER_389_ONWARD.md`
- first identity probe closure -> `archive/investigations/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE_RESULT.md`
- superseded narrow correction -> `archive/investigations/SPEED_RUNTIME_HERO_FAMILY_NORMALIZATION_CORRECTION_SUPERSEDED.md`
- Speed architecture -> ADR-0004 + ADR-0005 + ADR-0007
- build/deploy/startup -> `PROJECT_OPERATING_PROCEDURES.md` POP-02/03/04

## Still paused

```text
NO Raise implementation while Speed is open
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
