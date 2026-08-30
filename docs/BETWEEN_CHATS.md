# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1-E source-specific / marker / broader validation

C1-O2-P2 is closed for the tested outer-acquisition/binding model. Canonical result: **EV-205**.

C1-R1 implementation:

```text
93e5a2f2d4839ec908a8940927294217dd961c7a
```

Validated C1-R1 DLL:

```text
Script_FrameCollisionTest.dll
Length: 466432
SHA256: 449AC6BECB38B8627CAFAEA6311F4CC0697B91328A15D63B3446DA4766D3EAB5
Built/live match: True
```

Startup identity:

```text
STEP C1-R1 PHYSICAL REPAIR: exact live/equipped outstanding Item_Attack source resets to Item_Equipped at destructive AISetState finalization; native cleanup/no-op paths unchanged; no ClearTriggeredList.
```

Canonical physical-repair evidence:

```text
EV-206
```

Validation state:

```text
R1-A independent Normal Chat source audit = PASS
R1-B build / exact DLL identity / isolated load-unload = PASS
R1-C targeted positive repair = PASS
R1-D no-op controls = PASS
R1-E source-specific / marker / broader stability = CURRENT
```

## R1-C result

Three controlled 2H sequences were performed as:

```text
Whirl bad skip
→ wait
→ one ordinary Normal attack
```

Observed:

```text
Whirl generation 1
→ real offense
→ exact RIGHT It_2H_Sword_Flamberge remained live/equipped at 7
→ no cleanup observed before destructive finalization
→ one repair request 7 -> 5
→ result exactly 5
→ REPAIRED_TO_ITEM_EQUIPPED

Whirl generation 4
→ CombatMove existed
→ no C1 offense request
→ NO_OP_NO_OUTSTANDING
→ no repair

Whirl generation 7
→ real offense
→ exact RIGHT It_2H_Sword_Flamberge remained live/equipped at 7
→ no cleanup observed before destructive finalization
→ one repair request 7 -> 5
→ result exactly 5
→ REPAIRED_TO_ITEM_EQUIPPED
```

Following Normal generations `2/5/8` behaved normally. Every actual offensive activation in the R1-C run began `5 -> 7`; there was no inherited stale `7 -> 7` after either repair.

## R1-D result

Natural combat against a spawned golem exercised repeated Normal attacks, Stumbles/KnockDowns, four GetUpAttacks and three GetUpParades.

Reaction cleanup:

```text
7 executions of established Script_Game +0x24AFF reaction cleanup
→ exact RIGHT Flamberge 7 -> 5 each time
→ zero R1 repair attempts in the whole run
```

GetUpAttack generations:

```text
16 29 39 94
```

Each followed:

```text
PRECOMBAT_ACQUIRED
→ early exact-source offense on same OUTER_BOUND generation
→ PRECOMBAT_BRIDGE_CONSUMED
→ later persisted offense
→ native cleanup
→ finalization NO_OP_NO_OUTSTANDING
```

GetUpParade generations:

```text
49 70 84
```

Each remained `Outstanding: 0` and finalized `NO_OP_NO_OUTSTANDING`; Hit-named defensive resources did not create offense ownership.

R1-D failure/mutation signals:

```text
RepairAttempted: 1 = 0
REPAIRED_TO_ITEM_EQUIPPED = 0
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED = 0
UNRESOLVED_NOT_EQUIPPED = 0
C1 INVARIANT WARNING = 0
PhysicalCollisionChanged: 1 = 0
```

The run ended with normal DLL unload.

Processed R1-B/C/D raws are promoted unchanged to `research/archive/`.

---

## Accepted C1-R1 repair rule

```text
existing finalizer has exact outstanding source
+ exact current equipped identity establishes liveness
+ actual source group is Item_Attack(7)
→ SetCollisionGroup(Item_Equipped) exactly once on that source
→ no ClearTriggeredList()
→ verify exact result Item_Equipped(5)
```

No-op/unresolved branches remain non-mutating. Repair goes through the existing SetCollisionGroup hook. Finalization remains post-native-AISetState and uses fixed stack-local two-phase result capture/log emission.

Do not change execution acquisition, P1/P2 bridge behavior, CombatMove, hook transport, finalization timing, marker semantics, ClearTriggeredList activation/rearm behavior, family/action/input classifiers, external held-Use2 behavior, Fist/body semantics or rejected eager dispatch machinery.

EV-206 does **not** positively exercise an outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` case. Preserve the fail-closed rule and do not claim that branch runtime-proven.

---

## Current runtime responsibility — R1-E

R1-E must now validate the same physical-repair rule beyond the single-source 2H targeted/no-op matrix without changing source.

Minimum remaining responsibilities:

```text
1. Dual source-specific destructive repair control
   → prove an outstanding RIGHT or LEFT obligation repairs only that exact source
   → fulfilled/non-outstanding other side is untouched

2. Compact marker interaction
   → exercise marked RIGHT/LEFT/BOTH/OFF behavior around ordinary cleanup and, if practical, one destructive repair
   → prove R1 repair does not break marker-owned source retirement or exact-set semantics

3. Broader mixed stability / negatives
   → mixed player combat and interruptions across representative weapon configurations
   → include unmarked/native behavior and ordinary no-op paths
   → include some NPC combat if practical because production guard is actor/source-general
   → protect Fist/bow/crossbow/magic negatives; do not force weapon-style repair onto unsupported source classes
```

Do not treat R1-E as a requirement to reproduce every historical fixture. Use the smallest mixed run(s) that directly test source specificity, marker interaction and actor/general negative stability.

No source change, rebuild or redeploy is required before R1-E.
