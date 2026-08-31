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
Gate 2 sentinels already closed/open
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

Do not reopen C1-R1 or simplify marker bookkeeping during the current gate.

---

## Second-Pass Rewrite — IMPLEMENTED / GATE 1 PASS

Frozen contract: `docs/SECOND_PASS_REWRITE_CONTRACT.md`.

Implementation commit:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Architecture now separates:

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

Gate 1 source/build validation and the original post-rewrite CORE startup/load-unload sentinel are closed/PASS. Evidence: EV-208.

---

## Current Technical Gate — GATE 2 CORE DIAGNOSTIC SUFFICIENCY

Already PASS in the post-rewrite CORE run:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  marked-source regression
PASS  clean shutdown
```

Still OPEN:

```text
OPEN  legitimate reaction cleanup no-op
OPEN  Dual source independence
OPEN  Fist/unarmed negative
OPEN  crossbow negative
```

The focused reaction run looked correct visually and logged healthy `7 -> 5` cleanup with `NO_OP_NO_OUTSTANDING`, but the reduced CORE logger lacked enough gameplay context to prove whether a specific cleanup was ordinary Hit→Recover or legitimate reaction cleanup.

Classification:

```text
CORE DIAGNOSTIC SUFFICIENCY GAP
NOT a demonstrated behavior failure
```

---

## CORE Context Restoration — IMPLEMENTED / SOURCE REVIEW PASS

Frozen one-file correction was implemented and published at:

```text
5b92b79a5af63c38e66a7ec8deecd0876c2cf141
Restore Gate 2 SetCollisionGroup context
```

Changed file only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

`CollisionDiagnostics::LogSetCollisionGroup` now restores these current-player fields on relevant compact `ENGINE SetCollisionGroup` records:

```text
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
```

Independent Normal Chat review: **PASS**.

The diff is diagnostics-only and does not change:

```text
EngineBridge hooks/transport/order
CollisionLifecycleGuard / C1 semantics
FrameCollisionMarkers
CollisionSources / CollisionSourceOperations
RuntimeClock
CMake product separation
Script_FrameCollisionBehaviorTest
DeepDiagnostics default state
```

No source/API/calling-convention contradiction was found.

---

## Exact Next Responsibility — WINDOWS BUILD / RUNTIME VALIDATION

**Do not assign another behavior/source change before this validation.**

When the User is back on the authoritative Windows build/game PC:

```text
sync local branch to latest remote head
→ build Script_FrameCollisionTest Release
→ deploy diagnostic DLL only
→ verify exactly one intended live collision DLL
→ verify built/live SHA equality
→ verify CORE startup identity with DeepDiagnostics DISABLED
→ rerun only focused legitimate-reaction cleanup/no-op sentinel
→ preserve new raw log
→ interpret whether restored action/phase/state/motion makes reaction cleanup unambiguous
```

Because the change is confined to diagnostic-only source, `Script_FrameCollisionBehaviorTest` does not need to be rebuilt unless a later diff crosses the behavior/build boundary.

If reaction cleanup is proved unambiguously and remains no-op, continue Gate 2 with:

```text
Dual source independence
Fist/unarmed negative
crossbow negative
```

If still ambiguous, reassess the smallest compact evidence addition before enabling deep diagnostics.

If the User is on a non-build PC, planning/review may continue, but **the technical gate must not advance past this build/runtime boundary**.

---

## Explicit Current Non-Goals

Do not combine this gate with:

```text
new hooks or deep stack/callsite probes
C1 redesign
marker simplification
new marker families
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
| staged validation | `COLLISION_TEST_PLAN.md` |
| rewrite architecture/invariants | `SECOND_PASS_REWRITE_CONTRACT.md` |
| current post-rewrite evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-208–EV-209 |
| C1-R1 evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| lifecycle safety | `COLLISION_LIFECYCLE_PLAN.md` |
| diagnostics architecture | `COLLISION_LOGGER_PLAN.md` |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| local build/deploy/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |

---

## Forward Order

```text
Windows build/deploy of 5b92b79... — NEXT
→ focused legitimate-reaction CORE rerun
→ finish Gate 2 Dual/Fist/crossbow sentinels
→ Gate 2 CLOSED/PASS
→ behavior-only smoke/equivalence
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
