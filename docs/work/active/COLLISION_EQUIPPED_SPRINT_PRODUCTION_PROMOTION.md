# Equipped Sprint Production Promotion

**Status:** ACTIVE — ALL DIAGNOSTIC RUNTIME GATES PASS / BEHAVIOR-ONLY SMOKE PENDING  
**Type:** Bounded production-behavior promotion  
**Created:** 2026-09-19  
**Owner:** Work Chat implements; Normal Chat independently reviews and owns runtime acceptance.

## Purpose

Promote the accepted generic equipped-Sprint diagnostic mechanism into permanent behavior architecture without carrying research-probe ownership or diagnostic dependencies into the behavior-only product.

Evidence basis:

```text
EV-315  factual Goblin Action9/SPRINT RIGHT causal handoff        PASS
EV-316  raw8 Sprint protected sentinel                            PASS
EV-317  raw55 Sprint-origin protected sentinel                    PASS
EV-318  ordinary equipped true-Power protected sentinel           PASS
EV-321  BOTH with missing LEFT negative baseline                  PASS
EV-322  same-C1 Action9 -> Action2 RIGHT->OFF correction          PASS
EV-323  missing-LEFT/BOTH negative rerun after correction         PASS
EV-324  ordinary equipped true-Power after correction             PASS
```

EV-319 did not exercise factual Action9 and is not positive Sprint evidence.

Promotion decision rationale is recorded in:

`docs/decisions/ADR-0003-promote-equipped-sprint-as-permanent-behavior.md`

## Required read order

1. `README.md`
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/BETWEEN_CHATS.md`
4. this file
5. `docs/DESIGN.md`
6. `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`
7. `docs/COLLISION_DIAGNOSTICS.md`
8. `docs/COLLISION_REFERENCE.md`
9. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
10. `docs/FEATURE_DEVELOPMENT_METHOD.md`

Historical causal detail, only if implementation needs exact provenance:

`docs/archive/investigations/COLLISION_EQUIPPED_SPRINT_GENERIC_CAUSAL_PROBE.md`

and the EV-320 correction archive linked there.

## Production behavior contract

Eligible equipped Sprint remains factual, generic and marker-authored:

```text
origin family/action       = Sprint / Action9
phase                      = Hit / attack-hit eligible
matching current motion    = required
scan                       = valid
marker vocabulary          = RIGHT / LEFT / BOTH / OFF
activating requirement     = requiredSourceMask != NONE
required sources           = every source in requiredSourceMask must exist
FIST mixing                = excluded from this mechanism
valid C1 generation        = required
UseType restriction        = NONE added by Sprint behavior
species restriction        = NONE
```

Eligible origin behavior:

```text
eligible factual Sprint callback
-> suppress native early OnAI_PowerAttack callback
-> bind immutable Sprint-origin execution identity
-> authored RIGHT / LEFT / BOTH / OFF use existing generic marker semantics
-> Gothic retains target/contact/damage
-> Gothic/native lifecycle remains first cleanup authority
```

Native fallback remains mandatory for:
- unmarked Sprint;
- OFF-only Sprint;
- FIST-mixed motion;
- missing required equipped source;
- invalid/missing C1 or motion identity;
- unsupported/malformed marker state.

## Immutable Sprint-origin continuation

An already-bound Sprint execution may continue while current factual action becomes Power/2 only when all exact identity facts remain valid:

- same actor;
- same C1 generation;
- same motion identity;
- same complete-motion requiredSourceMask;
- all required sources still exist;
- exact required RIGHT/LEFT source identities still match;
- current phase remains Hit;
- current family/action is either original Sprint/9 or the exact allowed continuation Power/2.

Power/2 may **never create** a Sprint binding.

A new ordinary true-Power execution must never inherit Sprint ownership.

The generic marker execution identity must remain canonical to Sprint origin only for a marker explicitly authorized by this permanent Sprint owner. Factual current Action2 must remain available to diagnostics.

## Permanent module ownership

Create a permanent behavior module:

```text
EquippedSprintCollision.cpp
EquippedSprintCollision.h
```

This module owns only:
- equipped-Sprint eligibility policy;
- bound Sprint-origin execution state;
- exact identity validation;
- callback suppress/delegate decision;
- generic equipped-marker authorization;
- Sprint-origin Action9 -> Action2 continuation policy.

It does **not** own:
- marker scanning;
- RIGHT / LEFT / BOTH desired-set semantics;
- OFF deactivation semantics;
- occurrence/dedupe budgets;
- source activation/rearm/deactivation implementation;
- C1 cleanup/repair;
- target/contact/damage;
- raw8 FIST;
- raw55 PhysicalFist;
- physical hooks.

Those remain with their current owners.

## EngineBridge boundary

`EngineBridge` remains the sole hook owner and transport-only.

For `OnAI_PowerAttack`:
1. resolve factual action -> Sprint or Power as today;
2. run existing generic `EvaluateAttackCallback` ownership first;
3. delegate the remaining callback case to permanent `EquippedSprintCollision`;
4. suppress native only when permanent Sprint behavior returns the proven eligible Sprint-origin decision;
5. otherwise preserve existing raw55/native callback scope and original Gothic call.

Current Power continuation of an already-bound Sprint origin may preserve Sprint state but must delegate native; it must not introduce another Power suppression path.

## Marker dispatch boundary

After permanent raw55 `TryProcessMarker` declines ownership:
1. ask `EquippedSprintCollision` for generic equipped-marker authorization;
2. call `FrameCollisionMarkers::ProcessMarker` once;
3. keep generic marker semantics inside `FrameCollisionMarkers`.

The production `ProcessMarker` API must be capable of receiving the Sprint authorization/execution identity needed for canonical bookkeeping **without** `FRAME_COLLISION_DIAGNOSTICS`.

Do not globally weaken action-sensitive marker identity.

## Diagnostic separation

Do not promote `EquippedSprintProbe` as a production dependency.

Required end state:

```text
behavior-only product
  includes EquippedSprintCollision
  does not include EquippedSprintProbe
  does not require CollisionDiagnostics
  does not require diagnostic state or diagnostic-only hooks

