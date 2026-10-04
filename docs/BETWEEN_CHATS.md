# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
`main` frozen. Collision CLOSED/PASS and protected.

## Current state

```text
Speed v2 core = CLOSED/PASS through EV-410
Raise correction source = aab0189f... / static PASS EV-416
full Speed+Raise audit = EV-417
MAJOR = pinned AttackCollision replacement Hack bypasses G3AB Hack caller patches
MINOR = positive finite composition can underflow to zero
build/runtime acceptance = BLOCKED pending M1 correction
```

External compatibility reference:
`Jackydima/gothic3sdk@bbe769075bc896085a620a0ceb3491192c5beb61`

## Assigned responsibility — AttackCollision Hack Speed causal design

**READ-ONLY BOUNDED RESEARCH/DESIGN.** No source/docs edits, build, runtime, probes, commits or pushes.

Establish the smallest route-safe correction for EV-417 M1.

Must inspect:
- G3AB `AttackSpeed.cpp/.h`, `EngineBridge.cpp`, `BehaviorProfiles.cpp/.h`;
- existing sole `sAICombatMoveInstr` bridge/AttackRaise path only as needed;
- native tested-build Hack state / callers `+0x42FF4,+0x431B4,+0x432EB`;
- pinned `scripts/Script_AttackCollision/Script_AttackCollision.cpp`;
- pinned New Balance speed owner where compatibility matters.

Primary candidate to prove or reject:

```text
remove Hack authoring from the three native +0x42A0 caller patches
-> compose factual Action14 Hack at the shared CombatMove request boundary
-> consume the already-computed request AniSpeedScale as compatible B*M
-> apply Hack C/B exactly once
-> cover native Gothic + AttackCollision replacement without hooking AttackCollision DLL
```

Research requirements:
1. Map native Hack Raise/Hit/Recover speed calls through CombatMove and prove what `AniSpeedScale` contains if the three G3AB native caller hooks are absent.
2. Map AttackCollision replacement Raise/Hit/Recover likewise.
3. Prove whether one CombatMove-boundary rule can distinguish factual Hack from Finishing and avoid double composition.
4. Preserve ADR-0011 Hit-profile identity, New Balance side effects/results exactly once, and unconfigured pass-through.
5. Check interaction with `AttackRaise::RunCombatMove`: ordering, stored requests, FullStop, re-entry.
6. Confirm Collision invocation/lifecycle wrappers remain untouched.
7. Compare candidate against alternatives; strongly prefer no third-party-DLL RVA/function hook and no `+0x42A0` entry takeover.
8. Include EV-417 minor underflow guard in the eventual correction only if it remains a trivial independent fail-closed change.

Output:
- exact native/external data-flow;
- candidate PASS/REJECT with reasons;
- frozen smallest source/hook boundary if proven;
- files/functions to change;
- hooks to remove/add;
- compatibility/double-scale proof;
- focused later runtime fixture;
- STOP if no safe Speed-owned correction exists.

No implementation. Then return to Normal Chat.
