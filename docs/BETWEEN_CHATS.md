[Reading 20 lines from start (total: 48 lines, 28 remaining)]

# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — EV-451 Pierce/Hack exclusion closed

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## Bad-block first-release state

EV-449–EV-450:
- proven protected set = QuickAttackR(4), QuickAttackL(5), WhirlAttack(10), factual Hit, player, raw>2500;
- stateless branch-local return 2500 is causally sufficient.

EV-451:
- production G3AB + New Balance + observe-only timeout probe;
- repeated Pierce/Action11 and Hack/Action14 attempts;
- no visual bad skip;
- zero factual Action11/14 `HIT-SEEN` and zero `OVERDUE` at `Script_Game +0x633BF`;

[executed on device: DESKTOP-1HB54C3 (ee009201-9ef7-41b1-ae5c-82d3de3789be)]
[Reading 28 lines from line 20 (total: 48 lines, 0 remaining)]

- keep Action11 and Action14 excluded from v1 protector.

Archived task:
`docs/archive/investigations/BAD_BLOCK_PIERCE_HACK_EXCLUSION_VALIDATION.md`

Archived artifact:
`research/archive/2026-10-07_bad_block_pierce_hack_exclusion_probe.log`

## Next gate

Run one separate, small true Finishing/Action15 check.

Reason:
Hack/Action14 can use Finishing-named animation assets, which caused the earlier memory conflation. True Finishing/Action15 is a rare execution action performed over knocked-down NPCs.

Use:
- production G3AB ON;
- New Balance ON;
- observation-only Action15 logger at the same timeout seam;
- no Action15 protection.

User can use god mode, knock down NPCs, hold RMB close to the bad-skip threshold, then execute true finishing attacks.

If no contradiction:
-> lean diagnostics-free standalone protector
-> visual acceptance
-> production G3AB integration
-> final visual release-candidate smoke.

[executed on device: DESKTOP-1HB54C3 (ee009201-9ef7-41b1-ae5c-82d3de3789be)]