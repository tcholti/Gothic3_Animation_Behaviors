# Collision Reference

**Status:** Current accepted collision working contract
**Updated:** 2026-10-08
**Purpose:** One maintained collision-specific owner for supported behavior, module boundaries, invariants, diagnosis and safe re-entry. Collision is CLOSED/PASS through EV-390; later integrated features do not reopen its causal research by themselves.

Start here plus targeted production source. Retrieve [animation rules](ANIMATION_RULES.md) for authoring, [hook guide](SOURCE_HOOK_GUIDE.md) for engine/RVA facts, and existing [development method](FEATURE_DEVELOPMENT_METHOD.md), [POPs](PROJECT_OPERATING_PROCEDURES.md) and [Work protocol](WORK_IMPLEMENTATION_PROTOCOL.md) for operations. [DESIGN](DESIGN.md) owns cross-feature integration; [release architecture](GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md) owns product separation. Proof-sensitive questions use [EVIDENCE_INDEX](EVIDENCE_INDEX.md) → exact EV → original evidence only when needed. Archives are recovery material, not prerequisite reading.

## 1. Accepted scope and exclusions

Factual action, phase, current motion and source UseType govern eligibility. Filename R/L does not select equipped sides; a serialized `Fist` token does not distinguish raw8 from raw55. Collision authors native contact opportunities; Gothic retains target selection, contact geometry, block/parry, immunity, reactions and HP damage.

| Mechanism | Supported contract | Boundaries / fallback |
|---|---|---|
| Equipped | `G3AB_COL_RIGHT`, `LEFT`, `BOTH`, `OFF`; Normal, Quick, Power, Pierce, SimpleWhirl, full Whirl, tested 2H/Staff Hack, equipped Sprint | Complete factual required sources; LEFT shield/raw9 physical activation does not prove shield-bash damage (EV-308). Missing sources fail closed, never partial BOTH. |
| raw8 `gEUseType_Fist` | `G3AB_COL_FIST`; Normal, Quick, true Power, Sprint; one pending target-directed opportunity | Exact actor/C1/source/SPU; no equipped window, triggered-list rearm, custom damage or FIST_OFF. No species gate. |
| raw55 `gEUseType_PhysicalFist` | FIST only, one or two markers; Normal, Quick, true Power, Sprint origin | Exact current RIGHT source; no concurrent resolved raw8 source, LEFT generalization, mixed equipped/FIST markers, more than two FISTs or FIST_OFF. Tested Troll/BlackTroll domain; no species gate. |

Generic marker family recognition requires Hit: Normal Action1 additionally requires current `_Attack_Hit_`; Quick recognizes Actions3/4/5; Power2, Sprint9, SimpleWhirl6, Whirl10, Pierce11 and Hack14 have distinct factual identities. This does not widen each mechanism's own preflight. Finishing15, unsupported ranged/magic families and unproven source/native arms remain outside the accepted marker contract. Normal/Quick/full-Whirl AddRaise is a separate feature; collision recognition of Quick3 does not authorize selector-level Raise or Speed policy.

Unmarked and unsupported ownership paths preserve native behavior. Reserved marker effects are consumed as commands even when rejected/malformed; they are not effect-resource names. Separation/renaming mods can use markers on valid resolved assets, but unmarked replacements inherit no ownership from old assets (EV-369–375).

Validation is representative, not universal engine/actor coverage: equipped/body regression EV-299–374, intended New Balance stack EV-376–384/388, behavior-only controls EV-389 and production integration EV-390. Unmarked raw55 four-family standalone fallback is proven EV-387; EV-388's unmarked New Balance artifact contains Power/Normal/Quick, not Sprint. Special raw8 `SPU+0x154 == 0x39` has a separate native arm outside the generic-human timing model.

## 2. Production owners and native-event order

All source links below are the current production modules under `src/Script_G3AnimationBehaviors/`; use headers for public transport structures and the named functions for local inspection.

