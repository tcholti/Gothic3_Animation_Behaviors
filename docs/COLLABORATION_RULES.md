# Gothic 3 Project Collaboration Delta

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific collaboration authority  
**Version:** 1.1  
**Updated:** 2026-08-27

## Purpose

This file contains only the collaboration rules that are specific to the Gothic 3 Animation Behaviors project.

General collaboration behavior is governed by the active CAM framework in `tcholti/Collaborative-Agency-Model`, especially:

- `COLLABORATION_RULES.md` — general collaboration behavior;
- `COLLABORATION_PROFILE.md` — current User + Chat collaboration pattern;
- `PROJECT_COLLABORATION.md` — sustained-project mechanisms;
- `BETWEEN_CHATS.md` — context continuity.

Do **not** reload those CAM documents for every Gothic 3 prompt. This file is the project delta. Retrieve the broader CAM authority only when a collaboration/process question actually requires it.

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

---

## 4. Preserve Deep Gothic 3 Knowledge; Optimize Retrieval Instead

This repository is intended to become a useful Gothic 3 modding knowledge base, not merely a record of one feature.

Do not archive or delete valuable technical evidence, hook research, animation semantics, catalogs, source findings, or reusable engine knowledge merely because they are large or not needed by the current prompt.

Instead:

- index large documents by topic, heading, evidence range, symbol, action family, hook, subsystem, or search term;
- keep exact evidence and raw artifacts available for verification;
- prefer targeted section/evidence retrieval over full-document reading;
- separate current conclusions from chronological research history where practical;
- keep historical evidence discoverable when it explains why a current conclusion exists.

The objective is:

> **small active cognitive surface, deep recoverable Gothic 3 knowledge.**

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
4. continue only the missing responsibility.

Do not ask the User to repeat exact technical information that can be reliably retrieved from project authority.

When the product exposes a real context/usage warning and losing transient work would matter, preserve a minimal durable checkpoint. Do not invent hidden context percentages or usage state the product has not exposed.

---

## 9. Evolve the Project Method From Evidence

If collaboration becomes slow, lossy, over-documented, under-documented, or unreliable, diagnose the cause before adding another rule.

Prefer changing the lowest justified layer:

- task wording;
- project retrieval/indexing;
- knowledge authority/update triggers;
- Work implementation protocol;
- this Gothic 3 project delta;
- broader CAM framework only when the lesson genuinely generalizes.

Old collaboration documents and experiments may be archived once their durable lessons are represented in current authority. Their historical rationale remains available through archive/history.

---

## Core Project Collaboration Rule

> **Start from current state, retrieve only what the responsibility needs, preserve deep technical evidence for targeted reuse, automatically maintain only the records whose authority actually changed, and let Gothic 3 runtime/source evidence—not documentation volume—drive the engineering.**
