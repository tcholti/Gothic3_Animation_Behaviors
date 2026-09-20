# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **Phase 4 non-weapon creature regression ACTIVE / PARTIAL PASS through EV-341.**

No active Work implementation contract.

Current diagnostic test product remains:

```text
Script_FrameCollisionTest.dll
SHA256 DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A
```

Latest Phase-4 batch:
- EV-337 Sabretooth raw8 double-FIST, native + transformed player = PASS;
- EV-338 Sabretooth raw8 single-FIST, native + transformed player = PASS;
- EV-339 Wolf marked raw8, native + transformed player = PASS;
- EV-340 Wolf unmarked factual Fist/raw8 native-fallback control, native + transformed player = PASS;
- EV-341 Troll permanent raw55 mixed single/double FIST + player Staff = PASS.

Important distinctions:
- Sabretooth double-marker executions that reached both FISTs use first-marker early permission and later native-timing rearm; interrupted C1s that never reached marker2 are not failures.
- Wolf proves the raw8 opt-in boundary directly: same factual Fist/UseType8 source, marked => authored timing; unmarked => zero raw8 ownership/timing intervention and native damage remains healthy.
- Troll remains raw55, separate from raw8. Double-FIST Quick uses one physical opening plus contact rearm only on marker2; exact RIGHT cleanup remains native.
- zero nonzero/outstanding finalization failures or lifecycle/invariant/repair contradictions across all five logs.

Phase 4 remains open because more animal/monster fixtures are planned.

Next responsibility:
- continue `docs/COLLISION_TEST_PLAN.md` Phase 4 with other non-weapon creature/body-contact fixtures;
- prioritize new creature/source coverage rather than repeating Sabretooth/Troll unless a contradiction appears.

`research/raw/` should contain only `Keep.txt`.
