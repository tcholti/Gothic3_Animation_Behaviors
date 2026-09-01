# Gothic 3 Project Operating Procedures

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific procedure library  
**Version:** 1.6  
**Updated:** 2026-09-01

## Purpose

This document stores recurring operational patterns that are useful during normal Gothic 3 development but do not belong in technical architecture, evidence, current-state, bounded Work authority, stable project convention authority, participant-allocation rules, or the project charter.

It exists so a new Chat does not have to rediscover how we normally:

- synchronize and hand off the active Git branch;
- build the selected current product/target;
- deploy and verify a DLL before testing;
- verify that the selected product actually loaded;
- freeze runtime tests/logs;
- preserve and publish raw evidence;
- reduce oversized logs for efficient analysis without altering the evidence;
- work with large static binary/reference material;
- preflight a formal project review/audit so it respects the project hierarchy and each target's intended use.

`docs/README.md` is the Gothic project charter and highest project-specific authority beneath CAM for project purpose, long-term direction, scope and authority topology.

`PROJECT_PIPELINE.md` owns the stable naming, numbering, version/test ID, branch/state, product-identity, artifact-flow and validation-gate conventions used by these procedures. This file owns the **recurring sequences and their failure/stop behavior**, not independent alternative convention schemes.

Participant/tool allocation is owned by `COLLABORATION_RULES.md`. Bounded Work implementation execution is owned by `WORK_IMPLEMENTATION_PROTOCOL.md`.

These are reconstructable procedure patterns, not mandatory reading before every prompt and not frozen law. Procedure maintenance/evolution is owned by §13 below; `KNOWLEDGE_REGISTRY.md` determines whether a discovered improvement belongs here or in another authority.

---

## 1. When to Read This Document

Read or spot-read this document when entering an active local-operation sequence such as:

- source review → build → deploy → runtime test;
- runtime evidence capture/publish;
- Git handoff between connected GitHub writes and the User's local checkout;
- large-log or large-reference retrieval;
- a formal review/audit of project rules, procedures, architecture, documentation/knowledge structure, repository shape, or another cross-authority project surface.

Do not reread it after every prompt or every attack/test repetition.

A procedure name should usually be enough to reconstruct the sequence from memory/context. Open the exact section only when the detailed sequence or failure branch matters.

This document does not replace:

- `README.md` — project charter, highest project-specific authority, authority topology and retrieval map;
- `PROJECT_PIPELINE.md` — stable project naming/numbering/version/test/product/artifact conventions;
- `COLLABORATION_RULES.md` — User/Normal Chat/Work/home-PC/repository responsibility allocation and Gothic CAM operationalization;
- `WORK_IMPLEMENTATION_PROTOCOL.md` — bounded implementation/Work execution;
- `KNOWLEDGE_MAINTENANCE.md` — what durable authorities change after a meaningful result;
- `SESSION_ENTRYPOINT.md` — current technical responsibility;
- `BETWEEN_CHATS.md` — transient exact handoff when needed.

---

## 2. End-to-End Validation Cue

For a normal engine-facing change, the broad sequence is:

```text
design/evidence question frozen
→ bounded implementation when needed
→ implementation commit/publish
→ independent Normal Chat source review
→ User/local branch synchronization
→ select exact build product/target for the question
→ build only
→ deploy exact built DLL
→ verify selected product is the only intended live twin + SHA match
→ startup/load verification appropriate to that product
→ freeze exact runtime matrix + raw filename when diagnostic evidence is expected
→ User runs test
→ raw log copied unchanged into research/raw when the selected product emits canonical evidence
→ raw artifact commit/push
→ Normal Chat analyzes committed evidence
→ derived package/extract only if retrieval requires it
→ normal knowledge-maintenance transaction
```

This sequence conforms to the validation pipeline in `PROJECT_PIPELINE.md`. Do not collapse separate validation stages merely to save a message when the separation protects causal certainty. A successful build does not prove deployment; a matching deployment does not prove load; diagnostic banner presence proves neither the later behavioral result nor behavior-only loading.

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

