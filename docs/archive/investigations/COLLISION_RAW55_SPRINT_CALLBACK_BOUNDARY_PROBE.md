# Raw55 PhysicalFist Sprint Callback-Boundary Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-13

## Purpose

Answer the remaining raw55 family-ownership question after Quick is closed through EV-273, true Power through EV-276, and Normal through EV-279:

> For a factual marked raw55 Sprint execution (`Action=9 / Family=SPRINT`) transported through the existing `_AI_PowerAttack` hook, what does one original native callback invocation actually own? In particular, does that same invocation advance native `StatePosition 0 -> 1` and perform the exact RIGHT PhysicalFist/raw55 `Item_Equipped (5) -> Item_Attack (7)` transition?

This is a diagnostic-only observation. It is not Sprint production raw55 behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_274_ONWARD.md` through EV-279, plus the established raw8 Sprint transport result in EV-251.

---

## 1. Evidence Boundary

The current raw55 research state is deliberately family-specific:

```text
Quick:
    whole callback suppression rejected
    native StatePosition progression separated from premature raw55 opening
    authored FIST activation + exact contact rearm required in tested path
    closed through EV-273

true Power / Action2:
    same original _AI_PowerAttack invocation owns StatePosition 0 -> 1 + RIGHT raw55 5 -> 7
    selective 5 -> 7 suppression preserves StatePosition progression
    authored FIST activation alone restores native damage
    no probe ClearTriggeredList required
    closed through EV-276

Normal / Action1:
    same original _AI_Attack invocation owns StatePosition 0 -> 1 + RIGHT raw55 5 -> 7
    selective 5 -> 7 suppression preserves StatePosition progression
    authored FIST activation alone restores native damage
    no probe ClearTriggeredList required
    closed through EV-279

Sprint / Action9:
    factual Action9 is already available at existing _AI_PowerAttack callback entry
    current temporary raw55 research still suppresses the whole eligible Sprint callback
    callback side-effect ownership is therefore unresolved
```

Raw8 Sprint is already a separate production-supported mechanism. EV-251 proves factual Action9 arrives through `_AI_PowerAttack` and can be classified as first-class `Family=SPRINT`; this task must not alter raw8 Sprint behavior.

Do not infer Sprint behavior from true Power merely because both use `_AI_PowerAttack` transport.

---

## 2. Single Probe Question

For exact eligible marked factual raw55 Sprint only:

```text
stop temporary whole-callback suppression
run the original _AI_PowerAttack callback exactly once
observe before/after factual state around each native invocation
observe ordinary raw55 SetCollisionGroup traffic independently
```

The probe asks only whether one original Sprint callback invocation contains:

```text
StatePosition 0 -> 1
and/or
exact RIGHT PhysicalFist/raw55 5 -> 7
```

No intervention is authorized at either boundary.

A decisive compound-ownership shape, if Sprint matches tested true Power/Normal, would be:

```text
CORE COLLISION_GROUP ... Source=TrollFist UseType=55 Requested=7 Before=5 After=7
CORE RAW55_SPRINT_CALLBACK_BOUNDARY ... SameC1=1 SameRight=1 Action=9->9 StatePosition=0->1 RightGroup=5->7 NativeResult=1
```

But this is an expected comparison shape, not an assumption. Any different factual result is valid evidence.

---

## 3. Exact Observer Eligibility

A Sprint callback observation may be active only when all of the following are factual:

```text
FRAME_COLLISION_DIAGNOSTICS build
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
resolved family == AttackFamily_Sprint
factual routine Action == gEAction_SprintAttack / 9
Sprint attack Hit eligible
matching current motion found
marker scan valid
marker present
at least one authored G3AB_COL_FIST
no RIGHT / LEFT / BOTH / OFF marker authored
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
RIGHT source exists
RIGHT source UseType == gEUseType_PhysicalFist / raw55
```

The observer must not gate by Troll/BlackTroll name, species, animation filename, or `PowerAttack` motion naming.

For observation eligibility, do **not** require RIGHT to remain group5 after native opening. The same Sprint C1 must remain observable on later callback invocations after a factual `5 -> 7` transition.

---

## 4. Observation Scope / Reentrancy

Add a dedicated `SprintCallbackObservation` owned by `PhysicalFistProbe`.

It must be per-invocation and reentrancy-safe, following the already-proven observer shape used for Normal/Power:

```text
previous scope pointer
actor instance
exact RIGHT source instance
C1 generation
action before
phase before
state time before
StatePosition before
RIGHT UseType/group before
motion/source identity before
```

Nested/ineligible observations must shadow rather than borrow an outer observation's authority. End observation must restore the previous scope.

This state is diagnostic observation only; it must not authorize mutation.

---

## 5. Existing Hook Ownership

`EngineBridge` remains the sole physical `_AI_PowerAttack` hook owner.

The current wrapper already resolves:

```text
Action9 -> AttackFamily_Sprint
otherwise -> AttackFamily_Power
```

Use only the smallest existing-hook transport change needed to bracket the one original Sprint callback invocation:

```text
if family == POWER:
    existing Power Begin/End observation unchanged

