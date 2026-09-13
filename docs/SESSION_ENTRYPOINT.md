# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_REPEAT_FIST_ELIGIBILITY_OBSERVABILITY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_269_ONWARD.md` through **EV-272**; prior raw55 causal evidence EV-262–EV-268 is in the preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick first-FIST behavior remains proven:

```text
EV-269
    frame-1 FIST at StatePosition 0
    exact RIGHT PhysicalFist/raw55 5 -> 7
    one ClearTriggeredList
    later native Quick 7 -> 7
    StatePosition 0 -> 1
    damage on contact
    native 7 -> 5 cleanup
```

Repeated-FIST implementation exists at:

```text
a68361a48662f4236e2d742057aa64bde2d03346
```

Runtime artifact:

```text
research/raw/2026.09.13_troll_quick_fist_activation_frame_1_frame_15_test_2.log
upload commit 1d9b11a375bbc760dfd9b70ed977af19765228e5
```

EV-272 establishes:

```text
later frame-15 FIST is delivered
same Quick C1
StatePosition=1
RIGHT raw55 remains group7
BUT repeat-rearm CORE intervention log never appears
therefore second ClearTriggeredList never executes
```

User observes one damaging contact per Quick. This does NOT prove repeated `ClearTriggeredList()` failure because the intervention was never reached.

Canonical evidence is through **EV-272**.

A frozen diagnostics-only eligibility observability Work task is now active. No permanent raw55 implementation is authorized.

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
equipped + raw8 frame-0/frame-1 marker support  CONFIRMED — EV-271
raw55 repeated-FIST intervention eligibility    OPEN — EV-272
raw55 repeated-FIST rearm primitive             STILL UNTESTED
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Immediate Responsibility — Eligibility Observability

Frozen authority:

```text
docs/COLLISION_RAW55_QUICK_REPEAT_FIST_ELIGIBILITY_OBSERVABILITY_PROBE.md
```

Question:

```text
Which exact eligibility predicate rejects the delivered later raw55 Quick FIST?
```

The next Work task is observability-only inside `PhysicalFistProbe.cpp`.

Add one bounded marker-dispatch record:

```text
CORE RAW55_QUICK_REPEAT_FIST_ELIGIBILITY
```

Expose factual current/stored C1 and source identity, proof flags, marker scan counts, raw8 absence, Quick/state/group/use-type facts, plus `Eligible` and one stable `FirstFailedGate` token.

Do not mutate any behavior and do not add another collision/damage intervention.

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Build execution is NOT authorized for Work.

Normal Chat reviews the exact diff before User build/runtime.

---

## Power / Sprint Clarification

The EV-272 run's non-damaging animation named `...PowerAttack...` is factual:

```text
Action=9
Family=SPRINT
```

and the old temporary Sprint raw55 whole-callback suppression logs `SUPPRESS_NATIVE=1`.

Earlier damaging true Power evidence was:

```text
Action=2
Family=POWER
SuppressNative=0
```

Do not infer family from the animation filename alone. True raw55 Power ownership remains an unfinished later responsibility.

---

## Date Provenance Note

Several September 13 controls were accidentally named with `2026.09.12` filenames. Do not rename already-cited artifacts; the evidence ledger records their actual runtime date as September 13 while preserving filenames for provenance.

---

## Protected Boundaries

For the current eligibility observability probe:

```text
first EV-269 FIST behavior unchanged
current repeated-FIST intervention unchanged
ClearTriggeredList calls unchanged
SetCollisionGroup behavior unchanged
FrameCollisionMarkers unchanged
Raw8FistCollision unchanged
CollisionLifecycleGuard unchanged
CollisionSources unchanged
CollisionSourceOperations unchanged
EngineBridge unchanged
CMake unchanged
native Quick callback / 7 -> 7 / StatePosition progression / 7 -> 5 cleanup unchanged
Normal/Sprint/Power temporary raw55 behavior unchanged
```

Do not add:

```text
new ClearTriggeredList
new collision-group request
custom damage
state write
manual cleanup
new occurrence bookkeeping
frame/time heuristics
new hook/RVA/timer/polling
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
