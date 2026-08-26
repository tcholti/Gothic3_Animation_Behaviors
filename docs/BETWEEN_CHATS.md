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
- therefore `StartRecover` is not the post-cleanup boundary and the defect is not Staff-specific or Whirl-specific.

## B4 CALL-SITE PROBE — PAUSED BEFORE WORK

Do **not** execute the previously planned native cleanup call-site probe yet.

Older validated observations introduce two high-value counterexamples that should be compared first with the existing B3 diagnostic build:

1. native/unmarked Quick attacks with Recover animations absent were previously observed still cleaning collision correctly;
2. finishing attacks with a Raise transition can survive the problematic block/attack transition without leaving stale collision, even when the analogous no-Raise path reproduces the skip.

Also, stale collision has previously been reproduced on Dual / 1H1H Quick, so the defect is already known to extend beyond Whirl and beyond 2H/Staff.

## Immediate no-code comparative test

Use the existing B3 DLL. No source change is required.

Keep all tested attacks unmarked / native-collision controlled.

Capture a short run containing, where practical:

1. one known bad no-Raise attack performed from holding block that reproduces stale collision;
2. one Dual / 1H1H Quick stale-collision reproduction;
3. one Quick path with its Recover animation absent that nevertheless cleans correctly, using the same setup previously tested;
4. one finishing attack with Raise, performed through the comparable block/attack transition, where cleanup remains correct.

The current B3 logger already records PrimaryFirst motion transitions, `sAICombatMoveStartRecover`, collision-group changes, action/phase context, and equipped source identity.

## Causal questions

Determine separately:

- Does a no-Recover-animation Quick still call `StartRecover`, even though no Recover motion exists?
- Does its native `7 -> 5` cleanup still occur after that transition attempt?
- On a bad block -> Hit/no-Raise path, is `StartRecover` skipped because the Hit entered through a different CombatMove state?
- On the comparable finishing attack, does Raise establish a state/path that later permits normal cleanup?
- Does Dual / 1H1H Quick show the same lifecycle shape as the 2H/Staff stale cases?

Do not infer that missing Recover animation itself causes the defect. Distinguish missing Recover **asset/motion** from skipping the engine's **Recover transition path**.

After this comparison, decide whether the next source probe should trace the native cleanup call site, the Hit-entry/CombatMove state path, or both.
