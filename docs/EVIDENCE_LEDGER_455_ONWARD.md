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
