# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-29

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
initial Speed v2 Normal/Quick runtime proof = PASS through EV-395
expanded Speed source = 642c88a4e6244ae7377ba835507750af7914e2f5
expanded user-facing scope = Normal, Quick, Power, Pierce, Hack, SimpleWhirl, Whirl
internal expanded-source static review = PASS
independent review Sprint/Power blocker = CLOSED by runtime causal probe
Sprint Speed authoring = inherits Power profile on proven shared Hit route
CURRENT = expanded production local build/deploy/runtime acceptance
Raise behavior = PAUSED until Speed closes
main = FROZEN
```

Primary task:

`docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`

Sprint authority:

`docs/decisions/ADR-0009-sprint-inherits-power-speed-profile.md`

Sprint probe result:

`docs/archive/investigations/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE_RESULT.md`

## Sprint closure

Runtime diagnostics at `Script_Game+0x47F6C` proved on Goblin, Troll and Sabertooth:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
CurrentActionAfter=9
CurrentMovementAni=*PowerAttack*
```

The tested families also showed matching compatible bases between ordinary Power and Sprint:

```text
Goblin       1.0 / 1.0
Troll        1.5 / 1.5
Sabertooth   1.0 / 1.0
```

Therefore Sprint deliberately inherits configured Power timing. No Sprint-specific profile key or source correction is required.

## Immediate route at local build PC

Remove the diagnostic DLL first:

```text
Script_SpeedSprintProbe.dll
```

Then:

```text
sync development
-> build Script_G3AnimationBehaviors Release
-> deploy the production DLL
-> verify built/live SHA equality
-> startup smoke
-> bounded expanded-Speed runtime matrix
```

Runtime matrix:

```text
Normal + Quick regression
Power configured-speed control
Sprint inherited-Power control where practical
Pierce / Hack where visually practical
SimpleWhirl / Whirl where visually practical
unconfigured fallback
New Balance compatibility sanity
```

## Still frozen

```text
NO +0x42A0 entry hook
NO rewrite of live compatible-owner EAX
NO Sprint-specific Speed keys absent contradictory evidence
NO Raise implementation until Speed closes
NO collision redesign absent contradictory evidence
NO promotion to main before agreed integrated checkpoint
```
