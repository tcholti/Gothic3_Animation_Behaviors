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

## Collision-twin state

Both collision twins compile the same shared behavior source. The diagnostic twin only adds diagnostic compilation/files.

```text
behavior SOURCE = current with shared behavior changes
behavior BINARY = NOT proven current unless rebuilt
```

Last recorded validated behavior SHA256 is still the pre-New-Balance standalone binary:

`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

Latest recorded diagnostic SHA256 after raw55 compatibility corrections:

`81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`

There is no post-compatibility behavior built/live hash on record. After the EV-385 correction and source review, build **both** twins and record both new hashes.

## Runtime-log context rule

`PROJECT_OPERATING_PROCEDURES.md` v1.19 now hard-requires bounded retrieval for every runtime log, regardless of size. Normal Chat should analyze through exact searches/counts and bounded event windows, retaining conclusions/provenance and only minimal supporting excerpts in Chat context. POP-07 remains the large-log specialization.

Immediate route:

```text
bounded Work implementation
-> independent Normal Chat review
-> build BOTH collision twins from same exact reviewed source
-> record behavior + diagnostic SHA256
-> deploy diagnostic twin / SHA + sole-live-twin verification
-> corrected standalone diagnostic sentinel:
   direct 1+3 SPRINT/SP1 second-marker retest
   one representative POWER/SP1 continuation control
   single-FIST SPRINT/SP1
   factual true-Power single/double
   unmarked raw55 native fallback
-> one SMALL diagnostic New Balance/raw55 regression
   preserve Sprint-origin SP2 / Action9->Action2 compatibility
-> deploy behavior twin ONLY / SHA + sole-live-twin verification
-> final diagnostics-free observational collision session
   include representative raw55/equipped/native traffic
   include several authored animations whose desired RIGHT collision exists only through G3AB marker behavior
-> if behavior-only PASS:
   production collision migration
   production integration validation
```

Do not run more tests on the pre-correction source. Do not treat the old behavior DLL hash as the final candidate.

EV-385 logs are already archived under POP-06 and `research/raw/` is back to `Keep.txt` only.