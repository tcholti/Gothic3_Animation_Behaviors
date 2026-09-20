# Gothic 3 — Raw8 TouchDamage Contact-Boundary Observation

**Status:** ACTIVE — IMPLEMENTED / NORMAL CHAT SOURCE REVIEW PASS / LOCAL BUILD + RUNTIME OBSERVATION PENDING  
**Opened:** 2026-09-20  
**Evidence basis:** EV-106–EV-116, EV-221–EV-240, EV-290, EV-346–EV-350  
**Production behavior change:** PROHIBITED  
**Work build execution:** PROHIBITED

## Repository

`https://github.com/tcholti/Gothic3_Animation_Behaviors.git`

Branch:

`docs/collision-source-evidence`

Frozen research state before this task:

`04c96f8a9f8ffd3231f9fe7aada3309459611af6`

The exact implementation HEAD to use is the current branch HEAD supplied in the Work handoff.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`
5. `docs/SOURCE_HOOK_GUIDE.md`
6. `docs/COLLISION_DIAGNOSTICS.md`
7. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
8. `docs/FEATURE_DEVELOPMENT_METHOD.md`

Then inspect only the exact source required by this frozen observation contract.

## Research question

The physical weapon/raw55 model provides a clean native contact concept:

```text
source active
-> target contacted
-> target becomes visited/triggered for that source
-> same target cannot consume another opportunity
-> ClearTriggeredList re-arms target contact
```

EV-233 proves raw8 does **not** use `ClearTriggeredList()` as the control mechanism for the tested combat-loop path.

The tested binary nevertheless contains:

- `gCTouchDamage_PS::CanBeActivatedNow` at `Game.dll + 0x000692F0`;
- `gCTouchDamage_PS::TriggerTarget` at `Game.dll + 0x000693B0`.

The exact bounded question is:

> During a factual raw8 Fist attack, does the exact raw8 TouchDamage source reach `CanBeActivatedNow` and/or `TriggerTarget`, and if so do those boundaries correlate with native target/contact resolution rather than HP-damage outcome?

This task is **observation only**.

## Why this is the next smallest question

Static raw8 combat-loop evidence shows:

```text
timing threshold passes
-> SPU+0x164 = 1 at Game+0x16E1A3
-> multiple additional target/contact checks
-> several branches can still exit at Game+0x16E352
-> final gCEntity::OnDamage call returns at Game+0x16E348
```

Therefore the latch write is attempt-level consumption and is too early to represent accepted contact.

The physical-source analogy suggests looking for a native target-resolution boundary before using `OnDamage` as a proxy.

Historical N2B does **not** answer this question because that runtime reported `DeepDiagnostics: DISABLED`.

## Required implementation shape

Create a temporary diagnostic-only owner:

```text
Raw8FistContactBoundaryProbe.cpp
Raw8FistContactBoundaryProbe.h
```

Compile it into `Script_FrameCollisionTest` only.

Do not add it to `FRAME_COLLISION_BEHAVIOR_SOURCES`.

`EngineBridge` remains the sole physical hook owner.

### 1. Exact invocation scope

Around the existing `AICombatMoveInstr_FrameCollisionTest` original call, install a diagnostics-only thread-local invocation scope.

At scope begin, capture only factual runtime identity available without mutation:

- `a_pSPU`;
- actor instance from `a_pSPU->GetSelfEntity()`;
- current C1 generation token;
- current action;
- current movement animation;
- exact current Fist source from `CollisionSources::ResolveFistCollisionSource(actor)`;
- exact source UseType;
- exact `gCTouchDamage_PS *` belonging to that source.

The scope is eligible only when:
- actor/SPU identity is valid;
- C1 generation is valid;
- resolved Fist source exists;
- source UseType is exactly `gEUseType_Fist` / raw8;
- TouchDamage property-set identity is exact.

Support nesting with a previous-scope pointer.

Do **not** require species identity.

### 2. Observe CanBeActivatedNow

Use the already-known tested hook target:

`Game.dll + 0x000692F0`

Install it in the diagnostic product under `FRAME_COLLISION_DIAGNOSTICS`, not behavior-only.

The wrapper must:
- call the original exactly once;
- preserve the exact original return value;
- delegate observation only when `a_pThis` matches the current exact raw8 scope TouchDamage pointer.

Record:
- elapsed time;
- actor/source/SPU/C1/action/motion identity;
- entity argument address/name;
- contact-iterator address;
- native return value;
- read-only trigger visited state before and after original:
  - `EntitiesVisited` size;
  - `EntitiesVisitedCount` size;
  - whether each entity argument is present when safely resolvable;
  - corresponding visit count when present.

No array mutation.

### 3. Observe TriggerTarget

Use the already-known tested hook target:

`Game.dll + 0x000693B0`

Install it in the diagnostic product under `FRAME_COLLISION_DIAGNOSTICS`, not behavior-only.

The wrapper must:
- call the original exactly once;
- perform no suppression or argument change;
- delegate observation only on exact current raw8 TouchDamage identity.

Record before and after original:
- elapsed time;
- exact actor/source/SPU/C1/action/motion;
- entity argument 1 address/name;
- entity argument 2 address/name;
- contact-iterator address;
- read-only `EntitiesVisited` / `EntitiesVisitedCount` sizes;
- presence/count for argument 1 and argument 2 where safely resolvable.

Do not assume in code which entity argument is the target. Log both.

### 4. Correlation only

The existing generic `CORE ONDAMAGE` diagnostic remains unchanged.

The probe may record an invocation-local ordinal for:
- CanBeActivatedNow;
- TriggerTarget.

It must **not** classify either as production success yet.

The runtime analysis will compare ordering against:
- accepted FIST marker;
- raw8 early timing permission;
- `CORE ONDAMAGE`;
- C1 finalization.

## Diagnostic log vocabulary

Use collision/contact terminology, not damage-success terminology.

Suggested compact records:

```text
CORE RAW8_CONTACT_GATE ...
CORE RAW8_CONTACT_TARGET ...
```

Do not emit names such as:
- `DamageSucceeded`;
- `ExactNativeDamageObserved`;
- `DamageOpportunity`.

The generic Gothic API logger may remain named `CORE ONDAMAGE` because that is the API/event being observed.

## Protected behavior

This task must not:

- write `SPU+0x164`;
- arm/rearm timing permission;
- alter `GetPlayTime` return values;
- call `ClearTriggeredList()`;
- alter visited arrays;
- alter collision groups;
- suppress either native TouchDamage function;
- suppress `gCEntity::OnDamage`;
- add custom/direct damage;
- change target identity;
- change reaction/block/immunity policy;
- change marker recognition;
- change C1 lifecycle;
- change raw55;
- change equipped collision/Sprint;
- change production integration.

Every hooked original must execute exactly once with unchanged arguments/return semantics.

## Existing DEEP hooks

`EngineBridge.cpp` currently contains player-only DEEP versions of these two hook targets.

Do not install duplicate hooks.

The bounded implementation should reuse/replace the existing physical hook ownership so:
- there is exactly one hook per target;
- CORE diagnostic can perform the new actor-general exact-raw8 observation;
- behavior-only still has neither hook;
- DEEP-only historical diagnostics may remain available only if they can coexist without duplicate physical hook ownership.

If preserving the old DEEP logger would broaden or complicate the task, prefer the new bounded CORE observation and remove only the obsolete player-only delegation needed to avoid duplicate ownership. Do not alter unrelated DEEP diagnostics.

## Expected source scope

Expected changed/added files:

```text
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/Raw8FistContactBoundaryProbe.cpp   ADD
prototypes/Script_FrameCollisionTest/Raw8FistContactBoundaryProbe.h     ADD
```

`CollisionDiagnostics.*` should not need modification if the temporary probe logs through `CollisionDiagnostics::GetLog()`.

If safe read-only visited-state capture requires a tiny diagnostics helper or the exact expected scope is insufficient, STOP and report the contradiction rather than broadening silently.

## Static verification

Before publication verify:

- temporary probe is diagnostic-target-only;
- behavior-only source set unchanged;
- exactly one hook owner for `Game+0x692F0`;
- exactly one hook owner for `Game+0x693B0`;
- both originals called exactly once;
- no latch/timing/group/trigger-list/visited-state mutation;
- no custom damage;
- generic `CORE ONDAMAGE` untouched;
- no species rules;
- `git diff --check` passes.

## Runtime fixture after Normal Chat review

Do not bake fixture assumptions into behavior.

Planned first runtime:

- same Gargoyle factual raw8 Power animation;
- same frame-3 FIST marker;
- several deliberate close-start attacks;
- several deliberate far-start attacks;
- diagnostic CORE product only.

Primary observation:

```text
close contact:
does CanBeActivatedNow occur?
does TriggerTarget occur?
does visited bookkeeping change?
how do they order vs CORE ONDAMAGE?

