# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-16

## Current Bridge — EV-289 CLOSED; RAW55 NORMAL NATIVE TRIGGER-CLEAR OBSERVATION FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-289**. No permanent raw55 implementation is authorized.

Current frozen diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_OBSERVATION_PROBE.md`

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

User runtime observation:

```text
both Normal swings damaged the player
no abnormal/stuck behavior reported
```

Representative factual Normal C1=11:

```text
frame-1 FIST at SP0 / StateTime ~= 0.058
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList
-> POST_PRESTATE_REARM:
     ResetOnUntouch=0
     VisitedSize=0
     PlayerPresent=0

first ONDAMAGE around ~= 0.204

change-only snapshot around ~= 0.213:
-> VisitedSize=1
-> VisitedCountSize=1
-> PlayerPresent=1
-> PlayerVisitCount=1

NATIVE_7TO7_SUPPRESS_PRE around ~= 0.259:
-> player still present/count1
-> ResetOnUntouch=0

existing EV-288 native 7 -> 7 setter suppression fires

same original _AI_Attack invocation:
-> StatePosition 0 -> 1 survives
-> RIGHT remains group7
-> SP0_TO1_POST_CALLBACK:
     ResetOnUntouch=0
     VisitedSize=0
     VisitedCountSize=0
     PlayerPresent=0

later callback can contain another visited entity while player remains absent

frame-15 FIST around ~= 0.600
-> LATER_FIST
-> RIGHT group7
-> PlayerPresent=0
-> no Normal marker-2 intervention

second ONDAMAGE around ~= 0.737

subsequent snapshot:
-> PlayerPresent=1
-> PlayerVisitCount=1

native exact RIGHT 7 -> 5 cleanup
clean C1 finalization
```

Therefore:

```text
hit 1 inserts PC_Hero into exact RIGHT trigger bookkeeping       PASS
player still visited immediately before native 7->7 suppression PASS
native 7->7 setter suppressed                                    PASS
visited bookkeeping resets during same native SP0->1 callback    PASS
ResetOnUntouch is enabled                                        NO — factual value is 0
reset occurs before marker 2                                     PASS
marker 2 owns reset                                              NO
hit 2 re-inserts PC_Hero                                         PASS
native cleanup / clean C1                                        PASS
```

The factual conclusion is narrow:

> Gothic performs another trigger-bookkeeping reset during the native Normal `SP0 -> 1` callback transition. That reset creates the current implicit second-contact opportunity before marker 2. The exact native operation is not yet identified.

Do **not** claim:

```text
StatePosition itself clears the trigger
ResetOnUntouch causes the reset
marker 2 causes the reset
native 7 -> 7 SetCollisionGroup causes the reset
```

Those explanations are either rejected or unproven.

## Static follow-up — exact clear API anchors

The tested binaries provide a direct next observation route:

```text
Script_Game.dll imports PSTouchDamage::ClearTriggeredList()

Script.dll:
PSTouchDamage::ClearTriggeredList() = +0x13720
```

Disassembly of that Script wrapper shows it resolves the underlying engine property set and tail-jumps to the engine clear API.

Tested Engine exports:

```text
eCTrigger_PS::ClearTriggeredList()          Engine + 0x7DDA0
eCTrigger_PS::ClearTriggeredList(eCEntity*) Engine + 0x7DDF0
```

The next probe observes both exact public engine clear functions for the exact RIGHT raw55 trigger. It logs PRE/POST visited state plus caller module/RVA and never suppresses or adds a clear.

## Current frozen question

During the proven EV-289 Normal C1, does either exact public `eCTrigger_PS::ClearTriggeredList` overload perform the post-hit-1 visited-state reset?

Decisive routes:

```text
public clear observed after hit1
+ PRE player present
+ POST player absent/reset
    => factual reset operation/caller identified

entity-specific clear(PC_Hero) observed
+ player entry removed
    => factual player-reset operation identified

known marker-owned initial clear observed
+ NO later exact public clear
+ EV-289 visited reset still occurs
    => public clear APIs ruled out; continue into lower/private trigger internals
```

This next task is still diagnostics-only observation. No clear suppression, marker-2 rearm or StatePosition intervention is authorized.

## Deployment-path correction

Canonical workstation authority is `LOCAL_WORKSTATION_PATHS.md`.

Use:

```text
live collision DLL directory:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic log directory:
E:\SteamLibrary\steamapps\common\Gothic 3
```

On 2026-09-16 Normal Chat accidentally supplied a deployment command that copied the DLL to the game root. The User corrected it manually before the EV-289 runtime test, so EV-289 is valid. The workstation path authority now explicitly says collision DLLs must never be deployed to the game root.

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
