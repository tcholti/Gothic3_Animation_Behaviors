# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-25

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: New Balance full intended-stack compatibility remains open. The bounded Sprint-origin first-FIST SP2 correction is implemented and independent Normal Chat diff review is **PASS**.

Active bounded task:

`docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_FIRST_SP2_COMPATIBILITY_CORRECTION.md`

Implementation:

```text
implementation SHA:
  ce59e5a2bad564652eaba970e959bdef0b479d82

handoff HEAD:
  858d5ca173c03c7149594b3da946594c97a13be5

PhysicalFistCollision.cpp only:
  IsFirstFistAllowed(...)
  AttackFamily_Sprint branch only

currentFamily == AttackFamily_Sprint
&& (statePosition == 1 || statePosition == 2)
&& execution.earlyOpeningSuppressed
```

Independent review confirmed:

```text
one production file
one predicate substitution
SP1 preserved
SP2 additionally accepted
current Sprint identity preserved
earlyOpeningSuppressed preserved
no authored-count branch
no >=1 generalization
no helper/state/module/hook
no New Balance/DLL detection
no neighboring behavior change
```

Next:

```text
1. User local build/deploy from current branch.
2. New Balance focused acceptance from COLLISION_TEST_PLAN.md §4.4:
   - single-FIST Sprint-origin Action9/SP2 -> accepted/open/cleanup
   - double-FIST Sprint-origin SP1 marker1 + Power/SP2 marker2 -> unchanged PASS
   - true-Power single/double controls
   - Normal/Quick raw55 controls
   - representative equipped/raw8 controls
3. If focused New Balance PASS, resume representative/full-stack New Balance coverage.
4. Before final collision-source certification, disable New Balance/AttackCollision and run the bounded standalone raw55 sentinel in §4.5. This proves the compatibility changes remain additive and the mod still works correctly without New Balance.
```

Do not repeat the old broad standalone campaign unless the sentinel finds contradictory evidence.

Runtime-evidence hygiene is closed through EV-378: processed logs are archived; `research/raw/` contains only `Keep.txt`.
