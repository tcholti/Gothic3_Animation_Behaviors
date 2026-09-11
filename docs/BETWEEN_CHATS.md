# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — GOBLIN 1H/RAW2 CLOSED; DEMON 2H/RAW3 NEXT

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
```

Sprint production implementation:
`270d98f59fd7f83ab332d7cfbfc07d243273e0ca`

Validated diagnostic built/live SHA256:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`

No code changed after that production binary; later commits are evidence/documentation only.

---

## EV-252 native 1H/raw2 closure

One unchanged CORE log exercised two separate native NPC attackers one at a time:

```text
Goblin      -> It_1H_Club_01       / UseType 2
BlackGoblin -> It_1H_Sword_Rust_01 / UseType 2
```

Observed marked attack families included Normal and Quick, with Quick Action 4 and Action 5 directions.

Healthy equipped lifecycle repeated across both actors:

```text
RIGHT source begins group 5
ATTACK_OWNERSHIP RequiredMask=1
G3AB_COL_RIGHT Result=ACCEPTED
exact factual source 5 -> 7
one C1 offense request outstanding
Clears=1
native attack/contact exercised
native cleanup exact source 7 -> 5
C1 CLEANUP FULFILLED
C1 final Outstanding=0 / NO_OP_NO_OUTSTANDING
```

Player counterattacks are separately attributed as `PC_Hero` and do not contaminate NPC source ownership.

Whole-log targeted anomaly checks found none of:

```text
REJECTED_*
C1 INVARIANT WARNING
REPAIR_DIVERGED
UNRESOLVED_NOT_EQUIPPED
LIFECYCLE_ISSUE
REPAIRED_TO_ITEM_EQUIPPED
```

The diagnostic DLL unloaded cleanly.

Processed evidence:

```text
research/archive/2026.09.11_goblin_1h_native_equipped_control.log
```

Do not expand Goblin testing merely for more routine variation.

---

## Next validation responsibility — Demon 2H/raw3

Authority:

```text
docs/COLLISION_TEST_PLAN.md §8.1
```

Run one separate native Demon control:

```text
Demon -> factual 2H / raw3
```

Question:

```text
does established equipped marker ownership follow the exact factual 2H/raw3 source
for a native Demon, including activation, native cleanup and clean C1 finalization?
```

Use the already-deployed compact CORE diagnostic DLL; no rebuild is required. Seek the smallest useful marked attack fixture and let attacks connect where practical. Preserve and commit the complete raw log unchanged before interpretation.

If Demon passes, the remaining §8.1 control is:

```text
Ogre -> factual Axe / raw52
```

Do not yet begin:

```text
additional broad actor/family matrix
2H-vs-Axe mod compatibility
1H-vs-Rapier mod compatibility
final native mixed/stress regression
AttackContinuationProtection
Raise/speed/config work
```
