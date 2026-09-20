# Gothic 3 — Raw8 Persistent Opportunity Token Causal Probe

**Status:** ACTIVE — IMPLEMENTED / NORMAL CHAT REVIEW BLOCKED / GENERATION-SAFE FINALIZATION CORRECTION REQUIRED  
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
- pending OPEN/CLOSED state;
- current invocation observation state as needed.

The **opportunity token lifetime is C1/execution-scoped**, not Action/family/phase/motion-scoped.

Action, family, phase and motion may be recorded for diagnostics, but none of them is terminal authority by itself.

This is required by existing Sprint-origin evidence:
- EV-316: factual raw8 Sprint can continue inside the same C1 from Action9/SPRINT to Action2/POWER;
- EV-322: generic equipped Sprint-origin ownership likewise survives proven same-C1 Action9 -> Action2 continuation.

A separate timing substate may bind:
- animation actor;
- motion identity/type;
- stored forced-play-time value if learned.

Timing-substate retirement does **not** consume/close the C1 opportunity token.

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
- exact current C1/source identity is capturable.

Capture current Action/family/motion for diagnostics, but do not make token OPEN depend on one immutable Action value.

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
- actor/C1/source/SPU identity exact;
- the timing substate still matches the exact animation actor/motion call that established the forced value;
- real play time remains below the stored forced value;

return a value sufficient to preserve the same already-proven marker-time native threshold permission.

Do not advance the actual animation clock.

Do not invent a new threshold constant if the permanent raw8 code did not already expose one through its returned value.

Once real time naturally reaches/passes the stored value, return the permanent/native result unchanged.

If animation/timing identity changes, retire only the timing substate. Do **not** close the pending opportunity token solely because Action, family, phase or motion changed inside the same C1.

### E. Whole combat-move invocation scope

Around existing `AICombatMoveInstr_FrameCollisionTest` original execution, maintain a diagnostics-only nested invocation scope.

Before the original:
- validate any existing token against actor/C1/source/SPU execution identity;
- if factual C1 generation replacement is already visible, CLOSE the stale token before native execution and force its still-live exact latch to `1` only when SPU/actor/source identity is revalidated;
- if only Action/family/phase/motion changed while the same exact C1 continues, preserve the token;
- if `a_bFullStop == GETrue`, record it if useful but **do not close the token from FullStop alone**. FullStop is not terminal lifecycle authority.

During the invocation:
- mark whether the exact native contact-resolution dispatch consumed the token.

After the original:
- if the same exact token is still pending;
- same C1/source/SPU execution identity still holds;
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

**Terminal authority is the exact attack/C1 execution ending, not an Action value.**

The token must survive legitimate same-C1 transport such as the proven Sprint-origin:

```text
Action9 / SPRINT
-> Action2 / POWER
same C1 generation
```

Do not close from:
- Action change alone;
- family change alone;
- phase change alone;
- motion-name change alone;
- Recover naming alone;
- FullStop alone;
- callback return alone.

Use existing lifecycle execution identity/finalization surfaces.

#### AISetState finalization seam

The existing wrapper already captures a `CollisionLifecycleGuard::GenerationToken` before native `AISetState` and finalizes that exact C1 after the native original returns.

For this diagnostic probe:
- use that captured exact generation as the terminal ownership authority, not the requested state string;
- if the pending raw8 token belongs to that exact captured generation, CLOSE it and force its exact still-live SPU latch to `1` at the bounded finalization seam;
- do not inspect requested state name or current Action to decide whether to close;
- do not touch another generation/source/SPU;
- preserve existing equipped C1 finalization ordering/behavior.

The implementation may place the raw8 close immediately before native `AISetState` **only if** it is keyed strictly to the already-captured exact generation that this wrapper will finalize, not to state/action classification. Otherwise perform it at the bounded post-original finalization seam while exact liveness is revalidated.

#### Replacement / destructive-abandonment backup

Also close a stale pending token when factual new-generation detection proves the original C1 has been replaced before another combat-move original executes.

This is the fail-safe for interruption, knockdown, terrain/state replacement, bad continuation loss or another path that ends/replaces the Hit execution.

When closing because the exact old execution ended:
- force latch `1` only after actor/SPU/source liveness is revalidated;
- erase the pending token;
- retire any timing substate;
- never allow the old opportunity to enter the new generation.

This is specifically required by EV-237 and EV-349.

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
- close a raw8 token merely because Action9 changed to Action2 within the same exact C1;
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
- token lifetime is keyed to C1 execution identity, not Action/family/phase/motion alone;
- FullStop alone cannot close the token;
- proven same-C1 Sprint-origin Action9 -> Action2 transport is preserved;
- timing-substate retirement cannot by itself consume the opportunity token;
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


