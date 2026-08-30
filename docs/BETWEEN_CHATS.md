# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1-E broader mixed stability / negatives

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
R1-E broader mixed player/NPC/negative stability = CURRENT
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

Raw evidence:

```text
research/raw/2026-08-30_c1r1e_dual_source_specific_physical_repair.log
commit: d8add95
blob: 9e879f9a86e61b62c3c5c86fd23cdfea7c543334
bytes: 1275389
```

Exact first-copy accounting:

```text
44 C1 finalizations
× 2 tracked Dual sources
= 88 per-source outcomes

13 REPAIRED_TO_ITEM_EQUIPPED
75 NO_OP_NO_OUTSTANDING

13 repairs:
5 RIGHT
8 LEFT

34 C1 OFFENSE REQUEST
34 C1 CLEANUP FULFILLED
```

Each repair mutated only the exact outstanding side. The opposite Dual source remained `RepairAttempted=0 / PhysicalCollisionChanged=0`. Later legitimate activations did not inherit `7 -> 7`.

Failure signals:

```text
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED = 0
UNRESOLVED_NOT_EQUIPPED = 0
C1 INVARIANT WARNING = 0
```

This run was unmarked/native and closes only Dual source specificity.

---

## R1-E compact marked Staff regression — PASS

Raw evidence:

```text
research/raw/2026-08-30_c1r1e_marked_staff_terminal_repair_regression.log
commit: 82e5873
bytes: 268710
```

Authored marked Staff Whirl fixture:

```text
weapon/source: Wrestling Staff_BBM, RIGHT
motion: Hero_Parade_None_Staff_P0_WhirlAttack_Hit_N_Fwd_00_%_00_P0_150_R.xmot
markers:
frame 4  = G3AB_COL_RIGHT
frame 10 = G3AB_COL_OFF
frame 15 = G3AB_COL_RIGHT
```

User runtime sequence:

```text
1 clean Whirl
2 back-to-back skipped Whirls
1 normal Whirl where bad-skip attempt failed
1 confirmed bad-skip Whirl
1 final clean Whirl
```

Six C1 generations were observed:

```text
gen 1 = clean marked Whirl
gen 2 = destructive skip after first RIGHT marker armed
gen 3 = destructive skip before offense marker
gen 4 = clean marked Whirl / failed bad-skip attempt
gen 5 = destructive skip before offense marker
gen 6 = final clean marked Whirl
```

Generation 2 is the decisive marker-owned repair case:

```text
accepted G3AB_COL_RIGHT
→ exact RIGHT Wrestling Staff obligation
→ Staff 5 -> 7
→ destructive finalization before marker-owned cleanup
→ outstanding exact Staff still live/equipped at 7
→ one C1-R1 request Item_Equipped(5)
→ resulting group exactly 5
→ REPAIRED_TO_ITEM_EQUIPPED
→ C1 CLEANUP FULFILLED observed through existing SetCollisionGroup hook
→ repair caller = Script_FrameCollisionTest.dll
→ RetiredMarkerExecutionCount: 1
```

Thus the physical repair retired the existing marker-owned source bookkeeping through the normal SetCollisionGroup hook rather than bypassing marker cleanup semantics.

After the repair, late callbacks from the abandoned marked motion arrived with unsupported action and the Staff already at 5, so they were rejected and did not reopen stale ownership.

Generations 3 and 5 prove destructive skips can occur before the first marker arms offense; both correctly finalized `NO_OP_NO_OUTSTANDING` with zero mutation.

Clean generations 1, 4 and 6 preserved existing marker behavior. Their authored RIGHT/OFF/RIGHT flow produced fresh marker budgets and clean `5 -> 7` activations; generation 6 proves the execution after the physical repair begins from clean source and marker-owned state rather than inheriting the abandoned execution.

Failure signals:

```text
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED = 0
UNRESOLVED_NOT_EQUIPPED = 0
C1 INVARIANT WARNING = 0
```

Test-design note: preparing or modifying test animations is explicitly acceptable when it strengthens falsification. Do not avoid a purpose-built marker fixture merely to reuse an old animation.

### Newly clarified bad-skip timing boundary

The marked Staff run proves two distinct consequences of the same destructive bad-skip route depending on timing relative to collision activation:

```text
A. destructive skip AFTER an accepted collision-ON marker
   → exact weapon source has a real outstanding Item_Attack(7) obligation
   → ordinary marker cleanup can be lost with the destroyed attack execution
   → C1-R1 repairs the exact live/equipped source 7 -> 5

B. destructive skip BEFORE the first accepted collision-ON marker
   → no offense obligation ever exists
   → C1-R1 correctly performs no mutation
   → later marker callbacks may still arrive from the abandoned motion,
     but native action ownership is already gone and those callbacks are rejected
   → that abandoned attack never gains collision/damage
```

