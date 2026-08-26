# Work Implementation Protocol

**Status:** Active project protocol / living document  
**Version:** 0.3  
**Updated:** 2026-08-26

## Purpose

This protocol translates the project's engineering principles into concrete rules for a coding/Work session.

A Work session is not asked to rediscover the architecture by brute force. Its normal job is to implement one already-reasoned, bounded source change faithfully, perform the source-level review needed for that change, commit/push it, report what remains unverified, and stop.

The broader engineering loop normally belongs to Chat plus the user's authoritative Gothic 3 development machine: architecture, planning, build/test instructions, runtime testing, log interpretation, evidence updates, documentation, and deciding the next code change.

This division exists because phrases such as "keep it simple" are too ambiguous by themselves and because expensive agentic coding capacity should be spent where it adds real value. It is a default, not an absolute prohibition: a Work session may build/test when explicitly requested and when that execution is genuinely needed to resolve the coding task.

---

## 1. Default Chat / Work Division

Use the following loop unless a specific task justifies a different split:

```text
Chat / design
    ↓
reason from evidence
freeze the smallest next code task
    ↓
Work
    ↓
implement only that bounded code task
source-level review
commit / push
STOP
    ↓
Chat + authoritative local environment
    ↓
sync
build
runtime test
interpret logs/evidence
update documentation
choose next change
    ↓
next bounded Work task only if code changes are needed
```

### Chat normally owns

- architecture and design;
- hypothesis formation and test design;
- deciding what Work is allowed to change;
- build/test commands and local synchronization instructions;
- interpretation of compiler output and runtime logs supplied by the user;
- evidence classification;
- documentation and repository continuity;
- deciding whether another code change is needed.

### Work normally owns

- the explicitly scoped source implementation/refactor;
- targeted source/API inspection necessary to implement that task;
- source-level parity/review;
- CMake/source-list changes required by the code change;
- committing and pushing the bounded implementation;
- reporting uncertainties or contradictions instead of silently expanding scope.

### Work does not automatically own

- broad architecture redesign;
- large repository/document review;
- routine build verification;
- runtime testing;
- log interpretation;
- documentation consolidation;
- planning the next several implementation steps.

Those activities may be assigned to Work explicitly when they materially benefit from its environment, but they are not the default use of Work capacity.

**Rule:** use Work primarily to change code, not to replace the rest of the engineering process.

---

## 2. Preserve Behavior Integrity

**Behavior integrity** means that behavior outside the explicitly targeted change remains semantically unchanged.

For every change distinguish:

- **target behavior** — what is intentionally changing;
- **protected behavior** — what is already proven and must remain unchanged;
- **diagnostic behavior** — observation only, never required for production correctness;
- **provisional scaffolding** — temporary mechanisms that may later be removed after their replacement is proven.

Structural improvement is not permission to redesign runtime behavior.

**Rule:** when the requested step is structural, preserve behavior first and validate parity before adding new behavior.

---

## 3. Restate the Governing Principles Before Coding

Before a non-trivial implementation, identify the smallest set of principles the code is supposed to express.

For the current collision work these include:

1. While a marked Hit is alive, the current marker defines the desired offensive collision set.
2. At actual Hit end/replacement, offensive attack collision must be clean.
3. Prefer one execution-level native cleanup guard; use source-aware cleanup only if evidence proves it necessary.
4. Marked and native attacks should differ primarily in activation timing, not in the general cleanup invariant.
5. Actual motion execution is the preferred lifetime authority after acquisition; action/phase remain useful context, not continuing lifetime authority.

If the proposed code cannot be explained as a direct implementation of the governing principles, stop and return the problem to design rather than adding machinery.

---

## 4. One Runtime Owner, Modular Responsibilities

When collision behavior and diagnostics need the same Gothic 3 hook, keep one authoritative hook owner in the research DLL.

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
- design temporary integration around the future separation boundary.

Removing diagnostics from a later production build must not require redesigning collision behavior.

---

## 5. Use the Smallest Sufficient Model

Do not add state, masks, caches, timers, scans, helper layers, or branches merely because they are available or already exist in the prototype.

Before adding persistent state ask:

> What decision requires this state, and can that decision be derived from a more authoritative existing fact or event?

Prefer one authoritative fact over several inferred proxies.

Do not preserve old prototype bookkeeping merely because removing it would require thought. Prototype scaffolding must justify its continued existence under the new model.

---

## 6. Find Universal Rules Before Local Fixes

Do not create separate production solutions for Quick, Whirl, Staff, block timeout, missing Recover, damage interruption, terrain interruption, or other observed failure paths unless evidence proves the general rule cannot cover them.

Treat those as test cases first.

Before adding an exception ask:

1. Does this case truly require different correct behavior?
2. Or is it another manifestation of the same ownership/lifecycle invariant?
3. Can a more authoritative event or abstraction eliminate multiple branches?

**Rule:** exceptions are evidence-backed deviations, not the default implementation method.

---

## 7. Use Resources Deliberately

More compute, memory, context, code-generation capacity, tool access, or development time does not justify unnecessary complexity.

Use resources where they buy real capability: correctness, robustness, observability, compatibility, maintainability, adaptability, or meaningful functionality/performance.

Do not substitute broad scans, repeated polling, duplicate state, large rewrites, many special cases, or unnecessary agentic work for a better model or a cheaper reliable step.

**Rule:** resource abundance raises what we can achieve; it does not lower the standard for efficient architecture.

