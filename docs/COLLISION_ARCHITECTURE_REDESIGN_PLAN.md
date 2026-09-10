# Collision Architecture and Diagnostic Redesign Plan

**Status:** Canonical audit result and staged refactor authority  
**Updated:** 2026-09-10  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Freeze the completed collision architecture audit after EV-249, record the implemented and locally validated Stage A structural refactor, and define Stage B diagnostics plus the later Sprint sequence before broad compatibility testing.

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

Current source has no `AttackFamily_Sprint` and no Sprint callback/adapter plumbing. Sprint is therefore a factual missing family to investigate after Stage B and the compact equivalence sentinel.

Current evidence does **not** establish Sprint as Fist-only, creature-only, Power-equivalent, or equipped-capable.

Do not add a Sabretooth-specific exception and do not implement Sprint during Stage B.

---

## 3. Architecture Audit Result

The audit found that most of the mature collision architecture was already correctly separated.

Healthy boundaries retained:

```text
CollisionSources
  factual equipped/Fist source identity and UseType resolution

CollisionSourceOperations
  physical source mutation and equipped ClearTriggeredList behavior

CollisionLifecycleGuard
  C1 generation/source ownership, pre-combat acquisition policy,
  outstanding obligations, cleanup reconciliation and repair decision

RunScriptFunctionScope in EngineBridge
  legitimate hook-invocation transport lifetime for the pre-combat bridge

EngineBridge
  exactly one physical owner per Gothic hook/call-site

CMake product separation
  behavior-only target excludes diagnostic source files;
  diagnostic target adds CORE and optional DEEP definitions/sources

FrameCollisionMarkers
  current-motion scan, reserved-marker ownership, occurrence/dedupe,
  equipped RIGHT/LEFT/BOTH/OFF semantics, family/phase marker eligibility,
  StatePosition marker semantics
```

The current attack-family resolver remains in `FrameCollisionMarkers`; resolving whether the exact current action/phase is a supported marker Hit is part of marker ownership. No new `AttackFamilies` module is justified.

Confirmed drift at audit time:

```text
1. raw8 FIST feature state/policy split across EngineBridge + FrameCollisionMarkers
2. Hack motion-routing policy inside EngineBridge
3. C1-R1 physical repair mutation directly inside CollisionLifecycleGuard
4. research-era CORE diagnostic verbosity
```

Stage A closed 1–3. Stage B addresses 4 only.

---

## 4. Stage A — CLOSED/PASS THROUGH LOCAL BUILD/LOAD

Published source commit:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Frozen base:

```text
5f8101179de6417dbb20d310b00b378a3f36ad8a
```

Independent source review: **PASS**.  
Work static audit: PASS.  
`git diff --check`: PASS.  
Material contradiction: None.

Local validation on 2026-09-10:

```text
Script_FrameCollisionBehaviorTest Release build  PASS
Script_FrameCollisionTest Release build          PASS
built/live diagnostic SHA256                     MATCH
runtime load                                     PASS
hook installation                                PASS
Hack callback identity                           PASS
normal unload                                    PASS
```

Built/live SHA256:

```text
07F682C2F7AD6227D0EE81CD2DE053C9704B8E7EC4AFFB54793E91A55BD7D945
```

Therefore the Stage A compile/deploy/load/unload gate is **CLOSED/PASS**.

Non-fatal compiler warnings remain, including behavior-only unused variables whose uses are diagnostics-only. They do not invalidate Stage A and should only be cleaned within a bounded later responsibility.

The startup `BehaviorCore:` text is stale and omits `Raw8FistCollision` and `AttackMotionRouting`; Stage B should correct it.

---

## 5. Implemented Behavior Architecture

```text
Script_G3AnimationBehaviors / research twin
|
+-- EngineBridge
|    sole physical Gothic hook/call-site owner
|    hook-local fact extraction
|    native call transport
|    delegation
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
|    supported raw8 FIST family policy = Normal + Power + Quick
|    raw8 marked-execution state
|    initial SPU+0x164 close
|    accepted-FIST SPU+0x164 rearm
|    exact timing-permission state/identity
|    threshold capture and one-shot timing decision
|
+-- AttackMotionRouting
|    optional CombatMove motion-substitution policy
|    currently only factual Hack routing
|
+-- RuntimeClock
|
+-- AttackContinuationProtection [later independent feature]
+-- AttackRaise
+-- AttackSpeed
+-- Config
```

Dependency rule:

```text
EngineBridge owns hooks, then delegates.
Feature modules install no competing hook.
CollisionLifecycleGuard decides repair; CollisionSourceOperations mutates.
FrameCollisionMarkers owns generic marker semantics; Raw8FistCollision owns raw8 behavior.
```

---

## 6. Raw8FistCollision Implemented Seam

`Raw8FistCollision.h/.cpp` owns:

```text
Normal + Power + Quick supported-family predicate
raw8 marked-execution state
primary motion timing capture
Game+0x308308 native threshold read
exact raw8 source validation
pending timing-permission retirement
initial SPU+0x164 = 1 close once per C1 generation
accepted FIST SPU+0x164 = 0 latch rearm
post-marker timing-permission arming
exact Game+0x16E180 one-shot timing decision/consumption
```

