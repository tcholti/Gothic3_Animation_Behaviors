# Raw55 PhysicalFist Sprint Selective Group-Suppression Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-14

## Purpose

Answer one causal/separability question after EV-280 and before any Sprint authored-FIST activation or permanent raw55 design:

> If the original marked factual raw55 Sprint / Action9 `_AI_PowerAttack` callback executes normally, but only its exact nested RIGHT raw55 `Item_Equipped (5) -> Item_Attack (7)` collision-group request is suppressed, does native Sprint still advance `StatePosition 0 -> 1` cleanly while the raw55 source remains group5?

This is a temporary diagnostics-only intervention. It is not production raw55 marker behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_280_ONWARD.md` EV-280.

---

## 1. Evidence Boundary

EV-280 establishes factual raw55 Sprint as:

```text
Script=_AI_PowerAttack
Action=9
Family=SPRINT
RIGHT TrollFist / PhysicalFist raw55
motion may be PowerAttack-named but filename is not family authority
```

Repeated decisive native Sprint invocations show:

```text
before: StatePosition 0, RIGHT group5
inside: exact RIGHT raw55 SetCollisionGroup request 5 -> 7
after:  StatePosition 1, RIGHT group7
SameC1=1
SameRight=1
Action=9->9
NativeResult=1
```

Authored `G3AB_COL_FIST` is later delivered while the same C1 still has factual Action9 / Family SPRINT and RIGHT is already group7. Native damage and native `7 -> 5` cleanup occur in exercised executions.

Later callbacks in the same PowerAttack-named motion can become factual Action2 / Family POWER after contact. This does not change the Action9 opening fact. Future Sprint policy must therefore key to factual Action9 / Sprint callback scope, never to animation filename.

Whole-callback Sprint suppression is rejected: EV-280 proves the callback owns required StatePosition progression as well as premature physical opening.

---

## 2. Single Probe Question

Run the original native `_AI_PowerAttack` exactly once for each eligible factual Sprint callback, unchanged except for one narrow diagnostic interception:

```text
active exact marked raw55 Sprint callback scope
+ factual Action9 / Family SPRINT
+ exact factual RIGHT raw55 source
+ source currently Item_Equipped / group5
+ native request Item_Attack / group7
+ same factual actor/C1/source identity still current
= suppress only that physical group mutation
```

Everything else in the native Sprint callback must run normally.

The decisive positive shape is:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION ... SUPPRESS_GROUP=1
CORE RAW55_SPRINT_CALLBACK_BOUNDARY ...
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1
```

---

## 3. Existing Sprint Scope Is the Authority

Reuse the reviewed reentrancy-safe `SprintCallbackObservation` already owned by `PhysicalFistProbe`.

Do not create another callback hook or parallel Sprint-family detector.

The active Sprint scope is eligible only when the existing observer has already established the exact factual marked raw55 Sprint fixture:

```text
valid actor / actor instance
valid SPU and SPU self == actor
valid current C1 generation
factual Action == gEAction_SprintAttack / 9
resolved Family == AttackFamily_Sprint
Sprint Hit eligible
matching current motion found
marker scan valid
marker present
at least one authored G3AB_COL_FIST
no RIGHT / LEFT / BOTH / OFF marker authored
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
exact RIGHT source exists
RIGHT UseType == PhysicalFist/raw55
```

The scope identity is factual actor instance + exact RIGHT source instance + C1 generation + factual Action9.

Do not gate by Troll/species/entity name, animation filename, `PowerAttack` token, or any other content-name policy.

---

## 4. Exact SetCollisionGroup Suppression Eligibility

Inside the already-existing SetCollisionGroup hook transport, `PhysicalFistProbe` may suppress a request only when **all** of the following are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
active SprintCallbackObservation exists and is active
scope actionBefore == gEAction_SprintAttack / 9
current actor still equals scoped actor
current factual Action is still gEAction_SprintAttack / 9
current source pointer == scoped exact RIGHT source pointer
current equipped RIGHT source still equals that pointer
source UseType == PhysicalFist/raw55
requested group == Item_Attack / 7
before/current group == Item_Equipped / 5
current C1 generation valid and equals scoped C1 generation
Sprint Hit remains factually eligible
```

If any condition fails, existing SetCollisionGroup behavior continues unchanged.

The Sprint rule must not suppress:

```text
7 -> 5 cleanup
7 -> 7
5 -> 5
another source / actor / C1
raw8 Fist
ordinary equipped weapons
Normal / Quick / true-Power requests
unmarked raw55 traffic
factual Action2 requests that occur later in a Sprint-origin motion
any request outside the exact active Action9 Sprint callback scope
```

Important: EV-280 observed that later callbacks in the same motion may become Action2 after contact. Those are **not Sprint scope** and must not borrow Sprint suppression merely because the motion filename still says PowerAttack.

---

## 5. Existing Closed Probe Behavior Must Remain Observable

Do not disable or rewrite the closed Power/Normal/Quick diagnostic mechanisms merely to simplify this Sprint test.

If, after the exact Action9 request is suppressed, a later factual Action2 callback in the same C1 attempts another `5 -> 7`, the existing Power selective-suppression logic may log its own `RAW55_POWER_GROUP_SUPPRESSION` record. That is useful evidence of a second native activation path and must be reported as such; do not hide, merge, or reinterpret it as Sprint success.

A positive Sprint separability result requires:

```text
Sprint exact Action9 5 -> 7 suppressed
same Sprint callback still advances StatePosition 0 -> 1
RIGHT remains group5
later authored FIST is delivered
no physical raw55 5 -> 7 occurs later in the same C1
no alternate Power/other 5 -> 7 request is silently ignored
no raw55 offense obligation / repair is fabricated
```

---

## 6. Diagnostic State / Proof

`PhysicalFistProbe` may record the exact successful Sprint early-suppression fact for the same actor/source/C1 so later research can require factual proof.

Keep this state minimal and diagnostic-only. It may contain only the factual identity/proof needed to say:

```text
actor
exact RIGHT source
C1 generation
raw55 UseType
Sprint early suppression proven
```

No Sprint authored-FIST activation, activation-used decision, rearm, damage, or cleanup action may consume this proof in this task.

---

## 7. Logging

Keep existing:

```text
CORE RAW55_SPRINT_CALLBACK_BOUNDARY
```

Add exactly one compact record for each exact Action9 Sprint mutation suppressed:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION
```

