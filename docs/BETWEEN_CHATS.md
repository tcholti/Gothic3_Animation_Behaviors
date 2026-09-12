# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 QUICK EARLY-WINDOW CONTROL WORK TASK

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence now reaches **EV-267**.

No permanent raw55 implementation is authorized.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md
4. EVIDENCE_LEDGER_265_ONWARD.md EV-265–EV-267
5. FEATURE_DEVELOPMENT_METHOD.md
6. WORK_IMPLEMENTATION_PROTOCOL.md
7. only exact source/API files required for this bounded implementation
```

Prior raw55 probe contracts are closed causal context. Preserve their behavior except where this exact control intentionally replaces EV-265/EV-267 Quick timing ownership.

---

## Closed Raw55 Evidence

### EV-265 — early Quick group activation and StatePosition progression are separable

```text
exact early RIGHT raw55 5 -> 7 request suppressed
original _AI_QuickAttack still executes
StatePosition 0 -> 1 preserved
RIGHT stays group5
```

### EV-266 — authored FIST group opening and native cleanup work

```text
FIST at StatePosition 1 / StateTime ~0.48–0.49
exact RIGHT raw55 5 -> 7 succeeds
real C1 offense obligation created
native 7 -> 5 cleanup succeeds
no damage without rearm
```

### EV-267 — one exact triggered-list clear restores raw55 Quick damage when contact occurs

Runtime artifacts:

```text
research/raw/2026.09.12_troll_quick_fist_activation_3.log
research/raw/2026.09.12_black_troll_quick_fist_activation_3.log
research/raw/2026.09.12_troll_native_collision_3.log
```

Results:

```text
11 marked Troll + 9 marked BlackTroll FIST-time activations reached group7
all logged ClearTriggeredList=1
marked Troll: 5 OnDamage events to PC_Hero during Quick group7 windows
marked BlackTroll: 4 OnDamage events to PC_Hero during Quick group7 windows
native cleanup remains healthy
no terminal repair/lifecycle issue
```

User runtime observation adds a range-dependent difference:

```text
marked Quick:
    very close -> no damage when the fist has already passed beyond the player
    farther back -> Quick can damage when the fist reaches the player

native/unmarked Troll:
    damage can occur even very close
    visually, a broader part of the attacking limb appears damaging

ordinary blocking/body collision:
    present in both marked and native cases
```

The logs identify the same factual RIGHT `TrollFist` / raw55 source in native and marked Quick. They do **not** identify its geometric extent, so do not promote "fist-only" vs "whole limb/body" as a proven engine fact.

The strongest open variable is timing:

```text
native Quick raw55 opening = very early
marked EV-267 opening      = authored FIST around StateTime ~0.47–0.49
```

---

## Frozen Work Responsibility

Authority:

```text
docs/COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md
```

Implement **only** the temporary diagnostics-only early-window control frozen there.

Single question:

> On the same marked factual raw55 Quick animation, if the exact original native early RIGHT raw55 `5 -> 7` request is allowed instead of suppressed, while the later diagnostic FIST activation/rearm is disabled for that execution, does very-close-range damage return?

### Required behavior

For the exact marked raw55 Quick fixture already proven by EV-264–EV-267:

```text
original _AI_QuickAttack executes exactly once
same marker scan / raw55 source eligibility
exact nested RIGHT raw55 5 -> 7 request is recognized
```

But for this control:

```text
DO NOT suppress that exact early request
DO NOT create an early-suppression proof record for the execution
allow normal SetCollisionGroup transport/original/lifecycle observation
retain Quick callback-boundary observation
```

Because no valid suppression proof exists for that C1, the later `PhysicalFistProbe::OnMarkerProcessed()` path must not perform EV-267 FIST-time `5 -> 7` activation or `ClearTriggeredList()`.

Add compact:

```text
CORE RAW55_QUICK_EARLY_WINDOW_CONTROL
```

with the fields frozen in the probe contract, including:

```text
ALLOW_EARLY=1
FIST_INTERVENTION=0
```

Stale proof state must not leak into the control C1.

---

## Protected Boundaries

Do not change:

```text
FrameCollisionMarkers semantics
Raw8FistCollision
CollisionLifecycleGuard semantics
CollisionSources semantics
CollisionSourceOperations
CMake separation
hook RVAs/ownership
raw8 behavior
equipped RIGHT/LEFT/BOTH/OFF
Normal/Sprint raw55 diagnostic behavior
native cleanup
contact geometry / body physics
animation assets / marker placement
```

Do not add:

```text
ClearTriggeredList for this control
custom/direct damage
manual TriggerTarget / OnDamage
StatePosition write
SPU+0x164 write
manual cleanup
second group7 request
species/name policy
new hook/RVA/timer/polling/per-frame scan
permanent PhysicalFistCollision
```

---

## Expected Changed Files

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h` may change only if directly necessary for clean temporary control state. No stable behavior module or CMake change is expected. `EngineBridge.cpp` should not need policy changes.

If the task cannot be implemented within those boundaries because of a real source/API contradiction, stop and report instead of broadening scope.

---

## Work Stop / Report

Follow `WORK_IMPLEMENTATION_PROTOCOL.md`:

```text
read frozen authorities
-> inspect only necessary source/API
-> implement bounded diagnostic control
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

### A — timing explains close-range divergence

```text
marked Quick marker still present
exact early raw55 5 -> 7 allowed
StatePosition native progression preserved
no later FIST probe intervention
very-close-range OnDamage returns
native 7 -> 5 cleanup remains healthy
```

Then do not infer a geometry/source difference. The authored FIST timing in the tested Troll animation is simply too late to cover the earlier proximal-limb overlap at very close range.

### B — timing does not explain it

Exact early marked raw55 path occurs but very-close-range damage still does not return. Then isolate geometry/contact state next; do not compensate in this task.

### C — state/lifecycle contradiction

Stop and analyze before any further intervention.

Broader raw55 production design and Normal/Sprint generalization remain paused.
