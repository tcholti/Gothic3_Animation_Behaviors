# Large-Log Evidence Tool

This directory contains the deterministic post-processing tool used by POP-07 for oversized runtime logs.

## Normal Windows entrypoint

Use the wrapper, not the PowerShell script directly:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.cmd <arguments>
```

The wrapper is the preferred Windows entrypoint because it deliberately provides both pieces of environment handling the underlying script should not require the User to manage manually:

```text
powershell.exe -NoProfile -ExecutionPolicy Bypass
+ absolute repository-root research\derived OutputRoot
```

This avoids two observed failure modes when invoking `Build-LargeLogEvidencePackage.ps1` directly:

1. a normal Windows execution policy may reject the `.ps1` before it runs;
2. a relative `OutputRoot` can be resolved by .NET against the process working directory rather than the PowerShell logical location, which can send output toward an unrelated directory (observed with the Visual Studio process directory).

The wrapper's `ExecutionPolicy Bypass` applies only to the child PowerShell process it launches. It does not require changing the machine's permanent execution policy.

## Example

From the repository root:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.cmd `
    -InputPath '.\research\raw\example.log' `
    -ExtraSignalPattern 'REPAIRED_TO_ITEM_EQUIPPED' `
    -ExtraSignalPattern 'REPAIR_DIVERGED_FROM_ITEM_EQUIPPED'
```

For a plain package with only the tool's built-in signal vocabulary:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.cmd `
    -InputPath '.\research\raw\example.log'
```

## Evidence rule

The source raw log remains canonical evidence. The generated directory under `research/derived/` is only a deterministic retrieval/analysis aid. Do not rewrite, trim, or replace the raw log to make connector retrieval easier.

If direct `.ps1` invocation is ever genuinely necessary, pass an absolute `-OutputRoot` and use an execution-policy scope appropriate to that explicit manual operation. Direct invocation is not the default project procedure.
