# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1-E focused negative closure

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

Canonical physical-repair evidence through R1-D: **EV-206**.

Validation state:

```text
R1-A independent source audit = PASS
R1-B build / identity / isolated load-unload = PASS
R1-C targeted positive repair = PASS
R1-D no-op / reaction / GetUp controls = PASS
R1-E Dual source-specific repair = PASS
R1-E compact marker regression = PASS
R1-E broad mixed exercised coverage = PASS
R1-E focused unarmed/crossbow negative closure = CURRENT
```

---

## Accepted C1-R1 repair rule

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

All no-op/unresolved branches remain non-mutating. Repair goes through the existing SetCollisionGroup hook and finalization stays after native AISetState. The finalizer remains two-phase so nested SetCollisionGroup diagnostics complete before the C1 FINALIZATION block.

Do not change execution acquisition, P1/P2 bridge behavior, CombatMove, hook transport, finalization timing, marker semantics, ClearTriggeredList activation/rearm behavior, family/action/input classifiers, external held-Use2 behavior, Fist/body semantics or rejected eager dispatch machinery.

The outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` branch still lacks positive runtime exercise; preserve the fail-closed rule and do not claim that branch tested.

---

## R1-E Dual source-specific result — PASS

Raw:

```text
research/raw/2026-08-30_c1r1e_dual_source_specific_physical_repair.log
commit: d8add95
bytes: 1275389
```

Observed:

```text
44 C1 finalizations × 2 tracked Dual sources = 88 per-source outcomes
13 REPAIRED_TO_ITEM_EQUIPPED = 5 RIGHT + 8 LEFT
75 NO_OP_NO_OUTSTANDING
34 C1 OFFENSE REQUEST
34 C1 CLEANUP FULFILLED
```

Each repair mutated only the exact outstanding side. The opposite Dual source remained non-mutating. Later legitimate activations did not inherit stale `7 -> 7`.

Failure signals were absent: no repair divergence, unresolved-not-equipped outcome or C1 invariant warning.

---

## R1-E compact marked Staff regression — PASS

Raw:

```text
research/raw/2026-08-30_c1r1e_marked_staff_terminal_repair_regression.log
commit: 82e5873
bytes: 268710
```

Marked Wrestling Staff full-Whirl fixture:

```text
frame 4  = G3AB_COL_RIGHT
frame 10 = G3AB_COL_OFF
frame 15 = G3AB_COL_RIGHT
```

Decisive case:

```text
accepted RIGHT marker
→ exact RIGHT Staff 5 -> 7 / real obligation
→ destructive bad skip destroys native attack ownership before marker cleanup
→ C1-R1 repairs exact live/equipped Staff 7 -> 5
→ existing SetCollisionGroup hook observes fulfillment
→ RetiredMarkerExecutionCount: 1
→ REPAIRED_TO_ITEM_EQUIPPED
```

Late callbacks from the abandoned motion were rejected and could not reopen collision. A later new marked Whirl began from clean source/marker state and accepted its normal marker sequence.

The same run also proved destructive skips before the first collision-ON marker produce no offense obligation and correctly receive no R1 mutation.

### Bad-skip timing boundary

```text
skip AFTER collision ON
→ C1-R1 fails closed by repairing the orphaned 7 -> 5
→ remaining visual portion of that abandoned attack may no longer hit

skip BEFORE collision ON
→ no offense exists
→ R1 correctly does nothing
→ late markers from the dead execution are rejected
→ that abandoned attack may miss
```

Do not try to make markers resurrect damage after Gothic 3 has already killed native attack ownership.

Future root investigation is separate and documented in:

```text
docs/BAD_SKIP_FUTURE_INVESTIGATION.md
```

Preferred first root-fix hypothesis: preserve held-Use2 timing semantics if practical, but suppress/defer only its destructive FullStop/state-replacement consequence while a real attack CombatMove is active. Keep C1-R1 underneath as the cleanup fail-safe even if such a root fix later succeeds.

---

## R1-E broad mixed exercised coverage — PASS

Raw authority:

```text
research/raw/2026-08-30_c1r1e_broad_player_npc_negative_stability.log
commit: 1df7665
SHA256: DBA13D46007D59CE67FE61B887A6CCF33770BDEA51777EB83BDBDD6EA8D96D74
bytes: 8366619
lines: 275139
```

Derived retrieval package:

```text
research/derived/2026-08-30_c1r1e_broad_player_npc_negative_stability_large_log/
commit: 6e0bf4f
```

Package accounting:

```text
10530 event blocks
326 C1 lifecycle starts
269 C1 finalizations
248 C1 offense requests
236 C1 cleanup fulfillments
653 SetCollisionGroup events

