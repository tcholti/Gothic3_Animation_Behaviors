# Gothic 3 Project Operating Procedures

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific procedure library  
**Version:** 1.2  
**Updated:** 2026-08-30

## Purpose

This document stores recurring operational patterns that are useful during normal Gothic 3 development but do not belong in technical architecture, evidence, current-state, bounded Work authority, or stable project convention authority.

It exists so a new Chat does not have to rediscover how we normally:

- synchronize and hand off the active Git branch;
- build the current prototype;
- deploy and verify a DLL before testing;
- verify that a diagnostic build actually loaded;
- freeze runtime tests/logs;
- preserve and publish raw evidence;
- reduce oversized logs for efficient analysis without altering the evidence;
- work with large static binary/reference material.

`PROJECT_PIPELINE.md` owns the stable naming, numbering, version/test ID, branch/state, artifact-flow and validation-gate conventions used by these procedures. This file owns the **sequences**, not independent alternative convention schemes.

These are reconstructable procedure patterns, not mandatory reading before every prompt and not frozen law.

The procedure-evolution rule is owned by `COLLABORATION_RULES.md` §9: use the established procedure without repeatedly auditing it, but if either participant notices repeated friction/mistakes, one serious failure, or a clearly better method, raise the improvement and revise the lowest owning procedure.

---

## 1. When to Read This Document

Read or spot-read this document when entering an active local-operation sequence such as:

- source review → build → deploy → runtime test;
- runtime evidence capture/publish;
- Git handoff between connected GitHub writes and the User's local checkout;
- large-log or large-reference retrieval.

Do not reread it after every prompt or every attack/test repetition.

A procedure name should usually be enough to reconstruct the sequence from memory/context. Open the exact section only when the detailed sequence or failure branch matters.

This document does not replace:

- `PROJECT_PIPELINE.md` — stable project naming/numbering/version/test/artifact conventions;
- `WORK_IMPLEMENTATION_PROTOCOL.md` — bounded implementation/Work execution;
- `KNOWLEDGE_MAINTENANCE.md` — what durable authorities change after a meaningful result;
- `SESSION_ENTRYPOINT.md` — current technical responsibility;
- `BETWEEN_CHATS.md` — transient exact handoff when needed.

---

## 2. End-to-End Validation Cue

For a normal engine-facing prototype change, the broad sequence is:

```text
design/evidence question frozen
→ bounded implementation when needed
→ implementation commit/publish
→ independent Normal Chat source review
→ User/local branch synchronization
→ build only
→ deploy exact built DLL
→ verify single live DLL + SHA match
→ launch/load verification + expected startup banner
→ freeze exact runtime matrix + raw filename
→ User runs test
→ raw log copied unchanged into research/raw
→ raw artifact commit/push
→ Normal Chat analyzes committed evidence
→ derived package/extract only if retrieval requires it
→ normal knowledge-maintenance transaction
```

This sequence conforms to the validation pipeline in `PROJECT_PIPELINE.md`. Do not collapse separate validation stages merely to save a message when the separation protects causal certainty. A successful build does not prove deployment; a matching deployment does not prove load; a startup banner does not prove runtime behavior.

---

## 3. POP-01 — Git Branch Handoff and Synchronization

### Trigger

Use whenever connected GitHub/assistant writes and the User's local checkout both need to write to the same active branch.

### Core rule — one branch writer window at a time

```text
Assistant finishes any required remote GitHub writes
→ Assistant identifies the resulting remote state
→ User synchronizes local checkout if needed
→ Assistant hands branch to User
→ Assistant does not push/write that branch during the User window
→ User performs local artifact/build-related commit and pushes
→ User reports successful push/SHA
→ branch returns to Assistant-side writes when needed
```

Once Normal Chat gives the User a local commit/push sequence, Normal Chat should not create another commit on that branch until the User reports that their push has completed or the handoff is explicitly cancelled.

This avoids the repeated pattern:

```text
Assistant pushes
→ User commits locally from older head
→ User push rejected: fetch first
→ avoidable pull/rebase/push cycle
```

### Preferred synchronization point

If the assistant has changed the remote branch since the User last synchronized, perform the pull/rebase before the User begins a new local artifact/commit window whenever practical.

Current active branch/state meaning is owned by `SESSION_ENTRYPOINT.md` + `PROJECT_PIPELINE.md`. At this revision the active branch is:

```text
docs/collision-source-evidence
```

