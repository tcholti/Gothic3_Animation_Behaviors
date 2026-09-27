# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **behavior-only release-purity collision validation CLOSED/PASS EV-389. Mature collision subsystem is ready for bounded production migration into `src/Script_G3AnimationBehaviors`.**

Reviewed behavior source:
`1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`

Final-candidate hashes:

```text
Behavior   D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78
Diagnostic AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
```

Closed final validation:

```text
EV-386 corrected marked standalone matrix PASS
EV-387 standalone unmarked raw55 native fallback PASS
EV-388 focused final-candidate New Balance/raw55 regression PASS
DIAGNOSTIC PHASE CLOSED/PASS

EV-389 behavior-only sole-live deployment:
  built/live behavior SHA exact match
  diagnostic twin absent
  startup smoke PASS

EV-389 observational release-purity session:
  authored/released animations follow marker timing
  Hack collision works
  2H ON -> OFF -> ON gives separate openings
  OFF negative control: weapon overlap during OFF produces no hit
  1H1H/dual multi-window marker patterns produce intended extra contacts
  human Fist double markers can hit twice
  Sabretooth raw8 double markers can hit twice
  Troll raw55 double markers can hit twice
  one-on-one + group combat: no observed stuck/persistent collision regression

BEHAVIOR-ONLY RELEASE-PURITY GATE = CLOSED/PASS
```

Immediate route:

```text
1. freeze one bounded production collision-migration task
2. migrate mature collision behavior into src/Script_G3AnimationBehaviors
3. diagnostics remain separate from shipping production code
4. preserve established collision semantics; migration is not a redesign opportunity
5. Work/source-only session must not build or run Gothic 3
6. User builds/tests locally at home after migration
7. production integration validation PASS -> collision migration closes
```

Current evidence ledger: `EVIDENCE_LEDGER_389_ONWARD.md`.  
Closed EV-384–EV-388 volume: `archive/evidence/EVIDENCE_LEDGER_384_388.md`.  
POP-06 remains mandatory for any future diagnostic runtime logs.