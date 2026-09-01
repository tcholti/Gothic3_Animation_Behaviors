# Work Collaboration Evolution

**Project:** Gothic3_Animation_Behaviors  
**Status:** Living retrospective and improvement roadmap  
**Updated:** 2026-08-27

## Purpose

This document records what we learn from actual Work sessions and turns those observations into better collaboration procedures.

It is not a complaint log and it is not a substitute for `WORK_IMPLEMENTATION_PROTOCOL.md` or `FROZEN_WORK_TASK_RULES.md`.

Its job is to answer three questions:

1. What kinds of tasks has Work performed well?
2. What recurring failure modes require stronger boundaries or review?
3. How can CAM-style collaboration principles be translated into operational rules that an implementation agent can follow without needing months of shared conversation?

The goal is progressive improvement, not permanent distrust and not blind trust.

---

## 1. Current Working Model

Normal Chat and Work have different responsibilities.

```text
Normal Chat / persistent collaboration
    evidence, interpretation, disagreement, architecture, semantics
                    ↓
             freeze a contract
                    ↓
Work / bounded implementation agent
    targeted source/API inspection, edit, source audit, commit/push
                    ↓
        independent contract review
                    ↓
Home PC / runtime evidence
                    ↓
Normal Chat decides what the result means
```

Work should be treated as a high-capability implementation instrument inside the wider collaboration, not as an automatically equivalent second architect.

Architecture may still be assigned to Work deliberately in the future when there is a reason to do so, but a frozen implementation task does not grant that authority implicitly.

---

## 2. Evidence From Recent Work Sessions

### Step A — large structural task can succeed when responsibilities are explicit

Representative commit:

`325c98e725502229bf796083e52c0fa977803cc0` — `Modularize frame collision research DLL`

The change was large in line count, but its conceptual purpose was explicit: separate hook/bootstrap, collision control, diagnostics, shared structures and runtime timing while preserving one hook owner and behavior parity.

Lesson:

> Small conceptual scope matters more than small textual diff size.

A large refactor can be a suitable Work task when the target responsibilities and protected behavior are already defined.

### Step B1 — bounded observation works well

Representative commit:

`7dcd514b0bcd51c05453e3e55500a927b9063159` — `Add PrimaryFirst motion event probe`

The task added the requested PlayMotion/StopMotion observation, kept it diagnostic-only and reused existing lifetime snapshots rather than turning the probe into behavior.

Lesson:

> Work is effective when asked to expose a specific engine fact at a specific boundary.

### Step B4 — exact mechanical gate works well

Representative commit:

`ddb44930401d1c22821cbde23b16e9845b06a08d` — `Add native cleanup call-site probe`

The probe stayed inside the existing SetCollisionGroup hook, gated the special record to an exact player equipped-source `Item_Attack -> Item_Equipped` cleanup, captured `_ReturnAddress()`, and resolved module/RVA without changing cleanup behavior.

Lesson:

> Exact predicates and explicit non-goals reduce the amount of semantic judgment Work must invent.

### Step B5 — extending a proven diagnostic path works well

Representative commit:

`807307570b85bcdd4f1c3c703204dbd34560feb6` — `Add B5 cleanup parent-stack probe`

The task extended the already-proven B4 cleanup observation with `CaptureStackBackTrace` and supported module resolution. It did not add another Gothic hook or reinterpret the cleanup event.

Lesson:

> Work is especially useful when one proven observation is being extended mechanically while its meaning remains unchanged.

### Step B6 — a small semantic gap can produce disproportionate risk

Initial Work implementation:

`2d9e1f08a09b0f41b1ff0e9227ca37e2537690b0` — `Add B6 Hit replacement stack probe`

Independent correction:

`dbd185ff8480ff1bf2625a57a6dd65d192462e58` — `Tighten B6 replacement emission after review`

Work made several good implementation decisions: it kept the opaque incoming PlayMotion descriptor opaque, used its raw pointer rather than guessing a layout, added no new Gothic hook, and added no persistent B6 state.

But it also invented a hard-coded attack-Hit filename classifier and initially emitted a `HIT REPLACEMENT STACK` record for every qualifying PlayMotion call without first proving that the outgoing PrimaryFirst was replaced.

That was not merely a coding detail. It filled in semantic/classification policy that the frozen task had not fully specified.

Lesson:

> Work risk rises sharply at the boundary between "how to implement this fact" and "what should count as this fact."

This is why source completion and a confident handoff cannot substitute for independent review against the frozen contract.

---

## 3. What Work Is Currently Best Used For

