# Raise — Normal Direction Continuation Research

**Status:** CLOSED/PASS — EV-424 static causal closure  
**Branch:** `development`  
**Baseline production source:** `41ed80c6420e5236d13fc037cb5923b946cb8ccc`  
**Trigger:** EV-423

## Question

Why does an inserted Normal Raise preserve the directional Raise animation but cause the following factual Action1 Hit to resolve as Fwd instead of the originally selected Left or Right variant?

## Runtime fact

With Normal AddRaise enabled:
```text
Left Normal request -> matching Left Raise plays -> following Hit resolves Fwd
Right Normal request -> matching Right Raise plays -> following Hit resolves Fwd
```

Generated dual Fwd Normal Raises and ordinary P0/P1 Quick Raises resolve and play correctly. The defect is therefore continuation selection, not Raise filename construction.

## Established source fact

`gCScriptProcessingUnit::sAICombatMoveInstr_Args` contains only:
```text
SelfEntity
TargetEntity
Action
PhaseName
AniSpeedScale
```

There is no direction field. Current `AttackRaise::RaiseContinuation` stores this request, runs a synthetic Raise, then replays the stored Hit request. For Action1, replaying those fields alone cannot encode whether the original native selection was Fwd, Left or Right.

The SDK SPU contains additional state including `m_DirectionVec`, `m_sMotionDesc`, `m_strAniString` and `m_InstrAction`; their relevance to directional Normal selection is not yet proven.

## Required research

1. Trace native Normal Action1 Fwd/Left/Right from Script_Game into `sAICombatMoveInstr` and `sAICombatMoveStart`.
2. Identify the exact state/value used by `GetAniName` / CombatMove to select Fwd vs Left vs Right.
3. Determine whether that value exists before G3AB intercepts the factual Hit request.
4. Determine exactly what the synthetic Raise changes or consumes before the stored Hit is replayed.
5. Compare with the historical higher-level Normal AddRaise transport only as evidence; do not assume it solves directional continuation.
6. Freeze the smallest preservation mechanism only after ownership is proven.

## Candidate mechanisms to test, not assume

```text
A. snapshot/restore one proven SPU directional-selection field
B. preserve an exact already-selected Hit animation/resource identity
C. let native state retain/re-enter its own directional selection while still reusing composed Hit speed
```

Reject any candidate that requires filename-side guessing, weapon-specific branches, copied Gothic direction policy, polling, or a second global CombatMove hook.

## Protected

Do not alter:
- Speed `B*M -> C*M` composition;
- custom Raise exact Hit-scale reuse;
- Quick factual Action4/5 selection;
- Whirl AddRaise;
- Power Raise live-ratio composition;
- Hack route-neutral compatibility;
- Collision modules/lifecycle;
- New Balance live speed ownership;
- public INI schema.

## Research boundary

Prefer static evidence first from:
- `AttackRaise.cpp/.h`;
- `EngineBridge.cpp`;
- pinned SDK `ge_scriptprocessingunit.h`;
- `Game+0x1696E0` / `sAICombatMoveStart`;
- `Game+0x16F840` / `GetAniName`;
- existing CombatMove animation-string/resource-query path;
- exact native Normal Script_Game call path.

If static evidence cannot identify the directional owner, the next step is a **small diagnostic-only probe**, preferably using already-owned boundaries, logging only the exact candidate state around native Fwd/Left/Right Hit and synthetic Raise. Do not modify production behavior for that probe.

## Exit condition

Research closes only when one mechanism explains:
```text
native Fwd remains Fwd
native Left remains Left
native Right remains Right
Raise remains before Hit
Hit-scale reuse remains exact
interruption cancellation remains fail-closed
```

Then freeze a separate bounded production implementation task and require independent source review + focused runtime validation.


## Result — EV-424

Static inspection identifies the exact owner:

```text
sAICombatMoveStart
-> rebuild current direction / actor-relative classification
-> choose gEDirection
-> build exact Fwd / Left / Right bCString
-> write Navigation current-animation direction
-> pass direction bCString as fifth GetAniName argument
-> GetAniName serializes it into the resource name
```

Therefore the previous animation filename is **not** the direction authority for the next Action1 CombatMove. The filename contract remains important for pose/resource identity, but Normal direction is explicitly supplied anew to `GetAniName`.

EV-423 occurs because G3AB inserts two separate CombatMoves:

```text
first start = Raise -> original Left/Right classification
second start = stored Hit -> fresh classification -> may become Fwd
```

No runtime diagnostic probe is required to identify the owner.

Frozen implementation mechanism:
- add one narrow call-site transport at `Game+0x16B056`;
- during the existing pending Normal continuation only, capture Gothic's exact direction string/current enum on synthetic Raise;
- on the immediately following stored Action1 Hit, substitute that captured native direction and restore the matching Navigation current-animation direction before Gothic `GetAniName` runs;
- otherwise pass unchanged.

No filename parsing, copied direction classifier, target/orientation mutation, resource-query rewrite, Speed change, or Collision change.
