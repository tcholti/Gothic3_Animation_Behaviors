# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`  
Stable branch: `main`

## Current state

```text
EV-390 production Script_G3AnimationBehaviors.dll collision integration = CLOSED/PASS
ADR-0007 shared Speed/Raise INI profile schema = ACCEPTED
CURRENT = implement shared startup profile/config foundation only
NEXT = Speed v2 research/design/implementation/testing ONLY
RAISE = PAUSED until Speed closes
```

`main` stays frozen. `development` is the only active general branch for this cycle.

## Frozen profile schema

All behavior profiles are free-form sections beginning with `Profile.`. The section suffix is a unique author label only; runtime identity comes from explicit fields.

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
BaseSpeed=0.80
Raise=Native
```

Exact identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

Rules:

```text
ActionProfile = Normal | Quick only
UseType fields = normalized animation tokens from ANIMATION_RULES.md
no P0/P1/P2/P3 profile split
BaseSpeed absent = native Speed fallback
BaseSpeed=1.00 = explicit configured base value
Raise absent/Native = native Raise fallback
Raise=On = reserved future Raise activation
no Raise=Off behavior promised yet
duplicate normalized identity = ambiguous -> no G3AB override for that identity
invalid mandatory identity = ignore profile
INI parsed once at startup -> normalized in-memory table
runtime = bounded in-memory lookup only
```

The exact pinned Gothic SDK (`90bfd344de4510dda7ac9da7461cc7f1eac911f7`) exposes `eCConfigFile::GetSections`, `GetSectionBlock`, `GetSectionArray`, `Contains`, `GetString`, scalar getters, and section/key enumeration, so numbered profile registries are unnecessary.

Architecture/rationale: ADR-0004 + ADR-0005 + ADR-0007.

## Speed — next exclusive behavior feature

```text
unconfigured = B * M
configured   = C * M
```

`C` is the configured base term; applicable Gothic/New Balance contextual modifiers `M` must remain effective. Exact intervention mechanism remains research under ADR-0004. Do not use final-result replacement, copied New Balance multiplier tables, arbitrary same-hook load-order dependency, or weapon-named C++ policy branches.

## Raise — paused

The shared config may parse/store `Raise`, but no Raise hook/intervention/behavior may be activated while Speed is open. Later `Raise=On` uses Gothic CombatMove semantics and Gothic's normal animation resolution under ADR-0005.

## Exact next route

```text
1. bounded source-only implementation of shared profile/config foundation:
   - enumerate Profile.* through eCConfigFile
   - normalize/validate identity
   - store optional BaseSpeed + future Raise mode
   - startup load once
   - immutable/bounded runtime lookup API
   - NO Speed hook or Raise behavior yet
2. independent source review
3. then begin focused Speed v2 mechanism research only
```

Collision is closed through EV-390; do not reopen historical collision campaigns absent contradictory evidence.
