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

EV-436 authoring contract:

```text
inactive / Off
= preserve current live compatible stack unchanged

configured K
= selected animation filename movement × K

K=1.0
= selected animation's authored movement exactly
```

Desired surface uses the existing profile attack groups:
`Normal / Quick / Power / Pierce / Hack / SimpleWhirl / Whirl`.

With New Balance active, configured movement deliberately takes magnitude ownership back from New Balance while preserving final direction and native stopping behavior. Missing/inactive configuration remains the compatibility escape hatch.

Remaining architecture question:
capture/retain the native authored magnitude before New Balance replaces it, then safely reapply `authoredMagnitude * K` at the final CombatMove movement call.

Do not implement yet.

Protect Collision, Speed, Raise, New Balance and AttackCollision.
