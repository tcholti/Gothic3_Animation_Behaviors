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
raw-8 Quick FIST family extension          CLOSED/PASS — post-change Sabretooth two-direction validation
```

Do not reopen these exact closed conclusions without concrete contradictory evidence.

Raw-8 FIST remains FIST-only: no authored FIST_OFF, no Fist ClearTriggeredList, no equipped weapon source window/C1 physical repair, and no direct/custom damage.

The bounded raw55 investigation did not observe `gEUseType_PhysicalFist` / raw 55. Tested transformations and several native body attackers resolved factual raw-8 `Fist`; weapon/magic controls resolved their own factual UseTypes. Raw55 remains unobserved/deferred, not globally disproven.

EV-247–EV-248 removed the earlier conservative human/species boundary for the tested raw-8 Normal/Power fixtures and classified Quick's native latch/timing mechanism. The bounded implementation `2c9f745106506fc6bdb009b35720a4bb7c81ea11` then admitted `AttackFamily_Quick` at the two existing FIST family gates only.

Post-change two-direction Sabretooth validation (`research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log`, source commit `1a0416b10bed694d47eb4809b7367b507228962d`) shows native and transformed Sabretooth Quick-left/right entering the existing FIST ownership path, accepting FIST, preserving Quick StatePosition 1, using the same latch/timing permission, and damaging through native `Game +0x16E348`. Traced `REJECTED_UNSUPPORTED_HIT` records belong to Action 9 using the PowerAttack-named motion, not Quick Action 4/5. No C1 invariant warning, repair divergence or exception was found; the diagnostic unloaded cleanly.

The supported/proven raw-8 FIST family set for the tested scope is therefore:

```text
Normal + Power + Quick
```

---

## Current Immediate Responsibility

> **Perform a complete collision-framework architecture audit before any larger NPC/mod-family compatibility test matrix.**

This is Normal Chat research/design first. Do not immediately refactor code.

Reason:

- collision is the mature foundation that later Raise/Speed/Config will join inside `Script_G3AnimationBehaviors`;
- remaining compatibility/stress tests should certify the architecture intended to survive into production;
- refactoring after those tests would leave avoidable uncertainty about whether the tested architecture still exists unchanged.

Primary authority:

```text
DESIGN.md modular architecture
BETWEEN_CHATS.md exact audit questions and next sequence
EV-208–EV-215 architecture foundation/verification
EV-221–EV-249 raw8 FIST evolution and current behavior
current source under prototypes/Script_FrameCollisionTest
```

Audit the full collision behavior structure for drift, especially but not only the raw8 FIST behavior/state accumulated in `EngineBridge.cpp`.

Target separation remains:

```text
EngineBridge
  sole physical Gothic hook owner
  hook transport / native fact delegation

FrameCollisionMarkers
  exact current-motion marker ownership and occurrence semantics

CollisionSources
  factual source identities / UseTypes

CollisionSourceOperations
  source-specific physical mutations

CollisionLifecycleGuard
  C1 generation/source obligations and terminal repair

Raw8FistCollision [candidate dedicated feature module]
  raw8 FIST execution state
  latch ownership policy
  timing-permission behavior and identity

Diagnostics
  diagnostic product only; absent from behavior-only production compilation
```

Hard audit rules:

```text
NO behavior change merely for aesthetics
NO competing feature hook owners
NO weakening diagnostics-free production separation
NO marker/source/lifecycle semantic redesign without concrete contradiction
NO AttackContinuationProtection implementation during this audit
NO Raise/speed/config implementation during this audit
NO new raw55 behavior
```

Determine which bridge-resident state/policy is genuine architectural drift and which pieces are legitimately hook-lifetime transport. In particular, do not assume `RunScriptFunctionScope` / the pre-combat bridge must move merely because it resides in `EngineBridge`; classify by responsibility and lifetime.

Once Normal Chat freezes the smallest justified correction, Work performs that bounded structural refactor. Then User + Normal Chat run one compact post-refactor equivalence sentinel before resuming compatibility testing.

Planned sentinel:

```text
Sabretooth raw8 Normal + Quick + Power
one ordinary marked equipped attack
one established multi-marker / OFF / rearm fixture
one established destructive bad-skip -> exact terminal repair
```

After the refactor sentinel passes, continue:

```text
native equipped-NPC marker tests: Goblin 1H / Demon 2H / Ogre Axe
-> additional prepared native/modded actor-family controls
-> separated 2H-vs-Axe mod marker compatibility
-> separated 1H-vs-Rapier mod marker compatibility
-> final native mixed/stress collision regression
-> separate AttackContinuationProtection
-> combined mature collision regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration into Script_G3AnimationBehaviors
-> diagnostics-free production validation
-> integrate Raise + Speed + Config
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
