# Gothic 3 Animation Behaviors — RAW55 Normal Pre-State Contact-Rearm Probe

**Status:** FROZEN DIAGNOSTIC CONTRACT  
**Date:** 2026-09-15  
**Scope:** diagnostics-only `Script_FrameCollisionTest`

## Purpose

Close the remaining Normal pre-StatePosition contact question exposed by EV-286.

EV-286 proves that an authored Normal FIST at `StatePosition == 0` is transported correctly and can physically open the exact current RIGHT PhysicalFist/raw55 source `5 -> 7` before Gothic reaches its ordinary Normal collision timing. Across the canonical run, representative Normal C1s 19, 21 and 23 all perform the same early marker-owned opening with `ClearTriggeredList=0`. Gothic later reaches its native Normal threshold around `StateTime ~= 0.25`, requests `7 -> 7`, advances `StatePosition 0 -> 1`, and later one native damage event occurs on the second physical swing. The frame-15 FIST is delivered but receives no Normal repeat intervention.

The remaining causal question is therefore not marker transport or source mutation. It is whether the early authored opening requires one exact triggered-list rearm to create an immediate first-contact opportunity before Gothic's native Normal transition.

This is a temporary diagnostic experiment only. It does not authorize permanent raw55 behavior.

---

## Single Causal Question

For the already-proven exact Normal SP0 FIST path:

```text
authored FIST at StatePosition 0
-> exact current RIGHT PhysicalFist/raw55 5 -> 7 succeeds
```

is adding exactly one:

```text
rightSource.TouchDamage.ClearTriggeredList()
```

immediately after that successful opening sufficient to allow the first physical swing to damage before Gothic reaches its native Normal `7 -> 7 / StatePosition 0 -> 1` transition?

Change no other causal variable.

---

## Exact Eligibility

Reuse the existing `TryApplyNormalPreStateFistProbe()` eligibility and identity from implementation `a99f4aa616c905c4eb66c72bdaa27709c9b75c77` unchanged:

```text
diagnostics build
actor/instance valid
valid current C1 generation
markerOpcode == FIST
result.opcode == FIST
stable result == UNSUPPORTED_MISSING_SOURCE
factual Action == gEAction_Attack / 1
Family NORMAL / Hit eligible
matching current motion found
marker scan valid
marker present
>=1 FIST
no RIGHT / LEFT / BOTH / OFF markers
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
exact current RIGHT source exists
result RIGHT == current RIGHT
RIGHT UseType == PhysicalFist/raw55
RIGHT current group == Item_Equipped/group5
StatePosition == 0
no prior Normal pre-state intervention for this exact actor + C1 + RIGHT source
```

Do not add species/name/motion-prefix/timer policy.

---

## Exact Intervention

Preserve the existing one-shot SP0 physical opening:

```text
rightSource.SetCollisionGroup(Item_Attack / 7)
read groupAfter
```

Then change exactly one causal variable:

```text
ONLY if groupAfter == Item_Attack / 7:
    rightSource.TouchDamage.ClearTriggeredList()
    exactly once
```

The clear must occur only after the successful exact SP0 marker-owned opening and must remain bound to the same actor + C1 generation + RIGHT source one-shot intervention.

Do not use `CollisionSourceOperations::ActivateOrRearm()`; keep the causal operations explicit.

Do not call custom damage, `TriggerTarget`, or `OnDamage`.

---

## Native Normal Progression Must Remain Untouched

After the SP0 marker intervention, the original `_AI_Attack` callback continues normally.

Preserve and observe Gothic's later native sequence:

```text
RIGHT already group7
native Normal threshold reached
native request 7 -> 7
StatePosition 0 -> 1
```

Do not suppress the native `7 -> 7` request.

Do not write StatePosition.

Do not modify the Normal early-suppression rule. Its existing gate already requires `beforeGroup == Item_Equipped/group5`, so it naturally does not suppress this later `7 -> 7` request.

---

## Second Marker Must Remain Outside This Probe

The current Troll fixture contains FIST markers at animation frames 1 and 15.

This probe changes only the first SP0 occurrence.

The later frame-15 FIST must remain observational only for Normal in this task:

```text
no Normal repeat rearm
no second ClearTriggeredList
no second group request
no new repeated-marker policy
```

The separate non-Quick repeated-FIST question remains future work after this first-contact causal boundary closes.

