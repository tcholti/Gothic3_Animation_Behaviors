# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 QUICK SELECTIVE GROUP-SUPPRESSION WORK TASK

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence now reaches **EV-264**.

No permanent raw55 implementation is authorized.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md
4. EVIDENCE_LEDGER_250_ONWARD.md EV-262 through EV-264
5. FEATURE_DEVELOPMENT_METHOD.md
6. WORK_IMPLEMENTATION_PROTOCOL.md
7. only the exact source/API files needed for this bounded implementation
```

The prior `COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md` is closed evidence context, not the current implementation contract.

---

## Closed Evidence

### EV-262 — whole-callback suppression

```text
old pre-FIST raw55 5 -> 7 removed             causal ownership supported
Normal/Sprint temporary suppression           clean in tested scope
Quick whole-callback suppression              failed
Quick rejected FIST under suppression         StatePosition 0
later Quick raw55 reactivation/repair          observed
```

Whole `_AI_QuickAttack` suppression is rejected as a production mechanism.

### EV-263 — raw8 Quick control

Native-NPC and transformed-player Sabretooth Quick remain healthy through factual raw8 `Fist`. Accepted-marker `StatePosition=1` is not pre-marker proof because accepted Quick marker processing itself writes marker-owned StatePosition before the compact marker line is emitted.

### EV-264 — raw55 Quick callback boundary

Repeated Troll/BlackTroll marked raw55 Quick executions prove that the same original `_AI_QuickAttack` invocation contains both net transitions:

```text
StatePosition 0 -> 1
RIGHT TrollFist raw55 group5 -> group7
```

This repeats for Quick Action 4 and Action 5. Damage can follow shortly after the early raw55 opening and well before authored FIST.

Therefore whole-callback suppression broke Quick because it removed required native state progression together with the unwanted early raw55 activation.

Active comparison artifacts:

```text
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
research/raw/2026.09.12_sabertooth_marked_quick.log
research/raw/2026.09.12_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_marked_quick_attacks.log
research/raw/2026.09.12_one_troll_native_attacks.log
```

---

## Frozen Work Responsibility

Authority: `docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md`.

Implement **only** the diagnostics-only selective raw55 Quick group-suppression causal probe frozen there.

Single causal question:

> While the original marked factual raw55 `_AI_QuickAttack` callback runs normally, can only its exact nested RIGHT raw55 `Item_Equipped/group5 -> Item_Attack/group7` request be suppressed while native StatePosition still advances `0 -> 1`, with no later physical raw55 reactivation or lifecycle repair?

### Required source behavior

Keep current Quick callback observation and let the original Quick callback execute exactly once.

`PhysicalFistProbe` must own the temporary per-invocation Quick scope and selective decision. Scope identity is the exact factual actor + RIGHT raw55 source + C1 generation established by the existing marked raw55 Quick fixture eligibility.

The scope must be per-invocation/reentrancy-safe; do not use a bare unscoped global boolean.

Inside the **existing** `SetCollisionGroup` hook, `EngineBridge` may add only the smallest diagnostics-only delegation before calling the original:

```text
ask PhysicalFistProbe whether this exact SetCollisionGroup request is suppressed
if yes -> return without calling original SetCollisionGroup
if no  -> existing SetCollisionGroup path unchanged
```

Suppression is allowed only when all frozen conditions match, including:

```text
active exact marked raw55 Quick callback scope
source == scoped factual RIGHT source
source factual UseType == PhysicalFist/raw55
before/current group == Item_Equipped / 5
requested group == Item_Attack / 7
current C1 == scoped C1
actor/context still matches
```

A suppressed request did not physically become offensive. It must therefore **not** be passed to `CollisionLifecycleGuard::ObserveCollisionGroupResult` as a real offense and must not create a fabricated outstanding C1 obligation.

Add compact diagnostic tag:

```text
CORE RAW55_QUICK_GROUP_SUPPRESSION
```

with Actor, C1, source, UseType, requested group, before group, StatePosition, StateTime, `SUPPRESS_GROUP=1`.

Keep existing:

```text
CORE RAW55_QUICK_CALLBACK_BOUNDARY
```

The decisive hoped-for probe shape is:

```text
exact raw55 5 -> 7 request suppressed
StatePosition 0 -> 1
RightGroup 5 -> 5
```

Repeated exact native 5 -> 7 attempts in one C1 are valid observations and may each be suppressed/logged.

---

## Existing Controls Must Stay Unchanged

```text
marked raw55 Normal -> prior temporary whole-callback suppression unchanged
marked raw55 Sprint -> prior temporary whole-callback suppression unchanged
marked raw55 Quick  -> original callback runs; only exact scoped raw55 5 -> 7 requests intercepted
```

All nonmatching SetCollisionGroup requests must follow the existing path unchanged.

---

## Protected Boundaries

Do **not** change:

```text
Raw8FistCollision
FrameCollisionMarkers behavior/semantics
CollisionLifecycleGuard behavior/semantics
CollisionSources behavior/semantics
CMake target/source separation
hook RVAs or hook ownership
raw8 FIST behavior
normal equipped RIGHT/LEFT/BOTH/OFF behavior
marker acceptance
StatePosition directly
SPU+0x164
ClearTriggeredList
contact/damage logic
species/name policy
```

Do not add:

```text
new hook
new RVA
timer
polling
per-frame scan
permanent PhysicalFistCollision
compensating Quick StatePosition write
```

`EngineBridge` remains transport-only. Probe state/policy belongs in `PhysicalFistProbe` and must remain compiled only into `Script_FrameCollisionTest`.

---

## Expected Changed Files

The bounded implementation should normally require only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

No CMake change is expected. If the frozen task cannot be implemented within these architecture boundaries because of a real source/API contradiction, stop and report the contradiction rather than broadening scope.

---

## Work Stop / Report

Follow `WORK_IMPLEMENTATION_PROTOCOL.md`.

```text
read frozen authorities
-> inspect only necessary source/API
-> implement bounded diagnostic probe
-> static/source audit
-> commit + push to docs/collision-source-evidence
-> report remote commit SHA, changed files, concise implementation result,
   build status, and any material contradiction
-> STOP
```

**Build execution is NOT authorized.** User + Normal Chat build after independent Normal Chat source review.

Do not update evidence conclusions or design a permanent raw55 mechanism in this Work task.

---

## After Work

Normal Chat will independently review the published diff against the frozen probe contract.

Only after review passes:

```text
User + Normal Chat build/deploy Script_FrameCollisionTest
-> focused marked Troll/BlackTroll Quick run
-> commit complete raw log to GitHub
-> Normal Chat analyzes and promotes evidence
```

Preferred focused runtime filename after review/build:

```text
research/raw/2026.09.12_raw55_quick_group_suppression_probe.log
```

Broader native-creature certification, compatibility work and AttackContinuationProtection remain paused until raw55 is resolved or explicitly deferred.
