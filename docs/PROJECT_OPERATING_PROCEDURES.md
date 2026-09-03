# Gothic 3 Project Operating Procedures

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific procedure library  
**Version:** 1.9  
**Updated:** 2026-09-03

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
- preflight a formal project review/audit so it respects the project hierarchy and each target's intended use;
- preserve continuity across planned Chat transitions and recover safely after an abrupt/max-context failure.

`docs/README.md` is the Gothic project charter and highest project-specific authority beneath CAM for project purpose, long-term direction, scope and authority topology.

`PROJECT_PIPELINE.md` owns the stable naming, numbering, version/test ID, branch/state, product-identity, artifact-flow and validation-gate conventions used by these procedures. This file owns the **recurring sequences and their failure/stop behavior**, not independent alternative convention schemes.

`LOCAL_WORKSTATION_PATHS.md` owns the User's current mutable Windows repository/build/runtime locations. Procedures may refer to those path roles, but they do not maintain a second canonical copy of workstation-specific path data.

Participant/tool allocation is owned by `COLLABORATION_RULES.md`. Bounded Work implementation execution is owned by `WORK_IMPLEMENTATION_PROTOCOL.md`.

These are reconstructable procedure patterns, not mandatory reading before every prompt and not frozen law. Procedure maintenance/evolution is owned by §14 below; `KNOWLEDGE_REGISTRY.md` determines whether a discovered improvement belongs here or in another authority.

---

## 1. When to Read This Document

Read or spot-read this document when entering an active local-operation sequence such as:

- source review → build → deploy → runtime test;
- runtime evidence capture/publish;
- Git handoff between connected GitHub writes and the User's local checkout;
- large-log or large-reference retrieval;
- planned Chat transition where transient work must be made durable;
- recovery after an abrupt/max-context/unusable previous Chat;
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
- `BETWEEN_CHATS.md` — transient exact handoff when needed;
- `LOCAL_WORKSTATION_PATHS.md` — current workstation-specific repository/build/runtime locations.

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

The exact active branch is current project state owned by `SESSION_ENTRYPOINT.md` / `PROJECT_PIPELINE.md`; this procedure must not maintain a competing branch identity. The current repository path is resolved from `LOCAL_WORKSTATION_PATHS.md` when concrete commands are produced.

Typical synchronization shape:

```powershell
$repoRoot = '<G3 Animation Behaviors repository from LOCAL_WORKSTATION_PATHS.md>'
Set-Location $repoRoot

$branch = '<active branch from SESSION_ENTRYPOINT.md>'
git pull --rebase origin $branch
```

Normal Chat should normally provide the resolved exact repository path and branch in the concrete command rather than making the User look them up manually.

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
→ build only that target into the repository-local build tree
→ leave the built artifact in the build tree
→ User reports success or smallest useful error excerpt
→ STOP build stage
```

The build stage must not use the live Gothic 3 `scripts` directory as a build output, staging area, backup location or disabled-product store. Build products remain in the repository-local `build\...` tree until POP-03 explicitly deploys one selected product for a runtime test.

Current collision research targets:

```text
Script_FrameCollisionTest
= diagnostic twin

Script_FrameCollisionBehaviorTest
= diagnostics-free behavior twin
```

Example diagnostic build:

```powershell
$repoRoot = '<G3 Animation Behaviors repository from LOCAL_WORKSTATION_PATHS.md>'
Set-Location $repoRoot

cmake --build build --config Release --target Script_FrameCollisionTest
```

Example behavior-only build:

```powershell
cmake --build build --config Release --target Script_FrameCollisionBehaviorTest
```

Do not build both merely because both exist; build the product selected by the current test responsibility.

A successful build does not automatically deploy the DLL. The User manually copies the exact selected built product during POP-03 when a runtime test requires deployment.

For a normal success, the User only needs to report that it succeeded. Do not ask for the complete successful build output.

If the build fails, request or use only the smallest relevant error excerpt first. Broaden only when needed.

---

## 5. POP-03 — Deploy and Binary-Identity Verification

### Trigger

Use after a successful build and before launching Gothic 3 for that build.

### Current collision twin locations

Resolve the current repository root and live Gothic 3 scripts directory from `LOCAL_WORKSTATION_PATHS.md`.

Both collision research targets are emitted from the same repository-relative prototype build directory:

```text
<repoRoot>\build\prototypes\Script_FrameCollisionTest\Release\
```

Current product files:

```text
Script_FrameCollisionTest.dll
= diagnostic twin

