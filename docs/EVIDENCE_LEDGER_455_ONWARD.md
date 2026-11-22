# Gothic 3 Animation Behaviors — Evidence Ledger EV-455 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-10-08

## Purpose

Record evidence after the closed EV-417–EV-454 first-release integration volume.

This ledger is proof history, not the normal knowledge interface. Established facts belong in their current reference/architecture owners; `EVIDENCE_INDEX.md` routes proof-sensitive retrieval.

## Entries


### EV-455 — First-release checkpoint review READY

Observed:
- reviewed `development @ 99ed4ac0b4883a082340c3eee41ae67ec69cb92a` against stable `main @ e899f37092706a9846312b93d6b52b34e715b53d`;
- `main` is an exact ancestor of the reviewed development checkpoint;
- only production-source delta is `src/Script_G3AnimationBehaviors/EngineBridge.cpp`;
- production INI is unchanged from stable main;
- no compiled binary/archive is tracked in the branch delta;
- raw intake contains only `Keep.txt`;
- public/integration product remains `Script_G3AnimationBehaviors.dll`;
- accepted built/live production SHA256 remains `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`;
- knowledge-state validation PASS and current worktree clean.

Maintenance performed before verdict:
- corrected stale root README current-product routing;
- rotated closed EV-417–EV-454 ledger to archive and opened EV-455 onward.

Limits:
- this is a repository/release checkpoint review, not a new gameplay validation campaign;
- promotion to main is deliberately not automatic.

Disposition:
- **READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT.**


### EV-456 — Quick pre-promotion documentation review PASS

Reviewed documentation checkpoint:
`development @ 8d42e9fc9de1e6c07bc6dbbf6972d921804474c2`

Scope:
- deliberately shallow pre-promotion review only;
- current-state/release wording;
- stale active-task/current-feature claims;
- broken active/archive routes;
- contradictions with EV-454/EV-455;
- no broad authority, duplication, compression or repository-structure audit.

Corrections made:
- root README now routes the current decision to first-release main promotion and includes Movement/bad-block surfaces;
- canonical `DESIGN.md` no longer says Raise is active or attack displacement/bad-block protection are future-only;
- accepted Movement architecture is represented in `DESIGN.md`;
- accepted EV-449–EV-454 stateless player bad-block architecture replaces the obsolete future-module concept;
- `PROJECT_PIPELINE.md` now reflects the promoted EV-447 Collision/Speed/Raise/Movement baseline and the current first-release promotion gate;
- `FUTURE_INVESTIGATIONS.md` marks Movement resolved/production-integrated and keeps only exact-pause/NPC bad-block questions as optional future research;
- top-level `SOURCE_HOOK_GUIDE.md` movement rows now agree with the closed §3B mechanism;
- stale current-qualification text in ADR-0006/ADR-0008 was refreshed without rewriting their preserved historical decision bodies;
- two old `docs/work/active/` ADR links were repointed to their archived task locations;
- `SESSION_ENTRYPOINT.md` date/frozen-state wording now matches the release checkpoint.

Verification:
- no live non-archive `docs/work/active/<task>.md` references remain;
- `docs/work/active/` contains only its README placeholder;
- remaining historical "Speed active / Raise follows" wording is inside the explicitly preserved historical ADR-0006 decision body;
- `git diff --check` PASS on the review changes;
- knowledge-state validation PASS;
- no release/product code or INI change was made.

Disposition:
- **PASS — DOCUMENTATION IS CLEAN ENOUGH FOR FIRST-RELEASE MAIN PROMOTION.**
- larger documentation/repository review remains intentionally deferred until after the stable main checkpoint is created.


### EV-457 — First-release stable promotion PASS

Observed:
- preflight verified clean local `development`, remote `development` and reviewed EV-456 checkpoint all matched `08a0bd8fcf42173088e233e09b706a80da882070`;
- previous `main @ e899f37092706a9846312b93d6b52b34e715b53d` was an ancestor of the reviewed development checkpoint;
- promotion used a normal fast-forward push from `development` to `main`;
- post-push verification showed remote `main` and remote `development` both exactly at `08a0bd8fcf42173088e233e09b706a80da882070`.

