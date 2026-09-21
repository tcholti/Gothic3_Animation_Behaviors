# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-21

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

Authority: `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md` §14.

Status after EV-361:

```text
1. Gargoyle close/delayed/no-contact    PASS — EV-359 + EV-360
2. Human Normal + true Power            PASS — EV-359
3. Later FIST same-C1 reopening         PASS — EV-359
4. Ordinary no-contact finalization     PASS — EV-359
5. Reaction/generation replacement      PASS — EV-360
6. Replacement -> unmarked fallback     OPEN
7. Native unmarked human target-control PASS — EV-361
8. Sprint Action9 -> Action2 transport  PASS — EV-360
9. raw55 + equipped coexistence         PASS — EV-357
10. Diagnostic/behavior parity          PASS — EV-357 + EV-358
```

EV-361 correction:
- exact motion `Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot`;
- 29 executions, all `MarkerPresent=0 / FistMarkers=0 / SuppressNative=0`;
- zero raw8 ownership/open/consumed/FIST-marker records on that motion;
- 2 exact native `Game+0x16E348` contacts, both to the locked `ReddockOrcScoutLeader`;
- no unmarked left-hand contact against nearby non-target Orcs;
- User deliberately switched targets and tried to hit bystanders.

The group-combat file is mixed marked + unmarked by design. File-wide marked traffic does not invalidate the exact unmarked P1-left control.

## Next responsibility

Only focused item 6 remains.

Next session, prepare one clean sentinel:

```text
marked human raw8 opportunity pending
-> factual reaction/interruption replaces generation
-> old opportunity closes
-> next relevant human raw8 attack is the genuinely unmarked P1-left Normal motion
-> no intervening newly marked FIST opportunity
-> unmarked attack follows native path; ordinary native contact is preferred
```

Use the known unmarked motion above. The decisive point is **no new marked opportunity between replacement close and the unmarked fallback attack/contact**.

After item 6 PASS:
1. close focused permanent raw8 acceptance;
2. begin `COLLISION_TEST_PLAN.md` §3.8 comprehensive final-source campaign:
   animals/body-contact -> equipped coverage -> modded/custom animations -> mixed stress -> New Balance + AttackCollision.

Sabretooth, Gargoyle and human Fist do not need automatic broad retesting after focused acceptance unless a later contradiction calls for them. Golem may be reused as a weapon target.

`research/raw/` contains only `Keep.txt`.
