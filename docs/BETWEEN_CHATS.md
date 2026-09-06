# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N4 Fist callback-suppression necessity test frozen

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file for the exact current continuation.

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
Fist Stage A marker/source plumbing             CLOSED/PASS — EV-221, reinterpreted by EV-224
Fist Stage B DamageDisabled intervention        CLOSED/FAIL AS OFF MECHANISM — EV-223
Fist N2C native damage path                     CLOSED/PASS — EV-224
Fist N2D latch-1 suppression                    CLOSED/PASS — EV-225
Fist N2E fresh-move latch reset                 CLOSED/PASS — EV-226
Stage C production FIST_OFF                     CLOSED/PASS — EV-227
same-move pre-N3 timing evidence                RECORDED — EV-228–EV-230
N3 same-move latch-zero rearm                   CLOSED/PASS — CASE A — EV-231
N4 Fist callback-suppression necessity test     CURRENT/NEXT — FROZEN CAUSAL CLEANUP
```

Do not reopen these findings without concrete contradictory evidence.

---

## Architectural correction — shared infrastructure, separate mechanisms

Human Fist is not a source-adapter special case inside the equipped-weapon collision mechanism.

```text
Generic authored-marker infrastructure
        |
        +--> Equipped-weapon collision mechanism
        |       G3AB_COL_RIGHT / LEFT / BOTH / OFF
        |       equipped RIGHT/LEFT identities
        |       Item_Attack / Item_Equipped
        |       weapon ClearTriggeredList repeated contacts
        |       marker-owned source masks/windows
        |       weapon C1 lifecycle/cleanup
        |
        +--> Human Fist/body-damage mechanism
                G3AB_COL_FIST / FIST_OFF
                exact human gEUseType_Fist / raw 8
                sAICombatMoveItlLoop native timing/eligibility
                SPU+0x164 factual combat latch
                gCEntity::OnDamage dispatch

                no equipped weapon source masks
                no Item_Attack ownership assumption
                no weapon marker-owned window
                no weapon C1 lifecycle obligation
```

The mechanisms may share exact motion/frame-effect scanning, reserved-marker recognition, marker occurrence/dedupe bookkeeping, factual C1-generation execution identity, exact animation/action/phase context and the generic decision that a marked execution opts into custom timing.

After that generic layer, weapon and human-Fist native-mechanism code must remain separate. This is a design-for-separation rule, not a demand to invent a permanent module or restructure source before the native Fist mechanism is understood. The closed equipped-weapon architecture remains unchanged.

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

Current slot/source lookup does not prove that a literal right-hand slot owns physical Fist damage. Do not reopen per-limb semantics or generalize this fact to `gEUseType_PhysicalFist` / raw 55 or monsters.

---

## N3 runtime closure — CASE A

Diagnostic implementation:

```text
e7a690d2127aa8c63aef4dd9f48b386f2d4fdd49
Add N3 Fist latch rearm probe
```

Validated diagnostic DLL:

```text
SHA256 184488B4D5185EB78E3FD2B98882138D0FE5F5B88C73E67AD3883FA1811D2509
length 440832
```

Canonical raw:

```text
research/raw/2026-09-06_fist_on_off_on_test_2.log
evidence commit 84d50b504befba0b201b1ce5e05137474bf960cc
SHA256 73087DB3B1A168664F951CE3AAEA20BB126012342436CD1116105B876A3F6294
length 252409
```

Three controlled executions reproduced:

```text
first accepted FIST       latch 0 -> 0 confirmed
accepted FIST_OFF         latch 0 -> 1 confirmed
second accepted FIST      latch 1 -> 0 confirmed
after second FIST         Fist-correlated ENTITY_ON_DAMAGE_ENTRY
                          CallerModule Game.dll
                          CallerRVA 0x0016E348
                          target Golem
                          source exact raw-8 Fist
                          attacker PC_Hero

User repeated observation first-punch damage  NO
User repeated observation second-punch damage YES
```

First execution timing:

```text
first FIST    ElapsedMs 40658.667  StateTime 0.122941
FIST_OFF      ElapsedMs 40905.173  StateTime 0.368936
second FIST   ElapsedMs 41016.174  StateTime 0.480915
OnDamage      ElapsedMs 41027.431  CallerRVA 0x0016E348
```

Classification:

```text
CASE A — SAME-MOVE REARM PASS
```

For the tested human raw-8 P0 Normal native combat-loop path, explicitly writing `SPU+0x164` from 1 back to 0 after FIST_OFF causally rearms the confirmed `sAICombatMoveItlLoop -> gCEntity::OnDamage` path in the same move.

### Critical qualification

N3 does **not** prove that latch zero is a complete authored-frame FIST ON mechanism. The first FIST occurred while the latch was already zero and the first punch still produced no damage. The second FIST occurred later, after native hit timing/eligibility had advanced, and reopening the latch was followed approximately 11 ms later by native OnDamage.

Preserve the distinction:

```text
SPU+0x164
    permits/suppresses/rearms the confirmed native Fist dispatch

another unresolved native condition
    determines when the Fist damage opportunity becomes eligible
```

Do not promote the diagnostic FIST latch-zero write into complete production FIST semantics from N3 alone.

---

## Current native Fist path

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game + 0x16DD00

    native timing / eligibility logic
        UNKNOWN — central mechanism still to identify

    Game + 0x16DFB9
        cmp byte ptr [SPU+0x164], 0

    nonzero
        exits before damage

    once native hit opportunity is reached
        Game + 0x16E1A3
        mov byte ptr [SPU+0x164], 1

    later gCEntity::OnDamage
        observed caller return Game.dll + 0x16E348
```

