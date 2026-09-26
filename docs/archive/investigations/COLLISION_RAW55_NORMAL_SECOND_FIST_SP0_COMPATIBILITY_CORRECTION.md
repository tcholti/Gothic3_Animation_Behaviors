# Gothic 3 — raw55 Normal Second-FIST SP0 Compatibility Correction

**Status:** CLOSED / RUNTIME PASS — EV-382  
**Opened:** 2026-09-26  
**Closed:** 2026-09-26  
**Task type:** BOUNDED PRODUCTION-BEHAVIOR IMPLEMENTATION + RUNTIME ACCEPTANCE  
**Owner:** `PhysicalFistCollision`

## Purpose

Remove the evidence-unnecessary StatePosition restriction on a legitimate second authored Normal raw55 FIST while preserving established Normal contact-rearm and native-cleanup invariants.

## Implementation basis

Branch: `docs/collision-source-evidence`

Frozen implementation parent:
`396c7b8b0886174860cc452176a2ed57bf530784`

Frozen production source blob before implementation:
`de175bb504c3abe13ad1c0bb9cda54997c9e3a26`

Published implementation:
`a31c66b97e45c27d0739b7df51252d33f490e7e1`

Independent Normal Chat static review: **PASS**.

Exact production change:

```cpp
// before
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && statePosition == 1;

// after
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

No other raw55 predicate, rearm mechanism, lifecycle behavior, hook, diagnostic surface, raw8 behavior, or equipped behavior changed.

## Evidence basis

EV-286–EV-292 had already established that:

```text
first Normal FIST may legitimately arrive at SP0
marker-owned ClearTriggeredList() can enable hit1 before SP0->SP1
Gothic's exact native between-contact clear from Script_Game.dll+0x386C6 creates the implicit second-contact opportunity
marked-Normal behavior suppresses that native clear so authored marker2 owns repeated-contact timing
a later authored marker2 can replace it with one exact current-RIGHT ClearTriggeredList()
```

Those older tests used marker2 at SP1 and proved SP1 sufficient, not necessary.

EV-380 then exposed the missing authoring boundary: in the archived 1+8 New Balance fixture, hit1 could occur before marker2 while marker2 was still factual `NORMAL/SP0`; the old source rejected it only through the SP1-only gate.

## Runtime acceptance

Diagnostic built/live SHA256:

`81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`

The User ran mixed BlackTroll raw55 double-FIST fixtures at marker placements `1+3`, `1+8`, and `1+15` under the intended New Balance environment.

### 1+3 — very early control

Repeated factual Normal executions show:

```text
marker1 NORMAL/SP0 -> accepted/open + initial clear
marker2 NORMAL/SP0 -> accepted
marker2 GroupBefore=7 / GroupAfter=7
marker2 GroupRequested=0
marker2 ClearTriggeredList=1
AcceptedFistCount=2
native cleanup -> 7 -> 5 / Outstanding=0
```

Marker2 can precede hit1. This is valid authored timing; two damage events are not required. Representative executions nevertheless can still produce two native `ONDAMAGE` events.

### 1+8 — decisive SP0-after-hit1 route

Repeated factual Normal executions show the exact causal requirement:

```text
marker1 NORMAL/SP0 -> accepted/open + initial clear
hit1 -> native ONDAMAGE
marker2 still NORMAL/SP0 -> ACCEPTED
marker2 GroupRequested=0
marker2 ClearTriggeredList=1
RIGHT remains group7
later native hit2 may occur
native cleanup -> 7 -> 5 / Outstanding=0
```

Representative C1=1:

```text
marker1 StateTime=0.039834 SP0
hit1 ONDAMAGE
marker2 StateTime=0.253015 SP0
AcceptedFistCount=2
GroupRequested=0
ClearTriggeredList=1
Result=ACCEPTED
cleanup Outstanding=0
```

Representative C1=5 repeats the route and produces a later second `ONDAMAGE` after marker2 rearm.

### 1+15 — later-placement control

The current New Balance timing still commonly places Normal marker2 at SP0 even with the frame15 authored position. Those marker2 events are accepted as clear-only rearm and clean normally. The fixture therefore supplies additional later-placement SP0 coverage rather than a fresh SP1 sample.

The already-established SP1 route remains protected because the production change is additive (`SP1` remains explicitly accepted) and SP1 marker2 behavior was runtime-proven in the earlier Normal causal campaign.

### Protected controls

Quick, true Power, and Sprint-origin raw55 controls remain healthy in the same mixed logs:

```text
first accepted FIST -> exact RIGHT 5 -> 7
second accepted FIST -> clear-only rearm / no second physical opening
native cleanup -> 7 -> 5 / final Outstanding=0
```

All three acceptance logs contain zero `CORE MARKER ANOMALY / DISCOVERY` records.

## Disposition

**PASS — NORMAL RAW55 SECOND-FIST EXPLICIT `{SP0,SP1}` ACCEPTANCE RUNTIME VALIDATED.**

The SP1-only gate was a conservative evidence boundary, not a native prerequisite for authored repeated-contact rearm.

Permanent Normal repeated-marker semantics are now:

```text
origin/current family = NORMAL
second FIST StatePosition = explicit SP0 OR SP1
same exact owned C1/source
source already group7
-> ClearTriggeredList()
-> no second physical opening
-> native contact/damage remains Gothic-owned
```

Together with EV-378, EV-379, EV-381 and the older raw55 campaign, focused raw55 Normal/Quick/Power/Sprint-origin compatibility is now CLOSED/PASS for the tested New Balance route.

Next gate: broader representative/full-stack New Balance compatibility, followed by the standalone/no-New-Balance post-compatibility raw55 sentinel before production collision migration.
