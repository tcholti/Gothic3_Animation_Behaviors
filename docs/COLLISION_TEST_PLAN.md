# Collision Lifecycle Test Plan

**Status:** Current staged validation plan — post-rewrite Gate 2 open  
**Updated:** 2026-08-31

## Purpose

Validate the collision system through small falsifiable stages while preserving the already-closed C1-R1 lifecycle-safety contract and the diagnostics-free release architecture.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact transient continuation: `BETWEEN_CHATS.md`.  
Frozen rewrite: `SECOND_PASS_REWRITE_CONTRACT.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## 1. Standing Rules

- Do not reopen closed C1-R1 semantics because code structure or diagnostics change.
- Native cleanup gets first opportunity.
- Successful exact-source `Item_Attack` creates the obligation; successful transition away fulfills it.
- Terminal repair may mutate only an already-owned exact outstanding source after native cleanup opportunity and established current-equipped liveness.
- Preserve marker ownership, occurrence/replay protection, source switching, OFF semantics, repeated-contact rearm and StatePosition suppression until their dedicated later simplification gate.
- Keep diagnostics independent from behavior correctness.
- Public/released behavior must not compile research diagnostics.
- Preserve raw runtime logs exactly as produced.
- If compact diagnostics make a required validation fact ambiguous, treat that as diagnostic insufficiency; do not reinterpret ambiguity as proof.
- Do not deploy diagnostic and behavior-only prototype DLLs together.
- Follow `PROJECT_OPERATING_PROCEDURES.md` for build/deploy/test/raw-artifact operations.

Authoritative diagnostic research target:

```text
Script_FrameCollisionTest
```

Behavior-only architecture target:

```text
Script_FrameCollisionBehaviorTest
```

---

## 2. Closed Safety / Pre-Rewrite Gates

```text
B6 replacement/deferred ProcessScript candidate      EV-174–EV-181
B7/B7b termination / continuation loss               EV-182–EV-189
B8 cross-family abandonment generality               EV-190
B9 cleanup/finalization ordering                      EV-191
C1 shadow execution/source obligation core           EV-192–EV-193
C1 pre-Combat acquisition gap                        EV-194
C1-O1 outer ScriptFunction lifetime/correlation      EV-195–EV-196
hook/finalizer substrate stabilization               EV-199–EV-203
C1-O2-P1 lightweight dispatch bridge                 EV-204
C1-O2-P2 lazy pre-Combat acquisition/consumption     EV-205
C1-R1 controlled native-equivalent physical repair   EV-206–EV-207
post-EngineBridge unchanged runtime baseline         CLOSED/PASS
```

C1-R1 validation is closed. Do not recreate the broad R1 program for structural changes.

Accepted terminal repair remains exactly:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify Item_Equipped(5)
```

Two explicit R1 qualifications remain and do not reopen the gate:

```text
- no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case;
- no positive NPC destructive-abandonment / C1 physical-repair case claimed.
```

---

## 3. Second-Pass Rewrite — IMPLEMENTED

Frozen architecture authority:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

Implementation:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

### Gate 1 — source/build separation: CLOSED/PASS

Completed:

```text
bounded source audit = PASS
git diff --check = PASS
Script_FrameCollisionTest Release build = PASS
Script_FrameCollisionBehaviorTest Release build = PASS
behavior-only target excludes CollisionDiagnostics/deep sources/defines/hooks = PASS
```

Startup/deployment sentinel also passed:

```text
built/live diagnostic SHA256:
25980C09DC0AB3ECAF69397F0AE3CA8D5566FF816B1210F44182D4508B292109

DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
Hooks installed.
Script_FrameCollisionTest unloading cleanly.
```

Raw:

```text
research/raw/2026-08-30_second_pass_core_diagnostic_startup_load_unload.log
commit 6bf59e6c08aebf6097566192b239092f0f734ea5
```

Evidence: EV-208.

---

## 4. Gate 2 — Post-Rewrite CORE Diagnostic Sufficiency: OPEN

Purpose:

```text
prove the reduced default CORE diagnostic build still supplies enough evidence
for the small structural-regression matrix without enabling deep diagnostics
```

Minimum sentinels:

```text
known positive stale-source repair
ordinary native cleanup no-op
legitimate reaction cleanup no-op
Dual source independence
one marked-source regression
Fist/unarmed negative
crossbow negative
clean shutdown
```

CORE diagnostics must establish, where relevant:

```text
marker ownership/suppression/result
exact source requested/before/after transition
C1 generation + exact-source obligation
cleanup fulfillment
pre-Combat acquisition/consumption
finalization/repair outcome
explicit invariant/failure signals
enough gameplay context to classify the sentinel being tested
```

### Gate 2 progress already closed/PASS

Mixed raw:

```text
research/raw/2026-08-30_second_pass_core_mixed_melee_bad_skip_attempts.log
commit a7995225310789c78a85cbce9940c86d41de74b0
```

