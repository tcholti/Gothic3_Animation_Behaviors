# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat  
**To:** Work  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B2 Result — CALLBACK CANDIDATE REJECTED

Runtime evidence is in:

- `research/raw/test_Script_FrameCollisionTest.log`;
- `research/raw/2026-08-26_stepB2_causal_extract.log`.

The focused extract contains 40 original-callback records, all Quick. On a clean Quick transition:

1. successor Recover `PlayMotion` occurs;
2. native weapon cleanup `7 -> 5` occurs;
3. only then does the first original Quick callback BEGIN;
4. that callback continues repeating during Recover.

Therefore original attack-family callback entry/return is not the cleanup boundary and is not a one-shot Hit-completion event. Do not build lifecycle ownership around it.

## Step B3 — BOUNDED COMBATMOVE RECOVER BOUNDARY PROBE

### Source evidence

Official SDK declares:

`gCScriptProcessingUnit::sAICombatMoveStartRecover(gCScriptProcessingUnit *)`

Tested `Game.dll` exports it at RVA `0x16E360`.

Tested disassembly shows the function calls high-level PrimaryFirst `PlayMotion` and continues executing before return.

### Exact runtime question

> On a clean attack, does native offensive-collision cleanup occur between `sAICombatMoveStartRecover` BEGIN and END? On the known Recover-skip/stale case, is this function entered and, if so, does it return without cleanup?

### Implement only this probe

1. Add exactly one diagnostic hook for tested Game RVA `0x16E360`, matching the SDK static/stdcall signature.
2. Main/hook bridge remains sole hook owner.
3. For the player entity only, log compact `COMBATMOVE STARTRECOVER BEGIN` immediately before the original function and `... END` immediately after it.
4. Each record should contain only what is needed for correlation:
   - high-resolution elapsed time;
   - actor address/name;
   - current Action/AniPhase/current movement animation;
   - existing PrimaryFirst snapshot fields;
   - current equipped LEFT/RIGHT source identity and collision group when available.
5. Call the original `sAICombatMoveStartRecover` exactly once and preserve behavior/return semantics exactly.
6. Add no persistent lifecycle state, cleanup, timer, polling, family exception, or production decision.

### Diagnostic noise reduction for this probe

The B1/B2 evidence is already preserved in raw logs and Git history. To keep B3 evidence small:

- make the existing PrimaryFirst `PlayMotion` / `StopMotion` diagnostic output player-only while leaving the hooks/original calls unchanged;
- remove or disable the temporary B2 `ORIGINAL ATTACK CALLBACK ... BEGIN/END` output; do not change the callback hook behavior or suppression paths;
- keep `SetCollisionGroup`, marker records, and the old marker-owned `OnTick` comparator available for correlation.

These are diagnostic-output changes only. Collision-control behavior must remain unchanged.

### Stop conditions

Do not implement cleanup or lifecycle ownership.  
Do not add another polling/checking mechanism.  
Do not broaden to `sAICombatMoveItlLoop` yet.  
Do not build or run Gothic 3.

Commit and push the source changes, overwrite this file with a concise Work-to-Chat result and final commit SHA, then STOP.
