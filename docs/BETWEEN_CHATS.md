# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-286 CLOSED; RAW55 NORMAL PRE-STATE CONTACT-REARM PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-286**. No permanent raw55 implementation is authorized.

Current frozen diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_PRESTATE_REARM_PROBE.md`

Read in order:

1. `SESSION_ENTRYPOINT.md`
2. this file
3. `COLLISION_RAW55_NORMAL_PRESTATE_REARM_PROBE.md`
4. `EVIDENCE_LEDGER_286_ONWARD.md` — EV-286
5. EV-268 through EV-273 only as Quick precedent
6. EV-277 through EV-279 only as Normal first-contact precedent
7. `FEATURE_DEVELOPMENT_METHOD.md`
8. `WORK_IMPLEMENTATION_PROTOCOL.md`

## EV-286 — What the previous probe proved

Canonical runtime:

`research/raw/2026.09.15_troll_raw55_normal_prestate_fist.log`

SHA256:

`5E081A79BCB39280A738C5FBA97E6C4FF4E5DCFB22479FA8D8C16407AA7EC349`

Upload commit:

`1f336c04173983428e5e95a348207040c2fe9a14`

Diagnostic implementation:

`a99f4aa616c905c4eb66c72bdaa27709c9b75c77`

Representative factual Normal C1s 19, 21 and 23 all repeat:

```text
frame-1 FIST arrives at Action1 / NORMAL / StatePosition=0
RIGHT TrollFist/raw55 is group5
-> probe immediately requests exact RIGHT 5 -> 7
-> group7 verified
-> ClearTriggeredList=0
-> original _AI_Attack continues

around StateTime ~= 0.25:
    Gothic requests native 7 -> 7
    StatePosition 0 -> 1

frame-15 FIST later arrives at SP1 while RIGHT remains group7
    current Normal research path performs no repeat intervention

one later native ONDAMAGE occurs
native 7 -> 5 cleanup follows
C1 closes cleanly
```

In C1=19 the second marker is delivered around StateTime `0.604`, and the one damage event occurs later around `0.716`. No Normal damage occurs before the native `7 -> 7 / SP0 -> 1` transition. C1=21 and C1=23 show the same broad pattern.

The User ran the fixture three times and consistently observed one damaging contact per Normal attack even though the copied Quick animation geometry can visibly connect twice.

Therefore:

```text
frame-1 marker transport = PASS
SP0 marker-owned physical raw55 5 -> 7 opening = PASS
native Normal progression after early opening = PASS
native cleanup = PASS
first-swing early damage with ClearTriggeredList=0 = FAIL / absent
```

Do **not** describe the frame-1 marker as rejected. The remaining unknown is contact eligibility.

## Current frozen causal question

Change one variable only:

```text
existing eligible Normal SP0 FIST
-> exact RIGHT 5 -> 7
-> verify groupAfter == 7
-> call exact RIGHT TouchDamage.ClearTriggeredList() once
```

Then observe whether the first physical swing can damage **before** Gothic reaches its ordinary Normal `7 -> 7 / StatePosition 0 -> 1` transition.

The later frame-15 FIST remains observational only in this probe. Do not add Normal repeat rearm yet.

Interpretation:

- early damage before native transition -> triggered-list rearm is the missing first-contact primitive;
- still no damage until after native transition -> Normal has an additional state/timing eligibility gate; isolate that next;
- any callback/lifecycle/cleanup divergence -> stop and analyze, do not compensate.

## Remaining collision order

After this transaction closes:

1. finish Normal early-contact eligibility if another native gate exists;
2. non-Quick repeated-FIST semantics;
3. Sprint same-C1 Action9 -> Action2 continuity within repeated-marker design;
4. permanent raw55 architecture and implementation;
5. standalone final collision regression;
6. New Balance 0.7 final bundle regression exactly as distributed, bundled AttackCollision active;
7. close collision module;
8. begin Raise / speed-control work.

New Balance 0.7 is not a current blocker. Existing combined runtime evidence remains EV-035/EV-150/EV-242, with corrected compatibility interpretation EV-285.
