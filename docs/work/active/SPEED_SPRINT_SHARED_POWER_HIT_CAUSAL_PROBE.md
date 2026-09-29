# Speed Sprint Shared-Power Hit Causal Probe

**Status:** ACTIVE  
**Task class:** Bounded diagnostics-only implementation + runtime evidence  
**Branch:** `development`

## Purpose

Resolve the single blocker found by the light independent expanded-Speed review: determine whether factual Sprint / `gEAction_SprintAttack` (Action9) reaches the shared Power Hit-speed caller at `Script_Game+0x47F6C` while the caller still passes `EAX=2` / Power.

This probe exists only to decide Sprint non-interference and the safety of the expanded Power hook. It must not change gameplay behavior.

## Frozen evidence

Pinned Script_Game static evidence establishes:

```text
Script_Game+0x47CE2  reads current PropertyAction
+0x47CE8             compares it with Action9
+0x47CEB             Action9 remains on the shared continuation at +0x47D02

Script_Game+0x47F67  hard-sets EAX=2
+0x47F6C              calls GetAnimationSpeedModifier (+0x42A0), Hit route
```

Native `Script_Game+0x42A0` independently reads the entity current action and contains an explicit Action9 branch at `+0x431D..+0x4329`.

Pinned New Balance replaces `+0x42A0` and branches on the action passed in EAX; its Sprint branch therefore does not by itself prove which Script_Game caller carries factual Sprint playback.

Current expanded production source `642c88a4e6244ae7377ba835507750af7914e2f5` hooks `+0x47F6C`, receives passed `EAX=2`, and maps it to the Power profile. If factual current Action9 is still present there, configured Power can incorrectly compose Sprint unless the transport/policy distinguishes it.

## Diagnostic responsibility

Create a standalone diagnostic DLL only. Do not modify `src/Script_G3AnimationBehaviors` production behavior.

Hook only:

```text
Script_Game+0x47F6C
```

Use the existing SDK `mCCallHook` + `mCCaller` pattern to preserve the original call semantics:

```text
capture passed EAX action
-> capture entity current PropertyAction before live call
-> call live Script_Game+0x42A0 exactly once with the original passed EAX
-> capture entity current PropertyAction after live call
-> log evidence
-> return the live compatible speed unchanged
```

Player-only logging is sufficient.

Log at minimum:

```text
PassedAction
CurrentActionBefore
RequestedPhase
CompatibleSpeed
CurrentActionAfter
CurrentMovementAni (observational only)
```

The probe must not:

```text
compose or override speed
change EAX before the live call except restoring the original captured value
change current action/state
hook +0x42A0 entry
hook any other Speed caller
modify collision or Raise behavior
```

## Runtime test

Run with the currently accepted live stack where the old production G3AB does **not** own `+0x47F6C`:

```text
Script_G3AnimationBehaviors.dll  (existing accepted six-site Speed build)
Script_NewBalance.dll
Script_AttackCollision.dll
Script_SpeedSprintProbe.dll
```

Perform:

1. several ordinary Power attacks;
2. several factual Sprint attacks;
3. if practical, repeat with different equipped melee families that use Sprint.

## Decision rule

### CONFIRMED SHARED SPRINT HIT

If an actual Sprint produces:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
```

then `+0x47F6C` is a shared Power/Sprint transport and the current expanded production hook requires a narrow Sprint non-interference correction before build acceptance.

Preferred correction direction is **not** to change the live compatible owner's input. Preserve the caller's original EAX=2 to `+0x42A0`, then prevent unsupported Sprint from being composed as configured Power. Exact implementation is decided only after evidence.

### POWER ONLY AT HIT CALL

If factual Sprint never reaches this caller with current Action9, while ordinary Power does, the Work concern is not reproduced and the expanded Power hook may proceed subject to the rest of acceptance.

### AMBIGUOUS

If Sprint reaches the caller but current action has already changed, or evidence is inconsistent, stop and report the exact sequence. Do not infer a fix.

## Build boundary

Source/static work may be prepared away from the game PC. Runtime acceptance requires the User's local build/game environment.

Do not build or claim runtime evidence until the User performs the probe locally.
