# Speed v2 Caller-Side Composition — Bounded Production Implementation

**Status:** CLOSED / IMPLEMENTED / SOURCE-REVIEW PASS / ARCHIVED  
**Date:** 2026-09-28  
**Feature:** Speed only  
**Final source:** `4f9911f57d8d6b36efd35adee41920560c3986e0`  
**Build/run during source task:** NOT ATTEMPTED / PROHIBITED

> Archived after bounded implementation and source review. The first review of the implementation lineage found one blocking omission at `c11c1486c05161a300fcb3ea6de1da5e5140cb04`: `AttackSpeed` was compiled but the six caller-side transport hooks were not installed. The bounded correction at `4f9911f57d8d6b36efd35adee41920560c3986e0` added only the frozen `EngineBridge` transport. Post-correction static review passed. Build/runtime validation remains a separate later gate.

## Responsibility

Replace the dormant/rejected Speed prototype with the smallest production implementation of the statically proven caller-side composition mechanism.

The feature invariant remains:

```text
unconfigured effective speed = B * M
configured effective speed   = C * M
```

where:

```text
B = exact evidenced compatible native/New Balance base for this route
C = configured profile BaseSpeed
M = compatible Gothic/New Balance contextual multiplier chain
```

Production composition is:

```text
live compatible result = B * M
G3AB result            = (B * M) * (C / B)
                       = C * M
```

This task does **not** own the final effective speed and does **not** copy New Balance's multiplier policy.

## Research closure

### Generic Quick / Action3

`gEAction_QuickAttack` / Action3 is a selector/request identity on the proven generic Quick route, not the action delivered to the speed function:

```text
GetPrimaryPoseExt(Action3, Hit)
-> choose/write PropertyAction = Action4 or Action5
-> later PropertyAction() returns 4/5
-> Script_Game+0x48677 calls GetAnimationSpeedModifier with EAX=4/5
```

Therefore no separate Action3 speed-consumer hook is required for the proven route. If Action3 unexpectedly reaches the bounded production thunk, it is unsupported and must fall through unchanged.

### Part-13 dynamic consumers

The `100FFEA8` action-carrier object's `+0x158` field is populated from an explicit constructor argument by `Script_Game+0x3A2D0`. Static constructors populate that exact field with Action4 and Action5, so the four `FEA8` speed consumers below are Quick-capable factual action consumers.

`Script_Game+0x38A8B` is **not** one of them. Its separate `100FFEA0` lineage receives `+0x158` from an integerized `PSRoutine::GetStateTime()` value and copies that scalar forward. A numeric 4/5 at that site is therefore not factual Quick identity. Hooking it would create a false-positive action match.

## Exact production call-site set

Install caller-side call hooks only at these six tested-build RVAs:

```text
Script_Game+0x383F0  fixed Action1 / Normal / Hit

Script_Game+0x38E9D  FEA8 factual action carrier / Hit
Script_Game+0x38F22  FEA8 factual action carrier / Hit
Script_Game+0x3937D  FEA8 factual action carrier / Hit
Script_Game+0x39402  FEA8 factual action carrier / Hit

Script_Game+0x48677  generic Quick route after Action3 -> PropertyAction 4/5 / Hit
```

The corresponding current-tested CALL bytes target `Script_Game+0x42A0`:

```text
+0x383F0  E8 AB BE FC FF
+0x38E9D  E8 FE B3 FC FF
+0x38F22  E8 79 B3 FC FF
+0x3937D  E8 1E AF FC FF
+0x39402  E8 99 AE FC FF
+0x48677  E8 24 BC FB FF
```

Do **not** hook:

```text
Script_Game+0x38A8B  # +0x158 is propagated integerized StateTime, not factual action
Script_Game+0x4AC6F  # action is concretely 27/28
Script_Game+0x4C6FA  # separate Action6 route
other GetAnimationSpeedModifier callers
StartPlayAni* globally
Script_Game+0x42A0 entry itself
```

## Hook ownership and transport

`EngineBridge.cpp` remains the sole low-level Gothic hook owner for the production DLL.

