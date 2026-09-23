# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-23

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Frozen state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`  
Source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Diagnostic SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Behavior SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

No source change absent new contradictory evidence.

## Current campaign

```text
Stage A body-contact                 PASS EV-365–EV-366
bad-skip C1-R1 stress               PASS EV-367
Stage B equipped/cumulative         PASS EV-368
Stage C separation compatibility    PASS EV-369–EV-372
Stage D mixed stress                ACTIVE
  broad natural gameplay run 1      PASS EV-373
```

## EV-373 broad mixed stress

User performed one long natural gameplay session with mixed combat/travel/weapon-source churn and reported everything looked/worked normally.

POP-07 package:
- raw SHA256 `0B5596584ED39571CA89CE7CBD90BA7065DF134CF4274BB3C4ADFA7CA5782652`
- 3,424,951 bytes / 16,693 lines
- exactly 6 anomaly-class timeline events

Disposition of those six:
- 4 C1-R1 finalization repairs: all exact live outstanding sources converged group7 -> group5; observed routes included player Staff/Halberd, Stalker Axe/raw52, ordinary 1H sword and a small-axe source with factual UseType2.
- 2 marker anomaly/discovery records: unsupported late/unknown callbacks failed closed (Action0/no valid C1; Action68/no live source); no stale activation.
- final observed combat cleanup returned player 1H RIGHT 7 -> 5; final obligations zero; diagnostic DLL unloaded cleanly.

Result: **PASS EV-373. No source change.** This corroborates C1-R1/fail-closed behavior under unscripted mixed gameplay.

## Next

Do not automatically schedule another test. In the next session decide deliberately whether EV-373 plus the previous structured coverage is sufficient to close Stage D, or whether one more differentiated broad stress run would add useful evidence. If Stage D closes, proceed to the planned New Balance + AttackCollision compatibility gate.

The EV-365–EV-372 ledger has been rotated to archive; current evidence begins at `EVIDENCE_LEDGER_373_ONWARD.md`.

After EV-373 closure, `research/raw/` contains only `Keep.txt`.
