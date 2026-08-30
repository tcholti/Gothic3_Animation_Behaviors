# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1-E marker / broader validation

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
R1-E compact marker regression = CURRENT
R1-E broader mixed player/NPC/negative stability = pending
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

User deliberately exercised repeated Dual QuickAttack bad-skip attempts from one stance/source, changed P0/P1 side with a Normal attack, then repeated from the other stance/source. Testing outside combat removed enemy-interruption noise.

Exact first-copy accounting from the committed raw:

```text
44 C1 finalizations
× 2 tracked Dual sources
= 88 per-source finalization outcomes

13 REPAIRED_TO_ITEM_EQUIPPED
75 NO_OP_NO_OUTSTANDING

34 C1 OFFENSE REQUEST
34 C1 CLEANUP FULFILLED
```

The 13 repairs split across both exact Dual sources:

```text
5 RIGHT repairs
8 LEFT repairs
```

Representative source-specific behavior:

```text
RIGHT outstanding at 7
→ RIGHT RepairAttempted=1
→ one request 5
→ RIGHT result 5 / PhysicalCollisionChanged=1
→ LEFT NO_OP_NO_OUTSTANDING / RepairAttempted=0 / PhysicalCollisionChanged=0

LEFT outstanding at 7
→ LEFT RepairAttempted=1
→ one request 5
→ LEFT result 5 / PhysicalCollisionChanged=1
→ RIGHT NO_OP_NO_OUTSTANDING / RepairAttempted=0 / PhysicalCollisionChanged=0
```

There was no `RequestedGroup: 7` with `BeforeGroup: 7`; later legitimate Dual activations began clean rather than inheriting stale offense.

Failure signals:

```text
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED = 0
UNRESOLVED_NOT_EQUIPPED = 0
C1 INVARIANT WARNING = 0
```

Normal DLL unload was captured.

This Dual run was **unmarked/native**: observed QuickAttack motion decisions reported `ContainsReservedSourceMarker: 0`. It therefore closes only the source-specific portion of R1-E and does not count as marker regression.

---

## Current runtime responsibility — R1-E compact marked terminal-repair regression

Reuse the already-proven v0.20 marked Staff full-Whirl fixture from:

```text
research/archive/2026-08-25_framecollision_v0.20_player_staff_2h_dual_block_timeout_marked_probe.log
```

Known fixture:

```text
weapon/source: Wrestling Staff_BBM, RIGHT
motion: Hero_Parade_None_Staff_P0_WhirlAttack_Hit_N_Fwd_00_%_00_P0_150_R.xmot
ContainsReservedSourceMarker: 1
G3AB_COL_RIGHT occurrence at frame 4
G3AB_COL_OFF occurrence at frame 10
later RIGHT occurrence also authored
```

Historical marked bad-skip behavior showed the first accepted RIGHT marker activating the Staff `5 -> 7`; after destructive state/action replacement, later marker callbacks could arrive with unsupported action and be rejected while the source remained offensive. That is exactly the interaction C1-R1 must now make safe without changing marker semantics.

### Frozen test

Use the same C1-R1 DLL; no rebuild/redeploy.

```text
1. Equip Wrestling Staff_BBM / Staff setup using the existing marked full-Whirl animation.
2. Perform ONE clean full Whirl and let it finish normally.
3. Reproduce the known held-Use2 bad skip on the marked full Whirl.
   Because manual timing can miss the armed window, make up to 3 attempts if needed.
4. After each bad-skip attempt, wait a couple of seconds.
5. After the attempts, perform ONE clean marked full Whirl and let it finish.
6. Exit normally.
```

The log, not visual timing, decides whether each attempted bad skip armed the marker-owned source.

### Required meaning

Clean marked Whirl before the destructive attempt must preserve existing marker behavior and ordinary cleanup/no-op finalization.

For any armed destructive marked case:

```text
accepted RIGHT marker
→ exact Staff source obligation / marker-owned source active at 7
→ later marker OFF may be rejected if native action/state was already destroyed
→ destructive finalization sees exact outstanding live Staff at 7
→ C1-R1 performs one exact 7 -> 5 repair
→ existing SetCollisionGroup hook observes cleanup
→ marker-owned source bookkeeping is retired through existing logic
→ finalization REPAIRED_TO_ITEM_EQUIPPED
```

The later clean marked Whirl must then begin from a clean source and accept its marker sequence normally; no stale `7 -> 7` inheritance or stale marker-owned bookkeeping may block/reuse the previous execution.

If an attempted bad skip occurs before the first accepted RIGHT marker, zero obligation/zero repair is the correct result.

Failure/high-signal checks:

```text
repair divergence
C1 invariant warning
unresolved source
stale marker-owned source carried into the next execution
marker occurrence budget not resetting for the new execution
unexpected suppression/fallback change
```

Frozen raw filename:

```text
research/raw/2026-08-30_c1r1e_marked_staff_terminal_repair_regression.log
```

Stop and preserve the run if the game crashes or behavior is clearly abnormal.

---

## After marker regression

If the compact marked test passes, the only remaining R1-E responsibility is broader mixed player/NPC/negative stability. That final run should deliberately cover representative weapon families plus some NPC activity and protect Fist/bow/crossbow/magic negative behavior without attempting to force C1 weapon-source repair onto unsupported source classes.
