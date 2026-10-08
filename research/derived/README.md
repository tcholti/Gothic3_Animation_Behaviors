# Derived Research Evidence

This directory is the working location for new/open deterministic analysis and navigation packages generated from canonical runtime evidence. POP-07 continues to create new packages here.

The original source artifact remains authoritative under `research/raw/` while active and follows the normal archive lifecycle after processing. Files here do not replace or silently modify the original evidence.

For ordinary oversized-runtime-log handling, follow [PROJECT_OPERATING_PROCEDURES.md — POP-07](../../docs/PROJECT_OPERATING_PROCEDURES.md#9-pop-07--large-runtime-log-analysis-without-losing-evidence) and the [tools/log_evidence/README.md](../../tools/log_evidence/README.md) `Prepare-Log.cmd` workflow. The [Build-LargeLogEvidencePackage.ps1](../../tools/log_evidence/Build-LargeLogEvidencePackage.ps1) generator remains available for advanced extraction.

A large-log package is tied to its source through the SHA-256 recorded in `manifest.txt`. Generated indexes and context windows may be rebuilt when retrieval needs change; conclusions must still be traced back to the canonical raw artifact.

Completed packages preserved by the approved archival stage are under [`research/archive/derived/`](../archive/derived/), retaining the exact package name and complete internal layout. Recover an old `research/derived/<package>/...` route as `research/archive/derived/<same-package>/...` for the frozen set in [EVIDENCE_PATH_MIGRATIONS](../../docs/EVIDENCE_PATH_MIGRATIONS.md#2026-10-08--completed-derived-evidence-archival). This is cold retrieval storage, not the output location for new packages.

Start with the current reference and [EVIDENCE_INDEX](../../docs/EVIDENCE_INDEX.md), then the exact EV. When deeper verification is needed, open the archived package's manifest and compact counts/indexes, then only the required source part or context range. Its recorded `SourceFileName` resolves to the unchanged canonical original in `research/archive/`; historical `SourceInput` text remains intact. The three closed manual checkpoints moved to `docs/archive/investigations/` through the same migration record. Archived generated files and manual checkpoints are preserved provenance, not current feature authorities.
