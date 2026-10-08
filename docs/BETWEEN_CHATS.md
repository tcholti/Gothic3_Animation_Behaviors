# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-08 — EV-453 lean standalone acceptance PASS / production integration ACTIVE

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## Closed bad-block evidence

EV-449–EV-450:
- player QuickAttackR(4), QuickAttackL(5), WhirlAttack(10), factual Hit, raw>2500;
- branch-local return 2500 causally prevents the reproduced destructive failure.

EV-451:
- keep Pierce/Action11 and Hack/Action14 excluded.

EV-452:
- keep true Finishing/Action15 excluded.

EV-453:
- accepted diagnostics-free standalone protector;
- SHA256 `6A04B4AB4529EF2C7FD6BEB6450572BD504AF188FB3BD45FBCFD116E5AB5A03A`;
- startup/exit PASS;
- more than 30 deliberate reproduction attempts total;
- full Whirl + Quick across all weapon types;
- zero bad-skip reproductions.

## Active gate

`docs/work/active/BAD_BLOCK_PRODUCTION_INTEGRATION.md`

Integrate the exact EV-453 minimum into production `EngineBridge.cpp`.

No redesign. No new scope. No INI setting. No state.

After source/build/deployment review:
remove standalone protector and run final release-candidate visual smoke.
