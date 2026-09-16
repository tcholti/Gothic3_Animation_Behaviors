# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-16

## Current Bridge — EV-290 CLOSED; RAW55 NORMAL NATIVE TRIGGER-CLEAR SUPPRESSION PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-290**. No permanent raw55 implementation is authorized.

Current frozen diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`

Read in order:

1. `SESSION_ENTRYPOINT.md`
2. this file
3. `COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`
4. `EVIDENCE_LEDGER_286_ONWARD.md` — EV-286 through EV-290
5. `FEATURE_DEVELOPMENT_METHOD.md`
6. `WORK_IMPLEMENTATION_PROTOCOL.md`

## EV-290 — closed result

Canonical runtime:

`research/raw/2026.09.16_troll_raw55_normal_native_trigger_clear_observation.log`

SHA256:

`E699B807059189289D4CAB6B243F966F49947C9083656EE693B8FDD21676693F`

Upload commit:

`8b483b48636deeec4fa6863533da4a7db4fe2e15`

POP-07 package:

`research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_observation_large_log/`

Diagnostic implementation:

`6ef27121c5fcd1d4993b914e0f6a9a9123a2b0b7`

Independent Normal Chat source review: **PASS**

Local build/live DLL SHA256:

`A2E3C1B463AF804B4ABE9DA83F261009B3780995DAEEB1CB4E4D58A44EDFCB77`

User runtime observation:

```text
both Normal swings damaged the player
```

Representative factual Normal C1=3:

```text
frame-1 FIST at SP0 / StateTime ~= 0.042
-> exact RIGHT TrollFist raw55 5 -> 7
-> existing marker-owned ClearTriggeredList() ALL
   caller Script_FrameCollisionTest.dll + 0x14DB0
-> first damage opportunity enabled

first ONDAMAGE around callback StateTime ~= 0.204

StateTime ~= 0.212:
-> VisitedSize=1
-> VisitedCountSize=1
-> PlayerPresent=1
-> PlayerVisitCount=1

StateTime ~= 0.255:
-> player still present/count1
-> existing EV-288 exact native RIGHT 7 -> 7 setter suppression fires

same original _AI_Attack invocation:
-> Gothic calls exact public eCTrigger_PS::ClearTriggeredList() ALL
-> caller Script_Game.dll + 0x386C6
-> PRE:  player present/count1
-> POST: visited arrays empty / player absent

-> original callback completes StatePosition 0 -> 1
-> RIGHT remains group7

frame-15 FIST around ~= 0.604
-> marker remains observational
-> player already absent due to native clear

second ONDAMAGE around ~= 0.733
-> player is later observed inserted again

native exact RIGHT 7 -> 5 cleanup
clean C1 finalization
```

Therefore:

```text
native public ALL clear occurs after hit1                         PASS
exact clear target is current RIGHT raw55 trigger                 PASS
PRE contains PC_Hero / POST removes PC_Hero                       PASS
caller resolves to Script_Game.dll + 0x386C6                     PASS
native 7 -> 7 setter remains suppressed                          PASS
SP0 -> 1 progression survives                                    PASS
marker2 performs no Normal intervention                          PASS
second damage still occurs after native reset                    PASS
native cleanup / clean C1                                        PASS
```

The exact native bookkeeping-reset operation observed in EV-289 is now identified as:

```text
eCTrigger_PS::ClearTriggeredList()
ClearKind = ALL
Caller    = Script_Game.dll + 0x386C6
```

Static binary reference is consistent: `Script_Game.dll + 0x386C0` is the indirect call instruction and `+0x386C6` is the following return address. The `PSTouchDamage::ClearTriggeredList()` Script wrapper tail-jumps into the Engine clear, so the Engine hook preserves that Script_Game return address.

Do **not** infer from EV-290 alone that this clear is causally required for hit2. It performs the observed reset; necessity is the next causal question.

## Current frozen causal question

With all EV-290 behavior preserved, suppress only the exact post-hit1 native ALL clear:

```text
eCTrigger_PS::ClearTriggeredList()
Engine + 0x7DDA0
CallerModule = Script_Game.dll
CallerRVA    = 0x386C6
```

and ask whether the second same-C1 damage opportunity disappears.

Required factual suppression gates include:

```text
Normal / Action=Attack
valid same actor + C1 + exact current RIGHT raw55 source
RIGHT group7
matching NormalPreStateFistIntervention
preStateRearmProven == true
nativeRearmSuppressionUsed == true
StatePosition == 0
player factually present exactly once in aligned visited/count arrays
PlayerVisitCount >= 1
exact Script_Game.dll + 0x386C6 caller
suppression unused for this C1
```

Protected controls:

```text
marker-1 ClearTriggeredList executes normally
entity-specific ClearTriggeredList(eCEntity*) executes normally
all other ALL-clear callers execute normally
existing native 7 -> 7 setter suppression remains
marker2 remains observational
no direct array mutation
no new clear
no StatePosition write
auto/native cleanup remains untouched
```

### Decisive result routes

```text
exact native clear suppressed
+ player remains visited through SP0 -> 1 and marker2
+ first hit survives
+ second hit disappears
+ cleanup healthy
    => native ALL clear is causally required for implicit second opportunity
    => next one-variable test may give marker2 the replacement clear

exact native clear suppressed
+ player remains visited
+ second hit persists
    => another native trigger/contact mechanism remains causal

callback progression/source cleanup materially diverges
    => clear has additional relevant semantics; stop and isolate
```

## Routine POP-07 workflow — keep this concrete

For oversized diagnostic logs, the routine Windows workflow is:

```text
copy/keep the untouched full log in research/raw/
-> drag that .log file onto tools\log_evidence\Prepare-Log.cmd
-> helper creates/rebuilds research/derived/<basename>_large_log/
-> commit/push BOTH the untouched raw log and generated derived package
```

`Prepare-Log.cmd` is the normal route; no custom signal arguments are needed. The raw log remains canonical evidence. The generated package contains manifest/hash, event counts/timeline, signals and a complete line-numbered split mirror for connector-friendly retrieval. Full tool authority: `tools/log_evidence/README.md`.

## Deployment authority

Use `docs/LOCAL_WORKSTATION_PATHS.md`:

```text
live collision DLLs:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic logs:
E:\SteamLibrary\steamapps\common\Gothic 3
```

Never deploy the collision DLL to the game root.

## Power observation

The User reports that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. This remains behavioral guidance, not a separate causal EV.

## Remaining collision order

```text
Normal exact native clear necessity probe
-> if required, authored Normal marker-2 replacement/rearm proof
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

New Balance 0.7 is not a current blocker. Existing combined runtime evidence remains EV-035/EV-150/EV-242, with corrected compatibility interpretation EV-285.
