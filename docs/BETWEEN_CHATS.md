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
final corrected Speed source = db7b24f1a0c19beaaf4e720cd69d19c331854340
CURRENT = local build/deploy/startup/runtime gate
RAISE = PAUSED until Speed closes
```

The Work audit independently re-derived the six caller sites, `+0x38A8B` exclusion, SDK x86 ABI, live-owner New Balance interaction, `B*M -> C*M` composition, fail-closed matrix and module responsibility boundaries. No blocker or major finding was found.

The only audit finding was MINOR S-01: extreme positive finite `BaseSpeed` could overflow the composed result. Correction `db7b24f1...` changes only `AttackSpeed.cpp` to return the live compatible result when `composedSpeed` is non-finite. Focused source review PASS.

Archive records:

```text
docs/archive/investigations/SPEED_V2_DEEP_INDEPENDENT_STATIC_AUDIT_RESULT.md
docs/archive/investigations/SPEED_V2_S01_FINITE_OUTPUT_GUARD.md
docs/archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md
```

`docs/work/active/` is clean except README.

## Frozen Speed v2 implementation

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

Do not hook `+0x42A0` itself. Do not hook `+0x38A8B`. Unconfigured/unsupported routes return the compatible result unchanged.

Technical bases:

```text
Normal:
None+1H / Shield+1H / Torch+1H / 1H+1H = 0.6
None+2H / None+Axe / None+Staff / None+Halberd = 0.7
Quick Action4/5 = 1.0
```

Normal Fist/PhysicalFist and non-Hero routes remain unsupported/fail-closed in this first Speed contract.

## Next

When back on the local build/game PC:

```text
build current development source containing db7b24f1... via POP-02
-> deploy/hash via POP-03
-> startup/load via POP-04
-> New Balance runtime validation first
-> configured Normal/Quick full stamina
-> equivalent depleted stamina
-> representative compatible modifier control(s)
-> unconfigured controls
-> supported hand configurations
-> native-only sanity/fallback
-> close Speed
-> Raise only afterward
```

Primary runtime stack:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Expected runtime invariant: configured base changes **and** the relative compatible contextual modifiers remain effective.

No additional native-speed logger run is currently requested.
