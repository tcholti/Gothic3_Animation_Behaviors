# Gothic 3 Animation Behaviors — Evidence Ledger EV-373 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-23

## Purpose

Record evidence after the EV-365–EV-372 final-source Stage-A/B/separation-compatibility volume.

This ledger is proof history, not the normal knowledge interface. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

## Entry format

```text
### EV-xxx — short factual title

Observed:
- direct factual result(s)

Scope / limits:
- exact actor/action/source/build/test limits
- explicit non-claims when important

Provenance:
- source/log/commit/hash/path as applicable

Disposition:
- PASS / FAIL / NEGATIVE CONTROL / INCONCLUSIVE / SUPERSEDED
```

## Entries

### EV-373 — Broad mixed-gameplay stress run PASS with bounded lifecycle recoveries

Observed:
- The User performed one long natural mixed-gameplay stress session involving ordinary travel/combat churn, multiple fights and weapon/source changes. The User reported that everything looked and worked normally in-game throughout the run.
- The CORE diagnostic log contains 16,693 lines / 3,424,951 bytes and was processed through the POP-07 large-log evidence package. The package exposed exactly six high-level anomaly-class events: four `CORE C1 FINALIZATION ANOMALY / REPAIR` records and two `CORE MARKER ANOMALY / DISCOVERY` records.
- All four C1-R1 events were bounded exact-source recoveries that converged the live outstanding physical source from group7 back to Item_Equipped/group5. The observed repaired routes included player Staff/Halberd, Stalker Axe/raw52, ordinary 1H sword, and a small-axe source whose factual runtime UseType was 2. No repair divergence or unresolved equipped-source state was observed.
- Both marker anomaly/discovery records were fail-closed unsupported/late traffic rather than stale collision activation: one arrived at Action0 with no valid C1, and one arrived under unknown Action68 with no live equipped source. Neither established ownership or left collision active.
- Representative early/middle/late source windows were inspected around all six exceptional events. The run ended with ordinary 1H+shield traffic cleaning RIGHT from group7 to group5, all shown final obligations at zero, followed by `Script_FrameCollisionTest unloading cleanly`.
- No contradictory runtime evidence requiring a collision-source change was found.

Scope / limits:
- This is the first broad Stage-D mixed-stress run on the frozen source. It is a meaningful PASS for this run, but it does not by itself close all of Stage D; whether another broad stress run is useful is intentionally left for the next session.
- The four repairs corroborate the existing C1-R1 safety-net architecture under unscripted real gameplay. They do not imply that ordinary native cleanup never misses, and they do not reopen the separate paused `AttackContinuationProtection` responsibility.
- The User's positive gameplay observation is supporting evidence alongside the diagnostics; the PASS disposition rests on the diagnostic convergence/fail-closed behavior as well.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw/derived evidence commit: `028c929005a9b1c35cb48e74070d1995c457ba06`;
- canonical raw source: `research/archive/2026.09.23_stress_collision_test.log`;
- raw Git blob: `95d57f8ee7ea1aa993b1b9773f31fca3be0afd40`;
- raw SHA256: `0B5596584ED39571CA89CE7CBD90BA7065DF134CF4274BB3C4ADFA7CA5782652`;
- raw size: 3,424,951 bytes / 16,693 lines;
- derived retrieval package: `research/derived/2026.09.23_stress_collision_test_large_log/` (60 complete-source parts, 17 signal parts).

Disposition:
- **PASS — Stage-D broad mixed-stress batch 1.**
- Stage D remains ACTIVE pending a deliberate next-session decision on whether another broad stress run is warranted.
- No source change is justified.

### EV-374 — Second broad mixed-gameplay stress PASS; Stage D and standalone regression CLOSED

