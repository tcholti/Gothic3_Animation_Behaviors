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
```

Current source task is the **Normal pre-StatePosition FIST probe** only.

EV-283 shows factual Normal FIST at:

```text
Action1 / Family NORMAL / Hit
StatePosition=0
RIGHT PhysicalFist/raw55 group5
valid C1
no Normal early-suppression proof yet
```

Frozen intervention:

```text
that exact SP0 authored FIST
-> exact current RIGHT raw55 SetCollisionGroup(Item_Attack / 7)
-> ClearTriggeredList=0
-> no StatePosition write
-> no damage call
-> no cleanup intervention
```

Then preserve and observe the original Normal callback. The intended PASS result is later native `StatePosition 0 -> 1`, native damage when contact occurs, native `7 -> 5` cleanup, and clean C1 finalization.

Do not copy Quick's triggered-list clear into this probe. Normal first contact already passed at SP1 with `ClearTriggeredList=0`.

No permanent raw55 implementation is authorized. Work must not build. Normal Chat reviews the source before User + Normal Chat build/deploy/runtime testing.

## Remaining collision sequence

```text
Normal pre-state causal closure
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
NO non-Quick repeat-FIST intervention in this task
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
