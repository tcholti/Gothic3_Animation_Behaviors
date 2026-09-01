# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Current validation authority: `docs/COLLISION_TEST_PLAN.md`  
Current lifecycle authority: `docs/COLLISION_LIFECYCLE_PLAN.md`  
Gate 4 result/contract: `docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`  
Completed second-pass rewrite reference: `docs/SECOND_PASS_REWRITE_CONTRACT.md`  
Release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`  
Knowledge-maintenance/audit rules: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Branch/convention authority: `docs/PROJECT_PIPELINE.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` → `docs/EVIDENCE_LEDGER*.md`  
Latest evidence continuation: `docs/EVIDENCE_LEDGER_STEP_E.md`  
Local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

```text
shared behavior architecture
→ diagnostics-free RELEASE/behavior-only build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Never normally load behavior-only and diagnostic twins together.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact current responsibility and latest accepted boundary.
3. Treat the release-purity rule above as standing architecture.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, artifact naming, build labels, branch meanings or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

After bootstrap, report briefly:

```text
current technical responsibility
closed architecture/evidence boundary relevant to that responsibility
exact immediate next step
what remains deliberately deferred
```

---

## Closed Collision Architecture — Do Not Reopen Without Contradicting Evidence

### Lifecycle safety

C1-R1 is closed through EV-206–EV-207.

```text
successful exact-source Item_Attack request
→ exact source obligation

successful transition away from Item_Attack
→ obligation fulfilled

post-native-AISetState finalization
+ exact obligation still outstanding
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList
→ verify exact group 5
```

Native cleanup always gets first opportunity.

Retained qualifications:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / physical-repair case claimed
```

### Second-pass architecture and marker bookkeeping

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

Accepted Gate 4 rule:

> **The monotonic C1 generation is the durable marker occurrence/dedupe execution identity. Marker-local guesses based on source/motion/action/phase/state-time or controlled-callback rollback are no longer execution-boundary authority. Authored marker semantics remain independent.**

Preserve unchanged in meaning:

```text
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
supported-family ownership
physical marker-window/source-bit retirement
Quick/full-Whirl StatePosition behavior
late/dead/unsupported marker rejection
unmarked/unsupported native fallback
closed C1 terminal-repair ordering and exact-source contract
```

Gate 4 implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Validated behavior-only product used for EV-215:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

Do not invent another broad architecture-verification matrix absent a concrete contradiction.

---

## Completed Repository Knowledge / Evidence Cleanup

The documentation/knowledge audit, authority-repair pass and processed-evidence location cleanup are complete.

Accepted cleanup result:

```text
active authorities no longer describe closed architecture verification as pending
EV-215 / EVIDENCE_LEDGER_STEP_E routing is current
EVIDENCE_LEDGER_STEP_D explicitly owns EV-206–EV-214
19 already-processed collision logs moved from research/raw/ to research/archive/
all 19 archived logs retain their exact original Git blob SHA
EVIDENCE_LEDGER_STEP_D provenance paths now point to research/archive/
research/raw/ contains only Keep.txt
```

Evidence migration commits:

```text
c366c5147d5128b7e53e47b57731b498a0ac1602
a3eb460d323a8590444d950b3a60a8e0db5c7083
87e3ffc24ca0bf604ffb6314248e4ab0b4d3ce39
```

The unrelated local untracked file remains outside this migration and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Temporary Branch Inspection — COMPLETE

Temporary branch:

```text
temp/second-pass-rewrite-publish
```

Current comparison established:

```text
merge base with active branch: 0aa6d19a6815934a3158715070320020bac64292
temp-only commits: 10
active branch ahead of temp: 60 commits at inspection time
```

The 10 temp-only commits are staging commits for the frozen second-pass rewrite: marker module, lifecycle guard, EngineBridge split, compact/deep diagnostics, RuntimeClock, source operations and final staging assembly.

Decisive preservation fact:

```text
temp head:
515d73fab14e7a66d94f3f19b0843072bbf70ef3

temp head tree:
f303ba47624fc904dd4bc3f64aadfab43cd536d6

accepted active rewrite commit:
4eeb701725e8b77d8850116d408155653ff4ad36

active rewrite tree:
f303ba47624fc904dd4bc3f64aadfab43cd536d6
```

Therefore the temp branch contains **no unique final file content that must be preserved**. Its only unique value is intermediate staging chronology, already superseded by the single accepted implementation commit plus Git history. Do not merge temp into the active branch.

Do not delete temp until stable `main` promotion is verified.

---

## Current Technical Responsibility — Promote Cleaned Verified Checkpoint to `main`

Current main comparison at inspection time:

```text
active branch ahead of main: 693 commits
main ahead of merge base: 1 commit
main-only commit: 76703d362a0aef0a749fc30626eb2b75a3d5fec3
message: Add adaptive collaboration and usage rules
```

That main-only commit contains old `COLLABORATION_RULES.md` v0.1. The active branch now contains the evolved project collaboration authority v1.8 and explicitly treats older Gothic collaboration rules as superseded where they conflict with the current project delta/CAM framework. No main-only content requires cherry-picking.

Main ruleset is active and protects against deletion and non-fast-forward updates. Stable promotion must therefore preserve history and remain fast-forward.

Preferred promotion shape:

```text
new main merge commit
  tree = exact cleaned active-branch tree
  parent 1 = old main head
  parent 2 = cleaned active head
```

This preserves the old main-only commit in ancestry without letting its obsolete v0.1 file overwrite the active v1.8 authority.

After promotion:

```text
verify main contains both histories
verify main tree equals promoted active tree
verify branch protection remains active
→ only then retire temp/second-pass-rewrite-publish
```

---

## After Stable Repository Checkpoint

Normal intended branch model:

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research
```

After main verification and safe temp retirement, resume engineering from the active branch.

---

## Forward Engineering Order

```text
equipped-melee marker expansion planning
→ freeze/implement/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature New Balance/Jackydima compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
