# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-28

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
Speed v2 caller-side mechanism/caller set = CLOSED STATIC through EV-391/EV-392
runtime family-source = CLOSED/PASS through EV-394 (Hero + Sabretooth)
generic profile calibration implementation = CLOSED/PASS
production build/deploy = PASS
configured Hero None+1H Normal/Quick behavior = PASS
New Balance stamina/context multiplier preservation = PASS on configured Hero None+2H Normal (EV-395)
CURRENT = final bounded Speed runtime acceptance/fallback coverage
RAISE = PAUSED until Speed closes
main = FROZEN
```

Active task:

`docs/work/active/SPEED_V2_FINAL_RUNTIME_ACCEPTANCE.md`

Closed implementation result:

`docs/archive/investigations/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION_RESULT.md`

## Frozen runtime/profile rule

```text
requested gEAction + requested gEPhase = Gothic request authority
Animation.GetSkeletonName(...)         = runtime AnimationFamily
left/right UseTypes                     = normalized equipment profile facts
CurrentMovementAni                      = observational context only
```

Family-source evidence:

```text
Hero       -> Hero
Sabretooth -> Sabretooth
```

## Production Speed v2 state

Production built/live SHA256:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

Primary intended stack:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Generic profile-owned composition:

```text
compatible = B * M
configured = compatible * (BaseSpeed / ReferenceHitBaseSpeed)
           = C * M
```

`AttackSpeed` no longer contains a Hero/weapon reference-base table. Factual reference bases live in the matching INI profile.

## Runtime evidence now passed

### Generic configured behavior

Hero / empty-left / right-hand 1H:

```text
multiple Normal variants at BaseSpeed=0.40 = PASS
multiple Quick variants at BaseSpeed=0.40  = PASS
```

One profile applies across the tested pose/animation variants; no P0/P1/P2/P3 split is required.

### New Balance contextual multiplier preservation

Hero / empty-left / right-hand 2H Normal:

```ini
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=2H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.70
BaseSpeed=1.00
RaiseOverride=Off
```

The configured 2H attack used the expected faster authored base at available/full stamina and visibly slowed at zero/depleted stamina.

Therefore the key ADR-0004 runtime invariant is now proven for this representative configured control:

```text
G3AB authors the base C
+ New Balance stamina/context multiplier M remains effective
```

Evidence:

```text
EV-394 = Sabretooth non-Hero family-source generalization PASS
EV-395 = generic configured Speed behavior + New Balance multiplier preservation PASS
```

Do **not** deploy the historical `Script_CombatMoveLogger` unchanged; it also hooks `Script_Game+0x42A0` and would contaminate the caller-side compatibility architecture.

## Immediate route for next session

Do not redesign anything.

Start from:

`docs/work/active/SPEED_V2_FINAL_RUNTIME_ACCEPTANCE.md`

Run only the smallest remaining controls needed to close Speed, expected to cover:

```text
representative unconfigured fallback
representative configured Normal/Quick/use-type coverage beyond the first fixture as needed
native-only sanity/fallback if still required by ADR-0004 acceptance
additional contextual modifier only if a real ambiguity remains
```

If those pass:

```text
close Speed v2
-> update current authorities/evidence
-> only then activate Raise under ADR-0006
```

## Still paused

```text
NO Raise implementation while Speed is open
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```
