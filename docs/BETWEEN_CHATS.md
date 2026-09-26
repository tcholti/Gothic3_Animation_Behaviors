# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-26

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **focused raw55 compatibility is CLOSED/PASS through EV-382.**

Runtime-confirmed raw55 compatibility corrections:

```text
6eb3e3ca96da55e89127c24d5f656e05610d315f
  true-Power first/second SP2
  Sprint-origin later current-Power SP2

ce59e5a2bad564652eaba970e959bdef0b479d82
  Sprint-origin first current-Sprint SP2

4c85193f4efd31e789bc07d7e3c71d31a9b5326e
  Sprint-origin second current-Sprint SP2

a31c66b97e45c27d0739b7df51252d33f490e7e1
  Normal second-FIST explicit SP0 or SP1
```

Latest runtime diagnostic built/live SHA256:

`81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`

EV-382 result:

```text
1+3:
  Normal marker2 SP0 accepted / clear-only / clean cleanup

1+8 decisive:
  marker1 Normal/SP0
  hit1
  marker2 still Normal/SP0
  marker2 accepted with ClearTriggeredList=1 / GroupRequested=0
  repeated runs show later hit2
  cleanup group5 / Outstanding=0

1+15:
  clean later-placement control
  current New Balance timing commonly still leaves Normal marker2 at SP0

all 3 logs:
  zero CORE MARKER ANOMALY / DISCOVERY
  Quick/Power/Sprint controls healthy
```

SP1 remains explicitly supported and was already runtime-proven in the earlier Normal causal campaign; EV-382 adds the missing SP0 proof.

No active focused raw55 Work task remains. The completed Normal task and the three test3 logs are archived during EV-382 closure maintenance; `research/raw/` should contain only `Keep.txt`.

Next gate:

```text
broader representative/full-stack New Balance compatibility
-> standalone/no-New-Balance post-compat raw55 sentinel
-> production collision migration + diagnostics-free integration validation
```

Do not reopen focused raw55 behavior without contradictory evidence.

Paused speed authority: `DESIGN.md` §3 + ADR-0004. Configured speed is base-speed authority; native/New Balance dynamic modifiers must remain composable.