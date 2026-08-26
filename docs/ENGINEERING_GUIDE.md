# Principle-First Engineering Guide

**Status:** Experimental / living document  
**Version:** 0.3  
**Scope:** Language-independent engineering principles. Stored in this repository first so the method can be tested against real work before being generalized to other projects.

## Purpose

Good code should be the implementation of a clear model, not an accumulation of local fixes.

The goal of this guide is to help us produce systems that are easier to understand, lighter, more stable, easier to test, and less likely to grow through brute-force special cases.

The guide is intentionally not about C++, GDScript, APIs, naming syntax, or style conventions. It is about how to reason about a technical problem before and while writing code.

---

## 1. Understand the System Before Changing It

Do not begin with the assumption that the observed symptom tells us where the real problem is.

Before changing behavior:

1. observe what actually happens;
2. identify the relevant native/existing mechanism;
3. separate confirmed facts from hypotheses;
4. determine which state or event actually owns the behavior;
5. only then decide where intervention belongs.

A logger, trace, controlled test, reference implementation, binary/source inspection, or minimal prototype is often more valuable than an early code change.

**Rule:** Research should reduce uncertainty before implementation adds complexity.

---

## 2. Solve the Invariant, Not Each Symptom

When several failures appear different, first ask whether they violate the same underlying rule.

Do not immediately create:

- one fix for interruption A;
- another for interruption B;
- another for weapon family C;
- another for state D.

Instead ask:

> What should always be true when this subsystem is correct?

Then try to enforce that invariant once.

### Current project example

Observed failures included block timeout, skipped Recover, Staff Whirl, Quick behavior, and stale collision after interruption.

A symptom-driven design tends toward separate cleanup rules for each case.

The stronger model is:

> If a real attack-Hit execution requested offensive collision, proper native cleanup must have occurred by the time that exact Hit execution actually ends or is replaced.

Different failure paths then become test cases for one rule rather than separate production mechanisms.

**Default:** universal rule first; evidence-proven exceptions second.

### 2.1 Simplicity Should Generate Necessary Complexity

Simplicity is not the objective by itself. A system should not become simpler by removing behavior that the domain genuinely requires.

> **Do not reduce complexity by stripping away necessary behavior. Reduce unnecessary rules by finding principles that generate the required behavior themselves.**

A strong architecture may produce rich, complicated, and highly adaptive behavior while remaining governed by a small set of authoritative rules.

> **A simple architecture is not one that produces simple behavior. A strong simple architecture can produce rich and complex behavior through the interaction and reuse of a small number of authoritative rules.**

This is one reason universal principles are valuable: their interaction can generate many correct outcomes without requiring those outcomes to be encoded one by one.

When evaluating a proposed abstraction, ask:

> When a new case appears, does the existing principle naturally answer it?

If yes, that is evidence that the abstraction is strong. If each new case requires another branch, flag, exception, timer, or subsystem, revisit the model before assuming the additional complexity is necessary.

**Rule:** seek generative simplicity, not simplicity for simplicity's sake.

---

## 3. Prefer the Smallest Sufficient Model

Do not track information merely because it is available or because an earlier prototype already tracks it.

For every state field, mask, cache, branch, timer, callback, or lookup table, ask:

> Does the final rule actually need this information?

If an execution-level fact is sufficient, do not maintain per-source state. If one authoritative engine event is sufficient, do not infer the same fact from several secondary signals.

Prefer:

`execution requested collision = true`

over a larger ownership structure if the larger structure adds no required behavior.

Use the more detailed model only when evidence proves the simpler one insufficient.

---

## 4. Separate Responsibilities Before Combining Logic

A subsystem often becomes complicated because several different questions are solved in the same mechanism.

Separate concepts such as:

- identification/acquisition;
- activation;
- authored behavior;
- lifetime ownership;
- cleanup;
- diagnostics;
- compatibility fallbacks.

One signal may be correct for acquisition but wrong for lifetime.

### Current project example

Native action/phase can be useful to establish that a real attack Hit has begun. The same action/phase values are not necessarily authoritative for the lifetime of that Hit after ownership has been established.

**Rule:** do not keep using a signal for a responsibility it was never proven to own.

### 4.1 Co-Locate Runtime Ownership, Separate Source Responsibilities

