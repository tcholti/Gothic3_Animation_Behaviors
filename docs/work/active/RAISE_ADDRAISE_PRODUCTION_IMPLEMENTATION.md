# Raise — Normal / Quick / Whirl AddRaise Production Implementation

**Status:** ACTIVE — FROZEN BOUNDED PRODUCTION IMPLEMENTATION  
**Task class:** production source + shipping INI implementation  
**Branch:** `development`  
**Frozen from source baseline:** `3d24ffd7fc3e92f5afaabfc5055bcfca822ef54c`  
**Build policy:** PROHIBITED in Work unless a later task explicitly authorizes build execution

## Purpose

Implement the locked first public AddRaise scope without reopening Collision or Speed:

```ini
Normal_AddRaise=On|Off
Quick_AddRaise=On|Off
Whirl_AddRaise=On|Off
```

All shipped values are `Off` by default.

This is production implementation after mechanism/design closure, not an exploratory probe.

## Read first

1. root `README.md` -> Start Here
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/BETWEEN_CHATS.md`
4. this task
5. `docs/DESIGN.md` Raise section
6. `docs/SOURCE_HOOK_GUIDE.md` Quick factual-action boundary
7. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
8. `docs/FEATURE_DEVELOPMENT_METHOD.md`
9. only the implementation files allowed below

Do not load broad evidence ledgers unless source inspection exposes a concrete contradiction.

## Closed Quick precheck

Generic Quick / Action3 is a selector/request identity on the proven native Quick route:

```text
GetPrimaryPoseExt(Action3, Hit)
-> Gothic chooses/writes PropertyAction = Action4 or Action5
-> later PropertyAction() returns Action4/5
-> Script_Game+0x48677 consumes factual Action4/5 / Hit
```

Therefore:

- `PS_Melee_QuickAttack` entry is not the factual R/L boundary for AddRaise;
- G3AB must never choose, alternate, infer, or reconstruct Quick R/L;
- factual Quick Raise uses only the Action4/Action5 Gothic has already selected;
- the smallest existing proven factual route is downstream after the native selector.

## Frozen production transport

Use one permanent Raise owner with two transport shapes.

### Normal

Use the proven high-level state pattern:

```text
PS_Melee_Attack
-> profile Normal_AddRaise Off/missing?
   yes -> untouched original state
   no  -> PREPEND_BREAK_BLOCK
          -> sAICombatMoveInstr(factual Action1, "Raise", 1.0f)
          -> wait for completion
          -> untouched original state / Hit / continuation
```

Remove the old player-only / None+2H policy gate. The historical source is mechanism reference only.

### Whirl

Use the same high-level pattern at `PS_Melee_WhirlAttack` with factual Action10/Whirl.

### Quick

Do not prepend at `PS_Melee_QuickAttack` entry.

Use the already-owned `sAICombatMoveInstr` transport only when the incoming factual request is:

```text
Action = QuickAttackR / Action4
OR
Action = QuickAttackL / Action5

Phase = Hit
```

At that boundary:

```text
matching resolved Quick profile + Quick_AddRaise Off/missing
-> pass original Hit request unchanged

