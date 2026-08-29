# Gothic 3 Project Collaboration Delta

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific collaboration authority  
**Version:** 1.6  
**Updated:** 2026-08-29

## Purpose

This file contains only the collaboration rules that are specific to the Gothic 3 Animation Behaviors project.

General collaboration behavior is governed by the active CAM framework in `tcholti/Collaborative-Agency-Model`, especially:

- `COLLABORATION_RULES.md` — general collaboration behavior;
- `COLLABORATION_PROFILE.md` — current User + Chat collaboration pattern;
- `PROJECT_COLLABORATION.md` — sustained-project mechanisms;
- `BETWEEN_CHATS.md` — context continuity.

This project also deliberately tracks the candidate reusable operational layer on CAM branch `current` where it reflects mechanisms already proven useful here or elsewhere:

- `REUSABLE_COLLABORATION_BASELINE.md` — candidate cross-project operating baseline;
- `KNOWLEDGE_SYSTEM.md` — reusable knowledge, retrieval, authority and maintenance model;
- `COLLABORATION_PROCEDURES.md` — recurring event-driven collaboration procedures.

The CAM `current` baseline does not replace this project delta or the Gothic-specific authorities below. It is the reusable layer against which project experience can be compared. Project-specific variation is expected; a mechanism should move upward only when evidence shows that it generalizes beyond the local conditions that produced it.

Do **not** reload those CAM documents for every Gothic 3 prompt. This file is the project delta. Retrieve the broader CAM authority or candidate baseline only when a collaboration/process question, cross-project comparison, or method-evolution question actually requires it.

Older Gothic 3 collaboration rules remain useful history but are superseded where they conflict with this document or the active CAM framework.

---

## 1. Branch and Authority Model

The current active development branch is:

`docs/collision-source-evidence`

It contains the newest collision research, prototype implementation, evidence, and continuation state.

`main` is the stable integration and reusable Gothic 3 knowledge baseline. It may receive stable documentation/research improvements before the current collision implementation is ready, but unfinished collision code should remain on the active branch until a deliberate stable integration point is reached.

For current work:

- current task/state → `docs/SESSION_ENTRYPOINT.md`;
- latest transient Chat/Work handoff → `docs/BETWEEN_CHATS.md` when one exists;
- document roles and retrieval routes → `docs/README.md`;
- knowledge-maintenance event model → `docs/KNOWLEDGE_MAINTENANCE.md`;
- knowledge authority/update triggers → `docs/KNOWLEDGE_REGISTRY.md`;
- exact implementation/source truth → the current branch source files and commits;
- exact technical evidence → the relevant evidence/reference document or raw artifact.

Do not assume `main` represents the newest implementation state while the active branch is ahead.

---

## 2. Keep the Active Retrieval Surface Small

Do not reread the whole repository, documentation set, research history, or evidence corpus between prompts.

Start from the smallest useful current state:

1. `docs/SESSION_ENTRYPOINT.md`;
2. `docs/BETWEEN_CHATS.md` only when a real transient handoff must be continued;
3. the exact source/task-specific authority required by the current responsibility.

Then broaden only when the task exposes a concrete need.

Within one continuing Chat or Work context, do not reread unchanged documents merely because another prompt arrived.

Large reference documents are durable external memory. Their existence does not make them mandatory context.

The knowledge-maintenance protocol and registry are process tools. They are not additional mandatory pre-reading for ordinary technical prompts; Normal Chat applies their trigger logic when a meaningful event completes.

### 2.1 Subsystem Orientation Pass

A small active retrieval surface must not become **context starvation**.

There are three useful retrieval depths:

```text
current-state retrieval
→ subsystem orientation when needed
→ question-specific retrieval
```

Normal Chat should automatically perform a **Subsystem Orientation Pass once** when it enters a substantial technical subsystem without a sufficiently fresh working model of that subsystem in the current Chat context.

Automatic triggers include:

- a new Normal Chat enters ongoing collision, Raise, playback-speed, animation-selection or another substantial subsystem;
- the collaboration deliberately switches to a different substantial subsystem inside the same Chat;
- the collaboration returns to a subsystem after substantial work elsewhere;
- the User points out that previously established subsystem context is missing or being treated as new.

