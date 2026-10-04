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

## Historical engine-resolution proof

The pre-profile Raise prototype already proved that G3AB does not need to construct animation filenames.

Historical source at commit `18844a35379992def7c9b112b0e70fdaa5fe082e` called `sAICombatMoveInstr` with:
- the actor/target;
- factual `gEAction_Attack`;
- phase name `"Raise"`;
- animation speed scale `1.0f`.

It supplied no animation filename.

The historical design recorded the accepted runtime result:

```text
custom Raise -> original state -> original Hit -> native continuation
the engine resolves the correct P0/P1 Raise animation automatically
```

Therefore the production/public authoring model is:

```text
G3AB requests factual action + Raise phase
-> Gothic resolves the concrete Raise request from its normal animation state
-> Gothic builds/looks up the corresponding serialized animation resource name
-> if that correctly named asset exists, Gothic uses it
```

Do not replace this with manual filename construction in G3AB.

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

Do not instruct authors to blindly replace only `Hit` with `Raise`. Gothic itself determines the requested Raise identity from its normal action/phase/pose/use-type/direction rules. Native evidence shows Raise often preserves the source pose while Hit performs the meaningful pose transition, and destination-pose / movement suffixes can therefore differ. The README should explain the engine naming fields/rules and show matched real examples so authors create the asset Gothic will actually request.

Native inventory evidence currently includes:
- 64 `_Attack_Raise_` names;
- 12 `_QuickAttackR_Raise_` names;
- 16 `_QuickAttackL_Raise_` names;
- 6 `_WhirlAttack_Raise_` names.

These counts prove naming patterns, not universal asset availability for every profile.

## Preferred transport direction

Historical runtime testing by the User established that the old 2H Normal Raise prepend **coexisted successfully with New Balance**. Speed compatibility failed in that older version, but the Raise prepend itself did not.

Therefore the preferred first implementation path is now the **high-level state prepend mechanism**, not the lower-level generic CombatMove interception.

Pinned New Balance source also hooks:
- `PS_Melee_Attack`
- `PS_Melee_QuickAttack`
- `PS_Melee_WhirlAttack`

That shared-hook fact remains relevant, but the historical runtime fixture is stronger than a purely static concern for `PS_Melee_Attack`: the old G3AB Normal Raise state hook and New Balance were observed working together in game.

Production direction:

```text
Normal -> PS_Melee_Attack prepend candidate
Quick  -> PS_Melee_QuickAttack prepend candidate
Whirl  -> PS_Melee_WhirlAttack prepend candidate
```

Each candidate should use the same generic profile lookup and `*_AddRaise` policy, request the factual action + `Raise` phase through `sAICombatMoveInstr`, wait via the existing `PREPEND_BREAK_BLOCK` semantics, then continue the untouched original state.

The existing lower-level `sAICombatMoveInstr` hook remains a fallback only if Quick/Whirl state-hook coexistence or profile/action transport fails in runtime.

Before production implementation, establish for the three state-prepend candidates:

```text
Action
PhaseName
AniSpeedScale
actor/profile identity
async completion/resume behavior
```

Desired shape:

```text
enter original melee state
-> resolve factual attack/profile
-> <Attack>_AddRaise == On?
   no  -> call untouched original state
   yes -> PREPEND_BREAK_BLOCK:
          request same factual attack / Raise through sAICombatMoveInstr
          wait until Raise completes
          then call untouched original state
```

Prefer this because the asynchronous sequencing is already proven and needs no new recursion latch. Introduce lower-level per-actor/SPU state only if the state-prepend route proves insufficient.

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

Perform bounded static research for `PS_Melee_Attack`, `PS_Melee_QuickAttack`, and `PS_Melee_WhirlAttack`, then freeze a minimal implementation/probe that restores the proven prepend pattern generically through profiles.

Runtime acceptance must include New Balance with the intended stack. Normal has historical coexistence evidence; Quick and Whirl still require direct coexistence proof.

If Quick/Whirl state hooks conflict or cannot preserve the required factual action/profile semantics, fall back to the existing lower-level `sAICombatMoveInstr` boundary rather than redesigning the feature.
