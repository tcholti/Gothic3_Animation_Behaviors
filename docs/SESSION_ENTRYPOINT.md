# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-29

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient Chat ↔ Work handoff when relevant: `docs/BETWEEN_CHATS.md`  
Stable naming/numbering/version/test/artifact conventions: `docs/PROJECT_PIPELINE.md`  
Recurring Git/build/deploy/test/log procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent transient handoff.
3. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
4. When substantial work on the active problem will interpret evidence or propose a new fix/architecture and the current Chat does not retain a fresh causal model, perform the targeted Active-Problem Reconstruction Pass routed below and in `docs/EVIDENCE_INDEX.md`.
5. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering an active local Git/build/deploy/runtime-artifact sequence; do not reread it after every prompt.
6. Before assigning or changing a gate/test ID, evidence/procedure ID, raw/derived filename, prototype/build/version label, branch/state meaning, or validation/artifact-flow convention, retrieve the relevant section of `docs/PROJECT_PIPELINE.md`. Preserve the established convention unless there is a deliberate reason to change it.
7. Do not scan the whole repository or reconstruct the project from old chat history.
8. Retrieve only the deeper authority listed under **Retrieval — Only What the Question Needs**.

Within one continuing subsystem context, do not repeatedly reread unchanged authorities, procedures, or pipeline conventions.

A Chat migration is not a reason to rename, renumber, restart, or reinterpret project conventions.

### If the previous Chat ended unexpectedly — copy/paste this into the new Chat

```text
Open `tcholti/Gothic3_Animation_Behaviors` on branch `docs/collision-source-evidence`.

Read `docs/SESSION_ENTRYPOINT.md` and follow its complete Fresh Normal Chat Bootstrap before claiming readiness.

Use the repository documentation as authority. Do not reconstruct the project from old Chat history and do not scan the whole repository. Follow the entry point's routes for any relevant transient handoff, subsystem orientation, operating procedure, pipeline convention, and exact current technical authority needed for the current responsibility.

When bootstrap is complete, tell me briefly what the current technical gate is and what responsibility comes next. Do not begin a new implementation step until then.
```

This fallback is intentionally generic. The durable current gate, handoff, procedures, pipeline conventions, and technical state remain in the repository and should evolve there rather than requiring the User to maintain a new restart prompt manually.

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-execution safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

Production repair is still **disabled**.

---

## Active Problem — Native Stale Melee Collision / Held-Use2 State-Stack Abandonment

Use the ordered route in `EVIDENCE_INDEX.md` once when this causal model is not fresh. The compact model is:

- **Historical trigger and reproduction:** Community Patch / Alternative AI documents a 2.5-second maximum continuous Hero parade; the tested binary independently compares held Use2 against 2500 ms before the bad FullStop path. Manual reproduction is timing-sensitive: hold RMB near the timeout, keep it held, begin an attack and let the timeout occur during a vulnerable Hit. Visual behavior helps reproduce; logs/evidence decide the result. See EV-187, EV-197–EV-198.
- **Normal full-Whirl mechanism:** the attack ScriptFunction starts CombatMove, returns false/suspends while the instruction remains active, resumes after completion and reaches its later native collision-cleanup continuation. See EV-182–EV-183.
- **Established bad path:** the timeout reaches AIFullStop / persisted CombatMove `fullStop`, immediately reaches SetState, discards the suspended state-stack continuation and leaves no ordinary cleanup or replacement reaction owner; an armed source can remain group 7. See EV-185, EV-187, EV-189–EV-191.
- **Legitimate reaction contrast:** reactions may also FullStop CombatMove, then use a separate reaction cleanup path including `7 -> 5`. FullStop means instruction termination, not collision cleanup. See EV-165, EV-184, EV-186, EV-188, EV-191.
- **Physical consequence and scope:** stale collision can persist through idle/movement, damage an NPC while the player runs, and be inherited by later attacks as legitimate `7 -> 7`; a later valid execution may clean it, but not every later action is proven to do so. The class is reproduced beyond full Whirl in tested Dual, plain 1H and Shield+1H Quick configurations. See EV-156, EV-162, EV-181, EV-190, EV-193.
- **Raise boundary:** the User has repeatedly reproduced this timeout failure on the vulnerable set lacking a working Raise and has not successfully reproduced it on attacks with a working Raise. The protective mechanism is unproven; Raise can still be interrupted by terrain, damage and other legitimate mechanisms. Adding Raise is not a collision-cleanup fix. See EV-153, EV-191, EV-198.
- **Rejected simplifications:** missing Recover, Recover as universal authority, StartRecover as universal boundary, PlayMotion replacement fallback, callback return, unconditional AIFullStop cleanup, Whirl-only repair, a held-Use2/2500-ms/patch-callsite production classifier and “add Raise.” See EV-154, EV-159–EV-162, EV-168–EV-191.
- **Governing invariant:** every real attack-Hit offensive request must receive Gothic's legitimate native cleanup opportunity; if that exact execution is destructively abandoned with an exact source obligation outstanding, repair only the remaining source using native cleanup semantics. See `COLLISION_LIFECYCLE_PLAN.md` and EV-192–EV-196.

