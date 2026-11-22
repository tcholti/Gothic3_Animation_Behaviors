# Hack / Finishing Recover transition investigation

**Status:** ACTIVE — first runtime evidence EV-458 analyzed and archived; native-first Recover ordering confirmed; no correction selected.
**Branch:** `development` only. **Opened:** 2026-11-22.

## User-established visual behavior
- Separate 2H Hack Raise/Hit/Recover and separate true Finishing execution animations all exist. Files intentionally differ and only Hack assets contain authored collision markers.
- Visually distinct Hack and Finishing animation content produces a very brief unnatural leg motion at Hack Hit→Recover. Identical animation content with different names/markers removes it. True Finishing executions are visually normal even with divergent Hack assets.
- Alfinos reports Hack Raise, Hit and Recover, but does not expose the intermediate native Recover motion. Recover animation files are not universal prerequisites; missing-asset speculation is excluded by inspection.
- The User confirmed that the visual leg discontinuity occurred in **each of the three captured Hack attacks (3/3)** and is noticeable for under one second. Their explanation: brief initial Finishing Recover activation may perturb the armature's blended pose, with lingering correction as Hack Recover takes over. This residual blending/pose-carryover mechanism remains a hypothesis until intervention; distinguish it from the confirmed native-first event sequence.

## Confirmed first diagnostic result — EV-458
- Runtime fixture: 3 factual Hack/Action14 + 2 true knocked-down-opponent Finishing/Action15 executions, with the different 2H assets installed.
- In each factual Hack, `sAICombatMoveStartRecover` first plays primary **FinishingAttack Recover** at time 0, **before** the later CombatMove resource query selects the existing **HackAttack Recover** and plays it. All three cases show the identical ordering and clock tick.
- In both factual Finishing executions, native StartRecover plays Finishing Recover first and the later native resource query plays Finishing Recover again; there is no change of animation content.
- This is **confirmed motion invocation/selection order**, not proof that the transient Finishing motion contributed a rendered frame, bone pose or measurable nonzero blending interval. That final causal link remains for a narrowly isolated test.
- Archival proof: `research/archive/2026-11-22_hack_transition_player2h_three_hack_two_executions.log` (SHA256 `C8C8B583EC76A69FA6EB595E2C77B36116DE2F9EF1BB6E4A04A4752A0A005632`). Evidence ledger EV-458 owns run details and limits; SOURCE_HOOK_GUIDE owns engine seam fact.

## Diagnostic and live installation
- Observation-only full-production source twin: `tools/Script_G3AB_HackTransitionProbe/`, built as `Script_G3AB_HackTransitionProbe.dll` with opt-in diagnostic flag; target SHA256 `A8FF8B4CE8A78F07FD05FA73A8C09983FC4E97EEA8975150CE2394114824918E`.
- Startup/load and first runtime log PASS; no diagnostic DLL remains installed. Release `Script_G3AnimationBehaviors.dll` was restored to live `scripts` after the test, verified sole G3AB product with accepted SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`.
- Diagnostic and preserved release copies are held in `E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\2.For AI to store\G3AB_HackTransition_2026-11-22`. Installed animations, INI and third-party DLLs unchanged.

## Next bounded research question
How can the initial Finishing Recover motion in factual Hack/Action14 be prevented from influencing the pose **before** the routed Hack Recover, without breaking the native Recover lifecycle, valid asset fallback, Action15 executions, other combat actions, Speed/Movement/collision or one-hook-owner safety?

Read-only seam review: native `Game+0x16E360` StartRecover enters before the later routed resource query; high `PlayMotion` is `Engine+0x30860`. SDK exposes primary motion, intro/extro blending and target-weight getters; EV-458 captured 0.2000 intro/extro parameters, **not** measured blend duration or rendered bone changes. Compare a narrow, Action14-and-existing-Hack-Recover-only interception of the first native Finishing Recover `PlayMotion` (suppress once or substitute correct motion) against doing nothing; preserving native lifecycle/fallback is a hard gate. The best *causal probe* alters only that first motion for the known 2H fixture and measures whether visible discontinuity vanishes. True Finishing/Action15, other actions, missing Hack assets, other actors, speed/movement/collision and one-hook-owner safety must remain unchanged. **No implementation or production fix approved yet.**

**Stop conditions:** unresolved action ownership, missing Hack Recover fallback semantics, altered true Finishing behavior, cross-actor/global hook interference, changed collision/Speed/Movement, unsupported pointer lifetime, or broader hook replacement. Keep `main` and `Backup` untouched. Review proposed options before any intervention build/deploy.
