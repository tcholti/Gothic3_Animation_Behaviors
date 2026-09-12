# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md`  
Prior raw55 probe contracts: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md`; `docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_FIST_REARM_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_265_ONWARD.md` through **EV-267**; prior raw55 causal evidence EV-262–EV-264 is in `docs/EVIDENCE_LEDGER_250_ONWARD.md`  
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
raw55 Quick group opening without rearm         INSUFFICIENT — EV-266
raw55 Quick FIST-time triggered-list rearm      CONFIRMED/PASS FOR CONTACT — EV-267
raw55 close-range marked/native coverage cause  OPEN — current probe
```

Raw8 FIST remains a separate proven mechanism. EV-267 raw55 rearm evidence must not be generalized back onto raw8.

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
    native _AI_QuickAttack contains both StatePosition 0 -> 1
    and early raw55 5 -> 7

EV-265:
    suppress only early 5 -> 7
    StatePosition progression survives

EV-266:
    authored FIST can open the exact raw55 source at ~StateTime 0.48–0.49
    native cleanup later returns 7 -> 5
    group opening alone does not restore damage

EV-267:
    add exactly one TouchDamage.ClearTriggeredList after successful FIST 5 -> 7
    marked Quick can now damage PC_Hero when damaging contact occurs
    native cleanup remains healthy
```

EV-267 also exposes a close-range coverage difference. The User observed that marked Quick did not damage while standing so close that the fist passed beyond the player's body before/around the authored opening, but did damage when farther back so the fist contacted after the marker. Native/unmarked Troll attacks could damage even very close. Ordinary blocking/body collision existed in both cases.

The logs identify the same RIGHT `TrollFist/raw55` physical source in marked and native Quick. They do not expose its geometric shape, so "only fist" versus "whole limb/body" is not yet a proven engine statement.

The strongest remaining variable is timing: native Quick opens raw55 near the beginning of Hit, while the marked EV-267 path suppresses that opening and waits until the FIST marker around StateTime ~0.47–0.49.

Permanent raw55 design remains intentionally unfrozen until this timing/geometry distinction closes.

---

## CURRENT IMMEDIATE RESPONSIBILITY — WORK IMPLEMENTATION

The next diagnostic contract is frozen in:

```text
docs/COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md
```

The exact bounded Work task is in:

```text
docs/BETWEEN_CHATS.md
```

Single question:

> On the same marked raw55 Quick animation, if we restore the original native early RIGHT raw55 `5 -> 7` timing and disable the later FIST activation/rearm intervention for that execution, does very-close-range damage return?

Required architecture:

```text
PhysicalFistProbe
    recognizes the same exact marked raw55 Quick fixture
    temporarily ALLOWS the exact early native 5 -> 7 request
    does not create an EV-265 suppression proof for that execution
    therefore does not perform EV-267 FIST-time activation/rearm later
    owns all temporary control logging/state hygiene

EngineBridge
    remains sole hook transport owner
    ordinary SetCollisionGroup path is unchanged once probe says do not suppress

FrameCollisionMarkers
    unchanged; raw55 FIST remains stable unsupported behavior

Raw8FistCollision
    unchanged
```

No probe-owned `ClearTriggeredList`, custom damage, StatePosition/SPU write, manual cleanup, geometry modification, or animation asset change is authorized.

Build execution is **not** authorized for Work. Normal Chat reviews source first; User + Normal Chat build only after review passes.

---

## Active Comparison Evidence

Keep in `research/raw/` while the close-range timing/geometry question remains open:

```text
research/raw/2026.09.12_troll_quick_fist_activation_3.log
research/raw/2026.09.12_black_troll_quick_fist_activation_3.log
research/raw/2026.09.12_troll_native_collision_3.log
research/raw/2026.09.12_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_black_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_troll_marked_attacks_2.log
research/raw/2026.09.12_black_troll_marked_attacks_2.log
```

The first three are canonically represented by EV-267; the next two by EV-266; the last two by EV-265.

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
no contact-geometry/body-physics changes
no animation asset/marker placement changes
no new hooks/timers/polling
```

---

## Still Paused

Until the Quick close-range timing/geometry question closes and raw55 design is sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint raw55 production generalization
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
