# ADR-0011 — Resolved Animation-Set Identity for Speed/Raise Profiles

**Status:** Accepted
**Date:** 2026-10-01
**Supersedes:** ADR-0010
**Related:** ADR-0004, ADR-0007, ADR-0008, ADR-0009, `docs/ANIMATION_RULES.md`, EV-393–EV-406

## Context

Speed configuration must follow the animation set whose timing is being authored.

Static raw-`gEUseType` normalization was initially attractive because vanilla Gothic maps several equipment types onto shared animation tokens. Runtime separation-mod testing showed that this is not the correct final identity:

```text
native Axe:
  raw UseType = Axe
  resolved request token = 2H

Axe Separation:
  raw UseType = Axe
  resolved request token = Axe

Rapier Separation:
  raw UseType = 1H
  resolved request token = Rapier

Zombie Separation:
  AnimationFamily = Zombie
  resolved request tokens = Zombie-family weapon sets
```

Rapier is decisive: raw UseType does not change, yet the animation set does. Conversely, native Axe should share 2H timing when it genuinely resolves the shared 2H assets.

The diagnostics-only EV-406 probe established that `Entity.GetAni(factualAction, factualPhase)` exposes the exact request-time animation identity at the proven Speed caller boundary, while `CurrentMovementAni()` may still be stale/outgoing.

## Decision

### 1. Profile identity follows the resolved animation set

The grouped profile identity is:

```text
AnimationFamily
+ LeftAnimationToken
+ RightAnimationToken
```

`AnimationFamily` continues to use `Animation.GetSkeletonName(...)`.

`LeftAnimationToken` and `RightAnimationToken` are extracted from the exact string returned by:

```text
Entity.GetAni(factualAction, factualPhase)
```

at the Speed request boundary.

For canonical Gothic melee names:

```text
Family_State_LeftAnimationToken_RightAnimationToken_Pose_Action_Phase_...
```

the third and fourth underscore-delimited fields are the profile tokens.

### 2. Shared animations share Speed profiles

If different raw equipment UseTypes resolve the same animation family/tokens, they intentionally use the same Speed profile.

Examples:

```text
native Hero raw 2H  -> Hero + None + 2H
native Hero raw Axe -> Hero + None + 2H

native Hero raw Staff   -> Hero + None + Staff
native Hero raw Halberd -> Hero + None + Staff
```

This directly implements the authoring rule that shared animations share authored timing.

### 3. Separated animation sets become independently configurable automatically

If a mod changes Gothic's resolved request token, the new animation set naturally selects a different profile:

```text
Axe Separation:
Hero + None + Axe

Rapier Separation:
Hero + None + Rapier

Zombie Separation:
Zombie + <left token> + <right token>

Zombie + Axe Separation:
Zombie + None + Axe
```

No mod-name detection, inventory-item exception, actor-name exception or dedicated Speed hook is required.

### 4. Raw UseType remains a factual source property, not Speed profile identity

Raw `gEUseType` remains important for collision/source semantics, diagnostics and causal research. It does not decide Speed profile identity.

This supersedes ADR-0010.

### 5. Factual action remains authoritative

Resolved animation naming does not decide the attack family.

Factual `gEAction` from the proven caller route still maps to:

```text
Normal, Quick, Power, Pierce, Hack, SimpleWhirl, Whirl
```

This matters because factual Hack may resolve a `FinishingAttack`-named animation asset. Profile attack selection remains Hack.

Sprint remains factual Action9 in actor state while the shared caller passes Power/Action2; ADR-0009 remains authoritative and Sprint has no separate Speed prefix.

### 6. Fail closed on unresolved/malformed identity

If `GetAni(action, phase)` is empty or does not satisfy the canonical minimum structure needed to extract left/right tokens, G3AB returns the live compatible speed unchanged.

Do not fall back to `CurrentMovementAni()` or guess from raw UseType.

### 7. INI field names reflect animation identity

Current grouped sections use:

```ini
AnimationFamily=Hero
LeftAnimationToken=None
RightAnimationToken=1H
```

The former `LeftAnimationUseType` / `RightAnimationUseType` spelling is superseded before the first finalized shipping INI, avoiding ambiguity with raw engine UseType.

## Consequences

- Native shared Axe/2H and Halberd/Staff routes need only the shared animation-set profile.
- Axe and Rapier separation mods can be supported with ordinary data-only profiles.
- Zombie family separation is expressed by `AnimationFamily=Zombie`.
- Combined family + animation-set separation composes naturally.
- Human bare Fist may now be included with calibrated Normal/Power reference `B=1.0`; Quick remains omitted until observed.
- The profile matcher may call `Entity.GetAni(action, phase)` once to obtain request identity; this call is identity lookup, not the live speed-owner call.
- The live compatible speed owner remains called exactly once by the bridge; C/B composition remains unchanged.
