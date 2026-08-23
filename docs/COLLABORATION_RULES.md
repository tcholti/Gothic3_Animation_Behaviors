# Collaboration Rules

**Project:** Gothic3_Animation_Behaviors  
**Status:** Experimental / living document  
**Version:** 0.1  
**Purpose:** Preserve the quality, continuity, and adaptability of our collaboration while using Work, repository review, documentation updates, and higher reasoning levels deliberately rather than automatically.

---

## 1. Core Principle

These rules exist to improve the collaboration, not to constrain it.

**Quality, correctness, evidence, and continuity take priority over usage savings.**

Usage efficiency should come primarily from avoiding unnecessary repeated work: rereading unchanged material, updating many documents after every small test, or using heavier reasoning when an established step can be handled reliably with less.

If following a rule would materially reduce the quality of the work, hide relevant evidence, create uncertainty, or make the process harder, the rule should be relaxed or changed.

The rules are defaults, not hard limits.

---

## 2. Preserve the Working Method That Already Works

The normal implementation cycle remains:

**hypothesis / question -> controlled test -> evidence -> interpretation -> smallest useful code change -> rebuild -> retest**

Do not weaken this cycle merely to save usage.

Continue to:

- investigate Gothic 3 behavior from evidence rather than assumption;
- use relevant SDK, example, binary-reference, source, and repository material when needed;
- preserve proven paths and change one meaningful variable at a time when practical;
- use logger evidence for timing and collision behavior rather than visual observation alone;
- reconsider earlier assumptions when new evidence contradicts them;
- broaden the investigation whenever the narrow path is no longer sufficient.

Efficiency should remove redundant work around the investigation, not reduce the quality of the investigation itself.

---

## 3. Reasoning-Level Guidance

The assistant should actively recommend the reasoning level rather than leaving the user to guess what a task requires.

### Medium reasoning — normal default

Recommend **Medium** when the work is a continuation of an established path, for example:

- interpreting a normal test result;
- making a small or localized code change;
- adjusting an existing hook, logger, configuration value, or known implementation;
- fixing a straightforward compile error;
- repeating a controlled experiment with one changed variable;
- reviewing a small number of already-known relevant files;
- discussing the next test in an established investigation.

Typical wording:

> **Medium is enough for this step.** We are continuing an established path and do not need a broad review.

### High reasoning — escalate when it provides real value

Recommend **High** when the task materially benefits from broader or deeper reasoning, for example:

- tracing an unknown Gothic 3 engine mechanism;
- designing a new subsystem or architecture;
- rewriting or substantially restructuring code;
- reviewing many files, systems, documents, or repositories together;
- resolving contradictory evidence or several competing explanations;
- investigating a failure after the established approach has stopped producing useful progress;
- making a decision that could create significant rework if wrong;
- performing a broad integration or stabilization review;
- reconstructing the state of the project after substantial changes or an uncertain handoff.

Typical wording:

> **I recommend switching to High for this step.** I need to trace/rewrite/cross-reference several parts of the project, and the extra reasoning is likely to improve the result.

### Return to Medium after the difficult step

High reasoning should not become the automatic setting for the rest of the session simply because one difficult task required it.

When the difficult investigation has produced a stable path, the assistant should say so and recommend returning to Medium.

Typical wording:

> **We can return to Medium now.** The uncertain part is resolved and the next steps are controlled implementation/tests.

### Lighter reasoning

A lighter setting may be suggested for genuinely simple work such as status checks, very small clerical changes, or other tasks that do not require meaningful engineering judgment.

Do not recommend a lighter setting merely to save usage when the current code/test decision contains real uncertainty.

---

## 4. Targeted Repository Review First

Do not automatically reread or re-review the entire repository between prompts.

Start with the smallest set of files that is reasonably sufficient for the current question.

Examples:

- if a test concerns one hook, inspect the hook implementation and the directly related logger/code first;
- if a compile error names a file or symbol, start there;
- if an existing design decision is already known and unchanged, do not reopen all design documents merely to confirm it again.

Broaden the review when evidence requires it.

There is **no fixed maximum number of files**. If five, twenty, or more files are genuinely needed to understand the problem correctly, review them. The rule prevents habitual broad review, not necessary broad review.

---

## 5. Do Not Re-Verify Stable Knowledge Without a Reason

Previously established project knowledge may be reused when:

- it is documented clearly;
- the relevant code or assumptions have not changed;
- there is no new evidence suggesting that it may be wrong.

Re-verify when:

- new results conflict with it;
- the implementation that supported it has changed;
- the current task depends critically on a subtle detail;
- the assistant is uncertain whether the remembered/documented conclusion still applies.

The objective is to avoid spending substantial work repeatedly proving the same stable fact while retaining the ability to challenge it when necessary.

---

## 6. Batch Routine Documentation Updates

Do not update every project document after every small experiment.

During a rapid test/code/test cycle, minor observations can accumulate until a **meaningful checkpoint**.

Good checkpoints include:

- a hypothesis being confirmed or rejected;
- a hook or implementation path becoming stable;
- a feature reaching a testable or working state;
- a significant engine behavior being established;
- the project changing direction;
- a session ending after meaningful progress;
- preparing to move to another chat or hand the work off;
- enough related evidence accumulating that consolidation will simplify later work.

At a checkpoint, update only the documents whose purpose is affected.

Avoid touching unrelated documents simply because a repository update is being made.

---

## 7. Important Findings Are an Exception to Batching

Do not leave a major confirmed finding only in transient chat context just to save usage.

