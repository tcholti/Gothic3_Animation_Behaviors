# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-22

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Frozen source

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Frozen collision source:
`f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Diagnostic SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Behavior SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

No source change is authorized absent contradictory evidence.

## Focused raw8 acceptance

Only item 6 remains open:

```text
marked pending opportunity
-> factual generation replacement
-> old opportunity closes
-> next relevant human raw8 attack is genuinely unmarked
-> no intervening newly marked FIST opportunity
-> unmarked route remains native
```

All other §14 focused items PASS through EV-361.

## EV-363 result

The combat timing is now good enough.

Two exact sequences were captured:

```text
P1-left marked OPEN
-> C1_GENERATION_REPLACED close
-> next relevant P0-right attack
-> zero intervening raw8 opens
```

But the P0-right runtime motion was still marked.

Intended unmarked motion:
`Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot`

Observed across the run:
- 60 ATTACK_OWNERSHIP records;
- all 60 `MarkerPresent=1`;
- all 60 `FistMarkers=1`;
- zero `MarkerPresent=0`;
- P0-right opened raw8 opportunities and therefore was behaviorally marked.

P1-left was also marked as intended.

Therefore item 6 remains open solely because the live P0-right asset did not reflect the intended marker removal.

The run also contained two successful generic equipped lifecycle repairs for Orc raw52 weapon sources, each group7 -> group5 with `REPAIRED_TO_ITEM_EQUIPPED`; no repair divergence was observed.

## Next responsibility

Before another combat attempt, verify that the **actual game-loaded** P0-right motion resolves:

```text
MarkerPresent=0
FistMarkers=0
Raw8Fist=<none>
SuppressNative=0
```

Do not change source code.

Once P0-right is truly unmarked, repeat the same group-combat setup. The interruption timing already succeeded twice, so no new test design is required.

After item 6 PASS:
1. close focused permanent raw8 acceptance;
2. begin `COLLISION_TEST_PLAN.md` §3.8 comprehensive final-source campaign.

Large-log provenance:
- archived raw: `research/archive/2026-09-22_human_fist_marked_unmarked_test2.log`;
- source SHA256: `1176CF999FBDAAE70C4D1AACD8730A3F917CAE86A66006F99E2FD4F91D1440AB`;
- retained derived package: `research/derived/2026-09-22_human_fist_marked_unmarked_test2_large_log/`.

`research/raw/` contains only `Keep.txt`.
