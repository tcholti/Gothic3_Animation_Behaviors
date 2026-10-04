# Raise / Speed Phase Consistency — Production Correction

**Status:** ACTIVE — BOUNDED PRODUCTION SOURCE IMPLEMENTATION  
**Branch:** `development`  
**Evidence authority:** EV-414–EV-415  
**Design authority:** `docs/DESIGN.md` Raise section  
**Runtime acceptance record:** `docs/work/active/RAISE_ADDRAISE_RUNTIME_ACCEPTANCE.md`

## Responsibility

Implement **only** the EV-415 production correction that makes configured attack speed consistent across the proven Raise/Hit behavior while preserving compatible/native phase relationships.

This is not new feature research. The mechanism is frozen.

## Read first

1. root `README.md` -> Start Here;
2. `docs/SESSION_ENTRYPOINT.md`;
3. `docs/BETWEEN_CHATS.md`;
4. this document;
5. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
6. `docs/FEATURE_DEVELOPMENT_METHOD.md`;
7. `docs/DESIGN.md` Raise + Speed sections;
8. only the exact source files allowed below unless a concrete compile/API contradiction requires one narrow lookup.

Do not load the full evidence ledger. EV-415 is summarized here and in DESIGN.

## Frozen authoring invariant

```text
one <Attack>_BaseSpeed
-> coherent authored attack timing across Raise / Hit / Recover where those phases exist
-> preserve Gothic/New Balance phase-specific native relationships and contextual modifiers
-> no separate RaiseSpeed
```

Two mechanisms are intentionally distinct:

```text
G3AB-added Raise
= part of the same authored Normal / Quick / Whirl attack
= use the exact already-composed effective Hit AniSpeedScale

native Power Raise
= has its own Gothic/New Balance live Raise result
= preserve that result and apply the same Power authoring ratio on top
```

Do not collapse these into one generic absolute-speed rule.

## Allowed production files

Edit only as needed:

```text
src/Script_G3AnimationBehaviors/AttackRaise.cpp
src/Script_G3AnimationBehaviors/AttackRaise.h
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
```

No CMake change is expected.

Do not modify:
- `BehaviorProfiles.cpp/.h`;
- shipping INI;
- collision modules;
- motion-routing modules;
- diagnostics;
- documentation during Work implementation.

If faithful implementation requires a file outside the allowed set, STOP and report the exact dependency instead of broadening.

## A. Custom AddRaise transport — Normal / Quick / Whirl

The existing sole physical `sAICombatMoveInstr` hook remains the one transport.

Generalize the current Quick continuation mechanism so it supports exactly these factual Hit actions:

```text
Normal:
  gEAction_Attack / Action1

Quick:
  gEAction_QuickAttackR / Action4
  gEAction_QuickAttackL / Action5

Whirl:
  gEAction_WhirlAttack / Action10
```

Required gate:

```text
incoming request phase = "Hit"
+ exact supported action above
+ matching resolved profile
+ corresponding Normal/Quick/Whirl_AddRaise = On
-> custom Raise continuation
```

Off/missing/unmatched/unsupported:
```text
-> pass native request unchanged
```

### Custom Raise request

Construct Raise from the factual incoming Hit request:

```text
SelfEntity   = incoming Hit SelfEntity
TargetEntity = incoming Hit TargetEntity
Action       = incoming factual Hit Action unchanged
PhaseName    = "Raise"
AniSpeedScale = incoming Hit AniSpeedScale
```

The speed field is not recalculated in `AttackRaise`.

Do not:
- call `GetAnimationSpeedModifier` again;
- calculate `BaseSpeed / ReferenceHitBaseSpeed` inside `AttackRaise`;
- query/copy New Balance policy;
- force `1.0f`;
- infer Quick R/L;
- reconstruct animation filenames.

### Continuation semantics

Preserve the already-reviewed Quick semantics, generalized only to the supported custom-AddRaise actions:

```text
store exact original factual Hit request
-> service Raise until complete
-> start/service exact stored Hit
-> erase state after Hit completes
```

Cancellation/fail-closed behavior remains:

- FullStop cancels current Raise continuation before native delegation;
- AISetState cancels current Raise continuation before destructive replacement;
- actor mismatch cancels;
- factual persisted action mismatch cancels;
- a different non-null request identity cancels and passes the replacement request natively;
- no state may leak into a later attack;
- native re-entrancy/cancellation must not start a stored Hit after its continuation was invalidated.

The implementation may rename `QuickContinuation` / `CancelQuickContinuation` to generic Raise-continuation names. That is local organization, not new semantics.

### Remove redundant high-level AddRaise hooks

After Normal and Whirl use the proven CombatMove continuation, remove the production AddRaise wrappers/hooks for:

```text
PS_Melee_Attack
PS_Melee_WhirlAttack
```

Specifically remove the corresponding:
- hook objects;
- wrapper script states;
- installation calls;
- `RunNormalState` / `RunWhirlState` public transport API if no longer used.

Do not remove or alter Gothic/New Balance's own states. This removes only G3AB's redundant wrappers.

There must still be exactly one physical G3AB `sAICombatMoveInstr` hook.

## B. Native Power Raise composition

Power has distinct tested-build live speed callers:

```text
Script_Game+0x47D51 = Action2 / Raise
Script_Game+0x47F6C = Action2 / Hit
```

The Hit caller is already in production.

Add exactly one new Speed call-site hook:

