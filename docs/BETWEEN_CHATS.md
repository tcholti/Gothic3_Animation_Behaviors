# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-06 — EV-447 stable promotion / final pre-release fix

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

Stable branch:
`main @ e899f37092706a9846312b93d6b52b34e715b53d`

Active branch:
`development`

## First-release stable baseline

EV-446 release-integration review PASS.  
EV-447 fast-forward promotion to `main` PASS.

Stable accepted features:
- Collision;
- Speed;
- Raise;
- absolute attack Movement through EV-445.

At the promotion moment, `main` and `development` were identical.

## Current development responsibility

Only one planned behavior fix remains before first public release:

`docs/work/active/BAD_BLOCK_SKIP_ATTACK_DEFER_TIMER_RESEARCH.md`

User goal:
```text
when bad-block-skip defer is counting down
+ the relevant actor attacks
-> pause countdown

when attack ends
-> resume from remaining defer time
```

Current task is READ-ONLY research.

Important:
- exact source owner/timer variable has not been assumed from remembered terminology;
- locate and prove the current lifecycle first;
- prefer an already-existing attack-state signal;
- no new hook unless evidence proves unavoidable;
- no implementation/build/runtime in the research task;
- Collision / Speed / Raise / Movement remain protected.

Release rule:
- if research yields a small clean fix, freeze a bounded implementation;
- if not clean enough, `main @ e899f370...` is the stable release fallback;
- no other new features before first release.
