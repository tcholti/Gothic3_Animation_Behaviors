# Gothic 3 Animation Behaviors — Deferred Future Investigations

**Status:** PARKED / NON-ACTIVE  
**Updated:** 2026-09-26

## Purpose

Park potentially useful investigation ideas that are **not current architecture, not active Work, and not commitments to implement anything**. An item may remain here indefinitely or never be pursued.

Opening this file does not reopen a subsystem or change the current validation gate. If an item is deliberately activated later, first recover the smallest relevant source/evidence route and create a bounded research responsibility under the normal feature-development method.

---

## 1. New Balance combat-move distance override

### Why it is parked

Native Gothic 3 attack travel can be influenced by the movement/distance number encoded in an animation filename. New Balance currently also controls combat-move travel in code, so animation-authored distance and New Balance behavior may disagree. There is no current plan to change this; it is recorded only so the mechanism does not need to be rediscovered if the question ever matters.

### Proven starting point

Jackydima source repository:

```text
Jackydima/gothic3sdk
scripts/Script_NewBalance/
```

Start with:

- `CallHook.cpp` — `CombatMoveScale()` and `Hook_CombatMoveScale`.
  - The current code normalizes `m_DirectionVec`, discarding its incoming magnitude, then scales it from `GetCombatMoveLength(...) / animationTime * ATTACK_REACH_MULTIPLIER`.
- `FunctionHook.cpp` — `GetCombatMoveLength()`.
  - Current New Balance assigns action-based combat travel lengths and applies a combat-skill range multiplier.
- `FunctionHook.cpp` — `GetAnimationSpeedModifier()`.
  - New Balance separately changes combat animation speed, so travel and playback timing must be considered together.
- `SharedConfig.cpp` / `Script_NewBalance.cpp` — `ATTACK_REACH_MULTIPLIER` / `AttackReachMultiplier`.
- Useful history anchor: commit `33624cb6105cc1cfba989f5a2bfa774234fcce4f` — `Script_Newbalance: Update Combatmovelength for Combat moves`.

### If ever reopened

Begin with a small native-vs-New-Balance A/B using the **same unchanged animation asset** and measure actual actor displacement during the attack. Only then decide whether filename-authored distance should be restored, combined with New Balance scaling, exposed as configuration, or left alone.

Keep this independent from authored collision timing/source ownership unless evidence later proves a real coupling.

---

## 2. New Balance Recover cancellation / premature Recover exit

### Why it is parked

Power-attack Recover animations are already relatively easy to interrupt in native Gothic 3. With the current New Balance version they can appear substantially more sensitive, and the User has observed cases where Recover seems to end early even while **all controls are untouched**.

The earlier observation that slight mouse movement can coincide with a skip is therefore **not a causal conclusion**. After attacks, mouse movement normally moves the camera rather than directly turning the Hero, and the no-input observation means future work must not begin from a mouse-turn hypothesis.

There is no current plan to change this behavior.

### Proven starting point

Jackydima source repository:

```text
Jackydima/gothic3sdk
scripts/Script_NewBalance/
```

Start with:

- History anchor: commit `ea7d4bc4e76549874e75d751327e5692301ff818` — `fixed canceling of forced recovery animations from other states`.
- `CallHook.cpp` — `EvadeMechanic()`.
  - The recovery-cancellation change widened eligibility around routine states and the current implementation uses a broad `_Loop` state test rather than a per-Recover-animation policy.
- `FunctionHook.cpp` — `OnPlayerSecondaryAction_NB`, `OnPlayerGameKeyPressed`, and `PS_Melee_Loop`.
  - These are useful entry points for custom input/state transitions around melee behavior.
- `FunctionHook.cpp` — `GetAnimationSpeedModifier()`.
  - Check whether timing changes make a native Recover boundary appear earlier even without an explicit cancel.
- Trace uses of `ClearInputEntry`, `Routine.SetState`, `FullStop`, queued actions, and PowerAttack state/phase transitions around Recover.

### If ever reopened

First reproduce with an identical asset in a strict A/B:

```text
native / New Balance
+ same PowerAttack animation
+ deliberately no player input
```

Trace at minimum:

```text
Action
Routine current state/task
animation phase
StatePosition
current movement animation
input/queued-action state
SetState / FullStop / ClearInputEntry transitions
animation-speed modifier
```

Separate these possible causes before proposing any change:

1. normal native Recover completion/interruptibility;
2. animation-speed/timing change;
3. automatic routine/task/state transition;
4. queued or stale input consumption;
5. explicit New Balance input-driven cancellation;
6. another New Balance/native interaction not yet identified.

Do not assume the no-input symptom and the known forced-recovery-cancel feature are the same mechanism until a trace proves it.

---

## Boundaries

These two items are **optional future research only**. They are not part of the current New Balance collision compatibility gate, do not change `CollisionLifecycleGuard`/C1-R1, and do not reopen or redefine the separately paused `AttackContinuationProtection` responsibility.
