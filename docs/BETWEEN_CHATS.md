# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Frozen Work task — C1-O2 shadow outer ScriptFunction binding integration

**Date:** 2026-08-29  
**Branch:** `docs/collision-source-evidence`

Read first:

1. `docs/SESSION_ENTRYPOINT.md`;
2. this file;
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
4. only the assigned source/API material below.

C1 remains **shadow-only**. Production physical repair is disabled.

### Purpose / exact question

Implement the smallest shadow integration that answers:

> Can C1 bind its existing monotonic generation to the live outer ScriptFunction frame, acquire a generation when a legitimate equipped-weapon `Item_Attack` request occurs before CombatMove, reuse that same generation when the later CombatMove begins, and retire the native frame binding before address reuse without changing the already-passed cleanup/finalization classification?

C1-O1 already proved in runtime that GetUpAttack has the same live outer ScriptFunction frame at pre-CombatMove offense → later CombatMove → cleanup, while raw frame/arguments addresses can be reused after the previous frame is retired.

### Authoritative source facts

Pinned SDK: `Georgeto/gothic3sdk@90bfd344de4510dda7ac9da7461cc7f1eac911f7`.

Relevant SDK declarations:

```text
gCScriptAdmin::RunScriptFunction(
    bCString const &,
    bTObjStack<gScriptRunTimeSingleState> &,
    gCScriptProcessingUnit *)

gCScriptProcessingUnit::GetSelfEntity()
gCScriptProcessingUnit::m_StateStack
gScriptRunTimeSingleState
```

Tested Game.dll:

```text
Game +0x1604E0  gCScriptAdmin::RunScriptFunction
Game +0x1605E9  indirect registered ScriptFunction call
Game +0x1605EB  first instruction after that call
```

Static behavior already established:

```text
ScriptFunction result false
→ runner returns false without removing the top runtime frame

ScriptFunction result true
→ runner removes the completed top runtime frame before returning true
```

`RunScriptFunction` is generic infrastructure. It is **context only**, never attack ownership by itself.

### Frozen frame-correlation rule

A C1 native outer-frame binding may match only while it is live and must use:

```text
exact gCScriptProcessingUnit *
+ top frame is ScriptFunction (not ScriptState)
+ non-null m_pArguments equal to the bound value
+ same ScriptFunction name
```

Do **not** use as identity authority:

- top-entry address;
- stack index/count;
- break block;
- action/phase/state;
- local callback;
- input;
- attack family.

Break block may legitimately advance during one execution. Raw addresses are not permanent IDs. C1's existing monotonic generation remains the durable plugin-side identity.

If a relevant ScriptFunction has null `m_pArguments`, do not guess a fallback identity: emit a concise diagnostic/invariant and leave that request unacquired by this new route.

### Frozen lifecycle semantics

#### 1. Ordinary CombatMove path

Preserve current C1 behavior when no generation is already bound to the same live outer frame:

```text
new CombatMove initial invocation
→ current candidate-generation path
→ bind that generation to the current live outer ScriptFunction frame from the supplied SPU
```

Existing immediate-true candidate cancellation remains valid for a generation that was created by this CombatMove candidate path.

#### 2. Pre-CombatMove offense acquisition

Add one minimal, nesting-safe transient `RunScriptFunction` dispatch context. It exists only while the registered ScriptFunction call is synchronously executing.

For a successful observed offensive request:

```text
requested group == Item_Attack
AND resulting group == Item_Attack
```

including `7 -> 7`, C1 may acquire a previously unowned request before CombatMove only if:

```text
current RunScriptFunction dispatch context exists
→ supplied SPU is valid
→ actor = SPU GetSelfEntity()
→ current top frame satisfies the frozen live-frame rule
→ changed source entity is exactly that actor's currently equipped RIGHT or LEFT weapon entity
```

Then:

- if no C1 generation exists for that actor/live frame, create one monotonic generation, bind it to that frame, register the exact equipped source(s), and apply the existing offensive-obligation semantics to the actual request;
- if the same actor/live frame already owns a generation, reuse it and apply the request to that generation;
- if another active generation exists for the actor but does **not** match this live frame, do not silently replace/adopt it through the new pre-CombatMove route; log an invariant/overlap and leave the new request unacquired for this experiment.

The pre-CombatMove acquired generation is already outer-execution-owned. It is **not** a CombatMove candidate.

#### 3. Later CombatMove for a pre-acquired execution

At new CombatMove initial invocation:

```text
same actor + same still-live bound outer frame
→ reuse the existing generation
→ attach/observe CombatMove as an inner milestone
→ do NOT create a replacement generation
→ do NOT apply immediate-true candidate cancellation to that pre-acquired generation
```

If no matching live binding exists, preserve the current new-candidate CombatMove behavior.

#### 4. Cleanup

Do not change cleanup authority.

Existing successful transition away from `Item_Attack` fulfills the exact source obligation through the existing source→generation mapping even when cleanup runs under reaction ScriptState/context rather than the old attack ScriptFunction.

#### 5. `RunScriptFunction` return

The wrapper must capture the live frame correlator before calling the original and call the original **exactly once**.

If original returns false:

```text
frame remains live
→ keep its C1 binding
```

If original returns true:

```text
completed native frame has been removed
→ retire/clear that native frame binding before its raw addresses can be reused
```

