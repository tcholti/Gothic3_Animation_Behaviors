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
Speed deep independent audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
first Speed production build/deploy/startup = PASS
first Speed behavior check = FAIL before composition
family-source probe = CLOSED/PASS on Hero + Sabretooth
ADR-0007 generic profile/request semantics = ACCEPTED
generic profile calibration refactor = IMPLEMENTED / STATIC REVIEW PASS
CURRENT = local production build gate
RAISE = PAUSED until Speed closes
```

## Frozen request/profile rule

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

Closed result:

`docs/archive/investigations/SPEED_RUNTIME_FAMILY_SOURCE_PROBE_RESULT.md`

## Implemented generic Speed profile

```ini
[Profile.Hero_None_1H_Normal]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Normal
ReferenceHitBaseSpeed=0.60
BaseSpeed=0.40
RaiseOverride=Off
```

Quick fixture:

```ini
[Profile.Hero_None_1H_Quick]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H
ActionProfile=Quick
ReferenceHitBaseSpeed=1.00
BaseSpeed=0.40
RaiseOverride=Off
```

`AttackSpeed` no longer owns a Hero/weapon reference-base table. It uses the matched profile's `ReferenceHitBaseSpeed`. Missing/invalid calibration fails closed to the compatible result. `ReferenceRaiseBaseSpeed` and `RaiseOverride` are reserved/parsed only; no Raise behavior is active. Recover has no independent setting.

Active task:

`docs/work/active/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION.md`

## Next

Sync `development`, then build only production:

```powershell
cmake --build build --config Release --target Script_G3AnimationBehaviors
```

Do not deploy/run until build PASS.

After PASS:

```text
deploy/hash production DLL
-> update live INI to the two profiles above
-> small human None+1H Normal + Quick runtime test
-> if visible Speed control works, continue New Balance acceptance
-> close Speed
-> only then begin Raise
```
