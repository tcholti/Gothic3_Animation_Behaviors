# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-26

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: New Balance full intended-stack compatibility remains OPEN. The bounded raw55 Sprint-origin second-FIST SP2 correction is implemented at `4c85193f4efd31e789bc07d7e3c71d31a9b5326e`, independently source-reviewed PASS, and now awaits User local build/deployment + runtime acceptance.

Latest previously deployed diagnostic:

```text
Built SHA256 = 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
Live  SHA256 = 490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C
```

EV-380 pre-correction state envelope:

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

Implemented rule:

```text
origin SPRINT
current POWER  -> preserve SP1 or SP2
current SPRINT -> add SP2 only
```

Implementation SHA:

`4c85193f4efd31e789bc07d7e3c71d31a9b5326e`

Independent source review:

```text
PASS
one commit ahead of frozen parent
one production file changed
exact IsSecondFistAllowed / AttackFamily_Sprint branch only
```

Current source:

```cpp
return (currentFamily == AttackFamily_Power
        && (statePosition == 1 || statePosition == 2))
    || (currentFamily == AttackFamily_Sprint
        && statePosition == 2);
```

Protected behavior remains untouched by the implementation diff: first-FIST predicates, Power/Normal/Quick, immutable origin/identity, raw8, generic equipped, lifecycle, native cleanup, diagnostics and hooks.

Hard exclusions remain: no `>=1`; no Sprint/SP1; no Normal/SP0 change; no new hook/state/timer/species/name/file/DLL policy; no custom damage.

Active runtime-gated task:

`docs/work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_SP2_COMPATIBILITY_CORRECTION.md`

Next local runtime batch:

```text
1+3  SPRINT/SP2 marker2 must accept/rearm, no second physical opening
1+8  SPRINT/SP2 and POWER/SP2 marker2 outcomes must both accept/rearm
1+15 POWER/SP2 remains accepted/rearm
single-FIST Sprint unchanged
true-Power double unchanged
Normal/Quick controls unchanged
```

After that, separate controlled sheath question:

```text
marked Sprint: no sheath vs deliberate sheath
unmarked/native Sprint: no sheath vs same sheath timing
```

Use that to distinguish marker ownership from native/New Balance target/contact-state behavior.

Paused speed authority: `DESIGN.md` §3 + ADR-0004. Configured speed is base-speed authority; native/New Balance dynamic modifiers must remain composable.