diagnostic product
  uses the same EquippedSprintCollision behavior
  may observe/log its factual decisions under FRAME_COLLISION_DIAGNOSTICS
```

Diagnostic logging may live behind compile guards in the permanent behavior module or observe compact factual result structures, following existing raw8/raw55 patterns. Behavior correctness must not depend on a log being open.

Remove/delete the temporary `EquippedSprintProbe.cpp/.h` once its proven responsibilities have been re-expressed in the permanent module.

Update CMake so `EquippedSprintCollision.cpp/.h` are in `FRAME_COLLISION_BEHAVIOR_SOURCES`; the behavior-only and diagnostic twins must compile the same Sprint behavior authority.

## Required implementation preservation

Do not change:
- raw8 FIST behavior;
- permanent raw55 behavior;
- true equipped Power behavior;
- non-Sprint equipped marker behavior;
- C1-R1 lifecycle rules;
- Gothic target/contact/damage ownership;
- hook RVAs/calling conventions;
- attack-motion routing;
- shield/raw9 deferred damage boundary;
- public release migration into `src/Script_G3AnimationBehaviors` yet.

No species/name gate. No raw2 gate. No custom damage. No polling/watchdog. No new cleanup system.

## Expected source boundary

Primary expected changes:

```text
prototypes/Script_FrameCollisionTest/EquippedSprintCollision.cpp   NEW
prototypes/Script_FrameCollisionTest/EquippedSprintCollision.h     NEW
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.cpp        DELETE
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.h          DELETE
```

Broaden this list only if required by the frozen architecture.

## Required static acceptance

Work must verify at minimum:
- `git diff --check` PASS;
- no behavior correctness references `EquippedSprintProbe`;
- behavior-only CMake includes permanent Sprint module;
- diagnostic-only CMake no longer owns Sprint behavior;
- production path is not gated by `FRAME_COLLISION_DIAGNOSTICS`;
- diagnostics remain optional observers;
- ordinary true Power cannot create Sprint binding;
- missing required source cannot partially acquire marker ownership;
- Action9 -> Action2 continuation remains exact-identity-only.

Do not build unless the active Work implementation protocol authorizes build execution.

## Required Normal Chat / user acceptance after Work

After independent source review:

1. build both `Script_FrameCollisionBehaviorTest` and `Script_FrameCollisionTest`;
2. verify diagnostics-free behavior twin contains/loads permanent Sprint behavior without research diagnostic dependency;
3. deploy diagnostic twin and rerun the compact acceptance controls:
   - Goblin RIGHT -> OFF positive continuation;
   - Goblin BOTH with LEFT absent negative;
   - player 2H ordinary true Power protected control;
4. then deploy behavior-only twin and perform a bounded smoke of the known Goblin Sprint fixture to confirm the diagnostics-free product still produces the intended gameplay behavior;
5. only after these pass promote current architecture/reference from “promotion pending” to permanent equipped-Sprint production support.

The later migration into `src/Script_G3AnimationBehaviors` remains a separate project stage.

## Stop condition

Work stops after implementing this production extraction/promotion, static audit, commit and push.

Report:
- final remote commit SHA;
- changed files;
- concise ownership/extraction result;
- confirmation that `EquippedSprintProbe` is removed from active source;
- confirmation that behavior-only and diagnostic twins share `EquippedSprintCollision`;
- confirmation that diagnostics do not own behavior;
- build status;
- material contradictions if any.


## Independent Normal Chat source review

Reviewed implementation:

`218c7ab73815a9afc46fc3ea5ac7246998bc2b1b`

Review result: **PASS — build/runtime still required.**

Confirmed:
- `EquippedSprintProbe.cpp/.h` are removed from active source.
- Permanent `EquippedSprintCollision.cpp/.h` are part of `FRAME_COLLISION_BEHAVIOR_SOURCES`, so behavior-only and diagnostic targets compile the same Sprint behavior authority.
- `EngineBridge` delegates to `EquippedSprintCollision` outside diagnostic compile guards; Sprint behavior is no longer enabled by diagnostics.
- Diagnostic logging inside `EquippedSprintCollision` is fully guarded by `FRAME_COLLISION_DIAGNOSTICS`; behavior state/decisions do not require `CollisionDiagnostics`, `RuntimeClock`, an open log, or diagnostic-only hooks.
- Existing generic attack ownership remains first in `OnAI_PowerAttack`; ordinary marked true Power therefore remains upstream of Sprint behavior.
- Power/2 cannot create a Sprint binding. It can only preserve an already-bound Sprint origin when generation, motion, required-source mask, required-source availability and exact required source identities still match.
- Missing required equipped sources still fail closed before Sprint binding creation.
- Marker authorization remains limited to RIGHT / LEFT / BOTH / OFF.
- `FrameCollisionMarkers` keeps generic source-set, OFF, occurrence/dedupe, marker-window and source-operation behavior.
- Production marker bookkeeping now receives the permanent Sprint authorization directly and canonicalizes execution action to Action9 only for an explicitly authorized bound Sprint execution; factual current `markerAction` remains unchanged for diagnostics.
- Permanent raw55 marker ownership still precedes generic equipped marker dispatch.
- No species, raw2 or other Sprint-specific UseType gate was introduced.
- Raw8/raw55 behavior, hook RVAs, lifecycle repair and target/contact/damage ownership were not changed by the promotion commit.

Static limitations:
- Work did not build either target under the implementation protocol.
- This review therefore cannot establish compile/link correctness, behavior-only startup purity, or runtime equivalence.
- Do not mark equipped Sprint production support accepted until the build/startup/runtime gates frozen below pass.

Next acceptance gate:
1. build `Script_FrameCollisionBehaviorTest`;
2. build `Script_FrameCollisionTest`;
3. verify behavior-only startup/load without diagnostics;
4. run diagnostic EV-322/323/324 compact controls;
5. run behavior-only Goblin Sprint smoke;
6. only then close/archive this promotion contract and promote the behavior baseline to permanent equipped-Sprint production support.


## Local build result

User-local validation after source review:

```text
Knowledge-state validation PASS
Script_FrameCollisionBehaviorTest build PASS
Script_FrameCollisionTest build PASS
```

Interpretation:
- the permanent shared `EquippedSprintCollision` extraction compiles in both product twins;
- compile/link correctness for the changed production surface is established;
- deployment/startup/runtime equivalence is not yet established.

Next gate: deploy **only** `Script_FrameCollisionBehaviorTest.dll`, require POP-03 behavior deployment PASS, launch to main menu, exit normally, and require no startup/load crash. No diagnostic banner/log is expected for the behavior twin.


## Behavior-only deployment and startup result

Behavior twin deployment/startup: **PASS**.

Observed:

```text
Selected live twin: Script_FrameCollisionBehaviorTest.dll
Built SHA256: FE31030B35868EBF30B9644650991D8136625C4DBFD6263403350DB612BDB250
Live  SHA256: FE31030B35868EBF30B9644650991D8136625C4DBFD6263403350DB612BDB250
BEHAVIOR DEPLOYMENT PASS
Gothic 3 reached main menu
normal exit
no startup/load crash
```

Interpretation:
- diagnostics-free behavior twin compiles, deploys as sole live collision twin, and starts cleanly;
- permanent `EquippedSprintCollision` has no startup-time dependency on diagnostic-only infrastructure;
- runtime equivalence is not yet established.

Next gate: redeploy the diagnostic twin and rerun the compact EV-322 / EV-323 / EV-324 acceptance controls from the same source state.


## Diagnostic deployment and startup result

Diagnostic twin deployment/startup: **PASS**.

Observed:

```text
Selected live twin: Script_FrameCollisionTest.dll
Built SHA256: DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A
Live  SHA256: DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A
DIAGNOSTIC DEPLOYMENT PASS
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
Hooks installed.
Script_FrameCollisionTest unloading cleanly.
```

Startup interpretation:
- diagnostic twin is the sole live collision product;
- built/live binary identity matches;
- CORE profile loads and installs behavior hooks;
- clean unload observed.

Minor non-blocking metadata note:
- the diagnostic startup `BehaviorCore:` banner string does not yet enumerate permanent `EquippedSprintCollision`;
- this is a stale descriptive banner only, not evidence that the module is absent from the built behavior core;
- do not change source during this acceptance run, because that would invalidate the pinned diagnostic binary identity above;
- fix the banner in a later bounded diagnostic-metadata cleanup after promotion acceptance.

Next gate: EV-322-equivalent RIGHT -> OFF positive runtime control on this exact diagnostic binary.


## Promoted Sprint runtime control batch — EV-325–EV-327

Diagnostic binary:

`DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`

### EV-325 — intended RIGHT->OFF artifact

Disposition: **NOT EXERCISED AS NAMED / SAFE MIXED FIXTURE**.

The P0 motion actually scanned `RequiredMask=3` and contained BOTH plus later OFF while LEFT was absent. P1 Sprint executions were separate RIGHT-only cases. The file therefore cannot serve as the intended positive RIGHT->OFF control. It showed safe fail-closed/native-fallback behavior and no lifecycle failure.

No rerun is required because EV-326 exercises a stronger positive sequence.

### EV-326 — RIGHT->OFF->RIGHT

Disposition: **PASS**.

Seven complete P0 Sprint C1s (10, 19, 27, 35, 48, 60, 71) repeat:

```text
Action9 Sprint bind
-> RIGHT accepted / 5->7
-> native damage
-> same C1 Action2 continuation
-> OFF accepted / 7->5
-> later RIGHT accepted / 5->7
-> native cleanup / 7->5
-> Outstanding=0
```

This closes the positive continuation runtime gate for the permanent promoted owner and additionally proves same-C1 reactivation after OFF.

### EV-327 — BOTH with LEFT absent

Disposition: **NEGATIVE PASS**.

Five complete P0 Sprint C1s (15, 32, 42, 53, 60) use `RequiredMask=3` with RIGHT present and LEFT absent. Permanent Sprint ownership is not acquired; native RIGHT fallback opens/damages/cleans, BOTH remains rejected, and every C1 finalizes `Outstanding=0`.

This closes the required-source negative runtime gate for production promotion.

### Remaining acceptance

Still required:
1. ordinary equipped true-Power protected control on the same diagnostic binary;
2. diagnostics-free behavior-only Goblin Sprint smoke.

Do not close/archive this promotion contract until both pass.


## EV-328 — ordinary equipped true-Power protected control

Disposition: **PASS**.

Observed on the same pinned diagnostic binary:
- 9 ordinary `PC_Hero Action=2 / POWER` ownership records;
- 9 accepted Flamberge RIGHT markers;
- 9 native Golem damage events;
- zero PC_Hero `EQUIPPED_SPRINT_COLLISION` records;
- zero Sprint-origin continuation signatures;
- zero true-Power marker rejection, repair or lifecycle failure.

Interpretation:
- a new true-Power execution still cannot create or inherit Sprint origin after permanent extraction;
- ordinary equipped Power remains structurally upstream of permanent Sprint behavior;
- all diagnostic runtime promotion controls are now complete.

Remaining acceptance:
1. redeploy the already-built behavior-only twin;
2. run a bounded known Goblin Sprint smoke with the permanent behavior-only product;
3. if gameplay is healthy, close/archive this promotion contract and promote equipped Sprint to permanent production support.

Do not rebuild either twin before the behavior-only smoke; use the already-pinned behavior DLL SHA256 `FE31030B35868EBF30B9644650991D8136625C4DBFD6263403350DB612BDB250`.
