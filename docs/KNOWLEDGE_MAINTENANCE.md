# Gothic 3 Knowledge Maintenance Protocol

**Status:** Active project knowledge-maintenance protocol  
**Version:** 1.0  
**Updated:** 2026-08-27

## Purpose

Keep the repository current through **small local maintenance transactions** instead of frequent repository-wide documentation reviews.

The User should not need to ask after every design decision, Work session, build, or runtime test whether documentation, evidence, indexes, raw logs, or archives were updated.

For Normal Chat, checking and performing the necessary local knowledge maintenance is part of completing the engineering step.

This protocol does not require every event to change documentation. It requires checking the event against the registry and changing only the authorities whose update trigger actually fired.

> **Normal maintenance is incremental. Full documentation audits are exceptional.**

---

## 1. Governing Model

The repository stores knowledge in four layers.

### Layer A — evidence / provenance

Examples:

- evidence-ledger entries;
- raw and archived runtime logs;
- exact animation-name inventories;
- source/binary observations;
- build-specific RVAs and call stacks.

This layer is primarily append-oriented. Old confirmed evidence is not rewritten merely because the project has moved on; qualifications or contradictions are recorded explicitly.

### Layer B — canonical topic authorities

Each important technical responsibility has one primary home.

Examples:

- overall system architecture → `DESIGN.md`;
- collision lifecycle architecture → `COLLISION_LIFECYCLE_PLAN.md`;
- native cleanup RVAs/stacks → `COLLISION_CLEANUP_CALLSITE_MAP.md`;
- generalized animation semantics → `ANIMATION_RULES.md`;
- concrete animation assets/fixtures → `ANIMATION_CATALOG.md`.

Other documents should route to these authorities rather than maintain independent copies of the same fact.

### Layer C — indexes / catalog records

Examples:

- `EVIDENCE_INDEX.md`;
- `ANIMATION_INDEX.md`;
- `KNOWLEDGE_REGISTRY.md`.

Indexes route a question to the correct authority/evidence. They do not become another narrative copy of the underlying knowledge.

### Layer D — current-state pointers

Examples:

- `SESSION_ENTRYPOINT.md`;
- `BETWEEN_CHATS.md`.

These are intentionally small and replaceable. They point to current responsibilities; they do not preserve long history.

---

## 2. Default Engineering + Knowledge Loop

The normal project loop is:

```text
User vision / desired behavior / problem
        ↓
User + Normal Chat
search only relevant existing knowledge
reason / challenge / design / decide architecture
        ↓
LOCAL MAINTENANCE TRANSACTION
update only authorities whose meaning changed
        ↓
freeze bounded implementation task
update transient current/handoff state if needed
produce Work prompt
        ↓
Work
implement from the frozen contract
source-audit / commit / push / concise handoff
        ↓
User reports Work completion
        ↓
Normal Chat
independent diff-against-contract review
        ↓
LOCAL MAINTENANCE TRANSACTION
record only implementation-state changes that matter
        ↓
home-PC build / install
        ↓
Normal Chat interprets build/load result
        ↓
LOCAL MAINTENANCE TRANSACTION when the gate changes
        ↓
User performs controlled runtime test
        ↓
Normal Chat interprets log + observation
        ↓
EVIDENCE TRANSACTION
raw intake → evidence conclusion → index/authority trigger check → archive processed artifact
        ↓
next design question
```

The User does not need to separately request the maintenance transactions.

---

## 3. Maintenance Transaction Rule

After a meaningful project event, Normal Chat asks internally:

1. **What actually changed?**
2. Is it a new fact/evidence result, a design decision, an implementation-state change, a current-task change, a reusable source/hook finding, or merely another confirmation of existing knowledge?
3. Which authority in `KNOWLEDGE_REGISTRY.md` owns that change?
4. Did that authority's update trigger fire?
5. Does an index need a new route, or does the existing route already cover it?
6. Does the current-state pointer need to advance?
7. Has a raw artifact now been fully processed and become archive material?

Then update only those local targets.

A normal result should usually require **one evidence update plus zero to three local authority/index/current-state updates**.

If a routine test seems to require a broad documentation review, stop and check whether knowledge is duplicated or authority boundaries are unclear.

---

## 4. Event Transactions

### Event A — design / architecture decision

Examples:

- lifecycle authority changes;
- marker semantics change;
- a subsystem responsibility moves;
- a previously open design choice is deliberately frozen.

Default transaction:

```text
update owning architecture/design authority
→ update current-state pointer if it changes active work
→ update index only if retrieval routing changed
→ no Evidence Ledger entry unless the decision also asserts a tested/source fact
```

Do not update unrelated evidence/history/reference documents merely because a design discussion occurred.

### Event B — frozen Work handoff

Default transaction:

```text
confirm architecture already authoritative
→ make current bounded task discoverable in SESSION_ENTRYPOINT or BETWEEN_CHATS as appropriate
→ produce exact Work prompt
→ no broad documentation review
```

Work should not be asked to reconstruct project history.

### Event C — Work implementation completed

