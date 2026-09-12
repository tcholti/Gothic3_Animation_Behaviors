# Raw55 PhysicalFist Quick Authored-FIST Contact-Rearm Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-12

## Purpose

Answer one causal question after EV-266 and before any permanent raw55 implementation is designed:

> With the EV-265 early Quick raw55 `5 -> 7` request still selectively suppressed, native Quick StatePosition progression preserved, and the EV-266 authored-FIST `5 -> 7` activation retained, is one exact `TouchDamage.ClearTriggeredList()` on that same RIGHT raw55 source immediately after successful FIST-time activation sufficient to restore Gothic's native contact/damage while preserving clean native `7 -> 5` cleanup?

This is a temporary diagnostics-only intervention. It does not make raw55 FIST a production-supported marker path.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.  
Governing evidence: `EVIDENCE_LEDGER_265_ONWARD.md` EV-265–EV-266.

---

## 1. Evidence Boundary

EV-265 proved:

```text
exact early RIGHT raw55 5 -> 7 request suppressed
original _AI_QuickAttack still runs
StatePosition 0 -> 1 preserved
RIGHT remains group5
```

EV-266 then proved:

```text
authored FIST arrives at StatePosition 1
exact RIGHT raw55 5 -> 7 request succeeds at the authored frame
real C1 offense obligation is created
source remains group7 through the intended late Quick window
native cleanup returns 7 -> 5
C1 obligation is fulfilled without repair
BUT no Troll/BlackTroll damage to PC_Hero occurs
```

Therefore source activation and cleanup are no longer the unknowns for this Quick path. The remaining causal question is contact/rearm eligibility.

`ClearTriggeredList()` is not a proven universal Fist mechanism. EV-233 remains authoritative for raw8 and must not be reinterpreted. This probe tests only the factual raw55 TouchDamage source in the preserved Quick context.

---

## 2. Single Probe Question

For an exact marked factual raw55 Quick execution that has already demonstrated the EV-265 early-suppression proof in the same C1 generation and reaches the EV-266 authored-FIST activation point:

```text
authored G3AB_COL_FIST occurs
+ current family is factual Quick Hit
+ native StatePosition == 1
+ exact RIGHT PhysicalFist/raw55 source is group5
+ same actor + RIGHT source + C1 as early-suppression proof
= request exact RIGHT raw55 group7 once

if and only if that request physically succeeds to group7:
    clear that exact source's TouchDamage triggered list exactly once
```

Do not perform any other contact/damage intervention.

The hoped-for causal shape is:

```text
early callback:
    native 5 -> 7 request suppressed
    StatePosition 0 -> 1
    RIGHT remains 5

authored FIST:
    exact RIGHT raw55 5 -> 7 succeeds
    exact RIGHT raw55 TouchDamage.ClearTriggeredList() executes once

then Gothic:
    owns target/contact/damage
    owns ordinary 7 -> 5 cleanup
```

---

## 3. Stable Marker Boundary Must Remain Unchanged

`FrameCollisionMarkers::ProcessMarker()` must remain unchanged. Raw55 FIST must still return the existing stable `MarkerResult_UnsupportedMissingSource` result because the stable FIST resolver remains the proven raw8 resolver.

The probe must not:

```text
change ProcessMarker acceptance
replace/generalize the raw8 resolver
pretend raw55 FIST was accepted
consume stable marker occurrence budget for raw55
call Raw8FistCollision for raw55
write marker-owned Quick StatePosition
```

The temporary raw55 intervention remains diagnostics-only after the stable marker result exists.

---

## 4. Required Prior-Proof State

Continue using the bounded `PhysicalFistProbe` proof record created only when the existing EV-265 early Quick suppression actually occurs.

The record must remain tied to:

```text
actor instance
C1 generation
exact RIGHT source instance
PhysicalFist/raw55 identity
early suppression actually proven
one-shot FIST intervention state
```

Generation/source mismatch invalidates the proof. No permission carries across attacks.

No species/name, filename-prefix, timer, polling, or global one-shot policy is allowed.

---

## 5. Exact Eligibility

At the reserved FIST marker path, after unchanged stable marker processing, the probe may intervene only when all EV-266 eligibility remains true:

```text
FRAME_COLLISION_DIAGNOSTICS build
marker opcode == FIST
stable marker result == UNSUPPORTED_MISSING_SOURCE
actor valid
current C1 valid and same as proof
current attack is factual Quick Hit
matching current motion found
marker scan valid
marker present
at least one FIST authored
no RIGHT / LEFT / BOTH / OFF authored
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
exact RIGHT source matches proof
RIGHT UseType == PhysicalFist/raw55
RIGHT current group == Item_Equipped/group5
current StatePosition == 1
early-suppression proof exists for same actor/source/C1
FIST intervention not already used for this C1
```

Do not gate by Troll/BlackTroll name, species, motion side, or other content identity.

---

## 6. Exact Diagnostic Intervention

When the full eligibility contract matches:

```text
mark FIST intervention used
request exact RIGHT source -> Item_Attack/group7 through ordinary SetCollisionGroup path
read resulting group

if resulting group == Item_Attack/group7:
    rightSource.TouchDamage.ClearTriggeredList()
    record exactly one probe-owned clear
else:
    do not clear
```

