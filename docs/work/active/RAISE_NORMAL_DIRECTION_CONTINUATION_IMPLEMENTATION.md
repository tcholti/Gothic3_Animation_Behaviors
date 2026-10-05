# Raise — Normal Direction Continuation Implementation

**Status:** ACTIVE — SOURCE REVIEW PASS / FOCUSED RUNTIME VALIDATION PENDING  
**Branch:** `development`  
**Required documentation baseline:** EV-424 causal closure  
**Production behavior baseline:** `41ed80c6420e5236d13fc037cb5923b946cb8ccc`  
**Implementation candidate:** `1da12cead5acfb54c5520a34d07bccc4c32fd64f`  
**Source review:** EV-426 PASS — blocker 0 / major 0 / minor 0

## Responsibility

Fix only this defect:

```text
Normal AddRaise Left/Right:
correct directional Raise
-> stored Action1 Hit re-resolves Fwd
```

Preserve Gothic's **already selected native Raise direction** into the immediately following stored Normal Hit.

## Frozen mechanism

Use one narrow call-site transport at:

```text
Game +0x16B056
sAICombatMoveStart -> GetAniName
```

For the existing pending Normal AddRaise continuation:

1. On the synthetic Action1 / Raise GetAniName call:
   - observe the exact native direction `bCString` Gothic supplies;
   - observe/capture the matching current `gEDirection` from Navigation after native classification;
   - store both in that continuation state;
   - invoke Gothic GetAniName unchanged.

2. On the subsequent stored Action1 / Hit GetAniName call for the same SPU/continuation:
   - require a captured direction;
   - restore Navigation current-animation direction to the captured enum;
   - pass the captured native direction string instead of the newly recomputed string;
   - invoke Gothic GetAniName exactly once.

3. Every unrelated GetAniName call passes through unchanged.

Direction state must share the existing continuation's lifetime and cancellation semantics.

## EV-425 pre-implementation review refinement

Do **not** refactor the existing Raise state machine before this correction. The current implementation is accepted as the clean baseline.

Keep the correction mechanically minimal:

```text
RaiseContinuation gains only:
  bool directionCaptured
  gEDirection capturedDirection
  bCString capturedDirectionName
```

No second map/cache/lifecycle owner is allowed.

The exact `GetAniName` signature is:

```text
void GetAniName(
    bCString &,
    eCEntity *,
    gEAction,
    bCString phaseName,
    bCString &directionName,
    GEBool);
```

At `Game+0x16B056`:
- the phase argument is the factual CombatMove request `PhaseName`;
- the direction argument is Gothic's freshly selected direction string;
- ECX is already the current `gCScriptProcessingUnit *`.

Therefore the semantic guard should use the exact pending continuation + `gEAction_Attack` + factual phase:

```text
pending Normal + Raise -> capture native directionName + Entity::GetCurrentAniDirection()
pending Normal + Hit   -> substitute captured directionName
                          + Entity::SetCurrentAniDirection(capturedDirection)
otherwise              -> pass unchanged
```

Use the official SDK `Entity::GetCurrentAniDirection()` / `SetCurrentAniDirection()`; do not access Navigation by raw offset.

The existing local `shared_ptr<RaiseContinuation>` pattern must remain. It is intentionally re-entrancy-safe when native callbacks cancel/replace the map entry while the current invocation still owns the stored request/state.

## Ownership

```text
AttackRaise
= continuation state + eligibility + captured direction semantic state

EngineBridge
= physical Game+0x16B056 call-site transport only
```

Do not move filename policy into EngineBridge.

## Allowed production files

```text
src/Script_G3AnimationBehaviors/AttackRaise.cpp
src/Script_G3AnimationBehaviors/AttackRaise.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
```

No other production source or INI file may change.

## Explicitly forbidden

- parsing or replacing `_Fwd_`, `_Left_`, or `_Right_` in resource names;
- recreating Gothic's geometry/dot/cross direction algorithm;
- changing target, actor transform, or facing to force classification;
- relying on Recover;
- changing `m_DirectionVec` as a guessed preservation input;
- direct PlayAni replacement of CombatMove;
- changing public config;
- changing Speed composition or Hit `AniSpeedScale`;
- changing Quick Action4/5 or Whirl behavior;
- changing Power Raise, Hack compatibility, New Balance speed ownership, or Collision;
- broad/global GetAniName policy outside the exact pending Normal continuation.

## Static acceptance

Independent review must prove:
- one new narrow call-site hook only;
- exact pass-through when no eligible Normal continuation exists;
- Raise captures Gothic-native direction without altering it;
- Hit receives exactly that captured direction once;
- Navigation current-animation direction and serialized name direction remain consistent;
- continuation cancellation removes direction state;
- no filename parsing;
- no Speed/Collision changes.

## Runtime acceptance

```text
Normal Fwd:   Fwd Raise   -> Fwd Hit
Normal Left:  Left Raise  -> Left Hit
Normal Right: Right Raise -> Right Hit
```

Test at least:
- one 1H-family route with native directional Raise assets;
- the dual-wield route that exposed EV-423;
- one Quick AddRaise control;
- one Whirl AddRaise control;
- one interruption/cancellation control.

Do not broaden beyond this matrix unless contradictory evidence appears.
