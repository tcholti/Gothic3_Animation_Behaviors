# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — architecture review complete; first modular refactor frozen

C1-R1 controlled validation is closed. Canonical result: **EV-206–EV-207**.

C1-R1 implementation:

```text
93e5a2f2d4839ec908a8940927294217dd961c7a
```

Validated C1-R1 DLL:

```text
Script_FrameCollisionTest.dll
Length: 466432
SHA256: 449AC6BECB38B8627CAFAEA6311F4CC0697B91328A15D63B3446DA4766D3EAB5
Built/live match: True
```

Accepted repair rule remains:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

Everything outside that predicate remains no-op/unresolved and non-mutating. Native cleanup retains precedence. Dual sources remain independent. Marker timing/ownership remains separate from terminal collision safety. Fist/body semantics remain separate from weapon-style Item_Attack cleanup.

Two qualifications remain explicit but do not reopen C1-R1:

```text
1. An outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED case has not been positively runtime exercised.
2. Natural NPC combat and marked Staff traffic support actor-general stability, but no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

---

## Read-only architecture review — COMPLETE

Reviewed bounded source trees:

```text
prototypes/Script_FrameCollisionTest/
src/Script_G3AnimationBehaviors/
```

### Main findings

1. **The validated research DLL is not a rewrite candidate.** It already contains real separations for `CollisionControl`, `CollisionLifecycleGuard`, `CollisionDiagnostics`, and a main file that is the sole physical hook owner.

2. **The main file is still the real engine bridge.** `HookBridgeRuntime` currently provides only the research elapsed-time clock. Hook objects, calling-convention transport, TLS RunScriptFunction scope and pre/original/post dispatch ordering still live in `Script_FrameCollisionTest.cpp`.

3. **Hook ordering/reentrancy is proven behavior and must survive refactoring.** In particular:

```text
RunScriptFunction
→ stack-local/TLS scope remains live across the original call

AICombatMoveInstr
→ BeginCombatMove before original
→ CompleteCombatMoveCandidate after original

AISetState
→ capture exact finalization token before original
→ native AISetState gets first opportunity
→ invalidate/finalize after original

