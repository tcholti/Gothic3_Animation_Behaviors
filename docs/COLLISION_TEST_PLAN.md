# Collision Validation Plan

**Status:** Collision validation CLOSED/PASS through production integration  
**Updated:** 2026-09-27

## Purpose

Define the accepted collision-validation boundary after the completed research, diagnostic, behavior-only, migration, and production-integration campaigns.

This file now owns the **closed validation posture** and the conditions under which collision testing should be reopened. It does not own implementation architecture, settled collision semantics, or historical proof.

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
- Production migration is not a redesign opportunity. Preserve the accepted behavior contract unless new contradictory evidence appears.
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
production collision integration               CLOSED/PASS EV-390
```

No full historical campaign should be repeated absent contradictory evidence.

---

## 3. Accepted final collision candidate and pre-migration proof

Reviewed behavior source:

`1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`

Final research binaries rebuilt from that shared source:

```text
Script_FrameCollisionBehaviorTest SHA256
D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78

Script_FrameCollisionTest SHA256
AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
```

The diagnostic twin completed final standalone and New Balance gates through EV-388.

EV-389 validated the diagnostics-free behavior twin itself through deliberately stronger-than-native controls:

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

Therefore the diagnostics-free collision behavior was accepted as release-pure before migration.

---

## 4. Production migration and integration closure

Production migration implementation:

`9da92dc559d8897a675d575f8d88b3631470ed7d`

Independent source review established:

```text
21/21 migrated behavior files match prototype Git blobs
production bootstrap adapted only as authorized
production CMake includes the complete collision behavior core
AttackRaise / AttackSpeed / SharedConfig excluded from production build
collision diagnostic implementations/macros excluded
prototype twins unchanged
```

EV-390 then validated the final production product:

```text
Script_G3AnimationBehaviors.dll builds successfully
built/live SHA256 exact match:
12FA5819FEEB5033B2D747A9B57CA1591E588EAAC0BAC9CC386307B77C367A55
sole live G3AB/collision product = PASS
full gameplay load = PASS
```

Focused marker-dependent production controls:

```text
2H double attacks / three markers = works
1H1H triple attacks / four markers = works
human Fist double / two markers = works
Sabretooth raw8 double / two markers = works
Troll raw55 double / two markers = works
```

These attacks deliberately request additional authored collision opportunities that native Gothic attack timing cannot provide by itself. Their success in the final production DLL is strong causal evidence that the migrated production behavior is active, not merely loadable.

EV-390 is intentionally focused: exact migration parity plus the prior EV-386–EV-389 campaigns protect the broad accepted behavior surface, while EV-390 proves final-product integration.

Disposition:

```text
PRODUCTION COLLISION MIGRATION = COMPLETE
PRODUCTION COLLISION INTEGRATION = CLOSED/PASS EV-390
COLLISION SUBSYSTEM = STABLE FOUNDATION FOR NEXT FEATURE WORK
```

---

## 5. Reopen conditions

Collision validation should be reopened only when one of these occurs:

```text
new runtime behavior directly contradicts an accepted collision invariant
future feature integration appears to regress collision behavior
new supported source/family/marker semantics are deliberately added
engine/mod compatibility scope materially expands beyond the accepted evidence
production build architecture changes in a way that can alter collision execution
```

A future assembled regression after Speed and Raise is **not** a reopening of collision research. It is a safety check that later modules did not regress the already-accepted collision subsystem.

If a migration/integration-specific failure appears later, isolate the smallest factual route before changing accepted collision semantics.

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

Production behavior validation may remain observational where diagnostics are intentionally absent. Exact binary/source provenance plus a frozen test matrix and User observation are valid release evidence, as established by EV-389 and EV-390.

---

## 7. Current sequence

```text
EV-386–EV-388 diagnostic final candidate      CLOSED/PASS
EV-389 behavior-only release-purity            CLOSED/PASS
EV-390 production integration                  CLOSED/PASS
COLLISION                                      CLOSED / stable foundation
CURRENT PROJECT PHASE                          shared Speed+Raise config foundation
NEXT                                           Speed v2 only until closed
LATER                                          Raise only after Speed closes
FINAL BEFORE MAIN                              assembled collision + Speed + Raise regression

AttackContinuationProtection remains separate unless deliberately reopened.
```
