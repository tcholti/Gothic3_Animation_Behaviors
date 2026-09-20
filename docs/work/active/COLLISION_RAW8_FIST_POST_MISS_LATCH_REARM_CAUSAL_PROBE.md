# Gothic 3 — Raw8 FIST Post-Miss Latch-Rearm Causal Probe

**Status:** ACTIVE — IMPLEMENTED / NORMAL CHAT SOURCE REVIEW PASS / RUNTIME PENDING
**Opened:** 2026-09-20
**Evidence basis:** EV-346–EV-347
**Production behavior change:** PROHIBITED
**Work build execution:** PROHIBITED

## Repository

`https://github.com/tcholti/Gothic3_Animation_Behaviors.git`

Branch:

`docs/collision-source-evidence`

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/FEATURE_DEVELOPMENT_METHOD.md`
6. `docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`
7. `docs/SOURCE_HOOK_GUIDE.md`

Then inspect only the exact source required by this frozen causal contract.

## Agreed design target — context only

Raw8 FIST authoring target:

```text
FIST
-> one target-directed native body-contact damage opportunity OPEN

unsuccessful native contact
-> opportunity remains OPEN

successful native contact
-> opportunity consumed

later FIST
-> opportunity rearmed

C1 / Hit termination
-> unused opportunity closed
```

No raw8 FIST_OFF absent future contradictory evidence.

This task does **not** implement the final production window.

## Established facts

EV-346:
- Gargoyle factual Action2 / Power / exact RIGHT Fist / UseType8;
- early frame-3 synthetic FIST can hit or miss depending on range;
- frame-6/native-timed FIST restores reliable contact.

EV-347:
- four exact frame-3 `SyntheticApplied=1` opportunities were observed;
- two exact misses and two exact native raw8 hits;
- every attempt returned with `SPU+0x164 = 1`;
- exact successful hit in the tested route is observable in the same invocation as:
  - caller return `Game.dll + 0x0016E348`;
  - `entityArgument1 == exact fistSourceInstance`;
  - `entityArgument2 == exact actorInstance`;
- existing `AICombatMoveInstr` wrapper provides the post-original boundary;
- no new hook is required.

Historical EV-231 additionally proves that a same-C1 explicit `SPU+0x164: 1 -> 0` write can rearm the confirmed native raw8 damage path at later/native timing.

## Single causal question

> If an exact marked raw8 Power execution consumes an early synthetic timing permission, produces no exact same-invocation native raw8 damage, and returns with the same exact identity and `SPU+0x164 = 1`, does writing that latch back to `0` **once** preserve a later native damage opportunity when the target is reached?

This task changes only the latch after a proven miss.

Do **not** rearm or extend the synthetic timing permission.

## Expected causal contrast

Far-range Gargoyle frame-3 case:

```text
FIST at frame 3
-> early synthetic native attempt
-> no exact raw8 damage
-> post-attempt latch 1
-> probe writes 1 -> 0 once
-> later iterations use only real/native timing
-> when Gothic's ordinary timing threshold is reached, native raw8 gets another opportunity
```

Close-range Gargoyle frame-3 case:

```text
FIST at frame 3
-> early synthetic native attempt
-> exact raw8 damage occurs
-> latch remains 1
-> probe performs NO rearm
-> no second damage opportunity from this marker
```

A causal PASS requires evidence that the post-miss write can produce the later native opportunity while the already-successful early path remains consumed.

This does not yet prove continuous eligibility between frame 3 and Gothic's native threshold. That is deliberately a later question.

## Required architecture

Because this task changes runtime behavior experimentally, follow `FEATURE_DEVELOPMENT_METHOD.md`.

Create a narrow temporary diagnostic-only probe module, preferably:

```text
Raw8FistWindowProbe.cpp
Raw8FistWindowProbe.h
```

The probe owns:
- eligibility for this temporary intervention;
- exact same-invocation success/miss classification;
- the one post-miss latch write;
- probe-specific logging/state.

Compile the probe into `Script_FrameCollisionTest` only, never `Script_FrameCollisionBehaviorTest`.

`EngineBridge` remains the physical hook owner and may receive only the smallest delegation seam needed to:
- begin/end exact invocation scope;
- pass the existing `OnDamage` call facts to the probe;
- allow the probe to enact the bounded post-original decision.

Do not move experimental policy into `EngineBridge` or permanent `Raw8FistCollision`.

The existing EV-347 observation diagnostics may remain as factual logging support if useful, but do not turn diagnostic counting alone into the intervention criterion.

## Exact intervention eligibility

The temporary latch write may occur only when all of the following are factual and still matched:

- exact marked raw8 execution already owned by the current raw8 mechanism;
- factual `Action=2 / Family=POWER` for this bounded first probe;
- exact current `gEUseType_Fist` / raw8 source;
- same actor;
- same SPU;
- same C1 generation;
- same current animation/motion identity;
- the current exact invocation consumed raw8 timing permission;
- `SyntheticApplied=1`;
- original `AICombatMoveInstr` has returned;
- current post-attempt latch is exactly `1`;
- **no** exact same-invocation native raw8 damage event matched all of:
  - caller `Game.dll + 0x0016E348`;
  - entityArgument1 == exact fist source;
  - entityArgument2 == exact actor.

Then and only then:

```text
SPU+0x164 1 -> 0
```

once for that failed synthetic attempt.

Read back and log the result.

## Successful-contact branch

If the exact same-invocation native raw8 damage identity above is observed:

```text
DO NOT write latch
DO NOT rearm timing
DO NOT clear anything
```

The native successful opportunity remains consumed.

## Protected behavior / prohibited changes

Do not:
- rearm timing permission;
- synthesize another GetPlayTime result;
- add a timer or polling;
- add a new engine hook;
- call damage directly;
- alter target selection/contact;
- clear triggered lists;
- mutate collision groups;
- add FIST_OFF;
- change unmarked raw8 behavior;
- change raw8 Normal/Quick/Sprint behavior in this bounded first probe;
- change raw55;
- change equipped weapons;
- change equipped Sprint;
- change production integration under `src/Script_G3AnimationBehaviors`.

No species-name gate is allowed. Gargoyle is the runtime fixture, not the semantic classifier.

## Diagnostic logging

Add one compact probe record sufficient to establish:
- exact identities;
- synthetic attempt consumed;
- exact native raw8 damage observed yes/no;
- post-attempt latch before probe;
- rearm requested yes/no;
- latch after probe;
- reason for no rearm when appropriate.

Do not duplicate full existing CORE logging unnecessarily.

## Stop conditions

Stop without implementing broader behavior if:
- exact `Game+0x16E348` / source / actor success identity cannot be obtained faithfully through the existing `OnDamage` hook;
- the existing invocation scope cannot bind that event to the exact synthetic attempt;
- the post-original boundary no longer has safe exact SPU/C1/source identity;
- faithful implementation would require a new hook, timing rearm, custom damage, target inference or species policy.

Report the contradiction to Normal Chat instead.

## Allowed files

Expected narrow scope:
- new `Raw8FistWindowProbe.cpp/.h`;
- `EngineBridge.cpp` for minimal diagnostic delegation;
- `CollisionDiagnostics.cpp/.h` for compact probe log;
- `CMakeLists.txt` only to compile the temporary module into diagnostic twin only;
- the smallest existing diagnostic-only interface seam if mechanically required.

Do not edit permanent raw55/equipped feature modules.

## Build / publication

Work build execution is **PROHIBITED**.

The User explicitly authorizes publication of this bounded diagnostic-only causal implementation to:
- repository: `tcholti/Gothic3_Animation_Behaviors`
- branch: `docs/collision-source-evidence`

Perform source/static checks only.

## Required report

Report:
- final remote commit SHA;
- changed files;
- concise causal intervention implemented;
- confirmation that the behavior-only twin excludes the probe;
- protected behavior confirmation;
- source/static checks;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`;
- any material contradiction.

Then STOP.


## Implementation checkpoint — 2026-09-20

Work implementation:

`ea652e3324fffb07da013229a2fd374c4f3b1c6b`

Parent:

`33840f0e8970b169bb8532accc23f2807b21a06c`

Normal Chat independent source review: **PASS**.

Review findings:
- exact four-file scope;
- temporary `Raw8FistWindowProbe` owns intervention policy/state;
- probe sources compile only into `Script_FrameCollisionTest`;
- shared behavior source list is unchanged;
- every EngineBridge probe reference is guarded by `FRAME_COLLISION_DIAGNOSTICS`;
- no new hook is installed;
- synthetic-attempt observation occurs only when existing `Raw8FistCollision::ApplyTimingPermission()` returns greater than real play time;
- exact success classification requires `Game.dll+0x16E348` + exact fist source pointer + exact actor pointer;
- the one latch write is post-original only, exact miss only, exact Power/raw8/current-identity only, latch 1 -> 0 with readback;
- successful exact native damage branch cannot request the write;
- no timing rearm, custom damage, target/contact mutation, trigger clear, collision-group mutation, species rule, raw55/equipped/Sprint change or production integration change was found.

Runtime evidence is pending.