---

## 8. Implementation Problems Are Design Feedback

If the agreed architecture becomes awkward to implement, do not silently compensate with a chain of workarounds.

First classify the problem:

- engine/API contradicts an assumption;
- required native operation does not exist;
- chosen hook cannot provide the required event;
- ownership/lifetime boundary is wrong;
- one real exception is needed;
- current implementation approach is wrong but the design remains sound.

If the issue is architectural, report it and return to Chat/design.

A coding session may challenge the plan with evidence. It must not silently replace the plan with accumulated compensating code.

---

## 9. Change One Conceptual Variable at a Time

Prefer:

```text
agreed design / hypothesis
        ↓
one bounded code change in Work
        ↓
commit / push / stop
        ↓
build + controlled test outside Work by default
        ↓
evidence interpreted in Chat
        ↓
keep / revise / revert
```

Avoid mixing structural refactor, new diagnostics, new cleanup behavior, broad cleanup, build investigation, and test interpretation in one Work task unless they are genuinely inseparable.

---

## 10. Current Collision Redesign Sequence

### Step A — Modularize v0.20 with behavior parity

Source modularization was completed and pushed at commit:

`325c98e725502229bf796083e52c0fa977803cc0`

The source now separates hook/bootstrap, collision control, diagnostics, shared structures, and runtime timing while keeping one research DLL/hook owner.

**Status:** source-level Step A complete; build/runtime parity is still unverified until the authoritative home-PC environment builds and tests it.

Do not begin Step B merely because the source refactor is committed. First complete the local parity gate.

### Step A parity gate — outside Work by default

On the authoritative Gothic 3 development PC:

1. synchronize the branch;
2. configure/build the existing `Script_FrameCollisionTest` target;
3. resolve compile/link issues if any through the smallest bounded code task;
4. confirm the DLL loads;
5. run focused parity tests against already-validated v0.20 behavior/diagnostics;
6. interpret evidence in Chat;
7. record the result before proceeding.

If a compile issue requires code changes, return only that bounded fix to Work (or make a small direct change through the normal repository workflow if appropriate). Do not reopen the entire refactor automatically.

### Step B — Redesign diagnostics around lifecycle questions

Only after Step A parity:

- add event-oriented lifecycle logging;
- capture offensive collision requests including `7 -> 7`;
- capture exact actual Hit execution/lifetime evidence;
- capture native cleanup evidence/path where available;
- add attacker/defender block/parade context only when required by planned tests.

Do not add production cleanup.

### Step C — Validate diagnostics on minimal known cases

First prove the diagnostics can express one clean lifecycle and one stale lifecycle unambiguously. If not, improve diagnostics before broad tests.

### Step D — Run the staged research tests

Follow `docs/COLLISION_TEST_PLAN.md` in Chat/local testing. Use tests to challenge the universal model, not to generate one code branch per test case.

### Step E — Choose cleanup architecture from evidence

Prefer System 1 if an attack-wide native cleanup guard is sufficient. Use System 2 only if source-specific/partial cleanup is proven necessary.

### Step F — Implement production cleanup

Return to Work with one bounded implementation task after the model is chosen. Remove/replace obsolete prototype scaffolding rather than layering the final guard over historical contingencies.

### Step G — Extract the production collision DLL

Once behavior is stable and broadly tested, keep stable behavior/hook modules, omit research diagnostics, and create the final production DLL without rewriting the validated architecture.

---

## 11. Stop Conditions

Pause implementation and report back instead of adding more code when any of these occur:

- two or more new special-case branches are being added to solve what was intended as one universal rule;
- a structural refactor unexpectedly changes behavior;
- diagnostics become necessary for collision behavior to work;
- the same engine fact is tracked independently in several ways without proven need;
- polling/scanning is introduced before a plausible authoritative event is investigated;
- provisional state can no longer be explained;
- hook ownership becomes duplicated or load-order dependent;
- the code becomes harder to explain in principle-level terms;
- the bounded task starts expanding into build/test/log-analysis/documentation work without explicit need.

These are design-review triggers, not invitations to brute-force through the difficulty.

---

## 12. Required Handoff From Work

After each bounded code task report:

1. files changed/created;
2. responsibility of each affected module;
3. hook ownership if relevant;
4. governing principle implemented;
5. behavior intended to remain unchanged;
6. source-level checks performed;
7. anything that remains unverified without build/runtime testing;
8. any engine/API finding that challenges the design;
9. commit SHA.

Then stop unless the user explicitly assigns another code task.

Do not claim architectural or runtime success merely because the source looks correct or a commit exists.

---

## 13. Read Order for Current Collision Coding

Before changing the collision research DLL, read:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
3. `docs/ENGINEERING_GUIDE.md`
4. `docs/COLLISION_LIFECYCLE_PLAN.md`
5. the specific plan for the bounded task (`COLLISION_LOGGER_PLAN.md`, later cleanup plan, etc.)
6. only the relevant source files
7. `docs/SOURCE_HOOK_GUIDE.md` only as needed.

Deeper evidence should be opened only when the task actually requires it. `docs/README.md` explains the role and authority of the broader documentation set.

---

## Core Rule

> **Implement principles, not accumulated symptoms. Use Work for bounded code changes, preserve behavior integrity, use resources deliberately, keep responsibilities separable, and return evidence/design/test interpretation to Chat rather than expanding the coding task by default.**