Typical synchronization:

```powershell
Set-Location 'E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors'

git pull --rebase origin docs/collision-source-evidence
```

Do not run a blind pull/rebase across important uncommitted local work. The normal handoff rule should make that unnecessary; if local work already exists, inspect the concrete state first.

### If a push is rejected with `fetch first`

If the intended local commit already exists and the only problem is that the remote branch advanced:

```powershell
git pull --rebase origin docs/collision-source-evidence
git push origin docs/collision-source-evidence
git rev-parse HEAD
```

If rebase reports a conflict, stop the routine procedure and inspect that conflict. Do not automatically choose one side.

---

## 4. POP-02 — Build Only

### Trigger

Use after the relevant source implementation has passed its required source-level review and a local runtime binary is needed.

### Pattern

```text
correct branch/source state
→ build requested target
→ User reports success or smallest useful error excerpt
→ STOP build stage
```

Current prototype command:

```powershell
Set-Location 'E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors'

cmake --build build --config Release --target Script_FrameCollisionTest
```

A successful build does not automatically deploy the DLL.

For a normal success, the User only needs to report that it succeeded. Do not ask for the complete successful build output.

If the build fails, request or use only the smallest relevant error excerpt first. Broaden only when needed.

---

## 5. POP-03 — Deploy and Binary-Identity Verification

### Trigger

Use after a successful build and before launching Gothic 3 for that build.

### Current paths

Built DLL:

```text
E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors\build\prototypes\Script_FrameCollisionTest\Release\Script_FrameCollisionTest.dll
```

Live DLL:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_FrameCollisionTest.dll
```

### Pattern

```text
copy exact built DLL to live scripts
→ enumerate matching live DLL names
→ require exactly one intended matching DLL
→ SHA256 built == live
→ only then launch
```

Typical command:

```powershell
$built = 'E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors\build\prototypes\Script_FrameCollisionTest\Release\Script_FrameCollisionTest.dll'
$liveDir = 'E:\SteamLibrary\steamapps\common\Gothic 3\scripts'
$live = Join-Path $liveDir 'Script_FrameCollisionTest.dll'

Copy-Item -LiteralPath $built -Destination $live -Force

Get-ChildItem -LiteralPath $liveDir -Filter 'Script_FrameCollisionTest*.dll' |
    Select-Object Name, Length, LastWriteTime

(Get-FileHash $built -Algorithm SHA256).Hash -eq (Get-FileHash $live -Algorithm SHA256).Hash
```

Expected:

- one intended `Script_FrameCollisionTest.dll`;
- final comparison `True`.

Never leave backup/alternate DLLs matching the same loader pattern in the live `scripts` directory. If duplicates appear or the hash is false, stop before launching and resolve deployment first.

---

## 6. POP-04 — Startup / Load Verification

### Trigger

Use after deploy/hash verification and before spending time on a runtime matrix.

### Pattern

```text
launch Gothic 3 only far enough to load the script
→ reach main menu or other agreed minimal load point
→ exit normally
→ search current log for the exact startup/banner text of this build
→ only then freeze/run the behavioral matrix
```

For `Script_FrameCollisionTest`, the current log is normally:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\Script_FrameCollisionTest.log
```

Normal Chat should provide the exact banner substring for the build being tested rather than expecting the User to remember it.

The build-identity convention is owned by `PROJECT_PIPELINE.md`: active gate/probe label + exact Git commit + deployed DLL identity/hash + startup banner.

Typical check:

```powershell
$log = 'E:\SteamLibrary\steamapps\common\Gothic 3\Script_FrameCollisionTest.log'

Select-String -Path $log -Pattern '<exact frozen startup banner substring>'
```

Missing banner, wrong binary, load failure, or crash is a stop condition for the runtime matrix.

---

## 7. POP-05 — Freeze a Runtime Test and Raw Filename

### Trigger

Use when a controlled runtime run is intended to answer an active causal/validation question and the log is worth preserving.

### Normal Chat responsibility before the run

Freeze in the same message whenever practical:

1. the exact test purpose;
2. the minimum fixture/configuration cases;
3. important ordering/reset requirements;
4. the outcomes or invariants to watch for;
5. one exact raw filename.

Do not change the meaning of the test after the run merely to fit the observed result.

### Naming authority

The canonical gate/test-ID and raw/derived filename conventions live in `PROJECT_PIPELINE.md` §§3, 6–7.