Use six `mCCallHook` instances in `EngineBridge.cpp`. Do not put new hook ownership in `AttackSpeed.cpp`.

The call-hook transport must pass incoming EAX as an explicit argument using the SDK register-argument mechanism (`AddRegArg(mERegisterType_Eax)` or the exact equivalent supported by the pinned SDK). This avoids shared register-magic state and lets the six sites delegate to one common transport thunk.

Conceptually:

```text
selected caller has:
    EAX = factual action
    stack = existing Entity + gEPhase arguments

mCCallHook
    -> push EAX as explicit action argument
    -> common Speed transport thunk(action, entity, phase)
```

The transport thunk then:

```text
1. invokes LIVE Script_Game+0x42A0 exactly once with the same entity/phase
   and with the captured factual action restored in EAX;
2. receives the compatible float result B*M;
3. delegates composition policy to AttackSpeed;
4. returns the resulting float through the same ABI/x87 return path.
```

Use the pinned SDK `mCCaller` register-call facility (or an equivalent already-supported SDK mechanism) to invoke the live `+0x42A0` entry with EAX restored. Do not capture/trampoline the displaced call target. The runtime call must target the live `Script_Game+0x42A0` address so whichever compatible owner is installed there at execution time remains authoritative.

This preserves New Balance ownership without depending on DLL load order.

## AttackSpeed feature responsibility

`AttackSpeed` owns only the Speed decision/composition after the compatible result has already been obtained.

Conceptually:

```text
ComposeCompatibleSpeed(entity, action, phase, compatibleSpeed)
```

Required behavior:

```text
phase != Hit
-> unchanged

unsupported action
-> unchanged

entity == None
-> unchanged

runtime profile identity cannot be built
-> unchanged

no exact profile or BaseSpeed absent
-> unchanged

no trustworthy technical base B for exact factual route
-> unchanged

otherwise
-> compatibleSpeed * (configuredBase / referenceBase)
```

Do not add feature state, attack lifecycle ownership, polling, diagnostics, or Raise behavior.

## Runtime profile identity

Reuse the accepted ADR-0007 identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

Runtime sources:

```text
AnimationFamily       <- Entity.Animation.GetResourceName()
raw left UseType      <- left-hand runtime item/source
raw right UseType     <- right-hand runtime item/source
ActionProfile Normal  <- factual Action1
ActionProfile Quick   <- factual Action4/Action5 on this proven transport surface
```

Normalize raw UseTypes according to `ANIMATION_RULES.md` before profile lookup. Keep raw UseTypes available separately for the technical `B` lookup; do **not** infer technical base only from normalized animation tokens, because multiple raw UseTypes can normalize to the same token while retaining different compatible speed policy.

The current melee normalization needed by this task includes the canonical mappings for at least:

```text
None
1H
2H
Shield
Torch
Staff
Fist
Axe -> 2H
Pickaxe -> 2H
Halberd -> Staff
PhysicalFist -> Fist
Broom/Rake/Shovel/Fan -> Staff
```

Unknown/unhandled runtime identity fails closed.

## Technical reference-base facts

`B` is implementation evidence, not a user-facing default. Do not add a new INI field merely to expose it.

Represent the accepted facts as a small immutable **data table / factual lookup**, not weapon-specific feature-policy branches.

For the primary current New Balance stack, exact source corroborates these Normal facts:

```text
Action1 / Normal:
raw left None    + raw right 1H       -> B=0.6
raw left Shield  + raw right 1H       -> B=0.6
raw left Torch   + raw right 1H       -> B=0.6
raw left 1H      + raw right 1H       -> B=0.6
raw left None    + raw right 2H       -> B=0.7
raw left None    + raw right Axe      -> B=0.7
raw left None    + raw right Staff    -> B=0.7
raw left None    + raw right Halberd  -> B=0.7
```

Direct runtime evidence already includes 1H Normal `0.600` and 2H Normal `0.700` on the tested routes.

For factual Quick playback actions:

```text
Action4 / QuickAttackR -> B=1.0
Action5 / QuickAttackL -> B=1.0
```

