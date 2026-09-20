# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **Phase 4 broad regression PAUSED at raw8 persistent-opportunity research through EV-348.**

Latest completed evidence: **EV-348**.

No active Work implementation task.

## Agreed raw8 design target

```text
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

No arbitrary timer. No raw8 FIST_OFF absent future contradictory evidence. Gothic retains target/contact/damage ownership.

## EV-347–EV-348 causal closure

EV-347:
- exact early synthetic hit and exact early synthetic miss both returned with `SPU+0x164 = 1`;
- therefore Gothic consumes the latch after the attempt, not only successful damage.

EV-348:
- reviewed probe implementation `ea652e3324fffb07da013229a2fd374c4f3b1c6b`;
- diagnostic DLL SHA256 `63261A1A4778FF293BDA94495B57EE363546650A7D386507304CA3D5FD9AB3FC`;
- 13 exact frame-3 Gargoyle synthetic Power attempts;
- 4 exact early hits -> no rearm;
- 9 exact early misses -> 9 confirmed latch `1 -> 0` rearms;
- 7/9 rearmed misses -> later exact native raw8 damage before same-C1 finalization, ~100.6–109.8 ms after rearm;
- 2/9 rearmed misses -> no later native damage;
- User visually observed all attacks connect except one very-far case, so one of the two no-damage C1s cannot be reconciled to a specific visual case and remains unassigned;
- all identities/finalization clean; no anomalies/warnings/repairs/divergence.

Conclusion:

> One post-miss latch-only rearm is causally sufficient to restore a later native raw8 opportunity on the tested Power route, without rearming timing permission.

This does **not** prove continuous eligibility during the interval between authored FIST and Gothic's later native timing.

Canonical evidence:
`research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_2.log`  
Git blob `b447d1a3995118e84b0884801c0347b49efd15d8`.

The closed latch-rearm probe is archived under `docs/archive/investigations/`.

## Current hard stop

POP-12 knowledge-state validation is pending.

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require:

```text
Knowledge-state validation PASS
```

Do not freeze/launch the next Work task or start another runtime causal test until this PASS is reported.

After PASS, Normal Chat should discuss/decide only the remaining narrow design question:

> Does the agreed FIST semantic require eligibility continuously from marker time until successful contact, including transient contact before Gothic's later native threshold, or is latch-only recovery at the later native timing sufficient?

`research/raw/` should contain only `Keep.txt`.
