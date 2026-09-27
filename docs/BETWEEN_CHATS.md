# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **EV-385 correction implemented + independently reviewed PASS; both twins rebuilt; diagnostic deployment/startup PASS; corrected standalone runtime sentinel is next.**

Reviewed correction source:
`1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`

Exact rule:

```text
origin SPRINT second FIST:
  current POWER  -> SP1 or SP2
  current SPRINT -> SP1 or SP2
```

Independent review confirms the new `SPRINT/SP1` arm remains second-FIST clear-only:

```text
2 authored FIST
+ 1 prior accepted FIST
+ RIGHT already group7
-> RearmTriggeredContacts()
-> no second ActivateAttackSource()
```

Final-candidate twin hashes from the same reviewed source:

```text
Behavior SHA256:
D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78

Diagnostic SHA256:
AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
```

Diagnostic deployment state:

```text
sole live collision twin = Script_FrameCollisionTest.dll
built SHA == live SHA = AEF0E182...
startup CORE banner present
hooks installed
clean unload
DIAGNOSTIC DEPLOYMENT / STARTUP PASS
```

Immediate route:

```text
1. standalone/no-New-Balance BlackTroll raw55 double-FIST 1+3
   -> direct retest of EV-385 failure
   -> expect marker1 SPRINT/SP1 accepted/open
   -> expect marker2 same C1 SPRINT/SP1 accepted clear-only
   -> GroupRequested=0 / ClearTriggeredList=1 on marker2
   -> native cleanup group7->5 / Outstanding=0
2. one POWER/SP1 continuation control (1+8 OR 1+15)
3. single SPRINT/SP1 control
4. factual true-Power single + double
5. unmarked raw55 native fallback
6. one small New Balance/raw55 Sprint SP2 / Action9->Action2 regression
7. deploy behavior twin ONLY; verify behavior SHA above
8. final diagnostics-free observational collision session
9. behavior-only PASS -> production collision migration + integration validation
```

Runtime-log rule: POP-06 hard-requires bounded retrieval for every runtime log regardless of size. Do not load whole logs into Chat merely because they fit.

Exact acceptance details: `COLLISION_TEST_PLAN.md` §4.5–§4.6.  
Active runtime contract: `docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md`.  
EV-385 artifacts are archived; `research/raw/` is `Keep.txt` only.