Observed:
- The User published a second long broad stress session on the unchanged frozen collision source. The POP-07 package contains 20,907 complete source lines / 4,650,022 bytes.
- The package reports exactly **one** anomaly-class timeline event: one `CORE C1 FINALIZATION ANOMALY / REPAIR`. There are no `CORE MARKER ANOMALY / DISCOVERY` records in the event package.
- The single repair occurs for `SlaveZombie` with exact RIGHT `It_Pickaxe / UseType52`: `OutstandingBeforeFinalization=1`, `ActualGroupBeforeRepair=7`, `LivenessEstablished=1`, `Outcome=REPAIRED_TO_ITEM_EQUIPPED`, `ActualGroupAfterRepair=5`, `PhysicalCollisionChanged=1`. The repair converges safely and no repair divergence follows.
- Targeted whole-package checks found no `WARNING`, `ERROR`, `MISMATCH`, `DIVERGENCE`, or `C1 INVARIANT WARNING` records.
- Representative windows demonstrate substantial mixed churn rather than an isolated smoke: player 2H combat against ScorpionKing; dual-1H BOTH/LEFT/OFF marker traffic interleaved with Snapper raw8 opportunities; Schakal raw8 while player 1H collision activates/cleans; Axe/raw52 zombie traffic mixed with player 1H+torch; Sandcrawler raw8 while player 2H/GetUpAttack collision is active; and terminal dual-1H/native-fallback traffic alongside TRex raw8 Sprint-origin transport.
- The terminal TRex sequence opens a marked raw8 Sprint opportunity at factual Action9, survives into factual Action2/Power, consumes on exact native contact, retires permission, and finalizes `Outstanding=0`. The final shown equipped player sources also clean back to group5 / `Outstanding=0`, and the DLL ends with `Script_FrameCollisionTest unloading cleanly`.
- No contradictory runtime evidence requiring a collision-source change was found.

Scope / limits:
- EV-374 itself does **not** exercise a factual raw55/Troll route. Stage-D closure therefore does not claim that every collision mechanism appeared in this one log.
- Stage-D closure is compositional under the standing campaign rule: exact frozen-source raw55+equipped coexistence is already established by EV-366; raw8/raw55/equipped coexistence is established by the focused frozen-source acceptance EV-359–EV-364; EV-373 and EV-374 add two long unscripted mixed-gameplay sessions with substantial C1/actor/weapon churn and natural cleanup/repair opportunities.
- The successful C1-R1 repair is safety-net corroboration, not evidence that native cleanup should be replaced or that the separate paused `AttackContinuationProtection` responsibility should reopen.
- This is standalone collision evidence only. It does not certify New Balance / AttackCollision compatibility.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw/derived evidence commit: `b6661547bf509ffeebec8f055ada7f857fd835fb`;
- canonical raw source after POP-06 closure: `research/archive/2026.09.24_stresstest_collision_2.log`;
- raw Git blob: `f319500a0ebbf0f7d82be5e6e057fd89e478698c`;
- raw SHA256: `BC7F1447C6F3B6FBE5C765C8A057EDFA81C3EDD205B9DAE7FC9F5DF60A4B06D6`;
- raw size: 4,650,022 bytes / 20,907 lines;
- derived retrieval package: `research/derived/2026.09.24_stresstest_collision_2_large_log/` (82 complete-source parts, 18 signal parts).

Disposition:
- **PASS — Stage-D broad mixed-stress batch 2.**
- **Stage D mixed stress CLOSED/PASS EV-373–EV-374.**
- **Standalone final-source collision regression CLOSED/PASS through EV-374.**
- New Balance exact distributed-bundle compatibility becomes the current gate.
- No source change is justified.

### EV-375 — Zombie + Axe separation asset-gap remedy PASS

Observed:
- The User tested the proposed remedy for the earlier combined Zombie Separation + Axe Separation zombie 2H/Axe animation gap: corresponding zombie `2H` animation assets were copied and the animation-family token was changed to `Axe` so Axe Separation could resolve an Axe-named zombie animation.
- Runtime directly shows `BenSala_Zombie_02` using the new `Zombie_..._Axe_...` motion family while the factual equipped source remains `It_Pickaxe / UseType52`.
- Marked copied/renamed Normal, Power and Whirl animations are detected and accepted. Representative examples include `Zombie_Stand_None_Axe_P0/P1_Attack...`, `Zombie_Stand_None_Axe_P0/P1_PowerAttack...`, and `Zombie_Parade_None_Axe_P0_WhirlAttack...`.
- Whirl exercises repeated authored collision timing on the copied/renamed asset: `RIGHT -> OFF -> RIGHT` is accepted, the exact Pickaxe/raw52 source opens/closes accordingly, and finalization returns `Outstanding=0`.
- The unmarked copied/renamed FinishingAttack/Hack asset remains native (`MarkerPresent=0 / RequiredMask=0 / SuppressNative=0`) and its factual Pickaxe/raw52 source still cleans normally.
- Whole-log checks found no `ANOMALY`, `DIVERGENCE`, `WARNING`, or `ERROR` records. The final shown source state is zero-outstanding and the diagnostic DLL unloads cleanly.

