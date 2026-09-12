# Work Implementation Protocol

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active bounded-implementation protocol  
**Version:** 1.6  
**Updated:** 2026-09-12

## Purpose

Define how Work or another implementation agent executes a bounded Gothic 3 source task **after User + Normal Chat have assigned that responsibility and sufficiently decided its important semantics**.

Participant allocation and why Work is used are owned by `COLLABORATION_RULES.md`. Project-wide research-to-production architecture is owned by `FEATURE_DEVELOPMENT_METHOD.md`. This protocol begins once the bounded implementation responsibility exists.

> **A bounded implementation task is an implementation assignment, not an invitation to complete missing architecture by brute force.**

> **Unknown feature behavior must not be explored by accumulating policy/state in a bridge or stable production module. For experimental behavior tasks, follow `FEATURE_DEVELOPMENT_METHOD.md`: isolated probe first; permanent owner only after the mechanism is proven.**

---

## 1. Minimal Read Order

For a frozen/bounded implementation task, start with only:

1. `docs/SESSION_ENTRYPOINT.md`;
2. `docs/BETWEEN_CHATS.md` when it contains the current assigned task/handoff;
3. this protocol;
4. `docs/FEATURE_DEVELOPMENT_METHOD.md` for any feature, probe, behavior, hook, or architecture-affecting source task;
5. the exact source files assigned by the task;
6. the specific design/evidence/reference section explicitly named by the task.

Do **not** automatically read the full evidence ledgers, every collision plan, the whole repository, or unrelated engineering authorities before coding. Retrieve additional material only when the implementation exposes a concrete dependency, contradiction, API uncertainty, or source question that requires it.

Within the same Work context, do not reread unchanged documents after every prompt.

---

## 2. Required Execution Sequence

A normal bounded task should follow:

```text
read assigned/current-state material
-> identify the frozen question and boundaries
-> inspect narrowly necessary source/API material
-> edit only the bounded implementation
-> audit against the contract and protected behavior
-> commit / publish
-> concise handoff
-> STOP
```

Do not broaden merely because more repository context, compute, or tooling is available.

---

## 3. Work Build Execution Policy

Default rule:

**Work MUST NOT attempt, probe, configure, generate, invoke, troubleshoot, or prepare a build unless the CURRENT frozen task explicitly authorizes Work to perform a build.**

Absence of explicit build authorization means **BUILD PROHIBITED**, not optional.

When build execution is not explicitly authorized, Work must not:

- invoke `cmake`, `cmake --build`, MSBuild, Visual Studio build tools, Ninja, Make, compilers, linkers, or equivalent tooling;
- probe build-tool availability merely to report it;
- configure/regenerate build directories;
- initialize/populate SDK or other submodules for building;
- search for or install dependencies;
- troubleshoot missing build tools/environment;
- attempt an alternative build route.

Ordinary Work validation is limited to source/static checks authorized by the task, such as exact diff/scope inspection, `git diff --check`, targeted source audit, protected-behavior audit, and exact file/change verification.

Normal project workflow:

```text
Work
    bounded source edit
    -> source/static audit
    -> commit/publish
    -> STOP

Normal Chat + User local environment
    -> independent source review
    -> local build
    -> deployment
    -> runtime validation
```

Standard handoff wording when build was not explicitly authorized:

```text
Build: NOT ATTEMPTED — Work build execution was not authorized for this task.
```

A task may explicitly authorize a bounded build. If that build encounters an unavailable tool/environment, report the failure once and do not troubleshoot/install/reconfigure unless the same task explicitly authorizes that additional work.

Historical tasks, previous build documentation, an existing build directory, or a request to report build status do not authorize a build.

---

## 4. Semantic Preflight

Before a non-trivial edit, the task should make sufficiently clear when relevant:

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

This is a semantic check, not mandatory paperwork. Tiny tasks do not need a long template when the boundary is obvious.

If missing information would materially decide intended behavior, classification, ownership, lifecycle, fallback, architecture, or another protected semantic rule, stop and return that issue rather than inventing it.

---

## 5. Modular Feature / Probe Boundary

This section is mandatory for feature, behavior, hook, and experimental implementation tasks.

