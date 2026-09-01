# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate transient handoff when needed: `docs/BETWEEN_CHATS.md`  
Project charter / highest Gothic-specific authority / retrieval map: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring local + formal review/audit procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge maintenance/ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

---

## Authority Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the **highest project-specific authority immediately beneath CAM** for the project's purpose, long-term direction, scope and authority topology. `COLLABORATION_RULES.md` owns how CAM/project principles are operationalized for participant allocation and collaboration inside Gothic 3.

```text
CAM constitutional collaboration principles
→ Gothic project charter (`docs/README.md`)
→ specialist Gothic authorities within delegated domains
→ procedures / bounded protocols
→ exact task execution
```

Specialist authorities are not all linearly ranked; each owns its delegated domain beneath the charter.

Ordinary Gothic engineering should use the lowest relevant Gothic authority rather than rereading CAM or the full charter by default.

A **formal project review/audit** must instead apply POP-10: establish the charter hierarchy and each target's intended responsibility before judging content, contradiction, duplication or cleanup.

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
3. Treat the CAM → project charter → specialist authority hierarchy and the release-purity rule above as standing constraints.
4. If the current responsibility is a **formal review/audit**, apply POP-10 in `docs/PROJECT_OPERATING_PROCEDURES.md` before evaluating the target. Read/confirm `docs/README.md` §0 and each target's intended Purpose/Scope/owner first. The review has not started until that preflight is satisfied.
5. If the active technical subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
6. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority.
7. Read other `docs/PROJECT_OPERATING_PROCEDURES.md` sections only when entering their relevant local Git/build/deploy/runtime-artifact sequences.
8. Retrieve the relevant `docs/PROJECT_PIPELINE.md` section before changing gate/test/evidence/procedure IDs, artifact naming, build labels, branch meanings or validation-flow conventions.
9. Do not scan the whole repository or reconstruct the project from old chat history.
10. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
11. Do not modify CAM from this project responsibility.

After bootstrap, report briefly:

```text
current responsibility
closed boundary relevant to it
exact immediate next step
what remains deliberately deferred
```

For a formal review/audit, also state the compact POP-10 preflight hierarchy and intended use of the major targets before findings.

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
= active collision development/research
= remains the sole active feature branch through completed collision behavior,
  production collision migration and collision validation
```

The stabilized governance/planning checkpoint is kept aligned with protected `main` before new collision implementation resumes. After that checkpoint, collision development may advance on `docs/collision-source-evidence` while `main` remains the stable baseline until the completed collision responsibility is deliberately promoted.

Accepted phase transition:

```text
complete collision on docs/collision-source-evidence
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from that newly updated main
```

Do **not** create `feature/raise-attack-speed` early.

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
→ combined collision regression
→ mature research-collision compatibility gate
→ migrate mature collision behavior into Script_G3AnimationBehaviors on the collision branch
→ diagnostics-free collision integration + compatibility validation
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from updated main
→ Raise + general/action/profile attack-speed + config redesign/migration
→ final assembled-behavior compatibility/regression
→ promote mature Raise/speed checkpoint to main
→ later target acquisition/climbing
→ retain separate diagnostic twins/tools
```
