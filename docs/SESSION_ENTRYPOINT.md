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

Never normally load behavior-only and diagnostic twins together.

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
what exact architecture-verification steps still remain
what happens only after architecture verification is complete
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

## Current Technical Responsibility — Finish Verification of the New Architecture

The project is **not moving on to documentation audit, branch cleanup or new marker expansion yet**.

EV-213 validly closed Gate 4 under the evidence already collected, including the equivalent two-contact full-Whirl no-leak proof. However, the User clarified that the original two-marker/two-contact 2H Normal historical regression fixture still exists in Blender and was simply not exported/installed for the last test.

Before declaring the new architecture fully verified for the next project phase, finish two final steps:

```text
1. literal EV-131-class diagnostic regression with the restored two-marker 2H Normal fixture
2. final behavior-only smoke with that restored fixture and ordinary melee afterwards
```

Only after **both** pass is architecture verification complete.

### Step 1 — literal EV-131 historical regression

Required causal route before freezing the test:

```text
EV-131 historical occurrence-budget leak
EV-132–EV-133 historical correction/test fixture
EV-213 generation-scoped replacement and equivalent Whirl proof
MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
COLLISION_TEST_PLAN.md
```

The User must first export/install the preserved Blender two-contact 2H Normal fixture.

Before attempting interruption, verify through CORE diagnostics that the live fixture is actually correct:

```text
Actor: PC_Hero
Family: NORMAL
exact intended 2H Normal motion
ContainsReservedSourceMarker: 1
AuthoredRIGHTCount: 2
```

Then prove:

```text
marked two-contact Normal execution A
→ first genuine RIGHT accepted under generation A
→ execution A interrupted before later genuine RIGHT

immediate next attack execution B
→ same exact Normal motion as A
→ different fresh C1 generation
→ first RIGHT starts fresh budget: 0 -> 1, ExecutionBudgetReset: 1
→ later genuine RIGHT accepted: 1 -> 2
→ replay protection remains intact
→ no REJECTED_NO_C1_GENERATION
→ no REJECTED_C1_GENERATION_INCONSISTENCY
→ no INVARIANT / DIVERGED / UNRESOLVED signal
→ clean diagnostic shutdown
```

If this fails, **reopen Gate 4 and stop**. Do not audit, promote or begin new feature work.

If it passes, record the literal historical confirmation as the next global evidence item. Preserve EV-213 and its Whirl-equivalent proof unchanged as valid prior evidence.

No source rebuild is required merely because the animation fixture changes.

### Step 2 — final behavior-only architecture smoke

After the exact diagnostic regression passes:

```text
remove diagnostic twin
→ deploy the already-validated Gate 4 behavior-only DLL alone
→ verify exact built/live identity
→ main-menu load/normal exit
→ test the restored two-contact Normal fixture visibly
→ perform several interruption/restart attempts
→ then ordinary Staff / 1H / 2H combat
→ confirm no stuck collision, crash or obvious regression
→ normal exit
```

Authoritative Gate 4 behavior-only identity:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

This final smoke is a functional/release-purity check only; internal proof remains the diagnostic evidence.

If both final steps pass:

```text
NEW ARCHITECTURE VERIFICATION = COMPLETE
```

Do not invent another broad matrix unless these tests expose a concrete contradiction.

---

## Only After Architecture Verification Is Complete — Documentation / Knowledge-System Audit

The User is not in a rush to audit. The audit begins **only after the new architecture has been completely verified**.

This is then the correct stable-subsystem checkpoint under `KNOWLEDGE_MAINTENANCE.md` and `KNOWLEDGE_REGISTRY.md`.

Audit for:

```text
contradictions between current authorities
unnecessary repeated narrative facts
same fact independently maintained in multiple documents
stale current-state or closed-contract wording
bootstrap/read-first bloat
index routes that no longer narrow retrieval
ledger continuation clarity and global EV continuity
EVIDENCE_LEDGER / STEP_B / STEP_C / STEP_D duplication versus useful storage splitting
processed artifacts unnecessarily left in research/raw
active vs archive boundaries
superseded documents that should be archived or compressed
redundant/speculative future-use cross-routes
```

Important boundary:

> **Do not merge/delete evidence ledgers or authorities merely because several files exist. First determine whether the split is useful retrieval/storage structure or actual duplication. Preserve provenance and global EV IDs.**

The audit should first produce concise findings + proposed cleanup. Perform destructive merge/delete/archive actions only when justified and after the User can review material changes.

---

## After the Audit — Stable Main Update and Branch Cleanup

`PROJECT_PIPELINE.md` already defines the intended normal two-branch model:

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research branch
```

`main` is currently stale. After architecture verification and the documentation audit/cleanup, this is the natural checkpoint to bring `main` up to the proven, reviewed architecture baseline.

A third temporary branch currently exists:

```text
temp/second-pass-rewrite-publish
```

Do **not** simply delete it. Comparison on 2026-09-01 showed:

```text
active branch ahead of temp by 35 commits
temp branch ahead of active by 10 commits
merge base: 0aa6d19a6815934a3158715070320020bac64292
```

Required sequence:

```text
architecture verification complete
→ documentation/knowledge audit complete
→ justified documentation cleanup complete
→ inspect temp-only commits/content
→ preserve anything unique that still matters
→ define stable promotion set
→ deliberately integrate proven + cleaned checkpoint into protected main
→ verify main
→ delete temp/second-pass-rewrite-publish only if safe
→ retain main + docs/collision-source-evidence as normal two-branch model
→ continue new work on docs/collision-source-evidence
```

Do not change branch meanings merely to achieve a branch count of two.

---

## Forward Order

```text
restore two-contact 2H Normal fixture — NEXT
→ literal EV-131 same-motion interruption/restart diagnostic regression
→ final behavior-only restored-fixture + ordinary-melee smoke
→ architecture verification COMPLETE
→ documentation + knowledge-system audit
→ review findings and perform justified cleanup/consolidation
→ inspect temp-only branch history
→ update protected main to proven + cleaned stable checkpoint
→ verify main
→ retire temp branch if safe
→ normal two-branch model restored
→ continue collision-source branch
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
