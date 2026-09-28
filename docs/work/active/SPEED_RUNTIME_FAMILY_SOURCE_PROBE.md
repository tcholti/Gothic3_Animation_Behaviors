# Speed Runtime Animation-Family Source Probe

**Status:** ACTIVE  
**Task class:** Bounded diagnostics-only runtime probe  
**Branch:** `development`

## Purpose

Resolve the last factual identity question before the generic Speed profile refactor: which runtime API surface can reliably provide the user-facing Gothic animation family token (`Hero`, `Demon`, `Goblin`, etc.) at the point where Normal/Quick attack profile identity is being observed.

The first identity probe proved that `Animation.GetResourceName()` returns `G3_Hero_Skeleton` for the tested player route, which is not the ADR-0007 family token `Hero`. A direct resource-name alias was deliberately rejected as premature architecture.

Canonical animation naming already defines the first animation-name token as `AnimationFamily`.

## Frozen causal questions

For player Normal/Quick CombatMove observations, record together:

1. factual action and requested phase;
2. `NPC.GetCurrentMovementAni()`;
3. `Animation.GetResourceName()`;
4. `Animation.GetSkeletonName(...)` availability and value;
5. `Entity.GetSkeletonName()`;
6. factual raw left/right `gEUseType` values;
7. the current production `BehaviorProfiles` key/match result for comparison.

The primary question is whether `GetCurrentMovementAni()` already exposes a current/resolved attack animation such as:

```text
Hero_...
```

at this observation point, allowing the family to be recovered generically as the first token before `_`.

## Implementation boundary

Extend only the existing standalone `Script_SpeedIdentityProbe` diagnostic tool.

The probe remains observational only and must:

- reuse current production `BehaviorProfiles` read-only;
- keep the already-proven player CombatMove observation point `Game+0x16B065`;
- make no animation-speed, Raise, collision, or gameplay change;
- install no `Script_Game+0x42A0` speed hook;
- coexist with production G3AB/New Balance/AttackCollision during the run.

## Allowed files

```text
tools/Script_SpeedIdentityProbe/Script_SpeedIdentityProbe.cpp
docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md
current-state/handoff documentation required for routing
```

Production behavior source is frozen for this probe. The temporary `g3_hero_skeleton -> hero` production mapping has been reverted.

## Runtime matrix

One short human test is sufficient initially:

```text
ordinary right-hand 1H
left hand empty
several Normal attacks
several Quick attacks
normal exit
```

If `CurrentMovementAni` does not expose the requested/current attack identity clearly at this observation point, do not guess. Use the returned skeleton/resource facts to choose the next smallest probe or source path.

A transformed/non-human control is optional only if the human result proves a promising generic family source and one additional family is needed to validate the extraction rule.

## Interpretation

Preferred result:

```text
CurrentMovementAni=Hero_...
```

with stable first-token family extraction across Normal/Quick observations.

That would support a generic runtime rule:

```text
current resolved animation name
-> first token before '_'
-> AnimationFamily
```

If the current movement animation is stale/empty at this point, evaluate factual skeleton APIs next; do not revive a one-off Hero resource-name alias merely to make the first profile pass.

## Protected architecture already agreed

ADR-0007 revision freezes:

```text
ReferenceHitBaseSpeed = factual Hit reference B
ReferenceRaiseBaseSpeed = factual Raise reference B when later needed
BaseSpeed = single desired authored base C
RaiseOverride = Off | On
Recover = derived from effective Hit; no independent INI key/reference/hook
```

The later generic production implementation must remove the transitional Hero-only reference-base policy table from C++ and use profile calibration data instead.