POP-05 owns the act of freezing the test and one exact filename; it does not define a separate naming scheme.

Before inventing a new gate/test identifier or filename pattern, retrieve the relevant pipeline section and preserve the established convention.

If a test crosses midnight or is delayed after the filename is frozen, keep the frozen filename unless there is a concrete reason to rename it; consistency with the recorded test contract matters more than cosmetic date perfection.

### User responsibility

Run the test, then copy the complete produced log to the exact frozen path.

Extra repetitions are acceptable and often useful. If the configuration/order materially differs from the frozen matrix, tell Normal Chat so interpretation can distinguish those sections.

After copying, a short confirmation such as:

```text
file is in raw
```

is enough. Do not paste the full log into Chat by default.

---

## 8. POP-06 — Raw Runtime Evidence Integrity and Publish

### Raw evidence rule

A file in `research/raw/` is canonical raw evidence.

Preserve it byte/content-faithfully:

- do not clean trailing whitespace;
- do not reformat/rewrite it for readability;
- do not remove noisy lines from the canonical raw artifact;
- do not use `git diff --cached --check` as a pass/fail validator for raw logs, because logger-produced whitespace may be legitimate raw content.

Editable source/docs may still use normal whitespace/diff checks.

### Publish pattern

The normal sequence is:

```text
User confirms exact raw file exists
→ branch handoff/sync already settled
→ verify exact path/status
→ stage only intended artifact(s)
→ descriptive commit
→ push active branch
→ report resulting SHA
→ Assistant reads committed artifact from GitHub
```

Typical command pattern:

```powershell
Set-Location 'E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors'

$log = '.\research\raw\<frozen-log-name>.log'

Get-Item -LiteralPath $log |
    Select-Object Name, Length, LastWriteTime

git status --short -- $log
git add -- $log
git commit -m '<descriptive evidence commit message>'
git push origin docs/collision-source-evidence
git rev-parse HEAD
```

Normal Chat should normally ask only for the final SHA or a short success confirmation.

---

## 9. POP-07 — Large Runtime Log Analysis Without Losing Evidence

### Trigger

Use when the canonical raw log is too large for efficient GitHub/connector retrieval or would create unnecessary Chat/tool context pressure.

### Core rule

Do not reduce or rewrite the raw logger output merely to make retrieval easier.

Instead:

```text
full canonical raw log
→ deterministic local post-processing
→ derived retrieval package under research/derived/
→ Assistant reads manifest/counts/signals/timeline slices first
→ raw remains canonical and available for exact verification
```

The raw log remains the evidence. Derived files are retrieval/analysis aids.

### Current reusable tool

The project now has a deterministic large-log packaging tool at:

```text
tools/log_evidence/
```

On Windows, use the wrapper entrypoint rather than invoking the PowerShell implementation directly:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.cmd <arguments>
```

The wrapper deliberately provides:

```text
powershell.exe -NoProfile -ExecutionPolicy Bypass
+ absolute repository-root research\derived OutputRoot
```

This avoids the two already-observed direct-`.ps1` failure modes:

1. local execution policy rejecting the script before it runs;
2. relative `OutputRoot` resolving against an unrelated process working directory.

The wrapper's `ExecutionPolicy Bypass` applies only to its child PowerShell process and does not require changing the machine's permanent policy.

Full tool usage and argument examples: `tools/log_evidence/README.md`.

### Derived package requirements

The deterministic package should record/provide enough mechanically extracted information to support causal retrieval, including as applicable:

- source raw relative path;
- source SHA256;
- source byte/line count;
- tool/version identity and extraction criteria;
- event counts;
- event timeline chunks;
- high-signal signal index/context chunks;
- lifecycle start/status/finalization;
- offensive requests, including `7 -> 7`;
- cleanup observations;
- `WOULD_REPAIR` / `REPAIRED_TO_ITEM_EQUIPPED` / repair divergence outcomes;
- invariant warnings/unowned/overlap/generation-change/liveness failures;
- CombatMove/AIFullStop/AISetState context when relevant;
- timestamps, action/phase/state and source identity/side/group;
- enough context to distinguish fixtures/configurations.

Current derived package location is normally:

```text
research/derived/<raw-stem>_large_log/
```

The source raw artifact remains unchanged in `research/raw/` or its later canonical archive location according to the normal evidence lifecycle.

Derived naming conventions are owned by `PROJECT_PIPELINE.md`.

### Extra signal vocabulary

When the current gate introduces high-signal strings not covered by the tool's built-in vocabulary, pass only the exact additional patterns needed for that gate. Example:

```powershell
.\tools\log_evidence\Build-LargeLogEvidencePackage.cmd `
    -InputPath '.\research\raw\example.log' `
    -ExtraSignalPattern 'REPAIRED_TO_ITEM_EQUIPPED' `
    -ExtraSignalPattern 'REPAIR_DIVERGED_FROM_ITEM_EQUIPPED'
```

