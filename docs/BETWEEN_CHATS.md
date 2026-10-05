# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-427 Normal direction closure

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
`main` remains frozen.

## Current closure

Collision, Speed v2, Raise phase-speed/Hack compatibility and the Normal AddRaise direction correction are CLOSED/PASS through EV-427.

Accepted Normal direction mechanism:

```text
pending Normal synthetic Raise
-> Gothic selects native Fwd/Left/Right
-> capture exact direction bCString + current gEDirection at Game+0x16B056
-> stored Action1 Hit
-> restore same gEDirection + reuse same direction bCString
-> Gothic GetAniName resolves Hit normally
```

Production direction source:

`1da12cead5acfb54c5520a34d07bccc4c32fd64f`

EV-426 source review:
```text
PASS
blocker 0
major 0
minor 0
```

EV-427 local result:
```text
build PASS
deployment PASS
runtime PASS
Normal Fwd   -> Fwd Raise   -> Fwd Hit
Normal Left  -> Left Raise  -> Left Hit
Normal Right -> Right Raise -> Right Hit
frozen 1H / dual-wield / Quick / Whirl / interruption controls reported working
```

Exact built/live SHA256 values were not transcribed into Chat and are not asserted as evidence.

## Durable owners

```text
DESIGN.md
SOURCE_HOOK_GUIDE.md
EVIDENCE_INDEX.md
EVIDENCE_LEDGER_417_ONWARD.md
docs/archive/investigations/RAISE_NORMAL_DIRECTION_CONTINUATION_IMPLEMENTATION.md
docs/archive/investigations/RAISE_NORMAL_DIRECTION_CONTINUATION_RESEARCH.md
```

## Next

No Raise-direction implementation task remains active.

User + Normal Chat should select/freeze the next engineering responsibility from the current project state. Do not reopen EV-423/EV-424 direction work absent contradictory evidence.
