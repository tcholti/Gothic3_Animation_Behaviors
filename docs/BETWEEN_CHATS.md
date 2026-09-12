# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 QUICK AUTHORED-FIST ACTIVATION WORK TASK

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence now reaches **EV-265**.

No permanent raw55 implementation is authorized.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md
4. EVIDENCE_LEDGER_265_ONWARD.md EV-265
5. EVIDENCE_LEDGER_250_ONWARD.md EV-262 through EV-264 only as prior causal context
6. FEATURE_DEVELOPMENT_METHOD.md
7. WORK_IMPLEMENTATION_PROTOCOL.md
8. only exact source/API files required for this bounded implementation
```

The earlier callback-suppression, callback-boundary and selective-group probe contracts are closed evidence context. Preserve their current diagnostic behavior only where this task explicitly depends on it.

---

## Closed Raw55 Evidence

### EV-262 — whole-callback suppression

Whole marked-raw55 callback suppression removes the premature opening, but Quick fails because required native state progression is also removed. Whole `_AI_QuickAttack` suppression is rejected.

### EV-264 — Quick callback compound ownership

Repeated Troll/BlackTroll Quick Action 4/5 executions prove the same original `_AI_QuickAttack` invocation contains:

```text
StatePosition 0 -> 1
RIGHT PhysicalFist/raw55 group5 -> group7
```

### EV-265 — Quick responsibilities are separable

Runtime artifacts:

```text
research/raw/2026.09.12_troll_marked_attacks_2.log
research/raw/2026.09.12_black_troll_marked_attacks_2.log
```

Results across 20 Troll + 9 BlackTroll marked Quick executions:

```text
exact early RIGHT raw55 5 -> 7 request suppressed
original Quick callback still executes
StatePosition 0 -> 1 preserved
RIGHT remains group5
FIST later arrives at StatePosition 1
no later physical TrollFist opening
no OnDamage against PC_Hero
no outstanding raw55 obligation / repair / lifecycle issue
```

Therefore the early physical opening and native Quick state progression are independently gateable at the existing `SetCollisionGroup` boundary.

The two EV-265 logs remain **ACTIVE COMPARISON** for the authored-FIST activation follow-up. Earlier raw55 baseline/suppression/callback-boundary logs may also remain in raw until the raw55 design closes.

---

## Frozen Work Responsibility

Authority:

```text
docs/COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md
```

Implement **only** the temporary diagnostics-only Quick authored-FIST activation causal probe frozen there.

Single causal question:

> With the proven EV-265 early Quick raw55 5-to-7 gate still active and the original native Quick callback otherwise unchanged, is one exact RIGHT PhysicalFist/raw55 group5-to-group7 request at the authored `G3AB_COL_FIST` event sufficient to restore Gothic's native contact/damage at authored timing and then receive clean native 7-to-5 cleanup?

### Required behavior

Preserve the EV-265 early gate exactly:

```text
marked factual raw55 Quick callback
-> original _AI_QuickAttack executes exactly once
-> exact scoped early RIGHT raw55 5 -> 7 request suppressed
-> native StatePosition progression remains
```

When that exact early suppression actually occurs, `PhysicalFistProbe` records a bounded per-actor proof keyed to:

```text
actor instance
C1 generation
exact RIGHT source instance
raw55 identity
activation-used state
```

At the later reserved FIST frame effect, after stable `FrameCollisionMarkers::ProcessMarker()` has returned its unchanged result, the probe may intervene only if the full frozen contract matches, including:

```text
marker == FIST
stable result == UNSUPPORTED_MISSING_SOURCE
current family == Quick Hit
matching motion / marker scan valid
FIST authored; no RIGHT/LEFT/BOTH/OFF
requiredSourceMask == none
raw8 resolver absent
exact RIGHT source == PhysicalFist/raw55
RIGHT current group == 5
StatePosition == 1
same actor + RIGHT source + C1 as recorded early-suppression proof
activation not already used for this C1
```

Then, exactly once:

```text
mark activation-used
request exact RIGHT source SetCollisionGroup(Item_Attack / 7)
```

Use the ordinary setter path so existing `EngineBridge` SetCollisionGroup transport and `CollisionLifecycleGuard` observe the real mutation and real offense obligation.

Do **not** use `CollisionSourceOperations::ActivateOrRearm()` because it also calls `ClearTriggeredList()`.

Do **not** issue probe-owned `ClearTriggeredList()`.

Add compact diagnostic:

```text
CORE RAW55_QUICK_FIST_ACTIVATION_PROBE
```

with the exact fields frozen in the probe contract.

---

## Stable Marker Boundary Must Stay Untouched

Current stable raw55 FIST remains unsupported because `FrameCollisionMarkers` routes FIST through the proven raw8 resolver. That behavior is intentional at this research stage.

Do not:

```text
change FrameCollisionMarkers semantics
replace/generalize the raw8 FIST resolver
change MarkerProcessResult to accepted
consume stable marker occurrence budget for raw55
change Raw8FistCollision
write Quick StatePosition
write SPU+0x164
```

`EngineBridge` remains hook transport owner. Its only new responsibility is a diagnostics-only delegation after the existing stable marker result exists.

All raw55 probe policy/state stays in `PhysicalFistProbe`.

---

## Existing Controls Must Stay Unchanged

```text
marked raw55 Normal -> prior temporary whole-callback suppression unchanged
marked raw55 Sprint -> prior temporary whole-callback suppression unchanged
marked raw55 Quick  -> EV-265 selective early 5 -> 7 suppression unchanged
raw8 FIST            -> unchanged
normal equipped markers -> unchanged
```

The new authored-FIST activation intervention is **Quick only**.

---

## Protected Boundaries

Do not change:

```text
Raw8FistCollision
FrameCollisionMarkers behavior/semantics
CollisionLifecycleGuard behavior/semantics
CollisionSources behavior/semantics
CollisionSourceOperations
CMake target/source separation
hook RVAs/ownership
raw8 behavior
equipped RIGHT/LEFT/BOTH/OFF behavior
contact/target/damage implementation
```

Do not add:

```text
new hook/RVA
timer/polling/per-frame scan
custom damage
manual cleanup
ClearTriggeredList
species/name policy
permanent PhysicalFistCollision
Normal/Sprint authored-FIST activation
```

---

## Expected Changed Files

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

No CMake change is expected. If the frozen task cannot be implemented within these boundaries because of a real source/API contradiction, stop and report it instead of broadening scope.

---

## Work Stop / Report

Follow `WORK_IMPLEMENTATION_PROTOCOL.md`:

```text
read frozen authorities
-> inspect only necessary source/API
-> implement bounded diagnostic probe
-> static/source audit
-> commit + push to docs/collision-source-evidence
-> report final remote SHA, changed files, concise result,
   build status, material contradiction if any
-> STOP
```

**Build execution is NOT authorized.**

Normal Chat reviews the source first. Only after review passes does User + Normal Chat build/deploy/test locally.

---

## Expected Runtime After Review/Build

A successful causal shape would be:

```text
early callback 5 -> 7 suppressed
callback preserves StatePosition 0 -> 1 / group5
stable FIST remains unsupported
probe FIST intervention requests real RIGHT raw55 5 -> 7
physical source becomes group7 at authored timing
contact/damage, when contact occurs, happens only after that opening
native cleanup 7 -> 5
C1 obligation fulfilled without repair
```

If group7 opens but damage does not return, investigate native contact/rearm state rather than adding custom damage.

If cleanup fails, isolate cleanup rather than treating C1 repair as feature behavior.

Broader raw55 family design remains paused until this Quick-only causal question closes.