Scope / limits:
- this EV records branch promotion only;
- no product source, INI, runtime binary or release behavior changed during promotion;
- later audit work must not mutate `main`.

Provenance:
- EV-455 = first-release checkpoint review PASS;
- EV-456 = quick pre-promotion documentation review PASS;
- promoted SHA = `08a0bd8fcf42173088e233e09b706a80da882070`.

Disposition:
- **PASS — FIRST-RELEASE STABLE CHECKPOINT PROMOTED TO MAIN.**
- `main @ 08a0bd8fcf42173088e233e09b706a80da882070` is the trusted pre-audit baseline.
- future review/audit work continues on `development` only.

### EV-458 — Hack Recover starts native Finishing before Hack resource replacement (2026-11-22)

Fixture: real Gothic 3 game, release-equivalent `Script_G3AB_HackTransitionProbe.dll` observation twin (build SHA256 `A8FF8B4CE8A78F07FD05FA73A8C09983FC4E97EEA8975150CE2394114824918E`), user-authored *different* 2H Hack and Finishing Raise/Hit/Recover files, New Balance/AttackCollision left installed. User performed **three factual Hack/Action14 attacks** followed by **two actual Finishing/Action15 executions of knocked-down opponents**. Game exited normally.

Canonical source: `research/archive/2026-11-22_hack_transition_player2h_three_hack_two_executions.log` (675 lines / 114,182 bytes; SHA256 `C8C8B583EC76A69FA6EB595E2C77B36116DE2F9EF1BB6E4A04A4752A0A005632`; raw unchanged, published first at `development @ d14603c7aa5472e5c14b81f955d55f1922c4af75`, then archived byte-identically).

Observed independently in all three Hack instances (event clock 679102031, 679108343, 679114359):
- `sAICombatMoveStartRecover` begins with primary **Hack Hit** at final time 0.4800; native Recover start **plays primary Finishing Recover** (`PLAY_AFTER`, slot 0, time 0.0000). The `RECOVER_BOUNDARY AFTER` snapshot still identifies Finishing Recover.
- **Only afterward** the resource query for factual Action14 requests a Finishing-named Recover and the G3AB router returns a **Hack** resource; a second `PlayMotion` sets primary **Hack Recover** (time 0.0000). This ordering occurs 3/3. All observations at each boundary share the same integer-millisecond timestamp; do not infer a measured nonzero time interval.
- Corresponding original Recover resources are present; no missing-Hack-Recover fallback was involved. The diagnostic only exposed slot 0 in these snapshots (target weight 1.0, blend mode 1, intro/extro 0.2000). It does not directly measure final rendered bones or transient internal blend weights.

Control in the two genuine executions (clock 679138750, 679143000): factual Action15 similarly starts **Finishing Recover**, then a native Finishing resource lookup occurs, followed by another **Finishing Recover** `PlayMotion`. Thus the native-first sequence is not unique to Hack, but the **content-changing** Finishing-to-Hack Recover replacement is. This is consistent with the User's prior visual A/B results: different animation content causes a very brief Hack-only leg movement; identical Hack/Finishing contents do not; true Finishing executions look correct. The User subsequently confirmed the leg discontinuity was visible in **all 3/3 Hack attacks during this captured run**, lasting **less than a second**; true Finishing executions continued to look normal. The User's proposed mechanism is that even a very brief incorrect Finishing Recover activation could initialize the armature's pose/blending, so the following Hack Recover takes additional time to settle. That is a **plausible hypothesis**, not a directly measured render/blend fact.

Interpretation: **CONFIRMED native-first Recover motion ordering and Hack-specific content-changing second playback**, strongly implicated in the leg-pose discontinuity. **NOT YET PROVEN:** that the first motion is actually sampled/rendered or held for a nonzero blend interval; this requires a narrowly isolated causal intervention or more direct pose observation. No production behavior or animation files were changed and no fix accepted.

