# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-06 — EV-444 MovementOverride public cleanup

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains Collision + Speed + Raise stable through EV-433.

## Attack movement current state

Research/architecture: closed through EV-440.  
Production source review: EV-441 PASS.  
Initial local build: EV-442 PASS.

EV-443 runtime mechanism PASS:
- deployment DLL/INI hash identity PASS;
- Hero 2H Normal, Quick, Power, Whirl and Hack;
- Off / 0 / 100 / 300;
- tested both with and without New Balance;
- all cases behaved correctly and differences were clearly visible.

EV-444 pre-release UX cleanup:
```text
<Attack>_Movement
->
<Attack>_MovementOverride
```

Reason: `Power_MovementOverride=Off` makes clear that the **override** is off, not attack movement itself.

Architecture is unchanged:
```text
BehaviorProfiles = config
AttackMovement = stateless movement policy
EngineBridge = one Game+0x16B8B7 hook
```

Shipping INI:
- 97 `_MovementOverride=Off` keys;
- zero legacy `_Movement=` keys;
- simplified movement instructions;
- User-added section separators preserved.

## Active responsibility

`docs/work/active/ATTACK_MOVEMENT_RUNTIME_ACCEPTANCE.md`

Next:
1. Fetch/Pull latest development;
2. rebuild Release Win32 because parser key changed;
3. deploy DLL + INI with accepted PowerShell hash procedure;
4. quick previously-proven 2H sanity:
   - `Power_MovementOverride=Off`
   - `Power_MovementOverride=0`
   - `Power_MovementOverride=300`
5. if that passes, do not repeat EV-443 full matrix; continue broader representative validation.

No source redesign is justified absent contradictory runtime evidence.
