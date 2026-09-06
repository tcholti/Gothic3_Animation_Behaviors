# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N6B timing-gate observability CLOSED/PASS; N6C causal timing-gate probe IMPLEMENTATION FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file, then `docs/WORK_IMPLEMENTATION_PROTOCOL.md`. This bridge is the authoritative transient continuation where older durable wording still names an earlier Fist step as current.

---

## Closed / protected boundary

```text
collision architecture verification              COMPLETE — EV-206–EV-215
equipped-weapon RIGHT/LEFT/BOTH/OFF architecture CLOSED/UNCHANGED
Power marker adapter validation                  CLOSED/PASS
Pierce marker adapter validation                 CLOSED/PASS
SimpleWhirl current marker/semantic stage        CLOSED/PASS
Hack isolated routing/source/marker validation   PASS
Fist body-contact semantics                      CLOSED/PASS — EV-029, EV-080–EV-084
Fist Stage A marker/source plumbing              CLOSED/PASS — causal ON interpretation superseded
Fist Stage B DamageDisabled intervention         CLOSED/FAIL AS OFF MECHANISM
Fist N2C native damage path                      CLOSED/PASS
Fist N2D latch-1 suppression                     CLOSED/PASS
Fist N2E fresh-move latch reset                  CLOSED/PASS
Stage C production FIST_OFF                      CLOSED/PASS
N3 same-move latch-zero rearm                    CLOSED/PASS — CASE A — EV-231
N4 Fist OnAI_Attack suppression necessity        CLOSED/PASS
N5 Fist TouchDamage.ClearTriggeredList necessity CLOSED/PASS
N6A native Fist timing/eligibility static trace  CLOSED/PASS
N6B native timing-gate runtime observability     CLOSED/PASS
N6C first-FIST timing-gate causal intervention   CURRENT — IMPLEMENTATION CONTRACT FROZEN
```

Do not reopen these findings without concrete contradictory evidence.

---

## Architectural boundary — shared marker infrastructure, separate native mechanisms

Human Fist is not an equipped-weapon source-adapter special case.

```text
Generic authored-marker infrastructure
        |
        +--> Equipped-weapon collision mechanism
        |       RIGHT / LEFT / BOTH / OFF
        |       equipped identities
        |       Item_Attack / Item_Equipped
        |       weapon ClearTriggeredList repeated-contact semantics
        |       marker-owned weapon source masks/windows
        |       weapon C1 lifecycle / C1-R1 cleanup
        |
        +--> Human Fist/body-damage mechanism
                FIST / FIST_OFF
                exact human gEUseType_Fist / raw 8
                sAICombatMoveItlLoop native timing/eligibility
                SPU+0x164 factual combat latch
                gCEntity::OnDamage dispatch

                no equipped weapon source masks
                no Item_Attack ownership assumption
                no weapon marker-owned window
                no weapon C1 lifecycle obligation
                no Fist-specific weapon-style OnAI_Attack suppression
                no Fist TouchDamage.ClearTriggeredList operation
```

Shared generic pieces may still include exact motion/frame-effect scanning, reserved-marker recognition, marker occurrence/dedupe bookkeeping, factual C1-generation execution identity, exact animation/action/phase context, and generic marked-execution opt-in.

Exact logical human `gEUseType_Fist` / raw 8 is a body-contact source, not literal right-hand weapon collision. Controlled tests established damaging contact through at least left hand, right hand, left leg, right leg and head. Do not generalize this to `gEUseType_PhysicalFist` / raw 55 or monsters.

---

## Confirmed native human-Fist path

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game.dll + 0x16DD00

    tested generic arm
    Game.dll + 0x16DFB9
        cmp byte ptr [SPU+0x164], 0
        nonzero -> exit before damage

    native timing gate
        GetMaxTime(motion type 0)
        * native double at Game.dll RVA 0x308308
        compared with GetPlayTime(motion type 0)

        GetPlayTime < threshold
            -> jump to common exit Game.dll + 0x16E352

        GetPlayTime >= threshold
            -> continue directly into native damage preparation
            -> Game.dll + 0x16E1A3 writes SPU+0x164 = 1

    later confirmed gCEntity::OnDamage call
        caller return Game.dll + 0x16E348
