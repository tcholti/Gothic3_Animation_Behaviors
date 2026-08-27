# Work Implementation Protocol

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active bounded-implementation protocol  
**Version:** 1.0  
**Updated:** 2026-08-27

## Purpose

This protocol defines how Work or another implementation agent should execute a bounded Gothic 3 source task after the important semantics have already been decided.

It replaces the previous split between the general Work protocol and `FROZEN_WORK_TASK_RULES.md`.

A bounded implementation task is an implementation assignment, not an invitation to complete missing architecture by brute force.

The normal responsibility split is currently:

```text
User + Normal Chat
reason from evidence / decide semantics / freeze bounded task
        ↓
Work
inspect only what implementation needs / edit / source-audit / commit-push / concise handoff
        ↓
Normal Chat + authoritative home PC
independent source review / build / runtime evidence / interpretation
```

This allocation is evidence-based and revisable; it is not a universal product hierarchy.

---

## 1. Minimal Read Order

For a frozen/bounded implementation task, start with only:

1. `docs/SESSION_ENTRYPOINT.md`;
2. `docs/BETWEEN_CHATS.md` when it contains the current assigned task/handoff;
3. this protocol;
4. the exact source files assigned by the task;
5. the specific design/evidence/reference section explicitly named by the task.

Do **not** automatically read `ENGINEERING_GUIDE.md`, the full evidence ledgers, `RESEARCH_MAP.md`, `SOURCE_HOOK_GUIDE.md`, the entire collision plan set, or the whole repository before coding.

Retrieve additional material only when the implementation exposes a concrete dependency, contradiction, API uncertainty, or source question that requires it.

Within the same Work context, do not reread unchanged documents after every prompt.

---

## 2. Required Execution Sequence

A normal bounded task should follow:

```text
read assigned/current-state material
→ identify the frozen question and boundaries
→ inspect narrowly necessary source/API material
→ edit only the bounded implementation
→ audit against the contract and protected behavior
→ commit / push
→ concise handoff
→ STOP
```

Do not broaden merely because more repository context, compute, or tooling is available.

---

## 3. Semantic Preflight

Before a non-trivial edit, the task should make the following sufficiently clear when they matter:

```text
Target change:
Question the code is supposed to answer:
Protected behavior:
Allowed files/modules/hooks/interfaces:
Authoritative facts/events:
Semantic decisions already frozen:
Decisions implementation is not authorized to make:
Required evidence/source audit:
Stop conditions:
```

This is a semantic check, not mandatory paperwork. Tiny tasks do not need a long template when the boundary is already obvious.

If missing information would materially decide intended behavior, classification, ownership, lifecycle, fallback, architecture, or another protected semantic rule, stop and return that issue rather than inventing it.

---

## 4. What Bounded Implementation May Decide

Implementation may choose ordinary local details when they are reversible and preserve the frozen semantics, such as:

- normal naming/local organization;
- direct use of an already-approved SDK/API pattern;
- the smallest helper needed to express the assigned behavior;
- straightforward compile fixes that do not alter architecture;
- source-level mechanical details that do not change ownership or behavior meaning.

Implementation must not silently decide:

- what event counts as the authoritative lifetime/ownership boundary;
- what should count as an attack, execution, replacement, source, cleanup, or other semantic category;
- a new fallback taxonomy or policy;
- a new ownership/lifecycle model;
- architectural responsibility;
- protected behavior changes;
- unrelated future generalization.

A source/API contradiction may challenge the frozen task. Report it narrowly as:

```text
expected by task
vs.
observed source/API fact
vs.
why faithful implementation cannot continue
```

Then stop unless an allowed fallback is already defined.

---

## 5. Project Engineering Constraints

For current Gothic 3 engine-facing work:

- use native action, phase, UseType and source semantics when available;
- do not infer collision ownership solely from generic animation filename tokens;
- keep physical damage-source selection separate from attack family/phase identity;
- preserve exact marker/animation ownership where frame-authored collision is involved;
- preserve native behavior for unconfigured/unmarked cases unless the task explicitly changes it;
- diagnostics observe facts and must not quietly become a second behavior/lifecycle authority;
- when behavior and diagnostics share a Gothic hook, keep one authoritative hook owner unless the design explicitly changes that rule.

Do not add persistent state, polling, caches, masks, classifiers, fallback tables, or helper layers merely because they might be useful later.

"Simple" means the smallest direct implementation of the already-decided behavior—not the fewest lines at any cost.

"Separate" means responsibilities/authority remain independently understandable and removable, not merely that code lives in different files.

---

## 6. Preserve One Conceptual Change

Prefer one bounded conceptual variable per implementation task when doing so improves causal testing and review.

Do not casually combine:

- structural refactor;
- new diagnostic semantics;
- production behavior;
- broad cleanup;
- build investigation;
- runtime interpretation;
- documentation consolidation.

They may be combined only when the task makes clear that they are genuinely inseparable.

Adjacent improvements discovered during implementation should be reported rather than silently added unless they are necessary for correctness of the assigned change.

---

## 7. Source Audit Before Commit

Before committing, ask:

1. Did I implement only the assigned conceptual change?
2. Did I stay inside allowed files/hooks/interfaces except for clearly necessary mechanical support?
3. Did I preserve protected behavior?
4. Did I add a semantic classifier, ownership rule, lifecycle rule, fallback, or state that was not already decided?
5. Did I use a weaker inferred proxy when a stronger agreed fact/event exists?
6. Is every new branch/state/helper directly justified by the task?
7. Did I call the original/native function exactly as required where wrapper parity matters?
8. Did I distinguish diagnostic observation from behavior?
9. If source evidence contradicted the task, did I surface it instead of coding around it?
10. Are completion claims limited to what source inspection actually proves?

Mechanical checks should target known risks; do not build a compliance system larger than the implementation.

---

## 8. Required Handoff

After the bounded task report only what the receiving context needs:

- files changed;
- what behavior/responsibility changed;
- protected behavior preserved;
- source-level checks performed;
- material source/API contradiction if any;
- what still requires build/runtime verification;
- commit SHA.

Do not reproduce the whole project, design, or evidence history in the handoff.

Then stop unless another task is explicitly assigned.

---

## 9. Independent Review and Trust

For current engine-facing Gothic 3 implementation, a meaningful Work commit should normally receive an independent Normal Chat diff-against-contract review before runtime validation or before the implementation is treated as authoritative.

This is task-specific calibration, not permanent distrust.

Repeated clean performance in a stable task class may justify shorter task contracts and more targeted review. A new task class, changed conditions, semantic novelty, or higher consequence may justify stronger review again.

A Work self-review, apology, confidence statement, or commit existence is not independent evidence.

---

## 10. Stop Conditions

Stop and return the issue rather than accumulating compensating code when:

- a necessary semantic/ownership/lifecycle/classification decision is missing;
- two or more special-case branches are appearing where one general rule was expected and the task did not authorize exceptions;
- a structural change unexpectedly alters protected runtime behavior;
- diagnostics become necessary for production behavior to work;
- hook ownership becomes duplicated or load-order dependent without explicit design authority;
- the task is expanding into architecture, broad research, runtime interpretation, or unrelated documentation;
- the implementation can no longer be explained as a direct expression of the frozen question.

These are design-review triggers, not invitations to brute-force completion.

---

## Core Rule

> **Implement the decided question faithfully from the smallest necessary context. If implementation discovers a missing semantic decision, return it to design instead of silently becoming a second architect.**
