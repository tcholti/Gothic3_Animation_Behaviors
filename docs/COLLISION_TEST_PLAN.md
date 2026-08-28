# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-28

## Purpose

Validate the preferred execution-level collision-cleanup model with the smallest tests that can falsify it, then broaden only after the lifecycle boundary is proven.

Earlier test chronology and superseded gate wording are preserved in:

`docs/archive/technical_2026-08-27/COLLISION_TEST_PLAN_pre_ia.md`

Exact established findings should be retrieved through `EVIDENCE_INDEX.md` rather than re-running old matrices without a reason.

---

## 1. Rules for the Current Test Phase

- diagnostics remain observational;
- do not implement production cleanup while B6 is still answering the post-native-opportunity question;
- do not add Staff/Quick/Whirl/block-timeout-specific cleanup branches;
- preserve native behavior for unmarked controls;
- compare one conceptual variable at a time where practical;
- visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence;
- stop and revise the diagnostic if the required event ordering cannot be reconstructed clearly;
- do not repeat already-closed marker/source tests unless a later implementation could have regressed them.

Authoritative local deployment for controlled runtime tests:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_FrameCollisionTest.dll
```

Before treating a rebuilt diagnostic run as evidence, verify that the built DLL and this exact live DLL are identical or otherwise verify the intended revised startup banner. Do not infer deployment from backup/tool directories under `E:\Mods`.

---

## 2. Gate B6 — Hit Teardown / Replacement Stack and Script-Context Validation

This is the **current gate**.

Question:

> **Do the relevant actual Hit disappearance/replacement paths occur inside one useful SPU / `gCScriptProcessingUnit::ProcessScript()` execution context, allowing a later tightly gated one-shot checkpoint to run after Gothic's native cleanup opportunity?**

### B6-A — Build/load sanity

Passed for the current empty-Primary diagnostic after verifying that only the intended live `Script_FrameCollisionTest.dll` was present, the built/live SHA256 hashes matched, and the runtime log reported:

```text
STEP B6 HIT STARTRECOVER / STOP / REPLACEMENT / EMPTY-PRIMARY SUCCESSOR STACK PROBE
```

EV-173 separately records why backup Script DLLs must not remain in the live `scripts` directory.

Required for any further revised probe:

1. current `Script_FrameCollisionTest` builds;
2. DLL loads/unloads normally with only the intended active prototype DLL present;
3. the authoritative live path above contains the intended build;
4. Win32 stack/module resolution produces readable frames when the relevant capture branch executes;
5. existing B4/B5 cleanup diagnostics remain intact;
6. no marker/collision behavior changes are introduced by the diagnostic.

### B6-B — Clean completion disappearance/replacement

EV-174/EV-175 corrected the earlier StopMotion interpretation: clean 2H Normal still had the exact Hit at `StartRecover BEGIN`, but PrimaryFirst was already empty by StopMotion-hook entry.

The StartRecover-BEGIN refinement then produced valid clean-path stack evidence in all three repeated attacks:

```text
attack Hit Primary exists / right weapon = Item_Attack(7)
→ StartRecover BEGIN
→ HIT STARTRECOVER BEGIN STACK
     diagnostic wrapper
     → Game + 0x169772  (inside sAICombatMoveInstr, starts +0x1696E0)
     → Game + 0x16F240  (inside ProcessScript, starts +0x16F120)
→ PrimaryFirst-empty StopMotion
→ Recover PlayMotion
→ StartRecover END
→ native cleanup 7 -> 5
```

EV-176 records this result.

Interpretation:

- B6-B **supports** a useful current `ProcessScript()` context for clean completion;
- StartRecover remains only an observable clean-path entry point and is still too early/bypassable for production cleanup;
- `ProcessScript()` remains generic timing infrastructure, not combat ownership authority;
- no production hook/state is justified until B6-C and B6-D are compared.

### B6-C — Legitimate damage/reaction teardown/replacement

EV-177 confirms the legitimate player 2H Normal interruption sequence:

```text
attack Hit / weapon armed
→ legitimate native interruption cleanup at Script_Game + 0x24AFF
→ Primary already empty at StopMotion
→ reaction PlayMotion begins from empty Primary
→ Stumble / KnockDown successor
```

The direct replacement-stack gate could not capture the successor because the outgoing attack Primary was already gone.

B6-C2 therefore added a diagnostic-only empty-Primary PlayMotion capture gated by the existing Normal attack-Hit semantic predicate. EV-178 shows that this refinement also misses the intended reaction successor: it fires on fresh Normal `Attack_Hit` installation from empty Primary, but by the time Stumble/KnockDown is requested the old Normal semantic gate has expired.

Representative Normal sequence from EV-178:

```text
Normal Hit activates weapon
→ legitimate +0x24AFF cleanup 7 -> 5
   action/phase still report Normal Hit at cleanup
   StateTime = 0 / StatePosition = 0
