# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-26

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: New Balance full intended-stack compatibility remains OPEN. EV-380 mapped the remaining raw55 Sprint-origin second-FIST timing envelope.

Latest deployed diagnostic:

```text
Built SHA256 = 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
Live  SHA256 = 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
```

EV-380:

```text
frame1+3:
  marker1 SPRINT/SP2 -> accepted/open
  marker2 SPRINT/SP2 -> rejected

frame1+8:
  marker2 can be SPRINT/SP2 OR POWER/SP2

frame1+15:
  marker2 POWER/SP2 -> accepted/clear-only rearm
```

Earliest tested Hit marker is already SP2; Sprint/SP1 second-FIST support remains unproven.

Frozen implementation rule:

```text
origin SPRINT
current POWER  -> preserve SP1 or SP2
current SPRINT -> add SP2 only
```

Active Work task:

`docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_SP2_COMPATIBILITY_CORRECTION.md`

Exact source responsibility:

`prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp`

Change only `IsSecondFistAllowed(...)`, `case AttackFamily_Sprint`:

```cpp
return (currentFamily == AttackFamily_Power
        && (statePosition == 1 || statePosition == 2))
    || (currentFamily == AttackFamily_Sprint
        && statePosition == 2);
```

Protected: first-FIST predicates, Power/Normal/Quick, identity/origin continuity, raw8, generic equipped, lifecycle, native cleanup, diagnostics, hooks.

Hard exclusions: no `>=1`; no Sprint/SP1; no Normal/SP0 change; no new hook/state/timer/species/name/file/DLL policy; no custom damage.

**Work build execution is PROHIBITED.** Work should make the bounded source edit, static-audit it, update this file with result + commit SHA, commit/push, then STOP.

After source review + User local build:

```text
1+3  SPRINT/SP2 marker2 must accept/rearm
1+8  SPRINT/SP2 and POWER/SP2 outcomes must both accept/rearm
1+15 POWER/SP2 remains accepted
single-FIST Sprint unchanged
true-Power double unchanged
Normal/Quick controls unchanged
```

Separate after correction: marked/unmarked Troll Sprint, with/without sheathing, to determine whether missing contacts are native target/contact-state behavior or marker-route behavior.

Paused speed authority: `DESIGN.md` §3 + ADR-0004. Configured speed is base-speed authority; native/New Balance dynamic modifiers must remain composable.
