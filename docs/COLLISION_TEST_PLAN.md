# Collision Lifecycle Test Plan

**Status:** Gates 1–4 currently CLOSED/PASS by existing evidence; exact historical EV-131 Normal-fixture confirmation required before stable promotion/audit checkpoint  
**Updated:** 2026-09-01

## Purpose

Validate the collision system through small falsifiable stages while preserving the closed C1-R1 lifecycle-safety contract, diagnostics-free release architecture and one-product-at-a-time test discipline.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact continuation: `BETWEEN_CHATS.md`.  
Gate 4 contract: `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`.  
Rewrite authority: `SECOND_PASS_REWRITE_CONTRACT.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## 1. Standing Rules

- Do not reopen closed C1-R1 semantics without contradicting evidence.
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
- Expand future marker support one bounded mechanism/family at a time.

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

Explicit R1 qualifications remain:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / C1 physical-repair case claimed
```

---

## 3. Second-Pass Rewrite / Product Gates

Architecture implementation:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

### Gate 1 — source/build separation: CLOSED/PASS

Evidence: EV-208.

### Gate 2 — CORE diagnostic sufficiency: CLOSED/PASS

Evidence: EV-209–EV-211.

Validated matrix:

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

Final Gate-2 CORE identity:

```text
Script_FrameCollisionTest.dll
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
```

### Gate 3 — behavior-only smoke/equivalence: CLOSED/PASS

Evidence: EV-212.

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

Deployment isolation, main-menu load/exit and functional smoke passed.

---

## 4. Gate 4 — Generation-Scoped Marker Bookkeeping

Implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Current evidence closure:

```text
EV-213
```

Accepted architecture:

```text
valid C1 generation
= durable marker occurrence/dedupe execution identity
```

Preserve independently:

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

Authoritative Gate-4 CORE diagnostic identity:

```text
Script_FrameCollisionTest.dll
Length: 416768
SHA256: E69FB2602E3599A0905B63F2064B732D57CA9E1817CDED2BD7AB6C01C08392E9
```

Authoritative Gate-4 behavior-only identity:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

EV-213 already proves:

```text
PASS source audit / no new hooks / read-only generation query
PASS same-generation full-Whirl RIGHT -> OFF -> RIGHT
PASS first RIGHT 0 -> 1; second genuine RIGHT 1 -> 2
PASS replay OFF occurrence-budget rejection
PASS replay RIGHT same-update duplicate rejection
PASS natural cleanup retires exact physical marker source bit only
PASS incomplete prior execution cannot leak state into a later same-motion Whirl generation
PASS destructive full-Whirl bad-skip dead/late rejection
PASS unchanged C1 exact-source repair
PASS 1H/Dual source-specific repair regression
PASS unsupported Power/native fallback regression
PASS zero no-generation / generation-inconsistency / invariant / divergence / unresolved signal
PASS clean diagnostic shutdown
PASS behavior-only build/deploy isolation + functional smoke
```

### 4.1 Precision correction / final promotion-confidence test: PENDING

The last Gate-4 run used the installed marked 2H Normal P0 asset, which had only one authored RIGHT. The User later clarified that the original historical two-marker/two-contact Normal regression fixture still exists in Blender and was simply not exported for that run.

Therefore EV-213 remains valid, but before the new architecture is accepted for stable promotion/documentation cleanup, perform the literal EV-131-class Normal regression with the restored fixture.

Before the runtime attempt, verify through CORE diagnostics that the live fixture actually reports:

```text
Actor: PC_Hero
Family: NORMAL
ContainsReservedSourceMarker: 1
AuthoredRIGHTCount: 2
```

Then prove:

```text
A. execution A uses exact Normal motion M
B. first genuine RIGHT accepted under generation A
C. execution A interrupted before its later genuine RIGHT
D. next attack execution uses same exact motion M
E. execution B has a different fresh C1 generation
F. first RIGHT of B = 0 -> 1 and ExecutionBudgetReset: 1
G. later genuine RIGHT of B = 1 -> 2
H. replay callbacks remain rejected
I. no REJECTED_NO_C1_GENERATION
J. no REJECTED_C1_GENERATION_INCONSISTENCY
K. no INVARIANT / DIVERGED / UNRESOLVED signal
L. clean shutdown
```

Freeze one exact raw filename before the test according to `PROJECT_PIPELINE.md` and POP-05.

Interpretation:

```text
PASS
→ add next global EV confirmation
→ EV-213 remains valid and is strengthened by literal historical-fixture coverage
→ optionally perform one compact behavior-only fixture smoke with the already-built Gate-4 behavior-only DLL
→ architecture validation/promotion checkpoint complete

FAIL
→ reopen Gate 4
→ stop before documentation audit, stable integration or new marker expansion
```

No source rebuild is required solely because the animation fixture changes.

---

## 5. Stable-Subsystem Checkpoint After Exact Gate 4 Confirmation

Before new equipped-melee expansion, perform the User-requested documentation/knowledge-system audit under `KNOWLEDGE_MAINTENANCE.md` and `KNOWLEDGE_REGISTRY.md`.

Audit targets include:

```text
authority contradictions
unnecessary narrative duplication
stale current-state/closed-contract wording
bootstrap/read-first bloat
index routing quality
ledger continuation and global EV continuity
EVIDENCE_LEDGER / STEP_B / STEP_C / STEP_D duplication versus useful file splitting
processed raw artifacts needing archive promotion
superseded/obsolete documents
redundant future-use routes
```

Do not collapse ledger files merely because several exist. Preserve provenance and evidence IDs. First produce findings and a cleanup plan; then perform only justified consolidation/archive/deletion.

---

## 6. Stable Integration / Branch Cleanup After Documentation Audit

The established normal branch model is already:

```text
main
+ docs/collision-source-evidence
```

A third temporary branch exists:

```text
temp/second-pass-rewrite-publish
```

As of 2026-09-01 it is diverged from the active branch:

```text
active ahead by 35 commits
temp ahead by 10 commits
merge base 0aa6d19a6815934a3158715070320020bac64292
```

Required sequence:

```text
audit documentation/knowledge first
→ inspect temp-only commits/content
→ preserve anything unique that matters
→ define stable promotion set for proven architecture + cleaned knowledge
→ deliberately integrate stable checkpoint into protected main
→ verify main
→ delete temp branch only if safe
→ keep main + docs/collision-source-evidence as the normal two-branch model
```

Do not change branch meanings just to reduce the branch count.

---

## 7. Work After the Promotion Checkpoint

Only after the exact Gate-4 confirmation, audit and branch/stable-integration checkpoint should Normal Chat return to equipped-melee marker expansion planning.

Then:

```text
classify current marker-supported equipped-melee families/actions
→ review unsupported candidates and exact physical sources
→ explicitly resolve the Dual P1 Quick authored-RIGHT versus older native-LEFT evidence
→ choose one bounded expansion
→ freeze marker/source/callback + diagnostic/behavior-only acceptance contract
→ launch bounded Work
```

Keep Fist source adaptation, AttackContinuationProtection, Raise/speed/config, compatibility and later systems separate.

---

## 8. Evidence Handling Rule

Diagnostic runtime stages:

```text
freeze exact question/matrix/raw filename
→ preserve raw unchanged
→ publish raw
→ interpret in Normal Chat
→ update exact evidence/current authorities
```

Behavior-only smoke stages remain functional/visual claims; do not add diagnostics to the behavior-only product merely to create a log.
