# Derived Research Evidence

This directory contains reproducible analysis/navigation products generated from canonical runtime evidence.

The original source artifact remains authoritative under `research/raw/` while active and follows the normal archive lifecycle after processing. Files here do not replace or silently modify the original evidence.

For oversized runtime logs, use `tools/log_evidence/Build-LargeLogEvidencePackage.ps1` and follow `docs/LARGE_LOG_EVIDENCE_PROCEDURE.md`.

A large-log package is tied to its source through the SHA-256 recorded in `manifest.txt`. Generated indexes and context windows may be rebuilt when retrieval needs change; conclusions must still be traced back to the canonical raw artifact.