| Owner | Relevant entry points / responsibility |
|---|---|
| [FrameCollisionMarkers](../src/Script_G3AnimationBehaviors/FrameCollisionMarkers.cpp) | `TryGetCurrentAttackHitFamily`, `GetCurrentMarkerDecision`, `EvaluateAttackCallbackOwnership`, `ProcessMarker`; current-motion scan, occurrence/dedupe/budgets, exact equipped sets; `RetireMarkerOwnedSource`, `RetireFinalizedGeneration` retire bookkeeping. |
| [CollisionSources](../src/Script_G3AnimationBehaviors/CollisionSources.cpp) / [CollisionSourceOperations](../src/Script_G3AnimationBehaviors/CollisionSourceOperations.cpp) | `GetEquippedCollisionSources`, `ResolveFistCollisionSource`, `GetCollisionSourceUseType`; factual identity. `ActivateAttackSource`, `RearmTriggeredContacts`, `DeactivateOwnedAttackSource`; physical mutation, not feature policy. |
| [EquippedSprintCollision](../src/Script_G3AnimationBehaviors/EquippedSprintCollision.cpp) | `ShouldSuppressNativeCallback`, `AuthorizeGenericEquippedMarker`, `RetireFinalizedGeneration`; immutable Sprint-origin authorization. |
| [Raw8FistCollision](../src/Script_G3AnimationBehaviors/Raw8FistCollision.cpp) | `UpdateMarkerOwnership`, `ApplyAcceptedMarkerLatch`, `UpdateTimingPermissionFromMarker`, `ApplyTimingPermission`; `Begin/CompleteCombatMoveInvocation`, `ObserveContactResolutionDispatch`, `CloseForFinalization`; §4.1 policy. |
| [PhysicalFistCollision](../src/Script_G3AnimationBehaviors/PhysicalFistCollision.cpp) | `TryResolveEligibility`, `ResolveExecution`, `IsFirstFistAllowed`, `IsSecondFistAllowed`, `TryProcessMarker`, `ShouldSuppressCollisionGroupRequest`, `ShouldSuppressNormalNativeTriggerClear`; §4.2 policy. |
| [CollisionLifecycleGuard](../src/Script_G3AnimationBehaviors/CollisionLifecycleGuard.cpp) | `BeginCombatMove`, `ObserveCollisionGroupResult`, `CompleteCombatMoveCandidate`, `RetirePreCombatBridgeAfterDispatch`, `CaptureFinalizationToken`, `FinalizeAfterAISetState`; C1 identity/obligations/backup. |
| [EngineBridge](../src/Script_G3AnimationBehaviors/EngineBridge.cpp) | Sole physical hook owner. Attack callbacks, `StartEffect_FrameCollisionTest`, `RunScriptFunction_FrameCollisionTest`, `InvokeCombatMove_FrameCollisionTest`, `AISetState_FrameCollisionTest`, setter/clear/timing/contact transports capture facts and delegate. Historic function suffixes do not imply diagnostic-only behavior. |
| [RuntimeClock](../src/Script_G3AnimationBehaviors/RuntimeClock.cpp) | Monotonic elapsed-time input for marker duplicate acceptance; behavior-required, never diagnostic-gated. |

Startup initializes RuntimeClock, loads profiles once, then installs Bridge hooks. At StartEffect, raw55 gets first refusal; otherwise Sprint authorization/generic marker processing runs, then accepted raw8 timing is updated. Each actual native CombatMove is surrounded by C1 begin/completion and raw8 invocation scope. Shared request order is Raise sequencing → stateless Hack Speed composition → collision invocation wrapper → native original once. AISetState cancels Raise, captures C1, calls native once, closes captured raw8/marker/Sprint/raw55 state, then finalizes C1. Exact-generation checks protect any replacement created reentrantly during native execution.

## 3. Equipped markers and Sprint

| Marker | Exact desired offensive set | Operation |
|---|---|---|
| RIGHT | `{RIGHT}` | Close omitted owned side; activate/rearm RIGHT. |
| LEFT | `{LEFT}` | Close omitted owned side; activate/rearm LEFT. |
| BOTH | `{RIGHT, LEFT}` | Require both factual sources; activate/rearm both. |
| OFF | `{}` | Close owned equipped windows inside Hit; no terminal finalization. |

Repeated source markers can author later contacts through `ClearTriggeredList()`. Eligibility requires the complete motion's required source set, valid matching current motion and C1, supported action/phase/source facts, authored per-opcode occurrence budgets and same-update duplicate/replay suppression. Cache only valid resolved motion scans. Reject late/dead/unsupported ownership; do not infer a new execution from filename, callback rollback, phase, action or state-time changes. Natural source retirement clears only its exact marker-owned bit/window; OFF/set switching does not erase the whole execution.

`EquippedSprintCollision` binds factual Action9 origin to exact C1, motion and required sources and excludes FIST mixtures. Only that bound execution may retain authorization through same-C1 Action9 → Action2/Power continuation. New ordinary Power cannot inherit it. Missing sources preserve native fallback. Generic equipped operations stay in FrameCollisionMarkers (ADR-0003; EV-320–329/377).

