# Speed + Raise — Final Bounded Source Review

**Status:** CLOSED/PASS — EV-431 independent review accepted  
**Mode:** independent read-only review  
**Production source under review:** `d642f30bcb6b564deaaffed26fd11b763da88163`  
**Prior large-review task baseline:** `d5d829e07eb2bfe8de428aa2ad148ba1f2d3835c`

## Purpose

Perform one final **bounded, independent source review** of the production Speed + Raise implementation before the repository-level release audit / promotion checkpoint.

This is intentionally smaller than the prior large Astra audit. Do not repeat broad historical research or re-audit unrelated repository areas merely for completeness.

## Review question

> Given the production changes since the prior large Speed+Raise audit, does the current integrated implementation remain correct, simple, modular, performant, and compatible with Gothic 3, Jackydima New Balance and AttackCollision, with Collision behavior left intact?

## Required startup

1. root `README.md` → Start Here;
2. `docs/SESSION_ENTRYPOINT.md`;
3. `docs/BETWEEN_CHATS.md`;
4. POP-10 in `docs/PROJECT_OPERATING_PROCEDURES.md`;
5. `docs/WORK_IMPLEMENTATION_PROTOCOL.md` only for review/boundary discipline;
6. this task;
7. relevant Speed/Raise sections of `docs/DESIGN.md` and `docs/SOURCE_HOOK_GUIDE.md` only as needed.

Use the pinned external SDK/reference already owned by the project. New Balance and AttackCollision compatibility remain hard requirements.

## Scope

Review the current production integration end to end, but prioritize the source delta since `d5d829e...`.

Primary production files:

```text
src/Script_G3AnimationBehaviors/AttackRaise.cpp
src/Script_G3AnimationBehaviors/AttackRaise.h
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
```

Dependency boundaries to inspect, but not redesign:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
```

Inspect Collision code only as far as necessary to verify shared EngineBridge transport/hook non-interference.

## Delta priorities

### 1. Hack Speed integration

Review:
- route-neutral CombatMove Hack speed adapter;
- Raise/Hit/Recover phase handling;
- retirement of the prior three caller-specific Hack speed hooks;
- exactly-once B*M -> C*M composition;
- New Balance multiplier preservation;
- AttackCollision compatibility;
- Finishing/Hack separation;
- underflow/fail-closed guard added after the prior audit.

### 2. Normal AddRaise direction continuation

Review:
- continuation-owned capture fields;
- `Game+0x16B056` GetAniName call hook;
- ABI/calling convention/original-function transport;
- capture on the exact synthetic Normal Raise;
- one-shot restore for its stored Action1 Hit;
- cancellation/reentrancy/lifetime behavior;
- no effect on Quick/Whirl/Power/Hack/unrelated GetAniName calls;
- no duplicate direction owner or filename policy.

### 3. Existing Speed/Raise composition

Reconfirm only enough to catch integration regressions:
- resolved animation-set profile identity;
- Quick factual Action4/5 -> shared Quick profile;
- Sprint -> Power profile inheritance;
- custom Normal/Quick/Whirl AddRaise sequencing;
- Hit speed reused for custom Raise;
- native Power Raise phase-relative compatible composition;
- missing/off settings preserve native behavior;
- partial Raise-resource coverage remains a runtime asset behavior, not a reason to add policy to C++.

## External compatibility

Hard requirement:
- Jackydima New Balance;
- Script_AttackCollision.

Re-check exact overlapping hooks/routes in the pinned reference. Inspect other external scripts only if a concrete current hook overlap requires it.

## Protected behavior / non-goals

```text
Collision = CLOSED/PASS and protected
no Collision redesign
no new hooks merely for cleanliness
no profile-schema redesign
no new probes
no runtime testing
no build/deploy
no source edits
no documentation edits
no refactor merely to produce a finding
```

If a real Speed/Raise issue would require modifying Collision ownership, report **STOP / architectural conflict** rather than proposing a Collision change.

## Evidence discipline

Use current accepted evidence through EV-430 only where it helps interpret code. Do not reload large runtime logs unless a specific source question genuinely requires one.

Do not treat runtime PASS as proof that unsafe source is correct; do not treat hypothetical possibilities as findings without a concrete reachable mechanism.

## Required report

Findings ordered:

```text
BLOCKER
MAJOR
MINOR
NOTE
```

For each substantive finding include:
- exact source/hook;
- factual problem;
- reachable failure mode;
- why it matters;
- smallest Speed/Raise-owned correction;
- New Balance / AttackCollision / Collision consequence.

Explicit verdicts:
- correctness;
- New Balance compatibility;
- AttackCollision compatibility;
- Collision non-interference;
- simplicity;
- modularity;
- performance;
- configuration/profile architecture;
- hook architecture;
- release-checkpoint readiness.

End with exactly one:

```text
PASS — ready for repository release audit / main promotion checkpoint
PASS WITH NON-BLOCKING NOTES
FAIL — correction required before repository release audit
```

Then STOP. Do not modify the repository.


## Closure — EV-431

Independent review result:

```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    EV-430 partial-resource evidence boundary only
```

All required verdicts passed, including New Balance compatibility, AttackCollision compatibility, Collision non-interference, configuration/profile architecture and hook architecture.

Final disposition:

`PASS — ready for repository release audit / main promotion checkpoint`

No repository files were changed by the reviewer.
