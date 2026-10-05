# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-429 representative Raise closure

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
`main` remains frozen.

## Raise state

Raise pre-release representative validation is CLOSED/PASS through EV-429.

Accepted direction source:

`1da12cead5acfb54c5520a34d07bccc4c32fd64f`

Public AddRaise surface:
```text
Normal
Quick
Whirl
```

Representative structural coverage now includes:
```text
Normal Fwd
Normal Left/Right continuation
QuickAttackR
QuickAttackL
full Whirl
human weapon / dual / bare Fist
nonhuman None+Fist
Troll Fist+Fist
native Raise assets
user-authored Raise assets
native/configured timing including 0.1 controls
in-combat and out-of-combat fixture coverage where applicable
```

`SimpleWhirl` is separate and is not part of the public AddRaise surface.

EV-429 is **representative type/structure coverage**, not exhaustive proof for every animation asset, pose, actor family, weapon token combination or INI profile.

Newly runtime-proven authored Troll/Sabretooth Raise names are stored in:
`data/animation_names/user_created_tested_animation_names.txt`

Completed validation record:
`docs/archive/investigations/RAISE_PRE_RELEASE_VALIDATION.md`

## Protected state

```text
EV-423/EV-424 Normal direction defect = CLOSED
Raise sequencing = CLOSED/PASS
Raise phase-speed composition = CLOSED/PASS
representative AddRaise type matrix = CLOSED/PASS EV-429
Speed core = CLOSED/PASS
Hack compatibility = CLOSED/PASS
Collision = CLOSED/PASS
```

## Next

No Raise implementation or pre-release validation task is active.

Broader Raise testing should occur naturally as additional animation assets are authored/redesigned or when post-release contradictory evidence appears. Do not reopen Raise architecture merely because every individual Gothic 3 animation asset has not been tested.
