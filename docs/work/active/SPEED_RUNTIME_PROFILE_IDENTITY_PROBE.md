# Speed Runtime Profile Identity Probe

**Status:** ACTIVE  
**Task class:** Bounded diagnostics-only implementation/runtime probe  
**Branch:** `development`

## Purpose

The first Speed v2 runtime acceptance run produced no visible speed change with an otherwise valid-looking `G3AnimationBehaviors.ini`, including deliberately extreme `BaseSpeed=2.0` and `BaseSpeed=0.4` values.

The INI has been confirmed at the exact runtime path:

`<Gothic 3>\Ini\G3AnimationBehaviors.ini`

with active Hero/None/1H Normal and Quick profiles.

This probe answers only whether the production profile/configuration identity layer can factually match the player at runtime before any Speed transport redesign is considered.

## Frozen causal questions

For player combat-move observations, determine:

1. what `Entity.Animation.GetResourceName()` actually returns;
2. the factual raw left/right `gEUseType` values;
3. the factual combat action;
4. the exact normalized `BehaviorProfiles::ProfileKey` produced by the production implementation;
5. whether the exact production `BehaviorProfiles::Find()` resolves a profile;
6. whether the matched profile has `BaseSpeed`, and its parsed value.

## Implementation boundary

Create a standalone diagnostic tool `Script_SpeedIdentityProbe`.

The probe must:

- compile and reuse the exact production `BehaviorProfiles.cpp/.h` implementation rather than reimplementing its parser/matcher;
- call `BehaviorProfiles::Load()` once at probe startup;
- observe only the already-proven player combat-move call site used by `Script_CombatMoveLogger` (`Game+0x16B065`);
- log player-only factual identity/match results to `SpeedIdentityProbe.log`;
- be observational only;
- install no `Script_Game+0x42A0` speed hook;
- make no animation-speed, collision, Raise, or gameplay change;
- coexist with the production `Script_G3AnimationBehaviors.dll` and New Balance for this diagnostic run.

## Allowed files

- `tools/Script_SpeedIdentityProbe/CMakeLists.txt` [new]
- `tools/Script_SpeedIdentityProbe/Script_SpeedIdentityProbe.cpp` [new]
- root `CMakeLists.txt` only to register the diagnostic tool subdirectory
- current-state/handoff documentation required to route the active probe

Production `BehaviorProfiles.cpp/.h` are reused read-only and must not be modified for this task.

## Runtime matrix

One short run is sufficient:

- start game with the current `G3AnimationBehaviors.ini` containing Hero/None/1H Normal and Quick `BaseSpeed=0.4`;
- equip ordinary right-hand 1H with empty left hand;
- perform several Normal attacks and several Quick attacks;
- exit normally;
- inspect only bounded probe log facts.

## Interpretation

- If exact profile match + `BaseSpeed=0.4` is observed, configuration/profile identity is cleared and the next causal question is Speed transport/composition execution.
- If runtime identity differs or no profile matches, fix only that factual configuration boundary before investigating transport.

## Exclusions

Do not change production Speed source, the six call sites, `AttackSpeed`, collision behavior, Raise behavior, New Balance, or the production release DLL in this task.
