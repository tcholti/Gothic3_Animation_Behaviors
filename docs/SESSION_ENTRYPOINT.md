# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-31

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Validation authority: `docs/COLLISION_TEST_PLAN.md`  
Frozen architecture rewrite: `docs/SECOND_PASS_REWRITE_CONTRACT.md`  
Release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` / `docs/EVIDENCE_LEDGER_STEP_D.md`  
Local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Long-term model:

```text
shared behavior architecture
→ diagnostics-free RELEASE build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Never normally load release/behavior-only and diagnostic twins together.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact current responsibility and latest accepted boundary.
3. Treat the release-purity rule above as standing architecture.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, artifact naming, prototype/build labels or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

If the previous Chat ended unexpectedly, after bootstrap report briefly:

```text
current technical gate
exact immediate responsibility
Gate 2 / Gate 3 closure state
protected behavior/architecture invariants
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle and modular collision architecture.**

Governing invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision inside a live Hit. Terminal exact-source safety is a separate execution-level responsibility.

---

## Closed Safety / Marker Invariants

C1-R1 controlled validation is closed through EV-206–EV-207.

Terminal repair remains exactly:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact Item_Equipped(5)
```

Native cleanup always gets first opportunity.

Preserve these independent marker invariants while the simplification audit is active:

```text
exact current-motion marker ownership
Normal / Quick / full-Whirl predicates
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window retirement
OFF as an intra-Hit gap
late/dead-execution rejection
unmarked/unsupported native fallback
current research Fist behavior without forcing weapon Item_Attack semantics
```

Do not reopen C1-R1. Gate 4 may classify bookkeeping for removal only where stronger native/C1 authority genuinely supersedes execution-lifetime inference; it must not remove independent marker invariants merely because Gate 3 passed.

---

## Second-Pass Rewrite — IMPLEMENTED

Frozen contract: `docs/SECOND_PASS_REWRITE_CONTRACT.md`.

Implementation commit:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Architecture:

```text
EngineBridge
FrameCollisionMarkers
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
RuntimeClock
CollisionDiagnostics          diagnostic target only
CollisionDiagnosticsDeep      opt-in diagnostic/deep capability
```

Build products:

```text
Script_FrameCollisionTest
= CORE diagnostic research target

Script_FrameCollisionBehaviorTest
= behavior-only prototype target
= no diagnostic sources/defines/hooks
```

Gate 1 source/build separation is CLOSED/PASS. Evidence: EV-208.

---

## Gate 2 — CORE Diagnostic Sufficiency: CLOSED/PASS

The compact CORE diagnostic profile proved the complete frozen structural sentinel matrix without enabling deep diagnostics:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  legitimate reaction cleanup no-op
PASS  Dual source independence
PASS  marked-source regression
PASS  Fist/unarmed negative
PASS  crossbow negative
PASS  clean shutdown
```

Evidence: EV-209–EV-211.

Validated diagnostic DLL after the diagnostics-only context correction:

```text
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
```

The current tested Dual P1 Quick asset carries `G3AB_COL_RIGHT`, so the behavior follows RIGHT even though older native-source evidence maps tested Dual P1 Quick to LEFT. Preserve that as a later equipped-melee marker-authoring/source-map review item, not a Gate-2 lifecycle failure.

---

## Gate 3 — Behavior-Only Smoke / Equivalence: CLOSED/PASS

Purpose:

> **Prove intended collision behavior still works when diagnostic sources/state/hooks are not compiled or loaded.**

Authoritative local source head for the behavior-only build:

```text
2fb28e5a27333eb6da902dc5c1d46a11fbe0d809
```

Built and deployed behavior-only DLL:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

Deployment isolation was verified:

```text
only Script_FrameCollisionBehaviorTest.dll was live
built SHA == live SHA
Script_FrameCollisionTest.dll diagnostic target absent
```

Runtime observations:

```text
main menu reached successfully
normal main-menu exit succeeded
User then performed many different functional tests under the frozen Gate-3 exercise and reported everything working as intended
```

Because the behavior-only target intentionally contains no diagnostics, this is a **functional smoke/equivalence claim only**. It does not replace Gate-2 internal event evidence or create new internal lifecycle/source claims.

Gate 3 is CLOSED/PASS.

---

## Current Technical Gate — GATE 4 MARKER-BOOKKEEPING SIMPLIFICATION AUDIT

Immediate responsibility is **audit/classification only**. No source edit is authorized yet.

Question:

> Which current `FrameCollisionMarkers` execution/bookkeeping checks are now genuinely superseded by stronger native/C1 execution authority, and which remain independent marker invariants that must be preserved?

Required evidence route before proposing removals:

```text
EV-066–EV-075
EV-131–EV-133
EV-167
EV-182–EV-196
EV-206–EV-207
EV-209–EV-211
COLLISION_LIFECYCLE_PLAN.md §9
```

Classify each relevant current marker guard/check as:

```text
A. execution-lifetime inference genuinely superseded by stronger C1/native authority
B. independent marker invariant still required
```

Group B must continue to include, unless direct contradictory evidence is found:

```text
exact current-motion marker ownership
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
RIGHT/LEFT/BOTH/OFF exact-set behavior
StatePosition native-activation suppression
interruption/dead-execution rejection
```

Only after the audit is complete and a bounded simplification is frozen may Work/source implementation begin.

---

## Explicit Current Non-Goals

Do not combine Gate 4 audit with:

```text
source edits before classification is frozen
new hooks/deep probes
C1 redesign
new attack-family marker support
new/generalized Fist semantics
AttackContinuationProtection
Raise
speed/config redesign
New Balance / Jackydima compatibility work
production migration
target acquisition
climbing
```

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| exact current continuation | `BETWEEN_CHATS.md` |
| staged validation / Gate 4 audit | `COLLISION_TEST_PLAN.md` |
| rewrite architecture/invariants | `SECOND_PASS_REWRITE_CONTRACT.md` |
| post-rewrite evidence / Gate 2 closure | `EVIDENCE_LEDGER_STEP_D.md` EV-208–EV-211 |
| C1-R1 evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| lifecycle safety / simplification constraints | `COLLISION_LIFECYCLE_PLAN.md` §9 |
| diagnostics architecture | `COLLISION_LOGGER_PLAN.md` |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| local build/deploy procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |

---

## Forward Order

```text
Gate 4 marker-bookkeeping simplification audit — NEXT
→ freeze only evidence-supported bounded simplification, if any
→ implement/review/test that bounded simplification
→ equipped-melee marker expansion
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature research compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
