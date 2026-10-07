# Bad Block Skip — True Finishing / Action15 Exclusion Validation

**Status:** ACTIVE
**Mode:** bounded observation-only runtime validation
**Frozen by:** User + Normal Chat, 2026-10-07
**Launch base:** `development @ 79a5c9e6b5bd2864c55c78a7e631579c42794a54`
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`

## Purpose

Check true `gEAction_FinishingAttack = 15` separately from Hack/Action14.

Reason:
Hack can use Finishing-named animation assets, which caused the earlier memory conflation. True Action15 is the rare execution action performed over a knocked-down NPC.

This task does not change the EV-450 protector and does not protect Action15.

## Observation seam

`Script_Game +0x633BF`, using the already-proven native DurationPressedMSecs getter transport.

For the player:
```text
if factual Routine Action == FinishingAttack(15)
AND factual phase == Hit
-> first observation logs HIT-SEEN with current raw
-> if same Hit later reaches raw > 2500, log OVERDUE
-> always return native raw unchanged

otherwise
-> return native raw unchanged
```

No timer mutation, no clamp, no gameplay token, no production G3AB behavior edit.

## Runtime fixture

- production `Script_G3AnimationBehaviors.dll` ON;
- `Script_NewBalance.dll` ON;
- `Script_G3AB_BadBlockExclusionProbe.dll` ON;
- old protection/control research DLLs OFF;
- existing third-party stack otherwise unchanged.

## Runtime test

User may use god mode for convenience.

1. knock down one or more NPCs so true execution is available;
2. hold RMB near the known bad-skip timeout;
3. while positioned for the execution, hold LMB so Gothic selects the true finishing action;
4. repeat several times at deliberately aggressive timeout timings;
5. observe whether the execution/attack continuation is visibly destroyed during Hit.

Interpretation:
- `HIT-SEEN Action15` + `OVERDUE` + visible bad skip => Action15 exclusion contradicted.
- `HIT-SEEN Action15` + `OVERDUE` + no bad skip => direct evidence supporting exclusion.
- `HIT-SEEN Action15` but no `OVERDUE` => Action15 factual Hit reached the seam but not the dangerous timing.
- no Action15 `HIT-SEEN` despite true executions => the tested timeout seam did not observe factual Action15 Hit; negative evidence only.

Frozen raw filename:
`research/raw/2026-10-07_bad_block_finishing_exclusion_probe.log`

After this gate, absent contradiction:
lean diagnostics-free standalone protector -> visual acceptance -> production G3AB integration -> final visual release-candidate smoke.
