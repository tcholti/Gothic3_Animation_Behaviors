# ADR-0007 — Shared INI Profile Schema for Speed and Raise

**Status:** Accepted  
**Date:** 2026-09-27  
**Revised:** 2026-09-28  
**Related:** ADR-0004, ADR-0005, ADR-0006, `docs/DESIGN.md` §§2–3, `docs/ANIMATION_RULES.md`

**Current qualification — partial supersession:** The shared-profile foundation remains preserved rationale; startup loading, factual request identity and compatible base composition remain valid. [ADR-0008](ADR-0008-grouped-loadout-profiles-expanded-attack-scope.md) supersedes the per-ActionProfile section shape with grouped loadouts/expanded attack prefixes and supersedes the ReferenceRaiseBaseSpeed requirement. [ADR-0009](ADR-0009-sprint-inherits-power-speed-profile.md) owns Sprint/Power inheritance. [ADR-0010](ADR-0010-raw-use-type-speed-profile-identity.md) supersedes this ADR's normalized-animation-token semantics for profile UseType fields: current Speed/Raise profile identity preserves raw `gEUseType`.

The historical decision body below is preserved.

## Context

Speed is the next exclusive feature after EV-390 closed collision production integration. Raise remains paused until Speed is completely closed, but both features must share one configuration/profile model so the project does not redesign its INI when Raise work begins.

The original prototype INI hard-coded 2H Normal keys and therefore did not represent the intended generic product architecture.

Runtime work on 2026-09-28 established important constraints:

1. the user-facing animation family remains the Gothic animation-family token (`Hero`, `Sabretooth`, `Demon`, `Goblin`, etc.), not an incidental resource API string such as `G3_Hero_Skeleton` or `G3_Sabertooth_Body_01`;
2. the generic runtime source for this family token is `Animation.GetSkeletonName(...)`, proven with both Hero and Sabretooth and corroborated by `Entity.GetSkeletonName()`;
3. the selected downstream Speed composition mechanism needs factual reference base values `B` in order to transform a compatible result `B*M` into configured `C*M` without replacing contextual modifiers;
4. Speed/Raise profile selection preserves the successful pre-collision request-semantics design: factual requested `gEAction` and `gEPhase` come from Gothic's request path, not from whichever motion happens to be playing at that instant.

The pre-collision prototypes already proved this separation:

- Speed received the factual requested action from EAX and the factual requested phase as the `GetAnimationSpeedModifier` argument, and never needed `CurrentMovementAni()` to identify the requested attack.
- Raise hooked the original melee state and explicitly requested factual `gEAction_Attack` + `Raise` through `sAICombatMoveInstr`; Gothic then resolved the concrete P0/P1/etc. Raise animation itself.

The 2026-09-28 family-source probe is consistent with that architecture. At the CombatMove request boundary, `CurrentMovementAni()` may still name the outgoing/current motion while the new Hit is already being requested. That is expected and is not a reason to delay profile selection until the new motion becomes current.

The schema therefore stores factual reference values in generic profile data instead of hard-coding weapon/family base tables in behavior code, while runtime identity remains split cleanly between stable actor/equipment facts and Gothic's factual action/phase request.

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

`AnimationFamily` uses the stable Gothic animation-family token exposed by `Animation.GetSkeletonName(...)`. Proven examples are `Hero` and `Sabretooth`. Runtime configuration does not use raw resource identities such as `G3_Hero_Skeleton` or `G3_Sabertooth_Body_01`, and it does not infer the requested attack from `CurrentMovementAni()`.

`LeftAnimationUseType` and `RightAnimationUseType` use normalized animation tokens owned by `ANIMATION_RULES.md`, not blindly serialized raw `gEUseType` spelling.

`ActionProfile` currently accepts only:

```text
Normal
Quick
```

C++ remains responsible for mapping factual engine actions to these profile classes. Configuration does not redefine Gothic action identity.

The factual requested `gEPhase` is also engine-owned. It gates the feature behavior at runtime but is not part of the user-facing profile identity for the current Normal/Quick design. Hit Speed therefore uses factual `gEPhase_Hit`; later Raise behavior explicitly requests/handles factual Raise rather than deducing it from a current filename.

