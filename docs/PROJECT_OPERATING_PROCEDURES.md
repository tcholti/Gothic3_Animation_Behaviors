# Gothic 3 Project Operating Procedures

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific procedure library  
**Version:** 1.13  
**Updated:** 2026-09-08

## Purpose

This document stores recurring operational patterns that are useful during normal Gothic 3 development but do not belong in technical architecture, evidence, current-state, bounded Work authority, stable project convention authority, participant-allocation rules, or the project charter.

It exists so a new Chat does not have to rediscover how we normally:

- synchronize and hand off the active Git branch, using GitHub Desktop for routine User-side Git where practical;
- build the selected current product/target;
- deploy and verify a DLL before testing;
- verify that the selected product actually loaded;
- freeze runtime tests/logs;
- preserve, publish and close raw evidence transactions;
- reduce oversized logs for efficient analysis without altering the evidence;
- work with large static binary/reference material;
- request bounded Chat-safe PowerShell output for the next decision;
- preflight a formal project review/audit so it respects the project hierarchy and each target's intended use;
- preserve continuity across planned Chat transitions, launch bounded Work tasks from durable repository handoffs, and recover safely after an abrupt/max-context failure.

`docs/README.md` is the Gothic project charter and highest project-specific authority beneath CAM for project purpose, long-term direction, scope and authority topology.

`PROJECT_PIPELINE.md` owns stable naming, numbering, version/test ID, branch/state, product-identity, artifact-flow and validation-gate conventions. This file owns recurring sequences and their failure/stop behavior, not competing convention schemes.

`LOCAL_WORKSTATION_PATHS.md` owns mutable workstation-specific repository/build/runtime locations. `COLLABORATION_RULES.md` owns participant/tool allocation. `WORK_IMPLEMENTATION_PROTOCOL.md` owns bounded Work implementation execution.

These are reconstructable procedure patterns, not mandatory reading before every prompt and not frozen law. Procedure evolution is owned by §14; `KNOWLEDGE_REGISTRY.md` determines whether a discovered improvement belongs here or somewhere else.

---

## 1. When to Read This Document

Read or spot-read when entering:

- source review -> build -> deploy -> runtime test;
- runtime evidence capture/publish/closure;
- Git handoff between connected GitHub writes and the User's local checkout;
- large-log or large-reference retrieval;
- planned Chat transition where transient work must be made durable;
- recovery after an abrupt/max-context/unusable previous Chat;
- a formal review/audit of project rules, procedures, architecture, documentation/knowledge structure, repository/product shape, or another cross-authority surface.

Do not reread it after every prompt. A procedure name should normally be enough to reconstruct the sequence; open the exact section when the detailed sequence or failure branch matters.

This document does not replace the charter, pipeline, collaboration rules, Work protocol, knowledge-maintenance protocol, current-state pointers, or workstation-path authority.

---

## 2. End-to-End Validation Cue

For a normal engine-facing change:

```text
design/evidence question frozen
-> bounded implementation when needed
-> implementation commit/publish
-> independent Normal Chat source review
-> User/local branch synchronization
-> select exact build product/target
-> build only
-> deploy exact built DLL
-> verify selected product is the only intended live twin + SHA match
-> startup/load verification
-> freeze exact runtime matrix + raw filename when diagnostic evidence is expected
-> User runs test
-> raw log copied unchanged into research/raw
-> raw artifact commit/push
-> Normal Chat analyzes committed evidence
-> derived package/extract only if retrieval requires it
-> close evidence transaction: explicit disposition + canonical evidence promotion when warranted
-> archive processed source artifact when no longer an active comparison input
-> only then advance to the next causal question or planned handoff
-> normal knowledge-maintenance transaction for affected technical/current-state owners
```

Do not collapse stages merely to save messages when the separation protects causal certainty. Build != deployment; deployment != load; load != behavioral proof.

---

## 3. POP-01 — Git Branch Handoff and Synchronization

### Trigger

Use whenever Assistant-side GitHub writes and the User's local checkout both need to write the same active branch.

### Core rule — one branch writer window at a time

```text
Assistant finishes required remote writes
-> Assistant identifies resulting remote state
-> User synchronizes local checkout if needed
-> Assistant hands branch to User
-> Assistant does not write that branch during the User window
-> User performs local artifact/build-related commit and pushes
-> User reports successful push/SHA or compact success confirmation
-> branch returns to Assistant-side writes when needed
```