```

Protected latch interpretation:

```text
SPU+0x164 = 1
    suppresses confirmed tested dispatch path

fresh combat move
    naturally restores tested latch to 0

same-move explicit 1 -> 0
    causally rearms confirmed dispatch after FIST_OFF

latch 0 by itself
    is NOT complete authored FIST ON
```

---

## N6A closure — static timing gate isolated

Binary authority:

```text
Repository: tcholti/Gothic3_Binary_Reference
builds/current_tested/modules/Game/disassembly/part_0093.txt
builds/current_tested/modules/Game/disassembly/part_0094.txt
builds/current_tested/modules/Game/imports.txt
```

Relevant static control flow:

```text
Game + 0x16E160
    GetMaxTime(motion 0)

Game + 0x16E16E..0x16E17C
    GetMaxTime * qword [Game + 0x308308]
    -> timing threshold

Game + 0x16E180
    GetPlayTime(motion 0)

Game + 0x16E186..0x16E190
    compare play time against threshold
    below -> common exit +0x16E352

Game + 0x16E196..0x16E1A3
    passing comparison continues directly
    +0x16E1A3 writes SPU+0x164 = 1
```

Engine import mapping:

```text
Game IAT 0x1024C5F8 -> eCWrapper_emfx2Actor::GetPlayTime
Game IAT 0x1024C5FC -> eCWrapper_emfx2Actor::GetMaxTime
```

SDK signatures are factual:

```text
GEDouble eCWrapper_emfx2Actor::GetPlayTime(eEMotionType) const
GEDouble eCWrapper_emfx2Actor::GetMaxTime(eEMotionType) const
```

---

## N6B closure — timing gate correlated at runtime

Implementation:

```text
2c32d6bb6301801d259d69d9890356c34673c2cb
Add N6B Fist native timing-gate probe
```

Canonical raw evidence:

```text
research/raw/2026-09-06_fist_n6b_native_timing_gate.log
01796a5b63d243430d0d1ede730dc0ac69c85159  evidence commit
```

Controlled fixture remained:

```text
same P0 Normal human raw-8 Fist animation
same Golem target/setup
frame 3  FIST
frame 9  FIST_OFF
frame 12 FIST
```

Repeated representative observations:

```text
PrimaryMaxTime                  ~0.680000007 s
NativeThresholdConstant        ~0.600000024
ComputedThreshold              ~0.408000021 s

first FIST play time            ~0.112–0.116 s
first FIST BelowThreshold       1
first FIST AtOrAboveThreshold   0
first FIST latch                0 -> 0
visual first punch damage       NO

FIST_OFF play time              ~0.353–0.356 s
FIST_OFF BelowThreshold         1
FistOffLatchBefore              0
FistOffLatchAfter               1

second FIST play time           ~0.477–0.480 s
second FIST BelowThreshold      0
second FIST AtOrAboveThreshold  1
second FIST latch               1 -> 0
visual second punch damage      YES

