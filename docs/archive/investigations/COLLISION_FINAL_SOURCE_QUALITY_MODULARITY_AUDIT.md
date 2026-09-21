# Gothic 3 — Final Collision Source Quality / Modularity Audit

**Status:** CLOSED — READ-ONLY AUDIT COMPLETE / NORMAL CHAT DISPOSITION RECORDED  
**Opened:** 2026-09-21  
**Source candidate under review:** `7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd`  
**Latest diagnostic smoke:** EV-355 PASS  
**Latest diagnostics-free behavior smoke:** EV-356 PASS  
**Implementation/source changes:** PROHIBITED  
**Build execution:** PROHIBITED

## 1. Purpose

Perform one final architecture/source-quality audit of the standalone collision implementation **before** the expensive focused acceptance and remaining full collision regression.

This audit exists because the collision system has passed causal research, permanent promotion, independent static review, both-twin build, broad diagnostic smoke and diagnostics-free behavior smoke. The objective now is to identify any **justified structural cleanup that should happen before the source candidate is treated as frozen for full validation**.

This is not a redesign task and not a generic style review.

The audit must protect the project's established principles:

- one physical hook owner inside the DLL;
- `EngineBridge` transports native facts/delegates but does not own feature policy/state machines;
- behavior modules own their own proven policy/state;
- diagnostics remain mechanically removable from behavior;
- feature modules should be independently removable where practical;
- temporary research scaffolding must not survive promotion without a current purpose;
- duplicated responsibility and dead/stale compatibility code should not remain merely because it once helped research;
- defensive checks are justified when they protect a proven engine/lifetime invariant, but speculative or redundant defensive layers are not automatically desirable;
- abstraction is earned by real shared responsibility, not by line-count reduction;
- native fallback and proven generation/source/latch safety must not be weakened for cosmetic simplification.

## 2. POP-10 formal-audit preflight — mandatory before findings

The audit has not started until Work explicitly performs POP-10.

Read/confirm first:

1. `docs/README.md` §0 Project Charter;
2. `docs/PROJECT_OPERATING_PROCEDURES.md` POP-10;
3. `docs/DESIGN.md` current collision architecture, especially hook/module ownership;
4. `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`;
5. `docs/COLLISION_REFERENCE.md`;
6. `docs/COLLISION_LIFECYCLE.md`;
7. `docs/COLLISION_DIAGNOSTICS.md`;
8. `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`;
9. `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`;
10. `docs/FEATURE_DEVELOPMENT_METHOD.md`;
11. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
12. this audit contract.

Then state, before evaluating source:

```text
governing hierarchy
review scope
intended owner/purpose of each major source module
higher-level behavior/release intent that must be preserved
what this audit is not authorized to redefine
```

If that preflight cannot be stated coherently, STOP and report the ownership/authority contradiction.

## 3. Source scope

Primary audit scope is the current standalone collision target:

```text
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp

prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/EngineBridge.h

prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h
prototypes/Script_FrameCollisionTest/FrameCollisionShared.h

prototypes/Script_FrameCollisionTest/CollisionSources.cpp
prototypes/Script_FrameCollisionTest/CollisionSources.h
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.h
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.h

prototypes/Script_FrameCollisionTest/EquippedSprintCollision.cpp
prototypes/Script_FrameCollisionTest/EquippedSprintCollision.h
prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
prototypes/Script_FrameCollisionTest/Raw8FistCollision.h
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.h
prototypes/Script_FrameCollisionTest/AttackMotionRouting.cpp
prototypes/Script_FrameCollisionTest/AttackMotionRouting.h
prototypes/Script_FrameCollisionTest/RuntimeClock.cpp
prototypes/Script_FrameCollisionTest/RuntimeClock.h

prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/CollisionDiagnosticsDeep.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnosticsDeep.h
```

Do not broaden into unrelated future modules, tooling, historical probes, SDK internals or final production migration implementation unless a concrete dependency in this exact target makes it necessary.

