# Gothic 3 — Raw8 Persistent Opportunity Token Causal Probe

**Status:** ACTIVE — BOUNDED DIAGNOSTIC-ONLY CAUSAL INTERVENTION TASK  
**Opened:** 2026-09-20  
**Evidence basis:** EV-231, EV-233–EV-240, EV-346–EV-352  
**Production behavior change:** PROHIBITED  
**Work build execution:** PROHIBITED

## Repository

`https://github.com/tcholti/Gothic3_Animation_Behaviors.git`

Branch:

`docs/collision-source-evidence`

The exact implementation HEAD to use is the current branch HEAD supplied in the Work handoff.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`
5. `docs/COLLISION_REFERENCE.md`
6. `docs/SOURCE_HOOK_GUIDE.md`
7. `docs/COLLISION_DIAGNOSTICS.md`
8. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
9. `docs/FEATURE_DEVELOPMENT_METHOD.md`

Then inspect only the exact source required by this frozen probe contract.

## Causal question

Can one exact marker-owned **pending opportunity token** make raw8 FIST behave as an authored opportunity window:

```text
FIST
-> opportunity OPEN

native raw8 attempt misses before contact
-> opportunity remains OPEN
-> Gothic's one-shot latch/timing path is made eligible again

first exact native raw8 contact-resolution dispatch
-> opportunity CONSUMED
-> no further rearm

later FIST in same exact C1
-> one opportunity OPEN again

