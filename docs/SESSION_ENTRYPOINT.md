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
shared BehaviorProfiles foundation = IMPLEMENTED + independent source-review PASS
implementation SHA = 81d4964201579c9f7a989404426c3d9dc9ab4834

CURRENT = Speed v2 mechanism research/design ONLY
NEXT = freeze the smallest evidence-backed Speed implementation after the composition mechanism is proven
RAISE = PAUSED until Speed is completely closed
```

`docs/work/active/` is clean; there is no active bounded Work implementation task while Normal Chat researches the Speed mechanism.

## Branch model

ADR-0006 owns:

```text
main
= last deliberately promoted stable integration checkpoint
= leave unchanged during current feature development

development
= sole active general development/research/integration branch
= shared config -> Speed -> Raise -> assembled safety regression

docs/collision-source-evidence
= historical collision branch
```

## Shared profile foundation — accepted

Production now contains startup-only `BehaviorProfiles` loading and read-only lookup for:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile(Normal|Quick)
```

Optional profile data:

```text
BaseSpeed=<positive finite float>
Raise=Native|On   # stored only; Raise behavior still inactive
```

Important semantics remain:

```text
BaseSpeed absent -> no Speed override
BaseSpeed=1.00 -> explicit configured base 1.00
duplicate normalized identity -> ambiguous -> no G3AB override
invalid mandatory identity -> ignored
INI parsed once during ScriptInit before hook installation
```

Archived implementation contract: `archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`.

## Speed v2 — current exclusive feature

Required composition:

```text
unconfigured effective speed = B(profile, action, phase) * M(context)
configured effective speed   = C(profile, action, phase) * M(context)
```

`C` is G3AB configured base speed. Applicable Gothic/New Balance contextual modifiers `M` must remain effective. Final-result replacement, copied New Balance multiplier tables, arbitrary same-hook load-order dependency and weapon-specific C++ base-speed switches remain rejected by ADR-0004.

### Primary compatibility environment

During Speed development/testing keep the intended New Balance stack active:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Compatibility with this live stack is the primary runtime target. Native-only testing remains a later fallback/sanity control, not a substitute for New Balance compatibility.

Pinned Jackydima reference:

```text
316d32406a133f8884e7e302752c35f66b4f54fc
```

Verified 2026-09-27: the pin still equals upstream `Jackydima/gothic3sdk` `master`.

Source roles:

```text
Script_NewBalance/FunctionHook.cpp
-> owns GetAnimationSpeedModifier hook at Script_Game +0x42A0
-> combines action/use-type base choices with contextual multiplier logic

Script_AttackCollision/Script_AttackCollision.cpp
-> hooks melee AI callbacks/collision timings
-> does not own GetAnimationSpeedModifier
-> remains part of full-stack attack-flow compatibility testing
```

### Current causal question

The old G3AB prototype is insufficient because it calls the prior speed function and then replaces the final configured result outright.

Research now asks:

> Where can G3AB substitute only the base term `B -> C` while leaving the live Gothic/New Balance modifier chain `M(context)` intact, without requiring arbitrary competing ownership of the whole `GetAnimationSpeedModifier` function and without copying New Balance policy?

`Script_Game +0x42A0` remains a proven observation/prototype surface, not yet frozen as the final production intervention.

## Immediate route

```text
1. inspect the tested binary/native call route around GetAnimationSpeedModifier and its consumers
2. identify whether a narrower stable base-choice/input surface exists before final modifier composition
3. compare that with current New Balance hook ownership and chaining semantics
4. only if source/static evidence is insufficient, freeze the smallest diagnostics-only runtime probe
5. do not implement Speed behavior until the composition mechanism is evidence-backed
6. after Speed closes, begin Raise
```

## Read next by question

- exact continuation -> `BETWEEN_CHATS.md`
- Speed composition rationale -> `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`
- exact profile schema -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- overall architecture -> `DESIGN.md` §§2–3
- source/hook research order -> `SOURCE_HOOK_GUIDE.md`
- current third-party compatibility source -> `../references/README.md`
- completed config implementation contract -> `archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`
- collision proof -> `EVIDENCE_INDEX.md` -> EV-389–EV-390

## Still paused

```text
NO Raise implementation/research while Speed is open
NO AttackContinuationProtection work
NO targeting/climbing work
NO promotion of development to main before the agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
