# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — exact EV-131 Normal fixture confirmation NEXT; audit/promotion checkpoint after PASS

Repository:

```text
tcholti/Gothic3_Animation_Behaviors
```

Branch:

```text
docs/collision-source-evidence
```

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap, then read this file.

Do not reconstruct the project from old chat history and do not scan the whole repository.

---

## Accepted technical state

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS by current evidence — EV-213
```

Gate 4 implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Gate 4 contract/evidence:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
docs/EVIDENCE_LEDGER_STEP_D.md — EV-213
```

Accepted execution model:

```text
valid C1 generation
= durable marker occurrence/dedupe execution identity
```

Independent marker semantics remain protected: exact current-motion ownership; Normal/Quick/full-Whirl eligibility; RIGHT/LEFT/BOTH/OFF; authored occurrence budgets; duplicate/replay suppression; repeated-contact `ClearTriggeredList()` rearm; exact-set switching; physical marker-window retirement; OFF intra-Hit gap; Quick/full-Whirl StatePosition suppression; current Fist research behavior; late/dead rejection; unsupported/unmarked native fallback.

C1 terminal repair remains unchanged and native cleanup gets first opportunity.

---

## User correction that changes the immediate next responsibility

The final Gate 4 diagnostic run used the currently installed 2H Normal P0 asset, which reported only one authored RIGHT. EV-213 therefore used a two-contact full-Whirl sequence to prove the same incomplete-execution/no-leak property.

The User has now clarified:

> The original two-marker/two-contact 2H Normal fixture used for the historical EV-131-style regression still exists in Blender. It was not exported/installed because the User misread the last test as Whirl-focused.

This does **not** invalidate EV-213. It creates one final literal historical-regression confidence test before the new architecture is treated as ready for audit/stable promotion.

Do not proceed to equipped-melee expansion yet.

---

## Exact next responsibility — restore and run the literal EV-131-class Normal regression

First retrieve only:

```text
EVIDENCE_LEDGER.md — EV-131, EV-132, EV-133
EVIDENCE_LEDGER_STEP_D.md — EV-213
MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
COLLISION_TEST_PLAN.md
PROJECT_PIPELINE.md only for test/log naming conventions
PROJECT_OPERATING_PROCEDURES.md for deploy/runtime/raw-artifact procedure
```

Then work one manageable step at a time.

### Fixture requirement

The User must export/install the preserved Blender two-contact 2H Normal fixture before the test.

Before attempting the interruption regression, use the CORE diagnostic marker-ownership record to verify that the live Normal fixture is actually the intended one. At minimum it must show:

```text
Actor: PC_Hero
Family: NORMAL
exact intended 2H Normal motion
ContainsReservedSourceMarker: 1
AuthoredRIGHTCount: 2
```

Do not rely on visual memory alone. If the fixture does not report two authored RIGHTs, stop and correct the fixture/deployment before testing.

### Historical regression requirement

Create an execution where:

```text
Normal execution A
→ first genuine RIGHT accepted
→ interrupt execution A before its later genuine RIGHT

immediate next attack execution B
→ same exact Normal motion as A
→ fresh C1 generation
→ first RIGHT accepted 0 -> 1 with ExecutionBudgetReset: 1
→ later genuine RIGHT accepted 1 -> 2
```

Also confirm replay suppression remains intact and whole-log searches show no:

```text
REJECTED_NO_C1_GENERATION
REJECTED_C1_GENERATION_INCONSISTENCY
INVARIANT
DIVERGED
UNRESOLVED
```

Require clean DLL shutdown.

Freeze the exact raw filename in the same message that requests the runtime test, following the established project pipeline. The User will copy the generated log unchanged to `research/raw/`, confirm it is there, then receive verify/add/commit/push commands.

### Result handling

If PASS:

```text
record the literal historical confirmation as the next global EV item
preserve EV-213's Whirl-equivalent proof as valid prior evidence
```

Because no source change is required, do not rebuild merely for the animation fixture. For maximum release-purity confidence, a small final behavior-only fixture smoke may follow using the already-validated Gate 4 behavior-only DLL; keep its claim functional/visual only.

If FAIL:

```text
Gate 4 reopens
STOP
interpret the contradiction before audit/promotion/new feature work
```

---

## Validated Gate 4 products / current live state

CORE diagnostic:

```text
Script_FrameCollisionTest.dll
Length: 416768
SHA256: E69FB2602E3599A0905B63F2064B732D57CA9E1817CDED2BD7AB6C01C08392E9
```

Behavior-only:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

At the end of the previous Chat, the validated **diagnostic** DLL was the sole live `Script_FrameCollision*.dll` in Gothic 3's `scripts` directory. The behavior-only twin had been removed.

The last diagnostic run exited cleanly.

The User's local repository was synchronized to:

```text
39229a3b8dcdc1b0c427cdf07e5e12dad5758206
```

Assistant-side handoff documentation advances remote beyond that commit. At the start of the next local write/build/test window, sync first per POP-01 after reading the updated handoff.

Known unrelated local file to leave untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Mandatory phase after the exact regression passes — documentation/knowledge-system audit

The User explicitly wants the project documentation audited before stable branch cleanup and before new equipped-melee expansion.

This is a deliberate stable-subsystem/promotion checkpoint. Use `KNOWLEDGE_MAINTENANCE.md` and `KNOWLEDGE_REGISTRY.md` as the audit rules.

Audit for:

```text
contradictions between authorities
unnecessary repetition / separately maintained copies of the same fact
stale current-state wording
closed contracts that should be compressed or archived
read-first/bootstrap growth
index routes that no longer narrow retrieval
EVIDENCE_LEDGER + STEP_B + STEP_C + STEP_D continuity and duplication
whether ledger splitting is useful structure or unnecessary fragmentation
processed research/raw artifacts that should move to archive
archive/current-state boundaries
obsolete cross-routes or duplicated future-use notes
```

Do not automatically merge the ledgers. Preserve the global EV sequence and provenance. First determine whether the split is solving file-size/retrieval needs or merely copying information.

The audit should produce a concise findings + proposed cleanup plan before destructive consolidation/deletion.

---

## Branch/stable-integration checkpoint after the audit

`PROJECT_PIPELINE.md` already defines the intended normal branch model:

```text
main
+ docs/collision-source-evidence
```

A third temporary branch currently exists:

```text
temp/second-pass-rewrite-publish
```

Do not delete it blindly. A comparison performed on 2026-09-01 found:

```text
status: diverged
active branch ahead by: 35 commits
temp branch ahead by: 10 commits
merge base: 0aa6d19a6815934a3158715070320020bac64292
```

After the documentation audit:

```text
inspect temp-only commits/content
→ preserve anything unique that still matters
→ decide the stable promotion set for the proven architecture + cleaned knowledge
→ integrate the stable checkpoint deliberately into protected main
→ verify main
→ delete temp/second-pass-rewrite-publish only when safe
→ retain main + docs/collision-source-evidence as the normal two-branch model
```

Do not change branch meanings just to reduce the count.

---

## Forward order

```text
restore two-contact 2H Normal fixture
→ literal EV-131 same-motion interruption/restart diagnostic regression
→ final evidence / optional compact behavior-only fixture smoke
→ documentation + knowledge-system audit
→ review findings and perform justified cleanup
→ stable integration to main
→ inspect/retire temp branch if safe
→ normal two-branch model restored
→ equipped-melee marker expansion planning
→ freeze/implement/test one expansion mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature compatibility gate
→ Raise + speed + config redesign/migration
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
