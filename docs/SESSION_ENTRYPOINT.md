# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Validation authority: `docs/COLLISION_TEST_PLAN.md`  
Gate 4 contract: `docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`  
Frozen architecture rewrite: `docs/SECOND_PASS_REWRITE_CONTRACT.md`  
Knowledge-maintenance/audit rules: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Branch/convention authority: `docs/PROJECT_PIPELINE.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` / `docs/EVIDENCE_LEDGER_STEP_D.md`  
Local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

```text
shared behavior architecture
→ diagnostics-free RELEASE/behavior-only build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Never normally load the behavior-only and diagnostic twins together.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact current responsibility and latest accepted boundary.
3. Treat the release-purity rule above as standing architecture.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, artifact naming, build labels, branch meanings or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

After bootstrap, report briefly:

```text
current technical responsibility
Gates 1–4 evidence state
exact historical regression still required before promotion checkpoint
what comes after that regression
```

---

## Closed Foundations — Do Not Reopen Without Contradicting Evidence

### C1-R1 lifecycle safety

Closed through EV-206–EV-207.

```text
successful exact-source Item_Attack request
→ exact source obligation

successful transition away from Item_Attack
→ obligation fulfilled

post-native-AISetState finalization
+ exact obligation still outstanding
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList
→ verify exact group 5
```

Native cleanup always gets first opportunity.

Retained qualifications:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / physical-repair case claimed
```

### Second-pass architecture / product gates

```text
Gate 1 source/build separation            CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency        CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping      CLOSED/PASS by current evidence — EV-213
```

Second-pass architecture implementation:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Gate 4 implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Accepted Gate 4 architecture:

> **The monotonic C1 generation is the durable marker occurrence/dedupe execution identity. Marker-local guesses based on source/motion/action/phase/state-time are no longer execution-boundary authority. Authored marker semantics remain independent.**

Preserve RIGHT/LEFT/BOTH/OFF exact-set semantics, occurrence budgets, duplicate/replay suppression, repeated-contact rearm, supported-family ownership, physical marker-window retirement, StatePosition behavior, late/dead rejection, native fallback and the closed C1 terminal-repair contract.

---

## Current Technical Responsibility — Exact EV-131 Historical Regression Confirmation

EV-213 validly closed Gate 4 using the equivalent two-contact full-Whirl no-leak proof because the **installed** marked 2H Normal P0 asset in that run had only one authored RIGHT.

The User has now clarified that this was a test-fixture misunderstanding: the original **two-marker/two-contact 2H Normal regression fixture still exists in Blender** and simply was not exported/installed for the final run.

Therefore, before treating the new architecture as ready for its stable promotion/documentation checkpoint, perform one final literal EV-131-class confirmation with that restored Normal fixture.

This is a **confidence/promotion completion**, not a source redesign. EV-213 remains valid evidence; do not erase or rewrite the Whirl-equivalent proof.

Required causal route before freezing the test:

```text
EV-131  historical occurrence-budget leak
EV-132–EV-133 historical correction/test fixture
EV-213  generation-scoped replacement and equivalent Whirl proof
MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
COLLISION_TEST_PLAN.md
```

Required result:

```text
marked two-contact 2H Normal execution A
→ first RIGHT accepted under generation A
→ execution interrupted before later genuine RIGHT

next same exact Normal motion execution B
→ different fresh C1 generation
→ first RIGHT starts a fresh occurrence budget (0 -> 1, ExecutionBudgetReset: 1)
→ later genuine RIGHT is accepted (1 -> 2)
→ replay protection remains intact
→ no no-generation / generation-inconsistency / invariant / divergence / unresolved signal
→ clean shutdown
```

If the exact historical confirmation fails, **reopen Gate 4 and stop before documentation audit/promotion work**.

If it passes, record the literal confirmation as the next evidence item and complete one compact behavior-only fixture smoke if useful; no source rebuild is required merely because the animation fixture changed.

Do not begin equipped-melee expansion before this checkpoint sequence is complete.

---

## Mandatory Checkpoint After Exact Gate 4 Confirmation — Documentation / Knowledge-System Audit

The User explicitly wants a broad documentation review **after the new architecture is fully tested and before branch/stable-integration cleanup or new marker expansion**.

This is an appropriate stable-subsystem/promotion checkpoint under `KNOWLEDGE_MAINTENANCE.md`.

The audit must review the repository knowledge system for:

```text
contradictions between current authorities
unnecessary repeated narrative facts
same fact maintained independently in multiple documents
stale current-state or closed-contract wording
bootstrap/read-first bloat
index routes that no longer narrow retrieval
ledger continuation clarity and monotonic EV continuity
EVIDENCE_LEDGER / STEP_B / STEP_C / STEP_D duplication versus useful storage splitting
processed artifacts still unnecessarily left in research/raw
active vs archive boundaries
superseded documents that should be archived or compressed
future-use cross-routes that became speculative or redundant
```

Important boundary:

> **Do not merge/delete evidence ledgers or authorities merely because there are several files. First determine whether the split is useful retrieval/storage structure or actual duplication. Preserve provenance and old evidence IDs.**

The audit should first produce a concise findings/cleanup plan. Perform destructive merge/delete/archive actions only after the rationale is clear and the User has had a chance to review material changes.

---

## Branch / Stable-Integration Checkpoint After Documentation Audit

`PROJECT_PIPELINE.md` already defines the intended normal two-branch model:

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research branch
```

The repository currently has a third temporary branch:

```text
temp/second-pass-rewrite-publish
```

Do **not** simply delete it. A comparison on 2026-09-01 showed it is diverged from the active branch:

```text
active branch ahead of temp by 35 commits
temp branch ahead of active by 10 commits
merge base: 0aa6d19a6815934a3158715070320020bac64292
```

After the documentation audit:

```text
inspect the temp-only commits/content
→ identify anything unique that still needs preservation
→ define the stable promotion set for the proven new architecture/docs
→ deliberately integrate the stable checkpoint into protected main
→ verify main
→ delete temp/second-pass-rewrite-publish only if its unique history/content is safely preserved or intentionally superseded
→ retain main + docs/collision-source-evidence as the normal two-branch model
```

Do not change branch meanings merely to achieve a branch count of two.

---

## Forward Order

```text
exact restored two-contact 2H Normal EV-131 regression — NEXT
→ evidence/behavior-only closure confirmation
→ documentation + knowledge-system audit
→ review findings and perform justified cleanup/consolidation
→ stable-integration checkpoint to main
→ verify and retire temp/second-pass-rewrite-publish if safe
→ return to normal two-branch model
→ equipped-melee marker expansion planning
→ freeze/implement/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
