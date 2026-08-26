# Work Implementation Protocol

**Status:** Active project protocol / living document  
**Version:** 0.2  
**Updated:** 2026-08-26

## Purpose

This protocol translates the project's engineering principles into concrete rules for a coding/Work session.

A coding session is not asked to rediscover the architecture by brute force. Its job is to implement an already-reasoned design faithfully, test it, and report when engine/API evidence contradicts that design.

The protocol exists because phrases such as "keep it simple" are too ambiguous by themselves. Simplicity here means principle-first, resource-efficient, behavior-preserving engineering — not merely fewer lines of code.

---

## 1. Preserve Behavior Integrity

**Behavior integrity** means that behavior outside the explicitly targeted change remains semantically unchanged.

A refactor, module split, logger redesign, cleanup rewrite, or hook reorganization must preserve all already-validated behavior unless the current task explicitly says otherwise.

For every change distinguish:

- **target behavior** — what is intentionally changing;
- **protected behavior** — what is already proven and must remain unchanged;
- **diagnostic behavior** — observation only, never required for production correctness;
- **provisional scaffolding** — temporary mechanisms that may later be removed after their replacement is proven.

Structural improvement is not permission to redesign runtime behavior.

**Rule:** when the requested step is structural, prove behavior parity before adding new behavior.

---

## 2. Restate the Governing Principles Before Coding

Before a non-trivial implementation, identify the smallest set of principles the code is supposed to express.

For the current collision work these include:

1. While a marked Hit is alive, the current marker defines the desired offensive collision set.
2. At actual Hit end/replacement, offensive attack collision must be clean.
3. Prefer one execution-level native cleanup guard; use source-aware cleanup only if evidence proves it necessary.
4. Marked and native attacks should differ primarily in activation timing, not in the general cleanup invariant.
5. Actual motion execution is the preferred lifetime authority after acquisition; action/phase remain useful context, not continuing lifetime authority.

If the proposed code cannot be explained as a direct implementation of these principles, stop and review the design before adding machinery.

---

## 3. One Runtime Owner, Modular Responsibilities

When collision behavior and diagnostics need the same Gothic 3 hook, keep one authoritative hook owner in the research DLL.

Separate responsibilities at source level:

```text
Main / Hook Bridge
    owns each engine hook once
        ├──> Collision Control
        └──> Collision Diagnostics
```

Rules:

- install each overlapping engine hook once;
- behavior code must not require the diagnostic module;
- diagnostics observe shared facts/events and never decide behavior;
- shared headers/interfaces should contain only facts genuinely needed by both sides;
- design the temporary combined DLL around the future separation boundary.

Removing diagnostics from a later production build must not require redesigning collision behavior.

---

## 4. Use the Smallest Sufficient Model

Do not add state, masks, caches, timers, scans, helper layers, or branches merely because they are available or already exist in the prototype.

Before adding any persistent state ask:

> What decision requires this state, and can that decision be derived from a more authoritative existing fact or event?

Prefer one authoritative fact over several inferred proxies.

Do not preserve old prototype bookkeeping merely because removing it would require thought. Prototype scaffolding must justify its continued existence under the new model.

---

## 5. Find Universal Rules Before Local Fixes

Do not create separate production solutions for Quick, Whirl, Staff, block timeout, missing Recover, damage interruption, terrain interruption, or other observed failure paths unless evidence proves the general rule cannot cover them.

Treat those as test cases first.

Before adding an exception ask:

1. Does this case truly require different correct behavior?
2. Or is it another manifestation of the same ownership/lifecycle invariant?
3. Can a more authoritative event or abstraction eliminate multiple branches?

**Rule:** exceptions are evidence-backed deviations, not the default implementation method.

---

## 6. Use Resources Deliberately

More compute, memory, context, code-generation capacity, tool access, or development time does not justify unnecessary complexity.

Use resources where they buy real capability:

- correctness;
- robustness;
- observability;
- compatibility;
- maintainability;
- adaptability;
- meaningful performance or functionality.

Do not substitute broad scans, repeated polling, duplicate state, large rewrites, or many special cases for a better model when a simpler authoritative solution may exist.

**Rule:** resource abundance raises what we can achieve; it does not lower the standard for efficient architecture.

---

## 7. Implementation Problems Are Design Feedback

If the agreed architecture becomes awkward to implement, do not silently compensate with a chain of workarounds.

First classify the problem:

- engine/API contradicts an assumption;
- required native operation does not exist;
- chosen hook cannot provide the required event;
- ownership/lifetime boundary is wrong;
- one real exception is needed;
- current implementation approach is wrong but the design remains sound.

If the issue is architectural, report it and return to design/research.

