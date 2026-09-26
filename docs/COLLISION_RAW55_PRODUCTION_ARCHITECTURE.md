# Permanent raw55 PhysicalFist Architecture

**Status:** Current production-behavior architecture  
**Updated:** 2026-09-26

## Purpose

Define the permanent diagnostics-free collision behavior for factual `gEUseType_PhysicalFist` / raw55 after the completed causal research campaign and the bounded New Balance compatibility corrections through EV-382.

This file describes the **current architecture**. Historical probes/implementation contracts are preserved under `docs/archive/investigations/`.

Ordinary factual lookup: `COLLISION_REFERENCE.md`.  
Exact proof: `EVIDENCE_INDEX.md`.

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

There is no species/name gate and no filename-based family inference. No LEFT raw55 generalization is currently supported.

---

## 2. Permanent owner

`PhysicalFistCollision` owns raw55 semantic behavior/state.

`EngineBridge` remains the sole physical hook/call-site transport owner.

Relevant responsibility split:

```text
EngineBridge
  physical Gothic hook/call-site ownership
  native fact capture + narrow delegation

FrameCollisionMarkers
  marker recognition/current-motion scan
  factual Hit-family/marker dispatch

CollisionSources
  factual source/UseType access

CollisionSourceOperations
  generic physical source operations

CollisionLifecycleGuard
  C1 obligations/native-cleanup reconciliation/terminal backup repair
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

For an eligible marked execution, when a supported native callback attempts an evidence-backed premature exact RIGHT raw55 `5 -> 7` opening:

```text
premature native opening
-> suppress only the exact proven raw55 opening
-> preserve callback/state progression
```

At the first accepted authored FIST:

```text
exact current RIGHT raw55 source
-> authored physical 5 -> 7 opening
-> contact bookkeeping rearm where required by the proven family route
-> Gothic owns target/contact/damage
```

At a later accepted FIST in the same C1:

```text
source already offensive
-> ClearTriggeredList/rearm only
-> no second physical group opening
-> Gothic owns target/contact/damage
```

At attack end:

```text
Gothic native exact RIGHT 7 -> 5 cleanup first
-> CollisionLifecycleGuard remains backup only if an exact outstanding live/equipped group7 obligation survives
```

There is no custom raw55 terminal cleanup path.

---

## 4. Family/origin semantics

### Quick

The native Quick callback owns its state progression and may attempt a premature raw55 physical opening. Permanent behavior suppresses only the evidence-backed raw55 opening, not the callback.

The first authored FIST opens/rearms the source. A later authored FIST may occur at the factual Quick state available at that marker and owns another contact-bookkeeping rearm.

Evidence: EV-264–EV-273 plus protected controls through EV-382.

### Normal

The first authored FIST may arrive at StatePosition0 and own the physical opening/first contact opportunity before Gothic's ordinary Normal transition.

Gothic has a native between-contact clear from the proven exact caller:

```text
Script_Game.dll +0x386C6
```

For supported marked Normal, that native between-contact clear is suppressed so it cannot silently substitute for authored marker2 ownership. The later authored FIST performs the replacement contact rearm.

Final Normal second-FIST acceptance after EV-382 is explicit and evidence-bounded:

```text
origin family = NORMAL
current family = NORMAL
StatePosition = SP0 OR SP1
```

Why SP0 is valid:

```text
marker1 NORMAL/SP0 -> open + initial clear
native hit1 may occur while still SP0
marker2 can still arrive NORMAL/SP0
marker2 -> ClearTriggeredList/rearm only
no second physical opening
later native hit2 may occur
```

Very-early marker2 may also occur before hit1. That clear may simply clear an empty visited set; it does not create an artificial damage guarantee and requires no new hit1 flag, queue, delay, or timer.

SP1 remains explicitly supported and was runtime-proven in the earlier Normal causal campaign. EV-382 adds direct runtime proof that SP0 can be a legitimate second-contact authoring point after hit1.

The native callback's state progression and final cleanup remain Gothic-owned.

Evidence: EV-277–EV-279, EV-286–EV-292, EV-380, EV-382.

### true Power

True Power is factual Action2/POWER, distinct from Sprint even though Sprint shares physical callback transport.

The native callback is preserved; only the premature exact raw55 opening is selectively suppressed. Authored FIST owns first/repeated contact timing.

Current New Balance-compatible state acceptance:

```text
first FIST:
  current POWER
  + StatePosition {SP1,SP2}
  + earlyOpeningSuppressed

