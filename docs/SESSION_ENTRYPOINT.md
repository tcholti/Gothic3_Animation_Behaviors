# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-09

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
human raw-8 FIST Normal/Power              CLOSED/PASS — EV-221–EV-240
PhysicalFist/raw55 bounded discovery       CLOSED/DEFERRED — EV-245–EV-246
transformed Sabretooth Normal/Power FIST   PASS — EV-247
native Sabretooth Normal/Power FIST        PASS — EV-248
raw-8 Quick relevant native mechanism      CLASSIFIED — EV-248
```

Do not reopen these exact closed conclusions without concrete contradictory evidence.

Raw-8 FIST remains FIST-only: no authored FIST_OFF, no Fist ClearTriggeredList, no equipped weapon source window/C1 physical repair, and no direct/custom damage.

The bounded raw55 investigation did not observe `gEUseType_PhysicalFist` / raw 55. Tested transformations and several native body attackers resolved factual raw-8 `Fist`; weapon/magic controls resolved their own factual UseTypes. Raw55 remains unobserved/deferred, not globally disproven.

EV-247–EV-248 remove the earlier conservative human/species boundary for the tested raw-8 Normal/Power fixtures. Both transformed and genuine native Sabretooth attacks entered the existing FIST ownership/timing mechanism. The intended architecture is governed by factual raw-8 source identity plus a supported/proven native attack-family mechanism, not actor species or animation-family naming.

EV-248 also closes the prerequisite Quick mechanism question. Native Sabretooth Quick-left/right factually use raw-8 `Fist` and damage through `Game +0x16E348`. Tested Game.dll control flow establishes that this damaging route passes the generic `SPU+0x164` gate, the motion-0 `+0x16E180` timing comparison and the native `SPU+0x164 = 1` write at `+0x16E1A3`; the alternate sub-arm returns before the `+0x16E348` damage dispatch. Quick therefore has sufficient mechanism proof for bounded reuse of the existing raw-8 FIST contract.

---

## Current Immediate Responsibility

> **Implement only the bounded raw-8 FIST Quick family-scope extension, then validate it on native Sabretooth Quick-left/right.**

No new mechanism is required. Current source already:

```text
recognizes QuickAttack / QuickAttackR / QuickAttackL as AttackFamily_Quick
uses StatePosition 1 for Quick marker bookkeeping
routes OnAI_QuickAttack through EvaluateAttackCallback
resolves the same factual raw-8 Fist source
contains the existing exact FIST latch/timing machinery
```

Current deliberate blockers are the FIST family checks that admit only Normal + Power. The bounded implementation responsibility is therefore:

```text
admit AttackFamily_Quick at the existing FIST ownership/dispatch family gates
preserve every other raw-8 FIST invariant exactly
```

Primary authority:

```text
EV-248
DESIGN.md raw-8 Fist architecture
COLLISION_TEST_PLAN.md pre-regression compatibility gates
BETWEEN_CHATS.md exact bounded continuation
```

Hard boundaries:

```text
NO new hook
NO new marker opcode/vocabulary
NO species/name/animation-family branch
NO raw55/PhysicalFist behavior
NO new latch/timing mechanism
NO direct/custom damage
NO FIST_OFF resurrection
NO Fist ClearTriggeredList
NO equipped Item_Attack/Item_Equipped Fist window
NO C1 weapon cleanup change
NO AttackContinuationProtection work
NO Raise/speed work
NO unrelated equipped-family/source redesign
```

After implementation, User + Normal Chat build/deploy the diagnostic twin normally and run a bounded native-Sabretooth Quick validation. Require Quick markers to become accepted, initial ownership close and marker rearm/timing permission to follow the existing FIST contract, damage only after the authored opportunity, and unmarked/native fallback to remain native.

Both current Sabretooth logs remain **ACTIVE COMPARISON — KEEP RAW** until this post-change Quick validation closes:

```text
research/raw/2026.09.08_sabertooth_marked_attacks.log
research/raw/2026.09.09_sabertooth_npc_marked_attacks.log
```

After Quick closes, continue:

```text
native equipped-NPC marker tests: Goblin 1H / Demon 2H / Ogre Axe
-> additional prepared native/modded actor-family marker controls, one log per actor/family
-> separated 2H-vs-Axe mod marker compatibility
-> separated 1H-vs-Rapier mod marker compatibility
-> final native mixed/stress collision regression
-> separate AttackContinuationProtection
-> combined marker/lifecycle/continuation regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration
```

If an intermediate actor/family fails, stop and resolve that exact failure before continuing the matrix.

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

Before the next local write/test window, synchronize the local checkout if the Assistant has made newer remote handoff/evidence-maintenance commits.

---

## Interrupted-Context Rule

If the previous Chat dies without a trustworthy planned handoff, do not blindly follow this file's NEXT pointer. Enter POP-11 Recovery Lock first: authority orientation, recent durable-tail reconstruction, missed evidence/maintenance closure, current-state repair, and POP-10 only if the contradiction gate exposes broad drift.

Do not begin broad documentation cleanup merely because a Chat failed.
