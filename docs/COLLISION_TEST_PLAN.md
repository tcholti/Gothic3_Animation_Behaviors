# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-29

## Purpose

Validate one general execution-level collision-cleanup model with the smallest tests that can falsify it. Historical gate detail is preserved through `EVIDENCE_INDEX.md`, the canonical evidence ledgers and raw/archive artifacts; this file owns the **current and forward validation sequence**.

Current state and exact next responsibility: `SESSION_ENTRYPOINT.md`.  
Current lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.

---

## 1. Rules for the Current Test Phase

- C1 remains **shadow-only**; production physical repair is disabled.
- Compare one conceptual variable at a time where practical.
- Do not add Staff/Quick/Whirl/GetUp/input/state-name-specific ownership or repair branches.
- Do not treat `RunScriptFunction`, FullStop or AISetState as unconditional cleanup authority.
- Preserve native behavior for unmarked controls and preserve all proven marker bookkeeping.
- Visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence.
- Reuse the current diagnostic/hook owner when it already exposes the needed fact; add another hook only for a specific unresolved question.
- Preserve raw runtime logs exactly as produced.
- Follow `PROJECT_PIPELINE.md` for gate identity, build identity and raw/derived artifact naming, and `PROJECT_OPERATING_PROCEDURES.md` for local build/deploy/test/log operations.
- Preserve external/native combat-rule choices. The collision project must remain compatible with New Balance and other compatible setups without recreating or removing their blocking/balance behavior unless collision safety proves that intervention is necessary.

Authoritative research DLL remains:

```text
Script_FrameCollisionTest
```

Before any controlled runtime result becomes evidence, verify the exact intended build/deployment identity and startup banner using the project procedures.

---

## 2. Closed Lifecycle Gates — Retrieve, Do Not Rerun by Default

### B6 — replacement-triggered deferred `ProcessScript()` candidate rejected

Clean completion exposed useful `sAICombatMoveInstr -> ProcessScript()` context, but bad armed replacement did not expose a comparable universal replacement-time ScriptAdmin/SPU context.

Evidence: EV-174–EV-181.

### B7 / B7b — CombatMove termination and Whirl continuation loss resolved

Bad full Whirl and legitimate reaction can both FullStop CombatMove, but only the legitimate reaction receives separate cleanup ownership. The tested bad held-Use2 Whirl path proceeds through `FullStop -> SetState`, discarding the suspended attack ScriptFunction continuation that would otherwise reach native cleanup.

Evidence: EV-182–EV-189.

### B8 — cross-family abandonment generality resolved

The same tested held-Use2 stale class appears in player Quick configurations beyond full Whirl.

Evidence: EV-190.

### B9 — cleanup/finalization ordering resolved

Tested bad armed abandonment reaches AISetState before cleanup; tested clean ordinary and legitimate reaction paths fulfill cleanup before the relevant destructive replacement. AISetState is therefore useful only when gated by exact owned execution/source obligation state.

Evidence: EV-191.

### C1 — shadow execution/source obligation model core passed

The tested C1 matrix preserved clean/reaction/pre-activation no-op behavior, classified known armed bad abandonments as `WOULD_REPAIR`, and correctly attributed an inherited-stale `7 -> 7` request to the new generation.

Evidence: EV-192–EV-193.

### C1 acquisition boundary gap

GetUpAttack can legitimately request `Item_Attack(7)` before CombatMove starts, so CombatMove is not a universal outer execution-acquisition boundary.

Evidence: EV-194.

### C1-O1 — outer ScriptFunction lifetime/identity probe resolved

The same live GetUp ScriptFunction frame spans pre-CombatMove offense → later CombatMove → cleanup. Raw frame/arguments addresses can be reused after retirement, so they are lifetime-bound correlators only; C1's monotonic generation remains durable identity.

Evidence: EV-195–EV-196.

---

## 3. Higher-Level Gate — C1-O2 Shadow Outer ScriptFunction Binding Integration

C1-O2 remains the higher-level outer-binding target, but direct `RunScriptFunction` dispatch-capture integration is currently **suspended** while the required hook transport is hardened and stabilized. `SESSION_ENTRYPOINT.md` owns the exact immediate hardening responsibility.

The C1-O2 question remains:

> **Can C1 bind its existing monotonic generation to the live outer ScriptFunction frame, acquire legitimate equipped-weapon offense before CombatMove, reuse that same generation when the later CombatMove belongs to the same still-live frame, and retire the native binding before address reuse without changing the already-passed cleanup/finalization classification?**