There is no P0/P1/P2/P3 field in the user-facing profile identity. Gothic remains responsible for resolving the exact concrete animation variant from its normal request facts.

### 3. Request semantics are authoritative; current motion is not profile identity

For Speed and later Raise, the runtime model is:

```text
stable actor/equipment facts:
  AnimationFamily from Animation.GetSkeletonName(...)
  LeftAnimationUseType
  RightAnimationUseType

request facts owned by Gothic:
  factual gEAction
  factual gEPhase
```

These facts select/gate behavior. The currently playing motion is observational context only and must not be used as the sole authority for the requested attack family or phase.

This deliberately preserves the successful pre-collision architecture:

```text
Speed:
Gothic requested action + requested phase
-> map factual action to Normal/Quick
-> build profile from family + UseTypes + ActionProfile
-> apply configured base composition only for the factual supported phase

Raise later:
matching profile + RaiseOverride=On
-> explicitly request the corresponding action + Raise phase
-> Gothic resolves the exact P0/P1/etc. Raise animation
-> continue the untouched original attack path
```

A stale/outgoing `CurrentMovementAni()` at the request boundary is therefore expected and does not invalidate the request facts.

### 4. `BaseSpeed` is the single desired authored playback base

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

### 5. `ReferenceHitBaseSpeed` is factual calibration data

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

### 6. Raise uses `RaiseOverride=On|Off`

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

### 7. A G3AB-inserted Raise inherits the same desired `BaseSpeed`

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

### 8. Recover is derived from Hit and has no configuration key

There is no:

```text
RecoverSpeed
ReferenceRecoverBaseSpeed
RecoverOverride
```

Recover follows the effective Hit playback as already decided by ADR-0004/ADR-0005 and observed in the earlier 2H speed work.

Therefore the shared profile controls only the desired Hit base and, later, whether G3AB inserts Raise. Recover requires no independent user-facing tuning or reference calibration.

### 9. Example profiles

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

### 10. Startup enumeration and runtime lookup

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
obtain AnimationFamily from Animation.GetSkeletonName(...)
+ normalized left/right animation UseTypes
+ factual requested gEAction mapped to Normal/Quick
+ factual requested gEPhase used as behavior gate
-> construct normalized profile key from family/use types/action profile
-> bounded in-memory lookup
-> apply only feature override with complete valid factual calibration
-> missing/invalid/unsupported = native-compatible fallback
```

The INI is never reread for every attack.

### 11. Ambiguity and malformed-profile policy

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

### 12. No weapon/family policy table in behavior C++

Profiles such as:

```text
Hero + None + 1H + Normal
Hero + Shield + 1H + Quick
Hero + Torch + 1H + Normal
Hero + 1H + 1H + Quick
Hero + None + 2H + Normal
Sabretooth + None + Fist + Normal
Demon + None + 2H + Normal
```

are data, not C++ feature-policy branches.

C++ owns generic engine interpretation:

```text
Animation.GetSkeletonName(...) -> AnimationFamily
raw UseTypes -> normalized animation tokens
factual requested action -> ActionProfile
factual requested phase -> behavior gate
generic compatible C/B composition
```

Configuration owns profile selection and factual reference calibration. Supporting another evidence-backed family/use-type profile should not require adding a new weapon/family branch to `AttackSpeed`.

## Consequences

- The previous `Raise=Native|On` spelling is superseded by `RaiseOverride=Off|On`.
- One desired `BaseSpeed` governs Hit and, when later enabled, the inserted Raise by default.
- Recover stays derived from Hit and remains absent from the INI.
- Phase-specific factual reference values remain separate where the composition mechanism requires them.
- The transitional Hero/weapon hard-coded reference-base table has been removed from `AttackSpeed`; reference calibration now comes from the matched profile.
- Speed/Raise attack identity follows Gothic's factual request semantics; `CurrentMovementAni()` is not part of user-facing profile identity and is not used to infer the requested attack/phase.
- `Animation.GetSkeletonName(...)` is the accepted generic runtime `AnimationFamily` source after consistent Hero and Sabretooth controls.
- Missing/invalid family or reference calibration fails closed to native/compatible behavior.
- Raise behavior remains paused until Speed closes under ADR-0006.
