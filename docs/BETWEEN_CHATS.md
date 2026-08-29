# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — FROZEN WORK TASK: C1 finalization source-liveness safety

### Why this task exists

The SetCollisionGroup extended gameplay run at implementation `fbb300065af2f9119531e06949eac59c2586a519` crashed, but exact crashed-DLL disassembly has now superseded the initial transport-failure interpretation.

Canonical evidence authority: `docs/EVIDENCE_LEDGER_STEP_C.md` EV-202.

The exact crashed DLL SHA256 was:

```text
C5D85C44A751C68BB956C2F1D6C9ABE6E889BDBB3363FDC328158F2933DA0397
```

The crash dump's machine stack contained direct return address `Script_FrameCollisionTest` RVA `0xD839`. User-run `dumpbin` on that exact DLL proves:

```text
RVA 0xD833: call imported eCEntity::GetCollisionGroup()
RVA 0xD839: instruction immediately after that call
```

This call is inside `CollisionLifecycleGuard::FinalizeAfterAISetState()`.

The higher summarized crash frame, DLL RVA `0x10802`, is the instruction immediately after the AISetState wrapper calls `FinalizeAfterAISetState()`.

Therefore the observed crash path is:

```text
AISetState wrapper
→ native AISetState original
→ CollisionLifecycleGuard::FinalizeAfterAISetState()
→ remembered raw sourceInstance pointer
→ sourceInstance->GetCollisionGroup()
→ Engine +0x225650
→ internal lookup result FFFFFFFF dereferenced
→ EXCEPTION_ACCESS_VIOLATION
```

This is a C1 post-AISetState source-liveness defect. It is **not evidence that SetCollisionGroup `.ThisCall()` transport failed**. SetCollisionGroup's extended validation was interrupted after 307 logged SetCollisionGroup blocks; it remains not fully validated, but there is no current evidence requiring rollback.

A bounded User control with the research DLL removed also reproduced persistent stale offensive collision for roughly five minutes or more: ordinary running did not clean it, repeated contact damaged many NPCs and provoked attacks, and no crash occurred during that control. Treat this only as bounded supporting observation, not proof that stale collision can never crash.

---

# FROZEN RESPONSIBILITY

Make **only** `CollisionLifecycleGuard::FinalizeAfterAISetState()` source-liveness-safe so it never dereferences a remembered raw collision-source pointer whose current liveness has not been established through the current equipped-source snapshot.

This is an **observation/classification safety correction only**.

It must not change gameplay collision behavior, C1 repair state, attack classification, marker semantics, hook transport, or C1-O2 state.

## Allowed source edit surface

Only:

```text
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp
```

Do not edit any other production/prototype source file.

Documentation changes are limited to the normal audited Work handoff/status update required by `docs/WORK_IMPLEMENTATION_PROTOCOL.md`; do not broaden design documentation.

## Required implementation behavior

Inside `FinalizeAfterAISetState()`:

1. Preserve the existing token/generation validation and current equipped-source snapshot.
2. For each remembered `SourceLifecycleRecord`, determine current side/equipped identity using **pointer comparison only** against the current equipped-source snapshot **before any method call or dereference through `source.sourceInstance`**.
3. A remembered source pointer that is not currently one of the equipped source instances is **not established live for C1 finalization**.
4. For a source whose liveness is not established:
   - do **not** call `source.sourceInstance->GetCollisionGroup()`;
   - do **not** pass that pointer to `GetEntityName()` or any other helper/member that dereferences the entity;
   - do not physically repair or modify the entity;
   - if `outstandingCleanup == true`, preserve classification as `UNRESOLVED_NOT_EQUIPPED`;
   - if `outstandingCleanup == false`, preserve classification as `NO_OP_NO_OUTSTANDING`;
   - preserve machine-readable diagnostics by explicitly recording that the remembered source was not dereferenced / liveness was not established. A numeric sentinel such as `ActualGroup: -1` is acceptable if accompanied by an explicit liveness/dereference diagnostic so it cannot be mistaken for an observed physical group.
