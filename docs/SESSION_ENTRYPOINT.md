# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md`  
Prior closed raw55 probes: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_250_ONWARD.md` through **EV-264**  
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
raw55 uniform whole-callback suppression gate   FAILED/REJECTED — EV-262
raw55 Quick callback compound ownership         CONFIRMED/CLOSED — EV-264
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

EV-262 established that suppressing the marked raw55 attack-family callback removes the old early/pre-FIST raw55 opening, but whole-callback suppression is not safe for Quick.

EV-264 now explains the Quick failure at callback granularity. Repeated marked Troll/BlackTroll Quick Action 4 and 5 executions show the same original `_AI_QuickAttack` invocation contains both:

```text
native StatePosition 0 -> 1
RIGHT raw55 collision group5 -> group7
```

The early group opening can damage shortly afterward and occurs well before authored FIST. Therefore whole Quick callback suppression removed required native state progression together with the unwanted early physical opening.

The exact internal native instruction/callee remains unspecified; EV-264 proves compound ownership only at the original callback invocation boundary.

The next causal question is **separability**: allow native Quick to run, but suppress only the exact nested RIGHT raw55 group5-to-group7 request and observe whether StatePosition still advances cleanly.

---

## CURRENT IMMEDIATE RESPONSIBILITY — WORK IMPLEMENTATION

The next diagnostic contract is frozen in:

```text
docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md
```

The exact Work task is in:

```text
docs/BETWEEN_CHATS.md
```

Work must implement only the diagnostics-only selective raw55 Quick group-suppression probe:

```text
marked factual raw55 Quick callback scope established
-> original _AI_QuickAttack still executes exactly once
-> exact nested RIGHT raw55 5 -> 7 SetCollisionGroup request may be suppressed
-> all other native Quick behavior continues
-> existing callback-boundary observation remains
```

`PhysicalFistProbe` owns temporary eligibility/scope/policy. `EngineBridge` remains sole hook owner and receives only the minimum diagnostics-only delegation inside the already-existing SetCollisionGroup transport.

No new hook/RVA/timer/polling path is authorized.

Build execution is **not** authorized for Work. After Work publishes, Normal Chat reviews the source diff first; only then does User + Normal Chat build/deploy/test locally.

---

## Expected Decisive Runtime Shape After Review/Build

If the responsibilities are separable, an exact marked raw55 Quick invocation should show:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION ... Before=5 Requested=7 SUPPRESS_GROUP=1
CORE RAW55_QUICK_CALLBACK_BOUNDARY ... StatePosition=0->1 ... RightGroup=5->5
```

and the same C1 should have:

```text
rejected authored FIST at native StatePosition 1
no physical raw55 5 -> 7 later
no raw55 offense/damage opening
no outstanding raw55 obligation / terminal repair
```

If StatePosition remains 0, raw55 opens later through another path, or lifecycle divergence appears, return to Normal Chat design rather than compensating in source.

---

## Active Comparison Evidence

Keep these in `research/raw/` while the selective Quick probe remains open:

```text
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
research/raw/2026.09.12_sabertooth_marked_quick.log
research/raw/2026.09.12_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_native_attacks.log
```

The three newest Troll logs are canonically represented by EV-264 and remain active comparison inputs, not unprocessed evidence.

---

## Protected Boundaries

```text
Raw8FistCollision unchanged
FrameCollisionMarkers semantics unchanged
CollisionLifecycleGuard semantics unchanged
equipped RIGHT/LEFT/BOTH/OFF unchanged
EngineBridge remains hook transport owner
PhysicalFistProbe remains temporary diagnostics-only
no species/name policy
no permanent PhysicalFistCollision contract yet
no manual Quick StatePosition compensation
no new hooks/timers/polling
```

---

## Still Paused

Until the selective raw55 Quick separability question is closed and raw55 design is either accepted or explicitly deferred:

```text
NO permanent raw55 implementation
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