Once Normal Chat gives the User a local commit/push sequence, do not create another commit on that branch until the User reports the push completed or the handoff is explicitly cancelled.

### Preferred routine User interface — GitHub Desktop

As of 2026-09-08, GitHub Desktop is the preferred interface for ordinary User-side repository synchronization, branch switching, change review, local commits, pushes and history inspection.

The User has only just begun using GitHub Desktop and must be treated as a **beginner**. Do not infer familiarity because one operation succeeded once. When asking the User to perform a GitHub Desktop action, normally provide the concrete steps again in one manageable sequence. Repetition is expected until the User explicitly indicates that the steps no longer need explaining. Avoid unexplained Git terminology when a screen/button description is clearer.

Before a routine Desktop operation, verify visually:

```text
Current repository = Gothic3_Animation_Behaviors
Current branch     = exact active branch from SESSION_ENTRYPOINT.md
Changes            = understood before pull/switch/commit
```

Prefer branch switching when `Changes` shows `0 changed files`. If important uncommitted changes exist, do not assume they can safely follow a branch switch or pull; identify them first.

Routine synchronization after Assistant-side remote writes:

```text
open Gothic3_Animation_Behaviors in GitHub Desktop
-> verify Current branch
-> click Fetch origin
-> if remote commits are available and no important local changes block synchronization,
   click Pull origin
-> require the top action to return to Fetch origin
-> verify no unexpected local Changes
```

Interpretation for the User:

```text
Fetch origin = check whether GitHub has newer remote state; does not itself change local files
Pull origin  = bring newer remote commits into the local checkout
```

Do not use `Preview Pull Request` merely to synchronize the established working branch.

Routine local publication:

```text
verify Current branch
-> inspect Changes and select only intended files
-> enter the agreed descriptive Summary
-> Commit to <active branch>
-> Push origin
-> report compact success or commit SHA when the current procedure requires it
```

Important distinction:

```text
Commit = create local Git checkpoint
Push   = publish local commit(s) to GitHub
```

A local Commit is not considered remotely published until Push succeeds. The History tab may be used to inspect recent commits and short SHAs.

Do not commit to `main` merely because it is the default/stable branch. Branch selection remains deliberate and follows `SESSION_ENTRYPOINT.md` / `PROJECT_PIPELINE.md`.

### Assistant remote writes and local synchronization

If the Assistant changed the remote since the User last synchronized, the User should normally Fetch/Pull through GitHub Desktop before beginning a new local write window.

If the User already has important local commits or uncommitted work when the remote has also advanced, do not improvise a merge/rebase sequence in the UI. Stop, report the visible state, and choose the smallest safe recovery deliberately.

### PowerShell / command-line fallback

GitHub Desktop is a convenience interface, not a ban on exact command-line work. Use PowerShell/Git when it is materially clearer or safer for the task, especially for:

```text
exact SHA/status diagnostics
build/configure commands
deployment and DLL/hash verification
bounded log filtering/counts
scripted or bulk repository operations
conflict/rebase diagnosis
operations GitHub Desktop cannot express precisely enough
```

Do not paste long Git command blocks into Chat when the same routine Fetch/Pull/Commit/Push action can be performed safely in GitHub Desktop.

If a push is rejected, GitHub Desktop reports a conflict, or the visible local/remote state is unclear, stop and inspect; do not guess or auto-pick a side.

Command-line fallback for a known clean synchronization remains available when needed:

```powershell
$repoRoot = '<repository from LOCAL_WORKSTATION_PATHS.md>'
Set-Location $repoRoot
$branch = '<active branch from SESSION_ENTRYPOINT.md>'
git pull --rebase origin $branch
```

If a deliberate command-line rebase conflicts, stop and inspect; do not auto-pick a side.

---

## 4. POP-02 — Build Only

### Trigger

Use after required source review when a local runtime binary is needed.

### Pattern

```text
correct branch/source state
-> choose exact target required by frozen question
-> build only that target into repository-local build tree
-> leave artifact in build tree
-> User reports success or smallest useful error excerpt
-> STOP build stage
```

Do not use the live Gothic 3 `scripts` directory as build output/staging/backup. Current collision research products are mutually exclusive:

