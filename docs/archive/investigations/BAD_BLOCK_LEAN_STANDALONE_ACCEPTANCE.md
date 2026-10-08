# Bad Block Skip — Lean Standalone Acceptance

**Status:** CLOSED — runtime visual acceptance PASS / EV-453  
**Mode:** bounded diagnostics-free standalone implementation + visual runtime acceptance  
**Frozen by:** User + Normal Chat, 2026-10-07  
**Launch base:** `development @ ef6635470325f670ab24721c095d28c397d84836`  
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`

## Purpose

Validate the exact minimum EV-450 mechanism in a diagnostics-free standalone DLL before production G3AB integration.

This task does not reopen bad-block research.

## Frozen behavior

At `Script_Game +0x633BF`:

```text
call native/current DurationPressedMSecs getter exactly once

if raw > 2500
AND receiver-owning actor == player
AND factual Routine Action in:
    QuickAttackR = 4
    QuickAttackL = 5
    WhirlAttack  = 10
AND factual phase == Hit
-> return 2500 for this call only

otherwise
-> return raw
```

## Required implementation shape

Standalone target:
`Script_G3AB_BadBlockProtector.dll`

Keep only:
- exact six-byte call-site ownership at `Script_Game +0x633BF`;
- current getter-slot lookup;
- one native getter call with the original receiver;
- player identity check;
- factual Action4/5/10 check;
- factual Hit-phase check;
- branch-local `2500` return for qualifying calls.

Do not include:
- log file;
- diagnostic banners;
- A/B mode;
- diagnostic episode state;
- Pierce/Hack/Finishing observers;
- actor/timer maps;
- gameplay tokens;
- NPC handling;
- global getter/IAT mutation;
- global FullStop/SetState suppression;
- collision-guardian coupling;
- production G3AB edits.

## Runtime fixture

Required:
- production `Script_G3AnimationBehaviors.dll` ON;
- `Script_NewBalance.dll` ON;
- `Script_G3AB_BadBlockProtector.dll` ON;
- old bad-block research/control/exclusion DLLs OFF;
- existing third-party stack otherwise unchanged.

Production G3AB does not own `Script_Game +0x633BF` at this checkpoint, so this coexistence is the intended acceptance fixture.

## Runtime acceptance

Visual-only; no diagnostic log is expected.

User deliberately attempts the known failure on:
- Quick attacks across representative weapon routes;
- full Whirl on 2H/Staff.

Primary failure signature:
- abrupt attack movement/continuation stop during Hit.

Secondary signature where practical:
- stale offensive collision after the visible attack.

Acceptance:
- repeated attempts do not reproduce bad skip;
- no startup/load crash;
- normal non-protected attacks remain behaviorally normal.

If this passes:
integrate the same minimum into production `Script_G3AnimationBehaviors.dll`, then remove the standalone protector and run the final release-candidate visual smoke.


## End-of-day checkpoint — 2026-10-07

Implementation checkpoint:
`development @ bc7d341abd71dc064e6be6faf88d51dff6d62eb4`

Source review:
- diagnostics-free standalone source PASS;
- no logger/A-B/episode/exclusion-observer code;
- only factual Action4/5/10 + Hit can return `2500`;
- native/current getter is called exactly once.

Built/deployed protector:
`Script_G3AB_BadBlockProtector.dll`
`SHA256 6A04B4AB4529EF2C7FD6BEB6450572BD504AF188FB3BD45FBCFD116E5AB5A03A`

Live acceptance fixture left deployed for next session:
- `Script_G3AB_BadBlockProtector.dll` = `6A04B4AB4529EF2C7FD6BEB6450572BD504AF188FB3BD45FBCFD116E5AB5A03A`;
- production `Script_G3AnimationBehaviors.dll` = `4F05583E74F0B2F49FBC3682DB244EDE86C277BA810DBFE0C985859D69A32B68`;
- `Script_NewBalance.dll` = `0C06C35F294F2FDF3011AC82FF506CA422947B6908CE2530AA1B057A243A6F88`;
- old bad-block research/control/exclusion products absent.

Runtime acceptance has **not started yet**.

Exact next step next session:
1. launch Gothic 3 to the main menu and exit normally; no log is expected, so successful startup/exit is the diagnostics-free startup gate;
2. if startup is clean, repeatedly try to reproduce known bad skip with Quick attacks and full Whirl;
3. if visual acceptance passes, integrate this same minimum into production G3AB; do not redesign.


## Final result — EV-453

Accepted standalone source checkpoint:
`development @ bc7d341abd71dc064e6be6faf88d51dff6d62eb4`

Accepted standalone binary:
`Script_G3AB_BadBlockProtector.dll`
`SHA256 6A04B4AB4529EF2C7FD6BEB6450572BD504AF188FB3BD45FBCFD116E5AB5A03A`

Runtime fixture:
- production G3AB ON;
- New Balance ON;
- lean standalone protector ON;
- old bad-block research/control/exclusion DLLs OFF.

Startup acceptance:
- Gothic 3 launched and exited normally with the diagnostics-free protector active.

User runtime acceptance:
- more than 30 deliberate bad-skip reproduction attempts in total;
- full Whirl exercised;
- Quick attacks exercised across all weapon types;
- no bad skip could be reproduced.

Result:
**PASS — LEAN DIAGNOSTICS-FREE STANDALONE PROTECTOR ACCEPTED.**

Production integration is authorized only as the same proven minimum. Do not redesign or broaden scope.
