# Raise — Generic CombatMove Research and Design

**Status:** ACTIVE — RESEARCH/DESIGN ONLY  
**Date:** 2026-10-04  
**Branch:** `development`  
**Depends on:** Speed v2 CLOSED/PASS through EV-410; neutral Speed INI locked

## Purpose

Determine the smallest compatible production mechanism for optional added Raise phases without reopening Speed or collision.

The early G3AB prototype already proved the basic behavior on one narrow fixture:

```text
PS_Melee_Attack
-> prepend sAICombatMoveInstr for the same Normal action with phase "Raise"
-> wait until Raise completes
-> continue the untouched original melee state
```

Historical proof source: commit `18844a35379992def7c9b112b0e70fdaa5fe082e`, `AttackRaise.cpp`.

That proves the concept. It does **not** freeze the old player-only / None+2H state hook as production architecture.

## Locked user-facing configuration

Use the existing resolved animation-set profile identity:

```text
AnimationFamily
+ LeftAnimationToken
+ RightAnimationToken
```

Raise is per attack inside that profile.

User-facing syntax:

```ini
Normal_AddRaise=On
Quick_AddRaise=On
Whirl_AddRaise=On
```

General syntax if later expanded:

```text
<Attack>_AddRaise=On|Off
```

Semantics are additive only:

```text
missing / Off
= G3AB adds no Raise; native Gothic behavior remains untouched

On
= G3AB adds the matching Gothic Raise phase before that attack's Hit
```

`_AddRaise=Off` means G3AB adds nothing. G3AB does not provide a player-facing control for disabling or replacing Raise phases that Gothic already uses natively.

All shipped `*_AddRaise` settings default to `Off`.

Player-facing explanation should be simple:

> Normal and Quick attacks do not normally execute a Raise phase in Gothic 3. Matching Raise animation files exist for some native animation sets but not necessarily for every set you may use. Turn AddRaise on only when the correct Raise animation exists for that exact animation set, for example because an animation mod provides it or you created it yourself. Otherwise leave it Off.

Whirl follows the same opt-in safety rule.

## First production scope

Implement/accept only:

```text
Normal
Quick
Whirl
```

Do not initially add custom Raise behavior to:

```text
Power
Pierce
Hack
SimpleWhirl
Finishing
Sprint
```

Rationale:
- Power and several other routes already have native Raise behavior where appropriate;
- SimpleWhirl currently works without added Raise;
- Finishing is execution-oriented and remains outside this precision-combat feature;
- broader expansion is a later product decision after the generic mechanism is proven.

Do not expose `Power_AddRaise`, `Hack_AddRaise`, `SimpleWhirl_AddRaise`, or similar native-Raise controls merely for symmetry. If keeping a generic internal per-attack flag makes the implementation simpler, that is acceptable, but the supported player-facing INI surface remains only the attacks for which G3AB deliberately adds a missing/unused Raise.

## Reuse the existing profile architecture

Do not add weapon-specific policy branches.

The current grouped profile model already has per-attack Raise storage under the dormant internal name `RaiseOverride`. During Raise implementation, migrate the player-facing key/parser naming to `<Attack>_AddRaise` while preserving the generic per-attack/profile structure. Internal storage may remain generic if that is cleaner, but no work is required to create a user-facing switch for attacks that already have native Raise.

Adding a new weapon/animation set should remain a profile/INI operation when Gothic resolves a distinct animation family/token combination. It must not require a C++ branch such as "if 1H", "if 2H", "if Axe", "if Rapier", etc.

## Release README requirement

When Raise ships, the public README must explain how to name matching Raise animation files.

Use real Gothic naming examples and distinguish the factual attack variant:

```text
Normal:
..._Attack_Hit_...
..._Attack_Raise_...

Quick right:
..._QuickAttackR_Hit_...
..._QuickAttackR_Raise_...

Quick left:
..._QuickAttackL_Hit_...
..._QuickAttackL_Raise_...

Whirl:
..._WhirlAttack_Hit_...
..._WhirlAttack_Raise_...
```

Do not instruct authors to blindly replace only `Hit` with `Raise`. Native evidence shows Raise often preserves the source pose while Hit performs the meaningful pose transition, and the destination-pose / movement suffix can therefore differ. The README should show matched real examples and explain that the authored Raise file must follow Gothic's expected Raise request for that exact animation route.

Native inventory evidence currently includes:
- 64 `_Attack_Raise_` names;
- 12 `_QuickAttackR_Raise_` names;
- 16 `_QuickAttackL_Raise_` names;
- 6 `_WhirlAttack_Raise_` names.

These counts prove naming patterns, not universal asset availability for every profile.

## Preferred transport research question

Do **not** immediately restore the old direct `PS_Melee_*` production hooks.

Pinned New Balance source also hooks:
- `PS_Melee_Attack`
- `PS_Melee_QuickAttack`
- `PS_Melee_WhirlAttack`

SDK `mCFunctionHook` patches the function entry; safe multi-mod chaining at those exact state entries is not established.

G3AB already owns a generic `sAICombatMoveInstr` transport hook for collision lifecycle. Research whether the incoming Hit CombatMove request is a sufficient generic Raise insertion boundary.

For factual Normal, QuickR, QuickL and Whirl, establish at the existing CombatMove boundary:

```text
Action
PhaseName
AniSpeedScale
actor/profile identity
async completion/resume behavior
```

Desired shape:

```text
incoming matching Hit
-> existing resolved profile lookup
-> <Attack>_Raise == On?
   no  -> pass original Hit unchanged
   yes -> execute same factual action / Raise
          using Gothic's own animation resolution
          then resume/pass the original Hit exactly once
```

Any per-actor/SPU latch/state must be Raise-owned and generation-safe enough to prevent recursive reinsertion or duplicate Raise for the same pending Hit.

## Raise speed rule

Do not add a separate user-facing Raise speed control.

First prove whether the inserted Raise can naturally inherit/reuse the attack's effective timing through the existing CombatMove path, especially its `AniSpeedScale`.

For the first Normal/Quick/Whirl scope, the intended authoring behavior is:

```text
change attack BaseSpeed
-> same relative speed adjustment applies to the added Raise
```

Do not add `RaiseSpeed`, `RaiseBaseSpeed`, or duplicate New Balance/native speed policy unless runtime evidence proves natural inheritance/reuse is insufficient.

Native Power Raise remains outside the first custom-Raise scope. Its already-observed native/reference relationship is preserved; this task does not flatten native Power Raise to Hit speed.

## Protected boundaries

- Speed v2 is CLOSED; do not redesign its profile identity/composition.
- Collision is CLOSED/PASS; do not redesign collision.
- Do not touch Finishing behavior.
- Do not add weapon-specific Raise branches.
- Do not hard-code animation filenames.
- Do not require New Balance.
- Do not copy New Balance policy.
- Do not implement broader Raise families before Normal/Quick/Whirl acceptance.
- No build/deploy/runtime changes until a bounded implementation/probe task is frozen.

## Immediate next step

Perform bounded static/diagnostic research around the existing `sAICombatMoveInstr` boundary for Normal, QuickR/L and Whirl.

If the boundary exposes the required factual action, Hit phase, effective speed scale and safe asynchronous continuation, freeze a minimal diagnostic/implementation task around that mechanism.

If it does not, identify the smallest alternative transport boundary while preserving New Balance coexistence and the generic profile architecture.
