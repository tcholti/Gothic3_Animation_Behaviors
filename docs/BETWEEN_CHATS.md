# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Source/authority checkpoint before audit handoff: `a4b2e5bb5cb4e1780a0f79ff7ac867f0187d1346`. Later commits are docs-only task routing.  
`main` remains frozen.

## Current state

```text
Collision = CLOSED/PASS through EV-390; protected / out of review scope
Speed v2 = CLOSED/PASS through EV-410
Raise sequencing = PASS EV-411–EV-412
Raise correction = EV-415
production correction source = aab0189f2067f00653f669792b7d267135c745f0
independent source review = PASS EV-416
corrected-source runtime acceptance = PENDING
```

## Assigned responsibility — full independent Speed + Raise audit

**READ-ONLY FORMAL REVIEW.** Apply POP-10. No edits, build, deploy, runtime test, probe, or documentation maintenance.

Review the complete current Speed + Raise implementation end to end: INI/config loading, `BehaviorProfiles`, ADR-0011 resolved profile identity, all supported Speed routes/call sites, `B*M -> C*M`, Sprint→Power inheritance, Hack/Finishing separation, AddRaise Off fallback, Normal/Quick R/L/Whirl continuation, Power Raise composition, Speed+Raise interaction, hook/calling-convention/RVA assumptions, simplicity/modularity/performance.

Primary source:
```text
BehaviorProfiles.cpp/.h
AttackSpeed.cpp/.h
AttackRaise.cpp/.h
EngineBridge.cpp
Ini/G3AnimationBehaviors.ini
```
Read directly connected Speed/Raise startup/config source only as needed.

Authorities: `docs/README.md` §0, `DESIGN.md` Speed/Raise, `SOURCE_HOOK_GUIDE.md`, `ENGINEERING_GUIDE.md`, ADR-0004/0005/0008/0009/0011, active Raise runtime-acceptance record. Use `EVIDENCE_INDEX.md` only when a premise needs proof.

### Protected Collision boundary

Do **not** review/redesign/propose cleanup to Collision modules, marker semantics, cleanup/repair, or `CollisionLifecycleGuard`. In shared `EngineBridge`, check only that Speed/Raise does not disturb the existing Collision invocation/hook boundary. Any issue requiring Collision changes is a STOP/escalation, not an ordinary fix.

### Compatibility — MUST PASS

Review against `Jackydima/gothic3sdk` `master` pinned at:
`bbe769075bc896085a620a0ceb3491192c5beb61`

Prioritize:
`scripts/Script_NewBalance/`
`scripts/Script_AttackCollision/`

Check exact hook/API/state overlap, chaining/load-order assumptions, duplicate execution/side effects, melee-state interactions, and whether current G3AB preserves New Balance contextual speed policy. In particular Power Raise must preserve the live value (Hero `1.5*M`, Orc `1.3*M` where applicable) and apply G3AB's Power ratio on top, never replace it.

Core invariants:
```text
unconfigured -> live compatible/native unchanged
ReferenceHitBaseSpeed = native Gothic B, not NB result
configured = compatible * (C/B)
no global +0x42A0 replacement
Quick = factual Action4/5, never Action3 inference
Sprint uses Power profile but preserves live contextual difference
custom Normal/Quick/Whirl Raise = exact incoming Hit AniSpeedScale
Power Raise = live compatible Raise * Power C/B
Hack/Pierce = no second Raise scale
Finishing = outside configured Speed
Collision = unchanged
```

Report findings by BLOCKER / MAJOR / MINOR / NOTE with exact file/function/hook and smallest Speed/Raise-owned correction. Do not manufacture refactors. Give verdicts for correctness, NB compatibility, AttackCollision compatibility, Collision non-interference, simplicity, modularity, performance, config/profile architecture, hook architecture, and runtime-test readiness.

End: `PASS`, `PASS WITH NON-BLOCKING NOTES`, or `FAIL`. Then STOP.
