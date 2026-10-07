# Gothic 3 Animation Behaviors — Evidence Path Migrations

**Status:** Canonical provenance-path lookup  
**Updated:** 2026-10-05

## Purpose

Record deliberate repository path migrations of canonical evidence artifacts without changing their content, identity, evidence meaning or historical Git provenance.

Primary ownership:

```text
this file
= evidence storage-path migration lookup only
```

It is **not** an Evidence Ledger, technical authority, processing chronology, or current-state document.

Use it when processed canonical evidence moves between repository storage layers such as `research/raw/` -> `research/archive/` and a historical path would otherwise become ambiguous.

Historical EV rows and old commits may keep the path that was correct when written. This map supplies the forward location so historical wording does not require cosmetic rewriting merely because storage changed.

Routine evidence interpretation remains owned by the Evidence Ledger; evidence routing by `EVIDENCE_INDEX.md`; archive/intake procedure by POP-06; research-layer directory meaning by `research/README.md`.

---

## 2026-09-07 — September collision/Fist stable-subsystem archive

At the completed human-Fist production checkpoint, the September 2–7 expansion/Fist runtime sequence was reviewed for evidence closure before archival. Missing reusable conclusions were promoted as EV-241–EV-244 before the source artifacts left active intake. Intermediate Fist probes whose active questions were superseded by EV-221–EV-240 were classified as historical investigation provenance rather than given artificial new conclusions.

Migration rule for the **49 dated runtime logs** then present in `research/raw/` for 2026-09-02 through 2026-09-07:

```text
research/raw/<same September 2–7 basename>
    -> research/archive/<same basename>
```

Separate processed historical crash artifact:

```text
research/raw/ge3log10.log
    -> research/archive/ge3log10.log
```

`ge3log10.log` is a Gothic 3 `EXCEPTION_ACCESS_VIOLATION` crash log dated 2026-09-03 from an earlier diagnostic state with `Script_FrameCollisionTest.dll` loaded. The User identified it as an old completed crash artifact; no active unresolved crash responsibility remained. It is retained only as historical crash provenance.

Migration properties:

- every moved file kept its existing Git blob/content identity;
- no log was rewritten, normalized, trimmed or regenerated;
- basename stayed unchanged;
- evidence meaning/status stayed unchanged;
- historical commits remain valid provenance;
- current routes should use `research/archive/...`;
- historical ledger rows spelling `research/raw/...` resolve by same basename through this map.

Verified set:

```text
50 artifacts total
= 49 dated September 2–7 runtime logs
+ ge3log10.log
```

Broad dated coverage:

```text
2026-09-02  Power / Pierce / Hack-callback startup evidence
2026-09-03  Pierce / SimpleWhirl controls
2026-09-04  Hack routing/source controls + SimpleWhirl StatePosition closure
2026-09-05  Fist Stage A/B + N1/N2A/N2B/N2C
2026-09-06  Fist N2D/N2E/N4/N5/N6 + OFF/interruption/Power controls
2026-09-07  final production Normal+Power frame-12 acceptance
```

Evidence disposition:

- Power/Pierce reusable conclusions: EV-241–EV-242.
- September 4 SimpleWhirl StatePosition closure: EV-243.
- Hack callback identity: EV-216; later actual Hack marker/source validation: EV-244.
- Fist Stage A/B and N1–N6 reusable conclusions: EV-221–EV-240.
- N2A/N2B and earlier Stage-B causal-probe material remain superseded investigation provenance inside the later causal chain.

Deliberately retained active intake:

```text
research/raw/Keep.txt
```

Local-only backup files outside the repository are not part of this migration.

---

## 2026-09-12 — Completed auxiliary collision evidence

The September 12 Recovery Lock closed three already-interpreted auxiliary runtime artifacts after their reusable conclusions were promoted as EV-259–EV-261. Each artifact moved byte-identically with its existing Git blob identity and unchanged basename:

