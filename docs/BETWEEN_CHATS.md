# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — GOBLIN + DEMON CONTROLS CLOSED; OGRE AXE/RAW52 NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_TEST_PLAN.md §8.1
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
```

Sprint production implementation:
`270d98f59fd7f83ab332d7cfbfc07d243273e0ca`

Validated diagnostic built/live SHA256:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`

No code changed after that production binary; later commits are evidence/documentation only.

---

## EV-252 native 1H/raw2 closure

One unchanged CORE log exercised two native NPC attackers one at a time:

```text
Goblin      -> It_1H_Club_01       / UseType 2
BlackGoblin -> It_1H_Sword_Rust_01 / UseType 2
```

Normal and Quick marked attacks followed the established RIGHT-source lifecycle: exact source `5 -> 7`, accepted marker, `Clears=1`, native contact, native cleanup `7 -> 5`, and clean C1 finalization. No anomaly or repair path was observed.

Processed evidence:

```text
research/archive/2026.09.11_goblin_1h_native_equipped_control.log
```

---

## EV-253 native 2H/raw3 closure

The unchanged Demon CORE log exercised:

```text
Demon -> It_2H_DemonSword_01 / UseType 3
Normal
Quick Action 4
Quick Action 5
Power
```

Healthy lifecycle repeated:

```text
RIGHT source group 5
ATTACK_OWNERSHIP RequiredMask=1
G3AB_COL_RIGHT Result=ACCEPTED
exact source 5 -> 7
one offense request outstanding
Clears=1
native contact/damage exercised
native cleanup exact source 7 -> 5
C1 CLEANUP FULFILLED
C1 final Outstanding=0 / NO_OP_NO_OUTSTANDING
```

A deliberate player counterattack also captured a legitimate reaction interruption after Demon Power had armed collision:

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

This is positive legitimate-reaction evidence. It did not reproduce destructive continuation loss and required no C1-R1 repair.

Whole-log targeted checks found none of:

```text
ReplacedOutstanding=1
REPAIRED_TO_ITEM_EQUIPPED
C1 INVARIANT WARNING
REPAIR_DIVERGED
UNRESOLVED_NOT_EQUIPPED
LIFECYCLE_ISSUE
```

The diagnostic DLL unloaded cleanly.

Processed evidence:

```text
research/archive/2026.09.11_demon_2h_native_equipped_control.log
```

---

## Next validation responsibility — Ogre Axe/raw52

Authority:

```text
docs/COLLISION_TEST_PLAN.md §8.1
```

Run the remaining separate native equipped-NPC control:

```text
Ogre -> factual Axe / raw52
```

Question:

```text
does established equipped marker ownership follow the exact factual Axe/raw52 source
for a native Ogre, including activation, native cleanup and clean C1 finalization?
```

Use the already-deployed compact CORE diagnostic DLL; no rebuild is required. Seek the smallest useful marked attack fixture and let attacks connect where practical. Preserve and commit the complete raw log unchanged before interpretation.

Do not yet begin:

```text
additional broad actor/family matrix
2H-vs-Axe mod compatibility
1H-vs-Rapier mod compatibility
final native mixed/stress regression
AttackContinuationProtection
Raise/speed/config work
```