Script_FrameCollisionBehaviorTest.dll
= diagnostics-free behavior twin
```

Live scripts directory role:

```text
<runtime mod-script DLL directory from LOCAL_WORKSTATION_PATHS.md>
```

### Pattern

```text
resolve the exact selected built DLL in the repository-local build tree
→ ensure every mutually exclusive non-selected collision twin is physically absent from the live scripts directory
→ manually copy only the selected DLL to its exact live name
→ enumerate every Script_FrameCollision* file in the live scripts directory
→ require exactly one selected collision twin live and no renamed/disabled sibling copies
→ SHA256 built == selected live DLL
→ only then launch
```

For collision research, **do not co-load** `Script_FrameCollisionTest.dll` and `Script_FrameCollisionBehaviorTest.dll`.

The live Gothic 3 `scripts` directory is a deployment surface, not storage for alternative builds. A product that is not intended to load must be moved out of the live `scripts` directory or deleted from it. **Do not attempt to disable a script DLL by renaming it in place** (for example `Script_FrameCollisionBehaviorTest.dll.disabled`). Runtime evidence on 2026-09-03 showed Gothic mapping such a renamed file as a loaded module, so suffixing or extending the filename is not a safe disable mechanism.

Keep alternate/currently inactive builds in their normal repository-local build output or another location outside the live Gothic 3 `scripts` directory. Deploy them manually only when they become the selected runtime product.

Normal Chat should provide the concrete selected product paths rather than asking the User to infer them. A guarded deployment must enumerate the whole relevant product-name family so renamed siblings such as `.dll.disabled` cannot evade the check.

Conceptual check:

```powershell
$liveDir = '<runtime mod-script DLL directory from LOCAL_WORKSTATION_PATHS.md>'

Get-ChildItem -LiteralPath $liveDir |
    Where-Object {
        $_.Name -like 'Script_FrameCollision*'
    } |
    Select-Object Name, Length, LastWriteTime
```

Expected:

- exactly one `Script_FrameCollision*` runtime product;
- it is the exact product selected by the frozen test;
- no renamed/disabled sibling copy remains in the live directory;
- built/live SHA256 match.

If any additional collision twin/sibling is present, the wrong selected product is present, or the hash is false, stop before launching and resolve deployment first.

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

For `Script_FrameCollisionTest`, loading is normally verified with both normal game startup and the exact expected diagnostic banner in the runtime-root `Script_FrameCollisionTest.log`. Resolve the runtime root from `LOCAL_WORKSTATION_PATHS.md`.

Normal Chat should provide the exact banner substring for the build being tested rather than expecting the User to remember it.

Typical diagnostic check:

```powershell
$gameRoot = '<Gothic 3 runtime/game root from LOCAL_WORKSTATION_PATHS.md>'
$log = Join-Path $gameRoot 'Script_FrameCollisionTest.log'
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

When the same matrix contains comparable no-target and target-dependent cases, run all no-target cases first and then the target-dependent cases unless the causal question requires another order. Freeze any required exception explicitly.

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
$repoRoot = '<G3 Animation Behaviors repository from LOCAL_WORKSTATION_PATHS.md>'
Set-Location $repoRoot

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

Normal Chat should provide the resolved exact repository path, active branch and exact frozen filename in the concrete command. The User should not have to substitute placeholders during an actual test transaction.

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

### Whole-run interpretation safeguards

Large-log reduction is a retrieval method, not permission to reason from a convenient excerpt as though it represented the whole run.

Normal analysis order is:

```text
verify manifest/source identity + hash
→ inspect whole-run event counts to learn what occurred
→ inspect chronological event timeline across the full run
→ enumerate high-signal/invariant/failure matches
→ read the source-context windows for those matches
→ retrieve additional exact source ranges when the timeline exposes a relevant event outside the automatic windows
→ only then correlate the final tail/crash/symptom with the complete run
```

Preserve these interpretation rules:

- event/signal counts are navigation leads, not conclusions by themselves;
- a signal match must be read in context before being classified as a defect;
- a tail-only extract can help correlate a final symptom but cannot establish that earlier parts of the run were clean;
- repeated earlier occurrences may be more causally useful than the final visible failure;
- user visual observations remain valid evidence inputs and should be correlated with logging rather than discarded merely because a logger does not encode the visual consequence directly;
- distinguish diagnostic/shadow outcomes from actual physical mutations;
- if the derived package is insufficient, request/regenerate exact ranges from the canonical source rather than rerunning Gothic solely because Chat cannot directly retrieve the large raw file.

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

