# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — final Speed + Raise source review handoff

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
`main` remains frozen.

## Current state

```text
Collision = CLOSED/PASS
Speed v2 = CLOSED/PASS
Raise = CLOSED/PASS / well tested through EV-430
production source checkpoint = d642f30bcb6b564deaaffed26fd11b763da88163
```

## Active responsibility

`docs/work/active/SPEED_RAISE_FINAL_SOURCE_REVIEW.md`

This is a **read-only independent final source review** before the repository release audit / main-promotion checkpoint.

It is intentionally smaller than the prior large Astra Speed+Raise audit. Re-check the integrated Speed/Raise ownership boundary, but focus heavily on the production delta since the prior audit baseline `d5d829e07eb2bfe8de428aa2ad148ba1f2d3835c`:

```text
AttackSpeed:
  Hack route-neutral CombatMove adapter
  underflow/fail-closed guard

EngineBridge:
  retirement of three caller-specific Hack speed hooks
  Hack CombatMove transport
  Normal direction GetAniName hook at Game+0x16B056

AttackRaise:
  continuation-owned exact native direction carry
```

`BehaviorProfiles` is unchanged but remains a dependency boundary that must be checked for correct integration.

Hard compatibility requirements:
```text
Jackydima New Balance
Script_AttackCollision
Collision non-interference
```

No source/docs edits, build, deploy, probes or runtime during this review.

## After PASS

Normal Chat + User:
1. consume/review the report;
2. perform a quick repository health/authority audit;
3. if clean, promote the accepted checkpoint to `main`;
4. return to `development`;
5. begin research on attack forward displacement / how far attacks may move the character, including New Balance's existing Normal/Quick changes.

Do not begin attack-displacement research before the release checkpoint is closed.
