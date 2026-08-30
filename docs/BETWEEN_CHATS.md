# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — CollisionSources extraction CLOSED; EngineBridge extraction design/freeze next

C1-R1 controlled validation remains closed. Canonical result: **EV-206–EV-207**.

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

## First modular refactor — generic CollisionSources extraction CLOSED

Implementation commit:

```text
43fa1e719b5af716c54e17430c101251bbc36ff8
```

Created:

```text
prototypes/Script_FrameCollisionTest/CollisionSources.h
prototypes/Script_FrameCollisionTest/CollisionSources.cpp
```

Moved unchanged into `FrameCollision::CollisionSources`:

```text
GetEquippedCollisionSources(Entity &actor)
GetCollisionSourceUseType(Entity &source)
HasRequiredCollisionSources(EquippedCollisionSources const &sources, unsigned int requiredMask)
```

Result:

```text
CollisionLifecycleGuard no longer depends on CollisionControl for generic equipped-source lookup.
CollisionControl uses CollisionSources for source queries.
Script_FrameCollisionTest main/bridge uses CollisionSources directly.
CollisionDiagnostics remains textually unchanged for now through temporary using aliases in CollisionControl.h.
The helper implementations exist only in CollisionSources.
```

Validation:

```text
detached exact diff/source audit = PASS
no hook wrapper/target/install change = PASS
no marker state/semantics change = PASS
no lifecycle decision change = PASS
no Fist behavior change = PASS
git diff --check = PASS (no output before successful build)
local CMake Release build of Script_FrameCollisionTest = PASS
Gothic 3 runtime matrix = not required for this low-risk query extraction
```

The temporary diagnostic aliases are intentionally deferred to the later dedicated `CollisionDiagnostics.cpp` review; do not treat them as a second implementation or permanent architecture.

---

## Current Normal-Chat responsibility — design/freeze real central EngineBridge extraction

Do not edit source until this responsibility is frozen.

### Intended structural goal

`Script_FrameCollisionTest.cpp` is currently the real physical hook owner even though the hook-transport responsibility is not named as its own module. Extract that transport into a dedicated central module without changing tested semantics.

Preferred narrow target:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

`EngineBridge` should become the sole owner of:

```text
all mCFunctionHook objects
all Gothic hook/callback wrapper functions
RunScriptFunctionScope TLS transport state
hook-local helper functions required only by those wrappers
InstallHooks()
```

`Script_FrameCollisionTest.cpp` should remain the DLL entry/composition root only:

```text
HookBridgeRuntime::InitializeClock()
CollisionDiagnostics::OpenLog()
EngineBridge::InstallHooks()
GetScriptInit()
DllMain / log close
```

`HookBridgeRuntime` remains the existing research clock in this step. Do not rename or merge it into EngineBridge yet.

### Proven ordering/reentrancy that must be preserved exactly

```text
RunScriptFunction
→ stack-local/TLS scope installed before original
→ original called exactly once with unchanged arguments
→ TLS restored after original
→ temporary pre-Combat bridge retired after original if still active
→ offense-scope return logging remains after TLS restore

AICombatMoveInstr
→ BeginCombatMove before original for initial non-fullStop candidate
→ original called exactly once
→ CompleteCombatMoveCandidate after original

AISetState
→ capture finalization token before original
→ diagnostic pre-state capture remains before original
→ original AISetState called exactly once
→ InvalidateScriptFunctionDispatchAfterAISetState after original
→ FinalizeAfterAISetState after original
→ diagnostic post-state capture remains after finalization

SetCollisionGroup
→ capture before/caller/cleanup diagnostic context before original
→ real setter executes first
→ marker-owned-source retirement after original when resulting group leaves Item_Attack
→ C1 ObserveCollisionGroupResult after original using resulting group
→ diagnostic SetCollisionGroup / outer-frame observation remains after lifecycle observation
→ C1-R1 repair continues to re-enter this same shared SetCollisionGroup hook path

AIFullStop / PlayMotion / StopMotion / StartRecover / OnTick
→ diagnostic-only behavior and original-call ordering remain exactly unchanged

StartEffect / attack callbacks
→ current marker ownership/suppression semantics remain exactly unchanged
```

### Explicit non-goals for EngineBridge extraction

Do not combine this move with:

```text
hook target/RVA changes
calling-convention changes
new hook chaining/compatibility work
marker simplification
marker-family expansion
Fist changes
lifecycle simplification/dead dispatch cleanup
logger reduction
renaming HookBridgeRuntime
AttackContinuationProtection
production DLL migration
Raise/speed/config work
New Balance integration
```

The extraction is structural only: move existing hook transport as one unit and expose only the minimum module entrypoint needed by DLL composition.

### Expected minimum EngineBridge public API

```cpp
namespace FrameCollision::EngineBridge
{
void InstallHooks();
}
```

Do not publish feature-specific hook internals through the header unless implementation proves a concrete need.

### Required implementation validation after freeze

```text
- inspect only the current Script_FrameCollisionTest hook owner and direct dependencies;
- move hook objects/wrappers/TLS/helper transport without semantic edits;
- verify every original-function call remains exactly once and in the same relative order;
- verify .ThisCall() remains on RunScriptFunction, AISetState, AIFullStop and SetCollisionGroup;
- verify hook RVAs/script callbacks are unchanged;
- verify ScriptInit order remains clock → log → hook install;
- verify CollisionLifecycleGuard / CollisionControl / CollisionSources behavior files are otherwise untouched;
- git diff --check;
- successful local CMake Release build;
- commit/publish only the structural extraction.
```

After this higher-risk hook extraction, do **not** begin marker simplification. Proceed to the mandatory per-CPP review gate below.

---

## Mandatory post-EngineBridge source-review gate

After EngineBridge extraction/build passes, perform a complete read-only source-review gate over every `.cpp` in `prototypes/Script_FrameCollisionTest`, one file at a time.

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

Likely deep-probe candidates include broad PrimaryFirst PlayMotion/StopMotion snapshots, OnTick lifetime observation, StartRecover stacks, AIFullStop callsite/input stacks, broad AISetState/outer-frame stack snapshots and full native-cleanup stack dumps. These are candidates only until the file review verifies that no active collision responsibility still depends on them.

The preferred result is not a less precise logger. It is a tiered logger: compact exact evidence by default, with deep diagnostics enabled only when a concrete investigation needs them.

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

## Agreed forward roadmap

```text
CollisionSources extraction — CLOSED
→ EngineBridge structural extraction — current design/freeze responsibility
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
