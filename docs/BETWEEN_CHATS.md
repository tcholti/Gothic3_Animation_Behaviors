# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-16

## Current Bridge — EV-290 CLOSED; NATIVE CLEAR SUPPRESSION IMPLEMENTED + SOURCE-REVIEW PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-290**. No permanent raw55 implementation is authorized.

Current diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`

Current diagnostic implementation:

`2839c8c271fa240b81ce5ccd203c34058870a5bb`

Required implementation base:

`23400f2b5b3afdbe8c03088be01aa4bc969849db`

Normal Chat independently reviewed the Work commit and marked **SOURCE REVIEW PASS**.

The implementation is exactly one commit ahead of the frozen base and changes only:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

Review result:

- existing `Engine + 0x7DDA0` ALL-clear hook is reused; no new hook/RVA;
- `EngineBridge` only transports/enacts the suppression decision;
- `PhysicalFistProbe` owns exact Normal actor/C1/RIGHT/raw55/contact/caller gating, one-shot state and logging;
- marker-1 authored clear remains unsuppressed;
- entity-specific clear remains unsuppressed;
- unrelated ALL clears execute normally;
- existing EV-288 exact native `7 -> 7` suppression remains unchanged;
- no direct visited-array mutation, new clear, StatePosition write, damage dispatch, cleanup change or production-module change;
- Work build was not attempted.

## Canonical factual checkpoint — EV-290

EV-290 identifies the exact native reset operation behind Normal's implicit second-contact opportunity:

```text
first FIST at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList()
-> first damage
-> PC_Hero enters visited list / count1

later native Normal transition
-> existing EV-288 exact RIGHT 7 -> 7 setter suppression fires
-> PC_Hero is still visited
-> Gothic calls eCTrigger_PS::ClearTriggeredList() ALL
   caller = Script_Game.dll + 0x386C6
   PRE  = player present/count1
   POST = arrays empty/player absent
-> original _AI_Attack completes SP0 -> 1

later marker2
-> observational only
-> second damage occurs
-> player re-enters visited list
-> native 7 -> 5 cleanup / clean C1
```

Canonical EV-290 evidence:

```text
raw:
research/raw/2026.09.16_troll_raw55_normal_native_trigger_clear_observation.log

SHA256:
E699B807059189289D4CAB6B243F966F49947C9083656EE693B8FDD21676693F

upload commit:
8b483b48636deeec4fa6863533da4a7db4fe2e15

derived POP-07 package:
research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_observation_large_log/
```

Do **not** infer from EV-290 alone that the native clear is required for hit2. EV-290 identifies the operation; the current probe tests necessity.

## Current causal question

With EV-290 behavior otherwise preserved, suppress exactly once the post-hit1 native:

```text
eCTrigger_PS::ClearTriggeredList()
Engine + 0x7DDA0
CallerModule = Script_Game.dll
CallerRVA    = 0x386C6
```

only when the exact current Normal actor/C1/RIGHT raw55 source is group7, the frame-1 rearm is proven, EV-288 suppression has already fired, StatePosition is 0, and `PC_Hero` is factually present exactly once in aligned visited/count arrays with visit count >= 1.

Marker1 remains unchanged. Marker2 remains observational.

Decisive routes:

```text
suppression fires
+ player remains visited through SP0 -> 1 / marker2
+ hit1 survives
+ hit2 disappears
+ cleanup healthy
    => native ALL clear is causally required
    => next one-variable test may give marker2 the replacement clear

suppression fires
+ player remains visited
+ hit2 still occurs
    => another native contact mechanism remains

progression/source/cleanup materially diverges
    => preserve contradiction and isolate before authored replacement
```

## Immediate next responsibility — LOCAL VALIDATION ONLY

Do not launch another Work task.

1. User syncs GitHub Desktop: **Fetch origin -> Pull origin -> Fetch origin**.
2. Confirm `Changes = 0 changed files`.
3. Build only `Script_FrameCollisionTest` Release.
4. STOP on build result.
5. If PASS, deploy only to:
   `E:\SteamLibrary\steamapps\common\Gothic 3\scripts`
6. Verify built/live SHA and sole collision twin.
7. Verify diagnostic startup banner from the game-root log.
8. Run the same Normal two-FIST Troll fixture.
9. Record visually whether first and second swings damage and whether anything abnormal occurs.
10. Preserve the new log under a new exact filename frozen by Normal Chat before the run.
11. For a large log, use the routine drag-and-drop workflow: drag the untouched raw `.log` onto `tools\log_evidence\Prepare-Log.cmd`, then commit/push both raw + generated derived package.
12. Close the new runtime as the next EV before advancing.

## Raw/derived retrieval discipline for the next Chat

**Do not enumerate or scan `research/raw/` during orientation.** The raw folder contains many processed historical logs, including multi-megabyte files.

For current work:

- start from EV-290 in `docs/EVIDENCE_LEDGER_286_ONWARD.md`;
- use the EV-290 derived package above if exact runtime verification is needed;
- open the full raw log only for a precise unresolved fact that the EV/derived package cannot answer;
- older EV-286–EV-289 raw logs are processed historical provenance and are not active orientation inputs.

Physical archive cleanup of older large raw files was **not performed in this Chat** because the connected GitHub write surface cannot guarantee a byte-faithful multi-megabyte move without reconstructing file content. Canonical evidence integrity takes priority over cosmetic cleanup. This is not a blocker for continuation.

## Small continuity review findings

- `SESSION_ENTRYPOINT.md` and this handoff must be the only current-state front door.
- `EVIDENCE_LEDGER_286_ONWARD.md` canonically owns EV-286–EV-290.
- `EVIDENCE_INDEX.md` is a cold routing index and currently has some stale ledger-split/range wording from before `EVIDENCE_LEDGER_286_ONWARD.md`; do not use that stale range wording as current-state authority. It should be repaired in a later bounded documentation-maintenance pass, not during the active causal test.
- No architecture contradiction was found in the active Normal route.
- No permanent `PhysicalFistCollision` is authorized yet.

## Deployment authority

```text
live collision DLLs:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic logs:
E:\SteamLibrary\steamapps\common\Gothic 3
```

Never deploy the collision DLL to the game root.

## Remaining collision order

```text
Normal native ALL-clear necessity runtime
-> if required, authored Normal marker2 replacement/rearm proof
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```
