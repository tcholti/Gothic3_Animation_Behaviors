# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

For document roles and authority, see `docs/README.md`. For the latest Chat/Work bridge, see `docs/BETWEEN_CHATS.md`.

## Active Subsystem

Frame-controlled melee collision lifecycle.

The RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is optional authored early shutoff inside a live Hit; it is not the general end-of-Hit safety mechanism.

Known native defect: offensive weapon collision can remain `Item_Attack` after a Hit is replaced/interrupted without normal cleanup. Recover is not the universal cleanup owner.

## Preferred Cleanup Model

Prefer **System 1: execution-level native cleanup guard**.

For every real attack-Hit execution that requests offensive collision, follow the exact actual Hit execution until it ends/replaces. If Gothic 3 already performed proper native cleanup, do nothing; if it did not, invoke the native cleanup Gothic 3 should have performed.

Marked and native attacks should differ primarily in activation timing. Marker control changes collision **inside** the Hit; the preferred end-of-Hit cleanup rule remains shared. Use **System 2 source-aware cleanup only if evidence proves cleanup is genuinely source-specific or partially independent**.

Production cleanup must be actor-general. Player-only filtering in current Step B diagnostics is only a controlled research choice; later validation must include NPCs.

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

`325c98e725502229bf796083e52c0fa977803cc0` — `Modularize frame collision research DLL`

The research DLL remains one DLL with one owner for each hook, split into hook bridge, collision control, collision diagnostics, shared facts, and runtime timing modules.

Home-PC validation on 2026-08-26:

- MSVC Release build succeeded;
- Gothic 3 loaded and ran without crash;
- marked Normal/Quick/Whirl smoke test covered 2H, Staff, and Dual/1H+1H;
- marker/control/diagnostic behavior remained present;
- the known stale-lifecycle defect remained reproducible, as expected for a parity-only refactor.

Processed pre-Step-B logs were archived in commit `ed01c2e4d9489d971c0635e76114d9bf85ffc9e0`.

## Step B1 — PRIMARYFIRST EVENT PROBE VALIDATED

Source commits:

- `7dcd514b0bcd51c05453e3e55500a927b9063159` — add diagnostic `PlayMotion`/`StopMotion` probe;
- `81e88026a4b47086a8995ab65d2933a041f8d2fd` — namespace fix.

Established findings:

