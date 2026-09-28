# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-28

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 collision production integration = CLOSED/PASS
EV-391/EV-392 Speed caller-side mechanism + six-site caller set = CLOSED STATIC
EV-393 Hero family-source control = PASS
EV-394 Sabretooth family-source generalization = PASS
generic profile calibration implementation = CLOSED/PASS
production build/deploy = PASS
built/live SHA = 6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
Hero None+1H Normal + Quick configured behavior = PASS
EV-395 configured Hero None+2H Normal preserves New Balance stamina slowdown = PASS
CURRENT = final bounded Speed runtime acceptance/fallback coverage
RAISE = PAUSED until Speed closes
```

## Frozen rule

```text
requested gEAction + requested gEPhase = Gothic request authority
Animation.GetSkeletonName(...)         = runtime AnimationFamily
left/right UseTypes                     = normalized equipment profile facts
CurrentMovementAni                      = observational context only
```

Composition:

```text
compatible = B * M
configured = (B * M) * (C / B) = C * M
```

## Proven runtime controls

### 1H Normal + Quick

With Hero / empty-left / right-hand 1H profiles configured at `BaseSpeed=0.40`, multiple Normal and Quick variants visibly used the configured slow speed.

### New Balance multiplier preservation

With Hero / empty-left / right-hand 2H Normal configured as:

```ini
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=2H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.70
BaseSpeed=1.00
RaiseOverride=Off
```

the attack used the intended faster `1.0` authored base at available/full stamina and visibly slowed at zero/depleted stamina.

This closes the key ADR-0004 compatibility question for a representative configured route: the G3AB base override does not erase the tested New Balance stamina/context multiplier.

Do not use the historical `Script_CombatMoveLogger` unchanged; its `+0x42A0` hook would contaminate this architecture.

## Next

Active task:

`docs/work/active/SPEED_V2_FINAL_RUNTIME_ACCEPTANCE.md`

Closed implementation result:

`docs/archive/investigations/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION_RESULT.md`

Tomorrow, do not redesign or re-probe family identity. Run only the smallest remaining Speed closure matrix:

```text
representative unconfigured fallback
-> representative configured Normal/Quick/use-type coverage as still needed
-> native-only sanity/fallback if required
-> extra contextual modifier only if a real ambiguity remains
-> close Speed if all pass
-> activate Raise only afterward
```
