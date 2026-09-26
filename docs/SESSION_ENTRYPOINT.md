# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-26

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
standalone frozen collision baseline = f1f5d2aad3edc3564a9a8b40541840b94f8fa903
first raw55 SP2 correction = 6eb3e3ca96da55e89127c24d5f656e05610d315f
Sprint-first SP2 correction = ce59e5a2bad564652eaba970e959bdef0b479d82
Sprint-second SP2 candidate = 4c85193f4efd31e789bc07d7e3c71d31a9b5326e
latest runtime evidence = EV-380
current ledger = EVIDENCE_LEDGER_380_ONWARD.md

standalone final-source collision regression = CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy = PASS EV-375
New Balance equipped/raw8 Sprint controls = PASS EV-377
first raw55 SP2 correction = runtime PASS EV-378
Sprint-first SP2 correction = runtime PASS EV-379
Sprint second-FIST timing envelope = MAPPED EV-380
Sprint-second SP2 candidate = IMPLEMENTED + INDEPENDENT SOURCE REVIEW PASS
New Balance full intended-stack compatibility = OPEN
current responsibility = local build/deploy + focused runtime acceptance of Sprint-second SP2 candidate
active task = docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_SP2_COMPATIBILITY_CORRECTION.md
```

## Frozen behavior

Permanent raw8:

```text
accepted FIST -> one target-directed opportunity OPEN
native miss -> stays OPEN + latch rearm
first exact native contact -> CONSUMED
later FIST in same C1 -> may OPEN another opportunity
C1 finalization/replacement -> unused opportunity CLOSED
unmarked raw8 -> native
```

Permanent raw55 first/repeated semantics:

```text
first accepted FIST -> exact RIGHT raw55 5 -> 7
later accepted FIST -> ClearTriggeredList/rearm only; no second physical opening
native target/contact/damage remains Gothic-owned
native cleanup 7 -> 5 remains Gothic-owned first
```

Final standalone diagnostic SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Final standalone behavior SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

Latest previously deployed diagnostic SHA256:
`490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C`

## EV-380 result

Deliberate BlackTroll double-FIST fixtures mapped marker2 timing:

```text
frames 1+3:
  marker1 SPRINT/SP2 -> accepted/open
  marker2 SPRINT/SP2 -> rejected by pre-correction source

frames 1+8:
  marker2 may be SPRINT/SP2 OR POWER/SP2

frames 1+15:
  marker2 POWER/SP2 -> accepted/clear-only rearm
```

The tested Hit is already SP2 at frame1. Sprint/SP1 second-FIST acceptance is therefore unproven and not authorized.

Evidence-bounded rule:

```text
origin = immutable SPRINT
current POWER  -> preserve explicit SP1 or SP2
current SPRINT -> additionally accept explicit SP2 only
NO >=1 generalization
NO Sprint/SP1 widening
```

The completed state-mapping investigation is archived at:

`archive/investigations/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_STATE_INVESTIGATION.md`

## Implemented candidate / review

Implementation commit:

`4c85193f4efd31e789bc07d7e3c71d31a9b5326e`

Required parent:

`4f52f5e7cc586a5847c2f4200fc6911765a4cc7c`

Independent Normal Chat source review:

```text
PASS
one commit ahead of frozen parent
one production file changed
PhysicalFistCollision.cpp only
exact Sprint-origin second-FIST branch only
```

Implemented predicate:

```cpp
return (currentFamily == AttackFamily_Power
        && (statePosition == 1 || statePosition == 2))
    || (currentFamily == AttackFamily_Sprint
        && statePosition == 2);
```

The active task remains open until runtime acceptance; the implementation is not yet declared runtime PASS.

## Exact next route

User local build/deploy from current branch, then focused runtime acceptance:

```text
1. frame1+3 BlackTroll Sprint
   marker1 SPRINT/SP2 accepted/open
   marker2 SPRINT/SP2 MUST accept/rearm
   marker2 must not request another physical opening

2. frame1+8 transition-race fixture
   SPRINT/SP2 marker2 MUST accept/rearm
   POWER/SP2 marker2 MUST remain accepted/rearm

3. frame1+15
   POWER/SP2 remains accepted/rearm

4. single-FIST Sprint control unchanged
5. true-Power double-FIST control unchanged
6. representative Normal + Quick controls unchanged
```

After that, run the separate marked/unmarked sheath/no-sheath Troll Sprint control if the missing-contact observation persists.

## Current intended New Balance environment

```text
New Balance 0.7 as distributed
+ all normally used/distributed New Balance DLLs
+ relevant Script_AttackCollision environment
+ Zombie Separation
+ Axe Separation
+ Rapier Separation
+ EV-375 zombie Axe copied/renamed assets
+ exactly one Gothic3_Animation_Behaviors collision twin
```

## Paused speed-control authority

Future speed control is governed by `DESIGN.md` §3 and `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`.

Configured speed is **base-speed authority**, not final effective-speed authority. Gothic/New Balance stamina and other legitimate dynamic modifiers must remain composable. Exact v2 hook/order remains research-pending. Raise/speed stays paused until collision compatibility closes.

## Read next by question

- active runtime-gated task → `work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_SP2_COMPATIBILITY_CORRECTION.md`
- exact continuation → `BETWEEN_CHATS.md`
- current facts → `COLLISION_REFERENCE.md`
- validation gate → `COLLISION_TEST_PLAN.md`
- raw55 architecture → `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
- evidence proof → `EVIDENCE_INDEX.md` → EV-376–EV-380
- speed architecture → `DESIGN.md` §3 / ADR-0004

## Still paused

```text
NO production migration until New Balance compatibility + standalone post-compat sentinel close
NO Raise/speed implementation yet
NO AttackContinuationProtection work
NO Normal/SP0 second-FIST widening without separate research
```
