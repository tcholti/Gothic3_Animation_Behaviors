# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N6A static timing trace CLOSED; N6B runtime timing-gate observability IMPLEMENTATION FROZEN

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
N6B native timing-gate runtime observability     CURRENT — IMPLEMENTATION CONTRACT FROZEN
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

## N4/N5 causal cleanup closure

N4:

```text
fdec0ce431e555d469597a5684ef2e9dd8d5aeaf  Add N4 Fist callback pass-through probe
research/raw/2026-09-06_fist_n4_callback_passthrough.log
7ffba2ae129cd31f17c26274b8cee10f1128ba60  evidence commit
```

Result: same N3 latch sequence and native `Game.dll + 0x0016E348` OnDamage path with `SuppressNativeCallback = 0`; repeated visual result first punch NO, second punch YES. Human Fist therefore does not require weapon-style `OnAI_Attack` suppression. Equipped-weapon callback suppression remains protected.

N5:

```text
082029d86b900b647d3f8c157615a958bdbfd269  Add N5 Fist triggered-list necessity probe
research/raw/2026-09-06_fist_n5_no_triggered_list_clear.log
9ddece8698f2067927739d0c002ef114dab1fa33  evidence commit
```

Result: same latch sequence and native OnDamage path with every accepted FIST showing `TriggeredListClearCount = 0` / `FistTriggeredListCleared = 0`; repeated visual result first punch NO, second punch YES. Stage-A Fist `TouchDamage.ClearTriggeredList()` is not required for the tested human raw-8 combat-loop path. This does not weaken weapon repeated-contact ClearTriggeredList semantics or claim global uselessness on other TouchDamage paths.

---

## Confirmed native human-Fist path

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game.dll + 0x16DD00

    generic tested arm
    Game.dll + 0x16DFB9
        cmp byte ptr [SPU+0x164], 0
        nonzero -> exit before damage

    timing gate isolated by N6A
        GetMaxTime(motion type 0)
        * native double constant at Game.dll RVA 0x308308
        compared with GetPlayTime(motion type 0)

        GetPlayTime < threshold
            -> jump to common exit Game.dll + 0x16E352

        GetPlayTime >= threshold
            -> continue into native damage preparation
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

## N6A closure — native timing gate isolated statically

Binary authority:

```text
Repository: tcholti/Gothic3_Binary_Reference
builds/current_tested/modules/Game/disassembly/part_0093.txt
builds/current_tested/modules/Game/disassembly/part_0094.txt
builds/current_tested/modules/Game/imports.txt
```

Static facts:

```text
Game + 0x16E14F
    required native selector/motion match; failure -> common exit

Game + 0x16E160
    push motion type 0
    call Engine import eCWrapper_emfx2Actor::GetMaxTime

Game + 0x16E16E..0x16E17C
    GetMaxTime result * qword [Game + 0x308308]
    store native timing threshold

Game + 0x16E180
    call Engine import eCWrapper_emfx2Actor::GetPlayTime for motion type 0

Game + 0x16E186..0x16E190
    compare GetPlayTime against threshold
    GetPlayTime < threshold -> jb Game + 0x16E352 common exit

Game + 0x16E196..0x16E1A3
    passing threshold continues directly into damage preparation
    Game + 0x16E1A3 writes SPU+0x164 = 1
```

Engine import mapping:

```text
Game IAT 0x1024C5F8 -> eCWrapper_emfx2Actor::GetPlayTime
Game IAT 0x1024C5FC -> eCWrapper_emfx2Actor::GetMaxTime
```

N6A isolated one sufficiently narrow factual candidate: **motion-0 play time crossing a native fraction of motion-0 max time**. It does not yet prove that this comparison distinguishes the early first FIST from the later damaging opportunity in the controlled fixture. Do not infer the semantic meaning/value of the native double at RVA `0x308308` beyond its factual role in the threshold expression.

The function also contains other selector/entity/target checks and a separate special arm when `[SPU+0x154] == 0x39`; N6B does not generalize those paths.

---

# N6B FULL WORK IMPLEMENTATION CONTRACT

## Frozen research question

```text
In the same controlled frame-3 FIST / frame-9 FIST_OFF / frame-12 FIST
human raw-8 P0 Normal fixture, is the first authored FIST still below the
native motion-time threshold while the later second FIST has reached or
passed it before the confirmed Game.dll + 0x16E348 OnDamage event?
```

N6B is **runtime observability only**. It must not alter the native timing condition or any production collision/body-damage behavior.

## Required base state

