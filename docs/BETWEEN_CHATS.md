# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-423 directional Raise contradiction

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Collision, Speed core and Hack compatibility remain CLOSED/PASS. `main` frozen.

## New contradiction — EV-423

Rule-derived dual Raise assets worked:
```text
P0/P1 Fwd Normal Raise = selected + plays correctly
P0/P1 Quick R/L Raise = selected + plays correctly
P3 QuickL Raise = not observed; corresponding P3->P61 Hit also not observed
```

But directional Normal AddRaise is wrong:
```text
native Left Normal selected -> Left Raise plays -> following Hit becomes Fwd
native Right Normal selected -> Right Raise plays -> following Hit becomes Fwd
```

This is not an animation-name defect.

Static fact:
`sAICombatMoveInstr_Args` contains Self/Target/Action/Phase/AniSpeedScale only. No direction field exists. Current AttackRaise stores/replays that generic Action1 Hit after synthetic Raise, so the original Fwd/Left/Right selection identity is not carried by the stored request.

## Active responsibility

`docs/work/active/RAISE_NORMAL_DIRECTION_CONTINUATION_RESEARCH.md`

Prove:
```text
where Gothic stores/derives the factual Normal Fwd/Left/Right selection
what synthetic Raise changes/consumes
smallest way to preserve already-selected Hit across Raise
```

Protect:
```text
Hit-scale reuse / phase-speed correction
Quick factual Action4/5
Whirl AddRaise
Power Raise composition
Hack compatibility
Collision
New Balance ownership
```

Do not hard-code Left/Right filenames or implement from hypothesis.
