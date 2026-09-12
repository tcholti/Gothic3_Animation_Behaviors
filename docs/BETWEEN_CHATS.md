# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 QUICK PRE-STATE FIST WORK TASK

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence now reaches **EV-268**.

No permanent raw55 implementation is authorized.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md
4. EVIDENCE_LEDGER_265_ONWARD.md EV-267–EV-268
5. FEATURE_DEVELOPMENT_METHOD.md
6. WORK_IMPLEMENTATION_PROTOCOL.md
7. only exact source/API files required for this bounded implementation
```

`COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md` is **SUPERSEDED BEFORE IMPLEMENTATION** by EV-268. Do not implement it.

---

## Closed Raw55 Evidence Relevant Here

### EV-267 — delayed authored FIST + rearm restores Quick damage

```text
post-state FIST at ~StateTime 0.48–0.49
exact RIGHT raw55 5 -> 7
one TouchDamage.ClearTriggeredList()
OnDamage returns when contact occurs
native cleanup remains healthy
```

### EV-268 — frame timing closes the prior close-range question and exposes a pre-state gap

Runtime artifacts:

```text
research/raw/2026.09.12_troll_quick_fist_activation_frame_4.log
research/raw/2026.09.12_troll_quick_fist_activation_frame_1.log
```

Frame 4:

```text
native early raw55 request around StateTime ~0.10 is suppressed
native StatePosition advances 0 -> 1
FIST arrives later around StateTime ~0.16 at StatePosition 1
existing EV-267 activation/rearm executes
8 OnDamage events to PC_Hero in the run
User observes native-like early damage and later re-entry damage
```

Frame 1:

```text
FIST itself is observed correctly
valid C1
factual RIGHT TrollFist / PhysicalFist/raw55
StatePosition still 0
FIST occurs before native early raw55 request / suppression proof
current probe does not intervene
later native 5 -> 7 is suppressed and StatePosition advances 0 -> 1
no second FIST opportunity
no RAW55_QUICK_FIST_REARM_PROBE
no OnDamage
```

Source inspection explains the frame-1 failure: current `PhysicalFistProbe::OnMarkerProcessed()` requires an already-existing EV-265 suppression proof and later requires `StatePosition == 1`.

Therefore frame-1 marker transport works; the temporary raw55 proof/state gate is the limitation.

Frame-0 ordering remains unproven.

---

## Frozen Work Responsibility

Authority:

```text
docs/COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md
```

Implement **only** the temporary diagnostics-only pre-StatePosition FIST causal probe frozen there.

Single question:

> When exact marked raw55 Quick FIST arrives with a valid C1/source while StatePosition is still 0 and before the native early raw55 request exists, can that authored FIST immediately perform one exact RIGHT raw55 `5 -> 7` activation plus one exact `TouchDamage.ClearTriggeredList()`, while the later original Quick callback still preserves native StatePosition progression and native cleanup?

### Exact new path

At `PhysicalFistProbe::OnMarkerProcessed()`, add a separate one-shot pre-state path requiring the exact frozen fixture:

```text
FIST / stable UNSUPPORTED_MISSING_SOURCE
Quick Hit
valid matching marker scan
FIST present; no RIGHT/LEFT/BOTH/OFF
requiredSourceMask none
raw8 resolver absent
valid current C1
factual current RIGHT source matches result RIGHT
RIGHT PhysicalFist/raw55
RIGHT group5
StatePosition == 0
no pre-state intervention already used for actor/source/C1
```

Do **not** require an EV-265 early-suppression proof for this pre-state path.

Exactly once:

```text
request RIGHT SetCollisionGroup(Item_Attack / 7)
read groupAfter
if groupAfter == 7:
    RIGHT TouchDamage.ClearTriggeredList()
```

Use the ordinary setter path so the real mutation/lifecycle facts are observed.

### Later native Quick request

The original `_AI_QuickAttack` callback remains untouched and executes normally.

If pre-state FIST already put RIGHT in group7, the later native request may naturally be `7 -> 7`.

Do **not** add a suppression rule for that `7 -> 7` in this task.
Do **not** change `CollisionLifecycleGuard` to hide it.
Observe the existing callback boundary and lifecycle facts.

The decisive required facts are:

```text
pre-state FIST physically opens 5 -> 7
clear executes once
native StatePosition still advances 0 -> 1
contact/damage can occur while the authored window is open
native cleanup later returns 7 -> 5
C1 closes without repair
```

If the later native request unexpectedly sees group5 again, or StatePosition/cleanup diverges, stop and report the contradiction rather than compensating.

---

## Stable Boundaries

Do not change:

```text
FrameCollisionMarkers semantics or acceptance
Raw8FistCollision
CollisionLifecycleGuard semantics
CollisionSources
CollisionSourceOperations
CMake target/source separation
hook RVAs/ownership
raw8 behavior
equipped RIGHT/LEFT/BOTH/OFF
Normal/Sprint raw55 diagnostic behavior
native cleanup
contact geometry / body physics
animation assets / marker placement in code
```

Do not add:

```text
custom/direct damage
TriggerTarget / OnDamage
StatePosition write
SPU+0x164 write
manual cleanup
new native 7 -> 7 suppression
second probe-owned group7 request in same C1
second triggered-list clear in same C1
species/name policy
new hook/RVA/timer/polling/per-frame scan
permanent PhysicalFistCollision
```

---

## Expected Changed Files

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

`EngineBridge.cpp` should not need a new seam. No CMake change is expected.

If the task cannot be implemented within these boundaries because of a real source/API contradiction, stop and report instead of broadening scope.

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

Normal Chat reviews source first. Only after review passes does User + Normal Chat build/deploy/test locally.

---

## Expected Runtime Classification

### A — pre-state FIST works

```text
frame-1 FIST observed at StatePosition 0
5 -> 7 succeeds
one ClearTriggeredList executes
later original Quick callback advances StatePosition 0 -> 1 while RIGHT remains group7
OnDamage can occur when contact exists
native 7 -> 5 cleanup
no repair
```

Then the prior frame-1 failure is closed as a temporary probe ordering limitation.

### B — activation/rearm works but damage remains state-gated

Return to Normal Chat and isolate the remaining native damage-eligibility state.

### C — state/lifecycle/cleanup divergence

Stop and analyze before further intervention.

Frame 0 is a separate follow-up ordering question after frame 1 closes.