# Speed Separation Profile Identity Probe

**Status:** ACTIVE
**Task class:** Bounded diagnostics-only probe extension + runtime identity research
**Branch:** `development`

## Purpose

Resolve the final generic Speed/Raise profile identity before production profile matching is changed.

Raw `gEUseType` is already accepted as an independent profile fact under ADR-0010. The remaining question is whether raw UseType + current `AnimationFamily` is sufficient for known animation-separation mods.

Existing collision evidence creates three materially different fixtures:

```text
Axe Separation
-> separated ..._Axe_... motions
-> factual equipped source remains Axe/raw52

Zombie Separation
-> native Hero_... motions become Zombie_...
-> several weapon UseTypes remain available

Rapier Separation
-> separated Hero_..._Rapier_... motions
-> factual equipped source remains ordinary 1H/raw2
```

The Rapier case means production must not be changed until the request-time identity is observed directly.

## Causal question

At the proven Speed caller boundary, which stable factual request-time fields distinguish:

1. vanilla/shared animation routes;
2. Axe-separated routes;
3. Zombie-separated routes;
4. Rapier-separated routes?

In particular:

- does `Animation.GetSkeletonName(...)` change from `Hero` to `Zombie` under Zombie Separation?
- does raw equipped UseType alone distinguish Axe Separation as expected?
- does Gothic's direct request resolver `Entity.GetAni(passedAction, phase)` expose `Rapier` for the Rapier-separated route while raw equipped UseType remains `1H`?
- if Rapier requires a separate request-animation token, can that fact be represented generically without weapon-name special cases?

## Frozen implementation responsibility

Extend **only**:

`tools/Script_SpeedCalibrationProbe/Script_SpeedCalibrationProbe.cpp`

Add diagnostics for the exact requested animation resolved at the intercepted request boundary.

Required behavior:

```text
capture currentActionBefore
-> resolve requested animation with entity.GetAni(passedAction, phase)
-> preserve that exact string as diagnostic observation identity/output
-> call live Script_Game+0x42A0 exactly once with original passedAction/EAX
-> record currentActionAfter + returned speed
-> return returned speed unchanged
```

The resolved-requested-animation string must participate in observation deduplication so two distinct resolved animation identities cannot collapse into one summary row merely because family/raw-use-types/action/speed match.

Use an explicit field name such as:

`ResolvedRequestedAni=...`

Do not replace or reinterpret the existing `SampleAni` / `CurrentMovementAni` field; that remains useful as observational contrast.

## Protected behavior

Do not:

- modify `src/Script_G3AnimationBehaviors`;
- change production profile identity;
- edit the shipping INI;
- add production hooks;
- change the proven 18 Hit caller set or Power Raise observation caller;
- change action/EAX supplied to the live owner;
- call the live speed owner more than once;
- change the returned speed;
- add behavior intervention;
- begin Raise work;
- change collision behavior;
- infer final Rapier/Zombie/Axe profile policy inside the probe.

This task is observation only.

## Build policy

Work build execution is **PROHIBITED**.

Work performs source/static audit, commits/pushes the bounded change, and stops.

Normal Chat + User own local build, POP-03 deployment/hash verification and runtime interpretation.

## Runtime campaign after implementation

Use separate logs for causal clarity.

### A. Human bare-Fist native Speed control

Separation mods OFF; clean native calibration fixture.

Goal: close the currently missing Hero human-Fist Speed references.

Exercise naturally available human Fist attacks, especially Normal / Quick / Power and Sprint if factual Sprint occurs.

### B. Axe Separation

Enable only the known-working Axe separation stack required by that mod.

Exercise ordinary player Axe attacks and, as a control, ordinary 2H.

Record:

```text
AnimationFamily
raw UseTypes
ResolvedRequestedAni
current movement sample
action/phase
speed
```

### C. Zombie Separation

Enable only the known-working Zombie separation stack required by that mod.

Exercise at least two materially different zombie loadouts when practical, preferably:

```text
1H or 1H+shield
2H/Axe-like route
Staff
```

The key question is whether request-time `AnimationFamily` itself changes to `Zombie` or whether only the resolved requested animation string changes.

### D. Rapier Separation

Enable only the known-working Rapier separation stack required by that mod.

Exercise Normal / Quick / Power / Pierce on the Epee/Rapier fixture.

Key comparison:

```text
raw equipped UseType
vs
AnimationFamily
vs
ResolvedRequestedAni
```

Do not assume Rapier is distinguishable by raw item UseType merely because the mod is conceptually UseType-driven.

### Optional E. Zombie + Axe combined composition control

Only after A-D are interpreted, and only if the User's tweaked Zombie+Axe stack is known to work without G3AB.

This is useful to prove that the final identity dimensions compose, e.g. a Zombie-family actor plus an Axe-separated request, but it is not required before A-D close.

## Acceptance / stop rule

Stop after A-D and return to Normal Chat.

Normal Chat decides one of:

```text
raw UseType + AnimationFamily sufficient
OR
raw UseType + AnimationFamily + one generic request-animation dimension required
OR
another factual source must be researched
```

Do not implement the production matcher in the same task.
