# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-291 CLOSED; MARKER2 REPLACEMENT-CLEAR IMPLEMENTED + SOURCE-REVIEW PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-291**. No permanent raw55 implementation is authorized.

Latest canonical evidence:

`docs/EVIDENCE_LEDGER_291_ONWARD.md` — EV-291

Current frozen diagnostic contract:

`docs/COLLISION_RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE.md`

## Canonical factual checkpoint — EV-291

EV-291 proves that the exact post-hit1 native public ALL clear is causally required for Normal's implicit second same-C1 damage opportunity:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList()
-> hit1
-> PC_Hero visited/count1

native Normal transition
-> EV-288 exact native 7 -> 7 setter suppression fires
-> exact eCTrigger_PS::ClearTriggeredList() ALL arrives
   Engine +0x7DDA0
   caller Script_Game.dll +0x386C6
-> EV-291 suppression fires
-> original clear skipped
-> PC_Hero remains visited/count1
-> original _AI_Attack still completes SP0 -> 1

marker2
-> observational
-> PC_Hero still visited/count1
-> hit2 disappears

native exact RIGHT 7 -> 5 cleanup
-> clean C1 finalization
```

User visual result:

```text
first swing damaged = YES
second swing damaged = NO
```

## Current implementation under local validation

Implementation commit:

```text
f2ae82991bc1c1675c6e56c45b6f1bd267f093ee
```

Frozen base:

```text
7aa215eb7812f8819d87bd9a46c3dc9fa86490d9
```

Normal Chat independent review: **SOURCE REVIEW PASS**.

The commit is exactly one source commit over the frozen base and changes only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Review confirms:

- the previous read-only later-FIST seam is converted into the bounded marker2 replacement-clear probe;
- exact FIST/result/Normal-hit/motion-marker gates are preserved and strengthened to exactly two FIST markers;
- same current C1 and exact current/stored RIGHT source identity are required;
- exact RIGHT must remain PhysicalFist/raw55, group7, StatePosition1;
- `preStateRearmProven`, `nativeRearmSuppressionUsed`, and `nativeTriggerClearSuppressionUsed` are all required;
- a one-shot `marker2ReplacementClearUsed` gate prevents repeated clears in the same C1;
- PRE trigger state must be aligned with `PC_Hero` resolved, present exactly once, and visit count >=1;
- the exact current RIGHT `TouchDamage.ClearTriggeredList()` is called once;
- POST trigger state is captured and logged, while the existing shared clear hook remains available to observe the actual call;
- marker1 behavior, EV-288 native 7->7 suppression, EV-291 native ALL-clear suppression, cleanup and all other families are unchanged;
- no `EngineBridge`, header API, hook, RVA, CMake or production source change occurred.

Work build status: **NOT ATTEMPTED — correctly prohibited**.

No material contradiction was found in source review.

## Frozen runtime question

Preserve the complete EV-291 environment and change exactly one thing:

```text
at the factual later authored Normal FIST:
-> require same actor/C1/current RIGHT raw55 group7
-> require player still factually visited exactly once
-> execute exactly one replacement ClearTriggeredList()
```

Question:

```text
Does authored marker2 replacement ClearTriggeredList restore hit2?
```

Interpretation:

```text
replacement clear executes
+ PRE player visited
+ POST player absent
+ hit1 survives
+ hit2 returns
+ cleanup healthy
    => Normal marker2 triggered-list rearm ownership proven

replacement clear executes
+ visit clears
+ hit2 still absent
    => another Normal eligibility mechanism remains

progression/source/cleanup materially diverges
    => preserve contradiction and isolate
```

## Immediate next responsibility — LOCAL VALIDATION ONLY

Do not launch another Work task.

1. User syncs GitHub Desktop: **Fetch origin -> Pull origin -> Fetch origin**.
2. Confirm `Changes = 0 changed files`.
3. Build only:

```powershell
cmake --build build --config Release --target Script_FrameCollisionTest
```

4. STOP on build result.
5. If PASS, use normal POP-03 deploy/hash/twin verification.
6. Deploy only to `E:\SteamLibrary\steamapps\common\Gothic 3\scripts`.
7. Verify startup banner/hooks from the game-root diagnostic log.
8. Run the same Normal two-FIST Troll fixture.
9. Observe first swing, second swing, and abnormal/stuck behavior.
10. Preserve the untouched runtime source as:

```text
research/raw/2026.09.17_troll_raw55_normal_marker2_replacement_clear.log
```

11. Process with `tools\log_evidence\Prepare-Log.cmd` if useful/large.
12. Publish raw + derived evidence and close the result as the next canonical EV before advancing.

## Remaining collision order

```text
Normal marker2 replacement-clear causal proof
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO production Normal marker2 behavior until causal proof closes
NO Power/Sprint repeated-FIST intervention yet
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