Do **not** trigger the pass merely because:

- another prompt arrived;
- another B6/B7/etc. substep starts inside the same active subsystem;
- another runtime log is interpreted;
- Work returns a bounded implementation;
- a short tangent mentions another subsystem without actually switching work to it.

The orientation procedure is:

```text
recover current state / transient handoff
→ identify the active subsystem
→ use the Subsystem Orientation Route in docs/README.md
→ spot-read the small set of relevant indexes/canonical sections
→ synthesize a temporary compact mental model of the subsystem
→ continue with exact question-specific retrieval
```

The temporary model should be broad enough to retain major mechanisms, established findings, important negative results, known historical traps, relevant reference/third-party work and unresolved boundaries. It should not attempt to memorize every EV number, address, filename or raw-log detail; those remain external and are retrieved when needed.

Do not create a new persistent summary document merely to hold the temporary orientation model. If the orientation pass repeatedly cannot recover an important topic efficiently, strengthen an existing index/subject route rather than duplicating canonical facts into another summary.

The detailed retrieval-depth model and subject routes live in `docs/README.md`.

---

## 3. Evidence-First Gothic 3 Engineering

The normal engineering loop remains:

```text
question / hypothesis
    ↓
smallest useful source or runtime investigation
    ↓
controlled evidence
    ↓
interpretation
    ↓
smallest justified design/code change
    ↓
build / runtime test
    ↓
update durable state when the result matters
```

For engine-facing behavior:

- prefer native action, phase, UseType, source/API, hook, and runtime evidence over assumptions from filenames alone;
- use controlled player/NPC tests where actor scope matters;
- use logging for collision timing/reset and other subtle runtime behavior rather than visual inspection alone;
- preserve proven paths while testing one meaningful conceptual variable at a time when that improves causal evidence;
- let contradictory evidence challenge the current model.

Do not re-prove stable findings without a reason, but do not protect them from new evidence.

### Runtime test log handoff

When Normal Chat asks the User to run a controlled runtime test whose log is expected to become evidence, use this default transfer procedure:

```text
Normal Chat defines test conditions + exact raw-log filename
        ↓
User runs the test locally
        ↓
User places the resulting log in research/raw/ under that filename
        ↓
User confirms that the file is in place
        ↓
Normal Chat gives concise Git commands to verify, stage only the intended artifact, commit, and push
        ↓
Normal Chat reads the committed raw log from GitHub and performs interpretation/maintenance
```

Rules:

- include the intended `research/raw/...` filename in the same message that defines the test whenever practical;
- prefer descriptive filenames containing the date and enough gate/family/condition information to distinguish the artifact later;
- do not ask the User to paste a complete successful build output or full runtime log into Chat by default;
- for routine successful commands, a short confirmation or the relevant final line is sufficient;
- if a build/test fails, request only the smallest error/output excerpt needed to diagnose it, broadening to full output only when necessary;
- after the User confirms the raw artifact is in place, provide commands that first verify the intended path/status, then stage only the intended file(s), commit descriptively, and push the active branch;
- once pushed, retrieve and analyze the artifact from GitHub rather than duplicating it into the chat context;
- if GitHub transfer is temporarily unavailable, use the smallest relevant pasted excerpt as a fallback;
- do not commit every trivial exploratory run automatically: use this procedure for logs that support the active causal gate, evidence record, regression result, or another result worth preserving.

This procedure keeps chat context compact while making the repository the durable evidence surface.

---

## 4. Preserve Deep Gothic 3 Knowledge; Optimize Retrieval Instead

This repository is intended to become a useful Gothic 3 modding knowledge base, not merely a record of one feature.

Do not archive or delete valuable technical evidence, hook research, animation semantics, catalogs, source findings, or reusable engine knowledge merely because they are large or not needed by the current prompt.

Instead:

- index large documents by topic, heading, evidence range, symbol, action family, hook, subsystem, or search term;
- keep exact evidence and raw artifacts available for verification;
- prefer targeted section/evidence retrieval over full-document reading;
- separate current conclusions from chronological research history where practical;
- keep historical evidence discoverable when it explains why a current conclusion exists;
- reconstruct a compact subsystem model once when entering that subject, then retrieve exact details only as needed.

The objective is:

> **small active cognitive surface, deep recoverable Gothic 3 knowledge, and enough subsystem orientation to avoid rediscovering established work.**

---

## 5. Incremental Knowledge Maintenance Is Part of Completing the Step

The User should not need to ask after every design decision, Work session, build, or runtime test whether documentation, evidence, indexes, handoffs, raw artifacts, or archives were updated.

For meaningful engineering events, Normal Chat should automatically perform the small maintenance transaction defined in:

- `docs/KNOWLEDGE_MAINTENANCE.md`;
- `docs/KNOWLEDGE_REGISTRY.md`.

The rule is:

```text
meaningful event completes
→ determine what actually changed
→ update only the owning authorities whose trigger fired
→ update index/current-state routing only when needed
→ archive processed provenance when appropriate
→ continue
```

A normal result should usually require one evidence update plus zero to three local authority/index/current-state updates, not a repository-wide documentation review.

A code commit does not automatically require documentation changes. A repeated runtime confirmation does not automatically require architecture changes. Absence of documentation churn is correct when no authority changed.

Full documentation audits remain valuable but should be exceptional: schema/authority changes, contradiction resolution, major stabilization/promotion checkpoints, or occasional health reviews after substantial growth.

---

## 6. Current Chat / Work Allocation

Current evidence often favors:

```text
User + Normal Chat
research / evidence interpretation / disagreement / architecture / semantics / task freezing
        ↓
Work when useful
bounded implementation / targeted source or API inspection / source audit / commit-push
        ↓
Normal Chat + authoritative home PC
independent source review / build / runtime testing / evidence interpretation
```

Normal Chat also owns the project knowledge-maintenance transaction around those stages. Work remains an implementation responsibility and should not become a second documentation/architecture authority unless a task explicitly assigns a narrow documentation edit.

This is a current project allocation, not a permanent product hierarchy.

Use Work when its execution environment materially helps. Do not move a context-heavy design problem to Work merely because Work has more compute or repository automation.

Use `docs/WORK_IMPLEMENTATION_PROTOCOL.md` for a bounded coding task.

No permanent Medium/High reasoning policy is part of this project. Use sufficient reasoning for the actual responsibility and avoid spending resources on repeated reconstruction that the repository can prevent.

---

## 7. Bounded Implementation Must Not Invent Missing Architecture

For an implementation task whose semantics have already been decided:

- preserve the frozen question and protected behavior;
- inspect only source/API material necessary to implement it;
- do not silently create new ownership, lifecycle, classification, fallback, or architecture rules;
- return material semantic contradictions to the design responsibility;
- distinguish source completion from build/runtime proof;
- independently review meaningful Work diffs against the contract before treating them as implementation authority while current evidence still justifies that review depth.

The detailed compact execution contract is in `docs/WORK_IMPLEMENTATION_PROTOCOL.md`.

---

## 8. Continuity and Interruption

A Chat or Work context is not the sole project memory.

Before reconstructing or redoing interrupted work:

1. inspect `docs/SESSION_ENTRYPOINT.md`;
2. inspect the relevant durable commit/source/document;
3. inspect `docs/BETWEEN_CHATS.md` if it carries newer transient state;
4. if the active subsystem is not already sufficiently oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`;
5. continue only the missing responsibility.

Do not ask the User to repeat exact technical information that can be reliably retrieved from project authority.

When the product exposes a real context/usage warning and losing transient work would matter, preserve a minimal durable checkpoint. Do not invent hidden context percentages or usage state the product has not exposed.

### When the User says they are moving to a new Normal Chat

Treat the announced chat move as a small continuity-maintenance event, not as a request to write a large narrative handoff.

Before ending the current chat:

1. inspect the current `docs/SESSION_ENTRYPOINT.md` and the actual latest repository/task state;
2. check whether any already-completed design, Work review, build, runtime result, evidence interpretation, raw/archive transition, or gate change still needs its normal local maintenance transaction;
3. update `SESSION_ENTRYPOINT.md` only if the current subsystem, causal gate, immediate candidate, or next Normal Chat responsibility has changed;
4. inspect `docs/BETWEEN_CHATS.md` and decide whether a transient handoff is genuinely needed;
5. create or refresh `BETWEEN_CHATS.md` only when exact transient context would otherwise be lost — for example an active/fresh Work contract or result, a frozen implementation boundary, an unresolved local-only test/build state, or another short-lived responsibility not yet represented by durable authority;
6. if `SESSION_ENTRYPOINT.md` already contains everything the next Normal Chat needs and no transient state exists, do **not** create another handoff file merely because the chat is changing;
7. never create a parallel "new chat handoff" authority; use `SESSION_ENTRYPOINT.md` as the durable front door and `BETWEEN_CHATS.md` as the replaceable transient bridge;
8. give the User one short copyable starter instruction for the new Normal Chat, normally telling it to read `docs/SESSION_ENTRYPOINT.md` on the active branch and continue from the current Normal Chat responsibility;
9. the new Normal Chat should then perform the one-time Subsystem Orientation Pass for the active subsystem before deep question-specific work unless that orientation is already present in its context;
10. do not require the User to summarize project history, relay technical state between chats, or decide which deeper documents the new chat should preload.

The intended transition is:

```text
User announces chat move
        ↓