The group request must remain the same ordinary path proven at EV-266 so the existing SetCollisionGroup transport and `CollisionLifecycleGuard` see the real offense request.

Do not call `CollisionSourceOperations::ActivateOrRearm()` in this probe. Calling the exact `TouchDamage.ClearTriggeredList()` directly after the already-proven group request keeps the causal delta from EV-266 to one responsibility only.

No second group request is authorized.

---

## 7. Existing Quick Early Gate Must Stay Active

Preserve EV-265 unchanged:

```text
marked raw55 Quick callback
-> original callback executes exactly once
-> exact scoped early RIGHT raw55 5 -> 7 request suppressed
-> native StatePosition progression remains
```

Also preserve temporary controls:

```text
marked raw55 Normal -> prior whole-callback suppression unchanged
marked raw55 Sprint -> prior whole-callback suppression unchanged
```

The new triggered-list intervention is Quick only.

---

## 8. Modular Ownership

`EngineBridge` remains hook/marker transport only.

`PhysicalFistProbe` owns all temporary raw55 proof state and policy:

```text
early-suppression proof
exact FIST eligibility
one-shot authored group activation
successful-group verification
one exact triggered-list clear
compact probe logging
```

No new hook/RVA is authorized.

`CollisionSourceOperations` remains unchanged. This probe intentionally does not reuse its combined helper because the experimental variable is the clear itself.

---

## 9. Diagnostic Logging

Keep existing causal records:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION
CORE RAW55_QUICK_CALLBACK_BOUNDARY
CORE COLLISION_GROUP
CORE ONDAMAGE
C1 lifecycle records
```

Add/replace the temporary FIST intervention record with:

```text
CORE RAW55_QUICK_FIST_REARM_PROBE
```

Include at minimum:

```text
Actor
C1 generation
Action
StatePosition
StateTime
RIGHT source
RIGHT UseType
GroupBefore
RequestedGroup
GroupAfter
EarlySuppressionProof=1
ClearTriggeredList=1 or 0
REARM_PROBE=1
```

`ClearTriggeredList=1` is allowed only when groupAfter is actually 7.

Do not add broad per-frame logging.

---

## 10. Forbidden Changes

Do not:

```text
change FrameCollisionMarkers
change Raw8FistCollision
change CollisionLifecycleGuard semantics
change CollisionSources
change CollisionSourceOperations
write StatePosition
write SPU+0x164
perform custom/direct damage
change target selection
manually call TriggerTarget / OnDamage
manually force 7 -> 5 cleanup
add Normal/Sprint FIST activation or rearm
add species/name policy
add new hook/RVA/timer/polling/per-frame scan
create permanent PhysicalFistCollision
```

Do not infer from this raw55 probe that raw8 requires `ClearTriggeredList()`.

---

## 11. Diagnostic Build Boundary

All probe state/policy remains in diagnostics-only `PhysicalFistProbe` / `Script_FrameCollisionTest`.

`Script_FrameCollisionBehaviorTest` remains free of `PhysicalFistProbe` and unchanged after preprocessing/source selection.

No CMake change is expected or authorized absent a direct contradiction; if one appears, Work stops and reports it.

---

## 12. Static Audit

Before publication verify:

```text
EV-265 early Quick suppression unchanged
original Quick callback still executes exactly once
EV-266 FIST-time exact RIGHT 5 -> 7 request retained
stable marker result unchanged
same actor/source/C1 proof required
StatePosition 1 required
one FIST intervention maximum per proof record
ClearTriggeredList occurs only after verified groupAfter == 7
exactly one probe-owned clear maximum
no second group7 request
no raw8 change
no custom damage / TriggerTarget / OnDamage call
native cleanup untouched
Normal/Sprint unchanged
no new hooks/RVAs
CMake separation unchanged
```

Build execution is not authorized by this contract.

---

## 13. Runtime Interpretation

### Interpretation A — triggered-list rearm sufficient in tested Quick context

```text
early 5 -> 7 suppressed
StatePosition 0 -> 1 preserved
FIST 5 -> 7 succeeds
one exact ClearTriggeredList executes
native OnDamage to PC_Hero appears after authored opening/rearm when contact occurs
native cleanup 7 -> 5
C1 fulfilled without repair
```

This would prove that the missing EV-266 contact responsibility is restored by triggered-list rearm in this factual raw55 Quick context. It would not yet authorize Normal/Sprint generalization or raw8 reinterpretation.

### Interpretation B — group7 + clear still produces no damage

`ClearTriggeredList()` is insufficient. Do not add another intervention in the same task. Return to Normal Chat and isolate the next native TouchDamage/contact eligibility fact.

### Interpretation C — damage returns but cleanup/lifecycle diverges

Do not normalize C1 repair into the feature. Isolate the cleanup/lifecycle consequence before production design.

### Interpretation D — FIST group request no longer succeeds

Treat as a contradiction with EV-266 and stop rather than compensating elsewhere.

---

## 14. Stop Boundary

After one adequate Troll/BlackTroll runtime capture:

```text
Normal Chat analyzes committed GitHub evidence
-> promotes result canonically
-> either freezes the next single causal question
   or, only when mechanism evidence is sufficient, designs the permanent owner
```

Do not implement permanent `PhysicalFistCollision` in the same Work task.