```text
Script_FrameCollisionTest
= diagnostic twin

Script_FrameCollisionBehaviorTest
= diagnostics-free behavior twin
```

Build only the selected target. A successful build does not deploy it. Request only compact success or smallest useful failure output.

---

## 5. POP-03 — Deploy and Binary-Identity Verification

### Trigger

Use after a successful build and before launching Gothic 3 for that build.

### Invariant

```text
resolve exact selected built DLL
-> ensure every mutually exclusive non-selected collision twin is physically absent from live scripts
-> manually copy only selected DLL
-> enumerate Script_FrameCollision* files in live scripts
-> require exactly one selected collision twin and no renamed/disabled sibling copies
-> SHA256 built == selected live DLL
-> only then launch
```

Do not co-load the diagnostic and behavior-only twins. The live scripts directory is deployment surface, not storage. Renaming a script DLL in place is not a safe disable mechanism; EV-173 showed a renamed backup can still participate in runtime loading.

If any sibling/wrong product is live or the hash differs, stop before launch.

---

## 6. POP-04 — Startup / Load Verification

### Trigger

Use after deploy/hash verification and before spending time on the full runtime matrix.

### Common invariant

```text
launch only far enough to exercise script loading
-> reach agreed minimal load point
-> exit normally unless continuing directly is part of frozen test
-> verify loading using evidence surface appropriate to selected product
-> only then run behavioral matrix
```

For `Script_FrameCollisionTest`, verify expected diagnostic startup banner. Missing banner/wrong binary/load failure/crash is a stop condition.

For `Script_FrameCollisionBehaviorTest`, no diagnostic banner/log is expected by design. Sole-live-DLL + SHA followed by normal main-menu load/exit is the minimal load check; later functional smoke provides behavior evidence.

---

## 7. POP-05 — Freeze a Runtime Test and Raw Filename

### Trigger

Use when a controlled runtime run is intended to answer an active causal/validation question and the log is worth preserving.

### Normal Chat responsibility before the run

Freeze whenever practical:

1. exact test purpose;
2. minimum fixture/configuration cases;
3. important ordering/reset requirements;
4. outcomes/invariants to watch;
5. one exact raw filename when the selected product/test is expected to emit canonical runtime evidence.

Do not invent raw-log requirements for diagnostics-free smokes merely to make all validation look identical. Do not change the meaning of the test after the run to fit the result.

Naming authority remains `PROJECT_PIPELINE.md`.

The User runs the frozen test and copies the complete produced log to the exact frozen path. Extra repetitions are fine; material deviations from the frozen matrix should be reported so interpretation can distinguish them.

After copying, a short confirmation such as `file is in raw` is enough. Do not paste the full log into Chat by default.

---

## 8. POP-06 — Raw Runtime Evidence Integrity, Publish, and Closure

### Raw evidence rule

A file in `research/raw/` is canonical raw evidence. Preserve it byte/content-faithfully. Do not clean whitespace, reformat, remove noise, or use source-style whitespace checks as evidence validators.

### Publish pattern

Routine User-side publishing should normally use GitHub Desktop under POP-01:

```text
User confirms exact raw file exists
-> branch handoff/sync settled
-> GitHub Desktop: verify repository + active branch
-> inspect Changes and select only intended artifact(s)
-> enter descriptive Summary
-> Commit to active branch
-> Push origin
-> report compact success or SHA when requested
-> Assistant reads committed artifact from GitHub
```

If GitHub Desktop does not express the exact operation safely enough, use a bounded PowerShell/Git fallback instead.

Normal Chat should provide the resolved exact path/branch/filename and the concrete Desktop steps or commands appropriate to the operation. Because the User is new to GitHub Desktop, repeat the relevant UI sequence when asking for it rather than assuming prior demonstrations were memorized. Ask only for the smallest useful confirmation/output; the Assistant can usually resolve the pushed remote SHA directly.

### Same-investigation evidence-closure invariant

> **No completed runtime investigation may be knowingly handed off to a later Chat, or followed by a new causal question, while its reusable conclusion exists only in conversation, a derived artifact, an index, or an unprocessed file in `research/raw/`.**

Once committed evidence is interpreted, Normal Chat automatically continues:

