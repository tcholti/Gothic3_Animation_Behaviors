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
Current frozen probe authority: `docs/COLLISION_RAW55_NORMAL_NATIVE_REARM_SOURCE_PROBE.md`  
Latest canonical evidence: through **EV-287** in `docs/EVIDENCE_LEDGER_286_ONWARD.md`  
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
raw55 Normal SP0 contact rearm / early first damage CLOSED/PASS — EV-287
```

EV-287 proves the exact Normal frame-1 path:

```text
FIST at StatePosition 0
-> exact current RIGHT PhysicalFist/raw55 5 -> 7
-> exact RIGHT ClearTriggeredList once
-> first native damage while StatePosition is still 0
-> first damage occurs BEFORE Gothic's ordinary Normal timer/SP transition
```

The same C1 then shows:

```text
native Normal exact RIGHT 7 -> 7
StatePosition 0 -> 1
frame-15 FIST delivered at SP1 / RIGHT still group7
NO Normal marker-2 intervention
second native damage nevertheless occurs
native 7 -> 5 cleanup
clean finalization
```

Therefore the Normal first-contact primitive is closed, but the second-contact **ownership** is not. Do not credit marker 2 with the second hit yet.

## Current frozen causal question

Test whether Gothic's intervening native exact RIGHT `7 -> 7` setter request is what implicitly rearms Normal after the first marker-owned contact.

Frozen intervention:

```text
preserve frame-1 SP0 5 -> 7 + ClearTriggeredList path unchanged
preserve first early damage opportunity

when the same factual Normal C1 later makes its native exact RIGHT 7 -> 7 request at SP0:
    suppress ONLY that one setter request
    leave the original _AI_Attack callback running
    StatePosition must still progress 0 -> 1

frame-15 FIST remains observational only
no marker-2 rearm yet
```

The decision stays in temporary `PhysicalFistProbe`. `EngineBridge` remains unchanged and transport-only.

Interpretation:

```text
first hit survives + native 7->7 suppressed + SP0->1 survives + second hit disappears
    => native setter is the implicit second rearm source

second hit still occurs
    => another native callback/state/contact mechanism owns that rearm

state/callback/cleanup divergence
    => stop and analyze
```

## Power observation

The User reports from the same test session that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. This is useful behavioral guidance and is consistent with current Power evidence, but it is not yet promoted as a separate new causal EV. Finish the Normal native-rearm-source question first.

## Remaining collision sequence

```text
Normal native rearm-source causal closure
-> if native 7->7 owns second opportunity, replace that ownership with authored marker-2 causal rearm
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
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
NO Normal marker-2 rearm in the current probe
NO Power/Sprint repeat-FIST intervention yet
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
