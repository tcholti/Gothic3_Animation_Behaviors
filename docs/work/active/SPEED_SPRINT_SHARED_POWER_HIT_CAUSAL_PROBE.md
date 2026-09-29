# Speed Sprint Shared-Power Hit Causal Probe

**Status:** SOURCE IMPLEMENTED / STATIC PASS / LOCAL BUILD+RUNTIME PENDING  
**Task class:** Bounded diagnostics-only implementation + runtime evidence  
**Branch:** `development`

## Purpose

Resolve the single blocker found by the light independent expanded-Speed review: determine whether factual Sprint / `gEAction_SprintAttack` (Action9) reaches the shared Power Hit-speed caller at `Script_Game+0x47F6C` while the caller still passes `EAX=2` / Power.

This probe exists only to decide Sprint non-interference and the safety of the expanded Power hook. It does not change gameplay behavior.

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

## Implemented diagnostic

Standalone tool:

```text
tools/Script_SpeedSprintProbe/CMakeLists.txt
tools/Script_SpeedSprintProbe/Script_SpeedSprintProbe.cpp
```

Root CMake registers the tool only under `G3AB_BUILD_TOOLS`.

The probe owns exactly one hook:

```text
Script_Game+0x47F6C
```

Runtime sequence:

```text
capture passed EAX action
-> capture entity current PropertyAction before live call
-> restore original passed EAX into mCCaller
-> call live Script_Game+0x42A0 exactly once
-> capture current PropertyAction after live call
-> log player-only evidence
-> return compatible speed unchanged
```

Logged fields:

```text
PassedAction
CurrentActionBefore
RequestedPhase
CompatibleSpeed
CurrentActionAfter
CurrentMovementAni
```

Static review of the probe source confirms:

```text
no production source change
no speed composition
no state/action mutation
no +0x42A0 entry hook
no second Speed caller hook
original EAX preserved for live compatible owner
live compatible result returned unchanged
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

Expected log:

```text
SpeedSprintProbe.log
```

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

## Current gate

**NEXT = local build of `Script_SpeedSprintProbe`, deploy diagnostic DLL only, then runtime Power/Sprint observation.**

Do not build/deploy the expanded production Speed source until this probe closes.
