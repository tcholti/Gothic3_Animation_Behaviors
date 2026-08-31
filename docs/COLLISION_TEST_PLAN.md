# Collision Lifecycle Test Plan

**Status:** Current staged validation plan — Gate 2 CLOSED/PASS; Gate 3 OPEN/FROZEN  
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
- Follow `PROJECT_OPERATING_PROCEDURES.md` for local build/deploy/test/artifact operations.

Authoritative diagnostic target:

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

Initial post-rewrite diagnostic startup/load-unload also passed. Evidence: EV-208.

---

## 4. Gate 2 — Post-Rewrite CORE Diagnostic Sufficiency: CLOSED/PASS

Purpose:

```text
prove the reduced default CORE diagnostic build still supplies enough evidence
for the frozen structural-regression matrix without enabling deep diagnostics
```

Required sentinels:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  legitimate reaction cleanup no-op
PASS  Dual source independence
PASS  one marked-source regression
PASS  Fist/unarmed negative
PASS  crossbow negative
PASS  clean shutdown
```

### 4.1 Initial mixed CORE closure

Raw:

```text
research/raw/2026-08-30_second_pass_core_mixed_melee_bad_skip_attempts.log
commit a7995225310789c78a85cbce9940c86d41de74b0
```

Established:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  marked-source regression
PASS  clean shutdown
```

Eight exact `REPAIRED_TO_ITEM_EQUIPPED` finalizations were observed across 2H Whirl and 1H Quick; ordinary clean attacks remained native-cleanup/no-op. Evidence: EV-209.

### 4.2 Reaction ambiguity and bounded diagnostic correction

The first focused reaction run behaved correctly but lacked enough compact context to prove reaction-owned cleanup. That was classified as diagnostic insufficiency, not behavior failure.

Diagnostics-only correction:

```text
5b92b79a5af63c38e66a7ec8deecd0876c2cf141
Restore Gate 2 SetCollisionGroup context
```

Restored compact fields:

```text
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
```

Validated rebuilt diagnostic DLL:

```text
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
```

Focused reaction rerun:

```text
research/raw/2026-08-31_second_pass_core_legitimate_reaction_cleanup_noop_context_restored.log
commit 2ca3f76aeb1b832d5be22985e3f6fd58ef8d4191
```

The restored context separated ordinary completion cleanup from interruption/knockdown cleanup and proved the reaction sentinel unambiguously while remaining `NO_OP_NO_OUTSTANDING` with no repair. Evidence: EV-210.

### 4.3 Remaining sentinel closure

Dual:

```text
research/raw/2026-08-31_second_pass_core_dual_source_independence.log
commit c5d833c6d749636f238879b46d196e7865248ac8
```

Fist/unarmed:

```text
research/raw/2026-08-31_second_pass_core_fist_unarmed_negative.log
commit b914f7660a424f502b21f85ee668b694760dbbae
```

Crossbow:

```text
research/raw/2026-08-31_second_pass_core_crossbow_negative.log
commit 0b23be7a22c3b96e817db2fc9522d854b4739d2f
```

Results:

```text
PASS  Dual exact-source independence
PASS  Fist group-0 / no weapon-style C1 obligation
PASS  crossbow/Bolt negative behavior
PASS  clean shutdown
```

No searched repair-divergence/invariant/unresolved/failure signal occurred in these focused runs. Evidence: EV-211.

### 4.4 Gate 2 conclusion

```text
Gate 2 = CLOSED/PASS
```

The compact CORE diagnostic profile is sufficient for the frozen post-rewrite structural matrix. Deep diagnostics were not required.

Do not rerun Gate 2 merely because Gate 3 uses the behavior-only target.

---

## 5. Gate 3 — Behavior-Only Smoke / Equivalence: OPEN / FROZEN

Purpose:

```text
prove intended collision behavior does not depend on diagnostic source/state/hooks
```

This is a **small functional smoke**, not a duplicate of the full diagnostic Gate-2 matrix.

### 5.1 Build/deploy contract

```text
sync local branch to current remote head
→ build Script_FrameCollisionBehaviorTest Release
→ identify/hash exact built DLL
→ remove Script_FrameCollisionTest diagnostic DLL from live scripts
→ deploy Script_FrameCollisionBehaviorTest.dll alone
→ verify exactly one intended collision prototype DLL is live
→ verify built/live SHA equality
→ main-menu load/exit smoke
→ only then run the functional matrix
```

Diagnostic and behavior-only prototypes must never be live together.

Because the post-Gate-1 source correction touched diagnostic-only `CollisionDiagnostics.cpp`, no behavior-core semantic change has occurred since the behavior-only target's Gate-1 build. Gate 3 still rebuilds the behavior-only target at the current branch head so deployment identity is explicit.

### 5.2 Frozen functional matrix

#### A. Marked 2H Normal positive

```text
fixture:
marked player 2H Normal

minimum:
2–3 attacks against a target

pass:
intended attack damage/contact still occurs
no crash or obvious marker-path regression
```

#### B. Stale-source repair functional smoke

```text
fixture:
established vulnerable player 2H full-Whirl held-Use2 bad-skip reproduction

minimum:
3 attempts in which the attack has already made offensive contact before the destructive skip

after each successful destructive skip:
return to Ambient/running
→ touch/run into the target without attacking
→ target must not take passive stale-weapon damage
→ perform a following ordinary attack
→ that ordinary attack must damage normally
```

This is the user-visible consequence check for the already-validated C1 repair. It does not attempt to re-prove internal per-source diagnostics without diagnostics.

#### C. Unsupported/native-fallback smoke

```text
fixture:
player crossbow

minimum:
3 ordinary shot cycles against a target

pass:
aim/shoot/reload flow remains normal
no visible melee-marker/repair interference
```

#### D. Shutdown

```text
exit Gothic 3 normally
```

### 5.3 Gate 3 acceptance

```text
main-menu load succeeds
no runtime crash
marked 2H positive behavior remains functional
no passive stale-weapon damage after destructive skip
later legitimate melee attack remains functional
crossbow/native fallback remains functional
normal exit
```

### 5.4 Evidence handling

`Script_FrameCollisionBehaviorTest` intentionally contains no diagnostics, so no `Script_FrameCollisionTest.log`-style raw runtime artifact is expected.

Do **not** co-load diagnostics or add logging just to create Gate-3 evidence.

Gate-3 evidence will consist of:

```text
exact source/branch head
exact behavior-only built/live DLL identity/hash
successful main-menu load
User's controlled functional observations for A–D
```

If a functional failure occurs, stop and isolate the smallest failing case before any source change.

---

## 6. Gate 4 — Later Marker Bookkeeping Simplification

Only after rewrite + Gate 2 + Gate 3 pass.

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

## 7. Later Order

```text
Gate 3 behavior-only smoke/equivalence
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

## 8. Evidence Handling Rule

For diagnostic runtime stages:

```text
freeze exact question/matrix/raw filename
→ preserve raw unchanged
→ publish raw
→ use deterministic large-log reduction only if retrieval requires it
→ interpret in Normal Chat
→ update exact evidence/current authorities when meaning changes
```

For behavior-only Gate 3, follow §5.4 instead; do not add diagnostics merely to force the diagnostic artifact workflow onto a diagnostics-free product.