No C1-O2 implementation task is currently frozen. Resume direct dispatch capture only after the prerequisite hook-transport work passes its own isolated source/build/runtime checks.

### C1-O2 implementation/source-review acceptance

When C1-O2 resumes, it must preserve:

1. one minimal nesting-safe `RunScriptFunction` dispatch context;
2. original `RunScriptFunction` call exactly once with unchanged real arguments;
3. live-frame correlation only by the frozen rule:
   - exact SPU;
   - top frame is ScriptFunction;
   - non-null bound `m_pArguments`;
   - same ScriptFunction name;
4. pre-CombatMove acquisition only for a successful `Item_Attack` request on the supplied SPU actor's exact equipped RIGHT/LEFT weapon entity;
5. later matching CombatMove reuses, rather than replaces, the pre-acquired generation;
6. ordinary CombatMove-created generation behavior remains available when no matching pre-acquired binding exists;
7. successful cleanup remains source/consequence based and does not require the old frame to remain current;
8. true `RunScriptFunction` return retires the native binding before pointer reuse;
9. outstanding obligation at true return is diagnostic-only (`OUTER_RETURN_OUTSTANDING`-style failure signal), not physical repair or a newly invented finalization rule;
10. existing AISetState shadow finalization and `WOULD_REPAIR` classification remain unchanged;
11. no null-arguments fallback, family/action/input classifier, arbitrary group-7 adoption, polling/timer/world scan or marker-core refactor.

No runtime acceptance can compensate for a source-level violation of these rules.

---

## 4. C1-O2 Runtime Validation — After Hook Hardening + Independent Source Review + Build/Load Verification

Normal Chat will freeze the exact controlled fixture and raw filename only after the prerequisite hook transport is stable, the C1-O2 implementation passes independent diff review, and the exact built/live DLL identity is verified.

The first runtime matrix should answer these factual questions with the smallest sufficient set of controls:

### A. Pre-CombatMove GetUp acquisition

Expected:

```text
legitimate equipped-weapon Item_Attack before CombatMove
→ C1-O2 acquires one generation from the live outer ScriptFunction context
→ later CombatMove for the same live frame reuses that same generation
→ ordinary native cleanup fulfills the exact source obligation
→ no repair candidate / no binding invariant
```

This is the primary positive test for the new route.

### B. Ordinary CombatMove-created control

Representative clean Normal/full-Whirl executions that do not need pre-CombatMove acquisition should still use the existing CombatMove-start path and bind/reuse the live outer frame without changing cleanup classification.

Expected: native cleanup observed; finalization no-op.

### C. Known armed bad abandonment — retained destructive stress case

Representative held-Use2 stale Whirl/Quick cases should still produce the same C1 shadow consequence classification as before.

Expected: outstanding exact source at destructive AISetState → `WOULD_REPAIR` shadow outcome only; no physical repair during C1-O2.

Keep this known bad path intact through universal-guard validation. It is the strongest currently reproducible destructive positive case and must not become a production classifier by Use2, 2500 ms, family or Community Patch caller.

### D. Pre-activation bad abandonment

Expected: no offensive request → no cleanup obligation → no repair candidate.

### E. Legitimate reaction interruption — critical negative control

Expected: reaction-side native cleanup fulfills the exact source obligation even though cleanup can execute outside the old attack ScriptFunction context; no repair candidate.

This remains a critical negative/no-repair control because legitimate reactions can also FullStop CombatMove.

### F. Inherited-stale `7 -> 7` control

Expected: a later legitimate request while the source is already group 7 is attributed to the later execution's generation when that execution owns the request; later native cleanup fulfills that generation.

### G. Frame-lifetime failure signals

The controlled run must specifically check for:

- frame mismatch / overlap invariants;
- null-arguments failure;
- `OUTER_RETURN_OUTSTANDING`;
- generation replacement where reuse was expected;
- a retired binding matching a later reused raw address.

Any such occurrence is a design/test-gate result to interpret in Normal Chat, not something to hide with fallback behavior.

---

## 5. C1-O2 Runtime Acceptance

C1-O2 passes its shadow binding gate only if all tested controls support the same model:

```text
outer live ScriptFunction frame
= temporary native lifetime correlator

C1 monotonic generation
= durable plugin execution identity

actual successful Item_Attack request
= exact source obligation

native transition away from Item_Attack
= obligation fulfilled

destructive AISetState with obligation still outstanding
= existing shadow WOULD_REPAIR classification
```

