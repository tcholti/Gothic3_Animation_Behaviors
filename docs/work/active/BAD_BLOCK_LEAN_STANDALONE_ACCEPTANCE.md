# Bad Block Skip — Lean Standalone Acceptance

**Status:** ACTIVE  
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
