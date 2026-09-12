# Raw55 PhysicalFist Quick Selective Group-Suppression Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-12

## Purpose

Answer one causal/separability question after EV-264 and before any permanent raw55 implementation is designed:

> If the original marked factual raw55 `_AI_QuickAttack` callback is allowed to execute normally, but only its exact nested RIGHT raw55 `Item_Equipped (5) -> Item_Attack (7)` collision-group request is suppressed, does native Quick still advance StatePosition `0 -> 1` cleanly without an early raw55 opening, later raw55 reactivation, or lifecycle repair?

This is a temporary diagnostics-only intervention. It is not production raw55 marker behavior.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_250_ONWARD.md` EV-262–EV-264.

---

## 1. Evidence Boundary

EV-262 established that whole marked-raw55 callback suppression removes the old pre-FIST offensive opening but fails for Quick: rejected FIST arrives at StatePosition 0, later raw55 reopens, and C1 can require terminal repair.

EV-264 closes the callback-boundary question:

```text
normal native marked raw55 Quick invocation
    before: StatePosition 0, RIGHT TrollFist group5
    inside: exact RIGHT raw55 SetCollisionGroup request 5 -> 7
    after:  StatePosition 1, RIGHT TrollFist group7
```

This repeats for Troll and BlackTroll and for Quick Action 4 and 5. Damage can follow shortly after the early group opening, well before authored FIST.

Therefore whole `_AI_QuickAttack` suppression is too broad: it removes both the unwanted early raw55 activation and required native Quick state progression.

The unresolved question is whether those two responsibilities can be separated at the already-observed collision-group mutation boundary.

---

## 2. Single Probe Question

Run the original native `_AI_QuickAttack` exactly once per callback invocation, unchanged except for one narrow diagnostic interception:

```text
exact marked factual raw55 Quick callback scope
+ exact factual RIGHT raw55 source
+ source currently Item_Equipped / group5
+ native request is Item_Attack / group7
+ same factual C1 generation still current
= suppress only that physical group mutation
```

Everything else in the native Quick callback must run normally.

The decisive expected observation if the responsibilities are separable is:

```text
RAW55_QUICK_CALLBACK_BOUNDARY
StatePosition=0->1
RightGroup=5->5
```

---

## 3. Exact Scope Eligibility

The active Quick callback scope may be established only from the already-proven exact raw55 marked fixture identity:

```text
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
Quick attack Hit eligible
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

Do not gate by actor/species name, Troll filename prefix, QuickAttackL/QuickAttackR suffix, or any other content-name policy.

The callback-scope identity is factual actor instance + factual RIGHT source instance + C1 generation and exists only while the original Quick callback is executing.

The scope mechanism must be per-invocation and reentrancy-safe: nested/reentrant diagnostic scopes, if they occur, must restore the prior scope rather than using a bare unscoped global boolean.

---

## 4. Exact Collision-Group Suppression Eligibility

Inside the existing `SetCollisionGroup` hook transport, `PhysicalFistProbe` may suppress a request only when **all** of the following are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
an exact active marked-raw55 Quick callback scope exists
current source pointer == scoped factual RIGHT source pointer
requested group == eECollisionGroup_Item_Attack / group7
current/before group == eECollisionGroup_Item_Equipped / group5
source still resolves factual UseType == gEUseType_PhysicalFist / raw55
current C1 generation is valid and equals the scoped C1 generation
scoped actor identity is still the current owner/context
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
unmarked raw55 Quick
marked raw55 Normal or Sprint group traffic outside their existing temporary callback-suppression experiment
any request outside the original Quick callback scope
```

---

## 5. Modular Ownership

`EngineBridge` remains the sole hook owner for both `_AI_QuickAttack` and `SetCollisionGroup`.

Its only new diagnostic transport responsibility is:

```text
inside existing SetCollisionGroup wrapper, before calling the original:
    ask PhysicalFistProbe whether this exact request is probe-suppressed
    if yes, return without calling the original SetCollisionGroup
    if no, continue the existing path unchanged
```

A probe-suppressed request did not physically enter group7. Therefore it must not be reported to `CollisionLifecycleGuard::ObserveCollisionGroupResult` as a real offense request and must not fabricate an outstanding C1 obligation.

`PhysicalFistProbe` owns all temporary policy/state:

```text
exact marked raw55 Quick callback-scope eligibility
per-invocation scope lifetime / restoration
exact source/C1 identity
selective 5 -> 7 suppression decision
compact suppression logging
existing Quick callback-boundary before/after logging
```

No feature policy or persistent probe state belongs in `EngineBridge`.

---

## 6. Diagnostic Logging

Keep the existing:

```text
CORE RAW55_QUICK_CALLBACK_BOUNDARY
```

Add one compact record for each exact mutation the probe suppresses:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION
```