The exact active branch is current project state owned by `SESSION_ENTRYPOINT.md` / `PROJECT_PIPELINE.md`; this procedure must not maintain a competing branch identity.

Typical synchronization shape:

```powershell
Set-Location 'E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors'

$branch = '<active branch from SESSION_ENTRYPOINT.md>'
git pull --rebase origin $branch
```

Normal Chat should normally provide the resolved exact branch in the concrete command rather than making the User look it up manually.

Do not run a blind pull/rebase across important uncommitted local work. The normal handoff rule should make that unnecessary; if local work already exists, inspect the concrete state first.

### If a push is rejected with `fetch first`

If the intended local commit already exists and the only problem is that the remote branch advanced:

```powershell
$branch = '<active branch from SESSION_ENTRYPOINT.md>'
git pull --rebase origin $branch
git push origin $branch
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
→ choose the exact target required by the frozen question
→ build only that target
→ User reports success or smallest useful error excerpt
→ STOP build stage
```

Current collision research targets:

```text
Script_FrameCollisionTest
= diagnostic twin

Script_FrameCollisionBehaviorTest
= diagnostics-free behavior twin
```

Example diagnostic build:

```powershell
Set-Location 'E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors'

cmake --build build --config Release --target Script_FrameCollisionTest
```

Example behavior-only build:

```powershell
cmake --build build --config Release --target Script_FrameCollisionBehaviorTest
```

Do not build both merely because both exist; build the product selected by the current test responsibility.

A successful build does not automatically deploy the DLL.

For a normal success, the User only needs to report that it succeeded. Do not ask for the complete successful build output.

If the build fails, request or use only the smallest relevant error excerpt first. Broaden only when needed.

---

## 5. POP-03 — Deploy and Binary-Identity Verification

### Trigger

Use after a successful build and before launching Gothic 3 for that build.

### Current collision twin paths

Both collision research targets are emitted from the same prototype build directory:

```text
E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors\build\prototypes\Script_FrameCollisionTest\Release\
```

Current product files:

```text
Script_FrameCollisionTest.dll
= diagnostic twin

Script_FrameCollisionBehaviorTest.dll
= diagnostics-free behavior twin
```

Live scripts directory:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts
```

### Pattern

```text
resolve the exact selected built DLL
→ remove/avoid the other mutually exclusive collision twin from the live directory
→ copy selected DLL to its exact live name
→ enumerate both collision twin names
→ require exactly one selected twin live
→ SHA256 built == selected live DLL
→ only then launch
```

For collision research, **do not co-load** `Script_FrameCollisionTest.dll` and `Script_FrameCollisionBehaviorTest.dll`.

Normal Chat should provide the concrete selected product paths rather than asking the User to infer them. A guarded deployment should verify both twin names, not only a wildcard that happens to match one of them.

Conceptual check:

```powershell
$liveDir = 'E:\SteamLibrary\steamapps\common\Gothic 3\scripts'

Get-ChildItem -LiteralPath $liveDir |
    Where-Object {
        $_.Name -eq 'Script_FrameCollisionTest.dll' -or
        $_.Name -eq 'Script_FrameCollisionBehaviorTest.dll'
    } |
    Select-Object Name, Length, LastWriteTime
```

Expected:

- exactly one collision twin, and it is the product selected by the frozen test;
- built/live SHA256 match.

If both twins are present, the wrong twin is present, or the hash is false, stop before launching and resolve deployment first.

For another future product, apply the same invariant using its defined mutually exclusive/loader set rather than mechanically reusing the collision names.

---

## 6. POP-04 — Startup / Load Verification

### Trigger

Use after deploy/hash verification and before spending time on the full runtime matrix.

### Common invariant

```text
launch Gothic 3 only far enough to exercise script loading
→ reach the agreed minimal load point
→ exit normally unless the frozen test requires continuing directly
→ verify loading using the evidence surface appropriate to the selected product
→ only then run/spend time on the behavioral matrix
```

### Diagnostic collision twin

For `Script_FrameCollisionTest`, loading is normally verified with both normal game startup and the exact expected diagnostic banner in:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\Script_FrameCollisionTest.log
```

