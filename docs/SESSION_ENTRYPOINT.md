# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_POWER_GROUP_SUPPRESSION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_274_ONWARD.md` through **EV-274**; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier raw55 causal evidence is in the preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick remains closed for the tested scope through EV-273:

```text
frame-1 FIST can activate exact RIGHT PhysicalFist/raw55 5 -> 7
first FIST ClearTriggeredList rearms contact
native Quick later performs 7 -> 7 + StatePosition 0 -> 1
later FIST is delivered in the same C1
later FIST can ClearTriggeredList again while RIGHT remains group7
a second damaging contact can occur in the same Quick execution
native cleanup returns exact RIGHT 7 -> 5
```

EV-274 now closes the true-Power callback-boundary question:

```text
factual true Power = Action=2 / Family=POWER
same original _AI_PowerAttack invocation:
    StatePosition 0 -> 1
    exact RIGHT PhysicalFist/raw55 5 -> 7
SameC1=1
SameRight=1
NativeResult=1
later FIST is delivered while RIGHT remains group7
native damage can occur
native cleanup returns RIGHT 7 -> 5
C1 finalizes cleanly
```

Therefore true Power has **compound callback ownership** at this boundary. Whole `_AI_PowerAttack` suppression is not a valid true-Power production mechanism because it would remove required native state progression together with the premature raw55 opening.

Canonical evidence is through **EV-274**. Recovery Lock remains **CLOSED**.

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
raw55 true Power callback compound ownership    CONFIRMED/CLOSED — EV-274
raw55 true Power group/state separability       CURRENT RESEARCH
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Frozen Responsibility — True Power Selective Group Suppression

Authority:

```text
docs/COLLISION_RAW55_POWER_GROUP_SUPPRESSION_PROBE.md
```

Single question:

> While the original factual true-Power `_AI_PowerAttack` callback executes normally, can only its exact nested RIGHT raw55 `Item_Equipped (5) -> Item_Attack (7)` request be suppressed while native StatePosition still advances `0 -> 1`, with no later raw55 opening or lifecycle divergence?

Expected decisive shape if separable:

```text
CORE RAW55_POWER_GROUP_SUPPRESSION ... SUPPRESS_GROUP=1
CORE RAW55_POWER_CALLBACK_BOUNDARY ... StatePosition=0->1 ... RightGroup=5->5
```

`PhysicalFistProbe` owns Power scope, identity, suppression policy and logging. `EngineBridge` remains the sole hook owner and transport layer; its existing diagnostic SetCollisionGroup delegation should be reused rather than expanded with feature policy.

No authored Power FIST activation/rearm is part of this task.

Build execution is **not authorized for Work**.

---

## Power / Normal / Sprint Boundary

```text
true Power: Action=2 / Family=POWER / callback compound ownership proven / selective group separability current
Normal:     Family=NORMAL / temporary whole-callback suppression remains active
Sprint:     Action=9 / Family=SPRINT / temporary whole-callback suppression remains active
```

Do not infer family from the `PowerAttack` motion filename. `_AI_PowerAttack` transports both true Power and Sprint; factual action selects the family.

Do not generalize EV-274 to Sprint merely because the transport callback is shared.

---

## Current Runtime Artifacts

Correct EV-274 build/runtime transaction:

```text
research/raw/2026.09.13_build log.txt
research/raw/2026.09.13_troll_raw55_power_callback_boundary_2.log
upload commit ab2522ae9d451e8663da95e324dd3621f051fd91
```

Earlier artifact:

```text
research/raw/2026.09.13_troll_raw55_power_callback_boundary.log
```

was generated from stale pre-probe local source and is retained only as provenance; it is not evidence about Power observer eligibility or callback ownership.

---

## Still Paused

Until the remaining raw55 family/ownership decisions are sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO authored Power FIST replacement yet
NO Normal/Sprint production redesign yet
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