It must include at minimum:

```text
Actor
C1 generation
RIGHT source identity
RIGHT UseType
requested group
before/current group
StatePosition
StateTime
SUPPRESS_GROUP=1
```

Repeated exact suppression records in one C1 are evidence, not automatically an error: they would show native Quick retrying the same offensive request while the physical source remains group5.

Do not add broad per-frame logging.

---

## 7. Existing Diagnostic Controls

Preserve current temporary diagnostic behavior outside this Quick-only intervention:

```text
marked raw55 Normal -> prior whole-callback suppression experiment unchanged
marked raw55 Sprint -> prior whole-callback suppression experiment unchanged
marked raw55 Quick  -> original callback runs; only exact scoped RIGHT raw55 5 -> 7 requests may be suppressed
```

The previous Quick callback-boundary observation remains active so the same callback invocation shows whether StatePosition advances while physical raw55 remains group5.

---

## 8. Forbidden Changes

The probe must not:

```text
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
change equipped RIGHT/LEFT/BOTH/OFF behavior
add actor/species/name policy
add a new hook/RVA/timer/polling path
create permanent PhysicalFistCollision
```

Do not suppress the entire Quick callback again.

---

## 9. Diagnostic Build Boundary

All `PhysicalFistProbe` state and policy remain diagnostic-only and compile only into `Script_FrameCollisionTest`.

`Script_FrameCollisionBehaviorTest` must remain free of the probe after preprocessing/source selection. Its Quick and SetCollisionGroup paths retain existing behavior.

No CMake target/source-boundary change is expected or authorized unless Work finds a direct contradiction in the current target definition; if so, stop and report rather than broadening the task.

---

## 10. Required Static Audit

Before publication verify:

```text
original Quick callback still called exactly once
Quick callback is not whole-callback suppressed by PhysicalFistProbe
selective suppression is diagnostics-only
suppression requires exact scoped RIGHT raw55 source + group5 -> requested group7 + same C1
suppressed SetCollisionGroup request does not reach original SetCollisionGroup
suppressed request does not enter CollisionLifecycleGuard as a real offense
all nonmatching SetCollisionGroup requests follow the previous path unchanged
scope is restored after each native Quick invocation
Normal/Sprint prior probe meaning unchanged
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
research/raw/2026.09.12_raw55_quick_group_suppression_probe.log
```

Minimum useful run:

```text
one marked factual raw55 Troll/BlackTroll fixture
several naturally selected Quick attacks
extra Normal/other attacks are harmless incidental traffic
```

No large mixed-actor run is required unless the focused run is inconclusive.

Correlate by actor + C1 generation:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION
CORE RAW55_QUICK_CALLBACK_BOUNDARY
CORE COLLISION_GROUP
FIST marker result
CORE ONDAMAGE
C1 finalization / repair
```

### Interpretation A — separability supported

```text
exact early raw55 5 -> 7 request is probe-suppressed
callback boundary still shows StatePosition 0 -> 1
RIGHT raw55 remains 5 -> 5
rejected authored FIST sees native StatePosition 1
no physical raw55 5 -> 7 appears later in that C1
no raw55 damage path becomes offensive
no outstanding raw55 obligation / terminal C1 repair
```

This supports that native Quick state progression can be preserved while the premature raw55 opening is independently gated. It does **not** itself authorize production implementation; Normal Chat then designs the permanent raw55 responsibility around the proven separation.

### Interpretation B — state progression also fails

If exact group suppression leaves Quick at StatePosition 0, the two effects are more tightly coupled than callback-boundary evidence alone revealed. Do not invent a compensating StatePosition write; investigate the native coupling.

### Interpretation C — another activation path exists

If the exact scoped early request is suppressed but raw55 later physically opens `5 -> 7` in the same C1 outside the suppressed request, isolate that second activation path before production design.

### Interpretation D — lifecycle divergence

If the selective intervention causes outstanding raw55 obligations, repair, unexpected cleanup, or other lifecycle divergence, the mechanism is not yet production-safe even if StatePosition reaches 1.

---

## 12. Stop Boundary

After one adequate focused runtime capture:

```text
Normal Chat analyzes the committed GitHub log
-> promotes the result to canonical evidence
-> either designs the permanent raw55 mechanism from proven separability
   or freezes the next single causal question
```

Do not implement permanent `PhysicalFistCollision` or raw55 FIST handling in the same Work task.
