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

The B3 test deliberately used native/unmarked attacks so marker-driven OFF transitions could not be mistaken for Gothic 3 cleanup.

Established findings:

- On clean 2H and Staff Normal/Quick/Whirl transitions, `sAICombatMoveStartRecover` begins while the Hit is still active, starts the Recover PrimaryFirst motion, and returns while the weapon source is still collision group 7.
- Native `7 -> 5` cleanup occurs only **after** `sAICombatMoveStartRecover` returns. Example Staff Whirl: StartRecover BEGIN `88819.525`, Recover PlayMotion result `88819.622`, StartRecover END `88819.644`, native cleanup `88819.704`.
- Therefore StartRecover is not the post-cleanup boundary.
- In reproduced broken 2H and Staff Whirls, the Hit activates collision and is then replaced directly by an Ambient PrimaryFirst motion with **no StartRecover call and no cleanup**.
- The stale source survives into the next Whirl, which can request `7 -> 7`.
- Thus the defect is not Staff-specific and is not "StartRecover ran but forgot cleanup". The broken path skips the normal CombatMove Recover transition itself.

This strongly supports an execution-level rule based on actual Hit replacement, but the correct post-native-opportunity repair point is still open.

## Immediate Research Question — B4 Cleanup Call-Site Ownership

Before broadening to the whole `sAICombatMoveItlLoop`, prefer the narrower diagnostic question:

> Which exact native caller/call site performs the clean `SetCollisionGroup(Item_Equipped)` / `7 -> 5` reset after StartRecover returns, and what enclosing function provides the post-opportunity boundary?

Preferred smallest probe: extend the **existing** SetCollisionGroup diagnostic only for relevant player weapon cleanup events to record the immediate return/caller address (and module/RVA if practical), without changing behavior or adding lifecycle state.

Then inspect that call site in the tested binary reference. If it identifies a narrow enclosing combat transition function, probe that function rather than defaulting to a broad per-update loop.

Do not add cleanup, timers, new polling, or family-specific repair rules yet.

## Current Testing Rule

For immediate lifecycle/cleanup research, prefer **native/unmarked attacks** so Gothic 3's own activation and cleanup are causally isolated. Reintroduce marked fixtures later to prove that marked and native attacks converge on the same end-of-Hit cleanup rule.

## Repository Access Note For New Sessions

For GitHub-backed project work, use the connected GitHub repository interface as the authoritative assistant-side access path.

Do **not** assume the assistant's local/container runtime has outbound network access to GitHub. A local `git fetch`, `git pull`, clone, or raw HTTP request from that runtime may fail even while the connected GitHub interface can read and write the repository normally. Do not treat such a local-network failure as evidence that the repository is unavailable.

Practical rule for a new Chat or Work session:

1. read this file through the connected GitHub interface;
2. use the connected GitHub interface for repository reads/writes, commits, branch inspection, and source/document access;
3. use the user's home-PC checkout for actual local `git pull`, build, install, and Gothic 3 runtime testing;
4. use assistant local/container filesystem/network only when a task genuinely requires it and access has been verified.

If a large repository file cannot be returned through the connected interface, prefer a targeted extract/smaller derived evidence file rather than falling back to repeated assumptions about local GitHub network access.

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
