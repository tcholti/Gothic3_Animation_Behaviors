# Raise — Generic AddRaise Research and Implementation Freeze

**Status:** CLOSED — QUICK STATIC PRECHECK RESOLVED / PRODUCTION IMPLEMENTATION FROZEN  
**Date:** 2026-10-04  
**Branch:** `development`  
**Depends on:** Speed v2 CLOSED/PASS through EV-410; neutral Speed INI locked

## Closure result

Static precheck result:

```text
generic Quick / Action3
-> GetPrimaryPoseExt(Action3, Hit)
-> Gothic chooses/writes PropertyAction = Action4 or Action5
-> downstream PropertyAction returns factual 4/5
-> proven Script_Game+0x48677 Quick Hit consumer receives factual 4/5
```

Therefore `PS_Melee_QuickAttack` entry is not an authorized factual R/L selection point for AddRaise. G3AB must not invent or mirror Gothic's Quick R/L selector. The smallest existing proven factual boundary is downstream after Gothic writes `PropertyAction` Action4/5; the production task uses the already-owned CombatMove transport narrowly for Quick.

Reusable architecture was promoted to `docs/DESIGN.md` and the source lookup consequence to `docs/SOURCE_HOOK_GUIDE.md`.

Active implementation contract:

`docs/work/active/RAISE_ADDRAISE_PRODUCTION_IMPLEMENTATION.md`

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

Normal already has historical state-prepend runtime proof, including New Balance coexistence. Whirl has a direct high-level state candidate. The only unresolved pre-implementation transport fact is Quick: determine whether `PS_Melee_QuickAttack` entry already exposes factual Action4/Action5, or whether it still enters as generic Action3 before Gothic selects R/L.

Desired production shape:

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
- No build/deploy/runtime changes until the Quick factual-action precheck is closed and a bounded implementation task is frozen.

## Immediate next step

Perform **one bounded static precheck** for `PS_Melee_QuickAttack`:

```text
At the state-entry boundary intended for PREPEND_BREAK_BLOCK,
is the factual Quick action already Action4/QuickAttackR or Action5/QuickAttackL?

YES
-> freeze the generic production implementation for Normal / Quick / Whirl
-> use the selected factual R/L action when requesting Quick Raise

NO / still Action3
-> identify the smallest existing factual-selection boundary inside the same Quick route
-> do not invent R/L selection logic in G3AB
-> if necessary, use the existing lower-level CombatMove boundary only for Quick
```

Do not repeat broad Raise architecture research. Everything else needed for the first implementation is already decided.

After the Quick precheck, freeze one bounded production task:
- generic profile-driven Normal/Quick/Whirl AddRaise;
- no 2H-specific source branch;
- shipping AddRaise keys Off by default;
- 2H is only the first runtime fixture;
- Work build prohibited unless explicitly authorized;
- independent Normal Chat source review before local build/runtime testing.

Runtime acceptance must include both native and intended New Balance stacks. Normal has historical coexistence evidence; Quick and Whirl still require direct coexistence proof.

If Quick/Whirl state hooks conflict or cannot preserve the required factual action/profile semantics, fall back narrowly rather than redesigning the feature.


## First runtime acceptance sequence

The User already has authored Raise assets ready for Hero None+2H:
- Normal;
- Quick;
- full Whirl.

Implementation architecture must nevertheless be generic from the start. The 2H fixture is only the first acceptance surface, not a 2H-specific source gate.

Shipping INI:
- supported `Normal_AddRaise`, `Quick_AddRaise`, `Whirl_AddRaise` entries remain `Off` by default;
- the User manually turns them On only for the profile currently under test.

Initial runtime order:

```text
A. AddRaise Off control
   -> 2H Normal / Quick / Whirl remain native

B. Native stack, Hero None+2H
   -> Normal_AddRaise=On
   -> Quick_AddRaise=On
   -> Whirl_AddRaise=On
   -> verify Raise -> Hit -> native continuation
   -> verify no duplicate/repeated Raise
   -> for Quick, verify both factual QuickAttackR and QuickAttackL routes where gameplay reaches them

C. Intended New Balance stack
   -> repeat the same 2H Normal / Quick / Whirl fixture
   -> verify historical Normal coexistence remains true
   -> establish first direct Quick + New Balance and Whirl + New Balance coexistence evidence

D. Speed-coupling contrast
   -> after basic AddRaise transport passes at neutral BaseSpeed=ReferenceHitBaseSpeed,
      deliberately change the tested BaseSpeed values
   -> observe whether inserted Raise naturally follows the same relative timing change
   -> only if it does not, design the smallest generic relative-scale solution;
      do not add a user-facing Raise speed key

E. Cross-profile generalization
   -> create/provide matching 1H Raise assets
   -> enable AddRaise for the relevant 1H profile(s)
   -> verify no new C++ branch is needed
```

Quick-specific implementation caution:
- user-facing `Quick_AddRaise` is one setting;
- Gothic's factual playback/asset variants are QuickAttackR (Action4) and QuickAttackL (Action5);
- the implementation must let Gothic select/use the correct factual R/L Raise route rather than inventing or collapsing it to generic Action3.