A coding session may challenge the plan with evidence. It must not silently replace the plan with accumulated compensating code.

---

## 8. Change One Conceptual Variable at a Time

Prefer this cycle:

```text
agreed hypothesis/design
        ↓
one bounded code change
        ↓
build
        ↓
controlled test
        ↓
evidence
        ↓
keep / revise / revert
```

Avoid mixing structural refactor, new diagnostics, new cleanup behavior, and broad code cleanup in one step unless they are inseparable.

This preserves causal understanding and makes rollback practical.

---

## 9. Current Collision Redesign Sequence

The next versions should proceed in this order.

### Step A — Modularize v0.20 with behavior parity

Restructure the existing `Script_FrameCollisionTest` research DLL into modular source files while preserving current behavior.

Target responsibility split:

- Main / Hook Bridge — hook installation and dispatch;
- `CollisionControl.cpp` — collision behavior;
- `CollisionDiagnostics.cpp` — observational diagnostics;
- minimal shared headers/interfaces where needed.

Do not redesign collision semantics in this step.

Acceptance criterion:

> The modularized DLL builds and reproduces the already-validated v0.20 behavior and diagnostics.

### Step B — Redesign diagnostics around lifecycle questions

Only after Step A parity:

- add high-resolution/event-oriented lifecycle logging;
- capture offensive collision requests including `7 -> 7`;
- capture exact actual Hit execution/lifetime evidence;
- capture native cleanup evidence/path where available;
- add attacker/defender block/parade context only when required by the planned tests.

Do not add production cleanup.

### Step C — Validate the logger on minimal known cases

First prove the diagnostics can show:

```text
clean execution:
Hit X acquired
→ offensive collision requested
→ native cleanup observed
→ actual Hit ends/replaces
```

and:

```text
stale execution:
Hit Y acquired
→ offensive collision requested
→ actual Hit ends/replaces
→ no corresponding cleanup
→ offensive collision remains active
```

If the timeline is ambiguous, improve diagnostics before broad tests.

### Step D — Run the staged research tests

Follow `docs/COLLISION_TEST_PLAN.md`.

Use tests to challenge the universal model, not to generate one code branch per test case.

### Step E — Choose cleanup architecture from evidence

Prefer System 1 if an attack-wide native cleanup guard is sufficient.

Use System 2 only if source-specific/partial cleanup is proven necessary.

### Step F — Implement production cleanup only after the model is chosen

At this stage remove/replace provisional v0.20 cleanup/lifetime scaffolding made obsolete by the proven model.

Do not layer the final guard on top of unnecessary historical contingencies.

### Step G — Extract the production collision DLL

Once behavior is stable and broadly tested:

- keep the stable hook/behavior modules;
- omit research diagnostics;
- create the final frame-based/attack-collision production DLL;
- preserve the validated architecture rather than rewriting it during extraction.

---

## 10. Stop Conditions

Pause implementation and report back instead of adding more code when any of these occur:

- two or more new special-case branches are being added to solve what was intended as one universal rule;
- a structural refactor unexpectedly changes runtime behavior;
- diagnostics become necessary for collision behavior to work;
- the same engine fact is being tracked in several independent ways without proven need;
- polling/scanning is being introduced where a plausible authoritative event may exist but has not been investigated;
- the implementation requires preserving provisional state whose purpose can no longer be explained;
- hook ownership becomes duplicated or load-order dependent;
- the code becomes harder to explain in principle-level terms after the change.

These are design-review triggers, not invitations to brute-force through the difficulty.

---

## 11. Required Handoff From a Coding Session

After each meaningful step report:

1. what changed;
2. which governing principle it implements;
3. which behavior was intentionally preserved;
4. what was tested and what evidence was observed;
5. what provisional code remains and why;
6. whether any engine/API finding challenges the current architecture;
7. the smallest justified next step.

Do not claim architectural success merely because the DLL compiles or one reproduction passes.

---

## 12. Read Order for Current Work

Before changing the collision research DLL, read:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
3. `docs/ENGINEERING_GUIDE.md`
4. `docs/COLLISION_LIFECYCLE_PLAN.md`
5. `docs/COLLISION_LOGGER_PLAN.md`
6. `docs/COLLISION_TEST_PLAN.md`
7. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
8. `prototypes/Script_FrameCollisionTest/CMakeLists.txt`
9. `docs/SOURCE_HOOK_GUIDE.md` only as needed.

Deeper evidence should be opened only when the current question requires it. `docs/README.md` explains the role and authority of the broader documentation set.

---

## Core Rule

> **Implement principles, not accumulated symptoms. Preserve behavior integrity, use resources deliberately, keep responsibilities separable, and return to design whenever the code begins to grow beyond what the governing model can explain.**