## 13. POP-11 — Normal Chat Continuity and Interrupted-Context Recovery

### Trigger

Use when:

- a planned Normal Chat transition is approaching;
- the product exposes a real context/usage warning and losing current transient work would matter;
- the previous Chat stopped abruptly, reached maximum context, became unusable, or otherwise ended before normal maintenance/handoff completed.

This is a recurring recovery sequence. It does not make `BETWEEN_CHATS.md` a second current-state authority and it does not turn Chat transcripts into canonical evidence.

### Planned transition

Before deliberately moving to a new Normal Chat:

```text
finish the current meaningful engineering step as far as it has actually completed
→ run the normal KNOWLEDGE_MAINTENANCE transaction for completed results
→ update SESSION_ENTRYPOINT if the immediate responsibility changed
→ update BETWEEN_CHATS only when exact short-lived continuation detail is genuinely needed
→ check once for completed work/results that have not yet been recorded durably
→ verify a fresh Chat following SESSION_ENTRYPOINT would begin at the correct responsibility
→ give the User a short starter instruction
```

Do not perform broad documentation cleanup merely because a Chat is ending.

### Context/usage warning safeguard

When the product exposes a real warning that the current context is approaching a limit, and losing the transient reasoning/result state would create material reconstruction work:

> **Create the smallest useful durable checkpoint before continuing deep work. Do not wait for the context to fail.**

Depending on what has actually completed, the checkpoint may be only:

- a current-state/handoff update;
- a committed raw artifact already produced;
- a canonical evidence/interpretation maintenance transaction;
- another existing authority update required by `KNOWLEDGE_MAINTENANCE.md`.

Do not manufacture a checkpoint commit when nothing durable has changed. The safeguard exists to preserve real completed/transient work, not to create ceremony.

### Abrupt / max-context recovery

If the previous Chat ended before the planned sequence could run, the new Chat must assume that `SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` **may be stale** until checked against newer durable facts.

Recovery sequence:

```text
read SESSION_ENTRYPOINT first as the normal front door, but do not blindly execute its NEXT step yet
→ confirm active branch and newest remote commits around the last known durable point
→ inspect only the recent tail needed to determine what happened after the maintained state
→ inspect newly committed/raw active artifacts relevant to that tail
→ use a User-supplied previous-chat transcript/TXT when available to recover reasoning/observations that were not yet made durable
→ classify which meaningful engineering events actually completed
→ perform any missed KNOWLEDGE_MAINTENANCE transaction at the smallest owning authorities
→ update canonical evidence only for claims the preserved source/runtime/user evidence supports
→ correct stale SESSION_ENTRYPOINT / BETWEEN_CHATS pointers
→ verify the recovered current responsibility against current source/branch state
→ only then resume normal technical work
```

A supplied transcript is **recovery material**, not automatically canonical project authority. Its claims must be separated into source facts, runtime facts, User observations, interpretations, hypotheses and proposed next tests before promotion into the normal owners.

Do not reconstruct the entire repository or reread every authority merely because one Chat failed. Start from the maintained front door and examine only the recent durability gap.

### Recovery stop conditions

Surface the contradiction instead of silently choosing a story when:

- newest commits/raw artifacts contradict the remembered/transcript account;
- it is unclear whether a test/result actually completed;
- an interpretation would promote a hypothesis beyond what the preserved evidence supports;
- branch state indicates another writer advanced the branch after the recovered point.

The User should only be asked for information that cannot be recovered from repository state or supplied recovery material.

### Final continuity check

Before declaring recovery complete, ask:

> **If a fresh Normal Chat followed `SESSION_ENTRYPOINT.md` literally now, would it begin with the correct immediate responsibility and be able to retrieve the evidence needed for it?**

If no, the recovery transaction is not complete.

---

## 14. Procedure Maintenance

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
| planned Chat transition / context warning / previous Chat failed | POP-11 Continuity and interrupted-context recovery |

## Core Procedure Rule

> **Preserve causal certainty and canonical evidence, select and verify the exact product required by the question, never co-load mutually exclusive research twins, hand the active Git branch between writers deliberately, preserve Normal Chat continuity without making the User reconstruct failed context, understand the project hierarchy and each target's intended use before formal review/audit, use stable project conventions and the canonical workstation-path reference rather than reinventing them, keep routine outputs compact, and store reusable operational patterns externally so future Chats can reconstruct the workflow without repeatedly rediscovering it.**
