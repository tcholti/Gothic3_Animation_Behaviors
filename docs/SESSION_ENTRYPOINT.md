# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-30

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient Chat ↔ Work handoff when relevant: `docs/BETWEEN_CHATS.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring Git/build/deploy/test/log procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` when continuing the current/recent responsibility.
3. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
4. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
5. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
6. Before changing gate/test IDs, evidence/procedure IDs, artifact naming, prototype/build labels, branch meanings, or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
7. Do not scan the whole repository or reconstruct the project from old chat history.
8. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

### If the previous Chat ended unexpectedly

```text
Open `tcholti/Gothic3_Animation_Behaviors` on branch `docs/collision-source-evidence`.

Read `docs/SESSION_ENTRYPOINT.md` and follow its Fresh Normal Chat Bootstrap before claiming readiness.

Use repository documentation as authority. Do not reconstruct the project from old chat history and do not scan the whole repository. Retrieve only the exact deeper authority/evidence required by the current responsibility.

When bootstrap is complete, tell me briefly what the current technical gate is and what responsibility comes next. Do not begin a new implementation step until then.
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-execution safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

Production physical repair is still **disabled**.

---

## Active Problem — Native Stale Melee Collision

Use `EVIDENCE_INDEX.md` Active-Problem Reconstruction when the causal model is not fresh. Compact model:

- normal attack ScriptFunctions suspend around CombatMove and later resume into native cleanup;
- legitimate reactions can terminate CombatMove and still receive separate cleanup ownership;
- the known held-Use2 destructive path can terminate CombatMove and discard the suspended attack continuation before cleanup, leaving offensive collision stale;
- stale collision can persist through later idle/movement and can be inherited by a later legitimate execution as `7 -> 7`;
- C1 tracks successful offensive requests as exact per-source obligations, observes native cleanup, and classifies outstanding obligations at destructive AISetState finalization;
- GetUpAttack can request offense before CombatMove, so CombatMove alone is too late as a universal acquisition boundary;
- C1-O1 proved the live outer ScriptFunction frame can correlate pre-CombatMove offense → CombatMove → cleanup, while raw frame/argument addresses are lifetime-bound correlators only and may be reused after retirement;
- C1's own monotonic generation remains the durable plugin execution identity.

Evidence route: EV-151–EV-203.

---

## Agreed Strategic Direction — Universal Guard First

```text
preserve proven marker behavior
→ finish stable shadow execution/source ownership
→ prove controlled native-equivalent physical repair
→ preserve the known destructive abandonment as a stress case
→ preserve ordinary / legitimate reaction / pre-activation / inherited-state controls
→ broad marked/unmarked/player/NPC/negative regression
→ stable production integration
→ only later consider marker-bookkeeping simplification
```

The held-Use2 / 2500-ms path is a **test case**, not production classification authority.

The universal guard owns collision safety only. It should not rewrite unrelated external/native movement, state, balance or interruption behavior when collision integrity can be guaranteed independently.

---

## C1 Shadow Guard — Current Stable State

C1 remains event-driven and shadow-only. It tracks real offensive requests, including inherited `7 -> 7`, observes native cleanup, and reports `WOULD_REPAIR` without physically changing collision.

Core model and acquisition evidence:

- EV-192–EV-193 — shadow execution/source obligation model;
- EV-194 — GetUp pre-CombatMove acquisition gap;
- EV-195–EV-196 — outer ScriptFunction lifetime and C1-O1 correlation/pointer-reuse qualification.

### Directly relevant hook/finalizer substrate

Current tested state:

```text
RunScriptFunction
= recursion-safe explicit-this pure pass-through
= direct C1-O2 dispatch capture still suspended

AISetState
= explicit-this recursion-safe .ThisCall()
= PASS for tested extended stability

AIFullStop
= explicit-this recursion-safe .ThisCall()
= PASS for tested extended stability

SetCollisionGroup
= explicit-this recursion-safe .ThisCall()
= PASS for tested extended stability

FinalizeAfterAISetState
= remembered-source liveness gated by current equipped identity before source observation
= PASS for tested isolated + extended stability
```

Canonical continuation evidence: `docs/EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-203.

