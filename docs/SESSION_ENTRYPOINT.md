# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_POWER_FIST_ACTIVATION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_274_ONWARD.md` through **EV-275**; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier raw55 causal evidence is in preceding ledgers  
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

True raw55 Power is now closed through EV-275 for callback ownership and early-group/state separability:

```text
factual true Power = Action=2 / Family=POWER
EV-274:
    same original _AI_PowerAttack invocation owns
    StatePosition 0 -> 1
    exact RIGHT raw55 5 -> 7
EV-275:
    suppress only exact scoped native RIGHT raw55 5 -> 7
    original callback still returns StatePosition 0 -> 1
    RIGHT remains 5 -> 5
    no later raw55 opening
    FIST still arrives at StatePosition=1 with RIGHT group5
    no Power damage
    C1 finalizes with no offense obligation or repair
```

Therefore true Power's required state progression and premature physical opening are **separable**. Whole `_AI_PowerAttack` suppression remains rejected.

Canonical evidence is through **EV-275**. Recovery Lock remains **CLOSED**.

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
raw55 true Power group/state separability       CONFIRMED/PASS — EV-275
raw55 true Power authored-FIST activation       CURRENT RESEARCH
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Frozen Responsibility — True Power Authored-FIST Activation

Authority:

```text
docs/COLLISION_RAW55_POWER_FIST_ACTIVATION_PROBE.md
```

Single question:

> After the proven EV-275 selective early-group suppression preserves native Power `StatePosition 0 -> 1` while RIGHT remains raw55 group5, can the authored `G3AB_COL_FIST` event itself request the exact RIGHT PhysicalFist/raw55 source `5 -> 7` at marker time while Gothic retains ownership of contact/damage/cleanup?

Important isolation rule:

```text
activate exact RIGHT raw55 5 -> 7 at FIST time only
NO ClearTriggeredList in this probe
```

This keeps physical activation separate from contact/rearm. If group7 appears but damage does not return, the next causal question is rearm, not custom damage.

`PhysicalFistProbe` owns the EV-275 suppression proof, same actor/source/C1 validation, exact Power/FIST eligibility, one-shot activation decision, and logging. `EngineBridge` already provides the marker delegation seam and should remain unchanged.

Build execution is **not authorized for Work**.

---

## Power / Normal / Sprint Boundary

```text
true Power: Action=2 / Family=POWER / compound ownership + group/state separability proven / authored FIST activation current
Normal:     Family=NORMAL / temporary whole-callback suppression remains active
Sprint:     Action=9 / Family=SPRINT / temporary whole-callback suppression remains active
```

Do not infer family from the `PowerAttack` motion filename. `_AI_PowerAttack` transports both true Power and Sprint; factual action selects the family.

Do not generalize EV-274/EV-275 to Sprint merely because the transport callback is shared.

---

## Current Runtime Artifact

EV-275:

```text
research/raw/2026.09.13_troll_raw55_power_group_suppression.log
upload commit edc71a113381c0551ce72cfe3f38a1f22c363bb7
implementation 9fdea8a857faf23eefa873b3792bb8da37bf8288
```

Two factual true-Power C1s independently show the decisive PASS shape.

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
