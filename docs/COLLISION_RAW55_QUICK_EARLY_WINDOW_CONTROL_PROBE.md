# Gothic 3 Animation Behaviors — RAW55 Quick Early-Window Control Probe

**Status:** FROZEN DIAGNOSTIC CONTRACT  
**Date:** 2026-09-12  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Close one causal question left by EV-267:

> Is the close-range marked/native damage-coverage difference explained by the late authored FIST activation window, or does a separate geometry/contact-state difference remain even when the same marked Quick animation is allowed to use native early raw55 timing?

EV-267 proves that, after the EV-265 early gate, authored FIST `5 -> 7` plus one exact `TouchDamage.ClearTriggeredList()` can restore raw55 Quick damage when contact occurs after the marker. It also records a close-range divergence: the User could be damaged by native Troll Quick while standing very close, but marked Quick only damaged when positioned so the fist reached the player after the authored opening.

The current logs identify the same factual RIGHT `TrollFist` / PhysicalFist/raw55 source in both marked and native Quick. They do not expose the geometric extent of that source. The strongest remaining variable is timing:

```text
native Quick: early raw55 5 -> 7 near the beginning of Hit
marked EV-267: early request suppressed; authored FIST opens raw55 around StateTime ~0.47–0.49
```

This probe changes only that timing ownership for the exact marked Quick control.

---

## Single Causal Question

For an exact marked factual raw55 Quick execution, if the original `_AI_QuickAttack` callback is allowed to perform its own early RIGHT raw55 `Item_Equipped/group5 -> Item_Attack/group7` request exactly as native code requests it, while the later diagnostic FIST activation/rearm intervention is disabled for that execution, does very-close-range damage return?

Interpretation:

### A — close-range damage returns

Timing-window explanation supported:

```text
same marked animation + marker metadata
same factual raw55 source
native early group opening restored
close-range damage restored
```

Do not infer a special whole-limb or whole-body source. The EV-267 authored marker simply starts the damage window too late for very-close proximal-limb overlap in the tested animation.

### B — close-range damage still absent

Timing alone is insufficient. The next research question must isolate a geometry/contact-state difference without changing damage code.

### C — lifecycle or state divergence

If allowing the native early opening causes an unexpected StatePosition/lifecycle difference, stop and analyze that contradiction before any geometry conclusion.

---

## Exact Eligibility

Use the same factual marked raw55 Quick fixture already proven by EV-264–EV-267:

```text
actor/instance valid
SPU valid and SPU self == actor
valid current C1 generation
Quick Hit eligible
matching current motion
valid marker scan
marker present
>=1 FIST
no RIGHT / LEFT / BOTH / OFF markers
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
RIGHT source exists
RIGHT source UseType == gEUseType_PhysicalFist / raw55
RIGHT current group == Item_Equipped / 5
```

No species/name/file-prefix policy.

---

## Required Diagnostic Behavior

Preserve the original Quick callback exactly once.

For the exact nested RIGHT raw55 `5 -> 7` request that EV-265/EV-267 currently suppress:

```text
DO NOT suppress it in this control probe.
DO NOT create an EV-265 early-suppression proof record for this execution.
Allow the existing EngineBridge SetCollisionGroup hook to continue its normal path:
    call original SetCollisionGroup
    observe actual result
    let CollisionLifecycleGuard observe the real offense request
```

The current Quick callback boundary observation remains active so the log still shows native StatePosition and group progression.

Because no early-suppression proof is created, the existing FIST-time `PhysicalFistProbe::OnMarkerProcessed()` intervention must not perform the EV-267 authored activation/rearm for this execution. Stable `FrameCollisionMarkers` behavior remains unchanged; raw55 FIST may still report `UNSUPPORTED_MISSING_SOURCE`.

Do not issue a probe-owned `ClearTriggeredList()` in this control execution. The point is to restore native early physical timing, not combine it with EV-267 rearm behavior.

---

## Reentrancy / Proof Hygiene

Before allowing the exact early control request for an actor/C1, retire or invalidate any stale diagnostic early-suppression proof that could otherwise let a later FIST event intervene in the same execution.

Do not broaden proof cleanup outside `PhysicalFistProbe`.

---

## Diagnostic Tag

Add a compact diagnostic before allowing the exact request:

```text
CORE RAW55_QUICK_EARLY_WINDOW_CONTROL
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
BeforeGroup
RequestedGroup
ALLOW_EARLY=1
FIST_INTERVENTION=0
```

Existing:

```text
CORE RAW55_QUICK_CALLBACK_BOUNDARY
CORE COLLISION_GROUP
CORE C1 OFFENSE REQUEST
CORE C1 CLEANUP FULFILLED
CORE ONDAMAGE
```

remain the authoritative downstream facts.

---

## Protected Boundaries

Do not change:

```text
FrameCollisionMarkers semantics
Raw8FistCollision
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations
CMake target/source separation
hook RVAs or hook ownership
raw8 behavior
equipped RIGHT / LEFT / BOTH / OFF behavior
Normal/Sprint raw55 diagnostic behavior
native cleanup
contact geometry
physics/body collision
animation asset or marker placement in code
```

Do not add:

```text
custom/direct damage
manual TriggerTarget / OnDamage
StatePosition write
SPU+0x164 write
manual cleanup
second group7 request
ClearTriggeredList for this control
new hook/RVA
timer/polling/per-frame scan
species/name policy
permanent PhysicalFistCollision
```

---

## Expected Source Scope

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h` may change only if directly necessary for clean temporary state. `EngineBridge.cpp` should not require a new hook or policy path; its existing suppression query and SetCollisionGroup transport should remain sufficient.

No CMake change is expected.

---

## Runtime Test Shape

After Normal Chat source review and local build/deploy:

Use one Troll first. The goal is not a broad combat regression.

1. Same marked Quick animations used in EV-267.
2. Stand very close, reproducing the position where EV-267 authored-FIST Quick did not damage because the fist passed beyond the player.
3. Let several Quick attacks occur.
4. Also step back for a few attacks as a sanity control.
5. Do not attack the Troll unless needed to vary AI behavior; if you do, record that in the handoff.

One compact Troll log is sufficient if the close-range result is clear. BlackTroll replication is optional unless the Troll result is ambiguous or contradictory.

---

## Decisive Expected Shapes

Timing explanation supported:

```text
CORE RAW55_QUICK_EARLY_WINDOW_CONTROL ... BeforeGroup=5 RequestedGroup=7 ALLOW_EARLY=1 FIST_INTERVENTION=0
CORE COLLISION_GROUP ... TrollFist ... Requested=7 Before=5 After=7
CORE RAW55_QUICK_CALLBACK_BOUNDARY ... StatePosition=0->1 ... RightGroup=5->7
CORE ONDAMAGE ... Target=PC_Hero
...
CORE COLLISION_GROUP ... Requested=5 Before=7 After=5
CORE C1 CLEANUP FULFILLED ... Outstanding=0
```

If close-range damage is visually restored under that shape, timing is sufficient to explain the observed EV-267 coverage difference.

If the exact same early physical path occurs but close-range damage remains absent, do not compensate. Return to Normal Chat for a geometry/contact-state probe.

---

## Production Boundary

This is a diagnostic control only.

A timing PASS does not authorize blindly moving every raw55 FIST marker earlier. Marker placement remains animation-specific authoring. A future permanent raw55 owner, if frozen, must preserve the proven separation between:

```text
native Quick StatePosition progression
early native physical opening ownership
authored activation timing
raw55 triggered-list rearm
native cleanup
```

Normal/Sprint remain outside this Quick-only mechanism proof.
