# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-16

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If Normal Chat ends before evidence closure, use POP-11 Recovery Lock. Oversized runtime logs use POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current probe authority: `docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_OBSERVATION_PROBE.md`  
Latest canonical evidence: through **EV-289** in `docs/EVIDENCE_LEDGER_286_ONWARD.md`  
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
```

EV-289 establishes the current Normal two-contact sequence:

```text
marker 1 at SP0
-> exact RIGHT 5 -> 7 + ClearTriggeredList
-> trigger visited state empty

hit 1
-> PC_Hero enters exact RIGHT visited state / count1

immediately before native 7 -> 7 suppression
-> PC_Hero still visited
-> ResetOnUntouch=0

native exact RIGHT 7 -> 7 setter suppressed
-> original _AI_Attack still advances SP0 -> 1
-> exact RIGHT visited state becomes empty during that callback
-> ResetOnUntouch remains 0

marker 2 later at SP1
-> PC_Hero already absent
-> no Normal marker-2 intervention

hit 2
-> PC_Hero enters visited state again

native 7 -> 5 cleanup
clean C1 finalization
```

Therefore Gothic supplies an **implicit trigger-bookkeeping reset before marker 2**. The exact native operation remains unknown. Do not attribute the reset to marker 2, the suppressed collision-group setter, `ResetOnUntouch`, or StatePosition itself.

Canonical EV-289 artifact:

`research/raw/2026.09.16_troll_raw55_normal_trigger_state_observation.log`

SHA256:

`978817C03EE01EA3098D265CFE85544F4D3DE06019279AD04C337C4ADBE00D08`

Diagnostic implementation:

`ec20e769a347bd206577427bfd28a85bd51a79b3`

Local build/live DLL SHA256:

`D336619855E4812EA950797057D57BC44D41F141DA244D209880793C0ED69367`

## Current frozen question

Identify whether one of Gothic's exact public trigger-clear APIs performs that reset.

Static anchors from the tested binaries:

```text
Script_Game.dll imports PSTouchDamage::ClearTriggeredList()

Script.dll:
PSTouchDamage::ClearTriggeredList() = Script + 0x13720
-> thin property-set wrapper / tail-jump

Engine.dll:
eCTrigger_PS::ClearTriggeredList()          = Engine + 0x7DDA0
eCTrigger_PS::ClearTriggeredList(eCEntity*) = Engine + 0x7DDF0
```

Current authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_OBSERVATION_PROBE.md`

The next diagnostics-only probe adds two exact Engine clear-function observation hooks under `FRAME_COLLISION_DIAGNOSTICS`. `EngineBridge` owns only hook transport. `PhysicalFistProbe` owns exact Normal actor/C1/RIGHT/raw55 eligibility and factual logging.

For relevant exact RIGHT calls, observe PRE and POST trigger state plus caller module/RVA. Preserve every original clear call exactly once.

The task must not:

```text
suppress a clear
add a clear
change the existing marker-1 clear
change the existing native 7->7 suppression
add marker-2 rearm
write StatePosition
change collision cleanup/repair
change Quick/Power/Sprint/raw8 behavior
enter production architecture
```

Decisive interpretation:

```text
post-hit1 public clear observed
+ PRE player visited
+ POST player absent/reset
    => factual public reset operation/caller identified

entity-specific clear(PC_Hero) observed
+ player removed
    => factual player reset operation identified

known marker-owned initial clear observed
+ no later public clear
+ EV-289 reset still occurs
    => public clear APIs ruled out; inspect lower/private trigger internals
```

## Deployment authority

Use `docs/LOCAL_WORKSTATION_PATHS.md`.

```text
live collision DLLs:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic logs:
E:\SteamLibrary\steamapps\common\Gothic 3
```

Never deploy `Script_FrameCollisionTest.dll` or `Script_FrameCollisionBehaviorTest.dll` to the game root.

## Power observation

The User reports that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. This remains behavioral guidance, not a separate causal EV.

## Remaining collision sequence

```text
Normal exact native trigger-clear observation
-> if a public clear is identified, isolate/causally test it only if needed
-> establish authored Normal marker-2 ownership
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
NO Normal marker-2 rearm yet
NO Power/Sprint repeat-FIST intervention yet
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
