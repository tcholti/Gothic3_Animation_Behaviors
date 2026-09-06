# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N6A static timing trace CLOSED; N6B runtime timing-gate observability NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file for the exact current continuation. Where older durable wording still names N4 or N6A as current, this bridge is the authoritative transient continuation until the next documentation consolidation.

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
N6B native timing-gate runtime observability     CURRENT/NEXT — FROZEN
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

---

## Protected human body-contact fact

Exact logical human `gEUseType_Fist` / raw 8 is a body-contact source, not literal right-hand weapon collision. Controlled tests established damaging contact through at least left hand, right hand, left leg, right leg and head. Do not generalize this to `gEUseType_PhysicalFist` / raw 55 or monsters.

---

## N4/N5 causal cleanup closure

N4 implementation/evidence:

```text
fdec0ce431e555d469597a5684ef2e9dd8d5aeaf  Add N4 Fist callback pass-through probe
research/raw/2026-09-06_fist_n4_callback_passthrough.log
7ffba2ae129cd31f17c26274b8cee10f1128ba60  evidence commit
```

N4 reproduced the N3 latch sequence and native `Game.dll + 0x0016E348` OnDamage path with `SuppressNativeCallback = 0`; User repeatedly observed first punch NO, second punch YES. Therefore human Fist does not require weapon-style `OnAI_Attack` suppression. Equipped-weapon callback suppression remains protected.

N5 implementation/evidence:

```text
082029d86b900b647d3f8c157615a958bdbfd269  Add N5 Fist triggered-list necessity probe
research/raw/2026-09-06_fist_n5_no_triggered_list_clear.log
9ddece8698f2067927739d0c002ef114dab1fa33  evidence commit
```

N5 reproduced the same latch sequence and native OnDamage path with every accepted FIST showing `TriggeredListClearCount = 0` / `FistTriggeredListCleared = 0`; User repeatedly observed first punch NO, second punch YES. Therefore Stage-A Fist `TouchDamage.ClearTriggeredList()` is not required for the tested human raw-8 combat-loop path. This does not weaken proven weapon repeated-contact ClearTriggeredList semantics or claim global uselessness on other TouchDamage paths.

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

Protected latch interpretation remains:

```text
SPU+0x164 = 1
    suppresses the confirmed tested dispatch path

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

Static facts for the damage-producing arm selected after the known latch check:

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

The Engine import table maps the adjacent IAT entries exactly:

```text
Game IAT 0x1024C5F8 -> eCWrapper_emfx2Actor::GetPlayTime
Game IAT 0x1024C5FC -> eCWrapper_emfx2Actor::GetMaxTime
```

N6A therefore isolated one sufficiently narrow native timing candidate: **motion-0 play time crossing a native fraction of motion-0 max time**. This is a factual static control-flow result, not yet runtime proof that this compare is what distinguishes the first authored FIST from the later damaging opportunity in the controlled fixture.

Do not yet infer the semantic meaning/value of the native double at RVA `0x308308` beyond its factual role in this threshold expression.

The function contains other selector/entity/target checks and a separate special arm when `[SPU+0x154] == 0x39`; N6A does not generalize those paths. The current runtime question remains intentionally limited to the already-traced tested human-Fist arm containing the established `+0x16DFB9` latch check and `+0x16E348` OnDamage caller.

---

## Exact next responsibility — N6B timing-gate runtime observability probe

### Frozen question

```text
In the same controlled frame-3 FIST / frame-9 FIST_OFF / frame-12 FIST
human raw-8 P0 Normal fixture, is the first authored FIST still below the
native motion-time threshold while the later second FIST has reached or
passed it before the confirmed Game.dll + 0x16E348 OnDamage event?
```

### Change only diagnostics

At accepted FIST/FIST_OFF marker observations for the exact tested human-Fist execution, record the native timing-gate inputs without mutating them:

```text
motion type                       0
GetMaxTime(0)                     factual returned value
GetPlayTime(0)                    factual returned value
native threshold constant         qword at Game.dll RVA 0x308308
computed threshold                GetMaxTime * native constant
comparison                        GetPlayTime < threshold OR >= threshold
existing SPU+0x164 latch          before/after marker operation
C1 generation / StateTime         existing execution correlation
```

Preserve existing `ENTITY_ON_DAMAGE_ENTRY` caller logging so event ordering remains comparable.

### Required controlled fixture

```text
same P0 Normal human raw-8 Fist animation
same Golem target/setup
frame 3  FIST
frame 9  FIST_OFF
frame 12 FIST
repeat enough executions to establish consistency
```

### N6B interpretation

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

### Protected behavior / exclusions

N6B is **observability only**. Do not:

- change GetPlayTime, GetMaxTime or the native threshold constant;
- force the timing comparison outcome;
- add production FIST ON semantics;
- change FIST latch-zero or FIST_OFF latch-one behavior;
- restore Fist OnAI_Attack suppression;
- restore Fist ClearTriggeredList;
- alter equipped-weapon callback suppression/source operations;
- alter C1 lifecycle/bookkeeping;
- broaden into interruption/lifecycle testing;
- broaden into raw55/PhysicalFist, monsters or per-limb logic.

---

## Direction after N6B

Only if N6B positively correlates the isolated threshold with the early/later difference:

```text
freeze one causal timing intervention
-> change only that proven native timing condition
-> test whether authored FIST can create the native-equivalent damage opportunity
```

Do not yet decide whether the final implementation should mutate play time, call a native function, alter a threshold/eligibility decision, or use another lower-level mechanism. That decision requires the causal result first.

---

## Monsters remain future scope

Do not generalize this human architecture to `gEUseType_PhysicalFist` / raw 55 or monsters. Qualified armature observations for Golem/Dragon/Wolf/Boar remain future comparison only and do not prove engine damage routing or authorize a fallback algorithm.
