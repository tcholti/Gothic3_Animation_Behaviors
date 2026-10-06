# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-06 — EV-448 bad-block research deferred / first release next

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

Stable release branch:
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

## Final pre-release timer research — CLOSED / DEFERRED

EV-448 result:
**NOT CLEAN ENOUGH FOR FIRST RELEASE for exact remaining-time pause.**

Recovered player seam:
```text
Script_Game +0x633BF DurationPressedMSecs getter
+0x633C5 compare 2500
+0x633CA jbe bypass
otherwise:
+0x633F1 FullStop
+0x63409 SetState PS_Melee_Loop
```

A one-hook stateless player adapter could **defer** this destructive branch during a factual attack, but native held time would continue advancing. It is not exact pause/resume.

Recovered NPC Alternative-AI timeout:
```text
non-player OnAI_Parade
StatePosition == 1
StateTime > 2.0
-> +0x46F39 StopAIGoto
-> +0x46F51 SetState ZS_Attack_Loop
```

Player and NPC use different clocks and different branches. NPC timeout overlapping a factual active attack remains unproven.

Exact pause requires a new stateful virtual-clock lifecycle whose timer episode/reset and attack interval boundaries are not proven. It is parked for post-release work.

Durable routes:
- `docs/SOURCE_HOOK_GUIDE.md §6`
- `docs/archive/investigations/bad_block_skip_static_research_2026-10-06.md`
- `docs/archive/investigations/BAD_BLOCK_SKIP_ATTACK_DEFER_TIMER_RESEARCH.md`
- `docs/FUTURE_INVESTIGATIONS.md §3`

## Next

Do **not** implement the timer fix for v1.

Next session:
**perform final first-release preparation / release audit from stable `main`.**

No active behavior feature task remains before first release.