Sometimes two temporary capabilities must live in the same executable/module because they need the same low-level hook, patch point, transaction, connection, lock, device, or other exclusive runtime resource.

Do not force them into separate runtime modules if doing so creates hook conflicts, load-order dependence, duplicated ownership, or unsafe chaining.

But temporary co-location must not become architectural entanglement.

Prefer:

- one authoritative owner of the shared low-level resource;
- separate source modules for separate responsibilities;
- a small shared event/context interface between them;
- one-way dependencies where possible;
- diagnostics/observers that never become required for production behavior;
- build boundaries that allow temporary modules to be omitted later without rewriting the core system.

For example, a research DLL may contain:

```text
Main / Hook Bridge
    owns each engine hook once
        ↓
Collision Control
    owns behavior

Collision Diagnostics
    observes the same events
    never decides behavior
```

The collision module should not call into the logger to function correctly. The logger may observe shared events, but removing the logger must leave collision behavior unchanged.

When the research phase ends, a production build can exclude the diagnostic module or move the stable behavior into a new DLL/project with minimal structural change.

> **Design temporary integration around the future separation boundary.**

This principle applies beyond DLLs: test harnesses, telemetry, migration adapters, compatibility layers, experimental UIs, and temporary data collectors should be co-located when runtime ownership requires it, but structurally separated according to the responsibilities that will eventually diverge.

**Rule:** share runtime ownership when necessary; do not share responsibility unnecessarily.

---

## 5. Prefer Existing Native or High-Level Operations

Before recreating behavior manually, determine whether the engine/library/system already has an operation that expresses the intended semantic action.

Prefer:

> run the native attack cleanup

rather than:

> manually set several fields to values that appear to resemble cleanup

when the native operation is available and understood.

This reduces duplicated assumptions and preserves side effects we may not yet know about.

Use a lower-level reconstruction only when the higher-level operation is unavailable, unsafe, or too broad for the required context.

---

## 6. Preserve Native Behavior Until Ownership Is Intentional

Custom code should not replace behavior merely because it can.

If the existing system is correct for an unconfigured/unmarked/unsupported case, leave it alone.

A custom mechanism should have a clear ownership boundary:

- before ownership: native behavior remains authoritative;
- while owned: custom behavior changes only what it intentionally controls;
- after ownership: return to the correct native/safe lifecycle.

This reduces compatibility risk and keeps the custom system smaller.

---

## 7. Prefer Events and Authoritative Transitions Over Continuous Guessing

If a reliable event tells us that something happened, prefer that over repeated polling and inference.

Prefer:

- actual callback;
- actual state transition;
- actual collision request;
- actual motion end/replacement;

when available, rather than repeatedly asking every frame whether several indirect conditions suggest the same thing.

Polling is acceptable as a diagnostic or fallback when no stable event exists, but should not become the default architecture merely because it was easy to prototype.

---

## 8. Do Not Encode Failure Paths Unless the Failure Path Matters

If the correct response is identical regardless of why a state ended, the production code should not care why it ended.

For example, if the same cleanup is required after:

- normal completion;
- block timeout;
- damage interruption;
- terrain interruption;
- missing Recover;

then those should normally converge on one lifecycle boundary rather than five branches.

**Rule:** reasons belong in diagnostics and tests unless they genuinely change required behavior.

---

## 9. Main Plan First, Fallback Second

Design the simplest architecture that the evidence currently supports.

Then identify what evidence would invalidate it and define a fallback.

Do not implement both plans simultaneously "just in case."

### Example pattern

**Main plan:** execution-level cleanup guard.

**Fallback:** source-aware guard only if research proves cleanup can fail independently per source or no attack-wide native cleanup exists.

This preserves adaptability without paying the complexity cost before it is necessary.

---

## 10. Exceptions Must Be Earned by Evidence

An exception is justified when a real case cannot satisfy the general rule without incorrect behavior.

Do not add an exception because:

- a case looks unusual;
- the implementation is temporarily difficult;
- an old prototype already contains a branch;
- a speculative future case might exist.

When an exception is added, document:

1. which general rule it cannot follow;
2. the evidence proving that;
3. why the exception is the smallest safe deviation.

If exceptions multiply, revisit the model before adding more.

---

## 11. Complexity Is a Cost That Must Be Justified

Every additional:

- state variable;
- ownership record;
- source mask;
- timer;
- hook;
- cache;
- special-case branch;
- duplicated cleanup path

