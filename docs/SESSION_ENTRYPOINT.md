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
Phase 4 non-weapon creatures = PAUSED PENDING RAW8 DIAGNOSTICS-ONLY REVIEW CORRECTION + FOCUSED PERMANENT ACCEPTANCE
focused permanent raw55 acceptance = CLOSED/PASS at EV-298
latest completed evidence = EV-354
active evidence ledger = EVIDENCE_LEDGER_342_ONWARD.md
active temporary review = RAW8 PRODUCTION IMPLEMENTATION STATIC REVIEW COMPLETE: BEHAVIOR PASS / DIAGNOSTIC CORRECTION OPEN
active Work implementation task = COLLISION_RAW8_PRODUCTION_DIAGNOSTIC_COMPACTION_CORRECTION.md
current stop gate = POP-12 validation of review-maintained state, then bounded diagnostics-only correction before any build
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

**EV-354 closes the pre-Work Sabretooth Sprint-origin sentinel PASS: 20 opportunities opened under Action9/SPRINT and were consumed under Action2/POWER in the same C1 on the same PowerAttack-named motion; two also survived an earlier miss/rearm. Production task remains frozen; run POP-12 before Work.**

Production implementation `3426cede41c0087e43edc0d81c825ff167e8e034` has completed independent Normal Chat static review.

Behavior/state-machine review: **PASS**. The implementation correctly promotes the EV-353/EV-354 mechanism into permanent `Raw8FistCollision`, makes the proven OnDamage/combat-move/timing/finalization transports behavior-required in both twins, preserves the C1 execution record after contact, and removes the temporary probe.

Before build, one bounded diagnostics-only correction is required:

- routine `RAW8_OPPORTUNITY_CLOSE` must represent only an actually unused pending opportunity, not later retirement of an already contact-consumed execution;
- routine CORE opportunity records must not carry rich raw pointer-address fields reserved for DEEP/anomaly diagnostics.

No raw8 behavior architecture is reopened.

Permanent raw8 authority: `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`.

Reviewed parent implementation contract: `docs/work/active/COLLISION_RAW8_PERSISTENT_OPPORTUNITY_PRODUCTION_IMPLEMENTATION.md`.

Active correction contract: `docs/work/active/COLLISION_RAW8_PRODUCTION_DIAGNOSTIC_COMPACTION_CORRECTION.md`.

## Current runtime provenance

Latest runtime-reviewed diagnostic implementation:

`015a3ef90bf135cf502ac6507fb68f7c8c962800`

Current unbuilt permanent raw8 production source candidate:

`3426cede41c0087e43edc0d81c825ff167e8e034` — behavior static review PASS; diagnostics-only correction pending

Current diagnostic DLL:

`Script_FrameCollisionTest.dll`  
SHA256 `539282F9DAD4A690CFE5AA22B5C5A85066EDFC81C617859EEDDE5341CE869DD5`

Build, sole-live diagnostic deployment and startup/unload gate: PASS.

## Read next by question

- active raw8 diagnostics-only review correction → `docs/work/active/COLLISION_RAW8_PRODUCTION_DIAGNOSTIC_COMPACTION_CORRECTION.md`
- reviewed parent raw8 production implementation → `docs/work/active/COLLISION_RAW8_PERSISTENT_OPPORTUNITY_PRODUCTION_IMPLEMENTATION.md`
- exact short-lived continuation → `BETWEEN_CHATS.md`
- current collision facts → `COLLISION_REFERENCE.md`
- current validation matrix → `COLLISION_TEST_PLAN.md`
- exact proof/provenance → `EVIDENCE_INDEX.md` → EV-347–EV-354
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
