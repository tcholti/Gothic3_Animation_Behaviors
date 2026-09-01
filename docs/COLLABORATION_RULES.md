# Gothic 3 Project Collaboration Delta

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active project-specific collaboration authority  
**Version:** 2.1  
**Updated:** 2026-09-01

## Purpose

Define only the collaboration rules that are specific to the Gothic 3 Animation Behaviors project: participant responsibilities, responsibility allocation, interaction/authorization boundaries, and the project's operational relationship to CAM.

This file does **not** own:

```text
retrieval-depth procedure / subsystem orientation  → README.md
stable branch/test/log/version conventions          → PROJECT_PIPELINE.md
recurring Git/build/deploy/test/evidence sequences  → PROJECT_OPERATING_PROCEDURES.md
bounded Work execution details                      → WORK_IMPLEMENTATION_PROTOCOL.md
knowledge-maintenance transactions                  → KNOWLEDGE_MAINTENANCE.md
knowledge authority/update triggers                 → KNOWLEDGE_REGISTRY.md
technical engineering principles                    → ENGINEERING_GUIDE.md / technical authorities
current technical responsibility                    → SESSION_ENTRYPOINT.md
transient continuation detail                       → BETWEEN_CHATS.md
```

> **One collaboration responsibility should have one project-local owner. This file allocates responsibility; it does not duplicate every procedure used by those responsibilities.**

---

## 1. Authority Hierarchy and CAM Boundary

The Gothic 3 project operates under CAM as its higher-order collaboration philosophy. CAM is the constitutional layer: it supplies the reusable principles and agency model that project-local rules are meant to operationalize.

The practical hierarchy is:

```text
CAM philosophy / reusable collaboration principles
        ↓
Gothic 3 project-specific rules and responsibility allocation
        ↓
stable project conventions / authority routing
        ↓
recurring procedures and bounded implementation protocols
        ↓
exact task-specific execution / transient handoff
```

A lower layer may specialize, constrain and operationalize a higher layer for Gothic 3, but it should not silently redefine or contradict the higher layer.

The Gothic 3 repository's current authorities govern **concrete Gothic work** because they are the project's maintained operationalization of that hierarchy. Ordinary engineering should therefore use the project-local authority that owns the immediate responsibility rather than repeatedly loading abstract CAM material.

The separate `tcholti/Collaborative-Agency-Model` repository may evolve through dedicated CAM-focused work. A newer CAM revision does **not** silently rewrite this project merely because it exists. Incorporating a CAM evolution into Gothic 3 requires a deliberate project-local review/update so the operational consequences are understood rather than mechanically synchronized.

From Gothic 3 work:

```text
apply the adopted CAM principles through current Gothic authorities
read/compare CAM when a collaboration-level question genuinely requires it
improve the lowest owning Gothic authority when project experience exposes friction
identify a lesson as a possible CAM-evolution candidate when warranted
never modify CAM from this project responsibility
```

If Gothic experience appears to expose a genuine constitutional gap or tension rather than a merely local procedural weakness:

```text
preserve the concrete project lesson
→ avoid pretending a lower project rule has silently rewritten CAM
→ mark the issue for separate CAM comparison/evolution
→ STOP upward modification in this project
→ dedicated User-authorized CAM chat decides whether CAM should change
→ any adopted CAM evolution is then deliberately operationalized back into Gothic authorities
```

Editing CAM rules, profiles, procedures, philosophy, reusable baselines, or theory requires that separate User-authorized CAM-focused responsibility.

Do not load CAM documents during ordinary Gothic engineering merely to reconfirm established project practice. Constitutional authority does not imply repeated pre-reading when the current project rules already operationalize it clearly.

---

## 2. Participant Responsibilities

The User, Normal Chat, Work, the authoritative home PC, and the repository are complementary participants rather than interchangeable execution environments.

### User

Primary responsibilities:

```text
vision and desired behavior
priorities and trade-offs
first-person gameplay/animation observations
authoritative local runtime execution when required
challenge/correction of interpretations
final project-direction decisions
```

The User should not need to reconstruct repository history, repeatedly relay facts already stored in authority, or manually remember routine documentation/evidence housekeeping.

### Normal Chat

Primary responsibilities:

```text
retrieve relevant project knowledge
interpret source/runtime evidence
reason with the User and surface disagreement/uncertainty
architecture and semantic design
creative simplification
freeze bounded implementation/test responsibilities
independent review of meaningful Work implementation
knowledge-maintenance trigger/check
repository documentation/evidence maintenance when appropriate
interpret build/runtime results and choose the next responsibility
```

