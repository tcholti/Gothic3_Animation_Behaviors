# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-441 attack movement source review

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains Collision + Speed + Raise stable through EV-433.

## Attack movement

Research/architecture closed through EV-440.

Production implementation:
`7393f390f30d1981a5065b6342a684cd590fbac9`

Independent source review:
`EV-441 PASS`

User-local build:
`EV-442 PASS — Release Win32 build succeeded`

Reviewed implementation:
```text
one physical hook: Game+0x16B8B7
BehaviorProfiles: optional Movement
AttackMovement: stateless policy
EngineBridge: transport only
97 shipping Movement keys: all Off
```

Semantics:
```text
Movement=Off
-> preserve native/New Balance

Movement=<finite non-negative number>
-> absolute authored-style factual Hit distance

Movement=0
-> active zero CombatMove translation
```

No Collision, AttackSpeed or AttackRaise source change.

## Active responsibility

`docs/work/active/ATTACK_MOVEMENT_RUNTIME_ACCEPTANCE.md`

Build is complete. Deployment/runtime were intentionally deferred at session end.

Next:
- Fetch/Pull latest documentation state if needed before continuing repository work;
- run the already accepted deployment/hash PowerShell script;
- require exactly one live G3AB project DLL;
- require built/live DLL SHA256 identity;
- require source/live INI SHA256 identity;
- require `G3AB RELEASE DEPLOYMENT PASS`;
- then
- Off-path compatibility;
- strong 0/short/long numeric contrast;
- New Balance On/Off override control;
- representative action/nonhuman sanity coverage.

No further source modification absent build/runtime contradiction.