---

## Diagnostic Logging

Keep the existing marker/group/callback/lifecycle diagnostics.

The actual SP0 intervention record must truthfully show the new causal variable. Either update the existing:

```text
CORE RAW55_NORMAL_PRESTATE_FIST_PROBE
```

record so that it reports:

```text
ClearTriggeredList=1
PRESTATE_FIST=1
PRESTATE_REARM=1
```

or emit an additional compact dedicated record:

```text
CORE RAW55_NORMAL_PRESTATE_REARM_PROBE
```

with at minimum:

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
ClearTriggeredList=1
PRESTATE_REARM=1
```

Do not leave a diagnostic claiming `ClearTriggeredList=0` when the clear actually occurred.

---

## Protected Boundaries

Preserve unchanged:

```text
existing Normal SP0 exact source eligibility/one-shot identity
existing Normal SP1 activation path
existing Normal selective early 5 -> 7 suppression
original Normal callback
Quick raw55 behavior and research state
Power raw55 behavior and research state
Sprint raw55 behavior and research state
raw8 FIST
FrameCollisionMarkers semantics
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations semantics
equipped RIGHT / LEFT / BOTH / OFF marker behavior
native cleanup
```

Do not add:

```text
Normal second-marker rearm
Power/Sprint repeat-FIST behavior
StatePosition write
custom/direct damage
manual cleanup/repair
SPU+0x164 write
raw8 timing permission
new hook/RVA/timer/polling/per-frame scan
species/name/filename policy
permanent PhysicalFistCollision
New Balance compatibility changes
Raise/speed work
```

---

## Expected Source Scope

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h` should not be required unless a real source contradiction demands it.

`EngineBridge.cpp` must remain unchanged. No CMake change is expected.

If a real API/source contradiction prevents the bounded implementation, stop and report it rather than broadening scope.

---

## Required Static Audit

Before publication verify:

```text
only the existing eligible Normal SP0 path gains one ClearTriggeredList
clear occurs only after verified groupAfter == 7
maximum one clear per exact actor/C1/RIGHT SP0 intervention
no second-marker Normal rearm added
original Normal callback still runs exactly once per invocation
later native 7 -> 7 remains unsuppressed
no StatePosition write
no damage call
no cleanup/repair change
Quick/Power/Sprint/raw8 unchanged
FrameCollisionMarkers and lifecycle semantics unchanged
EngineBridge unchanged
no new hook/RVA/CMake change
```

Build execution is not authorized by this contract.

---

## Runtime Fixture

Use the same Troll Normal animation content already validated in EV-286, with authored FIST at frames 1 and 15 and geometry known by the User to permit two physical contacts when contact eligibility is available.

Preferred artifact:

```text
research/raw/2026.09.15_troll_raw55_normal_prestate_rearm.log
```

Correlate each factual Normal C1:

```text
frame-1 FIST at SP0
-> exact RIGHT 5 -> 7
-> ClearTriggeredList=1
-> observe whether ONDAMAGE occurs before native Normal 7 -> 7 / SP0 -> 1
-> later frame-15 FIST remains no-op for Normal
-> observe later contact/damage
-> native 7 -> 5 cleanup
-> clean C1 finalization
```

### Interpretation A — rearm is sufficient

If native `ONDAMAGE Target=PC_Hero` occurs after the SP0 marker/clear but before the native Normal threshold / `StatePosition 0 -> 1`, then the missing early-contact primitive is triggered-list rearm. Normal can own the first authored opportunity at SP0 without waiting for the native timer.

### Interpretation B — rearm is not sufficient

If SP0 `5 -> 7` plus one exact clear succeeds but no damage can occur until after Gothic reaches the native `7 -> 7 / StatePosition 0 -> 1` transition, then Normal has an additional native state/timing eligibility gate. Stop and isolate that gate next; do not add damage code or force StatePosition.

### Interpretation C — lifecycle/progression diverges

If the clear causes StatePosition, native callback, cleanup, or C1 finalization divergence, stop and analyze. Do not compensate in the same probe.

---

## Stop Boundary

After one adequate runtime capture, Normal Chat closes the evidence transaction and freezes only the next smallest causal responsibility.

Do not implement Normal repeat-FIST, Power/Sprint repeat-FIST, Sprint Action9 -> Action2 repeat ownership, or permanent raw55 architecture in the same task.
