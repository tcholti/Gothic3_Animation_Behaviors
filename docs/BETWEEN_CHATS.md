# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **standalone/no-New-Balance post-compat raw55 sentinel = PARTIAL FAIL EV-385; bounded correction is frozen before further runtime testing.**

Closed compatibility background:

```text
focused raw55 New Balance compatibility = CLOSED/PASS EV-376–EV-382
New Balance intended full-stack compatibility = CLOSED/PASS EV-384
```

EV-385 batch:

```text
standalone/no-New-Balance BlackTroll raw55

1+3 double FIST:
  four distinct Sprint-origin C1s repeat:
  first marker  SPRINT/SP1 -> ACCEPTED / RIGHT 5 -> 7
  second marker SPRINT/SP1 -> REJECTED_UNSUPPORTED_HIT
  marker2 does not ClearTriggeredList
  native cleanup remains healthy -> group5 / Outstanding=0

1+8 and 1+15 double FIST:
  zero marker anomalies
  first marker SPRINT/SP1 -> ACCEPTED/open
  second marker same Sprint-origin C1 after transition -> POWER/SP1
  -> ACCEPTED clear-only / GroupRequested=0 / ClearTriggeredList=1
  -> clean cleanup

single marker:
  zero anomalies
  SPRINT/SP1 accepted/open/clean cleanup

all four logs:
  no C1 invariant warning
  no terminal C1 repair anomaly
```

The exact compatibility hole is therefore current-SPRINT/SP1 **second** FIST only. Current source already accepts current POWER/SP1+SP2 and current SPRINT/SP2 for the same Sprint-origin second-FIST ownership.

Frozen correction:

```text
PhysicalFistCollision::IsSecondFistAllowed()
origin SPRINT:
  current POWER  -> explicit SP1 or SP2 (unchanged)
  current SPRINT -> explicit SP1 or SP2 (add SP1)
```

Do not use generic `>=1` and do not change first-FIST rules, hooks, damage ownership, cleanup, Normal/Quick/Power, or any other collision policy.

Active Work task:

`docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md`

Immediate route:

```text
bounded Work implementation
-> independent Normal Chat review
-> build both collision twins
-> deploy diagnostic twin / SHA + sole-live-twin verification
-> direct standalone 1+3 acceptance retest
-> preserve 1+8/1+15 + single Sprint controls
-> bounded New Balance Sprint SP2/transition regression because source changed after EV-384
-> finish factual true-Power single/double + unmarked raw55 fallback sentinel controls
-> only then production collision migration if final sentinel passes
```

Do not run more tests on the pre-correction source.

EV-385 logs are to be archived during POP-06 closure; `research/raw/` must return to `Keep.txt` only before the task handoff is considered clean.