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
Speed deep independent audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
corrected production build/deploy/startup = PASS
first Speed behavior check = FAIL BEFORE COMPOSITION
first runtime identity probe = CLOSED / CAUSAL RESULT CAPTURED
ADR-0007 shared profile schema = REVISED/ACCEPTED 2026-09-28
interim g3_hero_skeleton -> hero production alias = SUPERSEDED AND REVERTED
production behavior source = back to pre-alias tested content
CURRENT = diagnostics-only runtime animation-family source probe
RAISE = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`

## First Speed runtime result

Production `Script_G3AnimationBehaviors.dll` built, deployed and reached main menu successfully. Built/live SHA256 matched:

`7CD8507A267384AED86E2CDEF8C29098D55221C05158DEA4117C1D96D781C959`

The first behavior test used active Hero/None/1H Normal + Quick profiles, including extreme `BaseSpeed=2.0` and `0.4`, but produced no visible speed change.

The INI path/name/content were confirmed correct.

## First identity probe result

Standalone `Script_SpeedIdentityProbe` built/deployed with SHA256:

`4CE2AE915B3B76D867DDDAD6F1AC2C1848389DAF3CBCFDEE0E3783BA2DB5CC8E`

The player 1H Normal/Quick run proved:

```text
AnimationResourceName=G3_Hero_Skeleton
RawLeftUseType=0 -> none
RawRightUseType=2 -> 1h
Normal Action=1 / Hit
Quick Action=4 or 5 / Hit
RuntimeKeyBuilt=true
Key.AnimationFamily=g3_hero_skeleton
ProfileMatch=false
```

Therefore the first Speed runtime failure occurs before `AttackSpeed` composition.

Closed probe record:

`docs/archive/investigations/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE_RESULT.md`

Processed raw log:

`research/archive/2026.09.28_SpeedIdentityProbe.log`

## Why the narrow Hero-resource correction was rejected

A direct runtime alias:

```text
g3_hero_skeleton -> hero
```

was prepared briefly, then superseded before a new production build/runtime test.

Reason: `Animation.GetResourceName()` is only one identity surface and returned a resource name, not necessarily the canonical animation family. The User identified the distinct human skeleton/armature naming, while `ANIMATION_RULES.md` already defines the first animation-name token as the animation family (`Hero`, `Demon`, `Goblin`, etc.).

The temporary production alias was reverted. Production `BehaviorProfiles.cpp` is again byte-identical to its pre-alias content.

Superseded-correction record:

`docs/archive/investigations/SPEED_RUNTIME_HERO_FAMILY_NORMALIZATION_CORRECTION_SUPERSEDED.md`

## Revised generic profile contract

ADR-0007 now freezes the intended generic data model:

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
Recover                 = follows effective Hit; NO RecoverSpeed/reference/override key
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

On the local build/game PC:

```text
1. sync development
2. rebuild Script_SpeedIdentityProbe
3. deploy/hash refreshed probe beside existing production stack
4. keep current human 1H test setup
5. run several Normal + Quick attacks
6. inspect together:
   CurrentMovementAni
   AnimationResourceName
   AnimationSkeletonName
   EntitySkeletonName
   raw left/right UseTypes
   action/phase
7. decide the factual generic AnimationFamily source
8. only then freeze/implement generic BehaviorProfiles + profile-calibrated AttackSpeed refactor
9. rebuild/deploy production and resume Speed runtime acceptance
10. close Speed completely
11. only then begin Raise
```

Primary runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

`Script_SpeedIdentityProbe.dll` may coexist only for the bounded diagnostic run.

## Read next

- exact continuation -> `BETWEEN_CHATS.md`
- active probe -> `work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`
- revised schema -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- first identity probe closure -> `archive/investigations/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE_RESULT.md`
- superseded narrow correction -> `archive/investigations/SPEED_RUNTIME_HERO_FAMILY_NORMALIZATION_CORRECTION_SUPERSEDED.md`
- Speed architecture -> ADR-0004 + ADR-0005 + ADR-0007
- static mechanism evidence -> EV-391 + EV-392 in `EVIDENCE_LEDGER_389_ONWARD.md`
- build/deploy/startup -> `PROJECT_OPERATING_PROCEDURES.md` POP-02/03/04

## Still paused

```text
NO Raise implementation while Speed is open
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