Normal Chat first performs the independent source review required by `WORK_IMPLEMENTATION_PROTOCOL.md`.

Default transaction after review:

```text
implementation matches contract
→ record exact implementation/commit state only where current continuation needs it
→ preserve semantic authorities unchanged unless implementation exposed a real contradiction

implementation exposed contradiction
→ return to design
→ update authority only after the contradiction is interpreted/resolved
```

A source commit is not engine evidence.

### Event D — build / load result

Default transaction:

```text
build/load passes and this was expected
→ usually only advance current test gate

build/load establishes a reusable toolchain/API fact
→ evidence/reference authority may also update

build/load fails
→ diagnose locally; do not rewrite architecture unless failure reveals an architectural/API contradiction
```

### Event E — controlled runtime result

This is the main evidence transaction.

Default transaction:

```text
preserve raw log/source artifact
→ interpret result
→ add/update exact EV entry
→ update EVIDENCE_INDEX only if a route/range materially changes
→ update owning design/reference authority only if its semantic model changed
→ update SESSION_ENTRYPOINT if the active gate/direction changed
→ move processed artifact raw → archive when no longer active/unprocessed
```

Repeated confirmation of an already-established fact may require only provenance/archive handling and no architecture edit.

### Event F — stable subsystem / promotion checkpoint

Use a somewhat broader but still scoped review:

- stable public/reusable knowledge;
- current subsystem architecture;
- evidence qualifications;
- implementation readiness;
- `main` promotion set;
- archive/current-state cleanup.

This is an appropriate time for consolidation. It is still not automatically a whole-repository audit.

---

## 5. Evidence Intake and Archival Lifecycle

Use:

```text
new/unprocessed artifact
→ research/raw/
→ interpret against current question
→ canonical EV/result recorded
→ durable technical value routed to authority/index if needed
→ artifact moved to research/archive/
```

An artifact may remain in `research/raw/` while:

- its interpretation is incomplete;
- it is still being compared with another control;
- a question in the current causal gate remains unresolved.

Once its relevant result is represented canonically and it is no longer active input, move it to archive without changing the artifact contents.

`research/archive/` is deep provenance, not dead material.

---

## 6. Current-State Maintenance

### `SESSION_ENTRYPOINT.md`

Update when:

- active subsystem changes;
- current causal gate changes;
- the immediate architecture candidate materially changes;
- a test gate is completed and the next responsibility becomes different.

Do **not** add the full history of how the current state was reached.

### `BETWEEN_CHATS.md`

Use only when there is a real transient handoff that another context needs.

Replace/overwrite rather than accumulate chronology.

When the receiving context has incorporated the state into durable authorities, `BETWEEN_CHATS.md` can become minimal again.

---

## 7. Index Maintenance

An index is updated when **retrieval changes**, not every time underlying evidence grows.

Examples:

Update `EVIDENCE_INDEX.md` when:

- a new evidence range opens;
- an existing topic now routes to a materially different EV range;
- a major new search term/symbol/subsystem needs a route.

Do not update it merely because EV-174 is another confirmation already covered by an existing row.

Update `ANIMATION_INDEX.md` when:

- a new animation knowledge category appears;
- an existing question should route to a different section/data source;
- a new family/search route becomes materially useful.

---

## 8. Full Reviews / Audits — Exceptional Triggers

A broad review is appropriate when:

- authority boundaries themselves changed;
- a major subsystem is being declared stable or promoted to `main`;
- contradictions appear across several authorities;
- many local updates accumulated without clear ownership;
- a long period of development suggests index/registry drift;
- the repository is being reorganized or its knowledge schema changes;
- a health check is deliberately scheduled after substantial growth.

A full review is **not** the normal response to:

- one new test;
- one new Work commit;
- one compile failure;
- one new animation fixture;
- another confirmation of an already-canonical fact.

---

## 9. Future Mechanical Automation

The current protocol is assistant-driven and repository-driven; it requires no separate request from the User.

Later, if the pattern proves stable, parts can be mechanically validated without changing semantic authority. Useful candidates include:

- broken cross-reference detection;
- duplicate/competing `Status: current` ownership warnings;
- EV-range/index consistency checks;
- `research/raw/` age/processed-status reminders;
- branch knowledge-promotion manifests;
- stale `BETWEEN_CHATS.md` warnings;
- registry paths/heading existence checks.

A validator should detect maintenance problems, not decide engineering meaning.

Do not build automation until repeated manual use shows which checks are genuinely valuable.

---

## 10. User Responsibility

The User remains responsible for vision, desired behavior, priorities, observations and authoritative local runtime testing.

The User should **not** need to manage repository housekeeping after each normal engineering step.

Normal Chat owns the maintenance trigger check and should report important durable updates as part of the result.

If no document needs changing, it can simply continue; absence of documentation churn is healthy when no authority changed.

---

## Core Rule

> **Every meaningful event updates the smallest owning records automatically; no routine event earns a whole-repository review. Preserve knowledge once, route to it by index, and let full audits become rare health/stabilization tools.**