### 5.1 Bridge / hook-owner rule

A bridge or hook-owner module may:

```text
own a low-level engine hook exactly once
capture native facts
translate transport into stable project context
call a feature/probe module
enact the narrow returned transport decision
```

It may not become the default home for:

```text
feature policy
experimental state machines
causal probe state
source/family special cases
research-only timing logic
production behavior merely because the hook is convenient
```

If a new behavior needs an already-owned hook, add the **smallest delegation seam** and keep the behavior decision in its own owner.

### 5.2 Unknown mechanism -> temporary probe

If the frozen task is experimental and the underlying mechanism/ownership is not yet proven:

- put intervention/state/policy in a dedicated temporary probe/test module by default;
- compile the probe only into the diagnostic/research target whenever practical;
- keep established production feature modules unchanged unless the task has already proved the experiment is an extension of their exact mechanism;
- keep diagnostic observation separate from behavior intervention;
- do not make release behavior depend on the probe.

A probe task is not permission to implement the final feature.

### 5.3 Proven mechanism -> permanent owner

If the frozen task is production implementation after research closure:

- implement the minimum proven responsibility in the permanent feature module that actually owns it;
- create a new permanent module when the responsibility is genuinely new;
- extend an existing module only when the contract establishes that the mechanism/ownership is the same;
- remove or exclude experiment-only state, diagnostics, guards, branches, and scaffolding;
- do not promote a probe wholesale simply because it passed;
- preserve the bridge as transport-only.

A production task is not permission to continue experimenting.

### 5.4 Validation sequencing consequence

Do not knowingly prepare a broad/final-certification candidate while a concrete scope-changing feature discovery is still undecided. When a new mechanism appears during validation, return it to Normal Chat/design for disposition before broad certification resumes.

Full authority: `FEATURE_DEVELOPMENT_METHOD.md`.

---

## 6. What Bounded Implementation May Decide

Implementation may choose ordinary local details when reversible and semantics-preserving, such as:

- normal local naming/organization;
- direct use of an already-approved SDK/API pattern;
- the smallest helper needed to express assigned behavior;
- straightforward compile fixes that do not alter architecture;
- mechanical details that do not change ownership or behavior meaning.

Implementation must not silently decide:

- what event counts as authoritative lifetime/ownership boundary;
- what counts as an attack, execution, replacement, source, cleanup, or semantic category;
- a new fallback taxonomy/policy;
- a new ownership/lifecycle model;
- architectural responsibility;
- whether an uncertain experiment belongs in an existing production module;
- protected behavior changes;
- unrelated future generalization.

A source/API contradiction may challenge the frozen task. Report narrowly:

```text
expected by task
vs.
observed source/API fact
vs.
why faithful implementation cannot continue
```

Then stop unless an allowed fallback is already defined.

---

## 7. Project Engineering Constraints

For current Gothic 3 engine-facing work:

- use native action, phase, UseType and source semantics when available;
- do not infer collision ownership solely from animation filename tokens;
- keep physical damage-source selection separate from attack family/phase identity;
- preserve exact marker/animation ownership where frame-authored collision is involved;
- preserve native behavior for unconfigured/unmarked cases unless explicitly changed;
- diagnostics observe facts and must not quietly become a second behavior/lifecycle authority;
- when behavior and diagnostics share a Gothic hook, keep one authoritative hook owner unless design explicitly changes that rule;
- preserve modularity: transport, feature behavior, lifecycle, diagnostics, and temporary probes remain independently understandable/removable.

Do not add persistent state, polling, caches, masks, classifiers, fallback tables, or helper layers merely because they may be useful later.

"Simple" means the smallest direct implementation of the already-decided behavior—not the fewest lines at any cost.

"Separate" means responsibilities/authority remain independently understandable and removable, not merely that code lives in different files.

---

## 8. Preserve One Conceptual Change

Prefer one bounded conceptual variable per implementation task when that improves causal testing and review.

Do not casually combine:

- structural refactor;
- new diagnostic semantics;
- causal experiment;
- production behavior;
- broad cleanup;
- build investigation;
- runtime interpretation;
- documentation consolidation.

