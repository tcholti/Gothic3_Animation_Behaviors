# Collision Lifecycle Test Plan

**Status:** Current staged validation plan — Gates 1–3 CLOSED/PASS; Gate 4 AUDIT OPEN  
**Updated:** 2026-08-31

## Purpose

Validate the collision system through small falsifiable stages while preserving the closed C1-R1 lifecycle-safety contract and diagnostics-free release architecture.

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
- Keep diagnostics independent from behavior correctness.
- Public/released behavior must not compile research diagnostics.
- Do not deploy diagnostic and behavior-only prototype DLLs together.
- Preserve raw runtime logs exactly as produced.
- If compact diagnostics make a required validation fact ambiguous, treat that as diagnostic insufficiency; do not reinterpret ambiguity as proof.
- Marker-bookkeeping simplification may remove only execution-lifetime inference genuinely superseded by stronger authority; independent marker invariants remain protected until direct evidence says otherwise.

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
```

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

Main evidence:

```text
EV-209  mixed positive/ordinary/marker/shutdown closure + reaction ambiguity
EV-210  compact context restoration + unambiguous reaction closure
EV-211  Dual/Fist/crossbow closure
```

Validated final CORE diagnostic identity for Gate 2:

```text
Script_FrameCollisionTest.dll
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
```

Gate 2 conclusion:

```text
Gate 2 = CLOSED/PASS
```

The compact CORE diagnostic profile is sufficient for the frozen post-rewrite structural matrix. Deep diagnostics were not required.

Do not rerun Gate 2 merely because later work uses the behavior-only target.

---

## 5. Gate 3 — Behavior-Only Smoke / Equivalence: CLOSED/PASS

Purpose:

```text
prove intended collision behavior does not depend on diagnostic source/state/hooks
```

### 5.1 Build/deployment identity

The User synchronized the local checkout to:

```text
2fb28e5a27333eb6da902dc5c1d46a11fbe0d809
```

The behavior-only target built successfully:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

Deployment checks:

```text
Script_FrameCollisionTest.dll diagnostic target removed
Script_FrameCollisionBehaviorTest.dll deployed alone
live listing contained only Script_FrameCollisionBehaviorTest.dll
built SHA == live SHA
```

### 5.2 Frozen functional matrix

The frozen minimum exercise was:

```text
A. marked 2H Normal positive
B. established vulnerable 2H full-Whirl held-Use2 stale-source consequence check
C. crossbow/native-fallback smoke
D. normal exit
```

Acceptance was:

```text
main-menu load succeeds
no runtime crash
marked melee positive behavior remains functional
no passive stale-weapon damage after destructive skip
later legitimate melee attack remains functional
crossbow/native fallback remains functional
normal exit
```

### 5.3 Runtime result

Observed:

```text
main menu reached successfully
main-menu exit succeeded normally
User then performed many different functional tests under the frozen Gate-3 exercise and reported everything working as intended
```

Because `Script_FrameCollisionBehaviorTest` intentionally contains no diagnostics, no diagnostic runtime artifact was expected or required.

Interpretation boundary:

```text
Gate 3 proves functional behavior-only smoke/equivalence
Gate 3 does NOT independently prove internal C1/marker/source events
Gate 2 remains the internal diagnostic evidence authority
```

Conclusion:

```text
Gate 3 = CLOSED/PASS
```

If a later behavior-only regression appears, isolate that regression directly rather than reopening this entire smoke matrix by default.

---

## 6. Gate 4 — Marker-Bookkeeping Simplification Audit: OPEN

### 6.1 Purpose

Determine whether parts of the current marker execution/bookkeeping machinery are now redundant because stronger native/C1 execution authority exists, without weakening independent marker correctness.

This gate begins as an **audit/classification responsibility only**. It does not authorize source changes yet.

### 6.2 Required evidence route

Before proposing removal/consolidation, review only the active causal set:

```text
EV-066–EV-075
EV-131–EV-133
EV-167
EV-182–EV-196
EV-206–EV-207
EV-209–EV-211
COLLISION_LIFECYCLE_PLAN.md §9
```

Then inspect only the current `FrameCollisionMarkers` source necessary to map each relevant guard/check to the evidence.

### 6.3 Required classification

For every relevant marker guard/check classify:

```text
A. execution-lifetime inference genuinely superseded by stronger C1/native authority
B. independent marker invariant still required
```

A guard may be removed or consolidated only if the audit can state:

```text
what responsibility it currently owns
what stronger mechanism now owns that exact responsibility
why the old regression it prevented remains impossible or independently protected
which evidence establishes that claim
```

If that chain is incomplete, classify it as B / preserve.

### 6.4 Mandatory preserve-unless-disproved set

```text
exact current-motion marker ownership
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
RIGHT/LEFT/BOTH/OFF exact-set behavior
StatePosition native-activation suppression
interruption/dead-execution rejection
```

EV-131–EV-133 and EV-167 are mandatory before removing execution-retirement machinery.

### 6.5 Gate 4 output

The audit must produce a bounded table or equivalent mapping:

```text
current guard/check
→ responsibility
→ evidence route
→ classification A or B
→ proposed action: remove / consolidate / preserve
→ regression risk / required validation
```

Only after Normal Chat freezes an evidence-supported bounded simplification may a Work/source implementation task begin.

The current Dual P1 Quick authored RIGHT-marker/native LEFT-source mismatch belongs to later equipped-melee marker expansion and should not be folded into this bookkeeping audit unless it directly bears on one guard's correctness.

---

## 7. Later Order

```text
finish Gate 4 audit
→ implement/review/test only the bounded simplification actually justified
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

For behavior-only smoke stages, do not add diagnostics merely to force a diagnostic artifact workflow onto a diagnostics-free product. Preserve exact build/deployment identity plus the controlled user-observed result and keep the claim at functional-smoke scope.