```text
read committed evidence from GitHub
-> correlate logger facts + User observations + frozen test contract
-> decide narrow factual result and epistemic status
-> assign every produced artifact an explicit disposition
-> promote reusable factual conclusion to canonical Evidence Ledger at correct global EV number
-> update EVIDENCE_INDEX only when routing materially changes
-> perform required technical/current-state maintenance at smallest owners
-> archive fully processed artifact when no active comparison needs raw intake
-> record path migration when historical raw paths would otherwise become ambiguous
-> verify represented repository state matches actual tree
-> ONLY THEN advance to next causal question or planned handoff
```

A derived checkpoint aids retrieval; it is not canonical evidence. `EVIDENCE_INDEX.md` routes evidence; it must not become the only owner of a factual result.

### Required artifact disposition

Every published runtime artifact must end as one of:

```text
NEW CANONICAL EVIDENCE
SUPERSEDED / NEGATIVE PROVENANCE
ACTIVE COMPARISON — KEEP RAW
UNPROCESSED — KEEP RAW
ARCHIVED PROVENANCE
```

If a log supports a reusable conclusion and remains an active comparison, promote the conclusion immediately but keep the source in raw until comparison closure.

### Archive rule

Archive when:

```text
frozen question interpreted
+ every reusable conclusion has canonical evidence home
  OR artifact explicitly classified as superseded/negative provenance
+ no active comparison needs raw intake location
```

Preserve basename and content identity whenever possible. Archive is durable provenance, not deletion/demotion. Historical EV rows may keep old paths; `EVIDENCE_PATH_MIGRATIONS.md` resolves deliberate later moves.

### Completeness / automation check

Interpretation remains evidence-driven and Normal-Chat reviewed. Automation may check bookkeeping completeness but must not decide what evidence means.

At the end of each evidence transaction, and again before a planned Chat transition or stable-subsystem checkpoint, check:

```text
all newly published raw artifacts have explicit disposition
completed reusable findings are in canonical Evidence Ledger
EVIDENCE_INDEX does not claim a factual result that exists nowhere canonically
processed artifacts are not left in raw without active-comparison reason
archive/current routes point to paths that actually exist
no current-state document relies on an unpromoted chat-only result
```

A deterministic repository tool may later flag raw inventory, path existence, EV/index inconsistency, or stale processed-raw state. It may not auto-author conclusions or silently rewrite authorities.

### Planned vs failed Chat transition

The invariant above is strict for a **planned** transition: do not knowingly move Chats while completed evidence remains unclosed.

An abrupt/max-context/unusable Chat failure is different because the normal closure sequence may have become impossible. That failure does **not** invalidate the project or block a new Chat from opening. Instead:

> **The uncompleted evidence/maintenance closure obligation transfers to the recovering Chat as its first responsibility under POP-11. New causal/implementation work remains blocked until that recovery closure is complete.**

This exception exists only for unavoidable failed transitions; it is not permission to defer ordinary maintenance deliberately.

### Closure stop conditions

Do not advance when:

- artifact cannot yet be interpreted reliably;
- a required User visual observation is missing;
- conclusion would outrun logged/source evidence;
- a factual result exists only in derived/index material and has no canonical EV;
- a processed artifact is about to be archived while reusable conclusion lacks canonical owner;
- docs claim an archive move the repository tree does not contain.

Keep unresolved artifacts in raw with explicit disposition rather than making a later Chat infer their state.

---

## 9. POP-07 — Large Runtime Log Analysis Without Losing Evidence

### Trigger / invariant

Use when a canonical runtime log is too large for efficient retrieval.

```text
canonical raw/archive log
-> deterministic local post-processing when needed
-> derived retrieval package under research/derived/
-> read smallest useful derived signals/timeline first
-> return to canonical source for exact verification
```

Current deterministic tool: `tools/log_evidence/` with usage in its README.

A derived package must remain reproducibly tied to source identity/hash and extraction identity. It is a retrieval aid, not replacement evidence.

Whole-run interpretation order:

```text
verify source identity/hash
-> inspect whole-run event counts
-> inspect chronological timeline
-> enumerate high-signal/invariant/failure matches
-> read source-context windows
-> retrieve additional exact source ranges when needed
-> correlate final symptom with complete run
```

Counts are navigation leads, not conclusions. Tail-only extracts cannot prove earlier cleanliness. User visual observations remain valid evidence inputs. Distinguish diagnostic/shadow outcomes from actual mutations. If derived material is insufficient, retrieve exact source ranges rather than rerunning Gothic solely for Chat convenience.

