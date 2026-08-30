# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1-C targeted physical-repair validation

C1-O2-P2 is closed for the tested outer-acquisition/binding model. Canonical result: **EV-205** plus the dedicated shutdown-closure evidence commit `4946d382041e9ec86400291395e5acbad77b1de6`.

C1-R1 implementation:

```text
93e5a2f2d4839ec908a8940927294217dd961c7a
```

Validated C1-R1 built/live DLL:

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

Validation state:

```text
R1-A independent Normal Chat source audit = PASS
R1-B build / exact DLL identity / isolated load-unload = PASS
R1-C targeted positive repair = CURRENT
R1-D no-op controls = pending
R1-E source-specific / marker / broader stability = pending
```

R1-B canonical raw:

```text
research/raw/2026-08-30_c1r1_isolated_load.log
commit: 246babb
```

R1-B confirms exact C1-R1 startup identity, successful hook installation, and `Script_FrameCollisionTest unloading.` as the final event.

---

## Accepted C1-R1 repair rule

The physical mutation is exactly:

```text
existing finalizer has exact outstanding source
+ exact current equipped identity establishes liveness
+ actual source group is Item_Attack(7)
→ SetCollisionGroup(Item_Equipped) exactly once on that source
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

Existing no-op/unresolved branches remain non-mutating:

```text
no outstanding obligation
→ NO_OP_NO_OUTSTANDING

remembered source not established as exact current equipped RIGHT/LEFT
→ UNRESOLVED_NOT_EQUIPPED
→ do not dereference remembered source

exact live/equipped outstanding source already not Item_Attack
→ NO_OP_PHYSICALLY_CLEAN_RECONCILED
```

Repair goes through the already-hooked SetCollisionGroup path. Finalization uses fixed stack-local two-phase result capture so nested SetCollisionGroup diagnostics complete before the final C1 FINALIZATION block is printed.

Do not change execution acquisition, P1/P2 bridge behavior, CombatMove, hook transport, finalization timing, marker semantics, ClearTriggeredList activation/rearm behavior, family/action/input classifiers, external held-Use2 behavior, Fist/body semantics, or rejected eager dispatch machinery.

---

## Current runtime responsibility — R1-C

Question:

> Can one already-proven destructive stale-collision case now physically reset the exact live/equipped outstanding source from `Item_Attack(7)` to `Item_Equipped(5)`, and does the next legitimate attack begin from a clean `5 -> 7` state instead of inheriting stale `7 -> 7`?

Use one controlled player 2H setup and the same known held-Use2 destructive reproduction previously used to create an armed stale case. Prefer the established full-Whirl/held-Use2 trigger if it is reliable in the chosen save/setup.

Minimum sequence:

```text
1. Load the controlled 2H setup.
2. Reproduce ONE known armed destructive abandonment while the weapon has genuinely requested Item_Attack.
3. Allow the destructive transition to complete / return to a stable successor state.
4. Perform ONE ordinary clean 2H Normal attack with the same weapon.
5. Exit normally.
```

Expected positive repair lifecycle:

```text
real offense obligation
→ no native cleanup before destructive AISetState
→ exact source still live/equipped at Item_Attack(7)
→ one repair request to Item_Equipped(5)
→ nested SetCollisionGroup observes 7 -> 5 cleanup
→ finalization reports REPAIRED_TO_ITEM_EQUIPPED
→ RepairAttempted: 1
→ ActualGroupBeforeRepair: 7
→ RepairRequestedGroup: 5
→ ActualGroupAfterRepair: 5
→ PhysicalCollisionChanged: 1
```

Expected later ordinary control:

```text
same weapon's next legitimate offense normally begins 5 -> 7
→ native cleanup later returns 7 -> 5
→ no second repair for that clean execution
```

If the game crashes or anything visibly abnormal happens, stop immediately and preserve that run; do not repeat the destructive case.

Frozen raw filename:

```text
research/raw/2026-08-30_c1r1c_player_2h_targeted_physical_repair.log
```

Do not broaden into R1-D/R1-E controls yet.
