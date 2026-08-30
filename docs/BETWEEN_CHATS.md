# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — FROZEN WORK TASK: C1-O2-P2 lazy pre-Combat acquisition

### Established result

C1-O2-P1 passed source audit, isolated load/unload and targeted meaning validation. The lightweight `RunScriptFunction` bridge is stack-local/TLS only and did not reproduce the old eager-capture crash.

Four reproduced GetUpAttack executions showed the same ordering:

```text
live _AI_GetUpAttack RunScriptFunction
→ legitimate equipped-source Item_Attack 5 -> 7
→ matching player CombatMove begins in the same live ScriptFunction frame
→ RunScriptFunction later returns false / suspends
→ later timer 7 -> 7 occurs with no live RunScriptFunction scope
```

At each initial GetUp offense the P1 scope existed, its SPU and runtime-stack identity matched the player SPU/state stack, the ScriptFunction was `_AI_GetUpAttack`, and the later dispatch return was `GEFalse`. Ordinary Normal/Quick timer offense usually had no live P1 scope even though its ScriptFunction remained suspended on the SPU.

Therefore P2 must test the smaller model first: **native ScriptFunction identity is a temporary bridge from pre-Combat offense to matching CombatMove, not persistent execution identity across suspension.** C1's monotonic generation remains the durable plugin identity.

---

# FROZEN RESPONSIBILITY — C1-O2-P2

Implement only **lazy pre-Combat C1 generation acquisition plus temporary bridge consumption**.

The question is:

> **Can C1 use the proven P1 live `RunScriptFunction` scope only at a successful exact equipped-source pre-CombatMove offense to acquire its existing monotonic generation, let matching CombatMove in that same live ScriptFunction invocation reuse that generation, then consume/retire the native-frame bridge before `RunScriptFunction` returns — without reconnecting the rejected eager dispatch machinery or changing cleanup/finalization/physical collision behavior?**

## Required architecture

Keep the existing P1 stack-local/TLS scope. Do not add another per-dispatch container or persistent dispatch object.

At a successful `Item_Attack` result, the current P1 scope may be exposed to `CollisionLifecycleGuard` as a **transient non-owning view** containing only hook-supplied identities needed for validation, such as:

```text
SPU pointer
runtime-stack pointer
ScriptFunction-name reference
```

Only at that real offense event may C1 perform actor/equipped-source/state-stack work.

Pre-Combat acquisition is allowed only when all of these are true:

1. a current P1 scope exists;
2. its SPU is valid;
3. its runtime-stack identity is the same SPU state stack;
4. that SPU's current top frame is a real ScriptFunction;
5. the top frame has non-null `m_pArguments`;
6. top ScriptFunction name matches the live wrapper ScriptFunction name;
7. the offensive source is the exact currently equipped RIGHT and/or LEFT source of that SPU actor;
8. no incompatible C1 generation/binding already owns the actor/source.

No family/action/input/GetUp/state-name classifier is allowed.

When those conditions pass:

```text
real pre-Combat offense
→ create/reuse one C1 monotonic generation
→ bind that generation temporarily by SPU + arguments + ScriptFunction name
→ attribute the real source obligation to that generation
→ return a tiny generation/bridge token to the same stack-local P1 scope
```

The temporary binding may copy only the minimum lifetime-bound identity needed between the relevant offense and matching CombatMove. Any allocation/string ownership here is event-driven, not per generic `RunScriptFunction` dispatch.

## Matching CombatMove

`BeginCombatMove()` must preserve the existing ordinary path when no matching pre-acquired binding exists.

When the current CombatMove frame exactly matches a pre-acquired binding by:

```text
same actor
same SPU
same non-null arguments pointer
same ScriptFunction name
```

it must:

```text
reuse the SAME C1 generation
→ mark that already-real generation as persisted/owned by the CombatMove path
→ consume/retire the temporary native-frame binding immediately
→ keep the durable generation and source obligation alive
```

Do not wait for later ScriptFunction continuation/return to make the generation durable. The pre-Combat generation is already real because an actual offensive request occurred.

The existing ordinary CombatMove-created candidate/result semantics must remain unchanged when there was no matching pre-acquired generation.

## Wrapper return safety

The P1 stack-local scope may retain only a tiny C1 generation/bridge token needed to detect whether its pre-Combat bridge was consumed.

After native `RunScriptFunction` returns and TLS has been restored:

- if the bridge was already consumed by matching CombatMove, no native binding remains;
- if a pre-Combat bridge is still active, emit a dedicated diagnostic invariant and retire that native binding before the wrapper returns;
- do **not** keep the raw native-frame binding alive across suspension;
- do **not** discard an already-real outstanding C1 source obligation merely because the bridge was not consumed;
- do **not** invent fallback continuation ownership or physical repair.

This makes an unconsumed bridge a falsifiable P2 result without exposing later raw-pointer reuse.

## Rejected machinery remains rejected

Do not reconnect or depend on:

```text
g_ScriptFunctionDispatchStack
BeginScriptFunctionDispatch()
EndScriptFunctionDispatch()
```

Do not restore per-dispatch vector mutation, copied strings, eager state-stack capture, actor lookup or logging around every `RunScriptFunction` call.

Dormant legacy declarations/functions may remain disconnected unless a small bounded cleanup is strictly necessary for the P2 implementation. Do not refactor them merely for tidiness.

## Protected behavior

Do not:

- add parent/outer fallback selection;
- persist the P1 scope or ScriptFunction-name reference beyond wrapper return;
- add null-arguments fallback;
- adopt arbitrary group-7 state without a real successful offense request;
- change exact source-obligation or native-cleanup semantics;
- change AISetState finalization semantics;
- change AISetState/AIFullStop/SetCollisionGroup/RunScriptFunction hook transport;
- enable physical repair;
- change marker names, marker ownership, marker retirement, source selection or callback suppression;
- add timers, polling or world scans.

Physical collision behavior must remain unchanged.

## Primary source scope

Expected files are limited to the existing owners of this responsibility:

```text
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.h
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h        only if needed
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp      only if needed
```

Use no new hook or source module. If a concrete source/API contradiction requires a broader design, STOP and report it.

## Required source audit

Confirm before publish:

1. generic `RunScriptFunction` still performs only stack-local/TLS bookkeeping plus the original call before native execution;
2. no old dispatch vector/Begin/End path was reconnected;
3. pre-Combat state-stack/actor/C1 work occurs only after a real successful offense with a live current scope;
4. exact equipped-source and live-frame rules are enforced without family/state classifiers;
5. one pre-acquired generation is reused, not replaced, by matching CombatMove;
6. the temporary native binding is retired at matching CombatMove;
7. an unconsumed bridge cannot survive wrapper return;
8. ordinary CombatMove-created generation behavior is unchanged;
9. source cleanup and AISetState finalization semantics are unchanged;
10. physical repair remains disabled.

## Stop conditions

STOP rather than improvise if:

- matching CombatMove cannot safely reuse the pre-acquired generation without changing ordinary C1 semantics;
- the native binding would have to survive `RunScriptFunction` return to make the tested GetUp path work;
- source/API reality requires parent-scope selection, null-argument fallback, another hook or production classification;
- safe wrapper-return retirement would require dropping a real outstanding source obligation.

## Publishing authorization

The User authorizes bounded P2 implementation commits to:

```text
Repository: https://github.com/tcholti/Gothic3_Animation_Behaviors.git
Branch: docs/collision-source-evidence
```

After source audit, publish and report only: files changed, exact P2 behavior, confirmation protected behavior stayed unchanged, any contradiction, what still needs build/runtime verification, and final remote SHA. Then STOP.