```text
research/raw/2026.09.12_stalker_native_markers_test.log
    -> research/archive/2026.09.12_stalker_native_markers_test.log
    blob d6348c8d7e2158ff41c9deb5bba507c9c72041d2

research/raw/2026.09.12_fall_down_damage.log
    -> research/archive/2026.09.12_fall_down_damage.log
    blob c3c1662cb2110018fe7b14f7db631479a0d08c33

research/raw/2026.09.12_blunt_arrow_bolt_test.log
    -> research/archive/2026.09.12_blunt_arrow_bolt_test.log
    blob c36a18f6e3b29a1a3d3b266e2a077cca5e91b4a3
```

The raw55 baseline and callback-suppression logs were intentionally **not** archived at this boundary. EV-262 closed their then-current evidence interpretation, but both remained active comparison inputs for the unresolved Quick-specific causal question at that time.

That temporary retention reason was later superseded by the completed Quick/raw55 causal chain through EV-273 and the subsequent family work. Those files are included in the 2026-09-16 archive transaction below.

---

## 2026-09-16 — Processed September 8–16 collision evidence archive

After canonical collision evidence reached EV-290, the remaining dated September 8–16 runtime/build artifacts in `research/raw/` were reviewed against the later evidence chain and current causal responsibility.

The retained files no longer owned an unresolved comparison obligation:

```text
September 8–9 transformed/Sabretooth comparison
    -> closed by the later compatibility/StatePosition evidence chain, including EV-249 and EV-263

September 10–11 transport-probe artifacts
    -> superseded by the later factual raw55 family/source causal chain

September 12 Quick/raw55 and auxiliary Troll controls
    -> Quick repeated-FIST route closed through EV-273

September 13–14 Normal/Power/Sprint first-contact family probes
    -> family first-contact route closed through EV-282

September 15–16 Normal repeated-FIST/reset-source probes
    -> current reusable conclusions canonically recorded through EV-290
```

Migration rule for the **51 processed artifacts** then remaining in `research/raw/`:

```text
research/raw/<same September 8–16 basename>
    -> research/archive/<same basename>
```

Migration properties:

- every move reused the file's existing Git blob SHA in a single Git tree transaction;
- no large file was downloaded, reconstructed, re-encoded, normalized, trimmed or regenerated;
- basename stayed unchanged;
- the move is therefore byte-identical by Git object identity;
- evidence meaning/status stayed unchanged;
- historical commits and historical EV rows remain valid provenance;
- current retrieval resolves the same basename under `research/archive/`;
- large-log `research/derived/` packages remain the preferred routine retrieval surface where they exist.

Archive commit:

```text
b19ac5db0fdf233ed2a502dc53cf947ce0a91564
```

Verified post-migration intake state:

```text
research/raw/Keep.txt
```

No new EV was created for this storage transaction because it establishes no new runtime/source fact. EV-290 remains the latest canonical collision evidence at this boundary.

For EV-286–EV-290 and other historical rows that still spell `research/raw/<basename>`, resolve the canonical source artifact as:

```text
research/archive/<same basename>
```

The derived packages referenced by those EVs are unchanged.

---

## 2026-09-18 — Focused permanent raw55 acceptance closure

Focused permanent raw55 acceptance closed at EV-298. The four active acceptance/control sources no longer own any unresolved comparison question and were moved byte-identically by reusing their existing Git blob SHAs:

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
    -> research/archive/2026.09.17_troll_raw55_permanent_acceptance.log
    blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b

research/raw/2026-09-18_troll_raw55_diagnostic_corrections_control.log
    -> research/archive/2026-09-18_troll_raw55_diagnostic_corrections_control.log
    blob 843d1054683996761b941493a95b76ffa2f9f60d

research/raw/2026-09-18_troll_raw55_unmarked_native_fallback_sentinel.log
    -> research/archive/2026-09-18_troll_raw55_unmarked_native_fallback_sentinel.log
    blob 795e137626b787654ceca66f29a9e09fc2e1c958

research/raw/2026-09-18_sabertooth_raw8_fist_sentinel.log
    -> research/archive/2026-09-18_sabertooth_raw8_fist_sentinel.log
    blob 3f0dedbba3580711761610476ba1080b4916b634
