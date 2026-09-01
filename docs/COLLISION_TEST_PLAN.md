# Collision Validation Plan

**Status:** Current collision validation authority — architecture verification COMPLETE through EV-215  
**Updated:** 2026-09-01

## Purpose

Define standing collision-validation rules, preserve closed boundaries, and state the minimum validation responsibilities for future collision work without retaining completed test chronology as a live queue.

Current state: `SESSION_ENTRYPOINT.md`.  
Transient continuation: `BETWEEN_CHATS.md` when needed.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.  
Exact proof: `EVIDENCE_INDEX.md` → canonical evidence ledgers.

---

## 1. Standing Validation Rules

- Do not reopen closed C1-R1 or Gate-4 semantics without contradicting evidence.
- Native cleanup gets first opportunity.
- Successful exact-source `Item_Attack` creates the lifecycle obligation; successful transition away fulfills it.
- Terminal repair may mutate only an already-owned exact outstanding source after native cleanup opportunity and established current-equipped liveness.
- The monotonic C1 generation is the durable marker occurrence/dedupe execution identity.
- C1 generation does not replace authored marker semantics, exact-set meaning, occurrence counts, replay suppression, OFF, repeated-contact rearm, supported-family ownership, physical marker-window state or terminal lifecycle repair.
- Keep diagnostics independent from behavior correctness.
- Released behavior must not compile research diagnostics.
- Do not deploy diagnostic and behavior-only twins together.
- Preserve raw runtime logs exactly as produced.
- If compact diagnostics make a required fact ambiguous, treat that as diagnostic insufficiency rather than proof.
- Freeze exact test purpose/cases/order/raw filename before controlled diagnostic runs according to `PROJECT_PIPELINE.md` and POP-05.
- Do not invent a broader matrix after a gate is closed unless a concrete contradiction or intentionally new responsibility creates a new falsifiable question.

Authoritative current prototype products:

```text
Script_FrameCollisionTest
= instrumented diagnostic twin

Script_FrameCollisionBehaviorTest
= diagnostics-free behavior twin
```

---

## 2. Closed Lifecycle / C1 Foundation

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

Accepted terminal repair:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify Item_Equipped(5)
```

Retained qualifications:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / C1 physical-repair case claimed
```

These are limits on what is claimed, not open validation gates.

---

## 3. Verified Modular Architecture / Product Boundary

Second-pass architecture implementation:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

```text
Gate 1 source/build separation            CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency        CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping      CLOSED/PASS — EV-213
literal historical EV-131 regression      CLOSED/PASS — EV-214
final behavior-only architecture smoke    CLOSED/PASS — EV-215
```

```text
NEW COLLISION ARCHITECTURE VERIFICATION = COMPLETE
```

CORE diagnostics already proved the required architecture controls, including:

```text
known positive stale-source repair
ordinary native cleanup no-op
legitimate reaction cleanup no-op
Dual source independence
marked-source regression
Fist/unarmed negative
crossbow negative
clean shutdown
```

Historical product identities and exact run provenance remain in EV-208–EV-215 and archived evidence. They are not current deployment instructions.

---

## 4. Accepted Generation-Scoped Marker Model

Gate-4 implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Core rule:

```text
valid C1 generation
= durable marker occurrence/dedupe execution identity
```

Marker execution boundaries are no longer inferred from marker-local guesses based on source/motion/action/phase/state-time/authored-count changes or controlled-callback rollback.

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

EV-213 proves the generation-scoped implementation; EV-214 directly closes the literal EV-131 same-motion interruption/restart defect; EV-215 closes the final diagnostics-free functional/release-purity smoke.

Validated behavior-only identity used for EV-215:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

The behavior-only result is functional/release-purity evidence only. Internal generation, occurrence-budget, exact-set, replay/dedupe and terminal-repair proof remains in diagnostic evidence.

---

## 5. Current Validation Posture

There is **no pending architecture-verification test**.

New collision testing begins only when one of these occurs:

```text
a concrete contradiction appears
an existing behavior responsibility changes
a new source/family/marker mechanism is intentionally added
AttackContinuationProtection is implemented
a compatibility gate becomes active
production migration changes hook/source/config architecture
```

For each new responsibility:

```text
reconstruct only the causal evidence route relevant to that responsibility
→ freeze one falsifiable question
→ define the minimum positive + negative/regression controls
→ build/deploy only the exact product required
→ preserve one-product-at-a-time release/diagnostic separation
→ record canonical evidence only after interpretation
```

---

## 6. Future Required Collision Validation Boundaries

### Equipped-melee marker expansion

Add one mechanism/family responsibility at a time. Preserve all closed Normal/Quick/full-Whirl marker and C1 lifecycle behavior as regression controls.

Known deliberate source/authoring review item:

```text
Dual P1 Quick tested authored marker = RIGHT
older native-source evidence for tested Dual P1 Quick = LEFT
```

### Fist/body source adapter

Fist/body semantics remain separate from equipped weapon `Item_Attack`/`Item_Equipped` handling. Do not use weapon-style assumptions until a dedicated source model is proven.

### AttackContinuationProtection

`AttackContinuationProtection` is a **prevention** responsibility for the known held-Use2 destructive continuation-loss route. It must remain separate from `CollisionLifecycleGuard`, which remains the general exact-source lost-cleanup fail-safe.

Do not begin by resurrecting an attack after destructive teardown. First investigate whether the cleaner root fix is to prevent or defer only the destructive timeout consequence while a real attack CombatMove execution is active.

Preferred investigation model:

```text
held-Use2 timer continues normally

when its destructive consumer becomes due:
    if a real attack CombatMove execution would be destroyed
        suppress/defer only that destructive consequence
    else
        preserve native timeout behavior
```

Do not assume the timer itself should be reset/frozen; changing the timer may alter post-attack input semantics. Prefer the smallest native decision boundary supported by source/runtime evidence.

Before implementation prove:

1. the exact timeout decision/call path leading to destructive AIFullStop/state replacement;
2. whether that timeout has any legitimate responsibility while attack CombatMove is active;
3. whether preventing/defering only the destructive decision lets the attack complete normally;
4. whether the same timeout still behaves natively outside attacks;
5. whether legitimate reaction/interruption FullStop and AISetState remain untouched;
6. whether the module can consume shared execution facts without redefining C1 collision ownership.

Minimum first runtime falsification if source evidence supports the model:

```text
known bad-skip attack + held Use2 crossing threshold
→ destructive skip does not occur
→ attack continues through normal marker/native lifecycle
→ collision windows and native cleanup remain normal
→ C1-R1 remains available underneath but should not need to repair the prevented case

outside-attack control
→ same held-Use2 timeout preserves native behavior

reaction control
→ legitimate interruption/reaction cleanup and FullStop behavior still works
```

Even if prevention succeeds, keep C1-R1:

```text
AttackContinuationProtection
= prevent the known destructive route

CollisionLifecycleGuard / C1-R1
= fail-safe if an exact offensive source nevertheless loses cleanup opportunity
```

### Compatibility Gate 1 — mature research collision DLL

Before production collision migration, validate the mature marker/source/lifecycle/continuation assembly against New Balance and relevant Jackydima DLLs. Do not assume arbitrary same-function hook chaining or load-order safety.

### Compatibility Gate 2 — final `Script_G3AnimationBehaviors`

After collision migration plus Raise and redesigned speed control, repeat compatibility validation on the final production assembly before stable/release promotion.

---

## 7. Evidence and Artifact Boundary

```text
controlled runtime/source investigation
→ research/raw/ canonical intake
→ commit/publish unchanged artifact
→ interpretation
→ canonical EV update
→ EVIDENCE_INDEX route only when retrieval changes
→ research/archive/ once processed provenance is deliberately migrated
```

Future raw→archive migrations must preserve bytes/provenance and update canonical paths without leaving broken references.

`research/derived/` remains a deterministic navigation/analysis layer for oversized evidence; it does not replace canonical raw/archive artifacts.

---

## 8. Current Project Sequence

Architecture verification, evidence migration, stable promotion and temporary-branch retirement are complete.

The current repository responsibility is project stabilization, not collision testing:

```text
structural document/tool simplification
→ Gothic rules/procedures consistency audit
→ build/product/repository-shape audit
→ final readiness check
→ equipped-melee marker expansion planning
```

Exact current responsibility remains owned by `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`.
