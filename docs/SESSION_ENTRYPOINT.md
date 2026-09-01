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

Do not carry detailed Gate-4 history or validated binary identities in this front door; those are owned by the technical/evidence authorities.

---

## Repository Boundary

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research
```

The verified collision-architecture checkpoint is already on `main`. Structural stabilization after that checkpoint is intentionally being completed on the active branch before another stable promotion.

Known unrelated local file remains outside project maintenance and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Current Responsibility — Project Stabilization Pass 2

### Pass 1 — COMPLETE

Structural simplification is complete. Durable result:

```text
three canonical evidence-ledger files
obsolete Script_FrameEffectLogger retired
redundant standalone large-log procedure retired
completed one-off collision contracts retired after durable absorption
parallel RESEARCH_MAP chronology retired
superseded documentation snapshots retired in favor of Git history
research/raw / archive / derived evidence layers retained
```

Exact details are recoverable from Git history and the current documentation/evidence map; do not reconstruct Pass-1 chronology during normal work.

### Pass 2 — CURRENT

Audit the Gothic project rules/procedures as one responsibility hierarchy:

```text
COLLABORATION_RULES.md
WORK_IMPLEMENTATION_PROTOCOL.md
PROJECT_OPERATING_PROCEDURES.md
PROJECT_PIPELINE.md
KNOWLEDGE_MAINTENANCE.md
KNOWLEDGE_REGISTRY.md
README.md
SESSION_ENTRYPOINT.md
```

Current objective:

```text
CAM principles remain the constitutional layer
Gothic rules operationalize CAM rather than competing with it
one responsibility → one primary project authority
no contradictory User / Normal Chat / Work / home-PC / repository allocation
no duplicate convention/procedure ownership
no obsolete temporary rules
no unnecessary rereading or current-state bloat
no CAM modification from this project
```

Preserve useful distinct responsibilities. Do not merge documents merely because they are related.

---

## After Pass 2

### Pass 3 — build/product/repository-shape audit

```text
verify only justified current build products/tools remain
preserve release/diagnostic twin architecture
verify branch/dependency/build assumptions are explicit
identify orphan prototype/build paths only if they actually exist
```

### Pass 4 — final readiness check

```text
fresh Chat/Work can recover the project from a small retrieval surface
important engine facts route index → EV → provenance
build/product model is unambiguous
repository state has no unresolved structural ambiguity
```

Do **not** start equipped-melee marker expansion until all stabilization passes are complete.

After stabilization:

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
