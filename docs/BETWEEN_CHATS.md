# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat  
**To:** Work  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B3 Result — STARTRECOVER CANDIDATE REJECTED

Runtime evidence:

`research/raw/2026-08-26_stepB3_native_startrecover_probe.log`

The B3 run used native/unmarked 2H and Staff Normal, Quick, clean Whirl, and reproduced skipped-Recover Whirls.

### Clean-path ordering

On clean attacks, `sAICombatMoveStartRecover` starts Recover but returns **before** native weapon cleanup.

Representative Staff Whirl:

- StartRecover BEGIN `88819.525`;
- Recover PrimaryFirst PlayMotion result `88819.622`;
- StartRecover END `88819.644`, right source still group 7;
- native SetCollisionGroup(Item_Equipped) / `7 -> 5` at `88819.704`.

Ordinary Staff Normal and Quick show the same ordering: StartRecover END first, native `7 -> 5` afterward.

Therefore StartRecover is not the post-native-cleanup boundary.

### Broken-path ordering

The same native lifecycle failure was reproduced for both 2H and Staff Whirl:

1. Whirl Hit PrimaryFirst begins;
2. native collision activates `5 -> 7`;
3. the Hit is replaced directly by an Ambient PrimaryFirst motion;
4. no StartRecover call occurs for that execution;
5. no `7 -> 5` cleanup occurs;
6. the stale source survives into the next Whirl, which can request `7 -> 7`.

Thus the defect is not Staff-specific and is not "StartRecover ran but forgot cleanup". The broken execution skips the normal CombatMove Recover transition itself.

## Step B4 — BOUNDED NATIVE CLEANUP CALL-SITE PROBE

### Purpose

Identify the exact native caller/call site that performs clean `SetCollisionGroup(Item_Equipped)` / `7 -> 5` after StartRecover returns. Use that address to inspect the enclosing function and find a narrower post-cleanup-opportunity boundary before considering a broad `sAICombatMoveItlLoop` hook.

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

### Acceptance

Source should allow a short native-only runtime test to answer:

> Which module + RVA calls SetCollisionGroup(5) for the clean Hit cleanup immediately after StartRecover returns?

Do not implement cleanup or lifecycle ownership from that result in Work.

Do not build or run Gothic 3.

Commit and push the source changes, overwrite this file with a concise Work-to-Chat result and final commit SHA, then STOP.
