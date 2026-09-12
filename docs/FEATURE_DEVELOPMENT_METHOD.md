# Feature Development Method

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-wide engineering methodology  
**Version:** 1.0  
**Updated:** 2026-09-12

## Purpose

Define how new behavior is researched, tested, and promoted into production so the mod stays modular and proven subsystems do not have to be redesigned merely because research scaffolding was placed in the wrong module.

This method applies to **all future behavior/features**, not only collision work.

It complements:

- `ENGINEERING_GUIDE.md` — general engineering principles;
- `WORK_IMPLEMENTATION_PROTOCOL.md` — bounded Work execution;
- feature-specific design/evidence authorities — exact semantics of the feature being built.

`SESSION_ENTRYPOINT.md` must keep the short mandatory form of this rule visible to every fresh project context.

---

## 1. Governing Principle

> **Research architecture should already point toward production architecture. Experimental uncertainty must be isolated so proving a feature makes final implementation easier, not so entangled that stable modules must later be ripped apart.**

A stable module must not become the place where unknown behavior is explored merely because its hook or data is convenient.

The difficult research history belongs in evidence and temporary probe modules. The final runtime architecture should contain only the responsibilities the finished feature actually needs.

---

## 2. Stable Module Boundary

Every permanent module should have one understandable responsibility.

In particular:

```text
Bridge / hook-owner module
= owns low-level engine hooks exactly once
= captures native facts
= translates hook transport into stable project interfaces
= delegates

Bridge / hook-owner module
!= feature policy
!= experimental state machine
!= causal probe implementation
!= convenient storage for behavior that has no owner yet
```

When several features need the same physical hook, preserve one authoritative hook owner. Share transport; do not merge feature responsibilities.

A stable feature module may receive an extension only when evidence already establishes that the new case uses the **same mechanism and ownership model**. Example: a newly proven attack family using the already-established raw8 Fist mechanism can extend `Raw8FistCollision`; an unknown `PhysicalFist/raw55` mechanism cannot be assumed to belong there.

---

## 3. Unknown Mechanism -> Isolated Probe

When runtime evidence reveals a new mechanism, classification, lifecycle, or feature whose production behavior is not yet known:

1. **do not implement the experiment in the bridge;**
2. **do not put it into an existing production feature module merely because the names are related;**
3. create a narrow temporary probe/test module when behavior intervention is required;
4. compile the probe only into the diagnostic/research target whenever practical;
5. let the bridge expose only the smallest transport/delegation seam required by the probe;
6. keep experiment-only state, causal interventions, logging, and hypotheses inside the probe.

Suggested naming pattern:

```text
<Feature>Probe.cpp/.h
<Feature>Research.cpp/.h
```

The exact name is secondary. The important property is that the module is obviously temporary and removable.

Diagnostic observation that requires no behavior intervention may stay in the existing diagnostic module. Once an experiment changes runtime behavior, its feature policy belongs in the isolated probe rather than the logger or bridge.

---

## 4. One Causal Question Per Probe Step

Research should answer the smallest decision needed for production.

Prefer:

```text
one factual hypothesis
-> one bounded intervention
-> one positive/negative control set
-> interpret result
-> retain, revise, or revert
```

Do not simultaneously test source resolution, callback suppression, replacement activation, cleanup repair, target semantics, and compatibility unless they are mechanically inseparable.

A failed hypothesis should be cheap to remove because the experiment did not contaminate stable modules.

---

## 5. Promotion to Production

A successful probe is **evidence**, not production architecture.

Before production implementation:

1. freeze the factual mechanism and intended semantics;
2. identify the permanent responsibility owner;
3. create a dedicated permanent feature module when the responsibility is genuinely new;
4. extend an existing module only when the mechanism is proven to be the same responsibility;
5. move/rewrite only the minimal proven behavior needed by production;
6. remove experiment-only branches, state, logs, guards, and scaffolding;
7. keep the bridge limited to the smallest permanent delegation/transport seam;
8. ensure diagnostics are not required for release behavior to work.

Do **not** promote a temporary probe wholesale merely because it passed. Re-express the proven result as the minimum sufficient production design.

