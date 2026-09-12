# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md`  
Prior raw55 probe contracts: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md`; `docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_265_ONWARD.md` EV-265; prior raw55 causal evidence EV-262–EV-264 is in `docs/EVIDENCE_LEDGER_250_ONWARD.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` (historical raw55 routing there predates EV-262; for active raw55 work use this entry point + EV-262–EV-265 until the index is refreshed at the next stable raw55 checkpoint)  
Evidence path moves: `docs/EVIDENCE_PATH_MIGRATIONS.md`  
Bounded Work execution: `docs/WORK_IMPLEMENTATION_PROTOCOL.md`  
Feature method: `docs/FEATURE_DEVELOPMENT_METHOD.md`  
Architecture: `docs/DESIGN.md`; `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Validation: `docs/COLLISION_TEST_PLAN.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Closed Collision Boundary

```text
C1-R1 lifecycle safety                         CLOSED — EV-206–EV-207
collision architecture verification            CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack             CLOSED/PASS — EV-216–EV-244
raw8 FIST shared mechanism + later controls     CLOSED/PASS through EV-263
native NPC equipped controls                    CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control               CLOSED/PASS — EV-259
fall-down logger boundary                       CLOSED — EV-260
BluntArrow/BluntBolt classification             CLOSED — EV-261
raw55 early callback causal ownership           CONFIRMED — EV-262
raw55 whole-callback suppression gate           FAILED/REJECTED — EV-262
raw55 Quick callback compound ownership         CONFIRMED/CLOSED — EV-264
raw55 Quick early-group/state separability      CONFIRMED/PASS — EV-265
```

Raw8 FIST remains a separate proven mechanism. Do not generalize it to raw55.

---

## Current Raw55 State

Factual Troll/BlackTroll source:

```text
TrollFist
gEUseType_PhysicalFist / raw55
resting collision group5
```

EV-264 proved that one original native marked-raw55 Quick callback invocation contains both:

```text
StatePosition 0 -> 1
RIGHT raw55 group5 -> group7
```

EV-265 then proved those responsibilities are separable at the existing `SetCollisionGroup` boundary. Across 20 Troll + 9 BlackTroll marked Quick executions:

```text
exact early RIGHT raw55 5 -> 7 request suppressed
original _AI_QuickAttack still runs
StatePosition 0 -> 1 preserved
RIGHT stays group5
FIST later arrives at native StatePosition 1
no later physical TrollFist group opening
no OnDamage to PC_Hero
no raw55 outstanding/repair/lifecycle issue
```

This closes the early-gating question for Quick. It does **not** yet prove authored FIST activation/contact/cleanup semantics.

The current `DESIGN.md` raw55 deferred text predates this reopened factual raw55 research. Do not use that historical paragraph as the active raw55 mechanism authority. Current authority is EV-262–EV-265 plus the frozen probe/handoff named above. Permanent design remains intentionally unfrozen.

---

## CURRENT IMMEDIATE RESPONSIBILITY — WORK IMPLEMENTATION

The next diagnostic contract is frozen in:

```text
docs/COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md
```

The exact bounded Work task is in:

```text
docs/BETWEEN_CHATS.md
```

Single question:

> With the EV-265 early Quick raw55 group5-to-group7 request still selectively suppressed, can one exact RIGHT raw55 group5-to-group7 request at the authored FIST event restore Gothic's native contact/damage at authored timing and then receive clean native group7-to-group5 cleanup?

Required architecture:

```text
PhysicalFistProbe
    owns prior-suppression proof state
    owns exact Quick/FIST eligibility
    owns one-shot temporary FIST-time raw55 activation policy

EngineBridge
    remains sole hook transport owner
    only delegates after stable ProcessMarker result exists

FrameCollisionMarkers
    unchanged; raw55 FIST remains UNSUPPORTED_MISSING_SOURCE in stable code

Raw8FistCollision
    unchanged
```

The probe must not issue `ClearTriggeredList`, custom damage, StatePosition writes, manual cleanup, species/name gates, or Normal/Sprint FIST activation.

Build execution is **not** authorized for Work. Normal Chat reviews source first; User + Normal Chat build only after review passes.

---

## Active Comparison Evidence

Keep in `research/raw/` while authored-FIST activation remains open:

```text
research/raw/2026.09.12_troll_marked_attacks_2.log
research/raw/2026.09.12_black_troll_marked_attacks_2.log
research/raw/2026.09.12_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_native_attacks.log
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
```

The first two are canonically represented by EV-265. Earlier logs are closed prior-step comparison inputs, not unprocessed evidence.

---

## Protected Boundaries

```text
Raw8FistCollision unchanged
FrameCollisionMarkers semantics unchanged
CollisionLifecycleGuard semantics unchanged
CollisionSources semantics unchanged
CollisionSourceOperations unchanged
equipped RIGHT/LEFT/BOTH/OFF unchanged
EngineBridge remains transport-only
PhysicalFistProbe remains temporary diagnostics-only
no species/name policy
no permanent PhysicalFistCollision yet
no custom damage
no probe-owned ClearTriggeredList
no new hooks/timers/polling
```

---

## Still Paused

Until the Quick authored-FIST activation/contact/cleanup question closes and raw55 design is either sufficiently proven for a permanent owner or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint raw55 production generalization
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