matching resolved Quick profile + Quick_AddRaise On
-> request Raise using the SAME factual incoming Action4 or Action5
-> wait until that Raise completes
-> continue the untouched original factual Hit request
```

The permanent Raise owner may keep only the minimum per-SPU continuation state needed to guarantee:

- exactly one added Raise precedes one factual Quick Hit execution;
- an incomplete Raise resumes as Raise rather than starting the Hit early;
- once Raise completes, repeated continuation calls service the original Hit without injecting another Raise;
- state clears when that original Hit completes;
- state also clears/fails closed on FullStop/state replacement or factual request identity change so it cannot leak into a later attack.

`EngineBridge` remains sole physical hook owner. It may expose only the smallest factual CombatMove delegation/cleanup seam to the Raise owner. Do not add another physical CombatMove hook.

If the above continuation semantics cannot be expressed at the existing owned transport without changing Collision lifecycle semantics or adding another physical hook, STOP and report the exact contradiction. Do not compensate by inventing Quick R/L selection.

## Profile/config contract

Reuse the accepted profile identity exactly:

```text
AnimationFamily
+ ResolvedLeftAnimationToken
+ ResolvedRightAnimationToken
```

For all three supported attacks, resolve the profile from the factual attack's `Hit` request identity using the existing `BehaviorProfiles::TryBuildRuntimeKey(entity, action, gEPhase_Hit, ...)` path. Do not resolve the profile from a manually built Raise filename.

Rename the player-facing dormant parser key:

```text
<Attack>_RaiseOverride
-> <Attack>_AddRaise
```

Do not retain `_RaiseOverride` as a compatibility alias; it never became the finalized public shipping surface.

Internal enum/storage may remain generic if clean.

Only Normal, Quick and Whirl are supported AddRaise behavior in this task. Do not add behavior for Power, Pierce, Hack, SimpleWhirl, Finishing or Sprint merely because the generic profile structure stores attack settings.

## Shipping INI

Add supported AddRaise keys with `Off` values to shipped profiles where that attack block already exists.

Do not create a new attack block solely to expose AddRaise.

The Hero None+2H profile must ship:

```ini
Normal_AddRaise=Off
Quick_AddRaise=Off
Whirl_AddRaise=Off
```

Do not turn any AddRaise setting On in the shipping file.

Do not add a RaiseSpeed/RecoverSpeed setting.

## Animation-resolution rule

Never construct a Raise animation filename.

Always ask Gothic for factual action + `Raise` phase and let Gothic resolve the concrete resource.

Public README naming guidance is deferred until runtime acceptance; do not edit release README in this implementation task.

## Allowed source/files

Production edits are bounded to the smallest necessary subset of:

```text
src/Script_G3AnimationBehaviors/AttackRaise.cpp
src/Script_G3AnimationBehaviors/AttackRaise.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp
src/Script_G3AnimationBehaviors/CMakeLists.txt
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
src/Script_G3AnimationBehaviors/SharedConfig.cpp
src/Script_G3AnimationBehaviors/SharedConfig.h
```

`SharedConfig.*` is obsolete historical prototype configuration. Remove it if no longer referenced after the production Raise migration; do not preserve a parallel 2H-specific Raise policy.

Do not edit Collision feature modules, AttackSpeed, AttackMotionRouting, diagnostics/probe targets, SDK/submodules, release README, or unrelated documentation.

## Permanent ownership

`AttackRaise` owns:

- AddRaise policy;
- Normal/Whirl state prepend behavior;
- minimum Quick continuation state;
- factual Action4/5 reuse;
- profile/AddRaise decision helpers.

`BehaviorProfiles` owns:

- startup config parsing/storage;
- resolved animation-set identity.

`EngineBridge` owns:

- the existing low-level CombatMove hook exactly once;
- factual transport/delegation only;
- minimal Raise cleanup notification if required by FullStop/state replacement.

Do not move Raise policy into `EngineBridge`.

## Protected behavior

Must remain unchanged:

```text
Collision production behavior and lifecycle
Speed v2 composition/profile behavior
Speed caller set and +0x42A0 ownership model
Finishing behavior
AttackMotionRouting
raw8/raw55/equipped collision behavior
unconfigured/native melee behavior
New Balance policy
main branch
```

Also prohibited:

- weapon-specific `if 1H/2H/Axe/Staff/Rapier` AddRaise policy;
- species/name gates;
- Quick R/L alternation or selector logic;
- animation filename construction;
- new physical hook;
- polling/timers;
- copied New Balance multiplier policy;
- RaiseSpeed key;
- broader AddRaise families;
- broad refactor/cleanup.

## Static validation

Work may perform only source/static checks authorized by the implementation protocol:

- inspect exact diff/scope;
- verify no Action3-to-Action4/5 chooser exists in G3AB;
- verify Off/missing paths pass original behavior unchanged;
- verify Quick uses incoming factual Action4/5 unchanged for Raise;
- verify one physical CombatMove hook remains;
- verify AttackRaise is compiled/installed;
- verify shipping AddRaise values are all Off;
- verify obsolete 2H-specific SharedConfig path is absent from active production;
- `git diff --check` or equivalent source-format checks.

Build: **NOT ATTEMPTED — Work build execution is not authorized for this task.**

## Publication / stop

Work may commit and push exactly this bounded implementation to `development`.

Then STOP.

Do not build, deploy, run Gothic 3, interpret runtime behavior, add diagnostics, broaden scope, or perform repository-wide maintenance.

Normal Chat performs independent source review before any local build/runtime acceptance.

## Later runtime acceptance — not part of Work

After independent source review and local build/deployment verification:

```text
A. AddRaise Off control
B. native stack, Hero None+2H: Normal / Quick R+L / full Whirl
C. intended New Balance stack: repeat all three
D. deliberate BaseSpeed contrast to observe Raise timing coupling
E. later 1H cross-profile generalization with matching authored assets
```

The User already has ready Hero None+2H Raise assets for Normal, Quick and full Whirl.
