# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-13

## Current Bridge — NORMAL CLOSED EV-279; RAW55 SPRINT OBSERVER REVIEWED; RUNTIME PENDING

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-279**.

No permanent raw55 implementation is authorized yet.

No new Work/source task is authorized. The next responsibility belongs to User + Normal Chat: local build/deploy/runtime validation of the already-reviewed Sprint callback observer.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_SPRINT_CALLBACK_BOUNDARY_PROBE.md
4. EVIDENCE_LEDGER_274_ONWARD.md EV-274–EV-279 as needed
5. EVIDENCE_LEDGER_250_ONWARD.md EV-251 only for established raw8 Sprint transport/support
6. exact PhysicalFistProbe / existing _AI_PowerAttack bridge source only if runtime interpretation requires it
```

---

## Closed Result — EV-279 Normal Authored-FIST Activation

Runtime artifact:

```text
research/raw/2026.09.13_troll_raw55_normal_fist_activation.log
runtime upload commit e01eae6482b0d106d6825a2fc879cca184e7bcc8
implementation d1c9d6f39ece5b5b4f4228d3d46ded976e6ae21a
```

Four independent factual Normal Troll executions — C1=8, 10, 14 and 36 — repeat the full proven mechanism:

```text
Action=1 / Family=NORMAL
exact RIGHT TrollFist / PhysicalFist raw55

early original _AI_Attack:
    exact premature RIGHT 5 -> requested7 suppressed at StatePosition0
    same callback still returns StatePosition 0 -> 1
    SameC1=1
    SameRight=1
    RightGroup=5->5
    NativeResult=1

later authored G3AB_COL_FIST at StatePosition1:
    ordinary exact RIGHT raw55 request 5 -> 7
    GroupAfter=7
    EarlySuppressionProof=1
    ClearTriggeredList=0
    ACTIVATE_FIST=1

then Gothic owns:
    native OnDamage against PC_Hero
    native exact RIGHT cleanup 7 -> 5
    C1 cleanup fulfilled
    Outstanding=0
    Cleanup=1
    PhysicalChanged=0
    Outcome=NO_OP_NO_OUTSTANDING
```

Conclusion:

```text
raw55 Normal tested mechanism CLOSED/PASS
Normal authored-FIST activation alone is sufficient for tested first contact
NO Normal-specific ClearTriggeredList is required
preserve native damage and cleanup ownership
```

Do not generalize this no-rearm result to Quick; Quick's tested mechanism independently requires contact rearm.

---

## Reviewed Sprint Observer Implementation

Frozen authority:

```text
docs/COLLISION_RAW55_SPRINT_CALLBACK_BOUNDARY_PROBE.md
```

Frozen implementation base:

```text
332cf840d641e0756ba90e1d9269cb396915e751
```

Work implementation:

```text
5c9e40c53162c4f16099107a44892e8c03f2bdaf
message: Observe raw55 Sprint callback boundary
```

Independent Normal Chat review: **PASS**.

Commit comparison proves:

```text
exactly one commit ahead of frozen base
only authorized files changed:
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
    prototypes/Script_FrameCollisionTest/EngineBridge.cpp
no CMake change
no unrelated behavior-module change
```

Reviewed implementation shape:

```text
PhysicalFistProbe:
    temporary whole-callback raw55 Sprint suppression disabled
    all current raw55 probe families now keep native callbacks enabled
    dedicated thread_local SprintCallbackObservation scope added
    BeginSprintCallbackObservation shadows prior scope before eligibility checks
    exact factual Action9 / Family SPRINT required
    existing TryResolveRaw55ProbeFixture reused with requireEquippedGroup=false
    captures exact actor + RIGHT source + C1 + before facts
    EndSprintCallbackObservation restores previous scope first
    compares current C1 / exact RIGHT identity and after facts
    emits CORE RAW55_SPRINT_CALLBACK_BOUNDARY

EngineBridge:
    remains sole _AI_PowerAttack hook owner
    existing Action9 -> AttackFamily_Sprint resolution unchanged
    Family POWER still uses existing Power observer
    Family SPRINT now uses smallest Sprint Begin/End observer delegation
    original _AI_PowerAttack called exactly once
    original native result returned unchanged
```

No Sprint intervention was added:

```text
NO Sprint SetCollisionGroup suppression
NO Sprint authored-FIST activation
NO Sprint ClearTriggeredList
NO StatePosition/SPU write
NO custom/direct damage
NO cleanup compensation
NO new hook/RVA/timer/polling
NO lifecycle-policy change
```

Work static/source audit reported PASS including `git diff --check`; Normal Chat source review found no material contradiction.

Build status: **NOT RUN per task boundary**.

Runtime status: **NOT YET TESTED**.

---

## Tomorrow — Exact Next Step

Do not start another Work/source task.

User + Normal Chat:

```text
1. sync local branch to current remote HEAD
2. verify local HEAD
3. build Script_FrameCollisionTest locally
4. manually replace live Script_FrameCollisionTest.dll
5. verify built/live SHA256 equality
6. launch Gothic 3 and exercise Troll until factual Action9 / Family SPRINT occurs
7. preserve the raw diagnostic log unchanged
8. commit/push the raw artifact
9. Normal Chat closes the evidence transaction before any next source task
```

Preferred runtime artifact for the next-day test:

```text
research/raw/2026.09.14_troll_raw55_sprint_callback_boundary.log
```

Single runtime question:

> With exact eligible marked raw55 Sprint no longer whole-callback suppressed, what responsibilities occur inside the original `_AI_PowerAttack` invocation?

Decisive compound result, if factual, would look like:

```text
CORE COLLISION_GROUP ... Source=TrollFist UseType=55 ... Requested=7 Before=5 After=7
CORE RAW55_SPRINT_CALLBACK_BOUNDARY
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->7
    NativeResult=1
```

Do **not** assume Sprint matches Power/Normal. A different factual boundary result decides the next causal question.

Also inspect surrounding authored FIST, OnDamage, cleanup and C1-final records, but do not add compensation during this observation run.

---

## Protected Boundary

Preserve unchanged:

```text
closed Quick raw55 behavior/research state
closed true-Power EV-274–EV-276 behavior/research state
closed Normal EV-277–EV-279 behavior/research state
raw8 FIST including production Sprint
FrameCollisionMarkers semantics
CollisionSources semantics
CollisionSourceOperations semantics
CollisionLifecycleGuard / C1-R1
AttackMotionRouting
CMake target/source separation
release target / release purity
```

Do not create permanent raw55 architecture yet.