later OnDamage caller           Game.dll + 0x0016E348
second-FIST -> OnDamage delay   ~10–11 ms in representative executions
```

N6B conclusion:

> In the controlled human raw-8 fixture, the native motion-time threshold cleanly distinguishes the early first FIST from the later damaging opportunity. Latch zero is necessary but not sufficient: the tested native path also requires motion play time to have reached the 60%-of-max-time threshold before it can advance into the native latch-write/damage-preparation arm.

This is strong runtime correlation plus the N6A static control-flow relation. It is not yet causal proof that forcing only this timing comparison to pass is sufficient to advance the native path.

---

# N6C FULL WORK IMPLEMENTATION CONTRACT

## Frozen causal question

```text
When the first accepted authored FIST occurs while the real motion-0 play time
is still below the proven native threshold and SPU+0x164 is already 0, does
making ONLY the next matching Game.dll + 0x16E180 GetPlayTime result appear
just above that threshold cause the native sAICombatMoveItlLoop path to advance
past the timing gate and perform its own SPU+0x164 = 1 write before frame-9
FIST_OFF, while the actual animation play clock remains unchanged?
```

N6C changes exactly one causal variable: **the value returned to one native timing comparison after the first authored FIST**.

### Primary causal endpoint — NOT visual damage

Do **not** define N6C PASS as “first punch visually damages the Golem.” Frame 3 may precede physical target/contact eligibility, and downstream target/contact checks remain outside this experiment.

The direct native consequence of passing the timing comparison is already known statically:

```text
comparison passes
-> Game + 0x16E196
-> Game + 0x16E1A3 writes SPU+0x164 = 1
-> later target/contact/damage preparation continues
```

Therefore the primary runtime endpoint is:

```text
N6B baseline at frame-9 FIST_OFF:
    FistOffLatchBefore = 0

N6C causal expectation:
    one first-FIST timing override consumed
    + FistOffLatchBefore = 1
```

That difference directly tests whether the native path advanced through its own `+0x16E1A3` latch write. Early `Game + 0x16E348` OnDamage before FIST_OFF would be stronger additional evidence, but it is not required for N6C PASS.

## Required base state

Work must begin from the exact branch HEAD containing this contract. The invoking handoff supplies that SHA. If remote HEAD differs, STOP and report the mismatch rather than rebasing or broadening.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`

Then inspect only the source/API material required for this exact causal probe.

## Required binary/API transport

### Exact native call site

Target only:

```text
Game.dll + 0x16E180
FF 15 ...    call Engine import eCWrapper_emfx2Actor::GetPlayTime
```

In this tested arm:

```text
ECX = eCWrapper_emfx2Actor* used as the GetPlayTime this pointer
EDI = the same gCScriptProcessingUnit* whose [EDI+0x164] latch is checked/written
original stack argument = motion type 0, already pushed by native code
```

Before implementing, Work must confirm these register/call-site facts against the tested binary reference. If they contradict the current binary reference, STOP and report the contradiction.

### Use mCCallHook — do not patch the branch

Use a diagnostics-only `mCCallHook` at `RVA_Game(0x16E180)`.

The Gothic 3 SDK `mCCallHook` implementation factually:

- decodes the instruction at the supplied call address;
- verifies it is an `FC_CALL`;
- records the actual instruction size;
- supports call-site replacement/relocation rather than requiring a five-byte direct call;
- therefore supports this six-byte indirect call-site shape without hand-patching the `jb` at `+0x16E190`.

Do **not**:

- NOP or rewrite the conditional branch at `+0x16E190`;
- patch the threshold constant;
- globally hook `eCWrapper_emfx2Actor::GetPlayTime`;
- globally hook `GetMaxTime`;
- change the animation clock.

The intended call-hook shape is conceptually:

```cpp
static mCCallHook Hook_FistTimingGateGetPlayTime;

static GEDouble GE_STDCALL FistTimingGateGetPlayTime_FrameCollisionTest(
    gCScriptProcessingUnit *a_pSPU,
    eCWrapper_emfx2Actor *a_pAnimationActor,
    eCWrapper_emfx2Actor::eEMotionType a_MotionType);

Hook_FistTimingGateGetPlayTime
    .Prepare(RVA_Game(0x16E180),
             &FistTimingGateGetPlayTime_FrameCollisionTest)
    .AddRegArg(mERegisterType_Edi)
    .AddThisArg()
    .Hook();
```

The exact helper names are implementation detail, but the transport is frozen.

Important: **do not add motion type with `AddImmArg(0)`**. The native `push 0` is already the original call’s stack argument and must remain the third argument seen by the replacement function. Only the SPU/EDI and this/ECX are added ahead of it.

This hook exists only under `FRAME_COLLISION_DIAGNOSTICS`.

