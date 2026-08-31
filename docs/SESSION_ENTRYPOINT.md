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
Gate 2 closure state
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

Preserve marker invariants until the later dedicated simplification gate:

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

Do not reopen C1-R1 or simplify marker bookkeeping during Gate 3.

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

The compact CORE diagnostic profile has now proved the complete frozen structural sentinel matrix without enabling deep diagnostics.

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

Evidence:

```text
EV-209  mixed CORE positive/ordinary/marker/shutdown pass + reaction ambiguity
EV-210  compact SetCollisionGroup context restoration + unambiguous reaction rerun
EV-211  Dual/Fist/crossbow completion and Gate 2 closure
```

The diagnostic-only context correction was implemented at:

```text
5b92b79a5af63c38e66a7ec8deecd0876c2cf141
Restore Gate 2 SetCollisionGroup context
```

Validated diagnostic DLL after that correction:

```text
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
```

The focused reaction rerun proved reaction-owned cleanup unambiguously from restored action/phase/state-time/current-motion context and remained `NO_OP_NO_OUTSTANDING` with no repair. Dual exact-source independence, Fist group-0 non-ownership and crossbow/Bolt negative behavior then passed cleanly.

One later marker-expansion note is preserved in EV-211: the current tested Dual P1 Quick asset carries `G3AB_COL_RIGHT`, so the behavior correctly follows the authored RIGHT marker even though older native-source evidence maps tested Dual P1 Quick to LEFT. Treat that as a later marker-authoring/source-map review item, not a Gate-2 lifecycle failure.

---

## Current Technical Gate — GATE 3 BEHAVIOR-ONLY SMOKE / EQUIVALENCE

Purpose:

> **Prove the intended collision behavior still works when the diagnostic sources/state/hooks are not compiled or loaded.**

The exact Gate 3 matrix is frozen in `docs/COLLISION_TEST_PLAN.md`.

### Required local sequence

```text
sync local branch to latest remote head
→ build Script_FrameCollisionBehaviorTest Release
→ identify/hash exact built behavior-only DLL
→ remove the diagnostic prototype from the live scripts directory
→ deploy Script_FrameCollisionBehaviorTest.dll alone
→ verify exactly one intended collision prototype DLL is live
→ verify built/live SHA equality
→ main-menu load/exit smoke
→ run the frozen small behavior-only functional matrix
→ report observations
```

No diagnostic log is expected from the behavior-only target. Do **not** reintroduce or co-load diagnostics merely to manufacture Gate-3 log evidence.

### Frozen Gate 3 functional matrix

```text
A. marked 2H Normal positive
   - perform 2–3 marked 2H Normal attacks against a target
   - intended attack damage/contact must still occur

B. stale-source repair functional smoke
   - use the established vulnerable 2H full-Whirl held-Use2 bad-skip reproduction
   - perform 3 attempts where the attack has already made an offensive contact before the destructive skip
   - after returning to Ambient/running, touch/run into the target without attacking
   - there must be no passive stale-weapon damage
   - a following ordinary attack must still damage normally

C. unsupported/native-fallback smoke
   - perform 3 normal crossbow shot cycles against a target
   - aim/shoot/reload flow must remain normal
   - no melee-marker/repair behavior may visibly interfere

D. exit Gothic 3 normally
```

Acceptance:

```text
no load/runtime crash
marked melee positive behavior remains functional
known stale-source consequence is absent after destructive skip
later legitimate melee attack still functions
crossbow/native fallback remains functional
normal exit
```

This is intentionally smaller than Gate 2. Gate 3 validates diagnostics independence, not the already-closed diagnostic sentinel matrix again.

---

## Explicit Current Non-Goals

Do not combine Gate 3 with:

```text
new source changes
new hooks/deep probes
C1 redesign
marker simplification
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
| staged validation / Gate 3 matrix | `COLLISION_TEST_PLAN.md` |
| rewrite architecture/invariants | `SECOND_PASS_REWRITE_CONTRACT.md` |
| post-rewrite evidence / Gate 2 closure | `EVIDENCE_LEDGER_STEP_D.md` EV-208–EV-211 |
| C1-R1 evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| lifecycle safety | `COLLISION_LIFECYCLE_PLAN.md` |
| diagnostics architecture | `COLLISION_LOGGER_PLAN.md` |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| local build/deploy/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |

---

## Forward Order

```text
Gate 3 behavior-only build/deploy/functional smoke — NEXT
→ Gate 3 CLOSED/PASS if clean
→ dedicated marker-bookkeeping simplification audit
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
