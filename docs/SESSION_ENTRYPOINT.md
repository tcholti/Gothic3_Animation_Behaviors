# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_FIST_REARM_PROBE.md`  
Prior raw55 probe contracts: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md`; `docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_265_ONWARD.md` through **EV-266**; prior raw55 causal evidence EV-262–EV-264 is in `docs/EVIDENCE_LEDGER_250_ONWARD.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
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
raw55 Quick authored-FIST group activation      CONFIRMED/PASS — EV-266
raw55 Quick native cleanup after FIST opening   CONFIRMED/PASS — EV-266
raw55 Quick damage from group opening alone     FAILED/INSUFFICIENT — EV-266
```

Raw8 FIST remains a separate proven mechanism. Do not generalize raw55 findings onto raw8.

---

## Current Raw55 State

Factual Troll/BlackTroll source:

```text
TrollFist
gEUseType_PhysicalFist / raw55
resting collision group5
```

Current Quick causal chain:

```text
EV-264:
    native _AI_QuickAttack invocation contains both
    StatePosition 0 -> 1
    and early raw55 5 -> 7

EV-265:
    suppress only the early 5 -> 7
    StatePosition 0 -> 1 survives
    source stays group5

EV-266:
    at authored FIST (~StateTime 0.48–0.49), request exact RIGHT raw55 5 -> 7
    physical transition succeeds
    real C1 offense obligation is created
    source stays group7 through late Quick window
    Gothic cleans 7 -> 5 normally
    C1 closes cleanly
    BUT no Troll/BlackTroll damage to PC_Hero occurs
```

Therefore early gating, authored source activation, and native cleanup are individually demonstrated for the tested Quick path. The remaining unresolved responsibility is native contact/rearm eligibility after delayed authored activation.

The current `DESIGN.md` raw55 deferred paragraph predates this reopened factual research and is not the active raw55 mechanism authority. Current authority is EV-262–EV-266 plus the frozen probe/handoff named above. Permanent design remains intentionally unfrozen.

---

## CURRENT IMMEDIATE RESPONSIBILITY — WORK IMPLEMENTATION

The next diagnostic contract is frozen in:

```text
docs/COLLISION_RAW55_QUICK_FIST_REARM_PROBE.md
```

The exact bounded Work task is in:

```text
docs/BETWEEN_CHATS.md
```

Single question:

> Keeping EV-265 early suppression and EV-266 authored-FIST `5 -> 7` activation unchanged, does exactly one `TouchDamage.ClearTriggeredList()` on the exact RIGHT raw55 source immediately after verified successful FIST-time activation restore Gothic's native contact/damage while preserving native cleanup?

Required architecture:

```text
PhysicalFistProbe
    owns prior-suppression proof state
    owns exact Quick/FIST eligibility
    owns one-shot FIST-time raw55 activation
    owns one exact post-activation triggered-list clear for this probe

EngineBridge
    remains sole hook/marker transport owner
    no raw55 policy added

FrameCollisionMarkers
    unchanged; raw55 FIST remains UNSUPPORTED_MISSING_SOURCE

Raw8FistCollision
    unchanged

CollisionSourceOperations
    unchanged; do not use its combined ActivateOrRearm helper for this probe
```

The causal delta from EV-266 must be exactly the direct triggered-list clear after successful group7 activation. No custom damage, manual TriggerTarget/OnDamage, StatePosition writes, SPU writes, or cleanup changes.

Build execution is **not** authorized for Work. Normal Chat reviews source first; User + Normal Chat build only after review passes.

---

## Active Comparison Evidence

Keep in `research/raw/` while the Quick contact/rearm question remains open:

```text
research/raw/2026.09.12_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_black_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_troll_marked_attacks_2.log
research/raw/2026.09.12_black_troll_marked_attacks_2.log
research/raw/2026.09.12_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_native_attacks.log
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
```

The first two are canonically represented by EV-266; the next two by EV-265. Earlier logs are closed comparison evidence, not unprocessed evidence.

---

## Protected Boundaries

```text
Raw8FistCollision unchanged
FrameCollisionMarkers semantics unchanged
CollisionLifecycleGuard semantics unchanged
CollisionSources unchanged
CollisionSourceOperations unchanged
equipped RIGHT/LEFT/BOTH/OFF unchanged
EngineBridge remains transport-only
PhysicalFistProbe remains temporary diagnostics-only
no species/name policy
no permanent PhysicalFistCollision yet
no custom/direct damage
no manual TriggerTarget / OnDamage
no StatePosition or SPU writes
no manual cleanup
no new hooks/timers/polling
```

The only newly authorized intervention is one exact `TouchDamage.ClearTriggeredList()` after verified successful authored-FIST raw55 group7 activation in the exact proven Quick C1.

---

## Still Paused

Until the Quick contact/rearm question closes and raw55 design is either sufficiently proven for a permanent owner or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint raw55 production generalization
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
