# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-26

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: focused raw55 Sprint compatibility is CLOSED/PASS through EV-381. The bounded Normal raw55 second-FIST SP0 correction is implemented and independently reviewed; runtime acceptance is now the only remaining responsibility.

Active task:
`docs/work/active/COLLISION_RAW55_NORMAL_SECOND_FIST_SP0_COMPATIBILITY_CORRECTION.md`

Implementation:
`a31c66b97e45c27d0739b7df51252d33f490e7e1`

Implementation parent:
`396c7b8b0886174860cc452176a2ed57bf530784`

Independent Normal Chat static review: **PASS**.

Reviewed production diff is exactly one Normal `IsSecondFistAllowed(...)` predicate widening:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

Only Normal second-FIST acceptance changed. Quick, Power, Sprint, every first-FIST predicate, Normal native-clear suppression, marker2 clear-only behavior, C1/lifecycle ownership, hooks and diagnostics are unchanged.

Evidence basis:

```text
EV-286–EV-292:
  Normal marker1 can own SP0 opening+rearm
  exact native between-contact ClearTriggeredList is causally required for implicit hit2
  permanent marked-Normal path suppresses that native clear
  authored marker2 ClearTriggeredList can replace it and restore the later opportunity

archived New Balance 1+8 fixture:
  marker1 NORMAL/SP0 -> accepted/open+clear
  hit1 ONDAMAGE occurs
  marker2 still NORMAL/SP0 -> old SP1-only gate rejects
  RIGHT already group7
```

Current runtime acceptance:

```text
1+3:
  marker2 NORMAL/SP0 -> ACCEPTED
  ClearTriggeredList=1
  GroupRequested=0
  two hits not required because marker2 may precede hit1

1+8 decisive route:
  marker1 SP0 -> hit1 -> marker2 still SP0
  marker2 -> ACCEPTED + ClearTriggeredList=1 + GroupRequested=0
  healthy 7->5 cleanup / outstanding0

1+15 positive control:
  marker2 NORMAL/SP1 remains accepted/clear-only
  healthy cleanup

Quick / Power / Sprint remain controls in the same mixed logs.
```

Native target/contact/damage stays Gothic-owned; collision correctness is marker acceptance/rearm plus healthy cleanup, not a guaranteed hit count.

Latest deployed diagnostic before this correction:
`B4161D74DD849F4B7B67D9ACCFC42A8D8784F7EF19FB968F2E44D67ED57BD689`

Build of this candidate: NOT YET REPORTED. Work build execution was not authorized.

Next step: user locally builds/deploys, runs `1+3`, `1+8`, `1+15`, and uploads the logs. Normal Chat then reviews evidence, records the next EV, and either closes/archives this task or reports the exact remaining contradiction.

After runtime Normal closure:
`focused raw55 closure -> broader New Balance full-stack compatibility -> standalone/no-New-Balance sentinel -> production collision migration`.

Paused speed authority: `DESIGN.md` §3 + ADR-0004.