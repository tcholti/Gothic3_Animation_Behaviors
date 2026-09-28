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
ADR-0007 shared Speed/Raise INI schema = ACCEPTED
BehaviorProfiles foundation = IMPLEMENTED / SOURCE-REVIEW PASS
Speed v2 mechanism proof = EV-391
Speed v2 Quick/caller-set static closure = EV-392
Speed v2 deep independent static audit = PASS WITH NON-BLOCKING FINDINGS
Speed v2 S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
first corrected-Speed build/deploy/startup = PASS
first Speed behavior check = FAIL BEFORE COMPOSITION
Speed runtime identity probe = CLOSED / CAUSAL RESULT CAPTURED
factual player animation resource = G3_Hero_Skeleton
runtime profile-family mismatch = CONFIRMED
current bounded correction = exact g3_hero_skeleton -> hero normalization in BehaviorProfiles
current correction source lineage = 28182c8898a29b5fa61b6b5c3a044b882550d54f

CURRENT = rebuild/redeploy SpeedIdentityProbe and require exact profile match before rebuilding production DLL
RAISE = PAUSED until Speed is completely closed
main = FROZEN
```

Active task:

`docs/work/active/SPEED_RUNTIME_HERO_FAMILY_NORMALIZATION_CORRECTION.md`

## First Speed runtime result

The production target built and deployed successfully from the corrected S-01 lineage. Built/live SHA256 matched:

`7CD8507A267384AED86E2CDEF8C29098D55221C05158DEA4117C1D96D781C959`

Gothic 3 reached the main menu and exited normally.

The first behavior check used active Hero/None/1H Normal and Quick profiles, including deliberately extreme `BaseSpeed=2.0` and `0.4`, but no visible speed change occurred.

INI path/name/content were then verified correct at:

`<Gothic3>\Ini\G3AnimationBehaviors.ini`

## Runtime identity probe closure

The bounded standalone `Script_SpeedIdentityProbe` compiled and deployed with built/live SHA256:

`4CE2AE915B3B76D867DDDAD6F1AC2C1848389DAF3CBCFDEE0E3783BA2DB5CC8E`

It reuses the exact production `BehaviorProfiles` implementation and does not modify speed.

The player 1H Normal/Quick run established:

```text
AnimationResourceName=G3_Hero_Skeleton
RawLeftUseType=0
RawRightUseType=2
RuntimeKeyBuilt=true
Key.AnimationFamily=g3_hero_skeleton
Key.LeftAnimationUseType=none
Key.RightAnimationUseType=1h
Normal Action=1 / Hit
Quick Action=4 or 5 / Hit
ProfileMatch=false
```

Therefore the first runtime failure occurs before `AttackSpeed` composition: ADR-0007 config `AnimationFamily=Hero` normalizes to `hero`, while factual runtime extraction previously normalized the raw resource literally to `g3_hero_skeleton`.

Closed probe result:

`docs/archive/investigations/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE_RESULT.md`

Processed raw log:

`research/archive/2026.09.28_SpeedIdentityProbe.log`

## Current bounded production correction

Preserve ADR-0007's user-facing token:

```ini
AnimationFamily=Hero
```

The only authorized production correction is inside `BehaviorProfiles::TryBuildRuntimeKey()` runtime-family extraction:

```text
exact observed g3_hero_skeleton -> hero
all other unproven runtime family strings unchanged/fail-closed
```

Current implementation changes only `src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp`. `AttackSpeed`, all six Speed caller hooks, collision behavior, Raise behavior and the INI schema remain untouched.

## Frozen Speed v2 production shape

```text
six callers:
+0x383F0
+0x38E9D
+0x38F22
+0x3937D
+0x39402
+0x48677

caller mCCallHook
-> explicit factual EAX action
-> mCCaller invokes LIVE Script_Game+0x42A0 once with EAX restored
-> compatible result B*M
-> exact configured/evidenced route applies C/B
-> finite C*M returned
-> non-finite composed result fails closed to compatible result
```

Hard exclusions remain:

```text
NO hook/ownership of Script_Game+0x42A0 entry
NO +0x38A8B StateTime-as-action site
NO global StartPlayAni/speed override
NO copied New Balance multiplier policy
NO final-result replacement
```

Initial evidence-bounded technical bases remain:

```text
Normal Action1:
None+1H / Shield+1H / Torch+1H / 1H+1H = 0.6
None+2H / None+Axe / None+Staff / None+Halberd = 0.7

Quick Action4/5 = 1.0
```

Unsupported/unproven routes, including Normal Fist/PhysicalFist and non-Hero families, remain compatible/native fail-closed.

## Immediate route

When the User is on the local build/game PC:

```text
1. synchronize development to current remote
2. rebuild Script_SpeedIdentityProbe (it compiles the same production BehaviorProfiles.cpp)
3. deploy/hash refreshed probe beside the existing production stack
4. keep current Hero/None/1H Normal + Quick BaseSpeed=0.4 INI
5. repeat several Normal + Quick 1H attacks
6. require:
   Key.AnimationFamily=hero
   ProfileMatch=true
   ProfileHasBaseSpeed=true
   ProfileBaseSpeed=0.400000
7. only then rebuild/deploy Script_G3AnimationBehaviors.dll
8. repeat the small Speed behavior check
9. if Speed changes correctly, continue New Balance full/depleted/contextual/unconfigured/native-only acceptance
10. close Speed completely
11. only then begin Raise
```

Primary production runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

`Script_SpeedIdentityProbe.dll` may coexist only for the bounded identity-validation run.

Expected final runtime invariant remains:

```text
configured base changes
AND
relative Gothic/New Balance contextual modifiers remain effective
```

## Read next

- exact short continuation -> `BETWEEN_CHATS.md`
- active correction -> `work/active/SPEED_RUNTIME_HERO_FAMILY_NORMALIZATION_CORRECTION.md`
- closed identity probe -> `archive/investigations/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE_RESULT.md`
- Speed architecture -> ADR-0004 + ADR-0005 + ADR-0007
- static mechanism evidence -> EV-391 + EV-392 in `EVIDENCE_LEDGER_389_ONWARD.md`
- independent audit closure -> `archive/investigations/SPEED_V2_DEEP_INDEPENDENT_STATIC_AUDIT_RESULT.md`
- S-01 correction closure -> `archive/investigations/SPEED_V2_S01_FINITE_OUTPUT_GUARD.md`
- completed implementation contract -> `archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`
- build/deploy/startup procedures -> `PROJECT_OPERATING_PROCEDURES.md` POP-02/03/04

## Still paused

```text
NO Raise work while Speed is open
NO AttackContinuationProtection
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
