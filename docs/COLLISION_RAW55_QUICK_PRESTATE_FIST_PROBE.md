# Gothic 3 Animation Behaviors — RAW55 Quick Pre-State FIST Activation Probe

**Status:** FROZEN DIAGNOSTIC CONTRACT  
**Date:** 2026-09-12  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Close the marker-ordering gap exposed by EV-268.

The current temporary raw55 Quick probe works only when authored `G3AB_COL_FIST` arrives after the native Quick callback has already attempted its early raw55 opening and advanced StatePosition to 1. User-authored timing controls prove that this is a limitation of the probe, not a failure of frame-effect transport:

```text
FIST at animation frame 4:
    native early 5 -> 7 attempt occurs first and is suppressed
    native StatePosition advances 0 -> 1
    FIST arrives later at StatePosition 1
    authored 5 -> 7 + ClearTriggeredList executes
    Quick damage occurs

FIST at animation frame 1:
    FIST is observed with valid C1 and factual RIGHT TrollFist/raw55
    FIST arrives while StatePosition is still 0
    no prior early-suppression proof exists yet
    current probe therefore does not intervene
    later native 5 -> 7 attempt is suppressed and StatePosition advances 0 -> 1
    no second FIST opportunity occurs
    no raw55 opening / no damage
```

This probe asks whether the exact authored FIST event can own raw55 activation/rearm immediately even when it arrives before the native Quick StatePosition transition.

This is not a production implementation.

---

## Single Causal Question

For an exact marked factual raw55 Quick execution whose authored FIST arrives while the current C1 is valid but before the native early raw55 request / StatePosition `0 -> 1` transition, is one immediate exact RIGHT raw55 `5 -> 7` request plus one exact `TouchDamage.ClearTriggeredList()` sufficient to make collision active from that authored frame while allowing the later original Quick callback to preserve native StatePosition progression and native cleanup?

The frame-1 Troll fixture from EV-268 is the primary runtime fixture.

---

## Exact Eligibility

At `PhysicalFistProbe::OnMarkerProcessed()`, permit this temporary pre-state path only when all are true:

```text
diagnostics build
actor/instance valid
valid current C1 generation
markerOpcode == FIST
result.opcode == FIST
stable result == UNSUPPORTED_MISSING_SOURCE
Quick Hit eligible
matching current motion found
marker scan valid
marker present
>=1 FIST
no RIGHT / LEFT / BOTH / OFF markers
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
factual current RIGHT source exists
result RIGHT source == current actor RIGHT source
RIGHT UseType == gEUseType_PhysicalFist / raw55
RIGHT current group == Item_Equipped / 5
StatePosition == 0
no pre-state FIST intervention already used for this actor/C1/source
```

No species/name/file-prefix policy.

Do **not** require an EV-265 early-suppression proof for this path; EV-268 proves the authored FIST can occur before such a proof exists.

The intervention identity must be keyed to the exact actor instance + factual RIGHT source instance + C1 generation and be one-shot.

---

## Exact Intervention

For the eligible pre-state FIST event, exactly once:

```text
mark pre-state FIST intervention used
request rightSource.SetCollisionGroup(Item_Attack / 7)
read groupAfter

ONLY if groupAfter == Item_Attack / 7:
    rightSource.TouchDamage.ClearTriggeredList()
    exactly once
```

Use the ordinary setter path so `EngineBridge` and `CollisionLifecycleGuard` observe the real physical request.

Do not use `CollisionSourceOperations::ActivateOrRearm()`; keep the causal operations explicit.

Do not call custom damage / TriggerTarget / OnDamage.

---

## Later Native Quick Request — Observe, Do Not Hide

After a successful pre-state FIST opening, the original `_AI_QuickAttack` callback must continue executing normally.

The later native raw55 request may now arrive while RIGHT is already group7, producing an observed native request shaped like:

```text
requested group7
before group7
result group7
```

Do **not** add a new suppression rule for that `7 -> 7` request in this probe.

Do **not** modify `CollisionLifecycleGuard` to conceal it. The guard may record another successful offense request because its existing contract treats requested/resulting group7 as an offense request. That is an expected diagnostic consequence of this causal probe, not authorization to redesign lifecycle bookkeeping.

The authoritative questions are:

