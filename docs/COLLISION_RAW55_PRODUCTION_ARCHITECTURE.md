# Permanent raw55 PhysicalFist Architecture

**Status:** Current production-behavior architecture  
**Updated:** 2026-09-19

## Purpose

Define the permanent diagnostics-free collision behavior for factual `gEUseType_PhysicalFist` / raw55 after the completed causal research campaign.

This file describes the **current architecture**. The original production implementation contract and all family-specific probe documents are preserved under `docs/archive/investigations/`.

Ordinary factual lookup: `COLLISION_REFERENCE.md`.  
Exact proof: `EVIDENCE_INDEX.md` → EV-262–EV-298.

---

## 1. Proven scope

Supported marked raw55 families:

```text
Normal
Quick
true Power
Sprint-origin
```

Current source scope:

```text
exact current RIGHT equipped source
UseType = PhysicalFist / raw55
reserved FIST authoring
1 or 2 authored FIST markers
no equipped RIGHT/LEFT/BOTH/OFF marker mixture
valid current C1 generation
supported factual attack family
```

There is no species/name gate and no filename-based family inference.

No LEFT raw55 generalization is currently supported.

---

## 2. Permanent owner

`PhysicalFistCollision` owns raw55 semantic behavior/state.

`EngineBridge` remains the sole physical hook/call-site transport owner.

Relevant surrounding responsibilities:

```text
EngineBridge
  physical Gothic hook/call-site ownership
  native fact capture + narrow delegation
  no raw55 policy

FrameCollisionMarkers
  marker recognition / current-motion scan
  factual Hit-family/marker dispatch

CollisionSources
  factual source/UseType access

CollisionSourceOperations
  generic physical source operations

CollisionLifecycleGuard
  C1 obligations / native-cleanup reconciliation / terminal backup repair
  no ordinary raw55 timing policy

Raw8FistCollision
  separate raw8 mechanism

PhysicalFistCollision
  raw55 execution eligibility
  family/origin state
  premature native opening suppression
  authored FIST operations
  repeated-contact ownership
  Sprint-origin continuity
  exact Normal native between-contact clear suppression
```

A hook's physical location does not make `EngineBridge` the feature owner.

---

## 3. Governing behavior

### Unmarked raw55

```text
unmarked raw55
-> native Gothic behavior
```

Permanent raw55 intervention is marker-owned. Native fallback remains intact.

### Marked supported raw55

Before the first authored FIST, the supported native callback may attempt an early exact RIGHT raw55 `5 -> 7` opening.

For an eligible marked execution:

```text
premature native opening
-> suppress only the exact evidence-backed raw55 opening
-> preserve original callback/state progression
```

At the first accepted authored FIST:

```text
exact current RIGHT raw55 source
-> authored physical 5 -> 7 opening
-> contact bookkeeping rearm as required by proven family route
-> Gothic owns target/contact/damage
```

At a later accepted FIST in the same C1:

```text
source already offensive
-> rearm contact bookkeeping only
-> no second physical group opening
-> Gothic owns target/contact/damage
```

At the end of the attack:

```text
Gothic native exact RIGHT 7 -> 5 cleanup first
-> CollisionLifecycleGuard only remains backup if an exact outstanding live/equipped group7 obligation survives
```

There is no custom raw55 terminal cleanup path.

---

## 4. Family/origin semantics

### Quick

The native Quick callback owns required state progression and also attempts a premature raw55 physical opening. Permanent behavior suppresses only the raw55 opening, not the callback.

The first authored FIST opens/rearms the source. A later authored FIST owns another contact-bookkeeping rearm.

Evidence: EV-264–EV-273.

### Normal

The first authored FIST may arrive while StatePosition is still 0. It can own the physical opening and first contact opportunity before Gothic's ordinary Normal transition.

Gothic has a native between-contact clear from the proven exact caller:

```text
Script_Game.dll +0x386C6
```

For the supported marked Normal route, that native between-contact clear is suppressed so it does not silently substitute for authored marker2 ownership. The later authored FIST performs the replacement contact rearm.

The native callback's state progression and final cleanup remain Gothic-owned.

Evidence: EV-277–EV-279, EV-286–EV-292.

### true Power

True Power is factual Action 2 / POWER, distinct from Sprint even though Sprint shares physical callback transport.

The native callback is preserved; only the premature exact raw55 opening is selectively suppressed. Authored FIST owns first/repeated contact timing.

Evidence: EV-274–EV-276, EV-293.

### Sprint-origin

Sprint is factual Action 9 at origin and may later continue within the same C1 after Action9 -> Action2 transition.

That transition does not create a new attack execution.

Permanent raw55 ownership therefore preserves Sprint-origin identity across the same C1 so a later authored FIST remains part of the same authored execution.

Evidence: EV-280–EV-285, EV-294.

---

## 5. Execution identity and safety

Permanent state is bounded to the factual C1 execution and exact source/origin identity.

A valid execution requires the current source/family/marker facts to match the owned execution.

Identity replacement or contradiction must not authorize a new raw55 intervention.

Diagnostics may surface identity contradictions, but diagnostics do not decide release behavior.

The post-audit callback-identity surfacing correction is diagnostics-only; behavior on contradiction remains “no new raw55 intervention.”

Focused validation: EV-295–EV-298.

---

## 6. Native ownership retained

The feature does **not** own:

```text
target selection
contact geometry
damage amount/dispatch
reaction selection
ordinary callback/state progression
final native exact RIGHT 7 -> 5 cleanup
unmarked raw55 behavior
generic C1 terminal policy
```

Physical activation alone is not evidence that every source type/action has a native damage route; shield/raw9 EV-308 is the explicit counterexample for that broader assumption.

---

## 7. Production exclusions

Do not add without new evidence:

```text
raw8 SPU+0x164 timing/latch reuse
LEFT raw55 support
species/name gating
filename-driven family identity
mixed raw55 FIST + equipped RIGHT/LEFT/BOTH/OFF semantics
more than two raw55 FIST markers
FIST_OFF
direct/custom raw55 damage
polling/timer ownership
global ClearTriggeredList policy
whole native callback suppression
diagnostic/probe state as release dependency
```

Unknown future behavior returns to an isolated probe under `FEATURE_DEVELOPMENT_METHOD.md`.

---

## 8. Release / diagnostic separation

The permanent behavior source must compile in both collision twins:

```text
Script_FrameCollisionBehaviorTest
  behavior only

Script_FrameCollisionTest
  same behavior + diagnostics
```

Release behavior must not require `CollisionDiagnostics`, historical `PhysicalFistProbe` state, or diagnostic-only hooks.

The historical probe modules/contracts are archived and are not current design input unless a contradiction requires reconstruction.

---

## 9. Validation closure

Permanent raw55 focused acceptance is CLOSED/PASS at EV-298.

Validated boundaries include:

```text
four supported families
first and repeated FIST behavior
native final cleanup
unmarked raw55 fallback
raw8 coexistence
equipped authored-marker coexistence
post-audit diagnostics controls
```

Do not reopen family-specific causal probing merely for routine variation. New factual contradiction or a deliberate scope extension is required.

---

## 10. Retrieval

```text
current fact
-> COLLISION_REFERENCE.md

raw55 architecture question
-> this file

source/hook/RVA question
-> SOURCE_HOOK_GUIDE.md

validation question
-> COLLISION_TEST_PLAN.md

proof/provenance question
-> EVIDENCE_INDEX.md -> exact EV / archived source
```
