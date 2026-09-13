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
Current frozen probe: `docs/COLLISION_RAW55_NORMAL_FIST_ACTIVATION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_274_ONWARD.md` through **EV-278**; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier raw55 causal evidence is in preceding ledgers  
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

True raw55 Power remains closed through EV-276 for the tested scope:

```text
preserve original factual Action2 / Family POWER callback
suppress only premature exact RIGHT raw55 5 -> 7
native StatePosition 0 -> 1 survives
authored FIST later activates exact RIGHT raw55 5 -> 7
ClearTriggeredList=0
native damage returns
native cleanup returns exact RIGHT 7 -> 5
```

Raw55 Normal is now closed through EV-278 for callback ownership + early group/state separability:

```text
EV-277:
    factual marked Normal = Action1 / Family NORMAL / _AI_Attack
    same original callback invocation owns both:
        StatePosition 0 -> 1
        exact RIGHT raw55 5 -> 7
    whole-callback Normal suppression rejected

EV-278:
    seven factual Normal C1s suppress exact scoped premature RIGHT raw55 5 -> 7
    same original callback still advances StatePosition 0 -> 1
    RIGHT remains group5
    completed samples stay group5 through authored FIST
    stable raw55 FIST remains UNSUPPORTED_MISSING_SOURCE
    no Normal damage from the suppressed physical source
    completed C1s finalize with no offense obligation or repair
```

Canonical runtime evidence is through **EV-278**. Recovery Lock remains **CLOSED**.

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
raw55 Normal callback compound ownership        CONFIRMED/CLOSED — EV-277
raw55 Normal group/state separability           CONFIRMED/PASS — EV-278
raw55 Normal authored-FIST activation           CURRENT RESEARCH
raw55 Sprint callback ownership                 DEFERRED UNTIL NORMAL BOUNDARY CLOSES
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8 or across attack families without evidence.

---

## Current Frozen Responsibility — Raw55 Normal Authored-FIST Activation

Authority:

```text
docs/COLLISION_RAW55_NORMAL_FIST_ACTIVATION_PROBE.md
```

Single question:

> With EV-278 selective early Normal raw55 suppression preserved and the original `_AI_Attack` callback still running normally, can the authored `G3AB_COL_FIST` event itself request the exact RIGHT PhysicalFist/raw55 source `5 -> 7` at `StatePosition=1`, with Gothic retaining contact/damage/cleanup ownership?

Frozen diagnostic shape:

```text
preserve EV-278 exact early Normal 5 -> 7 suppression
record proof only when that exact suppression occurs
at later authored FIST require same actor + exact RIGHT source + same C1
require factual Action1 / Family NORMAL Hit
require StatePosition=1 and RIGHT still group5
stable marker result remains UNSUPPORTED_MISSING_SOURCE
request exact RIGHT raw55 5 -> 7 once through ordinary setter
NO ClearTriggeredList for Normal in this probe
NO custom damage
NO StatePosition/SPU writes
NO manual cleanup compensation
Sprint temporary whole-callback suppression unchanged
Quick and Power closed research behavior unchanged
```

The purpose is to isolate physical activation from contact rearm. Power proved activation alone sufficient in its tested context; Quick required rearm. Normal must be tested independently.

Build execution is **not authorized for Work**.

---

## Power / Normal / Sprint Boundary

```text
true Power: Action=2 / Family=POWER / tested mechanism closed through EV-276
Normal:     Action=1 / Family=NORMAL / ownership EV-277 + separability EV-278 / authored-FIST activation current
Sprint:     Action=9 / Family=SPRINT / temporary whole-callback suppression remains active pending independent boundary research
```

Do not infer family from motion filename. `_AI_PowerAttack` transports both true Power and Sprint; factual action selects that family boundary.

Do not generalize Quick or Power activation/rearm details onto Normal or Sprint.

---

## Current Runtime Artifact

EV-278:

```text
research/raw/2026.09.13_troll_raw55_normal_group_suppression.log
upload commit 3bf12e61e0d5045c72b61849f0d0742869c538f0
implementation cf89f5ef55dcf89e322672babfee2bc30f3074ab
```

Seven factual Normal C1s independently prove early-group/state separability. C1=18 is interrupted when the User damages the Troll and is used only for the immediate separability boundary; completed Normal C1s independently preserve group5 through authored FIST and finalize cleanly without offense obligation or repair.

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
