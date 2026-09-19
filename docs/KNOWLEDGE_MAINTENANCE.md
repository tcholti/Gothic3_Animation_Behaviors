# Gothic 3 Knowledge Maintenance Protocol

**Status:** Active project knowledge-maintenance authority  
**Version:** 2.0  
**Updated:** 2026-09-19

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Purpose

Keep the repository useful as long-term external memory **without forcing ordinary work to reread the history of how knowledge was discovered**.

Normal Chat owns this maintenance automatically. The User should not need to ask whether a completed design decision, Work task, runtime test, probe, audit, evidence batch, or handoff also needs documentation cleanup.

> **Current reference tells us what we know. Architecture tells us how our system uses it. ADRs preserve why important choices were made. Evidence proves it. Temporary work records how we are finding out. Closed temporary work and closed ledger volumes are archived.**

This protocol is the canonical lifecycle authority. Other rule/procedure documents route here instead of restating independent variants.

---

## 1. Governing authority

```text
CAM constitutional collaboration layer
        ↓
docs/README.md project charter
        ↓
specialist current authorities / references
        ↓
this maintenance lifecycle + project procedures
        ↓
current-state / temporary work
```

Maintenance may update lower owners when their trigger fires. It must not silently change project purpose, long-term direction, scope, authority topology, or CAM-level principles.

A broad documentation/authority review uses POP-10 first.

---

## 2. Five documentation roles

### A. Current reference — what is established

Compact factual projections for ordinary retrieval.

Examples:

- `COLLISION_REFERENCE.md`;
- `ANIMATION_RULES.md`;
- `SOURCE_HOOK_GUIDE.md`;
- `COLLISION_CLEANUP_CALLSITE_MAP.md`.

Reference statements should be short, current, qualified where necessary, and point to supporting EVs rather than reproduce full evidence reasoning.

### B. Current architecture — how the project uses those facts

Owns current responsibilities, invariants, module boundaries and intended behavior.

Examples:

- `DESIGN.md`;
- `COLLISION_LIFECYCLE.md`;
- `COLLISION_DIAGNOSTICS.md`;
- `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`;
- `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

Architecture is not experiment chronology.

### C. Decision records — why a significant choice was made

`docs/decisions/` contains short ADRs for non-obvious project/architecture choices whose rationale may matter later.

Create an ADR only when a future maintainer could reasonably ask “why did we choose this instead of the plausible alternative?”

Do not create ADRs for routine test results, individual probe steps, implementation minutiae, or facts already captured by reference/evidence.

### D. Evidence / provenance — prove it

Includes:

- EV entries;
- raw/archived runtime logs;
- deterministic derived packages;
- exact source/binary observations;
- hashes/build provenance.

Evidence is append-oriented proof history. It is **not** the normal interface for settled knowledge.

### E. Temporary work — what we are currently testing/building

Active probes, bounded implementation contracts, audit tasks and short-lived research designs live under:

```text
docs/work/active/
```

They exist to control an unresolved question. They are not permanent architecture.

When closed they move to:

```text
docs/archive/investigations/
```

only after reusable conclusions are promoted.

---

## 3. Ordinary retrieval order

For a question already researched:

```text
current state (only if needed)
-> current reference
-> owning architecture/reference detail
-> EVIDENCE_INDEX
-> exact EV
-> archived raw/derived/probe only for verification or contradiction
```

Do **not** scan evidence ledgers, archived probes, raw logs or completed audits merely to answer “how does this work now?”

If current reference and evidence disagree, evidence wins the factual dispute and the current reference must be corrected.

---

## 4. Maintenance transaction

After every meaningful project event, Normal Chat asks:

1. What actually changed?
2. Is it a factual discovery, architecture decision, implementation-state change, current-state change, validation result, or only another confirmation?
3. Which current authority/reference owns the reusable result?
4. Does an ADR-worthy rationale exist?
5. Does exact proof need a new EV?
6. Does an active temporary document now close?
7. Does a current-state pointer need to move?
8. Is a future responsibility now dependent on this knowledge?
9. Can that future responsibility retrieve the current owner without opening historical material?
10. Can the knowledge-state validator pass after this transaction?

Update only the owners whose triggers fired.

A routine result should normally produce:

```text
0–1 evidence entry
0–2 current reference/architecture edits
0–1 index route
0–1 current-state edit
temporary document archive when its question closes
```

A result that appears to require broad edits across many unrelated authorities is a signal to stop and inspect ownership before continuing.

---

## 5. Temporary-document lifecycle — mandatory closure

### Creation

A probe, implementation contract, audit task or other bounded research document goes in `docs/work/active/` and declares:

```text
**Status:** ACTIVE
```

Do not create new temporary task/probe documents in the root `docs/` directory.

### While active

The document may contain detailed hypotheses, controls, implementation boundaries and reasoning necessary to run the investigation safely.

Do not promote an unproven hypothesis into current reference merely because it appears in an active task document.

### Closure

A temporary document is not closed until this transaction completes:

```text
result established
-> exact evidence recorded when applicable
-> reusable factual conclusion promoted to current reference
-> architecture consequence promoted to owning architecture
-> significant non-obvious rationale -> ADR when warranted
-> future-use/index route checked
-> current-state pointer updated if needed
-> temporary document moved to docs/archive/investigations/
-> knowledge-state validation passes
```

Hard closure question:

> **If this temporary document disappeared from ordinary retrieval tomorrow, has every reusable conclusion already been promoted to its durable owner?**

If no, closure is incomplete.

Archive preserves history; it is not a deletion step.

---

## 6. Evidence ledger lifecycle

### Current ledger

Exactly **one** evidence ledger may remain in the active `docs/` root:

```text
EVIDENCE_LEDGER_<first-open-EV>_ONWARD.md
```

All closed volumes live under:

```text
docs/archive/evidence/
```

`EVIDENCE_INDEX.md` routes EV ranges to the correct volume.

### New entry format

New EV entries are provenance-first and concise:

```text
EV ID + short title
Observed
Scope / limits
Provenance
Disposition
```

Do not repeat a long causal narrative once the reusable result has a current reference owner.

### Rotation

Rotate the active ledger at a natural closed checkpoint and **before it becomes a routine context burden**. The mechanical validator warns above 64 KiB; do not treat that warning as a target to reach.

Rotation transaction:

```text
close current last EV
-> verify EVIDENCE_INDEX routes the completed range
-> move closed ledger to docs/archive/evidence/
-> open next EVIDENCE_LEDGER_<next-EV>_ONWARD.md
-> update SESSION_ENTRYPOINT latest/current-ledger pointer
-> run knowledge-state validation
```

Never renumber EVs. Ledger movement is storage-only.

---

## 7. Runtime evidence lifecycle

Runtime artifacts remain:

```text
research/raw/      unprocessed/open intake only
research/derived/  deterministic retrieval aids
research/archive/  processed canonical runtime provenance
```

For every uploaded batch under POP-06:

```text
preserve source unchanged
-> interpret every artifact
-> record canonical EV conclusion
-> promote reusable current fact
-> archive processed source when no active comparison remains
-> verify research/raw/ contains only genuinely open inputs
```

A derived package helps retrieval but never replaces canonical source provenance.

---

## 8. Current-state discipline

`SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` are small replaceable pointers, not history stores.

### SESSION_ENTRYPOINT

Own only:

- current branch/state;
- current gate/responsibility;
- latest relevant evidence checkpoint;
- exact immediate next route;
- minimal safety/recovery cues.

Established subsystem history belongs in current reference/architecture/evidence, not here.

### BETWEEN_CHATS

Own only short-lived continuation details that another context genuinely needs and that are not already obvious from current authorities.

Replace rather than accumulate.

If either current-state file starts carrying old campaigns, audit chronology or detailed proof, move that material to its proper owner and compress the pointer.

---

## 9. Decision-record lifecycle

Create ADRs under `docs/decisions/`.

Accepted ADRs are not rewritten to make history look cleaner. If a later choice changes the decision:

```text
new ADR
-> old ADR status = Superseded by ADR-xxxx
-> current architecture/reference updated to the new rule
```

ADRs explain rationale; they do not replace current architecture or evidence.

---

## 10. Future-relevance and workaround checks

When a finding materially affects a foreseeable future responsibility, make that fact retrievable from the current owner with the smallest route necessary.

When new knowledge makes an old workaround potentially unnecessary:

1. preserve why the workaround existed;
2. identify the invariants/regressions it protects;
3. reevaluate it deliberately;
4. remove/simplify only when those protections are demonstrably retained.

Do not let new knowledge silently strand historical workarounds.

---

## 11. Archive policy

`docs/archive/` is cold provenance.

Ordinary orientation/search must not scan it. Open archive material only when:

- a current reference/evidence pointer requires exact historical detail;
- a contradiction appears;
- an audit needs provenance;
- a current statement cannot be verified from its normal evidence route.

Closed archive material is preserved; it is not a second current authority.

Git history remains the fallback for old wording and path history.

---

## 12. Mechanical automation

Canonical validator:

```text
python tools/knowledge/validate_knowledge_state.py
```

It checks at minimum:

- exactly one active evidence ledger remains in `docs/`;
- closed ledger volumes are not left in the active surface;
- temporary probe/task/correction/implementation/refactor filenames are not left in root `docs/`;
- active temporary documents declare ACTIVE status;
- required rule/procedure authorities route to this lifecycle;
- current Markdown files use the permitted `docs/`, `docs/decisions/`, or `docs/work/active/` topology;
- every allowlisted permanent `docs/*.md` file has a recognizable `KNOWLEDGE_REGISTRY.md` route;
- ordinary/current Markdown file links and fragments resolve;
- numeric `FILE.md §N` / `FILE.md §N.M` routes resolve to matching numbered headings;
- required archive/work directories exist.

GitHub Actions runs the same validator on relevant pushes and pull requests.

Automation catches mechanically decidable structural drift; it does not decide whether technical conclusions are correct, whether differently worded authorities duplicate responsibility, or whether a task is factually ready to close. Those remain evidence/POP-10/manual-review responsibilities.

---

## 13. Full reviews / audits

Routine work uses local maintenance transactions.

A broad review is justified by repeated drift, conflicting owners, inability to retrieve settled knowledge, uncontrolled document growth, or another structural problem that cannot be repaired locally.

Formal review begins with POP-10. It must preserve the distinction between:

```text
current knowledge
current architecture
decision rationale
evidence/provenance
temporary/history
```

unless the User deliberately changes the project knowledge model.

---

## 14. User responsibility

The User decides project direction and higher-level intent.

Normal Chat owns routine maintenance, promotion, archival, evidence closure and validator use automatically. The User should not need to remember housekeeping rules after every engineering step.

---

## Core rule

> **Preserve proof deeply, present knowledge shallowly. Promote reusable conclusions before archiving temporary work. Keep only one current evidence ledger. Keep current-state files small. Start from reference/architecture and descend into evidence only when needed. Let automation detect lifecycle drift before it becomes context bloat.**
