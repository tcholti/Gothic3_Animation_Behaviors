# Raw55 PhysicalFist Normal Callback-Boundary Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic observation probe  
**Updated:** 2026-09-13

## Purpose

Answer one unresolved causal question before any permanent raw55 Normal behavior is designed:

> During an exact marked raw55 `Family=NORMAL` Hit, what changes across the original native `_AI_Attack` invocation that owns the old early RIGHT PhysicalFist/raw55 opening: StatePosition, collision group, or both?

This is a diagnostic observation probe. The earlier temporary whole-callback suppression for marked raw55 Normal must be disabled for this probe so the original native `_AI_Attack` can execute and be observed. The task must not otherwise intervene in Normal collision/contact behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.

---

## 1. Evidence Boundary

EV-262 established two relevant facts for marked raw55 Normal:

```text
native baseline:
    RIGHT TrollFist / PhysicalFist raw55 begins group5
    native Normal opens raw55 5 -> 7 before authored FIST
    native damage can occur while offensive
    native cleanup returns 7 -> 5

temporary whole-callback suppression:
    exact marked raw55 Normal callback is suppressed while RIGHT is group5
    old pre-marker 5 -> 7 disappears
    authored FIST is still reached with current UNSUPPORTED_MISSING_SOURCE behavior
    observed Normal damage disappears
    lifecycle remains clean in sampled Normal executions
```

That proved causal ownership of the premature opening at callback-family granularity, but it did **not** prove that whole `_AI_Attack` suppression is production-safe. In particular, it did not bracket the original Normal callback and determine whether the same invocation also owns required native StatePosition progression or another state responsibility.

Quick later proved exactly such compound ownership at `_AI_QuickAttack` (EV-264), and true Power proved the same pattern at `_AI_PowerAttack` (EV-274). Therefore Normal must be measured independently rather than inheriting either family's answer.

True Power is closed through EV-276 for the tested scope. Closed Quick and Power research behavior must not be altered by this task.

---

## 2. Single Probe Question

For an exact marked raw55 Normal Hit, allow the already-owned original `_AI_Attack` callback to execute normally and record state immediately before and immediately after each eligible native invocation.

Required observation fields:

```text
Actor
C1 generation
Action before -> after
AniPhase before -> after
StateTime before -> after
StatePosition before -> after
current motion before -> after
RIGHT source identity
RIGHT UseType
RIGHT collision group before -> after
same-C1 identity after call
same-RIGHT-source identity after call
native callback return value
```

The original native callback must execute exactly once.

No collision-group request is to be suppressed in this task once exact Normal observation is active. No authored-FIST activation or contact rearm is part of this task.

---

## 3. Exact Observation Eligibility

Observation is active only for an exact marked raw55 Normal Hit:

```text
FRAME_COLLISION_DIAGNOSTICS build
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
factual family == AttackFamily_Normal
Normal attack Hit eligible
matching current motion found
marker scan valid
marker present
at least one authored G3AB_COL_FIST
no RIGHT / LEFT / BOTH / OFF authored for this fixture
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
RIGHT source exists
RIGHT source UseType == gEUseType_PhysicalFist / raw55
```

Do **not** require RIGHT group5 for observation. Once the exact marked Normal execution is identified, later invocations in the same factual execution must remain observable if RIGHT has already become group7.

Do not gate by Troll/BlackTroll name, species, animation filename token, or inferred damaging limb.

---

## 4. Temporary Normal Suppression Disposition

The existing `PhysicalFistProbe` whole-callback suppression for marked raw55 Normal is temporary research scaffolding from EV-262, not production behavior.

For this probe only:

```text
Normal must no longer be an IsSuppressionFamily / whole-callback-suppressed family
Sprint remains under its existing temporary whole-callback suppression unchanged
Quick remains on its closed precise research path unchanged
Power remains on its closed EV-275/EV-276 precise research path unchanged
```

Removing Normal from the temporary suppression set is required so the original `_AI_Attack` can be observed. This is not a production-design decision and does not itself authorize permanent Normal behavior.

Do not delete historical Normal suppression diagnostics or rewrite EV-262 evidence merely because the active probe state advances.

---

## 5. Mandatory Modular Ownership

`EngineBridge` remains the sole `_AI_Attack` hook owner.

Its diagnostic-only responsibility is limited to:

```text
preserve existing EvaluateAttackCallback ownership evaluation
if the native Normal callback will execute, ask PhysicalFistProbe to begin observation
call the same original `_AI_Attack` exactly once
pass native result/post-call context back to PhysicalFistProbe
```

`PhysicalFistProbe` owns:

```text
removal of Normal from the temporary whole-callback suppression set
raw55 Normal observation eligibility
before snapshot
post-call snapshot
compact RAW55_NORMAL_CALLBACK_BOUNDARY diagnostic
```

Do not move Normal research policy/state into `EngineBridge`. Hook ownership remains transport only.

No permanent `PhysicalFistCollision` module is authorized in this task.

---

## 6. Protected Existing Behavior

Must remain unchanged:

```text
Sprint raw55 temporary whole-callback suppression
all closed raw55 Quick suppression/activation/rearm research behavior
all closed true-Power selective suppression + authored-FIST activation research behavior
raw8 FIST behavior
all equipped RIGHT/LEFT/BOTH/OFF behavior
FrameCollisionMarkers semantics
CollisionSources semantics
CollisionSourceOperations semantics
CollisionLifecycleGuard / C1-R1
AttackMotionRouting
native target/contact/damage
native cleanup
```

