# Raw55 PhysicalFist Normal Selective Group-Suppression Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-13

## Purpose

Answer one causal/separability question after EV-277 and before any permanent raw55 implementation is designed:

> If the original marked factual raw55 Normal `_AI_Attack` callback is allowed to execute normally, but only its exact nested RIGHT raw55 `Item_Equipped (5) -> Item_Attack (7)` collision-group request is suppressed, does native Normal still advance StatePosition `0 -> 1` cleanly while the raw55 source remains group5, with no later raw55 activation or lifecycle divergence?

This is a temporary diagnostics-only intervention. It is not production raw55 marker behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_274_ONWARD.md` EV-277.

---

## 1. Evidence Boundary

EV-277 established factual marked raw55 Normal as:

```text
Script=_AI_Attack
Action=1
Family=NORMAL
RIGHT TrollFist / PhysicalFist raw55
```

Repeated decisive native callback invocations show:

```text
before: StatePosition 0, RIGHT group5
inside: exact RIGHT raw55 SetCollisionGroup request 5 -> 7
after:  StatePosition 1, RIGHT group7
SameC1=1
SameRight=1
NativeResult=1
```

The same Normal C1 later receives authored FIST while RIGHT is already group7, can damage `PC_Hero`, and cleans the exact RIGHT source `7 -> 5` natively with clean finalization.

Therefore whole `_AI_Attack` suppression is too broad for Normal: it removes both the premature raw55 opening and required native state progression. The earlier stale-binary runtime that still logged `RAW55_CALLBACK_SUPPRESSION_PROBE Family=NORMAL SUPPRESS_NATIVE=1` is deployment/provenance evidence only and is not part of the causal Normal result.

The unresolved question is whether the two native responsibilities are separable at the already-observed collision-group mutation boundary.

---

## 2. Single Probe Question

Run the original native `_AI_Attack` exactly once per eligible marked raw55 Normal callback invocation, unchanged except for one narrow diagnostic interception:

```text
exact marked factual raw55 Normal callback scope
+ Family=NORMAL / factual Action=1 in the tested fixture
+ exact factual RIGHT raw55 source
+ source currently Item_Equipped / group5
+ native request is Item_Attack / group7
+ same factual C1 generation still current
= suppress only that physical group mutation
```

Everything else in the native Normal callback must run normally.

The decisive expected observation if the responsibilities are separable is:

```text
CORE RAW55_NORMAL_GROUP_SUPPRESSION ... SUPPRESS_GROUP=1
CORE RAW55_NORMAL_CALLBACK_BOUNDARY ... StatePosition=0->1 ... RightGroup=5->5
```

Do not infer eligibility from animation filename or actor/species name.

---

## 3. Exact Normal Scope Eligibility

The active Normal callback scope may be established only when all of the following are factual:

```text
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
resolved family == AttackFamily_Normal
Normal attack Hit eligible
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

Do not gate by Troll/BlackTroll name, species, Normal animation filename token, or any other content-name policy.

The callback-scope identity is factual actor instance + factual RIGHT source instance + C1 generation and exists only while the original eligible Normal callback is executing.

The scope must be per-invocation and reentrancy-safe. If nested/reentrant diagnostic scopes occur, restore the previous scope rather than using a bare unscoped global boolean.

---

## 4. Exact Collision-Group Suppression Eligibility

