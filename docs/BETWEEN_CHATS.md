# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current state — C1 shadow core passed; outer execution boundary remains open

**Date:** 2026-08-29  
**Branch:** `docs/collision-source-evidence`

C1 remains **shadow-only**. Production physical repair is disabled.

Durable current state is in `docs/SESSION_ENTRYPOINT.md`. Recurring local Git/build/deploy/test/log patterns are now in `docs/PROJECT_OPERATING_PROCEDURES.md` and should be read once when that operational sequence is entered, not after every prompt.

## C1 core result to preserve

Raw:

`research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log`

Derived connector extract:

`research/archive/2026-08-28_c1_shadow_core_lifecycle_matrix_connector_extract.txt`

The tested shadow classification behaved as intended for the main matrix:

- 8 actual `WOULD_REPAIR` outcomes = 1 armed bad full Whirl + 7 armed bad Dual Quick;
- clean completion = no repair candidate;
- pre-activation bad skip = no repair candidate;
- tested legitimate interruption = native cleanup, no repair candidate;
- inherited stale `7 -> 7` on the next Normal attack was attributed to the new generation and then fulfilled by native `7 -> 5` cleanup.

## New boundary finding

The run also produced 11 `UNOWNED_PLAYER_OFFENSE_REQUEST` warnings around knockdown/GetUp-related handling.

Static inspection confirms GetUpAttack can legitimately arm its weapon **before** the CombatMove boundary currently used to create the C1 generation:

```text
Script_Game +0x41CA6  Item_Attack(7) request region
Script_Game +0x41D5A  later call to the same CombatMove import used by full Whirl
Script_Game +0x41E10  known ordinary cleanup
```

Therefore:

```text
CombatMove start
= useful inner asynchronous-instruction boundary
≠ universal outer collision-owning ScriptFunction execution start
```

## Exact current Normal Chat question

Determine whether Gothic 3 exposes a stable **ScriptFunction/SPU execution identity or native outer boundary** that:

1. already exists when the pre-CombatMove offensive request occurs;
2. remains identifiable when the later CombatMove begins;
3. can therefore own the same cleanup obligation through completion or destructive abandonment.

First use narrow pinned-SDK/static-reference inspection. If that cannot establish the identity, freeze the smallest factual runtime diagnostic comparing identity at offense request → CombatMove entry → cleanup/finalization.

Do **not** solve the gap by:

- adding a GetUpAttack/action/family ownership special case;
- adopting any pre-existing group-7 equipped weapon at CombatMove start;
- enabling physical repair;
- adding polling/timers/per-frame/world scans;
- weakening existing marker bookkeeping.

There is currently **no frozen Work implementation task**. The next responsibility remains Normal Chat architecture/source reasoning.
