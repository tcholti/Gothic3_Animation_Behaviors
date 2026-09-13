# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_REPEAT_FIST_REARM_PROBE.md`  
Current raw55 diagnostic implementation baseline: `0bfb2ba13ba91488570a41592504ac84428def2a`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_269_ONWARD.md` through **EV-271**; prior raw55 causal evidence EV-262–EV-268 is in the preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick first-FIST mechanism is strongly bounded:

```text
EV-269 first frame-1 pre-state FIST:
    exact RIGHT PhysicalFist/raw55 5 -> 7
    one ClearTriggeredList
    later native Quick 7 -> 7
    StatePosition 0 -> 1
    damage on contact
    native 7 -> 5 cleanup
    clean C1 finalization
```

EV-270 proves a later FIST is delivered in the same Quick execution, but the current temporary `PhysicalFistProbe` blocks a second intervention by policy.

EV-271 confirms frame 0 and frame 1 are valid for the tested established marker mechanisms. User clarification: the extra raw8 frame-0 misses were only on spawned-NPC Sabretooth attacks against `PC_Hero`; transformed-player frame-0 Quick attacks hit the spawned Sabretooth consistently. Treat that difference as contact/timing variation, not marker unreliability.

Canonical evidence remains through **EV-271**.

### Repeated-FIST Work attempt 1 — source contradiction

Work correctly stopped without modifying source.

Current remote at that stop:

```text
ec2cb73cebb91b4e92db8d4e49441acf40d08fe2
```

Reason:

```text
raw55 FIST returns UNSUPPORTED_MISSING_SOURCE
before stable generic occurrence consumption
```

Therefore these fields are unavailable for raw55 FIST:

```text
authoredMarkerCount
acceptedMarkerCountBefore
acceptedMarkerCountAfter
executionBudgetReset
```

The repeated-FIST contract has been revised. Do not modify/reorder stable `FrameCollisionMarkers` for this diagnostic.

A revised frozen Work task is active. No permanent raw55 implementation is authorized.

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
raw55 Quick group opening without rearm         INSUFFICIENT — EV-266
raw55 Quick triggered-list rearm                CONFIRMED/PASS — EV-267
raw55 close-range timing cause                  CONFIRMED — EV-268
raw55 Quick frame-1 pre-state activation        CONFIRMED/PASS — EV-269
raw55 later FIST transport                      CONFIRMED — EV-270
raw55 repeated-FIST second rearm                REVISED FROZEN PROBE / IMPLEMENTATION NEXT
equipped + raw8 frame-0/frame-1 marker support  CONFIRMED — EV-271
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Raw55 Quick Causal Chain

Factual Troll/BlackTroll source:

```text
TrollFist
gEUseType_PhysicalFist / raw55
resting collision group5
```

```text
EV-264:
    native Quick contains both StatePosition 0 -> 1 and early raw55 5 -> 7

EV-265:
    early 5 -> 7 can be suppressed while StatePosition 0 -> 1 survives

EV-266:
    authored FIST can open 5 -> 7 and native cleanup works
    opening alone does not restore damage

EV-267:
    ClearTriggeredList after FIST opening restores damage on contact

EV-268:
    prior close-range divergence was marker timing, not proven geometry

EV-269:
    frame-1 FIST at StatePosition 0 can itself open/rearm raw55
    later native Quick still advances 0 -> 1 through natural 7 -> 7
    damage and native 7 -> 5 cleanup remain healthy

EV-270:
    later FIST delivery in the same Quick execution is visible
    current diagnostic one-shot bookkeeping prevents a second raw55 rearm
```

Permanent raw55 design remains intentionally unfrozen until repeated-marker semantics and remaining raw55 family ownership are resolved.

---

## Current Immediate Responsibility — Revised Work Implementation

Frozen authority:

```text
docs/COLLISION_RAW55_QUICK_REPEAT_FIST_REARM_PROBE.md
```

The stable marker engine cannot provide generic accepted-occurrence counters to raw55 because raw55 FIST returns before that bookkeeping.

For this diagnostics-only causal probe, `PhysicalFistProbe` may use only the smallest temporary sequence observation:

```text
first proven EV-269 pre-state FIST
+
first later eligible FIST dispatch in the same actor/source/C1
```

The controlled animation decision must contain exactly two FIST markers.

Causal delta:

```text
first FIST remains EV-269 unchanged
source remains group7
first later eligible FIST in same controlled two-FIST C1
    -> NO SetCollisionGroup
    -> one TouchDamage.ClearTriggeredList()
```

No frame/time/source-name/species/motion/action/phase/callback-rollback heuristic may be added.

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Build execution is NOT authorized for Work.

Normal Chat must review the exact diff before User build/runtime.

---

## Production Architecture Consequence — Later

The source contradiction reveals a real production-design requirement:

```text
raw55 repeated-marker support needs factual generic occurrence identity
before/perhaps independent of raw8-specific FIST source acceptance
```

Do not solve that by permanently duplicating counters in `PhysicalFistCollision`. The eventual production architecture must reconcile raw55 with the generic marker occurrence system without regressing raw8/equipped behavior.

This is not part of the current causal probe.

---

## Separate Later Raw55 Responsibilities

Not part of the current Work task:

```text
Power family ownership — marked raw55 Power currently leaks native collision
Normal/Sprint — still carry earlier whole-callback temporary experiments
production generic occurrence integration
permanent PhysicalFistCollision design/promotion
```

---

## Protected Boundaries

For the current repeated-FIST probe:

```text
Raw8FistCollision unchanged
stable FrameCollisionMarkers unchanged
CollisionLifecycleGuard semantics unchanged
CollisionSources unchanged
CollisionSourceOperations unchanged
EngineBridge hook ownership unchanged
native cleanup unchanged
first EV-269 FIST behavior unchanged
later native Quick 7 -> 7 unchanged
no species/name policy
no permanent PhysicalFistCollision yet
no custom/direct damage
no TriggerTarget / OnDamage
no StatePosition or SPU writes
no manual cleanup
no second-FIST collision-group request
no new hooks/timers/polling
```

---

## Still Paused

Until raw55 repeated-marker/family semantics are sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