If the bound generation has no outstanding source obligation, clean bookkeeping retirement/no-op is allowed.

If an obligation is still outstanding at this true-return boundary:

- log a distinct high-signal `OUTER_RETURN_OUTSTANDING`-style shadow invariant containing generation/actor/source/frame context;
- clear/retire the native frame correlator so later pointer reuse cannot match it;
- do **not** physically repair;
- do **not** invent a new fallback/finalization policy to compensate;
- leave the existing destructive AISetState shadow-finalization mechanism unchanged for this task.

Any runtime occurrence of this invariant is a design/test gate failure for later interpretation, not something Work should solve now.

#### 6. AISetState

Preserve the existing C1 AISetState capture/finalization ordering and shadow `WOULD_REPAIR` classification unchanged. C1-O2 must not make RunScriptFunction return, FullStop, or AISetState an unconditional cleanup operation.

### New hook boundary

One new diagnostic/context hook is allowed at tested:

```text
Game +0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
```

Requirements:

- use the official member signature / established hook convention;
- original is called exactly once with unchanged arguments;
- transient dispatch context is nesting-safe;
- generic runner context performs no family/action/input classification;
- verify this prototype does not already install another owner for the same target; if it does, stop and report the conflict instead of chaining blindly.

The hook may provide context to C1, but diagnostics must remain removable from production behavior semantics.

### Allowed source files

Primary allowed files:

```text
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.h
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp
prototypes/Script_FrameCollisionTest/HookBridgeRuntime.h
prototypes/Script_FrameCollisionTest/HookBridgeRuntime.cpp
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp
```

Diagnostic logging support may also change, only if needed for the frozen C1-O2 events:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Do not modify marker behavior files, production `Script_G3AnimationBehaviors`, animation/configuration behavior, unrelated diagnostics, CMake/build structure, or pinned SDK.

### Required diagnostic signal

Keep existing C1/C1-O1 logging. Add only enough high-signal events to verify:

```text
pre-CombatMove outer acquisition + generation
later CombatMove reuse of same generation
ordinary CombatMove-created generation binding
live-frame binding retirement on true return
OUTER_RETURN_OUTSTANDING / frame mismatch / null-arguments failure if they occur
```

Add a distinct C1-O2 startup banner substring for load verification.

Do not add stack dumps or broad per-call `RunScriptFunction` logging. The generic hook must stay quiet unless an event is relevant to C1 binding/acquisition/retirement.

### Protected behavior

Must remain unchanged:

- no physical collision repair;
- existing C1 per-source obligation meaning, including successful `7 -> 7` request attribution;
- existing native cleanup observation;
- existing AISetState shadow finalization and `WOULD_REPAIR` semantics;
- all marker RIGHT/LEFT/BOTH/OFF behavior;
- marker occurrence/replay/execution bookkeeping;
- native collision activation for unmarked attacks;
- Fist/body special semantics;
- OnTick behavior;
- original-call parity of all existing hooks.

### Explicitly forbidden

Do not add:

- GetUpAttack/action/family/input/state-name ownership tables or classifiers;
- adoption of arbitrary already-group-7 weapons;
- unconditional cleanup/finalization on RunScriptFunction return, FullStop or AISetState;
- timers, polling, world scans or per-frame repair;
- persistent raw-pointer identity without explicit lifetime retirement;
- a fallback for null `m_pArguments`;
- production repair;
- marker-core simplification/refactor;
- unrelated cleanup or architectural refactor.

### Required source audit

Before commit, verify at minimum:

1. new `RunScriptFunction` wrapper calls original exactly once and forwards all real arguments unchanged;
2. transient dispatch context cannot leak across wrapper exit and is nesting-safe;
3. frame matching uses only the frozen live-frame rule;
4. no raw frame/arguments address can remain authoritative after true-return retirement or AISetState record removal;
5. pre-CombatMove acquisition requires exact equipped RIGHT/LEFT source ownership by the SPU actor;
6. later matching CombatMove reuses rather than replaces the pre-acquired generation;
7. ordinary existing CombatMove candidate behavior remains unchanged when no pre-acquired match exists;
8. cleanup remains source/consequence based;
9. no physical repair or marker/callback/bookkeeping semantic change was added;
10. `git diff --check` passes for editable source/docs.

### Stop conditions

Stop and report instead of compensating if:

- the tested `RunScriptFunction` signature/hook convention cannot be established from the pinned SDK/current source;
- faithful nesting-safe transient context requires a materially broader runtime architecture than described here;
- a pre-CombatMove request cannot be associated with the SPU actor's exact equipped source without a new ownership guess;
- matching later CombatMove would require action/family/input classification;
- a relevant ScriptFunction has null arguments and the frozen correlator therefore cannot bind it;
- another hook owner for `Game +0x1604E0` is already installed by this prototype and safe single-owner integration is not straightforward;
- implementation would require production repair or marker-core changes.

### Completion boundary

Implementation/source audit only:

```text
edit
→ audit
→ commit/push `docs/collision-source-evidence`
→ replace this handoff with a concise Work result containing files changed, protected behavior, audit result, contradictions if any, runtime work still required, and commit SHA
→ STOP
```

Do **not** build or run Gothic 3 in Work. Normal Chat will independently review the diff before the home-PC build/load/runtime sequence.
