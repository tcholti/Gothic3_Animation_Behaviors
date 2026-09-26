# ADR-0004 — Speed Control Authors Base Speed and Preserves Dynamic Modifiers

**Status:** Accepted  
**Date:** 2026-09-26  
**Evidence basis:** earlier standalone speed-control runtime investigation + observed stamina behavior; New Balance source/runtime compatibility observations are supporting context, not yet the final hook specification

## Context

The first G3AB speed-control prototype proved that attack playback speed can be changed, but its effective ownership is too broad: a configured attack can keep the configured speed even when depleted stamina would normally slow the equivalent native attack.

That means the prototype can replace the final effective playback speed instead of participating in Gothic's normal speed calculation.

The earlier runtime investigation also measured native action/phase base values directly, including tested:

```text
1H Normal / Action1 Hit        = 0.600
QuickAttackL / Action5 Hit     = 1.000
PowerAttack / Action2 Raise    = 1.500
PowerAttack / Action2 Hit      = 1.000
2H Normal Raise                = 1.000
2H Normal Hit                  = 0.700
```

These values are direct runtime observations for those tested routes; they must not be generalized automatically to untested families.

Several corresponding values also appear in New Balance's speed-hook logic, alongside additional contextual modifiers. That is useful corroboration, but it does not establish the exact current distributed New Balance binary calculation order.

New Balance compatibility makes the architectural issue more important: G3AB must not erase stamina, arena, species/action, perk, skill, or other legitimate contextual modifiers simply because an animator/user configured a base attack speed.

## Decision

A G3AB configured attack speed represents **base-speed authority**, not final effective-speed authority.

Future speed-control architecture must preserve the applicable native/mod dynamic modifier chain. Conceptually:

```text
native/action/phase base
        ↓
G3AB configured base choice or base adjustment
        ↓
applicable Gothic + compatible-mod dynamic modifiers
        ↓
final effective playback speed
```

Required invariant:

> If the same contextual multiplier would affect an otherwise equivalent unconfigured attack, it must also affect a G3AB-configured attack unless a future explicit feature deliberately owns that multiplier.

Examples that must remain composable where applicable include:

```text
Gothic stamina / exhaustion slowdown
New Balance arena/NPC modifiers
New Balance species/action modifiers
New Balance perk/skill-related speed modifiers
other proven contextual multipliers discovered during research
```

The exact hook/intervention point and exact arithmetic order are **not** decided by this ADR. They remain a research question.

`Script_Game +0x42A0 GetAnimationSpeedModifier` remains a proven/prototype surface, not automatically the final production hook.

## Consequences

- Depleted stamina must still slow a configured attack when it would slow the corresponding native attack.
- New Balance modifiers must remain effective on configured attacks where those modifiers legitimately apply.
- G3AB must not solve compatibility by hard-coding copies of New Balance's whole multiplier table.
- Arbitrary DLL load order or competing same-function hooks are not accepted architecture.
- Recover continues to follow effective Hit speed; no independent final-speed ownership is introduced for Recover.
- Exact native speed values remain evidence-bounded; observed values are not generalized to untested families merely because third-party source contains similar constants.
- The existing prototype behavior is not accepted as final architecture where it bypasses downstream native/mod modifiers.

## Research required before speed-control v2

Before freezing the next speed implementation, collect at minimum:

```text
A. standalone Gothic
   - representative 1H / 2H / Staff/Axe families
   - relevant Raise / Hit / Recover observations
   - full-stamina vs depleted-stamina comparisons

B. current intended New Balance stack
   - same representative attacks
   - exact effective/base values at candidate hook surfaces
   - Troll/Sprint and other known New Balance modifiers
   - arena/skill/perk modifiers where practical

C. composition tests
   - configured attack at full stamina
   - same configured attack at depleted stamina
   - configured attack under New Balance modifier conditions
   - unconfigured native controls
```

The causal question is not merely "can G3AB set a speed?" It is:

> **Where can G3AB author the intended base speed while leaving Gothic's and compatible mods' legitimate dynamic multiplier chain intact?**

## Hard exclusions before evidence

Do not freeze or implement yet:

```text
final-speed replacement as intended architecture
same-hook load-order dependency
New Balance DLL/version detection as primary design
hard-coded copies of every New Balance multiplier
global animation-speed override
stamina bypass
unverified per-family constants
```

## Current authorities

- `docs/DESIGN.md` §3
- `docs/SOURCE_HOOK_GUIDE.md`

This ADR records why future speed control must compose with the game's/mods' dynamic speed system rather than replacing the final speed result.
