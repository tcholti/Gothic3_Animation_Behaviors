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

CURRENT = Speed v2 mechanism research/design ONLY
NEXT = prove a composition/intervention mechanism, then freeze the smallest Speed implementation
RAISE = PAUSED until Speed is completely closed
```

`docs/work/active/` is clean; there is no active bounded Work implementation task.

## Branch model

```text
main        = frozen stable integration checkpoint
development = sole active branch for shared config -> Speed -> Raise -> assembled regression
```

Do not advance `main` during this feature cycle.

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

### Current causal question

The old G3AB prototype is rejected because it replaces the previous hook's final result for configured attacks.

Research asks:

> Where can G3AB substitute/transform only `B -> C` while preserving `M`, without competing for ownership of the whole `+0x42A0` function and without copying New Balance policy?

A downstream ratio transform `(B*M) * (C/B) = C*M` is a candidate only, not accepted architecture. First prove a stable consumer/intervention surface and determine whether factual `B` values are actually needed.

## Immediate route

```text
1. continue static investigation of GetAnimationSpeedModifier consumers/downstream playback path
2. locate a stable composition surface outside competing +0x42A0 entry ownership if possible
3. determine whether the mechanism requires exact B values
4. only then request missing native logger evidence if needed
5. if static evidence is insufficient, freeze the smallest diagnostics-only causal probe
6. after mechanism proof, freeze bounded Speed implementation
7. close Speed completely before Raise begins
```

## Read next

- exact handoff -> `BETWEEN_CHATS.md`
- Speed authority -> `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`
- profile schema -> `decisions/ADR-0007-shared-ini-profile-schema.md`
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
