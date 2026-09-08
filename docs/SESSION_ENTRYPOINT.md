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
human raw-8 FIST Normal/Power              CLOSED/PASS — EV-221–EV-240
PhysicalFist/raw55 bounded discovery       CLOSED/DEFERRED — EV-245–EV-246
transformed Sabretooth Normal/Power FIST   PASS — EV-247
```

Do not reopen these exact closed conclusions without concrete contradictory evidence.

Raw-8 FIST remains FIST-only: no authored FIST_OFF, no Fist ClearTriggeredList, no equipped weapon source window/C1 physical repair, and no direct/custom damage.

The bounded raw55 investigation did not observe `gEUseType_PhysicalFist` / raw 55. Tested transformations and several native body attackers resolved factual raw-8 `Fist`; weapon/magic controls resolved their own factual UseTypes. Raw55 remains unobserved/deferred, not globally disproven.

EV-247 materially qualifies the earlier conservative actor-family boundary: transformed Sabretooth Normal and Power entered the existing raw-8 FIST ownership/timing mechanism successfully. The intended architecture is not human-animation-family- or species-gated; factual raw-8 source identity plus a supported/proven native attack-family mechanism governs applicability.

EV-247 also establishes that transformed Quick-left/right is **not marker-controlled today**. The raw8 source and native `Game +0x16E348` damage route are present, but each FIST marker is explicitly `REJECTED_UNSUPPORTED_HIT` because current code permits FIST only for Normal + Power. Do not implement Quick until its native latch/timing mechanism is classified.

---

## Current Immediate Responsibility

> **Native Sabretooth NPC -> player marked Normal/Power compatibility control. No code change before this test.**

Use the same marked Sabretooth Normal/Power animations that passed under `Transform_Sabertooth_Potion`, but let a genuine native Sabretooth NPC attack the player.

Primary authority:

```text
COLLISION_TEST_PLAN.md §5
DESIGN.md raw-8 Fist architecture
EV-247
BETWEEN_CHATS.md exact continuation
```

Purpose:

```text
separate transformed-player success
from actual native-NPC actor compatibility
without changing production code first
```

`research/raw/2026.09.08_sabertooth_marked_attacks.log` is **ACTIVE COMPARISON — KEEP RAW** until this native-NPC comparison is closed.

After the native Sabretooth control, the planned bounded sequence is:

```text
raw8 Quick mechanism classification / bounded extension only if proven
-> native equipped-NPC marker tests: Goblin 1H / Demon 2H / Ogre Axe
-> separated 2H-vs-Axe mod marker compatibility
-> separated 1H-vs-Rapier mod marker compatibility
-> final native mixed collision regression
-> separate AttackContinuationProtection
-> combined marker/lifecycle/continuation regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration
```

Hard boundaries:

```text
NO raw55/PhysicalFist implementation without new factual runtime UseType 55 evidence
NO species/name-specific marker vocabulary or actor-family gating
NO Quick FIST code before mechanism proof
NO AttackContinuationProtection work inside the pre-regression compatibility sequence
NO Raise/speed work
NO new source/lifecycle redesign
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

Before the next local write/test window, synchronize the local checkout if the Assistant has made newer remote handoff/evidence-maintenance commits.

---

## Interrupted-Context Rule

If the previous Chat dies without a trustworthy planned handoff, do not blindly follow this file's NEXT pointer. Enter POP-11 Recovery Lock first: authority orientation, recent durable-tail reconstruction, missed evidence/maintenance closure, current-state repair, and POP-10 only if the contradiction gate exposes broad drift.

Do not begin broad documentation cleanup merely because a Chat failed.