Based on observed sessions, good Work candidates include:

- implementing a fully specified diagnostic at a known hook/boundary;
- extending an already-proven diagnostic with additional captured facts;
- localized source changes with explicit invariants and protected behavior;
- mechanical refactors whose responsibility boundaries are already decided;
- adapting known SDK/example patterns to an already-decided use;
- compile/link fixes when the error and intended architecture are clear;
- source audits against explicit mechanical constraints;
- repository-wide edits when the transformation itself is unambiguous.

These can still be technically difficult. The important property is that the **semantic contract is complete enough** that implementation does not require Work to decide what the system means.

---

## 4. High-Risk Work Conditions

A task should stay in Normal Chat, or return there, when it requires deciding:

- what event is authoritative;
- what counts as an execution, replacement, owner, phase, source or cleanup;
- whether a filename/action/state is behavioral authority or only context;
- which abstraction should own a responsibility;
- whether a fallback or exception is architecturally justified;
- how several contradictory engine observations should be reconciled;
- whether a new classifier/taxonomy/state machine is conceptually correct;
- what "simple" or "separate" should mean for a new subsystem.

These are not forbidden topics for Work forever. They are simply architecture/design tasks and should be assigned explicitly rather than smuggled into an implementation task as an unresolved detail.

---

## 5. CAM Principles Must Be Operationalized

The collaboration developed through CAM contains useful principles, but an episodic execution agent should not be expected to recover months of shared discussion implicitly.

Use this translation process:

```text
CAM principle
    ↓
operational definition
    ↓
positive example
    ↓
failure example
    ↓
mechanical or reviewable check where possible
    ↓
observe future sessions
    ↓
keep / refine / remove the rule based on evidence
```

Examples:

### "Simple"

Principle:

> Prefer generative simplicity over accumulated machinery.

Operational Work meaning:

> Implement the smallest code that expresses the already-decided question. Do not add a generalized classifier, fallback taxonomy, extra state or future-facing machinery unless the frozen contract requires it.

### "Separate"

Principle:

> Responsibilities should remain independently understandable and removable.

Operational Work meaning:

> Separate authority, not merely files. Hook bridge collects facts; diagnostics observe; behavior modules decide. A diagnostic helper that creates its own lifecycle policy is not separate merely because it lives in `CollisionDiagnostics.cpp`.

### "Challenge instead of blindly agreeing"

Principle:

> A contradiction is useful information.

Operational Work meaning:

> When source/API evidence contradicts the frozen task, report `expected -> observed -> consequence` and stop. Do not agree verbally and then code around the contradiction.

### "Planning is more important than the plan"

Principle:

> Plans may change when reality disproves an assumption.

Operational Work meaning:

> Work may challenge a frozen plan with concrete source evidence, but may not silently replace it. The planning layer decides the new plan.

---

## 6. Frozen-Task Preflight Contract

For a non-trivial frozen task, Normal Chat should make the following explicit when they materially affect the implementation:

```text
Target change:
Question the code is supposed to answer:
Protected behavior:
Allowed files/modules:
Allowed hooks/interfaces:
Forbidden changes:
Authoritative facts/events:
Context-only facts that must not become authority:
Semantic decisions already frozen:
Decisions Work is NOT authorized to make:
Expected output/log shape if relevant:
Stop conditions:
Required source audit:
```

Not every tiny task needs every field written out. The purpose is to expose ambiguity before coding, not to create paperwork.

A useful test is:

> Could two competent engineers read the frozen task and independently make the same important semantic decisions?

If not, the task probably needs more planning before Work.

---

## 7. Mechanical Checks Where They Buy Real Confidence

Some CAM principles can be partly enforced by checking the diff rather than relying on self-description.

Examples:

```text
Allowed files = three source files + handoff
-> compare commit and verify only those files changed

No new Gothic hooks
-> inspect hook declarations/installation count

Original function exactly once
-> source audit the wrapper call path

No persistent state
-> check for new globals/maps/caches/static execution records

Diagnostic-only
-> verify behavior/control module is unchanged unless explicitly assigned

No new semantic classifier
-> inspect new predicates/tables/tokens/enums that decide what an event "is"
```

Mechanical checks should target known risks. Do not create a large compliance system whose maintenance costs more than the engineering it protects.

---

## 8. Independent Post-Work Review

For now, every meaningful Work code session should be reviewed in Normal Chat before runtime validation or before its implementation is treated as authoritative.

The review should compare **the diff to the contract**, not merely read Work's handoff.

Check in this order:

1. Did Work change only the assigned conceptual variable?
2. Did it stay inside allowed files/hooks/interfaces?
3. Did it preserve protected behavior?
4. Did it add any semantic rule, classifier, fallback, state or authority not present in the frozen contract?
5. Did it use a weaker proxy where a stronger pre-agreed fact existed?
6. Are claims in the handoff actually supported by the diff?
7. Is the result ready for build/runtime evidence, or does it need a small source correction first?

A Work apology, promise, self-audit or confident completion message is not evidence of improved behavior. The diff and later runtime evidence are.

---

## 9. Session Retrospective Loop

After a Work session, ask only if there is a meaningful lesson:

- What did Work do particularly well that we should make easier to repeat?
- What mistake or inefficiency occurred?
- Was the problem in Work execution, or was the frozen contract itself ambiguous?
- Would a better operational rule have prevented it?
- Can the lesson be checked mechanically?
- Is it important/recurrent enough to document, or should it remain a one-off observation?

Do **not** add a new rule after every small imperfection. Rules should earn their place by preventing meaningful rework or preserving collaboration quality.

---

## 10. Trust Should Be Evidence-Based and Task-Specific

Do not use one global judgment such as "Work is trustworthy" or "Work is untrustworthy."

Trust should be earned separately for task classes.

Current default:

### Level 0 — supervised execution

- frozen contract required;
- independent Normal Chat review required;
- no unassigned semantic discretion;
- runtime claims require local evidence.

This is the current level for engine-facing Gothic 3 implementation.

### Level 1 — proven task class

After repeated clean sessions of the same kind, the task template may become shorter and the review may become more targeted, while still checking the important invariants.

Example candidates could eventually include known diagnostic extensions, small compile fixes or repetitive configuration additions.

### Level 2 — calibrated implementation discretion

If a task class repeatedly demonstrates sound handling of minor implementation choices, Work may be granted explicitly bounded discretion within that class.

This does not automatically grant architectural authority elsewhere.

### Architecture/design authority

Architecture remains an explicit assignment, not a maturity level Work silently acquires. If we deliberately ask Work to help design something, that is a different mode with different review expectations.

Trust can increase, decrease or remain mixed by task class based on observed results.

---

## 11. Future CAM-Derived Collaboration Framework

The long-term aim is broader than Gothic 3.

If this process proves useful, extract a project-independent framework shaped by CAM:

```text
shared collaboration principles
        ↓
persistent planning / reasoning layer
        ↓
project-specific architecture and evidence
        ↓
frozen implementation contract
        ↓
bounded execution agent
        ↓
independent contract review
        ↓
runtime/user evidence
        ↓
retrospective and rule refinement
```

Potential future projects include UAA and game-design/code projects, but each should retain its own domain knowledge, permissions, artifacts and technical constraints.

Do not prematurely copy Gothic 3-specific rules into another project. First extract the general principle, then instantiate it for that project.

The desired result is not to force every execution agent to recreate months of CAM conversations. It is to encode the **most generative lessons** from those conversations in a compact form that improves real behavior.

---

## 12. What Would Count as Progress

Evidence that collaboration with Work is improving would include:

- repeated frozen tasks completed without invented semantics;
- contradictions surfaced before code is written around them;
- Work handoffs that accurately distinguish source completion from runtime proof;
- decreasing need for corrective commits after independent review;
- shorter task prompts without loss of behavior integrity;
- stable task classes where review can become more targeted;
- useful initiative inside explicitly granted boundaries rather than uncontrolled expansion;
- fewer rules needed over time because a small set of operational principles covers many cases.

The goal is not obedience for its own sake. The goal is **reliable calibrated initiative**.

---

## 13. Current Core Lessons

1. Work can be highly effective at difficult implementation when the semantic boundary is already decided.
2. A small unresolved semantic gap can matter more than the size of the code change.
3. Verbal agreement or apology is not durable learning; important lessons must be externalized.
4. A source commit is not proof of correct architecture, and a self-review is not a substitute for contract review.
5. Independent review should inspect the diff against the frozen contract before runtime testing.
6. Rules should be derived from observed failures/successes and should remain lightweight enough not to become the work.
7. Trust should be calibrated by task class and evidence, not assumed globally.
8. CAM principles become useful to Work when converted into operational definitions, examples and checks.
9. If a lesson matters, externalize it. If a claimed improvement matters, verify it.
10. The long-term objective is not merely tighter control of Work; it is to discover how to grant it **more useful freedom safely** as evidence earns that freedom.
