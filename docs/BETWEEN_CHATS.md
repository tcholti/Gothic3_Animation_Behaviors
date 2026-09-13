# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-13

## Current Bridge — RAW55 REPEATED QUICK FIST DESIGN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is now through **EV-271**.

No permanent raw55 implementation is authorized yet.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. EVIDENCE_LEDGER_269_ONWARD.md EV-269–EV-271
4. ANIMATION_RULES.md §§8–10
5. PhysicalFistProbe.cpp only if needed for the next repeated-FIST design
6. earlier raw55 evidence only as routed by EVIDENCE_INDEX.md
```

The earlier `COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md` task is complete and runtime-validated. The superseded early-window-control probe remains stale and must not be implemented.

---

## Closed Runtime Result — EV-269

Current diagnostic implementation:

```text
commit: 0bfb2ba13ba91488570a41592504ac84428def2a
source review: PASS
local Release build: PASS
```

Frame-1 Troll Quick result:

```text
FIST arrives while StatePosition=0
RIGHT TrollFist/raw55 5 -> 7
ClearTriggeredList=1
later untouched native Quick requests 7 -> 7
native StatePosition advances 0 -> 1
OnDamage occurs on contact
native cleanup 7 -> 5
C1 closes cleanly without repair/lifecycle issue
```

User observation: frame-1 Quick damaged at both very close and ordinary range.

Primary artifact:

```text
research/raw/2026.09.12_troll_quick_fist_activation_frame_1_test2.log
```

---

## Repeated-FIST Finding — EV-270

User also tested Quick with an early FIST and a later FIST in the same attack.

The later FIST event reaches the diagnostic boundary, but the current temporary raw55 probe records the first pre-state intervention as used and intentionally refuses another probe-owned intervention in that actor/source/C1.

Therefore:

```text
later FIST transport = observed
second raw55 rearm = not tested by the current behavior
```

Do not interpret the missing second rearm as a Gothic limitation.

Artifact:

```text
research/raw/2026.09.12_troll_quick_fist_activation_frame_1_frame15.log
```

---

## Early Frame Authoring Closure — EV-271

Four user controls compare frame 0 and frame 1:

```text
research/raw/2026.09.12_2h_normal_activation_frame_0.log
research/raw/2026.09.12_2h_normal_activation_frame_1.log
research/raw/2026.09.12_sabertooth_quick_fist_activation_frame_0.log
research/raw/2026.09.12_sabertooth_quick_fist_activation_frame_1.log
```

Result:

```text
EQUIPPED 2H NORMAL RIGHT
frame 0 -> accepted marker, 5 -> 7, ClearTriggeredList, damage, native cleanup
frame 1 -> same healthy path

RAW8 SABERTOOTH QUICK FIST
frame 0 -> ownership close, accepted FIST, latch rearm, timing permission, positive native damage
frame 1 -> same healthy mechanism and positive native damage
```

No global frame-1 minimum exists.

User observed more Sabertooth misses with frame 0. The frame-0 logs show successful FIST acceptance and timing-permission use even on attacks that do not damage, so this is not marker transport failure. Raw8 FIST is a one-shot native opportunity and can simply be authored earlier than useful contact.

Canonical authoring rule is now in `ANIMATION_RULES.md` §§8–10.

---

## Important Raw55 Design Status

The project authoring philosophy remains:

```text
resolved Hit motion is scanned for reserved markers
no relevant marker -> native behavior
valid marked execution -> authored collision timing owns the relevant native mechanism
marker occurrence timing is literal
repeated legitimate markers author repeated contact opportunities
```

How native behavior is displaced/rearmed is mechanism-specific:

```text
equipped source markers -> physical Item_Attack window + ClearTriggeredList
raw8 FIST -> native opportunity latch/timing mechanism
raw55 PhysicalFist -> separate mechanism still being proven
```

Temporary `PhysicalFistProbe` behavior is research scaffolding, not the final authoring contract.

Known unfinished raw55 responsibilities:

```text
1. repeated Quick FIST rearm after the first pre-state FIST
2. Power family ownership — current temporary probe does not own/suppress marked raw55 Power
3. Normal/Sprint still use earlier temporary whole-callback suppression and are not final production semantics
```

---

## Next Normal-Chat Responsibility

Do **not** send a Work task yet merely to remove the one-shot flag.

First freeze one exact repeated-Quick-FIST causal question:

> With the first frame-1 FIST already opening/rearming raw55 and the source still naturally group7, is one later legitimate FIST in the same actor/source/C1 sufficient to author a second contact by clearing the exact source's triggered list once, without another collision-group request?

The next diagnostic must preserve:

```text
first EV-269 FIST behavior unchanged
later native Quick 7 -> 7 unchanged
StatePosition progression unchanged
native cleanup unchanged
no second group7 request at the later FIST when source is already group7
no custom/direct damage
no manual cleanup
no new hook/RVA/timer/polling
```

The final diagnostic should also expose enough occurrence identity to distinguish a genuine later FIST from a same-update duplicate before any permanent raw55 module is designed.

---

## Separate Incidental Finding — Raw55 Power

In the frame-1 Troll run, marked Power attacks could damage the User.

Current source explains this: temporary `PhysicalFistProbe` raw55 fixture/suppression coverage does not include Power in its custom ownership path, so native Power collision can still open raw55 and damage despite the marker.

Treat this as an **unfinished raw55 family-ownership responsibility**, not as desired production behavior and not as evidence that the overall marker architecture drifted.

Power classification comes after repeated Quick rearm unless a contradiction requires reordering.

---

## Protected Boundaries

Until the repeated-FIST probe is frozen:

```text
Raw8FistCollision
stable equipped FrameCollisionMarkers behavior
CollisionLifecycleGuard
CollisionSources
CollisionSourceOperations
EngineBridge hook ownership / RVAs
native cleanup
contact geometry
animation assets except user-authored test marker positions
```

Do not add permanent `PhysicalFistCollision` yet.