This is a routing reconstruction, not a duplicate ledger. Retrieve raw/source proof only for a fact being verified or reinterpreted.

---

## C1 Shadow Guard — Implemented and Core Runtime-Tested

C1 is an event-driven **shadow-only** execution/source obligation model. It tracks real offensive `Item_Attack` requests, including inherited `7 -> 7`, observes native cleanup, and reports `WOULD_REPAIR` at destructive AISetState finalization without physically changing collision.

Key implementation/review commits:

```text
3778517f421d07e940c620745bc7ccdf0da54313  C1 implementation
f04c3e18f4129e0ee7727a3f266d6fc55fb13a8c  independent source review PASS
```

Core runtime evidence:

```text
research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log
raw commit: a3c41c829a0e7d083ccfc657eafc285f68b60d4b
research/archive/2026-08-28_c1_shadow_core_lifecycle_matrix_connector_extract.txt
extract commit: e5d8da1323b3c43c52ce0f58ea010081e00a364f
```

### Core result

- **8 actual `WOULD_REPAIR` outcomes** were accounted for by known armed bad held-Use2 abandonments: 1 full Whirl and 7 Dual Quick;
- clean ordinary completions did not become repair candidates;
- tested pre-activation bad skips did not become repair candidates;
- tested legitimate reaction interruptions cleaned natively and did not become repair candidates;
- inherited-stale control passed: bad Whirl left group 7, the next Normal execution legitimately requested `7 -> 7`, C1 attributed that request to the **new** generation, and later native `7 -> 5` cleanup fulfilled the new generation.

The remaining defect exposed by this matrix was acquisition: GetUpAttack can legitimately request `Item_Attack(7)` before CombatMove begins, so CombatMove cannot be the universal outer execution start.

---

## C1-O1 — Outer ScriptFunction Lifetime Probe Resolved the Identity Gate

Implementation and evidence:

```text
54a64552514f4d6795b4a51cbad7848b5df3795b  C1-O1 diagnostic implementation
research/raw/2026-08-29_c1o1_outer_scriptfunction_identity_probe.log
raw commit: adf6a6102007c56f7502b01072acbe00bcbc35a4
research/archive/2026-08-29_c1o1_outer_scriptfunction_identity_probe_connector_extract.txt
extract commit: 5da094a0c2d6fc58fe260933799a76e43ef7d1d3
```

### Runtime result

C1-O1 positively identified a usable native outer **lifetime**, with an important qualification about identity tokens.

Representative GetUpAttack:

```text
pre-CombatMove Item_Attack request
→ top frame = _AI_GetUpAttack
→ later CombatMove initial invocation
→ same SPU / same live ScriptFunction / same non-null m_pArguments
→ later cleanup
→ same live _AI_GetUpAttack frame; break block advanced
```

Repeated GetUp executions used different argument pointers, confirming distinct live executions.

Clean Normal/Whirl likewise retained the same attack ScriptFunction frame through CombatMove/offense/cleanup and removed it before the later enclosing state transition.

Bad full Whirl retained `_AI_WhirlAttack` at `AI_SET_STATE_BEFORE`; `AI_SET_STATE_AFTER` no longer contained that frame, and no cleanup occurred between those observations.

### Critical qualification — pointer reuse

`m_pArguments` and the stack-entry address are **not globally unique execution IDs**. C1-O1 observed an address reused by a later different ScriptFunction shortly after the previous frame was retired.

Therefore:

```text
raw frame/arguments address
= lifetime-bound correlator only
≠ permanent execution identity
```

C1's own monotonic generation remains the durable plugin-side execution identity. Any native frame correlator must be explicitly retired before address reuse.

The tested attack ScriptFunction snapshots used non-null argument pointers. Null argument records were observed for ScriptStates; future relevant null-argument ScriptFunctions must fail diagnostically rather than be guessed into ownership.

---

## Static Follow-Up — General Pre-CombatMove Actor/SPU Context

Pinned SDK and tested Game.dll establish:

```text
gCScriptAdmin::RunScriptFunction(..., stateStack, spu)
    receives the exact SPU
    → spu->GetSelfEntity() exposes the actor
    → calls the registered ScriptFunction at Game +0x1605E9
    → Game +0x1605EB is the first instruction after that ScriptFunction call
```

When the ScriptFunction returns false because asynchronous work remains active, the state-stack frame is retained. When it returns true, the tested runner removes the completed top frame before returning.

`gCScriptAdmin` does not expose a documented public accessor that can safely be treated as “the currently executing NPC SPU”; its protected admin `m_SPU` must not be substituted for the explicit per-dispatch SPU without evidence.

