# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-16

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Routine oversized-log preparation is drag-and-drop onto `tools\log_evidence\Prepare-Log.cmd`; preserve/commit the untouched source artifact and generated derived package. After evidence closure, processed source artifacts move unchanged from `research/raw/` to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Latest canonical evidence: **EV-291** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      SP1 first-contact CLOSED/PASS through EV-279
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED — EV-283
raw55 Normal SP0 physical opening CLOSED/PASS — EV-286
raw55 Normal SP0 contact rearm / early first damage CLOSED/PASS — EV-287
raw55 Normal native 7->7 setter as second-rearm source REJECTED — EV-288
raw55 Normal native trigger-bookkeeping reset before marker2 CONFIRMED — EV-289
raw55 Normal exact native public ALL-clear reset operation IDENTIFIED — EV-290
raw55 Normal native ALL-clear causal necessity CLOSED/PASS — EV-291
```

## EV-291 factual result

The User-local build/deploy/load/runtime sequence passed for diagnostic implementation:

```text
2839c8c271fa240b81ce5ccd203c34058870a5bb
DLL SHA256 = 0F2CBF35199D111C405E03E5AE824B0AC76BF47B06C1BF13A47098BCFFF6F830
```

EV-291 proves Route A:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList executes normally
-> first damage
-> PC_Hero becomes visited/count1

later native transition
-> existing exact native 7 -> 7 setter suppression fires
-> PC_Hero still visited
-> exact native ALL clear from Script_Game.dll + 0x386C6 is eligible
-> SUPPRESS_CLEAR=1
-> original clear is skipped
-> PC_Hero remains visited/count1
-> original _AI_Attack still completes SP0 -> 1

marker2 later
-> observational only
-> PC_Hero still visited/count1
-> second damage disappears

native RIGHT 7 -> 5 cleanup
-> clean C1 finalization
```

User visual result: **only the first swing damaged**.

Conclusion:

> The exact native public ALL clear from `Script_Game.dll + 0x386C6` is causally required for Normal's implicit second same-C1 damage opportunity in the tested route.

## Immediate next responsibility — NORMAL CHAT DESIGN/FREEZE ONLY

Do not launch another Work task automatically and do not modify production architecture yet.

The next smallest one-variable causal probe may:

```text
preserve EV-291 exact native ALL-clear suppression
+ keep marker1 unchanged
+ let marker2 perform exactly one replacement ClearTriggeredList()
+ preserve all other controls/cleanup
```

Question:

```text
Does authored marker2 replacement clear restore hit2?
```

If yes, Normal marker2 triggered-list rearm ownership is proven. If no, preserve the contradiction and continue causal isolation.

Freeze that exact probe contract in Normal Chat before any Work implementation.

## Evidence retrieval discipline

Do **not** scan raw/archive evidence directories during orientation.

Use in this order:

1. this file;
2. `BETWEEN_CHATS.md`;
3. EV-291 in `EVIDENCE_LEDGER_291_ONWARD.md`;
4. the EV-291 derived package only if exact runtime verification is needed.

EV-291 derived package:

```text
research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_suppression_large_log/
```

Canonical source provenance was uploaded in commit:

```text
056951242b549c0de690ef80714b0806c688ef28
```

Source SHA256:

```text
33C2B2F3E7732B3AB9BEB42C4ED6528D91E0F08F5782F498AF9F1F1A231D9D98
```

## Deployment authority

```text
live collision DLLs:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic logs:
E:\SteamLibrary\steamapps\common\Gothic 3
```

Never deploy a collision DLL to the game root.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO production Normal marker2 behavior until replacement-clear causal proof closes
NO Power/Sprint repeated-FIST intervention yet
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