---

## 10. POP-08 — Large Static Binary / Reference Retrieval

For large extracted/disassembled `Game`, `Engine`, `Script_Game`, or similar static references:

```text
complete local/extracted provenance
-> split/index into manageable stable chunks in Gothic3_Binary_Reference
-> retrieve by module + RVA/symbol/import/search term
-> open only relevant region
```

Static split is for random access, not evidence summarization. Exact findings that become project evidence still belong in Gothic evidence/source authorities.

---

## 11. POP-09 — Routine Failure / Stop Behavior

Routine procedures fail narrowly and visibly.

```text
build error -> inspect smallest useful error excerpt
wrong/multiple live twins -> stop before launch
SHA mismatch -> stop before launch
missing diagnostic banner -> stop before runtime matrix
behavior-only load crash -> stop before functional smoke
GitHub Desktop unexpected branch/changes/conflict/rejected push -> stop and inspect; do not guess
Git command-line rebase conflict -> stop automatic Git procedure
unexpected invariant warning -> treat as evidence/design question
```

### Chat-safe PowerShell output

When the User will paste output back into Chat, commands should print only bounded explicit information needed for the next decision. Prefer labeled scalar values, exact filters, hashes/counts, and deliberately small excerpts. Avoid width-dependent formatted tables for required values and avoid unbounded logs/listings.

---

## 12. POP-10 — Formal Project Review / Audit Preflight

### Trigger

Use **before every formal project review or audit** whose conclusions may evaluate or change project rules, procedures, architecture, authority/document structure, knowledge organization, repository/product shape, or another cross-authority surface.

A narrow source review of an already-frozen implementation inherits the principle but need not reload the whole hierarchy when the governing owner is already explicit and fresh.

### Hard gate

> **A review/audit has not started until the reviewer can explain the governing authority hierarchy and the intended responsibility of the material being reviewed.**

Do not compare files as if every document were a peer.

### Required preflight sequence

```text
identify project and exact review/audit question
-> read/confirm docs/README.md §0 Project Charter first
-> state relevant hierarchy from CAM -> Gothic charter -> specialist owner -> procedure/task layer
-> identify each target's stated Purpose / Scope / Status
-> use KNOWLEDGE_REGISTRY when ownership/update responsibility is not obvious
-> classify target: charter / specialist authority / convention / procedure / evidence / current-state / historical / implementation
-> state review criteria that follow from those roles
-> ONLY THEN evaluate content, duplication, contradiction, quality or cleanup
```

For a large audit, state compactly:

```text
governing hierarchy
review scope
intended use/owner of each major target
higher-level intent that must be preserved
what the review is not authorized to redefine
```

### Review interpretation rules

1. Hierarchy comes before textual similarity.
2. Intended use comes before cleanup.
3. File size, age, detail and recency do not define authority.
4. Lower authorities specialize higher ones; they do not silently rewrite them.
5. Specialist authorities may be parallel.
6. Evidence and normative authority are distinct.
7. Historical/current separation remains mandatory.
8. Resolve at the lowest correct owner.
9. Escalate genuine charter-level conflict to the User.
10. CAM is constitutional but externally evolved: Gothic review may identify a CAM gap but must not modify CAM.

Before calling two statements contradictory/redundant, ask whether they own the same responsibility, sit at the same layer, are principle vs procedure, evidence vs consequence, or current vs historical.

### Stop / escalation conditions

Stop destructive/normative changes when:

- reviewer cannot explain relevant hierarchy;
- target purpose/owner is unclear or two current docs claim same primary responsibility;
- cleanup may remove unique durable knowledge before a surviving owner is identified;
- lower-level fix would materially change project purpose/direction/scope;
- issue appears to require CAM evolution;
- factual premise needed for review is disputed and evidence has not been reconstructed.

### Output discipline

```text
preflight hierarchy + intended-use statement
-> findings
-> proposed smallest-owner corrections
-> User discussion when higher-level intent is implicated
-> implementation only after review boundary is clear
-> post-change contradiction/retrieval check
```

Do not create another review-procedure document.

---

## 13. POP-11 — Normal Chat Continuity and Interrupted-Context Recovery

### Trigger

Use when:

