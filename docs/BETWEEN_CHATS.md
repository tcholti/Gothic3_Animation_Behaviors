# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-291 CLOSED; MARKER2 REPLACEMENT-CLEAR PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-291**. No permanent raw55 implementation is authorized.

Latest canonical evidence:

`docs/EVIDENCE_LEDGER_291_ONWARD.md` — EV-291

Current frozen diagnostic contract:

`docs/COLLISION_RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE.md`

## Canonical factual checkpoint — EV-291

EV-291 proves that the exact post-hit1 native public ALL clear is causally required for Normal's implicit second same-C1 damage opportunity:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList()
-> hit1
-> PC_Hero visited/count1

native Normal transition
-> EV-288 exact native 7 -> 7 setter suppression fires
-> exact eCTrigger_PS::ClearTriggeredList() ALL arrives
   Engine +0x7DDA0
   caller Script_Game.dll +0x386C6
-> EV-291 suppression fires
-> original clear skipped
-> PC_Hero remains visited/count1
-> original _AI_Attack still completes SP0 -> 1

marker2
-> observational
-> PC_Hero still visited/count1
-> hit2 disappears

native exact RIGHT 7 -> 5 cleanup
-> clean C1 finalization
```

User visual result:

```text
first swing damaged = YES
second swing damaged = NO
```

The native ALL clear is therefore not merely correlated bookkeeping; it creates the tested Normal second-contact opportunity.

EV-291 provenance:

```text
implementation tested:
2839c8c271fa240b81ce5ccd203c34058870a5bb

DLL SHA256:
0F2CBF35199D111C405E03E5AE824B0AC76BF47B06C1BF13A47098BCFFF6F830

original source upload commit:
056951242b549c0de690ef80714b0806c688ef28

source SHA256:
33C2B2F3E7732B3AB9BEB42C4ED6528D91E0F08F5782F498AF9F1F1A231D9D98

derived package:
research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_suppression_large_log/
```

Processed source is archived unchanged; `research/raw/` is intake-only again.

## Frozen next causal question

Preserve the complete EV-291 environment and change exactly one thing:

```text
keep marker1 unchanged
keep EV-288 native 7 -> 7 suppression unchanged
keep EV-291 Script_Game +0x386C6 ALL-clear suppression unchanged

at the factual later authored Normal FIST only:
-> require same actor/C1/current RIGHT raw55 group7
-> require native clear suppression already used
-> require PC_Hero still factually visited exactly once
-> execute exactly one replacement ClearTriggeredList()
```

Question:

```text
Does authored marker2 replacement ClearTriggeredList restore hit2?
```

Interpretation:

```text
replacement clear executes
+ PRE player visited
+ POST player absent
+ hit1 survives
+ hit2 returns
+ cleanup healthy
    => Normal marker2 triggered-list rearm ownership proven

replacement clear executes
+ visit clears
+ hit2 still absent
    => another Normal eligibility mechanism remains

progression/source/cleanup materially diverges
    => preserve contradiction and isolate
```

## Frozen implementation responsibility

Implement ONLY `docs/COLLISION_RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE.md`.

Current source inspection shows the required seam already exists in `PhysicalFistProbe.cpp`:

- same-C1/source `NormalPreStateFistIntervention` state;
- `preStateRearmProven`;
- `nativeRearmSuppressionUsed`;
- `nativeTriggerClearSuppressionUsed`;
- Normal trigger-state capture;
- later authored Normal FIST observation inside `OnMarkerProcessed`;
- shared Engine clear hook already observes replacement clear calls.

Expected source scope is therefore exactly:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Expected implementation shape:

```text
one per-C1 marker2 replacement-clear used flag
+ convert/strengthen existing later-Normal-FIST observation seam into exact gated intervention
+ factual PRE state gate/log
+ one exact current RIGHT TouchDamage.ClearTriggeredList()
+ factual POST state/log
```

No `EngineBridge.cpp` change is expected.  
No `PhysicalFistProbe.h` API change is expected.  
No new hook/RVA/CMake/production change is expected.

If broader source scope or another mutation appears necessary, STOP and report the contradiction instead of broadening.

Work build execution remains prohibited. Work publishes source only and stops; Normal Chat independently reviews before User-local build.

## Remaining collision order

```text
Normal marker2 replacement-clear causal proof
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO production Normal marker2 behavior until causal proof closes
NO Power/Sprint repeated-FIST intervention yet
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
