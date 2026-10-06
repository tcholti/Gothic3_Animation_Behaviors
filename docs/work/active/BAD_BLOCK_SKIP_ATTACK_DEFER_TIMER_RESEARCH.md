# Bad Block Skip — Pause Defer Timer During Attack Research

**Status:** ACTIVE  
**Mode:** bounded read-only static research / mechanism and lifecycle investigation  
**Release role:** final small-fix candidate before first public release  
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`

## Purpose

Determine whether the existing bad-block-skip defer timer can be paused while the affected actor is actively attacking, then resume afterward, without redesigning block-skip behavior or disturbing accepted Collision / Speed / Raise / Movement systems.

The User's desired behavior is conceptually:

```text
bad-block skip defer timer running
+ actor enters an attack
-> defer countdown pauses

attack ends
-> defer countdown resumes from remaining time
```

This task is **research only**. Do not implement the fix yet.

## Start from repository evidence, not remembered terminology

The exact source owner, timer variable, hook path and lifecycle are not yet re-established by name.

First locate and prove:
1. what project behavior corresponds to "bad block skip";
2. where its defer timing is owned;
3. how the countdown is represented and advanced;
4. what event/state starts it;
5. what clears/expires it;
6. whether it is actor-specific or global;
7. what current hooks feed that lifecycle.

Do not infer the owner from old conversation wording.

## Research question

Can the current defer countdown be paused only while the same relevant actor is in an attack, then resumed with the exact remaining defer duration?

Prefer the smallest solution that reuses already-observed attack state/lifecycle.

## Required investigation

### A. Existing bad-block-skip lifecycle

Trace the current production source from trigger through defer/skip decision and retirement.

Produce:
- owning module/file;
- state fields;
- units/time source;
- update/check locations;
- actor identity semantics;
- reset/retirement paths.

### B. Attack-active signal candidates

Inspect existing production signals already available to G3AB.

Prefer, in order:
1. an already-maintained per-actor factual combat/action state;
2. an existing hook callback that can answer attack-active without new polling;
3. a minimal existing engine state query at the defer-check seam.

Do not add a new hook merely because one could work.

Establish what "during an attack" must mean for this fix:
- factual attack action families only;
- exact start/end boundaries available from current architecture;
- whether Raise / Hit / Recover all count as attack-active;
- whether Sprint/shared Power routes need special handling.

### C. Pause semantics

Compare only minimal viable mechanisms.

Target semantics:
```text
remaining defer time before attack
=
remaining defer time after attack
```

Reject mechanisms that silently restart the full timer unless evidence shows that is actually the desired native/project behavior.

Consider whether the existing timer representation naturally supports:
- stop/resume;
- deadline adjustment by elapsed attack duration;
- accumulated paused duration.

### D. Safety / compatibility

Explicitly check:
- multi-actor behavior;
- actor death/removal/state reset;
- interruption/cancelled attack;
- repeated/chained attacks;
- New Balance;
- accepted collision lifecycle;
- no dependency on Speed, Raise or Movement configuration;
- static/per-frame cost.

## Protected systems

Do not redesign or modify:
- Collision accepted behavior;
- Raw8 / Raw55 / EquippedSprint owners except where factual read-only tracing requires;
- AttackSpeed;
- AttackRaise;
- AttackMovement;
- BehaviorProfiles public semantics;
- New Balance compatibility;
- shipping INI.

## Prohibited in this task

- no production source edits;
- no documentation architecture redesign;
- no new hook;
- no probe unless static evidence is genuinely insufficient and Normal Chat freezes one later;
- no build;
- no deployment;
- no runtime testing.

## Deliverable

Return a concise evidence report with:

```text
existing timer owner:
existing lifecycle:
attack-active signal:
pause mechanism candidate:
new hook required? yes/no
new persistent state required? yes/no, exact minimum
multi-actor safety:
compatibility:
blockers/uncertainties:
recommended smallest implementation:
verdict:
```

Classify the result as:
- PASS — small production implementation can be frozen;
- NEEDS ONE BOUNDED RUNTIME PROBE;
- NOT CLEAN ENOUGH FOR FIRST RELEASE.

Stop after the research conclusion.
