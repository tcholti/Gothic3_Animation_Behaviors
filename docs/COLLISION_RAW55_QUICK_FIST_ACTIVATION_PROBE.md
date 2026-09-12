# Raw55 PhysicalFist Quick Authored-FIST Activation Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-12

## Purpose

Answer one causal question after EV-265 and before any permanent raw55 implementation is designed:

> With the proven marked-raw55 Quick early `Item_Equipped/group5 -> Item_Attack/group7` request still selectively suppressed and the original `_AI_QuickAttack` callback otherwise running normally, is one exact RIGHT raw55 `5 -> 7` request at the authored `G3AB_COL_FIST` event sufficient to restore native contact/damage at authored timing and then receive clean native `7 -> 5` cleanup?

This is a temporary diagnostics-only intervention. It does not make raw55 FIST a production-supported marker path.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_250_ONWARD.md` EV-262 through EV-265.

---

## 1. Evidence Boundary

EV-264 established that a native marked raw55 Quick callback invocation contains both:

```text
StatePosition 0 -> 1
RIGHT TrollFist raw55 group5 -> group7
```

EV-265 established that those responsibilities are separable at the existing `SetCollisionGroup` boundary. Across repeated Troll and BlackTroll Action 4/5 Quick executions:

```text
exact early RIGHT raw55 5 -> 7 request suppressed
original Quick callback still runs
StatePosition 0 -> 1 preserved
RIGHT raw55 stays group5
no later raw55 opening
no damage to PC_Hero
no outstanding raw55 obligation / repair
```

The authored FIST event then arrives later with native `StatePosition=1`, but the stable marker path still reports `UNSUPPORTED_MISSING_SOURCE` because raw55 is deliberately not routed through `Raw8FistCollision`.

Therefore the next unknown is not early gating. It is whether raw55 can be opened at the authored frame while retaining Gothic's native contact/damage/cleanup behavior.

---

## 2. Single Probe Question

For an exact marked factual raw55 Quick execution that has already demonstrated the EV-265 early-suppression event in the same C1 generation:

```text
authored G3AB_COL_FIST occurs
+ current family is factual Quick Hit
+ native Quick StatePosition is 1
+ exact RIGHT PhysicalFist/raw55 source is still group5
+ same C1 generation and exact source as the prior early-suppression proof
= request RIGHT raw55 group7 exactly once at the authored FIST event
```

Do not perform any other collision/contact intervention.

The hoped-for causal shape is:

```text
early callback:
    native 5 -> 7 request suppressed
    StatePosition 0 -> 1
    RIGHT remains 5

authored FIST:
    probe requests exact RIGHT raw55 5 -> 7
    existing SetCollisionGroup transport observes a real offense request

then Gothic:
    owns contact/damage
    owns ordinary 7 -> 5 cleanup
    C1 obligation is fulfilled without terminal repair
```

---

## 3. Stable Marker Boundary Must Remain Unchanged

`FrameCollisionMarkers::ProcessMarker()` currently rejects raw55 FIST as `MarkerResult_UnsupportedMissingSource` because its FIST resolver is the proven raw8 resolver. That is correct for current production semantics and must remain unchanged.

The probe must not:

```text
change ProcessMarker acceptance
replace/generalize the raw8 resolver
pretend raw55 FIST was accepted
consume stable marker occurrence budget on behalf of raw55
call Raw8FistCollision for raw55
write marker-owned Quick StatePosition
```

The reserved FIST frame effect is still consumed by `EngineBridge` as today. The temporary raw55 intervention is a separate diagnostics-only action after the stable marker result is obtained.

---

## 4. Required Prior-Proof State

`PhysicalFistProbe` must remember a bounded per-actor proof record when the existing EV-265 early Quick suppression actually occurs.

The record must contain at least:

```text
actor instance
C1 generation
exact RIGHT source instance
raw55 / PhysicalFist identity
proof that the exact early group5 -> requested group7 mutation was suppressed
whether the authored-FIST activation probe has already been used for that C1
```

A later FIST intervention is eligible only if the current actor/source/C1 still exactly matches that proof record.

Generation/source mismatch invalidates the proof. Do not carry permission across attacks.

No bare species/name flag, animation-prefix flag, timer, or global one-shot boolean is allowed.

---

## 5. Exact Authored-FIST Eligibility

At the existing reserved-marker `StartEffect` path, after the stable `FrameCollisionMarkers::ProcessMarker()` result exists, the diagnostic probe may intervene only when **all** of the following are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
marker opcode == FIST
stable marker result == UNSUPPORTED_MISSING_SOURCE
actor and actor instance valid
current C1 generation valid
current attack is factual Quick Hit
matching current motion found
marker scan valid
marker present
at least one authored FIST
no RIGHT / LEFT / BOTH / OFF authored
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
exact RIGHT source exists
RIGHT source UseType == PhysicalFist/raw55
RIGHT source current group == Item_Equipped/group5
current StatePosition == 1
same actor + RIGHT source + C1 as the recorded EV-265 early-suppression proof
probe activation has not already been used for this C1
```

