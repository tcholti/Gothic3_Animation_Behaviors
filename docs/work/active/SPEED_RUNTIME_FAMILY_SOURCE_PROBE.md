# Speed Runtime Animation-Family Source Probe

**Status:** ACTIVE — HUMAN PASS / ONE NON-HUMAN CONTROL REMAINS  
**Task class:** Bounded diagnostics-only runtime probe  
**Branch:** `development`

## Purpose

Resolve the last factual identity question before the generic Speed profile refactor: which runtime API surface can reliably provide the user-facing Gothic animation family token (`Hero`, `Demon`, `Goblin`, etc.) while preserving the already-proven request-semantics architecture for Speed and later Raise.

The first identity probe proved that `Animation.GetResourceName()` returns `G3_Hero_Skeleton` for the tested player route, which is not the ADR-0007 family token `Hero`. A direct resource-name alias was deliberately rejected as premature architecture.

Canonical animation naming already defines the first animation-name token as `AnimationFamily`, but the family source is an actor/animation identity concern only. The requested attack itself remains identified from Gothic's factual action/phase request.

## Preserved pre-collision architecture

The successful pre-collision prototypes already established the intended separation:

```text
Speed:
requested gEAction from Gothic
+ requested gEPhase from Gothic
+ actor/equipment facts
-> configured behavior

Raise:
matching attack/profile
-> explicitly request factual Action + Raise through CombatMove
-> Gothic resolves the concrete Raise animation
```

The old Speed prototype did not inspect `CurrentMovementAni()` to decide which attack was being requested. The old Raise prototype did not wait for a Raise motion to become current; it asked Gothic for `gEAction_Attack + Raise` and let Gothic resolve P0/P1/etc.

Therefore this probe is **not** trying to find a current Hit filename to identify the attack. It is only selecting the stable runtime source for the `AnimationFamily` component of profile identity.

## Frozen causal questions

For Normal/Quick CombatMove observations, record together:

1. factual action and requested phase;
2. `NPC.GetCurrentMovementAni()` as observational timing context only;
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

`CurrentMovementAni()` could still report the outgoing/current motion while the new Hit request was already factual, including:

```text
Hero_..._HoldRight_End_...
Hero_..._Attack_Recover_...
Hero_..._Ambient_Loop_...
Hero_..._Parade_Begin_...
```

This is now interpreted as expected request-boundary behavior, not as a defect in the observation point. It confirms why Speed must continue to trust Gothic's factual requested Action/Phase instead of inferring the requested attack from whichever motion is currently playing.

Both skeleton APIs returned the exact author-facing family token `Hero` on every observation. `Animation.GetSkeletonName(...)` is the preferred candidate for the separate family component because:

- it belongs directly to the animation property set whose family is being keyed;
- it returns the exact `Hero` token expected by ADR-0007;
- it provides an explicit success/failure result, allowing a natural fail-closed runtime-key build;
- it avoids one-off parsing/aliasing of `G3_Hero_Skeleton`;
- it does not replace or duplicate the factual Action/Phase request semantics.

The current production key still uses `GetResourceName()` and therefore still produced `g3_hero_skeleton` / `ProfileMatch=false`; this is expected and confirms no production behavior changed during the probe.

Processed human-control log:

`research/archive/2026.09.28_SpeedIdentityProbetest_2.log`

## Why one non-human control remains

The human result is sufficient to reject raw resource-name identity for Hero and to keep `CurrentMovementAni()` out of Speed request classification. It strongly supports `Animation.GetSkeletonName(...)` as the stable family component.

Before using that API as the generic production family source, run one additional known non-Hero family. This is a bounded generalization check that the same API returns another stable Gothic family token rather than a Hero-specific special case.

This control does **not** re-test action/phase timing or attack animation resolution; those remain governed by Gothic's factual request semantics.

## Final runtime control

Use the already-built/deployed `Script_SpeedIdentityProbe.dll`; no source or build change is required.

Preferred fixture:

```text
transform player into Sabretooth
perform several ordinary Normal attacks
perform several Quick attacks if available on the transformed player route
exit normally
```

No Sabretooth INI profile is required. The only required family facts are:

```text
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=<stable non-Hero family token>
EntitySkeletonName=<same stable family token>
```

Action/phase and UseTypes remain useful context. `CurrentMovementAni` and `AnimationResourceName` remain observational comparison fields only.

If the skeleton APIs agree on a stable non-Hero token, close the family-source probe and use `Animation.GetSkeletonName(...)` as the generic runtime `AnimationFamily` source while retaining Gothic's factual requested Action/Phase as the attack/phase authority.

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

ADR-0007 freezes:

```text
AnimationFamily = stable actor/animation family component
ActionProfile = mapped from factual requested gEAction
factual gEPhase = runtime behavior gate
CurrentMovementAni = not request identity
ReferenceHitBaseSpeed = factual Hit reference B
ReferenceRaiseBaseSpeed = factual Raise reference B when later needed
BaseSpeed = single desired authored base C
RaiseOverride = Off | On
Recover = derived from effective Hit; no independent INI key/reference/hook
```

The later generic production implementation must remove the transitional Hero-only reference-base policy table from C++ and use profile calibration data instead.
