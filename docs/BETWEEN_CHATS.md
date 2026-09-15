# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-287 CLOSED; RAW55 NORMAL NATIVE REARM-SOURCE IMPLEMENTED + SOURCE-REVIEW PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-287**. No permanent raw55 implementation is authorized.

Current frozen diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_REARM_SOURCE_PROBE.md`

Current diagnostic implementation:

`6ca48c84e9fdf370ffdb824f9142e8ef0e267a7c`

Required implementation base:

`0aec52f2464c245f62d70077783ab78597952a11`

Normal Chat independently reviewed the Work commit and marked **SOURCE REVIEW PASS**.

The commit is exactly one commit ahead of the frozen base and changes exactly:

`prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp`

with 105 additions and no other source/build changes.

Build status remains **NOT ATTEMPTED**. Local build/deploy/runtime validation belongs to User + Normal Chat next session.

## EV-287 — What is already proven

Canonical runtime:

`research/raw/2026.09.15_troll_raw55_normal_prestate_rearm.log`

SHA256:

`73DB5D9ED77B6121FF01157A6973433CFCB7305C6911FA37AB80904D904C33C6`

Upload commit:

`06a9fb5875a3c78edc596638f3d019e3e3d87852`

Prior diagnostic implementation:

`50db909b414eb821b536cd68baa75efbf5589c1b`

Prior local build/live DLL SHA256:

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

The User ran the fixture twice and visibly observed Normal damaging twice in both runs, although positioning/timing was substantially harder than Quick.

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

## Current implementation under validation

The Work commit implements exactly the frozen one-variable probe.

Temporary `NormalPreStateFistIntervention` research state now records:

```text
preStateRearmProven
nativeRearmSuppressionUsed
```

`preStateRearmProven` is set only after the already-proven SP0 path has:

```text
opened exact RIGHT raw55 5 -> 7
verified groupAfter == 7
executed exact RIGHT TouchDamage.ClearTriggeredList()
```

The new suppression applies only to one factual nested Normal request satisfying all required ownership facts:

```text
active Normal callback scope
Action1 / NORMAL / Hit
same exact current RIGHT PhysicalFist/raw55
valid same actor + same C1 generation
matching proven Normal SP0 intervention
preStateRearmProven == true
requested group7
before/current group7
StatePosition == 0
nativeRearmSuppressionUsed == false
```

For that one request only, `PhysicalFistProbe` returns suppression before the underlying native `SetCollisionGroup(7)` call executes, then records the one-shot as used.

The original `_AI_Attack` callback remains enabled. No StatePosition write, marker-2 clear/rearm, damage call, cleanup intervention, EngineBridge change, header change or CMake change was added.

Diagnostic added:

`CORE RAW55_NORMAL_NATIVE_REARM_SUPPRESSION_PROBE`

with factual actor/C1/action/SP/time/RIGHT/use-type/requested/before/proof/suppression fields.

## Immediate next session — local validation only

1. User syncs branch through GitHub Desktop: Fetch origin -> Pull origin -> Fetch origin.
2. Confirm Changes is empty.
3. Build only `Script_FrameCollisionTest` Release.
4. STOP on the short build result.
5. If build passes, perform POP-03 deployment/hash/twin verification.
6. Perform POP-04 startup-banner verification.
7. Run the same Normal two-FIST Troll fixture.
8. Preserve the untouched raw log and close via POP-07/POP-06 if large.

Preferred raw artifact:

`research/raw/2026.09.16_troll_raw55_normal_native_rearm_source.log`

Decisive interpretation remains:

```text
first hit remains
+ native exact RIGHT 7 -> 7 suppression fires
+ original callback still advances SP0 -> 1
+ frame-15 FIST remains observational
+ second damage disappears
    => native 7 -> 7 setter request is causally required for the current implicit second-contact opportunity

second damage still occurs under the same conditions
    => native group setter itself is not the rearm source; isolate another callback/state/contact mechanism

first hit, SP progression, cleanup or lifecycle diverges
    => stop and analyze; do not compensate
```

No EV-288 exists yet. Do not promote an evidence conclusion until runtime closes the probe.

## Power observation from the same User test session

The User reports that prepared Power two-swing animations visibly damage on the first authored marker but do not rearm for a second hit. Treat this as useful behavioral guidance, not as a standalone causal EV from the Normal log.

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