Do not gate by Troll/BlackTroll name, motion filename side, species, or other content-name policy.

If any condition fails, do nothing and preserve the current marker path unchanged.

---

## 6. Exact Diagnostic Intervention

When the full eligibility contract matches:

```text
mark the C1 proof record as activation-used
request exact RIGHT raw55 source -> eECollisionGroup_Item_Attack/group7
```

Use the ordinary source/native setter path so the existing `SetCollisionGroup` hook and `CollisionLifecycleGuard` observe the real physical transition and real offense obligation.

The FIST-time request occurs outside the `_AI_QuickAttack` invocation scope, so the EV-265 early-suppression rule must not suppress it.

This probe must **not** call `CollisionSourceOperations::ActivateOrRearm()` because that helper also calls `ClearTriggeredList()`.

This probe must issue **no probe-owned `ClearTriggeredList()`**.

Important interpretation boundary:

> A successful runtime result would prove that marker-time group activation is sufficient in the preserved native Quick-callback context **without an additional probe-issued ClearTriggeredList**. It would not prove that no native callback side effect ever touches the triggered list, and it must not be generalized to other attack families from this probe alone.

---

## 7. Existing Quick Early Gate Must Stay Active

Preserve the already-proven EV-265 behavior unchanged:

```text
marked raw55 Quick callback
-> original callback executes exactly once
-> exact scoped early RIGHT raw55 5 -> 7 request is suppressed
-> native StatePosition progression remains
```

Do not remove or weaken that gate in this task.

Also preserve the current temporary controls:

```text
marked raw55 Normal -> prior whole-callback suppression experiment unchanged
marked raw55 Sprint -> prior whole-callback suppression experiment unchanged
```

The new FIST activation intervention is **Quick only**.

---

## 8. Modular Ownership

`EngineBridge` remains sole physical hook owner.

Its only new diagnostic responsibility is the smallest delegation in the already-existing reserved-marker transport:

```text
ProcessMarker(...) unchanged
Raw8FistCollision timing update unchanged
under FRAME_COLLISION_DIAGNOSTICS:
    give actor + marker opcode + stable marker result to PhysicalFistProbe
```

`PhysicalFistProbe` owns all temporary raw55 policy/state:

```text
early-suppression proof record
exact Quick/FIST eligibility
same actor/source/C1 validation
one-shot FIST-time activation decision
exact RIGHT raw55 group request
compact probe logging
```

Do not put raw55 policy/state into `EngineBridge`.

---

## 9. Diagnostic Logging