These windows do not normalize Gothic character-hit policy. SimpleWhirl remains target-centered at SP1 rather than a strict marker-only character-damage window; tested SP2 did not provide sufficient normalization. Power/Pierce retain native action-specific targeting/reactions. Hack14 optional `_FinishingAttack_` → `_HackAttack_` asset routing belongs to `AttackMotionRouting`, only when the candidate exists; Finishing15 remains native.

## 4. Two distinct FIST contracts

### 4.1 Raw8 — persistent opportunity, separate timing

Native generic-human raw8 time-gates an attempt and sets its attempt latch before the remaining contact checks finish, so a miss can still spend that native attempt. An accepted G3AB FIST instead creates or refreshes one logical pending opportunity: it rearms after native misses until an exact matching native contact-resolution dispatch consumes it, or execution end/replacement/invalid identity safely retires it. Timing permission is a separate helper; pending does not mean continuous checking or a permanent hitbox, and contact dispatch does not guarantee HP damage.

The execution record binds exact actor instance, monotonic C1, factual raw8 source and SPU. First marked ownership closes native permission (`SPU+0x164 = 1`). Accepted FIST confirms latch `0`, opens or refreshes **one** pending opportunity and retires prior timing state; opportunities never stack.

After the untouched native CombatMove, a matching pending opportunity/ordinal still present without exact contact can rearm latch `1 → 0`, with readback. A native miss leaves it pending. FullStop itself is not terminal authority.

Consumption occurs **before** Gothic's original OnDamage, only for caller-return `Game+0x16E348`, active raw8 invocation scope, exact Arg1 source/Arg2 actor, matching C1/source/SPU/opportunity ordinal and current raw8 identity. Native original runs once with unchanged arguments. Keep the execution record so later FIST can reopen. Contact dispatch is not HP success: Parade/block may produce zero visible damage (EV-349). Never inspect damage result, visited targets or gameplay outcome to decide consumption.

Timing permission at exact `Game+0x16E180` can repeatedly return the proven threshold+epsilon while the opportunity is pending, matching timing actor/motion and real time below that value. It never changes the real animation clock. Reaching the value, timing-identity change, refresh or contact retires timing; timing retirement alone **does not consume** the opportunity. Logical lifetime survives proven same-C1 Sprint9 → Power2 transport (EV-354/377); animation identity governs timing, not logical lifetime.

After native AISetState, close the captured generation only: revalidate actor/SPU/source and close latch to1 when current generation still matches. If generation changed/invalid, retire stale stored state without writing the replacement latch. That no-write branch is source-reviewed, not naturally executed in EV-353. A later CombatMove also retires already-stale raw8 state and closes the exact live latch under strict liveness checks; replacement → later unmarked native fallback was accepted EV-364. No polling, per-target list, triggered-list mutation, collision-group cleanup or custom contact/damage policy.

### 4.2 Raw55 — exact first opening, second clear only

Eligibility precedes these tables: exact current RIGHT/raw55, valid actor/C1 and matching marked Hit motion, immutable origin and source, one/two authored FIST markers, no equipped-marker mixture or resolved raw8 source. Same-origin continuation is required, except bound Sprint may continue as Power. Duplicate/budget/identity contradictions cannot authorize intervention.

Within the exact supported native callback scope, suppress only a premature RIGHT `5 → 7` request before any accepted FIST; retain callback/state progression. Never suppress the whole callback or normalize arbitrary states.

| Immutable origin | FIRST family/SP gate | SECOND family/SP gate |
|---|---|---|
| Quick | Current Quick AND (SP0 OR (SP1 AND `earlyOpeningSuppressed`)) | Current Quick; no additional SP predicate here. |
| Normal | Current Normal AND (SP0 OR (SP1 AND `earlyOpeningSuppressed`)) | Current Normal AND (SP0 OR SP1). |
| True Power | Current Power AND (SP1 OR SP2) AND `earlyOpeningSuppressed` | Current Power AND (SP1 OR SP2). |
| Sprint | Current Sprint AND (SP1 OR SP2) AND `earlyOpeningSuppressed` | Current Power at SP1/SP2 OR current Sprint at SP1/SP2, within the bound execution. |

