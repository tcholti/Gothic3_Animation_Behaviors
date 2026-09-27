# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-27

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
latest closed collision evidence = EV-390
collision production integration = CLOSED/PASS
ADR-0007 shared Speed/Raise INI schema = ACCEPTED
BehaviorProfiles foundation = IMPLEMENTED + independent source-review PASS
implementation SHA = 81d4964201579c9f7a989404426c3d9dc9ab4834
Speed v2 static mechanism evidence = EV-391

CURRENT = Speed v2 mechanism research/design ONLY
NEXT = close generic Quick/Action3 consumer provenance, then freeze smallest Speed implementation
RAISE = PAUSED until Speed is completely closed
```

`docs/work/active/` is clean; there is no active bounded Work implementation task.

## Shared profile foundation — accepted

Profile identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile(Normal|Quick)
```

Optional profile data:

```text
BaseSpeed=<positive finite float>
Raise=Native|On   # parsed/stored only; Raise behavior inactive
```

Semantics:

```text
BaseSpeed absent -> no G3AB Speed override
BaseSpeed=1.00 -> explicit authored base 1.00
duplicate normalized identity -> ambiguous -> no G3AB override
invalid identity -> ignored
INI parsed once during ScriptInit before hook installation
```

Exact schema: ADR-0007. Completed config task: `archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`.

## Speed v2 — current exclusive feature

Required composition:

```text
unconfigured effective speed = B * M
configured effective speed   = C * M
```

`C` is the configured authored base; legitimate Gothic/New Balance contextual modifiers `M` remain effective.

### Authoring model

For explicitly controlled Normal/Quick profiles, `1.0` is the intended **neutral authored playback scale**. Known `0.6`/`0.7` Normal attack values are treated as attack-specific reductions from that neutral reference, not desired G3AB authoring defaults. Authors can build Normal/Quick animations around a common convenient timing/frame convention and tune gameplay speed in the INI.

Do not overclaim that all or most Gothic animations have been proven to use `1.0`; that engine-wide statement is not exhaustively measured. Native/mod `B` values are technical facts only and should be measured further only if the selected implementation mechanism requires them.

### Primary compatibility environment

Keep live during Speed development/testing:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

New Balance compatibility is the primary target; native-only testing is later sanity/fallback.

Pinned Jackydima source `316d32406a133f8884e7e302752c35f66b4f54fc` matched upstream `master` when checked 2026-09-27.

```text
Script_NewBalance/FunctionHook.cpp
-> owns Script_Game +0x42A0 GetAnimationSpeedModifier
-> combines base choices with stamina/disease/arena/etc. modifiers

Script_AttackCollision/Script_AttackCollision.cpp
-> owns melee callback/collision timing behavior
-> does not own GetAnimationSpeedModifier
```

### Static mechanism state — EV-391

The old G3AB prototype is rejected because it replaces the previous hook's final result for configured attacks.

Static consumer tracing now proves a narrower composition class outside competing `+0x42A0` ownership:

```text
target Script_Game attack/Hit caller
-> call LIVE Script_Game+0x42A0
-> receive compatible result B*M
-> caller-side G3AB transform only for exact configured profile
-> (B*M) * (C/B) = C*M
-> existing downstream animation/state path
```

Direct Hit-consumer proof currently includes:

```text
Normal / gEAction_Attack (1)                 Script_Game+0x383F0
QuickAttackR/L / gEAction 4/5 route          Script_Game+0x48677
```

Additional nearby dynamic Hit consumers preserve exact action context and strengthen the same intervention class, but the exhaustive production call-site set is not yet frozen.

This mechanism can avoid owning/hooking the whole `+0x42A0` function: a targeted caller-side thunk/call redirection can invoke the live entry, allowing New Balance to compute `B*M` first, then apply only `C/B` for a configured supported profile.

Existing evidence is sufficient for the first intended base groups; do **not** request another native-speed logger run now. Unsupported/future routes remain native/fail-closed until their exact `B` is proven.

Remaining static gap before implementation freeze:

```text
ADR-0007 Quick = QuickAttack / QuickAttackR / QuickAttackL
Action4/5 consumer provenance = proven
Action3 generic QuickAttack consumer provenance = still open
```

## Immediate route

```text
1. trace gEAction_QuickAttack / Action3 into the dynamic Script_Game combat consumer family
2. close the exact Normal+Quick Hit consumer-callsite set
3. verify each selected site retains entity + exact action/profile identity needed by BehaviorProfiles
4. only if that static closure fails, freeze the smallest diagnostics-only causal probe
5. after mechanism/callsite proof, freeze bounded Speed v2 implementation
6. validate New Balance composition first; native-only sanity later
7. close Speed completely before Raise begins
```

## Read next

- exact handoff -> `BETWEEN_CHATS.md`
- Speed authority -> `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`
- profile schema -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- static mechanism evidence -> EV-391 in `EVIDENCE_LEDGER_389_ONWARD.md`
- architecture -> `DESIGN.md` §§2–3
- hook/source route -> `SOURCE_HOOK_GUIDE.md`
- third-party source -> `../references/README.md`

## Still paused

```text
NO Raise implementation/research while Speed is open
NO AttackContinuationProtection
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