Keep the existing:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION
CORE RAW55_QUICK_CALLBACK_BOUNDARY
```

Add one compact record for each actual authored-FIST activation intervention:

```text
CORE RAW55_QUICK_FIST_ACTIVATION_PROBE
```

Include at minimum:

```text
Actor
C1 generation
Action
StatePosition
StateTime
RIGHT source identity
RIGHT UseType
GroupBefore
RequestedGroup
GroupAfter
EarlySuppressionProof=1
ClearTriggeredList=0
ACTIVATE_FIST=1
```

Do not add broad per-frame logging.

The existing ordinary `CORE COLLISION_GROUP`, `CORE ONDAMAGE`, marker-result and C1 lifecycle logs remain the factual outcome evidence.

---

## 10. Forbidden Changes

The probe must not:

```text
change FrameCollisionMarkers semantics
change Raw8FistCollision
change CollisionLifecycleGuard semantics
change CollisionSources semantics
change CollisionSourceOperations
accept raw55 FIST in stable marker code
write StatePosition
write SPU+0x164
ClearTriggeredList
perform direct/custom damage
change target/contact logic
manually force cleanup group7 -> group5
add species/name policy
add a new hook/RVA/timer/polling/per-frame scan
create permanent PhysicalFistCollision
broaden to Normal or Sprint authored-FIST activation
```

No permanent production raw55 design is authorized by this probe.

---

## 11. Diagnostic Build Boundary

All probe state/policy remains diagnostic-only in `Script_FrameCollisionTest`.

`Script_FrameCollisionBehaviorTest` remains free of `PhysicalFistProbe` and retains current behavior after preprocessing/source selection.

No CMake change is expected or authorized unless Work finds a direct contradiction; if so, stop and report instead of broadening scope.

---

## 12. Required Static Audit

Before publication verify:

```text
EV-265 early Quick selective suppression remains unchanged
original Quick callback still executes exactly once
new intervention occurs only on exact FIST marker path
stable ProcessMarker result/semantics unchanged
Raw8FistCollision unchanged
same actor/source/C1 prior-suppression proof required
StatePosition 1 required
one activation maximum per C1 proof record
only exact RIGHT PhysicalFist/raw55 group5 source can be requested to group7
request goes through ordinary SetCollisionGroup/lifecycle observation
no ClearTriggeredList call added
no custom damage/cleanup added
Normal/Sprint FIST activation not added
no new hook/RVA
CMake source separation unchanged
```

Build execution is not authorized by this contract.

---

## 13. Local Runtime Test

After Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest`.

Preferred focused artifacts may remain split by actor to control log size, for example:

```text
research/raw/2026.09.12_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_black_troll_raw55_quick_fist_activation.log
```

Minimum useful run:

```text
marked factual raw55 Troll and/or BlackTroll
several naturally selected Quick attacks
stand close enough that post-marker contact can plausibly occur
incidental Normal/Sprint/other attacks are acceptable controls
```

User should report whether any Quick attacks visibly damage `PC_Hero` and whether the damage appears shifted away from the old very-early contact.

Correlate by actor + C1 generation:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION
CORE RAW55_QUICK_CALLBACK_BOUNDARY
stable FIST marker result
CORE RAW55_QUICK_FIST_ACTIVATION_PROBE
CORE COLLISION_GROUP
CORE ONDAMAGE
C1 cleanup/finalization/repair
```

### Interpretation A — authored activation mechanism supported

```text
early native 5 -> 7 request suppressed
StatePosition 0 -> 1 preserved
RIGHT remains group5 until FIST
FIST intervention requests real 5 -> 7
physical group becomes7 at authored timing
contact/damage, when contact occurs, appears only after that opening
native cleanup returns 7 -> 5
C1 obligation is fulfilled
no terminal repair/lifecycle issue
```

This supports marker-time raw55 activation in the preserved native Quick context. It does not yet authorize Normal/Sprint generalization or permanent production implementation.

### Interpretation B — group opens but contact/damage does not return

Do not add custom damage. Investigate the remaining native contact/rearm state, including whether a triggered-list or another native side effect is required.

### Interpretation C — group opens but native cleanup fails

Do not normalize C1 repair into the feature. Isolate the cleanup requirement before production design.

### Interpretation D — FIST request fails to become group7

Treat the source mutation boundary itself as unresolved; do not compensate elsewhere.

---

## 14. Stop Boundary

After one adequate runtime capture:

```text
Normal Chat analyzes committed GitHub evidence
-> promotes the result canonically
-> either freezes the next single raw55 causal question
   or, only if the mechanism is sufficiently proven, designs the permanent owner
```

Do not implement permanent `PhysicalFistCollision` in the same Work task.