## One-shot arming responsibility

Arm the N6C override only from the first accepted exact-human-Fist `FIST` marker of a factual C1 generation.

Required arming conditions:

```text
actor != None
result.code == MarkerResult_Accepted
result.opcode == MarkerOpcode_Fist
result.fistSourceInstance != nullptr
result.fistSourceUseType == gEUseType_Fist / raw 8
result.c1GenerationValid == true
result.acceptedMarkerCountBefore == 0
result.acceptedMarkerCountAfter == 1
current SPU exists
current SPU+0x164 == 0
motion type 0 timing is available
real GetPlayTime(0) < computed native threshold
```

If any condition is false, do not arm and do not manufacture a causal test.

The arming observation should occur in `StartEffect_FrameCollisionTest` after `ProcessMarker(...)` and after the existing N6B read-only timing snapshot, but before the unchanged `ApplyAndLogFistCombatLatchRearmProbe(...)` write. The existing FIST latch-zero probe remains authoritative and unchanged.

Store only the bounded identity required to prevent leakage, including at least:

```text
armed flag
actor instance
SPU pointer
animation-actor pointer
C1 generation
current animation identity or equivalent exact execution identity
real play time at arm
max time / constant / threshold at arm
```

A single `thread_local` diagnostics probe state is appropriate. Do not create production state or modify C1/marker bookkeeping.

## Exact replacement-call behavior

Every invocation of the `Game + 0x16E180` call-site wrapper must first obtain the **real** current value through the public SDK:

```text
a_pAnimationActor->GetPlayTime(a_MotionType)
```

Calling the public method from inside this call-site hook is not a recursive call-site hook: N6C hooks only the specific Game.dll call site, not the Engine function globally.

### Unarmed or mismatched calls

Return the real `GetPlayTime` result unchanged for every call that is not the exact armed first-FIST execution.

Do not consume the arm for unrelated NPC/SPU/animation-actor calls.

### Matching armed call

Before applying the override, verify at minimum:

```text
a_pSPU == armed SPU
animation actor == armed animation actor
motion type == 0
current player/actor identity == armed actor
current C1 generation still equals armed generation
real current play time is still below the computed native threshold
```

If the generation is no longer current, clear the stale arm and return real play time.

If the matching call has already naturally reached/passed the threshold, do **not** fabricate an override; return the real value, log that the causal opportunity was missed/invalid, consume or expire the probe so the later second FIST is not affected, and let runtime interpretation stop on that invalid execution.

### Synthetic value

For the single valid matching call only, return a synthetic value that is clearly but minimally above the computed threshold while leaving the real animation state untouched.

Use:

```text
syntheticPlayTime = computedThreshold + 0.001 seconds
```

for the tested binary/fixture, provided it remains below/equal to max time. If a defensive clamp is required, clamp only to max time and log the factual returned value.

The override must be consumed exactly once. After returning the synthetic value, immediately mark the arm consumed/inactive so no later timing call—including the second FIST—receives a synthetic result.

Do not call `SetPlayTime`, alter max time, alter play speed, alter the native constant, or mutate animation motion ownership.

## Stale-arm retirement

The one-shot arm must never leak into the second FIST or a future execution.

Required retirement:

- if the matching override is consumed: clear/inactivate immediately;
- if the same-generation accepted `FIST_OFF` occurs while the arm is still pending: log expiration and clear it before the second FIST can use it;
- if C1 generation changes before consumption: clear stale state;
- if a new execution begins, do not carry old N6C state forward.

Do not change C1 itself to implement this retirement.

## Required N6C logging

Preserve all N6B timing-gate logging and existing latch/OnDamage logs.

Add clearly delimited causal-probe records sufficient to establish:

### ARM record