Normal Chat should provide the exact banner substring for the build being tested rather than expecting the User to remember it.

Typical diagnostic check:

```powershell
$log = 'E:\SteamLibrary\steamapps\common\Gothic 3\Script_FrameCollisionTest.log'
Select-String -Path $log -Pattern '<exact frozen startup banner substring>'
```

A missing expected diagnostic banner, wrong binary, load failure or crash is a stop condition.

### Diagnostics-free collision behavior twin

For `Script_FrameCollisionBehaviorTest`, **no diagnostic startup banner/log is required or expected by design**.

After sole-live-DLL + SHA verification, the load check is the agreed minimal behavior-only observation, normally:

```text
Gothic 3 reaches the main menu normally
→ normal exit
→ no crash/load error/obvious abnormal behavior
```

A later functional smoke provides the behavior evidence applicable to that diagnostics-free product.

The product/build identity convention is owned by `PROJECT_PIPELINE.md`.

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
5. one exact raw filename **when the selected product/test is expected to emit canonical runtime evidence**.

Do not invent a raw-log requirement for a diagnostics-free behavior-only smoke merely to make every validation step look identical.

Do not change the meaning of the test after the run merely to fit the observed result.

### Naming authority

The canonical gate/test-ID and raw/derived filename conventions live in `PROJECT_PIPELINE.md` §§3, 6–7.

POP-05 owns the act of freezing the test and filename when applicable; it does not define a separate naming scheme.

Before inventing a new gate/test identifier or filename pattern, retrieve the relevant pipeline section and preserve the established convention.

If a test crosses midnight or is delayed after the filename is frozen, keep the frozen filename unless there is a concrete reason to rename it; consistency with the recorded test contract matters more than cosmetic date perfection.

### User responsibility

Run the frozen test. When a canonical raw artifact is part of the test, copy the complete produced log to the exact frozen path.

Extra repetitions are acceptable and often useful. If the configuration/order materially differs from the frozen matrix, tell Normal Chat so interpretation can distinguish those sections.

After copying a raw artifact, a short confirmation such as:

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

Use this section only when the frozen test actually produced a canonical raw artifact.

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

$branch = '<active branch from SESSION_ENTRYPOINT.md>'
$log = '.\research\raw\<frozen-log-name>.log'

Get-Item -LiteralPath $log |
    Select-Object Name, Length, LastWriteTime

git status --short -- $log
git add -- $log
git commit -m '<descriptive evidence commit message>'
git push origin $branch
git rev-parse HEAD
```

Normal Chat should provide the resolved exact branch and exact frozen filename in the concrete command. The User should not have to substitute placeholders during an actual test transaction.

Normal Chat should normally ask only for the final SHA or a short success confirmation.

---

## 9. POP-07 — Large Runtime Log Analysis Without Losing Evidence

### Trigger

Use when a canonical runtime log is too large for efficient repository/connector retrieval or would create unnecessary Chat/tool context pressure.

### Invariant

The source log remains canonical evidence. Retrieval convenience must never cause it to be trimmed, rewritten or replaced by a summary.

```text
canonical raw/archive log
→ deterministic local post-processing when needed
→ derived retrieval package under research/derived/
→ read the smallest useful derived signals/timeline first
→ return to canonical source whenever exact verification is required
```

### Reusable tool

The current deterministic implementation lives under:

```text
tools/log_evidence/
```

Use its normal Windows wrapper and exact usage documented in:

```text
tools/log_evidence/README.md
```

The tool README owns wrapper syntax, execution-policy handling, examples and implementation-specific invocation details. Do not duplicate that manual here.

A derived package must remain reproducibly tied to its canonical source, including source identity/hash and tool/extraction identity sufficient to verify how it was produced. Gate-specific extra signal patterns may be supplied when necessary; do not rewrite the canonical log because the built-in vocabulary is incomplete.

Derived artifact naming/location conventions remain owned by `PROJECT_PIPELINE.md`. Derived material is a retrieval aid, not a replacement evidence authority.

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

both mutually exclusive collision twins live / wrong selected product live
→ stop before game launch

built/live SHA mismatch
→ stop before game launch

diagnostic product: expected startup banner missing
→ stop before runtime matrix

behavior-only product: load crash / main-menu failure / abnormal exit
→ stop before functional smoke

Git rebase conflict
→ stop automatic Git procedure and inspect conflict

unexpected invariant warning in a diagnostic
→ treat as evidence/design question, not something to filter out
```