Work must begin from the exact branch HEAD that contains this contract. The invoking handoff supplies that SHA. If remote HEAD differs, STOP and report the mismatch rather than rebasing or broadening.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`

Then inspect only the source/API material needed for this responsibility.

## Expected source scope

The intended implementation should require only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

Do **not** edit `FrameCollisionMarkers.cpp`, `CollisionSourceOperations.cpp`, `CollisionSources.cpp`, `CollisionLifecycleGuard.cpp`, C1 logic, marker ownership logic, or equipped-weapon behavior for N6B.

If a compile-time include/API requirement forces another purely diagnostic file change, keep it minimal and report it explicitly. Do not use that as permission to alter behavior.

## Existing source/API facts to reuse

Do not rediscover or replace these mechanisms:

- `CollisionDiagnosticsDeep.cpp` already demonstrates the correct public SDK route from `Entity` to `eCVisualAnimation_PS`, then `GetActor()`, then motion type `0`, `HasMotionInstance()`, `GetPlayTime()`, and `GetMaxTime()`.
- N6B belongs in normal `FRAME_COLLISION_DIAGNOSTICS`, not `FRAME_COLLISION_DIAGNOSTICS_DEEP`; do not make the test depend on deep diagnostics.
- `EngineBridge.cpp::StartEffect_FrameCollisionTest` already calls `FrameCollisionMarkers::ProcessMarker(...)`, then existing diagnostics, including `ApplyAndLogFistCombatLatchRearmProbe(actor, result)`, and finally `LogMarkerResult(actor, result)`.
- `ApplyAndLogFistCombatLatchRearmProbe(...)` is the established N3/N4/N5 FIST latch-zero diagnostic and must remain behaviorally unchanged.
- FIST_OFF latch-one behavior is already performed inside `ProcessMarker(...)` and recorded in `MarkerProcessResult::fistOffLatchBefore/fistOffLatchAfter`.
- `LogEntityOnDamageEntry(...)` already records caller module/RVA and must remain unchanged so `Game.dll + 0x0016E348` ordering stays comparable.

## Exact N6B implementation responsibility

Add one bounded diagnostic snapshot for accepted exact-human-Fist `FIST` and `FIST_OFF` markers.

A suitable interface is conceptually:

```cpp
void LogFistNativeTimingGateProbe(
    Entity &actor, MarkerProcessResult const &result);
