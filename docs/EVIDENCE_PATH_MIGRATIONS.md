# Gothic 3 Animation Behaviors — Evidence Path Migrations

**Status:** Canonical provenance-path lookup  
**Updated:** 2026-09-16

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
