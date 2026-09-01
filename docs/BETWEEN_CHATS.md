# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — documentation cleanup checkpoint

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

## Accepted boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
Literal historical EV-131 regression       CLOSED/PASS — EV-214
Final behavior-only architecture smoke     CLOSED/PASS — EV-215

NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

Accepted marker execution identity:

```text
C1 monotonic generation
= durable marker occurrence/dedupe execution identity
```

Independent marker semantics and the closed C1 terminal-repair contract remain unchanged. Exact architecture/evidence belongs in:

```text
MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
COLLISION_LIFECYCLE_PLAN.md
COLLISION_TEST_PLAN.md
EVIDENCE_INDEX.md
EVIDENCE_LEDGER_STEP_D.md — EV-206–EV-214
EVIDENCE_LEDGER_STEP_E.md — EV-215 onward
```

Do not reopen a completed architecture gate or invent another broad diagnostic/runtime matrix absent a concrete contradiction.

---

## Documentation audit result / current responsibility

The first approved audit cleanup pass is **non-destructive authority repair only**.

Completed in this pass:

```text
SESSION_ENTRYPOINT.md
COLLISION_TEST_PLAN.md
KNOWLEDGE_REGISTRY.md
EVIDENCE_INDEX.md
SECOND_PASS_REWRITE_CONTRACT.md
COLLISION_LIFECYCLE_PLAN.md
DESIGN.md
COLLISION_LOGGER_PLAN.md
RESEARCH_MAP.md
README.md
EVIDENCE_LEDGER_STEP_D.md range metadata only
BETWEEN_CHATS.md
```

Result:

```text
- stale pending-verification language removed from active authorities
- EV-215 / EVIDENCE_LEDGER_STEP_E routing added
- Step D explicitly closes at EV-214
- completed second-pass contract retained as reference/provenance rather than deleted
- DESIGN/lifecycle/logger authorities aligned with C1-generation marker execution identity
- RESEARCH_MAP restored to history-only routing
- README/entrypoint bootstrap routing reduced and clarified
- evidence-ledger split retained as useful storage/retrieval structure
- no source code changed
- no evidence claim was renumbered or deleted
- no raw evidence moved or deleted
```

Next responsibility after review/synchronization is the **separate processed-evidence raw→archive migration decision/transaction**. Do not mix that with this authority-repair pass.

---

## Raw/archive boundary — deliberately deferred

Several already-processed artifacts still live under `research/raw/` and are cited there by canonical evidence.

Do not move them piecemeal.

If the migration is performed, it must be one deliberate transaction:

```text
identify exact processed raw set
→ verify current canonical provenance references
→ move bytes unchanged to research/archive/
→ update every affected canonical path/reference in the same transaction
→ verify hashes/provenance
→ commit/publish the complete migration
```

No historical artifact should be renamed merely for cosmetic normalization.

---

## Local synchronization / branch ownership

Assistant documentation writes have advanced the remote branch beyond the User's last synchronized local HEAD.

Before any new local Git/build/deploy/runtime window:

```text
User synchronizes local branch
→ verify HEAD/status
→ only then begin the next local window
```

Once the User owns a local implementation/test window, the assistant must not concurrently write this branch.

Known unrelated local file to leave completely untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Stable promotion / temporary branch — later

Normal branch model remains:

```text
main
= stable integration + reusable stable knowledge

docs/collision-source-evidence
= active development/research
```

`main` must be updated deliberately only after this cleanup checkpoint and any justified evidence-location cleanup have been reviewed.

Temporary branch:

```text
temp/second-pass-rewrite-publish
```

Do not delete it blindly. Its unique history/content must be inspected first; preserve anything unique that still matters, then define the stable promotion set, update/verify protected `main`, and retire the temporary branch only if safe.

Any previously recorded ahead/behind counts are historical snapshots and must be re-queried when this branch-cleanup responsibility actually begins.

---

## Forward order

```text
review/synchronize completed authority-repair pass — NEXT
→ separate justified raw→archive provenance migration
→ inspect temp-only branch history/content
→ define stable promotion checkpoint
→ update protected main
→ verify main
→ retire temp branch if safe
→ normal two-branch model restored
→ equipped-melee marker expansion planning
→ freeze/implement/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature New Balance/Jackydima compatibility gate
→ Raise + speed + config redesign/migration
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
