# Large-Log Evidence Tool

This directory contains the deterministic post-processing tools used by POP-07 for oversized runtime logs.

The canonical raw log remains untouched in `research/raw/`. Generated files under `research/derived/` are retrieval aids tied to the raw file by SHA-256; they do not replace canonical evidence.

For the normal project workflow, **both the unchanged raw log and its generated derived package are committed and pushed together through GitHub Desktop**. The Assistant then analyzes the derived package by default; the raw file remains canonical provenance and is opened only when a concrete byte-level/provenance/package-integrity reason requires it.

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

The complete-source mirror is intentionally comprehensive so later analysis does not depend on predicting every useful signal before generation. It is also the normal Assistant retrieval surface: use `manifest.txt`, indexes, and `full_source_part_*.txt` rather than repeatedly opening the oversized raw file. The raw source remains the byte-faithful evidence authority.

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

Normal publication sequence:

```text
place complete log in research/raw/
-> run Prepare-Log.cmd
-> verify research/derived/<stem>_large_log/ was generated
-> GitHub Desktop: review both raw + derived changes
-> Commit both
-> Push origin
-> tell Normal Chat the push is complete
```

Normal Chat should start from the processed package and should not request the raw log again unless the package or provenance itself is insufficient.
