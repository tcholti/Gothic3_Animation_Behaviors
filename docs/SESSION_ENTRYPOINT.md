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
Current frozen probe authority: `docs/COLLISION_RAW55_NORMAL_PRESTATE_REARM_PROBE.md`  
Latest canonical evidence: through **EV-286** in `docs/EVIDENCE_LEDGER_286_ONWARD.md`  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      SP1 first-contact CLOSED/PASS through EV-279
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED as evidence — EV-283
raw55 Normal SP0 physical opening CLOSED/PASS — EV-286
```

EV-286 proves:

```text
frame-1 Normal FIST at StatePosition 0 is transported
-> exact current RIGHT PhysicalFist/raw55 opens 5 -> 7
-> ClearTriggeredList=0
-> source remains group7
-> later native Normal 7 -> 7 occurs around StateTime ~= 0.25
-> native StatePosition advances 0 -> 1
-> later frame-15 FIST is delivered but receives no Normal repeat intervention
-> one later damage event occurs
-> native 7 -> 5 cleanup and clean C1 finalization
```

Therefore the first marker is **not rejected** and does not wait for the native timer to open the physical source. The remaining first-contact question is whether one exact triggered-list clear is required for an early damaging opportunity before Gothic's native Normal transition.

## Current frozen intervention

For the already-proven exact Normal SP0 path only:

```text
SP0 authored FIST
-> exact RIGHT SetCollisionGroup(Item_Attack / 7)
-> verify groupAfter == 7
-> exact RIGHT TouchDamage.ClearTriggeredList() once
```

Change nothing else.

The original `_AI_Attack` callback must continue untouched. Preserve Gothic's later native `7 -> 7 / StatePosition 0 -> 1` transition. Do not suppress it, write StatePosition, call damage, or modify cleanup.

The frame-15 FIST remains observational only for Normal in this probe. No Normal repeated-FIST rearm is authorized yet.

## Interpretation

```text
early ONDAMAGE before native 7 -> 7 / SP0 -> 1
    => triggered-list rearm is the missing early-contact primitive

no early damage even with clear; damage only after native transition
    => additional native Normal state/timing eligibility gate exists

callback/lifecycle/cleanup divergence
    => stop and analyze before further intervention
```

## Remaining collision sequence

```text
Normal SP0 contact-rearm causal closure
-> if needed, isolate remaining native Normal timing/state gate
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
NO Normal second-marker rearm in the current probe
NO Power/Sprint repeat-FIST intervention
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
