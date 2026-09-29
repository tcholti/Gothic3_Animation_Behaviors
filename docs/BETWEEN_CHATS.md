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
independent review = BLOCKED on Sprint/Power shared-call isolation
Sprint classification = PLAUSIBLE BUT UNPROVEN
expanded production build = PAUSED
Raise = PAUSED
CURRENT = Script_SpeedSprintProbe local build/runtime gate
```

## Why build is paused

Static binary evidence shows factual Action9 is recognized on the shared Power routine before the later Hit-speed consumer:

```text
+0x47CE2..+0x47CEB  current action 9 recognized, shared continuation
+0x47F67            EAX=2
+0x47F6C            call +0x42A0
```

Native `+0x42A0` separately checks current Action9. Therefore current Action9 and passed Power/2 may coexist. The expanded G3AB hook maps passed `2` to Power, so configured Power could affect Sprint if the factual Action9 survives to the Hit call.

## Current probe

Active task:

`docs/work/active/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE.md`

Tool source:

```text
tools/Script_SpeedSprintProbe/CMakeLists.txt
tools/Script_SpeedSprintProbe/Script_SpeedSprintProbe.cpp
```

Probe properties:

```text
hooks only Script_Game+0x47F6C
captures passed EAX and current PropertyAction
calls live +0x42A0 exactly once with original EAX
returns compatible speed unchanged
player-only logging
no production behavior change
```

Expected output:

`SpeedSprintProbe.log`

## Next at local build PC

```text
sync development
-> build Script_SpeedSprintProbe Release
-> deploy diagnostic DLL beside existing accepted live G3AB/NewBalance/AttackCollision stack
-> ordinary Power attacks
-> factual Sprint attacks
-> provide SpeedSprintProbe.log
```

Decision:

```text
PassedAction=2 + CurrentActionBefore=9 + RequestedPhase=Hit during Sprint
-> shared Sprint/Power transport confirmed
-> make narrow Sprint non-interference correction before expanded production build

Power reaches probe but Sprint never does with current Action9
-> independent blocker not reproduced
-> resume expanded production build/runtime acceptance
```

Archived review:

`docs/archive/investigations/SPEED_EXPANDED_SCOPE_LIGHT_INDEPENDENT_REVIEW_AND_SPRINT_RESEARCH_RESULT.md`

Do not begin Raise or speculative Sprint authoring support before this gate closes.
