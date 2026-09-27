# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **behavior-only release-purity collision validation CLOSED/PASS EV-389. Bounded production collision-core migration is now frozen and CURRENT.**

Active task:

```text
docs/work/active/PRODUCTION_COLLISION_CORE_MIGRATION.md
```

Frozen migration direction:

```text
accepted EV-389 collision behavior core
-> exact-copy behavior modules into src/Script_G3AnimationBehaviors
-> production entry point = RuntimeClock init + EngineBridge hook install
-> production CMake builds collision core as Script_G3AnimationBehaviors.dll
-> old AttackRaise / AttackSpeed / SharedConfig excluded from build but left physically untouched
-> prototype behavior/diagnostic twins unchanged
-> no collision redesign
-> no Raise/Speed implementation
-> Work build/run prohibited
```

Final-candidate behavior hash from EV-389 lineage:

```text
Script_FrameCollisionBehaviorTest
D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78
```

Closed final validation:

```text
EV-386 corrected marked standalone matrix PASS
EV-387 standalone unmarked raw55 native fallback PASS
EV-388 focused final-candidate New Balance/raw55 regression PASS
DIAGNOSTIC PHASE CLOSED/PASS

EV-389 behavior-only sole-live deployment:
  built/live behavior SHA exact match
  diagnostic twin absent
  startup smoke PASS

EV-389 observational release-purity session:
  authored/released animations follow marker timing
  Hack collision works
  2H ON -> OFF -> ON gives separate openings
  OFF negative control: weapon overlap during OFF produces no hit
  1H1H/dual multi-window marker patterns produce intended extra contacts
  human Fist double markers can hit twice
  Sabretooth raw8 double markers can hit twice
  Troll raw55 double markers can hit twice
  one-on-one + group combat: no observed stuck/persistent collision regression

BEHAVIOR-ONLY RELEASE-PURITY GATE = CLOSED/PASS
```

Recent accepted architecture additions:

```text
final DLL name = Script_G3AnimationBehaviors.dll
Jackydima source reference pinned under references/jackydima-gothic3sdk
Raise/speed profiles = AnimationFamily + LeftAnimationUseType + RightAnimationUseType + Normal/Quick
INI loaded once at startup into normalized in-memory rules
Raise lets Gothic resolve the actual animation
Speed v2 must replace/configure the base term while preserving applicable contextual multipliers
exact Speed v2 intervention remains future research
```

Authorities:

```text
DESIGN.md
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md
ADR-0004
ADR-0005
references/README.md
```

Immediate route:

```text
1. Work executes only PRODUCTION_COLLISION_CORE_MIGRATION.md
2. Work publishes source-only implementation to docs/collision-source-evidence
3. Normal Chat independently reviews exact parity + build target
4. User builds/tests locally at home
5. production integration PASS -> close/archive migration task
6. then proceed to generic Raise/config responsibility; Speed v2 remains separate research
```

Current evidence ledger: `EVIDENCE_LEDGER_389_ONWARD.md`.  
POP-06 remains mandatory for any future diagnostic runtime logs.