Disposition: **NEW CANONICAL EVIDENCE — ARCHIVED PROVENANCE**. Immediate next research: determine a minimum safe way to prevent the first Finishing Recover pose from affecting factual Hack while preserving Action15, absent-Hack-resource native fallback, the Recover lifecycle, collision/Speed/Movement and shared hook ownership.

### EV-459 — Scoped first-Finishing Recover suppression removes the visible 2H Hack glitch (2026-11-22)

Fixture: continuation of EV-458 with the same visually different two-handed Hack and Finishing animation sets, game INI, New Balance and AttackCollision installed. The separate **research-only**, full-production-source causal twin `Script_G3AB_HackRecoverCausalProbe.dll` (Release SHA256 `E194E58C25102286492B602218C75CC817F250631E189B873E4EA08DDE35E89A`) was deployed as the sole G3AB DLL after hash/inventory checks. Main-menu startup banner PASS. User performed **three normal Hack/Action14 attacks and two true Finishing/Action15 executions** of knocked-down opponents; the game exited normally.

Canonical raw evidence: `research/archive/2026-11-22_hack_recover_causal_three_hack_two_finishing.log`, 920 lines, 162,556 bytes, SHA256 `73FBDCFC672DFBEB0EFBAF486227492CB48427B78AC112A9E7167814F28F6B9B`. Copied from the game into `research/raw/` and moved to archive byte-identically after processing; raw intake now contains only `Keep.txt`. EV-458 remains the original unmodified baseline.

Diagnostic intervention, **not a production fix**: for factual player Hack14 inside native `sAICombatMoveStartRecover` only, the first primary `PlayMotion` was suppressed after matching the exact 2H Finishing Recover motion descriptor and obtaining a valid corresponding Hack Recover resource via the engine admin. Native StartRecover continued, the existing resource router later selected Hack Recover, and the original subsequent `PlayMotion` played it. Guard failures fall back to native, and genuine Finishing15 was excluded. This probe uses a hardcoded single 2H fixture and stores the observed animation-admin pointer: its implementation is not automatically suitable for shipping.

**Observed, all 3/3 Hack trials** (clock 681880140, 681883203, 681886375):
- `CAUSAL_SUPPRESS_FIRST_NATIVE_FINISHING action=14` occurred exactly once for each Hack, followed by `PLAY_SUPPRESSED`, with **zero `CAUSAL_FALLBACK` events**. No first Finishing Recover `PLAY_AFTER` appeared within those Hack transitions.
- The following factual Action14 request selected a Hack resource, and `PLAY_AFTER` started the exact `Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot` on primary slot 0 in each of the three trials.
- User observed **no visible leg glitch in any of the three Hacks (0/3)**, in contrast to visible glitch 3/3 with the observation-only baseline EV-458.

**True Finishing controls, 2/2** (clock 681912625, 681917031): native first Finishing Recover `PLAY_AFTER`, factual Action15 native Recover resource lookup, and second Finishing Recover `PLAY_AFTER` all remained present; **no suppression** occurred. The User reported completing both true executions; no abnormality was reported. The log confirms native motion routing for these trials, not a full gameplay regression across every combat mode.

**Conclusion:** **CAUSAL INTERVENTION PASS for the exact player 2H fixture.** Preventing the preliminary wrong Recover playback removed the repeatedly observed Hack-only visual discontinuity, with normal later Hack Recover and two true Finishing controls. This establishes strong causal evidence for the unwanted native-first Recover playback as the correction target; it does not measure internal bone blending, prove wider weapon/NPC coverage, or validate resource fallback when Hack Recover is missing. Production correction and generalization remain a separate design/review gate.