```

Archive transaction:

```text
5700aedb2feadbde1d1a635a9538ed788836f36d
```

Migration properties:

- exact existing Git blob identities were reused;
- no runtime log was downloaded, reconstructed, normalized, trimmed or regenerated;
- basenames and evidence meaning stayed unchanged;
- EV-295–EV-298 own the final focused validation/closure conclusions;
- existing `research/derived/` packages remain unchanged retrieval aids.

---

## 2026-09-25 — New Balance pre-remediation compatibility evidence closure

After EV-376 reduced the open New Balance incompatibility to the raw55 Power/Sprint-origin `StatePosition=2` gate, EV-377 closed the requested equipped-Sprint and Sabertooth raw8 Sprint controls without finding a second contradiction. The broad temporary retention exception created during the open investigation was therefore no longer needed.

The **11 processed New Balance runtime artifacts** were moved byte-identically from intake to archive in one Git tree transaction:

```text
research/raw/2026.09.24_newbalance_blacktroll.log
    -> research/archive/2026.09.24_newbalance_blacktroll.log
    blob 528335dca84844db86385f2425f0a611ddfb1c67

research/raw/2026.09.24_newbalance_blacktroll_2.log
    -> research/archive/2026.09.24_newbalance_blacktroll_2.log
    blob e1215279fcefe4c0ee093abe6229a98ed17e0e92

research/raw/2026.09.24_newbalance_blacktroll_3.log
    -> research/archive/2026.09.24_newbalance_blacktroll_3.log
    blob 715a57e84d189fa59a73342f5858fa27c2781fe7

research/raw/2026.09.24_newbalance_different_weapons_no_target.log
    -> research/archive/2026.09.24_newbalance_different_weapons_no_target.log
    blob 4a20b99fcb2f80b50eb0dd47d7f4a290227574de

research/raw/2026.09.24_newbalance_fist_no_target.log
    -> research/archive/2026.09.24_newbalance_fist_no_target.log
    blob 4237c63bd4105b859ec1bbb54b3641222a88e229

research/raw/2026.09.24_newbalance_goblin.log
    -> research/archive/2026.09.24_newbalance_goblin.log
    blob 33900e6828a3633779472372aa4fabb2e1a09d67

research/raw/2026.09.24_newbalance_sabertooth.log
    -> research/archive/2026.09.24_newbalance_sabertooth.log
    blob 7d0e50328df213a37a32f21c6894128a1d9ec9e9

research/raw/2026.09.24_newbalance_troll.log
    -> research/archive/2026.09.24_newbalance_troll.log
    blob d6e262b8a5941ea55a2aab47fdc844ce940941b0

research/raw/2026.09.24_newbalance_troll2.log
    -> research/archive/2026.09.24_newbalance_troll2.log
    blob 8327578ae061c2b325d20017247a997b9cd4c8bc

research/raw/2026.09.25_newbalance_blackgoblin.log
    -> research/archive/2026.09.25_newbalance_blackgoblin.log
    blob c844fe24336af090a5bb356338f3292ea81e04d7

research/raw/2026.09.25_newbalance_sabertooth_2.log
    -> research/archive/2026.09.25_newbalance_sabertooth_2.log
    blob 40b0fc19a2075d67057273f5240aa155ab047686
