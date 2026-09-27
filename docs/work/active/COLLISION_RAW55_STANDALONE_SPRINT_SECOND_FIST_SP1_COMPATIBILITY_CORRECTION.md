# Gothic 3 — Standalone raw55 Sprint second-FIST SP1 compatibility correction

**Status:** ACTIVE  
**Type:** Bounded production-behavior implementation task  
**Owner:** Normal Chat design/evidence -> Work implementation  
**Frozen from evidence:** EV-385

## Purpose

Correct one exact standalone/no-New-Balance compatibility hole exposed by EV-385 without redesigning permanent raw55 behavior.

The permanent `PhysicalFistCollision` mechanism, C1/source/origin ownership model, first-FIST opening, repeated-contact clear-only behavior, Sprint-origin continuation, native damage ownership, and native cleanup are already proven. EV-385 adds the previously missing factual state proof that a legitimate Sprint-origin second FIST can arrive while current runtime state is still `SPRINT / Action9 / SP1`.

## Required base / branch

```text
Repository: tcholti/Gothic3_Animation_Behaviors
Branch: docs/collision-source-evidence
Required base: use the current remote HEAD containing EV-385 and this frozen task
```

Do not implement from an older local checkout.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this file
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/FEATURE_DEVELOPMENT_METHOD.md`
6. only the exact source required by this responsibility:
   `prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`

Use `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md` / EV-385 only when a factual boundary needs confirmation. Do not broaden into unrelated collision modules.

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

The exact current source gate is `PhysicalFistCollision::IsSecondFistAllowed()`:

```text
origin Sprint + current POWER  -> explicit SP1 or SP2
origin Sprint + current SPRINT -> SP2 only
```

The current-SPRINT/SP1 exclusion is therefore the sole frozen production responsibility.

## Required implementation

In `prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`, modify **only** the Sprint-origin second-FIST state gate in `IsSecondFistAllowed()` so that:

```text
origin family = SPRINT

current family = POWER:
  StatePosition = SP1 OR SP2

current family = SPRINT:
  StatePosition = SP1 OR SP2
```

Express the accepted states explicitly. Do **not** replace them with `>= 1`, a broad range predicate, or a generic family-independent rule.

The smallest expected source correction is the current-Sprint arm changing from:

```text
statePosition == 2
```

to explicit:

```text
statePosition == 1 || statePosition == 2
```

while preserving the existing current-Power arm.

## Must preserve

Do not change:

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

## Prohibited

Do not add:

- new hooks;
- timers, polling, queues, delayed marker handling;
- hit1 or visited-target flags;
- custom/direct damage;
- species/name/filename/DLL/version policy;
- generic StatePosition widening;
- LEFT raw55 support;
- more than two FIST markers;
- unrelated refactors, cleanup, formatting sweeps, or documentation redesign.

## Work execution boundary

This is a **production-behavior implementation**, not a diagnostic probe.

Work must:

```text
inspect exact current source
-> implement only the frozen state-gate correction
-> perform bounded static/source review
-> commit and push to docs/collision-source-evidence
-> report commit SHA + exact changed files + concise review result
-> STOP
```

Work build/run execution is prohibited. Runtime validation remains User/local after independent Normal Chat review.

## Post-implementation validation owned by Normal Chat/User

Because this changes behavior after EV-384, final-candidate validation must include:

```text
standalone/no-New-Balance:
  direct 1+3 Sprint-origin double-FIST retest
    marker1 SPRINT/SP1 accepted/open
    marker2 SPRINT/SP1 accepted clear-only
    AcceptedFistCount=2
    GroupRequested=0 on marker2
    ClearTriggeredList=1 on marker2
    native cleanup group7 -> group5
    final Outstanding=0
    no supported-traffic marker anomaly

  preserve representative 1+8 / 1+15 same-C1 POWER/SP1 continuation
  preserve single-FIST SPRINT/SP1
  finish true-Power single/double control
  finish unmarked raw55 native-fallback control

New Balance representative regression:
  recheck a bounded Sprint-origin SP2 / transition fixture
  confirm the source correction did not regress EV-381/EV-384 behavior
```

Do not rerun the entire historical standalone or New Balance campaign unless the focused final-candidate validation exposes contradictory evidence.

## Completion criterion

This Work task is complete only when the bounded source change is committed and pushed. Runtime acceptance is a separate later gate; do not mark EV-385 resolved from source review alone.