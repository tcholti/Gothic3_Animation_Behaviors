# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Feature-development method: `docs/FEATURE_DEVELOPMENT_METHOD.md`  
Prior raw55 suppression probe: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`  
Current Quick callback-boundary probe: `docs/COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_250_ONWARD.md` through EV-262  
Evidence path moves: `docs/EVIDENCE_PATH_MIGRATIONS.md`  
Bounded Work execution: `docs/WORK_IMPLEMENTATION_PROTOCOL.md`  
Architecture: `docs/DESIGN.md`; `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Validation: `docs/COLLISION_TEST_PLAN.md`

---

## Closed Collision Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
collision architecture verification        CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack         CLOSED/PASS — EV-216–EV-244
raw8 FIST Normal/Power/Quick/Sprint         CLOSED/PASS — EV-221–EV-251
native NPC equipped controls                CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control           CLOSED/PASS — EV-259
fall-down logger boundary                   CLOSED — EV-260
BluntArrow/BluntBolt classification         CLOSED — EV-261
raw55 early-callback causal ownership       CONFIRMED — EV-262
raw55 uniform suppression production gate   FAILED/RETURN TO DESIGN — EV-262
```

Raw8 FIST remains one shared proven mechanism across Normal, Power, Quick and Sprint. Marker applicability is not species-gated.

---

## Current Raw55 State

Native Troll/BlackTroll baseline uses factual `TrollFist / gEUseType_PhysicalFist / raw55 / group5`; raw8 resolver is absent. Representative native Quick opens raw55 `5 -> 7` before authored FIST, can damage while offensive, then cleans `7 -> 5` with clean C1 finalization.

EV-262 established that suppressing the exact marked raw55 attack-family callback removes the old pre-FIST raw55 opening, but whole-callback suppression is not uniformly safe. Normal and Sprint remained clean in the tested scope. Quick diverged: rejected raw55 FIST arrived at StatePosition 0 instead of the native baseline's StatePosition 1, later raw55 reopened after FIST, and finalization could require C1 repair.

The follow-up diagnostic source therefore changes **Quick only** from intervention to observation:

```text
Normal marked raw55 -> prior suppression experiment unchanged
Sprint marked raw55 -> prior suppression experiment unchanged
Quick marked raw55  -> native callback runs; before/after callback facts logged
```

For Quick, `PhysicalFistProbe` now records `StatePosition`, RIGHT raw55 collision group, action/phase/state-time/motion, C1 generation, and native result across the original `_AI_QuickAttack` invocation. `EngineBridge` remains the sole hook owner and contains only the diagnostic begin/original/end delegation seam.

The September 12 Sabretooth marked-Quick control remains useful as a healthy raw8 control across native-NPC and transformed-player ownership, but its compact accepted-marker `StatePosition=1` is not pre-marker proof because accepted Quick marker processing itself writes marker-owned StatePosition before that compact line is emitted.

Active comparison artifacts include:

```text
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
research/raw/2026.09.12_sabertooth_marked_quick.log
```

---

## CURRENT IMMEDIATE RESPONSIBILITY — QUICK RAW55 CALLBACK-BOUNDARY RUNTIME

The bounded observation probe source is published. Do not add another source intervention before runtime evidence.

Single causal question:

> Across each normal native `_AI_QuickAttack` invocation in an exact marked factual raw55 Quick execution, does StatePosition change, does TrollFist collision group change, or do both change in the same callback invocation?

Local next step:

```text
User + Normal Chat build/deploy Script_FrameCollisionTest
-> exercise several marked Troll/BlackTroll Quick attacks
-> capture CORE RAW55_QUICK_CALLBACK_BOUNDARY records
-> correlate with collision-group / FIST / C1 records
-> interpret against COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md
-> promote evidence
-> return to design
```

No Normal/Sprint runtime sample is required for the causal answer unless used as a convenient sanity control.

Do not patch Quick speculatively. Do not broaden into species policy, raw8 changes, equipped behavior changes, new hooks, timers, polling, permanent `PhysicalFistCollision`, or AttackContinuationProtection.

The broader native-creature and compatibility sequence remains paused until raw55 is resolved or explicitly deferred.
