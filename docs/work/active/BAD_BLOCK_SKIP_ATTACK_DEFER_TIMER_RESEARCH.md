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


### E. Player vs NPC scope

Do **not** assume this is player-only.

Historical evidence proves the player held-Use2 / 2500 ms path, but that is only an evidence boundary. The User reports that NPC blocks may also be force-ended by a timeout.

Research separately:
1. whether NPC block/parade duration is capped;
2. whether NPCs use the same `DurationPressedMSecs > 2500` mechanism;
3. whether NPCs use a sibling Script_Game branch, state-time threshold, AI decision timer, or other mechanism;
4. whether the same attack-interruption bug can occur while an NPC is attacking;
5. whether one smallest fix can safely cover both player and NPC without broad global timer ownership.

Classify conclusions explicitly as:
```text
player path: proven / not proven
NPC path: proven / not proven
same mechanism: yes / no / unresolved
same fix can cover both: yes / no / unresolved
```

If NPC scope cannot be established statically, identify the **smallest single runtime probe** that would resolve only that uncertainty.



## Desktop Commander — authorized read-only static inspection

Desktop Commander is available and online on the User's authorized Windows PC.

It may be used in this research task to inspect the **actual local tested Gothic 3 installation/binaries and repository files** where that materially closes the remaining static uncertainty.

Authorized use is **read-only static inspection only**.

Allowed:
- locate the User's actual Gothic 3 installation and `Script_Game.dll`;
- inspect file metadata / hashes;
- inspect the exact local `Script_Game.dll` instruction sequence around the proven bad-path region, especially approximately `+0x633BB .. +0x63409`;
- use available local disassembly/static-analysis tools from the command line if present;
- inspect the local repository/source/reference files;
- compare the local binary against the already-documented RVA evidence;
- establish the exact instruction/call producing or consuming the held-duration value and the exact conditional branch governing `FullStop -> SetState`.

Not allowed:
- modify local repository files;
- patch or modify Gothic 3 binaries;
- write into the Gothic 3 installation;
- build;
- deploy;
- launch/run Gothic 3;
- attach a debugger to a running game;
- create a runtime probe;
- change Desktop Commander configuration unless strictly required for read-only access and explicitly justified.

If multiple Gothic 3 installations/binaries are present, identify the **actual tested installation** before drawing conclusions. Prefer hash/path evidence over assumptions.

Desktop Commander should be used to close the exact static seam if possible. If the local binary can establish the instruction-level control flow, do not stop merely because the raw disassembly artifact is absent from the repository.

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


## Research checkpoint — Normal Chat

### Established facts

The desired "defer timer" is **not a G3AB-owned timer**.

EV-187 proves the tested bad held-Use2 path reads the player's held-input duration and compares it against `2500 ms` before entering the destructive branch.

Official SDK surface:

```text
gCCharacterControl_PS / PSCharacterControl
- PressedKey
- IsPressed
- IsPressedBefore
- DurationPressedMSecs
```

The engine property is generic CharacterControl input state. No narrow public API exists to pause only the block/parade timeout. Directly rewriting `DurationPressedMSecs` would therefore take ownership of generic input timing and is not the preferred release fix.

Tested destructive path:

```text
Use2 held
-> DurationPressedMSecs > 2500
-> Script_Game +0x633F1 PSRoutine::FullStop()
-> active CombatMove fullStop=true
-> Script_Game +0x63409 PSRoutine::SetState(...)
-> suspended attack continuation discarded
```

EV-189 proves that the subsequent `SetState` clears the relevant SPU continuation. EV-185/EV-186 prove that FullStop itself is also real instruction termination and is shared with legitimate reaction paths.

Therefore:

```text
suppress FullStop only = insufficient
suppress SetState only = too late for uninterrupted attack
global AIFullStop suppression = unsafe
global CharacterControl timer mutation = too broad
```

A clean behavior fix should prevent/bypass the **whole exact bad timeout branch** while the protected attack is active.

### Current production reuse

Production already has:
- factual Routine Action access;
- factual animation phase access;
- existing `AISetState` transport for collision finalization;
- attack-family classification helpers.

However, `FrameCollisionMarkers::TryGetCurrentAttackHitFamily()` is deliberately Hit-only and collision-oriented. Do not automatically make the release fix depend on marker/collision ownership.

The attack-protection classifier should be factual routine/action based and independent from Collision configuration.

### New Balance cross-check

Pinned New Balance source:
`Jackydima/gothic3sdk @ 316d32406a133f8884e7e302752c35f66b4f54fc`

Its current `OnPlayerGameKeyPressed` handling does not own/read `DurationPressedMSecs` for this timeout and does not replace the proven CP/native 2500-ms destructive branch.

Compatibility rule therefore remains:

```text
if New Balance / live stack never reaches the native destructive condition
-> G3AB does nothing

if the exact native destructive condition is reached during a protected attack
-> only then may G3AB intervene
```

### Open static question

The repository preserves the proven interpretation of Script_Game `+0x633BB..+0x63409`, but not the raw disassembly artifact itself.

Before implementation, establish the exact instruction/call seam that supplies or consumes the held-duration value around the `2500 ms` comparison.

Preferred order:

1. if one exact call produces the duration/result immediately before the compare, intercept that call locally and alter only the branch-local effective duration;
2. otherwise identify the exact conditional branch bypass covering both FullStop and SetState;
3. avoid adding two broad function hooks merely to suppress FullStop and SetState separately.

Do not invent an RVA from remembered evidence.

### Current provisional verdict

```text
existing timer owner:
  Gothic/CP CharacterControl DurationPressedMSecs

existing lifecycle:
  generic held-key duration; exact bad path compares >2500 ms

attack-active signal:
  factual player Routine Action / animation state; final phase semantics still to freeze

pause mechanism candidate:
  exact branch-local effective-duration/conditional bypass

new hook required?:
  likely one narrow Script_Game call-site/branch hook; exact seam not yet proven

new persistent state required?:
  unknown if exact "resume remaining time" is required;
  branch suppression alone defers destruction but does not mathematically pause elapsed held time

multi-actor safety:
  proven historical evidence covers the player held-Use2 path only;
  do NOT infer that NPCs are unaffected.
  Research whether NPC block/parade timeout uses the same mechanism,
  a sibling timeout path, or separate AI logic before recommending scope.

compatibility:
  preserve New Balance/live stack; intervene only if exact native destructive condition remains reachable

blocker:
  exact static instruction seam around +0x633BB..+0x63409 must be re-established

verdict:
  RESEARCH OPEN — one bounded static disassembly step remains
```
