# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current state — C1 shadow guard built/deployed/loaded; core runtime matrix frozen

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`  
**C1 implementation:** `3778517f421d07e940c620745bc7ccdf0da54313`  
**Independent review:** PASS  
**Build:** PASS  
**Deployment hash:** PASS  
**Load banner:** PASS

C1 remains **shadow-only**. `WOULD_REPAIR` must never change physical collision.

## Frozen C1-A core runtime matrix

Raw filename:

`research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log`

Run all cases in one Gothic 3 session, with no target except where reaction interruption is required.

### 1. Clean ordinary completion

- Full Whirl: 3 clean completions.
- Dual / 1H+1H Quick: 3 clean completions.

Expected C1 model:

- lifecycle generation starts/persists;
- offensive request is attributed when it occurs;
- ordinary native cleanup fulfills the exact obligation;
- later AISetState finalizes with only `NO_OP_*` outcomes;
- zero `WOULD_REPAIR` and zero invariant warnings.

### 2. Full Whirl bad held-Use2 skips

Reproduce enough attempts to obtain both:

- at least 2 clear **pre-activation** skips where the weapon never requested offense;
- at least 3 clear **armed stale** skips where the weapon had already requested `Item_Attack`.

Expected:

- pre-activation finalization -> zero `WOULD_REPAIR`;
- armed stale finalization -> exactly one `WOULD_REPAIR` for the still-equipped stale weapon source;
- physical weapon must remain group 7 because shadow mode performs no repair.

### 3. Inherited stale `7 -> 7` control

Immediately after one armed bad Whirl has produced `WOULD_REPAIR` and left the real weapon stale at group 7:

- perform one clean Normal attack with the same weapon;
- let it finish normally.

Expected:

- new CombatMove generation starts after the old shadow generation was retired;
- its offensive request is attributed even if the physical transition is `7 -> 7`;
- the later native `7 -> 5` cleanup fulfills the new generation's obligation;
- its finalization is `NO_OP_*`, not `WOULD_REPAIR`.

Any `OVERLAP_OUTSTANDING`, `UNOWNED_PLAYER_OFFENSE_REQUEST`, or generation-change warning here is architecture-significant.

### 4. Quick bad held-Use2 skips

Use Dual / 1H+1H Quick and reproduce enough attempts to obtain:

- useful pre-activation skips if they occur;
- at least 3 clear **armed stale** Quick skips if practical.

Expected same consequence-based behavior as Whirl:

- no offense request -> no `WOULD_REPAIR`;
- armed stale exact source -> `WOULD_REPAIR`;
- no family-specific logic required.

Do not treat failure to reproduce a Quick bad skip as C1 failure; Quick timing is known to be harder to reproduce.

### 5. Legitimate reaction interruption

Spawn the durable target only for this section.

- Normal attack: at least 3 armed legitimate Stumble/KnockDown-type interruptions.
- Quick attack: at least 3 armed legitimate interruptions.

Expected:

- FullStop alone does not finalize C1;
- reaction-side native `7 -> 5` cleanup fulfills the exact obligation;
- later state finalization yields `NO_OP_*` only;
- zero `WOULD_REPAIR` for legitimate reactions.

## Pass/fail signals for C1-A

Strong pass requires:

1. clean completion -> no `WOULD_REPAIR`;
2. pre-activation bad skip -> no `WOULD_REPAIR`;
3. armed bad Whirl -> exact stale source `WOULD_REPAIR`;
4. armed bad Quick, when reproduced -> exact stale source `WOULD_REPAIR`;
5. legitimate reaction -> cleanup fulfilled before finalization, no `WOULD_REPAIR`;
6. inherited stale `7 -> 7` -> attributed to the new generation and later fulfilled;
7. no unexpected C1 invariant warnings.

If any invariant warning or false-positive `WOULD_REPAIR` occurs, stop production progression and inspect the raw chronology. Do **not** enable physical repair.

## Deferred validation after C1-A

Do not mix these into the first core run unless convenient. If C1-A passes, Normal Chat will freeze a second bounded regression matrix for:

- marked RIGHT / LEFT / BOTH / OFF and repeated-marker source switching;
- Fist negative;
- bow / crossbow / magic negatives;
- any actor-generic/NPC coverage needed before production repair.

Production repair remains disabled until both core lifecycle and marker/negative regression evidence support it.
