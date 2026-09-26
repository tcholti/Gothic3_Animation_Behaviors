# Gothic 3 — New Balance raw55 Sprint Second-FIST State Investigation

**Status:** ACTIVE — STATE ENVELOPE ESTABLISHED / DOWNSTREAM SHEATH CONTROL PENDING / NO PRODUCTION CHANGE AUTHORIZED  
**Opened:** 2026-09-25  
**Updated:** 2026-09-26  
**Task type:** BOUNDED DIAGNOSTIC INVESTIGATION  
**Work build execution:** NOT REQUIRED  
**Owner under investigation:** `PhysicalFistCollision`

## Purpose

Determine the complete factual native state envelope in which a legitimate **second** authored FIST can arrive during one already-owned raw55 Sprint-origin execution under the intended New Balance environment, before freezing the smallest follow-up implementation.

A separate user observation from the timing sweep — sheathing immediately before Troll Sprint can appear to change whether one or both contacts land — is now tracked as a downstream native-contact control question. It must not be conflated with marker acceptance.

## Factual basis before the 2026-09-26 sweep

EV-379 validated the Sprint-first SP2 correction and exposed a second-marker timing split:

```text
origin SPRINT
marker1 current SPRINT / Action9
marker2 may arrive current POWER / Action2 / SP2 -> accepted clear-only rearm
marker2 may arrive current SPRINT / Action9 / SP2 -> rejected by current second-FIST predicate
```

The open question was whether moving marker2 earlier could also produce a legitimate `current SPRINT / Action9 / SP1` second FIST.

## 2026-09-26 timing sweep

The User published three otherwise-comparable BlackTroll double-FIST fixtures:

```text
frame 1 + frame 3
frame 1 + frame 8
frame 1 + frame 15
```

All runs used the same current New Balance environment and the already-reviewed collision candidate.

### Frame 1 + frame 3

Repeated Sprint-origin executions show:

```text
marker1:
  current SPRINT / Action9 / SP2
  StateTime ~= 1.90
  ACCEPTED / physical 5 -> 7

marker2:
  current SPRINT / Action9 / SP2
  StateTime ~= 1.95
  RIGHT already group7
  REJECTED_UNSUPPORTED_HIT
```

Moving marker2 almost immediately after marker1 therefore does **not** expose Sprint/SP1. The Hit motion is already at native SP2 by frame1 in these New Balance Troll Sprint executions.

### Frame 1 + frame 8

This fixture straddles the factual Action9 -> Action2 transition.

Most reviewed executions show:

```text
marker1 = SPRINT / Action9 / SP2 -> accepted/open
marker2 = POWER  / Action2 / SP2 -> accepted/clear-only rearm
```

But at least one reviewed execution shows:

```text
marker1 = SPRINT / Action9 / SP2 -> accepted/open
marker2 = SPRINT / Action9 / SP2 -> rejected
```

Therefore the same authored marker timing can land on either side of the native family/action transition.

### Frame 1 + frame 15

Reviewed Sprint-origin executions consistently show:

```text
marker1 = SPRINT / Action9 / SP2 -> accepted/open
marker2 = POWER  / Action2 / SP2 -> accepted/clear-only rearm
```

The full 1/15 log contains no CORE marker anomaly.

## Established Sprint second-FIST state envelope

For this tested New Balance BlackTroll Sprint route:

```text
current POWER  / Action2 / SP2 -> legitimate / current code ACCEPTS
current SPRINT / Action9 / SP2 -> legitimate / current code REJECTS
current SPRINT / Action9 / SP1 -> not observed; deliberate frame1/3 probe could not reach it because frame1 was already SP2
```

This is enough to reject the earlier idea that implementation should wait for a Sprint/SP1 example. The earliest practical authored Hit marker in the tested fixture is already SP2.

## Smallest evidence-backed implementation boundary

Current source retains for Sprint-origin second FIST:

```cpp
currentFamily == AttackFamily_Power
&& (statePosition == 1 || statePosition == 2)
```

The smallest extension supported by the runtime evidence is **not** generic `(SPRINT || POWER) && {SP1,SP2}` because Sprint/SP1 remains unproven.

