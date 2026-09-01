# Work Implementation Protocol

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active bounded-implementation protocol  
**Version:** 1.3  
**Updated:** 2026-08-30

## Purpose

This protocol defines how Work or another implementation agent should execute a bounded Gothic 3 source task after the important semantics have already been decided.

It replaces the previous split between the general Work protocol and `FROZEN_WORK_TASK_RULES.md`.

A bounded implementation task is an implementation assignment, not an invitation to complete missing architecture by brute force.

### Operating intent

Work is intentionally given bounded responsibilities because its comparative advantage in this project is disciplined execution against an already-decided contract: narrow source/API inspection, implementation, source audit and publication. Architecture, semantic uncertainty, evidence interpretation and creative simplification normally stay upstream in User + Normal Chat, where accumulated collaborative context is strongest.

This boundary also uses project resources deliberately. The User's Work access has limited hourly/weekly budget, so Work should not spend that budget reconstructing project history, performing routine knowledge maintenance, or exploring open-ended design when those responsibilities are already owned effectively elsewhere.

The objective is not to constrain a strong executor unnecessarily. It is to give Work enough intent, authority and context to implement well while preventing implementation pressure or available compute from silently turning Work into a second architect.

The normal responsibility split is currently:

```text
User + Normal Chat
reason from evidence / decide semantics / freeze bounded task
        ↓
Work
inspect only what implementation needs / edit / source-audit / commit-publish / concise handoff
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
→ commit / publish
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

## 8. Commit and Publish Path

When a bounded Work task is expected to publish its audited result, the launcher or frozen task should state the **exact destination repository and branch** and explicitly authorize publication of the commits created for that bounded task.

Example authorization shape:

```text
Publishing authorization:
The User explicitly authorizes Work to publish the audited commits created for this bounded task to:
Repository: https://github.com/tcholti/Gothic3_Animation_Behaviors.git
Branch: docs/collision-source-evidence
This authorization is limited to this bounded task and this exact destination.
```

This authorization does not grant permission to publish unrelated changes, another branch, or another repository.

If the execution environment still requires a separate interactive destination approval despite that explicit task authorization, request that approval. Treat it as a publishing permission checkpoint, not an implementation contradiction and not a reason to modify the source.

Use the local Git checkout for normal source inspection, diffing, auditing, and commit preparation.

For publishing the audited result:

1. prefer normal `git push` when command-line GitHub authentication is already available;
2. if `git push` fails specifically because the Work checkout has no usable GitHub credential, do **not** spend task time troubleshooting, installing, or persisting credentials;
3. verify the intended repository, target branch, and exact audited source state;
4. use the connected GitHub repository API to publish that same audited state on the intended branch;
5. verify the **resulting remote branch commit identity** after publication and record the final remote implementation SHA in the handoff.

A credential-only CLI push failure is therefore a publishing-path issue, not an implementation blocker. Do not change code, broaden scope, or invent a different Git workflow merely to compensate for it.

Connected-API publication may reconstruct the audited commit on the remote branch and therefore produce a different SHA from the local pre-publication commit. When that happens:

- the remote SHA is the authoritative published implementation identity;
- the handoff must report the final remote implementation SHA and, when applicable, the final remote handoff SHA;
- any earlier local SHA may be noted only as superseded pre-publication provenance;
- do not tell the receiving context that publication is complete using only a local SHA that the remote repository cannot resolve.

If repository identity, branch identity, write permission, source-state equivalence, or resulting remote commit identity cannot be verified, stop and report the contradiction instead of publishing or handing off uncertain state.

---

## 9. Required Handoff

After the bounded task report only what the receiving context needs:

- files changed;
- what behavior/responsibility changed;
- protected behavior preserved;
- source-level checks performed;
- material source/API contradiction if any;
- what still requires build/runtime verification;
- final published commit SHA.

Do not reproduce the whole project, design, or evidence history in the handoff.

Then stop unless another task is explicitly assigned.

---

## 10. Independent Review and Trust

For current engine-facing Gothic 3 implementation, a meaningful Work commit should normally receive an independent Normal Chat diff-against-contract review before runtime validation or before the implementation is treated as authoritative.

This is task-specific calibration, not permanent distrust.

Repeated clean performance in a stable task class may justify shorter task contracts and more targeted review. A new task class, changed conditions, semantic novelty, or higher consequence may justify stronger review again.

A Work self-review, apology, confidence statement, or commit existence is not independent evidence.

---

## 11. Stop Conditions

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
