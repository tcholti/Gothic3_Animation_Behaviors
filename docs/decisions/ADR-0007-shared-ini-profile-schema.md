# ADR-0007 — Shared INI Profile Schema for Speed and Raise

**Status:** Accepted  
**Date:** 2026-09-27  
**Related:** ADR-0004, ADR-0005, ADR-0006, `docs/DESIGN.md` §§2–3, `docs/ANIMATION_RULES.md`

## Context

Speed is the next exclusive feature after EV-390 closed collision production integration. Raise remains paused until Speed is completely closed, but both features must share one configuration/profile model so the project does not redesign its INI when Raise work begins.

The original prototype INI hard-coded 2H Normal keys and therefore did not represent the intended generic product architecture.

The production project builds against Gothic 3 SDK revision:

`90bfd344de4510dda7ac9da7461cc7f1eac911f7`

At that exact revision `eCConfigFile` supports both direct known-key access and enumeration, including:

```text
ReadFile
Contains
GetBool / GetFloat / GetInt / GetString / GetValue
GetSections
GetSectionBlock
GetSectionArray
```

`eCConfigFile_SectionObject` also exposes section names, key counts and indexed key objects. Therefore the schema does not need a numbered `[Profiles] Count=N` registry merely to make profiles discoverable.

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
BaseSpeed=0.80
Raise=Native
```

The text after `Profile.` is a unique author-facing label only. It is **not** parsed as behavior identity and does not participate in runtime matching.

Therefore this is equally valid:

```ini
[Profile.MyModSwordNormal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
BaseSpeed=0.80
Raise=Native
```

This keeps human naming independent from engine policy and avoids delimiter/filename-style parsing inside the configuration layer.

### 2. Exact profile identity lives in explicit fields

The mandatory identity fields are:

```text
AnimationFamily
LeftAnimationUseType
RightAnimationUseType
ActionProfile
```

Together they form the already accepted profile key:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

`AnimationFamily` uses the Gothic animation/resource-family token (`Hero`, `Demon`, etc.).

`LeftAnimationUseType` and `RightAnimationUseType` use the **normalized animation tokens** owned by `ANIMATION_RULES.md`, not blindly serialized raw `gEUseType` spelling. Examples include `None`, `1H`, `2H`, `Shield`, `Torch`, `Staff`, and `Fist`.

`ActionProfile` accepts only:

```text
Normal
Quick
```

Quick's multiple factual Gothic action variants may normalize to the single user-facing `Quick` profile as decided by ADR-0005; factual action distinctions remain available internally where engine behavior requires them.

There is no P0/P1/P2/P3 field in the user-facing profile identity.

### 3. `BaseSpeed` is optional and absence is meaningful

Speed uses:

```ini
BaseSpeed=<positive float>
```

Examples:

```ini
BaseSpeed=0.80
BaseSpeed=1.00
BaseSpeed=1.15
```

The key is deliberately named `BaseSpeed`, not merely `Speed`, because ADR-0004 requires G3AB to author the base term while applicable Gothic/New Balance contextual modifiers remain effective.

Semantics:

```text
BaseSpeed key absent
-> no G3AB Speed override for this profile
-> native / compatible-mod behavior remains authoritative

BaseSpeed=1.00
-> explicit configured base value of 1.00
-> NOT the same as absence/native fallback
```

`eCConfigFile::Contains(section,key)` makes this distinction directly representable; no sentinel float is required.

A non-numeric, non-finite, zero or negative `BaseSpeed` is invalid for Speed and must not create an active Speed override. An invalid Speed field does not by itself invalidate another independently valid feature field in the same profile.

No arbitrary upper bound is frozen without runtime evidence requiring one.

### 4. `Raise` is part of the shared schema but behavior remains paused

The shared profile format reserves:

```ini
Raise=Native
```

and future configured activation:

```ini
Raise=On
```

Current schema semantics are:

```text
Raise key absent
or Raise=Native
-> no G3AB Raise override; preserve native behavior

Raise=On
-> profile requests G3AB Raise behavior once the later Raise feature is implemented/validated
```

No `Raise=Off` suppression behavior is promised by this ADR. If later Raise research establishes a useful and safe explicit suppression mode, the value set may be extended without changing the profile structure.

During the Speed-only phase the configuration foundation may parse/store the Raise field for schema completeness, but no Raise hook, Raise intervention or Raise behavior is activated. Raise research/implementation remains blocked until Speed is closed under ADR-0006.

### 5. Profiles may contain either or both feature controls

Valid examples:

Speed only:

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
BaseSpeed=0.80
```

Future Raise only:

```ini
[Profile.Hero_None_1H_Quick]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Quick
Raise=On
```

Both in one profile:

```ini
[Profile.Hero_Torch_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=Torch
RightAnimationUseType=1H
ActionProfile=Normal
BaseSpeed=0.85
Raise=On
```

This is one shared profile table, not independent Speed and Raise weapon tables.

### 6. Startup enumeration and runtime lookup

Startup:

```text
read G3AnimationBehaviors.ini once
-> enumerate sections through eCConfigFile
-> consider only section names beginning with Profile.
-> parse/normalize mandatory identity fields
-> parse optional feature fields
-> build immutable/normalized in-memory profile table
```

Runtime:

```text
obtain factual animation family + normalized left/right animation UseTypes + Normal/Quick profile
-> construct normalized profile key
-> bounded in-memory lookup
-> apply only the feature override actually present
-> missing profile/feature = native fallback
```

The INI is never reread/reparsed for each attack.

### 7. Ambiguity and malformed-profile policy

Fail safely rather than depending on INI order.

```text
section missing/invalid mandatory identity field
-> ignore that section

unsupported ActionProfile
-> ignore that section

unknown/un-normalizable animation UseType token
-> ignore that section

multiple sections normalize to the same exact profile identity
-> identity is ambiguous
-> no G3AB feature override is active for that identity
-> do NOT use first-wins or last-wins behavior
```

A malformed optional feature field disables only that feature override where practical; independently valid fields may remain usable.

Unknown non-owned keys may be ignored for forward compatibility. User-facing startup warning/reporting for malformed configuration is an implementation concern and must remain lightweight; it is not permission to add research diagnostics to the release DLL.

### 8. No weapon-specific policy is encoded in C++

Profiles such as:

```text
Hero + None + 1H + Normal
Hero + Shield + 1H + Quick
Hero + Torch + 1H + Normal
Hero + 1H + 1H + Quick
Hero + None + 2H + Normal
Hero + None + Staff + Quick
```

are data, not C++ feature branches.

Raw runtime UseTypes that normalize to an existing animation token follow `ANIMATION_RULES.md`. For example, animation-token normalization may intentionally collapse multiple raw UseTypes onto the same animation category. Supporting a modded item that uses an existing factual animation category therefore does not require adding a weapon-named behavior branch.

This ADR does not promise support for an invented runtime UseType/category that Gothic itself does not expose or that the project cannot normalize factually.

## Consequences

- The old `[AttackRaise] EnableTwoHandedNormal` and `[AttackSpeed] TwoHandedNormal` layout is historical prototype syntax and will not define the new production configuration.
- Profile discovery is generic and does not require a compile-time list of weapon combinations.
- `BaseSpeed=1.0` remains distinguishable from native fallback.
- Raise can be added later without changing the profile identity or moving settings into a second table.
- Speed implementation can proceed independently while Raise stays behaviorally dormant.
- The exact Speed v2 hook/composition mechanism remains unresolved under ADR-0004; this ADR freezes configuration semantics, not engine intervention.
