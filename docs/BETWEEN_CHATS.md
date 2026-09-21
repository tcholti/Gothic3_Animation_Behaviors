# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-21

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Current state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Latest runtime evidence:
- EV-355 diagnostic production-candidate smoke PASS;
- EV-356 diagnostics-free behavior-twin smoke PASS.

Final source-quality audit: CLOSED, no material behavioral contradiction, no MUST-correct findings.

Final cleanup commits:
- `9789254866bb47dcbadb145aeb9831c7c0e4e97f` — exact-generation C1 metadata retirement; independent Normal Chat static review PASS.
- `f1f5d2aad3edc3564a9a8b40541840b94f8fa903` — release/diagnostic hygiene + CORE compaction; independent Normal Chat static review PASS.

Current final source candidate:
`f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

No Work implementation task is active.

## Next gate

After pulling the maintained documentation state, run:

`python tools/knowledge/validate_knowledge_state.py`

Require exact:

`Knowledge-state validation PASS`

Then build both twins once from the final source candidate:

```powershell
cmake --build build --config Release --target Script_FrameCollisionBehaviorTest
cmake --build build --config Release --target Script_FrameCollisionTest
```

A successful build does not deploy.

After both builds pass:
1. deploy only the diagnostic twin using POP-03 sole-live/hash verification;
2. run POP-04 main-menu startup/clean-unload;
3. run a small targeted diagnostic re-smoke designed to exercise the two cleanup classes:
   - raw8 marked opportunity/contact/miss/finalization;
   - equipped Sprint material bind/Action9 -> Action2 continuation log path;
   - raw55 repeated-FIST + generic equipped marker coexistence;
   - generation-finalization churn sufficient to exercise the new metadata retirement without broad regression.
4. analyze/close that evidence;
5. deploy behavior-only twin and run a small functional parity re-smoke;
6. if both pass, freeze source and begin focused permanent raw8 acceptance.

Do not begin the full focused acceptance matrix before post-cleanup re-smoke closes.

Closed cleanup contracts:
- `docs/archive/investigations/COLLISION_FINAL_C1_METADATA_RETIREMENT_CLEANUP.md`
- `docs/archive/investigations/COLLISION_FINAL_RELEASE_DIAGNOSTIC_HYGIENE_CLEANUP.md`

`research/raw/` should contain only `Keep.txt` before the next runtime evidence capture.