`RunScriptFunction` is **generic infrastructure**. It must not become combat ownership or unconditional cleanup authority. Its only proposed C1-O2 role is a narrow transient execution context so a synchronous pre-CombatMove `Item_Attack` request can be tied to the exact actor/SPU that is executing it.

---

## Current Immediate Responsibility — Hook-Hardening Before C1-O2 Can Resume

The higher-level C1-O2 outer-frame binding gate remains conceptually relevant, but direct `RunScriptFunction` dispatch capture is **suspended**. It is not the next ready implementation/runtime gate.

Current durable sequence:

1. The original C1-O2 capture and its recursion-safe `.ThisCall()` correction crashed in equivalent registered-ScriptFunction paths (`Script.dll +0x1494C`, `Script_Game.dll +0x3776D`, return at `Game +0x1605EB`, observed `ECX=0`).
2. `RunScriptFunction` was reduced to recursion-safe pure pass-through: explicit real `this`, unchanged arguments, exactly one original call, no dispatch capture or C1-O2 lifecycle work.
3. That pure pass-through baseline passed the bounded load/idle isolation.
4. Extended gameplay then produced a **different** crash through the existing AISetState path (`Script.dll +0x12F61`, `Game +0x1604D3`), not the earlier `RunScriptFunction +0x1605EB` path.
5. Source analysis found AISetState still used the SDK's legacy shared `GetSelf` ThisCall transport, which is not recursion/thread safe.
6. AISetState alone was converted to explicit per-invocation `gCScriptRoutine_PS *this` with the recursion-safe `.ThisCall()` builder; its original ordering and C1 semantics were preserved.
7. Independent source review passed.
8. The extended stability run passed for about **329.9 seconds** and unloaded normally: 172 AISetState records, 43 AIFullStop records and 62 C1 finalizations; zero `OUTER_RETURN_OUTSTANDING`, `LIVE_FRAME_MISMATCH`, `PRECOMBAT_GENERATION_FRAME_OVERLAP`, `OVERLAP_OUTSTANDING`, `CANDIDATE_GENERATION_CHANGED`, `FINALIZATION_GENERATION_CHANGED` or `NULL_ARGUMENTS` records. One deliberately reproduced bad full Whirl produced the expected log-only `WOULD_REPAIR`; physical repair remained disabled.

Canonical stability artifacts:

```text
8024d846eed626725ca46fa744a79af44fcb2815  AISetState recursion-safe implementation
2c666c7bf2374c3875e2706c6ee54563f31c593f  Work handoff/result record
research/raw/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability.log
raw commit: 6b4cda21466ccca6c42a9c51b98fbbfe6da48ed3
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_extract.txt
extract/current head: 86308b1c91176501c294ee50af99ce9bb418900d
```

Only **one** bad full-Whirl reproduction was confirmed despite at least two attempts. Do not generalize the stability run as more than one confirmed bad case.

Legacy ThisCall transports still present at this point are AIFullStop, SetCollisionGroup, PlayMotion, StopMotion and StartEffect. AIFullStop is the leading next hardening candidate because it is on the proven destructive path, but **no coding task is frozen**.

### Next Normal Chat responsibility

1. review the current documentation/current-state model;
2. confirm the hook-hardening interpretation and constraints with the User;
3. explicitly expose and freeze the next bounded hook-hardening responsibility before implementation.

Do not restore C1-O2 dispatch capture. Do not begin or freeze AIFullStop implementation merely from this entry point.

---

## Relevant Tested Native Points

```text
Game +0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game +0x1605E9 = indirect registered ScriptFunction call
Game +0x1605EB = first instruction after that call
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

GetUpAttack boundary evidence:

```text
Script_Game +0x41CA6  pre-CombatMove Item_Attack request region
Script_Game +0x41D5A  later CombatMove call
Script_Game +0x41E10  ordinary cleanup
```

All addresses are tested-build-specific.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| active stale-collision causal reconstruction | `EVIDENCE_INDEX.md` Active-Problem Reconstruction → exact EV entries only as needed |
| current outer-lifetime / cleanup architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| transient current Work/Normal handoff | `BETWEEN_CHATS.md` when it contains a relevant active handoff |
| naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` relevant section only |
| recurring Git/build/deploy/test/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| exact evidence | `EVIDENCE_INDEX.md` → `EVIDENCE_LEDGER_STEP_B.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| SPU / ScriptFunction / CombatMove / hook lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/static reference as needed |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| staged validation | `COLLISION_TEST_PLAN.md` |
| marker execution lifetime / future simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` |
| animation semantics/assets | `ANIMATION_INDEX.md` |
| overall Raise/speed/collision architecture | `DESIGN.md` |
| older chronology | `RESEARCH_MAP.md` / archive only when specifically needed |

Do **not** load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay systems such as jumping, wading and climbing.
