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

Normal native trigger-clear observation probe:
    implementation 6ef27121c5fcd1d4993b914e0f6a9a9123a2b0b7
    required base 1e411056a586b71217a1f5941774b44e16e6588e
    independent Normal Chat source review PASS
    local build/deploy/runtime PENDING
```

EV-289 establishes:

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

marker 2 later
-> PC_Hero already absent
-> no Normal marker-2 intervention

hit 2
-> PC_Hero enters visited state again

native 7 -> 5 cleanup
clean C1 finalization
```

Therefore Gothic supplies an implicit trigger-bookkeeping reset before marker 2. The exact native operation remains unknown. Do not attribute the reset to marker 2, the suppressed collision-group setter, `ResetOnUntouch`, or StatePosition itself.

Canonical EV-289 artifact:

`research/raw/2026.09.16_troll_raw55_normal_trigger_state_observation.log`

SHA256:

`978817C03EE01EA3098D265CFE85544F4D3DE06019279AD04C337C4ADBE00D08`

## Current implementation under local validation

Source-reviewed implementation:

`6ef27121c5fcd1d4993b914e0f6a9a9123a2b0b7`

Exactly three diagnostics-source files changed from the frozen base:

```text
EngineBridge.cpp       +47 / -0
PhysicalFistProbe.cpp  +180 / -0
PhysicalFistProbe.h    +17 / -0
```

The probe adds diagnostics-only hooks for:

```text
eCTrigger_PS::ClearTriggeredList()          Engine + 0x7DDA0
eCTrigger_PS::ClearTriggeredList(eCEntity*) Engine + 0x7DDF0
```

Both hooks use explicit `.ThisCall()` transport, capture caller identity, record PRE state, execute the original exactly once, then record POST state. `EngineBridge` owns hook transport only. `PhysicalFistProbe` owns exact Normal actor/C1/current-RIGHT/PhysicalFist eligibility and all interpretation/logging.

The marker-1 clear remains a useful control: the intervention identity exists before that clear, while `preStateRearmProven` is set only after it returns. The hook can therefore record the control call with factual `PreStateRearmProven=0` without broadening eligibility.

This remains observation-only:

```text
NO clear suppression
NO new clear
NO change to marker-1 clear
NO change to native 7->7 suppression
NO marker-2 rearm
NO collision-group mutation
NO StatePosition write
NO direct damage
NO cleanup/repair change
NO polling
NO production-module change
```

## Immediate next step

User + Normal Chat perform local validation only:

```text
GitHub Desktop: Fetch origin -> Pull origin -> Fetch origin
-> confirm Changes empty
-> build Script_FrameCollisionTest Release only
-> STOP on build result
-> POP-03 deploy/hash/twin verification if build passes
-> deploy only to E:\SteamLibrary\steamapps\common\Gothic 3\scripts
-> POP-04 startup banner
-> same Normal two-FIST Troll runtime
-> preserve log from E:\SteamLibrary\steamapps\common\Gothic 3
-> POP-07/POP-06 evidence closure
```

Preferred runtime artifact:

`research/raw/2026.09.16_troll_raw55_normal_trigger_clear_observation.log`

No EV-290 exists yet.

## Decisive interpretation

```text
later public clear after hit 1
+ PRE player present
+ POST player absent/reset
    => factual public reset operation/caller identified

ENTITY clear with PC_Hero
+ player removed
    => factual player-specific reset operation identified

known marker-1 clear observed
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
