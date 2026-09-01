# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — final behavior-only architecture smoke

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

---

## EV-214 — literal historical regression is now closed

The preserved historical 2H Normal fixture was re-exported/reinstalled and tested with the current Gate-4 CORE diagnostic.

Exact motion:

```text
Hero_Stand_None_2H_P0_Attack_Hit_N_Fwd_00_%_00_P1_90_R.xmot
```

Live fixture proof:

```text
Actor: PC_Hero
Family: NORMAL
ContainsReservedSourceMarker: 1
AuthoredRIGHTCount: 2
FirstRIGHTMarkerFrame: 4
AuthoredOFFCount: 1
FirstOFFMarkerFrame: 10
```

Decisive EV-131-class sequence:

```text
generation 11
→ first RIGHT accepted 0 -> 1
→ ExecutionBudgetReset: 1
→ interrupted before OFF / later RIGHT
→ exact physical source naturally cleaned 7 -> 5

next actual _AI_Attack of same exact motion = generation 18
→ first RIGHT accepted fresh 0 -> 1
→ ExecutionBudgetReset: 1
→ OFF accepted within same generation
→ later genuine RIGHT accepted 1 -> 2
→ replay protections remain intact
```

Intervening reaction/ambient generations did not carry marker occurrence state into the next attack execution.

The same mixed run also exercised special Dual Normal fixtures:

```text
P0: BOTH -> LEFT  -> OFF -> BOTH
P1: BOTH -> RIGHT -> OFF -> BOTH
```

These preserved exact-set semantics: BOTH-to-single retired only the opposite physical source bit, OFF closed the exact owned window, and later BOTH reopened/rearmed both sources without resetting the same-generation execution budget.

Whole-log exact searches found zero:

```text
REJECTED_NO_C1_GENERATION
REJECTED_C1_GENERATION_INCONSISTENCY
INVARIANT
DIVERGED
UNRESOLVED
```

The diagnostic unloaded cleanly.

Authoritative raw evidence:

```text
research/raw/2026-09-01_gate4_pc_2h_dual_interruption_restart_mixed_combat.log
raw-evidence commit: 1040a16926bb4b8a450c7548636dd886ddf17aaf
raw blob: 3c2ea936a90114d47bedc39a67345161ea4d14cb
EV-214 documentation commit: 551980fcb102aae864a49404630166246d958001
```

EV-213 remains valid and unchanged. Its Whirl sequence was equivalent proof for the asset installed at that time; EV-214 is the later-requested literal historical fixture confirmation.

**Do not reopen Gate 4 or invent another diagnostic matrix unless a concrete contradiction appears.**

---

## Only remaining architecture-verification step — behavior-only restored-fixture smoke

This step is required before declaring the whole new collision architecture verified.

Validated Gate-4 behavior-only product:

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
→ main-menu load / normal exit
→ load test save
→ restored two-contact 2H Normal behaves correctly
→ several interruption/restart attempts
→ ordinary Staff / 1H / 2H combat afterwards
→ no visible stuck collision, crash or obvious regression
→ normal exit
```

Because the behavior-only product intentionally has no diagnostics, this result is functional/release-purity evidence only. Internal generation/marker proof remains EV-213/EV-214 CORE diagnostic evidence.

If this smoke passes:

```text
NEW ARCHITECTURE VERIFICATION = COMPLETE
```

Do not add another broad architecture matrix after it absent a concrete contradiction.

---

## Local synchronization / ownership

The User's last pushed local head before the documentation updates was:

```text
1040a16926bb4b8a450c7548636dd886ddf17aaf
```

Assistant documentation advanced the remote branch after that point. Before the next local deploy/test window, synchronize first per POP-01. Once the User owns the local test window, the assistant must not write this branch again until that local work is complete/pushed.

Known unrelated local file to leave completely untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## After architecture verification — documentation/knowledge-system audit

Only after the final behavior-only smoke passes, use `KNOWLEDGE_MAINTENANCE.md` and `KNOWLEDGE_REGISTRY.md` to audit current authorities for contradictions, duplicate maintained facts, stale current-state wording, read-first/bootstrap growth, index usefulness, evidence-ledger continuity/splitting, raw-vs-archive boundaries, superseded documents and unnecessary cross-routes.

Do not automatically merge evidence ledgers. Preserve global EV IDs and provenance. First produce concise findings + proposed cleanup; perform destructive consolidation/archive/delete only when justified.

---

## After audit — stable promotion / branch cleanup

Normal branch model remains:

```text
main
= stable integration + reusable stable knowledge

docs/collision-source-evidence
= active development/research
```

`main` is stale and must be updated deliberately only after architecture verification + documentation audit.

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
final behavior-only restored-fixture + ordinary-melee smoke — NEXT
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
