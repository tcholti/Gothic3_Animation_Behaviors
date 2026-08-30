# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — FROZEN WORK TASK: C1-O2-P1 lightweight dispatch bridge

### Why this task exists

The C1-O2 reassessment is complete enough to select one bounded diagnostic candidate.

Established comparison:

```text
old C1-O2 capture
= RunScriptFunction hook + eager Begin/End dispatch capture
= per-dispatch state-stack/top-frame work + actor/entity work + thread_local vector/string bookkeeping
= crashed

ABI-corrected C1-O2 capture
= explicit-this recursion-safe .ThisCall()
= same eager Begin/End capture lifecycle
= still crashed in equivalent registered-ScriptFunction path

current baseline
= same explicit-this recursion-safe RunScriptFunction transport
= pure pass-through only
= stable
```

The old crash therefore cannot be attributed to RunScriptFunction transport alone. The strongest remaining suspect class is the eager capture/lifetime machinery performed around every dispatch.

Later source/runtime evidence also established:

- native `RunScriptFunction` already receives the SPU, runtime-stack reference and ScriptFunction name;
- its native return value already distinguishes suspended/unfinished (`false`) from completed (`true`) ScriptFunction execution;
- the current stable build already performs lazy outer-frame/state-stack inspection only at relevant player offense/cleanup events, including 230 `OUTER_FRAME OFFENSE` observations in the corrected extended run;
- therefore P1 should test only whether a zero-allocation synchronous current-dispatch bridge can coexist safely with native execution.

---

# FROZEN RESPONSIBILITY — C1-O2-P1

Implement only a **diagnostic lightweight current-RunScriptFunction scope bridge** around the already-stable explicit-this `RunScriptFunction` hook.

The question is:

> **Can the stable RunScriptFunction hook carry one nesting-safe, zero-allocation, stack-local current-dispatch scope across the native call, with no engine/API work before the native callback, and expose that scope only when an already-relevant player offensive SetCollisionGroup event occurs?**

This is a diagnostic substrate probe only. It must not yet become C1 execution ownership.

## Frozen implementation shape

Use a tiny stack-local scope in the RunScriptFunction hook translation unit with only the information already supplied by the hook call:

```text
previous/current-scope link
SPU pointer
runtime-stack pointer/reference identity
ScriptFunction-name reference/pointer identity
offense-observed flag
```

Use one `thread_local` pointer to the current scope so nested RunScriptFunction calls naturally form a parent chain through the native C++ call stack.

Normal unrelated RunScriptFunction entry/exit must do only local/TLS pointer bookkeeping plus the original native call. In particular, before calling the original RunScriptFunction, P1 must perform **no**:

- state-stack inspection;
- `GetSelfEntity()` or actor/entity lookup;
- C1 map/record lookup;
- string copy/ownership;
- vector/container push/pop;
- heap allocation;
- logging;
- collision work.

The original/native RunScriptFunction must be called exactly once with the real unchanged arguments through the existing explicit-this recursion-safe hook transport.

## Relevant-event observation

Only after the existing SetCollisionGroup diagnostics have already established a successful offensive request on the player's exact equipped source may P1 inspect the current TLS scope.

At that event only:

- observe whether a current RunScriptFunction scope exists;
- compare its SPU pointer with the already-resolved player SPU by pointer identity;
- compare its runtime-stack address with the actor SPU state-stack address by pointer identity when available through the already-existing diagnostic path;
- log the current ScriptFunction name while its wrapper/reference is synchronously live;
- log whether a parent scope exists, but do not invent parent/outer ownership semantics in P1;
- if the current scope matches the relevant player SPU, set its local `offense-observed` flag.

When that same wrapper returns from native RunScriptFunction:

- restore the previous TLS pointer before any diagnostic logging;
- only if that local scope observed a relevant offense, log its native return result (`false` suspended/unfinished vs `true` completed) and the same transient identities;
- do not persist the scope object or its ScriptFunction-name reference after wrapper return.

Diagnostic support may live in `CollisionDiagnostics.*`, but diagnostics must remain observation-only and must not own the runtime bridge or C1 behavior.

## Allowed source scope

Primary allowed files:

```text
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Do not modify `CollisionLifecycleGuard.*` for P1. Its older dormant C1-O2 Begin/End machinery must remain disconnected.

Use no new hook and no new source module unless a concrete compile/API contradiction proves the frozen implementation cannot be expressed in the allowed files; if that occurs, STOP and report the contradiction.

## Protected behavior

Do not:

- reconnect `BeginScriptFunctionDispatch()` / `EndScriptFunctionDispatch()`;
- acquire or bind a C1 generation from P1;
- change existing CombatMove generation logic;
- change source-obligation or cleanup classification;
- enable physical repair;
- change AISetState/AIFullStop/SetCollisionGroup transport;
- change finalizer semantics;
- alter marker names, marker ownership, marker retirement, source selection or callback suppression;
- add timers, polling, world scans, family/action/input/state-name classifiers or null-argument fallbacks;
- refactor dormant C1-O2 code merely because P1 may later replace it.

The tested collision behavior must remain physically identical to the current baseline.

## Required source audit before commit

Confirm explicitly:

1. generic RunScriptFunction path performs no engine/API calls before the original;
2. no dynamic container/string ownership is introduced on that path;
3. nesting is represented only by stack-local scope + previous TLS pointer;
4. original RunScriptFunction is called exactly once with unchanged arguments;
5. TLS is restored before relevant-return diagnostics;
6. scope/name references never survive wrapper return;
7. offense observation occurs only after the existing exact player-equipped successful-offense gate;
8. no `CollisionLifecycleGuard` behavior changed;
9. physical repair remains disabled;
10. only allowed files changed unless a reported contradiction required stopping.

## Stop conditions

STOP rather than improvise if source/API inspection shows that:

- the hook arguments cannot safely remain referenced for the synchronous wrapper lifetime;
- the current thread/nesting model cannot be represented by a stack-local chained scope;
- logging the relevant scope would require persistent ownership or pre-native engine calls;
- another hook or semantic ownership rule would be required;
- implementation would have to modify C1 lifecycle behavior to make the probe meaningful.

Do not solve continuation retirement, generation reuse, outer-parent selection or physical repair in this Work task.

## Publishing authorization

The User explicitly authorizes Work to publish the audited commits created for this bounded task to:

```text
Repository: https://github.com/tcholti/Gothic3_Animation_Behaviors.git
Branch: docs/collision-source-evidence
```

This authorization is limited to C1-O2-P1 and this exact destination.

## Handoff requirement

After source audit, commit/publish and report only:

- files changed;
- exact P1 bridge/logging behavior implemented;
- confirmation that protected collision/C1 behavior was untouched;
- source/API contradiction if any;
- what still requires independent build/load/runtime verification;
- final remote commit SHA.

Then STOP.
