# Attack Movement — Absolute-Distance Architecture Review

**Status:** CLOSED / PASS — EV-440  
**Mode:** independent read-only static architecture/source-hook review  
**Parent research:** `docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RESEARCH.md`

## Purpose

Independently challenge EV-438/EV-439 before production implementation is frozen.

Review only whether the proposed **absolute per-profile Hit movement** architecture is correct, minimal, modular, and compatible with native Gothic, New Balance, AttackCollision, and the already-accepted G3AB Collision/Speed/Raise systems.

Do not redesign the feature unless a concrete defect requires it.

## Frozen intended semantics

```text
<Attack>_Movement=Off
= G3AB does not alter CombatMove movement for that attack

<Attack>_Movement=<finite non-negative number>
= absolute authored-style CombatMove distance for that factual Hit

Movement=0
= valid: no CombatMove movement for that Hit
```

With New Balance installed:
- Off must preserve New Balance exactly;
- configured numeric movement deliberately overrides New Balance's final Hit **magnitude** for that attack;
- final direction and Gothic downstream stopping/navigation behavior remain native/compatible.

## Candidate architecture under review

```text
BehaviorProfiles
= optional movement value stored with existing AttackSettings/profile identity

AttackMovement
= action eligibility + absolute-distance policy + vector magnitude composition

EngineBridge
= one physical insert immediately before Game+0x16B8B7
```

Candidate runtime flow:

```text
native CombatMove resolves motion/direction/speed
-> native filename movement scaling at +0x16B8A3
-> New Balance CombatMoveScale at +0x16B8A9 if installed
-> G3AB movement insert
-> original Game+0x16B8B7 EnableCombatMovementFromSPU call unchanged
```

Configured math:

```text
T = current primary motion max time / request.AniSpeedScale
desiredVelocityMagnitude = configuredMovement / T
preserve final compatible direction
replace magnitude only
```

No movement setting -> no mutation.

## Required review checks

### 1. Exact binary/hook transport

Reverify against the tested Gothic binary reference:
- `Game+0x16B8B7` is the exact CombatMove-specific call to `Game+0xEA0C0`;
- its receiver/arguments;
- the final vector argument points to the intended `SPU.m_DirectionVec`;
- whether an `mCCallHook::InsertCall` immediately before this call can receive `[EBP+8]` CombatMove args and `[EBP+0xC]` SPU without corrupting ECX/stack/register state;
- what exact hook builder transport would be safest.

### 2. Load-order / New Balance compatibility

At the project pin:
`references/jackydima-gothic3sdk @ 316d32406a133f8884e7e302752c35f66b4f54fc`

Verify:
- New Balance inserts at `Game+0x16B8A9`;
- the proposed G3AB insert is downstream and does not replace/chain the same physical hook;
- Off path cannot disturb New Balance;
- configured path sees New Balance's final direction before replacing only magnitude;
- no New Balance module detection is required.

### 3. AttackCollision compatibility

Verify the pinned AttackCollision source does not own/hook `+0x16B8A9/+0x16B8B7` or otherwise bypass the downstream movement seam for factual Hack.

### 4. Speed interaction

Verify:
- request `AniSpeedScale` at this path is already the final composed Speed value;
- movement must not query `GetAnimationSpeedModifier` again;
- `maxTime / AniSpeedScale` is the correct same duration basis used by native/New Balance;
- the movement setting therefore controls nominal distance while Speed controls how quickly that distance is traversed.

### 5. Raise/phase interaction

Verify:
- movement policy can gate strictly on factual physical Hit;
- AddRaise's synthetic Raise/stored Hit sequence does not require movement state;
- Raise/Recover remain untouched;
- no duplicate movement composition occurs.

### 6. Profile/action mapping

Review the cleanest reuse of current `BehaviorProfiles`:
```text
Normal
Quick (Action4/5 factual routes)
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Sprint should inherit Power only if the factual route/evidence makes that safe at this seam. Do not create Sprint-specific configuration merely for symmetry.

Finishing/JumpAttack/RamAttack are outside initial scope.

### 7. Fail-closed behavior

Required:
- null/invalid context -> untouched;
- unsupported/non-Hit -> untouched;
- missing/Off/invalid setting -> untouched;
- invalid/non-positive duration -> untouched;
- positive movement + degenerate final vector -> untouched;
- configured zero -> zero vector is valid.

EV-439 establishes that the known native `Troll_None_Fist` zero-distance attack set could not be made to occur in runtime and is not the factual Troll route used by this project. Do not justify a second hook/state machine solely for that unused route.

### 8. Simplicity / modularity / performance

Explicitly assess whether the candidate preserves:
- one movement hook only;
- stateless per-request behavior;
- no filename parsing;
- no per-frame polling;
- no third-party hooking/detection;
- no Collision source changes;
- no Speed/Raise policy changes;
- O(1) profile lookup / bounded work.

## Non-goals

Do not:
- implement code;
- modify docs;
- build/deploy/run Gothic 3;
- create a probe;
- redesign New Balance;
- add archive injection;
- broaden to execution/jump/ram actions.

## Required report

Findings ordered:
```text
BLOCKER
MAJOR
MINOR
NOTE
```

For each substantive finding give:
- exact source/address;
- reachable failure mode;
- smallest correction;
- compatibility consequence.

Explicit verdicts:
- hook/ABI safety;
- native compatibility;
- New Balance compatibility;
- AttackCollision compatibility;
- Speed compatibility;
- Raise compatibility;
- profile architecture;
- simplicity;
- modularity;
- performance;
- production-freeze readiness.

End with exactly one:

```text
PASS — absolute movement architecture ready for production freeze
PASS WITH NON-BLOCKING NOTES
FAIL — architecture correction required
```

Then STOP. Do not modify the repository.


## Closure — EV-440

Independent result:
```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    3
PASS WITH NON-BLOCKING NOTES
```

The three notes were promoted into EV-440 as mandatory implementation details. No architecture correction is required.
