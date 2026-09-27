# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **EV-385 correction implemented and independently source-reviewed PASS; runtime validation is next.**

Reviewed correction source:

`1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`

Exact implemented rule:

```text
origin SPRINT second FIST:
  current POWER  -> SP1 or SP2
  current SPRINT -> SP1 or SP2
```

Independent review confirms the added `SPRINT/SP1` arm still enters only the existing second-FIST clear-only branch:

```text
2 authored FIST markers
+ 1 prior accepted FIST
+ RIGHT already group7
-> RearmTriggeredContacts()
-> no second ActivateAttackSource()
```

No neighboring family, first-FIST, hook, lifecycle, cleanup or diagnostic behavior changed.

Collision-twin state:

```text
both twins compile the same shared behavior source
behavior source candidate = current at 1c45e5e...
behavior binary = stale/unverified until rebuilt
```

Last recorded behavior SHA256 is pre-compatibility:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

Latest recorded diagnostic SHA256 before this correction:
`81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`

Immediate route:

```text
sync local branch
-> build BOTH twins from reviewed final source
-> record both hashes
-> deploy diagnostic twin
-> corrected standalone sentinel:
   1+3 direct SPRINT/SP1 retest
   one POWER/SP1 continuation control
   single SPRINT/SP1
   true-Power single/double
   unmarked raw55 fallback
-> one small diagnostic New Balance/raw55 Sprint SP2/transition regression
-> deploy behavior twin ONLY
-> final diagnostics-free observational session:
   representative raw55/equipped/native
   several animations whose desired RIGHT collision exists only through G3AB markers
-> behavior-only PASS
-> production collision migration + integration validation
```

Runtime-log rule: `PROJECT_OPERATING_PROCEDURES.md` v1.19 / POP-06 hard-requires bounded retrieval for every runtime log regardless of size; keep whole log bodies out of Chat context unless a concrete exceptional reason requires incremental full-source reading.

Exact acceptance details: `COLLISION_TEST_PLAN.md` §4.5–§4.6.  
Active runtime contract: `docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md`.  
EV-385 artifacts are archived; `research/raw/` is `Keep.txt` only.