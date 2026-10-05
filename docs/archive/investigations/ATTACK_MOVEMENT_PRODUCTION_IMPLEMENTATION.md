# Attack Movement — Absolute-Distance Production Implementation

**Status:** CLOSED / SOURCE REVIEW PASS — EV-441  
**Mode:** bounded production source implementation  
**Architecture authority:** EV-438–EV-440

## Purpose

Implement the accepted per-profile **absolute CombatMove Hit distance** feature.

This task is implementation only. The architecture and user-facing semantics are frozen.

## Frozen semantics

For each supported attack setting:

```text
<Attack>_Movement=Off
= G3AB does not alter CombatMove movement for that attack

<Attack>_Movement=<finite non-negative number>
= G3AB owns the nominal CombatMove distance for that factual Hit

Movement=0
= valid; no CombatMove translation for that Hit
```

Examples:

```ini
Normal_Movement=Off
Quick_Movement=Off
Power_Movement=120
```

A numeric value is absolute Gothic authored-style movement distance. It is **not**:
- a multiplier over the animation filename;
- a multiplier over New Balance;
- a literal guaranteed world-space endpoint.

Native obstacle/ledge/target/navigation stopping remains authoritative.

## Compatibility contract

```text
Native + Movement=Off
= exact native movement behavior

New Balance + Movement=Off
= exact New Balance movement behavior

Native + Movement=numeric
= G3AB absolute Hit distance ownership

New Balance + Movement=numeric
= New Balance runs normally first
-> G3AB replaces only the final Hit movement magnitude
-> native CharacterMovement executes normally
```

Do not detect New Balance or AttackCollision at runtime.

## Protected accepted systems

```text
Collision = CLOSED/PASS
Speed = CLOSED/PASS
Raise = CLOSED/PASS
New Balance compatibility = protected
AttackCollision compatibility = protected
```

No Collision source or policy may change.
No Speed policy may change.
No Raise policy/sequencing may change.

## Allowed production files only

```text
src/Script_G3AnimationBehaviors/CMakeLists.txt
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/AttackMovement.cpp
src/Script_G3AnimationBehaviors/AttackMovement.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Do not edit any other production file.

## Module ownership

### BehaviorProfiles

Extend existing `AttackSettings` with optional movement configuration.

Required semantic shape:

```cpp
bool hasMovement;
float movement;
```

Use the existing profile identity and attack-setting storage.

Do not create a separate movement profile map.

Movement parsing is intentionally separate from Speed parsing:

```text
missing -> inactive
Off     -> inactive
finite numeric >= 0 -> active
invalid / negative / non-finite -> inactive
```

Case handling should follow existing normalized INI parsing.

Do not weaken or reinterpret positive-only Speed parsing.

### AttackMovement

Create `AttackMovement.cpp/.h` as the permanent movement policy owner.

Responsibilities only:
- physical Hit eligibility;
- factual action -> existing `BehaviorProfiles::AttackType`;
- existing profile lookup;
- Sprint/Power behavior through factual request identity;
- absolute distance -> velocity magnitude composition;
- fail-closed validation;
- mutation of the supplied final movement vector only after all required validation succeeds.

Do not put hook installation in AttackMovement.

Do not add state/cache/generation tracking.

### EngineBridge

Own only the physical hook transport.

Add exactly one movement hook at:

`Game+0x16B8B7`

No other movement hook is authorized.

## Frozen hook / ABI transport — EV-440

Immediately before the native call:

```text
ECX       = gCCharacterMovement_PS receiver from SPU+0x12C
[ESP]     = native enable argument 1
[ESP+4]   = native local target-proxy reference
[ESP+8]   = vector reference -> SPU+0xFC
[EBP+8]   = current CombatMove request
[EBP+0xC] = current SPU
```

`+0x16B8B7` is the five-byte call to `Game+0xEA0C0`:

```cpp
EnableCombatMovementFromSPU(
    GEBool,
    eCEntityProxy const &,
    bCVector &);
```

Use the reviewed insertion shape:

```cpp
Hook_AttackMovement
    .Prepare(RVA_Game(0x16B8B7), &AttackMovement_Compose)
    .InsertCall()
    .AddPtrStackArgEbp(0x8)
    .AddPtrStackArgEbp(0xC)
    .AddPtrStackArg(0x8)
    .SaveReg(mERegisterType_Ecx)
    .Hook();
