# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-15

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If Normal Chat ends before evidence closure, use POP-11 Recovery Lock. Oversized runtime logs use POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe authority: `docs/COLLISION_RAW55_NORMAL_PRESTATE_FIST_PROBE.md`  
Latest canonical evidence: through corrected **EV-285**  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      first-contact CLOSED/PASS through EV-279
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED as evidence — EV-283

Normal pre-StatePosition FIST probe:
    implementation a99f4aa616c905c4eb66c72bdaa27709c9b75c77
    independent Normal Chat source review PASS
    local build/deploy/runtime PENDING
```

The current diagnostic changes only `PhysicalFistProbe.cpp` and adds the exact Normal SP0 intervention frozen in the probe contract:

```text
factual Action1 / Family NORMAL / Hit
valid current C1
exact current RIGHT PhysicalFist/raw55 group5
stable FIST result = UNSUPPORTED_MISSING_SOURCE
StatePosition=0
-> exact RIGHT SetCollisionGroup(Item_Attack / 7)
-> ClearTriggeredList=0
```

No StatePosition write, damage call, cleanup intervention, new hook, or permanent feature code was added.

Independent review confirmed the later native Normal request is not hidden after the marker-owned opening: existing selective suppression requires before-group 5, so a later native `7 -> 7` remains observable. The existing SP1 activation path cannot double-activate because it still requires the old suppression proof plus group5/SP1.

## Immediate next step

User + Normal Chat now perform local validation only:

```text
sync branch
-> build Script_FrameCollisionTest Release only
-> STOP on build result
-> POP-03 deploy/hash verification if build passes
-> POP-04 startup banner
-> Troll runtime
-> POP-07/POP-06 evidence closure
```

Preferred runtime artifact:

`research/raw/2026.09.15_troll_raw55_normal_prestate_fist.log`

Desired causal result:

`SP0 FIST 5->7 / ClearTriggeredList=0 -> untouched native Normal SP0->1 -> native damage when contact occurs -> native 7->5 cleanup -> clean C1 finalization.`

## Remaining collision sequence

```text
Normal pre-state evidence closure
-> non-Quick repeated-FIST causal closure
-> preserve Sprint same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

New Balance 0.7 is not a current blocker. Source-level preflight is EV-284; corrected AttackCollision coexistence interpretation is EV-285, with prior combined runtime passes EV-035/EV-150/EV-242.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO non-Quick repeat-FIST intervention until this transaction closes
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