Do not rewrite the raw log merely because the built-in signal vocabulary needs extension.

### Direct `.ps1` invocation

Direct invocation is not the normal procedure. If it is genuinely necessary, use an absolute `-OutputRoot` and an execution-policy scope appropriate to that explicit manual operation.

Do not move extraction logic into production/runtime behavior merely for connector convenience.

---

## 10. POP-08 — Large Static Binary / Reference Retrieval

Runtime logs and static binary references should not use the same reduction strategy.

For large extracted/disassembled `Game`, `Engine`, `Script_Game`, or similar static reference material:

```text
complete local/extracted provenance
→ split/index into manageable stable chunks in Gothic3_Binary_Reference
→ retrieve by module + RVA/symbol/import/search term
→ open only the relevant chunk/region
```

The purpose of splitting static material is direct random access, not evidence summarization. Preserve enough indexing that an address such as `Script_Game +0x41D5A` can route directly to its surrounding static code without loading a monolithic dump.

Do not repeatedly regenerate/reupload the whole reference merely because another static question arises. Extend or revise the reference structure only when retrieval actually fails or the source set changes.

Exact static-engine findings that become project evidence still belong in the appropriate Gothic 3 evidence/source authority; the binary-reference repository is a retrieval/provenance surface, not the only interpretation authority.

---

## 11. POP-09 — Routine Failure / Stop Behavior

Routine procedures should fail narrowly and visibly rather than accumulating compensating steps.

Examples:

```text
build error
→ inspect smallest useful error excerpt

multiple matching live DLLs
→ stop before game launch

built/live SHA mismatch
→ stop before game launch

startup banner missing / load crash
→ stop before runtime matrix

Git rebase conflict
→ stop automatic Git procedure and inspect conflict

unexpected invariant warning in a diagnostic
→ treat as evidence/design question, not something to filter out
```

Do not ask the User for full successful outputs or entire logs merely because a command was run. Expand output only when the current failure cannot be diagnosed from the compact result.

---

## 12. Procedure Maintenance

The active procedure is the current best default. Git history preserves old versions; the active document should not accumulate obsolete variants.

Use this maintenance trigger:

```text
use procedure normally
→ no routine audit
→ repeated friction/mistake OR one serious failure OR clearly better method appears
→ whichever participant notices first raises it
→ diagnose actual cause
→ revise the smallest owning procedure/rule
→ continue using revised procedure
```

If the issue is actually a naming/numbering/version/state convention rather than a recurring sequence, update `PROJECT_PIPELINE.md` instead of silently embedding a new convention here.

When a procedure becomes too long, ask whether stable detail can be moved into a reusable script/tool while this document keeps only the trigger, invariant, and sequence cue.

When a new recurring operation appears, first ask whether an existing POP section can absorb it. Create another procedure only when the responsibility is genuinely distinct and expected to recur.

---

## Quick Procedure Index

| Cue | Procedure |
|---|---|
| assistant/user both writing same branch | POP-01 Git branch handoff and synchronization |
| source reviewed, need DLL | POP-02 Build only |
| build succeeded, need live DLL | POP-03 Deploy and binary-identity verification |
| DLL copied, before full test | POP-04 Startup/load verification |
| ready for controlled runtime evidence | POP-05 Freeze runtime test and raw filename |
| runtime log copied locally | POP-06 Raw evidence integrity and publish |
| raw log too large to retrieve efficiently | POP-07 Large runtime log analysis |
| large static Engine/Game/Script_Game material | POP-08 Static binary/reference retrieval |
| routine command/procedure fails | POP-09 Routine failure/stop behavior |

## Core Procedure Rule

> **Preserve causal certainty and canonical evidence, hand the active Git branch between writers deliberately, use the stable project conventions rather than reinventing them, keep routine outputs compact, and store reusable operational patterns externally so future Chats can reconstruct the workflow without repeatedly rediscovering it.**