```

The exact private helper names are implementation detail, but the observable behavior below is frozen.

### Eligibility filter

The new diagnostic must do nothing unless all of these are true:

```text
actor != None
result is an accepted marker result relevant to the authored Fist path
opcode is FIST or FIST_OFF
resolved Fist source exists
resolved Fist UseType == gEUseType_Fist / raw 8
```

For FIST, the accepted result is `MarkerResult_Accepted`.
For FIST_OFF, use the actual accepted result code already produced by the current implementation; do not weaken marker validation just to make logging fire.

Do not log raw55/PhysicalFist or monster paths as if they were covered by this experiment.

### Animation API observation

Use the public SDK animation path, equivalent to the already-proven deep-diagnostic helper:

```text
actor.Animation.IsValid()
-> eCVisualAnimation_PS
-> HasActor()
-> GetActor()
-> motion type 0
-> HasMotionInstance(0)
-> GetPlayTime(0)
-> GetMaxTime(0)
```

Do **not** hook `GetPlayTime` or `GetMaxTime`.
Do **not** call those functions by raw Game/Engine addresses.
Do **not** change play time, max time, play speed, motion state, or motion ownership.

### Native constant observation

Resolve the loaded `Game.dll` module at runtime and read the proven double at:

```text
Game.dll module base + RVA 0x00308308
```

Requirements:

- read only;
- use module-base + RVA so ASLR is respected;
- interpret the qword as the same native double used by the N6A disassembly;
- do not patch or temporarily modify it;
- if `Game.dll` cannot be resolved, log that the constant is unavailable rather than guessing a value.

### Derived values

When the required inputs are available, compute diagnostically only:

```text
threshold = GetMaxTime(0) * nativeConstant
belowThreshold = GetPlayTime(0) < threshold
atOrAboveThreshold = !belowThreshold
```

Use double precision consistent with the native threshold expression. Do not round before comparing.

### Required log payload

Emit one clearly delimited N6B block per accepted FIST/FIST_OFF observation, containing at minimum:

```text
Boundary: FIST_NATIVE_TIMING_GATE_PROBE
ElapsedMs
Actor / ActorAddress
MarkerOpcode / MarkerName
Action
AniPhase
StateTime
CurrentMovementAni
C1Generation
FistSourceAddress
FistUseType
MotionType: 0
AnimationPSResolved
AnimationActorResolved
PrimaryHasMotionInstance
PrimaryPlayTime
PrimaryMaxTime
GameModuleResolved
NativeThresholdConstantRVA: 0x00308308
NativeThresholdConstantAvailable
NativeThresholdConstant
ComputedThreshold
BelowThreshold
AtOrAboveThreshold
CurrentSPUAddress
CurrentLatchOffset: 0x164
CurrentLatchValue
```

For FIST_OFF also include the already-recorded factual transition from the result:

```text
FistOffLatchBefore
FistOffLatchAfter
FistOffLatchWriteConfirmed
```

For FIST, do not invent a duplicate latch transition inside the timing-gate logger. The existing immediately following `FIST_COMBAT_LATCH_REARM_PROBE` remains the authoritative before/after record of the N3 latch-zero write.

Unavailable values must be logged explicitly with availability flags/sentinel values rather than dereferencing null pointers or manufacturing data.

## Required call ordering

In `StartEffect_FrameCollisionTest`, after:

```text
FrameCollisionMarkers::ProcessMarker(...)
```

and **before**:

```text
CollisionDiagnostics::ApplyAndLogFistCombatLatchRearmProbe(actor, result)
```

call the new N6B timing-gate logger.

This ordering is important:

- accepted FIST is observed before the existing N3 latch-zero diagnostic mutation;
- accepted FIST_OFF has already executed its existing marker-owned latch-one operation inside `ProcessMarker`, while its `result` still contains the factual before/after transition;
- timing inputs themselves remain read-only;
- the existing latch rearm probe, marker-result log, and OnDamage caller log keep their current ordering/semantics.

Do not move existing diagnostics merely for prettier log grouping.

## Protected behavior — MUST remain unchanged

N6B must not:

- change `GetPlayTime`, `GetMaxTime`, play speed, or the native threshold constant;
- force or bypass the native `GetPlayTime < threshold` comparison;
- add a production FIST ON mechanism;
- change the existing FIST latch-zero write;
- change FIST_OFF latch-one semantics;
- restore human-Fist `OnAI_Attack` suppression;
- restore Fist `TouchDamage.ClearTriggeredList()`;
- alter equipped-weapon callback suppression;
- alter RIGHT/LEFT/BOTH/OFF source operations;
- alter marker occurrence/dedupe/bookkeeping;
- alter marker-owned weapon windows;
- alter C1 generation/lifecycle/C1-R1 repair;
- add new native hooks for the timing functions;
- broaden into interruption/lifecycle testing;
- broaden into raw55/PhysicalFist, monsters, or per-limb logic.

No production behavior should differ between an N6B diagnostic build and the current pre-N6B source except for additional logging/read-only observations.

## Source audit requirements

Before publication, verify:

1. only the bounded diagnostic files changed, except a separately reported unavoidable diagnostic include/API adjustment;
2. no mutation exists for play time, max time, threshold constant, animation state, or new Fist state;
3. existing FIST latch-zero code is unchanged;
4. existing FIST_OFF latch-one code is unchanged;
5. equipped-weapon suppression/source operations are unchanged;
6. C1 and marker bookkeeping are unchanged;
7. the new logger is called after `ProcessMarker` and before `ApplyAndLogFistCombatLatchRearmProbe`;
8. no new timing-function hook was added.

## Build execution

**BUILD EXECUTION: PROHIBITED** for this Work task unless the invoking prompt explicitly overrides this contract.

Perform source-level/API audit only. Do not run CMake, Visual Studio, compiler, game, deployment, or runtime test from Work.

Required handoff wording:

```text
Build: NOT ATTEMPTED — Work build execution was not authorized for this task.
```

## Publication

The invoking handoff explicitly authorizes publication of this bounded N6B implementation to:

```text
Repository: tcholti/Gothic3_Animation_Behaviors
Branch: docs/collision-source-evidence
```

Publish one conceptual implementation commit. Do not append unrelated documentation consolidation or runtime interpretation to that commit.

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

Runtime testing happens later, outside Work, using the same established fixture:

```text
same P0 Normal human raw-8 Fist animation
same Golem target/setup
frame 3  FIST
frame 9  FIST_OFF
frame 12 FIST
repeat enough executions to establish consistency
```

The expected N6B factual comparison is:

```text
first FIST consistently below threshold
+ second FIST consistently at/above threshold
+ later OnDamage still from Game.dll + 0x16E348
    -> runtime supports the isolated motion-time threshold as the missing
       eligibility condition separating early FIST from later opportunity
    -> freeze a later one-variable causal intervention; do not mutate yet

comparison does not distinguish early vs later state
    -> N6A static gate is real but does not explain the observed authored-FIST
       timing difference by itself
    -> STOP and reassess the next native condition rather than mutating it
```

Visual damage remains a secondary confirmation:

```text
first punch damage  NO
second punch damage YES
```

Do not require the exact historical millisecond delay between the second FIST and OnDamage; require correct causal ordering and the same native caller/path.

---

## Direction after N6B

Only if N6B positively correlates the isolated threshold with the early/later difference:

```text
freeze one causal timing intervention
-> change only that proven native timing condition
-> test whether authored FIST can create the native-equivalent damage opportunity
```

Do not yet decide whether the final implementation should mutate play time, call a native function, alter a threshold/eligibility decision, or use another lower-level mechanism. That decision requires the N6B runtime result first.

---

## Monsters remain future scope

Do not generalize this human architecture to `gEUseType_PhysicalFist` / raw 55 or monsters. Qualified armature observations for Golem/Dragon/Wolf/Boar remain future comparison only and do not prove engine damage routing or authorize a fallback algorithm.
