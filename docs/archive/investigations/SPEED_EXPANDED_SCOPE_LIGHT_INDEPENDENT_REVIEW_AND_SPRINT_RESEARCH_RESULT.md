# Speed Expanded Scope — Light Independent Review and Sprint Research — Result

**Status:** CLOSED / BLOCKED ON SPRINT NON-INTERFERENCE EVIDENCE  
**Date:** 2026-09-29  
**Production source reviewed:** `642c88a4e6244ae7377ba835507750af7914e2f5`

## Verdict

The independent read-only review found the expanded implementation otherwise clean, but returned **BLOCKED** for pre-build acceptance on one material question: the newly hooked Power Hit caller `Script_Game+0x47F6C` may also execute during factual Sprint / Action9.

This is not an observed runtime regression and does not invalidate the Speed v2 architecture.

## Confirmed implementation review

The review confirmed:

```text
original six Normal/Quick callers unchanged
nine newly added callers are direct +0x42A0 Hit consumers
Hack callers use EAX=14
Pierce callers use EAX=11
Power +0x47F6C uses EAX=2
SimpleWhirl dynamic caller is the Action6 path
Whirl caller uses EAX=10
Power Raise +0x47D51 is not hooked
common mCCaller/live +0x42A0 composition remains ABI/x87 compatible
grouped profile parser and fail-closed behavior conform to ADR-0008
no bounded collision/Raise drift found
```

## Sprint blocker

Pinned Script_Game evidence shows:

```text
+0x47CE2  reads current PropertyAction
+0x47CE8  compares with Action9
+0x47CEB  Action9 jumps to the shared continuation at +0x47D02

+0x47F67  mov eax,2
+0x47F6C  call +0x42A0   # Hit-speed consumer hooked by expanded G3AB
```

Native `+0x42A0` also reads current PropertyAction and contains an explicit Action9 branch at `+0x431D..+0x4329`.

Therefore passed caller action `2` and factual current actor action `9` can coexist conceptually on this route. The expanded G3AB hook currently receives only the passed EAX value and maps `2` to configured Power.

The independent review could not statically certify that current Action9 remains present at the later Hit call across the whole continuation. Sprint classification is therefore:

```text
PLAUSIBLE BUT UNPROVEN
```

## New Balance nuance

Pinned New Balance `GetAnimationSpeedModifier` reads the action supplied through EAX and has its own explicit Sprint branch. This policy proves neither the Script_Game carrier nor Sprint isolation. The live compatible owner must continue receiving the caller's original EAX unless separate evidence justifies otherwise.

## Follow-up

The smallest next step is the bounded diagnostic task:

`docs/work/active/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE.md`

Observe only `Script_Game+0x47F6C` during actual Power and Sprint execution, logging:

```text
PassedAction
CurrentActionBefore
RequestedPhase
CompatibleSpeed
CurrentActionAfter
```

Do not build the expanded production Speed source until this non-interference question is resolved.
