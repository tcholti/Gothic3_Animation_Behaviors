# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-13

## Current Bridge — NORMAL SELECTIVE GROUP SUPPRESSION IMPLEMENTED / REVIEWED; RUNTIME PENDING

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-277**.

No permanent raw55 implementation is authorized yet.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_NORMAL_GROUP_SUPPRESSION_PROBE.md
4. EVIDENCE_LEDGER_274_ONWARD.md EV-277
5. implementation commit cf89f5ef55dcf89e322672babfee2bc30f3074ab
6. only exact PhysicalFistProbe source needed if re-review is necessary
```

---

## Closed Result — EV-277

Valid runtime artifact:

```text
research/raw/2026.09.13_troll_raw55_normal_callback_boundary_2.log
upload commit 031d2be6ea6b0ef0972cbed7d66d3a5b045a89e6
implementation 7d6fb67dd60937a64b68d571a5cd4dbc7eafe7bd
```

Multiple independent factual marked Normal executions repeat the same decisive callback shape.

```text
Action=1 / Family=NORMAL
RIGHT TrollFist / PhysicalFist raw55
same original _AI_Attack invocation:
    StatePosition 0 -> 1
    exact RIGHT raw55 5 -> 7
    SameC1=1
    SameRight=1
    NativeResult=1
```

The same compound transition repeats in C1=33, 40, 42 and 46. Native `OnDamage` occurs while offensive; native cleanup returns the exact RIGHT source `7 -> 5`; C1 cleanup is fulfilled and finalization needs no repair.

Conclusion:

```text
raw55 Normal callback compound ownership CONFIRMED
whole _AI_Attack suppression REJECTED as a Normal production mechanism
required native StatePosition progression must be preserved
premature physical raw55 opening must be separated rather than suppressing the whole callback
```

The earlier `research/raw/2026.09.13_troll_raw55_normal_callback_boundary.log` is deployment/provenance evidence only. The User confirmed the newly built DLL had not been copied before that run.

---

## Current Probe Implementation — REVIEWED PASS / NOT YET RUNTIME-TESTED

Authority:

```text
docs/COLLISION_RAW55_NORMAL_GROUP_SUPPRESSION_PROBE.md
```

Implementation:

```text
cf89f5ef55dcf89e322672babfee2bc30f3074ab
Suppress scoped raw55 Normal group request
```

Independent Normal Chat source review: **PASS**.

Compare against frozen base `6d6d3215c7e90acf8f9b64246652835897f0b304` proves:

```text
exactly 1 commit ahead
changed only:
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
EngineBridge unchanged
CMake unchanged
```

Implemented responsibility:

```text
Normal callback remains enabled and executes through the existing EngineBridge transport
NormalCallbackObservation now carries a previousScope pointer
thread-local current Normal scope is established before eligibility evaluation
nested/ineligible observations shadow an outer scope rather than borrowing its authority
EndNormalCallbackObservation restores the previous scope

inside existing SetCollisionGroup diagnostic delegation:
    suppress only when active Normal scope is exact
    Action == gEAction_Attack / 1
    current source == scoped exact RIGHT source
    requested group == Item_Attack / 7
    before/current group == Item_Equipped / 5
    source remains PhysicalFist/raw55
    factual equipped RIGHT still equals the scoped source
    current valid C1 matches the scoped actor/C1

emit:
    CORE RAW55_NORMAL_GROUP_SUPPRESSION
```

No new lifecycle observation is fabricated for a suppressed request because the existing bridge suppression contract returns before original `SetCollisionGroup` and lifecycle observation.

Protected behavior remains unchanged:

```text
Sprint temporary whole-callback suppression
closed Quick research behavior
closed Power EV-275/EV-276 behavior
raw8 FIST
CollisionLifecycleGuard
EngineBridge hook/transport ownership
CMake target separation
release target / release purity
```

Build status at stopping point:

```text
NOT RUN — Work boundary respected
```

Material contradiction: **none**.

---

## Exact Resume Point

Do **not** start another Work/source task.

Next action belongs to User + Normal Chat only:

```text
1. sync local branch to repository HEAD
2. verify git rev-parse HEAD contains reviewed implementation + checkpoint docs
3. build Script_FrameCollisionTest locally
4. replace the live diagnostic DLL in the Gothic 3 folder
5. verify deployment provenance before runtime
6. run focused Troll fixture
7. commit the raw log unchanged
8. Normal Chat closes the evidence transaction before any next causal question
```

Because a stale live DLL occurred immediately before EV-277, deployment provenance must be treated explicitly. A successful build alone is not proof that the live game DLL was replaced.

Preferred runtime artifact remains:

```text
research/raw/2026.09.13_troll_raw55_normal_group_suppression.log
```

Single runtime question:

> With the original eligible marked raw55 Normal `_AI_Attack` executing exactly once, can only its exact scoped RIGHT PhysicalFist/raw55 `5 -> 7` request be suppressed while native `StatePosition 0 -> 1` still occurs, with RIGHT remaining group5 and lifecycle staying clean?

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

Then verify:

```text
no alternate raw55 5 -> 7 later before/after FIST
FIST still arrives
no Normal OnDamage from the suppressed physical source
no fabricated C1 offense obligation
no terminal repair/lifecycle divergence
```

No authored-FIST activation/rearm belongs in this probe.

---

## Protected Boundary

Preserve unchanged:

```text
Sprint/Action9 temporary whole-callback suppression
closed Quick behavior/research state
closed true-Power selective suppression + FIST activation research state
raw8 FIST
FrameCollisionMarkers semantics
CollisionSources semantics
CollisionSourceOperations semantics
CollisionLifecycleGuard / C1-R1
AttackMotionRouting
CMake target/source separation
release target / release purity
```

Do not add:

```text
whole Normal callback suppression
Normal authored-FIST activation/rearm
ClearTriggeredList for Normal
StatePosition/SPU writes
custom damage
manual cleanup compensation
new hook/RVA/timer/polling
species/name/filename policy
permanent PhysicalFistCollision
release-module promotion
```
