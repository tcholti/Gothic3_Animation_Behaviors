# Gothic 3 Animation Behaviors — RAW55 Normal Pre-State FIST Activation Probe

**Status:** FROZEN DIAGNOSTIC CONTRACT  
**Date:** 2026-09-15  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Close the Normal marker-ordering gap exposed by EV-283 before permanent raw55 architecture is designed.

The existing Normal raw55 research path was proven for the post-state ordering:

```text
native Normal callback attempts RIGHT raw55 5 -> 7
selective gate suppresses only that physical opening
native StatePosition still advances 0 -> 1
authored FIST later arrives at StatePosition 1
probe opens exact RIGHT raw55 5 -> 7
ClearTriggeredList=0
native damage can occur
native cleanup returns 7 -> 5
```

EV-283 shows that valid authored Normal FIST can also arrive earlier, while `StatePosition=0`, before the Normal early-suppression proof exists. The current diagnostic activation path ignores that first marker because it requires the later suppression proof and `StatePosition==1`; a second FIST at SP1 then becomes the first probe-owned activation.

This probe asks whether the **first legitimate authored Normal FIST at SP0 can itself own the physical raw55 opening** while Gothic retains ownership of later Normal callback progression, contact/damage, and cleanup.

This is not a production implementation.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: EV-269 as the Quick pre-state precedent, EV-279 for Normal first-contact activation without triggered-list clearing, and EV-283 for the newly exposed Normal SP0 ordering.

---

## 1. Single Causal Question

For an exact marked factual raw55 Normal execution whose authored `G3AB_COL_FIST` arrives while the current C1 is valid and `StatePosition==0`, before Normal has produced its ordinary early `5 -> 7` request / suppression proof:

> Is one immediate exact RIGHT PhysicalFist/raw55 `Item_Equipped/group5 -> Item_Attack/group7` request at that authored FIST sufficient to establish the authored collision window, **without `TouchDamage.ClearTriggeredList()`**, while allowing the untouched original Normal callback to perform its later native StatePosition progression and native cleanup?

Only that variable changes.

The causal target is:

```text
authored FIST at SP0:
    exact RIGHT raw55 5 -> 7
    ClearTriggeredList = 0

later original Normal callback:
    remains enabled
    native state progression remains native
    its own group7 request is observed, not replaced

then Gothic owns:
    contact / damage outcome
    ordinary 7 -> 5 cleanup
```

---

## 2. Why `ClearTriggeredList()` Is Forbidden In This Step

Quick EV-269 required one triggered-list clear for its delayed/pre-state raw55 contact path.

Normal is not allowed to inherit that operation by analogy. EV-279 already proved that, for the tested post-state Normal authored opening, exact RIGHT raw55 `5 -> 7` produced native first-contact damage with:

```text
ClearTriggeredList=0
```

Therefore this probe must test **physical pre-state activation alone**.

If the source opens successfully but contact/damage does not occur, that is evidence for a separate Normal pre-state contact/rearm question. Do not add a clear in the same implementation.

---

## 3. Stable Marker Boundary Must Remain Unchanged

`FrameCollisionMarkers::ProcessMarker()` remains unchanged.

Raw55 FIST remains unsupported by the stable raw8 resolver and may continue to report:

```text
MarkerResult_UnsupportedMissingSource
```

The diagnostic intervention occurs only after the stable marker result exists.

Do not:

```text
accept raw55 through ProcessMarker
change/generalize ResolveFistCollisionSource
call Raw8FistCollision for raw55
change authored occurrence semantics
reinterpret FIST as RIGHT
```

---

## 4. Exact Pre-State Eligibility