Historical evidence/source may be consulted only to decide whether suspicious code is evidence-backed. Do not reconstruct the entire research chronology by default.

## 4. Intended module responsibilities

Use the owning architecture as authority, not filename aesthetics.

### `EngineBridge`

Intended responsibility:

```text
sole physical Gothic hook/call-site owner
native fact capture / invocation transport
delegation into feature owners
native original-call sequencing
```

It must not become:

```text
raw8/raw55/equipped feature state machine
collision policy owner
research-probe policy owner
generic dumping ground for convenient cross-feature logic
```

### `FrameCollisionMarkers`

Intended responsibility:

```text
exact current-motion ownership
action/phase marker-family resolution
generic equipped RIGHT/LEFT/BOTH/OFF semantics
marker occurrence bookkeeping
production FIST dispatch into proven feature owner(s)
```

### `CollisionSources`

Factual source identity / UseType resolution.

### `CollisionSourceOperations`

Physical source mutation primitives, including equipped activation/rearm and exact terminal deactivation/repair mutation.

### `CollisionLifecycleGuard`

Generic C1 execution/source obligations, finalization and backup repair decision/classification. It must not own raw8/raw55/equipped feature policy.

### `EquippedSprintCollision`

Permanent factual equipped-Sprint eligibility, immutable Sprint-origin identity and exact same-C1 Action9 -> Action2 continuation authorization into generic equipped marker semantics.

### `Raw8FistCollision`

Sole raw8 marker behavior/state owner: marked execution, latch/timing permission, persistent authored opportunity, miss rearm, exact contact consumption and generation-safe finalization.

### `PhysicalFistCollision`

Sole permanent raw55 feature owner: supported family eligibility/state, selective early native-opening suppression, authored FIST activation/rearm, Normal native-clear suppression and Sprint-origin continuation.

### `AttackMotionRouting`

Narrow proven factual optional motion-substitution policy.

### `RuntimeClock`

Small shared runtime time source only.

### Diagnostics

`CollisionDiagnostics*` observe/prove behavior. They must not be behavior prerequisites. CORE and DEEP should not recreate feature policy/state ownership.

### CMake / target root

Must preserve one shared behavior source set for both twins, with diagnostics added only to the diagnostic target. No stale probe/source dependency should remain.

## 5. Required audit questions

### A. Hook ownership and bridge purity

For every physical hook/call-site interception in `EngineBridge`:

- identify its factual purpose;
- identify the permanent owner it delegates to;
- flag feature policy/state remaining in the bridge;
- flag duplicate physical ownership elsewhere;
- flag behavior hooks that exist only because old diagnostics once needed them;
- separately recognize hooks now proven behavior-required even if first discovered through diagnostics.

Do **not** recommend moving hook-invocation lifetime/transport state out of the bridge merely to make the file smaller when that state is genuinely transport ownership.

### B. Feature-module removability / coupling

Perform a static removability analysis for at least:

```text
EquippedSprintCollision
Raw8FistCollision
PhysicalFistCollision
AttackMotionRouting
CollisionDiagnostics + CollisionDiagnosticsDeep
```

Ask:

> If this feature were deliberately removed, are its state/policy and feature-specific implementation sufficiently localized that removal would mostly mean removing its module plus narrow bridge/marker delegation and build references?

Flag:
- hidden feature state in generic modules;
- feature-specific branches duplicated across unrelated modules;
- circular dependencies;
- public interfaces broader than callers actually require;
- feature modules directly owning generic hooks they should receive through the bridge.

Do not require perfect zero-touch removal when one central hook owner necessarily needs a delegation removed.

### C. Research-scaffolding retirement

Search current target for:
- stale probe names/includes/flags/state;
- research-only maps/counters/branches compiled into the behavior twin;
- obsolete fallback paths superseded by permanent owners;
- comments or code paths whose only justification was an already-closed causal probe;
- disabled/dead code that cannot execute under current build definitions.