```

Archive transaction:

```text
2e9079cfdeec75d5e7bbdfa5a8d20e840ea25160
```

Migration properties:

- every move reused the existing Git blob SHA;
- no log was downloaded, reconstructed, re-encoded, normalized, trimmed or regenerated;
- basenames and evidence meaning stayed unchanged;
- EV-376 owns the raw55 New Balance contradiction and bounded correction scope;
- EV-377 owns the focused equipped-Sprint/raw8-Sprint control conclusions;
- the large Sabertooth retrieval package remains at `research/derived/2026.09.25_newbalance_sabertooth_2_large_log/`;
- archived logs remain available for exact before/after comparison during remediation acceptance; they no longer need to occupy intake.

Verified post-migration intake state:

```text
research/raw/Keep.txt
```

This closes the stale broad active-comparison exception. The unresolved engineering responsibility is still the bounded raw55 SP2 correction; storage cleanup does not close EV-376 itself.

---

## 2026-09-26 — New Balance raw55 Sprint remediation closure

EV-378–EV-381 completed the focused New Balance raw55 Power/Sprint StatePosition remediation and runtime acceptance. The previously retained before/after comparison set no longer owns an open collision question.

The following **9 artifacts** were moved byte-identically by reusing their exact existing Git blob identities:

```text
research/raw/2026.09.25_newbalance_blacktroll_all_double_marker2.log
 -> research/archive/2026.09.25_newbalance_blacktroll_all_double_marker2.log
 blob f33b578479b8b38d5f18760b8254aa2e48d89b84

research/raw/2026.09.25_newbalance_blacktroll_all_single_marker2.log
 -> research/archive/2026.09.25_newbalance_blacktroll_all_single_marker2.log
 blob 05abf1f7a7e025ff9b1dbfbf33b5074e2c5f4b0d

research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_3.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_3.log
 blob cf0bd2e8883658697f66f4d2c0e5e2833b454289

research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_8.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_8.log
 blob 0b66fa4f17ec0909fa1f173a7fac9fdb4c30b070

research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_15.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_15.log
 blob c9a199d6acea5dd303d8d0eaff3f44411123668f

research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_3_test2.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_3_test2.log
 blob c2d6937feb521b213b8141d702e44b2f23342378

research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_8_test2.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_8_test2.log
 blob 99fe4f3fb5373088da155740d440b486fb6ac9c6

research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_15_test2.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_double_markers_1_15_test2.log
 blob 1c9e57619387f2a34ca7ea3bc73131f1056c95e1

research/raw/2026.09.26_newbalance_blacktroll_all_native_test.log
 -> research/archive/2026.09.26_newbalance_blacktroll_all_native_test.log
 blob 67a834077c04b4c980e78a13649ab9a20b18077e
```

Archive transaction:

```text
3fc7cec54f33cf3a96d9d3615559e9c3c8c67fba
```

Migration properties:

- all moves reused the original Git blob SHA, so content is byte-identical;
- no runtime artifact was rewritten, normalized, trimmed or re-encoded;
- EV-378–EV-381 own the promoted compatibility conclusions;
- the closed bounded Sprint second-FIST task moved to `docs/archive/investigations/` in the same archive transaction;
- the separate Normal/SP0 early-second-FIST question can use these archived artifacts later without retaining duplicate raw copies.

Verified intended post-migration intake state:

```text
research/raw/Keep.txt
```

---


## 2026-09-30 — Speed Sprint provenance reconciliation and native calibration closure

Normal Chat positively reconciled the three previously retained Sprint speed-probe artifacts and closed the processed September 30 human/Finishing calibration intake under POP-06.

The following artifacts were moved byte-identically by reusing their existing Git blob identities:

```text
research/raw/2026.09.29_sprint_probe_goblin.log
 -> research/archive/2026.09.29_sprint_probe_goblin.log
 blob 8e0472f1ca86202964eb05f54d6f9c2aa11d0db6

research/raw/2026.09.29_sprint_probe_troll.log
 -> research/archive/2026.09.29_sprint_probe_troll.log
 blob e65a0b4d1e4c81f01f33c181193db2d3391b2c5a

research/raw/2026.09.29_sprint_probe_troll_sabertooth_zombie.log
 -> research/archive/2026.09.29_sprint_probe_troll_sabertooth_zombie.log
 blob 18b31ccb65e5af283df28c6ef5be1cec515d009e

research/raw/2026.09.30_speed_calibration_human_weapon_types.log
 -> research/archive/2026.09.30_speed_calibration_human_weapon_types.log
 blob d69f4012bc1697c315bd0fe81c58843fd007c006

