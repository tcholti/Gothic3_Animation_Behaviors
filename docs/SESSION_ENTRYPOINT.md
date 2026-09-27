# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-27

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
standalone frozen collision baseline = f1f5d2aad3edc3564a9a8b40541840b94f8fa903
first raw55 SP2 correction = 6eb3e3ca96da55e89127c24d5f656e05610d315f
Sprint-first SP2 correction = ce59e5a2bad564652eaba970e959bdef0b479d82
Sprint-second SP2 correction = 4c85193f4efd31e789bc07d7e3c71d31a9b5326e
Normal-second SP0 correction = a31c66b97e45c27d0739b7df51252d33f490e7e1
standalone Sprint-second SP1 candidate = 1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0
latest runtime evidence = EV-385
current ledger = EVIDENCE_LEDGER_384_ONWARD.md

standalone final-source collision regression = CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy = PASS EV-375
focused raw55 New Balance compatibility = CLOSED/PASS EV-376–EV-382
dual-1H four-marker / three-window authoring = PASS EV-383
New Balance full intended-stack compatibility = CLOSED/PASS EV-384
standalone/no-New-Balance post-compat raw55 sentinel = PARTIAL FAIL EV-385 / CORRECTED CANDIDATE PENDING RUNTIME
Work implementation = COMPLETE
independent Normal Chat source review = PASS
active runtime contract = docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md
```

## EV-385 exact finding

Standalone/no-New-Balance BlackTroll/raw55 tests used double FIST markers at `1+3`, `1+8`, `1+15`, plus a single-FIST control set.

```text
1+3 Sprint-origin:
  marker1 current SPRINT/SP1 -> ACCEPTED / exact RIGHT 5 -> 7
  marker2 same C1/source/origin, still current SPRINT/SP1
  -> REJECTED_UNSUPPORTED_HIT
  -> no marker2 clear/rearm
  -> native cleanup still returns 7 -> 5 / Outstanding=0

1+8 and 1+15 Sprint-origin:
  marker1 current SPRINT/SP1 -> ACCEPTED/open
  marker2 after same-C1 transition current POWER/SP1
  -> ACCEPTED clear-only
  -> GroupRequested=0 / ClearTriggeredList=1
  -> clean native cleanup

single FIST:
  current SPRINT/SP1 -> ACCEPTED/open/clean cleanup
```

Four distinct `1+3` Sprint C1s repeat the same rejection. All other three logs have zero marker anomalies. Across all four logs there are no C1 invariant warnings or terminal repair anomalies.

This is a bounded repeated-marker eligibility compatibility hole, not a cleanup/lifecycle/generation failure.

## Corrected candidate / independent review

Published correction:

`1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`

Exact implemented rule:

```text
Sprint-origin second FIST:
  current POWER  -> explicit SP1 or SP2
  current SPRINT -> explicit SP1 or SP2
```

Independent Normal Chat source review: **PASS**.

The diff is one predicate only. The second-FIST branch still requires exactly two authored FIST markers, exactly one prior accepted FIST, the source already in group7, and then calls only `RearmTriggeredContacts()`. It does not call `ActivateAttackSource()`, so the added SPRINT/SP1 acceptance cannot request a second physical opening.

No generic `>=1`, new hook, timer/queue/hit flag/custom damage, first-FIST change, or neighboring family change was introduced.

## Collision twin / binary state

Both collision twins compile the same behavior-facing source set, including `PhysicalFistCollision.cpp`:

```text
Script_FrameCollisionBehaviorTest
  shared behavior source only

Script_FrameCollisionTest
  same shared behavior source
  + FRAME_COLLISION_DIAGNOSTICS
  + diagnostic-only files
```

Therefore the behavior source candidate is current, but the behavior DLL binary is current only after that target is rebuilt from the exact reviewed source.

Recorded binary state before this correction:

```text
Final standalone diagnostic SHA256 before compatibility work:
5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313

Final standalone behavior SHA256 before compatibility work:
A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340

Latest deployed diagnostic SHA256 after raw55 compatibility corrections:
81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3
```

No post-compatibility behavior built/live hash is recorded. Treat the old behavior DLL as stale/unverified binary state.

## Runtime-log retrieval rule

`PROJECT_OPERATING_PROCEDURES.md` v1.19 makes bounded retrieval mandatory for **all** runtime logs, not only oversized logs:

```text
artifact identity / metadata
-> exact searches + counts
-> bounded event windows
-> representative route samples / whole-run-class checks as required
-> conclusions + provenance in Chat
```

Do not load/reproduce a complete raw log into Chat context merely because it fits. POP-07 remains the large-log specialization using derived manifest/count/index/full-source windows.

## Exact next route

```text
1. User syncs local branch to current remote state containing reviewed candidate 1c45e5e...
2. build BOTH collision twins from the same reviewed final source
   -> record behavior SHA256
   -> record diagnostic SHA256
3. deploy diagnostic twin / verify sole-live-twin + SHA
4. finish corrected standalone diagnostic sentinel:
   - 1+3 direct SPRINT/SP1 second-FIST retest
   - one representative POWER/SP1 continuation control
   - single-FIST SPRINT/SP1 control
   - factual true-Power single/double
   - unmarked raw55 native fallback
5. one small diagnostic New Balance/raw55 regression on the same final source
   -> compatibility-sensitive Sprint-origin SP2 / Action9->Action2 route
6. deploy behavior twin ONLY / verify sole-live-twin + behavior SHA
7. final diagnostics-free observational collision confirmation:
   - representative raw55/equipped/native behavior
   - include several authored animations whose desired RIGHT collision window exists only through G3AB marker behavior
   - no diagnostic log expected
8. only after behavior-only PASS:
   production collision migration + production integration validation
```

Do not run another runtime test from the pre-correction source.

## Current environment boundary

EV-385 is from the intended standalone sentinel environment:

```text
New Balance / Script_AttackCollision absent or disabled
normal standalone G3AB test environment
exactly one current diagnostic collision twin live
same compatibility source lineage through a31c66b...
```

## Read next by question

- exact continuation → `BETWEEN_CHATS.md`
- current runtime contract → `docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md`
- current facts → `COLLISION_REFERENCE.md`
- validation gate → `COLLISION_TEST_PLAN.md` §4.5–§4.6
- operating procedure / bounded log retrieval → `PROJECT_OPERATING_PROCEDURES.md` POP-06/POP-07
- raw55 architecture → `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
- proof → `EVIDENCE_INDEX.md` → EV-385

## Still paused

```text
NO production migration until corrected diagnostic gates + behavior-only confirmation pass
NO Raise/speed implementation yet
NO AttackContinuationProtection work
```