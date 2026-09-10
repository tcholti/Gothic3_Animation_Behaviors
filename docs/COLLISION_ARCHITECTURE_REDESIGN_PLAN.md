# Collision Architecture and Diagnostic Redesign Plan

**Status:** Canonical audit result and staged refactor authority  
**Updated:** 2026-09-10  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Freeze the completed collision architecture audit after EV-249 and define the exact staged refactor sequence before SprintAttack investigation and the remaining compatibility matrix.

This document does **not** authorize broad source redesign. Normal Chat freezes each bounded Work task separately under `WORK_IMPLEMENTATION_PROTOCOL.md`.

Related authorities:

```text
SESSION_ENTRYPOINT.md          current front door
BETWEEN_CHATS.md               exact handoff
DESIGN.md                      overall intended architecture
COLLISION_LOGGER_PLAN.md       diagnostic architecture
COLLISION_TEST_PLAN.md         validation authority
EVIDENCE_LEDGER_232_ONWARD.md  runtime evidence through EV-249
```

---

## 1. Closed Starting Point

Raw-8 FIST Quick is CLOSED/PASS for the tested native/transformed Sabretooth fixture.

```text
implementation: 2c9f745106506fc6bdb009b35720a4bb7c81ea11
validation:     research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log
evidence:       EV-249
```

Supported/proven raw-8 FIST families for the tested scope:

```text
Normal + Power + Quick
```

Preserve the single existing raw-8 mechanism. No Quick-specific hook, species branch, raw55 behavior, FIST_OFF, Fist ClearTriggeredList, equipped Fist window, direct damage, or weapon-C1 obligation is justified.

---

## 2. SprintAttack Boundary

EV-249 also exposed repeated native Sabretooth traffic with:

```text
Action: 9 = gEAction_SprintAttack
motion: ...PowerAttack_Hit...
source: Fist / raw8
G3AB_COL_FIST: REJECTED_UNSUPPORTED_HIT
```

These are SprintAttack executions reusing a PowerAttack-named motion. Factual action identity outranks filename naming.

Current source has no `AttackFamily_Sprint` and no Sprint callback/adapter plumbing. Sprint is therefore a factual missing family to investigate after the refactor and sentinel.

Current evidence does **not** establish Sprint as Fist-only, creature-only, Power-equivalent, or equipped-capable.

Do not add a Sabretooth-specific exception and do not implement Sprint during the parity refactor.

---

## 3. Architecture Audit Result

The audit found that most of the mature collision architecture is already correctly separated.

### Keep as-is by responsibility

```text
CollisionSources
  factual equipped/Fist source identity and UseType resolution

CollisionSourceOperations
  equipped physical source mutation and ClearTriggeredList behavior

CollisionLifecycleGuard
  C1 generation/source ownership, pre-combat acquisition policy,
  outstanding obligations, cleanup reconciliation and repair decision

RunScriptFunctionScope in EngineBridge
  legitimate hook-invocation transport lifetime for the pre-combat bridge

EngineBridge physical hook ownership
  exactly one owner per Gothic hook/call-site

CMake product separation
  behavior-only target excludes diagnostic source files;
  diagnostic target adds CORE and optional DEEP definitions/sources

FrameCollisionMarkers
  current-motion scan, reserved-marker ownership, occurrence/dedupe,
  equipped RIGHT/LEFT/BOTH/OFF semantics, family/phase marker eligibility,
  StatePosition marker semantics
```

Do **not** split these further merely for aesthetics.

### Confirmed structural drift

Four bounded corrections are justified:

1. **Raw-8 FIST feature policy/state is split across modules.**
   - initial marked-execution latch ownership, timing state and timing permission live in `EngineBridge.cpp`;
   - accepted FIST marker latch rearm lives in `FrameCollisionMarkers.cpp`.
   - These belong under one feature owner.

2. **Hack motion-routing policy lives in `EngineBridge.cpp`.**
   - the physical CombatMove resource-query hook belongs in EngineBridge;
   - the factual Hack `_FinishingAttack_ -> _HackAttack_` candidate policy does not.