## Lifecycle clarification — frozen before Work

The User explicitly required the raw8 token to inherit the project's universal **execution-lifetime principle** without mixing raw8 into equipped collision cleanup.

Required invariant:

```text
same factual attack-Hit / same C1 generation
-> token may survive internal Action/family/phase/motion transport

factual Hit/C1 execution ends or is replaced
-> token must close regardless of why:
   ordinary completion
   reaction / being hit
   knockdown
   terrain/state replacement
   destructive/bad continuation loss
   other factual C1 replacement
```

Action values are observations, never token lifetime authority.

EV-316 is the protected raw8 Sprint sentinel: Action9/SPRINT -> Action2/POWER can occur inside the same C1. EV-322 proves the same origin-continuation principle in equipped Sprint. EV-237 proves raw8 interruption safety must remain generation-scoped. EV-349 proves stale rearmed raw8 permission may leak into a replacement C1 if not explicitly closed.

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


## Implementation review checkpoint — 2026-09-20

Work implementation:

`e86c1ce03b36ef0ef7421a19284c5b38e58615ed`

Parent:

`efe75dcdc7e368043d37891f11c87d4fc8a43f01`

Normal Chat review result: **BLOCKED — ONE NARROW LIFECYCLE CORRECTION REQUIRED**.

Confirmed clean:
- exact six-path scope;
- closed EV-351 files/hooks removed;
- new probe diagnostic-only;
- `FRAME_COLLISION_BEHAVIOR_SOURCES` unchanged;
- permanent `Raw8FistCollision.cpp/.h` textually unchanged;
- generic `OnDamage` original remains exactly-once/pass-through;
- no target/list/group/custom-contact/custom-damage mutation;
- token identity is actor/C1/raw8-source/SPU, not Action/family/phase/motion;
- FullStop does not independently close the token;
- timing substate retires independently;
- same-C1 Action9 -> Action2 transport is not used as terminal authority.

### Review defect — terminal latch write lacks current-generation revalidation

`EngineBridge::AISetState_FrameCollisionTest` correctly captures the exact finalization generation before native `AISetState`, calls Gothic original first, then delegates `Raw8FistPersistentOpportunityProbe::CloseForFinalization(finalization)`.

However the current `CloseForFinalization()` implementation:
- confirms that the stored token generation equals the captured finalization generation;
- revalidates live actor/SPU/raw8-source identity before writing the latch;
- **does not revalidate that `CollisionLifecycleGuard::CaptureCurrentGenerationToken(actor)` is still that captured generation after native `AISetState` returned**.

The existing `CollisionLifecycleGuard::FinalizeAfterAISetState()` explicitly refuses finalization when the current generation changed during the native call (`LifecycleIssue_FinalizationGenerationChanged`). The raw8 probe must preserve the same generation-safety property.

Without this check, a nested/replacement generation created during native `AISetState` could share the same actor/SPU/Fist source and receive the old token's terminal `SPU+0x164 = 1` write.

That is prohibited cross-C1 contamination.

### Exact correction

Change **only**:

`prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.cpp`

Inside `CloseForFinalization(generation)`, after finding an old token whose stored generation equals the captured finalization generation and **before any latch mutation**:

1. capture the current generation with `CollisionLifecycleGuard::CaptureCurrentGenerationToken(generation.actorInstance)`;
2. require:
   - current generation valid;
   - current actor matches;
   - current generation number equals the captured finalization generation;
3. if the current generation is invalid or changed:
   - erase/close only the stale logical token;
   - retire timing state;
   - emit `CORE RAW8_OPPORTUNITY_CLOSE` with a factual reason such as `FINALIZATION_GENERATION_CHANGED_NO_LATCH_WRITE`;
   - **do not write `SPU+0x164` at all**;
4. only when the current generation still exactly equals the captured generation may the existing terminal close perform its revalidated live latch write `-> 1`.

Do not move the close to Action/family/motion classification.
Do not change the existing same-C1 Sprint behavior.
Do not broaden source scope.

Expected correction diff: **one file only**.

### Correction static gate

Verify:
- only `Raw8FistPersistentOpportunityProbe.cpp` changes;
- current C1 generation is checked before terminal finalization latch write;
- changed/invalid generation path performs no latch write;
- same-generation path preserves existing terminal close;
- no changes to miss rearm, contact consumption, timing persistence or marker OPEN;
- no behavior-only/permanent source changes;
- `git diff --check` passes.

Work build execution remains PROHIBITED for this correction.

After correction publication, Normal Chat must independently review again before local build.
