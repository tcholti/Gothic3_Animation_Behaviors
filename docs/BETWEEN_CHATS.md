# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-26

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: focused raw55 Sprint compatibility is CLOSED/PASS through EV-381. Before the broader New Balance gate, close the remaining Normal raw55 second-FIST SP0 authoring boundary.

Active Work task:

`docs/work/active/COLLISION_RAW55_NORMAL_SECOND_FIST_SP0_COMPATIBILITY_CORRECTION.md`

Frozen task base HEAD:

`5f50cbef0ebd37f1fbee0ef74c293fd15950325b`

Frozen production source blob:

`de175bb504c3abe13ad1c0bb9cda54997c9e3a26`

Current source Normal second-FIST gate:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && statePosition == 1;
```

Required change:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

Nothing else in production behavior is authorized to change.

Evidence basis:

```text
EV-286–EV-292:
  Normal marker1 can own SP0 opening+rearm
  exact native between-contact ClearTriggeredList is causally required for implicit hit2
  permanent marked-Normal path suppresses that native clear
  authored marker2 ClearTriggeredList can replace it and restore hit2

2026-09-26 archived 1+8 fixture:
  marker1 NORMAL/SP0 -> accepted/open+clear
  hit1 ONDAMAGE occurs
  marker2 still NORMAL/SP0 -> current gate rejects
  RIGHT already group7
```

Representative C1=1:

```text
marker1 StateTime=0.025186 SP0
hit1
marker2 StateTime=0.241280 SP0 -> rejected
```

Representative C1=3 repeats the same class with marker2 StateTime=0.246752 SP0 after hit1.

Runtime acceptance after implementation:

```text
1+3:
  marker2 SP0 accepted/clear-only
  two hits NOT required because marker2 may precede hit1

1+8:
  decisive route: marker1 -> hit1 -> marker2 still SP0
  marker2 must accept + ClearTriggeredList=1 + GroupRequested=0

1+15:
  existing SP1 marker2 acceptance/rearm remains healthy
```

Quick / Power / Sprint remain controls from the same mixed logs.

Latest deployed diagnostic before this correction:
`B4161D74DD849F4B67D9ACCFC42A8D8784F7EF19FB968F2E44D67ED57BD689`

After runtime Normal closure:

```text
focused raw55 Normal/Quick/Power/Sprint closure
-> broader representative New Balance full-stack compatibility
-> standalone/no-New-Balance sentinel
-> production collision migration
```

Paused speed authority: `DESIGN.md` §3 + ADR-0004. Configured speed is base-speed authority; native/New Balance dynamic modifiers must remain composable.