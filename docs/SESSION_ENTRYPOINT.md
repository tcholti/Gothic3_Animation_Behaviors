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
Speed v2 production source = IMPLEMENTED / SOURCE-REVIEW PASS
final reviewed source SHA = 4f9911f57d8d6b36efd35adee41920560c3986e0

CURRENT = Speed v2 local build/deploy gate
BUILD/RUN = not attempted in source task; requires User local game/build PC
RAISE = PAUSED until Speed is completely closed
main = FROZEN
```

The first source-review pass found one blocker in the pre-final lineage: `c11c1486c05161a300fcb3ea6de1da5e5140cb04` compiled `AttackSpeed` but omitted the six caller-side `EngineBridge` transports. The bounded correction at `4f9911f5...` added only that frozen transport; post-correction static review passed and the correction diff did not alter collision behavior.

Closed implementation contract:

`archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`

## Speed v2 — accepted source shape

Required composition:

```text
live compatible result = B * M
configured result      = (B * M) * (C / B) = C * M
```

The final source uses six tested-build `Script_Game` caller hooks owned by `EngineBridge.cpp`:

```text
+0x383F0
+0x38E9D
+0x38F22
+0x3937D
+0x39402
+0x48677
```

Transport:

```text
selected caller
-> mCCallHook passes factual EAX action explicitly
-> mCCaller invokes LIVE Script_Game+0x42A0 exactly once with EAX restored
-> compatible owner (including New Balance) produces B*M
-> AttackSpeed applies C/B only for exact configured + evidenced route
-> existing downstream path receives C*M
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

Keep active for the first runtime acceptance:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Pinned references:

```text
SDK:              90bfd344de4510dda7ac9da7461cc7f1eac911f7
New Balance:      316d32406a133f8884e7e302752c35f66b4f54fc
Binary reference: c9d12cb5f0dcb4f96af6a82c02138c1c15e981b6
```

## Immediate route

When the User is back on the local build/game PC:

```text
1. build final reviewed source 4f9911f57d8d6b36efd35adee41920560c3986e0 using the current POP-02 production build procedure
2. deploy/hash through POP-03
3. startup/load gate through POP-04
4. validate New Balance composition first:
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

No additional native-speed logging is currently requested.

## Read next

- exact short continuation -> `BETWEEN_CHATS.md`
- Speed architecture -> ADR-0004 + ADR-0005 + ADR-0007
- static proof -> EV-391 + EV-392 in `EVIDENCE_LEDGER_389_ONWARD.md`
- completed source contract -> `archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`
- build/deploy/startup procedures -> `PROJECT_OPERATING_PROCEDURES.md` POP-02/03/04

## Still paused

```text
NO Raise work while Speed is open
NO AttackContinuationProtection
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
