# ADR-0004 — Speed Control Authors Base Speed and Preserves Dynamic Modifiers

**Status:** Accepted  
**Date:** 2026-09-26  
**Clarified:** 2026-09-27  
**Evidence basis:** earlier standalone speed-control runtime investigation + observed stamina behavior; current New Balance source/runtime compatibility observations are supporting context, not yet the final hook specification

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

Several corresponding values also appear in the current New Balance speed-hook logic, alongside additional contextual modifiers. This corroborates that values such as Normal 1H `0.6`, Normal 2H/Axe/Staff/Halberd `0.7`, and Quick `1.0` are part of the effective base-selection problem we must compose with.

However, those native/mod base values are **not the desired G3AB authoring defaults**. They are implementation/evidence facts only.

The animation-authoring goal is to avoid forcing Blender assets for different weapon families to use different frame counts or deliberately compressed timing merely to compensate for Gothic's historical base-speed constants. G3AB should let authored Normal/Quick animations share a convenient nominal timing and let the INI choose the intended gameplay playback rate.

New Balance compatibility makes the architectural issue more important: G3AB must not erase stamina, arena, disease, species/action, perk, skill, or other legitimate contextual modifiers simply because an animator/user configured a base attack speed.

## Decision

A G3AB configured attack speed represents **base-speed authority**, not final effective-speed authority.

### Authoring baseline

For Normal and Quick profiles that the mod author chooses to control, the intended G3AB nominal authored baseline is:

```text
BaseSpeed = 1.0
```

This means `1.0` is the convenient authoring reference: an animation authored around the chosen nominal frame/timing standard can play at that nominal rate before contextual gameplay modifiers are applied.

### Neutral playback-scale interpretation

For Speed design, treat `1.0` as the **neutral playback scale** and values such as `0.6` and `0.7` as attack-specific playback scalars below that neutral scale. This interpretation is strongly supported by the observed/native New Balance values and is the useful model for animation authoring: G3AB is effectively restoring configured Normal/Quick attacks to the neutral authored scale first, then allowing the INI to tune them above or below it.

Do **not** overstate this as a proven engine-wide claim that "most Gothic animations use 1.0". The project has not exhaustively measured all animation classes. The durable fact needed by G3AB is narrower: `1.0` is the neutral authored reference for our controlled profiles, while `0.6`/`0.7` are known attack-specific reductions on tested/current routes.

Per-profile INI values may then deliberately deviate from `1.0`, for example conceptually:

```text
2H Normal = 1.00
2H Quick  = 1.05 or 1.10
1H Normal = 1.05
1H Quick  = 1.10 or 1.15
```

Those numbers are examples of author tuning, not frozen production defaults for every profile.

ADR-0007 semantics remain unchanged:

```text
BaseSpeed absent -> no G3AB Speed override / preserve compatible native-mod behavior
BaseSpeed=1.00 -> explicit G3AB authored base value of 1.00
```

Therefore G3AB does **not** globally force every attack to `1.0` merely because the DLL is installed. A profile that should use the normalized authored baseline must explicitly configure `BaseSpeed=1.0`; other exact profiles may use different values or remain unconfigured.

Future speed-control architecture must preserve the applicable native/mod dynamic modifier chain. Conceptually:

```text
existing native/mod base B
        ↓
G3AB configured authored base C (nominally 1.0 unless author chooses otherwise)
        ↓
applicable Gothic + compatible-mod dynamic modifiers M
        ↓
final effective playback speed
```

Required invariant:

> If the same contextual multiplier would affect an otherwise equivalent unconfigured attack, it must also affect a G3AB-configured attack unless a future explicit feature deliberately owns that multiplier.

Examples that must remain composable where applicable include:

```text
Gothic/New Balance stamina or exhaustion slowdown
New Balance arena/NPC modifiers
New Balance disease modifiers
New Balance species/action modifiers
New Balance perk/skill-related speed modifiers
other proven contextual multipliers discovered during research
```

The exact hook/intervention point and exact arithmetic order are **not** decided by this ADR. They remain a research question.

`Script_Game +0x42A0 GetAnimationSpeedModifier` remains a proven/prototype observation surface, not automatically the final production hook.

## Native/mod base values — technical role only

Native/mod base values such as `0.6`, `0.7`, and `1.0` matter only where the chosen composition mechanism technically needs them.

For example, a downstream transform of an already-computed result could require:

```text
existing effective = B * M
configured result  = (B * M) * (C / B)
                   = C * M
```

Such an approach would require a trustworthy factual `B` for the exact route. If the final intervention instead occurs before the base choice or otherwise does not require `B`, exhaustive native-base logging is unnecessary.

Accordingly, native speeds are **not product defaults** and are **not automatically a prerequisite for implementation**. Additional native-speed logging should be requested only when the selected mechanism needs missing calibration/evidence.

## Consequences

- Normal/Quick animation authors can target a common nominal timing/frame convention instead of baking Gothic's `0.6`/`0.7` distinctions into the source animations.
- Per-profile gameplay feel is tuned in the INI through explicit `BaseSpeed` values.
- Depleted stamina must still slow a configured attack when it would slow the corresponding compatible native/New Balance attack.
- New Balance modifiers must remain effective on configured attacks where those modifiers legitimately apply.
- G3AB must not solve compatibility by hard-coding copies of New Balance's whole multiplier table.
- Arbitrary DLL load order or competing same-function hooks are not accepted architecture.
- Recover continues to follow effective Hit speed; no independent final-speed ownership is introduced for Recover.
- Exact native speed values remain evidence-bounded; observed values are not generalized to untested families merely because third-party source contains similar constants.
- The existing prototype behavior is not accepted as final architecture where it bypasses downstream native/mod modifiers.

## Research required before speed-control v2

Research is now mechanism-first rather than exhaustive native-timer-first.

```text
A. composition mechanism
   - identify where the live New Balance/Gothic result is produced and consumed
   - seek the narrowest intervention that can replace/transform only the base contribution
   - avoid competing ownership of the full +0x42A0 function
   - determine whether the candidate mechanism actually requires factual B values

B. current intended New Balance stack (primary compatibility environment)
   - Script_G3AnimationBehaviors.dll
   - Script_NewBalance.dll
   - Script_AttackCollision.dll
   - configured full-stamina control
   - configured depleted-stamina control
   - representative disease/arena/other practical modifier controls where evidence requires them
   - unconfigured controls

C. native-only fallback/sanity
   - run after the primary New Balance composition works
   - collect additional exact native base values only if the selected implementation needs them
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
unverified per-family constants used as production policy
```

## Current authorities

- `docs/DESIGN.md` §3
- `docs/SOURCE_HOOK_GUIDE.md`
- `docs/decisions/ADR-0007-shared-ini-profile-schema.md`

This ADR records why future speed control must compose with the game's/mods' dynamic speed system rather than replacing the final speed result, while treating `1.0` as the intended nominal authored baseline for explicitly configured Normal/Quick profiles.