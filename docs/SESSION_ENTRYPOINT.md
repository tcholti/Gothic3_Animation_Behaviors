# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-31

`docs/collision-source-evidence` contains the newest research/prototype state. `main` is the stable integration baseline.

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Frozen architecture rewrite: `docs/SECOND_PASS_REWRITE_CONTRACT.md`  
Project-wide release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`  
Validation authority: `docs/COLLISION_TEST_PLAN.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` / `docs/EVIDENCE_LEDGER_STEP_D.md`  
Recurring local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Mandatory Gothic 3 Release-Purity Rule

> **Every released Gothic 3 behavior DLL must contain behavior only. Research diagnostics are a separate build product and must not be compiled into the release binary.**

This applies to frame collision, lifecycle repair, AttackContinuationProtection, Raise, playback speed, target acquisition, climbing and all future systems.

Long-term model:

```text
shared behavior architecture
→ diagnostics-free RELEASE build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Never normally load release/behavior-only and diagnostic twins together. Canonical authority: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact current responsibility and latest accepted boundary.
3. Treat the release-purity rule above as standing architecture before proposing any script/DLL change.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, artifact naming, prototype/build labels or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

### If the previous Chat ended unexpectedly

```text
Open `tcholti/Gothic3_Animation_Behaviors` on branch `docs/collision-source-evidence`.

Read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap.
Then read the current `docs/BETWEEN_CHATS.md`.

Use repository documentation as authority. Do not reconstruct the project from old chat history and do not scan the whole repository.

When bootstrap is complete, tell me briefly:
- the current technical gate;
- the exact frozen responsibility;
- the key behavior invariants that must not change;
- which Gate 2 sentinels are already closed and which remain open.

Do not redesign outside the frozen responsibility.
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle and modular collision architecture.**

Governing invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision inside a live Hit. Terminal exact-source safety is a separate execution-level responsibility.

---

## Closed Collision-Safety Model

C1-R1 controlled validation is **CLOSED through EV-206–EV-207**.

Accepted lifecycle:

```text
real attack execution
→ monotonic C1 generation
→ successful exact-source Item_Attack request creates/refreshes obligation
→ successful later transition away from Item_Attack fulfills obligation
→ destructive post-native-AISetState finalization checks only remaining obligations
```

Accepted terminal repair remains exactly:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact Item_Equipped(5)
```

Native cleanup retains first opportunity. Everything outside the predicate remains no-op/unresolved and non-mutating.

Explicit qualifications that do not reopen R1:

```text
- no positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED case;
- no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

Do not invent another broad R1 program solely to force those branches.

---

## Proven Marker Invariants

Preserve until the later dedicated simplification gate:

```text
exact current-motion marker ownership
Normal / Quick / full-Whirl current family predicates
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window state
natural SetCollisionGroup retirement
OFF as an intra-Hit authored gap, not terminal cleanup
interruption/dead-execution rejection
unmarked/unsupported native fallback
current research Fist behavior without forcing weapon Item_Attack semantics
```

EV-131–EV-133 and EV-167 remain mandatory evidence before changing marker execution bookkeeping.

---

## Second-Pass Architecture Rewrite — IMPLEMENTED

Frozen contract: `docs/SECOND_PASS_REWRITE_CONTRACT.md`.

Implementation commit:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Implemented architecture:

```text
EngineBridge
├─ sole behavior-required Gothic hook owner
├─ FrameCollisionMarkers
├─ CollisionSources
├─ CollisionSourceOperations
├─ CollisionLifecycleGuard
└─ RuntimeClock

DIAGNOSTIC build additionally compiles compact CollisionDiagnostics
and opt-in CollisionDiagnosticsDeep capability.

BEHAVIOR-ONLY prototype excludes diagnostic sources/defines/hooks.
```

Gate 1 source/build validation is **CLOSED / PASS**:

```text
bounded source audit = PASS
git diff --check = PASS
Script_FrameCollisionTest Release build = PASS
Script_FrameCollisionBehaviorTest Release build = PASS
behavior-only target mechanically excludes diagnostic sources/defines/hooks = PASS
```

The deployed CORE diagnostic DLL was verified built/live identical:

```text
SHA256 25980C09DC0AB3ECAF69397F0AE3CA8D5566FF816B1210F44182D4508B292109
Length 417792
```

Startup/load-unload sentinel is **CLOSED / PASS** at commit `6bf59e6c08aebf6097566192b239092f0f734ea5`:

```text
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
expected behavior-core module list
Hooks installed.
Script_FrameCollisionTest unloading cleanly.
```

Evidence: EV-208.

---

## Current Technical Gate — GATE 2 CORE DIAGNOSTIC SUFFICIENCY

Gate 2 is **OPEN**. Do not deploy `Script_FrameCollisionBehaviorTest` yet.

Already closed/PASS in the post-rewrite CORE run:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  marked-source regression
PASS  clean shutdown
```

