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

Marked and native attacks should differ primarily in activation timing. Use **System 2 source-aware cleanup only if evidence proves cleanup is genuinely source-specific or partially independent**.

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

Runtime test covered 2H Normal, Quick, clean Whirl, and two reproduced Whirl skip/stale-collision cases.

Established findings:

- `eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst Hit-acquisition and successor/replacement signal in the controlled cases.
- In the two stale Whirl reproductions, successor `PlayMotion` exposed replacement roughly 0.51–0.66 seconds before the old Script `OnTick` probe detected the mismatch.
- The `PlayMotion` before-snapshot is often already empty; outgoing execution identity must therefore be retained from prior Hit acquisition rather than recovered from that before-snapshot.
- `StopMotion(type 0)` is supporting evidence only and did not provide the authoritative skipped-Whirl replacement signal.
- In clean 2H Normal, Quick, and Whirl transitions, successor Recover `PlayMotion` occurred first and native weapon cleanup `7 -> 5` followed about 0.059–0.062 ms later, effectively in the same transition/update.
- Therefore a production guard must **not** clean immediately inside successor `PlayMotion`; Gothic 3 must first get its normal same-transition opportunity to perform cleanup.
- Unfiltered global PrimaryFirst logging is too noisy for later research/production; future diagnostics should be narrowly filtered or correlated.

The old `OnTick` lifetime probe remains only as a temporary comparator. Do not promote it to production architecture.

## Step B2 — ORIGINAL-CALLBACK BOUNDARY PROBE RUNTIME DATA CAPTURED

Source commit:

`106209bdefa6c9c52e1f1408a3d148dd52b2664e` — add player-filtered BEGIN/END diagnostics around the existing unsuppressed original Normal/Quick/Whirl callback calls.

No hook, timer, polling/checking path, lifecycle state, cleanup behavior, or special-case behavior was added. Marked-Hit suppression and collision control remain unchanged.

Runtime evidence has been captured and pushed:

- full log: `research/raw/test_Script_FrameCollisionTest.log`;
- filtered Hero event extract: `research/raw/2026-08-26_stepB2_player_event_extract.log`.

The filtered extract exists specifically because the full 152k-line log can exceed GitHub connector/file-response limits. Preserve the full log as raw evidence; use the filtered extract for normal analysis.

Current causal question:

> After successor PrimaryFirst starts, does native collision cleanup occur inside Gothic 3's original `OnAI_Attack`, `OnAI_QuickAttack`, or `OnAI_WhirlAttack` callback call?

If native cleanup occurs between original-callback entry and return, that return is a promising natural point at which Gothic 3 has already had its cleanup opportunity. This could avoid both immediate-PlayMotion cleanup and a polling/timer fallback.

Do **not** implement production cleanup until the Step B2 runtime ordering has been interpreted.

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
