# ADR-0004 — Speed Control Authors Base Speed and Preserves Dynamic Modifiers

**Status:** Accepted  
**Date:** 2026-09-26  
**Evidence basis:** earlier standalone speed-control runtime investigation + observed stamina behavior; New Balance source/runtime compatibility observations are supporting context, not yet the final hook specification

## Context

The first G3AB speed-control prototype proved that attack playback speed can be changed, but its effective ownership is too broad: a configured attack can keep the configured speed even when depleted stamina would normally slow the equivalent native attack.

That means the prototype can replace the final effective playback speed instead of participating in Gothic's normal speed calculation.

The earlier runtime investigation also measured native action/phase base values directly, including tested 1H Normal Hit `0.600`, Quick Hit `1.000`, Power Raise `1.500` / Hit `1.000`, and 2H Normal Raise `1.000` / Hit `0.700`. Several corresponding values also appear in New Balance's speed-hook logic, alongside additional contextual modifiers.

New Balance compatibility makes the same architectural issue more important: G3AB must not erase stamina, arena, species/action, perk, or other legitimate contextual modifiers simply because an animator/user configured a base attack speed.

## Decision

A G3AB configured attack speed represents **base-speed authority**, not final effective-speed authority.

Future speed-control architecture must preserve the applicable native/mod dynamic modifier chain. Conceptually:

```text
base speed chosen/adjusted by the appropriate native + G3AB rule
-> applicable Gothic/New Balance/contextual multipliers continue to apply
-> final effective playback speed
```

The exact hook/intervention point and exact arithmetic order are **not** decided by this ADR. They remain a research question.

`Script_Game +0x42A0 GetAnimationSpeedModifier` remains a proven/prototype surface, not automatically the final production hook.

## Consequences

- Depleted stamina must still slow a configured attack when it would slow the corresponding native attack.
- New Balance modifiers must remain effective on configured attacks where those modifiers legitimately apply.
- G3AB must not solve compatibility by hard-coding copies of New Balance's whole multiplier table.
- Arbitrary DLL load order or competing same-function hooks are not accepted architecture.
- Additional standalone/New Balance runtime tests are required before speed-control v2 is designed or implemented.
- Recover continues to follow effective Hit speed; no independent final-speed ownership is introduced for Recover.
- Exact native speed values remain evidence-bounded; observed values are not generalized to untested families merely because third-party source contains similar constants.

## Current authorities

- `SPEED_CONTROL_ARCHITECTURE.md`
- `DESIGN.md` §3
- `SOURCE_HOOK_GUIDE.md`

This ADR records why future speed control must compose with the game's/mods' dynamic speed system rather than replacing the final speed result.