`EngineBridge` retains the physical `Game +0x16E180` hook and delegates only the existing permission decision.

`FrameCollisionMarkers` retains generic FIST marker ownership/occurrence processing and delegates only the accepted FIST latch operation.

Stage A intentionally preserved historical diagnostic names such as `HumanFist...`; diagnostic naming/compaction is Stage B.

---

## 7. AttackMotionRouting Implemented Seam

`AttackMotionRouting.h/.cpp` owns only:

```text
factual action == gEAction_HackAttack
+ queried resource contains _FinishingAttack_
-> try corresponding _HackAttack_ candidate
-> use candidate only when the resource exists
-> otherwise original resource query remains native
```

`EngineBridge` still owns the physical `Game+0x16B10C` query hook, SPU+0x154 factual-action extraction, and original-query fallback.

No other action routing was introduced.

---

## 8. C1-R1 Implemented Mutation Seam

`CollisionLifecycleGuard::FinalizeAfterAISetState` still owns every condition deciding whether terminal repair is justified.

When the exact live current-equipped outstanding source remains `Item_Attack(7)`, the physical change goes through:

```text
CollisionSourceOperations::DeactivateOwnedAttackSource(source)
```

Preserved:

```text
requested target = Item_Equipped(5)
NO ClearTriggeredList
same liveness/outstanding/group7 criteria
same before/after verification
same finalization outcome classification
same SetCollisionGroup-hook observation/reentrancy path
```

---

## 9. Current Responsibility — Stage B Diagnostic Refactor

Stage B changes diagnostics only. It must not change collision behavior.

Governing rule:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Target product split:

```text
PRODUCTION
  diagnostics not compiled

CORE
  compact known-path regression facts
  rich unsupported/unknown/anomaly/repair/invariant evidence
  enough action/source/marker/damage/lifecycle information for larger tests
  relevant NPC as well as player evidence

DEEP
  retained opt-in reverse-engineering probes
```

Planned CORE reductions:

```text
Fist CanBeActivatedNow/TriggerTarget research hooks -> DEEP only
routine Fist trigger-state snapshots -> DEEP only
healthy C1 START/BINDING/STATUS chronology -> compact or DEEP
SetCollisionGroup no-op/raw8 0->0 noise -> suppress from CORE
known successful marker ownership/result -> compact events
known successful raw8 timing -> compact ownership/opportunity/consumption events
OnDamage -> compact factual event; detailed addresses/contact internals in DEEP
terminal repair/divergence/invariant -> rich CORE
unknown/unsupported action/family/source -> rich CORE automatically
```

CORE must support NPC as well as player regression evidence; do not retain player-only filtering where that would hide relevant NPC equipped lifecycle behavior.

For unsupported traffic such as Sprint, CORE must retain at minimum:

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

Reusable research capability should be retained in DEEP, not simply deleted.

Stage B should also correct stale startup metadata to list `Raw8FistCollision` and `AttackMotionRouting`.

Behavior hard boundaries:

```text
NO Sprint support
NO new gameplay behavior
NO hook RVA/calling-convention semantic changes
NO marker vocabulary/StatePosition changes
NO raw8 family/latch/timing changes
NO equipped source changes
NO C1 generation/repair changes
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55 behavior
```

---

## 10. Post-Stage-B Gates

After Stage B source implementation and independent review:

```text
build both Release twins
deploy/hash diagnostic DLL
load/unload smoke
```

Then run the compact equivalence sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

Failure stops the sequence and is resolved before Sprint work.

---

## 11. Sprint Investigation After Sentinel

Sprint remains deliberately unsupported during Stage B.

The later bounded investigation must establish:

```text
which actors execute gEAction_SprintAttack
which source UseTypes occur
which callback/transport owns Sprint
native StatePosition
whether raw8 Sprint uses the same latch/timing route
whether equipped Sprint exists in practical runtime
```

If support is justified, prefer a first-class `AttackFamily_Sprint` adapter. Do not add species-, Sabretooth-, or filename-based exceptions.

---

## 12. Frozen Sequence

```text
Raw8 Quick FIST closure                              DONE — EV-249
SprintAttack missing-family discovery               IDENTIFIED
architecture + diagnostic audit                     DONE
Stage A behavior architecture source refactor       DONE
Stage A local build/load                            CLOSED/PASS
Stage B diagnostic-volume refactor                  NEXT
Stage B local build/load
compact equivalence sentinel
SprintAttack source/transport/mechanism investigation
bounded Sprint implementation if evidence supports it
focused Sprint validation
Goblin 1H / Demon 2H / Ogre Axe native controls
remaining native/modded family compatibility
final mixed/stress collision regression
AttackContinuationProtection
combined mature collision regression
New Balance + relevant Jackydima compatibility
production migration into Script_G3AnimationBehaviors
diagnostics-free production validation
integrate Raise + Speed + Config
```