SetCollisionGroup
→ original setter first
→ marker-owned-source retirement / C1 observation afterward
→ C1-R1 repair deliberately re-enters this same shared setter path
```

4. **`CollisionControl` currently owns too many responsibilities.** It combines marker scanning/cache, attack-family qualification, equipped-source lookup, Fist identification, duplicate suppression, authored occurrence budgets, marker-execution inference, marker-owned windows, source-set switching, physical activation/deactivation, repeated-contact rearm and StatePosition handling.

5. **The lifecycle guard is semantically strong but structurally coupled to marker code.** `CollisionLifecycleGuard.cpp` currently includes `CollisionControl.h` primarily to obtain generic equipped-source information. That dependency should be removed before larger hook/module extraction.

6. **Marker bookkeeping divides into two categories.** C1/native execution identity may later replace some old execution-lifetime inference, but it does not replace independent marker invariants.

Potential later simplification candidates:

```text
animation/action/phase/source-snapshot/state-time rollback used only to infer a new marker execution
controlled-callback retirement based on key change/state-time rollback
MarkerWindowStillMatchesActorExecution lifetime inference
```

Must remain until independently replaced/proven:

```text
exact current-motion marker ownership
authored per-opcode occurrence budgets
same-update duplicate/replay protection
RIGHT/LEFT/BOTH/OFF exact-set ownership
repeated-contact ClearTriggeredList rearm
StatePosition behavior required to suppress competing native activation
marker-owned source/window state so OFF closes only marker-owned offense
dead/late execution rejection
```

7. **Fist already behaves like a different source adapter.** Current marker code detects Fist/PhysicalFist, skips weapon-style `SetCollisionGroup(Item_Attack)`, and still rearms `TouchDamage` through `ClearTriggeredList()`. EV-207 confirms Fist remains outside weapon-style C1 obligations. Do not collapse this distinction during modularization.

8. **Research-only diagnostic hooks are separable from production behavior.** Current `OnTick`, `PlayMotion`, `StopMotion`, `AICombatMoveStartRecover`, and current `AIFullStop` usage are diagnostic probes. `AICombatMoveInstr`, `AISetState`, `SetCollisionGroup`, `RunScriptFunction`, attack callbacks and `StartEffect` contain current behavior-required responsibilities (some also emit diagnostics).

9. **The existing production DLL is only superficially modular.** `AttackRaise` and `AttackSpeed` are separate files but each directly owns its own hook, both duplicate player/2H matching, configuration is two globals, and no common engine bridge/profile matcher exists. `AttackSpeed` directly hooks `GetAnimationSpeedModifier`, a documented New Balance compatibility concern. It remains proof-of-concept only.

10. **One suspected dead historical path was found but is NOT part of the first refactor.** `CollisionLifecycleGuard::BeginScriptFunctionDispatch` / `EndScriptFunctionDispatch` and their internal dispatch stack appear unused by the current research main path. Verify/remove separately rather than mixing cleanup into the first modular extraction.

11. **One cache risk was noted but is NOT part of the first refactor.** `GetCurrentMarkerDecision` currently caches by animation name even when exact matching-motion resolution fails. Tests pass, so do not change this opportunistically; revisit during the later marker audit.

---

## Frozen next implementation responsibility — extract generic collision-source queries only

This is the **smallest behavior-preserving modular refactor** and must be implemented in `prototypes/Script_FrameCollisionTest` only.

### Exact responsibility

Create:

```text
prototypes/Script_FrameCollisionTest/CollisionSources.h
prototypes/Script_FrameCollisionTest/CollisionSources.cpp
```

Move exactly these existing generic source-query functions out of `CollisionControl` into namespace `FrameCollision::CollisionSources` without changing their logic:

```text
GetEquippedCollisionSources(Entity &actor)
GetCollisionSourceUseType(Entity &source)
HasRequiredCollisionSources(EquippedCollisionSources const &sources, unsigned int requiredMask)
```

Then update only the necessary includes/call sites so:

```text
CollisionLifecycleGuard
CollisionControl
CollisionDiagnostics
Script_FrameCollisionTest main/bridge
```

consume those generic queries through `CollisionSources` rather than through `CollisionControl`.

Add the two new files to the research target CMake source list.

### Explicitly preserved in this step

```text
FrameCollisionShared.h types and SourceMask values remain where they are
CollisionControl marker semantics remain byte-for-byte equivalent in meaning
all marker maps/budgets/windows remain
Fist detection/activation behavior remains
all hook objects/wrappers/targets/calling conventions remain in the main file
RunScriptFunction TLS scope remains unchanged
AICombatMoveInstr ordering remains unchanged
AISetState capture/original/finalize ordering remains unchanged
SetCollisionGroup original/retirement/C1-observation ordering remains unchanged
C1-R1 repair re-entry through SetCollisionGroup remains unchanged
CollisionDiagnostics behavior/log vocabulary remains unchanged
no dead-code removal
no cache change
no marker-family expansion
no marker simplification
no bad-skip prevention
no production-DLL migration
no Raise/speed/config behavior change
```

### Why this is first

It removes the lifecycle guard's dependency on the marker-control module while avoiding the higher-risk calling-convention/reentrancy work of moving hook wrappers. It creates the physical-source module seam we will later need for equipped weapons vs Fist without prematurely designing the Fist adapter.

### Required implementation audit

Before commit/publish:

```text
- inspect only source needed for this extraction;
- verify the three moved function bodies are semantically unchanged;
- verify no old CollisionControl declarations/call sites remain for those three functions;
- verify no hook wrapper or hook installation line changed;
- verify no marker behavior/state structure changed;
- build Script_FrameCollisionTest successfully;
- run git diff --check on editable source;
- commit/publish only this bounded refactor.
```

No Gothic 3 runtime matrix is required for this first source-query extraction alone. If build/source audit exposes a concrete contradiction, stop rather than broadening the refactor.

---

## Mandatory post-EngineBridge source-review gate

After the source-query extraction, the next structural implementation may extract/define the real central `EngineBridge` while preserving the proven hook targets, calling conventions, recursion safety and pre/original/post ordering.

**After that EngineBridge extraction, do not proceed directly to marker simplification.** First perform a complete read-only source-review gate over every `.cpp` in `prototypes/Script_FrameCollisionTest`, one file at a time.

For each `.cpp`, explicitly review:

```text
- one-sentence responsibility / what the file is allowed to own;
- dependencies and whether dependency direction matches the modular architecture;
- behavior-critical code vs diagnostic-only code;
- state/data ownership and lifetime;
- calling-convention / hook-order assumptions where relevant;
- duplicated responsibility, dead historical paths or unnecessary coupling;
- marker/lifecycle/source invariants the file must preserve;
- New Balance / Jackydima compatibility risk where relevant;
- verdict: accepted as-is, or requires a separately frozen bounded correction.
```

Do not perform opportunistic feature expansion during this review. If a correction is needed, freeze it separately, apply only that correction, and re-review the affected responsibility before the gate is considered complete.

Only when every research-DLL `.cpp` has an explicit accepted disposition may the project continue to marker-bookkeeping simplification.

### Diagnostics / logger review inside this gate

`CollisionDiagnostics.cpp` receives a dedicated evidence-volume audit during the per-file review.

Goal:

> Preserve all information needed to prove the collision/marker/lifecycle system correct while stopping routine runs from emitting historical deep-probe data that no longer answers an active question.

Classify diagnostic output into:

```text
CORE COLLISION EVIDENCE
= retained for ordinary collision development/regression

