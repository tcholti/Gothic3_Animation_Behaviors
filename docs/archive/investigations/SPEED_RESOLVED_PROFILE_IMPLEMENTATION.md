# Speed Resolved Profile Implementation

**Status:** CLOSED — IMPLEMENTED / NORMAL CHAT SOURCE REVIEW PASS
**Task class:** Bounded production source + shipping INI implementation
**Branch:** `development`

## Required base

`88ba784c45797b44d6fefc09fbd2e03d03aa9c36`

## Purpose

Implement the now-closed ADR-0011 profile identity and populate the first active shipping Speed INI.

The research question is closed by EV-406. This task is implementation only.

Final Speed/Raise profile identity is:

```text
AnimationFamily
+ LeftAnimationToken
+ RightAnimationToken
```

where the left/right tokens come from Gothic's exact request-time animation returned by:

```text
Entity.GetAni(factualAction, factualPhase)
```

Factual `gEAction` remains the independent attack-family authority.

## Read first

1. root `README.md` -> Start Here
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/BETWEEN_CHATS.md`
4. this task
5. `docs/decisions/ADR-0011-resolved-animation-set-speed-profile-identity.md`
6. `docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`
7. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
8. `docs/FEATURE_DEVELOPMENT_METHOD.md`
9. only the four allowed implementation files below

Do not load broad evidence ledgers unless a concrete contradiction requires it.

## Allowed files

Modify only:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Do not modify hooks, EngineBridge, collision source, diagnostics/probe source, CMake/build files, or other documentation.

## Frozen source responsibility

### 1. Rename grouped profile identity fields

Replace the production/profile identity meaning:

```text
leftAnimationUseType
rightAnimationUseType
```

with:

```text
leftAnimationToken
rightAnimationToken
```

INI keys become exactly:

```ini
AnimationFamily=...
LeftAnimationToken=...
RightAnimationToken=...
```

Do not retain `LeftAnimationUseType` / `RightAnimationUseType` as compatibility aliases. The prior schema was not a finalized active shipping schema.

Case-insensitive/outer-whitespace normalization remains as already established.

### 2. Remove raw inventory UseType from Speed profile selection

Production Speed profile lookup must no longer derive left/right identity from equipped items or raw `gEUseType`.

Remove the now-obsolete profile-identity helpers if they become unused:

```text
TryGetAnimationUseTypeToken(...)
GetHandUseType(...)
```

Do not change collision's independent UseType logic.

### 3. Build runtime key from the exact resolved request

Update the profile-key construction interface so it receives the factual:

```text
entity
action
phase
```

At lookup time:

1. obtain `AnimationFamily` using the existing `entity.Animation.GetSkeletonName(...)`;
2. call `entity.GetAni(action, phase)` exactly once for profile identity;
3. parse the returned canonical Gothic request name.

Canonical minimum structure:

```text
Family_State_LeftAnimationToken_RightAnimationToken_...
```

The parser needs only the first four underscore-delimited fields.

Required parse result:

```text
field 0 = resolved family text, observational/structure field
field 1 = state
field 2 = LeftAnimationToken
field 3 = RightAnimationToken
```

Profile `AnimationFamily` still comes from `Animation.GetSkeletonName(...)`, not from field 0.

Accept the key only when:

- skeleton-family lookup succeeds and is non-empty;
- `GetAni(action, phase)` returns non-empty text;
- at least four underscore-delimited fields exist;
- fields 0, 1, 2 and 3 are all non-empty;
- extracted left/right tokens are non-empty after normal identity normalization.

Otherwise fail closed: no profile match / no G3AB Speed intervention.

Do not:
- use `CurrentMovementAni()`;
- fall back to raw UseType;
- fall back to static `ANIMATION_RULES.md` normalization;
- special-case Axe, Rapier, Zombie, Fist, or any mod name;
- interpret serialized action-name text as the factual action.

### 4. Preserve factual attack mapping

`AttackSpeed::ComposeCompatibleSpeed` already receives factual `action` and `phase`.

Pass those same values into runtime profile-key construction.

Keep attack mapping unchanged:

```text
Action1  -> Normal
Action4/5 -> Quick
Action2  -> Power
Action11 -> Pierce
Action14 -> Hack
Action6  -> SimpleWhirl
Action10 -> Whirl
```

Do not add Finishing/Action15 production support.

Do not add Sprint/Action9 mapping. On the proven shared caller path Sprint still arrives as passed Action2 and therefore selects Power under ADR-0009.

### 5. Preserve C/B composition exactly

Do not change:

```text
configured = compatibleSpeed * (BaseSpeed / ReferenceHitBaseSpeed)
```

Keep all finite/positive/fail-closed guards.

The live compatible speed owner remains outside this module and remains called exactly once by the existing bridge.

## Full active shipping INI

Replace the comment-only provisional example with a concise documented active configuration.

Use:

```text
BaseSpeed=1.00
```

for every active attack block below.

Do not add active `RaiseOverride=On`. Raise remains paused. It is acceptable to keep concise schema comments saying the field is reserved for later Raise work.

### Active core profiles

#### Hero + None + 1H

```text
Normal B=.60
Quick B=1.00
Power B=1.00
Pierce B=1.00
```

#### Hero + Shield + 1H

Same four references.

#### Hero + Torch + 1H

Same four references.

#### Hero + 1H + 1H

```text
Normal B=.60
Quick B=1.00
Power B=.90
Pierce B=1.00
SimpleWhirl B=1.30
```

#### Hero + None + 2H

```text
Normal B=.70
Quick B=1.00
Power B=1.00
Hack B=1.00
Whirl B=1.00
```

Native raw Axe/Pickaxe-style routes share this profile only when Gothic actually resolves `..._None_2H_...`.

#### Hero + None + Staff

```text
Normal B=.70
Quick B=1.00
Power B=1.00
Hack B=1.00
Whirl B=1.00
```

Native Halberd/tool-style routes share this profile only when Gothic actually resolves `..._None_Staff_...`.

#### Hero + None + Fist

```text
Normal B=1.00
Power B=1.00
```

Do not add Quick. Native human Fist has no Quick attack animation family.

#### Sabertooth + None + Fist

```text
Normal B=1.00
Quick B=1.00
Power B=1.00
```

#### Troll + Fist + Fist

```text
Normal B=1.00
Quick B=1.00
Power B=1.00
```

The resolved animation tokens are `Fist/Fist`; raw PhysicalFist is not part of Speed profile identity.

### Active tested separation-mod compatibility profiles

These sections are ordinary resolved-animation profiles, not mod-name special cases.

#### Hero + None + Axe

```text
Normal B=.70
Quick B=1.00
Power B=1.00
Hack B=1.00
Whirl B=1.00
```

#### Hero + None + Rapier

```text
Normal B=.60
Quick B=1.00
Power B=1.00
Pierce B=1.00
```

### Commented Zombie examples

Do not exhaustively activate Zombie profiles in the first shipping INI.

Add concise commented examples demonstrating the identity rule for:

```text
Zombie + Shield + 1H
Zombie + None + 2H
Zombie + None + Staff
Zombie + None + Axe
```

Use only EV-406-supported references in examples.

The comments must explain that the sections match whatever Gothic resolves at request time. They are not activated/detected by mod name.

## INI exclusions

Do not add:

- Sprint keys;
- Finishing keys;
- human Fist Quick;
- uncalibrated work-tool-specific profiles;
- active Raise behavior;
- New Balance-derived values as `ReferenceHitBaseSpeed`.

## Static acceptance

Before commit/push, audit:

```text
only four allowed files changed
old profile UseType field names absent from production parser/header/active INI
raw equipped UseType no longer participates in Speed profile lookup
GetAni(action, phase) used once per runtime-key construction
canonical first-four-field parser is bounded/fail-closed
factual action mapping unchanged
C/B composition unchanged
no hook changes
no collision changes
no Raise behavior
full active INI contains exactly evidence-backed blocks
Sprint absent
Finishing absent
human Fist Quick absent
Axe/Rapier profiles are data only
Zombie examples are commented only
git diff --check PASS
knowledge-state validation PASS
```

## Build policy

**BUILD PROHIBITED.**

Do not configure, invoke, troubleshoot, or probe any build environment.

Normal Chat + User own independent review, local Release build, deployment, and runtime acceptance.

## Stop condition

Commit/push the bounded four-file implementation to `development`, report the commit SHA and exact changed files, and STOP.

Do not begin runtime testing or Raise work.


## Closure

Work published the bounded four-file implementation as:

```text
ba3e76549eff5c7fdfc2d165ec976e640ef9c24c
```

Exact changed files:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Work reported static audit, `git diff --check`, and local knowledge-state validation PASS. Build was not attempted, as prohibited.

Normal Chat independently reviewed the published source and accepted the implementation boundary:

- request-time `GetAni(action, phase)` identity only;
- skeleton family remains family authority;
- raw item UseType/current movement fallbacks removed from Speed profile lookup;
- factual action mapping unchanged;
- C/B composition unchanged;
- 11 active profiles / 44 calibrated attack blocks;
- no active Raise, Sprint, Finishing, or native human-Fist Quick configuration.

Runtime acceptance is **not** part of this closed source task. It remains owned by:

`docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`

Next gate: local Release build -> POP-03 deployment identity -> focused final Speed runtime acceptance.
