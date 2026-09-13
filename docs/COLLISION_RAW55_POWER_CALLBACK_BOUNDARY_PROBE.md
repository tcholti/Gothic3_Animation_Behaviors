# Raw55 PhysicalFist Power Callback-Boundary Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic observation probe  
**Updated:** 2026-09-13

## Purpose

Answer one unresolved causal question before any permanent raw55 Power behavior is designed:

> During a factual marked `Action=2 / Family=POWER` raw55 execution, what changes across the original native `_AI_PowerAttack` invocation that opens the RIGHT PhysicalFist/raw55 source: StatePosition, collision group, or both?

This is observation-only. It must not suppress Power, activate raw55, rearm contact, modify marker handling, or implement production behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.

---

## 1. Evidence Boundary

Canonical raw55 Quick research is closed through EV-273 for the tested scope. Do not reopen it in this task.

The latest runtime adds a clean factual true-Power baseline:

```text
Actor=Troll
Script=_AI_PowerAttack
Action=2
Family=POWER
MarkerPresent=1
FistMarkers=1
RequiredMask=0
Raw8Fist=<none>
SuppressNative=0
RIGHT TrollFist / UseType=55 starts group5
native RIGHT request 5 -> 7 occurs before authored FIST
FIST is delivered later at StatePosition=1 while RIGHT is group7
native OnDamage against PC_Hero occurs
native RIGHT cleanup 7 -> 5 occurs
C1 cleanup is fulfilled and finalizes without repair
```

Power is currently outside `PhysicalFistProbe` suppression policy. The current temporary suppression set remains Normal + Sprint only. Therefore this Power sample is native behavior, not a result of the raw55 suppression experiment.

The shared `_AI_PowerAttack` hook also transports factual Sprint/Action9. Family identity must remain action-based; motion filename alone is not authority.

---

## 2. Single Probe Question

Bracket the already-owned original `_AI_PowerAttack` call for factual raw55 `Family=POWER` only and record the native state immediately before and immediately after that invocation.

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
native callback return value
```

If practical without broadening the seam, also log whether current/stored actor and RIGHT source identity still match across the observation. No new persistent feature state is required.

The original native callback must execute exactly once.

---

## 3. Exact Observation Eligibility

Observation is active only for an exact marked factual raw55 Power Hit:

```text
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
factual family == AttackFamily_Power
factual action == gEAction_PowerAttack / Action 2
attack Hit eligible
matching current motion found
marker scan valid
marker present
at least one authored G3AB_COL_FIST
no RIGHT / LEFT / BOTH / OFF marker authored for this fixture
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
RIGHT source exists
RIGHT source UseType == gEUseType_PhysicalFist / raw55
```

Do **not** require RIGHT group5 for observation. Once the exact marked Power execution is identified, an invocation must remain observable if RIGHT has already become group7.

Do not gate by Troll/BlackTroll name, species, PowerAttack filename token, or inferred damaging limb.

---

## 4. Mandatory Modular Ownership

`EngineBridge` remains the sole `_AI_PowerAttack` hook owner.

Its diagnostic-only responsibility is limited to:

```text
resolve factual Power vs Sprint family from action
preserve existing EvaluateAttackCallback behavior
if native Power callback will execute, ask PhysicalFistProbe to begin observation
call the same original native callback exactly once
pass native result/post-call context back to PhysicalFistProbe
```

`PhysicalFistProbe` owns:

```text
raw55 Power observation eligibility
before snapshot
post-call snapshot
compact RAW55_POWER_CALLBACK_BOUNDARY diagnostic
```

Do not place Power research policy/state inside `EngineBridge`. Shared hook ownership is transport, not feature ownership.

No new permanent module is authorized in this task.

---

## 5. Protected Existing Behavior

Must remain unchanged:

```text
raw55 Power native behavior and SuppressNative=0
Normal raw55 temporary whole-callback suppression
Sprint raw55 temporary whole-callback suppression
all closed raw55 Quick behavior/probes/interventions
first/repeated Quick ClearTriggeredList behavior
raw8 FIST behavior
all equipped RIGHT/LEFT/BOTH/OFF behavior
FrameCollisionMarkers semantics
CollisionSources semantics
CollisionSourceOperations semantics
CollisionLifecycleGuard/C1-R1
AttackMotionRouting
native target/contact/damage
native cleanup
```

No source mutation is authorized by this probe.

---

## 6. Forbidden Changes

Do not:

```text
suppress the true Power callback
suppress a nested Power collision-group request
set raw55 group7 or group5
ClearTriggeredList
write StatePosition
write SPU+0x164
use raw8 timing permission
accept/process raw55 FIST differently
change C1 lifecycle or repair policy
perform custom damage
change target/contact behavior
add species/name policy
add animation-name classification
add hook/RVA/timer/polling/per-frame machinery
create production PhysicalFistCollision
```

This task is observation only.

---

## 7. Expected Source Scope

Expected implementation files:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

`EngineBridge.cpp` may receive only the smallest `#ifdef FRAME_COLLISION_DIAGNOSTICS` begin/end delegation around the original factual Power call.