```text
Does authored frame-1 FIST physically open 5 -> 7?
Does ClearTriggeredList execute exactly once?
Can native OnDamage occur after that authored opening when contact exists?
Does the original Quick callback still advance StatePosition 0 -> 1?
Does Gothic later clean the physical source 7 -> 5?
Does C1 end with no outstanding obligation / repair?
```

If the later native request is instead again `5 -> 7`, treat that as a contradiction/state divergence and return to Normal Chat; do not compensate.

---

## Relationship to Existing EV-265 / EV-267 Paths

The existing post-state path remains unchanged for FIST markers that arrive after EV-265 proof and at StatePosition 1.

For a pre-state FIST execution:

```text
FIST itself opens raw55 before native early request
there is therefore no need for EV-265 suppression proof as the activation authority
later native callback continues naturally
```

Do not manufacture an early-suppression proof merely to satisfy the older post-state path.

Ensure one C1 cannot receive both the new pre-state intervention and a later second probe-owned FIST activation/rearm.

---

## Diagnostic Tag

Add a compact diagnostic:

```text
CORE RAW55_QUICK_PRESTATE_FIST_PROBE
```

Minimum fields:

```text
Actor
C1
Action
StatePosition
StateTime
Right
RightUseType
GroupBefore
RequestedGroup
GroupAfter
ClearTriggeredList=1|0
PRESTATE_FIST=1
```

Existing callback-boundary / group / lifecycle / damage diagnostics remain authoritative.

---

## Protected Boundaries

Do not change:

```text
FrameCollisionMarkers semantics or acceptance
Raw8FistCollision
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations
CMake target/source separation
hook RVAs / hook ownership
raw8 behavior
equipped RIGHT / LEFT / BOTH / OFF behavior
Normal/Sprint raw55 diagnostic behavior
native cleanup
contact geometry / body physics
animation assets / marker placement in code
```

Do not add:

```text
custom/direct damage
manual TriggerTarget / OnDamage
StatePosition write
SPU+0x164 write
manual cleanup
new suppression for native 7 -> 7
second probe-owned group7 request in the same C1
second ClearTriggeredList in the same C1
species/name policy
new hook/RVA/timer/polling/per-frame scan
permanent PhysicalFistCollision
```

---

## Expected Source Scope

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

`EngineBridge.cpp` should not need a new seam: the existing diagnostics-only marker delegation and SetCollisionGroup hook are sufficient.

No CMake change is expected.

If a real API/source contradiction prevents this bounded implementation, stop and report rather than broadening scope.

---

## Runtime Test Shape

Primary fixture:

```text
Troll QuickAttackR / QuickAttackL
G3AB_COL_FIST authored at animation frame 1
```

Test several Quick attacks at close and ordinary contact distance.

The decisive expected sequence is:

```text
FIST observed while StatePosition=0
CORE COLLISION_GROUP ... TrollFist ... Requested=7 Before=5 After=7
CORE RAW55_QUICK_PRESTATE_FIST_PROBE ... StatePosition=0 ... GroupAfter=7 ClearTriggeredList=1
later original Quick callback remains healthy
CORE RAW55_QUICK_CALLBACK_BOUNDARY ... StatePosition=0->1 ... RightGroup=7->7
native contact/damage may occur whenever geometry overlaps during the now-open window
later native cleanup 7 -> 5
C1 closes without repair
```

### Interpretation A — pre-state FIST works

Frame-1 authored timing can open/rearm raw55 before the native Quick transition while preserving native StatePosition and cleanup. The previous frame-1 failure was solely a temporary-probe proof/state gate.

### Interpretation B — physical opening succeeds but damage remains state-gated

If `5 -> 7` + clear succeeds at StatePosition 0 but damage cannot occur until/after the native transition, then another native damage-eligibility state exists. Isolate it next; do not add damage code.

### Interpretation C — StatePosition/lifecycle/cleanup diverges

Stop and analyze. Do not compensate in the same probe.

---

## Frame-0 Boundary

EV-268 proves frame-1 marker transport only. It does **not** prove frame-0 ordering.

After this frame-1 causal question passes, the same diagnostic build may be used for a separate observational frame-0 run. If frame 0 occurs before a valid C1 exists, that is a distinct execution-order question and must not be silently folded into the frame-1 result.

---

## Production Boundary

A PASS does not yet authorize permanent `PhysicalFistCollision` or Normal/Sprint generalization.

The eventual production design must be able to honor authored marker timing independently of the incidental order in which native Quick reaches its own StatePosition/collision request, while preserving native callback progression and cleanup.