The evidence-backed semantic set is:

```text
origin must remain immutable SPRINT

current POWER:
  preserve existing explicit SP1 or SP2 acceptance

current SPRINT:
  additionally accept explicit SP2 only
```

Conceptually:

```cpp
(currentFamily == AttackFamily_Power
    && (statePosition == 1 || statePosition == 2))
|| (currentFamily == AttackFamily_Sprint
    && statePosition == 2)
```

This is a candidate implementation boundary only. No production change is authorized until Normal Chat freezes a separate bounded Work task.

## Incidental raw55 authoring-boundary discovery

Because the timing sweep moved **all** raw55 second markers earlier, it also exposed a separate Normal-family question:

```text
Normal marker1 can open at SP0
very early Normal marker2 can also arrive at SP0
current Normal second-FIST predicate requires SP1
-> early marker2 is rejected in the 1/3 and 1/8 fixtures
```

Quick does not share that exact restriction; reviewed early Quick second markers can be accepted at SP0.

This does **not** authorize a Normal change. It is a future causal question relevant to the project's animator-authored-timing principle: determine whether Normal/SP1 is a genuine native prerequisite for second-contact rearm or only a conservative historical evidence guard.

## Sheath-before-Sprint observation — separate open control

The User reports that sheathing the player's weapon immediately before BlackTroll Sprint can sometimes appear to prevent both contacts, or occasionally the first contact, from landing.

Current evidence does **not** establish a marker failure:

- marker acceptance and physical opening/rearm are distinct from native contact/damage;
- some fully accepted two-marker Sprint executions naturally show fewer visible `ONDAMAGE` events than accepted marker opportunities;
- the current CORE marker rows do not log the player's exact action/phase/motion when a contact opportunity misses;
- existing logs contain Normal and Quick damage while the player motion is `HoldRight_End`, so sheathing is not a universal immunity or universal marker failure.

Before changing collision behavior, run a controlled A/B with the eventual corrected Sprint second-FIST build:

```text
A. marked Troll Sprint, player does not sheath
B. marked Troll Sprint, intentionally sheath immediately before attack
C. unmarked/native Troll Sprint, no sheath
D. unmarked/native Troll Sprint, same sheath timing
```

Primary distinction:

```text
markers accepted/open/rearm correctly but no damage
-> investigate native target/contact/player-state behavior

marker itself rejected/ownership lost
-> investigate G3AB marker route

same sheath effect on unmarked native Sprint
-> native/New Balance behavior, not authored-marker ownership
```

If the existing CORE facts are insufficient to distinguish a missing native contact, add diagnostics only after the controlled A/B demonstrates the need. Do not add production behavior for this observation.

## Protected boundaries

No production implementation is authorized by this investigation.

Do not change:

```text
IsFirstFistAllowed
true-Power predicates
Normal / Quick predicates
raw8 behavior
generic equipped behavior
EquippedSprintCollision
C1 lifecycle
native cleanup
AttackMotionRouting
hook set
```

Do not introduce:

```text
StatePosition >= 1
generic family widening
Sprint/SP1 second-FIST acceptance without evidence
authored-count-specific policy
species/name gates
animation filename inference
New Balance / DLL detection
new hook/module/state
timer/polling
custom contact/damage
```

## Evidence inputs

EV-379 comparison inputs remain temporarily in `research/raw/`:

```text
research/raw/2026.09.25_newbalance_blacktroll_all_single_marker2.log
research/raw/2026.09.25_newbalance_blacktroll_all_double_marker2.log
```

2026-09-26 timing-sweep inputs:

```text
research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_3.log
research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_8.log
research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_15.log
```

Retain them only while the immediate Sprint timing/sheath comparison remains active; archive under POP-06 once the controlled comparison closes.

## Separate paused speed-control authority

Speed-control semantics are now durably owned by:

`docs/SPEED_CONTROL_ARCHITECTURE.md`

and decision rationale by:

`docs/decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`

The tested native base-speed observations are not merely a working hypothesis. The open research question is the exact current New Balance multiplier order/intervention point. Speed work remains paused until collision compatibility closes.