Do not ask the User for full successful outputs or entire logs merely because a command was run. Expand output only when the current failure cannot be diagnosed from the compact result.

---

## 12. POP-10 — Formal Project Review / Audit Preflight

### Trigger

Use **before every formal project review or audit** whose conclusions may evaluate or change project rules, procedures, architecture, authority/document structure, knowledge organization, repository/product shape, or another cross-authority project surface.

A narrow source review of an already-frozen implementation also inherits this principle. It does not need to reload the whole charter/authority system when the governing hierarchy and target responsibility are already explicit and fresh in the current context, but it must still know which higher authority defines the behavior being reviewed.

### Hard gate

> **A review/audit has not started until the reviewer can explain the governing authority hierarchy and the intended responsibility of the material being reviewed.**

Do not begin by comparing files as if every document were a peer.

### Required preflight sequence

```text
identify the project and exact review/audit question
→ read/confirm `docs/README.md` §0 Project Charter first
→ state the relevant hierarchy from CAM → Gothic charter → specialist owner → procedure/task layer
→ identify every target document/system's stated Purpose / Scope / Status
→ use `KNOWLEDGE_REGISTRY.md` when ownership/update responsibility is not already obvious
→ classify what each target is: charter / specialist authority / convention / procedure / evidence / current-state / historical / implementation
→ state the review criteria that follow from those roles
→ ONLY THEN evaluate content, duplication, contradiction, quality or cleanup
```

For a large audit, the preflight statement should be explicit and compact. It should normally identify:

```text
governing hierarchy
review scope
intended use/owner of each major target
what higher-level intent must be preserved
what the review is not authorized to redefine
```

### Review interpretation rules

1. **Hierarchy comes before textual similarity.** Similar wording across a charter, specialist rule and procedure may be deliberate layered operationalization rather than duplication.
2. **Intended use comes before cleanup.** Do not merge/delete documents until the review understands why each exists and whether it owns a distinct responsibility.
3. **File size, age, detail and recency do not define authority.** Authority comes from the project charter and ownership structure.
4. **Lower authorities specialize higher ones; they do not silently rewrite them.** A procedure cannot redefine a project goal; a current-state file cannot redefine architecture; an implementation cannot redefine the frozen semantic authority merely because the code is newer.
5. **Specialist authorities may be parallel.** `DESIGN.md`, `COLLABORATION_RULES.md`, `PROJECT_PIPELINE.md`, evidence authorities and other owners govern different domains beneath the charter. Do not invent a false total ordering between them.
6. **Evidence and normative authority are distinct.** New evidence may justify changing architecture/rules, but the evidence record itself does not silently become the project rule.
7. **Historical/current separation remains mandatory.** Git history and historical EV wording can explain why an older decision existed, but they do not override maintained current authorities.
8. **Resolve at the lowest correct owner.** When a problem can be fixed consistently within an existing lower authority, change that owner rather than unnecessarily rewriting a higher layer.
9. **Escalate genuine higher-level conflict.** If a proposed review finding would change the project's why, long-term direction, scope or authority topology, expose it to the User and update the charter deliberately rather than hiding it in a lower edit.
10. **CAM is constitutional but externally evolved.** A Gothic review may identify a possible CAM gap, but it must not modify CAM. Preserve the project lesson and route it to a separate User-authorized CAM-focused responsibility.