The table is not a standalone acceptance predicate: FIRST additionally needs exact source group5; SECOND needs authored count2, accepted count1 and source group7. Power/Sprint first-marker suppression is mandatory at **both** SP1 and SP2. Current-Sprint/SP1 marker2 is accepted, not the superseded SP2-only rule (EV-385–388).

| Event | Physical operation |
|---|---|
| FIRST | Request exact RIGHT `Item_Equipped(5) → Item_Attack(7)` and verify group7. Clear contacts for Quick, or Normal at SP0; no universal first clear for Power/Sprint or Normal/SP1. |
| SECOND | `ClearTriggeredList()` only; no second physical opening. |
| Marked Normal native between-contact clear | Within the exact Normal callback scope, after first accepted FIST at SP0, suppress the exact current owned trigger/`Script_Game+0x386C6` clear once; marker2 owns replacement rearm. |
| End | Gothic exact native `7 → 5` first; C1 backup only for an outstanding live/equipped source. No independent raw55 terminal system. |

Normal marker2 may be SP0 before or after hit1 (EV-382). An early clear can clear an empty list and guarantees no second damage event. No hit1 flag, visited-target gate, delay, queue, version detection or `SP >= 1` generalization is accepted. Correct raw55 open/rearm/cleanup and zero native contact can coexist; unmarked native windows can also miss (EV-381).

## 5. C1 lifecycle and must-preserve safety

C1 monotonic generation is durable execution identity, shared with marker occurrence/dedupe. Each exact equipped source has its own cleanup obligation; successful offense requests count even `7 → 7`, and a successful transition away fulfills that source's obligation. Dual sources stay independent. Marker bookkeeping, physical obligation and contact visited-list bookkeeping are distinct.

CombatMove acquires ordinary generations. Proven pre-Combat offense can lazily acquire through a validated live ScriptFunction/SPU/state-stack/frame/source correlator; matching CombatMove consumes/retires that temporary binding before dispatch return/suspension. Raw frame/argument pointers are not durable identities. Preserve GetUpAttack pre-Combat offense, GetUpParade/defensive and pre-activation no-offense, ordinary completion, reaction cleanup and reentrant replacement behavior.

After native AISetState returns, finalize only the captured generation. Establish exact current equipped RIGHT/LEFT liveness **before dereferencing** remembered source pointers:

| Captured exact-source condition | C1-R1 result |
|---|---|
| No outstanding obligation | `NO_OP_NO_OUTSTANDING` |
| Outstanding, not current equipped source | `UNRESOLVED_NOT_EQUIPPED`; no dereference/mutation. |
| Live, actual group already not7 | `NO_OP_PHYSICALLY_CLEAN_RECONCILED` |
| Live, outstanding, actual group7 | `DeactivateOwnedAttackSource` once to5; verify `REPAIRED_TO_ITEM_EQUIPPED`, otherwise divergence with no retry/fallback mutation. |

No `ClearTriggeredList()` terminal cleanup. Do not substitute Recover, FullStop, motion replacement, callback return, generic ProcessScript dispatch, held-Use2 time, world scan or wall-clock timer for exact ownership/finalization. Mutate fixed sources first, report diagnostics afterwards. Raw8 retires its own generation-safe latch/opportunity (§4.1), never an equipped obligation. Raw55 retains native cleanup plus this backup.

