# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. `Script_FrameCollisionBehaviorTest` is the diagnostics-free behavior twin used to verify preprocessing/source separation during development. The eventual shipped plugin target remains `Script_G3AnimationBehaviors`; proven collision behavior must be deliberately promoted into permanent release-owned modules there, while `PhysicalFistProbe` and diagnostic scaffolding are excluded/removed.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_SPRINT_CALLBACK_BOUNDARY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_274_ONWARD.md` through **EV-279**; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier evidence remains in preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick is closed for the tested scope through EV-273:

```text
preserve original Quick callback/state progression
exact authored FIST can open exact RIGHT PhysicalFist/raw55
Quick tested contact requires ClearTriggeredList rearm
later authored FIST can rearm another contact in same C1
native cleanup returns exact RIGHT 7 -> 5
```

True raw55 Power is closed through EV-276:

```text
preserve original factual Action2 / Family POWER _AI_PowerAttack
suppress only premature exact scoped RIGHT raw55 5 -> 7
native StatePosition 0 -> 1 survives
authored FIST activates exact RIGHT raw55 5 -> 7
ClearTriggeredList=0
native damage returns
native cleanup returns exact RIGHT 7 -> 5
```

Raw55 Normal is closed through EV-279:

```text
EV-277: same original _AI_Attack invocation owns StatePosition 0 -> 1 + RIGHT raw55 5 -> 7
EV-278: exact premature 5 -> 7 can be suppressed while StatePosition 0 -> 1 survives
EV-279: authored FIST then opens exact RIGHT raw55 5 -> 7 at StatePosition1
        ClearTriggeredList=0
        native OnDamage returns
        native cleanup returns 7 -> 5
        C1 finalizes cleanly
```

Normal therefore needs no separate contact-rearm probe for the tested first authored-FIST contact. Do not generalize this no-rearm result to Quick.

Canonical runtime evidence is through **EV-279**. Recovery Lock remains **CLOSED**.

No permanent raw55 implementation is authorized yet.

---

## Closed / Current Collision Boundary

```text
C1-R1 lifecycle safety                         CLOSED — EV-206–EV-207
collision architecture verification            CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack equipped   CLOSED/PASS — EV-216–EV-244
raw8 FIST shared mechanism + controls           CLOSED/PASS through EV-271
raw8 Sprint                                     CLOSED/PASS — EV-251
native NPC equipped controls                    CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control               CLOSED/PASS — EV-259
fall-down logger boundary                       CLOSED — EV-260
BluntArrow/BluntBolt classification             CLOSED — EV-261
raw55 early callback causal ownership           CONFIRMED — EV-262
raw55 uniform whole-callback production gate    FAILED/REJECTED — EV-262
raw55 Quick mechanism                           CLOSED/PASS through EV-273
raw55 true Power mechanism                      CLOSED/PASS through EV-276
raw55 Normal mechanism                          CLOSED/PASS through EV-279
raw55 Sprint callback ownership                 CURRENT RESEARCH
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8 or across raw55 attack families without evidence.

---

## Current Frozen Responsibility — Raw55 Sprint Callback Ownership

Authority:

```text
docs/COLLISION_RAW55_SPRINT_CALLBACK_BOUNDARY_PROBE.md
```

Established facts entering this probe:

```text
factual Sprint = Action9 / Family SPRINT
Sprint is already factual at existing _AI_PowerAttack callback entry
raw8 Sprint is independently supported and must remain unchanged
raw55 Sprint is the only remaining family still under temporary whole-callback suppression
Power also uses _AI_PowerAttack, but Power's raw55 causal result must not be generalized to Sprint
```

Single question:

> When exact eligible marked raw55 Sprint is allowed to run its original `_AI_PowerAttack` exactly once, does that same invocation own native `StatePosition 0 -> 1` and the exact RIGHT PhysicalFist/raw55 `5 -> 7` transition, or does Sprint divide those responsibilities differently?

Frozen diagnostic shape:

```text
disable only temporary whole-callback raw55 Sprint suppression
add reentrancy-safe SprintCallbackObservation in PhysicalFistProbe
bracket the existing one original _AI_PowerAttack invocation
log CORE RAW55_SPRINT_CALLBACK_BOUNDARY
observe ordinary CORE COLLISION_GROUP independently
NO Sprint group suppression yet
NO Sprint FIST activation/rearm
NO ClearTriggeredList
NO StatePosition/SPU writes
NO custom damage or cleanup
Quick/Power/Normal closed research behavior unchanged
raw8 Sprint unchanged
```

Expected compound comparison shape if Sprint independently matches true Power/Normal:

```text
CORE COLLISION_GROUP ... TrollFist ... Requested=7 Before=5 After=7
CORE RAW55_SPRINT_CALLBACK_BOUNDARY ...
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->7
    NativeResult=1
```

This shape is not assumed. Any factual different result decides the next question.

Build execution is **not authorized for Work**.

---

## Current Runtime Artifact

EV-279:

```text
research/raw/2026.09.13_troll_raw55_normal_fist_activation.log
runtime upload commit e01eae6482b0d106d6825a2fc879cca184e7bcc8
implementation d1c9d6f39ece5b5b4f4228d3d46ded976e6ae21a
```

Four factual Normal C1s (8, 10, 14, 36) independently reproduce early suppression -> native StatePosition progression -> authored 5 -> 7 activation without clear -> native damage -> native 7 -> 5 cleanup -> clean finalization.

---

## Still Paused

Until Sprint raw55 ownership is sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO promotion/copy of PhysicalFistProbe into release code
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