- a planned Normal Chat transition is approaching;
- the product exposes a real context/usage warning and losing current transient work would matter;
- the previous Chat stopped abruptly, reached maximum context, became unusable, or otherwise ended before normal maintenance/handoff completed.

This is a recurring continuity/recovery sequence. It does not make `BETWEEN_CHATS.md` a second current-state authority and does not turn transcripts into canonical evidence.

### Planned transition

Before deliberately moving to a new Normal Chat:

```text
finish current meaningful engineering step as far as actually completed
-> close every completed runtime evidence transaction under POP-06; leave only explicitly active/unprocessed raw inputs
-> run normal KNOWLEDGE_MAINTENANCE transaction for completed results
-> update SESSION_ENTRYPOINT if immediate responsibility changed
-> update BETWEEN_CHATS only when exact short-lived continuation detail is genuinely needed
-> check once for completed work/results not yet durable
-> verify a fresh Chat following SESSION_ENTRYPOINT would begin at correct responsibility
-> give User a short starter instruction
```

Do not perform broad documentation cleanup merely because a Chat is ending.

### Normal Chat -> Work launcher

Frozen substantive task state belongs in durable repository authorities, especially `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`. A normal Work launcher should identify repository, branch, base HEAD, required read order, bounded responsibility, publication authorization when needed, and instruction to execute the frozen durable contract.

Do not duplicate a long design/evidence contract into the launcher when repository handoff already carries it.

### Context/usage warning safeguard

When a real context/usage warning appears and losing transient reasoning would create material reconstruction work:

> **Create the smallest useful durable checkpoint before continuing deep work. Do not wait for context failure.**

Checkpoint may be a current-state/handoff update, already-produced raw artifact, canonical evidence/interpretation maintenance, or another existing authority update required by knowledge maintenance. Do not manufacture a commit when nothing durable changed.

### Abrupt / max-context recovery — Recovery Lock

If the previous Chat ended before the planned sequence could run, the new Chat must assume `SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` **may be stale** until checked against newer durable facts.

Immediately enter **Recovery Lock**:

```text
DO NOT start new implementation
DO NOT freeze/run a new runtime experiment
DO NOT launch a new Work task
DO NOT blindly execute an old NEXT pointer
```

The first responsibility is to restore a trustworthy shared project state.

### Authority-orientation gate before recovery edits

Before the recovering Chat changes documentation/evidence/current-state, it must understand the ownership structure relevant to the recovery gap.

Read/confirm only the smallest necessary authority chain:

```text
SESSION_ENTRYPOINT first as a clue, not unquestioned truth
-> docs/README.md §0 Project Charter
-> KNOWLEDGE_REGISTRY.md ownership/update routing
-> KNOWLEDGE_MAINTENANCE.md maintenance rules
-> relevant specialist authority for the subsystem that was active
-> COLLABORATION_RULES.md only when participant/authorization/CAM operationalization is materially part of the recovery question
```

Then state a compact **recovery preflight**:

```text
governing authority hierarchy
last trusted durable checkpoint
what durability gap must be reconstructed
which owners may legitimately need maintenance
what higher-level intent must be preserved
what recovery is NOT authorized to redefine
```

> **A recovering Chat may inspect recent facts before this statement is complete, but it must not start documentation cleanup/review edits until it can explain the relevant authority hierarchy and ownership.**

This is an orientation gate, not automatically a formal project audit.

### Durable-state reconstruction

After orientation:

```text
confirm active branch and newest remote commits around last trusted durable point
-> inspect only recent tail needed to determine what happened after maintained state
-> inspect newly committed/raw active artifacts relevant to that tail
-> use User-supplied previous-chat transcript/TXT when available for reasoning/observations not yet durable
-> classify which meaningful engineering events actually completed
```

Classify recovered material explicitly where useful:

```text
completed + already durable
completed but maintenance/evidence closure missed
published evidence but unclosed
partial/incomplete work
conversation-only interpretation/hypothesis
still-active responsibility
```

A supplied transcript is **recovery material, not authority**. Separate transcript claims into source facts, runtime facts, User observations, interpretations, hypotheses and proposed tests before promotion.

### Recovery closure

Once the recent durable state is understood:

```text
perform missed POP-06 evidence closure before any new causal question
-> perform missed KNOWLEDGE_MAINTENANCE at smallest owning authorities
-> update canonical evidence only for claims supported by preserved source/runtime/User evidence
-> correct stale SESSION_ENTRYPOINT / BETWEEN_CHATS pointers
-> verify recovered current responsibility against current branch/source state
```

Do **not** reconstruct the entire repository or reread every authority because one Chat failed. Default recovery is bounded to the durability gap.

### Contradiction gate — bounded recovery vs formal audit

Interrupted-context recovery is **not** permission for an improvised full documentation review.

If bounded recovery finds only local missed closure/stale pointers, fix those owners and continue.

If recovery instead exposes any of the following:

```text
multiple current authority layers materially contradict each other
ownership of the needed correction is unclear
several unrelated documents appear stale in ways not explained by the recent gap
processed evidence has accumulated broadly without canonical promotion
resolving the gap would require judging document structure/duplication across authorities
project purpose/direction/authority topology appears implicated
```

then:

```text
STOP ordinary recovery edits
-> invoke POP-10 formal review/audit preflight
-> explain hierarchy / owners / scope / non-authorized changes
-> obtain User agreement when the review boundary is broad or higher-level intent may be affected
-> only then perform the formal review
```

This gate prevents a recovery Chat from misunderstanding layered authority and "cleaning up" the wrong documents.

### Recovery stop conditions

Surface contradiction instead of choosing a story when:

- newest commits/raw artifacts contradict remembered/transcript account;
- unclear whether a test/result actually completed;
- interpretation would promote hypothesis beyond preserved evidence;
- branch state shows another writer advanced the branch after recovered point;
- recovering Chat cannot explain the relevant authority hierarchy or owner for a proposed edit.

Ask the User only for information that cannot be recovered from repository state or supplied recovery material.

### Final continuity check

Before declaring recovery complete:

> **If a fresh Normal Chat followed `SESSION_ENTRYPOINT.md` literally now, would it begin with the correct immediate responsibility, see only intentionally active raw inputs, and be able to retrieve the evidence and owning authorities needed for that responsibility?**

If no, recovery is not complete.

Only after this check may Recovery Lock end and normal technical work resume.

---

## 14. Procedure Maintenance

The active procedure is the current best project-specific operationalization. Git history preserves old versions; the active document should not accumulate obsolete variants.

Maintenance trigger:

```text
use procedure normally
-> no routine audit
-> repeated friction/mistake OR one serious failure OR clearly better recurring method appears
-> whichever participant notices first raises it
-> diagnose actual cause
-> revise smallest owning procedure/rule
-> continue using revised procedure
```

If the issue is naming/numbering/version/state/product convention, update `PROJECT_PIPELINE.md`. If participant/tool allocation or CAM operationalization, update `COLLABORATION_RULES.md`. If project purpose/long-term direction/scope/authority topology, update the charter rather than hiding it here.

The GitHub Desktop beginner guidance in POP-01 is intentionally operational and may be simplified later only when repeated use shows the User no longer needs step-by-step reminders. Do not remove it merely because setup succeeded once.

When a procedure becomes too long, ask whether stable detail can move into a reusable script/tool while this document keeps the trigger, invariant and sequence cue.

---

## Procedure Routing Summary

| Situation | Procedure |
|---|---|
| branch writer handoff / sync / routine GitHub Desktop workflow | POP-01 |
| build only | POP-02 |
| deploy + binary identity | POP-03 |
| startup/load verification | POP-04 |
| freeze runtime test/raw filename | POP-05 |
| publish/interpret/close/archive runtime evidence | POP-06 |
| large runtime log | POP-07 |
| large static binary/reference material | POP-08 |
| routine failure / Chat-safe output | POP-09 |
| formal project review/audit | POP-10 |
| planned Chat transition / context warning / previous Chat failed | POP-11 |

## Core Procedure Rule

> **Preserve causal certainty and canonical evidence; close completed runtime evidence before planned handoff; when a Chat fails unavoidably, recover authority/ownership and close the durability gap before new work; select and verify the exact runtime product; hand the active branch deliberately; use GitHub Desktop for routine User-side Git with repeated beginner guidance while preserving exact command-line fallbacks; keep Chat-bound output bounded; launch Work from durable handoffs; understand hierarchy and intended use before formal reviews; and keep recurring operational knowledge in the smallest correct owner so future Chats can resume without rediscovery or accidental redesign.**