Scope / limits:
- This verifies the proposed asset-gap remedy for the tested Ben Sala zombie Axe/raw52 route and proves that Zombie Separation + Axe Separation can coexist on that route when matching `Zombie_..._Axe_...` assets are supplied.
- It does not claim every special-zombie animation asset or every third-party separation combination is automatically complete; missing assets would still need corresponding coverage.
- This is not a collision-source change. The result further confirms that the earlier observed failure was an animation asset-availability/naming problem, not a Gothic3_Animation_Behaviors collision incompatibility.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- raw upload commit: `212de868ae1310e2b29d4ce9a947e0a629bfc3a2`;
- canonical archived runtime: `research/archive/2026.09.24_zombie_axe_asset_gap_fix.log`;
- raw Git blob: `f5a7e5d9c1d606cd32551606c2896c8a7fe1498a`;
- raw size: 88,785 bytes / 472 lines.

Disposition:
- **PASS — proposed Zombie+Axe separation asset-gap remedy verified for the tested route.**
- Combined Zombie + Axe separation is no longer treated as fundamentally incompatible.
- All separation mods may remain installed for the upcoming New Balance compatibility environment because that now matches the User's intended load order.
- No collision source change is justified.

### EV-376 — New Balance / AttackCollision raw55 Power StatePosition=2 compatibility contradiction

Observed:
- Runtime with the User's intended New Balance compatibility stack exposes a deterministic incompatibility in the frozen `PhysicalFistCollision` raw55 Power state gate, not a broad collision-system failure.
- With the original single-FIST Troll Power fixture, factual true Power (`Action=2 / Family=POWER`) repeatedly suppresses the premature exact RIGHT `TrollFist / UseType55` opening as intended, but the sole authored FIST arrives around `StateTime ~= 1.58` after the callback has advanced to `StatePosition=2`. The exact same actor/C1/right-source/raw55 execution is still present, yet the frozen production gate accepts Power only at StatePosition1, so the FIST fails closed as `REJECTED_UNSUPPORTED_HIT`; RIGHT remains group5 and no authored activation occurs.
- A second independent Troll run repeats the same true-Power SP2 rejection many times while raw55 Normal and Quick continue to behave normally and cleanly.
- The no-target equipped weapon sweep found no marker anomaly/warning/error. Representative Power for 2H, Staff, 1H, Torch+1H, Shield+1H, Rapier and Axe remains accepted with clean lifecycle behavior. Dual-1H Power is an important control: generic equipped BOTH/RIGHT/LEFT/OFF markers are accepted safely at factual `StatePosition=2` and clean to group5/zero outstanding, proving that StatePosition2 itself is not globally invalid collision state.
- Three BlackTroll double-FIST runs expose the same raw55 incompatibility at the repeated-marker boundary. For true Power, marker1 arrives around `StateTime ~= 0.97 / StatePosition=1`, opens the exact RIGHT TrollFist `5 -> 7`, is accepted, and produces native damage. Marker2 in the same exact C1 arrives around `StateTime ~= 1.33–1.35 / StatePosition=2` with RIGHT already group7 and is rejected instead of performing the established clear-only repeated-contact rearm. The User visually observed that Troll/BlackTroll Power attacks could damage with the double-marker fixture; the logs show this is the accepted first SP1 marker, not successful second-marker semantics.
- The same BlackTroll runs capture the previously missing New Balance Sprint-origin continuation. Marker1 is factual `Action=9 / Family=SPRINT / StatePosition=1`, is accepted, opens the exact RIGHT raw55 source and can produce native damage. The same C1 later continues as factual `Action=2 / Family=POWER / StatePosition=2`; marker2 is then rejected while immutable origin remains Sprint. This exactly preserves the previously proven Sprint-origin identity model while exposing the new SP2 incompatibility at the continuation marker.
- Targeted anomaly review of the three BlackTroll logs found 18 marker anomalies, all of the same class: exact raw55 Power-state FIST traffic at StatePosition2 after the execution was already established. No second rejected-marker class was found.
- Cross-mechanism controls remain healthy: Goblin equipped combat, Sabertooth raw8, and human raw8/fist runs show no marker anomalies; representative Goblin equipped Power and human raw8 Power are accepted on their existing routes.
- Source inspection of Jackydima `Script_AttackCollision` corroborates the runtime transition. Its `OnAI_PowerAttack` advances StatePosition `0 -> 1` after `ActivePowerAttackStartTime`, then later advances `1 -> 2` after `ActivePowerAttack1H1HStartTime`; the `StatePosition = 2` assignment is outside the dual-1H conditional. Current source defaults are `0.1f` and `1.0f`, matching the observed first-marker-before-second-threshold / later-marker-after-second-threshold pattern. This source inspection is causal corroboration, not exact binary provenance for the User's installed DLL.