research/raw/2026.09.30_speed_calibration_human_weapon_types_finishing attacks.log
 -> research/archive/2026.09.30_speed_calibration_human_weapon_types_finishing attacks.log
 blob faadc0fa72fcb6921a895accdbf836f42b22d8ed

research/raw/2026.09.30_speed_calibration_human_weapon_types_finishing attacks2.log
 -> research/archive/2026.09.30_speed_calibration_human_weapon_types_finishing attacks2.log
 blob 8f8b76f5f98694d2ce833d0db3cddea2fffaafd8
```

Disposition/provenance:

- `sprint_probe_goblin.log` and `sprint_probe_troll_sabertooth_zombie.log` are explicitly named by the closed `SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE_RESULT.md` and ADR-0009.
- `sprint_probe_troll.log` is an earlier same-probe standalone Troll control showing ordinary Power and factual Sprint reaching the shared Power caller at the same `1.0` compatible speed. It adds no unresolved mechanism beyond the closed Sprint result and EV-396 and is archived as superseded/duplicate provenance rather than left in intake indefinitely.
- `speed_calibration_human_weapon_types.log` and the pre-extension finishing-attempt log are promoted through EV-397.
- `speed_calibration_human_weapon_types_finishing attacks2.log` is promoted through EV-398.
- All moves preserve exact existing blob identity; no runtime log content was rewritten.

After this transaction, intended intake is:

```text
research/raw/Keep.txt
research/raw/2026.09.29_speed calibration_1h_troll.log
```

The remaining EV-396 log is an explicit active comparison baseline and is not stale intake.


## 2026-10-01 — Speed representative-NPC / Goblin context comparison closure

EV-401 closed the only remaining comparison obligation owned by the September 30 representative-NPC log and the focused October 1 Goblin control. Both artifacts were moved byte-identically by reusing their existing Git blob identities:

```text
research/raw/2026.09.30_speed_calibration_representative_npcs.log
 -> research/archive/2026.09.30_speed_calibration_representative_npcs.log
 blob e800b0d0836b36e85c15a6c681415f9490a02809

research/raw/2026.10.01_speed_calibration_goblin.log
 -> research/archive/2026.10.01_speed_calibration_goblin.log
 blob 9859e3d5e9a77a8662fa84562f2c4f74a25f8745
```

Disposition/provenance:

- EV-400 owns the representative Hero/Orc/Goblin NPC checkpoint and originally retained the September 30 log for one open Goblin Power/Sprint comparison.
- EV-401 closes that comparison with same-run ordinary BlackGoblin Power Hit `1.0` versus factual Sprint Hit `1.5` through passed Power/Action2.
- The archive move preserves exact Git blob identity; neither runtime log was downloaded, rewritten, normalized, trimmed or regenerated.
- Historical references to the September 30 raw path resolve to the archived basename through this migration entry.

After this transaction, intended intake is again:

```text
research/raw/Keep.txt
research/raw/2026.09.29_speed calibration_1h_troll.log
```

The EV-396 baseline remains an explicit active comparison fixture while broad native calibration continues.


## 2026-10-01 — Speed separation identity campaign closure

EV-406 closed the diagnostics-only separation-profile identity campaign. All five processed runtime artifacts were moved byte-identically by reusing their existing Git blob identities:

```text
research/raw/2026.10.01_speed_identity_native_fist_orc_demon.log
 -> research/archive/2026.10.01_speed_identity_native_fist_orc_demon.log
 blob 4c8cb5466762e8854264bcc345c385c4c40f5dd2

research/raw/2026.10.01_speed_identity_zombie_separation.log
 -> research/archive/2026.10.01_speed_identity_zombie_separation.log
 blob d259ea2dd4d24a85f704558ae2815d69f6226b05

research/raw/2026.10.01_speed_identity_axe_separation.log
 -> research/archive/2026.10.01_speed_identity_axe_separation.log
 blob a73758f78812b521e3a9f034605234cb7597c94f