Normal is the only family whose temporary whole-callback suppression state changes, and only to restore the native callback for observation.

---

## 7. Forbidden Changes

Do not:

```text
whole-callback suppress Normal in the new observation path
selectively suppress a nested Normal group request yet
activate raw55 at authored FIST
ClearTriggeredList for Normal
write StatePosition
write SPU+0x164
use raw8 timing permission for raw55
accept/process raw55 FIST differently
change C1 lifecycle or repair policy
perform custom/direct damage
change target/contact logic
change Sprint behavior
change Quick behavior/research state
change Power behavior/research state
add species/name/filename policy
add hook/RVA/timer/polling/per-frame machinery
create permanent PhysicalFistCollision
change CMake/source-boundary semantics
```

This task answers only the callback-boundary ownership question.

---

## 8. Diagnostic Logging

Add one compact observation record:

```text
CORE RAW55_NORMAL_CALLBACK_BOUNDARY
```

Minimum shape:

```text
Actor=<...>
C1=<generation>
SameC1=<0|1>
SameRight=<0|1>
Action=<before>-><after>
Phase=<before>-><after>
StateTime=<before>-><after>
StatePosition=<before>-><after>
MotionBefore=<...>
MotionAfter=<...>
Right=<source>
RightUseType=55
RightGroup=<before>-><after>
NativeResult=<...>
OBSERVE_NATIVE=1
```

Do not add broad per-frame logging.

Existing ordinary `CORE COLLISION_GROUP`, marker, `CORE ONDAMAGE`, cleanup, and C1 lifecycle records remain the factual outcome evidence.

---

## 9. Expected Source Scope

Expected files:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

`EngineBridge.cpp` may receive only the smallest `#ifdef FRAME_COLLISION_DIAGNOSTICS` begin/end delegation around the existing original `_AI_Attack` call.

`PhysicalFistProbe` may remove Normal from the temporary suppression-family predicate and add the Normal observation state/helpers.

No CMake change should be required. A semantic need to modify permanent behavior modules is a contradiction and must be returned to Normal Chat instead of broadening the task.

---

## 10. Required Static Audit

Before publication verify:

```text
marked raw55 Normal original callback now executes exactly once
Normal no longer uses the EV-262 whole-callback suppression intervention
new logic only observes Normal native boundary
Sprint whole-callback suppression remains unchanged
Quick precise research behavior remains unchanged
Power precise research behavior remains unchanged
all new observation state is diagnostic-only
PhysicalFistProbe remains absent from Script_FrameCollisionBehaviorTest
EngineBridge contains transport/delegation only
no new hook/RVA
no collision-group mutation added for Normal
no ClearTriggeredList added for Normal
no StatePosition/SPU write added
Raw8FistCollision unchanged
FrameCollisionMarkers unchanged
CollisionLifecycleGuard unchanged
CollisionSourceOperations unchanged
CMake unchanged
```

Build execution is **not authorized for Work**.

---

## 11. Local Runtime Test

After independent Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest` and exercise marked Troll/BlackTroll attacks until at least one factual `Family=NORMAL` Hit is captured.

Preferred artifact:

```text
research/raw/2026.09.13_troll_raw55_normal_callback_boundary.log
```

The User does not need to identify Normal visually. Normal Chat will classify from the factual callback/ownership records.

Correlate:

```text
CORE ATTACK_OWNERSHIP Family=NORMAL
CORE RAW55_NORMAL_CALLBACK_BOUNDARY
CORE COLLISION_GROUP
G3AB_COL_FIST marker result
CORE ONDAMAGE
native cleanup
C1 finalization/repair
```

Incidental Quick/Power/Sprint traffic is acceptable but is not part of the causal result.

---

## 12. Interpretation

### A — compound ownership

If one original Normal invocation shows:

```text
StatePosition 0 -> 1
RightGroup    5 -> 7
SameC1=1
SameRight=1
```

then Normal matches the compound-ownership pattern already proven independently for Quick and Power. Whole-callback suppression is rejected as a Normal production mechanism; the next smallest question is selective exact `5 -> 7` suppression while preserving native progression.

### B — raw55 opening only

If:

```text
StatePosition unchanged
RightGroup    5 -> 7
```

then the observed invocation owns the physical opening but not the measured StatePosition transition. Do not immediately declare whole-callback suppression production-safe; first check whether the callback owns another required native responsibility visible in the bounded observation.

### C — progression only

If:

```text
StatePosition changes
RightGroup unchanged
```

then raw55 activation occurs elsewhere. Follow the factual opening path rather than suppressing the callback.

### D — neither changes

If neither changes across eligible original calls, the relevant mutation occurs through another invocation/context. Stop and inspect that route; do not add an intervention.

---

## 13. Stop Boundary

After one adequate runtime capture:

```text
Normal Chat analyzes committed evidence
-> promotes the result canonically
-> freezes the next smallest Normal causal question
```

Do not combine this task with Normal selective suppression, authored-FIST activation/rearm, Sprint redesign, permanent raw55 implementation, or release-module promotion.
