# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-435 displacement architecture semantics

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains the promoted Collision + Speed + Raise baseline through EV-433.

## Established displacement mechanism

EV-434:
```text
selected animation filename movement field -> native CombatMove velocity
Game+0x16B8A3 = native magnitude scale
Game+0x16B8A9 = project-pinned New Balance movement replacement
Game+0x16B8B7 = final CombatMove movement call
speed changes commanded velocity; nominal distance remains chosen movement value
```

EV-435:
```text
ordinary attack Hit carries the nonzero movement value
Raise/Recover are normally 0
movement occurs during the value-carrying phase
combat movement preserves native ledge/obstacle/target stopping
renaming the animation is not a practical control because packed resource
precedence makes replacement/repacking necessary
```

The proposed runtime re-proof probe was cancelled before implementation as redundant.

## Active responsibility

`docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RESEARCH.md`

Current architecture decision:

```text
Off = preserve current live compatible stack unchanged

configured 1.0 semantics remain to freeze:
- preserve final compatible (including New Balance), or
- restore selected animation-authored filename movement, or
- expose an explicit distinction
```

Do not implement until this authoring contract is decided.

Protect Collision, Speed, Raise, New Balance and AttackCollision.