They may be combined only when the task makes clear they are genuinely inseparable.

Adjacent improvements discovered during implementation should be reported rather than silently added unless necessary for correctness of the assigned change.

---

## 9. Source Audit Before Commit

Before committing, ask:

1. Did I implement only the assigned conceptual change?
2. Did I stay inside allowed files/hooks/interfaces except necessary mechanical support?
3. Did I preserve protected behavior?
4. Did I add a semantic classifier, ownership rule, lifecycle rule, fallback, or state not already decided?
5. Did I use a weaker proxy when a stronger agreed fact/event exists?
6. Is every new branch/state/helper directly justified by the task?
7. Did I call native/original behavior exactly as required where wrapper parity matters?
8. Did I distinguish diagnostic observation, temporary probe behavior, and production behavior?
9. Is `EngineBridge`/hook transport still free of feature/probe policy except explicitly authorized transport seams?
10. If this was a probe task, could the probe be removed without changing established production behavior?
11. If this was a production task, did experiment-only scaffolding stay out of the permanent implementation?
12. If source evidence contradicted the task, did I surface it rather than code around it?
13. Are completion claims limited to what source inspection actually proves?

Mechanical checks should target known risks; do not build a compliance system larger than the implementation.

---

## 10. Commit and Publish Path

When a bounded Work task is expected to publish its audited result, the launcher/frozen task should state the exact destination repository and branch and explicitly authorize publication for that bounded task.

Authorization is limited to that task and exact destination. It does not grant permission for unrelated changes or another repository/branch.

Use the local Git checkout for source inspection, diffing, auditing, and commit preparation.

For publication:

1. prefer normal `git push` when command-line authentication already works;
2. if push fails specifically for missing credential, do not spend task time troubleshooting/installing/persisting credentials;
3. verify intended repository, branch, and exact audited source state;
4. use the connected GitHub repository API to publish the same audited state when needed;
5. verify the resulting remote branch commit identity and report the final remote implementation SHA.

Connected-API publication may reconstruct the audited commit and therefore yield a different SHA from a local pre-publication commit. The final remote SHA is authoritative.

If repository identity, branch identity, write permission, source-state equivalence, or resulting remote commit identity cannot be verified, stop and report the contradiction instead of publishing uncertain state.

---

## 11. Required Handoff

After the bounded task report only what the receiving context needs:

- files changed;
- what behavior/responsibility changed;
- protected behavior preserved;
- source/static checks performed;
- material source/API contradiction if any;
- what still requires build/runtime verification;
- final published commit SHA.

For probe tasks, explicitly identify the code as temporary diagnostic/research scaffolding and state the exact causal question it is meant to answer.

Do not reproduce the whole project/design/evidence history. Then stop unless another task is explicitly assigned.

---

## 12. Independent Review and Trust

A meaningful engine-facing Work commit should normally receive an independent Normal Chat diff-against-contract review before runtime validation or before being treated as authoritative.

Repeated clean performance in a stable task class may justify shorter contracts/review. New task classes, changed conditions, semantic novelty, or higher consequence may justify stronger review.

A Work self-review, apology, confidence statement, or commit existence is not independent evidence.

---

## 13. Stop Conditions

Stop and return the issue rather than accumulating compensating code when:

- a necessary semantic/ownership/lifecycle/classification decision is missing;
- two or more special-case branches appear where one general rule was expected and exceptions were not authorized;
- a structural change unexpectedly alters protected runtime behavior;
- diagnostics become necessary for production behavior to work;
- experimental policy/state is starting to accumulate in `EngineBridge` or another stable module contrary to the feature-development method;
- hook ownership becomes duplicated or load-order dependent without explicit design authority;
- a temporary probe cannot remain removable without redesigning established modules;
- the task expands into architecture, broad research, runtime interpretation, or unrelated documentation;
- the implementation can no longer be explained as a direct expression of the frozen question.

These are design-review triggers, not invitations to brute-force completion.

---

## Core Rule

> **Implement the decided question faithfully from the smallest necessary context. Keep transport, temporary research, and permanent feature ownership separate. If implementation discovers a missing semantic or architectural decision, return it to design instead of silently becoming a second architect.**
