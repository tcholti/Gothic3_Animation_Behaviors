# ADR-0005 — Raise and Speed Use Startup-Loaded Generic Configuration Profiles

**Status:** Accepted  
**Date:** 2026-09-27  
**Related:** `docs/DESIGN.md` §§2–3, `docs/ANIMATION_RULES.md`, ADR-0004, `references/README.md`

## Context

The early `Script_G3AnimationBehaviors` prototype proved two useful mechanisms with a deliberately narrow 2H Normal fixture:

- a custom Raise can be inserted by asking Gothic's CombatMove system to execute the `Raise` phase and letting Gothic resolve the actual animation resource;
- attack playback speed can be changed through `GetAnimationSpeedModifier`.

That prototype hard-coded player + `None/2H` checks and exposed only `EnableTwoHandedNormal` / `TwoHandedNormal` settings. Those restrictions were fixture scope, not the intended final product architecture.

The project is a configurable animation-behavior framework. Raise and speed must therefore be data-selected rather than implemented as a growing collection of C++ weapon-type branches.

The current Jackydima/New Balance reference is pinned under `references/jackydima-gothic3sdk`; the source route is recorded in `references/README.md`. Current New Balance `GetAnimationSpeedModifier` source also confirms that base attack-speed selection and contextual modifiers can be combined in the same function, so speed compatibility must preserve the modifier factor rather than merely replace the final return value.

## Decision

### 1. Configuration is loaded once at startup

`G3AnimationBehaviors.ini` is parsed during DLL startup into a normalized in-memory rule table.

Runtime attack handling performs only an in-memory profile lookup. It must not reread or reparsed the INI on every attack.

Missing/unconfigured profiles leave Gothic behavior untouched.

### 2. Generic profile identity

Raise/speed profile identity is:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

Raw runtime UseTypes are normalized to animation categories according to `ANIMATION_RULES.md`.

The implementation must not contain feature-policy branches such as "if 1H", "if 2H", "if Axe", or "if Staff" merely to decide whether Raise/speed is enabled. Weapon/use-type selection belongs to configuration data and normalized runtime facts.

A modded item participates through the runtime UseType / animation category and animation family it exposes. Supporting another configured profile must not require adding a new C++ weapon branch.

No P0/P1/P2/P3 pose split is part of the user-facing Raise/speed profile identity.

### 3. Supported user-facing attack families

The intended Raise/speed configuration scope is deliberately:

```text
Normal
Quick
```

Power, Pierce, Whirl, Hack, Sprint and other attack families are not part of this configurable Raise/speed feature unless a later explicit decision expands the scope.

Quick runtime variants may have distinct factual Gothic actions internally; user-facing configuration still treats them as the Quick profile unless later evidence requires a narrower distinction.

### 4. Raise control preserves Gothic animation resolution

A configured Raise does not name a specific animation file in C++.

Conceptually:

```text
matching configured Normal/Quick attack
-> request the corresponding Raise CombatMove phase
-> Gothic resolves the animation from its normal animation-request facts
   (family/state/use types/pose/action/phase/direction/etc.)
-> after Raise completes, continue the untouched original attack path
```

This preserves Gothic's naming/resolution system. The author creates the correctly named Raise asset; G3AB enables the phase where the profile requests it.

The existing 2H Normal implementation is proof of the mechanism, not the final profile boundary. Other Normal/Quick profiles, especially custom Quick Raise, still require focused runtime validation before production acceptance.

User-facing Raise semantics are profile data (for example Native/On/Off or equivalent final syntax); exact INI spelling may be finalized during the bounded configuration implementation without changing this architecture.

### 5. Speed control authors the base term, not the final effective speed

For the configured Normal/Quick scope, reason about effective speed algebraically:

```text
unconfigured effective speed = B(profile, action, phase) * M(context)
configured effective speed   = C(profile, action, phase) * M(context)
```

where:

```text
B = native / compatible-mod base choice
C = G3AB configured base choice
M = every applicable contextual modifier that should still affect the equivalent attack
```

Current New Balance source provides concrete examples of the problem: Normal attack branches select base terms such as `0.6` or `0.7` and multiply them by `multiPlier`; Quick branches/default paths use a `1.0` base with the applicable multiplier, while contextual logic also covers stamina, arena, disease and other conditions.

Therefore G3AB must effectively substitute the configured base term while allowing the applicable modifier factor to continue to operate.

The exact intervention/hook point is still a research question under ADR-0004. This ADR does **not** authorize:

```text
final-speed replacement
copying New Balance's complete multiplier table
same-hook DLL load-order dependency
weapon-specific C++ base-speed switches
global animation-speed override
```

If profile-specific reference/base data is required by the eventual composition mechanism, it belongs in generic configuration/profile data or another generic factual source, not in weapon-name branches inside behavior code.

### 6. Recover remains derived

There is no independent user-facing `RecoverSpeed` control. Recover continues to follow the effective Hit speed as already decided by ADR-0004.

## Consequences

- The narrow old 2H Normal INI/source layout is a prototype fixture and must not define the production schema.
- Adding configured 1H, Torch+1H, Shield+1H, Dual, 2H, Axe, Staff, Halberd, or modded profiles is a data/configuration responsibility when their runtime animation categories are available, not a C++ feature expansion.
- Raise and speed can share the same normalized profile lookup while remaining separate behavior modules.
- Collision remains independently marker-driven and is not selected by these Raise/speed profiles.
- Configuration parsing cost occurs at startup; attack-time cost is bounded in-memory lookup and the enabled behavior itself.
