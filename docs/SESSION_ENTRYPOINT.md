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

CURRENT = shared startup parsing/normalization/profile lookup foundation only
NEXT = Speed v2 research/design/implementation/testing ONLY
RAISE = PAUSED until Speed is completely closed
```

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

Current cycle:

```text
development
-> collision production integration CLOSED/PASS EV-390
-> shared INI/profile schema ACCEPTED ADR-0007
-> shared config foundation
-> finish Speed v2 completely
-> finish Raise completely
-> assembled collision + Speed + Raise safety regression
-> deliberate promotion to main
```

The assembled regression is a final safety check that later features did not break already accepted behavior; it is not another Raise research phase.

## Shared profile architecture

Profile identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

`ActionProfile` = `Normal` or `Quick` only. UseType fields use normalized animation tokens from `ANIMATION_RULES.md`; no P0/P1/P2/P3 user-facing split and no weapon-named C++ policy branches merely to select configuration.

ADR-0007 freezes free-form sections:

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
BaseSpeed=0.80
Raise=Native
```

The `Profile.*` suffix is a unique author label only; explicit fields own runtime matching.

Semantics:

```text
BaseSpeed absent -> native/compatible-mod Speed behavior
BaseSpeed=1.00 -> explicit configured base 1.00
Raise absent/Native -> native Raise behavior
Raise=On -> future configured Raise activation
invalid mandatory identity -> ignore profile
duplicate normalized identity -> ambiguous -> no G3AB override for that identity
INI parsed once at startup -> normalized in-memory table
runtime -> bounded in-memory lookup only
```

The exact pinned SDK revision `90bfd344de4510dda7ac9da7461cc7f1eac911f7` exposes `eCConfigFile` section/key enumeration (`GetSections`, `GetSectionBlock`, `GetSectionArray`) plus `Contains`, `GetString` and scalar getters, so no numbered profile registry is required.

## Speed — next exclusive behavior feature

```text
unconfigured effective speed = B(profile, action, phase) * M(context)
configured effective speed   = C(profile, action, phase) * M(context)
```

`C` is G3AB configured base speed; applicable Gothic/New Balance contextual modifiers `M` remain effective. Exact intervention point/mechanism remains focused research under ADR-0004. Final-result replacement, copying New Balance's multiplier table, arbitrary same-hook load-order dependency and weapon-specific C++ base-speed switches are rejected.

## Raise — paused

The shared config foundation may parse/store the future Raise field, but no Raise hook, intervention or behavior begins while Speed is open. Later `Raise=On` follows ADR-0005: request Raise through Gothic CombatMove semantics and let Gothic resolve the actual animation normally.

## Immediate route

```text
1. freeze bounded source-only shared-config implementation task
2. implement Profile.* enumeration + identity normalization/validation + optional BaseSpeed/Raise storage
3. load once during ScriptInit and expose bounded in-memory lookup
4. NO Speed hook/composition behavior yet
5. NO Raise behavior
6. independent source review
7. then begin Speed v2 mechanism research only
```

## Read next by question

- exact continuation -> `BETWEEN_CHATS.md`
- Speed composition rationale -> `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`
- generic profile architecture -> `decisions/ADR-0005-raise-speed-config-profiles.md`
- branch/sequencing -> `decisions/ADR-0006-development-branch-and-sequential-speed-raise.md`
- exact INI schema -> `decisions/ADR-0007-shared-ini-profile-schema.md`
- overall architecture -> `DESIGN.md` §§2–3
- normalized animation tokens -> `ANIMATION_RULES.md`
- third-party compatibility source -> `../references/README.md`
- collision proof -> `EVIDENCE_INDEX.md` -> EV-389–EV-390

## Still paused

```text
NO Speed behavior implementation before shared config foundation passes source review
NO Raise implementation/research while Speed is open
NO AttackContinuationProtection work
NO targeting/climbing work
NO promotion of development to main before the agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
