# Gothic 3 Animation Behaviors — Evidence Path Migrations

**Status:** Canonical provenance-path lookup  
**Updated:** 2026-09-12

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

The raw55 baseline and callback-suppression logs were intentionally **not** archived at this boundary. EV-262 closes their current evidence interpretation, but both remain active comparison inputs for the unresolved Quick-specific causal question:

```text
research/raw/2026.09.12_troll_collision_test.log
research/raw/2026.09.12_troll_and_other_marker_test.log
```

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