87 RIGHT marker callbacks
27 LEFT marker callbacks
19 BOTH marker callbacks
19 OFF marker callbacks
195 marker ownership decisions
```

Eight actual broad-run physical repairs were observed:

```text
REPAIRED_TO_ITEM_EQUIPPED at raw lines:
11773
32155
42423
66682
68605
71051
72462
93933
```

Representative positives include marked 2H full-Whirl, 1H and Dual/Quick cases. In Dual cases only the exact outstanding source repaired while the partner source remained clean/non-mutating. Subsequent legitimate activations began clean rather than inheriting stale offense.

The broad run also re-protected P2/GetUp behavior under natural combat: pre-Combat GetUp acquisition, bridge consumption, duplicate later offense on the same generation and native cleanup remained coherent with zero R1 mutation after cleanup.

### Unsupported marker-bearing Power negative

A Dual PowerAttack motion contained reserved custom markers even though Power is not supported by the marker adapter. This produced the desired fallback behavior:

```text
Power Action 2
→ native RIGHT and LEFT weapon collision activation proceeds
→ authored BOTH/LEFT/OFF/etc marker callbacks physically arrive
→ marker adapter rejects them as unsupported action/phase
→ markers do not suppress or steal native Power collision ownership
→ native RIGHT and LEFT 7 -> 5 cleanup proceeds
→ finalization remains non-mutating
```

Thus merely embedding a reserved marker in an unsupported family does not make that family marker-controlled.

### NPC/general-actor stability

Natural combat included non-Hero actors such as Orcs and Golem with attack/reaction/CombatMove/marker-decision traffic interleaved with player lifecycle churn. The whole run remained stable. This supports actor-general stability of the exercised hooks but is **not** claimed as a positive NPC C1 repair unless an explicit NPC repair event is separately shown.

### High-signal failures

The derived signal index contained no:

```text
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED
UNRESOLVED_NOT_EQUIPPED
C1 INVARIANT WARNING
```

User reports that bow and magic were exercised during the broad session. The derived C1-oriented reduction does not independently identify every negative class strongly enough to use that user report as proof of exact class-specific C1 behavior. Crossbow was not independently established. Unarmed/Fist was explicitly omitted.

Therefore the broad run passes for its exercised coverage, but R1-E is not yet closed by overclaiming missing negatives.

---

## Current runtime responsibility — focused unarmed + crossbow negative closure

Use the same validated C1-R1 DLL. No source change, rebuild or redeploy.

Purpose: close only the remaining unsupported-source negative gap without repeating any successful melee/marker/Dual/broad coverage.

### Frozen test

```text
A. UNARMED / FIST
1. Unequip melee/ranged weapons so the Hero is genuinely unarmed.
2. Perform several ordinary unarmed attacks in normal gameplay.
3. If available naturally, include more than one unarmed attack form (for example ordinary/quick/power-style input), but do not force unsupported engine behavior.
4. Briefly allow normal reaction/interruption churn.

B. CROSSBOW
5. Equip a crossbow.
6. Perform several normal aim/fire/reload cycles in ordinary gameplay.
7. Briefly allow normal combat/reaction/state churn.

C. SHUTDOWN
8. Exit Gothic 3 normally.
```

No held-Use2 bad-skip reproduction is required. Do not add or modify markers merely for this closure unless an existing fixture already has them; the question is unsupported-source safety, not marker-family expansion.

Required meaning:

```text
- unarmed/Fist use must not manufacture an exact weapon-style C1 repair obligation
- crossbow use must not manufacture an exact melee weapon-style C1 repair obligation
- no inappropriate REPAIRED_TO_ITEM_EQUIPPED for those unsupported source classes
- no repair divergence
- no C1 invariant warning
- no unsafe unresolved-source dereference
- no crash or abnormal state behavior
- normal DLL unload
```

Frozen raw filename:

```text
research/raw/2026-08-30_c1r1e_unarmed_crossbow_negative_closure.log
```

After this focused closure is inspected, decide whether C1-R1 validation is closed. Do not automatically invent another broad matrix.