Scope / limits:
- Frozen Gothic3_Animation_Behaviors source is unchanged at `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`.
- The contradiction is bounded to the permanent raw55 PhysicalFist Power/Sprint-origin state acceptance under the tested New Balance/AttackCollision environment. It does **not** justify generic `StatePosition >= 1`, generic SP2 acceptance, species/name rules, filename inference, new hooks, polling/timers, or changes to raw8/equipped marker semantics.
- Evidence supports preserving true-Power SP1 behavior while additionally recognizing SP2 for the exact already-correlated raw55 Power execution where appropriate. It also supports recognizing SP2 for the established Sprint-origin marker2 continuation when current factual family has become Power. Every observed Sprint-origin first FIST remains factual Sprint/Action9 at StatePosition1, so there is no evidence to broaden Sprint first-marker acceptance. **This last observation is historical to EV-376 and is superseded by EV-378, which directly observes Sprint-origin first/only FIST at Action9/SP2.**
- Normal and Quick raw55 behavior are not contradicted and remain outside the compatibility correction.
- At EV-376 publication the processed New Balance logs were temporarily retained as active comparison inputs. EV-377 closes the additional Sprint controls and removes that broad retention exception; canonical runtime artifacts are subsequently migrated byte-identically to `research/archive/` under POP-06.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- original New Balance runtime input basenames: `2026.09.24_newbalance_troll.log`, `2026.09.24_newbalance_troll2.log`, `2026.09.24_newbalance_different_weapons_no_target.log`, `2026.09.24_newbalance_fist_no_target.log`, `2026.09.24_newbalance_goblin.log`, `2026.09.24_newbalance_sabertooth.log`, `2026.09.24_newbalance_blacktroll.log`, `2026.09.24_newbalance_blacktroll_2.log`, `2026.09.24_newbalance_blacktroll_3.log`; resolve current canonical locations through `EVIDENCE_PATH_MIGRATIONS.md`;
- latest evidence-upload branch HEAD before this maintenance transaction: `d0d59fc0628dc671bd052893d5d7bca54379a559`;
- corroborating external source: `Jackydima/gothic3sdk`, `scripts/Script_AttackCollision/Script_AttackCollision.cpp` blob `1c0e668e2cea38259ae9f400e0c5dead45fdd8c0`, `config.cpp` blob `b5e1766466d2c2837c8f247280854428b27f719f`, inspected 2026-09-24.

Disposition:
- **FAIL — SOURCE-CORRELATED NEW BALANCE COMPATIBILITY CONTRADICTION; BOUNDED RAW55 REMEDIATION REQUIRED.**
- The first bounded remediation was later implemented in `6eb3e3ca96da55e89127c24d5f656e05610d315f` and its exact changed predicates are runtime-confirmed by EV-378. EV-378 also discovers the separate Sprint-first SP2 case that was not known when EV-376 was written.

### EV-377 — New Balance equipped Sprint and Sabertooth raw8 Sprint controls PASS

