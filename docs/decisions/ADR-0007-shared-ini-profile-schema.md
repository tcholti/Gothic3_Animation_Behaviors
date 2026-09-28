# ADR-0007 — Shared INI Profile Schema for Speed and Raise

**Status:** Accepted  
**Date:** 2026-09-27  
**Revised:** 2026-09-28  
**Related:** ADR-0004, ADR-0005, ADR-0006, `docs/DESIGN.md` §§2–3, `docs/ANIMATION_RULES.md`

## Context

Speed is the next exclusive feature after EV-390 closed collision production integration. Raise remains paused until Speed is completely closed, but both features must share one configuration/profile model so the project does not redesign its INI when Raise work begins.

The original prototype INI hard-coded 2H Normal keys and therefore did not represent the intended generic product architecture.

Runtime work on 2026-09-28 additionally established two important constraints:

1. the user-facing animation family must remain the Gothic animation-name family token (`Hero`, `Demon`, `Goblin`, etc.), not an incidental skeleton/resource API string;
2. the selected downstream Speed composition mechanism needs factual reference base values `B` in order to transform a compatible result `B*M` into configured `C*M` without replacing contextual modifiers.

The revised schema therefore stores those factual reference values in generic profile data instead of hard-coding weapon/family base tables in behavior code.

The production project builds against Gothic 3 SDK revision:

`90bfd344de4510dda7ac9da7461cc7f1eac911f7`

At that exact revision `eCConfigFile` supports direct known-key access and section enumeration, so the schema does not need a numbered profile registry.

## Decision

### 1. One free-form section per profile

Every behavior profile is an INI section whose name begins with:

```text
Profile.
```

Example:

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.60
BaseSpeed=0.80
RaiseOverride=Off
```

The text after `Profile.` is an author-facing label only. It is **not** parsed as behavior identity and does not participate in runtime matching.

### 2. Exact profile identity lives in explicit fields

The mandatory identity fields are:

```text
AnimationFamily
LeftAnimationUseType
RightAnimationUseType
ActionProfile
```

Together they form:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

`AnimationFamily` uses the Gothic animation-name family token, for example `Hero`, `Demon`, `Goblin`, `Wolf`, etc. `ANIMATION_RULES.md` defines the first animation-name token as this family. The exact runtime source used to recover that token must be factual and is being validated separately; the schema must not require raw skeleton/resource names such as `G3_Hero_Skeleton`.

`LeftAnimationUseType` and `RightAnimationUseType` use normalized animation tokens owned by `ANIMATION_RULES.md`, not blindly serialized raw `gEUseType` spelling.

`ActionProfile` currently accepts only:

```text
Normal
Quick
```

C++ remains responsible for mapping factual engine actions to these profile classes. Configuration does not redefine Gothic action identity.

There is no P0/P1/P2/P3 field in the user-facing profile identity.

### 3. `BaseSpeed` is the single desired authored playback base

Speed uses:

```ini
BaseSpeed=<positive finite float>
```

`BaseSpeed` is the desired configured base `C`, not the native/reference value `B` and not the final effective speed.

Semantics:

```text
BaseSpeed absent
-> no G3AB Speed override for this profile
-> native / compatible-mod behavior remains authoritative

BaseSpeed present and valid
-> desired configured authored base C
-> Hit targets C while preserving applicable contextual modifier M
```

A non-numeric, non-finite, zero or negative `BaseSpeed` is invalid and must fail closed for Speed.

No separate user-facing `HitSpeed` exists. `BaseSpeed` is the Hit target.

### 4. `ReferenceHitBaseSpeed` is factual calibration data

The selected downstream composition mechanism observes an already-compatible result:

```text
compatible = B_hit * M
```

and therefore requires the factual reference base `B_hit` for the exact configured profile:

```ini
ReferenceHitBaseSpeed=<positive finite float>
```

Composition is conceptually:

```text
(B_hit * M) * (BaseSpeed / B_hit) = BaseSpeed * M
```

`ReferenceHitBaseSpeed` is not a tuning value. It records an evidence-backed native/compatible base fact required by the mechanism.

For this mechanism:

```text
BaseSpeed present + missing/invalid ReferenceHitBaseSpeed
-> no Speed intervention
-> return compatible result unchanged
```

Reference base facts belong in generic profile/configuration data or another generic factual source, not in weapon/family-specific C++ policy tables.

### 5. Raise uses `RaiseOverride=On|Off`

The user-facing Raise key is:

```ini
RaiseOverride=Off
```

or:

```ini
RaiseOverride=On
```

Semantics:

```text
RaiseOverride missing or Off
-> G3AB does not insert/own a custom Raise for this profile
-> existing Gothic/compatible behavior remains authoritative

