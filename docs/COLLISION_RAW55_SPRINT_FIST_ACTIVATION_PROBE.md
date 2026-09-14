# Raw55 PhysicalFist Sprint Authored-FIST Activation Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-14

## Purpose

Answer one causal question after EV-281 and before any permanent raw55 implementation is designed:

> With factual marked raw55 Sprint (`Action=9 / Family=SPRINT`) early `Item_Equipped/group5 -> Item_Attack/group7` still selectively suppressed and the original `_AI_PowerAttack` callback otherwise running normally, can the authored `G3AB_COL_FIST` event itself open the exact RIGHT PhysicalFist/raw55 source `5 -> 7` at authored timing, with Gothic retaining ownership of contact/damage/cleanup?

This is a temporary diagnostics-only intervention. It does not make raw55 FIST a production-supported marker path.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_280_ONWARD.md` EV-280 through EV-281.

---

## 1. Evidence Boundary

EV-280 established Sprint compound callback ownership:

```text
same original _AI_PowerAttack invocation
factual Action=9 / Family=SPRINT
StatePosition 0 -> 1
RIGHT PhysicalFist/raw55 5 -> 7
```

EV-281 establishes separability. Multiple factual Troll Sprint C1s independently suppress the exact scoped native `5 -> 7` while the immediately enclosing callback still returns:

```text
StatePosition 0 -> 1
RIGHT raw55 5 -> 5
SameC1=1
SameRight=1
Action=9->9
NativeResult=1
```

Representative C1=41 then receives authored `G3AB_COL_FIST` at `Action=9 / Family=SPRINT / StatePosition=1` while RIGHT remains group5. No Sprint authored-FIST activation intervention exists in EV-281. Completed Sprint C1s finalize with `Outstanding=0`, `Cleanup=0`, `NO_OP_NO_OUTSTANDING`; the suppressed request creates no offense obligation or repair.

The EV-281 causal run contains no `RAW55_POWER_CALLBACK_BOUNDARY` and no `RAW55_POWER_GROUP_SUPPRESSION` record. The PowerAttack-named motions exercised there were factual Sprint/Action9, so animation filename remains non-authoritative.

Therefore early gating is no longer the open question. The next unknown is whether the exact raw55 source can be opened at authored Sprint FIST time while preserving native Sprint progression and cleanup.

---

## 2. Single Probe Question

For an exact marked factual Sprint raw55 execution that has already demonstrated EV-281 selective early-group suppression in the same C1:

```text
authored G3AB_COL_FIST occurs
+ factual Action=9 / Family=SPRINT Hit
+ native StatePosition is 1
+ exact RIGHT PhysicalFist/raw55 source is still group5
+ same actor + RIGHT source + C1 as the prior Sprint suppression proof
= request exact RIGHT raw55 group7 once at the authored FIST event
```

Do not perform any other collision/contact intervention.

The causal target is:

```text
early native callback:
    exact 5 -> 7 request suppressed
    StatePosition 0 -> 1 preserved
    RIGHT remains 5

authored FIST:
    probe requests exact RIGHT raw55 5 -> 7
    existing SetCollisionGroup/lifecycle transport observes the real offense request

then Gothic owns:
    contact/damage outcome
    ordinary cleanup
```

---

## 3. Stable Marker Boundary Must Remain Unchanged

`FrameCollisionMarkers::ProcessMarker()` must remain unchanged. Raw55 FIST remains unsupported by the stable raw8 resolver and may continue to produce `MarkerResult_UnsupportedMissingSource`.

The probe must not:

```text
change ProcessMarker acceptance
replace/generalize the raw8 resolver
pretend raw55 FIST was accepted
change marker occurrence semantics
call Raw8FistCollision for raw55
```

The temporary raw55 intervention remains a diagnostics-only action after the stable marker result already exists.

---

## 4. Required Prior-Proof State

`PhysicalFistProbe` already records a bounded per-actor Sprint suppression proof only when the EV-281 selective suppression actually occurs.

For this probe the Sprint proof must include at least:

```text
actor instance
C1 generation
exact RIGHT source instance
raw55 / PhysicalFist identity
proof that the exact native group5 -> requested group7 request was suppressed
whether this authored-FIST activation probe has already been used for that C1
```

The existing `SprintEarlySuppressionProof` may be extended only as needed to add the one-shot activation-used state.

A FIST intervention is eligible only when current actor/source/C1 exactly match that proof. Generation or source mismatch invalidates the permission. Do not carry permission across attacks.

No species/name/motion-prefix/timer/global one-shot policy is allowed.

---

## 5. Exact Authored-FIST Eligibility

At the existing reserved-marker path, after the stable marker result exists, intervention is allowed only when **all** are true:

```text
FRAME_COLLISION_DIAGNOSTICS build
marker opcode == FIST
stable marker result == UNSUPPORTED_MISSING_SOURCE
actor + instance valid
current C1 generation valid
factual Action == gEAction_SprintAttack / 9
current attack ownership is Family=SPRINT and Hit eligible
matching current motion found
marker scan valid
marker present
at least one authored FIST
no RIGHT / LEFT / BOTH / OFF
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
exact RIGHT source exists
RIGHT UseType == PhysicalFist/raw55
RIGHT current group == Item_Equipped/group5
current StatePosition == 1
same actor + RIGHT source + C1 as EV-281 suppression proof
activation not already used for this proof/C1
```

If any condition fails, do nothing and preserve current behavior.

Do not gate by Troll/BlackTroll identity, species, motion filename, or visual attack name.

A later factual Action2/Power callback must not borrow Sprint activation permission. Eligibility is factual current Action9 + Family SPRINT only.

---

## 6. Exact Diagnostic Intervention

When all eligibility conditions match:

```text
mark the Sprint proof activation-used
request exact RIGHT raw55 source -> Item_Attack/group7 exactly once
```

Use the ordinary source/native setter path so the existing `SetCollisionGroup` hook and `CollisionLifecycleGuard` observe the real transition and real offense obligation.

The FIST-time request occurs outside the active `_AI_PowerAttack` callback suppression scope, so the EV-281 selective early-suppression rule must not suppress it.

This probe must **not** call `CollisionSourceOperations::ActivateOrRearm()` because that helper also clears triggered contacts.

This probe must issue **no `ClearTriggeredList()`**.

The purpose is to isolate physical activation from contact rearm. If group7 appears but damage does not return, that is evidence for a separate Sprint rearm/contact question, not permission to add custom damage.

---

## 7. Modular Ownership

`EngineBridge` remains the sole hook owner and transport layer.

The existing reserved-marker path already calls:

```text
PhysicalFistProbe::OnMarkerProcessed(actor, markerOpcode, result)
```

Therefore no `EngineBridge` source change is expected or desired.

`PhysicalFistProbe` owns all temporary Sprint research state/policy:

```text
Sprint early-suppression proof
same actor/source/C1 validation
exact Sprint/FIST eligibility
one-shot marker-time activation decision
exact RIGHT raw55 group request
compact probe logging
```

Do not move Sprint policy/state into `EngineBridge`.

---

## 8. Diagnostic Logging

Keep existing:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION
CORE RAW55_SPRINT_CALLBACK_BOUNDARY
```

