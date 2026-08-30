# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1-D no-op control validation

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

Validation state:

```text
R1-A independent Normal Chat source audit = PASS
R1-B build / exact DLL identity / isolated load-unload = PASS
R1-C targeted physical repair = PASS
R1-D no-op controls = CURRENT
R1-E source-specific / marker / broader stability = pending
```

R1-B raw:

```text
research/raw/2026-08-30_c1r1_isolated_load.log
commit: 246babb
```

R1-C raw:

```text
research/raw/2026-08-30_c1r1c_player_2h_targeted_physical_repair.log
commit: 50d5a0e
bytes: 226882
```

### R1-C result

The User intentionally performed three repetitions of:

```text
2H full-Whirl known bad skip
→ wait a few seconds
→ one ordinary 2H Normal attack
```

This usefully captured both positive and negative cases.

Whirl generations:

```text
generation 1 = armed destructive case → REPAIRED_TO_ITEM_EQUIPPED
generation 4 = pre-activation/no-offense case → NO_OP_NO_OUTSTANDING
generation 7 = armed destructive case → REPAIRED_TO_ITEM_EQUIPPED
```

For generations 1 and 7 the exact RIGHT source was `It_2H_Sword_Flamberge`. Each repair had:

```text
OutstandingBeforeFinalization: 1
CleanupObservedBeforeFinalization: 0
LivenessEstablished / StillEquipped: 1
CurrentSideMask: RIGHT
ActualGroupBeforeRepair: 7
RepairAttempted: 1
RepairRequestedGroup: 5
ActualGroupAfterRepair: 5
PhysicalCollisionChanged: 1
Outcome: REPAIRED_TO_ITEM_EQUIPPED
```

No `REPAIR_DIVERGED_FROM_ITEM_EQUIPPED`, `UNRESOLVED_NOT_EQUIPPED`, or `C1 INVARIANT WARNING` occurred.

Generation 4 reached `_AI_WhirlAttack` / CombatMove but produced no `C1 OFFENSE REQUEST`; finalization was `NO_OP_NO_OUTSTANDING`. This is a positive pre-activation negative control.

Following ordinary Normal generations were:

```text
generation 2
generation 5
generation 8
```

All three were `_AI_Attack`, requested offense, received native cleanup, and finalized `NO_OP_NO_OUTSTANDING`.

Across the whole R1-C log there were exactly five actual offensive `SetCollisionGroup(Item_Attack)` transitions (duplicated into ten diagnostic records by the existing engine/outer-frame logging), and every one began:

```text
BeforeGroup: 5
RequestedGroup: 7
AfterGroup: 7
```

Therefore neither successful R1-C repair left stale group 7 to be inherited by the following Normal attack. The physical stale state was actually removed.

R1-C therefore proves the first C1-R1 positive physical mutation twice and also contributes two R1-D controls already:

```text
ordinary clean completion = PASS in this run
pre-activation/no-offense destructive skip = PASS in this run
```

---

## Accepted C1-R1 repair rule

```text
exact outstanding source
+ exact current equipped identity establishes liveness
+ source still Item_Attack(7)
→ SetCollisionGroup(Item_Equipped) exactly once on that source
→ no ClearTriggeredList()
→ verify exact result Item_Equipped(5)
```

Native cleanup has precedence. Non-outstanding, not-safely-live and already-clean sources remain non-mutating. Dual/source ownership remains per exact source.

Do not change P1/P2 acquisition, CombatMove, hook transports, finalization timing, marker semantics, Fist/body semantics, external held-Use2 behavior, or rejected eager dispatch machinery.

---

## Current runtime responsibility — R1-D remaining no-op controls

Already covered by R1-C:

```text
ordinary clean completion = covered
pre-activation interruption/no offense = covered
```

Still required before R1-D closes:

```text
legitimate armed reaction/stumble/knockdown cleanup
clean GetUpAttack with P2 pre-Combat acquisition + native cleanup
GetUpParade defensive/no-offense control
```

Expected:

```text
legitimate reaction
→ native/reaction cleanup fulfills outstanding source
→ finalization no repair

clean GetUpAttack
→ P2 pre-Combat bridge remains correct where applicable
→ native cleanup fulfills source
→ finalization no repair

GetUpParade
→ Hit-named resource alone creates no C1 offense obligation
→ no repair
```

Physical repair remains under validation. R1-E must not begin until these remaining no-op controls pass.