Post-test: original release `Script_G3AnimationBehaviors.dll` restored as the only G3AB DLL in live `scripts`, SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`. Causal probe DLL preserved under the User's `2.For AI to store/G3AB_HackRecoverCausal_2026-11-22` folder, same built SHA256. Original animation assets, INI, `main` and `Backup` unchanged.

**Disposition:** **ACCEPTED BOUNDED CAUSAL RESEARCH; NOT PRODUCT ACCEPTANCE.** Next bounded step is a production-architecture proposal that derives the correct asset/actor/action context safely and preserves native fallback, with no reliance on the hardcoded player 2H fixture, no hook duplication and no interference with genuine Finishing/other combat. No production implementation has yet been approved.

### EV-460 — Simulated-null Hack Recover experiment rejected as non-representative (2026-11-22)

**Evidence:** User ran the research-only `Script_G3AB_HackMissingRecoverProbe.dll` with all authored 2H animations still installed. Immutable raw log `research/archive/2026-11-22_hack_missing_recover_simulated_null_runtime.log`, **1,213 lines / 222,141 bytes / SHA256 `9B9D1D27300C51A7FD8BCA2CC8C75CAAA770419F3FEDF07F07BA9120659EA3CA`** (first published separately to raw at commit `f821ff6c23e518d859637957c6482f70b3bbcb33`).

**Actual observations:** Four factual Hack14 StartRecover entries, all with the expected active custom Hack Hit, but only **one** `MISSING_PROBE_SUPPRESS_FIRST_FINISHING` and one forced `nullptr` Recover lookup. The three later Hack StartRecover entries had **no** matching first-play suppression nor Recover resource query. Three factual Finishing15 sequences were recorded, with native Finishing Raise and Hit resources selected, but **no Finishing Recover PlayMotion or Recover resource request** in the captured trace. No explicit Action15 suppression call occurred. User reported that the character held the Hit-end pose until releasing mouse buttons, then went idle, and suspected Finishing Recover had also been affected. The evidence shows abnormal/unrepresentative Recover progression; it cannot establish causality for the later Finishing behavior or prove any natural missing-file path.

**Disposition: INVALID AS A MISSING-ANIMATION TEST; RETAIN FOR PROVENANCE, DO NOT GENERALIZE.** The experimental hook manufactured a `nullptr` from a higher-level `.fxm` query while files remained installed, which is not equivalent to letting the engine request and fail to load an actually absent Recover resource. The User rejected this design and requested a production-shaped test that genuinely queries the Hack Recover asset while they independently remove it between runs. **No code-forced missing result is permitted in the next candidate.**

**Safety closure:** Gothic3.exe closed; original release `Script_G3AnimationBehaviors.dll` restored as the sole live G3AB product (SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`), invalid probe moved outside the game to `2.For AI to store/G3AB_HackMissingRecover_2026-11-22/` with original SHA256 `4BBDD080D29D16E532892C15478D54EDD3A57450DA69B5E3A4A5633EEA9CD254`. No animation file, INI, `main` or `Backup` changed. EV-459's accepted positive-asset causal result remains independent and valid.

### EV-461 — Real-asset Hack Recover positive control, Run A PASS (2026-11-22)

**Fixture:** research-only `Script_G3AB_HackRecoverRealAssetProbe.dll`, build/live SHA256 `9F0C2E8D37B2A32F628DD486A4721AD0669C0E15A5D1CFEDE4AEF852E1277A22`, sole installed G3AB DLL, with all different 2H custom Hack and Finishing animations **present**. Main-menu startup previously PASS. User performed **3 factual Hack14 attacks and 3 genuine knocked-down-opponent Finishing15 executions**, then closed Gothic 3 normally. User observed **all 6 looked fine**.

**Canonical original log:** `research/archive/2026-11-22_hack_recover_real_asset_runA_three_hack_three_finishing.log`, **741 lines, 120,096 bytes**, SHA256 **`250137E04C462D6B4E0EFFF6D26C9C1D0C38F942A11212DE0DE0575EF88A6829`**. Byte-identical raw copy from the game, first committed in `research/raw` at `b215edac501a544be1cf5a49bd1db11765793018` before archive promotion. Gothic3.exe was closed at collection.

