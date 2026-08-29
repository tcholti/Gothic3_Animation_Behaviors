# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — SetCollisionGroup transport prerequisite agreed / Work not yet frozen

- Universal-guard-first architecture remains authoritative. The known held-Use2 bad abandonment remains a destructive stress case, not a production classifier, balance fix, or reason to alter Community Patch / Alternative AI / New Balance behavior.
- C1 physical repair remains disabled. Direct C1-O2 `RunScriptFunction` dispatch capture remains suspended. `RunScriptFunction` remains recursion-safe pure pass-through.
- AISetState and AIFullStop have both passed their isolated explicit-this `.ThisCall()` transport stability gates. AIFullStop implementation: `18ff183e05b599de9e035722b15e3bfb6cbbc034`; validated DLL SHA256 `89329667BF83479E419C2775965E0CC41769F2BFD247F84C95939B673292B13B`; extended evidence commit `72273ead0ae7821a0d70b2e3b168ad00a1271f1a`; hook-transport evidence continuation `docs/EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-200.
- The AIFullStop run is **PASS for tested transport stability**, but does not prove that the original direct C1-O2 registered-ScriptFunction crash is solved.
- Closed/processed B6–B9, C1 core, C1-O1, AISetState stability and AIFullStop stability raw logs have been moved to `research/archive/`. The unresolved C1-O2 crash artifacts intentionally remain in `research/raw/` as active diagnostic context.
- Repository housekeeping also added a narrow `.gitattributes` rule so future runtime `.log` evidence is stored byte-faithfully rather than newline-normalized. The already-committed AIFullStop run remains valid; its recorded local pre-normalization SHA256 is the canonical original-local hash.

### SetCollisionGroup prerequisite — Normal Chat inspection complete

The exact current wrapper was inspected on branch `docs/collision-source-evidence` after the AIFullStop result.

Current source facts:

- `SetCollisionGroup_FrameCollisionTest` is currently a member-hook wrapper with signature `static void GE_STDCALL SetCollisionGroup_FrameCollisionTest(eECollisionGroup a_Group)`.
- It obtains the entity through legacy shared hook transport: `Hook_SetCollisionGroup.GetSelf<eCEntity *>()`.
- The hook target is the tested `Engine +0x225660` path.
- The install still uses legacy explicit hook-type transport: `.Prepare(..., mCBaseHook::mEHookType_ThisCall).Hook()`.
- The pinned Gothic 3 SDK declares `eCEntity::SetCollisionGroup(eECollisionGroup)` as an `eCEntity` member. Therefore there is **no SDK/API contradiction** to an explicit per-invocation `eCEntity *this` member-hook transport correction.
- This hook is directly relevant to C1 rather than merely another old hook: it is the exact observation path by which C1 sees successful offensive `Item_Attack` requests, including inherited `7 -> 7`, and later native cleanup fulfillment.

The current semantic ordering must remain unchanged:

```text
capture caller / exact pre-call entity collision state and any existing cleanup diagnostics
→ call the native original exactly once
→ perform existing marker-owned-source retirement logic from the native result
→ read exact post-call collision group
→ CollisionLifecycleGuard::ObserveCollisionGroupResult(...)
→ existing SetCollisionGroup diagnostics / remaining existing observations
```

### Agreed bounded correction

The User explicitly agreed in Normal Chat on 2026-08-29 to the following next prerequisite:

> Isolate `SetCollisionGroup` transport only. Convert that one hook from shared `GetSelf<eCEntity *>()` transport to explicit per-invocation `eCEntity *this` plus the already-proven recursion-safe `.ThisCall()` pattern, while preserving the exact before → native original → after → marker retirement → C1 observation → diagnostics semantics and ordering. Do not automatically harden unrelated remaining legacy hooks. After this isolated implementation/stability result, reassess C1-O2 directly.

No Work task has been frozen yet. This is intentional: the Chat is being migrated at this clean responsibility boundary.

### Immediate responsibility for the fresh Normal Chat

After completing the full `docs/SESSION_ENTRYPOINT.md` Fresh Normal Chat Bootstrap:

1. recognize that the API/source inspection and User agreement above are already complete; **do not ask the User to reconfirm them and do not repeat the investigation**;
2. freeze the bounded `SetCollisionGroup` transport-only Work task from the facts below;
3. give the User the short Work launcher used by the current collaboration protocol;
4. Work may inspect only the implementation/API details required by that frozen task, edit only the permitted source files, run the source audit, commit/push, report the short handoff, and STOP — no build or runtime test in Work;
5. Normal Chat then independently reviews the actual source diff before any local build/deploy/test.

Expected implementation shape to freeze unless a new concrete source contradiction is discovered:

```text
SetCollisionGroup_FrameCollisionTest receives explicit eCEntity *a_pThis plus eECollisionGroup a_Group
remove Hook_SetCollisionGroup.GetSelf<eCEntity *>()
use that exact per-invocation this for every existing before/after/retirement/C1/diagnostic operation
call the original exactly once with that same exact this and a_Group
install only SetCollisionGroup through the recursion-safe .ThisCall() builder pattern at Engine +0x225660
preserve _ReturnAddress() at the same logical entry point
preserve all existing collision, marker-retirement, C1 lifecycle and diagnostic ordering/semantics
optionally add only the narrow startup identity banner required to identify this transport baseline
```

Protected during this Work task:

```text
AICombatMoveInstr unchanged
AISetState unchanged
AIFullStop unchanged
RunScriptFunction unchanged pure pass-through
StartEffect unchanged
PlayMotion unchanged
StopMotion unchanged
all attack callbacks unchanged
CollisionLifecycleGuard generation / obligation / fulfillment / finalization semantics unchanged
marker behavior and marker execution bookkeeping unchanged
no physical repair
no Raise or playback-speed work
no held-Use2 / 2500-ms / Community Patch / Alternative AI / New Balance behavior changes
no C1-O2 dispatch capture restoration
no mechanical conversion of every remaining legacy ThisCall hook
```

Likely allowed edit surface for the frozen Work task:

1. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
2. `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp` only if the narrow startup identity banner is added

The Work source audit should explicitly verify:

1. explicit `eCEntity *this` is received per invocation;
2. no `Hook_SetCollisionGroup.GetSelf<eCEntity *>()` remains in this wrapper;
3. `_ReturnAddress()` remains at the same logical entry point;
4. native original is called exactly once;
5. the exact explicit `this` and requested group are forwarded to the original;
6. pre-call state/cleanup-stack capture still occurs before native original;
7. marker-owned-source retirement still occurs only after native original using the resulting collision state;
8. `CollisionLifecycleGuard::ObserveCollisionGroupResult(...)` still sees the exact same requested/result semantics and remains after the native result is known;
9. existing SetCollisionGroup diagnostics and any remaining observations preserve their ordering and fields;
10. only SetCollisionGroup changes transport style; AISetState, AIFullStop and RunScriptFunction are unchanged;
11. no collision/lifecycle/marker/gameplay semantics are added or removed;
12. only the permitted files changed;
13. `git diff --check` passes.

If implementation inspection exposes a real API/calling-convention contradiction, Work must STOP and report it rather than improvising.

After the isolated transport implementation passes independent source review and later runtime stability validation, reassess C1-O2 directly. Do **not** assume StartEffect, PlayMotion or StopMotion must be converted first merely because they still use legacy transport.
