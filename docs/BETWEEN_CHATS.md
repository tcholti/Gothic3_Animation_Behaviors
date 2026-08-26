# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat  
**To:** Work  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B3/B3b Result — LIFECYCLE FAILURE NARROWED

Runtime evidence:

- `research/raw/2026-08-26_stepB3_native_startrecover_probe.log`
- `research/raw/2026-08-26_stepB3b_native_block_skip_comparison.log`

Established:

- clean native Normal/Quick/Whirl paths call `sAICombatMoveStartRecover`, then native `7 -> 5` cleanup occurs shortly **after** StartRecover returns;
- broken native 2H/Staff Whirl and Dual/1H+1H Quick paths can activate offensive collision, skip StartRecover entirely, replace Hit directly by Ambient, and miss cleanup;
- stale collision can survive into the next attack and produce `7 -> 7` activation;
- native 1H and 1H+Shield P1 Quick animations with **no Recover animation asset** can still call StartRecover and clean correctly while Hit remains the PrimaryFirst motion;
- the same 1H+Shield no-Recover Quick also reproduced the bad direct-Ambient/no-StartRecover/no-cleanup path;
- therefore missing Recover asset is not the cause. The relevant distinction is whether the engine's lifecycle/bookkeeping transition is reached.

Working block-skip hypothesis, not yet proven internally:

> the skip may abandon some CombatMove/action ownership or bookkeeping while the physical Hit motion keeps playing. A skip during an active Hit is therefore potentially harmful whether offensive collision has already activated or not. If it occurs before native collision activation, the attack may lose the remaining native timing/behavior needed to make a visually connecting strike damage correctly. If it occurs after collision activation, later replacement can miss normal cleanup and leave the source stale. The exact interrupted state and whether collision activation itself is lost in the early-Hit case are not yet logger-confirmed.

Animation-author visual observation additionally suggests engine-driven forward attack movement may stop immediately at the same skip. Treat this as possible evidence of a broader native CombatMove teardown bug, not yet logger-confirmed.

A long Raise is not treated as a fix. It may only move the vulnerable skip before the offensive Hit begins; if the later Hit starts fresh, its native timing, movement, collision activation, and cleanup can proceed normally.

## Research-order decision

Finish the **universal execution-level collision safety solution first**. It must remain independent of the cause of Hit termination and later cover marked/native attacks, block skip, terrain interruption, damage interruption, and other genuine replacements.

Investigating/fixing the deeper native block-skip teardown itself is a separate later project question; do not make universal collision safety depend on it. A later deeper fix may need to preserve more than cleanup, including attack movement and collision activation/timing.

## Step B4 — BOUNDED NATIVE CLEANUP CALL-SITE PROBE

### Purpose

Identify the exact native caller/call site that performs clean `SetCollisionGroup(Item_Equipped)` / `7 -> 5` after StartRecover returns. Use that address to inspect the enclosing function and find a narrow post-cleanup-opportunity boundary before considering a broad `sAICombatMoveItlLoop` hook.

### Implement only this diagnostic change

Use the **existing** `eCEntity::SetCollisionGroup` hook. Do not add a new hook.

For a player-equipped LEFT or RIGHT source only, when all of these are true:

- requested group is `Item_Equipped` (5);
- before group is `Item_Attack` (7);
- after group is `Item_Equipped` (5);

log one compact `NATIVE CLEANUP CALL SITE` record containing:

- high-resolution elapsed time;
- changed entity/source identity and LEFT/RIGHT player-slot match;
- raw immediate caller/return address captured at the SetCollisionGroup wrapper entry;
- owning module name/base and caller RVA if practical and reliable in the current Win32/MSVC environment.

Prefer robust address-to-module resolution (for example from-address module lookup) over assuming the call originates in Game.dll.

Pass the captured caller address into diagnostics as a stack-local fact. Add no persistent lifecycle state.

### Preserve existing behavior

- call original SetCollisionGroup exactly once with unchanged argument;
- preserve existing retirement and SetCollisionGroup diagnostics;
- collision-control code and behavior unchanged;
- StartRecover probe may remain for one comparison run;
- player-only PrimaryFirst output remains as in B3;
- no B2 callback output;
- no new timer, polling/checking mechanism, cleanup behavior, family special case, or production decision;
- do not add or broaden to `sAICombatMoveItlLoop` yet.

### Documentation rule

When the exact cleanup call site/enclosing function is established, record durable reverse-engineering knowledge in `docs/SOURCE_HOOK_GUIDE.md` with module, RVA/address, tested context, purpose, and confidence/signature evidence. Keep project-local hook/call-site evidence useful enough to support possible future SDK research/upstream improvements.

### Acceptance

Source should allow a short native-only runtime test to answer:

> Which module + RVA calls SetCollisionGroup(5) for clean Hit cleanup immediately after StartRecover returns?

Do not implement cleanup or lifecycle ownership from that result in Work.

Do not build or run Gothic 3.

Commit and push the source changes, overwrite this file with a concise Work-to-Chat result and final commit SHA, then STOP.