research/raw/2026.10.01_speed_identity_rapier_separation.log
 -> research/archive/2026.10.01_speed_identity_rapier_separation.log
 blob cfcb457361dff01ea6d7692b00da1d53c7efbfc1

research/raw/2026.10.01_speed_identity_zombie_axe_separation.log.log
 -> research/archive/2026.10.01_speed_identity_zombie_axe_separation.log.log
 blob e168c4f06e3f1ec60c850aab7830ad7d0b4007e8
```

Disposition/provenance:

- the unusual double `.log.log` basename on the combined Zombie+Axe artifact is preserved deliberately;
- no runtime artifact was rewritten, normalized, trimmed or regenerated;
- EV-406 owns the promoted human-Fist calibration and resolved animation-set identity conclusions;
- the closed temporary task moved to `docs/archive/investigations/SPEED_SEPARATION_PROFILE_IDENTITY_PROBE.md`;
- intended raw intake after this transaction returns to `Keep.txt` plus the deliberately retained EV-396 calibration baseline.


## 2026-10-05 — EV-396 calibration baseline archive after Speed closure

The EV-396 native calibration control remained in active intake only while broad native calibration was an active comparison campaign. EV-403 deliberately stopped broad creature calibration as a current Speed blocker, and EV-404 confirmed broad native calibration was no longer a Speed-finalization blocker. The retention condition therefore expired.

The processed artifact was moved byte-identically by reusing its existing Git blob identity:

```text
research/raw/2026.09.29_speed calibration_1h_troll.log
 -> research/archive/2026.09.29_speed calibration_1h_troll.log
 blob 048e6db37129e27e652b194e31c0e5503d4bd96d
```

Disposition/provenance:

- EV-396 remains the canonical native-control evidence for the recorded Hero 1H and Troll PhysicalFist speed observations.
- EV-403–EV-404 close the broad-calibration retention condition; this move changes storage only, not evidence meaning.
- the archive move preserves exact Git blob identity; the runtime log is not rewritten, normalized, trimmed or regenerated.
- historical references to the former raw path resolve to the archived basename through this migration entry.
- intended raw intake after this transaction is `research/raw/Keep.txt` only.


## 2026-10-07 — Bad-block player A/B causal comparison closure

EV-449–EV-450 closed the isolated player bad-block A/B mechanism experiment. Both runtime logs were moved byte-identically out of active intake after the comparison was fully interpreted.

```text
research/raw/2026-10-07_bad_block_player_whirl_control.log
 -> research/archive/2026-10-07_bad_block_player_whirl_control.log
 SHA256 71F75C30D4CF8A5BC3125CA581FE63B0E0F36C1A599E6A36CC15F2E855B6F96C
 blob f8e7e1107f22d6c2928a1ef3badb231eaff4e657

research/raw/2026-10-07_bad_block_player_whirl_protection.log
 -> research/archive/2026-10-07_bad_block_player_whirl_protection.log
 SHA256 F173C80B3F57E0336A149C459F3566047F099A0380F94FEE9AD61DEB50E711B2
 blob 2c1c86824dd98103f771dc78a45f9be0080e3ec3
```

Disposition/provenance:
- EV-449 owns the CONTROL baseline;
- EV-450 owns the paired PROTECTION result and causal conclusion;
- neither file was rewritten, normalized, trimmed or regenerated during archival;
- historical references to the CONTROL raw path resolve through this migration entry;
- intended active raw intake returns to `research/raw/Keep.txt` only.

---

## Rule for Future Moves

Record a migration boundary here when all are true:

```text
artifact has been interpreted
→ every reusable conclusion is in canonical evidence
   OR artifact is explicitly superseded/negative provenance
→ artifact is no longer an active comparison input
→ source path + content identity are known
→ artifact moves unchanged to archive/another deliberate provenance layer
→ historical/current paths would otherwise be ambiguous
```

Then:

```text
move unchanged
→ update current routes only where retrieval changed
→ add concise migration mapping here
```

Do not rewrite historical EV rows merely to keep paths cosmetically current. Do not add an entry for every ordinary archive move when no historical/current path ambiguity exists.