Normal Chat should not outsource context-heavy design to Work merely because Work can execute code changes.

### Work

Use Work when its execution environment materially improves a **bounded implementation responsibility** whose important semantics are already decided.

Typical Work responsibilities:

```text
inspect narrowly necessary source/API material
implement the frozen change
perform source-level audit
publish the audited result when authorized
return a concise handoff
stop at the bounded responsibility
```

Work does not become a second architecture/evidence authority merely because it has broad source access or substantial compute.

Treat materially constrained Work usage as a project resource: do not spend it on project reconstruction, routine documentation maintenance, broad history review, or open-ended architecture when those responsibilities are already better served by User + Normal Chat.

Detailed Work execution and stop conditions are owned by `WORK_IMPLEMENTATION_PROTOCOL.md`.

### Authoritative home PC

The User's local Windows/Gothic 3 environment is authoritative for operations that require the real toolchain/game installation, including as applicable:

```text
branch synchronization before local work
Visual Studio/CMake build
exact DLL deployment
live-file/hash verification
Gothic 3 startup/load check
controlled gameplay/runtime test
capture of locally produced runtime artifacts
```

A source commit is not a runtime result; an assistant-side source review is not a substitute for the authoritative local build/game where those stages are required.

### Repository

The repository is the durable project memory and coordination surface:

```text
current source truth
current project authorities
canonical evidence conclusions
runtime/source provenance
indexes and retrieval routes
transient handoff when genuinely needed
Git history for superseded documentation wording
```

Use repository authority instead of making the User carry technical continuity between contexts.

---

## 3. Default Responsibility Allocation

Current project allocation:

```text
User + Normal Chat
research / interpretation / disagreement / architecture / semantics /
creative simplification / planning / task freezing / knowledge maintenance
        ↓
Work when materially useful
bounded implementation / narrowly necessary source or API inspection /
source audit / authorized publish / concise handoff
        ↓
Normal Chat + authoritative home PC
independent source review / build / deploy / runtime testing /
evidence interpretation / next design decision
```

When placement is uncertain, ask:

> **Which environment materially improves this responsibility, given the context it needs, the authority it carries, the tools it can actually use, and the resources it consumes?**

More compute, a larger context window, or repository automation does not automatically make Work the right owner of context-heavy design. Conversely, mechanically substantial but semantically frozen implementation need not remain in Normal Chat when Work materially improves execution.

This allocation is evidence-based and revisable within the CAM hierarchy. Change the lowest owning project rule deliberately if capabilities, constraints, or repeated results materially change the best allocation; if the lesson appears to challenge a CAM-level principle, use the separate upward-review path in §1 rather than silently redefining it here.

No permanent Medium/High reasoning-mode rule belongs in this project. Use sufficient reasoning for the responsibility and avoid spending resources reconstructing context that the repository can recover.

---

## 4. Interaction and Authorization Boundary

### Routine continuation

When the exact next operation is already established—for example build, deploy, verify, run the frozen test, preserve the requested log, or continue another explicitly frozen sequence—a short result such as `done`, `passed`, or the requested artifact advances that same responsibility.

Do not require ceremonial reconfirmation of an already-clear next operation.

### Interpretive/discovery transition

When new evidence changes interpretation, exposes a contradiction, or creates a genuine architecture/strategy choice:

1. present the interpretation and its evidence/boundary;
2. allow the User to add observations, disagree, or refine it;
3. expose the next responsibility and why it follows before treating agreement as execution authority.

A natural `agree`, `continue`, `yes`, `let's do it`, or equivalent authorizes the clearly exposed responsibility. Do not require a second artificial confirmation.

Agreement given **before** a new responsibility was exposed is agreement with the interpretation, not authorization for an unannounced implementation step.

> **Advance routine work from the established referent; expose a new interpretive responsibility before executing it.**

---

## 5. Bounded Work Handoff

When User + Normal Chat decide that Work is the appropriate executor:

```text
semantic/design responsibility is already sufficiently frozen
→ detailed transient contract lives once in BETWEEN_CHATS when needed
→ Work launcher stays compact
→ Work reads SESSION_ENTRYPOINT + relevant handoff + WORK_IMPLEMENTATION_PROTOCOL
→ Work implements/publishes only the bounded responsibility
→ Normal Chat independently reviews meaningful engine-facing changes before runtime authority is claimed
```

