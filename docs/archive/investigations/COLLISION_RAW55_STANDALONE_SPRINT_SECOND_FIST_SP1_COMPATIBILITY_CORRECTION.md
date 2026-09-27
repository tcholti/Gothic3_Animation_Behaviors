# Gothic 3 — Standalone raw55 Sprint second-FIST SP1 compatibility correction

**Status:** COMPLETE — IMPLEMENTED / INDEPENDENT REVIEW PASS / RUNTIME ACCEPTANCE PASS EV-386–EV-387  
**Type:** Bounded production-behavior implementation + acceptance task  
**Owner:** Normal Chat design/evidence -> Work implementation -> User/Normal Chat runtime validation  
**Frozen from evidence:** EV-385

## Purpose

Correct one exact standalone/no-New-Balance compatibility hole exposed by EV-385 without redesigning permanent raw55 behavior.

The permanent `PhysicalFistCollision` mechanism, C1/source/origin ownership model, first-FIST opening, repeated-contact clear-only behavior, Sprint-origin continuation, native damage ownership, and native cleanup were already proven. EV-385 added the previously missing factual state proof that a legitimate Sprint-origin second FIST can arrive while current runtime state is still `SPRINT / Action9 / SP1`.

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

Work implementation and standalone runtime acceptance are complete.

## Required branch/source state

```text
Repository: tcholti/Gothic3_Animation_Behaviors
Branch: docs/collision-source-evidence
Reviewed correction source: 1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0
```

## Frozen factual basis

EV-385 standalone/no-New-Balance BlackTroll/raw55 evidence established:

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

No C1 invariant warning, terminal repair anomaly, or cleanup contradiction accompanied the 1+3 failure.

The pre-correction source gate was:

```text
origin Sprint + current POWER  -> explicit SP1 or SP2
origin Sprint + current SPRINT -> SP2 only
```

The current-SPRINT/SP1 exclusion was therefore the sole frozen production responsibility.

## Implemented behavior

In `PhysicalFistCollision::IsSecondFistAllowed()` the Sprint-origin second-FIST rule is:

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

## Runtime acceptance result

Both collision twins were rebuilt from reviewed source `1c45e5e...`:

```text
Behavior SHA256:
D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78

Diagnostic SHA256:
AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
```

EV-386 corrected marked standalone acceptance:

```text
1+3 SPRINT/SP1 marker1 accepted/open
marker2 same-C1 SPRINT/SP1 accepted clear-only
AcceptedFistCount=2
GroupRequested=0
ClearTriggeredList=1
native cleanup group7 -> group5
Outstanding=0

1+8 / 1+15 same-C1 SPRINT/SP1 -> POWER/SP1 continuation preserved
single-FIST SPRINT/SP1 preserved
factual true-Power single + double controls PASS
zero REJECTED_* / ANOMALY in the marked batch
clean unload
```

EV-387 unmarked fallback acceptance:

```text
BlackTroll raw55 Quick / Normal / true Power / Sprint
MarkerPresent=0 / FistMarkers=0 / SuppressNative=0
zero RAW55_PHYSICAL_FIST_MARKER
zero RAW55_PHYSICAL_FIST_NATIVE_OPEN_SUPPRESSED
Gothic native 5->7 and 7->5 remains authoritative
Outstanding=0
zero rejection/anomaly/invariant warning
clean unload
```

Therefore the standalone/no-New-Balance final-candidate diagnostic raw55 sentinel is **CLOSED/PASS EV-386–EV-387**.

A separate focused final-candidate New Balance regression and the later diagnostics-free behavior-twin release-purity confirmation remain release gates, but they are no longer responsibilities of this completed correction task.

## Completion criterion

Satisfied.

The bounded implementation is published at `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`, independently reviewed PASS, and standalone runtime-accepted through EV-386–EV-387. This file was therefore archived from `docs/work/active/` after acceptance.