→ ~1.4 ms later StopMotion enters with empty Primary
→ reaction PlayMotion enters with empty Primary
→ LieKnockDown_Begin installed
→ NO HIT EMPTY-PRIMARY SUCCESSOR STACK record
```

An incidental 2H QuickAttackR interruption in the same controlled run independently showed the same cleanup -> empty Primary -> Stumble ordering. This is useful cross-family validation of the separation, but B6-C remains the frozen Normal-context caller-stack question.

#### Next B6-C diagnostic refinement

Improve only the missing observation fact.

Use the already-existing player/type-0 `PlayMotion` hook to capture a short caller stack for **factual empty-Primary successor installation during the controlled interruption fixture without requiring the old attack-family/action context to remain true**.

The capture must remain diagnostic-only:

- before original PlayMotion: require only the supported player/type-0 context and an available Primary snapshot with no motion instance;
- do not use Stumble, KnockDown, Recover, action, phase, StateTime, StatePosition, collision group, successor filename or another inferred cause as the pre-original capture gate;
- call original PlayMotion exactly once unchanged;
- after original: emit the record only if a real successor Primary motion instance was installed;
- log the installed successor factually so Normal Chat can identify the controlled reaction cases **post hoc**;
- preserve existing direct replacement, StopMotion, StartRecover, PrimaryFirst and collision/marker/callback behavior unchanged;
- add no production cleanup, lifecycle ownership, persistent diagnostic state, timer, polling, scan, cache, reaction classifier or new Gothic 3 hook.

This broader diagnostic will naturally capture unrelated empty-Primary player/type-0 motion installations during the short fixture. That is acceptable because the controlled test and factual successor name are used only for offline correlation; the diagnostic itself must not interpret those motions as lifecycle events.

Once an actual Stumble/KnockDown successor stack is captured, compare its Game/script-processing frames with EV-176. Only then proceed to B6-D.

### B6-D — Bad block-skip direct teardown/replacement

Run only after B6-C produces comparable factual boundary evidence.

Reproduce a native or marked bad block-skip case where offensive collision remains stale.

Required correlation:

```text
attack Hit requested offensive collision
→ no corresponding legitimate cleanup
→ actual PrimaryFirst Hit eventually disappears/replaces/restarts
→ supported factual disappearance/replacement stack/context
→ source remains offensive
```

The existing direct PlayMotion replacement-stack probe remains authoritative for paths where the outgoing Hit is still visible at PlayMotion entry and before/after proves replacement/restart.

This is the decisive negative-path comparison.

### B6 interpretation

**If all relevant disappearance/replacement paths share a useful current `ProcessScript()` invocation/context:**

- strengthen the deferred one-shot candidate;
- next design step is a narrowly gated post-script diagnostic/guard prototype, not unconditional ProcessScript cleanup.

**If a relevant disappearance/replacement occurs outside that context:**

- reject `ProcessScript()` as a universal timing checkpoint;
- return to architecture/search for another event boundary;
- do not compensate with family-specific repair branches.

**If stacks are ambiguous or a capture gate misses the event:**

- improve only the diagnostic fact needed to distinguish the execution context;
- do not convert the missed observation into lifecycle evidence.

Current immediate Normal Chat responsibility:

> Freeze and delegate only the factual player/type-0 empty-Primary successor stack refinement described above. After independent source review, build/load it and repeat a short legitimate player 2H Normal interruption fixture. Do not implement production lifecycle state or cleanup.

---

## 3. Gate C1 — Prove the Deferred Checkpoint Before Repairing Anything

Run only if B6 supports a common post-script timing point.

First add a **diagnostic-only** tightly gated one-shot checkpoint for an already-tracked/pending exact attack execution.

It must demonstrate:

1. the checkpoint runs after clean ordinary native cleanup;
2. it runs after legitimate interruption cleanup;
3. it runs after bad direct replacement even when cleanup was absent;
4. unrelated script processing does nothing because no owned execution is pending;
5. the same execution is checked once, not repeatedly.

Do not perform fallback cleanup in this gate. Establish ordering first.

---

## 4. Gate C2 — Minimal Cleanup Repair Prototype

Only after C1 proves the timing point.

Implement the smallest execution-owned repair:

```text
pending exact execution requested offensive collision
→ post-native-opportunity checkpoint
→ cleanup observed?
    yes -> retire/no-op
    no  -> perform native-equivalent repair for the owned offensive source(s)
