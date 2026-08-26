# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat  
**To:** Normal Chat / home-PC runtime validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B3 Result — STARTRECOVER CANDIDATE REJECTED

Runtime evidence:

`research/raw/2026-08-26_stepB3_native_startrecover_probe.log`

Established:

- clean native Normal/Quick/Whirl paths call `sAICombatMoveStartRecover`, start Recover, return, then perform native `7 -> 5` cleanup afterward;
- broken native 2H and Staff Whirl executions activate `5 -> 7`, skip `StartRecover`, are replaced directly by Ambient, and miss cleanup;
- stale collision was also previously reproduced on Dual / 1H1H Quick, so the defect is known beyond Whirl and beyond 2H/Staff;
- therefore `StartRecover` is not the post-cleanup boundary.

## Current block-skip hypothesis — TEST, DO NOT ASSUME

The stronger current hypothesis is not that missing Recover or missing Raise causes stale collision.

Instead, the vulnerable event may be the block-timeout/skip occurring **during Hit playback**:

1. the real Hit motion continues playing;
2. combat action/phase or some still-unidentified CombatMove ownership/bookkeeping leaves that Hit;
3. offensive collision is already active;
4. when the physical Hit motion later ends/replaces, the normal lifecycle path that would perform cleanup is no longer owned/reached;
5. collision remains stale.

`Raise` is not proposed as a cleanup fix. A long Raise may merely absorb the block skip **before** offensive Hit/collision begins. The subsequent Hit can then start as a fresh execution and complete normal cleanup.

Likewise, a missing Recover **animation asset** is not equivalent to skipping the engine's Recover **transition/bookkeeping**. Older tests indicated native Quick attacks with no Recover animation could still clean correctly.

The exact meaning of "ownership" above is unproven. B1 established only that action/phase can drift while the exact PrimaryFirst Hit motion continues.

## B4 CALL-SITE PROBE — PAUSED BEFORE WORK

Do **not** execute the previously planned native cleanup call-site probe yet.

Run the comparison below using the existing B3 diagnostic build first.

## Immediate no-code comparative test

All current custom replacement animations are temporarily removed, so use Gothic 3's native assets and native collision timing.

Capture controlled examples of:

1. **1H Quick P1 with no native Recover animation** — normal completion and, where practical, from/around block timing;
2. **1H + Shield Quick P1 with no native Recover animation** — same comparison;
3. **1H and 1H + Shield Quick paths that do have Recover** — normal completion, then attempt block interruption during Recover;
4. **Dual / 1H1H Quick** — reproduce the known block-skip stale-collision case;
5. **Finishing Attack with long Raise**, if practical — reproduce the comparable block skip during Raise and confirm the later Hit still starts and cleans.

No source change is required. The B3 logger already records player PrimaryFirst transitions, `sAICombatMoveStartRecover`, collision-group changes, action/phase context, and equipped source identity.

## Causal questions / predictions

Determine separately:

- Does a native Quick with **no Recover asset** still execute `StartRecover` or another lifecycle transition and perform `7 -> 5` cleanup?
- If a Quick has a real Recover and block interruption occurs **during Recover**, was collision already cleaned at the Hit -> Recover boundary, making that interruption harmless?
- Does Dual / 1H1H Quick block-skip show the same structural shape as 2H/Staff: Hit motion continues/replaces while action/CombatMove ownership has already left it, then cleanup is missed?
- On a finishing attack, can the block skip occur during Raise before offensive Hit/collision begins, after which the Hit starts fresh and cleans normally?

Do not infer causality from filename presence alone. Distinguish physical PrimaryFirst motion playback from action/phase/CombatMove lifecycle ownership.

After this comparison, decide whether the next source probe should trace the native cleanup call site, the Hit-entry/CombatMove ownership path, or both.

## Documentation rule after this comparison

After the new runtime evidence is interpreted, promote durable findings out of this transient bridge into the canonical project docs, especially `EVIDENCE_LEDGER.md`, `SESSION_ENTRYPOINT.md`, and `COLLISION_LIFECYCLE_PLAN.md`.

Also preserve reverse-engineered hook/call-site discoveries in `SOURCE_HOOK_GUIDE.md`. Any useful hook/call site not directly declared by the SDK should be recorded with at least module, RVA/address, tested build/context, purpose, and confidence/signature evidence when known. This project-local hook record may later help upstream SDK research or updates.
