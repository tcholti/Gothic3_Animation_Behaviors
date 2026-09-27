# Large-Log Evidence Tool

This directory contains the deterministic post-processing tools used by POP-07 for oversized runtime logs.

The canonical raw log remains untouched in `research/raw/` until normal POP-06 archival. Generated files under `research/derived/` are retrieval aids tied to the raw file by SHA-256; they do not replace canonical evidence.

`Prepare-Log.cmd` is for **large logs that are inefficient to retrieve directly**, not an automatic step for every diagnostic log. For a small CORE log, commit/push the unchanged raw log directly. When POP-07 is triggered for a genuinely large log, both the unchanged raw log and its generated derived package are committed and pushed together through GitHub Desktop. The Assistant then analyzes the derived package by default; the raw file remains canonical provenance and is opened only when a concrete byte-level/provenance/package-integrity reason requires it.

## Processed-log retrieval lock

When the User says a large log **has been processed**, or that `Prepare-Log.cmd` was used, that statement changes the normal retrieval path immediately:

```text
DO NOT start by opening the large raw log
DO NOT fetch a whole commit/diff merely because it contains the log/package
DO NOT walk every signals_part_* file
DO NOT walk every full_source_part_* file

START WITH:
  manifest.txt
  event_counts.tsv
  event_timeline_part_*.tsv
  the smallest relevant signal/index surface

THEN, only when a flagged event needs surrounding context:
  use full_source_index.tsv as a locator
  open only the exact full_source_part_* chunk/range containing that event
```

`full_source_part_*` exists as bounded random-access backing material, **not as a sequential reading assignment**. The complete mirror must never be interpreted as permission to load all chunks into Chat.

If the compact processed surfaces do not expose enough information for the frozen question, first use a narrower processed search/extract or identify the exact source-line range required. Do not fall back to brute-force traversal of the raw log or complete mirror merely because more context exists there.

This lock exists specifically to prevent oversized runtime evidence from consuming Chat context or timing out retrieval while preserving exact provenance and local source context when it is genuinely needed.

## Normal Windows workflow — one command or drag-and-drop

For routine use, use `Prepare-Log.cmd`.

From the repository root:

```powershell
.\tools\log_evidence\Prepare-Log.cmd ".\research\raw\example.log"
```

You can also drag a `.log` file onto `Prepare-Log.cmd` in Windows Explorer.

The wrapper:

- invokes PowerShell with `-NoProfile -ExecutionPolicy Bypass` only for the child process;
- writes the package under the repository's `research\derived` directory;
- rebuilds an existing package for the same source name;
- requires no Python or third-party program.

## What the package contains

For `research/raw/example.log`, the output directory is:

```text
research/derived/example_large_log/
```

It contains:

- `manifest.txt` — source path/name, SHA-256, byte/line counts, tool settings and file inventory;
- `event_counts.tsv` — whole-run event counts;
- `event_timeline_part_*.tsv` — chronological event-header locations;
- `signals_part_*.tsv` — standard high-signal matches plus optional caller-supplied patterns;
- `full_source_index.tsv` — maps every complete-source mirror part to its original line range;
- `full_source_part_*.txt` — a complete line-numbered mirror of the entire source log, split into small connector-friendly parts.

The complete-source mirror is intentionally comprehensive so later analysis does not depend on predicting every useful signal before generation. It is a **random-access fallback surface**: start with the compact manifest/count/timeline/signal/index outputs, then use `full_source_index.tsv` to open only the exact `full_source_part_*` context required for a flagged event. Do not sequentially inspect the complete mirror. The raw source remains the byte-faithful evidence authority.

## Built-in Gothic 3 signal vocabulary

Routine preparation automatically indexes important diagnostic families, including:

- invariant warnings, repair candidates, errors and mismatches;
- outstanding obligations;
- raw55 callback boundaries;
- raw55 selective group-suppression records;
- authored FIST activation and marker records;
- `ClearTriggeredList`;
- `OnDamage`;
- collision-group events;
- C1 cleanup/finalization;
- repair outcomes.

No signal arguments are required for the normal workflow.

## Existing advanced tool

`Build-LargeLogEvidencePackage.cmd` remains available for advanced POP-07 extraction when custom source-context windows or requested line ranges are useful. The routine Chat workflow should prefer `Prepare-Log.cmd` because it always creates the complete line-numbered source mirror and requires only the input log path.

## Evidence / publication rule

Do not rewrite, trim or replace the raw log to make retrieval easier. Generate or regenerate the derived package instead. The manifest records the raw source SHA-256 so the derived files can always be tied back to the canonical evidence.

Small-log publication sequence:

```text
place complete log in research/raw/
-> GitHub Desktop: review raw log
-> Commit
-> Push origin
-> tell Normal Chat the push is complete
```

Large-log POP-07 publication sequence:

```text
place complete log in research/raw/
-> run Prepare-Log.cmd
-> verify research/derived/<stem>_large_log/ was generated
-> GitHub Desktop: review both raw + derived changes
-> Commit both
-> Push origin
-> tell Normal Chat the push is complete
```

Normal Chat should start from the compact processed package surfaces for a POP-07 log and should not request the raw log again unless the package or provenance itself is insufficient. The presence of `full_source_part_*` does not authorize bulk traversal.

After interpretation, large-log evidence returns to the **same POP-06 closure path as every other runtime batch**: canonical EV representation, smallest required documentation/current-state maintenance, byte-identical archive of the processed raw source when no active comparison remains, raw-inventory verification, then the next test batch. POP-07 changes retrieval mechanics only; it does not defer or replace per-batch evidence closure.
