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

Normal native rearm-source probe:
    implementation 6ca48c84e9fdf370ffdb824f9142e8ef0e267a7c
    required base 0aec52f2464c245f62d70077783ab78597952a11
    independent Normal Chat source review PASS
    local build/deploy/runtime PENDING
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

## Current diagnostic implementation under local validation

The frozen probe now has a source-reviewed implementation in:

`6ca48c84e9fdf370ffdb824f9142e8ef0e267a7c`

Exactly one file changed:

`prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp`

It preserves the proven frame-1 SP0 `5 -> 7 + ClearTriggeredList()` path and records factual `preStateRearmProven` only after the clear actually occurs.

Then, during the same factual Normal execution, it suppresses exactly one nested native exact RIGHT PhysicalFist/raw55:

```text
Item_Attack/group7 -> Item_Attack/group7
```

request at `StatePosition == 0`, but only when the same actor + C1 generation + exact RIGHT source matches the proven pre-state rearm intervention.

The original `_AI_Attack` callback remains enabled and must still be allowed to advance:

```text
StatePosition 0 -> 1
```

The frame-15 FIST remains observational only. No marker-2 clear/rearm is implemented.

No EngineBridge, header, CMake, StatePosition-write, direct-damage, cleanup or permanent-architecture change is present.

## Immediate next step

User + Normal Chat perform local validation only:

```text
sync branch in GitHub Desktop
-> confirm Changes empty
-> build Script_FrameCollisionTest Release only
-> STOP on build result
-> POP-03 deploy/hash verification if build passes
-> POP-04 startup banner
-> same Normal two-FIST Troll runtime
-> POP-07/POP-06 evidence closure
```

Preferred runtime artifact:

`research/raw/2026.09.16_troll_raw55_normal_native_rearm_source.log`

Interpretation:

```text
first hit survives
+ native 7 -> 7 suppression fires
+ SP0 -> 1 survives
+ second hit disappears
    => native setter is causally required for the current implicit second-contact opportunity

second hit still occurs
    => another native callback/state/contact mechanism owns that rearm

first hit/state progression/cleanup diverges
    => stop and analyze
```

No EV-288 exists yet. Current canonical evidence remains EV-287 until runtime closure.

## Power observation

The User reports from the same test session that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. This remains behavioral guidance, not a separate causal EV. Finish the Normal native-rearm-source question first.

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