5. For a source that **is** still currently equipped:
   - current-source identity establishes the bounded liveness prerequisite for the existing finalization observation;
   - preserve the existing `GetCollisionGroup()` observation;
   - preserve existing classification semantics:
     - no outstanding obligation → `NO_OP_NO_OUTSTANDING`;
     - outstanding + actual group not `Item_Attack` → `NO_OP_PHYSICALLY_CLEAN_RECONCILED`;
     - outstanding + actual group `Item_Attack` → `WOULD_REPAIR`;
   - physical repair remains disabled.
6. Preserve current source-side computation and `StillEquipped` / `CurrentSideMask` semantics.
7. Preserve removal/retirement of the C1 record after finalization.
8. Do not introduce timers, polling, delayed lifetime checks, ownership tables, reference-count changes, exception swallowing, SEH, pointer probing, or weapon/action-family special cases.

## Protected behavior — DO NOT CHANGE

- `Hook_SetCollisionGroup` remains explicit-this recursion-safe `.ThisCall()` exactly as currently implemented.
- `Hook_AISetState` remains its passed explicit-this `.ThisCall()` transport.
- `Hook_AIFullStop` remains its passed explicit-this `.ThisCall()` transport.
- `RunScriptFunction` remains recursion-safe pure pass-through; direct C1-O2 dispatch capture stays **suspended**.
- C1 physical repair stays **disabled**; all repair behavior remains log-only `WOULD_REPAIR`.
- Do not change marker ownership, marker names, marker activation/retirement semantics, or collision source selection.
- Do not change held-Use2/2500-ms behavior or treat it as production classification authority.
- Do not mechanically convert `StartEffect`, `PlayMotion`, or `StopMotion`.
- Do not change native cleanup behavior or call additional `SetCollisionGroup` operations.
- Do not build or run Gothic 3 in Work.

## Source/API audit required before editing

Inspect only the material necessary to verify this exact bounded correction:

- current `FinalizeAfterAISetState()` implementation in `CollisionLifecycleGuard.cpp`;
- definitions of `EquippedCollisionSources` / `GetEquippedCollisionSources()` only as needed to verify that current-side determination is pointer comparison against current equipped instances;
- existing finalization log field conventions only as needed to preserve machine-readable diagnostics.

Do **not** redo the completed SetCollisionGroup ABI/`.ThisCall()` investigation unless implementation exposes a new concrete contradiction.

## Required source audit after editing

Prove from the final source/diff that:

1. no remembered source is dereferenced before current equipped identity/liveness is established;
2. the not-currently-equipped branch performs no entity method/helper dereference through the remembered pointer;
3. `UNRESOLVED_NOT_EQUIPPED` remains the outstanding/not-currently-equipped outcome;
4. `NO_OP_NO_OUTSTANDING` remains the non-outstanding outcome;
5. live/equipped sources preserve existing physical-group reconciliation and `WOULD_REPAIR` classification;
6. `PhysicalCollisionChanged` remains `0` and no physical repair path was introduced;
7. record retirement/removal still occurs;
8. no hook transport or unrelated behavior changed;
9. edit surface contains only the permitted source file plus required bounded handoff documentation;
10. `git diff --check` passes.

## Work publication requirement

Follow `docs/WORK_IMPLEMENTATION_PROTOCOL.md` exactly:

```text
read assigned files
→ inspect only necessary source/API
→ edit bounded source
→ source audit
→ commit/publish to docs/collision-source-evidence
→ verify published tree/SHA
→ concise Work handoff
→ STOP
```

If the bounded source/API audit exposes a concrete contradiction that requires architecture beyond this responsibility, **STOP and report it**. Do not improvise a broader solution.

## After Work — Normal Chat gate

Normal Chat will independently source-review the published commit before the User builds anything.

If source review passes, the next runtime gate will re-run the extended SetCollisionGroup/C1 gameplay stability coverage using the corrected C1 finalizer. That later run must answer two separate questions:

1. does the source-liveness correction prevent the identified post-AISetState finalization crash path?
2. does SetCollisionGroup explicit-this transport complete extended gameplay and normal unload when that independent defect is removed?

No runtime test is part of this Work task.
