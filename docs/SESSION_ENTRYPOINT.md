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
Raw55 probe authority: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`  
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

Temporary diagnostic `PhysicalFistProbe.cpp/.h` suppresses exact eligible marked raw55 Normal/Quick/Sprint callback invocations while leaving `EngineBridge` as sole hook owner and `Raw8FistCollision` unchanged.

Runtime result EV-262:

```text
old pre-FIST raw55 5 -> 7 removed             causal hypothesis SUPPORTED
Normal suppression path                        clean in tested scope
Sprint suppression path                        clean in tested scope
Sabretooth/raw8 + Golem controls               unaffected
Quick suppression path                         NOT clean
```

Quick-specific contradiction: after FIST, Troll/BlackTroll raw55 can reopen `5 -> 7`; after an apparent cleanup, C1 finalization can still observe RIGHT raw55 group7/outstanding and repair it to 5. Therefore no permanent `PhysicalFistCollision` production responsibility is frozen yet.

Active comparison artifacts remain:

```text
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
```

---

## CURRENT IMMEDIATE RESPONSIBILITY — QUICK RAW55 RETURN-TO-DESIGN

NORMAL CHAT only. Do not modify production/source behavior or launch Work yet.

Single causal question:

> What native side effect or second path causes marked raw55 Quick to reopen TrollFist from group5 to group7 after FIST when the early `_AI_QuickAttack` callback invocation is suppressed, and why does C1 finalization still observe raw55 group7/outstanding after the apparent cleanup?

Method:

```text
existing evidence comparison first
-> inspect only source/API needed for the Quick path
-> distinguish factual observation from inference
-> freeze at most one bounded diagnostic responsibility if evidence requires a new probe
-> separate Work task only after Normal Chat contract freeze
```

Do not patch Quick speculatively. Do not broaden into species policy, raw8 changes, equipped behavior changes, new hooks, timers, polling, or AttackContinuationProtection.

The broader native-creature and compatibility sequence remains paused until raw55 is resolved or explicitly deferred.