**3/3 Hack14 positive-control transitions (clock 688349031 / 688352640 / 688356656):** each had `MISSING_PROBE_OWNED_HACK_HIT` (historical event name; actual real-asset probe), `MISSING_PROBE_SUPPRESS_FIRST_FINISHING`, `REAL_ASSET_PROBE_OWNED_RECOVER_REQUEST`, `REAL_ASSET_HACK_RECOVER_FOUND`, and later `PLAY_AFTER` for exact `Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot`. All three actual engine resource queries returned non-null Hack resources; **zero** `REAL_ASSET_HACK_RECOVER_NOT_FOUND` events. The preliminary wrong Finishing Recover `PlayMotion` was suppressed only for these three Hack transitions; User observed no unusual leg movement or stuck pose.

**3/3 true Finishing15 controls (clock 688383500 / 688389234 / 688396796):** each native `RESOURCE action=15` request selected a non-null native Finishing Recover, and `PLAY_AFTER` logged the actual `Hero_Parade_None_2H_P1_FinishingAttack_Recover_N_Fwd_00_%_00_P0_0.xmot` (twice per native transition). No explicit Hack suppression for any genuine Finishing. This directly fixes the invalid EV-460 comparison, in which Action15 Recover had failed to appear. User confirmed normal visuals.

**Disposition: RUN A PASS for EXACT 2H PLAYER FIXTURE; NOT YET PRODUCTION ACCEPTANCE.** This shows the corrected test uses the real Hack resource without a fabricated missing result and leaves actual Finishing Recover native. Crucially, Run A proves **nothing yet** about the physically absent Hack Recover case. Keep the exact same diagnostic DLL installed for Run B. After verifying no game process, User—not assistant—backs up and manually renames/removes only the loose `Data/_compiledAnimation/Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot`, keeping Finishing Recover and Hack Raise/Hit untouched. Restart game to avoid engine cache, perform short controlled test and exit. Analyze `REAL_ASSET_HACK_RECOVER_NOT_FOUND` versus `FOUND` before claiming the asset was actually absent to the engine; packed archive alternatives may still resolve a resource. Stop on failure and preserve separate log. Original accepted release DLL remains held unchanged outside game; `main`/`Backup` and all animation assets remain untouched by assistant.

### EV-462 — Real-asset missing Hack Recover Run B: genuine Finishing Recover also absent (2026-11-22)

**Fixture:** same research-only `Script_G3AB_HackRecoverRealAssetProbe.dll` as passing EV-461 Run A (SHA256 `9F0C2E8D37B2A32F628DD486A4721AD0669C0E15A5D1CFEDE4AEF852E1277A22`); User manually removed the loose 2H `Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot`. Fresh launch, native two-handed Finishing Recover loose `.xmot` still present on disk. User reported Hack attacks behaved acceptably, with idle reached upon release of mouse buttons, **but genuine Finishing attacks did not play Recover**. Gothic3.exe closed normally at log capture.

**Canonical raw evidence:** `research/archive/2026-11-22_hack_recover_real_asset_runB_missing_hack_finishing_regression.log` (**751 lines, 123,510 bytes, SHA256 `3CD6DFAC3D01228C51EC2D8E4F315EE6F27B31D4EC320C27397B257E4ADE6108`**). Captured byte-identically from the game's probe log, initially committed in `research/raw` at `b8b3852b117a687d21a889bd44ac3fab5a86ef20`, then archived unchanged.

**Diagnostic facts:** four factual Hack14 `StartRecover` entries with active, exact authored custom Hack Hit. Only the **first** had `MISSING_PROBE_SUPPRESS_FIRST_FINISHING` and later `REAL_ASSET_PROBE_OWNED_RECOVER_REQUEST`; the actual `AttackMotionRouting::QueryOptionalSubstitution` returned **null** (`REAL_ASSET_HACK_RECOVER_NOT_FOUND`) with no test-synthesized missing resource. No later Hack Recover PlayMotion in the trace. The next **three** Hack StartRecover entries logged no primary first-play suppression and no Recover-resource query, then other ambient/idle motions eventually started.

