# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-16

## Current Bridge — EV-289 CLOSED; RAW55 NORMAL NATIVE TRIGGER-CLEAR OBSERVATION IMPLEMENTED + SOURCE-REVIEW PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-289**. No permanent raw55 implementation is authorized.

Current diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_OBSERVATION_PROBE.md`

Current diagnostic implementation:

`6ef27121c5fcd1d4993b914e0f6a9a9123a2b0b7`

Required implementation base:

`1e411056a586b71217a1f5941774b44e16e6588e`

Normal Chat independently reviewed the Work commit and marked **SOURCE REVIEW PASS**.

The implementation is exactly one commit ahead of the frozen base and changes only:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.cpp        +47 / -0
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp   +180 / -0
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h     +17 / -0
```

No CMake or production module changed.

The source review confirmed:

- both new hooks exist only under `FRAME_COLLISION_DIAGNOSTICS`;
- hook ownership remains in `EngineBridge`;
- exact eligibility/interpretation remains in `PhysicalFistProbe`;
- exact Engine anchors are `0x7DDA0` and `0x7DDF0`;
- both use the project's explicit `.ThisCall()` transport pattern;
- each hook records PRE, calls the original function exactly once, then records POST;
- caller address is captured before entering probe logic;
- the known marker-1 clear can be observed factually before `preStateRearmProven` becomes true because the intervention identity already exists, while actor/C1/exact-RIGHT/PhysicalFist eligibility remains enforced;
- no new clear, suppression, collision-group mutation, StatePosition write, damage dispatch, cleanup/repair change, polling or production behavior was added.

Build status remains **NOT ATTEMPTED**. Local build/deploy/runtime validation belongs to User + Normal Chat next.

Read in order:

1. `SESSION_ENTRYPOINT.md`
2. this file
3. `COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_OBSERVATION_PROBE.md`
4. `EVIDENCE_LEDGER_286_ONWARD.md` — EV-286 through EV-289
5. `FEATURE_DEVELOPMENT_METHOD.md`
6. `WORK_IMPLEMENTATION_PROTOCOL.md`

## EV-289 — closed result

Canonical runtime:

`research/raw/2026.09.16_troll_raw55_normal_trigger_state_observation.log`

SHA256:

`978817C03EE01EA3098D265CFE85544F4D3DE06019279AD04C337C4ADBE00D08`

Upload commit:

`f486da9cf48e10d06b7c7040f3393b1d9a54cd52`

Diagnostic implementation:

`ec20e769a347bd206577427bfd28a85bd51a79b3`

Local build/live DLL SHA256:

`D336619855E4812EA950797057D57BC44D41F141DA244D209880793C0ED69367`

Representative factual Normal C1=11:

```text
marker 1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList
-> visited state empty

hit 1
-> PC_Hero enters visited state / count1

immediately before native 7 -> 7 suppression
-> PC_Hero still visited
-> ResetOnUntouch=0

native 7 -> 7 setter suppressed
-> original _AI_Attack continues
-> SP0 -> 1 survives
-> visited state becomes empty during that callback

marker 2 later
-> PC_Hero already absent
-> no Normal marker-2 intervention

hit 2
-> PC_Hero enters visited state again

native exact RIGHT 7 -> 5 cleanup
clean C1 finalization
```

The User observed both Normal swings damaging the player.

Therefore Gothic supplies an implicit trigger-bookkeeping reset before marker 2. The exact native operation remains unknown. Do not attribute that reset to marker 2, the suppressed `7 -> 7` setter, `ResetOnUntouch`, or StatePosition itself.

## Current implemented probe under local validation

The probe observes the two exact public Engine clear APIs:

```text
eCTrigger_PS::ClearTriggeredList()          Engine + 0x7DDA0
eCTrigger_PS::ClearTriggeredList(eCEntity*) Engine + 0x7DDF0
```

For exact current Normal actor + C1 + RIGHT PhysicalFist/raw55 identity it records:

```text
Boundary=PRE|POST
ClearKind=ALL|ENTITY
ResetOnUntouch
VisitedSize / VisitedCountSize
PlayerResolved / PlayerPresent / PlayerEntryCount / PlayerVisitCount
CountsAligned
argument entity + ArgumentIsPlayer for ENTITY form
CallerResolved / CallerModule / CallerRVA / CallerAddress
PreStateRearmProven
Native7To7SuppressionUsed
```

The original clear always executes exactly once. The probe never suppresses or adds a clear.

### Decisive runtime interpretations

```text
later public clear observed after hit 1
+ PRE player present
+ POST player absent/reset
    => factual public reset operation and caller identified

ENTITY clear with PC_Hero observed
+ player removed
    => factual player-specific reset operation identified

known marker-1 clear observed
+ no later public clear
+ EV-289 reset still occurs
    => public clear APIs ruled out; inspect lower/private trigger internals
```

## Immediate next step — local validation only

1. User syncs the branch in GitHub Desktop: **Fetch origin -> Pull origin -> Fetch origin**.
2. Confirm **Changes is empty**.
3. Build only `Script_FrameCollisionTest` Release.
4. STOP on the short build result.
5. If build passes, perform POP-03 deployment/hash/twin verification.
6. Deploy the DLL only to:
   `E:\SteamLibrary\steamapps\common\Gothic 3\scripts`
7. Perform POP-04 startup-banner verification.
8. Run the same Normal two-FIST Troll fixture.
9. Preserve the untouched diagnostic log from the game root and close through POP-07/POP-06 if large.

Preferred raw artifact:

`research/raw/2026.09.16_troll_raw55_normal_trigger_clear_observation.log`

No EV-290 exists yet. Do not promote a conclusion until runtime closure.

## Power observation

The User reports that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. Keep this as behavioral guidance only until Normal second-contact ownership is fully separated from Gothic's implicit native reset.

## Remaining collision order

```text
Normal exact native trigger-clear observation
-> if a public clear is identified, test necessity only if needed for authored ownership
-> establish authored Normal marker-2 ownership
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

New Balance 0.7 is not a current blocker. Existing combined runtime evidence remains EV-035/EV-150/EV-242, with corrected compatibility interpretation EV-285.
