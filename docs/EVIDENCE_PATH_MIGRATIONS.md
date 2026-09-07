# Gothic 3 Animation Behaviors — Evidence Path Migrations

**Status:** Canonical provenance-path map  
**Updated:** 2026-09-07

## Purpose

Record deliberate repository path migrations of canonical evidence artifacts without changing their content, identity, evidence meaning or historical Git provenance.

Use this only when processed canonical evidence moves between repository storage layers such as `research/raw/` -> `research/archive/`.

Historical evidence-ledger rows and old commits may keep the path that was correct when they were written. This map provides the forward location so historical wording does not need cosmetic rewriting merely because storage changed.

---

## 2026-09-07 — September collision/Fist stable-subsystem archive

At the completed human-Fist production checkpoint, all dated runtime logs then present in `research/raw/` for **2026-09-02 through 2026-09-07** had been interpreted/promoted sufficiently for their source artifacts to leave the active intake folder.

Migration rule:

```text
research/raw/<same September 2–7 basename>
    -> research/archive/<same basename>
```

Properties of the migration:

- every moved file keeps the exact existing Git blob SHA/content;
- no log is rewritten, normalized, trimmed or regenerated;
- basename is unchanged;
- prior evidence claims/status are unchanged;
- historical commits remain valid provenance;
- current routes should use `research/archive/...`;
- historical ledger rows that still spell `research/raw/...` resolve by the same basename through this map.

Verified migration set: **49 dated logs**.

The archive set covers the processed September expansion/Fist sequence, including:

```text
2026-09-02  Power / Pierce / Hack-callback startup evidence
2026-09-03  Pierce / SimpleWhirl controls
2026-09-04  Hack routing/source controls + SimpleWhirl StatePosition closure
2026-09-05  Fist Stage A/B + N1/N2A/N2B/N2C
2026-09-06  Fist N2D/N2E/N4/N5/N6 + OFF/interruption/Power controls
2026-09-07  final production Normal+Power frame-12 acceptance
```

Deliberately **not** migrated in this checkpoint:

```text
research/raw/Keep.txt
research/raw/ge3log10.log
```

`Keep.txt` preserves the intake directory. `ge3log10.log` remains unidentified/unprocessed and therefore stays in active raw intake until its provenance/status is established.

Local-only backup files outside the repository are not part of this migration.

---

## Rule for future moves

When another stable-subsystem checkpoint archives processed raw evidence:

```text
confirm artifact has been interpreted/promoted
-> identify exact source path + blob/content identity
-> move unchanged to archive
-> update current routes/indexes
-> record a migration boundary here when historical paths would otherwise become ambiguous
```

Do not rewrite historical evidence rows merely to keep storage paths cosmetically current when this migration map can preserve both provenance and retrieval.