Two factual Finishing15 Raise+Hit executions also entered native `StartRecover`, and neither logged `RESOURCE action=15 ... Recover` nor a Finishing Recover `PLAY_AFTER`. No explicit `MISSING_PROBE_SUPPRESS_FIRST_FINISHING` occurred for these Action15 controls. The loose native `Hero_Parade_None_2H_P1_FinishingAttack_Recover_N_Fwd_00_%_00_P0_0.xmot` exists in the game directory, but no request is present in the captured call path. The test does **not** show why native StartRecover did not initiate any Recover playback after the first failed Hack lookup. User report and trace agree that genuine Finishing Recover did not play.

**Comparison:** EV-461 Run A (same DLL, all assets present) had correct Hack Recover 3/3 and native genuine Finishing Recover 3/3. Run B changes actual Hack Recover availability. The regression correlates with that change, but its root cause cannot be attributed to either the diagnostic or native engine from the present evidence alone. **RUN B FAIL; not production acceptance; do not generalize a no-Recover fallback or claim that genuine Finishing is protected.**

**Safety / next decisive control:** Original release `Script_G3AnimationBehaviors.dll` restored as sole G3AB product, SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`; research DLL preserved outside live game, SHA256 `9F0C2E8D37B2A32F628DD486A4721AD0669C0E15A5D1CFEDE4AEF852E1277A22`. User's missing loose Hack Recover remains **absent**, while loose Finishing Recover remains **present**; assistant made no changes to animation archives or files. Next: start a fresh game with this release DLL and the *same missing Hack asset*. Test genuine Finishing **before any Hack**; then one Hack; then genuine Finishing again. If Finishing fails before Hack, investigate native missing-resource conditions; if it fails only after Hack, investigate cross-attack state/resource caching; if Finishing works throughout, focus on new diagnostic's scoped interception/token behavior. Record each control separately. Stop on abnormal behavior. No production implementation authority granted.

### EV-463 — Original release fallback control with Hack Recover physically absent (2026-11-22)

**Evidence type: USER-OBSERVED RUNTIME CONTROL, not diagnostic log.** User launched Gothic 3 with the verified original release `Script_G3AnimationBehaviors.dll` (SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`) as sole live G3AB DLL, while the user-removed loose `Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot` remained absent and the loose native `Hero_Parade_None_2H_P1_FinishingAttack_Recover_N_Fwd_00_%_00_P0_0.xmot` remained present. User performed **3 Hack attacks and 3 genuine Finishing attacks**. **All three Hacks used native Finishing Recover fallback, and all three genuine Finishers used their intended Finishing Recover normally.** The order of the six attacks was not separately documented, so do not claim the specific before-Hack / after-Hack split proposed in EV-462. Game was closed at post-run inspection; asset inventory and release hash were verified. There is no per-attack instrumented log for this release-only visual control.

**Comparison / supported conclusion:** EV-461 real-asset experimental DLL with both assets present: Hack Recover 3/3, genuine Finishing Recover 3/3. EV-462 same experimental DLL with Hack Recover genuinely missing: actual Hack query null, subsequent Recover playback absent for additional Hacks **and** genuine Finishing15. EV-463 original release with the **same missing asset condition**: Finishing Recover fallback 3/3 for Hack, and native Finishing Recover 3/3 for true Finishing. Therefore the missing loose Hack Recover `xmot` **alone is insufficient** to explain EV-462. The key behavioral difference is the experimental path's suppression of initial native Finishing and then returning an unmatched/missing Hack resource without the release's native Finishing fallback. This **implicates the altered Recover transition/return path**, but does not yet prove which native internal state, animation slot, SPU lifecycle or cache is responsible; no direct Action15 suppression was logged in EV-462.

