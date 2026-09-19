# Raw55 PhysicalFist True Power Selective Group-Suppression Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-13

## Purpose

Answer one causal/separability question after EV-274 and before any permanent raw55 implementation is designed:

> If the original marked factual raw55 true-Power `_AI_PowerAttack` callback is allowed to execute normally, but only its exact nested RIGHT raw55 `Item_Equipped (5) -> Item_Attack (7)` collision-group request is suppressed, does native Power still advance StatePosition `0 -> 1` cleanly while the raw55 source remains group5, with no later raw55 activation or lifecycle divergence?

This is a temporary diagnostics-only intervention. It is not production raw55 marker behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_274_ONWARD.md` EV-274.

---

## 1. Evidence Boundary

EV-274 established factual true Power as:

```text
Script=_AI_PowerAttack
Action=2
Family=POWER
RIGHT TrollFist / PhysicalFist raw55
```

The decisive native callback invocation shows:

```text
before: StatePosition 0, RIGHT group5
inside: exact RIGHT raw55 SetCollisionGroup request 5 -> 7
after:  StatePosition 1, RIGHT group7
```

The same Power C1 later receives authored FIST, can damage `PC_Hero`, and cleans the exact RIGHT source `7 -> 5` natively with clean finalization.

Therefore whole `_AI_PowerAttack` suppression is too broad for true Power: it would remove both the premature raw55 opening and required native state progression.

The unresolved question is whether those two responsibilities can be separated at the already-observed collision-group mutation boundary.

Factual `Action=9 / Family=SPRINT` may use the same `_AI_PowerAttack` transport, but it is not true Power and is outside this probe.

---

## 2. Single Probe Question

Run the original native `_AI_PowerAttack` exactly once per true-Power callback invocation, unchanged except for one narrow diagnostic interception:

```text
exact marked factual raw55 true-Power callback scope
+ factual Action=2 / Family=POWER
+ exact factual RIGHT raw55 source
+ source currently Item_Equipped / group5
+ native request is Item_Attack / group7
+ same factual C1 generation still current
= suppress only that physical group mutation
```

Everything else in the native Power callback must run normally.

The decisive expected observation if the responsibilities are separable is:

```text
CORE RAW55_POWER_GROUP_SUPPRESSION ... SUPPRESS_GROUP=1
CORE RAW55_POWER_CALLBACK_BOUNDARY ... StatePosition=0->1 ... RightGroup=5->5
```

---

## 3. Exact Power Scope Eligibility

The active Power callback scope may be established only when all of the following are factual:

```text
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
factual current Action == gEAction_PowerAttack / 2
resolved family == AttackFamily_Power
Power attack Hit eligible
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

Do not gate by actor/species name, Troll filename prefix, animation filename token, or any other content-name policy.

The callback-scope identity is factual actor instance + factual RIGHT source instance + C1 generation and exists only while the original true-Power callback is executing.

The scope must be per-invocation and reentrancy-safe. If nested/reentrant diagnostic scopes occur, restore the previous scope rather than using a bare unscoped global boolean.

Sprint/Action9 must never establish this Power suppression scope.

---

## 4. Exact Collision-Group Suppression Eligibility

Inside the existing `SetCollisionGroup` hook transport, `PhysicalFistProbe` may suppress a request only when **all** of the following are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
an exact active marked-raw55 true-Power callback scope exists
scoped Action/family is factual Power, not Sprint
current source pointer == scoped factual RIGHT source pointer
requested group == eECollisionGroup_Item_Attack / group7
current/before group == eECollisionGroup_Item_Equipped / group5
source still resolves factual UseType == gEUseType_PhysicalFist / raw55
current C1 generation is valid and equals the scoped C1 generation
scoped actor identity is still current
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
unmarked raw55 Power
raw55 Quick group traffic
raw55 Normal or Sprint traffic outside their existing temporary probe behavior
any request outside the original true-Power callback scope
```

---

## 5. Modular Ownership

`EngineBridge` remains the sole physical hook owner for `_AI_PowerAttack` and `SetCollisionGroup`.

The existing SetCollisionGroup wrapper already provides diagnostic transport by asking:

```text
PhysicalFistProbe::ShouldSuppressCollisionGroupRequest(...)
```

Prefer extending policy/state inside `PhysicalFistProbe` so no new bridge behavior is needed. If a tiny diagnostic-only bridge change is mechanically necessary, it may only carry scope transport already frozen here; it must not own Power policy or research state.

A probe-suppressed request did not physically enter group7. Therefore it must not reach the original SetCollisionGroup call and must not be reported to `CollisionLifecycleGuard::ObserveCollisionGroupResult` as a real offense request or fabricate an outstanding C1 obligation.

`PhysicalFistProbe` owns:

```text
exact true-Power callback-scope eligibility
per-invocation scope lifetime / restoration
exact actor/source/C1 identity
selective 5 -> 7 suppression decision
compact suppression logging
existing Power callback-boundary before/after logging
```

Do not move feature policy/state into `EngineBridge`.

---

## 6. Diagnostic Logging

Keep the existing:

```text
CORE RAW55_POWER_CALLBACK_BOUNDARY
```

Add one compact record for each exact Power mutation the probe suppresses:

```text
CORE RAW55_POWER_GROUP_SUPPRESSION
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

