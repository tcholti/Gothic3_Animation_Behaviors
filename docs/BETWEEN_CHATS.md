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
Speed v2 production source = IMPLEMENTED / SOURCE-REVIEW PASS
final reviewed source = 4f9911f57d8d6b36efd35adee41920560c3986e0
CURRENT = local build/deploy gate
RAISE = PAUSED until Speed closes
```

The first review caught one omission in `c11c1486...`: `AttackSpeed` was compiled but the six `EngineBridge` caller transports were missing. Correction `4f9911f5...` adds only the frozen transport; the correction diff leaves collision untouched.

Completed contract:

`docs/archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`

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
-> explicit factual EAX action
-> mCCaller invokes LIVE Script_Game+0x42A0 once with EAX restored
-> compatible result B*M
-> exact configured/evidenced route applies C/B
-> C*M
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

User is currently away from the local build/game PC. No more source work is required before the next gate.

When back on that PC:

```text
build source 4f9911f57d8d6b36efd35adee41920560c3986e0 via POP-02
-> deploy/hash via POP-03
-> startup/load gate via POP-04
-> New Balance runtime validation first
-> configured Normal/Quick full stamina
-> equivalent depleted stamina
-> representative modifier control(s)
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

Expected invariant: configured base changes **and** the relative compatible contextual modifiers remain effective.

No additional native-speed logger run is currently requested.
