# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-25

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: New Balance full intended-stack compatibility remains open. The bounded Sprint-origin first-FIST SP2 compatibility correction is implemented at `ce59e5a2bad564652eaba970e959bdef0b479d82` and awaits independent Normal Chat diff review.

Active bounded task pending independent review:

`docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_FIRST_SP2_COMPATIBILITY_CORRECTION.md`

Implementation result:

```text
MODIFY only:
  prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp

within:
  IsFirstFistAllowed(...)
  case AttackFamily_Sprint only

implemented:
  currentFamily == AttackFamily_Sprint
  && (statePosition == 1 || statePosition == 2)
  && execution.earlyOpeningSuppressed

published implementation SHA:
  ce59e5a2bad564652eaba970e959bdef0b479d82
```

Reason: EV-378 repeatedly observes an exact already-owned Sprint-origin single-FIST execution at factual `Action9 / SPRINT / SP2`, with `earlyOpeningSuppressed=1` and RIGHT still group5. The previous SP1-only first-FIST predicate rejected it.

Protected unchanged:

```text
true-Power first-FIST SP1/SP2 predicate
true-Power second-FIST SP1/SP2 predicate
Sprint-origin later current-Power SP1/SP2 predicate
Normal
Quick
raw8 persistent-opportunity system
generic equipped markers
EquippedSprintCollision
PhysicalFistExecution identity
origin continuity
C1/lifecycle
premature native opening suppression
first-open / second-clear-only semantics
native callback progression
native final cleanup
EngineBridge/hooks
AttackMotionRouting
unmarked fallback
```

Explicitly prohibited:

```text
StatePosition >= 1
authored-count branching
new helper/state/module/hook
New Balance/DLL detection
species/name rule
filename inference
timer/polling
custom damage/contact
cleanup change
unrelated refactor
```

Work build execution was not attempted. The bounded source responsibility is complete; Normal Chat must now review the implementation diff against the frozen contract before local build/deployment.

After Normal Chat review, the User builds/deploys locally and runs `COLLISION_TEST_PLAN.md` §4.4 focused acceptance:

```text
1. single-FIST Sprint-origin Action9/SP2 -> accepted/open/cleanup
2. double-FIST Sprint-origin SP1 marker1 + Power/SP2 marker2 -> remains accepted/rearm
3. true-Power single/double controls
4. Normal/Quick raw55 controls
5. representative equipped/raw8 controls
```

Runtime-evidence hygiene is closed through EV-378: processed logs are archived; `research/raw/` contains only `Keep.txt`.