Current New Balance source applies `1.0 * multiPlier` for both; direct runtime evidence already includes QuickAttackL `1.000` on the tested route.

The initial production factual lookup must remain evidence-bounded. In particular:

```text
Action3 generic Quick -> no direct consumer in this surface; fail closed if encountered
Normal Fist/PhysicalFist -> unsupported for this composition contract
unknown raw UseType combination -> fail closed
unproven non-Hero animation family -> fail closed
```

New Balance's humanoid-Fist Normal branch returns its special base directly instead of the ordinary `B*M` form; it must not be silently treated as a normal `0.7*M` route.

Do not generalize `Axe -> 2H` or `Halberd -> Staff` normalization into a technical-base assumption for every raw type sharing those serialized tokens. Technical `B` selection uses factual raw UseTypes.

## Allowed source scope

Modify only what is required for this responsibility, expected to be:

```text
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/CMakeLists.txt
```

`AttackSpeed.cpp/.h` were dormant prototype files before this task and were not compiled by the production target. Rewrite them for the accepted production responsibility and add them to the production target. Do not resurrect the old `mCFunctionHook` ownership or the old player-only/2H-only/final-result replacement semantics.

A small local helper/data structure inside `AttackSpeed` or `BehaviorProfiles` is allowed when needed to express the frozen contract. Do not add a new subsystem unless source structure genuinely requires it.

## Protected behavior

Must remain unchanged:

```text
all collision behavior and hooks
unconfigured Speed profiles
unsupported Speed routes
New Balance contextual speed modifiers
native-only behavior when no matching configured/evidenced route applies
Raise behavior (still inactive/paused)
INI schema from ADR-0007
```

No source change may alter marker collision, raw8/raw55 ownership, equipped Sprint collision, cleanup, or diagnostics.

## Hard exclusions

Do not implement:

```text
mCFunctionHook ownership of Script_Game+0x42A0
same-hook chaining/load-order dependence
final effective-speed replacement
copied New Balance stamina/disease/arena/species policy
New Balance DLL/version detection as behavior policy
global animation-speed override
global StartPlayAni hook
Action3 guesswork
StateTime-as-action matching at +0x38A8B
new native-speed logger/probe
Raise
collision changes
```

## Static validation only

Source implementation validation is limited to:

```text
exact diff/scope review
six-hook-address review
call-site byte/target review against current tested reference
ABI/register-transport review
profile fallback review
B-fact table review
unconfigured/unsupported fail-closed review
collision protected-behavior review
git diff --check or equivalent source-only hygiene
```

**Build, deployment and game execution were not authorized in this source task.**

## Closure result

Final corrected source review established:

```text
six exact EngineBridge mCCallHook sites = present
excluded +0x38A8B = absent
Script_Game+0x42A0 entry ownership = not taken
incoming factual EAX = explicit hook argument
live +0x42A0 invocation = mCCaller with EAX restored
AttackSpeed = policy/composition only
BehaviorProfiles = normalized identity + separate raw UseTypes
technical B lookup = evidence-bounded immutable table
unsupported/unconfigured routes = fail closed / compatible result unchanged
collision correction diff = untouched
production CMake = AttackSpeed included
```

Source result: **PASS**.  
Build/runtime result: **NOT YET TESTED**.

## Later runtime acceptance gate

After local build, validate New Balance composition first:

```text
configured Normal/Quick full-stamina controls
configured equivalent depleted-stamina controls
representative disease/arena modifier controls where practical
unconfigured controls
multiple supported hand configurations
```

Expected invariant:

```text
configured base changes
AND
relative compatible modifiers remain effective
```

Then perform native-only sanity/fallback. Speed must close completely before Raise work begins.

## Authorities

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
4. `docs/FEATURE_DEVELOPMENT_METHOD.md`
5. ADR-0004
6. ADR-0005
7. ADR-0007
8. `docs/ANIMATION_RULES.md` §§3–5
9. EV-391 + EV-392
10. pinned SDK hook API at `90bfd344de4510dda7ac9da7461cc7f1eac911f7`
11. pinned New Balance reference `316d32406a133f8884e7e302752c35f66b4f54fc`