Record important information promptly when losing it could cause meaningful rework, especially:

- confirmed engine behavior;
- a newly proven callback/hook path;
- a disproven assumption that future work might otherwise repeat;
- a compatibility or safety constraint;
- a change to the project's current implementation direction;
- a result necessary for another chat to continue correctly.

Minor test details may wait for consolidation. Important durable knowledge should not.

---

## 8. Separate Code Progress From Documentation Churn

A code commit does not automatically require a full documentation pass.

Likewise, a documentation update does not require reviewing every implementation file.

During active experimentation, prioritize getting reliable evidence and a stable implementation. Consolidate documentation when the result is mature enough to describe accurately.

This avoids repeatedly rewriting documentation around temporary hypotheses that may change one or two tests later.

---

## 9. Use Broader Reviews Deliberately

A broad repository/document review is valuable when it has a clear purpose.

Examples:

- before a major architectural change;
- after several related implementations have accumulated;
- before declaring a subsystem stable;
- when contradictions appear between code, evidence, and documentation;
- when a new chat lacks enough context to continue safely;
- when technical debt or accumulated temporary decisions need consolidation.

When proposing a broad review, the assistant should explain briefly why it is useful.

Example:

> **This is a good point for a broader review.** We now have several collision findings and two implementation paths that affect the same subsystem, so consolidating them before the next change should reduce mistakes.

---

## 10. Assistant Usage-Awareness Responsibility

The assistant should consider likely Work/reasoning cost as one engineering constraint among many, but should not optimize blindly for it.

The assistant should proactively say when:

- Medium is sufficient;
- High is likely to materially improve the result;
- a broad repository review can probably wait;
- enough evidence has accumulated that a documentation checkpoint is worthwhile;
- several small updates can be combined into one coherent update;
- an attempted saving would create unacceptable uncertainty or risk.

The user should not have to manage this alone.

---

## 11. No Artificial Fragmentation

Do not split a naturally connected engineering task into many chats or artificial microtasks solely to reduce Work usage if doing so would damage context or efficiency.

Normal chat may be useful for general planning, conceptual discussion, or unrelated questions, but active repository implementation can remain together when continuity is valuable.

The choice of Chat versus Work should serve the task rather than become a rigid rule.

---

## 12. Preserve Adaptability

These rules must never prevent the assistant from changing approach when the evidence warrants it.

The assistant may:

- inspect additional files without prior permission when they become relevant;
- propose a different test or implementation path;
- recommend abandoning an approach that is failing;
- recommend High reasoning unexpectedly when a supposedly simple task reveals deeper uncertainty;
- update documentation earlier than planned if an important finding should be preserved;
- postpone a planned documentation update if the underlying result is still unstable.

When deviating substantially from the normal default, briefly state why.

---

## 13. Quality-Degradation Check

Periodically ask:

**Are these rules helping us avoid redundant work, or are they starting to make the engineering worse?**

Warning signs include:

- missing relevant references because the review was kept too narrow;
- repeated mistakes because documentation was postponed too long;
- loss of continuity between chats;
- reluctance to use High reasoning for a genuinely difficult problem;
- accumulating undocumented assumptions;
- spending more effort managing the rules than doing the work;
- lower confidence or slower progress than before the rules were introduced.

If these appear, change the rules rather than forcing the workflow to comply with them.

---

## 14. Collaboration-Rule Revision Process

This is a living document.

Changes should be based primarily on observed collaboration results rather than theoretical optimization.

When a rule appears useful:

- keep it and refine it if necessary.

When a rule is neutral:

- do not add complexity without a reason.

When a rule degrades work:

- modify or remove it.

When a recurring successful practice emerges naturally:

- consider adding it here so it survives chat transitions and can later be reused in other projects.

Major changes should increment the document version so the evolution of the collaboration method remains understandable.

---

## 15. Assistant Questions and Proposed Improvements

This section is intentionally reserved for future refinement.

The assistant may raise questions or propose additions when repeated work reveals a pattern that may deserve a rule.

Before turning a preference into a significant permanent rule, discuss it with the user when practical.

Possible questions to revisit later:

- How frequently should HANDOFF be refreshed during long experimental sessions?
- Which findings deserve immediate Evidence Ledger updates versus checkpoint batching?
- Does Medium reasoning remain sufficient for most controlled code/test loops in practice?
- Which repository reviews consume substantial usage without improving outcomes?
- Are there recurring tasks that should have their own lightweight procedure?
- Which parts of this protocol generalize well enough to become a project-independent collaboration framework?

Add new questions here as experience accumulates rather than prematurely creating rules for situations we have not encountered.

---

## 16. Current Experimental Default

Until experience suggests otherwise:

1. **Use Medium reasoning for normal implementation and controlled test loops.**
2. **Escalate to High when broad review, substantial rewriting, unknown engine tracing, contradictory evidence, or major architectural judgment makes it worthwhile.**
3. **The assistant should explicitly recommend the change in reasoning level when it sees the need.**
4. **Read relevant repository material selectively first; broaden freely when necessary.**
5. **Do not update every document after every small result.**
6. **Batch routine documentation at meaningful checkpoints.**
7. **Record major durable findings promptly rather than risking their loss.**
8. **Never sacrifice engineering quality merely to preserve usage allowance.**
9. **Review and revise these rules if they begin to hamper the work.**

This default is an experiment. The objective is to learn what produces the best balance of engineering quality, continuity, speed, and sustainable tool usage through actual collaboration.