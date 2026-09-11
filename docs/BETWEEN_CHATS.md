# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — NATIVE NPC TRIO CLOSED; ORC MULTI-WEAPON EXTENSION NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_TEST_PLAN.md §8
4. EVIDENCE_LEDGER_250_ONWARD.md
5. WORK_IMPLEMENTATION_PROTOCOL.md only if a later bounded code task is frozen
```

---

## Closed Starting Point

```text
Stage A architecture refactor                 CLOSED/PASS
Stage B diagnostic refactor                   CLOSED/PASS
Stage A/B compact equivalence sentinel        CLOSED/PASS — EV-250
production raw8 Sprint FIST support           CLOSED/PASS — EV-251
native NPC 1H/raw2 equipped control           CLOSED/PASS — EV-252
native NPC 2H/raw3 equipped control           CLOSED/PASS — EV-253
native NPC Axe/raw52 equipped control         CLOSED/PASS — EV-254
native equipped-NPC §8.1 trio gate            CLOSED/PASS — EV-252–EV-254
```

Sprint production implementation:
`270d98f59fd7f83ab332d7cfbfc07d243273e0ca`

Validated diagnostic built/live SHA256:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`

No code changed after that production binary; later commits are evidence/documentation only.

---

## EV-252–EV-254 native equipped-NPC closure

The planned three-control gate is complete:

```text
Goblin / BlackGoblin -> 1H / UseType 2
Demon                -> 2H / UseType 3
Ogre                 -> Axe / UseType 52
```

Across these controls, marked supported attacks repeatedly showed:

```text
factual RIGHT source begins group 5
ATTACK_OWNERSHIP RequiredMask=1
G3AB_COL_RIGHT Result=ACCEPTED
exact source 5 -> 7
one offense request outstanding
Clears=1
native contact/damage exercised where applicable
native cleanup exact source 7 -> 5
C1 CLEANUP FULFILLED
C1 final Outstanding=0 / NO_OP_NO_OUTSTANDING
```

No control produced a rejected marker, C1 invariant warning, repair divergence, unresolved equipped-source case, lifecycle issue, or required C1-R1 repair.

Processed evidence:

```text
research/archive/2026.09.11_goblin_1h_native_equipped_control.log
research/archive/2026.09.11_demon_2h_native_equipped_control.log
research/archive/2026.09.11_ogre_axe_native_equipped_control.log
```

### Demon interruption clarification

The User was not trying to reproduce a destructive interruption. They were trying to interrupt the Demon in the middle of an attack, with god mode enabled partway through because timing this safely was difficult otherwise.

One captured Power sequence happened to provide useful lifecycle evidence:

```text
Demon generation 106 Power
RIGHT accepted / It_2H_DemonSword_01 5 -> 7
player Quick attack damages Demon
native Demon source cleanup 7 -> 5
C1 obligation fulfilled
_AI_Stumble replaces execution as generation 108
ReplacedGeneration=106
ReplacedOutstanding=0
```

Interpret this only as a successful mid-attack reaction/interruption sample in which native cleanup completed before replacement. It did not reproduce destructive continuation loss and required no C1-R1 repair.

### Ogre EV-254

Ogre used factual `It_Axe_OgreMorningStar_01 / UseType 52` and exercised Normal, Power, and Quick Action 4. Each marked execution followed the same healthy RIGHT-source lifecycle and the diagnostic DLL unloaded cleanly. Quick Action 5 was not observed and is not required to close this bounded control.

---

## Next validation responsibility — Orc multi-weapon native extension

The User has prepared marked Orc animations. Orcs have greater attack variety and use multiple weapon types, so the next activity is an intentional broader native-NPC validation extension.

Use several separate logs rather than one giant mixed log. Keep one weapon/setup per log where practical; different attack families for that same setup may remain together.

For each Orc log, determine:

```text
actor / weapon identity
factual source + UseType
observed marked attack families
accepted marker and exact-source activation
native cleanup
C1 finalization
any rejection / invariant / repair / unsupported source
```

Player counterattacks are allowed; separate them by actor identity during interpretation.

This Orc extension does NOT reopen or delay the already-closed Goblin/Demon/Ogre §8.1 gate. Do not add behavior or new diagnostics unless an Orc log exposes a concrete unsupported path or contradiction.

After the Orc logs are dispositioned, return to the standing compatibility sequence in `COLLISION_TEST_PLAN.md`.
