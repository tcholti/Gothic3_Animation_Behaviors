# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 QUICK PRE-STATE FIST RUNTIME TEST

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence remains **EV-268**.

No permanent raw55 implementation is authorized.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md
4. EVIDENCE_LEDGER_265_ONWARD.md EV-267–EV-268
5. only exact source/log material needed for the runtime result
```

`COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md` was **SUPERSEDED BEFORE IMPLEMENTATION** by EV-268. Do not implement or run that stale control.

---

## Implementation / Build Checkpoint

Frozen pre-state probe implementation:

```text
commit: 0bfb2ba13ba91488570a41592504ac84428def2a
changed file:
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Normal Chat source review: **PASS**.

Local User build on 2026-09-12:

```text
git rev-parse HEAD
= 0bfb2ba13ba91488570a41592504ac84428def2a

cmake --build build --config Release --target Script_FrameCollisionTest
= PASS

output DLL:
build/prototypes/Script_FrameCollisionTest/Release/Script_FrameCollisionTest.dll
```

The observed `C5105` Windows SDK warning is non-fatal and did not prevent successful compilation/linking.

User reports the built diagnostic DLL has been copied to the Gothic 3 runtime `scripts` directory.

**Runtime test has NOT yet been executed. Do not promote new evidence until that test is complete.**

---

## Closed Evidence Relevant to Tomorrow

### EV-267 — delayed FIST + rearm restores Quick damage

```text
post-state FIST
RIGHT raw55 5 -> 7
one TouchDamage.ClearTriggeredList()
OnDamage returns when contact occurs
native cleanup remains healthy
```

### EV-268 — frame timing / pre-state boundary

Frame 4:

```text
native early raw55 request is suppressed around StateTime ~0.10
StatePosition advances 0 -> 1
FIST follows around StateTime ~0.16
existing post-state activation/rearm executes
run contains 8 OnDamage events to PC_Hero
User observes native-like early and late re-entry damage
```

Frame 1:

```text
FIST is observed correctly
valid C1
RIGHT TrollFist / PhysicalFist/raw55
StatePosition still 0
no prior EV-265 suppression proof exists
old probe therefore does not intervene
later native 5 -> 7 is suppressed while StatePosition advances 0 -> 1
no second FIST opportunity
no damage
```

Conclusion:

```text
frame-1 marker transport works
previous failure was the temporary probe's ordering gate
not evidence that early frame markers are missing
```

Frame 0 remains unproven and must stay separate until frame 1 closes.

---

## Tomorrow's Exact Runtime Responsibility

Keep the Quick `G3AB_COL_FIST` markers at **frame 1**.

Use the already-built/deployed diagnostic DLL from commit:

```text
0bfb2ba13ba91488570a41592504ac84428def2a
```

One Troll run is sufficient initially.

Test several marked Quick attacks at:

```text
1. very close range
2. ordinary fist-contact distance
```

Do not change code or marker placement before this run.

User observation to record:

```text
- can frame-1 marked Quick damage at very close range?
- can it damage at ordinary distance?
- any obviously abnormal repeated/multiple hit behavior?
```

Commit the complete runtime log to `research/raw/` and report only the filename + visual observation back to Normal Chat. Do not paste the large log into Chat.

---

## Decisive Log Shape

Expected successful pre-state path:

```text
CORE MARKER ... FIST ... StatePosition=0
CORE COLLISION_GROUP ... TrollFist ... Requested=7 Before=5 After=7
CORE C1 OFFENSE REQUEST ...
CORE RAW55_QUICK_PRESTATE_FIST_PROBE ... StatePosition=0 ... GroupBefore=5 GroupAfter=7 ClearTriggeredList=1
```

Then observe the untouched native Quick path:

```text
later Quick callback still advances StatePosition 0 -> 1
RIGHT remains group7
later native group7 request may appear as 7 -> 7
```

Damage/contact success:

```text
CORE ONDAMAGE ... Target=PC_Hero
```

Cleanup success:

```text
CORE COLLISION_GROUP ... Requested=5 Before=7 After=5
CORE C1 CLEANUP FULFILLED ... Outstanding=0
CORE C1_FINAL ... no repair / no lifecycle issue
```

A later native `7 -> 7` may cause lifecycle `Requests=2`; that is expected accounting and does not mean two probe-owned activations.

---

## Runtime Classification

### A — pre-state FIST works

```text
frame-1 FIST opens 5 -> 7
clear executes once
native StatePosition 0 -> 1 still occurs
OnDamage occurs on contact
native 7 -> 5 cleanup
clean C1 finalization
```

Then close the frame-1 ordering issue and decide whether frame 0 needs a separate bounded test before permanent raw55 design.

### B — activation/rearm works but damage remains state-gated

```text
pre-state 5 -> 7 + clear succeeds
native state progresses
but no OnDamage despite contact
```

Return to Normal Chat. Do not add another intervention.

### C — state/lifecycle/cleanup divergence

Any unexpected loss of StatePosition progression, source returning to group5 before intended cleanup, failed cleanup, repair, or lifecycle issue must be analyzed before further implementation.

---

## Protected Boundaries

Do not change before tomorrow's runtime:

```text
FrameCollisionMarkers
Raw8FistCollision
CollisionLifecycleGuard
CollisionSources
CollisionSourceOperations
EngineBridge hook ownership / RVAs
Normal/Sprint raw55 behavior
native cleanup
contact geometry
animation assets other than keeping the already-tested Quick FIST at frame 1
```

Do not add:

```text
custom/direct damage
TriggerTarget / OnDamage
StatePosition or SPU writes
manual cleanup
new 7 -> 7 suppression
another group7 request
another triggered-list clear
new hook/RVA/timer/polling
permanent PhysicalFistCollision
```

No Work task is active tonight. The next action is **runtime testing**, not implementation.
