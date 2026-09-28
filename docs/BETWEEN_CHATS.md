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
CURRENT = deep independent static audit before local build/deploy
ACTIVE = docs/work/active/SPEED_V2_DEEP_INDEPENDENT_STATIC_AUDIT.md
RAISE = PAUSED until Speed closes
```

The first review caught one omission in `c11c1486...`: `AttackSpeed` was compiled but the six `EngineBridge` caller transports were missing. Correction `4f9911f5...` adds only the frozen transport; the correction diff leaves collision untouched.

The User requested one additional heavy Work audit because the earlier implementation/review sequence suffered repeated interrupted/timed-out Chats. This audit is intentionally independent and adversarial: it must re-derive the critical caller/ABI/compatibility facts from pinned SDK, binary-reference and New Balance sources rather than rubber-stamping the earlier evidence. Production-code edits/build/run are prohibited inside the audit.

Active audit contract:

`docs/work/active/SPEED_V2_DEEP_INDEPENDENT_STATIC_AUDIT.md`

Completed implementation contract:

`docs/archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`

## Frozen Speed v2 implementation under audit

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

Technical bases under audit:

```text
Normal:
None+1H / Shield+1H / Torch+1H / 1H+1H = 0.6
None+2H / None+Axe / None+Staff / None+Halberd = 0.7
Quick Action4/5 = 1.0
```

Normal Fist/PhysicalFist and non-Hero routes remain unsupported/fail-closed in this first Speed contract.

Pinned independent references:

```text
SDK:              georgeto/gothic3sdk@90bfd344de4510dda7ac9da7461cc7f1eac911f7
New Balance:      Jackydima/gothic3sdk@316d32406a133f8884e7e302752c35f66b4f54fc
Binary reference: tcholti/Gothic3_Binary_Reference@c9d12cb5f0dcb4f96af6a82c02138c1c15e981b6
```

## Next

```text
run ONLY the deep independent static audit in Work
-> return its full report to Normal Chat
-> if BLOCKED: freeze smallest separate correction task
-> if PASS / PASS WITH NON-BLOCKING FINDINGS:
   local build via POP-02
   -> deploy/hash via POP-03
   -> startup/load via POP-04
   -> New Balance runtime validation
   -> configured Normal/Quick full stamina
   -> equivalent depleted stamina
   -> representative modifier control(s)
   -> unconfigured controls
   -> supported hand configurations
   -> native-only sanity/fallback
   -> close Speed
   -> Raise only afterward
```

Primary later runtime stack:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

Expected runtime invariant: configured base changes **and** the relative compatible contextual modifiers remain effective.

No additional native-speed logger run is currently requested.
