# Collision Validation Plan

**Status:** Current collision validation authority  
**Updated:** 2026-09-27

## Purpose

Define the current collision-validation gate and what counts as acceptance after the completed research/diagnostic/behavior-only campaigns.

This file owns **what must still be validated**. It does not own implementation architecture, settled collision semantics, or historical proof.

Current state: `SESSION_ENTRYPOINT.md`.  
Current facts: `COLLISION_REFERENCE.md`.  
Permanent raw55 architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.  
Proof routing: `EVIDENCE_INDEX.md`.  
Detailed pre-production-migration plan: `archive/investigations/COLLISION_TEST_PLAN_PRE_PRODUCTION_MIGRATION_2026-09-27.md`.

---

## 1. Standing validation rules

- Do not reopen a closed causal gate without concrete contradictory evidence or deliberate scope extension.
- Factual native action/source/UseType identity outranks animation filename inference.
- Native cleanup gets first opportunity.
- Raw8 Fist, raw55 PhysicalFist, and equipped-source collision are separate mechanisms.
- C1 generation remains the durable plugin attack-execution identity for occurrence/dedupe and exact-source obligations.
- C1-R1 remains exact-source terminal backup repair only; it is not ordinary attack timing policy.
- Diagnostics must not be required for release behavior correctness.
- Diagnostic and behavior-only collision twins are mutually exclusive at runtime.
- Migration is not a redesign opportunity. Preserve the accepted behavior contract unless new contradictory evidence appears.
- Work/source-only sessions must not build or run Gothic 3. Runtime build/test remains on the User's home PC.
- Any future diagnostic runtime log is interpreted through POP-06 bounded retrieval; POP-07 remains the large-log specialization.

---

## 2. Closed collision validation landmarks

```text
standalone broad final-source regression       CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy                    PASS EV-375
focused New Balance raw55 compatibility        CLOSED/PASS EV-376–EV-382
dual-1H four-marker / three-window authoring   PASS EV-383
broad intended-stack New Balance               CLOSED/PASS EV-384
standalone Sprint/SP1 contradiction            FOUND EV-385 / CLOSED EV-386
corrected marked standalone final candidate    PASS EV-386
unmarked standalone raw55 native fallback      PASS EV-387
final-candidate New Balance regression         PASS EV-388
diagnostic phase                               CLOSED/PASS EV-386–EV-388
behavior-only release-purity gate              CLOSED/PASS EV-389
```

No full historical campaign should be repeated absent contradictory evidence.

---

## 3. Accepted final collision candidate

Reviewed behavior source:

`1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`

Final research binaries rebuilt from that shared source:

```text
Script_FrameCollisionBehaviorTest SHA256
D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78

Script_FrameCollisionTest SHA256
AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
```

The diagnostic twin completed the final standalone and New Balance gates through EV-388.

EV-389 then validated the diagnostics-free behavior twin itself:

```text
sole live collision twin = Script_FrameCollisionBehaviorTest.dll
built/live SHA exact match = PASS
diagnostic twin absent = PASS
Gothic 3 startup smoke = PASS
```

The observational positive/negative controls were deliberately stronger than native-timer-equivalent combat:

```text
Hack authored collision works
2H ON -> OFF -> ON produces distinct offensive windows
weapon overlap during authored OFF produces no hit
1H1H/dual multi-window BOTH/single-side/OFF/BOTH authoring produces intended extra contacts
extra authored swings beyond native attack structure collide
human Fist double markers can hit twice
Sabretooth raw8 double markers can hit twice
Troll raw55 double markers can hit twice
one-on-one and group combat show no observed stuck/persistent collision regression
```

Therefore the diagnostics-free collision behavior is accepted as release-pure before migration.

---

## 4. Current gate — production collision migration

The mature collision subsystem is now ready to move from the research/prototype surface into:

`src/Script_G3AnimationBehaviors`

The migration responsibility must be frozen and bounded before Work begins.

### 4.1 Migration invariants

The migration must preserve the already-accepted behavior rather than re-derive it.

At minimum preserve:

```text
equipped RIGHT / LEFT / BOTH / OFF exact-set behavior
repeated-contact ClearTriggeredList semantics
Power / Pierce / SimpleWhirl / Hack behavior
permanent equipped Sprint policy
raw8 Normal / Power / Quick / Sprint behavior
raw55 Normal / Quick / true Power / Sprint-origin behavior
raw55 explicit state gates, including Sprint-origin SP1/SP2 compatibility
unmarked raw8/raw55 native fallback
C1 generation-scoped occurrence/dedupe
C1-R1 exact-source terminal repair
native cleanup first / outstanding-zero convergence
separation compatibility assumptions already accepted
no custom target/contact/damage ownership
```

### 4.2 Release-purity boundary

Production migration must **not** pull diagnostic-only machinery into shipping behavior merely because the prototype diagnostic twin used it for observation.

```text
behavior required for correctness -> production owner
historical probes / diagnostic logging / evidence-only hooks -> remain outside shipping behavior
```

If a shared hook transport is required by production behavior, preserve the established single-owner architecture rather than duplicating hook ownership.

### 4.3 Source-only Work boundary

For the bounded Work implementation:

```text
NO build
NO Gothic 3 runtime execution
NO opportunistic collision redesign
NO new hooks unless migration proves an already-required accepted hook is absent from the production target
NO timers/polling/new classifiers
NO widening of family/state/source contracts
```

Work should implement only the frozen migration responsibility, commit/push it, and update the exact continuation pointer.

---

## 5. Production integration validation — required after migration

After source review of the migration passes, the User builds/tests locally at home.

The production validation should be **focused but representative**, because the causal and release-purity behavior campaigns are already closed.

Minimum acceptance:

```text
production target builds successfully
shipping DLL loads / Gothic 3 reaches gameplay without startup crash
no diagnostic-only dependency is required for collision correctness
representative equipped marker attack works
representative marker-dependent Hack or equivalent strong positive control works
representative raw8 marked/double-contact behavior works
representative raw55 marked/double-contact behavior works
representative unmarked/native fallback remains native
OFF/inactive authored gap remains non-damaging
ordinary weapon/source/combat churn shows no stuck or persistent collision state
no user-observed regression against EV-389 behavior-only baseline
```

A small number of deliberately strong positive/negative controls is preferable to replaying the entire historical matrix.

If a migration-specific failure appears, isolate the smallest factual integration route before changing accepted collision semantics.

---

## 6. Evidence boundary

Diagnostic runtime batches, if any become necessary again:

```text
freeze setup
-> publish unchanged evidence
-> POP-06 bounded retrieval
-> exact EV
-> promote changed reusable fact
-> archive processed evidence
-> knowledge-state validation PASS
```

Production behavior validation may remain observational where diagnostics are intentionally absent. Exact binary/source provenance plus a frozen test matrix and User observation are valid release evidence, as established by EV-389.

---

## 7. Current sequence

```text
EV-386–EV-388 diagnostic final candidate      CLOSED/PASS
EV-389 behavior-only release-purity            CLOSED/PASS
CURRENT                                         bounded production collision migration
NEXT                                            production integration validation
THEN                                            close collision production migration
LATER                                           Raise + Speed + Config under DESIGN.md / ADR-0004

AttackContinuationProtection remains separate unless deliberately reopened.
```
