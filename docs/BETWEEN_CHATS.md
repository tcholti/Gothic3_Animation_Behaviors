# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **Phase 4 broad regression PAUSED at EV-346 raw8 FIST authoring-semantics research.**

Latest completed evidence: **EV-346**.

## Agreed raw8 design target

User + Normal Chat agreed:

```text
marked C1 starts
-> authored raw8 opportunity CLOSED

accepted FIST
-> one target-directed native body-contact damage opportunity OPEN

unsuccessful native contact
-> opportunity remains OPEN

successful native contact
-> opportunity CONSUMED/CLOSED

later FIST
-> opportunity OPEN again

C1 / Hit termination, interruption or factual replacement
-> any unused opportunity CLOSED
```

No arbitrary timer.

No authored raw8 FIST_OFF absent future evidence of a concrete unwanted-contact problem.

Gothic retains target/contact/damage ownership.

Raw55 must later be checked against the same author-facing abstraction without copying raw8 mechanics into raw55.

## Active raw8 probe

`docs/work/active/COLLISION_RAW8_FIST_POST_ATTEMPT_LATCH_OBSERVATION_PROBE.md`

Work implementation `4ab9a77557f9ad5057d158b7d26a3098db657b28` is independently source-reviewed **PASS**. Runtime validation is pending.

Probe responsibility is diagnostics-only:

> After the current early synthetic raw8 opportunity executes, observe the factual post-native `SPU+0x164` latch state and correlate it with native damage/no-damage.

Preferred existing boundary:
- current `EngineBridge` already wraps `AICombatMoveInstr`;
- current `Game+0x16E180` timing transport already knows when synthetic permission is consumed;
- if source facts support exact correlation, add only the smallest diagnostic state/record and read the latch after original `AICombatMoveInstr` returns;
- do not add a new engine hook if the existing wrapper is sufficient;
- if it is not sufficient, Work must report the contradiction and STOP rather than inventing a boundary.

Protected:
- zero new behavior;
- no new latch writes;
- no rearm;
- no timing change;
- no callback suppression;
- no direct/custom damage;
- no ClearTriggeredList;
- no group mutation;
- no raw55/equipped/Sprint change.

Work build execution is PROHIBITED.

Next:
1. User builds both `Script_FrameCollisionTest` and `Script_FrameCollisionBehaviorTest` locally; deploy diagnostic twin only.
2. Verify one live collision DLL/twin and capture diagnostic SHA256.
3. Use an isolated Gargoyle raw8 Power fixture with an early marker that produces `SyntheticApplied=1`; the approximate frame-3 fixture is preferred because the prior run naturally produced both hits and misses at identical authored timing.
4. Capture enough attacks to obtain at least one synthetic miss and one synthetic hit.
5. Correlate every `CORE RAW8_FIST_POST_ATTEMPT` OnDamage ordinal with the exact `ENTITY_ON_DAMAGE_ENTRY` record before interpreting hit/miss.
6. Do not resume broad Phase 4 until this causal research chain closes or the design is revised.

`research/raw/` currently contains only `Keep.txt`.
