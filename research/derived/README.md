# Derived Research Evidence

This directory contains reproducible analysis/navigation products generated from canonical runtime evidence.

The original source artifact remains authoritative under `research/raw/` while active and follows the normal archive lifecycle after processing. Files here do not replace or silently modify the original evidence.

For ordinary oversized-runtime-log handling, follow [PROJECT_OPERATING_PROCEDURES.md — POP-07](../../docs/PROJECT_OPERATING_PROCEDURES.md#9-pop-07--large-runtime-log-analysis-without-losing-evidence) and the [tools/log_evidence/README.md](../../tools/log_evidence/README.md) `Prepare-Log.cmd` workflow. The [Build-LargeLogEvidencePackage.ps1](../../tools/log_evidence/Build-LargeLogEvidencePackage.ps1) generator remains available for advanced extraction.

A large-log package is tied to its source through the SHA-256 recorded in `manifest.txt`. Generated indexes and context windows may be rebuilt when retrieval needs change; conclusions must still be traced back to the canonical raw artifact.
