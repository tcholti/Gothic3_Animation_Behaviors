# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-09

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate transient handoff: `docs/BETWEEN_CHATS.md`  
Current redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
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
raw-8 Quick FIST family extension          CLOSED/PASS — EV-249
```

Do not reopen these exact closed conclusions without concrete contradictory evidence.

Raw-8 FIST remains FIST-only: no authored FIST_OFF, no Fist ClearTriggeredList, no equipped weapon source window/C1 physical repair, and no direct/custom damage.

The bounded raw55 investigation did not observe `gEUseType_PhysicalFist` / raw 55. Tested transformations and several native body attackers resolved factual raw-8 `Fist`; weapon/magic controls resolved their own factual UseTypes. Raw55 remains unobserved/deferred, not globally disproven.

EV-247–EV-248 removed the earlier conservative human/species boundary for the tested raw-8 Normal/Power fixtures and classified Quick's native latch/timing mechanism. The bounded implementation `2c9f745106506fc6bdb009b35720a4bb7c81ea11` admitted `AttackFamily_Quick` at the two existing FIST family gates only.

EV-249 / `research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log` then closed Quick in both native-Sabretooth -> player and transformed-Hero -> native-Sabretooth directions. Quick-left/right accepted FIST, preserved StatePosition 1, used the existing latch/timing permission, and damaged through native `Game +0x16E348`.

The supported/proven raw-8 FIST family set for the tested scope is therefore:

```text
Normal + Power + Quick
```

---

## Newly Identified Missing Family — SprintAttack

The EV-249 validation log repeatedly contains:

```text
Actor: Sabertooth
Action: 9
CurrentMovementAni: ...PowerAttack_Hit...
G3AB_COL_FIST = REJECTED_UNSUPPORTED_HIT
```

Gothic action identity establishes:

```text
gEAction_SprintAttack = 9
```

These records are therefore **SprintAttack executions that reuse a PowerAttack-named motion**. They are not `gEAction_PowerAttack` failures and not Quick failures.

Current collision source has no `AttackFamily_Sprint` and no SprintAttack family adapter/hook plumbing. SprintAttack is now a factual missing family that the finished framework should investigate and, where evidence supports it, implement as a first-class family.

Current evidence limit:

```text
observed Sprint actor/source: native Sabretooth -> Fist/raw8
other actors/source types: not yet established
prior project tests: SprintAttack had not surfaced
```

Do not infer Sprint behavior from the `_PowerAttack_` filename, do not add a Sabretooth exception, and do not assume Sprint is Fist-only or equipped-capable before evidence.

Canonical planning authority: `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

---

## Current Immediate Responsibility

> **Perform the complete collision-framework architecture AND diagnostic-volume audit before any larger NPC/mod-family compatibility matrix.**

This is Normal Chat research/design first. Do not immediately refactor code and do not begin Sprint implementation yet.

Reason:

- collision is the mature foundation that later Raise/Speed/Config will join inside `Script_G3AnimationBehaviors`;
- remaining compatibility/stress tests should certify the architecture intended to survive into production;
- the current logger still carries research-era verbosity that makes larger tests unnecessarily difficult to process;
- Sprint must be accommodated cleanly by the architecture rather than bolted onto current drift.

Primary authority:

```text
COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
DESIGN.md modular architecture
COLLISION_LOGGER_PLAN.md diagnostic architecture
BETWEEN_CHATS.md exact next-session handoff
EV-208–EV-215 architecture foundation/verification
EV-221–EV-249 raw8 FIST evolution/current behavior
current source under prototypes/Script_FrameCollisionTest
```

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
  production: not compiled
  CORE: compact known-path regression evidence
  DEEP: opt-in research instrumentation
  unknown/anomalous behavior: automatically richer evidence
```

Governing bridge rule:

```text
EngineBridge = physical hook ownership + transport + delegation
EngineBridge != feature policy/state-machine ownership
```

Do not assume every bridge-local object is drift. State whose lifetime is inherently one hook invocation/transport scope may legitimately stay there. Classify by responsibility and lifetime.

Diagnostic redesign rule:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

CORE must remain capable of discovering Sprint and other unknown families/source UseTypes while substantially reducing repeated healthy-path state dumps. Reusable detailed probes should move to DEEP or become condition/anomaly-driven rather than simply being deleted.

Hard audit rules:

```text
NO behavior change merely for aesthetics
NO competing feature hook owners
NO weakening diagnostics-free production separation
NO marker/source/lifecycle semantic redesign without concrete contradiction
NO Sprint behavior implementation during parity refactor
NO AttackContinuationProtection implementation during this audit
NO Raise/speed/config implementation during this audit
NO new raw55 behavior
```

Once Normal Chat freezes the smallest justified correction, Work performs bounded structural/diagnostic refactor task(s). Then User + Normal Chat run one compact post-refactor equivalence sentinel before Sprint investigation or broader compatibility testing.

Planned sentinel:

```text
Sabretooth raw8 Normal + Quick + Power
one ordinary marked equipped attack
one established multi-marker / OFF / rearm fixture
one established destructive bad-skip -> exact terminal repair
```

After sentinel PASS:

```text
SprintAttack factual source/transport/mechanism investigation
-> bounded Sprint implementation only if evidence supports it
-> focused Sprint validation
-> native equipped-NPC marker tests: Goblin 1H / Demon 2H / Ogre Axe
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