No CMake change should be required because `PhysicalFistProbe` is already diagnostic-only. A semantic need to modify production feature modules is a contradiction and must be returned to Normal Chat.

---

## 8. Required Static Audit

Before publication verify:

```text
true Power remains unsuppressed
Normal/Sprint suppression meaning is unchanged
Sprint/Action9 is not observed as Power
Power original callback is called exactly once
all new observation logic is diagnostic-only
PhysicalFistProbe remains absent from behavior target
EngineBridge contains transport/delegation only
no new hook/RVA
no collision-group mutation added
no ClearTriggeredList added
no StatePosition write added
Raw8FistCollision unchanged
FrameCollisionMarkers unchanged
CollisionLifecycleGuard unchanged
CollisionSourceOperations unchanged
```

Build execution is **not authorized for Work**.

---

## 9. Local Runtime Test

After independent Normal Chat review, User + Normal Chat build/deploy `Script_FrameCollisionTest` locally and exercise several factual Troll/BlackTroll `Action=2 / Family=POWER` attacks using the existing marked FIST asset.

Target tag:

```text
CORE RAW55_POWER_CALLBACK_BOUNDARY
```

Correlate the boundary record with existing `CORE ATTACK_OWNERSHIP`, `CORE COLLISION_GROUP`, marker, `CORE ONDAMAGE`, cleanup, and C1 records.

Normal and Quick testing is not required unless a convenient sanity control is needed. Sprint must not be mistaken for Power.

---

## 10. Interpretation

If the same native Power invocation shows:

```text
StatePosition 0 -> 1
RightGroup    5 -> 7
```

then Power, like Quick, has compound callback ownership at this boundary. Whole-callback suppression is not a viable production ownership mechanism; the next question must be whether the physical group-opening request is separately suppressible while preserving native progression.

If:

```text
StatePosition unchanged
RightGroup    5 -> 7
```

then that invocation owns the raw55 opening but not the observed StatePosition progression. Do not yet assume whole-callback suppression is safe; first identify whether the callback owns any other required native responsibility.

If:

```text
StatePosition changes
RightGroup unchanged
```

then the callback owns native progression while raw55 activation occurs elsewhere. Follow the actual activation path rather than suppressing the callback.

If neither changes across observed eligible original calls, the opening/progression is downstream or occurs through another invocation/context. Stop and inspect that factual path; do not add an intervention.

---

## 11. Stop Boundary

After one adequate runtime capture:

```text
Normal Chat analyzes exact Power callback-boundary evidence
-> promotes the result canonically
-> chooses the next smallest causal question
```

Do not combine this step with Power suppression, authored-FIST activation, repeated rearm, Normal/Sprint redesign, or permanent raw55 implementation.
