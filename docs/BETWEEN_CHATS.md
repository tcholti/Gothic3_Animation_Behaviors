# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-29

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 collision production integration = CLOSED/PASS
EV-391/EV-392 original Speed Normal/Quick transport = CLOSED STATIC
EV-393/EV-394 family-source evidence = PASS
EV-395 configured Speed + New Balance stamina multiplier preservation = PASS

expanded grouped Speed source = IMPLEMENTED
production source frozen = 642c88a4e6244ae7377ba835507750af7914e2f5
internal expanded-source review = PASS
independent Sprint/Power blocker = CLOSED by runtime causal evidence
Sprint Speed model = inherits Power profile; no separate Sprint prefix
expanded production build/runtime = NEXT
Raise = PAUSED
```

## Sprint evidence

The standalone `Script_SpeedSprintProbe` proved that Goblin, Troll and Sabertooth factual Sprint/Action9 reaches the shared Power Hit caller at `Script_Game+0x47F6C` while the caller passes Action2:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
CurrentActionAfter=9
PowerAttack-named motion
```

Tested compatible bases match ordinary Power within each family:

```text
Goblin       Power 1.0 / Sprint 1.0
Troll        Power 1.5 / Sprint 1.5
Sabertooth   Power 1.0 / Sprint 1.0
```

ADR-0009 therefore freezes Sprint as an intentional Power timing alias for Speed authoring. Do not add `Sprint_BaseSpeed` or rewrite Action2 to Action9.

Authority:

`docs/decisions/ADR-0009-sprint-inherits-power-speed-profile.md`

Probe result:

`docs/archive/investigations/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE_RESULT.md`

## Next at local build PC

First remove:

```text
Script_SpeedSprintProbe.dll
```

Then:

```text
sync development
-> build Script_G3AnimationBehaviors Release
-> deploy production DLL
-> verify built/live SHA equality
-> startup smoke
-> runtime matrix:
   Normal/Quick regression
   Power configured control
   Sprint inherited-Power control where practical
   Pierce/Hack where practical
   SimpleWhirl/Whirl where practical
   unconfigured fallback
   New Balance compatibility sanity
```

Do not begin Raise or reopen collision before expanded Speed acceptance closes.
