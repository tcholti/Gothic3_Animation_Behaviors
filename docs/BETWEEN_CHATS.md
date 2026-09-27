# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 production collision integration = CLOSED/PASS
ADR-0007 shared Speed/Raise INI schema = ACCEPTED
BehaviorProfiles foundation = source-review PASS
implementation = 81d4964201579c9f7a989404426c3d9dc9ab4834
CURRENT = Speed v2 mechanism research/design ONLY
RAISE = PAUSED until Speed fully closes
```

Config task archived at `docs/archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`. `docs/work/active/` should be clean.

## Speed contract

Profile identity:

```text
AnimationFamily + LeftAnimationUseType + RightAnimationUseType + ActionProfile
ActionProfile = Normal | Quick only
```

INI loads once at startup. `BaseSpeed` absent = native/mod fallback. `BaseSpeed=1.00` = explicit authored base 1.00. No P0/P1/P2 split; no weapon-specific C++ policy branches.

For configured Normal/Quick profiles, `1.0` is the intended neutral authored playback scale. Known native/current-NB values such as Normal 1H `0.6`, Normal 2H/Axe/Staff/Halberd `0.7`, Quick `1.0` are technical base-selection facts, not desired G3AB defaults. Goal: author attacks around a common convenient Blender timing/frame convention, then tune gameplay through INI. Do not claim as proven that most/all Gothic animations use 1.0 engine-wide.

Required composition:

```text
unconfigured = B * M
configured   = C * M
```

`C` = configured authored base. `M` = legitimate Gothic/New Balance modifiers (stamina/exhaustion, disease, arena, species/action, perks/skills, etc.) and must remain effective.

Old `AttackSpeed.cpp` is rejected because it discards the previous hook's final result. A downstream `(B*M) * (C/B) = C*M` transform is only a candidate; use it only if a stable consumer surface and trustworthy exact `B` source are proven. Do not request extra native-speed logging unless the selected mechanism actually requires missing `B` values.

## Primary compatibility stack

Keep live during Speed development/testing:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

New Balance compatibility is PRIMARY; native-only is later sanity/fallback.

Pinned Jackydima source: `316d32406a133f8884e7e302752c35f66b4f54fc` (matched upstream `master` on 2026-09-27).

```text
Script_NewBalance/FunctionHook.cpp
  owns Script_Game +0x42A0 GetAnimationSpeedModifier
  combines base selection with contextual modifier logic

Script_AttackCollision/Script_AttackCollision.cpp
  owns melee callback/collision timing behavior
  does NOT own GetAnimationSpeedModifier
```

Native disassembly shows `Script_Game+0x42A0` is a large policy function with many branches/returns, not a clean base getter followed by a separate multiplier stage.

## Next route

```text
1. continue static tracing of GetAnimationSpeedModifier consumers/downstream playback path
2. seek the narrowest stable composition point outside competing +0x42A0 entry ownership
3. determine whether exact B values are technically required
4. only then request missing logger evidence if needed
5. if static evidence cannot resolve causality, freeze the smallest diagnostics-only probe
6. after mechanism proof, freeze bounded Speed implementation
7. close Speed completely before any Raise work
```

Authorities: ADR-0004, ADR-0007, `DESIGN.md` §§2–3, `SOURCE_HOOK_GUIDE.md`, `references/README.md`.

Hard exclusions: final-result replacement; same-hook load-order dependency; copied NB multiplier policy; global speed override; stamina bypass; premature Raise work; collision redesign.
