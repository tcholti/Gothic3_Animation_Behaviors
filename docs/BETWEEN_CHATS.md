# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-26

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: focused raw55 Sprint compatibility is CLOSED/PASS through EV-381. The Normal raw55 second-FIST SP0 correction is implemented at `a31c66b97e45c27d0739b7df51252d33f490e7e1`, independently reviewed PASS, and now runtime accepted by the 2026-09-26 `1+3`, `1+8`, and `1+15` BlackTroll mixed-attack fixtures.

Runtime diagnostic built/live SHA256:

`81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`

Accepted Normal second-FIST rule:

```cpp
case AttackFamily_Normal:
    return currentFamily == AttackFamily_Normal
        && (statePosition == 0 || statePosition == 1);
```

Runtime result:

```text
1+3:
  marker2 NORMAL/SP0 accepted
  ClearTriggeredList=1
  GroupRequested=0
  clean native 7->5 cleanup

1+8 decisive route:
  marker1 NORMAL/SP0
  hit1 ONDAMAGE
  marker2 still NORMAL/SP0
  marker2 accepted / clear-only rearm
  repeated examples produce later hit2
  cleanup Outstanding=0

1+15:
  later-placement control remains clean
  current New Balance timing commonly still places marker2 at SP0
  no marker anomalies
```

All three logs contain zero `CORE MARKER ANOMALY / DISCOVERY` records. Quick, Power, and Sprint controls remain healthy.

The older SP1 route remains supported because the implementation is additive and SP1 was already runtime-proven in the earlier Normal causal campaign.

Disposition: **Normal `{SP0,SP1}` correction PASS; focused raw55 Normal/Quick/Power/Sprint-origin compatibility CLOSED/PASS for the tested New Balance route.**

The three test3 logs and completed task are being archived byte-identically / as closed investigation during EV-382 maintenance. `research/raw/` should return to `Keep.txt` only.

Next gate after EV-382 canonicalization:

```text
broader representative/full-stack New Balance compatibility
-> standalone/no-New-Balance post-compat raw55 sentinel
-> production collision migration
```

No further focused raw55 source change is currently indicated.

Paused speed authority: `DESIGN.md` §3 + ADR-0004. Configured speed is base-speed authority; native/New Balance dynamic modifiers must remain composable.