if family == SPRINT:
    new Sprint Begin/End observation

call original _AI_PowerAttack exactly once
return its result unchanged
```

Do not add another callback hook or duplicate hook ownership.

The temporary whole-callback Sprint suppression in `PhysicalFistProbe::ShouldSuppressNativeCallback()` must be disabled for eligible Sprint so the original callback can be observed. Do not replace it with another intervention in this task.

---

## 6. Required Diagnostic Record

Add:

```text
CORE RAW55_SPRINT_CALLBACK_BOUNDARY
```

Each completed active observation must include at minimum:

```text
Actor
C1
SameC1
SameRight
Action before->after
Phase before->after
StateTime before->after
StatePosition before->after
MotionBefore
MotionAfter
Right
RightUseType
RightGroup before->after
NativeResult
OBSERVE_NATIVE=1
```

Existing ordinary records remain the physical evidence for nested mutations:

```text
CORE COLLISION_GROUP
CORE C1 OFFENSE REQUEST
CORE ONDAMAGE
native cleanup / C1 finalization
marker result
```

Do not add broad per-frame logging.

---

## 7. Explicit Non-Responsibilities

This probe must not:

```text
suppress any Sprint SetCollisionGroup request
activate raw55 at FIST
ClearTriggeredList for Sprint
write StatePosition
write SPU+0x164
perform custom/direct damage
perform cleanup compensation
change CollisionLifecycleGuard policy
change FrameCollisionMarkers semantics
change CollisionSources semantics
change CollisionSourceOperations semantics
change raw8 Sprint
change closed Quick behavior/research state
change closed Power behavior/research state
change closed Normal behavior/research state
add species/name/filename policy
add a new hook/RVA/timer/polling/per-frame path
create permanent PhysicalFistCollision
promote raw55 behavior into Script_G3AnimationBehaviors
```

Stable raw55 `G3AB_COL_FIST` processing remains unsupported by the raw8 resolver during this observation.

---

## 8. Expected Source Scope

Expected bounded implementation scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

`EngineBridge.cpp` changes must be limited to the smallest existing `_AI_PowerAttack` diagnostic observation delegation described above.

No CMake change is expected or authorized.

If a direct source contradiction requires broader hook/transport change, STOP and report the smallest exact contradiction to Normal Chat.

---

## 9. Required Static Audit

Before publication verify:

```text
Sprint no longer returns temporary whole-callback probe suppression
factual Action9 still resolves Family=SPRINT at existing _AI_PowerAttack entry
original Sprint _AI_PowerAttack executes exactly once
original callback return value preserved
new Sprint observer is diagnostics-only
observer eligibility requires exact marked raw55 Sprint fixture
observer scope is reentrancy-safe and restored
Power observer behavior unchanged
Normal observer/selective suppression/FIST activation unchanged
Quick closed behavior unchanged
raw8 Sprint unchanged
no SetCollisionGroup intervention added for Sprint
no FIST activation/rearm added for Sprint
no lifecycle policy change
no new hook/RVA
no CMake/source-boundary change
release target unchanged
git diff --check PASS
```

Build execution is **NOT authorized for Work**.

---

## 10. Local Runtime Test

After Normal Chat independently reviews the source, User + Normal Chat build/deploy `Script_FrameCollisionTest` locally.

Preferred artifact:

```text
research/raw/2026.09.13_troll_raw55_sprint_callback_boundary.log
```

Minimum useful run:

```text
one factual marked raw55 Sprint / Action9 Troll execution
prefer two independent Sprint C1s if practical
incidental Normal/Quick/Power traffic is harmless
```

The User does not need to identify Sprint by animation filename; factual `Action=9 / Family=SPRINT` in the log is authoritative.

Correlate by actor + C1 generation:

```text
CORE RAW55_SPRINT_CALLBACK_BOUNDARY
CORE COLLISION_GROUP
FIST marker result
CORE ONDAMAGE
native cleanup / C1 finalization
```

### Interpretation A — compound ownership

If one original Sprint callback shows:

```text
SameC1=1
SameRight=1
Action=9->9
StatePosition=0->1
RightGroup=5->7
NativeResult=1
```

then whole-callback Sprint suppression is too broad for the same causal reason established independently for true Power and Normal. The next smallest question becomes selective exact RIGHT raw55 `5 -> 7` suppression while preserving native Sprint StatePosition progression.

### Interpretation B — group opening without required StatePosition progression

Do not import the Power/Normal design automatically. Freeze the next question from the actual Sprint callback result.

### Interpretation C — StatePosition progression without raw55 opening

The callback/state and collision paths are already separated differently. Isolate the actual raw55 activation boundary before designing intervention.

### Interpretation D — neither responsibility occurs in the observed callback

Do not add compensation or infer hidden ownership. Identify the next existing factual boundary from the runtime evidence.

---

## 11. Stop Boundary

After one adequate focused runtime capture:

```text
commit raw log unchanged
Normal Chat interprets and promotes canonical evidence
freeze only the next smallest Sprint causal question
```

Do not combine this observation with Sprint selective group suppression, authored-FIST activation/rearm, permanent raw55 architecture, or release promotion.
