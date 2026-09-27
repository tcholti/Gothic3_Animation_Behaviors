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
EV-391 Speed v2 caller-side composition static evidence = RECORDED
CURRENT = Speed v2 mechanism research/design ONLY
RAISE = PAUSED until Speed fully closes
```

Config task archived at `docs/archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`. `docs/work/active/` is clean.

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

`C` = configured authored base. `M` = legitimate Gothic/New Balance modifiers and must remain effective.

## EV-391 mechanism finding

Static tracing found a viable composition boundary **after** the live `GetAnimationSpeedModifier` policy result but **before** downstream playback/state consumption.

Proven Hit consumers:

```text
Script_Game+0x383F0  explicit Action1 / gEAction_Attack / Normal
Script_Game+0x48677  PSRoutine::PropertyAction route after explicit Action4/5 assignment / Quick R/L
```

Nearby dynamic Hit consumers (`+0x38A8B`, `+0x38E9D`, `+0x38F22`, `+0x3937D`, `+0x39402`) preserve exact action context at the same boundary.

Preferred candidate shape:

```text
exact target caller
-> invoke LIVE Script_Game+0x42A0  # New Balance remains owner and computes B*M
-> if exact configured supported profile: multiply by C/B
-> result = C*M
-> continue native downstream path
```

A targeted caller-side thunk/call redirection is therefore preferred over:

```text
competing hook ownership of +0x42A0
final-result replacement
global StartPlayAni/StartPlayAniEx interception
copied New Balance multiplier policy
```

Existing runtime/ADR evidence plus pinned New Balance source already supplies the first intended base groups (`0.6`, `0.7`, `1.0`), so **do not request more native-speed logging now**.

This is not yet a frozen production call-site list. Generic `gEAction_QuickAttack` / Action3 remains the exact static gap; ADR-0007 Quick includes Action3/4/5.

## Primary compatibility stack

Keep live during Speed development/testing:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

New Balance compatibility is PRIMARY; native-only is later sanity/fallback.

Pinned Jackydima source: `316d32406a133f8884e7e302752c35f66b4f54fc`.

## Next route

```text
1. trace generic gEAction_QuickAttack / Action3 into the dynamic combat consumer family
2. close the exact Normal+Quick Hit consumer-callsite set
3. verify selected sites retain entity + exact action/profile identity for BehaviorProfiles lookup
4. if static evidence remains insufficient, freeze only the smallest diagnostics-only causal probe
5. after closure, freeze bounded Speed v2 implementation
6. validate intended New Balance stack first
7. close Speed completely before any Raise work
```

Authorities: ADR-0004, ADR-0007, `DESIGN.md` §§2–3, `SOURCE_HOOK_GUIDE.md`, EV-391, `references/README.md`.

Hard exclusions: final-result replacement; same-hook load-order dependency; copied NB multiplier policy; global speed override; stamina bypass; premature Raise work; collision redesign.
