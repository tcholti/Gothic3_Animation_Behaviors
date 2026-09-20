# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-20

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
standalone collision regression = ACTIVE
Phases 1–3 = CLOSED/PASS
generic equipped Sprint = PERMANENT PRODUCTION SUPPORT CLOSED/PASS THROUGH EV-329
Phase 4 non-weapon creatures = PAUSED AT RAW8 FIST AUTHORING-SEMANTICS RESEARCH
focused permanent raw55 acceptance = CLOSED/PASS at EV-298
latest completed evidence = EV-350
active evidence ledger = EVIDENCE_LEDGER_342_ONWARD.md
active temporary review = COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md
active Work implementation task = COLLISION_RAW8_TOUCHDAMAGE_CONTACT_BOUNDARY_OBSERVATION.md — source review PASS / local build + runtime observation pending
current stop gate = POP-12 validation of reviewed contact-boundary implementation state before runtime
```

## Current responsibility

User + Normal Chat have agreed on the desired raw8 author-facing semantic:

```text
FIST opens one target-directed native body-contact / hit opportunity
-> no native hit/contact resolution yet: opportunity remains available
-> first native hit/contact resolution consumes it for that target
-> block / immunity / reactions / HP damage remain outside this mod
-> later FIST rearms another opportunity
-> C1 / Hit termination closes any unused opportunity
```

No raw8 `FIST_OFF` is part of the design absent future contradictory evidence.

Latest causal closure:

- **EV-347:** native raw8 closes the latch after both hit and miss attempts.
- **EV-348:** one post-miss latch-only rearm can restore a later native opportunity.
- **EV-349:** Parade shows native hit/contact resolution can occur with zero visible damage, while a temporary rearmed opportunity can survive Hit-C1 replacement into Recover unless explicitly closed.

EV-350 closes the retirement: both twins built, diagnostic deployment/startup passed, closed raw8 research instrumentation stayed absent, and the optional Gargoyle control returned to the expected one-shot baseline.

**Work implementation `929bba9974788c873860f8e33f504c091f7aa524` is independently source-reviewed PASS. Before local runtime observation, POP-12 must validate this reviewed implementation-state handoff.**

Current bounded research question:

> Does exact raw8 reach `gCTouchDamage_PS::CanBeActivatedNow` and/or `TriggerTarget`, and do those native boundaries correlate with factual contact resolution independently of HP-damage policy?

Frozen task: `docs/work/active/COLLISION_RAW8_TOUCHDAMAGE_CONTACT_BOUNDARY_OBSERVATION.md`.

## Current runtime provenance

Current neutral diagnostic baseline implementation:

`ac1373a88b17c1fc36f8c2b7e06ce394d2777cc3`

Current diagnostic DLL:

`Script_FrameCollisionTest.dll`  
SHA256 `C33046D1AE139B5D905CF5E1004F725F07A5FE8CAC3A9705F11691497D7CD17D`

Build, sole-live diagnostic deployment and startup/unload gate: PASS.

## Read next by question

- active raw8 design/research gate → `docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`
- exact short-lived continuation → `BETWEEN_CHATS.md`
- current collision facts → `COLLISION_REFERENCE.md`
- current validation matrix → `COLLISION_TEST_PLAN.md`
- exact proof/provenance → `EVIDENCE_INDEX.md` → EV-347 / EV-348 / EV-349 / EV-350
- lifecycle/repair architecture → `COLLISION_LIFECYCLE.md`
- diagnostics architecture → `COLLISION_DIAGNOSTICS.md`
- permanent raw55 architecture → `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`

## Sequence after standalone collision regression

```text
complete seven standalone phases
-> New Balance 0.7 exact distributed-bundle regression incl. AttackCollision
-> mature collision migration into src/Script_G3AnimationBehaviors
-> diagnostics-free integration validation
-> later Raise/speed
```

Still paused:

```text
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
