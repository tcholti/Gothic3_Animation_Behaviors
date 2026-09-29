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
expanded Speed scope = Normal, Quick, Power, Pierce, Hack, SimpleWhirl, Whirl
expanded production source = 642c88a4e6244ae7377ba835507750af7914e2f5
internal expanded-source static review = PASS
independent expanded-source review = BLOCKED on one Sprint/Power non-interference question
Sprint transport classification = PLAUSIBLE BUT UNPROVEN
CURRENT = build/run standalone Sprint shared-Power Hit causal probe
expanded production build/deploy = PAUSED until probe closes
Raise behavior = PAUSED until Speed closes
main = FROZEN
```

Primary implementation task:

`docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`

Current causal-probe task:

`docs/work/active/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE.md`

Archived independent review:

`docs/archive/investigations/SPEED_EXPANDED_SCOPE_LIGHT_INDEPENDENT_REVIEW_AND_SPRINT_RESEARCH_RESULT.md`

## Independent-review finding

The new Power Hit caller is:

```text
Script_Game+0x47F67  mov eax,2
Script_Game+0x47F6C  call +0x42A0
```

Earlier in the same shared routine:

```text
+0x47CE2  reads current PropertyAction
+0x47CE8  compares with Action9 / Sprint
+0x47CEB  Action9 follows the shared continuation at +0x47D02
```

Native `+0x42A0` also has an explicit current-Action9 branch at `+0x431D..+0x4329`.

Therefore current actor action 9 and passed speed action 2 may coexist at the shared Power Hit-speed path. The expanded G3AB hook currently maps passed action 2 to the configured Power profile, so Sprint non-interference must be proven before production build acceptance.

## Current diagnostic

Standalone tool only:

```text
tools/Script_SpeedSprintProbe
```

It hooks only `Script_Game+0x47F6C`, calls the live `+0x42A0` compatible owner once with the original EAX, logs the factual state, and returns the speed unchanged.

Log fields:

```text
PassedAction
CurrentActionBefore
RequestedPhase
CompatibleSpeed
CurrentActionAfter
CurrentMovementAni
```

## Immediate route at local build PC

Do **not** build the expanded production DLL first.

```text
sync development
-> build target Script_SpeedSprintProbe Release
-> deploy Script_SpeedSprintProbe.dll beside the currently accepted live stack
-> run several ordinary Power attacks
-> run several factual Sprint attacks
-> upload/push SpeedSprintProbe.log
```

Acceptance discriminator:

```text
Sprint log shows PassedAction=2 + CurrentActionBefore=9 + Hit
-> shared Sprint/Power Hit transport CONFIRMED
-> implement narrow Sprint non-interference correction before expanded production build

Sprint never reaches +0x47F6C with current Action9, Power does
-> Work blocker not reproduced
-> proceed to expanded production build/runtime gate
```

## Still frozen

```text
NO speculative Sprint authoring support
NO change to live compatible-owner input
NO +0x42A0 entry hook
NO Raise implementation while Speed is open
NO collision redesign absent contradictory evidence
NO promotion to main before agreed integrated checkpoint
```