Observed:
- The focused BlackGoblin equipped-Sprint run repeatedly exercises factual `Action=9 / Family=SPRINT` through the permanent `EquippedSprintCollision` owner. Eligible native opening is suppressed, the bound RIGHT marker is authorized into the generic equipped path, the exact RIGHT 1H source opens `5 -> 7`, the marker is accepted at `StatePosition=1`, damage is observed, and native cleanup returns the source to group5 with `Outstanding=0` / `NO_OP_NO_OUTSTANDING` finalization.
- The same equipped run later shows an independent factual true-Power C1 where stale Sprint authorization is denied by C1-generation mismatch while the ordinary generic Power marker is accepted normally. This is a useful negative control that the Sprint owner does not leak authorization into a later Power execution.
- The prepared Sabertooth large-log package repeatedly captures factual raw8 Sprint ownership on `Sabertooth_Stand_None_Fist_P0_PowerAttack_Hit_N_Fwd_00_%_00_P0_300.xmot`. The authored FIST is accepted at factual `Action=9 / Family=SPRINT / StatePosition=1`, opens one raw8 opportunity, and arms/applies the existing early-permission route.
- Multiple Sabertooth Sprint executions then reach exact native contact in the **same C1** after factual state has changed to `Action=2 / Family=POWER`. The already-open raw8 opportunity is consumed by exact native contact, permission is retired, and `OnDamage` is emitted against `PC_Hero`. This independently confirms that New Balance's same-execution `Action9 -> Action2` transition is legitimate transport and is handled safely by the existing raw8 opportunity identity.
- Missed Sabertooth opportunities continue to use the established miss/rearm or C1-finalization close behavior. The deterministic prepared package contains 3,379 complete source lines in 18 full-source parts; its configured signal event table contains no recorded anomaly-class event rows.
- Neither focused control introduces a second compatibility contradiction beyond EV-376.

Scope / limits:
- The equipped-Sprint result proves the tested BlackGoblin RIGHT/1H Sprint route under the current New Balance stack. It does not claim that this particular run captured an equipped same-C1 `Action9 -> Action2` marker continuation.
- The Sabertooth result is raw8-specific. It proves that raw8 Sprint can accept at factual Sprint/SP1 and survive same-C1 factual transition into Power through contact consumption; it does not alter raw55 marker-state acceptance.
- The statement that the raw55 correction boundary did not include Sprint-first SP2 was correct for the evidence available at EV-377. EV-378 later supersedes that limitation with direct Sprint-first/only Action9-SP2 evidence.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- equipped-Sprint raw source basename: `2026.09.25_newbalance_blackgoblin.log`, Git blob `c844fe24336af090a5bb356338f3292ea81e04d7`;
- Sabertooth raw source basename: `2026.09.25_newbalance_sabertooth_2.log`, Git blob `40b0fc19a2075d67057273f5240aa155ab047686`;
- Sabertooth raw/derived upload commit: `4db1958d0c63ae182c4ab4cc190315b9ab12538a`;
- deterministic Sabertooth retrieval package: `research/derived/2026.09.25_newbalance_sabertooth_2_large_log/` (18 complete-source parts); canonical raw locations after POP-06 closure resolve through `EVIDENCE_PATH_MIGRATIONS.md`.

Disposition:
- **PASS — NEW BALANCE EQUIPPED-SPRINT AND RAW8-SPRINT CONTROLS.**
- Processed pre-remediation evidence is archived under POP-06.

### EV-378 — First raw55 SP2 correction runtime partial PASS; Sprint-first SP2 compatibility fact discovered

Observed:
- The User built and deployed the diagnostic twin after the reviewed first raw55 SP2 correction. Built and live SHA256 are identical: `E11D680590D2F9D87A50EAF64B642F70C8CECA019ABB651DC48B00AF01F37C74`. Deployment was reported PASS.
- The single-marker BlackTroll run directly validates the corrected true-Power first-FIST predicate. Repeated factual `Action=2 / Family=POWER` executions suppress the premature exact RIGHT raw55 opening, then accept the sole authored FIST at `StatePosition=2` around `StateTime ~= 1.58`. The exact RIGHT `TrollFist / UseType55` transitions `5 -> 7`, native `OnDamage` is observed when contact connects, native cleanup returns `7 -> 5`, and C1 finalization reaches zero outstanding.
- The double-marker BlackTroll run directly validates corrected true-Power second-FIST semantics. Marker1 at current `POWER / SP1` opens the exact RIGHT raw55 source and is accepted. Marker2 in the same C1 at current `POWER / SP2` is accepted with `GroupBefore=7 / GroupAfter=7`, `GroupRequested=0`, and `ClearTriggeredList=1`: the established clear-only rearm semantics are preserved with no second physical opening. Representative executions produce native damage after both opportunities and clean to group5/zero outstanding.
- The same double-marker run directly validates corrected Sprint-origin later-marker semantics. A representative C1 begins with immutable origin Sprint; marker1 is factual `Action9 / SPRINT / SP1`, accepted, and opens RIGHT `5 -> 7`. The same C1 later becomes factual `Action2 / POWER / SP2`; marker2 is accepted with `GroupRequested=0 / ClearTriggeredList=1`, preserving clear-only rearm and Sprint-origin identity. Native cleanup returns to group5/zero outstanding.
- Raw55 Normal and Quick remain healthy in both marker fixtures. In the double-marker run their first markers physically open and their second markers rearm without a second opening; representative two-contact damage is observed.
- The double-marker log contains no `CORE MARKER ANOMALY / DISCOVERY` record.
- The single-marker run exposes one new deterministic class not present in EV-376/EV-377. In repeated Sprint-origin executions, factual current state remains `Action=9 / Family=SPRINT`, premature native opening is suppressed, `earlyOpeningSuppressed=1`, RIGHT remains group5, but the first/only authored FIST arrives at `StatePosition=2` around `StateTime ~= 1.58`. Because the first correction intentionally left the Sprint-first gate at exact SP1, the marker fails closed as `REJECTED_UNSUPPORTED_HIT`. The reviewed single-marker anomaly records are this same Sprint-first/SP2 class.
- The User's gameplay observation matches the diagnostics: in the single-marker fixture Normal/Quick/Power could connect while Sprint did not; in the double-marker fixture Sprint could connect once and the other attacks could produce the expected repeated contacts.

