# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — finish new-architecture verification first

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

Accepted execution model:

```text
valid C1 generation
= durable marker occurrence/dedupe execution identity
```

Independent marker semantics remain protected: exact current-motion ownership; Normal/Quick/full-Whirl eligibility; RIGHT/LEFT/BOTH/OFF; authored occurrence budgets; duplicate/replay suppression; repeated-contact `ClearTriggeredList()` rearm; exact-set switching; physical marker-window retirement; OFF intra-Hit gap; Quick/full-Whirl StatePosition suppression; current Fist research behavior; late/dead rejection; unsupported/unmarked native fallback.

C1 terminal repair remains unchanged and native cleanup gets first opportunity.

---

## User correction and exact remaining architecture-validation work

The last Gate 4 diagnostic run used the currently installed 2H Normal P0 asset, which reported only one authored RIGHT. EV-213 therefore used a two-contact full-Whirl sequence to prove the equivalent incomplete-execution/no-leak property.

The User later clarified:

> The original two-marker/two-contact 2H Normal fixture used for the historical EV-131 regression still exists in Blender. It was not exported/installed because the final request was misread as Whirl-focused.

This does **not** invalidate EV-213. But the User explicitly wants the new architecture completely verified before documentation audit, branch cleanup or new feature work.

Therefore the next phase has exactly two final architecture-verification steps:

```text
1. literal EV-131-class diagnostic regression with restored two-marker Normal fixture
2. final behavior-only restored-fixture + ordinary-melee smoke
```

Do not proceed to audit or equipped-melee expansion until both pass.

---

## Step 1 — restore and run literal EV-131-class Normal regression

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

### Fixture verification

The User must export/install the preserved Blender two-contact 2H Normal fixture.

Before attempting the interruption regression, use the CORE diagnostic marker-ownership record to prove the live fixture is the intended one. At minimum:

```text
Actor: PC_Hero
Family: NORMAL
exact intended 2H Normal motion
ContainsReservedSourceMarker: 1
AuthoredRIGHTCount: 2
```

If the fixture does not report two authored RIGHTs, stop and correct fixture/deployment before testing.

### Historical regression

Create:

```text
Normal execution A
→ first genuine RIGHT accepted
→ interrupt execution A before later genuine RIGHT

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

Require clean diagnostic shutdown.

Freeze the exact raw filename in the same message that requests the runtime test, following `PROJECT_PIPELINE.md` and POP-05. The User will copy the generated log unchanged to `research/raw/`, confirm it is there, then receive verify/add/commit/push commands.

### Result handling

If PASS:

```text
record literal historical confirmation as next global EV item
preserve EV-213 Whirl-equivalent proof unchanged
proceed to Step 2 final behavior-only smoke
```

No source rebuild is required solely because the animation fixture changed.

If FAIL:

```text
Gate 4 reopens
STOP
interpret contradiction before audit, promotion or new feature work
```

---

## Step 2 — final behavior-only architecture smoke

This is **required** after the exact diagnostic regression passes. It is not merely optional promotion confidence.

Validated Gate 4 behavior-only product:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

Required sequence:

```text
remove diagnostic twin
→ deploy behavior-only DLL alone
→ verify exact built/live identity
→ main-menu load/normal exit
→ load test save
→ restored two-contact Normal behaves correctly
→ several interruption/restart attempts
→ ordinary Staff / 1H / 2H combat afterwards
→ no visible stuck collision, crash or obvious regression
→ normal exit
```

Because the behavior-only product intentionally has no diagnostics, keep this claim functional/visual only. Internal proof remains the CORE diagnostic evidence.

If both Step 1 and Step 2 pass:

```text
NEW ARCHITECTURE VERIFICATION = COMPLETE
```

Do not invent another broad architecture matrix unless a concrete contradiction appears.

---

## Validated products / current live state

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

At the end of the previous Chat, the validated **diagnostic** DLL was the sole live `Script_FrameCollision*.dll` in Gothic 3's `scripts` directory. The behavior-only twin had been removed. The last diagnostic run exited cleanly.

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

## Only after architecture verification is complete — documentation/knowledge-system audit

The User explicitly does **not** want audit/review work to displace unfinished architecture testing.

Only after Step 1 + Step 2 PASS, use `KNOWLEDGE_MAINTENANCE.md` and `KNOWLEDGE_REGISTRY.md` to audit:

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

The audit should produce concise findings + proposed cleanup before destructive consolidation/deletion.

---

## After the audit — update main and restore the normal two-branch model

`PROJECT_PIPELINE.md` already defines:

```text
main
= stable integration + reusable stable knowledge

docs/collision-source-evidence
= active development/research
```

`main` is currently stale. After architecture verification and the documentation audit/cleanup, promote the proven + reviewed checkpoint into `main`, then verify it.

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

Required sequence:

```text
architecture verification complete
→ documentation audit/cleanup complete
→ inspect temp-only commits/content
→ preserve anything unique that matters
→ define stable promotion set
→ integrate proven + cleaned checkpoint into protected main
→ verify main
→ delete temp branch only when safe
→ retain main + docs/collision-source-evidence
→ continue new work on docs/collision-source-evidence
```

Do not change branch meanings merely to reduce the branch count.

---

## Forward order

```text
restore two-contact 2H Normal fixture — NEXT
→ literal EV-131 same-motion interruption/restart diagnostic regression
→ final behavior-only restored-fixture + ordinary-melee smoke
→ NEW ARCHITECTURE VERIFICATION COMPLETE
→ documentation + knowledge-system audit
→ review findings and perform justified cleanup
→ inspect temp-only branch history
→ update protected main to proven + cleaned stable checkpoint
→ verify main
→ retire temp branch if safe
→ normal two-branch model restored
→ continue collision-source branch
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