The mixed run is:

```text
research/raw/2026-08-30_second_pass_core_mixed_melee_bad_skip_attempts.log
commit a7995225310789c78a85cbce9940c86d41de74b0
```

It contains eight exact `REPAIRED_TO_ITEM_EQUIPPED` outcomes across 2H Whirl and 1H Quick plus ordinary clean/no-op and Normal/Quick/Whirl marker coverage.

Still open:

```text
OPEN  legitimate reaction cleanup no-op
OPEN  Dual source independence
OPEN  Fist/unarmed negative
OPEN  crossbow negative
```

### Immediate blocking finding

The focused reaction run is:

```text
research/raw/2026-08-30_second_pass_core_legitimate_reaction_cleanup_noop.log
commit 86d41d4772ebfc320d67ca063e51b28523fcfb9e
```

Visually the behavior looked correct and the CORE log contains healthy `7 -> 5` cleanup followed by `NO_OP_NO_OUTSTANDING`, but the compact logger cannot prove whether a particular cleanup was ordinary Hit→Recover or a legitimate damage-reaction cleanup.

Current compact `ENGINE SetCollisionGroup` records source/slot/requested/before/after/retirement facts but not player gameplay context. Therefore the required Gate-2 reaction fact is ambiguous.

Per the frozen Gate-2 rule:

> **If the compact logger makes a required fact ambiguous, the diagnostic reduction is too aggressive.**

This is a **diagnostic-sufficiency gap, not a demonstrated collision-behavior failure**.

Evidence: EV-209.

---

## Exact Frozen Next Responsibility

Make only this compact diagnostics correction:

```text
CollisionDiagnostics::LogSetCollisionGroup

restore the current player's:
- PlayerAction
- PlayerAniPhase
- PlayerStateTime
- PlayerCurrentMovementAni

on relevant compact ENGINE SetCollisionGroup records.
```

The fields use already-established actor APIs in the current diagnostic source.

Do **not**:

```text
restore deep stack/callsite probes
add hooks
change EngineBridge transport or ordering
change CollisionLifecycleGuard
change marker ownership/bookkeeping
change C1 predicates/repair semantics
change CollisionSourceOperations
change RuntimeClock
change the behavior-only target
turn deep diagnostics on by default
expand attack families or Fist semantics
begin AttackContinuationProtection / Raise / speed / compatibility / production migration
```

After the correction:

```text
bounded source audit
→ git diff --check for editable source
→ build Script_FrameCollisionTest
→ verify behavior-only separation was not touched (rebuild only if source/build change actually requires it)
→ deploy exact diagnostic DLL alone
→ verify built/live SHA + CORE startup identity
→ rerun only the focused legitimate-reaction sentinel
→ interpret compact evidence
```

If reaction cleanup becomes unambiguous and remains no-op, continue the remaining Gate-2 Dual/Fist/crossbow sentinels. If it is still ambiguous, reassess compact evidence needs before enabling deep diagnostics.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| exact current continuation | `BETWEEN_CHATS.md` |
| rewrite architecture/invariants | `SECOND_PASS_REWRITE_CONTRACT.md` |
| current staged validation | `COLLISION_TEST_PLAN.md` |
| current post-rewrite evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-208–EV-209 |
| C1-R1 exact evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| lifecycle safety contract | `COLLISION_LIFECYCLE_PLAN.md` |
| compact/deep diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| source/API/hook transport | `SOURCE_HOOK_GUIDE.md` |
| local build/deploy/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| future held-Use2 prevention | `BAD_SKIP_FUTURE_INVESTIGATION.md` |

Do not load the whole documentation corpus by default.

---

## Forward Order

```text
bounded CORE SetCollisionGroup context restoration — NEXT
→ focused legitimate-reaction CORE rerun
→ finish Gate 2 Dual/Fist/crossbow compact sentinels
→ Gate 2 compact diagnostic sufficiency CLOSED/PASS
→ behavior-only smoke/equivalence
→ dedicated C1-vs-marker bookkeeping simplification audit
→ equipped-melee marker expansion one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker + lifecycle regression
→ AttackContinuationProtection
→ mature research New Balance/Jackydima compatibility gate
→ migrate/redesign Raise + speed + config into mature modular foundation
→ later independent systems such as target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain separate diagnostic twin
```