C1-R1 acceptance includes EV-206–207/367/384; no positive outstanding unresolved-not-equipped repair case or NPC destructive-abandonment physical-repair claim exists. These remain evidence limits, not open gates. Stateless player bad-block deferral in [DESIGN §9](DESIGN.md#9-attackcontinuationprotection) is accepted independently; successful prevention never removes C1 safety.

## 6. Diagnose with the smallest sufficient facts

**Marker recognized ≠ accepted occurrence ≠ source opened/rearmed ≠ native contact ≠ visible damage.** First classify which boundary failed. Observe actor, factual action/family/phase/SP, current motion, C1 generation, source identity/UseType/side, opcode/authored/accepted ordinal and rejection reason; then before/requested/after group, clear operation or raw8 opportunity/timing/contact state. Repair claims additionally need outstanding obligation, current-source liveness and verified result. Missing visible damage alone proves none of these failed.

Known successful paths use compact CORE; unexpected rejection, source/family, overlap, repair/divergence or identity contradiction needs richer factual observation. Add only the DEEP signal or isolated probe that resolves the concrete unknown. Exact historical CORE field schemas remain recoverable in the archived diagnostics snapshot. Do not restore broad stacks, repeated address/threshold dumps or polling as routine logging. RuntimeClock and raw8 timing/contact hooks remain behavior-required without diagnostics.

Retained `Script_FrameCollisionBehaviorTest` / `Script_FrameCollisionTest` are **historical collision-only twins**: they omit the full current Speed/Raise/Movement/integrated bad-block assembly. They cannot certify that assembly. Product dependency/purity and hook exclusivity are owned by release architecture §§2–7; never load competing products together or disable a DLL merely by renaming it inside `scripts`. Observational production validation with exact source/binary identity and frozen User matrix is legitimate when instrumentation is absent (EV-389/390).

## 7. Safe modification and deliberate reopening

1. Classify existing regression, asset/setup mismatch, or deliberate new mechanism/scope. Read the relevant section, named source owner and only the conditional hook/authoring facts.
2. Compare the strongest exact facts: source/C1/motion/ordinal, eligibility gate, requested operation, native contact and cleanup. Preserve fallback and all relevant exclusions. Do not invent damage policy from a miss.
3. Freeze the smallest bounded change and independent review under Work protocol. Truly unknown mechanisms use FEATURE_DEVELOPMENT_METHOD's isolated probe first, not experimental policy in Bridge or a stable feature.
4. For later authorized runtime validation, use POP-02–05 exact setup/fixtures, POP-06 evidence handling and POP-07 for large logs; include the directly changed route plus relevant fallback, replacement/cleanup and shared-hook sentinels. Release architecture §8 owns generic purity/integration gates. Work does not build/run unless explicitly authorized.

Collision validation may reopen for exactly these triggers:

1. New runtime observation directly contradicts an accepted collision invariant.
2. Future feature integration appears to regress accepted collision behavior.
3. A new supported source/family/marker semantic is deliberately added.
4. The engine/mod compatibility scope materially expands beyond accepted evidence.
5. Production build architecture changes in a way that could alter collision execution.

A routine assembled-system safety regression is not itself reopening closed collision causal research. If integration fails, isolate its smallest factual route first. Do not repeat complete closed campaigns without a new need. Promote changed reusable conclusions to this owner and proof to EV routing under knowledge-maintenance §3A/§5.

## 8. Rationale and deeper recovery

Use these only for the specific disputed detail. All EVs route through EVIDENCE_INDEX; archived snapshots preserve full causal reasoning and original claims.

| Topic / reason | Current exact facts / proof | Conditional archived depth |
|---|---|---|
| Native action/source outranks filename; exact-set authoring | Animation rules §§9–11; EV-143–147/241–244/306–308/383 | [Old reference](archive/investigations/COLLISION_REFERENCE_PRE_CONSOLIDATION_2026-10-08.md) |
| Native-first, exact-source liveness avoids stale-pointer repair | Hook guide §3; ADR-0002; EV-163–172/180–215/367/384 | [Lifecycle](archive/investigations/COLLISION_LIFECYCLE_PRE_CONSOLIDATION_2026-10-08.md), [cleanup map](archive/investigations/COLLISION_CLEANUP_CALLSITE_MAP_PRE_CONSOLIDATION_2026-10-08.md) |
| Raw8 must survive misses; contact is not damage; generation safety | Hook guide §4; EV-346–364, especially349/353/354/364; EV-377 | [Raw8 architecture](archive/investigations/COLLISION_RAW8_PRODUCTION_ARCHITECTURE_PRE_CONSOLIDATION_2026-10-08.md) |
| Raw55 gates retain native callback/contact progression | Hook guide §§3,5; EV-262–298/381–382/385–388 | [Raw55 architecture](archive/investigations/COLLISION_RAW55_PRODUCTION_ARCHITECTURE_PRE_CONSOLIDATION_2026-10-08.md) |
| Bound Sprint continuity is not ordinary Power ownership | ADR-0003; EV-320–329/354/377/385–388 | Corresponding mechanism snapshots above |
| Diagnostics observe; release cannot depend on them | Release architecture §§5–8; ADR-0001; EV-215/389–390 | [Diagnostics schema](archive/investigations/COLLISION_DIAGNOSTICS_PRE_CONSOLIDATION_2026-10-08.md), [closed test plan](archive/investigations/COLLISION_TEST_PLAN_PRE_CONSOLIDATION_2026-10-08.md) |

[Path migrations](EVIDENCE_PATH_MIGRATIONS.md#2026-10-08--collision-documentation-consolidation) records exact original checkpoint/blob/SHA256, seven snapshot paths and recovery of historical internal links. Current source and this contract remain the ordinary working interface.
