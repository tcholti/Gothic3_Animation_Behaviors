# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-27

For document roles and authority, see `docs/README.md`. For the latest Chat/Work bridge, see `docs/BETWEEN_CHATS.md`.

## Project scope

Technical engine-facing work in this repository is authorized offline modding/reverse-engineering of the 2006 single-player game Gothic 3 using community SDK tooling. The target is the user's local game installation and the project's own mod/research DLLs.

Reusable prompt wording and scope guidance: `docs/PROJECT_SCOPE_CONTEXT.md`.

## Active subsystem

Frame-controlled melee collision lifecycle.

Known native defect: an offensive Hit can lose enough CombatMove/action ownership/bookkeeping that the physical Hit motion continues or later replaces while Gothic 3 fails to run normal collision cleanup. This is confirmed natively and is not introduced by frame markers.

Preferred invariant:

> For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.

Marker control changes collision inside a live Hit; end-of-Hit cleanup should remain one shared invariant for marked and native attacks.

## Established Step-B results

Canonical continuation: `docs/EVIDENCE_LEDGER_STEP_B.md`, EV-158 onward.

Detailed cleanup map: `docs/COLLISION_CLEANUP_CALLSITE_MAP.md`.

Key results:

1. `eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst replacement signal, but clean successor Recover PlayMotion occurs before later native cleanup. Replacement is too early for immediate repair.
2. Later original attack callbacks and `sAICombatMoveStartRecover` are not reliable post-cleanup boundaries.
3. Missing Recover animation assets are not the root cause; native Dual/Quick/Whirl cases reproduce the same stale-collision structure.
4. Successful native completion cleanup is action-specific inside `Script_Game.dll`; legitimate damage/reaction interruption has a separate tested cleanup path at `Script_Game + 0x24AFF`.
5. B5 stack capture reached generic script execution:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

These are not combat-specific cleanup owners.

6. `gCScriptProcessingUnit::sAICombatMoveInstr` at tested `Game + 0x1696E0` is also too early: CombatMove instruction completion can occur before action-specific Script_Game code performs the native weapon `7 -> 5` cleanup.
7. Static comparison found no common immediate Script_Game post-cleanup helper across Normal/Quick/full Whirl.

## Current design candidate

```text
exact owned offensive Hit replacement observed
-> mark exact execution pending-finalization
-> let Gothic finish the current native script dispatch
-> at one tightly gated post-script opportunity:
       native cleanup observed -> no-op
       cleanup absent          -> repair
```

The generic script boundary would provide timing only. It must never define attack ownership by itself.

## Step B6 — FROZEN NEXT WORK TASK

Use only the existing player/type-0 `PlayMotion` hook to capture a short supported Win32 stack when an actual attack-Hit PrimaryFirst execution is replaced.

Compare later at runtime:

1. clean Hit -> Recover replacement;
2. legitimate damage/reaction replacement;
3. bad block-skip direct replacement with missing cleanup.

Question:

> Do all relevant replacement events occur inside the same SPU / `ProcessScript()` invocation so that a later one-shot post-script check is guaranteed to run after Gothic's native cleanup opportunity?

Exact implementation scope and restrictions are frozen in `docs/BETWEEN_CHATS.md`.

Do not implement production cleanup yet.

## Negative-scope plan after architecture is proven

Before release, test Fist, bow, crossbow and magic as negative/regression cases if the final design uses a generic SPU/script timing checkpoint.

Fist is especially important because it can share ordinary melee action enums while not using the tested weapon-style `Item_Attack(7)` source request. Action enum alone must not define ownership.

## Research order

1. Finish the universal execution-level collision safety rule.
2. Later, if worthwhile, investigate the deeper block-skip/CombatMove teardown itself to preserve movement, activation/timing and other gameplay behavior.
3. Preserve useful animation/CombatMove hook discoveries for later Gothic 3 animation-mechanics research; do not divert the current collision work until the lifecycle guard is stable.

## Chat / Work loop

```text
Chat: design / evidence / freeze one bounded code task
        ↓
Work: implement/review/commit/push/STOP
        ↓
Chat + authoritative local PC: sync/build/runtime test/log interpretation
        ↓
Chat: update evidence/docs and choose next step
```
