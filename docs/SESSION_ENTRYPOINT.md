# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-16

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If Normal Chat ends before evidence closure, use POP-11 Recovery Lock. Oversized runtime logs use POP-07. Routine oversized-log preparation is drag-and-drop onto `tools\log_evidence\Prepare-Log.cmd`; preserve/commit both the untouched raw log and generated derived package.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current probe authority: `docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`  
Latest canonical evidence: through **EV-290** in `docs/EVIDENCE_LEDGER_286_ONWARD.md`  
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
raw55 Normal native 7->7 setter as second-rearm source REJECTED — EV-288
raw55 Normal native trigger-bookkeeping reset before marker2 CONFIRMED — EV-289
raw55 Normal exact native public ALL clear reset operation IDENTIFIED — EV-290
```

## EV-290 current factual model

Representative Normal C1=3:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> existing marker-owned ClearTriggeredList()
-> first damage
-> PC_Hero becomes visited/count1

later native transition at SP0
-> existing EV-288 exact RIGHT 7 -> 7 setter request suppressed
-> PC_Hero still visited immediately before native trigger clear
-> Gothic calls exact current RIGHT eCTrigger_PS::ClearTriggeredList() ALL
   caller = Script_Game.dll + 0x386C6
   PRE  = player present/count1
   POST = visited arrays empty/player absent
-> original _AI_Attack completes SP0 -> 1
-> RIGHT remains group7

marker2 later at SP1
-> observational only
-> player already absent due to native clear

second damage
-> player inserted again

native 7 -> 5 cleanup
clean C1 finalization
```

Therefore the EV-289 hidden reset operation is factually identified as the public no-argument `eCTrigger_PS::ClearTriggeredList()` call from `Script_Game.dll+0x386C6`.

Do **not** yet claim that this clear is required for the second hit. EV-290 identifies the operation; causal necessity is the current question.

Canonical EV-290 artifact:

`research/raw/2026.09.16_troll_raw55_normal_native_trigger_clear_observation.log`

SHA256:

`E699B807059189289D4CAB6B243F966F49947C9083656EE693B8FDD21676693F`

Upload commit:

`8b483b48636deeec4fa6863533da4a7db4fe2e15`

Derived POP-07 package:

`research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_observation_large_log/`

Diagnostic implementation:

`6ef27121c5fcd1d4993b914e0f6a9a9123a2b0b7`

Local build/live DLL SHA256:

`A2E3C1B463AF804B4ABE9DA83F261009B3780995DAEEB1CB4E4D58A44EDFCB77`

## Current frozen question

Authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`

Suppress only the exact post-hit1 native ALL clear in the proven Normal C1:

```text
eCTrigger_PS::ClearTriggeredList()
Engine + 0x7DDA0
CallerModule = Script_Game.dll
CallerRVA    = 0x386C6
```

Required factual gating includes exact Normal actor/C1/current RIGHT PhysicalFist/raw55 identity, group7, proven frame-1 rearm, existing EV-288 native `7 -> 7` suppression already used, StatePosition 0, player factually present exactly once in aligned visited/count arrays, and one-shot use for the C1.

Preserve:

```text
marker1 clear unchanged and executed normally
entity-specific clear unchanged
all unrelated ALL-clear callers unchanged
existing native 7 -> 7 setter suppression
original _AI_Attack callback
marker2 observational only
native final cleanup
```

If suppression keeps the player visited and makes hit2 disappear while hit1/progression/cleanup remain healthy, the native clear is causally required. The next one-variable test may then add the authored marker2 clear as replacement. If hit2 persists, another trigger/contact mechanism remains.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO Normal marker-2 rearm until native-clear necessity is closed
NO Power/Sprint repeat-FIST intervention yet
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```

## Deployment authority

```text
live collision DLLs:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic logs:
E:\SteamLibrary\steamapps\common\Gothic 3
```

Never deploy a collision DLL to the game root.

## Remaining collision sequence

```text
Normal exact native clear necessity probe
-> if required, authored Normal marker-2 replacement/rearm proof
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```
