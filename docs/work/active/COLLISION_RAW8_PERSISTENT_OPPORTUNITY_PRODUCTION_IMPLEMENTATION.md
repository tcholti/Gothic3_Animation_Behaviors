# Gothic 3 — Raw8 Persistent Opportunity Production Implementation

**Status:** ACTIVE — PRODUCTION SOURCE CANDIDATE STATIC REVIEW PASS / BUILD + SMOKE + FOCUSED ACCEPTANCE PENDING  
**Opened:** 2026-09-20  
**Architecture:** `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`  
**Evidence closure:** EV-353  
**Pre-Work Sprint transport sentinel:** EV-354 PASS  
**Work build execution:** PROHIBITED

## Independent Normal Chat review — 2026-09-20

Published implementation: `3426cede41c0087e43edc0d81c825ff167e8e034`  
Parent: `ce4b4daee8bf74f29e85591cbfab5f6abc064cd4`

Static independent review accepted the permanent behavior/state-machine promotion and exact eight-path scope.

The bounded diagnostics-only follow-up was implemented in `7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd` and independently reviewed PASS. Its closed contract is archived at `docs/archive/investigations/COLLISION_RAW8_PRODUCTION_DIAGNOSTIC_COMPACTION_CORRECTION.md`.

Current production source candidate is therefore `7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd`. Next gate is build both twins, then the agreed small smoke/log check before the final read-only code-quality/modularity audit.

## Responsibility

Promote only the EV-353-proven persistent raw8 opportunity mechanism into the existing permanent owner, `Raw8FistCollision`, and completely remove the temporary `Raw8FistPersistentOpportunityProbe` runtime dependency.

This is production promotion after causal closure, not another experiment.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`
5. `docs/COLLISION_LIFECYCLE.md`
6. `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`
7. `docs/COLLISION_DIAGNOSTICS.md`
8. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
9. `docs/FEATURE_DEVELOPMENT_METHOD.md`

Then inspect only the exact assigned source.

## Pre-Work runtime sentinel — required before Work

### Sentinel result — EV-354 PASS

The required source-unchanged Sabretooth single-FIST control is complete.

EV-354 captured 20 exact opportunities that:
- opened under factual Action9/SPRINT;
- remained the same token/C1;
- were consumed under factual Action2/POWER;
- used the same PowerAttack-named motion throughout the tested transition;
- never closed merely because Action/family changed.

C1 183/token43 and C1 207/token47 additionally missed and rearmed under Action9 before the same token was consumed under Action2.

This satisfies the pre-Work sentinel. The production task may proceed after POP-12 validates the promoted EV-354 state.


The former pre-Work sentinel contract is satisfied and closed by EV-354. Do not rerun it before Work unless later evidence creates a new contradiction.


## Permanent ownership

`Raw8FistCollision` owns all raw8 opportunity state/policy. `EngineBridge` remains hook/transport only. `CollisionLifecycleGuard` remains generic C1 authority and must not gain raw8 state/policy.

Do not create another permanent raw8 module.

## Required behavior

### Marked execution start

Preserve existing exact marked raw8 ownership: first qualifying marked raw8 C1 writes `SPU+0x164 = 1` and creates one per-actor execution record bound to actor/C1/raw8 source/SPU.

Execution starts with logical opportunity CLOSED.

### Accepted FIST

Preserve existing `FrameCollisionMarkers` accepted-FIST latch write `-> 0`.

After confirmed accepted FIST, permanent `Raw8FistCollision` must:
- require exact actor/C1/source/SPU match;
- set one pending opportunity OPEN;
- refresh rather than stack if already pending;
- refresh/replace timing substate independently;
- not require immutable animation identity merely to keep the logical opportunity open.

### Timing persistence

Replace the current one-shot timing permission semantics with the EV-353 persistent behavior.

While opportunity is pending and the exact timing identity still matches, repeated exact `Game+0x16E180` primary-motion calls before the stored forced play time may return the same already-proven threshold+epsilon value.

Do not advance the real animation clock. Retire timing when real time reaches/passes the forced value or timing identity becomes stale. Timing retirement alone does not consume opportunity.

### Combat-move miss rearm

Move the proven diagnostic invocation-scope behavior into `Raw8FistCollision`.

After native `AICombatMoveInstr` original, if the exact same pending opportunity still exists and no exact contact dispatch consumed it, then if `SPU+0x164 == 1`, write `1 -> 0`, verify readback, and keep opportunity pending.

No pending opportunity means no miss rearm. `FullStop` alone must not close opportunity.

### Exact native contact consumption

Make the already-installed `gCEntity::OnDamage` hook behavior-required in both collision twins.

Before Gothic original, delegate caller/Arg1/Arg2 to `Raw8FistCollision`. Consume only when all architecture conditions match, including exact caller return `Game.dll+0x0016E348`, active exact raw8 invocation scope, exact source/actor/C1/SPU/current-generation identity and pending state.

On consumption:
- pending opportunity -> CLOSED/CONSUMED;
- timing helper -> retired;
- **keep the C1 execution record alive** so a later FIST in the same C1 can reopen another opportunity;
- do not mutate latch for contact consumption;
- call Gothic original exactly once with unchanged arguments;
- never inspect native result/HP/block/immunity/reaction outcome.

### C1 finalization

Move the proven generation-safe finalization behavior into `Raw8FistCollision`.

At existing post-native `AISetState` seam and before generic lifecycle record removal:
- locate only the execution belonging to the captured generation;
- recapture current generation before latch mutation;
- same current/captured generation: exact live pending latch may be forced `-> 1`, then timing/execution state retires;
- invalid/changed current generation: retire only stale old execution/timing, **no latch write into replacement generation**.

### Generation-replacement backup

Preserve the EV-353-proven pre-combat stale-generation backup from the diagnostic probe: when an old pending raw8 execution is discovered under a different factual current C1 before native combat-move original, retire it and close the exact live latch only under the same actor/SPU/source liveness checks used by the probe.

Do not invent a new Action/state-name classifier. The focused acceptance plan will explicitly test later unmarked raw8 fallback after such replacement.

## Merge rule — execution state vs opportunity state

The diagnostic probe had a separate token map underneath the existing permanent execution map. Production has only the permanent execution map.

Therefore:

```text
contact consumption
-> clear pending opportunity
-> retire timing
-> KEEP Raw8FistMarkerExecution until C1 finalization/replacement

