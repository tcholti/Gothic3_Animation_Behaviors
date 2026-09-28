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
final corrected Speed source SHA = db7b24f1a0c19beaaf4e720cd69d19c331854340

CURRENT = Speed v2 local build/deploy/startup/runtime gate
BUILD/RUN = not yet attempted for corrected Speed source
RAISE = PAUSED until Speed is completely closed
main = FROZEN
```

`docs/work/active/` is clean except its README.

## Independent audit closure

The heavy Work audit independently re-derived the tested-build caller/ABI/compatibility mechanism rather than trusting prior conclusions. It found no BLOCKER or MAJOR finding and confirmed:

- the exact six `Script_Game+0x42A0` caller sites;
- exclusion of `+0x38A8B` because its scalar originates from integerized `GetStateTime()`, not factual action identity;
- `mCCallHook` EAX capture, thunk stack/cleanup, `mCCaller` EAX restoration and x87 return compatibility;
- exactly-once invocation of the live `Script_Game+0x42A0` owner, including New Balance;
- `B*M -> (C/B) -> C*M` compatibility composition;
- EngineBridge/AttackSpeed/BehaviorProfiles responsibility boundaries and fail-closed unsupported routes;
- no collision-source change or dependency.

Audit closure record:

`docs/archive/investigations/SPEED_V2_DEEP_INDEPENDENT_STATIC_AUDIT_RESULT.md`

## S-01 correction

The audit found one MINOR edge: an extreme but finite configured `BaseSpeed` could make the composed arithmetic result non-finite.

Correction `db7b24f1a0c19beaaf4e720cd69d19c331854340` changes only `AttackSpeed.cpp`:

```text
compute composedSpeed = compatibleSpeed * (C / B)
-> if composedSpeed is non-finite, return compatibleSpeed unchanged
-> otherwise return composedSpeed
```

No parser cap, hook/ABI change, technical-base change, profile/schema change, collision change, diagnostics or Raise behavior was introduced.

Correction closure record:

`docs/archive/investigations/SPEED_V2_S01_FINITE_OUTPUT_GUARD.md`

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

Initial evidence-bounded technical bases:

```text
Normal Action1:
None+1H / Shield+1H / Torch+1H / 1H+1H = 0.6
None+2H / None+Axe / None+Staff / None+Halberd = 0.7

Quick Action4/5 = 1.0
```

Unsupported/unproven routes, including Normal Fist/PhysicalFist and non-Hero families, fail closed to the live compatible result.

## Primary runtime compatibility environment

Keep active for first runtime acceptance:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Pinned static references:

```text
SDK:              georgeto/gothic3sdk@90bfd344de4510dda7ac9da7461cc7f1eac911f7
New Balance:      Jackydima/gothic3sdk@316d32406a133f8884e7e302752c35f66b4f54fc
Binary reference: tcholti/Gothic3_Binary_Reference@c9d12cb5f0dcb4f96af6a82c02138c1c15e981b6
```

## Immediate route

When the User is on the local build/game PC:

```text
1. build corrected source lineage containing db7b24f1a0c19beaaf4e720cd69d19c331854340 via POP-02
2. deploy/hash via POP-03
3. startup/load gate via POP-04
4. New Balance runtime validation first:
   - configured Normal + Quick full-stamina controls
   - equivalent depleted-stamina controls
   - representative compatible modifier control(s) where practical
   - unconfigured controls
   - representative supported hand configurations
5. native-only sanity/fallback
6. close Speed completely
7. only then begin Raise
```

Expected runtime invariant:

```text
configured base changes
AND
relative Gothic/New Balance contextual modifiers remain effective
```

No additional native-speed logger run is currently requested.

## Read next

- exact short continuation -> `BETWEEN_CHATS.md`
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
