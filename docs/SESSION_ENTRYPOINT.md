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
PhysicalFist/raw55 bounded discovery       CLOSED/DEFERRED — EV-245–EV-246
```

Do not reopen these without concrete contradictory evidence.

Human raw-8 production remains FIST-only: no authored FIST_OFF, no Fist ClearTriggeredList, no equipped weapon source window/C1 physical repair, and no direct/custom damage.

The bounded raw55 investigation did not observe `gEUseType_PhysicalFist` / raw 55. Tested Hero Wolf/Sabertooth transformations and native body attackers resolved factual raw-8 `Fist`; weapon/magic controls resolved their own factual UseTypes. This is a bounded unobserved/deferred result, not proof that raw55 is globally unused by Gothic 3. Do not extend production `G3AB_COL_FIST` to monsters or raw55 from these observations, and do not infer that creature raw-8 attacks share every proven human timing/latch internal.

The major post-human-Fist documentation/evidence/retrieval maintenance milestone is complete through Transactions 1–4. Do not begin another broad documentation audit absent a new POP-10 trigger.

---

## Current Immediate Responsibility

> **Final native mixed collision regression over the deliberately supported current scope.**

This is regression/coexistence confirmation, not a new collision architecture or source-discovery stage.

Primary authority:

```text
COLLISION_TEST_PLAN.md §5
DESIGN.md current implementation order
EVIDENCE_INDEX.md current collision closure routes
```

Protect at minimum:

```text
equipped RIGHT / LEFT / BOTH / OFF exact-set behavior
repeated-contact ClearTriggeredList semantics
Power / Pierce / SimpleWhirl / Hack current behavior
C1 generation-scoped occurrence/dedupe identity
C1-R1 exact-source terminal repair
production human raw-8 FIST
unmarked/native fallback
one-live-collision-twin deployment invariant
```

Hard boundaries:

```text
NO raw55/PhysicalFist implementation without new factual runtime UseType 55 evidence
NO production G3AB_COL_FIST generalization to creature raw-8 or monsters
NO reopening closed human raw-8 Fist semantics
NO AttackContinuationProtection work inside this regression
NO Raise/speed work
NO new family/source redesign
```

Maintained roadmap afterward:

```text
final native mixed collision regression
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
