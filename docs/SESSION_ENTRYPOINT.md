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
Current frozen probe: `docs/COLLISION_RAW55_NORMAL_GROUP_SUPPRESSION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_274_ONWARD.md` through **EV-277**; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier raw55 causal evidence is in preceding ledgers  
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

Raw55 Normal callback ownership is closed through EV-277:

```text
factual marked Normal = Action1 / Family NORMAL / _AI_Attack
same original callback invocation owns both:
    StatePosition 0 -> 1
    exact RIGHT raw55 5 -> 7
repeated independently in C1=33, 40, 42, 46
native damage occurs while offensive
native cleanup returns exact RIGHT 7 -> 5
whole-callback Normal suppression is rejected
```

The selective Normal group-suppression implementation is now landed and independently reviewed:

```text
implementation cf89f5ef55dcf89e322672babfee2bc30f3074ab
Normal Chat source review PASS
only PhysicalFistProbe.cpp/.h changed
EngineBridge unchanged
build NOT RUN yet
runtime evidence NOT YET CAPTURED
```

Canonical runtime evidence remains through **EV-277**. Recovery Lock remains **CLOSED**.

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
raw55 Normal group/state separability           IMPLEMENTED / REVIEWED / RUNTIME PENDING
raw55 Sprint callback ownership                 DEFERRED UNTIL NORMAL BOUNDARY CLOSES
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8 or across attack families without evidence.

---

## Current Frozen Responsibility — Raw55 Normal Group/State Separability

Authority:

```text
docs/COLLISION_RAW55_NORMAL_GROUP_SUPPRESSION_PROBE.md
```

Implementation already reviewed PASS:

```text
cf89f5ef55dcf89e322672babfee2bc30f3074ab
```

Single runtime question:

> With the original marked raw55 Normal `_AI_Attack` callback still executing exactly once, can only its exact scoped RIGHT PhysicalFist/raw55 `5 -> 7` request be suppressed while native `StatePosition 0 -> 1` still occurs, with no later raw55 activation or lifecycle divergence?

Implemented diagnostic shape:

```text
original Normal callback remains enabled
reentrancy-safe exact actor + RIGHT source + C1 Normal scope
suppress only exact scoped raw55 group5 -> requested group7
keep existing Normal callback-boundary logging
NO authored-FIST activation yet
NO ClearTriggeredList for Normal
NO StatePosition/SPU writes
Sprint temporary whole-callback suppression unchanged
Quick and Power precise research behavior unchanged
```

Next action is local build/deploy/runtime by User + Normal Chat. Do not launch another Work task before this runtime evidence transaction closes.

Because the immediately preceding Normal test had one stale-live-DLL incident, verify the newly built `Script_FrameCollisionTest.dll` is actually copied into the game before interpreting runtime.

Preferred artifact:

```text
research/raw/2026.09.13_troll_raw55_normal_group_suppression.log
```

Expected decisive PASS shape:

```text
CORE RAW55_NORMAL_GROUP_SUPPRESSION
BeforeGroup=5
RequestedGroup=7
SUPPRESS_GROUP=1

CORE RAW55_NORMAL_CALLBACK_BOUNDARY
SameC1=1
SameRight=1
StatePosition=0->1
RightGroup=5->5
NativeResult=1
```

---

## Power / Normal / Sprint Boundary

```text
true Power: Action=2 / Family=POWER / tested mechanism closed through EV-276
Normal:     Action=1 / Family=NORMAL / EV-277 compound ownership closed / selective separability implementation awaiting runtime
Sprint:     Action=9 / Family=SPRINT / temporary whole-callback suppression remains active pending independent boundary research
```

Do not infer family from motion filename. `_AI_PowerAttack` transports both true Power and Sprint; factual action selects that family boundary.

Do not generalize Quick or Power activation/rearm details onto Normal or Sprint.

---

## Current Runtime Artifact

EV-277 valid runtime:

```text
research/raw/2026.09.13_troll_raw55_normal_callback_boundary_2.log
upload commit 031d2be6ea6b0ef0972cbed7d66d3a5b045a89e6
implementation 7d6fb67dd60937a64b68d571a5cd4dbc7eafe7bd
```

The earlier `research/raw/2026.09.13_troll_raw55_normal_callback_boundary.log` is stale-deployment provenance evidence only.

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