```text
Script_Game+0x47D51
```

Use the same existing `GetAnimationSpeedModifier_Composed` caller-side mechanism:
- restore/pass the factual Action2 exactly;
- invoke the live `Script_Game+0x42A0` owner exactly once;
- receive its compatible Raise result;
- delegate compatible composition to `AttackSpeed`.

No new entry-point `+0x42A0` hook.

### AttackSpeed phase rule

Current Hit behavior remains unchanged.

Extend compatible composition only so:

```text
phase == Hit
-> existing supported attack composition unchanged

phase == Raise
+ action == gEAction_PowerAttack
-> use Power profile
-> apply Power authoring ratio to the live compatible Raise result

all other non-Hit phases
-> pass compatible result unchanged
```

Power Raise formula:

```text
referenceHitBase = Power_ReferenceHitBaseSpeed
configuredBase   = Power_BaseSpeed
compatibleRaise  = live Gothic/New Balance result from +0x42A0

configuredRaise =
    compatibleRaise * (configuredBase / referenceHitBase)
```

Keep the existing finite/positive fail-closed guards.

Do not add a Raise reference setting.

### Profile identity for Power Raise

Use the same resolved Power attack/profile identity and `Power_ReferenceHitBaseSpeed` authority used by the Power Hit authoring model.

Do not create a phase-specific profile dimension or Raise-specific key.

If the existing `TryBuildRuntimeKey` call needs to use the Hit request identity when composing Power Raise so the exact Power profile remains authoritative, that is allowed and preferred over adding new profile semantics.

### Sprint preservation

ADR-0009 remains protected.

A factual Sprint/Action9 may reach the proven shared Power speed route with Action2 supplied to the compatible owner.

The new `+0x47D51` composition must:
- preserve the passed Action2 transport;
- preserve the live compatible Raise result;
- use the existing Power profile authoring ratio;
- add no Sprint key;
- add no Action9 rewrite;
- add no universal Sprint multiplier.

## C. Routes that must remain untouched

### Hack

EV-414 proves visible Hack Raise already follows configured Hack speed.

Do not add a Hack Raise caller/hook or second scale.

### Pierce

EV-414 proves visible Pierce Raise already follows configured Pierce speed.

Do not add a Pierce Raise caller/hook or second scale.

### SimpleWhirl

No factual Raise correction is established.

Do not add SimpleWhirl Raise behavior.

### Finishing

Outside the current production Speed/AddRaise authoring surface. Unchanged.

## D. Protected systems

Must remain behaviorally unchanged except for the exact phase-speed correction above:

- Collision through EV-390;
- Speed v2 Hit composition through EV-410;
- ADR-0011 resolved profile identity;
- AddRaise Off fail-closed behavior EV-411;
- AddRaise sequencing / factual Quick R/L / New Balance coexistence EV-412;
- Hack/Finishing speed isolation;
- Hack/Pierce already-coupled Raise behavior;
- destructive Alternative AI block-skip ownership remains `AttackContinuationProtection`, not Raise;
- motion routing;
- Finishing;
- shipping configuration.

## E. Static source acceptance

Before publication, verify at minimum:

1. custom AddRaise supports only Action1 / Action4 / Action5 / Action10 Hit requests;
2. Quick still has no Action3 chooser/inference;
3. inserted custom Raise copies incoming Hit `AniSpeedScale` exactly;
4. no hard-coded `1.0f` remains as custom Normal/Quick/Whirl Raise speed;
5. high-level G3AB `PS_Melee_Attack` and `PS_Melee_WhirlAttack` AddRaise hooks/wrappers are gone;
6. exactly one G3AB physical `sAICombatMoveInstr` hook remains;
7. Speed caller set changes only by adding `+0x47D51`;
8. `+0x47F6C` and all previously accepted Hit callers remain installed unchanged;
9. `AttackSpeed` composes Raise only for Action2/Power;
10. Hack/Pierce/SimpleWhirl receive no Raise-specific composition;
11. no `RaiseSpeed` / `ReferenceRaiseBaseSpeed` parser/config/key appears;
12. no copied New Balance policy appears;
13. collision lifecycle still wraps every actual native CombatMove invocation;
14. FullStop / AISetState cancellation remains fail-closed for generalized Raise continuation;
15. `git diff --check` or equivalent passes;
16. exact changed-file scope is within the allowed list.

## Build policy

**BUILD PROHIBITED.**

Work must not configure, build, deploy, run Gothic 3, probe compiler availability, or troubleshoot build tooling.

Report:

```text
Build: NOT ATTEMPTED — Work build execution was not authorized for this task.
```

## Publication

Commit and push exactly the bounded source correction to `development`.

Then STOP for Normal Chat independent source review.

Do not:
- modify documentation;
- create a probe;
- add diagnostics;
- broaden attack scope;
- begin runtime testing;
- perform general cleanup/refactor outside what the correction mechanically requires.

## Later runtime acceptance — not part of Work

After independent source review + User-local build/deployment:

1. AddRaise Off sanity;
2. custom Normal / Quick R/L / Whirl with obvious authored speed contrast;
3. native Power Raise with obvious authored speed contrast;
4. verify Power Raise preserves its relative native/live phase behavior while scaling with the authored attack;
5. Hack/Pierce positive controls remain correct and are not double-scaled;
6. native stack;
7. intended New Balance stack, including at least one contextual-modifier control;
8. only then resume broader assembled regression.
