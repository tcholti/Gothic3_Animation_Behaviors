# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — human Fist N4/N5 causal cleanup CLOSED; N6A native timing/eligibility trace NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file for the exact current continuation. Where older durable wording still names N4 as current, this bridge is the authoritative transient continuation until the next documentation consolidation.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
equipped-weapon RIGHT/LEFT/BOTH/OFF architecture CLOSED/UNCHANGED
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
Fist body-contact semantics                     CLOSED/PASS — EV-029, EV-080–EV-084
Fist Stage A marker/source plumbing             CLOSED/PASS — causal ON interpretation superseded
Fist Stage B DamageDisabled intervention        CLOSED/FAIL AS OFF MECHANISM
Fist N2C native damage path                     CLOSED/PASS
Fist N2D latch-1 suppression                    CLOSED/PASS
Fist N2E fresh-move latch reset                 CLOSED/PASS
Stage C production FIST_OFF                     CLOSED/PASS
N3 same-move latch-zero rearm                   CLOSED/PASS — CASE A — EV-231
N4 Fist OnAI_Attack suppression necessity       CLOSED/PASS
N5 Fist TouchDamage.ClearTriggeredList necessity CLOSED/PASS
N6A native Fist timing/eligibility trace        CURRENT/NEXT — FROZEN RESEARCH RESPONSIBILITY
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

Exact logical human `gEUseType_Fist` / raw 8 is a body-contact source, not literal right-hand weapon collision. Controlled tests established damaging contact through at least:

```text
left hand
right hand
left leg
right leg
head
```

Do not generalize this to `gEUseType_PhysicalFist` / raw 55 or monsters.

---

## Confirmed native human-Fist path

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game.dll + 0x16DD00

    native timing / eligibility
        UNKNOWN — next research target

    Game.dll + 0x16DFB9
        cmp byte ptr [SPU+0x164], 0

    nonzero
        exits before damage

    once native hit opportunity is reached
        Game.dll + 0x16E1A3
        mov byte ptr [SPU+0x164], 1

    later gCEntity::OnDamage
        observed caller return Game.dll + 0x16E348
```

Protected interpretation:

```text
SPU+0x164 = 1
    suppresses the confirmed tested dispatch path

fresh combat move
    naturally restores the tested latch to 0

same-move explicit 1 -> 0
    causally rearms the confirmed dispatch after FIST_OFF

latch 0 by itself
    is NOT a complete authored FIST ON mechanism
```

The first authored FIST can occur while the latch is already 0 and still produce no damage. A later FIST after native timing/eligibility has advanced can rearm the path and be followed by OnDamage.

---

## N4 closure — OnAI_Attack suppression NOT required for human Fist

Implementation:

```text
fdec0ce431e555d469597a5684ef2e9dd8d5aeaf
Add N4 Fist callback pass-through probe
```

Canonical raw evidence:

```text
research/raw/2026-09-06_fist_n4_callback_passthrough.log
evidence commit 7ffba2ae129cd31f17c26274b8cee10f1128ba60
```

Controlled result across repeated executions:

```text
marked human Fist ownership     SuppressNativeCallback = 0
original OnAI_Attack            BEFORE_ORIGINAL + AFTER_ORIGINAL observed
first FIST                      latch 0 -> 0
FIST_OFF                        latch 0 -> 1
second FIST                     latch 1 -> 0
native damage caller            Game.dll + 0x0016E348
visual first punch damage       NO
visual second punch damage      YES
```

Conclusion:

> Human-Fist marker ownership does not require weapon-style `OnAI_Attack` suppression for the tested native body-damage path. Equipped-weapon callback suppression remains protected and unchanged.

---

## N5 closure — Fist TouchDamage.ClearTriggeredList NOT required

Implementation:

```text
082029d86b900b647d3f8c157615a958bdbfd269
Add N5 Fist triggered-list necessity probe
```

Canonical raw evidence:

```text
research/raw/2026-09-06_fist_n5_no_triggered_list_clear.log
evidence commit 9ddece8698f2067927739d0c002ef114dab1fa33
```

Controlled result across repeated executions:

```text
accepted FIST                    TriggeredListClearCount = 0
accepted FIST                    FistTriggeredListCleared = 0
first FIST                       latch 0 -> 0
FIST_OFF                         latch 0 -> 1
second FIST                      latch 1 -> 0
native damage caller             Game.dll + 0x0016E348
visual first punch damage        NO
visual second punch damage       YES
```

Conclusion:

> The historical Stage-A Fist `TouchDamage.ClearTriggeredList()` operation is not required for the tested human raw-8 `sAICombatMoveItlLoop -> gCEntity::OnDamage` path. This conclusion is Fist-path-specific and does not weaken proven weapon repeated-contact ClearTriggeredList semantics or claim the operation is globally useless on other TouchDamage paths.

---

## Exact next responsibility — N6A native timing/eligibility static control-flow trace

### Frozen question

```text
Inside the tested human-Fist sAICombatMoveItlLoop path, what factual native
control-flow condition(s) must become eligible before the already-zero
SPU+0x164 latch can reach the later latch-write / gCEntity::OnDamage path?
```

### N6A responsibility

Trace only the tested binary control flow around:

```text
sAICombatMoveItlLoop entry       Game.dll + 0x16DD00
known latch compare              Game.dll + 0x16DFB9
known native latch write         Game.dll + 0x16E1A3
known OnDamage caller return     Game.dll + 0x16E348
```

Identify the smallest factual timing/eligibility branch, field, compare, or call that distinguishes the early first-FIST state from the later damaging opportunity strongly enough to justify one subsequent runtime probe.

### Protected behavior / exclusions

N6A is **static/research only**. Do not yet:

- mutate timing or eligibility state;
- add a production FIST ON mechanism;
- change the accepted FIST latch-zero write;
- change FIST_OFF latch-one semantics;
- restore OnAI_Attack suppression;
- restore Fist ClearTriggeredList;
- alter equipped-weapon callback suppression or weapon source operations;
- alter C1 lifecycle/bookkeeping;
- broaden into interruption/lifecycle testing;
- broaden into raw55/PhysicalFist, monsters or per-limb logic.

If the static trace exposes several plausible independent eligibility gates and cannot isolate one bounded runtime question, STOP and report that contradiction instead of instrumenting all of them.

---

## Direction after N6A

Only after N6A identifies one sufficiently narrow factual candidate:

```text
freeze one runtime observability probe
→ observe early first-FIST state vs later damaging state
→ no mutation unless a later separately frozen causal task authorizes it
```

The intended final authored-Fist principle remains:

```text
no Fist markers
    preserve native Fist behavior

Fist markers present
    suppress/control the actual native Fist timing/dispatch mechanism
    not equipped-weapon Item_Attack machinery

FIST
    create/release native-equivalent damage opportunity at authored frame

FIST_OFF
    suppress further damage opportunity
```

Do not yet decide whether final FIST semantics use a native timing field, a function call, eligibility release, lower-level damage dispatch, or another mechanism.

---

## Monsters remain future scope

Do not generalize this human architecture to `gEUseType_PhysicalFist` / raw 55 or monsters.

Qualified User armature observations remain future comparison only:

```text
Golem   right/left weapon-slot bones very near head
Dragon  right/left weapon-slot bones on head
Wolf    no weapon-slot bones found
Boar    no weapon-slot bones found
```

These observations do not prove engine damage routing or authorize a monster fallback algorithm.
