# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-04

## Current bridge — HackAttack isolated marker / optional routing validation

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap. If the previous Chat failed or hit maximum context, use POP-11 before trusting stale `NEXT` wording.

CAM is the constitutional collaboration layer; `docs/README.md` is the highest Gothic-specific project charter beneath CAM. Do not modify CAM from Gothic 3 work.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Hack callback runtime identity                  CLOSED — EV-216
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
```

Do not reopen C1 lifecycle/generation architecture, Power, Pierce, or the proven SimpleWhirl physical source layer without concrete contradicting evidence.

SimpleWhirl closure checkpoint:

`research/derived/2026-09-04_simplewhirl_stateposition_and_target_semantics_closure.md`

Accepted SimpleWhirl result:

```text
physical RIGHT / LEFT / BOTH / OFF marker-source control works
both swords can connect against the selected target
native actor-hit eligibility remains substantially target-directed
strict selected-target-only is false
StatePosition 2 did not make the action Power-like
native SimpleWhirl StatePosition 1 is restored
```

The observed nearby/intervening-secondary-target pattern is deliberately qualified in the closure checkpoint; it is not a proven cone/corridor/native algorithm.

---

## Hack implementation baseline

Remaining-melee implementation:

`f0d929c90fbe086f44f66f91a2523904d06c3903`

Generic marker StatePosition diagnostics:

`7c31784c5ef86bc79b54d573144b8e40f33e5e6b`

EV-216 tested callback identity:

```text
Script_Game +0x433D0
= OnAI_HackAttack
= .\Script\AI\AI_Commands\AI_HackAttack.cpp
```

Hack marker bookkeeping currently implemented:

```text
Hack -> StatePosition 1
```

`GetUpAttack` is not part of the planned marker roadmap. True runtime `FinishingAttack` action 15 remains deliberately native/unmarked. Fist/body remains a separate later source-adapter responsibility.

---

## Optional Hack animation-routing contract

Known runtime distinction:

```text
gEAction_HackAttack      = 14
gEAction_FinishingAttack = 15
```

Implemented routing:

```text
active native/installed resolver produces the ordinary resource name
-> CombatMove factual action is read from the existing SPU context
-> at the narrow CombatMove motion-resource query callsite:

   if factual action == HackAttack (14)
   and the resource name contains the exact _FinishingAttack_ token:
       derive one candidate by replacing only
       _FinishingAttack_ -> _HackAttack_

       candidate exists:
           use the candidate resource

       candidate absent:
           use the untouched original FinishingAttack resource

-> any non-Hack action, including true FinishingAttack (15):
   untouched native path
```

Dedicated Hack assets are optional overrides, not a dependency.

Preserve the namespace produced by Gothic or another active resolver such as Jackydima `Script_Animation`. Do not normalize `Axe`, `2H`, Staff or other namespaces into G3AB guesses, and do not globally replace `GetAniName` or action-string-table ownership.

---

## Preferred authored Hack fixtures

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_2H_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot

Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

`100` is animation-author metadata, not a DLL constant.

---

## Exact next responsibility

Validate Hack independently before the combined remaining-melee regression.

Minimum causal sequence:

```text
1. fallback control
   Action 14 / OnAI_HackAttack
   no matching dedicated _HackAttack_ asset
   -> untouched FinishingAttack resource remains usable
   -> no routing failure/crash

2. dedicated Hack positive
   matching _HackAttack_ fixture exists
   -> Action remains HackAttack
   -> dedicated Hack resource is selected
   -> reserved marker in the exact Hack Hit is owned as Family HACK
   -> accepted source marker leaves StatePosition 1
   -> exact equipped source activation/rearm/cleanup behaves normally

3. true FinishingAttack negative
   Action 15
   -> no Hack routing
   -> native/unmarked path remains intact
```

Keep the first positive fixture narrow. Do not broaden into every weapon type or compatibility stack before the basic routing + marker ownership result is known.

After Hack closes:

```text
combined remaining-melee marker/lifecycle regression
```

Fist/body source adaptation and AttackContinuationProtection remain separate later responsibilities.