```

Initial cases:

1. clean native completion — must no-op;
2. clean marked completion — must no-op;
3. legitimate damage/reaction interruption — must no-op;
4. known stale native block-skip — must repair;
5. known stale marked block-skip — must repair.

A successful repair must not create a second collision activation, duplicate list clear, or unrelated state mutation.

---

## 5. Gate C3 — Does Offensive Collision Ever Legitimately Survive Across Independent Hit Executions?

Once a repair exists, challenge the universal invariant with representative native/unmarked attack chaining.

Initial families:

- 1H Normal/Quick;
- Shield+1H Normal/Quick;
- Dual Normal/Quick;
- 2H Normal/full Whirl;
- Staff Normal/full Whirl.

Critical pattern to search for:

```text
Hit A requested offensive collision
Hit A physically ended
Hit B is an independent execution
NO legitimate cleanup occurred between them
and this persistence is intentional/native-correct
```

Interpretation:

- never observed legitimately → strengthens the universal end guard;
- clearly intentional transfer → architecture must represent that transfer before release;
- only observed in stale/bugged paths → supports the guard, not an exception.

Do not infer intentional carry merely from a later `7 -> 7` request; determine whether the previous source was already stale.

---

## 6. Gate C4 — Source-Aware Fallback Decision

Prefer one execution-level obligation unless evidence proves independent partial-source cleanup.

Use Dual/multi-source cases to ask:

- can RIGHT clean while LEFT legitimately remains offensive after the same Hit ends?
- can one source fail independently while another cleans?
- does the native cleanup semantic operation operate per source in a way the repair must mirror?

Adopt source-aware lifecycle state only if these tests show it is necessary.

Do not choose it merely because marker desired-set state already contains a source mask.

---

## 7. Gate C5 — Negative / No-Op Regression for Generic Script Timing

Required if the final design uses a generic SPU/script timing checkpoint.

At minimum test:

- Fist;
- bow;
- crossbow;
- magic.

Expected result:

> The generic checkpoint is a complete no-op because no exact owned weapon-style offensive execution is pending finalization.

Fist is especially important: it can share ordinary melee action enums but the tested logical Fist source does not request weapon-style `Item_Attack(7)`. This protects the rule that **actual collision ownership/request**, not action enum alone, creates the cleanup obligation.

---

## 8. Gate C6 — Block / Parade Defensive Collision Semantics

Run only before release if the chosen cleanup operation might affect defensive item state.

Controlled pairs:

- weapon into weapon block;
- weapon into shield block;
- 2H/Staff block with obvious bounce;
- ParadeStumble/block-stumble case.

Observe attacker and defender source/group requests around contact.

Questions:

1. Does a defender weapon/shield enter `Item_Attack` or another special collision state?
2. Is visual bounce physical collision or combat-state response logic?
3. Could the repair operation disturb a legitimate defensive state?

Do not add defensive special cases unless evidence requires them.

---

## 9. Marker-Core Regression — Reuse Existing Fixtures

The marker source-set core is already strongly validated. Re-run compact fixtures only after lifecycle changes that could plausibly affect it.

Representative semantics:

```text
RIGHT -> LEFT
BOTH -> RIGHT
RIGHT -> OFF -> RIGHT
BOTH -> LEFT -> OFF -> BOTH
```

Verify:

- desired-set transition;
- later source rearm through `ClearTriggeredList()`;
- occurrence/replay guards;
- natural/fallback execution retirement;
- no unexpected native timer activation.

Do not rebuild the historical v0.10–v0.18 matrix from scratch unless a regression demands it.

---

## 10. Broad Regression Phase — After the Lifecycle Model Is Chosen

Challenge the **one chosen rule** across:

- 1H;
- Shield+1H;
- Dual;
- 2H;
- Staff;
- Normal;
- Quick;
- Power;
- SimpleWhirl/full Whirl where applicable;
- player + controlled human NPC;
- marked + unmarked attacks;
- normal completion, chaining, damage interruption, blocking, and known skip conditions.

The matrix is evidence coverage, not a production branch matrix.

---

## 11. Success Criteria

The collision-lifecycle research is ready for production integration when evidence answers:

1. what constitutes an owned real attack-Hit execution;
2. what event establishes its actual physical end/replacement;
3. what creates the offensive collision obligation, including `7 -> 7` requests;
4. what timing point occurs after Gothic's legitimate cleanup opportunity;
5. how native cleanup success is observed;
6. whether repair must be attack-wide or source-specific;
7. whether any legitimate native sequence carries offensive collision across independent physical Hit executions;
8. whether defensive collision introduces a conflicting state;
9. whether unrelated Fist/ranged/magic script processing remains a no-op;
10. whether marked and native activation converge on one end-of-Hit safety rule.

Only then should the stable collision lifecycle be integrated into the production `Script_G3AnimationBehaviors` implementation.