far early miss:
do any of those contact boundaries occur?
or only the early raw8 attempt/latch/timing path?
```

If TouchDamage callbacks remain absent even in close cases while `CORE ONDAMAGE` occurs, the TouchDamage trigger path is ruled out for this raw8 combat-loop route and the next research step returns to the `Game+0x16E1A3 -> +0x16E348` branch region.

## Build / publication

Work build execution is **PROHIBITED**.

The User explicitly authorizes publication of this bounded diagnostic-only implementation to:
- repository: `tcholti/Gothic3_Animation_Behaviors`;
- branch: `docs/collision-source-evidence`.

Perform source/static checks only.

## Required report

Report:
- final remote commit SHA;
- parent SHA;
- changed/added files;
- exact hook ownership/result;
- confirmation behavior-only source set unchanged;
- confirmation every original remains exactly-once/pass-through;
- confirmation no behavior mutation exists;
- static checks;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`;
- any material contradiction.

Then STOP.

## Implementation checkpoint — 2026-09-20

Work implementation:

`929bba9974788c873860f8e33f504c091f7aa524`

Parent:

`dec7f7d4e13f38f8c5fc6dabd620056907c4383d`

Normal Chat independent source review: **PASS**.

Review findings:
- exactly one commit over the authorized parent;
- exact four-file scope;
- `FRAME_COLLISION_BEHAVIOR_SOURCES` is textually unchanged;
- generic `EntityOnDamage_FrameCollisionTest` is textually unchanged;
- exactly one `Game+0x692F0` hook and one original call;
- exactly one `Game+0x693B0` hook and one original call;
- both hooks are diagnostic-only under `FRAME_COLLISION_DIAGNOSTICS`;
- old player-only DEEP delegation was replaced without duplicate physical hook ownership;
- the temporary probe uses read-only `GetEntitiesVisited()` / `GetEntitiesVisitedCount()` access only;
- no latch, timing, collision-group, trigger-list, visited-state, target, lifecycle or gameplay-damage mutation exists;
- no damage-success terminology or classification exists;
- invocation identity is actor/SPU/C1/exact raw8-source/TouchDamage bounded and supports nested scope restoration.

Runtime interpretation note:
- `TriggerTarget` may observe the target already present in visited bookkeeping on entry if base `eCTrigger_PS` bookkeeping occurs before the virtual call. The probe records both before and after specifically to determine ordering; do not assume insertion occurs inside `gCTouchDamage_PS::TriggerTarget`.

Local build and runtime observation are pending.