OPT-IN DEEP PROBES
= retained in code or a diagnostic mode for a specific investigation,
  but disabled during ordinary runs

OBSOLETE HISTORICAL NOISE
= removable only when its durable conclusion already exists in canonical evidence
  and no current/future collision responsibility needs the runtime signal
```

Likely core signals include exact marker ownership/result, source SetCollisionGroup transitions, C1 generation/offense/cleanup/finalization outcomes, P2 bridge events when they occur, explicit invariant/failure records, build identity and clean unload.

Likely deep-probe candidates include broad PrimaryFirst PlayMotion/StopMotion snapshots, OnTick lifetime observation, StartRecover stacks, AIFullStop callsite/input stacks, broad AISetState/outer-frame stack snapshots and full native-cleanup stack dumps. These are **candidates only** until the file review verifies that no active collision responsibility still depends on them.

The preferred result is not a less precise logger. It is a **tiered logger**: compact exact evidence by default, with deep diagnostics enabled only when a concrete investigation needs them.

### Validation sequencing

Do not change EngineBridge behavior and logger output before the same runtime baseline.

Preferred order:

```text
EngineBridge extraction
→ build/source audit
→ one-by-one read-only .cpp review, including diagnostics classification
→ compact runtime collision baseline using the unchanged existing logger
→ if baseline passes, freeze/implement approved logger reduction separately
→ prove the reduced/default logger still exposes every required collision signal
→ only then begin marker-bookkeeping simplification
```

This preserves causal attribution: a structural behavior regression cannot be hidden by a simultaneous change to what the logger records.

---

## Agreed forward roadmap after this step

```text
source-query extraction
→ extract/define real central EngineBridge while preserving proven hook order/reentrancy
→ mandatory one-by-one .cpp source-review gate
→ compact structural collision-baseline runtime revalidation with existing logger
→ approved diagnostics/logger reduction into core default + opt-in deep probes
→ diagnostic sufficiency regression
→ marker-bookkeeping simplification audit against C1 authority
→ equipped-melee marker expansion one mechanism at a time
→ separate Fist source-adapter investigation/decision
→ full marker + lifecycle regression
→ modular AttackContinuationProtection investigation/implementation
→ guard + markers + continuation regression
→ mandatory New Balance/Jackydima compatibility on mature research DLL
→ redesign/migrate collision modules into modular Script_G3AnimationBehaviors
→ independent Raise + redesigned speed work
→ final full Script_G3AnimationBehaviors + New Balance/Jackydima compatibility regression
```

Overall architecture authority: `docs/DESIGN.md` §§10–11.  
Diagnostic authority: `docs/COLLISION_LOGGER_PLAN.md`.  
Staged validation authority: `docs/COLLISION_TEST_PLAN.md`.  
Future held-Use2 prevention: `docs/BAD_SKIP_FUTURE_INVESTIGATION.md`.
