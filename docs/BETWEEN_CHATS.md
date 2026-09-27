# Between Chats

**Purpose:** exact continuation handoff; replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`  
Stable branch: `main` — keep frozen until Speed + Raise + assembled regression close.

## Closed / accepted

```text
EV-390 production Script_G3AnimationBehaviors collision integration = CLOSED/PASS
shared Speed/Raise INI schema = ADR-0007 ACCEPTED
BehaviorProfiles config foundation = source-review PASS
implementation SHA = 81d4964201579c9f7a989404426c3d9dc9ab4834
collision research = CLOSED unless contradictory evidence appears
```

Completed config task is archived at `docs/archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`. `docs/work/active/` should be clean.

## Current exclusive feature: Speed v2

Raise is PAUSED until Speed is fully closed. Do not alternate between them.

Profile identity remains:

```text
AnimationFamily + LeftAnimationUseType + RightAnimationUseType + ActionProfile
ActionProfile = Normal | Quick only
```

INI is parsed once at startup. `BaseSpeed` absent = native/mod fallback. `BaseSpeed=1.00` = explicit authored base 1.00. No P0/P1/P2 split and no weapon-specific C++ policy branches.

### Authoring model

For explicitly controlled Normal/Quick profiles, `1.0` is the intended neutral authored playback scale. Known native/current-New-Balance values such as Normal 1H `0.6`, Normal 2H/Axe/Staff/Halberd `0.7`, Quick `1.0` are technical base-selection facts, not desired G3AB defaults.

Goal: author Normal/Quick animations around a common convenient frame/timing standard in Blender, then tune gameplay in INI, e.g. 2H Normal `1.0`, 2H Quick `1.05–1.10`, 1H Normal `1.05`, 1H Quick `1.10–1.15` (examples only).

Interpretation: `1.0` is the neutral playback reference and `0.6/0.7` are attack-specific reductions. Do not overclaim an exhaustively proven engine-wide rule that most animations use 1.0.

## Required composition

```text
unconfigured effective = B * M
configured effective   = C * M
```

`C` = G3AB configured authored base. `M` = legitimate Gothic/New Balance contextual modifiers (stamina/exhaustion, disease, arena, species/action, perk/skill, etc.). These must remain effective.

Old `AttackSpeed.cpp` is NOT final architecture: it calls the previous speed function then discards its result for configured attacks.

A downstream transform `(B*M) * (C/B) = C*M` is only a research candidate. It is acceptable only if a stable downstream consumer/intervention surface and trustworthy exact `B` source are proven. Native base logging is not needed unless the selected mechanism actually requires missing `B` values.

## Primary compatibility environment

Keep live during Speed development/testing:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

New Balance compatibility is PRIMARY. Native-only testing comes later as sanity/fallback.

Pinned Jackydima source: `316d32406a133f8884e7e302752c35f66b4f54fc`; verified against upstream `master` on 2026-09-27.

```text
Script_NewBalance/FunctionHook.cpp
  owns Script_Game +0x42A0 GetAnimationSpeedModifier
  combines base choices and contextual modifier logic

Script_AttackCollision/Script_AttackCollision.cpp
  owns melee callback/collision timing behavior
  does NOT own GetAnimationSpeedModifier
```

Native disassembly shows `Script_Game+0x42A0` is itself a large policy function with many branches/returns, not a clean base getter followed by a separate multiplier stage.

## Exact next route

```text
1. continue static tracing of GetAnimationSpeedModifier result consumers / animation playback path
2. seek the narrowest stable composition point outside competing +0x42A0 entry ownership
3. determine whether exact B values are technically required
4. only then request additional native logger runs if needed
5. if static evidence cannot resolve causality, freeze the smallest diagnostics-only probe
6. after mechanism proof, freeze bounded Speed implementation
7. close Speed completely before any Raise work
```

Authorities: ADR-0004, ADR-0007, `DESIGN.md` §§2–3, `SOURCE_HOOK_GUIDE.md`, `references/README.md`.

Hard exclusions: final-result replacement, same-hook load-order dependency, copying New Balance multiplier policy, global speed override, stamina bypass, premature Raise work, collision redesign.