Distinguish:
- **temporary scaffolding that should be removed**;
- **retained diagnostic instrumentation correctly isolated to diagnostic builds**;
- **evidence-backed permanent safety logic that only looks defensive**.

### D. Duplicate responsibility

Look for the same decision being made in more than one permanent owner, including:
- attack-family classification;
- factual source/UseType resolution;
- generation/liveness validation;
- collision-group mutation;
- raw8/raw55 eligibility;
- Sprint-origin continuation;
- marker dedupe/occurrence ownership;
- terminal repair policy.

Duplication is a finding only when two places actually own the same policy/fact. Revalidation at mutation boundaries is not automatically duplication.

### E. Defensive-code audit

Classify significant defensive checks/repair branches as one of:

```text
PROVEN REQUIRED
  backed by engine evidence / lifetime safety / exact source-generation invariant

JUSTIFIED BOUNDARY REVALIDATION
  intentionally repeated because a native call can invalidate earlier facts

REDUNDANT
  repeats the same invariant without an intervening invalidation boundary

SPECULATIVE
  handles no proven or plausible current contract and adds complexity/state

UNKNOWN — EVIDENCE CHECK NEEDED
  cannot be judged without exact proof
```

Do not recommend deletion of `PROVEN REQUIRED` or `JUSTIFIED BOUNDARY REVALIDATION` merely because the code is verbose.

### F. State/container audit

For each long-lived map/cache/execution record:
- identify owner and lifetime;
- identify creation/retirement paths;
- verify state is not duplicated elsewhere;
- flag fields that are written/read only for diagnostics but live in behavior state;
- flag fields no longer used by current permanent logic;
- flag state whose lifetime is broader than necessary.

Pay special attention to C1 generation, raw8 execution/opportunity/timing state, raw55 execution state and equipped Sprint origin state.

### G. Diagnostics/release separation

Verify statically:
- behavior target excludes `CollisionDiagnostics*`;
- diagnostic target adds diagnostics on top of identical behavior sources;
- behavior correctness has no logger/state dependency;
- no diagnostic-only hook/state accidentally became a release prerequisite;
- behavior-required raw8 GetPlayTime/OnDamage transports are correctly treated as behavior, not mislabeled as diagnostics;
- DEEP remains optional.

### H. CMake / compile-surface audit

Flag:
- stale source entries;
- unnecessary target-specific duplication;
- behavior source accidentally present only in one twin;
- diagnostic implementation accidentally present in behavior source membership;
- removed probe references;
- build flags that no longer correspond to current architecture.

### I. Complexity / abstraction / code-bloat audit

Identify only concrete complexity that earns a finding:
- helper exists only to wrap one trivial call with no boundary meaning;
- generalized abstraction has one caller and obscures feature ownership;
- repeated boilerplate can be collapsed without hiding Gothic/native sequencing;
- large function contains separable policy from transport;
- multiple near-identical branches encode the same invariant;
- stale comments/compatibility branches make current source harder to reason about.

Do **not** use:
- raw line count;
- function count;
- file size;
- preference for fewer modules;
- preference for more modules;
- generic “modern C++” aesthetics

as findings by themselves.

### J. Native fallback / proven-safety preservation

Every suggested cleanup must state whether it risks:
- unmarked/native fallback;
- C1 generation safety;
- exact source identity;
- original-call ordering;
- raw8 latch lifetime;
- raw55 native cleanup;
- equipped Sprint continuation;
- diagnostics-free parity.

If the risk cannot be bounded statically, classify the finding accordingly rather than proposing confident deletion.

## 6. Finding severity / output

Return a read-only audit report with findings grouped as:

```text
A. MUST CORRECT BEFORE FULL VALIDATION
B. SHOULD CORRECT BEFORE FULL VALIDATION
C. OPTIONAL / POST-VALIDATION CLEANUP
D. KEEP — suspicious-looking code that is actually justified
E. NO FINDING — areas explicitly checked and found architecturally clean
```

