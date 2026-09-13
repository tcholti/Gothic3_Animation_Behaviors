# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. `Script_FrameCollisionBehaviorTest` is the diagnostics-free behavior twin used to verify preprocessing/source separation during development. The eventual shipped plugin target remains `Script_G3AnimationBehaviors`; proven collision behavior must be deliberately promoted into permanent release-owned modules there, while `PhysicalFistProbe` and diagnostic scaffolding are excluded/removed. A missing behavior-twin DLL in a local Release output directory after `--clean-first` plus a diagnostic-only target build does not mean the behavior target was removed from CMake.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_NORMAL_CALLBACK_BOUNDARY_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_274_ONWARD.md` through **EV-276**; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier raw55 causal evidence is in preceding ledgers  
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

True raw55 Power is closed through EV-276 for the tested scope:

```text
EV-274:
    same original factual Action2 / Family POWER _AI_PowerAttack invocation owns
    StatePosition 0 -> 1
    exact RIGHT raw55 5 -> 7

EV-275:
    suppress only the exact scoped premature RIGHT raw55 5 -> 7
    original callback still advances StatePosition 0 -> 1
    RIGHT remains group5
    no later native raw55 opening

EV-276:
    authored G3AB_COL_FIST at StatePosition1 requests exact RIGHT raw55 5 -> 7
    ordinary collision/lifecycle path observes the real offense request
    ClearTriggeredList=0
    native OnDamage returns
    native cleanup returns exact RIGHT 7 -> 5
    C1 finalizes cleanly without repair
```

Therefore tested true Power requires preservation of native callback/state progression plus delayed authored-frame physical activation; no Power-specific probe `ClearTriggeredList` is required for the tested first FIST contact.

Canonical evidence is through **EV-276**. Recovery Lock remains **CLOSED**.

No permanent raw55 implementation is authorized yet.

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
raw55 uniform whole-callback production gate    FAILED/REJECTED — EV-262
raw55 Quick mechanism                           CLOSED/PASS through EV-273
raw55 true Power callback compound ownership    CONFIRMED/CLOSED — EV-274
raw55 true Power group/state separability       CONFIRMED/PASS — EV-275
raw55 true Power authored-FIST activation       CONFIRMED/PASS — EV-276
raw55 Normal callback ownership                 CURRENT RESEARCH
raw55 Sprint callback ownership                 DEFERRED UNTIL NORMAL BOUNDARY CLOSES
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8 or across attack families without evidence.

---

## Current Frozen Responsibility — Raw55 Normal Callback Boundary

Authority:

```text
docs/COLLISION_RAW55_NORMAL_CALLBACK_BOUNDARY_PROBE.md
```

Single question:

> During an exact marked raw55 `Family=NORMAL` Hit, what changes across the original native `_AI_Attack` invocation that owns the old early RIGHT PhysicalFist/raw55 opening: StatePosition, collision group, or both?

EV-262 proved that temporary whole-callback suppression removes Normal's old pre-marker raw55 opening and observed damage, but it never proved what required native state work that callback may also perform. Quick and true Power later demonstrated exactly that kind of compound callback ownership. Normal must now be measured independently.

For this diagnostic observation:

```text
Normal temporary whole-callback suppression is disabled
original marked raw55 Normal _AI_Attack executes exactly once
PhysicalFistProbe brackets eligible native Normal invocation
NO selective group suppression yet
NO authored-FIST raw55 activation yet
NO ClearTriggeredList for Normal
Sprint temporary whole-callback suppression remains unchanged
Quick and Power precise research behavior remain unchanged
```

Build execution is **not authorized for Work**.

---

## Power / Normal / Sprint Boundary

```text
true Power: Action=2 / Family=POWER / tested mechanism closed through EV-276
Normal:     Family=NORMAL / prior whole-callback suppression is temporary research scaffolding; native callback-boundary observation current
Sprint:     Action=9 / Family=SPRINT / temporary whole-callback suppression remains active pending its own independent boundary research
```

Do not infer family from motion filename. `_AI_PowerAttack` transports both true Power and Sprint; factual action selects that family boundary.

Do not generalize Quick or Power activation/rearm details onto Normal or Sprint.

---

## Current Runtime Artifact

EV-276:

```text
research/raw/2026.09.13_troll_raw55_power_fist_activation.log
upload commit 83d2150defd967e379d3ae602f6a2936e941d1bd
implementation 0131f7a04d548f186ed9c8581e59e84a7b24b1f7
```

Two factual true-Power C1s independently show authored-frame `5 -> 7`, native damage, native `7 -> 5` cleanup, and clean finalization with `ClearTriggeredList=0` in the Power activation probe.

---

## Still Paused

Until remaining raw55 family/ownership decisions are sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint production redesign yet
NO promotion of PhysicalFistProbe into release code
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