```

Naming may vary consistently, but transport semantics may not.

The `void GE_STDCALL` bridge helper receives:
1. current `sAICombatMoveInstr_Args`;
2. current SPU;
3. existing native `bCVector` reference.

The helper delegates immediately to AttackMovement policy.

Do not use shared implicit-this storage.
Do not use `.RestoreRegister()` for this hook.
Do not replace the original CharacterMovement call.
Do not call `EnableCombatMovementFromSPU` manually.

The relocated native call must execute exactly once after the helper and ECX must be restored.

## Action scope

Initial supported movement profile actions:

```text
gEAction_Attack        -> Normal
gEAction_QuickAttackR  -> Quick
gEAction_QuickAttackL  -> Quick
gEAction_PowerAttack   -> Power
gEAction_PierceAttack  -> Pierce
gEAction_HackAttack    -> Hack
gEAction_SimpleWhirl   -> SimpleWhirl
gEAction_WhirlAttack   -> Whirl
```

Do not add `gEAction_QuickAttack` merely because it exists in the enum; current proven physical Quick routes are Action4/5.

Do not add:
- FinishingAttack;
- JumpAttack;
- RamAttack;
- GetUpAttack.

Sprint requires **no new Sprint profile**. The proven Sprint shared route constructs the physical Action2/Power Hit request at this downstream seam, so it naturally resolves `Power_Movement`. Do not infer Sprint from actor Action9 here and do not rewrite its factual physical request.

## Physical phase gate

Movement ownership is Hit only.

Use the actual CombatMove request phase and require physical `Hit`.

Raise and Recover must pass untouched.

Synthetic AddRaise Raise requests therefore do not require movement state or continuation ownership.

## Absolute movement calculation

For an active numeric movement setting:

1. obtain the actor from `request.SelfEntity`;
2. resolve existing profile identity with the factual request/action and Hit phase;
3. resolve the configured movement value;
4. for a positive configured distance:
   - acquire the current visual-animation property set;
   - acquire its actor;
   - read current primary-first max time using the same SDK surface used by pinned New Balance;
   - consume **request.AniSpeedScale as already composed**;
   - compute:
```text
duration = maxTime / request.AniSpeedScale
velocityMagnitude = configuredMovement / duration
```
5. preserve the existing final compatible vector direction;
6. normalize and scale only after all validation has passed.

Do not call `GetAnimationSpeedModifier`.
Do not query or reconstruct New Balance reach.
Do not parse the animation filename.
Do not recompute Speed composition.

## Movement = 0

A configured numeric zero is active and means no CombatMove translation.

After request/entity/action/profile/Hit eligibility is confirmed, clear the supplied movement vector directly without normalizing it.

Do not treat zero as Off.

## Fail-closed rules

Return without mutating the vector when any required context is invalid:

- null request;
- null SPU;
- null/self-invalid actor;
- non-Hit request;
- unsupported factual action;
- missing profile;
- missing Movement setting;
- Movement=Off;
- invalid/negative/non-finite Movement;
- unavailable animation property set/actor when positive distance requires timing;
- non-finite or non-positive `AniSpeedScale`;
- non-finite or non-positive max time;
- non-finite or non-positive computed duration;
- positive configured Movement with degenerate final direction;
- non-finite computed velocity magnitude.

For positive movement:
- calculate the replacement locally first;
- validate it;
- only then normalize/scale/write the supplied vector.

Do not partially mutate and then fail.

EV-439: the known native `Troll_Stand_None_Fist` zero-distance attack route could not be made to occur in runtime and is not the project's factual Troll route. Do not add a second hook or direction state machine for that route.

## INI

Update the shipping INI documentation from Speed-only wording to Attack Behavior settings as appropriate.

For every attack type already represented in each shipping profile, add the corresponding inactive movement key alongside its existing settings, for example:

```ini
Normal_ReferenceHitBaseSpeed=0.70
Normal_BaseSpeed=0.70
Normal_AddRaise=Off
Normal_Movement=Off

Quick_ReferenceHitBaseSpeed=1.00
Quick_BaseSpeed=1.00
Quick_AddRaise=Off
Quick_Movement=Off

Power_ReferenceHitBaseSpeed=1.00
Power_BaseSpeed=1.00
Power_Movement=Off
```

Do not invent attack types absent from a profile merely to make the INI visually symmetric.

Document:
- `Off` preserves native/New Balance;
- numeric value is absolute Gothic authored-style CombatMove distance;
- `0` disables CombatMove movement for that Hit;
- movement is nominal and native stopping/navigation can reduce realized world travel.

Shipping defaults must all be `Off`.

## Build integration

Add `AttackMovement.cpp/.h` to the existing `target_tree_sources` list only.

No new library/target.

## Static audit before commit

Check all of the following:

- only allowed production files changed;
- exactly one new physical hook, at `Game+0x16B8B7`;
- hook uses the EV-440 transport exactly;
- no hook at New Balance `+0x16B8A9`;
- no New Balance/AttackCollision DLL detection or function hook;
- no state/cache/global per-actor movement lifecycle;
- no per-frame work;
- Off path performs no vector mutation;
- numeric zero is active;
- positive path validates finite replacement before mutation;
- original CharacterMovement call remains intact and executes once;
- request `AniSpeedScale` is consumed, not recomposed;
- no Collision module changed;
- no Speed/Raise source changed;
- profile lookup reused without redesign;
- Sprint obtains Power movement from the factual Action2 request;
- `git diff --check` passes.

## Build policy

Do not build.
Do not deploy.
Do not run Gothic 3.

The User owns local build/deploy/runtime after independent source review.

## Commit / handoff

If implementation passes the bounded static audit:
- commit/push to `development`;
- report exact implementation commit SHA;
- report changed files;
- report exact hook installation;
- summarize parser semantics and action mapping;
- summarize fail-closed behavior;
- report `git diff --check`;
- report **Build: NOT ATTEMPTED — not authorized**;
- STOP for independent Normal Chat source review.


## Closure — EV-441

Implementation commit:
`7393f390f30d1981a5065b6342a684cd590fbac9`

Independent Normal Chat source review:
```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    0
PASS
```

Next gate is User-local build/deploy/runtime acceptance. No further source changes are justified absent build/runtime contradiction.
