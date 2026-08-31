# Collision Lifecycle Test Plan

**Status:** Current staged validation plan — Gates 1–3 CLOSED/PASS; Gate 4 audit CLOSED/PASS; bounded implementation FROZEN  
**Updated:** 2026-08-31

## Purpose

Validate the collision system through small falsifiable stages while preserving the closed C1-R1 lifecycle-safety contract and diagnostics-free release architecture.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact transient continuation: `BETWEEN_CHATS.md`.  
Frozen Gate 4 implementation: `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`.  
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
- Gate 4 may replace only marker-local execution-lifetime inference with existing C1 generation identity. Independent marker invariants remain protected.

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

Conclusion:

```text
Gate 2 = CLOSED/PASS
```

Do not rerun Gate 2 merely because later work uses the behavior-only target.

---

## 5. Gate 3 — Behavior-Only Smoke / Equivalence: CLOSED/PASS

The User synchronized the local checkout to:

```text
2fb28e5a27333eb6da902dc5c1d46a11fbe0d809
```

Behavior-only target:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

Deployment isolation passed; the diagnostic target was absent and built/live SHA matched.

Runtime result:

```text
main menu reached successfully
main-menu exit succeeded normally
User then performed many different functional tests under the frozen Gate-3 exercise and reported everything working as intended
```

Interpretation boundary:

```text
Gate 3 proves functional behavior-only smoke/equivalence
Gate 3 does NOT independently prove internal C1/marker/source events
Gate 2 remains the internal diagnostic evidence authority
```

Evidence: EV-212.

Conclusion:

```text
Gate 3 = CLOSED/PASS
```

---

## 6. Gate 4 — Marker-Bookkeeping Simplification

Frozen authority:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
```

### 6.1 Audit/classification: CLOSED/PASS

The audit reconstructed the required historical route and inspected the current marker/C1 source.

Result:

> **The C1 monotonic generation now supplies the durable attack-execution identity that the older marker module inferred from source/motion/action/phase/state-time. Only that execution-lifetime inference is superseded. Authored marker semantics remain independent and protected.**

Superseded class A:

```text
controlled-callback key/state-time retirement
lastControlledCallbackStateTime
MarkerWindowStillMatchesActorExecution as lifetime authority
new-execution reset inferred from source/motion/action/phase/state-time changes
authored-count change used as new-execution trigger
whole marker-execution retirement inferred from natural source cleanup
```

Preserved class B:

```text
exact current-motion ownership
Normal / Quick / full-Whirl eligibility
required RIGHT/LEFT source preflight
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
marker-owned active source/window mask
exact-set switching
natural retirement of exact physical source bits
OFF intra-Hit gap
Quick/full-Whirl StatePosition suppression
Fist current research behavior
unmarked/unsupported native fallback
late/dead/unsupported marker rejection
valid-motion-only marker caching
```

### 6.2 Bounded implementation: FROZEN / NEXT

Implement only the contract.

Required new factual authority:

```text
CollisionLifecycleGuard read-only current-generation query

no actor record -> invalid
actor record -> current exact actor + monotonic generation
no lifecycle mutation
```

Marker occurrence/dedupe execution records become generation-scoped:

```text
different valid C1 generation
→ fresh marker budget + dedupe state

same valid C1 generation
→ preserve occurrence history
→ do not silently create a fresh execution because source/motion/action/phase/state-time changed
```

Unexpected contradiction within one generation must fail closed/reject rather than reset as a new execution.

Natural source retirement remains factual only:

```text
source leaves Item_Attack
→ clear exact active marker-owned source bit
→ erase physical marker-owned window if empty
```

It must no longer decide occurrence/dedupe execution lifetime through action/phase/motion/state-time heuristics.

Critical stop condition:

```text
if a marker point requiring generation-scoped bookkeeping has no valid C1 generation
OR source/API/calling-convention evidence contradicts the frozen contract
→ STOP and report
→ do not invent fallback execution identity
```

No new hook, no family expansion, no C1 repair change, no marker semantic change.

### 6.3 Required source implementation audit

Before publication:

```text
confirm no marker semantic removed
confirm no C1 lifecycle mutation semantics changed
confirm no new hook added
confirm RetireMarkerOwnedSource still retires exact physical source bits
confirm OFF/exact-set switching cannot retire whole occurrence execution
confirm duplicate + occurrence protection remain active
git diff --check
```

### 6.4 Frozen post-implementation CORE regression

After independent Normal Chat source review, deploy the diagnostic product alone and prove:

```text
A. same-motion two-contact attack
   - first genuine marker accepted
   - later genuine marker accepted
   - replay callbacks still rejected

B. interrupted attack after first marker -> immediate same-motion new attack
   - new attack receives a fresh C1 generation
   - first marker receives fresh occurrence budget
   - later genuine marker accepted

C. explicit OFF / exact-set switching inside one execution
   - remains on one C1 generation
   - does not reset occurrence execution

D. natural cleanup inside one execution
   - exact physical marker-owned source/window bit retires
   - no fabricated new generation

E. marked full-Whirl destructive bad skip
   - dead/late callbacks do not reopen collision
   - C1 terminal repair remains unchanged

F. whole run
   - no invariant/divergence/unresolved/failure signal
   - clean shutdown
```

If compact CORE does not expose the generation facts needed to prove this, add only the smallest compact factual field needed; do not enable deep diagnostics by default.

### 6.5 Behavior-only follow-up

Only after the CORE regression passes:

```text
rebuild/deploy Script_FrameCollisionBehaviorTest alone
perform compact functional smoke
confirm no diagnostic dependency
```

Then Gate 4 implementation can close.

---

## 7. Later Order

```text
implement/review/test Gate 4 bounded simplification
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
