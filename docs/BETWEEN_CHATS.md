# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-287 CLOSED; RAW55 NORMAL NATIVE REARM-SOURCE PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-287**. No permanent raw55 implementation is authorized.

Current frozen diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_REARM_SOURCE_PROBE.md`

Read in order:

1. `SESSION_ENTRYPOINT.md`
2. this file
3. `COLLISION_RAW55_NORMAL_NATIVE_REARM_SOURCE_PROBE.md`
4. `EVIDENCE_LEDGER_286_ONWARD.md` — EV-286 and EV-287
5. EV-268 through EV-273 only as Quick precedent
6. EV-274 through EV-282 only as Power/Normal/Sprint first-contact precedent
7. `FEATURE_DEVELOPMENT_METHOD.md`
8. `WORK_IMPLEMENTATION_PROTOCOL.md`

## EV-287 — What is now proven

Canonical runtime:

`research/raw/2026.09.15_troll_raw55_normal_prestate_rearm.log`

SHA256:

`73DB5D9ED77B6121FF01157A6973433CFCB7305C6911FA37AB80904D904C33C6`

Upload commit:

`06a9fb5875a3c78edc596638f3d019e3e3d87852`

Diagnostic implementation:

`50db909b414eb821b536cd68baa75efbf5589c1b`

Local build/live DLL SHA256:

`627BADF62B1B4DA62781DFEF2625D760D83C63DC95E4F17FEE87264F456B5068`

Factual Normal C1=3 proves:

```text
frame-1 FIST at SP0 / StateTime ~= 0.042
-> exact RIGHT TrollFist raw55 5 -> 7
-> ClearTriggeredList=1 / PRESTATE_REARM=1

first native ONDAMAGE around StateTime ~= 0.188
while StatePosition is still 0

later Gothic native Normal threshold around ~= 0.257
-> exact RIGHT request 7 -> 7
-> StatePosition 0 -> 1

frame-15 FIST around ~= 0.603
-> transported at SP1 while RIGHT remains group7
-> current Normal code performs NO marker-2 intervention

second native ONDAMAGE around ~= 0.723

native exact RIGHT 7 -> 5 cleanup
clean C1 finalization
```

The User ran the fixture twice and visibly observed Normal damaging twice in both runs, although the positioning/timing was much harder than Quick.

Therefore:

```text
Normal frame-1 marker transport                    PASS
Normal SP0 exact-source 5 -> 7 opening             PASS
Normal SP0 ClearTriggeredList first-contact rearm  PASS
first damage before native SP0 -> 1                PASS
second same-C1 damage                              OBSERVED/PASS
marker-2 ownership of that second damage           NOT PROVEN
native cleanup                                     PASS
```

Do not claim that Normal marker 2 already owns the second hit. Current Normal code does nothing at marker 2.

## Current frozen causal question

The strongest remaining candidate for the second opportunity is Gothic's native exact RIGHT `7 -> 7` setter request, because it occurs **after the first contact** and before marker 2.

Test one variable only:

```text
proven Normal SP0 marker path remains unchanged:
    frame-1 FIST -> 5 -> 7 -> ClearTriggeredList -> first hit

then, inside the same factual Normal C1:
    native exact RIGHT request 7 -> 7 at SP0
    -> suppress ONLY that setter request once
    -> original _AI_Attack callback continues
    -> StatePosition must still advance 0 -> 1

frame-15 FIST:
    observational only
    no marker-2 clear/rearm yet
```

Interpretation:

- first hit remains, native `7 -> 7` is suppressed, SP0->1 survives, second hit disappears -> native setter is the current implicit second rearm source;
- second hit still occurs -> native setter itself is not the rearm source; isolate another native callback/state/contact mechanism;
- callback/state/cleanup divergence -> stop and analyze, do not compensate.

## Power observation from the same User test session

The User reports that prepared Power two-swing animations visibly damage on the first authored marker but do not rearm for a second hit. Treat this as useful behavioral guidance, not as a new standalone causal proof from the Normal log.

It is consistent with the current evidence model:

```text
Power native timer/SP transition occurs BEFORE marker 1
marker 1 later opens raw55 and can damage
no later native transition follows first contact
marker 2 therefore lacks another contact opportunity
```

Do not launch Power repeat-rearm work until the current Normal native-rearm-source question is closed, because the answer determines whether permanent authored-marker ownership must explicitly neutralize a native Normal rearm side effect.

## Remaining collision order

After this transaction closes:

1. make Normal second-contact ownership authored-marker-causal if the native timer currently supplies it;
2. Power repeated-FIST rearm;
3. Sprint repeated-FIST rearm with same-C1 Action9 -> Action2 continuity preserved;
4. permanent raw55 architecture and implementation;
5. standalone final collision regression;
6. New Balance 0.7 final bundle regression exactly as distributed, bundled AttackCollision active;
7. close collision module;
8. begin Raise / speed-control work.

New Balance 0.7 is not a current blocker. Existing combined runtime evidence remains EV-035/EV-150/EV-242, with corrected compatibility interpretation EV-285.
