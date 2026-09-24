# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-24

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Frozen state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`  
Frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Diagnostic SHA256: `5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`  
Behavior SHA256: `A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

Source has **not** changed during the New Balance investigation.

## Current campaign

```text
standalone final-source regression   CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy          PASS EV-375
New Balance full-stack compatibility OPEN/BLOCKED EV-376
current responsibility               bounded raw55 Power/Sprint-origin SP2 correction
active Work task                     NONE
```

## EV-376 durable conclusion

The first New Balance compatibility contradiction has been reduced to the permanent raw55 `PhysicalFistCollision` state gate.

Single-FIST true Power:

```text
Action=2 / POWER
exact RIGHT TrollFist / UseType55
premature native 5 -> 7 opening suppressed
sole authored FIST arrives at SP2 (~1.58s)
current frozen gate rejects it
RIGHT remains group5
```

Double-FIST true Power:

```text
marker1: POWER / SP1 (~0.97s)
  -> accepted
  -> RIGHT 5 -> 7
  -> native damage possible

marker2: same exact C1/source / POWER / SP2 (~1.33–1.35s)
  -> currently rejected
  -> established clear-only repeated-contact rearm does not run
```

Sprint-origin double-FIST:

```text
marker1: origin SPRINT / Action9 / SP1
  -> accepted
  -> RIGHT 5 -> 7
  -> native damage possible

same C1 continues Action9 -> Action2
marker2: origin still SPRINT / current POWER / SP2
  -> currently rejected
```

The three BlackTroll logs contain 18 marker anomalies; all are this same SP2 raw55 Power-state class. No second rejected-marker class was found.

Scope-narrowing controls are healthy:

```text
equipped weapon sweep: no marker anomalies/warnings/errors
dual-1H generic Power markers already operate safely at SP2
Goblin equipped combat healthy
Sabertooth raw8 healthy
human raw8/fist healthy
raw55 Normal/Quick not contradicted
```

Jackydima `Script_AttackCollision` source corroborates the runtime: `OnAI_PowerAttack` advances SP0 -> SP1, then later SP1 -> SP2; the SP2 assignment is outside the dual-1H conditional. Defaults are 0.1s and 1.0s. Treat this as source corroboration, not exact installed-binary provenance.

## Exact implementation boundary for next session

Do **not** write code until one bounded Work task is frozen.

Candidate correction supported by EV-376:

```text
TRUE POWER — first FIST
current: SP1
bounded correction: SP1 or SP2

TRUE POWER — second FIST
current: SP1
bounded correction: SP1 or SP2

SPRINT ORIGIN — first FIST
keep unchanged: factual Sprint / Action9 / SP1

SPRINT ORIGIN — later FIST after same-C1 continuation
current: current Power / SP1
bounded correction: current Power / SP1 or SP2
```

Hard exclusions:

```text
NO generic StatePosition >= 1
NO generic SP2 widening outside exact raw55 execution
NO change to Normal
NO change to Quick
NO change to raw8
NO change to generic equipped marker handling
NO change to C1 identity/lifecycle
NO species/name gate
NO filename-family inference
NO AttackCollision DLL detection/config dependency
NO new hook
NO timer/polling
NO direct/custom damage
```

The likely source surface remains `prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`; inspect the exact live source again before freezing edits.

## Focused acceptance after implementation

```text
1. single-FIST true Power -> late SP2 FIST accepted/opened
2. double-FIST true Power -> marker1 opens, marker2 SP2 clear-only rearm
3. Sprint-origin -> marker1 Action9/SP1; marker2 same-C1 current Power/SP2 accepted as rearm
4. raw55 Normal/Quick controls unchanged
5. representative equipped/raw8 controls unchanged
6. then resume broader New Balance compatibility coverage
```

Expected lifecycle remains Gothic-owned native cleanup to group5 / zero outstanding.

## Active comparison artifacts — keep in research/raw for now

```text
2026.09.24_newbalance_troll.log
2026.09.24_newbalance_troll2.log
2026.09.24_newbalance_different_weapons_no_target.log
2026.09.24_newbalance_blacktroll.log
2026.09.24_newbalance_blacktroll_2.log
2026.09.24_newbalance_blacktroll_3.log
2026.09.24_newbalance_goblin.log
2026.09.24_newbalance_sabertooth.log
2026.09.24_newbalance_fist_no_target.log
```

Do not archive/delete these until the focused correction is runtime-accepted and the active comparison closes under POP-06.

## Tomorrow's startup route

```text
root README.md Start Here
-> SESSION_ENTRYPOINT.md
-> this file
-> COLLISION_REFERENCE.md §5–§6
-> COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md
-> COLLISION_TEST_PLAN.md §4.4
-> EV-376 only if exact proof is needed
-> read WORK_IMPLEMENTATION_PROTOCOL.md before a Work edit task
```

Production migration, Raise/speed, and AttackContinuationProtection remain paused.