**Engineering decision:** **REJECT** the experimental no-Hack-Recover => `nullptr` policy as production behavior. Do not treat this as native idle semantics, and do not try to repair it with speculative timers, permanent tokens, forced idle, or additional hooks. The minimal *evidence-supported* positive-asset fix is still the EV-459/EV-461 scoped first wrong Finishing Recover suppression **only after positively confirming matching Hack Recover**, with original release fallback behavior unchanged when absent. That means missing Hack Recover still plays native Finishing Recover, a deliberate compromise relative to the User's preferred no-Recover/idle semantics. If the User still requires direct idle, treat it as a **separate bounded research question** about native Recover ownership and no-Recover completion, not an assumption or hidden feature in the small glitch correction. In particular, do not suggest that having a missing `.fxm` returned by our hook after entering Recover is equivalent to an animation absent from the native game.

**State:** original release DLL remains sole live product; user's loose Hack Recover still absent (User should restore from own backup before any future positive-asset visual tests), loose native Finishing Recover present. Diagnostic DLLs stay outside the game. No code changes, `main` or `Backup` changes made in this evidence step. **Next decision:** prepare a narrowly scoped production correction based on proven positive resource gate, or explicitly commission separate native no-Recover lifecycle research if absent-Hack-Recover idle is a hard requirement.


### EV-464 — Production candidate positive-asset 2H Hack/Finishing visual acceptance PASS (2026-11-22)

**Evidence type: USER-OBSERVED, DIAGNOSTICS-FREE FOCUSED GAMEPLAY; no per-attack instrumentation.** Previous gate requested three player 2H Hack14 attacks followed by three genuine knocked-down-opponent Finishing15 executions using visually distinct Hack and Finishing animation sets. The User reported after that test: **"Test performed no visual glitches observed"**. This is a response to the requested 3+3 matrix; individual action counts, Recover resource names and exact playback are not independently instrumented. No leg discontinuity or Finishing visual regression was reported.

**Fixture and post-run identity:** production candidate `scripts/Script_G3AnimationBehaviors.dll`, 470,528 bytes, SHA256 `E46211EA7179DB8E0C4E1E3DED15C7750BF3DACE899A216ECCBE5FB62C343281`; exact user player 2H Hack Recover loose `.xmot` verified present at previous startup checkpoint. Following this gameplay report, Desktop Commander verified `Gothic3.exe` not running, candidate DLL still matches the hash, local repository `development @ cd5587474163344edd47a6b2e4ff7cbbc7ec978a` clean before EV documentation. Research probes not installed. Original release remains backed up outside game (prior SHA256 `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`, not rehashed during this gate).

**Disposition: FOCUSED POSITIVE-ASSET PLAYER 2H VISUAL PASS, NOT GENERAL PRODUCTION/RELEASE REGRESSION ACCEPTANCE.** This supports the intended elimination of the visible first Finishing Recover glitch for a complete custom Hack set in the tested fixture; it does not directly prove which motion was suppressed, runtime admin lookup, or all non-visual invariants. New production candidate missing-Hack-Recover fallback, Staff/Orc/NPC routes, other weapon variants, repeated/interrupted Recover and wider compatibility have **not** been re-tested in this candidate. The old release fallback control EV-463 and research real-asset controls EV-459/461 remain separate provenance; do not promote their scope to the new shipping build. No binary/source/animation changes made for this EV.

**Next:** preserve this focused PASS; the separate public release README section 6 copy was prepared with the exact locally verified player 2H Raise/Hit/Recover filename pairs after this PASS. A controlled absent-Hack-Recover native fallback check on the production candidate is still advisable before declaring broader shipping acceptance; User owns animation removal/restoration. Preserve `main` and `Backup`.


### EV-465 — Complete-custom-asset Staff follow-up visual PASS (2026-11-22; User fixture clarification)

**Evidence type: User-observed diagnostics-free gameplay.** After EV-464's positive player 2H test, User reported: "Just performed the same test as we had done with staffs, all looked fine. Next I will do this one: 1. Missing Hack Recover". This supports **no visible Staff attack/Finishing problem reported** in the just-completed run. The User described it as the same test as the prior 2H test; exact per-attack counts are not independently instrumented. **Subsequent User clarification:** "I removed the recover animations after I had performed the tests". Accordingly, the Staff Hack Recover was **present during the Staff gameplay**, then removed afterward for the planned missing-Recover test. Treat the positive-asset fixture as user-confirmed, not inferred from the later filesystem snapshot. Exact native motion routing remains uninstrumented.

