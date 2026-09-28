# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-28

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
latest closed collision evidence = EV-390
collision production integration = CLOSED/PASS
ADR-0007 shared Speed/Raise INI schema = ACCEPTED
BehaviorProfiles foundation = IMPLEMENTED + independent source-review PASS
implementation SHA = 81d4964201579c9f7a989404426c3d9dc9ab4834
Speed v2 mechanism proof = EV-391
Speed v2 Quick/caller-set static closure = EV-392

CURRENT = bounded Speed v2 source implementation
ACTIVE TASK = docs/work/active/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md
BUILD/RUN FOR ACTIVE TASK = PROHIBITED
RAISE = PAUSED until Speed is completely closed
```

## Shared profile foundation — accepted

Profile identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile(Normal|Quick)
```

Optional profile data:

```text
BaseSpeed=<positive finite float>
Raise=Native|On   # parsed/stored only; Raise behavior inactive
```

Semantics:

```text
BaseSpeed absent -> no G3AB Speed override
BaseSpeed=1.00 -> explicit authored base 1.00
duplicate normalized identity -> ambiguous -> no G3AB override
invalid identity -> ignored
INI parsed once during ScriptInit before hook installation
```

Exact schema: ADR-0007. Completed config task: `archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`.

## Speed v2 — frozen production mechanism

Required composition:

```text
unconfigured effective speed = B * M
configured effective speed   = C * M
```

`C` is the configured authored base; legitimate Gothic/New Balance contextual modifiers `M` remain effective.

For explicitly controlled Normal/Quick profiles, `1.0` remains the intended neutral authored playback scale. Native/mod `B` values such as `0.6`/`0.7` are technical facts only, not desired authoring defaults.

### Generic Quick / Action3 closure

Static tracing now closes the ADR-0007 Action3 gap:

```text
GetPrimaryPoseExt(Action3, Hit)
-> engine selects/writes PropertyAction = Action4 or Action5
-> later PropertyAction() returns 4/5
-> Script_Game+0x48677 calls +0x42A0 with EAX=4/5
```

Action3 is therefore selector/request identity on this proven route; actual playback-speed action is factual QuickAttackR/L 4/5.

### Exact production call-site set

EV-392 freezes six tested-build callers:

```text
Script_Game+0x383F0  Action1 / Normal / Hit
Script_Game+0x38E9D  factual FEA8 action carrier / Hit
Script_Game+0x38F22  factual FEA8 action carrier / Hit
Script_Game+0x3937D  factual FEA8 action carrier / Hit
Script_Game+0x39402  factual FEA8 action carrier / Hit
Script_Game+0x48677  generic Quick route after Action3 -> Action4/5 / Hit
```

Important exclusion:

```text
Script_Game+0x38A8B
```

is **not** a factual action carrier. Its apparent `+0x158` action value originates from integerized `PSRoutine::GetStateTime()` and is copied forward. Do not match numeric 4/5 there as Quick.

Other inspected non-targets remain excluded, including `+0x4AC6F` (action 27/28) and the `+0x4C6FA` Action6 route.

### Production transport

Do not own/hook the whole `Script_Game+0x42A0` entry.

```text
exact selected caller
-> EngineBridge-owned mCCallHook
-> pass incoming EAX factual action explicitly
-> invoke LIVE Script_Game+0x42A0 exactly once
-> compatible owner computes B*M
-> AttackSpeed applies C/B only for exact configured + evidenced route
-> C*M
-> existing downstream path
```

`EngineBridge.cpp` remains sole low-level hook owner. `AttackSpeed` owns feature composition only.

The pinned SDK supports the required transport:

```text
mCCallHook + AddRegArg(Eax)
mCCaller with EAX register argument for calling live +0x42A0
```

This avoids competing New Balance entry ownership and does not depend on arbitrary DLL load order.

### Technical base facts

The caller-side transform needs factual `B`; keep it as a small immutable technical data lookup keyed by exact runtime facts, not weapon-policy branches and not a new INI field.

Current first production facts under the primary New Balance stack:

```text
Normal Action1:
None+1H       -> 0.6
Shield+1H     -> 0.6
Torch+1H      -> 0.6
1H+1H         -> 0.6
None+2H       -> 0.7
None+Axe      -> 0.7
None+Staff    -> 0.7
None+Halberd  -> 0.7

Quick Action4/5 -> 1.0
```

Runtime profile matching still uses normalized ADR-0007 animation tokens. Technical `B` lookup must preserve **raw** UseTypes separately because multiple raw UseTypes can serialize to the same animation token while not sharing the same compatible base policy.

Fail closed for unsupported/unproven routes. Normal Fist/PhysicalFist is explicitly outside this first composition contract because current New Balance's special Fist Normal branch does not use the ordinary `B*M` path.

## Primary compatibility environment

Keep live during later Speed runtime testing:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

New Balance compatibility is primary; native-only testing is later sanity/fallback.

Pinned Jackydima source:

```text
316d32406a133f8884e7e302752c35f66b4f54fc
```

Pinned SDK:

```text
90bfd344de4510dda7ac9da7461cc7f1eac911f7
```

Pinned binary reference:

```text
c9d12cb5f0dcb4f96af6a82c02138c1c15e981b6
```

## Immediate route

```text
1. execute ONLY docs/work/active/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md
2. source/static audit only; no build/run in that task
3. independent source review after implementation commit
4. User local build/deploy
5. validate New Balance configured/unconfigured + modifier preservation
6. native-only sanity/fallback
7. close Speed completely
8. only then begin Raise
```

No diagnostics-only Speed probe is currently justified before implementation.

## Read next

- exact active responsibility -> `work/active/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`
- exact handoff -> `BETWEEN_CHATS.md`
- Speed authority -> `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`
- generic profile architecture -> ADR-0005 + ADR-0007
- static mechanism/closure evidence -> EV-391 + EV-392 in `EVIDENCE_LEDGER_389_ONWARD.md`
- runtime normalization -> `ANIMATION_RULES.md` §§3–5
- implementation protocol -> `WORK_IMPLEMENTATION_PROTOCOL.md`

## Still paused

```text
NO Raise implementation/research while Speed is open
NO AttackContinuationProtection
NO targeting/climbing
NO promotion to main before agreed integrated checkpoint
NO collision redesign absent contradictory evidence
```