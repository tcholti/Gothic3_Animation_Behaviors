# Permanent raw55 PhysicalFist Architecture

**Status:** Current production-behavior architecture  
**Updated:** 2026-09-27

## Purpose

Define the permanent diagnostics-free collision behavior for factual `gEUseType_PhysicalFist` / raw55 after the completed causal research campaign, New Balance compatibility work, and the EV-385 standalone post-compatibility finding.

This file describes the **current architecture and any explicitly pending evidence-backed correction**. Historical probes/implementation contracts are preserved under `docs/archive/investigations/`.

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

Evidence: EV-264–EV-273 plus protected controls through EV-385.

### Normal

The first authored FIST may arrive at StatePosition0 and own the physical opening/first contact opportunity before Gothic's ordinary Normal transition.

Gothic has a native between-contact clear from the proven exact caller:

```text
Script_Game.dll +0x386C6
```

For supported marked Normal, that native between-contact clear is suppressed so it cannot silently substitute for authored marker2 ownership. The later authored FIST performs the replacement contact rearm.

Accepted second-FIST state contract:

```text
origin family = NORMAL
current family = NORMAL
StatePosition = SP0 OR SP1
```

EV-382 proves SP0 can be legitimate both before and after hit1. SP1 remains supported from the original Normal causal campaign. No hit1 flag, target-visited gate, timer, queue, or delayed marker behavior is required.

Evidence: EV-277–EV-279, EV-286–EV-292, EV-380, EV-382.

### true Power

True Power is factual Action2/POWER, distinct from Sprint even though Sprint shares physical callback transport.

Current accepted state contract:

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

Evidence: EV-274–EV-276, EV-293, EV-376, EV-378, protected controls through EV-382. Final-candidate standalone true-Power sentinel control remains required after the EV-385 correction because the EV-385 four-log batch did not produce factual true-Power-origin traffic.

### Sprint-origin

Sprint is factual Action9 at origin and may later continue within the same C1 after Action9 -> Action2 transition. That transition does not create a new attack execution.

Permanent raw55 ownership preserves immutable Sprint-origin identity across the same C1.

First-FIST contract remains:

```text
origin family = SPRINT
current family = SPRINT
StatePosition {SP1,SP2}
earlyOpeningSuppressed mandatory
```

#### Implemented pre-EV-385 second-FIST gate

The source tested by EV-385 currently implements:

```text
origin family = SPRINT

current POWER:
  StatePosition {SP1,SP2}

current SPRINT:
  StatePosition {SP2} only
```

The current-Power SP1 route is established by the original standalone Sprint repeated-contact evidence (EV-294). New Balance later required and proved current-SPRINT/SP2 plus current-POWER/SP2 compatibility (EV-380–EV-381).

#### EV-385 standalone compatibility finding

EV-385 proves a legitimate second authored FIST can remain factual:

```text
origin family = SPRINT
current family = SPRINT
Action = 9
StatePosition = SP1
same C1
same exact current RIGHT raw55 source
source already group7
```

The `1+3` standalone fixture repeats this in four distinct Sprint C1s. Marker1 at `SPRINT/SP1` opens correctly; marker2 is still `SPRINT/SP1` and is rejected only by the state gate. Cleanup remains native and healthy. The same batch proves `1+8` and `1+15` remain healthy when marker2 has crossed to current `POWER/SP1`, and single-FIST `SPRINT/SP1` remains healthy.

This supplies the evidence that was previously missing. Therefore the frozen pending production correction is:

```text
origin family = SPRINT

current POWER:
  StatePosition {SP1,SP2}   // preserve

current SPRINT:
  StatePosition {SP1,SP2}   // add SP1
```

This is an explicit evidence-backed state union. It is **not** permission for generic `>=1`, arbitrary state widening, or family-independent policy.

The correction is frozen in:

`docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md`

Until that source change is implemented and runtime-accepted, the implemented source remains partial-fail for the standalone sentinel.

Evidence: EV-280–EV-285, EV-294, EV-376–EV-381, EV-385.

---

## 5. Execution identity and safety

Permanent state is bounded to the factual C1 execution and exact source/origin identity.

A valid execution requires current source/family/marker facts to match the owned execution. Identity replacement or contradiction must not authorize a new raw55 intervention.

EV-385 does not weaken these checks: its failing marker2 is already the same legitimate Sprint-origin C1/source and is rejected solely because current Sprint SP1 was absent from the second-FIST state whitelist.

Diagnostics may surface identity contradictions, but diagnostics do not decide release behavior.

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

EV-385 likewise separates marker2 eligibility from lifecycle safety: rejected standalone Sprint/SP1 marker2 executions still allow Gothic native cleanup to return the source to group5 with zero outstanding obligation.

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
visited-target/hit1 flags for Normal marker2
marker delays/queues
New Balance/DLL/version detection
```

Previous wording that excluded Sprint/SP1 second-FIST acceptance “without evidence” is superseded by EV-385: evidence now exists for the exact Sprint-origin/current-SPRINT/SP1 branch only.

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

Because EV-385 changes behavior-facing shared source, both twins must be rebuilt after implementation before final validation proceeds.

---

## 9. Compatibility disposition

Focused raw55 New Balance compatibility is CLOSED/PASS through EV-382. Broad intended-stack New Balance compatibility is CLOSED/PASS EV-384.

The post-compatibility standalone/no-New-Balance sentinel is **PARTIAL FAIL EV-385** because the pre-correction source rejects legitimate Sprint-origin second FIST at current `SPRINT/SP1`.

Current route:

```text
bounded EV-385 correction
-> independent source review
-> focused standalone retest of exact 1+3 failure
-> preserve 1+8/1+15 POWER/SP1 continuation + single SPRINT/SP1
-> bounded New Balance Sprint SP2/transition regression because source changed after EV-384
-> finish true-Power single/double + unmarked raw55 fallback standalone controls
-> sentinel PASS required before production collision migration
```

Do not reopen closed raw55 mechanisms or broad compatibility scope unless corrected-final-candidate evidence produces a new contradiction.