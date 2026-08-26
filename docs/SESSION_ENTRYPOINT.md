# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

For document roles and authority, see `docs/README.md`. For the latest Chat/Work bridge, see `docs/BETWEEN_CHATS.md`.

## Active Subsystem

Frame-controlled melee collision lifecycle.

The RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is optional authored early shutoff inside a live Hit; it is not the general end-of-Hit safety mechanism.

Known native defect: an offensive Hit can lose enough CombatMove/action ownership/bookkeeping that the physical Hit motion continues or later replaces, while Gothic 3 fails to run the normal collision cleanup path. This is confirmed natively and is not introduced by frame markers.

## Preferred Cleanup Model

Prefer **System 1: execution-level native cleanup guard**.

> For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its normal cleanup opportunity. When that exact Hit genuinely ends or is replaced, if proper cleanup was observed, do nothing; if not, repair the remaining offensive collision using the native cleanup semantics.

Marked and native attacks should differ primarily in activation timing. Marker control changes collision **inside** the Hit; end-of-Hit cleanup remains one shared invariant.

Native cleanup paths are **opportunities, not guarantees**. Gothic 3 has multiple legitimate completion and interruption cleanup paths, and a broken Hit can bypass them. Production should observe whether cleanup happened rather than assume one specific native path always runs.

Detailed architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

## Marker Rule While Hit Is Alive

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive collision set.

## Step A — VALIDATED

Implementation commit:

`325c98e725502229bf796083e52c0fa977803cc0` — modularized the research DLL while preserving behavior.

Home-PC validation confirmed build/load, marked Normal/Quick/Whirl behavior, and preservation of the known stale-lifecycle defect.

## Step B1 — PRIMARYFIRST EVENT PROBE VALIDATED

Source commits:

- `7dcd514b0bcd51c05453e3e55500a927b9063159`
- `81e88026a4b47086a8995ab65d2933a041f8d2fd`

Established:

