# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_POWER_CALLBACK_BOUNDARY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_269_ONWARD.md` through **EV-273**; prior raw55 causal evidence EV-262–EV-268 is in the preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick is closed for the tested scope through EV-273:

```text
frame-1 FIST can activate exact RIGHT PhysicalFist/raw55 5 -> 7
first FIST ClearTriggeredList rearms contact
native Quick later performs 7 -> 7 + StatePosition 0 -> 1
later FIST is delivered in the same C1
later FIST can ClearTriggeredList again while RIGHT remains group7
a second damaging contact can occur in the same Quick execution
native cleanup returns exact RIGHT 7 -> 5
```

EV-272's earlier repeat-intervention non-reach did not reproduce after an observability-only source change; retain it as provenance, not as evidence against the repeated rearm primitive.

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
raw55 true Power callback ownership             CURRENT RESEARCH
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Frozen Responsibility — True Raw55 Power Callback Boundary

Authority:

```text
docs/COLLISION_RAW55_POWER_CALLBACK_BOUNDARY_PROBE.md
```

Current factual baseline from the latest runtime:

```text
Actor=Troll
Script=_AI_PowerAttack
Action=2
Family=POWER
SuppressNative=0
RIGHT TrollFist / PhysicalFist/raw55 starts group5
native RIGHT 5 -> 7 occurs before authored FIST
FIST is delivered at StatePosition=1 while RIGHT is group7
native OnDamage occurs
native cleanup returns RIGHT 7 -> 5
C1 finalizes cleanly
```

Power is not currently part of `PhysicalFistProbe` suppression policy. Normal + Sprint remain the temporary suppression families.

Single question:

> Across the factual marked raw55 Power original `_AI_PowerAttack` invocation that opens RIGHT `5 -> 7`, what happens to StatePosition and the collision group?

The probe is **observation-only**. `PhysicalFistProbe` owns eligibility/snapshots/logging; `EngineBridge` may receive only the smallest diagnostic begin/end delegation around the already-owned original callback.

Target log:

```text
CORE RAW55_POWER_CALLBACK_BOUNDARY
```

No suppression, group mutation, `ClearTriggeredList`, StatePosition write, custom damage, new hook/RVA, timer, polling, or permanent module is authorized.

Build execution is **not authorized for Work**.

---

## Power / Normal / Sprint Boundary

```text
true Power: Action=2 / Family=POWER / native / can damage / CURRENT OBSERVATION TARGET
Normal:     Family=NORMAL / temporary whole-callback suppression remains active
Sprint:     Action=9 / Family=SPRINT / temporary whole-callback suppression remains active
```

Do not infer family from the `PowerAttack` motion filename. `_AI_PowerAttack` transports both true Power and Sprint; factual action selects the family.

---

## Still Paused

Until the remaining raw55 family/ownership decisions are sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint production redesign yet
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