RaiseOverride=On
-> profile requests G3AB Raise behavior once the later Raise feature is implemented and validated
```

`Off` means the **G3AB override is off**. It does not promise active suppression of every native Raise animation.

This wording is preferred over `Raise=Native` because it states the ownership decision directly and avoids implying that `Off` disables Gothic's native phase globally.

### 6. A G3AB-inserted Raise inherits the same desired `BaseSpeed`

Gothic speed selection is phase-specific. Existing runtime evidence includes:

```text
Power Action2 Raise = 1.500
Power Action2 Hit   = 1.000
2H Normal Raise     = 1.000
2H Normal Hit       = 0.700
```

Therefore a custom Raise cannot assume the Hit reference base.

When `RaiseOverride=On`, the profile may provide:

```ini
ReferenceRaiseBaseSpeed=<positive finite float>
```

This is the factual Raise reference `B_raise`, not a second desired tuning speed.

The desired Raise base remains the same `BaseSpeed`:

```text
compatible Raise = B_raise * M_raise
configured Raise = (B_raise * M_raise) * (BaseSpeed / B_raise)
                 = BaseSpeed * M_raise
```

The initial schema intentionally does **not** expose `RaiseSpeed` or `RaiseBaseSpeed`. If later authoring experience proves a real need to tune Raise differently from Hit, an optional separate desired Raise value may be added without changing profile identity.

During the current Speed-only phase, Raise behavior remains paused under ADR-0006.

### 7. Recover is derived from Hit and has no configuration key

There is no:

```text
RecoverSpeed
ReferenceRecoverBaseSpeed
RecoverOverride
```

Recover follows the effective Hit playback as already decided by ADR-0004/ADR-0005 and observed in the earlier 2H speed work.

Therefore the shared profile controls only the desired Hit base and, later, whether G3AB inserts Raise. Recover requires no independent user-facing tuning or reference calibration.

### 8. Example profiles

Speed-only profile:

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.60
BaseSpeed=0.80
RaiseOverride=Off
```

Future profile with G3AB Raise:

```ini
[Profile.Hero_None_2H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=2H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.70
ReferenceRaiseBaseSpeed=1.00
BaseSpeed=0.80
RaiseOverride=On
```

Only `BaseSpeed` is an author tuning target. `ReferenceHitBaseSpeed` and `ReferenceRaiseBaseSpeed` are mechanism calibration facts.

### 9. Startup enumeration and runtime lookup

Startup:

```text
read G3AnimationBehaviors.ini once
-> enumerate sections
-> consider only names beginning with Profile.
-> parse/normalize mandatory identity
-> parse optional feature/calibration fields
-> build immutable normalized profile table
```

Runtime:

```text
obtain factual animation family
+ normalized left/right animation UseTypes
+ factual action mapped to Normal/Quick
-> construct normalized key
-> bounded in-memory lookup
-> apply only feature override with complete valid factual calibration
-> missing/invalid/unsupported = native-compatible fallback
```

The INI is never reread for every attack.

### 10. Ambiguity and malformed-profile policy

Fail safely rather than depending on INI order.

```text
missing/invalid mandatory identity
-> ignore section

unsupported ActionProfile
-> ignore section

duplicate normalized profile identity
-> identity ambiguous
-> no G3AB override for that identity

invalid BaseSpeed or required reference base
-> Speed inactive for that profile

RaiseOverride=On without later-proven Raise requirements
-> Raise remains inactive/fail-closed until the Raise feature owns that case
```

Unknown non-owned keys may be ignored for forward compatibility.

### 11. No weapon/family policy table in behavior C++

Profiles such as:

```text
Hero + None + 1H + Normal
Hero + Shield + 1H + Quick
Hero + Torch + 1H + Normal
Hero + 1H + 1H + Quick
Hero + None + 2H + Normal
Demon + None + 2H + Normal
```

are data, not C++ feature-policy branches.

C++ owns generic engine interpretation:

```text
factual action -> ActionProfile
factual phase
factual/current animation family source
raw UseTypes -> normalized animation tokens
generic compatible C/B composition
```

Configuration owns profile selection and factual reference calibration. Supporting another evidence-backed family/use-type profile should not require adding a new weapon/family branch to `AttackSpeed`.

## Consequences

- The previous `Raise=Native|On` spelling is superseded by `RaiseOverride=Off|On`.
- One desired `BaseSpeed` governs Hit and, when later enabled, the inserted Raise by default.
- Recover stays derived from Hit and remains absent from the INI.
- Phase-specific factual reference values remain separate where the composition mechanism requires them.
- The current hard-coded Hero reference-base table is transitional and must be removed by the later bounded generic-profile implementation.
- The exact runtime source for the `AnimationFamily` token is being resolved by the active diagnostics-only family-source probe before production refactoring.
- Raise behavior remains paused until Speed closes under ADR-0006.