creates more interactions and more ways for the system to become inconsistent.

Complexity is acceptable when it represents real domain complexity. It is not acceptable merely because brute force can make the current test pass.

A useful warning sign is:

> We keep adding code but our explanation of the system is getting longer rather than clearer.

When this happens, stop and reconsider the model.

---

## 12. Make the Code Express the Model

A reviewer should be able to explain the important behavior in a small number of sentences and then recognize those concepts in the code.

If the design says:

> while a Hit is alive, markers define the desired offensive collision set

then the implementation should resemble that idea rather than a matrix of previous-marker combinations.

Prefer conceptual operations such as:

`SetDesiredOffensiveCollisionSet(RIGHT)`

rather than separate logic for:

- RIGHT after LEFT;
- RIGHT after BOTH;
- RIGHT after OFF;
- RIGHT after RIGHT;

unless those cases genuinely require different behavior.

---

## 13. Temporary Prototype Scaffolding Is Not Architecture

Diagnostics and prototypes often need extra state or guards to answer a question safely.

Do not assume those mechanisms belong in production merely because they were useful during research.

When the model becomes clearer:

1. identify temporary scaffolding;
2. mark it for review;
3. prove the replacement;
4. remove obsolete machinery rather than layering the new system on top of it.

A successful prototype may teach us what the final code should **delete**, not only what it should keep.

---

## 14. Preserve Proven Paths While Testing New Ideas

Do not rewrite unrelated working behavior during an uncertain experiment.

Prefer:

1. one hypothesis;
2. one bounded change or diagnostic;
3. controlled test;
4. interpret evidence;
5. retain or revert;
6. expand only after the narrow result is understood.

This keeps causality visible and rollback practical.

---

## 15. Test the General Rule Across Different Cases

Once a universal principle is proposed, tests should try to break the principle rather than merely repeat the case that inspired it.

Test across:

- normal success paths;
- different input families/types;
- rapid transitions;
- interruptions;
- boundary timing;
- multiple actors/sources where relevant;
- known historical failures.

The purpose is not to create separate code for every test. The purpose is to establish whether the same invariant survives them all.

---

## 16. Distinguish Observation, Interpretation, and Decision

Keep these separate:

**Observation:** what the logs/source/runtime actually show.

**Interpretation:** the current explanation that best fits those observations.

**Decision:** the architecture or implementation we choose based on that interpretation.

A decision can change without invalidating the observation. An interpretation can be revised when new evidence arrives.

This prevents temporary theories from becoming permanent code assumptions unnoticed.

---

## 17. Implementation Problems May Require Returning to Design

If implementation reveals that the agreed architecture cannot be expressed cleanly, do not automatically patch around the difficulty.

First determine whether:

- the engine/API contradicts an assumption;
- a required operation does not exist;
- the selected ownership boundary is wrong;
- the model needs one justified exception;
- or the implementation approach itself is simply wrong.

A coding agent may challenge the plan, but should not silently redesign the architecture through accumulated compensating code.

When implementation exposes a conceptual problem, return the problem to design/research before adding a chain of workarounds.

---

## 18. Optimize for Clarity and Correctness Before Cleverness

A short solution is not automatically simple, and a complex implementation is not automatically sophisticated.

Prefer code whose behavior is predictable from a few explicit principles.

Avoid clever compression that hides ownership or lifecycle rules. Avoid brute-force expansion that encodes every observed scenario separately.

The target is **conceptual simplicity with sufficient implementation detail**.

---

## 19. Document Why a Mechanism Exists

Important code should preserve the reason for unusual behavior, not merely describe what a line does.

Especially document:

- engine quirks;
- proven invariants;
- intentional deviations from native behavior;
- compatibility constraints;
- evidence-backed exceptions;
- temporary scaffolding scheduled for removal.

This helps future work distinguish architectural necessity from historical accident.

---

## 20. Revisit the Model When the Code Starts Growing Sideways

Before adding another special case, ask:

1. Is this genuinely a new behavior requirement?
2. Or is it another symptom of the same underlying lifecycle/ownership problem?
3. Can a more authoritative signal remove existing branches?
4. Can one invariant replace several fixes?
5. Are we preserving temporary prototype logic that the new model makes obsolete?

If several exceptions appear in a short period, pause implementation and perform a design review.

---