**Post-report read-only workstation check:** Gothic3.exe closed. Candidate production `Script_G3AnimationBehaviors.dll` still installed with SHA256 `E46211EA7179DB8E0C4E1E3DED15C7750BF3DACE899A216ECCBE5FB62C343281`; sole live G3AB DLL. Loose Staff `Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot` and `Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot` are present; **no loose Staff Hack Recover**. Likewise 2H Hack Raise/Hit present, **no loose 2H Hack Recover**. Corresponding native Finishing files present. This is a **post-removal snapshot**, not the earlier gameplay fixture. The User directly confirmed Recover animations were removed only *after* testing; archived resources were not exhaustively evaluated. Asset changes were not performed by the Assistant.

**Corrected disposition: Staff complete-custom-asset positive visual test PASS, User-confirmed Hack Recover present during test; not an instrumented proof of internal playback.** Keep EV-464 player 2H distinct-assets evidence separate. The current loose-file snapshot is consistent with the User's upcoming missing-Hack-Recover Test 1 for both weapon types, but engine-level absence still requires interpreting the actual gameplay and any alternative package resources. No instrumented log, production source edit or new product build. Next: perform separately observed 2H and Staff missing-Hack-Recover native fallback controls, genuine Finishing before/after Hacks, following the frozen matrix in the active task.


### EV-466 — Production candidate missing-Hack-Recover fallback, player 2H and Staff visual PASS (2026-11-22)

**Evidence type: USER-OBSERVED, DIAGNOSTICS-FREE controlled gameplay; no new instrumented runtime artifact.** The User performed the agreed **Test 1 — missing custom Hack Recover** with both player 2H and Staff on the installed production candidate. User reported: **"Performed the tests with staffs and 2h, all looked fine. hack attacks used recover animation from finishing attacks, finishing attacks worked fine"**. This directly reports intended native Finishing Recover fallback during Hack and intact genuine Finishing attacks for both weapon types, with no visual glitches observed. Do not fabricate exact per-action counts or instrumented event identity from the report; earlier planned matrix was three Hacks plus true Finishing controls before and after.

**Read-only post-run checks:** Gothic3.exe not running. Sole live project product remains `scripts/Script_G3AnimationBehaviors.dll`, SHA256 `E46211EA7179DB8E0C4E1E3DED15C7750BF3DACE899A216ECCBE5FB62C343281` (candidate unchanged). In loose `Data/_compiledAnimation`, Hack Recover files for both `Hero_Parade_None_2H` and `Hero_Parade_None_Staff` were absent; their Hack Raise/Hit and the native Finishing Recover files for both weapon types were present. This inventory supports the intended controlled loose-file fixture but cannot exclude packed or alternative providers. The User separately confirmed that Recover files were removed *after* the earlier complete-assets visual tests (EV-464/465) and before this test.

**Log inspection:** game root contained `G3AB_HackTransitionProbe.log` last modified 2026-11-22 11:51:46, `G3AB_BadBlockResearch.log` 2026-10-07 and `Script_FrameCollisionTest.log` 2026-09-27; Documents\\Gothic3 engine logs were older still (latest 2026-09-11). None were newly written by this production-candidate gameplay test. The production product has no matching per-attack diagnostic trace; do not confuse historical research logs with this run or manufacture a raw-log file.

**Disposition: Test 1 2H PASS + Staff PASS (visual/function), not internal motion-call trace.** The production positive-resource gate has not visibly disrupted native missing-Hack-Recover fallback or genuine Finishing for these fixtures. No production source, DLL, INI, animation assets, `main` or `Backup` changed by Assistant. Remaining User-approved matrix: **Test 2** with all custom Hack Raise/Hit/Recover absent for each of 2H and Staff, then **Test 3** with complete distinct custom Hack and native Finishing sets. User owns reversible file changes; launch fresh after each fixture; preserve native Finishing animations. General release acceptance remains open until these observations are collected and reviewed.
