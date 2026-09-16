# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-16

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Routine oversized-log preparation is drag-and-drop onto `tools\log_evidence\Prepare-Log.cmd`; preserve/commit the untouched source artifact and generated derived package. After evidence closure, processed source artifacts move unchanged from `research/raw/` to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current probe authority: `docs/COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`  
Latest canonical evidence: through **EV-290** in `docs/EVIDENCE_LEDGER_286_ONWARD.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      SP1 first-contact CLOSED/PASS through EV-279
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED — EV-283
raw55 Normal SP0 physical opening CLOSED/PASS — EV-286
raw55 Normal SP0 contact rearm / early first damage CLOSED/PASS — EV-287
raw55 Normal native 7->7 setter as second-rearm source REJECTED — EV-288
raw55 Normal native trigger-bookkeeping reset before marker2 CONFIRMED — EV-289
raw55 Normal exact native public ALL-clear reset operation IDENTIFIED — EV-290
```

Current diagnostic implementation:

`2839c8c271fa240b81ce5ccd203c34058870a5bb`

Required implementation base:

`23400f2b5b3afdbe8c03088be01aa4bc969849db`

Independent Normal Chat source review:

**PASS**

Build status:

**NOT ATTEMPTED** after the new implementation.

## Current factual model

EV-290 established:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7 + marker-owned ClearTriggeredList
-> first damage
-> PC_Hero becomes visited/count1

later native transition
-> existing native 7 -> 7 setter suppression fires
-> PC_Hero still visited
-> Gothic calls eCTrigger_PS::ClearTriggeredList() ALL
   caller Script_Game.dll + 0x386C6
   PRE player present/count1
   POST arrays empty/player absent
-> original _AI_Attack completes SP0 -> 1

marker2 later
-> observational only
-> second damage occurs
-> native 7 -> 5 cleanup / clean C1
```

EV-290 identifies the reset operation but does **not** yet prove that it is causally required for hit2.

## Current causal probe

The source-reviewed probe suppresses exactly once the native no-argument ALL clear from:

```text
Engine + 0x7DDA0
CallerModule = Script_Game.dll
CallerRVA    = 0x386C6
```

only for the exact proven Normal actor/C1/current RIGHT raw55 trigger after hit1 has factually inserted `PC_Hero`.

Protected controls remain unchanged:

```text
marker1 authored clear executes normally
entity-specific clear executes normally
unrelated ALL clears execute normally
existing native 7 -> 7 setter suppression remains
marker2 remains observational
no direct visited-array mutation
no new clear
no StatePosition write
no direct damage
native cleanup unchanged
```

## Immediate next step — local validation only

Do not launch another Work task.

```text
GitHub Desktop: Fetch origin -> Pull origin -> Fetch origin
-> confirm Changes empty
-> build Script_FrameCollisionTest Release only
-> STOP on build result
-> if PASS: deploy/hash/twin verification
-> DLL only to E:\SteamLibrary\steamapps\common\Gothic 3\scripts
-> startup-banner verification
-> same Normal two-FIST Troll runtime
-> note first-hit / second-hit / abnormal behavior
-> preserve new runtime log under a newly frozen filename
-> if large: drag raw log onto tools\log_evidence\Prepare-Log.cmd
-> commit/push raw + derived package
-> close next EV before advancing
```

## Retrieval discipline

Do **not** enumerate or scan large evidence directories to recover context. `research/raw/` is active intake, not project history; at the EV-290 maintenance boundary it contains only `Keep.txt`.

Use in this order:

1. this file;
2. `BETWEEN_CHATS.md`;
3. current suppression-probe contract;
4. EV-290 in `EVIDENCE_LEDGER_286_ONWARD.md`;
5. exact derived/archive evidence only if a concrete fact needs verification.

EV-290 preferred exact-runtime retrieval:

```text
research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_observation_large_log/
```

Canonical full source provenance is now archived unchanged:

```text
research/archive/2026.09.16_troll_raw55_normal_native_trigger_clear_observation.log
```

Historical EV rows that still spell the former `research/raw/<basename>` location resolve through `EVIDENCE_PATH_MIGRATIONS.md`; storage migration does not change evidence meaning.

## Documentation-maintenance state

The September 8–16 processed collision evidence backlog has been archived byte-identically. `research/raw/` is again intake-only.

A repository documentation audit also found older cold/convention documents whose ledger-split examples predate `EVIDENCE_LEDGER_283_ONWARD.md` and `EVIDENCE_LEDGER_286_ONWARD.md`. Those stale storage-range examples do **not** override the actual continuation headers, this entrypoint, or canonical evidence. Keep current-state reasoning on the authorities named above until those cold routing examples are normalized.

## Deployment authority

```text
live collision DLLs:
E:\SteamLibrary\steamapps\common\Gothic 3\scripts

runtime diagnostic logs:
E:\SteamLibrary\steamapps\common\Gothic 3
```

Never deploy a collision DLL to the game root.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO Normal marker2 rearm until native-clear necessity closes
NO Power/Sprint repeated-FIST intervention yet
NO New Balance final regression before permanent collision structure
NO Raise / speed-control work before collision module closes
NO AttackContinuationProtection work
```