This run establishes:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  marked-source regression
PASS  clean shutdown
```

Positive repair coverage is stronger than one sentinel: eight exact `REPAIRED_TO_ITEM_EQUIPPED` finalizations were observed across 2H Whirl and 1H Quick, each with outstanding exact source at group 7 and exact repair to group 5. Ordinary 2H/1H Normal and clean Quick cases show native cleanup fulfillment followed by `NO_OP_NO_OUTSTANDING`. Normal/Quick/Whirl marker ownership and Whirl OFF/occurrence/dead-callback handling are also represented.

Evidence: EV-209.

### Current Gate 2 blocker — reaction classification ambiguity

Focused reaction raw:

```text
research/raw/2026-08-30_second_pass_core_legitimate_reaction_cleanup_noop.log
commit 86d41d4772ebfc320d67ca063e51b28523fcfb9e
```

Observed:

```text
visual behavior looked correct
healthy exact source 7 -> 5 cleanup exists
C1 finalization is NO_OP_NO_OUTSTANDING
no repair is indicated
```

But current compact `ENGINE SetCollisionGroup` evidence does not include enough player gameplay context to distinguish:

```text
ordinary Hit -> Recover cleanup
vs
legitimate reaction-owned cleanup
```

Therefore the reaction sentinel is **NOT CLOSED**. This is a compact diagnostic-sufficiency failure, not a demonstrated collision behavior failure.

Per the Gate-2 rule, do not continue remaining sentinels while this required fact is ambiguous.

---

## 5. Immediate Bounded Correction Before More Gate 2 Runtime Testing

Change only compact diagnostics:

```text
CollisionDiagnostics::LogSetCollisionGroup
```

Restore these fields on relevant `ENGINE SetCollisionGroup` records:

```text
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
```

These use already-established actor APIs; no new source/API/calling-convention question is open.

Do not:

```text
add or restore deep hooks
add stack/callsite probes
change EngineBridge hook transport/order
change CollisionLifecycleGuard
change C1 predicates or repair
change marker semantics/bookkeeping
change source operations
change RuntimeClock
change behavior-only target
turn deep diagnostics on by default
expand attack families/Fist semantics
```

Required validation after the diagnostics-only source correction:

```text
bounded source diff audit
git diff --check
build Script_FrameCollisionTest Release
verify only intended diagnostic source changed and behavior-only separation remains intact
deploy exact diagnostic DLL alone
verify built/live SHA
verify CORE / DeepDiagnostics: DISABLED startup
rerun focused legitimate-reaction cleanup sentinel
```

If CORE then unambiguously proves reaction-owned 7->5 cleanup + `NO_OP_NO_OUTSTANDING`, mark reaction sentinel PASS and continue Gate 2.

If the required fact remains ambiguous, stop and reassess the smallest compact evidence addition before enabling deep diagnostics.

---

## 6. Remaining Gate 2 Sentinels After Reaction Closure

```text
OPEN  Dual source independence
OPEN  Fist/unarmed negative
OPEN  crossbow negative
```

Do not rerun already-closed positive repair, ordinary cleanup, marked-source or shutdown sentinels unless a later source change actually touches their behavior/diagnostic evidence.

When all Gate-2 sentinels are unambiguous and clean:

```text
Gate 2 = CLOSED/PASS
```

Only then proceed to behavior-only runtime testing.

---

## 7. Gate 3 — Behavior-Only Smoke / Equivalence

After Gate 2 passes, deploy `Script_FrameCollisionBehaviorTest` **instead of** the diagnostic target.

Purpose:

```text
prove intended collision behavior does not depend on diagnostic source/state/hooks
```

Freeze the exact small matrix only after Gate 2 closes. Do not infer behavior-only runtime correctness from compilation alone.

---

## 8. Gate 4 — Later Marker Bookkeeping Simplification

Only after rewrite + Gate 2 + behavior-only smoke pass.

Classify every existing marker guard/check into:

```text
A. execution-lifetime inference genuinely superseded by stronger C1/native authority
B. independent marker invariant still required
```

Preserve group B:

```text
exact current-motion marker ownership
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
RIGHT/LEFT/BOTH/OFF exact-set behavior
StatePosition native-activation suppression
interruption/dead-execution rejection
```

EV-131–EV-133 and EV-167 are mandatory evidence before removing execution-retirement machinery.

---

## 9. Later Order

```text
finish Gate 2
→ behavior-only smoke/equivalence
→ marker bookkeeping simplification audit
→ equipped-melee marker expansion one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker + lifecycle regression
→ AttackContinuationProtection
→ mature research New Balance/Jackydima compatibility gate
→ migrate/redesign Raise + speed + config into mature modular foundation
→ later independent systems such as target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain separate diagnostic twin
```

Do not combine unrelated later responsibilities unless a separately frozen contract explicitly authorizes it.

---

## 10. Evidence Handling

For runtime stages:

```text
freeze exact question/matrix/raw filename
→ preserve raw unchanged
→ publish raw
→ use deterministic large-log reduction only if retrieval requires it
→ interpret in Normal Chat
→ update exact evidence/current authorities when meaning changes
```

Do not ask the User to paste large successful logs into Chat.