The 2026-08-30 corrected extended run covered about 852.7 seconds with 992 SetCollisionGroup events, 333 C1 finalizations, 235 AIFullStop calls, 147 CombatMove FullStops and 195 native cleanup call sites without reproducing the prior finalizer crash. All nine C1 invariant warnings inspected were the already-known `UNOWNED_PLAYER_OFFENSE_REQUEST` acquisition-gap family.

Important qualification: the corrected run did **not** positively exercise an outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` finalization branch. Do not claim runtime proof of that exact branch.

---

## C1-O2 — Current Status

C1-O2 remains the higher-level architectural destination:

> **Can C1 bind its monotonic generation to the live outer ScriptFunction frame, acquire legitimate offense before CombatMove, reuse the same generation when later CombatMove belongs to that still-live frame, and retire the native binding before pointer reuse without changing the already-passed cleanup/finalization model?**

The original direct `RunScriptFunction` dispatch-capture attempt and its first recursion-safe correction crashed in equivalent registered-ScriptFunction paths around the tested `Game +0x1605EB` return point. That crash remains **unresolved**.

Later AISetState/AIFullStop/SetCollisionGroup/finalizer stability work does **not** prove that the old direct capture can simply be restored.

`RunScriptFunction` remains generic infrastructure and must not become unconditional combat ownership or cleanup authority.

---

## Current Immediate Responsibility — C1-O2 Reassessment From Stabilized Substrate

**No Work task is currently frozen.**

Next session begins in Normal Chat with reasoning/source review, not implementation.

Answer in order:

1. Reconstruct only the unresolved C1-O2 failure boundary from EV-199 plus the already-proven outer lifetime EV-195–EV-196.
2. Compare that failure with the now-stable surrounding substrate in EV-200–EV-203.
3. Determine whether a source-supported minimal nesting-safe dispatch context can be reintroduced without repeating the failed implementation.
4. If direct capture remains unsafe/unsupported, identify the narrowest alternative that can correlate synchronous pre-CombatMove offense with the proven live outer ScriptFunction lifetime without making generic `RunScriptFunction` combat authority.
5. Freeze only the smallest falsifiable source/diagnostic gate. Do not enable physical repair as part of this reassessment.

### Protected state

Do **not**:

- restore the old C1-O2 dispatch-capture implementation by assumption;
- enable physical repair;
- roll back SetCollisionGroup explicit-this transport;
- change AISetState/AIFullStop transport;
- alter marker names, marker ownership, marker retirement or source selection;
- classify production ownership by held Use2, 2500 ms, Whirl, Quick, GetUp or patch callsite;
- mechanically convert StartEffect, PlayMotion or StopMotion;
- treat the unobserved liveness-negative branch as runtime-proven.

The known destructive abandonment remains the strongest positive stress case. Clean completion, legitimate reaction cleanup, pre-activation interruption, inherited-state attribution, exact source-side behavior and no-repair outcomes remain protected controls.

---

## Qualified Runtime Observations To Preserve

These are useful future test hypotheses, not established causal mechanisms:

- a reaction/knockdown sequence appeared to restore a stale source to the equipped collision state before a later GetUpAttack reactivated it; the exact cleanup owner was not isolated;
- holster/draw appeared to restore stale collision; do not attribute this specifically to bone detachment or equip mechanics without a targeted sequence.

Route to EV-203 before using either observation architecturally.

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
Engine +0x225660 = tested SetCollisionGroup hook target
```

GetUp boundary evidence:

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
| current exact continuation | `BETWEEN_CHATS.md` |
| active stale-collision causal reconstruction | `EVIDENCE_INDEX.md` Active-Problem Reconstruction |
| C1-O2 / hook/finalizer continuation evidence | `EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-203 |
| outer lifetime / cleanup architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| current staged validation | `COLLISION_TEST_PLAN.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| SPU / ScriptFunction / CombatMove / hook lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/static reference as needed |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` relevant section only |
| recurring Git/build/deploy/test/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| marker execution lifetime / future simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` |
| animation semantics/assets | `ANIMATION_INDEX.md` |
| overall Raise/speed/collision architecture | `DESIGN.md` |
| older chronology | `RESEARCH_MAP.md` / archive only when specifically needed |

Do not load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay systems such as jumping, wading and climbing.