Include at minimum:

```text
Actor
C1
Action=9
Right source identity
RightUseType=55
RequestedGroup=7
BeforeGroup=5
StatePosition
StateTime
SUPPRESS_GROUP=1
```

Do not add broad per-frame logging.

---

## 8. Lifecycle Semantics

A suppressed request never physically entered group7.

Therefore the suppressed request must:

```text
not call original SetCollisionGroup
not be reported to CollisionLifecycleGuard as a real offense request
not fabricate an outstanding C1 obligation
not trigger cleanup compensation
```

Existing native cleanup and C1-R1 semantics remain untouched for all real physical openings.

---

## 9. Forbidden Changes

Do NOT:

```text
suppress the whole Sprint callback
write StatePosition
write SPU+0x164
activate raw55 at authored FIST
call ClearTriggeredList for Sprint
perform direct/custom damage
manually request group5 cleanup
change C1 lifecycle/repair policy
change FrameCollisionMarkers semantics
change CollisionSources / CollisionSourceOperations semantics
change raw8 Sprint behavior
change closed Quick behavior/research state
change closed true-Power behavior/research state
change closed Normal behavior/research state
alias Sprint to Power policy
use animation filename as family authority
add actor/species/name policy
add a new hook/RVA/timer/polling/per-frame path
create permanent PhysicalFistCollision
promote anything into Script_G3AnimationBehaviors
change CMake/source-boundary semantics
```

---

## 10. Expected Source Scope

Expected implementation scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h` may change only if the smallest diagnostic state declaration requires it.

No `EngineBridge.cpp` change is expected: the existing Sprint callback scope and existing SetCollisionGroup delegation seam should already provide all required transport.

No CMake change is authorized.

If current source proves a broader bridge/hook change is required, STOP and report the exact contradiction rather than broadening.

---

## 11. Required Static Audit

Before publication verify:

```text
whole-callback Sprint suppression remains disabled
original factual Sprint _AI_PowerAttack still called exactly once
native return preserved
existing Sprint observer unchanged in meaning
selective rule requires exact active Action9 Sprint scope
selective rule requires exact RIGHT raw55 source + same actor/C1 + 5 -> requested7
factual Action2 later in same motion cannot borrow Sprint suppression
suppressed request does not call original SetCollisionGroup
suppressed request does not enter lifecycle as real offense
all nonmatching requests follow previous path unchanged
existing Power/Normal/Quick rules unchanged
raw8 Sprint unchanged
no Sprint FIST activation/rearm
no StatePosition/SPU writes
no new hook/RVA
no CMake/release-boundary change
git diff --check PASS
```

BUILD EXECUTION IS NOT AUTHORIZED FOR WORK.

---

## 12. Local Runtime Test

After independent Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest` locally.

Preferred artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_group_suppression.log
```

Minimum useful run: capture at least one factual Action9 / Family SPRINT execution.

Correlate by actor + C1:

```text
RAW55_SPRINT_GROUP_SUPPRESSION
RAW55_SPRINT_CALLBACK_BOUNDARY
COLLISION_GROUP
FIST marker
any RAW55_POWER_GROUP_SUPPRESSION in same C1
ONDAMAGE
C1 cleanup/final/repair
```

### Interpretation A — separability PASS

```text
Action9 early 5 -> 7 is suppressed
same Sprint callback returns StatePosition 0 -> 1
RIGHT remains 5 -> 5
authored FIST arrives at StatePosition1 while RIGHT still group5
no alternate physical raw55 opening occurs
no Sprint damage occurs
C1 finalizes with no offense obligation / repair
```

Then Normal Chat may freeze the authored Sprint FIST activation question, testing physical activation alone first and leaving `ClearTriggeredList` separate.

### Interpretation B — StatePosition fails

Do not compensate with a StatePosition write. Return to native coupling analysis.

### Interpretation C — second activation path appears

Any later Sprint/Power/other `5 -> 7` request in the same C1 is a real second path. Isolate it before authored-FIST work.

### Interpretation D — lifecycle divergence

Any fabricated obligation, repair, unexpected cleanup, or cross-family effect returns the task to design.

---

## 13. Stop Boundary

Work stops after bounded source edit, static audit, commit and push.

Normal Chat independently reviews before local build/runtime. No authored Sprint FIST activation, Sprint rearm, permanent raw55 module, or release promotion belongs in this task.
