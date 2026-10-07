# Bad Block Skip — Pierce / Hack Exclusion Validation

**Status:** CLOSED — exclusion supported / EV-451
**Mode:** bounded observation-only research-DLL implementation + runtime validation
**Frozen by:** User + Normal Chat, 2026-10-07
**Launch base:** `development @ a4ab052f0150980384af094d706ceca822a0b645`
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`

## Purpose

Challenge the current first-release exclusion of:
- `gEAction_PierceAttack = 11`;
- `gEAction_HackAttack = 14`;

before the proven Action4/5/10 player protector is cleaned for production.

This task does **not** change the accepted EV-449–EV-450 protector.

## Frozen observation seam

Use the already-proven player timeout call site:

```text
Script_Game +0x633BF
native/current DurationPressedMSecs getter called exactly once
```

Observation predicate:

```text
receiver-owning actor == player
AND factual Routine Action is:
    PierceAttack = 11
    HackAttack   = 14
AND factual phase == Hit
```

For each factual Hit episode:
- emit one `HIT-SEEN` record at first observation, including current raw duration;
- if that same Hit later reaches `raw > 2500`, emit one `OVERDUE` record;
- include factual action, phase and actor/player identity;
- always return **native raw unchanged**.

Outside factual Action11/14 Hit:
- return native raw unchanged;
- rearm only diagnostic episode state.

The probe must never return 2500 for Action11/14 and must never modify attack/block behavior.

## Runtime fixture

Required:
- production `Script_G3AnimationBehaviors.dll` = ON;
- `Script_NewBalance.dll` = ON;
- `Script_G3AB_BadBlockExclusionProbe.dll` = ON;
- existing third-party stack otherwise unchanged from the User's normal intended runtime unless a startup conflict is found.

Explicitly absent:
- `Script_G3AB_BadBlockResearch.dll`;
- `Script_G3AB_BadBlockResearch_Control.dll`;
- unrelated G3AB diagnostic products.

Coexistence is explicitly authorized because production G3AB does not own `Script_Game +0x633BF` at this checkpoint; the temporary probe is the only owner of this timeout seam.

## Runtime test

For Pierce and Hack separately, deliberately try to reproduce bad skip during Hit, with the held-block timeout already overdue whenever the input route allows it.

Observe:
1. whether the visual attack/movement continuation is abruptly destroyed during Hit;
2. whether a qualifying Action11/14 + Hit + raw>2500 episode is logged.

Interpretation:
- qualifying episode + visible bad skip => exclusion contradicted; stop before lean protector.
- qualifying episode + no bad skip => positive evidence that this action reaches the timeout condition without the demonstrated destructive failure.
- no qualifying episode despite deliberate attempts => negative runtime evidence only; do not call impossibility proven.
- any probe-caused behavior change => invalid test; stop.

Frozen raw filename:
`research/raw/2026-10-07_bad_block_pierce_hack_exclusion_probe.log`

## Exclusions

Do not:
- protect Action11 or Action14;
- broaden protection scope;
- edit production G3AB behavior;
- add NPC intervention;
- alter New Balance;
- add persistent gameplay state;
- modify the shared duration property/timer;
- begin lean-protector cleanup or production integration until this runtime gate is interpreted and closed.


## Preliminary runtime observation — 2026-10-07

With production G3AB + New Balance + the first observe-only exclusion probe:
- User first reproduced the known bad skip visually on Whirl and Quick across the tested weapon routes, confirming the fixture/probe did not suppress the established failure;
- User then attempted Hack and Pierce and could not reproduce bad skip;
- the probe log contained no Action11/14 overdue episode records.

Interpretation:
- in the preliminary build, Hack/Action14 was an extra visual control because that first logger still watched Action11/15; the corrected/refined probe now watches factual Action11/14;
- Pierce produced useful negative evidence but the first logger could not distinguish "Action11 Hit seen below threshold" from "Action11 Hit never observed at this seam";
- therefore observability is refined only: `HIT-SEEN` + optional `OVERDUE`, with raw behavior preserved unchanged.

Correction after the preliminary run:
- the originally remembered Finishing concern came from Hack/Action14 using Finishing-named animation assets;
- factual Hack/Action14 is therefore the correct second exclusion target for this gate;
- true Finishing/Action15 is a rare execution action over knocked-down NPCs and is deferred to a separate small follow-up check after Pierce/Hack.

This correction changes only diagnostic scope; no behavior is modified.


## Final result — EV-451

Refined observe-only run:
- production G3AB ON;
- New Balance ON;
- exclusion probe ON;
- user attempted Pierce and Hack many times near/through the bad-skip timing;
- no visible bad skip could be reproduced for either action;
- probe loaded and installed the exact `Script_Game +0x633BF` seam cleanly;
- zero `HIT-SEEN` records for factual Action11/Action14;
- zero `OVERDUE` records.

The probe always returned native raw duration unchanged.

Interpretation:
- within this tested stack, the timeout seam did not observe factual Pierce/Action11 or Hack/Action14 during Hit despite deliberate attempts;
- this is strong first-release exclusion evidence, especially because the preceding same-fixture run reproduced the known Quick/Whirl failure while the observe-only probe was active;
- do not claim Pierce/Hack can never fail in every possible stack, but no evidence justifies adding either to the first-release protection set.

Disposition:
**CLOSED — KEEP ACTION11/14 EXCLUDED FROM THE V1 PROTECTOR.**

True Finishing/Action15 remains a separate, low-frequency execution-action check.