3. **C1-R1 repair performs the physical mutation inside `CollisionLifecycleGuard.cpp`.**
   - LifecycleGuard should decide whether exact terminal repair is justified;
   - the actual `Item_Attack -> Item_Equipped` mutation should use the existing `CollisionSourceOperations` owner.

4. **CORE diagnostics retain research-era verbosity.**
   - this is a separate second-stage diagnostic refactor after the behavior architecture compiles cleanly.

The current attack-family resolver remains in `FrameCollisionMarkers`; resolving whether the exact current action/phase is a supported marker Hit is part of marker ownership. No new `AttackFamilies` module is justified by this audit.

---

## 4. Frozen Target Behavior Architecture

```text
Script_G3AnimationBehaviors / research twin
|
+-- EngineBridge
|    sole physical Gothic hook/call-site owner
|    hook-local fact extraction
|    native call transport
|    delegation only
|
+-- FrameCollisionMarkers
|    exact current-motion/frame-effect ownership
|    supported action/phase marker-family resolution
|    occurrence/dedupe and C1-generation marker bookkeeping
|    equipped RIGHT/LEFT/BOTH/OFF semantics
|    StatePosition marker semantics
|    accepted FIST dispatch into Raw8FistCollision
|
+-- CollisionSources
|    factual source identities / UseTypes
|
+-- CollisionSourceOperations
|    equipped source mutations
|    Item_Attack activation/rearm + ClearTriggeredList
|    Item_Attack -> Item_Equipped deactivation/terminal repair mutation
|
+-- CollisionLifecycleGuard
|    C1 generation/source ownership
|    pre-combat acquisition and reconciliation policy
|    cleanup obligations
|    terminal repair decision and result classification
|
+-- Raw8FistCollision
|    supported raw8 FIST family policy
|    raw8 marked-execution state
|    initial SPU+0x164 close
|    accepted-FIST SPU+0x164 rearm
|    exact timing-permission state/identity
|    threshold capture and one-shot timing decision
|
+-- AttackMotionRouting
|    feature policy for optional CombatMove motion substitution
|    currently only the proven factual Hack routing rule
|
+-- RuntimeClock
|
+-- AttackContinuationProtection [later independent feature]
+-- AttackRaise
+-- AttackSpeed
+-- Config
```

### Dependency rule

```text
EngineBridge owns hooks, then delegates.
Feature modules do not install competing hooks.
CollisionLifecycleGuard decides repair; CollisionSourceOperations mutates.
FrameCollisionMarkers owns marker semantics; Raw8FistCollision owns raw8 behavior.
```

---

## 5. Raw8FistCollision Exact Seam

The first refactor creates `Raw8FistCollision.h/.cpp` and moves existing behavior without changing it.

The module owns:

```text
existing HumanFistMarkerExecution state -> factual Raw8Fist naming
primary motion timing capture
native threshold constant read
exact raw8 source validation
pending timing-permission retirement
marked-execution ownership/start close
accepted FIST latch rearm
post-marker timing-permission arming
exact +0x16E180 timing-permission decision/consumption
supported FIST family set = Normal + Power + Quick
```

`EngineBridge` retains the physical `Game +0x16E180` hook. Its wrapper obtains the real native play time and delegates only the policy decision to `Raw8FistCollision`.

`FrameCollisionMarkers` retains generic FIST marker ownership/occurrence processing but delegates the accepted FIST latch mutation into `Raw8FistCollision`.

The existing diagnostic output may remain textually unchanged during this first behavior refactor; diagnostic renaming/compaction belongs to Stage B.

---

## 6. AttackMotionRouting Exact Seam

Create `AttackMotionRouting.h/.cpp`.

Move only the existing Hack candidate policy:

```text
factual action == gEAction_HackAttack
+ queried resource contains _FinishingAttack_
-> try corresponding _HackAttack_ candidate
-> use candidate only when the resource exists
-> otherwise original resource query remains native
```