Scope / limits:
- EV-378 proves the three predicates changed by `6eb3e3ca96da55e89127c24d5f656e05610d315f` behave exactly as designed at runtime under the tested New Balance stack. It does not invalidate that correction.
- EV-378 **supersedes** the earlier EV-376/EV-377 evidence limitation that every observed Sprint-origin first FIST was at SP1. A first/only Sprint-origin FIST can factually remain Sprint/Action9 and arrive at SP2.
- The newly discovered remaining contradiction is bounded to `IsFirstFistAllowed` for an already-matched Sprint-origin raw55 execution. Existing actor/right-source/C1/origin/motion identity and mandatory `earlyOpeningSuppressed` are intact in the failing records.
- Evidence supports preserving Sprint-first SP1 while additionally considering explicit SP2. It does not support `StatePosition >= 1`, authored-count-specific policy, species/name gating, filename inference, New Balance/DLL detection, new hooks/state/timers, custom damage, generic SP2 policy, or neighboring-system changes.
- Broader New Balance full-stack certification remains open until this last reduced raw55 contradiction is resolved and focused regression passes.

Provenance:
- first raw55 SP2 correction source commit: `6eb3e3ca96da55e89127c24d5f656e05610d315f`;
- reviewed candidate documentation lineage before runtime upload: `74eb002d41aa74bde2dc3585365481de9c35bc3f`;
- runtime upload commit: `96ec7e85e6fbb64f8295618a81b75712a0eb73ce`;
- diagnostic built/live SHA256: `E11D680590D2F9D87A50EAF64B642F70C8CECA019ABB651DC48B00AF01F37C74`;
- single-marker canonical runtime: `research/archive/2026.09.25_newbalance_blacktroll_all_single_marker.log`, Git blob `147c96c703ee7d25aab7536b3077be5544ad9781`;
- double-marker canonical runtime: `research/archive/2026.09.25_newbalance_blacktroll_all_double_marker.log`, Git blob `de56082714c3d2e59210333744268158d389dd18`.

Disposition:
- **PARTIAL PASS — FIRST RAW55 SP2 CORRECTION VALIDATED FOR ITS EXACT CHANGED PREDICATES.**
- **NEW REDUCED CONTRADICTION — SPRINT-ORIGIN FIRST/ONLY FIST MAY ARRIVE AT FACTUAL SPRINT/ACTION9/SP2.**
- The first bounded correction task is complete and should be archived rather than silently expanded.
- Next source consideration, if accepted, should remain a one-predicate follow-up inside `PhysicalFistCollision`: Sprint-origin first FIST keeps current Sprint identity and mandatory `earlyOpeningSuppressed`, preserves SP1, and additionally accepts explicit SP2.

### EV-379 — Sprint-first SP2 correction runtime PASS; Sprint-origin second-FIST current-Sprint/SP2 case discovered

