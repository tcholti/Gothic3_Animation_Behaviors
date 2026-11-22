# Hack / Finishing transition — narrow diagnostic investigation

**Status:** ACTIVE — diagnostic DLL deployed with POP-03 SHA/inventory PASS; startup and behavioral runtime tests not yet performed.
**Branch:** `development` (not `main` or `Backup`).
**Opened:** 2026-11-22.
**Purpose:** Determine whether the visible brief leg pose change at the Hack Hit→Recover boundary comes from a Finishing motion/pose or from native blending of the actual Hack resources. No production fix is selected.

## Established input (User runtime observations)
- The actor has separate 2H Hack Raise/Hit/Recover and separate Finishing assets; all exist in `Data/_compiledAnimation`.
- If Hack and Finishing resource contents are identical despite separate names/markers, the visual problem disappears.
- With different motion content, ordinary Hack briefly moves legs oddly near Recover; true Finishing executions have no problem.
- Alfinos reports Hack Raise, Hit and Recover, not a Finishing motion, during the reproduced attack.
- Recover phase assets are not universally required for Gothic 3 attack execution; do not assume a missing Recover file.
- The User's installed first-release G3AB DLL SHA256 is `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`; production binary has not been changed.

## Narrow source fact / distinction
- `AttackMotionRouting::QueryOptionalSubstitution` substitutes existing `_HackAttack_` resource data for factual Action14's native `_FinishingAttack_` lookup. Original requested name and native action remain independent facts. No claim yet that a Finishing motion is actually blended.
- Prior EV-399 / EV-422 confirmed speed separation and transition sanity in their tested fixtures, but did not exercise the new pose-divergence case.
- The first causal question is what motion resource/slots, target weights and blend facts Gothic reports during the immediate transition.

## Diagnostic build contract
- Research-only target: `tools/Script_G3AB_HackTransitionProbe/`, opt-in via `G3AB_BUILD_TOOLS=ON`.
- Compiles the same source modules as `Script_G3AnimationBehaviors`, with `G3AB_HACK_TRANSITION_PROBE` conditional observation hooks; disabled production path retains original behavior.
- Observes player Action14/15 resource requests/results, motion Play/Stop, StartRecover boundary, and a short (~3s) tick window of the five motion slots. Log: `G3AB_HackTransitionProbe.log` in Gothic 3 runtime root.
- Diagnostics do not change routing policy, speed/movement, markers or gameplay decisions. Do not co-load this DLL with production or other G3AB research DLLs.
- Local Release diagnostic build PASS (2026-11-22), SHA256: `A8FF8B4CE8A78F07FD05FA73A8C09983FC4E97EEA8975150CE2394114824918E`. This is build identity, not runtime acceptance.
- Deployment 2026-11-22: Gothic3.exe confirmed closed; original installed release DLL SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9` moved, unchanged, to `E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\2.For AI to store\G3AB_HackTransition_2026-11-22\Script_G3AnimationBehaviors.dll`. Diagnostic copied to live `scripts` and verified exactly one G3AB runtime DLL, built/live SHA256 identical. **DIAGNOSTIC DEPLOYMENT PASS**. Startup log `G3AB_HackTransitionProbe.log` not yet created as of deployment verification; start game only to main menu for first load check.

## Frozen next runtime procedure
1. User closes Gothic 3 normally; do not modify live DLLs while the process is running.
2. Move the currently installed release DLL to a safe location **outside** `scripts`; deploy only `Script_G3AB_HackTransitionProbe.dll`. Preserve third-party New Balance and AttackCollision DLLs. Require exactly one G3AB project DLL and matching built/live SHA256 (POP-03). Verify startup banner/load at main menu first (POP-04); failure means restore production, stop.
3. Load the existing save with **different** 2H Hack and Finishing animations installed and execute ~3 regular Hack attacks, noting whether the brief leg movement occurs. Do not alter animation or INI files.
4. Preserve the exact raw log under `research/raw/` via POP-05/06; inspect whether any Finishing resource/motion, secondary layer, altered target weight, or unexplained pose interpolation appears across Hit→Recover. If no clue, make the next hypothesis explicit rather than forcing a fix.
5. Restore the known release DLL after the test; do not publish/ship the probe DLL.

**Stop conditions:** game startup/load failure; unexpected DLL coexistence; missing log banner; incorrect resource hook behavior; game crash; effect on normal combat. No change to `main` or `Backup` without separate approval.
