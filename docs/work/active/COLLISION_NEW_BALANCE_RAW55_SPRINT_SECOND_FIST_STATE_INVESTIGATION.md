# Gothic 3 — New Balance raw55 Sprint Second-FIST State Investigation

**Status:** ACTIVE — DIAGNOSTIC EVIDENCE MAPPING / NO PRODUCTION CHANGE AUTHORIZED  
**Opened:** 2026-09-25  
**Task type:** BOUNDED DIAGNOSTIC INVESTIGATION  
**Work build execution:** NOT REQUIRED  
**Owner under investigation:** `PhysicalFistCollision`

## Purpose

Determine the complete factual native state envelope in which a legitimate **second** authored FIST can arrive during one already-owned raw55 Sprint-origin execution under the intended New Balance environment.

Do not implement a source change from the first newly observed state alone. The goal is to establish the complete smallest rule before freezing any follow-up implementation.

## Factual basis

EV-379 validates the Sprint-first SP2 correction and exposes a separate second-marker timing split.

Proven legitimate second-FIST route:

```text
origin family = SPRINT
marker1 current family = SPRINT
marker1 Action = 9
marker1 StatePosition = 1
marker1 -> ACCEPTED / exact RIGHT raw55 5 -> 7

same C1 later:
marker2 current family = POWER
marker2 Action = 2
marker2 StatePosition = 2
marker2 -> ACCEPTED / ClearTriggeredList only
```

Newly observed legitimate arrival that the current predicate rejects:

```text
origin family = SPRINT
marker1 current family = SPRINT
marker1 Action = 9
marker1 StatePosition = 1
marker1 -> ACCEPTED / exact RIGHT raw55 5 -> 7

same C1 later:
marker2 current family = SPRINT
marker2 Action = 9
marker2 StatePosition = 2
RIGHT already group7
AcceptedFistCount = 1
marker2 -> REJECTED_UNSUPPORTED_HIT
```

The second sequence proves that the factual Action9 -> Action2 transition can occur **after** marker2, not only before marker2.

## Narrow causal question

Can a legitimate second FIST in the same Sprint-origin C1 also arrive while factual state is:

```text
current family = SPRINT
Action = 9
StatePosition = 1
```

If yes, the eventual follow-up rule must account for that proven state as well. If no after a deliberate timing probe, the evidence envelope remains narrower.

## Next runtime probe

Animation-fixture change only; no production source change.

1. Use the same BlackTroll raw55 Sprint-capable double-FIST fixture.
2. Move **marker2 earlier**, only enough to place it meaningfully closer to marker1.
3. Keep marker1 unchanged.
4. Run several Sprint executions under the same intended New Balance stack.
5. Capture the factual second-marker rows, especially:

```text
OriginFamily
CurrentFamily
Action
StatePosition
StateTime
AcceptedFistCount
GroupBefore / GroupAfter
GroupRequested
ClearTriggeredList
Result
C1
```

6. Also note whether the user can visually receive the second contact when it should connect.

The diagnostic goal is state mapping, not forcing a desired result.

## Known state matrix before the probe

```text
Sprint-origin second FIST:

current POWER  / SP2 -> proven legitimate / current code ACCEPTS
current SPRINT / SP2 -> proven legitimate arrival / current code REJECTS
current SPRINT / SP1 -> UNKNOWN; deliberate earlier-marker probe required
```

Do not infer other state combinations without direct evidence.

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
authored-count-specific policy
species/name gates
animation filename inference
New Balance / DLL detection
new hook/module/state
timer/polling
custom contact/damage
```

## Interpretation rule

The eventual correction, if evidence supports one, should remain scoped to an already-matched exact raw55 execution whose immutable origin is Sprint and whose second FIST is within the same valid C1/animation/source identity.

Do not freeze the implementation expression until the deliberate earlier-marker probe establishes whether `current SPRINT / SP1` belongs to the legitimate second-FIST state set.

## Evidence inputs

EV-379 active-comparison logs remain temporarily in `research/raw/`:

```text
research/raw/2026.09.25_newbalance_blacktroll_all_single_marker2.log
research/raw/2026.09.25_newbalance_blacktroll_all_double_marker2.log
```

They should be archived under POP-06 after the active timing comparison closes.

## Separate paused speed-control note

A separate observation from the same session is intentionally **not** part of this collision investigation: New Balance owns an animation-speed hook and appears to establish action/weapon-specific baseline speed values before applying additional modifiers. The User's working hypothesis is that values such as 1H `0.6`, 2H/Axe/Staff/Halberd `0.7`, and Quick/Pierce/Hack `1.0` are baseline definitions used inside that modifier pipeline rather than simple global slowdowns.

This is not yet proven for the current distributed binary. When Raise/speed work resumes, compatibility must be designed so Gothic3_Animation_Behaviors does not replace New Balance's speed hook/modifier chain and so applicable New Balance multipliers are preserved. Raise/speed remains paused until collision compatibility closes.