- `eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst Hit-acquisition and successor/replacement signal in the controlled cases.
- In stale Whirl reproductions, successor `PlayMotion` exposes replacement much earlier than the old Script `OnTick` comparator.
- In clean Normal/Quick/Whirl transitions, Recover `PlayMotion` occurs first and native weapon cleanup `7 -> 5` follows almost immediately in the same transition/update.
- Therefore production must not force cleanup immediately inside successor `PlayMotion`; Gothic 3 must first get its normal cleanup opportunity.
- Global PrimaryFirst logging is research-noisy; current diagnostics filter its output to the player.

The old `OnTick` lifetime probe remains only as a temporary comparator. Do not promote it to production architecture.

## Step B2 — ORIGINAL-CALLBACK CANDIDATE REJECTED

Source commit:

`106209bdefa6c9c52e1f1408a3d148dd52b2664e`

Runtime result:

- clean Quick transitions perform native `7 -> 5` before the original Quick callback begins;
- that callback then repeats during Recover;
- original attack-family callback entry/return is therefore neither the native cleanup boundary nor a one-shot Hit-completion event.

Do not use callback return as lifecycle authority.

## Step B3 — COMBATMOVE STARTRECOVER CANDIDATE REJECTED

Source commit:

`86fd222ace9ef27e88f4846cf0f720c32dce6f6a` — diagnostic hook for `gCScriptProcessingUnit::sAICombatMoveStartRecover` at tested Game RVA `0x16E360`.

Runtime evidence:

`research/raw/2026-08-26_stepB3_native_startrecover_probe.log`

Established findings:

- On clean 2H and Staff Normal/Quick/Whirl transitions, `sAICombatMoveStartRecover` begins while the Hit is still active, starts the Recover PrimaryFirst motion, and returns while the weapon source is still collision group 7.
- Native `7 -> 5` cleanup occurs only **after** `sAICombatMoveStartRecover` returns.
- In reproduced broken 2H and Staff Whirls, the Hit activates collision and is then replaced directly by an Ambient PrimaryFirst motion with **no StartRecover call and no cleanup**.
- The stale source survives into the next Whirl, which can request `7 -> 7`.
- Thus the defect is not Staff-specific and is not "StartRecover ran but forgot cleanup". The broken path skips the normal CombatMove Recover transition itself.

## Step B3b — NATIVE BLOCK-SKIP COMPARISON VALIDATED

Runtime evidence:

`research/raw/2026-08-26_stepB3b_native_block_skip_comparison.log`

Established findings:

- Native 1H P1 Quick and 1H+Shield P1 Quick animations that have **no Recover animation asset** can still execute `sAICombatMoveStartRecover` and perform correct `7 -> 5` cleanup while the Hit motion/phase remains current.
- The same 1H+Shield no-Recover Quick also produced the bad direct-Ambient/no-StartRecover/no-cleanup path.
- Therefore missing Recover **asset/motion** is separate from skipping the engine's Recover **lifecycle/bookkeeping path**.
- Dual / 1H+1H Quick reproduces the same structural stale path as 2H/Staff.

Current broader block-skip hypothesis:

> A skip during an active Hit may abandon some CombatMove/gameplay ownership while the physical Hit motion continues. Depending on timing, movement/collision activation may be lost before contact, or already-active collision may later miss cleanup. The stale-collision branch is confirmed; the early-Hit activation/movement-loss branch remains visual/working-hypothesis evidence.

Raise is not a cleanup fix. A skip during a pre-Hit Raise can occur before offensive Hit collision exists; a later Hit may then start a fresh lifecycle.

## Step B4/B4b — NATIVE CLEANUP CALL-SITE ARCHITECTURE VALIDATED

Source commit:

`ddb44930401d1c22821cbde23b16e9845b06a08d` — existing `SetCollisionGroup` hook extended with immediate caller/module/RVA diagnostics only.

Runtime evidence:

- `research/raw/2026-08-26_stepB4_native_cleanup_callsite_probe.log`
- `research/raw/2026-08-26_stepB4b_native_manyattacks_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_finishing_blow_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_interruption_cleanup_callsite.log`

Durable detailed map:

`docs/COLLISION_CLEANUP_CALLSITE_MAP.md`

Established findings:

- Every exact player-equipped `7 -> 5` cleanup observed by B4/B4b resolved to `Script_Game.dll`.
- Gothic 3 does **not** use one Script_Game cleanup call site for all melee actions. Cleanup is action-path-specific but ultimately calls the same imported entity collision-group setter.
- Confirmed cleanup call-site pairs include:
  - Attack/action 1: RIGHT `+0x3851A`, LEFT `+0x3854E`;
  - Power/action 2: RIGHT `+0x4809D`, LEFT `+0x480E4`;
  - QuickR/L/actions 4/5: RIGHT `+0x48794`, LEFT `+0x487CC`;
  - SimpleWhirl/action 6: RIGHT `+0x4C828`, LEFT `+0x4C858`;
  - full Whirl/action 10: RIGHT `+0x4E03C`;
  - Pierce/action 11: RIGHT `+0x477E3`, LEFT `+0x4781C`;
  - Hack/action 14: RIGHT `+0x432BC`;
  - Finishing/action 15: RIGHT `+0x4178A`, LEFT `+0x417C2`;
  - GetUpAttack/action 30: RIGHT `+0x41E10`.
- The exact same serialized 2H `FinishingAttack_Hit` motion was observed under action 14 (`gEAction_HackAttack`) and action 15 (`gEAction_FinishingAttack`) and cleaned through different Script_Game functions. This is direct evidence that native action semantics, not the filename alone, select lifecycle behavior.
- A separate interruption cleanup call site `Script_Game + 0x24AFF` was repeatedly observed while the routine still reported the original attack Hit; a few milliseconds later PrimaryFirst was replaced by Stumble/knockdown. Normal action completion and damage/reaction interruption therefore already use different native cleanup paths.
- The known block-skip failure can bypass normal action cleanup and fail to receive the interruption cleanup path, leaving offensive collision stale.

Architectural consequence:

> Do not build the production guard as one hook per attack-family cleanup function. The action-specific call sites define native success, but the production goal remains one execution-level end/replacement rule.

The B4/B4b map also strengthens the project rule that reverse-engineered call sites missing from the SDK should be documented with module/RVA/context rather than left only in chat.

## Research Order Decision

Keep two problems separate:

1. **First:** finish the universal execution-level collision safety rule. It must protect native and marked Hits against any genuine abnormal end/replacement, including block skip, damage interruption, terrain interruption, and other causes.
2. **Later / optional:** investigate the deeper native block-skip defect itself, potentially preserving movement and other CombatMove-owned behavior instead of only repairing collision cleanup.

Do not make the universal collision guard depend on fixing this one block-skip cause.

## Immediate Research Question — B5 COMMON PARENT / POST-OPPORTUNITY BOUNDARY

B4/B4b show that the immediate cleanup callers are action-specific. Before hooking those functions individually or broadening directly to Script `OnTick`, ask:

> Do the action-specific Script_Game cleanup paths converge on a common caller/dispatcher/CombatMove boundary after their native cleanup opportunity?

Preferred narrow next probe:

- keep the existing `SetCollisionGroup` hook as the only collision-group hook;
- for exact player weapon `7 -> 5` cleanup records, capture a short caller stack / higher causal parent frames if this can be done reliably in the tested Win32/MSVC build;
- compare Normal, Quick, Power, Pierce, SimpleWhirl, full Whirl, Finishing/Hack, GetUpAttack, and interruption cleanup;
- no cleanup behavior, timers, polling, family-specific repair or production lifecycle state yet.

If higher caller frames converge, inspect that common parent in the binary reference before considering `sAICombatMoveItlLoop` as the fallback diagnostic boundary.

## Current Testing Rule

For immediate lifecycle/cleanup research, prefer **native/unmarked attacks** so Gothic 3's own activation and cleanup are causally isolated. Reintroduce marked fixtures later to prove that marked and native attacks converge on the same end-of-Hit cleanup rule.

## Documentation Rule

Maintain `docs/COLLISION_CLEANUP_CALLSITE_MAP.md` and `SOURCE_HOOK_GUIDE.md` as project-local reverse-engineering knowledge. Useful hooks/call sites absent from or incomplete in the SDK should record module, RVA/address, tested build/context, purpose, and confidence/signature evidence where known. This may later support upstream SDK improvements.

Stable Step-B findings should also be promoted into `EVIDENCE_LEDGER.md`; the call-site map is the detailed source for B4/B4b rather than duplicating every address in multiple long documents.

## Compatibility Clarification

The current animation-behavior DLL was deliberately removed from the game installation during the native-only cleanup research to keep the tests clean. Its absence in these runs is **not** evidence that the animation-behavior DLL failed with the newer mod/configuration.

## Repository Access Note For New Sessions

For GitHub-backed project work, use the connected GitHub repository interface as the authoritative assistant-side access path.

Do **not** assume the assistant's local/container runtime has outbound network access to GitHub. A local `git fetch`, `git pull`, clone, or raw HTTP request from that runtime may fail even while the connected GitHub interface can read and write the repository normally.

Practical rule for a new Chat or Work session:

1. read this file through the connected GitHub interface;
2. use the connected GitHub interface for repository reads/writes, commits, branch inspection, and source/document access;
3. use the user's home-PC checkout for actual local `git pull`, build, install, and Gothic 3 runtime testing;
4. use assistant local/container filesystem/network only when a task genuinely requires it and access has been verified.

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

Keep this file short. Update it only when the active problem, validated checkpoint, or immediate next step materially changes.
