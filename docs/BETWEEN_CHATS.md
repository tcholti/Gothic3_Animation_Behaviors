# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-25

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: New Balance full intended-stack compatibility remains open. EV-378 runtime-confirmed every predicate changed by the first raw55 SP2 correction, then exposed one additional exact Sprint-origin first-FIST SP2 case.

Active bounded Work task:

`docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_FIRST_SP2_COMPATIBILITY_CORRECTION.md`

Frozen responsibility:

```text
MODIFY only:
  prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp

within:
  IsFirstFistAllowed(...)
  case AttackFamily_Sprint only

current:
  currentFamily == AttackFamily_Sprint
  && statePosition == 1
  && execution.earlyOpeningSuppressed

required:
  currentFamily == AttackFamily_Sprint
  && (statePosition == 1 || statePosition == 2)
  && execution.earlyOpeningSuppressed
```

Reason: EV-378 repeatedly observes an exact already-owned Sprint-origin single-FIST execution at factual `Action9 / SPRINT / SP2`, with `earlyOpeningSuppressed=1` and RIGHT still group5. The unchanged SP1-only first-FIST predicate rejects it.

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

Work build execution is PROHIBITED. Work must commit/publish the bounded source change, update this bridge with implementation result/final SHA as required by protocol, and stop for independent Normal Chat review.

After Normal Chat review, the User builds/deploys locally and runs `COLLISION_TEST_PLAN.md` §4.4 focused acceptance:

```text
1. single-FIST Sprint-origin Action9/SP2 -> accepted/open/cleanup
2. double-FIST Sprint-origin SP1 marker1 + Power/SP2 marker2 -> remains accepted/rearm
3. true-Power single/double controls
4. Normal/Quick raw55 controls
5. representative equipped/raw8 controls
```

Runtime-evidence hygiene is closed through EV-378: processed logs are archived; `research/raw/` contains only `Keep.txt`.
