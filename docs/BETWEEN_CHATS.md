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
ADR-0007 shared Speed/Raise schema = ACCEPTED
BehaviorProfiles foundation = PASS
implementation = 81d4964201579c9f7a989404426c3d9dc9ab4834
EV-391 Speed v2 caller-side mechanism = RECORDED
EV-392 Quick provenance + exact caller-set closure = PASS/RECORDED
CURRENT = bounded Speed v2 source implementation
ACTIVE TASK = docs/work/active/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md
BUILD/RUN = PROHIBITED for active source task
RAISE = PAUSED until Speed closes
```

## Frozen Speed v2 handoff

Required invariant:

```text
unconfigured = B * M
configured   = C * M
```

Production mechanism:

```text
selected Script_Game caller
-> EngineBridge-owned mCCallHook
-> pass factual incoming EAX action explicitly
-> invoke LIVE Script_Game+0x42A0 exactly once
-> receive compatible B*M
-> exact configured/evidenced route: * (C/B)
-> C*M
-> existing downstream playback path
```

Do not hook/own the `+0x42A0` entry. New Balance remains authoritative for its modifier calculation.

### Generic Quick closure

```text
Action3 / QuickAttack
-> GetPrimaryPoseExt(Action3, Hit)
-> PropertyAction = Action4 or Action5
-> +0x48677 calls +0x42A0 with factual 4/5
```

No separate Action3 speed hook is required on the proven route.

### Exact six call sites

```text
+0x383F0  Normal Action1 / Hit
+0x38E9D  FEA8 factual action carrier / Hit
+0x38F22  FEA8 factual action carrier / Hit
+0x3937D  FEA8 factual action carrier / Hit
+0x39402  FEA8 factual action carrier / Hit
+0x48677  Quick after Action3 -> Action4/5 / Hit
```

Explicitly exclude `+0x38A8B`: its `+0x158` value is propagated integerized `PSRoutine::GetStateTime()`, not factual Quick action. Also exclude inspected action27/28 and Action6 routes.

### Technical B facts

Keep `B` as immutable evidence data keyed by exact factual raw runtime facts. Profile selection remains normalized ADR-0007 identity.

Current first facts:

```text
Normal:
None+1H / Shield+1H / Torch+1H / 1H+1H = 0.6
None+2H / None+Axe / None+Staff / None+Halberd = 0.7

Quick Action4/5 = 1.0
```

Unknown/unproven routes fail closed. Do not treat normalized token equality as proof of technical B; retain raw UseTypes for B lookup. Normal Fist/PhysicalFist is outside this first composition contract.

## Active implementation boundary

Read and execute only:

`docs/work/active/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`

Expected source scope:

```text
EngineBridge.cpp
AttackSpeed.cpp/.h
BehaviorProfiles.cpp/.h
CMakeLists.txt
```

`EngineBridge` stays sole hook owner. `AttackSpeed` becomes composition policy only. Dormant prototype hook semantics are rejected.

Static/source audit only. **No build, deployment, runtime test, diagnostic logger or Raise work** in the active bounded task.

## After source implementation

```text
independent source review
-> User local build/deploy
-> New Balance composition validation first
-> unconfigured controls
-> depleted-stamina / relevant modifier preservation
-> native-only sanity/fallback
-> close Speed
-> only then Raise
```

Authorities: active task, `SESSION_ENTRYPOINT.md`, ADR-0004/0005/0007, EV-391/EV-392, `ANIMATION_RULES.md`, `WORK_IMPLEMENTATION_PROTOCOL.md`.

Hard exclusions: final-result replacement; same-hook load-order dependency; copied NB multiplier policy; global speed override; Action3 guesswork; StateTime-as-action matching; Raise; collision redesign.