second FIST:
  current POWER
  + StatePosition {SP1,SP2}
```

No `>=1` generalization is used.

Evidence: EV-274–EV-276, EV-293, EV-376, EV-378, protected controls EV-381–EV-382.

### Sprint-origin

Sprint is factual Action9 at origin and may later continue within the same C1 after Action9 -> Action2 transition. That transition does not create a new attack execution.

Permanent raw55 ownership therefore preserves immutable Sprint-origin identity across the same C1.

Current first-FIST rule:

```text
origin family = SPRINT
current family = SPRINT
StatePosition {SP1,SP2}
earlyOpeningSuppressed mandatory
```

Current second-FIST rule:

```text
origin family = SPRINT

current POWER:
  StatePosition {SP1,SP2}

current SPRINT:
  StatePosition {SP2} only
```

EV-380 proved the same authored marker2 can fall on either side of the native Action9 -> Action2 transition under New Balance. EV-381 runtime-validates the final asymmetric rule, including the formerly rejected `SPRINT/SP2` second-FIST route. Sprint/SP1 second-FIST remains unproven and is not authorized. No `>=1` generalization is used.

Evidence: EV-280–EV-285, EV-294, EV-376–EV-381 plus protected controls EV-382.

---

## 5. Execution identity and safety

Permanent state is bounded to the factual C1 execution and exact source/origin identity.

A valid execution requires current source/family/marker facts to match the owned execution. Identity replacement or contradiction must not authorize a new raw55 intervention.

Diagnostics may surface identity contradictions, but diagnostics do not decide release behavior.

Focused validation: EV-295–EV-298 plus compatibility evidence EV-376–EV-382.

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

EV-381 reinforces that an accepted/open/rearmed raw55 window may still produce zero `ONDAMAGE`; native unmarked raw55 windows can also miss completely. Therefore a visual miss is not itself evidence of marker failure.

The User's sheath/draw observation is non-blocking collision evidence: native behavior can also miss and can also damage during sheathing/drawing-related states. Do not add custom damage/contact policy for that observation without a separate causal need.

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
generic StatePosition range widening
Sprint/SP1 second-FIST acceptance without evidence
visited-target/hit1 flags for Normal marker2
marker delays/queues
New Balance/DLL/version detection
```

Unknown future behavior returns to an isolated probe under `FEATURE_DEVELOPMENT_METHOD.md`.

---

## 8. Release / diagnostic separation

Permanent behavior must compile in both collision twins:

```text
Script_FrameCollisionBehaviorTest
  behavior only

Script_FrameCollisionTest
  same behavior + diagnostics
```

Release behavior must not require `CollisionDiagnostics`, historical probe state, or diagnostic-only hooks.

---

## 9. Compatibility disposition

Focused raw55 Normal/Quick/true-Power/Sprint-origin compatibility is **CLOSED/PASS** for the tested intended New Balance route through EV-382.

Runtime-confirmed compatibility corrections:

```text
6eb3e3ca96da55e89127c24d5f656e05610d315f
  true-Power first/second SP2 compatibility
  Sprint-origin later current-Power SP2 compatibility

ce59e5a2bad564652eaba970e959bdef0b479d82
  Sprint-origin first-FIST SP2 compatibility

4c85193f4efd31e789bc07d7e3c71d31a9b5326e
  Sprint-origin second-FIST current-SPRINT/SP2 compatibility

a31c66b97e45c27d0739b7df51252d33f490e7e1
  Normal second-FIST explicit {SP0,SP1} acceptance
```

The next collision gate is **not another focused raw55 patch**. It is broader representative/full-stack New Balance compatibility. After that passes, run the small standalone/no-New-Balance post-compatibility raw55 sentinel before production collision migration.
