# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — Gate 4 CLOSED/PASS; equipped-melee marker expansion planning NEXT

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

## Closed foundations — do not reopen

```text
C1-R1 lifecycle safety                CLOSED — EV-206–EV-207
Gate 1 source/build separation        CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency    CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke            CLOSED/PASS — EV-212
Gate 4 marker-bookkeeping simplification CLOSED/PASS — EV-213
```

Gate 4 implementation commit:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Gate 4 contract/closure authority:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
docs/EVIDENCE_LEDGER_STEP_D.md — EV-213
```

Accepted marker execution model:

```text
valid C1 generation
= durable marker occurrence/dedupe execution identity
```

Different generation -> fresh marker budget/dedupe state.

Same generation -> do not silently reset because source, motion, action, phase or state-time changed.

Natural SetCollisionGroup cleanup still retires the exact physical marker-owned source bit only; it is not occurrence-execution retirement.

Preserve independent marker semantics:

```text
exact current-motion ownership
Normal / Quick / full-Whirl eligibility
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
exact-set source switching
marker-owned active source/window mask
OFF intra-Hit gap
Quick/full-Whirl StatePosition suppression
current Fist/PhysicalFist research behavior
late/dead/unsupported rejection
unmarked/unsupported native fallback
```

C1 terminal repair remains unchanged and native cleanup still gets first opportunity.

---

## Gate 4 validated products

CORE diagnostic:

```text
Script_FrameCollisionTest.dll
Length: 416768
SHA256: E69FB2602E3599A0905B63F2064B732D57CA9E1817CDED2BD7AB6C01C08392E9
```

Behavior-only follow-up:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

The behavior-only target was deployed alone, reached main menu, exited normally, and passed user-observed Staff/1H/2H combat plus repeated destructive bad-skip smoke.

Final no-leak precision:

```text
current marked 2H Normal P0 asset now has one authored RIGHT
→ cannot literally recreate old EV-131 two-RIGHT Normal fixture

same property proved with P0 full Whirl:
generation 34: first RIGHT accepted 0 -> 1, execution ends before OFF/second RIGHT
generation 40: same exact motion, fresh 0 -> 1, later genuine RIGHT 1 -> 2
```

Whole final diagnostic log contained zero no-generation/generation-inconsistency/invariant/divergence/unresolved signal and unloaded cleanly.

---

## Exact next responsibility — equipped-melee marker expansion planning

This is a **Normal Chat design/planning responsibility first**, not a source-implementation task yet.

Do the smallest retrieval necessary to answer:

```text
1. Which equipped-melee attack families/actions are currently marker-supported?
2. Which additional equipped-melee families are the next realistic expansion candidates?
3. What exact physical source does each candidate require?
4. Does each candidate need an existing callback adapter or a genuinely new behavior mechanism?
5. Which single candidate should become the first bounded expansion?
```

Explicitly review the known Dual P1 Quick discrepancy before expanding around it:

```text
tested authored asset: G3AB_COL_RIGHT
older tested native-source evidence: LEFT
```

Do not assume either side is automatically wrong. Determine whether this is authoring/fixture choice, source-map evidence, or intended semantic difference.

Then freeze **one** bounded expansion responsibility before any Work implementation.

---

## Keep separate

Do not combine the next equipped-melee planning step with:

```text
Fist source-adapter/generalization
AttackContinuationProtection / held-Use2 prevention
C1 repair redesign
Raise
speed/config redesign
compatibility work
production migration
target acquisition
climbing
```

---

## Local/runtime handoff note

The last local runtime step redeployed the validated Gate 4 diagnostic `Script_FrameCollisionTest.dll` alone in Gothic 3's live `scripts` directory for the final regression. The behavior-only twin was removed before that run.

Before any later runtime test, preserve the one-product-at-a-time rule and deploy whichever product the frozen test actually requires.

The User's local Git checkout contains the published raw evidence through:

```text
9483992bbe9513277382147ac20d0a27bd231a96
```

Assistant-side documentation maintenance follows that evidence commit. Before the next local source/build/commit window, synchronize the branch per POP-01 after receiving the new documentation commit SHA.

Known unrelated local file to leave untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Authorities

```text
SESSION_ENTRYPOINT.md                          current front door
BETWEEN_CHATS.md                               this exact continuation
COLLISION_TEST_PLAN.md                         staged validation / next gate
MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md  closed Gate 4 contract
EVIDENCE_LEDGER_STEP_D.md EV-213               Gate 4 evidence closure
EVIDENCE_INDEX.md                              evidence routing
ANIMATION_INDEX.md / ANIMATION_CATALOG.md      family/asset routing
COLLISION_LIFECYCLE_PLAN.md                    closed lifecycle architecture
SECOND_PASS_REWRITE_CONTRACT.md                modular architecture/invariants
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md          release-purity rule
PROJECT_OPERATING_PROCEDURES.md                local Git/build/deploy/test workflow
WORK_IMPLEMENTATION_PROTOCOL.md                bounded Work rules
```

---

## Forward order

```text
equipped-melee marker expansion planning — NEXT
→ freeze first bounded equipped-melee expansion
→ implement/review/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature research New Balance/Jackydima compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