Add one compact record for each actual authored-FIST activation intervention:

```text
CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE
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

Existing `CORE COLLISION_GROUP`, marker result, `CORE ONDAMAGE`, and C1 lifecycle logs remain the factual outcome evidence.

---

## 9. Protected / Forbidden Boundary

Preserve unchanged:

```text
closed Quick behavior and Quick research state
closed true-Power behavior/research state
closed Normal behavior/research state
Sprint original callback exactly once
EV-281 Sprint early selective suppression
raw8 FIST and raw8 Sprint
FrameCollisionMarkers semantics
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations semantics
AttackMotionRouting
```

Do not add:

```text
whole Sprint callback suppression
ClearTriggeredList for Sprint
custom/direct damage
StatePosition write
SPU+0x164 write
manual cleanup compensation
raw8 timing permission
new hook/RVA/timer/polling/per-frame scan
species/name/filename policy
permanent PhysicalFistCollision
Quick/Power/Normal behavior changes
release-module promotion
```

No permanent production raw55 design is authorized by this probe.

---

## 10. Required Static Audit

Before publication verify:

```text
EV-281 Sprint selective suppression remains unchanged
original Sprint callback still executes exactly once
new intervention occurs only on exact FIST marker path
stable ProcessMarker semantics unchanged
same actor/source/C1 prior-suppression proof required
Action9 / Family SPRINT / Hit eligibility required
StatePosition 1 required
one activation maximum per proof/C1
only exact RIGHT PhysicalFist/raw55 group5 source can be requested to group7
real request passes through ordinary SetCollisionGroup/lifecycle observation
no ClearTriggeredList call added
no custom damage or cleanup added
Quick/Power/Normal/raw8 unchanged
later factual Action2 cannot borrow Sprint permission
EngineBridge unchanged if existing marker delegation is sufficient
no new hook/RVA/CMake change
```

Build execution is not authorized by this contract.

---

## 11. Local Runtime Test

After Normal Chat source review, User + Normal Chat build/deploy `Script_FrameCollisionTest`.

Preferred artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation.log
```

Minimum useful run:

```text
one or more factual Family=SPRINT / Action9 Troll executions
incidental Quick/Power/Normal traffic is harmless
User does not need to identify the family visually
```

Correlate each Sprint C1:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION
CORE RAW55_SPRINT_CALLBACK_BOUNDARY
stable FIST marker result
CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE
CORE COLLISION_GROUP
CORE ONDAMAGE
C1 cleanup/finalization/repair
```

Also check whether a later factual Action2 appears in the same PowerAttack-named motion. If so, keep it factually separate from Sprint and do not treat it as Sprint activation evidence.

Interpretation:

### A — activation alone sufficient

```text
early native 5 -> 7 suppressed
StatePosition 0 -> 1 preserved
RIGHT stays5 until FIST
FIST probe performs real 5 -> 7
native contact/damage can occur after authored opening
native cleanup returns 7 -> 5
C1 obligation fulfilled without terminal repair
```

### B — group opens but damage does not return

Physical authored activation is proven, but activation alone is insufficient. The next question becomes a separate Sprint contact/rearm primitive: whether one exact `TouchDamage.ClearTriggeredList()` after successful authored-FIST opening is required. Do not combine that intervention into this probe.

### C — cleanup/lifecycle diverges

Do not normalize terminal repair into the feature. Isolate the lifecycle issue first.

### D — FIST request fails to become group7

The source-mutation boundary remains unresolved; do not compensate elsewhere.

---

## Stop Boundary

After one adequate runtime capture, Normal Chat promotes the evidence and freezes only the next smallest causal responsibility. Do not implement permanent raw55 behavior or another family change in the same task.