Case B is intentionally **not** a C1-R1 repair responsibility. Do not make the marker system reactivate collision after native attack ownership has been destructively terminated merely to rescue the visually continuing animation; doing so would create damage from an execution Gothic 3 has already killed and risks orphaned collision ownership.

The practical consequence is limited to that one prematurely abandoned attack: it may miss completely if the bad skip occurs before collision activation. A later new attack gets a fresh native execution and fresh marker budget and activates collision normally.

### Deliberate C1-R1 safety tradeoff for post-activation skips

Before C1-R1, a destructive bad skip that happened **after** collision had already been activated could leave the weapon stuck in `Item_Attack(7)`. Because collision remained armed, the visually continuing abandoned attack could still deal damage after the native attack execution had already been destroyed, and the weapon could remain offensive until some later action happened to perform a cleanup.

With C1-R1, that same post-activation skip is deliberately converted into a fail-closed outcome:

```text
collision already activated
→ destructive bad skip kills native attack ownership
→ C1-R1 immediately repairs exact outstanding source 7 -> 5
→ any remaining visually continuing portion of that abandoned attack has no further weapon collision
```

Therefore C1-R1 does trade unsafe lingering damage for safety: if the bad skip occurs after collision activation but before the weapon has actually contacted a target, the remainder of that abandoned attack can miss. If damage/contact already happened before finalization, that already-observed hit is not undone. This is not considered a C1-R1 defect; it is the fail-closed consequence of refusing to keep collision armed without a live native attack owner.

Before C1-R1, the post-activation route could appear more successful from a hit/damage perspective precisely because the unsafe collision leak remained active. Do not interpret that old behavior as a desirable lifecycle.

After C1-R1 universal guard validation is complete, a separate root-cause investigation of the destructive bad skip is a valid future candidate. A safe root fix could eliminate both timing outcomes at the source: the post-activation stale-collision case and the pre-activation missed-attack case. Such work must remain separate from C1-R1 and must not weaken the validated guard; even if a root fix later succeeds, C1-R1 remains a useful fail-safe for lost cleanup.

For case A, later frame markers from the **same abandoned execution** are not expected to continue normal RIGHT/OFF/RIGHT semantics after destructive finalization. They may arrive physically, but with native action ownership gone they are rejected. The relevant success condition is instead:

```text
outstanding source repaired to 5
→ stale marker-owned bookkeeping retired through existing SetCollisionGroup hook
→ abandoned motion's late callbacks cannot reopen collision
→ next legitimate attack begins fresh and its markers work normally
```

---

## Current runtime responsibility — R1-E broader mixed stability / negatives

No source change, rebuild or redeploy is required.

Goal: one broader runtime run that tests the already-frozen C1-R1 rule under ordinary gameplay diversity without adding new production classifiers or forcing unsupported sources into the weapon repair model.

Minimum useful coverage:

```text
player:
- representative 1H
- Shield + 1H
- Dual
- Staff
- 2H
- mix clean attacks and ordinary interruption/reaction churn
- some held-Use2 destructive skips are useful but not mandatory for every family

NPC/general actor:
- allow several NPC melee exchanges / attacks / reactions
- no Hero-only assumption; observe existing general actor/source guard under natural activity

negative/unsupported source classes:
- Fist/unarmed
- bow
- crossbow
- magic
```

Negative classes do not need artificial bad-skip reproduction. Their role is to prove ordinary use does not create inappropriate weapon-source repair obligations or crashes/regressions.

What must remain true:

```text
- legitimate/native cleanup still wins with zero R1 mutation
- any actual R1 repair is exact-source, 7 -> 5, one-shot
- no stale later 7 -> 7 inheritance after repair
- no repair divergence
- no C1 invariant warning
- no unsafe unresolved-source dereference
- no inappropriate weapon-style repair on Fist/bow/crossbow/magic
- marker behavior remains stable if marked motions happen to be exercised
- game remains stable through ordinary player/NPC state churn and normal unload
```

Do not treat this as a requirement to reproduce every historical test family. Prefer a reasonably long natural mixed session with deliberate representative coverage.

After this broader run is inspected, package the Dual + marker + broad R1-E evidence canonically and decide whether C1-R1 validation is closed or whether one specific remaining falsification is still justified.