Observed:
- The User built and deployed the diagnostic twin after the bounded Sprint-first SP2 correction. Built and live SHA256 are identical: `490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C`; deployment reported PASS.
- The single-FIST BlackTroll run repeatedly validates the corrected Sprint-first predicate. Factual Sprint-origin executions remain `Action=9 / Family=SPRINT`, the premature exact RIGHT raw55 opening is suppressed, and the first/only FIST arrives at `StatePosition=2` around `StateTime ~= 1.58`. The marker is now accepted, exact RIGHT `TrollFist / UseType55` opens `5 -> 7`, native damage is observed on connecting attacks, and native cleanup returns `7 -> 5` with zero outstanding. No marker anomaly was found in the reviewed single-marker log.
- The double-FIST BlackTroll run mostly preserves the previously proven Sprint-origin continuation: marker1 at `Action9 / SPRINT / SP1` opens RIGHT `5 -> 7`; when marker2 arrives after factual transition to `Action2 / POWER / SP2`, it is accepted with `GroupRequested=0 / ClearTriggeredList=1`, preserving clear-only rearm and no second physical opening.
- One double-FIST execution exposes a new timing-dependent state. In C1=124, marker1 is accepted at `Action9 / SPRINT / SP1`, but marker2 arrives while factual state is still `Action9 / SPRINT / SP2`. RIGHT is already group7, `AcceptedFistCount=1`, and the current Sprint-origin second-FIST predicate rejects because it only accepts current `POWER`. The marker fails closed as `REJECTED_UNSUPPORTED_HIT`; native cleanup later returns RIGHT `7 -> 5` normally.
- Targeted review found this as the single marker-anomaly class in the double-marker log. No `WARNING` or `ERROR` record was found. The User independently reported that the second Sprint contact had sometimes felt abnormal across several runs, consistent with this timing-dependent state split.
- True-Power, Normal and Quick raw55 controls shown in the same runs remain healthy; no evidence from this batch contradicts their established predicates.

Scope / limits:
- EV-379 directly validates the exact source change in `ce59e5a2bad564652eaba970e959bdef0b479d82`: Sprint-origin first FIST accepts explicit SP1 or SP2 while current family remains Sprint and `earlyOpeningSuppressed` remains mandatory.
- The newly exposed contradiction is separate from that first-FIST correction. It is bounded to Sprint-origin **second-FIST** continuation when current factual family has not yet changed from Sprint at SP2.
- Existing evidence already proves another legitimate second-FIST state for the same origin: current `POWER / SP2`. EV-379 therefore shows that the current-family value at marker2 is timing-dependent under New Balance.
- This evidence does **not yet** prove the complete second-FIST state set. In particular, no deliberate early-marker probe has yet established whether a legitimate second FIST can arrive while still `SPRINT / SP1`. Do not patch from the single observed `SPRINT / SP2` case alone.
- No evidence supports generic `StatePosition >= 1`, generic Sprint-family widening outside the already-owned same-C1 raw55 execution, marker-count-specific behavior, species/name gates, filename inference, New Balance/DLL detection, new hooks/state/timers, custom damage, or neighboring-system changes.

Provenance:
- Sprint-first SP2 correction source commit: `ce59e5a2bad564652eaba970e959bdef0b479d82`;
- runtime upload branch commit: `e9457ee5d31079eb0cb8d755fabba43d1df1113b`;
- diagnostic built/live SHA256: `490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C`;
- single-marker active comparison runtime: `research/raw/2026.09.25_newbalance_blacktroll_all_single_marker2.log`, Git blob `05abf1f7a7e025ff9b1dbfbf33b5074e2c5f4b0d`;
- double-marker active comparison runtime: `research/raw/2026.09.25_newbalance_blacktroll_all_double_marker2.log`, Git blob `f33b578479b8b38d5f18760b8254aa2e48d89b84`.

Disposition:
- **PASS — SPRINT-FIRST SP2 CORRECTION VALIDATED FOR ITS EXACT CHANGED PREDICATE.**
- **NEW BOUNDED CONTRADICTION — SPRINT-ORIGIN SECOND FIST MAY ARRIVE AT FACTUAL SPRINT/ACTION9/SP2 BEFORE THE ACTION9->ACTION2 TRANSITION.**
- Keep the two EV-379 logs in `research/raw/` temporarily as explicit active-comparison evidence for the next marker-timing probe.
- Next step is evidence gathering, not implementation: intentionally move marker2 earlier and determine whether legitimate second-FIST `SPRINT/SP1` also occurs; then define the complete smallest second-FIST state rule from the observed envelope.