Repeated exact suppression records in one Power C1 are evidence, not automatically an error: they would show native Power retrying the same offensive request while the physical source remains group5.

Do not add broad per-frame logging.

---

## 7. Existing Diagnostic Controls

Preserve all current probe behavior outside this true-Power-only intervention:

```text
raw55 Quick  -> closed Quick research behavior unchanged
raw55 Normal -> prior temporary whole-callback suppression unchanged
raw55 Sprint -> prior temporary whole-callback suppression unchanged
true Power   -> original callback runs; only exact scoped RIGHT raw55 5 -> 7 requests may be suppressed
```

The existing Power callback-boundary observation remains active so the same native invocation shows whether StatePosition advances while physical raw55 remains group5.

---

## 8. Forbidden Changes

The probe must not:

```text
suppress the whole true-Power callback
write StatePosition
write SPU+0x164
set raw55 group7 manually
set raw55 group5 as compensation
ClearTriggeredList
accept/process raw55 FIST differently
add raw55 marker ownership
use raw8 timing permission
change C1 lifecycle/repair policy
perform damage
change target/contact logic
change Raw8FistCollision
change FrameCollisionMarkers semantics
change CollisionLifecycleGuard semantics
change equipped RIGHT / LEFT / BOTH / OFF behavior
change closed Quick behavior or Quick research state
change Normal/Sprint temporary behavior
add actor/species/name/filename policy
add a new hook/RVA/timer/polling path
create permanent PhysicalFistCollision
```

---

## 9. Diagnostic Build Boundary

All `PhysicalFistProbe` state and policy remain diagnostic-only and compile only into `Script_FrameCollisionTest`.

`Script_FrameCollisionBehaviorTest` must remain free of the probe after preprocessing/source selection. Its Power/Sprint and SetCollisionGroup paths retain existing behavior.

No CMake target/source-boundary change is expected or authorized. If Work finds a direct contradiction in the current target definition, stop and report rather than broadening the task.

---

## 10. Required Static Audit

Before publication verify:

```text
original true-Power callback still called exactly once
Sprint/Action9 cannot establish Power suppression scope
Power callback is not whole-callback suppressed
selective suppression is diagnostics-only
suppression requires exact scoped RIGHT raw55 source + group5 -> requested group7 + same C1
suppressed SetCollisionGroup request does not reach original SetCollisionGroup
suppressed request does not enter CollisionLifecycleGuard as a real offense
all nonmatching SetCollisionGroup requests follow previous path unchanged
Power scope is restored after each native invocation
existing Power callback-boundary logging remains intact
Quick behavior/research state unchanged
Normal/Sprint temporary probe meaning unchanged
no new hook/RVA
Raw8FistCollision unchanged
FrameCollisionMarkers unchanged in behavior/semantics
CollisionLifecycleGuard unchanged in behavior/semantics
CMake diagnostic/behavior source separation unchanged
```

Build execution is not authorized by this contract.

---

## 11. Local Runtime Test

After Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest`.

Preferred focused artifact:

```text
research/raw/2026.09.13_raw55_power_group_suppression_probe.log
```

Minimum useful run:

```text
one marked factual raw55 Troll/BlackTroll fixture
wait for at least one factual Action=2 / Family=POWER execution
extra Quick/Normal/Sprint traffic is harmless incidental traffic
```

The User does not need to identify Power visually; factual Action/family in the log is authoritative.

Correlate by actor + C1 generation:

```text
CORE RAW55_POWER_GROUP_SUPPRESSION
CORE RAW55_POWER_CALLBACK_BOUNDARY
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

This proves the unwanted Power physical opening can be gated independently while preserving native Power state progression. It does **not** authorize permanent implementation yet; Normal Chat then decides the smallest authored-FIST replacement/rearm question.

### Interpretation B — state progression also fails

If exact group suppression leaves Power at StatePosition 0, the two effects are more tightly coupled than EV-274 revealed. Do not invent a compensating StatePosition write; investigate the native coupling.

### Interpretation C — another activation path exists

If the exact scoped request is suppressed but raw55 later physically opens `5 -> 7` in the same true-Power C1 outside the suppression scope, isolate that second activation path before production design.

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

Do not implement permanent `PhysicalFistCollision`, authored Power FIST activation/rearm, or Normal/Sprint redesign in the same Work task.