Normal Chat checks current maintenance + continuity state
        ↓
SESSION_ENTRYPOINT current?
        ├─ no  → update it
        └─ yes → leave it alone
        ↓
real transient context to preserve?
        ├─ yes → replace/update BETWEEN_CHATS
        └─ no  → no extra handoff document
        ↓
provide one short new-chat starter instruction
        ↓
new Normal Chat reads SESSION_ENTRYPOINT first
        ↓
performs subsystem orientation once
        ↓
retrieves BETWEEN_CHATS / deeper exact authority only as needed
```

This procedure should itself be revisited only when repeated chat transitions show that it is losing context, forcing redundant retrieval, or creating unnecessary document churn.

---

## 9. Evolve the Project Method From Evidence

If collaboration becomes slow, lossy, over-documented, under-documented, or unreliable, diagnose the cause before adding another rule.

Established procedures are **working defaults, not frozen law**. Use them normally without reviewing every procedure on every task or chat. Procedure review should be event-driven:

- repeated friction, repeated mistakes, or repeated unnecessary work;
- one serious failure or high-cost problem;
- a newly discovered method that is clearly simpler, safer, more reliable, or materially less wasteful.

Whoever notices such a trigger first — User or Chat — should raise the possible improvement. Diagnose the actual cause, change only the lowest owning procedure/rule that needs changing, and then use the revised procedure in subsequent work. Do not preserve obsolete active versions merely for history; Git already preserves procedure history.

The intended procedure-evolution pattern is:

```text
use established procedure normally
→ do not audit it merely because it exists
→ friction / failure / clearly better method appears
→ whoever notices first proposes improvement
→ diagnose the actual mechanism
→ revise the smallest owning procedure or rule
→ use the revision and observe whether it resolves the problem
```

Prefer changing the lowest justified layer:

- task wording;
- project retrieval/indexing;
- knowledge authority/update triggers;
- Work implementation protocol;
- project operating procedure;
- this Gothic 3 project delta;
- CAM `current` reusable operational baseline when a lesson genuinely generalizes beyond Gothic 3 but remains a project-derived candidate mechanism;
- stable CAM project/general framework only when broader evidence justifies changing the higher layer.

The intended learning loop is:

```text
real project success / friction / failure
→ diagnose the actual mechanism
→ improve the lowest owning project layer
→ observe subsequent use
→ compare the lesson with CAM current
→ generalize upward only when transfer is supported
→ compare later project evidence back against the reusable template/baseline
```

A CAM template is a starting structure, not a demand for identical project form. When another project legitimately varies from the template, first ask whether that is a useful project-specific adaptation or evidence that the reusable baseline itself should improve.

Old collaboration documents and experiments may be archived once their durable lessons are represented in current authority. Their historical rationale remains available through archive/history.

---

## Core Project Collaboration Rule

> **Start from current state, orient once to the relevant subsystem when context is fresh or has changed, retrieve only what the responsibility needs, preserve deep technical evidence for targeted reuse, automatically maintain only the records whose authority actually changed, and let Gothic 3 runtime/source evidence—not documentation volume—drive both the engineering and any collaboration-method lessons proposed for wider reuse.**
