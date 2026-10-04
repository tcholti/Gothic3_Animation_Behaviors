# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Collision CLOSED/PASS and protected. `main` frozen.

## Current state

```text
Speed core = CLOSED/PASS through EV-410
Raise correction = source PASS EV-416 / runtime pending
EV-417 = AttackCollision Hack coverage gap + minor underflow edge
EV-418 = route-neutral Hack correction mechanism FROZEN
build/runtime = BLOCKED until implementation/review
```

External compatibility reference:
`Jackydima/gothic3sdk@bbe769075bc896085a620a0ceb3491192c5beb61`

## Assigned responsibility — EV-418 Hack compatibility implementation

**BOUNDED PRODUCTION SOURCE IMPLEMENTATION.** Build/runtime prohibited.

Edit only:
```text
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
```

Implement the frozen route:

```text
CombatMove hook
-> AttackRaise::RunCombatMove
-> stateless Hack Speed adapter
-> unchanged InvokeCombatMove_FrameCollisionTest
-> original CombatMove
```

Hack adapter requirements:
- FullStop/null args/null SPU -> pass unchanged;
- only request Action14 + physical phase `Raise`/`Hit`/`Recover`;
- actor = request.SelfEntity;
- profile identity = existing Hack/Hit identity;
- incoming `AniSpeedScale` is compatible `B*M`;
- compose via existing Hack Hit `C/B`;
- forward a local request copy changing only `AniSpeedScale`;
- caller request never mutated;
- no extra `GetAnimationSpeedModifier` call/state/cache/marker.

Remove together:
```text
Hook_SpeedModifierCall_42FF4
Hook_SpeedModifierCall_431B4
Hook_SpeedModifierCall_432EB
```
including declarations + InstallHooks registrations. Native call instructions remain untouched.

Add EV-417 fail-closed arithmetic guard in `ComposeCompatibleSpeed`: after finite-result validation, when incoming compatible speed is positive and composed result is non-positive, return the original compatible value. No clamp/new config rule.

Protected:
- all other Speed hooks incl. Power Raise unchanged;
- AttackRaise/BehaviorProfiles/INI unchanged;
- Finishing Action15 excluded;
- no new physical hook / no AttackCollision hook / no +0x42A0 entry hook;
- Collision wrapper/modules/guard unchanged.

Static acceptance:
- exactly one physical CombatMove hook remains;
- Hack caller hooks = 0;
- Hack request composition covers Raise/Hit/Recover only;
- unconfigured Hack preserves incoming scale;
- no double composition path;
- New Balance owner invoked only by original route;
- `git diff --check`;
- changed files exactly the 3 allowed files.

Commit/push to `development`. Report changed files/checks.  
Build: NOT ATTEMPTED — Work build execution was not authorized.  
Then STOP for Normal Chat review.
