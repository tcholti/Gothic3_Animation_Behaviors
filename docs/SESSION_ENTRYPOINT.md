# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Completed diagnostic contract: `docs/COLLISION_RAW55_QUICK_REPEAT_FIST_ELIGIBILITY_OBSERVABILITY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_269_ONWARD.md` through **EV-273**; prior raw55 causal evidence EV-262–EV-268 is in the preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick first-FIST behavior remains proven by EV-269:

```text
frame-1 FIST at StatePosition 0
exact RIGHT PhysicalFist/raw55 5 -> 7
ClearTriggeredList once
later native Quick 7 -> 7
StatePosition 0 -> 1
damage on contact
native 7 -> 5 cleanup
```

EV-273 now closes the repeated-FIST primitive:

```text
later frame-15 FIST delivered in same Quick C1
CurrentC1 == StoredC1
CurrentRight == StoredRight
RIGHT PhysicalFist/raw55 remains group7
DecisionFistCount=2
RequiredSourceMask=0
Raw8ResolverAbsent=1
QuickHit=1
Eligible=1
FirstFailedGate=NONE
repeat helper executes ClearTriggeredList=1
second damaging contact can occur after rearm in same Quick execution
```

The User observed Quick attacks damaging twice, once per authored FIST marker. Multiple logged executions correlate an `OnDamage` before the later FIST and another `OnDamage` after the repeated rearm while the same Troll Quick C1 remains active.

The observability commit was diagnostics-only, so EV-272's earlier non-reach did **not** reproduce and its exact prior failed predicate remains unidentified. EV-272 is retained as provenance; it is not evidence that the repeated rearm primitive fails.

Canonical evidence is through **EV-273**. Recovery Lock remains **CLOSED**.

No permanent raw55 implementation is authorized.

---

## Closed / Current Collision Boundary

```text
C1-R1 lifecycle safety                         CLOSED — EV-206–EV-207
collision architecture verification            CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack equipped   CLOSED/PASS — EV-216–EV-244
raw8 FIST shared mechanism + controls           CLOSED/PASS through EV-271
native NPC equipped controls                    CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control               CLOSED/PASS — EV-259
fall-down logger boundary                       CLOSED — EV-260
BluntArrow/BluntBolt classification             CLOSED — EV-261
raw55 early callback causal ownership           CONFIRMED — EV-262
raw55 whole-callback suppression gate           FAILED/REJECTED — EV-262
raw55 Quick callback compound ownership         CONFIRMED/CLOSED — EV-264
raw55 Quick early-group/state separability      CONFIRMED/PASS — EV-265
raw55 Quick authored-FIST group activation      CONFIRMED/PASS — EV-266
raw55 Quick triggered-list rearm                CONFIRMED/PASS — EV-267
raw55 close-range timing cause                  CONFIRMED — EV-268
raw55 Quick frame-1 pre-state activation        CONFIRMED/PASS — EV-269
raw55 later FIST transport                      CONFIRMED — EV-270
equipped + raw8 frame-0/frame-1 marker support  CONFIRMED — EV-271
raw55 repeated-FIST eligibility/rearm            CONFIRMED/PASS — EV-273
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Normal Chat Responsibility

No Work task is active.

Normal Chat + User must choose the next smallest raw55 causal responsibility before another implementation is frozen. The leading unresolved candidates remain:

```text
true raw55 Power-family ownership
replace the old temporary Normal/Sprint whole-callback behavior with a mechanism justified by evidence
production generic FIST occurrence integration
permanent PhysicalFistCollision design/promotion
```

Do not jump directly to permanent raw55 promotion while family ownership and the temporary Normal/Sprint behavior remain unresolved.

---

## Power / Normal / Sprint Boundary

Latest runtime preserves the intended temporary distinction:

```text
true Power: Action=2 / Family=POWER / SuppressNative=0 / can damage
Normal:     Family=NORMAL / temporary whole-callback suppression remains active
```

The earlier EV-272 non-damaging motion named `...PowerAttack...` was factual `Action=9 / Family=SPRINT`, not true Power. Do not infer family from animation filename alone.

True raw55 Power ownership remains unfinished.

---

## Current Runtime Artifacts

```text
research/raw/2026.09.13_deployment_test.log
research/raw/2026.09.13_troll_quick_fist_frame_1_frame_15_repeat_fist_eligibility.log
upload commit 6cc1159c8f302ff600b96dc4eabc8f76167bc058
```

These remain useful active comparison inputs while the next raw55 family/ownership responsibility is selected.

---

## Still Paused

Until the remaining raw55 scope-changing family/ownership decisions are sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