```text
Boundary: FIST_TIMING_GATE_CAUSAL_ARM
ElapsedMs
Actor / ActorAddress
CurrentMovementAni
C1Generation
SPUAddress
AnimationActorAddress
AcceptedFistOccurrenceBefore
AcceptedFistOccurrenceAfter
LatchAtArm
RealPlayTimeAtArm
MaxTimeAtArm
NativeThresholdConstant
ComputedThresholdAtArm
RealBelowThresholdAtArm
ArmAccepted
```

### OVERRIDE record

```text
Boundary: FIST_TIMING_GATE_CAUSAL_OVERRIDE
ElapsedMs
Actor / ActorAddress
C1Generation
HookSPUAddress
HookAnimationActorAddress
MotionType
RealPlayTime
MaxTime
NativeThresholdConstant
ComputedThreshold
RealBelowThreshold
SyntheticPlayTimeReturned
SyntheticAtOrAboveThreshold
OverrideApplied
OverrideOrdinalWithinGeneration
ArmConsumed
```

### EXPIRE/INVALID record when applicable

If an armed probe expires at FIST_OFF/generation change or cannot validly intervene because real time already crossed the threshold, log the factual reason. Do not silently carry or rearm it.

Do not add high-volume per-tick logging for unarmed calls.

## Existing logs that remain authoritative

Do not duplicate or replace:

```text
FIST_NATIVE_TIMING_GATE_PROBE
FIST_COMBAT_LATCH_REARM_PROBE
MarkerResult logging
ENTITY_ON_DAMAGE_ENTRY caller logging
FIST_OFF factual before/after latch transition
```

For the primary N6C endpoint, use the existing `FistOffLatchBefore` recorded by the FIST_OFF result/N6B timing block.

## Expected source scope

The intended implementation should remain bounded to diagnostics/hook transport, normally:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

Do **not** edit:

```text
FrameCollisionMarkers.cpp
CollisionSourceOperations.cpp
CollisionSources.cpp
CollisionLifecycleGuard.cpp
weapon marker adapters/source operations
C1 marker bookkeeping/lifecycle
```

If a purely diagnostic declaration/include requires another file, keep it minimal and report it explicitly. Do not broaden behavior.

## Protected behavior — MUST remain unchanged

N6C must not:

- change actual animation play time;
- change max time or play speed;
- patch the native threshold constant;
- patch/skip the native comparison branch globally;
- globally hook GetPlayTime/GetMaxTime;
- change the existing FIST latch-zero write;
- change FIST_OFF latch-one semantics;
- restore human-Fist OnAI_Attack suppression;
- restore Fist TouchDamage.ClearTriggeredList;
- add production FIST ON behavior;
- alter equipped-weapon callback suppression;
- alter RIGHT/LEFT/BOTH/OFF source operations;
- alter marker occurrence/dedupe/bookkeeping;
- alter marker-owned weapon windows;
- alter C1 generation/lifecycle/C1-R1 repair;
- broaden into interruption/lifecycle tests;
- broaden into raw55/PhysicalFist, monsters, or per-limb logic.

Outside the one armed exact-human-Fist first-FIST call, the call-site hook must be a factual pass-through returning the real play time.

## Source audit requirements

Before publication verify:

1. hook target is exactly `RVA_Game(0x16E180)`;
2. transport is diagnostics-only `mCCallHook`, not a branch/data patch or global function hook;
3. only SPU/EDI and this/ECX are added; native motion-type stack arg remains intact;
4. replacement return type is the factual SDK `GEDouble`;
5. unarmed/mismatched calls return public-SDK real play time;
6. exactly one first-FIST occurrence can arm per C1 generation;
7. override consumes exactly once and cannot reach second FIST;
8. pending state expires by FIST_OFF or generation change;
9. no SetPlayTime/max-time/play-speed/constant mutation exists;
10. existing FIST/FIST_OFF latch writes are byte-for-byte/semantically unchanged;
11. N6B logger remains before the existing FIST latch-rearm probe;
12. equipped weapons, marker bookkeeping and C1 are unchanged;
13. `git diff --check` passes.

If the SDK call hook cannot safely represent this six-byte indirect call site or the register facts differ from the tested binary, STOP and report the material contradiction instead of substituting a broader patch.