And specifically:

- GetUp pre-CombatMove offense is no longer unowned;
- its later CombatMove reuses the same generation;
- clean ordinary paths remain clean/no-op;
- legitimate reactions remain native-clean/no-op;
- pre-activation failures remain no-op;
- known armed stale paths retain the existing `WOULD_REPAIR` shadow classification;
- inherited `7 -> 7` attribution remains correct;
- no lifetime-correlator reuse/leak invariant occurs;
- physical collision behavior remains unchanged by C1-O2.

If the new route requires family/action/input classification or a guessed null-arguments fallback to pass, C1-O2 fails.

---

## 6. After C1-O2 — Universal Guard First

Only after the outer binding model passes should Normal Chat freeze the exact physical-repair gate.

The agreed development order is:

```text
stable shadow execution/source ownership
→ controlled native-equivalent physical repair
→ retain the known bad held-Use2 abandonment as the strongest destructive positive stress case
→ preserve ordinary completion / legitimate reaction / pre-activation no-op controls
→ preserve inherited 7 -> 7 attribution
→ broad marked/unmarked/player/NPC/negative regression
→ only then consider stable production integration
```

Root-cause repair of the held-Use2 / Alternative-AI bad skip is **not** a planned prerequisite. If the universal guard safely prevents stale offensive collision, leave the remaining external gameplay/state behavior alone.

Reopen root-cause bad-skip repair only if evidence shows that general collision integrity cannot be guaranteed without changing that destructive lifecycle path—for example because exact execution/source identity is lost too early, post-abandonment native-equivalent cleanup is unsafe, inherited ownership cannot be distinguished reliably, or the supposed universal guard starts requiring cause-specific Use2/2500-ms/family/patch-callsite rules.

The guard owns collision safety only; it is not responsible for repairing every movement/state/gameplay consequence of an external interruption.

Likely later responsibilities remain evidence-dependent and must not be pre-authorized here:

- decide the exact gate for promoting shadow `WOULD_REPAIR` to native-equivalent physical repair;
- test broad marked/unmarked/player/NPC regression for the one chosen lifecycle rule;
- challenge whether any legitimate independent Hit sequence intentionally carries offensive collision across executions;
- verify negative/no-op behavior for Fist, bow, crossbow and magic;
- verify defensive block/parade semantics if the eventual physical repair operation could disturb them;
- reconsider marker-core simplification only after the stronger native lifetime and physical guard are proven to preserve the historical marker guarantees.

No root-cause bad-skip rewrite or marker refactor is authorized merely because C1-O2 is implemented.

---

## 7. Marker-Core Regression — Reuse Existing Fixtures When Relevant

If a lifecycle change can plausibly affect marker behavior, reuse compact proven fixtures such as:

```text
RIGHT -> LEFT
BOTH -> RIGHT
RIGHT -> OFF -> RIGHT
BOTH -> LEFT -> OFF -> BOTH
```

Verify desired-set transition, source rearm, occurrence/replay guards, execution retirement and absence of unexpected native timer activation.

Do not rebuild the full historical v0.10–v0.18 matrix unless a regression demands it.

Marker simplification is a later optimization question, not a prerequisite for the universal guard. Preserve duplicate/replay handling, occurrence protection, exact source-set semantics, repeated-contact rearm, Quick bookkeeping and any other mechanism whose original regression still requires it.

---

## 8. Success Criteria for Stable Collision Integration

Before stable lifecycle behavior can move into `Script_G3AnimationBehaviors`, evidence must support:

1. exact ownership of a real attack execution before and during CombatMove where needed;
2. exact creation of offensive source obligations, including `7 -> 7` requests;
3. reliable observation of native cleanup fulfillment;
4. safe lifetime retirement without raw-pointer reuse confusion;
5. a terminal/finalization rule that preserves Gothic's legitimate cleanup opportunity;
6. correct handling of clean, reaction, pre-activation, bad-abandonment and inherited-stale cases;
7. safe native-equivalent physical repair only for exact abandoned outstanding sources;
8. no-op behavior for unrelated mechanics/source models and compatible external combat-rule choices;
9. preservation of marked and native collision semantics behind one end-of-execution safety invariant.

Only after those conditions pass should stable production integration be considered. Root-cause repair of an external bad interruption remains conditional rather than part of the universal guard's definition.