At the existing diagnostics-only raw55 marker delegation, permit the Normal pre-state intervention only when **all** are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
actor/instance valid
valid current C1 generation
markerOpcode == FIST
result.opcode == FIST
stable result == UNSUPPORTED_MISSING_SOURCE
factual Action == gEAction_Attack / 1
current attack ownership is Family=NORMAL and Hit eligible
matching current motion found
marker scan valid
marker present
>= 1 authored FIST
no RIGHT / LEFT / BOTH / OFF markers
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
factual current RIGHT source exists
result/current RIGHT source identity matches
RIGHT UseType == gEUseType_PhysicalFist / raw55
RIGHT current group == Item_Equipped / 5
StatePosition == 0
no Normal pre-state intervention already used for this exact actor + C1 + RIGHT source
```

Do **not** require the EV-278/EV-279 Normal early-suppression proof. EV-283 demonstrates that the marker can legitimately precede that proof.

No species, actor-name, motion-prefix, filename, timer, or visual-attack policy.

The temporary intervention identity must be scoped to:

```text
actor instance
+ C1 generation
+ exact factual RIGHT source instance
```

and may be used once for this causal probe.

---

## 5. Exact Diagnostic Intervention

For the eligible SP0 Normal FIST, exactly once:

```text
mark Normal pre-state intervention used
capture GroupBefore
rightSource.SetCollisionGroup(Item_Attack / 7)
capture GroupAfter
```

Use the ordinary setter path so the existing `EngineBridge` SetCollisionGroup transport and `CollisionLifecycleGuard` observe the real physical request and real offense obligation.

Do **not** use `CollisionSourceOperations::ActivateOrRearm()` because it also calls `ClearTriggeredList()`.

This probe must issue:

```text
ClearTriggeredList = 0
```

and must not call custom damage, `TriggerTarget`, or `OnDamage`.

---

## 6. Later Native Normal Callback — Preserve and Observe

The original `_AI_Attack` callback must execute normally exactly as before.

After a successful pre-state authored opening, the later native Normal collision request may reasonably be observed as:

```text
requested group7
before group7
result group7
```

rather than the earlier EV-278 shape:

```text
requested group7
before group5
[suppressed]
group remains5
```

That is expected: once the authored marker has already opened the source, the later native request is no longer a premature `5 -> 7` opening.

Do **not** broaden the Normal suppression rule to hide or suppress a native `7 -> 7` request.

Do **not** manufacture an EV-278 suppression proof for this execution merely to satisfy the older post-state activation path.

The authoritative questions are:

```text
Did authored SP0 FIST physically open exact RIGHT 5 -> 7?
Did ClearTriggeredList remain unused by this probe?
Did the original Normal callback still advance native StatePosition 0 -> 1?
Did native contact/damage occur after the authored opening when geometry contacted?
Did Gothic later clean the exact source 7 -> 5?
Did the C1 finalize without terminal repair/lifecycle issue?
```

If the later native callback instead causes unexpected source closure/reopening or loses StatePosition progression, treat that as a contradiction and stop. Do not compensate in this probe.

---

## 7. Relationship to Existing Normal Post-State Path

The existing EV-279 post-state activation path remains unchanged for executions where:

```text
native early 5 -> 7 request occurs first
that exact request is selectively suppressed
native StatePosition advances 0 -> 1
FIST later arrives while RIGHT remains group5
same-C1 suppression proof exists
```

For the new pre-state ordering:

```text
FIST opens raw55 first at SP0
there is no prior suppression proof
later native callback progresses naturally
```

One execution must not receive both a new Normal pre-state opening and the older post-state one-shot activation. With the pre-state source already group7 and no prior `5 -> 7` suppression proof, the old post-state path should remain ineligible naturally; preserve that separation rather than adding compensating state mutations.

---

## 8. Modular Ownership

`EngineBridge` remains the sole hook owner and transport layer.

The existing marker delegation and SetCollisionGroup hook are already sufficient. No new bridge seam is expected.

`PhysicalFistProbe` owns all temporary Normal pre-state research policy/state:

```text
exact eligibility
actor/C1/RIGHT-source identity
one-shot causal intervention state
exact raw55 group request
compact diagnostic logging
```

Do not move this policy/state into `EngineBridge`, `FrameCollisionMarkers`, `CollisionLifecycleGuard`, or a production feature module.

---

## 9. Diagnostic Logging

Keep all existing Normal/raw55 diagnostics.

Add one compact record only for an actual pre-state intervention:

```text
CORE RAW55_NORMAL_PRESTATE_FIST_PROBE
```

Include at minimum:

```text
Actor
C1
Action
StatePosition
StateTime
Right
RightUseType
GroupBefore
RequestedGroup
GroupAfter
ClearTriggeredList=0
PRESTATE_FIST=1
```

Existing marker result, `CORE COLLISION_GROUP`, Normal callback-boundary, `CORE ONDAMAGE`, and C1 lifecycle records remain factual outcome evidence.

---

## 10. Protected / Forbidden Boundary

Preserve unchanged:

```text
existing Normal selective early group suppression
existing Normal post-state FIST activation probe
original Normal callback exactly once
closed Quick behavior/research paths
closed true-Power behavior/research paths
closed Sprint first-contact behavior/research paths
raw8 FIST
FrameCollisionMarkers semantics
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations semantics
AttackMotionRouting
all equipped RIGHT / LEFT / BOTH / OFF behavior
```

Do not add or change:

```text
ClearTriggeredList for this Normal pre-state probe
whole Normal callback suppression
custom/direct damage
StatePosition write
SPU+0x164 write
manual cleanup compensation
raw8 timing permission
new hook / RVA / timer / polling / per-frame scan
species/name/filename policy
permanent PhysicalFistCollision
Power/Sprint/Quick repeat-FIST behavior
Normal repeat-FIST behavior
production promotion
```

No permanent raw55 architecture is authorized by this probe.

---

## 11. Expected Source Scope

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

If the header does not need a public declaration, a `.cpp`-only change is preferable.

No `EngineBridge.cpp`, CMake, stable-marker, lifecycle, or production-module change is expected.

If a real source/API contradiction prevents this bounded implementation, stop and report it rather than broadening scope.

---

## 12. Required Static Audit

Before publication verify:

```text
pre-state path requires exact Action1 / Family NORMAL / Hit
pre-state path requires valid exact actor + C1 + current RIGHT raw55 source
StatePosition 0 required
RIGHT group5 required before intervention
ordinary SetCollisionGroup path used
ClearTriggeredList not called by the new intervention
original Normal callback remains enabled and unchanged
existing Normal post-state suppression/activation path remains intact
no manufactured suppression proof for pre-state execution
no StatePosition write
no custom damage / cleanup
Quick/Power/Sprint/raw8 unchanged
FrameCollisionMarkers unchanged
CollisionLifecycleGuard unchanged
EngineBridge unchanged if existing delegation is sufficient
no new hook/RVA/CMake change
```

Build execution is **not authorized** by this contract.

---

## 13. Local Runtime Test

After independent Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest`.