### Contradiction / duplication test

Before labeling two statements contradictory or redundant, ask:

```text
Do they own the same responsibility?
Are they at the same authority layer?
Is one a principle and the other its operational procedure?
Is one factual evidence and the other an engineering consequence?
Is one current authority and the other historical explanation?
Would removing one make its intended responsibility harder to reconstruct?
```

Only after those questions are answered should the review decide whether text is truly duplicated or conflicting.

### Stop / escalation conditions

Stop the review's destructive or normative change path and surface the issue when:

- the reviewer cannot explain the relevant authority hierarchy;
- a target's intended purpose/owner is unclear or two current documents claim the same primary responsibility;
- the proposed cleanup may remove unique durable knowledge before a surviving owner is identified;
- a lower-level fix would materially change the project charter's purpose/direction/scope;
- the issue appears to require CAM evolution rather than Gothic operationalization;
- a factual premise needed for the review is disputed and the relevant evidence has not been reconstructed.

A review may continue gathering facts after such a stop condition, but it must not pretend the unresolved authority question is already settled.

### Output discipline

For a structural/rules/procedure audit, prefer:

```text
preflight hierarchy + intended-use statement
→ findings
→ proposed smallest-owner corrections
→ User discussion when higher-level intent is implicated
→ implementation only after the review boundary is clear
→ post-change contradiction/retrieval check
```

Do not create another review-procedure document. This POP section is the reusable project procedure.

---

## 13. Procedure Maintenance

The active procedure is the current best project-specific operationalization. Git history preserves old versions; the active document should not accumulate obsolete variants.

Use this maintenance trigger:

```text
use procedure normally
→ no routine audit
→ repeated friction/mistake OR one serious failure OR clearly better recurring method appears
→ whichever participant notices first raises it
→ diagnose actual cause
→ revise the smallest owning procedure/rule
→ continue using revised procedure
```

If the issue is actually a naming/numbering/version/state/product convention rather than a recurring sequence, update `PROJECT_PIPELINE.md` instead of silently embedding a new convention here.

If the issue is participant/tool allocation or CAM operationalization rather than an operational sequence, update `COLLABORATION_RULES.md` instead.

If the issue is project purpose, long-term direction, scope or authority topology, update the project charter in `README.md` rather than hiding that change in a procedure.

When a procedure becomes too long, ask whether stable detail can be moved into a reusable script/tool while this document keeps only the trigger, invariant, and sequence cue.

When a new recurring operation appears, first ask whether an existing POP section can absorb it. Create another procedure only when the responsibility is genuinely distinct and expected to recur.

---

## Quick Procedure Index

| Cue | Procedure |
|---|---|
| assistant/user both writing same branch | POP-01 Git branch handoff and synchronization |
| source reviewed, need selected DLL | POP-02 Build only |
| build succeeded, need exact live product | POP-03 Deploy and binary-identity verification |
| DLL copied, before full test | POP-04 Product-appropriate startup/load verification |
| ready for controlled runtime evidence | POP-05 Freeze runtime test and raw filename when applicable |
| runtime log copied locally | POP-06 Raw evidence integrity and publish |
| raw/archive log too large to retrieve efficiently | POP-07 Large runtime log analysis |
| large static Engine/Game/Script_Game material | POP-08 Static binary/reference retrieval |
| routine command/procedure fails | POP-09 Routine failure/stop behavior |
| formal project review/audit | POP-10 Authority-hierarchy + intended-use preflight |

## Core Procedure Rule

> **Preserve causal certainty and canonical evidence, select and verify the exact product required by the question, never co-load mutually exclusive research twins, hand the active Git branch between writers deliberately, understand the project hierarchy and each target's intended use before formal review/audit, use stable project conventions rather than reinventing them, keep routine outputs compact, and store reusable operational patterns externally so future Chats can reconstruct the workflow without repeatedly rediscovering it.**