Typical transition:

```text
<Feature>Probe
    temporary causal intervention
    temporary state / rich diagnostics
        ↓ mechanism proven
freeze production contract
        ↓
<Feature>Collision / <Feature>Behavior / other permanent owner
    minimal production responsibility
        ↓
remove <Feature>Probe
```

---

## 6. Validation Sequencing

Tests intended to certify the final product should test the product we actually intend to ship.

Therefore:

- discovery tests may use temporary probes;
- focused acceptance tests validate a newly implemented production mechanism;
- **broad/final regression must wait until known scope-changing design decisions are resolved**;
- if broad validation discovers a new relevant mechanism, pause that validation sequence, classify the discovery, decide whether to reject/defer or implement it, and only then resume certification;
- if the new mechanism is implemented, prior tests remain useful evidence for the unchanged areas but do not by themselves certify the newly changed final assembly.

> **Do not finish the test matrix and then materially change the product those tests were supposed to certify.**

This does not mean every speculative future idea blocks testing. Only concrete factual discoveries or already-decided scope changes that materially affect the candidate product do.

---

## 7. Production Stability Rules

A new feature should normally preserve these properties:

```text
unconfigured / unmarked / unsupported case -> native behavior
proven existing modules                    -> unchanged unless responsibility requires otherwise
new behavior                               -> narrow factual ownership gate
native target/contact/damage               -> preserved unless feature explicitly owns it
one physical hook owner                    -> preserved
experiment-only diagnostics                -> mechanically absent from production
```

Avoid species/name special cases, animation-name inference, polling, custom damage, duplicated cleanup systems, or new hooks unless evidence proves the general mechanism cannot express the required behavior without them.

Performance should be judged by the final mechanism, not by the amount of research instrumentation temporarily used to discover it.

---

## 8. Module Placement Decision

Before adding behavior, answer in order:

```text
1. Is this only observation?
   -> diagnostic module.

2. Is this an experiment whose mechanism/ownership is still uncertain?
   -> isolated temporary probe module.

3. Is this proven to be the same mechanism/responsibility as an existing feature?
   -> extend that feature module narrowly.

4. Is this a new proven permanent responsibility?
   -> create/assign a dedicated production module.

5. Does it need an engine hook already owned by the bridge?
   -> bridge keeps hook ownership; feature/probe receives a small delegation seam.
```

If the answer is unclear, return to design rather than placing the logic in the bridge as a default.

---

## 9. Review Checklist Before a Feature Becomes Permanent

Normal Chat / design review should be able to answer:

1. What factual native mechanism did the probe establish?
2. What exact behavior does the mod intentionally own?
3. What remains native?
4. Which permanent module owns the new responsibility?
5. Is the bridge still transport-only?
6. Can the temporary probe be deleted completely?
7. Did experiment-only state or diagnostics leak into production?
8. Are existing stable feature modules unchanged unless their responsibility genuinely expanded?
9. Does the production implementation contain only evidence-backed complexity?
10. Are broad/final tests being run **after** this production candidate exists?

If the probe cannot be deleted without breaking the production behavior, the promotion is incomplete.

---

## 10. Work / Normal Chat Boundary

Normal Chat + User own open-ended mechanism research, evidence interpretation, architecture, and the decision whether a probe graduates into production.

Work may implement a **frozen probe task** or a **frozen production task**, but it must not silently convert one into the other.

For a frozen probe task:

```text
implement only the isolated diagnostic experiment
preserve production modules
publish evidence-capable diagnostic source
STOP for local runtime result
```

For a frozen production task:

```text
implement only the already-proven permanent responsibility
remove/avoid research scaffolding as required by the contract
source/static audit
publish
STOP for independent review/build/runtime validation
```

`WORK_IMPLEMENTATION_PROTOCOL.md` provides the execution rules.

---

## Core Rule

> **Unknown behavior is researched in an isolated probe, proven behavior is implemented in the module that truly owns it, hooks remain transport-only, temporary scaffolding is deleted rather than normalized, and final validation certifies the finished candidate rather than an earlier experimental architecture.**
