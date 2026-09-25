# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-25

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: New Balance full-stack compatibility remains open. The first bounded raw55 SP2 correction in `6eb3e3ca96da55e89127c24d5f656e05610d315f` passed independent static review and runtime-confirmed every predicate it changed, but EV-378 exposed one additional exact Sprint-first SP2 case that was outside the task's frozen evidence basis.

First correction task: **CLOSED** and archived at:

`docs/archive/investigations/COLLISION_NEW_BALANCE_RAW55_SP2_COMPATIBILITY_CORRECTION.md`

Runtime candidate/deployment:

```text
source correction = 6eb3e3ca96da55e89127c24d5f656e05610d315f
built SHA256 = E11D680590D2F9D87A50EAF64B642F70C8CECA019ABB651DC48B00AF01F37C74
live  SHA256 = E11D680590D2F9D87A50EAF64B642F70C8CECA019ABB651DC48B00AF01F37C74
```

EV-378 result:

```text
PASS within first correction scope:
  true Power single-FIST first/only marker at SP2 -> ACCEPTED, 5->7, native cleanup
  true Power double-FIST marker2 at SP2 -> ACCEPTED, clear-only rearm
  Sprint-origin double-FIST marker1 Action9/SP1 -> ACCEPTED/open
  same-C1 marker2 current Action2/Power/SP2 -> ACCEPTED, clear-only rearm
  Normal/Quick raw55 controls -> healthy

NEW reduced contradiction:
  Sprint-origin single-FIST
  current factual family = SPRINT / Action9
  first/only FIST can arrive at SP2
  earlyOpeningSuppressed = true
  group is still 5
  unchanged Sprint-first SP1-only predicate rejects it
```

The double-marker log contains no CORE marker anomaly. The single-marker anomaly records reviewed are the same Sprint-first/SP2 class. This supersedes the EV-376/EV-377 assumption that observed Sprint-origin first markers were always SP1.

Likely smallest follow-up question:

```text
Sprint-origin FIRST FIST only:
  keep current family = SPRINT / Action9
  keep earlyOpeningSuppressed mandatory
  preserve SP1
  additionally accept explicit SP2

Everything else remains unchanged.
```

Do not generalize to `StatePosition >= 1`, add authored-count branching, species/name rules, filename inference, New Balance/DLL detection, hooks, state, timers/polling, custom damage, cleanup changes, or neighboring-system edits unless new evidence requires them.

Runtime batch hygiene: both EV-378 logs are archived byte-identically under `research/archive/`; `research/raw/` should again contain only `Keep.txt`.

Next responsibility: promote EV-378/current-state docs, validate knowledge state, then freeze a new tiny follow-up Work task only after Normal Chat design disposition.
