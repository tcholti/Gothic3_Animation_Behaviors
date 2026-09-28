# Speed Runtime Animation-Family Source Probe

**Status:** ACTIVE — HUMAN PASS / ONE NON-HUMAN CONTROL REMAINS  
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

## Human control result — PASS

Deployment of the refreshed probe passed with matching built/live SHA256:

```text
DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F
```

A right-hand 1H / empty-left-hand Normal + Quick run produced, consistently:

```text
RequestedPhaseName=Hit
AnimationResourceName=G3_Hero_Skeleton
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Hero
EntitySkeletonName=Hero
RawLeftUseType=0
RawRightUseType=2
```

Normal observations used Action1; Quick observations used Action4/5.

`CurrentMovementAni()` was not the requested/new Hit identity at this observation point. Across observations it could still report prior/current motions such as:

```text
Hero_..._HoldRight_End_...
Hero_..._Attack_Recover_...
Hero_..._Ambient_Loop_...
Hero_..._Parade_Begin_...
```

Therefore the current-motion filename is rejected as the production family source for Speed at this hook: its `Hero_` prefix happens to remain useful for this actor, but the actual motion identity is stale relative to the requested Hit.

Both skeleton APIs returned the exact author-facing family token `Hero` on every observation. `Animation.GetSkeletonName(...)` is the preferred candidate because:

- it belongs directly to the animation property set whose family is being keyed;
- it returns the exact `Hero` token expected by ADR-0007;
- it provides an explicit success/failure result, allowing a natural fail-closed runtime-key build;
- it avoids one-off parsing/aliasing of `G3_Hero_Skeleton`.

The current production key still uses `GetResourceName()` and therefore still produced `g3_hero_skeleton` / `ProfileMatch=false`; this is expected and confirms no production behavior changed during the probe.

Processed human-control log:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

## Why one non-human control remains

The human result is sufficient to reject current-motion parsing and raw resource-name identity for Hero, and it strongly supports `Animation.GetSkeletonName(...)`.

Before using that API as the generic production family source, run one additional known non-Hero family. This is not a new architecture investigation; it is a bounded generalization check that the same API returns another stable Gothic family token rather than a Hero-specific special case.

## Final runtime control

Use the already-built/deployed `Script_SpeedIdentityProbe.dll`; no source or build change is required.

Preferred fixture:

```text
transform player into Sabretooth
perform several ordinary Normal attacks
perform several Quick attacks if available on the transformed player route
exit normally
```

No Sabretooth INI profile is required. The only required facts are the logged identity surfaces.

Acceptance:

```text
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=<stable non-Hero family token>
EntitySkeletonName=<same stable family token>
```

`CurrentMovementAni` and `AnimationResourceName` remain observational comparison fields only.

If the skeleton APIs agree on a stable non-Hero token, close the family-source probe and use `Animation.GetSkeletonName(...)` as the generic runtime `AnimationFamily` source.

If they disagree or return unsuitable resource-style names, do not guess; inspect the exact contradiction before changing production.

## Implementation boundary

The probe remains observational only and must:

- reuse current production `BehaviorProfiles` read-only;
- keep the already-proven player CombatMove observation point `Game+0x16B065`;
- make no animation-speed, Raise, collision, or gameplay change;
- install no `Script_Game+0x42A0` speed hook;
- coexist with production G3AB/New Balance/AttackCollision during the run.

Production behavior source remains frozen for this probe. The temporary `g3_hero_skeleton -> hero` production mapping remains reverted.

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
