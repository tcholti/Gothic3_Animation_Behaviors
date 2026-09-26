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
Sprint-second SP2 correction = 4c85193f4efd31e789bc07d7e3c71d31a9b5326e
Normal second-FIST SP0 correction = a31c66b97e45c27d0739b7df51252d33f490e7e1
latest runtime evidence = EV-381
current ledger = EVIDENCE_LEDGER_380_ONWARD.md

standalone final-source collision regression = CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy = PASS EV-375
New Balance equipped/raw8 Sprint controls = PASS EV-377
first raw55 SP2 correction = runtime PASS EV-378
Sprint-first SP2 correction = runtime PASS EV-379
Sprint second-FIST timing envelope = MAPPED EV-380
Sprint second-FIST SP2 correction = runtime PASS EV-381
focused New Balance raw55 Sprint contradiction = CLOSED/PASS
Normal raw55 second-FIST SP0 correction = IMPLEMENTED + INDEPENDENT REVIEW PASS / RUNTIME ACCEPTANCE PENDING
New Balance full intended-stack compatibility = OPEN / waits for raw55 Normal closure
active Work task = docs/work/active/COLLISION_RAW55_NORMAL_SECOND_FIST_SP0_COMPATIBILITY_CORRECTION.md
```

## Frozen raw55 behavior

Permanent raw55 first/repeated semantics:

```text
first accepted FIST -> exact RIGHT raw55 5 -> 7
later accepted FIST -> ClearTriggeredList/rearm only; no second physical opening
native target/contact/damage remains Gothic-owned
native cleanup 7 -> 5 remains Gothic-owned first
```

New Balance raw55 compatibility already runtime-confirmed:

```text
true Power first/second: current POWER explicit SP1 or SP2
Sprint-origin first: current SPRINT explicit SP1 or SP2 + earlyOpeningSuppressed
Sprint-origin second:
  current POWER explicit SP1 or SP2
  current SPRINT explicit SP2 only
```

Reviewed Normal candidate now has:

```text
second FIST = current NORMAL + explicit SP0 or SP1
```

This candidate is not promoted to accepted runtime behavior until the focused fixtures pass.

## Why Normal SP0 is evidence-backed

Earlier causal work EV-286–EV-292 proved:

```text
first Normal FIST may legitimately occur at SP0
marker-owned ClearTriggeredList() enables hit1 before SP0->SP1
Gothic's exact native between-contact ALL clear creates the implicit second opportunity
permanent marked-Normal behavior suppresses that native clear
later authored marker2 can replace it with one clear-only rearm
```

Those tests used marker2 at SP1 and proved SP1 sufficient, not necessary.

The archived New Balance `1+8` timing fixture adds the missing boundary evidence:

```text
marker1 NORMAL/SP0 -> accepted/open+clear
hit1 -> ONDAMAGE
marker2 still NORMAL/SP0 -> rejected only by the old second-FIST SP1 gate
RIGHT already group7
```

Representative C1=1:

```text
marker1 StateTime=0.025186 SP0
hit1
marker2 StateTime=0.241280 SP0 -> rejected
```

Representative C1=3 repeats the same class with marker2 StateTime=0.246752 SP0 after hit1.

Therefore SP1 is not a proven prerequisite for authored second-contact rearm.

## Reviewed implementation

Implementation commit:

`a31c66b97e45c27d0739b7df51252d33f490e7e1`

Implementation parent:

`396c7b8b0886174860cc452176a2ed57bf530784`

Independent Normal Chat static review: **PASS**.

Only this predicate changed:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && statePosition == 1;
```

became:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

Quick, Power, Sprint, all first-FIST predicates, marker2 clear-only behavior, Normal native-clear suppression, lifecycle, hooks and diagnostics remain unchanged.

## Runtime acceptance — current next action

User locally builds/deploys the reviewed candidate and reuses the same three mixed Troll fixtures:

```text
1+3
  Normal marker2 SP0 should ACCEPT + clear-only
  two damage events NOT required because marker2 may precede hit1

1+8
  decisive route:
  marker1 SP0 -> hit1 -> marker2 still SP0
  marker2 must ACCEPT + ClearTriggeredList=1 + GroupRequested=0
  later second native contact may occur when geometry/target state permits

1+15
  established Normal/SP1 marker2 must remain accepted/rearmed

Quick / Power / Sprint controls remain protected in the same logs
```

## Deployment references

Final standalone diagnostic SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Final standalone behavior SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

Latest deployed diagnostic before this Normal correction:
`B4161D74DD849F4B7B67D9ACCFC42A8D8784F7EF19FB968F2E44D67ED57BD689`

## Exact next route

```text
1. user builds/deploys reviewed Normal SP0 candidate
2. user runs 1+3, 1+8, 1+15 mixed Troll fixtures
3. Normal Chat reviews runtime evidence
4. if raw55 Normal closes cleanly:
   focused Normal/Quick/Power/Sprint raw55 closure
5. broader representative/full New Balance compatibility
6. standalone/no-New-Balance post-compat raw55 sentinel
7. production collision migration + diagnostics-free integration validation
```

Do not move to the broad New Balance gate before this raw55 Normal authoring boundary is closed.

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

- exact continuation → `BETWEEN_CHATS.md`
- active runtime-acceptance contract → `work/active/COLLISION_RAW55_NORMAL_SECOND_FIST_SP0_COMPATIBILITY_CORRECTION.md`
- current facts → `COLLISION_REFERENCE.md`
- validation gate → `COLLISION_TEST_PLAN.md`
- raw55 architecture → `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
- evidence proof → `EVIDENCE_INDEX.md` → EV-286–EV-292 + EV-380–EV-381
- speed architecture → `DESIGN.md` §3 / ADR-0004

## Still paused

```text
NO production migration until New Balance compatibility + standalone post-compat sentinel close
NO Raise/speed implementation yet
NO AttackContinuationProtection work
NO broad Normal redesign beyond reviewed SP0||SP1 second-FIST candidate
```