Do not duplicate a long implementation contract into several documents and prompts merely for self-containment.

The launcher should contain only what Work cannot safely derive from the repository, such as exact repository/branch/base identity, the responsibility to read, publication authorization/destination when needed, and an explicit stop boundary.

`WORK_IMPLEMENTATION_PROTOCOL.md` owns implementation preflight, allowed local decisions, source audit, publication behavior, required handoff, and stop conditions.

---

## 6. Keep User/Chat Transfer Burden Small

Routine successful command output and large runtime logs should not be pasted into Chat by default.

Project preference:

```text
successful routine command
→ short confirmation / relevant final identity is enough

failure
→ smallest useful error excerpt first
→ broaden only if diagnosis requires it

controlled runtime evidence
→ freeze test + exact filename
→ User places complete artifact in repository intake path
→ publish artifact
→ Normal Chat retrieves it from the repository
```

Exact log naming and validation conventions are owned by `PROJECT_PIPELINE.md`; the concrete runtime-test/raw-publish sequences are POP-05/POP-06 in `PROJECT_OPERATING_PROCEDURES.md`.

This is intended to keep the collaboration focused on meaning rather than turning the Chat transcript into a duplicate artifact store.

---

## 7. Continuity Without User Reconstruction

A Chat or Work context is not the sole project memory.

For continuation:

```text
current durable state          → SESSION_ENTRYPOINT.md
transient exact continuation   → BETWEEN_CHATS.md when genuinely needed
retrieval depth/routes         → README.md
exact technical evidence       → EVIDENCE_INDEX.md → exact EV/provenance
stable project conventions     → PROJECT_PIPELINE.md
```

Do not ask the User to repeat technical state that can be reliably recovered from project authority.

Do not reread the entire repository simply because a new prompt or Chat arrived. Use the retrieval model in `README.md`.

When the User announces a new Normal Chat, perform only the maintenance necessary to make `SESSION_ENTRYPOINT.md` and any genuinely needed `BETWEEN_CHATS.md` bridge current, then give the User a short starter instruction. The detailed current-state/maintenance rules are owned by `README.md` and `KNOWLEDGE_MAINTENANCE.md` rather than repeated here.

---

## 8. Project Method Evolution

Project procedures/rules are working operationalizations under the CAM constitutional layer, not immutable law.

When repeated friction, one serious failure, or a clearly better method exposes a real weakness:

```text
diagnose the actual mechanism
→ change the lowest owning Gothic authority that can solve it consistently with CAM
→ preserve only necessary rationale/history through current authority + Git history
→ use the revised method and observe it
```

Do not add a new rule or document simply because a problem occurred once if an existing owner can absorb the lesson.

Ownership of the change is determined by `KNOWLEDGE_REGISTRY.md`:

```text
stable convention            → PROJECT_PIPELINE.md
recurring operation          → PROJECT_OPERATING_PROCEDURES.md
bounded Work execution       → WORK_IMPLEMENTATION_PROTOCOL.md
knowledge maintenance        → KNOWLEDGE_MAINTENANCE.md
collaboration allocation     → this file
retrieval/document map       → README.md
```

### Bottom-up learning / upward CAM review

Gothic project experience is one empirical source from which CAM may eventually learn, but upward evolution is deliberately separate from ordinary project maintenance.

```text
Gothic success/friction/failure
→ improve the lowest Gothic owner when the lesson fits the adopted CAM principles
→ observe actual use
→ identify candidate wider value or a possible CAM-level gap when warranted
→ STOP upward modification in Gothic work
→ dedicated User-authorized CAM responsibility compares across projects and decides any CAM evolution
→ deliberately operationalize adopted CAM changes back into Gothic authorities where relevant
```

This preserves both directions of learning:

```text
CAM → governs and shapes project operationalization
project experience → supplies evidence for later CAM evolution
```

Do not modify CAM from this project-maintenance transaction.

---

## Core Project Collaboration Rule

> **Use CAM as the constitutional collaboration layer and the Gothic repository as its maintained project-specific operationalization: keep User + Normal Chat responsible for context-heavy interpretation/design, Work responsible for bounded execution when it materially helps, the authoritative home PC responsible for real build/game stages, and the repository responsible for durable memory; expose new interpretive responsibilities before executing them, minimize transfer burden, evolve the lowest Gothic authority from evidence, and reserve any CAM evolution for a separate deliberate upward-review responsibility.**
