# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — documentation / knowledge-system audit

Repository:

```text
tcholti/Gothic3_Animation_Behaviors
```

Branch:

```text
docs/collision-source-evidence
```

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap, then read this file. Do not reconstruct the project from old chat history and do not scan the whole repository.

---

## Accepted technical state

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
Literal historical EV-131 confirmation     PASS — EV-214
Final behavior-only architecture smoke     PASS — EV-215

NEW ARCHITECTURE VERIFICATION              COMPLETE
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

Independent marker semantics remain protected: exact current-motion ownership; Normal/Quick/full-Whirl eligibility; RIGHT/LEFT/BOTH/OFF; authored occurrence budgets; duplicate/replay suppression; repeated-contact `ClearTriggeredList()` rearm; exact-set switching; physical marker-window retirement; OFF intra-Hit gap; Quick/full-Whirl StatePosition suppression; current Fist research behavior; late/dead rejection; unsupported/unmarked native fallback. C1 terminal repair remains unchanged and native cleanup gets first opportunity.

Do not reopen the completed architecture gates or invent another broad diagnostic/runtime matrix absent a concrete contradiction.

---

## EV-214 — literal historical occurrence-budget defect closed

Preserved historical exact 2H Normal motion:

```text
Hero_Stand_None_2H_P0_Attack_Hit_N_Fwd_00_%_00_P1_90_R.xmot
```

Authored schedule proved live under CORE:

```text
RIGHT frame 4
OFF   frame 10
RIGHT frame 15
```

Decisive sequence:

```text
generation 11
→ first RIGHT accepted 0 -> 1
→ interrupted before OFF / later RIGHT
→ exact physical source naturally cleaned 7 -> 5

next actual _AI_Attack of same exact motion = generation 18
→ first RIGHT accepted fresh 0 -> 1
→ OFF accepted within same generation
→ later genuine RIGHT accepted 1 -> 2
```

The same run preserved special Dual Normal exact-set fixtures:

```text
P0: BOTH -> LEFT  -> OFF -> BOTH
P1: BOTH -> RIGHT -> OFF -> BOTH
```

Authoritative raw:

```text
research/raw/2026-09-01_gate4_pc_2h_dual_interruption_restart_mixed_combat.log
raw-evidence commit: 1040a16926bb4b8a450c7548636dd886ddf17aaf
raw blob: 3c2ea936a90114d47bedc39a67345161ea4d14cb
EV-214 documentation commit: 551980fcb102aae864a49404630166246d958001
```

EV-213 remains valid and unchanged; EV-214 supplies the later-requested literal historical fixture confirmation.

---

## EV-215 — final behavior-only architecture verification

Validated Gate-4 release-purity product:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

Correct build location:

```text
build/prototypes/Script_FrameCollisionTest/Release/Script_FrameCollisionBehaviorTest.dll
```

The diagnostic twin was removed from the live scripts directory and the behavior-only DLL was deployed alone with exact built/live identity. Gothic 3 reached main menu and exited normally.

The final in-game smoke then exercised the requested restored-fixture/interruption/restart coverage repeatedly across different weapon types and marked/unmarked animations. The User explicitly reported marked 2H, Staff and Dual Wield fixtures plus bows, crossbows and magic, and reported that everything worked as expected with no visible stuck collision, crash or obvious regression.

This is deliberately functional/release-purity evidence only. Internal C1-generation and marker bookkeeping proof remains the CORE diagnostic evidence EV-213/EV-214.

Global evidence continuation:

```text
docs/EVIDENCE_LEDGER_STEP_E.md — EV-215 onward
EV-215 evidence commit: f0ada39b6849499aa0012611348f6ead68dbf226
```

---

## Current responsibility — documentation / knowledge-system audit

Use:

```text
docs/KNOWLEDGE_MAINTENANCE.md
docs/KNOWLEDGE_REGISTRY.md
```

Audit current authorities for:

- contradictions between current-state documents;
- duplicate maintained facts or repeated policy text;
- stale wording that still describes closed gates as pending;
- read-first / bootstrap growth and unnecessary mandatory reads;
- usefulness and routing quality of indexes;
- evidence-ledger continuity and whether the current split remains useful;
- raw-vs-archive boundaries;
- superseded documents that should be archived or clearly demoted;
- speculative or redundant cross-routes that increase context cost without helping retrieval.

First produce concise findings and a proposed cleanup plan. Do not automatically merge evidence ledgers, delete/archive authorities, or rewrite provenance. Preserve global EV IDs and historical evidence. Perform destructive consolidation/archive/delete only when justified by the audit.

---

## Local synchronization / ownership

The User completed the final local behavior-only runtime window before the EV-215 documentation write. Assistant documentation has now advanced the remote branch.

Before the next local git/build/deploy/runtime window, synchronize per POP-01. Once the User owns a new local test or implementation window, the assistant must not concurrently write the branch.

Known unrelated local file to leave completely untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## After audit — stable promotion / branch cleanup

Normal branch model remains:

```text
main
= stable integration + reusable stable knowledge

docs/collision-source-evidence
= active development/research
```

`main` is stale and must be updated deliberately only after the documentation audit / justified cleanup.

Temporary branch:

```text
temp/second-pass-rewrite-publish
```

Last known comparison on 2026-09-01:

```text
status: diverged
active branch ahead by: 35 commits
temp branch ahead by: 10 commits
merge base: 0aa6d19a6815934a3158715070320020bac64292
```

Do not delete it blindly. Inspect temp-only commits/content, preserve anything unique, define the stable promotion set, update/verify protected `main`, then delete the temp branch only if safe.

---

## Forward order

```text
documentation + knowledge-system audit — NEXT
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