## Build execution

**BUILD EXECUTION: PROHIBITED** for this Work task unless the invoking prompt explicitly overrides this contract.

Perform source-level/API audit only. Do not run CMake, Visual Studio, compiler, game, deployment, or runtime test from Work.

Required handoff wording:

```text
Build: NOT ATTEMPTED — Work build execution was not authorized for this task.
```

## Publication

The invoking handoff explicitly authorizes publication of this bounded N6C implementation to:

```text
Repository: tcholti/Gothic3_Animation_Behaviors
Branch: docs/collision-source-evidence
```

Publish one conceptual implementation commit. Do not mix runtime evidence or broad documentation consolidation into it.

Report:

```text
final remote commit SHA
changed files
concise implementation result
build status
any material contradiction
```

Then STOP.

---

## Required controlled runtime fixture AFTER Work implementation

Use the same established fixture:

```text
same P0 Normal human raw-8 Fist animation
same Golem target/setup
frame 3  FIST
frame 9  FIST_OFF
frame 12 FIST
repeat enough executions to establish consistency
```

Record visual damage, but treat it as secondary:

```text
First punch damage:  YES / NO
Second punch damage: YES / NO
```

### N6C PASS pattern

Primary required evidence:

```text
first FIST real play time below threshold
first FIST latch rearm remains 0 -> 0
N6C arm accepted for first FIST
exactly one matching GetPlayTime override consumed
real GetPlayTime at override still below threshold
synthetic return at/above threshold
actual later animation timing remains natural/unmodified
frame-9 FIST_OFF: FistOffLatchBefore == 1
```

The changed `FistOffLatchBefore` from N6B baseline `0` to N6C `1` is the direct causal result: the native combat loop must have advanced through its own `Game + 0x16E1A3` latch write before FIST_OFF.

Protection/continuation evidence should also remain:

```text
FIST_OFF leaves/writes latch 1
second FIST remains a real, non-synthetic timing observation at/above threshold
second FIST rearm remains 1 -> 0
later damaging event, when contact permits, still uses Game.dll + 0x16E348
```

Early OnDamage before FIST_OFF:

```text
if observed from Game.dll + 0x16E348
    -> stronger evidence that timing-gate bypass released the full native
       damage opportunity while contact/target conditions were also satisfied

if not observed
    -> NOT an N6C failure by itself; downstream physical contact/target
       eligibility may simply not exist at frame 3
```

### N6C failure / stop conditions

```text
override consumed but FistOffLatchBefore remains 0
    -> timing comparison alone did not produce the expected native latch write
       or transport did not affect the intended comparison
    -> STOP and characterize; do not build production FIST ON

override never consumed before FIST_OFF
    -> execution is invalid for the causal question
    -> STOP and characterize hook/identity/timing mismatch

real timing had already crossed threshold before override
    -> causal opportunity invalid
    -> STOP/repeat controlled fixture; do not interpret as pass

second FIST accidentally receives synthetic timing
    -> probe leakage / invalid experiment
    -> STOP and fix probe containment before interpretation
```

---

## Direction after N6C

Only if N6C produces the direct native latch-write consequence while preserving real animation timing:

```text
N6C causal timing-gate PASS
-> timing gate is proven causally sufficient to advance the tested native arm
   from latch-zero eligibility into its own latch-write/damage-preparation path
-> then separately decide the smallest production-quality authored-FIST ON
   mechanism that releases native-equivalent timing without corrupting the
   animation clock or globally weakening native timing
```

Do not decide that final production mechanism inside N6C. In particular, N6C synthetic `GetPlayTime` return is a causal probe, not automatically the production design.

---

## Monsters remain future scope

Do not generalize this human architecture to `gEUseType_PhysicalFist` / raw 55 or monsters. Qualified armature observations for Golem/Dragon/Wolf/Boar remain future comparison only and do not prove engine damage routing or authorize a fallback algorithm.
