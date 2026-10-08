# Bad Block Skip — Production Integration

**Status:** ACTIVE  
**Mode:** bounded production source integration  
**Frozen by:** User + Normal Chat, 2026-10-08  
**Launch base:** `development @ db9463bc341f5d7be367f74ff5631a80b294d154`  
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`

## Purpose

Integrate the EV-450 / EV-453 proven lean bad-block protection into production `Script_G3AnimationBehaviors.dll`.

Do not redesign, broaden, or add configuration.

## Proven production rule

At exact player timeout call seam `Script_Game +0x633BF`:

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

## Production placement

`EngineBridge` remains sole owner of production Gothic hooks.

Integrate the minimum directly into `EngineBridge.cpp`:
- one `mCCallHook` owner;
- current getter-slot pointer;
- lean evaluator;
- adapter that calls native/current getter once;
- exact seam install with the same call-site guard used by the accepted standalone.

No new subsystem is required.

## Explicit exclusions

Do not add:
- generic QuickAttack/Action3;
- Pierce/Action11;
- Hack/Action14;
- Finishing/Action15;
- Normal/Power/SimpleWhirl/Sprint;
- NPC handling;
- persistent timer state;
- actor maps/tokens;
- logging or diagnostics;
- INI option;
- global getter/IAT mutation;
- global FullStop/SetState suppression;
- collision-guardian coupling.

## Validation

Before runtime:
1. source diff review against accepted standalone;
2. build production `Script_G3AnimationBehaviors.dll`;
3. deploy production build;
4. remove standalone `Script_G3AB_BadBlockProtector.dll`;
5. verify New Balance unchanged;
6. verify no old bad-block research/probe products are live.

Then final release-candidate visual smoke:
- startup;
- repeated Quick / full Whirl bad-skip attempts;
- brief representative collision/speed/raise/movement sanity;
- normal non-protected combat/block behavior sanity.

No further bad-skip research is planned unless contradictory runtime evidence appears.