Hit/C1 ends first
-> unused opportunity CLOSED
```

without:

- per-target visited bookkeeping;
- custom target selection;
- custom contact;
- custom/direct damage;
- interpreting HP outcome;
- changing raw55/equipped behavior?

## Evidence rationale

EV-231 proves explicit same-move `SPU+0x164: 1 -> 0` can restore a later native raw8 opportunity.

EV-233 proves `ClearTriggeredList()` is unnecessary for the tested raw8 combat-loop route.

EV-346–EV-348 prove:
- early marker-time attempts can miss;
- native raw8 closes the latch after the attempt;
- one post-miss latch-only rearm can restore later native opportunity.

EV-349 proves:
- exact `Game+0x16E348` dispatch may occur while Parade prevents visible HP damage;
- therefore the dispatch is not an HP-success oracle;
- stale rearmed opportunity must never survive Hit/C1 replacement.

EV-351 proves exact raw8 `CanBeActivatedNow` / `TriggerTarget` callbacks are absent on the tested route.

EV-352 strongly supports target-directed raw8 semantics:
- eight exact native human Fist dispatches in a group-combat interception control;
- all eight targeted the locked opponent;
- none targeted deliberately interposed/adjacent non-target opponents.

Therefore this probe uses **one pending token per exact actor/C1 execution**, not a per-target list.

## Architectural meaning of the exact contact boundary

For this probe only, exact entry into the existing generic `gCEntity::OnDamage` hook is treated as a **raw8 native contact-resolution dispatch** only when every identity condition matches:

- caller return = `Game.dll + 0x0016E348`;
- token actor is exact current actor;
- token C1 generation is exact current generation;
- `Arg1` is the exact token raw8 Fist source;
- `Arg2` is the exact token actor;
- source still resolves as exact `gEUseType_Fist`;
- token remains pending.

Consume the token **before calling the native original**.

Do not inspect:
- native return/outcome;
- HP change;
- target reaction;
- block/Parade;
- immunity;
- knockdown/get-up policy.

The API is named `OnDamage`, but this probe uses only the exact native dispatch-entry fact. Gameplay damage policy remains entirely Gothic/behavior-owned.

## Required implementation shape

Create temporary diagnostic-only:

```text
Raw8FistPersistentOpportunityProbe.cpp
Raw8FistPersistentOpportunityProbe.h
```

Compile only into `Script_FrameCollisionTest`.

Do not add to `FRAME_COLLISION_BEHAVIOR_SOURCES`.

`EngineBridge` remains sole physical hook owner.

Do **not** modify permanent `Raw8FistCollision.cpp/.h` behavior for this causal probe.

### A. Retire the closed EV-351 observation probe

Delete:

```text
Raw8FistContactBoundaryProbe.cpp
Raw8FistContactBoundaryProbe.h
```

Remove its CMake entries.

Remove the now-closed diagnostic hooks/delegation for:

- `Game+0x692F0`;
- `Game+0x693B0`.

Do not retain stale closed-probe hooks.

### B. Pending token identity

Maintain at most one token per actor.

A token must bind:

- actor instance;
- exact C1 generation;
- exact raw8 Fist source;
- exact SPU;
- animation actor if available;
- current movement animation identity;
- pending OPEN/CLOSED state;
- persistent pre-threshold forced-play-time value if learned;
- current invocation observation state as needed.

No target list.

No species identity.

### C. Token OPEN / rearm from accepted FIST

In `StartEffect_FrameCollisionTest`, after ordinary marker processing and permanent raw8 marker/timing handling have completed, delegate the factual marker result to the temporary probe.

Open/refresh one token only when:

- marker result = accepted `FIST`;
- C1 generation valid;
- exact source exists;
- exact source UseType = raw8 `gEUseType_Fist`;
- permanent FIST latch write was attempted and confirmed to `SPU+0x164 = 0`;
- SPU/actor identity matches;
- exact current generation/source/animation identity is capturable.

A later accepted FIST in the same C1 refreshes/reopens **one** token. It does not stack entitlements.

The permanent raw8 marker logic remains the owner of the marker-time latch write and its existing first timing permission.

### D. Persistent marker-time timing eligibility

The existing timing wrapper currently does:

```text
realPlayTime
-> Raw8FistCollision::ApplyTimingPermission(...)
-> returnedPlayTime
```

For the diagnostic product only, pass that permanent result through the temporary probe.

The probe may preserve the first exact synthetic returned play time as its marker-time threshold surrogate.

While:
- token pending;
- actor/C1/source/SPU/animation identity exact;
- current call is the exact primary-motion timing call;
- real play time remains below the stored forced value;

return a value sufficient to preserve the same already-proven marker-time native threshold permission.

Do not advance the actual animation clock.

Do not invent a new threshold constant if the permanent raw8 code did not already expose one through its returned value.

Once real time naturally reaches/passes the stored value, return the permanent/native result unchanged.

### E. Whole combat-move invocation scope

Around existing `AICombatMoveInstr_FrameCollisionTest` original execution, maintain a diagnostics-only nested invocation scope.

Before the original:
- validate any existing token;
- if its C1/source/SPU/animation identity is stale or replaced, CLOSE it before native execution and force its old exact latch to `1`;
- if `a_bFullStop == GETrue`, close the exact pending token for that actor and do not rearm it.

During the invocation:
- mark whether the exact native contact-resolution dispatch consumed the token.

After the original:
- if the same exact token is still pending;
- same C1/source/SPU/animation identity still holds;
- no exact contact dispatch consumed it;

then:
- read the exact latch;
- if native attempt left it `1`, write it back to `0`;
- confirm readback;
- keep token pending.

This is the causal **miss rearm**.

Do not write latch `0` if no pending token exists.

### F. Exact native contact consumption

Inside existing generic `EntityOnDamage_FrameCollisionTest`:

1. capture caller as already done;
2. delegate read-only identity to the temporary probe **before** native original;
3. if every exact raw8 token/contact condition matches, consume/close the token;
4. do not write latch `0`;
5. do not alter any argument;
6. call original exactly once as today.

The generic `CORE ONDAMAGE` diagnostic remains.

The token must be consumed on dispatch **entry**, not based on what the original later does.

### G. Exact Hit/C1 closure

Unused pending opportunity must not leak.

Provide a diagnostic-only closure seam from the existing `AISetState_FrameCollisionTest` before its native original:

- if the owner has a pending exact token belonging to the current generation, force its exact latch to `1` and erase/close the token before the state transition;
- do not touch unmarked raw8;
- do not touch a different generation/source/SPU.

Also close stale token on factual new-generation detection before a new combat-move original executes.

This is specifically required by EV-349.

### H. Logging

Use collision/opportunity vocabulary only.

Suggested compact records:

```text
CORE RAW8_OPPORTUNITY_OPEN
CORE RAW8_OPPORTUNITY_TIMING_HOLD
CORE RAW8_OPPORTUNITY_MISS_REARM
CORE RAW8_OPPORTUNITY_CONTACT_CONSUMED
CORE RAW8_OPPORTUNITY_CLOSE
```

Each causal mutation record must include enough identity/readback to prove:

- actor;
- C1;
- source;
- SPU;
- motion;
- reason;
- latch before/after when written.

Do not log or classify `DamageSucceeded`, HP delta, or equivalent.

## Protected behavior

This probe must not:

- add per-target bookkeeping;
- call `ClearTriggeredList()`;
- alter `EntitiesVisited`;
- change collision groups;
- choose/change target;
- directly invoke contact/damage;
- suppress `gCEntity::OnDamage`;
- alter its arguments;
- use native result/HP outcome to decide token state;
- alter unmarked raw8;
- alter raw55;
- alter equipped collision/Sprint;
- alter production integration;
- add raw8 FIST_OFF;
- change permanent `Raw8FistCollision` behavior source.

Every native original remains exactly-once/pass-through.

## Expected source scope

Expected:

```text
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
ADD    prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.cpp
ADD    prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.h
DELETE prototypes/Script_FrameCollisionTest/Raw8FistContactBoundaryProbe.cpp
DELETE prototypes/Script_FrameCollisionTest/Raw8FistContactBoundaryProbe.h
```

If safe implementation requires a permanent source change or broader hook ownership, STOP and report the contradiction.

## Static verification

Before publication verify:

- exact expected six-path scope;
- old `Raw8FistContactBoundaryProbe` absent;
- no `Game+0x692F0` / `Game+0x693B0` hooks remain;
- new probe diagnostic-only;
- behavior-only source list unchanged;
- permanent `Raw8FistCollision` unchanged;
- generic OnDamage original exactly once/pass-through;
- no target/list/group/custom-damage mutation;
- latch writes occur only for exact pending token OPEN/miss-rearm/close cases defined here;
- no species rules;
- `git diff --check` passes.

## First runtime fixture after Normal Chat review

Use the same Gargoyle factual raw8 Power animation with frame-3 FIST.

Run three classes:

1. **close start** — target already reachable at marker;
2. **medium/far start** — misses at marker but Gargoyle reaches player before Hit ends;
3. **very far start** — Gargoyle never reaches player before Hit ends.

Expected causal signatures if the model is correct:

```text
close:
OPEN
-> first native attempt
-> CONTACT_CONSUMED
-> no MISS_REARM

medium/far:
OPEN
-> one or more MISS_REARM / TIMING_HOLD cycles
-> later CONTACT_CONSUMED within same C1

very far:
OPEN
-> repeated bounded miss rearm while Hit remains exact
-> no contact dispatch
-> CLOSE at Hit/C1 end
-> zero cross-C1 contact
```

Do not add a second FIST in the first runtime.

Do not use Parade/knockdown as the first fixture; that is a later policy-neutrality control only if this mechanism passes.

## Build / publication

Work build execution is **PROHIBITED**.

The User explicitly authorizes publication of this bounded diagnostic-only causal probe to:

- repository: `tcholti/Gothic3_Animation_Behaviors`;
- branch: `docs/collision-source-evidence`.

Perform source/static checks only.

## Required report

Report:

- final remote commit SHA;
- parent SHA;
- changed/added/deleted files;
- exact hook/delegation changes;
- confirmation old EV-351 probe hooks/files retired;
- confirmation behavior-only source set unchanged;
- confirmation permanent raw8 source unchanged;
- confirmation generic OnDamage remains exactly-once/pass-through;
- confirmation no target/list/group/custom-damage mutation;
- static checks;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`;
- any material contradiction.

Then STOP.
