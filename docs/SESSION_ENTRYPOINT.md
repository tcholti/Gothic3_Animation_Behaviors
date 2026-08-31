# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-31

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Validation authority: `docs/COLLISION_TEST_PLAN.md`  
Frozen Gate 4 implementation: `docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`  
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
Gate 1 / Gate 2 / Gate 3 closure state
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

Preserve these independent marker invariants through Gate 4 implementation:

```text
exact current-motion marker ownership
Normal / Quick / full-Whirl predicates
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned active source/window state
natural retirement of exact physical source bits
OFF as an intra-Hit gap
late/dead/unsupported marker rejection
unmarked/unsupported native fallback
current research Fist behavior without forcing weapon Item_Attack semantics
```

Gate 4 may replace only marker-local execution-lifetime inference with the already-proven monotonic C1 generation. C1 does not replace authored marker semantics.

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

Authoritative local source head for the tested behavior-only build:

```text
2fb28e5a27333eb6da902dc5c1d46a11fbe0d809
```

Built/deployed behavior-only DLL:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

It was deployed alone, reached main menu, exited normally, and the User then performed many different functional tests under the frozen Gate-3 exercise and reported everything working as intended.

This is a functional smoke/equivalence claim only. Gate 2 remains the internal diagnostic evidence authority.

Evidence: EV-212.

---

## Current Technical Gate — GATE 4 BOUNDED MARKER-BOOKKEEPING IMPLEMENTATION

Gate 4 audit/classification is CLOSED/PASS.

Frozen authority:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
```

Audit conclusion:

> **Use the already-existing monotonic C1 generation as durable marker-execution identity where that generation is valid. Remove marker-local guesses about new-execution boundaries. Preserve all independent marker semantics and protections.**

### Superseded marker-local lifetime inference

The bounded implementation may remove/consolidate:

```text
controlled-callback key/state-time retirement
lastControlledCallbackStateTime
MarkerWindowStillMatchesActorExecution lifetime inference
new-execution reset inferred from source/motion/action/phase/state-time changes
authored-count change used as a new-execution trigger
whole-execution retirement inferred from natural source cleanup
```

### Required replacement

Expose one read-only current-generation fact from `CollisionLifecycleGuard`:

```text
actor record exists -> exact current monotonic generation
no actor record -> invalid token
no creation/replacement/finalization/mutation
```

Marker occurrence/dedupe execution records become scoped to that generation.

```text
different valid generation -> fresh budget/dedupe execution
same valid generation -> do not silently reset budget because incidental identity facts changed
```

Unexpected contradiction within one generation must fail closed/reject rather than fabricate a new execution.

### Natural source retirement remains

Keep the existing SetCollisionGroup bridge and `RetireMarkerOwnedSource()` responsibility for factual physical marker-window state:

```text
exact source leaves Item_Attack
→ clear that exact active source bit
→ erase window if no bits remain
```

It must no longer guess that the occurrence/dedupe execution ended by rechecking action/phase/motion/state time.

### Critical implementation stop rule

`FrameCollisionMarkers` does not create or finalize C1 generations.

If implementation/source audit finds a marker point that requires generation-scoped bookkeeping but has no valid C1 generation, or finds a concrete source/API/calling-convention contradiction, **STOP and report rather than inventing a fallback execution-ID scheme.**

### Expected bounded source scope

```text
CollisionLifecycleGuard.h/.cpp
FrameCollisionMarkers.h/.cpp
FrameCollisionShared.h only if required for factual transport
EngineBridge.cpp only if required for factual generation transport
CollisionDiagnostics.cpp/.h only if compact validation observability requires it
```

No new hooks. No attack-family expansion. No C1 repair changes. No marker semantic changes.

After implementation: source audit + `git diff --check` + commit/push, then STOP. Do not build/run Gothic 3 inside the bounded Work task.

---

## Gate 4 Post-Implementation Validation — FROZEN

After independent Normal Chat source review:

```text
1. same-motion two-contact attack:
   genuine first/later markers accepted
   replay callbacks rejected

2. interrupted after first marker -> immediate same-motion new attack:
   fresh C1 generation
   fresh occurrence budget
   later genuine marker accepted

3. OFF / exact-set switching:
   remains inside one generation

4. natural cleanup:
   exact physical marker-window bit retires
   no fabricated new generation

5. marked full-Whirl destructive bad skip:
   dead/late callbacks cannot reopen collision
   C1 repair remains unchanged

6. no invariant/divergence/unresolved/failure signal
   clean shutdown
```

Behavior-only smoke follows only after the diagnostic regression passes.

---

## Explicit Current Non-Goals

Do not combine Gate 4 implementation with:

```text
new hooks/deep probes
C1 redesign
new attack-family marker support
new/generalized Fist semantics
Dual P1 Quick marker-authoring correction
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
| frozen Gate 4 source responsibility | `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md` |
| staged validation | `COLLISION_TEST_PLAN.md` |
| rewrite architecture/invariants | `SECOND_PASS_REWRITE_CONTRACT.md` |
| post-rewrite evidence / Gates 1–3 | `EVIDENCE_LEDGER_STEP_D.md` EV-208–EV-212 |
| historical marker lifecycle defect | `EVIDENCE_LEDGER.md` EV-131–EV-133; Step B EV-167 |
| lifecycle safety / simplification constraints | `COLLISION_LIFECYCLE_PLAN.md` §9 |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| local build/deploy procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |

---

## Forward Order

```text
Gate 4 bounded implementation — NEXT
→ independent Normal Chat source review
→ frozen CORE marker-generation regression
→ behavior-only smoke if diagnostic regression passes
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
