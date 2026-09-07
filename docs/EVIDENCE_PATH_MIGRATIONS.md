# Gothic 3 Animation Behaviors — Evidence Path Migrations

**Status:** Canonical provenance-path map  
**Updated:** 2026-09-07

## Purpose

Record deliberate repository path migrations of canonical evidence artifacts without changing their content, identity, evidence meaning or historical Git provenance.

Use this only when processed canonical evidence moves between repository storage layers such as `research/raw/` -> `research/archive/`.

Historical evidence-ledger rows and old commits may keep the path that was correct when they were written. This map provides the forward location so historical wording does not need cosmetic rewriting merely because storage changed.

This file is a path/provenance lookup, not an evidence ledger and not a current technical authority.

---

## 2026-09-07 — September collision/Fist stable-subsystem archive

At the completed human-Fist production checkpoint, the September 2–7 expansion/Fist runtime sequence was reviewed for evidence closure before archival. Missing canonical conclusions were promoted as EV-241–EV-244 before the source artifacts left active intake; intermediate Fist probes whose active questions were superseded by EV-221–EV-240 were classified as historical investigation provenance rather than given artificial new conclusions.

Migration rule for the **49 dated runtime logs** then present in `research/raw/` for 2026-09-02 through 2026-09-07:

```text
research/raw/<same September 2–7 basename>
    -> research/archive/<same basename>
```

A separate processed historical crash artifact was also migrated unchanged:

```text
research/raw/ge3log10.log
    -> research/archive/ge3log10.log
```

`ge3log10.log` is a Gothic 3 `EXCEPTION_ACCESS_VIOLATION` engine crash log dated 2026-09-03 from an earlier diagnostic state with `Script_FrameCollisionTest.dll` loaded. The User identified it as an old completed crash artifact; the current audit found no active unresolved crash responsibility tied to it. It is retained only as historical crash provenance.

Properties of the migration:

- every moved file keeps the exact existing Git blob SHA/content;
- no log is rewritten, normalized, trimmed or regenerated;
- basename is unchanged;
- prior evidence claims/status are unchanged;
- historical commits remain valid provenance;
- current routes should use `research/archive/...`;
- historical ledger rows that still spell `research/raw/...` resolve by the same basename through this map.

Verified migration set: **50 artifacts total** = 49 dated September 2–7 runtime logs + `ge3log10.log`.

The dated archive set covers:

```text
2026-09-02  Power / Pierce / Hack-callback startup evidence
2026-09-03  Pierce / SimpleWhirl controls
2026-09-04  Hack routing/source controls + SimpleWhirl StatePosition closure
2026-09-05  Fist Stage A/B + N1/N2A/N2B/N2C
2026-09-06  Fist N2D/N2E/N4/N5/N6 + OFF/interruption/Power controls
2026-09-07  final production Normal+Power frame-12 acceptance
```

Evidence-disposition notes relevant to archival:

- Power and Pierce reusable conclusions are canonically promoted in EV-241–EV-242.
- the September 4 SimpleWhirl StatePosition probe/revert/final regression is promoted in EV-243.
- Hack callback identity remains EV-216; later actual Hack marker/source validation is promoted in EV-244.
- Fist Stage A/B and N1–N6 reusable conclusions are covered by EV-221–EV-240. N2A/N2B and the earlier Stage-B causal-probe artifact are preserved as superseded investigation provenance within that causal progression; they do not carry an independent current engineering consequence.

Deliberately retained in active intake:

```text
research/raw/Keep.txt
```

`Keep.txt` preserves the intake directory. Local-only backup files outside the repository are not part of this migration.

---

## Rule for future moves

When another stable-subsystem checkpoint archives processed raw evidence:

```text
confirm artifact has been interpreted
-> ensure every reusable conclusion is promoted to the canonical evidence owner
   OR explicitly classify the artifact as superseded/negative provenance with no independent surviving conclusion
-> confirm it is not still needed as an active comparison input
-> identify exact source path + blob/content identity
-> move unchanged to archive
-> update current routes/indexes only where retrieval changed
-> record a migration boundary here when historical paths would otherwise become ambiguous
```

Do not rewrite historical evidence rows merely to keep storage paths cosmetically current when this migration map can preserve both provenance and retrieval.
