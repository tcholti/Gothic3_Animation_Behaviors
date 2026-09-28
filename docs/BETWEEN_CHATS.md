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
BehaviorProfiles foundation = IMPLEMENTED/PASS
EV-391 Speed caller-side mechanism = RECORDED
EV-392 Quick provenance + exact six-site caller set = PASS/RECORDED
Speed v2 deep independent Work audit = PASS WITH NON-BLOCKING FINDINGS
S-01 finite-output correction = CLOSED / SOURCE-REVIEW PASS
first Speed runtime behavior check = FAIL before composition
Speed identity probe = CLOSED / CAUSAL RESULT CAPTURED
factual player runtime resource = G3_Hero_Skeleton
current production correction = exact g3_hero_skeleton -> hero runtime-family normalization
current correction source lineage = 28182c8898a29b5fa61b6b5c3a044b882550d54f
CURRENT = rebuild identity probe and confirm ProfileMatch=true before rebuilding production DLL
RAISE = PAUSED until Speed closes
```

The first Speed runtime test used active Hero/None/1H Normal + Quick profiles, including extreme `BaseSpeed=2.0` and `0.4`, but produced no visible speed change.

The bounded `Script_SpeedIdentityProbe` reused production `BehaviorProfiles` and proved the failure occurs before Speed composition:

```text
AnimationResourceName=G3_Hero_Skeleton
runtime normalized family=g3_hero_skeleton
left=none
right=1h
Normal Action=1 Hit
Quick Action=4/5 Hit
ProfileMatch=false
```

ADR-0007 deliberately keeps the author-facing family token `AnimationFamily=Hero`. Therefore the smallest evidence-bounded correction is in `BehaviorProfiles::TryBuildRuntimeKey()`:

```text
exact runtime g3_hero_skeleton -> schema token hero
all other unproven runtime family strings unchanged/fail-closed
```

The correction changes only production `BehaviorProfiles.cpp`. `AttackSpeed`, the six Speed caller hooks, collision behavior, Raise behavior and the INI schema are untouched.

Active correction contract:

`docs/work/active/SPEED_RUNTIME_HERO_FAMILY_NORMALIZATION_CORRECTION.md`

Closed probe result:

`docs/archive/investigations/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE_RESULT.md`

Processed raw evidence is archived at:

`research/archive/2026.09.28_SpeedIdentityProbe.log`

## Frozen Speed v2 transport remains unchanged

```text
six callers:
+0x383F0
+0x38E9D
+0x38F22
+0x3937D
+0x39402
+0x48677

caller mCCallHook
-> factual EAX action
-> mCCaller invokes LIVE Script_Game+0x42A0 exactly once
-> compatible result B*M
-> exact configured/evidenced route applies C/B
-> finite C*M
-> non-finite composed result fails closed to compatible result
```

Do not hook `+0x42A0` itself. Do not hook `+0x38A8B`.

## Next

On the local build/game PC:

```text
sync development to current remote
-> rebuild Script_SpeedIdentityProbe
-> deploy/hash refreshed probe beside the existing production stack
-> keep Hero/None/1H Normal + Quick BaseSpeed=0.4 INI
-> run several Normal + Quick 1H attacks
-> require runtime Key.AnimationFamily=hero, ProfileMatch=true, ProfileHasBaseSpeed=true, ProfileBaseSpeed=0.4
-> only then rebuild/deploy Script_G3AnimationBehaviors.dll
-> repeat small Speed behavior check
-> continue New Balance acceptance matrix if Speed now changes
```

Primary runtime stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

The diagnostic `Script_SpeedIdentityProbe.dll` may coexist only for this bounded identity-validation run.
