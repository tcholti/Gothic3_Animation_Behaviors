# Large Runtime Log Evidence Procedure

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project procedure  
**Introduced:** 2026-08-29

## Purpose

Gothic 3 runtime investigations routinely produce logs that are too large for reliable direct retrieval through Chat/GitHub connectors. This is expected project behavior, not an exceptional failure case.

A large log may contain evidence that occurs long before the final visible symptom or crash. In particular, an unsafe transition may be observed several times before it causes a crash, and a long gameplay session may contain multiple distinct collision/lifecycle failure modes. Therefore a tail-only extract, a manually chosen excerpt, or a few aggregate counts are not sufficient as the default analysis method.

This procedure keeps the original raw artifact canonical while creating small, reproducible navigation products that let Normal Chat inspect the whole run and retrieve exact source windows when needed.

## Core rule

> **Preserve one canonical raw log, index the entire run, then retrieve exact contextual windows by original source line. Never treat a tail-only extract as a complete analysis of a large runtime log.**

## Evidence layers

### 1. Canonical raw artifact

The original runtime log remains unchanged under `research/raw/` while it is active evidence, and later follows the normal research/archive lifecycle.

The raw artifact is the authority for exact runtime text.

### 2. Derived large-log evidence package

For a log that cannot be reliably retrieved in full, generate a package with:

- `manifest.txt` — source filename, SHA-256, byte count, line count, package parameters and generated-part inventory;
- `event_counts.tsv` — complete counts for every `===== EVENT =====` block type found in the run;
- `event_timeline_part_*.tsv` — chronological index of every event block across the whole log, with original start/end lines and selected diagnostic fields;
- `signals_part_*.tsv` — every match for high-signal diagnostics such as invariant warnings, `WOULD_REPAIR`, failures, stale/mismatch indicators and unsafe/bad skips;
- `signal_context_part_*.txt` — merged original-line windows around all high-signal matches, with original source line numbers;
- optional `requested_ranges_part_*.txt` — exact additional source ranges requested during interpretation.

Every generated text part is intentionally kept small enough for reliable connector retrieval.

Derived packages live under `research/derived/`. They are navigation/analysis products, not a replacement for the raw artifact.

## Tool

Use:

`tools/log_evidence/Build-LargeLogEvidencePackage.ps1`

Default invocation from the repository root:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.ps1 `
    -InputPath '.\research\raw\<runtime-log-name>.log'
```

The default package is written to:

`research/derived/<runtime-log-name>_large_log/`

If the package already exists and must be deterministically rebuilt from the same raw source:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.ps1 `
    -InputPath '.\research\raw\<runtime-log-name>.log' `
    -Force
```

When interpretation identifies exact source ranges that require more context:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.ps1 `
    -InputPath '.\research\raw\<runtime-log-name>.log' `
    -RequestedRange '121700-122050','134200-134500' `
    -Force
```

Additional investigation-specific regexes can be added without changing the raw log:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.ps1 `
    -InputPath '.\research\raw\<runtime-log-name>.log' `
    -ExtraSignalPattern 'YOUR_PATTERN_HERE' `
    -Force
```

## Standard large-log handoff

When a controlled runtime log is expected to become evidence:

```text
Normal Chat defines test + exact research/raw filename
        ↓
User runs the test and places the unchanged log in research/raw/
        ↓
User verifies/stages/commits/pushes the raw artifact
        ↓
Normal Chat attempts direct retrieval
        ↓
raw log is too large or direct line retrieval is unreliable?
        ├─ no  → analyze the raw log normally
        └─ yes → generate the standard large-log evidence package locally
                    ↓
                 commit/push only that package
                    ↓
                 Normal Chat reads manifest + whole-run indexes first
                    ↓
                 retrieve signal contexts and exact requested ranges as needed
                    ↓
                 interpret + perform normal knowledge maintenance
```

The User should not paste the full large log into Chat.

## Analysis order

For a large runtime log, Normal Chat should normally inspect in this order:

1. **Manifest**
   - verify the package SHA-256 matches the intended raw artifact;
   - verify byte and line counts;
   - note the number of event/signal/context parts.

2. **Event counts**
   - identify which diagnostic families actually occurred;
   - do not infer correctness from counts alone.

3. **Whole-run event timeline**
   - locate all relevant collision, lifecycle, AI state, stop/finalization and guard events across the session;
   - identify repeated patterns, not merely the last occurrence.

4. **Signal index**
   - enumerate every invariant warning, `WOULD_REPAIR`, failure/stale/mismatch signal and other configured abnormal event;
   - distinguish multiple abnormal patterns if they exist.

5. **Signal contexts**
   - inspect the original lines around every abnormal occurrence;
   - compare early, repeated and final occurrences;
   - determine what the shadow/diagnostic guardian observed versus what physical collision actually did.

6. **Crash or final symptom correlation**
   - only after whole-run enumeration, correlate the final runtime events with engine crash logs or the User's visual observation;
   - a final crash may be the delayed consequence of a transport/lifecycle defect already survived earlier in the run.

7. **Additional exact ranges**
   - if a relevant event is visible in the timeline but not covered by an automatic signal window, regenerate the package with `-RequestedRange` for that original source interval;
   - do not rerun Gothic 3 merely because Chat cannot directly retrieve a large raw range.

## Interpretation safeguards

- A signal match is an index lead, not automatically a defect.
- A warning count is not a substitute for reading the corresponding contexts.
- A tail window is useful for crash correlation but is not evidence that earlier parts of the run were clean.
- User visual observations remain valuable evidence and should be correlated with the log rather than discarded when the logger cannot directly encode the visual effect.
- Distinguish diagnostic/shadow actions such as `WOULD_REPAIR` from actual physical mutations.
- Preserve the raw SHA-256 in any derived package or evidence conclusion so the source can be verified later.
- If the logger vocabulary evolves, extend signal patterns or selected event fields; do not rewrite old raw evidence.

## Repository-size rule

Do **not** duplicate the entire raw log into connector-sized copies by default. The whole-run event/signal indexes plus targeted context windows provide navigability while avoiding a second full copy of every large runtime log in Git history.

If a future case proves that indexed/targeted retrieval cannot recover required evidence reliably, this rule can be revised from evidence.

## Relationship to the normal runtime-log procedure

This document is the large-log extension of the runtime test log handoff in `docs/COLLABORATION_RULES.md`.

The normal rule remains: preserve the raw log in GitHub and analyze it from the repository rather than pasting it into Chat. When connector size/retrieval limits prevent reliable direct analysis, this procedure supplies the missing retrieval layer.

The procedure should be revised when repeated use shows that it misses important event classes, produces excessive noise, or creates unnecessary manual work.
