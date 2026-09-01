# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate transient handoff when needed: `docs/BETWEEN_CHATS.md`  
Documentation/retrieval map: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge maintenance/ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

---

## Authority Boundary

CAM is the higher-order collaboration philosophy for this project. `COLLABORATION_RULES.md` owns how those principles are operationalized for Gothic 3.

```text
CAM constitutional collaboration principles
→ Gothic project-specific rules / authority allocation
→ project conventions and procedures
→ exact task execution
```

Ordinary Gothic engineering should use the lowest relevant Gothic authority rather than rereading CAM by default.

> **Do not modify the Collaborative-Agency-Model repository from Gothic 3 project work.** Any CAM evolution requires a separate User-authorized CAM-focused responsibility; adopted CAM changes are then deliberately operationalized back into this project.

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

```text
shared behavior architecture
→ diagnostics-free RELEASE/behavior-only build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Never normally load behavior-only and diagnostic twins together.

Release/product details live in `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when it contains an active transient responsibility.
3. Treat the CAM/project authority boundary and release-purity rule above as standing constraints.
4. If the active subsystem is not already oriented in the current Chat, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` only when entering a relevant local Git/build/deploy/runtime-artifact sequence.
7. Retrieve the relevant `docs/PROJECT_PIPELINE.md` section before changing gate/test IDs, evidence/procedure IDs, artifact naming, build labels, branch meanings or validation-flow conventions.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
10. Do not modify CAM from this project responsibility.

After bootstrap, report briefly:

```text
current technical/project responsibility
closed boundary relevant to it
exact immediate next step
what remains deliberately deferred
```

---

## Closed Collision Architecture Boundary

Collision architecture verification is complete and should not be reopened without concrete contradicting evidence.

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
Literal historical EV-131 regression       CLOSED/PASS — EV-214
Final behavior-only architecture smoke     CLOSED/PASS — EV-215
NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

For the actual architecture and protected semantics, use:

```text
DESIGN.md
COLLISION_LIFECYCLE_PLAN.md
COLLISION_LOGGER_PLAN.md
COLLISION_TEST_PLAN.md
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md
```

For proof and provenance, use `EVIDENCE_INDEX.md` → exact EV entry → archive/raw/source only when needed.

---

## Repository Boundary

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research
```

The verified collision-architecture checkpoint is already on `main`. The post-verification project stabilization is being completed on the active branch before another deliberate stable promotion.

Known unrelated local file remains outside project maintenance and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Project Stabilization

### Pass 1 — structural simplification: COMPLETE

```text
three canonical evidence-ledger files
obsolete Script_FrameEffectLogger retired
redundant standalone large-log procedure retired
completed one-off collision contracts retired after durable absorption
parallel RESEARCH_MAP chronology retired
superseded documentation snapshots retired in favor of Git history
research/raw / archive / derived evidence layers retained
```

### Pass 2 — Gothic rules/procedures consistency: COMPLETE

Accepted responsibility hierarchy:

```text
CAM constitutional collaboration layer
→ COLLABORATION_RULES: Gothic operationalization / participant allocation
→ PROJECT_PIPELINE: stable conventions
→ PROJECT_OPERATING_PROCEDURES: recurring operational sequences
→ WORK_IMPLEMENTATION_PROTOCOL: bounded implementation execution
→ KNOWLEDGE_REGISTRY: authority/update ownership
→ KNOWLEDGE_MAINTENANCE: maintenance process
→ README: retrieval map
→ SESSION_ENTRYPOINT: current state only
```

### Pass 3 — build/product/repository shape: COMPLETE

Verified current product/tool shape:

```text
Script_G3AnimationBehaviors
= production-direction behavior DLL; current Raise/speed implementation

Script_FrameCollisionBehaviorTest
= diagnostics-free collision behavior research twin

Script_FrameCollisionTest
= same collision behavior + diagnostic instrumentation

Script_CombatMoveLogger
= independent generic CombatMove / playback-speed diagnostic tool

tools/log_evidence
= offline deterministic large-log processor; not a Gothic DLL target
```

Verified structural rules:

```text
only one active collision prototype directory
behavior-only and diagnostic collision twins share one behavior source list
do not co-load the collision twins
official Georgeto SDK submodule is the build dependency
Jackydima SDK submodule is reference-only
obsolete FrameEffectLogger target/source and active build references are retired
prototype/research names remain until deliberate production migration
product-aware build/deploy/load procedures now distinguish diagnostic vs behavior-only evidence surfaces
```

No collision behavior was changed during Pass 3.

### Pass 4 — CURRENT: final readiness check

Prove the stabilized repository is ready to return to engineering:

```text
fresh Normal Chat can recover current state from a small hot path
bounded Work can recover a frozen implementation without reconstructing the project
important engine facts route EVIDENCE_INDEX → exact EV → provenance
build/product/dependency roles are unambiguous
active/stable branch roles are explicit
no unresolved structural/authority ambiguity remains
```

Do not create another cleanup task merely for stylistic uniformity. If these checks pass, stabilization is complete and the active checkpoint may be promoted to `main` deliberately.

---

## After Stabilization

```text
equipped-melee marker expansion planning
→ freeze/implement/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ compatibility gate
→ Raise + speed + config redesign/migration
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
