# Speed Sprint Shared-Power Hit Causal Probe — Result

**Status:** CLOSED / PASS  
**Date:** 2026-09-29  
**Branch:** `development`

## Question

Does factual Sprint / `gEAction_SprintAttack` / Action9 reach the shared Power Hit-speed caller at `Script_Game+0x47F6C` while that caller passes `EAX=2` / Power?

## Result

**YES — CONFIRMED SHARED SPRINT/POWER HIT TRANSPORT.**

The diagnostics-only `Script_SpeedSprintProbe.dll` hooked only `Script_Game+0x47F6C`, called the live `Script_Game+0x42A0` owner exactly once with the original EAX, returned the compatible speed unchanged, and logged factual state.

The final probe build/live SHA256 matched:

```text
660BF8A6C2381B4FFE0BB7819CD397404F4A72C436D95787C3392034A3063F94
```

## Runtime evidence

### Goblin / equipped 1H

The clean goblin run repeatedly observed:

```text
Entity=BlackGoblin
PassedAction=2
CurrentActionBefore=9
SprintBefore=true
RequestedPhase=Hit
CurrentActionAfter=9
SprintAfter=true
CurrentMovementAni=Goblin_..._PowerAttack_...
CompatibleSpeed=1.000000
```

The same run also captured ordinary Goblin Power with current Action2 and compatible speed `1.000000`.

### Troll / Fist

Repeated BlackTroll Sprint calls showed factual Action9 before and after the call, passed Action2, Hit phase, Power-named motion, and compatible speed `1.500000`.

Ordinary Troll Power calls in the same run also returned `1.500000`.

### Sabertooth / Fist

Repeated Sabertooth Sprint calls showed factual Action9 before and after the call, passed Action2, Hit phase, Power-named motion, and compatible speed `1.000000`.

Transformed-player Sabertooth Power controls returned the same `1.000000` base.

### Zombie/Mummy control

Mummy using Zombie animations repeatedly reached the same Power caller with current Action2 and Power-named motion. No Action9 event was observed for this control. This confirms ordinary Power transport but does not establish whether Sprint is available for that animation family.

## Interpretation

The independent review's static concern was real: current Action9 and passed Action2 do coexist at `+0x47F6C`.

However, the runtime evidence and animation-authoring requirement show that this is not an accidental Power/Sprint collision requiring suppression. Sprint intentionally reuses the Power Hit-speed route and Power-named animation. On all three tested Sprint families, the compatible base also matches ordinary Power within that family.

Therefore Speed authoring should treat Sprint as inheriting Power timing rather than expose a separate Sprint profile.

This decision is frozen in:

`docs/decisions/ADR-0009-sprint-inherits-power-speed-profile.md`

## Production consequence

No production source correction is required for Sprint timing.

The frozen expanded production source:

```text
642c88a4e6244ae7377ba835507750af7914e2f5
```

already receives Action2 at the shared caller and applies the Power profile. That is now the intended behavior.

The live compatible owner's input must remain unchanged; do not rewrite caller Action2 to Action9.

## Provenance

Runtime logs:

```text
research/raw/2026.09.29_sprint_probe_goblin.log
research/raw/2026.09.29_sprint_probe_troll_sabertooth_zombie.log
```

Final probe built/live SHA256:

```text
660BF8A6C2381B4FFE0BB7819CD397404F4A72C436D95787C3392034A3063F94
```

## Disposition

- **PASS — SHARED SPRINT/POWER HIT TRANSPORT CONFIRMED.**
- **PASS — SPRINT INHERITS POWER SPEED PROFILE FOR AUTHORING.**
- **NO SPRINT-SPECIFIC SPEED CODE OR INI KEYS REQUIRED.**
- Independent pre-build blocker is closed.
- Next gate: remove the diagnostic DLL, then build/deploy the expanded production source and run the bounded expanded-Speed runtime acceptance matrix.
