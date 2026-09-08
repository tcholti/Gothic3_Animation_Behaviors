# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-08

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate transient handoff: `docs/BETWEEN_CHATS.md`  
Project charter/retrieval model: `docs/README.md`  
Recurring Git/build/deploy/evidence/recovery procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge ownership/maintenance: `docs/KNOWLEDGE_REGISTRY.md` + `docs/KNOWLEDGE_MAINTENANCE.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

---

## Closed Collision Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
collision architecture verification        CLOSED/PASS — EV-208–EV-215
Power                                      CLOSED/PASS — EV-241
Pierce                                     CLOSED/PASS — EV-242
SimpleWhirl                                CLOSED/PASS — EV-217–EV-220, EV-243
Hack tested 2H/Staff scope                 CLOSED/PASS — EV-216, EV-244
production human raw-8 FIST                CLOSED/PASS — EV-221–EV-240
```

Do not reopen these without concrete contradictory evidence.

Human raw-8 production remains FIST-only: no authored FIST_OFF, no Fist ClearTriggeredList, no equipped weapon source window/C1 physical repair, and no direct/custom damage.

The major post-human-Fist documentation/evidence/retrieval maintenance milestone is complete through Transactions 1–4. Do not begin another broad documentation audit absent a new POP-10 trigger.

---

## Current Immediate Responsibility

> **Bounded PhysicalFist/raw55 discovery.**

This begins in a fresh Normal Chat after the planned handoff. The first stage is research/discovery only, not implementation.

Primary question:

> Does transformed/non-human `gEUseType_PhysicalFist` / raw 55 reuse the proven human raw-8 native body-damage path, use a related but distinct branch, or use a materially different family-specific mechanism?

Start from the maintained owners rather than reconstructing human-Fist chronology:

```text
COLLISION_TEST_PLAN.md §4
SOURCE_HOOK_GUIDE.md §5
DESIGN.md PhysicalFist/raw55 boundary
ANIMATION_RULES.md raw UseType -> serialized Fist distinction
EVIDENCE_INDEX.md PhysicalFist/raw55 future route
```

Preferred first fixtures when reproducible:

```text
one transformed animal form
+ one clearly different transformed monster form
```

Establish only enough facts to classify the mechanism. Do not invent a broad monster matrix before the first comparison is interpreted.

Hard boundaries:

```text
NO assumption raw55 == human raw8
NO reuse/generalization of production G3AB_COL_FIST before evidence proves equivalence
NO new monster/body marker vocabulary during discovery
NO reopening closed human raw-8 Fist semantics
NO AttackContinuationProtection work yet
```

If raw55 is essentially equivalent, consider the smallest evidence-backed extension. If it is related but distinct, keep the mechanism separate. If it is materially different or disproportionately complex, record the unsupported/deferred boundary and proceed with collision closure for the deliberately supported scope.

Maintained roadmap afterward:

```text
bounded PhysicalFist/raw55 discovery
-> any tractable evidence-backed extension
-> final native mixed collision regression
-> separate AttackContinuationProtection
-> combined marker/lifecycle/continuation regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration
```

---

## User-Side Git Workflow

GitHub Desktop is now the preferred routine local Git interface under POP-01/POP-06.

The User is a **GitHub Desktop beginner**. Do not assume an operation is learned because it was demonstrated once. When asking the User to Fetch, Pull, switch branch, review Changes, Commit, Push, or inspect History, provide the concrete UI steps again in a manageable sequence until the User explicitly says the reminders are no longer needed.

Routine User-side Git:

```text
verify repository + current branch
-> Fetch origin
-> Pull origin when remote is ahead and local state is safe
-> make/review intended Changes
-> Commit locally
-> Push origin to publish
```

PowerShell remains appropriate for exact SHA/status diagnostics, build/deploy/hash verification, bounded log processing, conflict diagnosis, or other operations GitHub Desktop cannot express precisely enough.

Before the next local build/write window, synchronize the local checkout if the Assistant has made newer remote handoff/procedure commits.

---

## Interrupted-Context Rule

If the previous Chat dies without a trustworthy planned handoff, do not blindly follow this file's NEXT pointer. Enter POP-11 Recovery Lock first: authority orientation, recent durable-tail reconstruction, missed evidence/maintenance closure, current-state repair, and POP-10 only if the contradiction gate exposes broad drift.

Do not begin broad documentation cleanup merely because a Chat failed.