Preferred artifact:

```text
research/raw/2026.09.15_troll_raw55_normal_prestate_fist.log
```

Use the current two-FIST Troll fixture from EV-283 because it already produces factual Normal executions where the first FIST arrives at SP0. Incidental Quick/Power/Sprint traffic is harmless and useful as regression context.

Minimum useful evidence is one or more factual `Family=NORMAL / Action1` executions with:

```text
FIST #1 at StatePosition 0
RIGHT PhysicalFist/raw55 group5
```

Correlate each eligible C1 through:

```text
stable authored FIST marker/result
CORE RAW55_NORMAL_PRESTATE_FIST_PROBE
CORE COLLISION_GROUP
later Normal callback boundary / StatePosition progression
CORE ONDAMAGE
native 7 -> 5 cleanup
C1 finalization / repair status
```

User should also report whether the first physical swing associated with the early marker visibly damages when contact occurs. A miss is not by itself failure if geometry does not contact; the log decides whether the authored opportunity existed.

---

## 14. Interpretation

### A — pre-state activation alone works

```text
FIST at SP0 performs real exact RIGHT 5 -> 7
ClearTriggeredList=0
original Normal callback later advances StatePosition 0 -> 1
native damage can occur after authored opening
native cleanup returns 7 -> 5
C1 closes without terminal repair
```

Conclusion: Normal first-marker ownership can begin at SP0 and does not require the later suppression proof. Preserve native callback/state progression. No Normal pre-state triggered-list operation is justified.

### B — 5 -> 7 works but no damage despite real contact opportunity

Physical pre-state ownership is proven, but contact eligibility differs from the already-proven post-state Normal path. The next question becomes one separate exact contact/rearm intervention. Do not infer Quick's `ClearTriggeredList()` automatically.

### C — later native StatePosition progression diverges

Stop. Pre-state physical ownership interacts with native Normal progression and requires causal analysis before any production design.

### D — cleanup/lifecycle diverges

Stop. Do not normalize terminal repair into the feature.

### E — authored request fails to become group7

The pre-state source-mutation boundary is unresolved. Do not compensate elsewhere.

---

## Stop Boundary

After one adequate runtime capture, Normal Chat closes this evidence transaction before any next source change.

Do not combine this task with:

```text
non-Quick repeat-FIST research
Sprint Action9 -> Action2 repeat ownership
permanent raw55 architecture
New Balance 0.7 final integration regression
Raise / speed-control work
```
