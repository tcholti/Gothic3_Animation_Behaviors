# Collision Architecture and Diagnostic Redesign Plan

**Status:** Canonical audit result and staged refactor authority  
**Updated:** 2026-09-10  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Freeze the completed collision architecture audit after EV-249, record the implemented and locally validated Stage A structural refactor, record the implemented and locally validated Stage B diagnostic refactor, and define the remaining equivalence-sentinel/Sprint sequence before broad compatibility testing.

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

Current source has no `AttackFamily_Sprint` and no Sprint callback/adapter plumbing. Sprint is therefore a factual missing family to investigate only after the compact equivalence sentinel.

Current evidence does **not** establish Sprint as Fist-only, creature-only, Power-equivalent, or equipped-capable.

Do not add a Sabretooth-specific exception and do not implement Sprint before the sentinel passes.

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

Stage A closed 1–3. Stage B closed 4.

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

## 9. Stage B Diagnostic Refactor — CLOSED/PASS THROUGH LOCAL BUILD/LOAD

Frozen contract:

```text
docs/COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md
```

Published source commit:

```text
5737db32e5eda76810989ddfb5659f8405c0c458
Refactor Stage B collision diagnostics
```

Frozen base:

```text
f9a88316e107e6d1ace6509f26dfe9980ec2f404
```

Independent source review: **PASS**.  
Work static audit: PASS.  
`git diff --check`: PASS.  
Material contradiction: None.

Implemented diagnostic split:

```text
CORE
  compact known-path marker/raw8/OnDamage/C1/source events
  rich unsupported/unknown/anomaly/repair/invariant events
  NPC as well as player lifecycle evidence

DEEP
  historical Fist gate/trigger hooks and snapshots
  detailed raw8 timing arithmetic/addresses
  detailed OnDamage contact/integer/address data
  full ownership tables and routine dispatch chronology
```

Behavior remained unchanged: no Sprint support, no behavior hook changes, no marker/StatePosition/raw8/equipped/C1/Hack semantic changes.

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
081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD
```

Startup metadata now correctly lists:

```text
Raw8FistCollision
AttackMotionRouting
```

Therefore the Stage B compile/deploy/load/unload gate is **CLOSED/PASS**.

---

## 10. Current Gate — Compact Equivalence Sentinel

Run the established compact sentinel before Sprint:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

The sentinel has two purposes:

```text
behavior parity after Stage A/B refactors
CORE readability + anomaly/repair evidence sufficiency
```

Failure stops the sequence and is resolved before Sprint work.

---

## 11. Sprint Investigation After Sentinel

Sprint remains deliberately unsupported until the sentinel passes.

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
Stage B diagnostic-volume refactor                  DONE
Stage B local build/load                            CLOSED/PASS
compact equivalence sentinel                        NEXT
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