- `eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst acquisition/replacement signal in controlled cases.
- It reports successor motion far earlier than the old Script `OnTick` comparator.
- Clean Recover `PlayMotion` happens **before** native `7 -> 5` cleanup, so successor PlayMotion itself is too early for immediate repair.
- `StopMotion` is supporting evidence only.

## Step B2 — ORIGINAL CALLBACK BOUNDARY REJECTED

Source commit:

`106209bdefa6c9c52e1f1408a3d148dd52b2664e`

Clean Quick transitions already perform native cleanup before the later original Quick callback begins, and that callback repeats during Recover. It is not a one-shot Hit-completion boundary.

## Step B3 — STARTRECOVER BOUNDARY REJECTED

Source commit:

`86fd222ace9ef27e88f4846cf0f720c32dce6f6a`

Tested hook:

`gCScriptProcessingUnit::sAICombatMoveStartRecover` at `Game + 0x16E360`.

Established:

- Clean Normal/Quick/Whirl: StartRecover begins while Hit is active, starts/attempts Recover handling, returns while weapon is still group 7, then native cleanup follows.
- Broken 2H/Staff Whirl: Hit can activate collision and be replaced directly by Ambient with **no StartRecover and no cleanup**.

Therefore StartRecover is neither the post-cleanup boundary nor a guaranteed path.

## Step B3b — NATIVE BLOCK-SKIP COMPARISON VALIDATED

Runtime evidence:

`research/raw/2026-08-26_stepB3b_native_block_skip_comparison.log`

Established:

- A Recover **animation asset** is not required for cleanup. Native 1H and Shield+1H Quick executions without Recover assets can still run the Recover lifecycle/bookkeeping path and clean correctly while the Hit motion remains Primary.
- The same no-Recover Quick can also follow the bad path: activate collision, direct replacement, no StartRecover, no cleanup, stale group 7.
- Native Dual / 1H+1H Quick reproduces the same structural failure.
- Several pre-Hit Raise motions can be replaced early while the later Hit still starts fresh and cleans correctly. This supports a timing hypothesis only; Raise is not a cleanup fix.

Current block-skip hypothesis:

> During the vulnerable skip Gothic 3 can abandon part of the attack/CombatMove gameplay ownership while the physical Hit animation remains alive. A skip during an active Hit is potentially harmful before or after collision activation. Cleanup loss after activation is confirmed; loss of movement and/or later activation before collision is plausible and partly supported by visual observation, but not yet fully logger-confirmed.

## Step B4/B4b — NATIVE CLEANUP ARCHITECTURE MAPPED

Primary evidence:

- `research/raw/2026-08-26_stepB4_native_cleanup_callsite_probe.log`
- `research/raw/2026-08-26_stepB4b_native_manyattacks_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_finishing_blow_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_interruption_cleanup_callsite.log`

Detailed map:

`docs/COLLISION_CLEANUP_CALLSITE_MAP.md`

Established:

- Native successful completion cleanup is **action-specific** inside `Script_Game.dll`, not one universal per-family function.
- Confirmed action paths include Normal, Power, Quick, SimpleWhirl, full Whirl, Pierce, Hack, Finishing, and GetUpAttack, with LEFT/RIGHT branches where observed.
- The same serialized 2H `FinishingAttack` Hit asset is processed under different runtime actions and cleanup functions: standing/block-breaking use can be `gEAction_HackAttack` (14), while true execution is `gEAction_FinishingAttack` (15).
- Legitimate damage/reaction interruption uses a separate cleanup call site, `Script_Game + 0x24AFF`, before Stumble/knockdown replacement in the tested matrix.
- Therefore production must not become a matrix of one cleanup hook per attack action.

## Step B5 — PARENT-STACK PROBE VALIDATED

Source commit:

`807307570b85bcdd4f1c3c703204dbd34560feb6`

Runtime evidence:

`research/raw/2026-08-26_stepB5_cleanup_parent_stack_probe.log`

The existing SetCollisionGroup hook captured supported Win32 call stacks for exact player-equipped `7 -> 5` cleanup events.

Established:

### Ordinary action completion

All observed ordinary action-specific cleanup sites in the B5 sample converged immediately to:

```text
Game + 0x1605EB
```

The tested binary shows this return point inside a Game function beginning at approximately:

```text
Game + 0x1604E0
```

This held across different Script_Game action-specific callers such as Normal, Quick, Power, Whirl, Pierce and Hack in the B5 sample.

### Legitimate damage/reaction interruption

The tested interruption cleanup path remained structurally different:

```text
Script_Game + 0x24AFF
→ another Script_Game frame
→ Game + 0x1604D3
```

The binary shows `Game + 0x1604D3` at the return/end of the immediately preceding sibling Game function; the ordinary path begins at `Game + 0x1604E0` directly after it.

Thus B5 found **adjacent sibling Game-level dispatcher/helper paths**, not one identical captured parent for both completion and interruption.

### Finishing-target-standing case

One attempted execution played `FinishingAttack_Raise` and the same `FinishingAttack_Hit` asset, but by the Hit/collision phase the runtime action was already `gEAction_HackAttack` (14). The log does not show a confirmed action-15 -> action-14 transition; treat it as action semantics selecting Hack behavior while reusing the FinishingAttack asset family.

## Earlier Marker-Bookkeeping Interruption Lesson

Do not confuse physical collision cleanup with marker-execution retirement.

The v0.15/v0.16 `RetireMarkerOwnedSource()` work solved an earlier case where Gothic **did** naturally reset a marked source `7 -> 5`, but our occurrence-budget/execution record could remain stale when interruption happened after an earlier marker and before later authored markers.

`RetireMarkerOwnedSource()` reacts to an already-performed source reset and retires marker bookkeeping when that reset represents execution end. It is not itself the physical fallback cleanup. Intentional intra-Hit OFF/source switching must not retire the whole execution.

A future authoritative Hit-lifetime boundary may simplify both:

1. marker execution/budget retirement;
2. final physical collision cleanup verification.

## Current Three-Path Model

```text
A. NORMAL COMPLETION
Hit
→ action-specific Script_Game cleanup
→ shared ordinary Game sibling path
→ collision clean
```

```text
B. LEGITIMATE DAMAGE/REACTION INTERRUPTION
Hit
→ Script_Game interruption cleanup (+0x24AFF)
→ interruption Game sibling path
→ reaction motion
→ collision clean
```

```text
C. BAD BLOCK SKIP / ABNORMAL TEARDOWN
Hit
→ some gameplay/CombatMove ownership is abandoned
→ neither proper completion cleanup nor proper interruption cleanup is guaranteed
→ physical Hit may continue/replacement may occur
→ stale collision possible
```

## Research Order Decision

Keep two problems separate:

1. **First:** finish the universal execution-level collision safety rule. It must protect native and marked Hits against any genuine abnormal end/replacement, regardless of which normal cleanup path would otherwise have run.
2. **Later / optional:** investigate and repair the deeper block-skip/CombatMove teardown itself, potentially preserving movement, collision activation/timing, and other gameplay behavior.

Do not make the universal guard depend on fixing the block-skip cause.

## Immediate Next Research Question

B5 disproved the simplest hope that successful completion and legitimate interruption share one identical captured Game parent frame. The two successful paths instead reach **adjacent sibling Game functions** around `Game + 0x1604D3` / `Game + 0x1604E0..0x1605EB`.

Next research should inspect these sibling Game functions and their callers/dispatch conditions before choosing another runtime hook. The goal remains to find the narrowest event-driven boundary at which Gothic has had its legitimate cleanup opportunity, without introducing one hook per action family or broad Script polling.

Do **not** implement production cleanup yet.

## Current Testing Rule

For lifecycle/cleanup research, prefer native/unmarked attacks when isolating Gothic's own activation/cleanup. Reintroduce marked fixtures only when testing convergence of the final execution-level guard.

## Documentation Rule

- `EVIDENCE_LEDGER.md` is the fact/hypothesis authority.
- `COLLISION_CLEANUP_CALLSITE_MAP.md` preserves build-specific reverse-engineered cleanup call sites and stack/parent findings.
- `SOURCE_HOOK_GUIDE.md` preserves practical hook/RVA knowledge.
- `COLLISION_LIFECYCLE_PLAN.md` owns the current design model.
- This file is only the concise current front door.

## Repository Access Note For New Sessions

Use the connected GitHub repository interface as the authoritative assistant-side access path. The user's home checkout is authoritative for local build/install/runtime testing.

Do not interpret assistant-container network failures as repository unavailability.

## Chat / Work Execution Model

```text
Chat: design / evidence / freeze one bounded code task
        ↓
Work: source implementation/refactor + targeted review + commit/push + STOP
        ↓
Chat + home PC: sync / build / runtime test / interpret logs
        ↓
Chat: update evidence/docs and choose next code task
```

Routine build verification, runtime testing, log interpretation, documentation, evidence consolidation, and next-step planning stay in Chat/local testing by default.