N2D proves latch 1 suppresses this path, N2E proves fresh-move native reset to zero, and N3 proves same-move `1 -> 0` rearm after FIST_OFF. The byte's global meaning outside this tested human-Fist path remains unresolved.

---

## Native Item_Attack group-7 request — factual qualification

The exact raw-8 Fist entity has received native:

```text
eCEntity::SetCollisionGroup(eECollisionGroup_Item_Attack / 7)
```

requests, including observed attack-time requests around StateTime ~0.25. Its observable group remained:

```text
BeforeGroup: 0
AfterGroup:  0
```

`SetCollisionGroup` is void. `AfterGroup: 0` is not a return/error code and must not be described as the engine returning zero or formally rejecting the request. The proven fact is only that group 7 was requested on the exact Fist entity while its observable group remained zero after the call.

Do not infer whether this was rejection, intentional no-op, unsupported item-style state, transient/internal behavior or generic combat code irrelevant to actual Fist damage. It is not architectural evidence that human Fist belongs in the weapon `Item_Attack` mechanism.

---

## Current Fist operations — corrected target status

### Fist-specific OnAI_Attack suppression

Current marker ownership can suppress the original Normal `OnAI_Attack` callback. This is causally useful for established weapon marker paths. For human Fist, however, the tested damage route continues through:

```text
sAICombatMoveItlLoop
-> native timing/eligibility
-> SPU+0x164
-> gCEntity::OnDamage
```

Marked-Fist `OnAI_Attack` suppression did not suppress this actual tested timer/dispatch path. Fist-specific participation in weapon-style callback suppression is therefore provisional, is not a proven native Fist ownership mechanism and must not be treated as the final Fist suppression architecture. Do not delete it before the N4 causal test. Weapon marker callback suppression remains protected.

### Stage-A ClearTriggeredList scaffolding

The current production FIST operation performs exact raw-8 validation plus `TouchDamage.ClearTriggeredList()`. The operation was executed in Stage A, but its causal role in the confirmed native combat-loop Fist damage path remains unproven.

`ClearTriggeredList()` is **not** part of the intended final human-Fist marker architecture unless new direct evidence separately proves it necessary. Do not claim it is globally useless or irrelevant to other TouchDamage paths. Do not combine its eventual source removal with an unrelated timing/suppression experiment unless a later frozen task explicitly authorizes that combination.

---

## Exact next responsibility — N4 FIST callback-suppression necessity test

### Frozen question

```text
If exact-human-Fist marker ownership stops suppressing the original
OnAI_Attack callback while all Fist marker/latch behavior and the controlled
N3 fixture remain otherwise unchanged, does the tested Fist behavior/path
remain unchanged?
```

Purpose: determine whether the existing Fist-specific callback suppression can be safely retired as unnecessary/wrong-layer behavior.

This is a planning freeze only. Do not implement N4 until a separate bounded task authorizes it. That implementation must leave equipped-weapon marker callback suppression untouched and preserve every other Fist variable so the test remains causal.

---

## Direction after bounded causal cleanup

After obsolete Fist callback suppression and Stage-A scaffolding are handled through separately frozen causal cleanup, investigate:

```text
What native Fist timing/eligibility mechanism inside
gCScriptProcessingUnit::sAICombatMoveItlLoop prevents damage at the first
authored FIST marker even though SPU+0x164 is already 0?
```

Intended final authored-Fist principle:

```text
resolve exact Hit animation and inspect reserved Fist markers

no Fist markers
    preserve native Fist behavior

Fist markers present
    suppress the actual native Fist timing/dispatch mechanism
    not weapon Item_Attack machinery

G3AB_COL_FIST
    create/release native-equivalent damage opportunity at authored frame

G3AB_COL_FIST_OFF
    suppress further Fist damage opportunity

native unmarked timing must not leak through marker-owned Fist execution
```

Do not yet decide whether the final FIST mechanism mutates a native timing field, calls a native function, releases eligibility, invokes lower-level damage or uses another mechanism. That decision requires direct evidence from the native path.

---

## Monsters remain future scope

Do not generalize this human architecture to `gEUseType_PhysicalFist` / raw 55 or monsters.

Qualified User armature observations for future comparison only:

```text
Golem   right/left weapon-slot bones very near head
Dragon  right/left weapon-slot bones on head
Wolf    no weapon-slot bones found
Boar    no weapon-slot bones found
```

These observations do not prove engine damage routing and do not authorize a monster fallback algorithm.

---

## Explicitly unresolved / out of scope

- production FIST latch-zero semantics merely from N3;
- the native timing/eligibility owner inside `sAICombatMoveItlLoop`;
- removal of Fist-specific `OnAI_Attack` suppression before N4;
- source removal of Stage-A `ClearTriggeredList()` in this documentation task;
- global meaning of `SPU+0x164` outside the tested human-Fist path;
- whether `ClearTriggeredList()` matters on other TouchDamage paths;
- manual latch restoration or persistent Fist lifecycle state;
- `gEUseType_PhysicalFist` / raw 55 and monsters/generalized body collision;
- per-limb Fist semantics;
- equipped-weapon RIGHT/LEFT/BOTH/OFF semantics and C1 lifecycle;
- marker-generation bookkeeping, unrelated collision families, Raise or playback-speed work.

Evidence authority: EV-224–EV-231 in `docs/EVIDENCE_LEDGER_199_ONWARD.md`.