For every A/B/C finding include:

```text
ID
severity
exact file + symbol/region
current responsibility
specific problem
violated/strained authority or design principle
why it matters
smallest justified correction
expected changed-file scope if corrected
behavioral risk
required retest scope
confidence
```

For category D, explain what looks redundant/defensive and why the evidence/architecture says to keep it.

## 7. Audit discipline

This audit must **not**:

- edit source or documentation;
- build;
- publish a cleanup commit;
- redesign raw8/raw55/equipped semantics;
- invent new abstraction layers without a concrete finding;
- reopen closed causal questions merely because implementation is complex;
- recommend merging independent feature modules merely to reduce files;
- recommend splitting files merely because they are large;
- treat diagnostic verbosity as behavior bloat when correctly compile-isolated;
- treat exact liveness/generation/source revalidation as unnecessary until native invalidation boundaries are considered;
- change marker vocabulary;
- begin final `Script_G3AnimationBehaviors` migration;
- begin New Balance compatibility work.

If a material behavioral contradiction is discovered, report it as a finding and STOP short of a fix.

## 8. Required completion statement

End with:

```text
AUDIT RESULT:
- source changes made: NONE
- build attempted: NO
- material behavioral contradiction: <YES/NO>
- must-correct findings before full validation: <count>
- should-correct findings before full validation: <count>
- optional findings: <count>
- candidate suitable to freeze for full validation without source cleanup: <YES/NO, with reason>
```

Then STOP. Normal Chat + User own the cleanup decision.


## Audit completion — 2026-09-21

Work completed the read-only audit with:
- material behavioral contradiction: NO;
- MUST CORRECT findings: 0;
- SHOULD CORRECT findings: 5;
- OPTIONAL findings: 1;
- source changes/builds: none.

Normal Chat independently checked the reported source regions and accepted the five SHOULD findings. The optional compact raw8 diagnostic-signature cleanup is also promoted into the pre-validation cleanup because the affected files are already being touched and this is the deliberate final cleanup boundary before expensive validation.

Accepted cleanup set:

1. **B-01 — generation-qualified C1 metadata retirement**
   - retire finalized-generation metadata from FrameCollisionMarkers dedupe/budget state, EquippedSprintCollision binding state and PhysicalFistCollision execution state;
   - metadata/state retirement only;
   - no physical cleanup, latch/group mutation or lifecycle-policy migration;
   - generation-qualified erasure must never erase a replacement generation.

2. **B-02 — raw8 release-purity cleanup**
   - diagnostic-only raw8 timing fields, FullStop logging state and ownership-time diagnostic timing capture must not compile/execute in the behavior twin;
   - behavior-required timing/opportunity/source/SPU/C1 state remains unchanged.

3. **B-03 — closed TouchDamage diagnostic API retirement**
   - remove only dead no-caller historical deep logging APIs/helper.

4. **B-04 — EquippedSprint CORE compaction**
   - remove routine pointer-rich/no-op callback spam;
   - retain compact evidence for material bind/authorization transitions and contradictions;
   - no diagnostic-only behavior state.

5. **B-05 — diagnostic build-identity banner**
   - include permanent EquippedSprintCollision and PhysicalFistCollision in the behavior-core banner.

6. **C-01 — raw8 compact diagnostic signature cleanup**
   - remove parameters left unused by the previous CORE compaction;
   - no behavior/log semantic expansion.

The audit's KEEP findings are explicitly accepted: raw8 repeated liveness checks, stale-generation latch backup, post-native generation revalidation, lifecycle source re-resolution, raw55 exact predicates, equipped Sprint canonical origin handling, behavior-required raw8 GetPlayTime/OnDamage transports, bridge invocation-scope transport state and active opt-in DEEP diagnostics are **not cleanup targets**.

Implementation is deliberately split into two bounded tasks so the moderate-risk lifecycle cleanup is independently reviewable from diagnostic/release hygiene.
