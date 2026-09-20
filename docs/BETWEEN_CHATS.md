# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Phase 4 remains paused at raw8 FIST authoring-semantics research. Latest completed evidence: **EV-349**. No active Work task.

Agreed author-facing target remains:

```text
FIST opens one target-directed native body-contact opportunity
-> genuine no-contact should not consume it
-> native target/vulnerability/damage remain Gothic-owned
-> successful native resolution consumes it
-> later FIST rearms it
-> C1 / Hit replacement or interruption closes any unused opportunity
```

No raw8 FIST_OFF absent future contradictory evidence.

## EV-347–EV-349

- EV-347: tested raw8 latch closes after both exact hit and exact miss attempts.
- EV-348: one exact post-miss latch `1 -> 0` rearm restored later native opportunity without timing rearm.
- EV-349: 12 Gargoyle frame-3 synthetic Power attempts; 4 immediate native entries; 8 post-miss rearms; 6 later native entries within the original Hit C1; 1 no later entry; 1 native entry only after Hit C1 55 was replaced by Recover C1 57.
- That cross-C1 entry occurred while the player was `Action=31` / `GetUpParade`; User observed no visible damage. User also observed another no-damage attack while already knocked down.
- Therefore visible health damage is not a collision-success oracle, and a future persistent opportunity must not override Gothic's knockdown/get-up target-state rules.
- The temporary probe also proves exact C1/Hit termination cleanup is mandatory: an unused rearmed opportunity can otherwise remain live into Recover.

Canonical latest log:
`research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_3.log`  
Git blob `9e46fa742d94d8e569226c51e509b224ac391ac1`.

## Current stop gate

Run POP-12 after pulling the latest branch:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require `Knowledge-state validation PASS`.

Do not launch another Work task or runtime causal test before that PASS.

After PASS, the next question is **not merely timing**:

> Find the smallest factual native boundary that distinguishes genuine no-contact from legitimate target-state rejection, while keeping Gothic in ownership and closing any unused authored opportunity at exact C1/Hit termination.

New Balance later needs an explicit knocked-down/get-up compatibility control because the User reports it changes some of this behavior; exact New Balance behavior is not yet established.

`research/raw/` should contain only `Keep.txt`.