later FIST
-> reopen pending opportunity in that same execution
```

Erasing the whole execution record at contact is a correctness bug.

## EngineBridge changes

Remove all `Raw8FistPersistentOpportunityProbe` includes/delegations.

Permanent bridge responsibilities:
- timing wrapper delegates only to permanent `Raw8FistCollision`;
- `StartEffect` delegates accepted marker follow-up only to permanent `Raw8FistCollision`;
- `AICombatMoveInstr` always creates/completes the narrow permanent raw8 invocation scope in both twins;
- `AISetState` always delegates permanent raw8 finalization at the frozen post-native seam;
- `Hook_EntityOnDamage` declaration/install/wrapper becomes behavior-required rather than `FRAME_COLLISION_DIAGNOSTICS`-only;
- OnDamage diagnostic logging/counters remain conditional under `FRAME_COLLISION_DIAGNOSTICS`;
- OnDamage native original remains exactly once/pass-through.

No new physical hook is authorized.

## Diagnostic promotion

Delete probe-owned direct logging. Add compact permanent diagnostic logging through `CollisionDiagnostics` only.

Keep enough CORE evidence for:
- `CORE RAW8_OPPORTUNITY_OPEN`;
- `CORE RAW8_OPPORTUNITY_MISS_REARM`;
- `CORE RAW8_OPPORTUNITY_CONTACT_CONSUMED`;
- `CORE RAW8_OPPORTUNITY_CLOSE`.

Do not make release behavior depend on logger code/state. Avoid restoring research-era per-frame timing-hold spam; existing raw8 timing diagnostics plus opportunity mutation events are sufficient.

## Temporary probe retirement

Delete:
- `prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.cpp`;
- `prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.h`.

Remove their diagnostic CMake entries.

After this task, the production candidate must behave identically with the temporary probe absent.

## Protected behavior

Do not change:
- `FrameCollisionMarkers.cpp/.h`;
- `CollisionLifecycleGuard.cpp/.h`;
- `PhysicalFistCollision.cpp/.h`;
- `EquippedSprintCollision.cpp/.h`;
- equipped RIGHT/LEFT/BOTH/OFF semantics;
- raw55 semantics;
- supported raw8 family set;
- unmarked raw8 native fallback intent;
- target selection/contact geometry;
- HP/block/immunity/reaction policy.

Do not add:
- FIST_OFF;
- target/visited lists;
- `ClearTriggeredList` for raw8;
- collision-group raw8 windows;
- custom/direct damage;
- species/name rules;
- timers/polling;
- new hook RVAs;
- Action/phase/motion-only terminal authority.

## Expected source scope

Expected paths:

```text
MODIFY prototypes/Script_FrameCollisionTest/CMakeLists.txt
MODIFY prototypes/Script_FrameCollisionTest/EngineBridge.cpp
MODIFY prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
MODIFY prototypes/Script_FrameCollisionTest/Raw8FistCollision.h
MODIFY prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
MODIFY prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
DELETE prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.cpp
DELETE prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.h
```

`FRAME_COLLISION_BEHAVIOR_SOURCES` membership must remain unchanged. The permanent raw8 owner already belongs to it.

If faithful implementation requires changing a protected module, adding a new hook, or creating another permanent behavior module, STOP and report the contradiction.

## Static verification

Before publication verify:
- exact expected eight-path scope;
- temporary probe files/references absent;
- behavior source membership unchanged;
- `Hook_EntityOnDamage` exists once and is installed in both twins through shared EngineBridge code;
- OnDamage original exactly once with unchanged args;
- contact consumption keeps execution record alive;
- later FIST can reopen within same C1;
- timing helper can retire without consuming opportunity;
- miss rearm requires exact pending opportunity;
- FullStop/Action/family/phase/motion alone cannot terminal-close opportunity;
- post-AISetState changed-generation path performs no latch write;
- no raw8 target/list/group/custom-damage logic;
- no protected-module changes;
- `git diff --check` passes.

## Build / publication

Work build execution is PROHIBITED.

The User authorizes publication of this bounded production implementation to `tcholti/Gothic3_Animation_Behaviors`, branch `docs/collision-source-evidence`.

## Required report

Report final remote commit SHA, parent SHA, changed/deleted files, concise permanent state-machine result, hook/delegation changes, temporary-probe retirement, behavior-vs-diagnostic separation, static checks, `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`, and any material contradiction. Then STOP.