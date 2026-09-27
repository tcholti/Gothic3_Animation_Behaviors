# Gothic 3 — Standalone raw55 Sprint second-FIST SP1 compatibility correction

**Status:** ACTIVE — IMPLEMENTED / INDEPENDENT REVIEW PASS / RUNTIME VALIDATION PENDING  
**Type:** Bounded production-behavior implementation + acceptance task  
**Owner:** Normal Chat design/evidence -> Work implementation -> User/Normal Chat runtime validation  
**Frozen from evidence:** EV-385

## Purpose

Correct one exact standalone/no-New-Balance compatibility hole exposed by EV-385 without redesigning permanent raw55 behavior.

The permanent `PhysicalFistCollision` mechanism, C1/source/origin ownership model, first-FIST opening, repeated-contact clear-only behavior, Sprint-origin continuation, native damage ownership, and native cleanup are already proven. EV-385 adds the previously missing factual state proof that a legitimate Sprint-origin second FIST can arrive while current runtime state is still `SPRINT / Action9 / SP1`.

## Implementation state

Published implementation:

```text
commit: 1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0
parent: ae1d0a9ed8b2fa128644294afa82c8a1f0345051
changed file: prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

Independent Normal Chat review: **PASS**.

The exact diff changes only the Sprint-origin second-FIST current-Sprint arm from SP2-only to explicit SP1-or-SP2 acceptance. The existing current-Power arm remains explicit SP1-or-SP2.

Review confirmed that the newly accepted state still enters the existing second-FIST branch only after:

```text
authoredFistCount == 2
acceptedFistCount == 1
IsSecondFistAllowed(...) == true
RIGHT source already group7
```

and then performs only `RearmTriggeredContacts()` / `ClearTriggeredList()` semantics. It does not call `ActivateAttackSource()` and therefore cannot create a second physical `5 -> 7` opening.

Work implementation is complete. Runtime acceptance remains open.

## Required branch/source state

```text
Repository: tcholti/Gothic3_Animation_Behaviors
Branch: docs/collision-source-evidence
Reviewed correction source: 1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0
```

Do not validate from an older local checkout.

## Frozen factual basis

EV-385 standalone/no-New-Balance BlackTroll/raw55 evidence establishes:

```text
Sprint-origin 1+3:
  marker1 -> current SPRINT / SP1 -> ACCEPTED
             exact RIGHT raw55 5 -> 7
  marker2 -> same C1/source/origin
             current SPRINT / SP1
             RIGHT already group7
             REJECTED_UNSUPPORTED_HIT

Sprint-origin 1+8 and 1+15:
  marker1 -> current SPRINT / SP1 -> ACCEPTED/open
  marker2 -> same C1/source/origin
             current POWER / SP1 -> ACCEPTED
             GroupRequested=0
             ClearTriggeredList=1

single-FIST:
  current SPRINT / SP1 -> ACCEPTED/open/clean cleanup
```

No C1 invariant warning, terminal repair anomaly, or cleanup contradiction accompanies the 1+3 failure.

The pre-correction source gate was:

```text
origin Sprint + current POWER  -> explicit SP1 or SP2
origin Sprint + current SPRINT -> SP2 only
```

The current-SPRINT/SP1 exclusion was therefore the sole frozen production responsibility.

## Implemented behavior

In `PhysicalFistCollision::IsSecondFistAllowed()` the Sprint-origin second-FIST rule is now:

```text
origin family = SPRINT

current family = POWER:
  StatePosition = SP1 OR SP2

current family = SPRINT:
  StatePosition = SP1 OR SP2
```

The states remain explicit. There is no `>= 1`, broad range predicate, or family-independent rule.

## Preserved boundaries

Unchanged:

- Sprint-origin first-FIST rule;
- `earlyOpeningSuppressed` requirement for first FIST;
- Normal `{SP0,SP1}` rules;
- Quick behavior;
- true-Power `{SP1,SP2}` behavior;
- immutable Sprint-origin / same-C1 continuation identity;
- exact current RIGHT raw55 / UseType55 source requirement;
- one physical first opening only;
- second-FIST clear-only rearm semantics;
- authored-FIST count limit;
- occurrence/dedupe behavior;
- native target/contact/damage ownership;
- native exact RIGHT `7 -> 5` cleanup ownership;
- C1-R1 terminal backup behavior;
- hook ownership or hook set;
- diagnostic/release separation.

Still prohibited without new evidence:

- new hooks;
- timers, polling, queues, delayed marker handling;
- hit1 or visited-target flags;
- custom/direct damage;
- species/name/filename/DLL/version policy;
- generic StatePosition widening;
- LEFT raw55 support;
- more than two FIST markers;
- unrelated refactors or policy changes.

## Runtime validation contract

Because this changes behavior after EV-384, final-candidate validation must include:

```text
1. rebuild BOTH collision twins from reviewed source 1c45e5e...
   -> record diagnostic SHA256
   -> record behavior SHA256

2. standalone/no-New-Balance diagnostic validation:
   direct 1+3 Sprint-origin double-FIST retest
     marker1 SPRINT/SP1 accepted/open
     marker2 SPRINT/SP1 accepted clear-only
     AcceptedFistCount=2
     GroupRequested=0
     ClearTriggeredList=1
     native cleanup group7 -> group5
     final Outstanding=0
     no supported-traffic marker anomaly

   preserve one representative POWER/SP1 continuation route
   preserve single-FIST SPRINT/SP1
   finish factual true-Power single/double control
   finish unmarked raw55 native-fallback control

3. one small New Balance diagnostic raw55 regression
   -> compatibility-sensitive Sprint-origin SP2 / Action9->Action2 route
   -> no need to repeat the full EV-376–EV-384 campaign

4. final diagnostics-free behavior-twin observational confirmation
   -> behavior twin only
   -> exact built/live behavior SHA match
   -> representative raw55/equipped/native behavior
   -> several animations whose desired RIGHT collision window exists only through G3AB markers
```

Do not rerun the entire historical standalone or New Balance campaign unless focused final-candidate validation exposes contradictory evidence.

## Completion criterion

The Work implementation portion is complete at `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0` and independently reviewed PASS.

This active task remains open only until the focused runtime acceptance above confirms the corrected final candidate. After acceptance and promotion, archive this file under `docs/archive/investigations/`.