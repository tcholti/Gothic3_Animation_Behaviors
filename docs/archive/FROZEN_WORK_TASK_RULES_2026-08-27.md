# Frozen Work Task Rules

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active implementation contract  
**Updated:** 2026-08-27

## Purpose

A frozen Work task is an implementation assignment, not an invitation to complete or reinterpret the architecture.

Normal Chat owns the design decisions, evidence interpretation, semantic authority, and exact task boundary. Work owns faithful implementation, narrowly necessary source/API inspection, source-level audit, commit/push, and handoff.

For the empirical lessons and longer-term plan for improving this collaboration, see `WORK_COLLABORATION_EVOLUTION.md`.

## Required execution sequence

For a frozen task, Work should normally do only:

```text
read assigned files
-> confirm the task contract and stop conditions
-> inspect only source/API material necessary to implement the frozen task
-> edit only the bounded implementation
-> source audit against the frozen task and protected behavior
-> commit / push
-> write concise handoff
-> STOP
```

Do not broaden the task merely because more code, tools, context, or reasoning capacity are available.

## Pre-edit semantic preflight

Before editing a non-trivial frozen task, Work should be able to identify from the assigned task/documentation:

```text
Target change:
Question the code is supposed to answer:
Protected behavior:
Allowed hooks/interfaces/modules:
Authoritative facts/events:
Semantic decisions already frozen:
Decisions Work is not authorized to make:
Stop conditions:
```

This does not require a long written ceremony for every small task. It is a check that the important semantics are actually present before implementation begins.

If a required field cannot be resolved from the frozen task or authoritative documentation and the missing information would change behavior, classification, ownership, lifecycle or architecture, that is a missing design decision and therefore a stop condition.

## Missing decisions are stop conditions

Implementation is not permission to fill in missing design decisions.

If the frozen task depends on a semantic, ownership, lifecycle, classification, fallback, or architectural decision that is not already defined by the task or authoritative project documentation:

1. do not invent the rule;
2. do not create a convenient classifier, taxonomy, fallback, helper policy, or second model merely to make the code complete;
3. record the exact missing decision or contradiction;
4. return it to Normal Chat/design.

A source commit is not evidence that the design decision was correct.

## What "simple" means

For a frozen Work task, **simple** means:

> the smallest code that directly expresses the already-decided question or behavior.

Simple does not mean "few lines at any cost," and it does not mean adding generalized machinery in anticipation of future needs.

Avoid unless explicitly required:

- speculative generalization;
- fallback taxonomies;
- broad classifiers;
- extra state;
- duplicate ownership/lifecycle models;
- defensive branches for unproven cases;
- helper layers that do not serve the frozen task directly;
- exploration unrelated to an actual implementation contradiction.

## What "separate" means

Separation is about responsibility and ownership, not merely putting code in different files.

For the current prototype:

```text
Hook bridge / main
    collects and dispatches engine facts

Collision diagnostics
    observes and records facts

Collision control
    owns collision behavior and decisions
```

Rules:

- diagnostics must not quietly become a second collision/lifecycle authority;
- hook code should not invent policy that belongs to collision control or design;
- shared structures should carry facts, not hidden behavioral decisions;
- temporary research instrumentation must remain removable without redesigning production behavior;
- code placed in separate files is not meaningfully separate if responsibilities are still coupled.

## What "good engineering" means in a frozen task

Good engineering here means:

- preserve the agreed authority and assumptions;
- preserve protected behavior outside the assigned change;
- make one conceptual change at a time;
- use the smallest authoritative fact/event available;
- keep changes reversible and testable;
- distinguish observation from behavior;
- avoid inferred proxies when a stronger fact exists;
- surface uncertainty or contradiction rather than hiding it in code;
- do not optimize for apparent completeness at the expense of architectural correctness;
- do not claim runtime or architectural success from source completion alone.

## B6 lesson

Step B6 exposed the failure mode this contract is intended to prevent.

Work introduced a hard-coded attack-Hit filename classifier and initially emitted a replacement record for every qualifying PlayMotion call. Even though this was diagnostic-only, it inserted classification semantics beyond the exact frozen question and did not first prove that replacement had occurred.

The later independent Normal Chat review corrected the implementation so the pre-call stack is captured while the outgoing Hit exists, but the replacement record is emitted only when the existing B1 before/after motion evidence proves a replacement/restart.

The lesson is general:

> When implementation reveals a missing semantic decision, Work must not silently become a second architect.

## Allowed challenge to a frozen task

Work may challenge the task when source/API evidence proves an assumption impossible or materially wrong.

That challenge should be narrow and explicit:

```text
expected by frozen task
vs.
observed source/API fact
vs.
why implementation cannot proceed faithfully
```

Then stop and return to Normal Chat unless the task itself already specifies the allowed fallback.

## Completion standard

Before committing, audit the result against these questions:

1. Did I implement only the frozen question/change?
2. Did I add any semantic rule that was not already decided?
3. Did I create a second ownership/lifecycle/classification model?
4. Did I add machinery for hypothetical future cases?
5. Did I preserve existing hooks and protected behavior unless explicitly assigned otherwise?
6. Can every new branch/state/helper be justified directly by the frozen task?
7. If I found a contradiction, did I report it instead of coding around it?
8. Does my handoff distinguish source completion from facts that still require build/runtime proof?

If any answer is problematic, fix it or stop and return the issue to Normal Chat before claiming the task complete.

## Independent review expectation

For the current collaboration stage, a meaningful Work code commit is not treated as implementation authority merely because Work reports success.

Normal Chat should independently compare the committed diff against the frozen contract before runtime validation, with particular attention to:

- unassigned semantic rules or classifiers;
- changes outside the allowed conceptual/file/hook boundary;
- protected behavior;
- new state or fallback machinery;
- claims in the handoff that are stronger than the source evidence.

This is a calibration mechanism, not a permanent assumption that Work cannot improve. Review depth may become more targeted for task classes that repeatedly demonstrate clean compliance.

## Retrospective rule

After a Work session, record a new durable collaboration rule only when the lesson is material, recurring, or likely to prevent meaningful rework.

Do not turn every minor imperfection into another rule. The aim is a small set of generative operational principles.

See `WORK_COLLABORATION_EVOLUTION.md` for the empirical session examples, task-specific trust model, CAM translation method, and future roadmap.

## Core rule

> **Frozen Work means faithful implementation, not design completion. If a necessary semantic decision is missing, stop and return it to Normal Chat rather than inventing it.**