Inside the existing `SetCollisionGroup` hook transport, `PhysicalFistProbe` may suppress a request only when **all** of the following are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
an exact active marked-raw55 Normal callback scope exists
current source pointer == scoped factual RIGHT source pointer
requested group == eECollisionGroup_Item_Attack / group7
current/before group == eECollisionGroup_Item_Equipped / group5
source still resolves factual UseType == gEUseType_PhysicalFist / raw55
current C1 generation is valid and equals the scoped C1 generation
scoped actor identity is still current
current family remains Normal / current action remains the same factual execution
```

If any condition fails, the existing SetCollisionGroup path runs unchanged.

The probe must **not** suppress:

```text
7 -> 5 cleanup
7 -> 7 requests
5 -> 5 requests
another source
another actor
another C1 generation
raw8 Fist
normal equipped weapons
unmarked raw55 Normal
raw55 Quick traffic
raw55 true-Power traffic
raw55 Sprint traffic
any request outside the original eligible Normal callback scope
```

---

## 5. Modular Ownership

`EngineBridge` remains the sole physical hook owner for `_AI_Attack` and `SetCollisionGroup`.

The existing SetCollisionGroup wrapper already provides diagnostic transport by asking:

```text
PhysicalFistProbe::ShouldSuppressCollisionGroupRequest(...)
```

Prefer extending policy/state inside `PhysicalFistProbe` so no new bridge behavior is needed. The existing Normal begin/end observation delegation is sufficient transport unless a direct contradiction is found.

A probe-suppressed request did not physically enter group7. Therefore it must not reach the original SetCollisionGroup call and must not be reported to `CollisionLifecycleGuard::ObserveCollisionGroupResult` as a real offense request or fabricate an outstanding C1 obligation.

`PhysicalFistProbe` owns:

```text
exact Normal callback-scope eligibility
per-invocation scope lifetime / restoration
exact actor/source/C1 identity
selective 5 -> 7 suppression decision
compact suppression logging
existing Normal callback-boundary before/after logging
```

Do not move feature policy/state into `EngineBridge`.

---

## 6. Diagnostic Logging

Keep the existing:

```text
CORE RAW55_NORMAL_CALLBACK_BOUNDARY
```

Add one compact record for each exact Normal mutation the probe suppresses:

```text
CORE RAW55_NORMAL_GROUP_SUPPRESSION
```

It must include at minimum:

```text
Actor
C1 generation
Action
RIGHT source identity
RIGHT UseType
requested group
before/current group
StatePosition
StateTime
SUPPRESS_GROUP=1
```

Repeated exact suppression records in one Normal C1 are evidence, not automatically an error: they would show native Normal retrying the same offensive request while the physical source remains group5.

Do not add broad per-frame logging.

---

## 7. Existing Diagnostic Controls

Preserve all current probe behavior outside this Normal-only intervention:

```text
raw55 Quick  -> closed Quick research behavior unchanged
raw55 Power  -> closed EV-275/EV-276 selective suppression + authored-FIST activation behavior unchanged
raw55 Sprint -> prior temporary whole-callback suppression unchanged
raw55 Normal -> original callback runs; only exact scoped RIGHT raw55 5 -> 7 requests may be suppressed
```

The existing Normal callback-boundary observation remains active so the same native invocation shows whether StatePosition advances while physical raw55 remains group5.

---

## 8. Forbidden Changes

The probe must not:

```text
suppress the whole Normal callback
write StatePosition
write SPU+0x164
set raw55 group7 manually
set raw55 group5 as compensation
ClearTriggeredList for Normal
accept/process raw55 Normal FIST differently
add Normal raw55 marker ownership
use raw8 timing permission
change C1 lifecycle/repair policy
perform damage
change target/contact logic
change Raw8FistCollision
change FrameCollisionMarkers semantics
change CollisionLifecycleGuard semantics
change equipped RIGHT / LEFT / BOTH / OFF behavior
change closed Quick behavior or Quick research state
change closed true-Power behavior or Power research state
change Sprint temporary behavior
add actor/species/name/filename policy
add a new hook/RVA/timer/polling path
create permanent PhysicalFistCollision
promote anything into Script_G3AnimationBehaviors
```

---

## 9. Diagnostic Build Boundary

All `PhysicalFistProbe` state and policy remain diagnostic-only and compile only into `Script_FrameCollisionTest`.

`Script_FrameCollisionBehaviorTest` must remain free of the probe after preprocessing/source selection. Its Normal and SetCollisionGroup paths retain existing behavior.

No CMake target/source-boundary change is expected or authorized. If Work finds a direct contradiction in the current target definition, stop and report rather than broadening the task.

---

## 10. Required Static Audit

Before publication verify:

```text
original Normal callback still called exactly once
Normal callback is not whole-callback suppressed
selective suppression is diagnostics-only
suppression requires exact scoped RIGHT raw55 source + group5 -> requested group7 + same C1
suppressed SetCollisionGroup request does not reach original SetCollisionGroup
suppressed request does not enter CollisionLifecycleGuard as a real offense
all nonmatching SetCollisionGroup requests follow previous path unchanged
Normal scope is restored after each native invocation
existing Normal callback-boundary logging remains intact
Sprint temporary whole-callback suppression unchanged
Quick behavior/research state unchanged
Power EV-275/EV-276 behavior/research state unchanged
no new hook/RVA
Raw8FistCollision unchanged
FrameCollisionMarkers unchanged in behavior/semantics
CollisionLifecycleGuard unchanged in behavior/semantics
CMake diagnostic/behavior source separation unchanged
release target unchanged
```

Build execution is not authorized by this contract.

---

## 11. Local Runtime Test

After Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest`.

Preferred focused artifact:

```text
research/raw/2026.09.13_troll_raw55_normal_group_suppression.log
```

Minimum useful run:

```text
one marked factual raw55 Troll/BlackTroll fixture
wait for at least one factual Family=NORMAL execution
prefer two independent Normal C1s when convenient
extra Quick/Power/Sprint traffic is harmless incidental traffic
```

The User does not need to identify Normal visually; factual family/action in the log is authoritative.

Correlate by actor + C1 generation:

```text
CORE RAW55_NORMAL_GROUP_SUPPRESSION
CORE RAW55_NORMAL_CALLBACK_BOUNDARY
CORE COLLISION_GROUP
FIST marker result
CORE ONDAMAGE
C1 finalization / repair
```

### Interpretation A — separability supported

```text
exact early raw55 5 -> 7 request is probe-suppressed
same callback boundary still shows StatePosition 0 -> 1
RIGHT raw55 remains 5 -> 5
authored FIST is still delivered
no physical raw55 5 -> 7 appears later in that C1
no early raw55 damage path becomes offensive
no outstanding raw55 obligation / terminal C1 repair
```

This proves the unwanted Normal physical opening can be gated independently while preserving native Normal state progression. It does **not** authorize permanent implementation yet; Normal Chat then decides the smallest authored-FIST activation/rearm question.

### Interpretation B — state progression also fails

If exact group suppression leaves Normal at StatePosition 0, the two effects are more tightly coupled than EV-277 revealed. Do not invent a compensating StatePosition write; investigate the native coupling.

### Interpretation C — another activation path exists

If the exact scoped request is suppressed but raw55 later physically opens `5 -> 7` in the same Normal C1 outside the suppression scope, isolate that second activation path before production design.

### Interpretation D — lifecycle divergence

If selective intervention causes outstanding raw55 obligations, repair, unexpected cleanup, or other lifecycle divergence, the mechanism is not yet production-safe even if StatePosition reaches 1.

---

## 12. Stop Boundary

After one adequate focused runtime capture:

```text
Normal Chat analyzes the committed GitHub log
-> promotes the result to canonical evidence
-> either freezes the next authored-FIST causal question
   or returns to design if separability fails
```

Do not implement permanent `PhysicalFistCollision`, authored Normal FIST activation/rearm, Sprint redesign, or release promotion in the same Work task.
