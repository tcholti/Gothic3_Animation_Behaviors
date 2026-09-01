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

Never normally load behavior-only and diagnostic twins together.

Release/product details live in `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when it contains an active transient responsibility.
3. Treat the CAM/project authority boundary and release-purity rule above as standing constraints.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` only when entering a relevant local Git/build/deploy/runtime-artifact sequence.
7. Retrieve the relevant `docs/PROJECT_PIPELINE.md` section before changing gate/test/evidence/procedure IDs, artifact naming, build labels, branch meanings or validation-flow conventions.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
10. Do not modify CAM from this project responsibility.

After bootstrap, report briefly:

```text
current responsibility
closed boundary relevant to it
exact immediate next step
what remains deliberately deferred
```

---

## Closed Collision Architecture Boundary

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

Do not reopen this architecture without concrete contradicting evidence. Technical semantics live in `DESIGN.md` and the collision authorities; proof lives behind `EVIDENCE_INDEX.md`.

---

## Repository Boundary

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research
```

Project structural/rules/product stabilization is complete and the cleaned checkpoint has been deliberately promoted to protected `main` with both histories preserved.

Known unrelated local file remains outside project maintenance and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Project Stabilization — COMPLETE

```text
Pass 1 structural document/tool simplification   PASS
Pass 2 Gothic rules/procedures consistency       PASS
Pass 3 build/product/repository-shape audit      PASS
Pass 4 final fresh-context/readiness check       PASS
stable main promotion                            PASS
```

Stable product/tool model:

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
= offline deterministic large-log processor
```

The cleanup found no remaining structural ambiguity that should delay engineering. Do not start another documentation cleanup merely for stylistic uniformity.

---

## CURRENT RESPONSIBILITY — Equipped-Melee Marker Expansion Planning

Return to engineering, but **do not modify code yet**.

First reconstruct only the current supported marker-family/source boundary from the existing architecture, `ANIMATION_INDEX.md` / `ANIMATION_CATALOG.md`, and the relevant evidence routes.

Then choose and freeze **one exact equipped-melee expansion mechanism/family** before implementation.

Required planning boundaries:

```text
preserve closed C1 lifecycle/generation architecture
preserve RIGHT / LEFT / BOTH / OFF semantics
preserve native fallback for unmarked/unsupported cases
separate physical source selection from action/family identity
review the recorded Dual P1 Quick authored-RIGHT vs older native-LEFT discrepancy deliberately
keep Fist/body source adaptation separate
keep AttackContinuationProtection separate
no broad all-family implementation in one step
```

Immediate next step:

```text
orientation/retrieval of current supported equipped-melee marker boundary
→ identify the smallest logical next expansion candidate
→ discuss/freeze it with the User
```

---

## Forward Order

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
