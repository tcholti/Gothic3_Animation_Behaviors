# Collision Lifecycle Test Plan

**Status:** Current staged validation plan — Gates 1–4 CLOSED/PASS; equipped-melee marker expansion planning NEXT  
**Updated:** 2026-09-01

## Purpose

Validate the collision system through small falsifiable stages while preserving the closed C1-R1 lifecycle-safety contract and diagnostics-free release architecture.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact transient continuation: `BETWEEN_CHATS.md`.  
Closed Gate 4 contract: `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`.  
Frozen rewrite: `SECOND_PASS_REWRITE_CONTRACT.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## 1. Standing Rules

- Do not reopen closed C1-R1 semantics because code structure, marker coverage or diagnostics change.
- Native cleanup gets first opportunity.
- Successful exact-source `Item_Attack` creates the obligation; successful transition away fulfills it.
- Terminal repair may mutate only an already-owned exact outstanding source after native cleanup opportunity and established current-equipped liveness.
- Keep diagnostics independent from behavior correctness.
- Public/released behavior must not compile research diagnostics.
- Do not deploy diagnostic and behavior-only prototype DLLs together.
- Preserve raw runtime logs exactly as produced.
- If compact diagnostics make a required validation fact ambiguous, treat that as diagnostic insufficiency; do not reinterpret ambiguity as proof.
- The monotonic C1 generation is the durable marker occurrence/dedupe execution identity.
- C1 generation does not replace authored marker semantics, source-set meaning, occurrence counts, replay suppression, OFF, repeated-contact rearm, supported-family ownership or physical marker-window state.
- Expand marker support one bounded equipped-melee mechanism/family at a time.

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

## 3. Second-Pass Rewrite / Product Gates

Frozen architecture authority:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

Implementation:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

### Gate 1 — source/build separation: CLOSED/PASS

Evidence: EV-208.

```text
bounded source audit = PASS
git diff --check = PASS
Script_FrameCollisionTest Release build = PASS
Script_FrameCollisionBehaviorTest Release build = PASS
behavior-only target excludes CollisionDiagnostics/deep sources/defines/hooks = PASS
```

### Gate 2 — CORE diagnostic sufficiency: CLOSED/PASS

Evidence: EV-209–EV-211.

Frozen structural sentinel matrix passed:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  legitimate reaction cleanup no-op
PASS  Dual source independence
PASS  marked-source regression
PASS  Fist/unarmed negative
PASS  crossbow negative
PASS  clean shutdown
```

Validated final Gate-2 CORE identity:

```text
Script_FrameCollisionTest.dll
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
```

### Gate 3 — behavior-only smoke/equivalence: CLOSED/PASS

Evidence: EV-212.

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

Deployment isolation, main-menu load/exit and user-observed functional smoke passed.

Interpretation boundary:

```text
Gate 3 proves functional behavior-only smoke/equivalence.
Gate 3 does not independently prove internal C1/marker/source events.
Gate 2 remains the internal diagnostic evidence authority for that build state.
```

---

## 4. Gate 4 — Marker-Bookkeeping Simplification: CLOSED/PASS

Frozen/closed authority:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
```

Implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Evidence closure:

```text
EV-213
```

### Accepted architecture

```text
valid C1 generation
= durable marker occurrence/dedupe execution identity
```

Superseded:

```text
marker-local execution reset inferred from source pointer
motion filename
action
phase
state-time rollback
authored-count change
controlled-callback state-time retirement
whole occurrence-execution retirement inferred from natural source cleanup
```

Preserved independently:

```text
exact current-motion ownership
Normal / Quick / full-Whirl eligibility
required source preflight
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
marker-owned physical source/window mask
exact-set switching
natural retirement of exact physical source bits
OFF intra-Hit gap
Quick/full-Whirl StatePosition suppression
current Fist/PhysicalFist research behavior
late/dead/unsupported marker rejection
unmarked/unsupported native fallback
valid-motion-only marker caching
C1 terminal repair contract and ordering
```

### Gate 4 source / CORE validation

Authoritative Gate-4 diagnostic identity:

```text
Script_FrameCollisionTest.dll
Length: 416768
SHA256: E69FB2602E3599A0905B63F2064B732D57CA9E1817CDED2BD7AB6C01C08392E9
```

Validated:

```text
PASS source audit / no new hooks / read-only generation query
PASS same-generation full-Whirl RIGHT -> OFF -> RIGHT
PASS first RIGHT 0 -> 1; second genuine RIGHT 1 -> 2
PASS replay OFF occurrence-budget rejection
PASS replay RIGHT same-update duplicate rejection
PASS natural cleanup retires exact physical marker source bit only
PASS incomplete prior execution cannot leak occurrence state into later same-motion generation
PASS destructive full-Whirl bad-skip dead/late rejection
PASS unchanged C1 exact-source repair
PASS 1H/Dual source-specific repair regression
PASS unsupported Power/native fallback regression
PASS zero no-generation / generation-inconsistency / invariant / divergence / unresolved signal
PASS clean diagnostic shutdown
```

Precision qualification:

```text
The current marked 2H Normal P0 asset has one authored RIGHT,
so it cannot literally reproduce EV-131's historical two-RIGHT Normal fixture.

The equivalent no-leak property was directly proven with the still-two-contact
P0 full Whirl: generation 34 consumed only first RIGHT; later generation 40
on the exact same motion received a fresh budget and accepted both genuine RIGHTs.
```

### Gate 4 behavior-only follow-up

Authoritative Gate-4 behavior-only identity:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

Validation:

```text
PASS build
PASS deployed alone; diagnostic twin absent
PASS exact built/live SHA match
PASS main-menu load
PASS normal exit
PASS user-observed Staff / 1H / 2H functional combat smoke
PASS repeated destructive bad-skip smoke
PASS no visible stuck collision, crash or regression
```

Conclusion:

```text
Gate 4 = CLOSED/PASS
```

Do not rerun Gate 4 merely for broader incidental combat coverage.

---

## 5. Next Validation Responsibility — Equipped-Melee Marker Expansion

This gate is **not yet frozen**. First perform Normal Chat design/planning.

Planning questions:

```text
1. current equipped-melee marker-supported families/actions
2. unsupported equipped-melee candidate families/actions
3. exact physical source semantics for each candidate
4. whether existing callback adapters are sufficient
5. which single candidate should become the first bounded expansion
```

Mandatory review item before expanding around Dual Quick:

```text
tested Dual P1 Quick authored marker = G3AB_COL_RIGHT
older tested native-source evidence = LEFT
```

Do not silently choose one interpretation. Determine whether the discrepancy is authoring/fixture intent, source-map evidence or a semantic distinction.

Before implementation:

```text
choose one candidate
→ freeze exact marker/source/callback contract
→ freeze compact diagnostic + behavior-only acceptance matrix
→ then launch bounded Work
```

Do not combine the first equipped-melee expansion with Fist source adaptation, AttackContinuationProtection, C1 redesign, Raise/speed/config or compatibility work.

---

## 6. Later Order

```text
equipped-melee marker expansion one mechanism at a time
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

---

## 7. Evidence Handling Rule

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
