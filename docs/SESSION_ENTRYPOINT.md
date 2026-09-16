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
Current probe authority: `docs/COLLISION_RAW55_NORMAL_TRIGGER_STATE_OBSERVATION_PROBE.md`  
Latest canonical evidence: through **EV-288** in `docs/EVIDENCE_LEDGER_286_ONWARD.md`  
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

Normal trigger-state observation probe:
    implementation ec20e769a347bd206577427bfd28a85bd51a79b3
    required base 9ad32fa078dfc4d64ad732317eacae17e10d9161
    independent Normal Chat source review PASS
    local build/deploy/runtime PENDING
```

EV-288 proves:

```text
frame-1 SP0 FIST -> exact RIGHT 5 -> 7 + ClearTriggeredList
-> first damage while SP0

later exact native Normal RIGHT 7 -> 7 setter request
-> suppressed once
-> original _AI_Attack callback still advances SP0 -> 1

frame-15 FIST
-> delivered at SP1
-> no Normal marker-2 intervention

second damage still occurs
native final 7 -> 5 cleanup remains healthy
clean C1 finalization
```

Therefore the native collision-group setter itself is **not** required for the second Normal damage opportunity. Do not infer that StatePosition itself causes rearm; that has not been isolated.

Canonical EV-288 artifact:

`research/raw/2026.09.16_troll_raw55_normal_native_rearm_source.log`

SHA256:

`AB8E7B8B300F08CD61B01E7338FC672E6A09DE7D57F055F4FFAFD68514628C6E`

## Current implementation under local validation

Source-reviewed implementation:

`ec20e769a347bd206577427bfd28a85bd51a79b3`

Exactly one source file changed from the frozen base:

`prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp`

The change is additions-only (`+339 / -0`) and preserves the EV-288 behavior. It adds read-only exact-source trigger-state observation using the official SDK's:

```text
eCTrigger_PS::EntitiesVisited
eCTrigger_PS::EntitiesVisitedCount
gCTouchDamage_PS::ResetOnUntouch
eCEntityProxy::GetEntity() const
```

Snapshots are scoped to the proven same actor + same C1 + exact current RIGHT PhysicalFist/raw55 intervention and are logged at:

```text
POST_PRESTATE_REARM
CALLBACK_CHANGE (change-only)
NATIVE_7TO7_SUPPRESS_PRE
SP0_TO1_POST_CALLBACK
LATER_FIST
```

The key question is whether `PC_Hero` enters the visited state after hit 1 and later disappears/resets before hit 2 without an explicit marker-2 clear.

This remains observation-only:

```text
NO new ClearTriggeredList
NO new SetCollisionGroup intervention
NO mutation of EntitiesVisited / EntitiesVisitedCount
NO ResetOnUntouch write
NO marker-2 rearm
NO StatePosition write
NO new hook/RVA
NO EngineBridge change
NO direct damage
NO cleanup/repair change
```

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

`research/raw/2026.09.16_troll_raw55_normal_trigger_state.log`

No EV-289 exists yet.

## Power observation

The User reports that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. This remains behavioral guidance, not a separate causal EV.

## Remaining collision sequence

```text
Normal trigger-state observation
-> isolate natural reset mechanism only if evidence requires it
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