`EngineBridge` keeps:

```text
physical Game+0x16B10C query hook
SPU+0x154 factual-action extraction
original query fallback
```

No other action routing is introduced.

---

## 7. C1-R1 Mutation Seam

`CollisionLifecycleGuard::FinalizeAfterAISetState` continues to own every condition deciding whether terminal repair is justified.

When the exact live current-equipped outstanding source is still `Item_Attack(7)`, perform the physical change through the existing:

```text
CollisionSourceOperations::DeactivateOwnedAttackSource(source)
```

Preserve exactly:

```text
requested target = Item_Equipped(5)
NO ClearTriggeredList
same before/after verification
same finalization outcome classification
same reentrancy through the existing SetCollisionGroup hook
```

No lifecycle criterion changes.

---

## 8. Stage A — First Work Task

Stage A is a **behavior architecture parity refactor only**:

```text
add Raw8FistCollision
add AttackMotionRouting
move raw8 FIST behavior/state out of EngineBridge/Markers
move Hack routing policy out of EngineBridge
route terminal repair mutation through CollisionSourceOperations
update CMake behavior-source membership
```

Hard boundary:

```text
NO Sprint support
NO new hooks
NO hook-address changes
NO marker vocabulary changes
NO family/state-position changes
NO raw8 behavior changes
NO equipped behavior changes
NO C1 criteria changes
NO diagnostic-volume redesign yet
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55
```

Work BUILD EXECUTION remains PROHIBITED.

After Stage A publish, Normal Chat reviews the exact diff. The next engineering gate is a User local build/smoke on the PC with the repository/game installation. Do not begin Stage B source edits before that build gate passes.

---

## 9. Stage B — Diagnostic Refactor After Stage A Build PASS

Only after Stage A compiles/loads cleanly, freeze the diagnostic task.

Target policy:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Planned CORE reductions:

```text
Fist CanBeActivatedNow/TriggerTarget research hooks -> DEEP only
routine Fist trigger-state snapshots -> DEEP only
healthy C1 START/BINDING/STATUS chronology -> DEEP or compact event form
SetCollisionGroup no-op/raw8 0->0 noise -> suppress from CORE
known successful marker ownership/result -> compact event records
known successful raw8 timing -> compact ownership/opportunity/consumption records
OnDamage -> compact factual event; detailed addresses/contact internals in DEEP
terminal repair/divergence/invariant -> remain rich in CORE
unknown/unsupported action/family/source -> automatically rich in CORE
```

CORE must support NPC as well as player regression evidence; do not retain player-only filtering where that would hide NPC equipped lifecycle behavior.

For an unsupported family such as Sprint, CORE must retain at minimum:

```text
actor
numeric action
phase / StatePosition
current motion
marker opcode/result
C1 generation when available
resolved source identity / UseType / collision group
rejection reason
native damage caller/entity correlation when observed
```

Do not remove reusable research capability; retain it in DEEP where appropriate.

---

## 10. Post-Refactor Gates

After Stage A and Stage B both build/load cleanly, run the compact equivalence sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

Failure stops the sequence and is resolved before Sprint work.

After sentinel PASS:

```text
SprintAttack factual source/transport/mechanism investigation
-> bounded first-class Sprint implementation only if evidence supports it
-> focused Sprint validation
-> Goblin 1H / Demon 2H / Ogre Axe native equipped-NPC controls
-> remaining native/modded family compatibility
-> final mixed/stress regression
-> AttackContinuationProtection
-> production migration and diagnostics-free validation
```

---

## 11. Sprint Rule During Redesign

The architecture is deliberately made extensible enough to add a future `AttackFamily_Sprint`, but Stage A/B must not silently implement it.

The later Sprint investigation decides:

```text
which actors execute Sprint
which source UseTypes occur
which callback/transport owns Sprint
native StatePosition
raw8 latch/timing equivalence
whether equipped Sprint exists in practical runtime
```

Evidence, not filename naming, determines its implementation.
