# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Current validation authority: `docs/COLLISION_TEST_PLAN.md`  
Current lifecycle authority: `docs/COLLISION_LIFECYCLE_PLAN.md`  
Gate 4 contract/result: `docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`  
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

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
literal historical EV-131 regression       CLOSED/PASS — EV-214
final behavior-only architecture smoke     CLOSED/PASS — EV-215

NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

Accepted Gate 4 rule:

> **The monotonic C1 generation is the durable marker occurrence/dedupe execution identity. Marker-local guesses based on source/motion/action/phase/state-time or controlled-callback rollback are no longer execution-boundary authority. Authored marker semantics remain independent.**

Preserve independently:

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

Native cleanup gets first opportunity. Retained C1-R1 qualifications remain evidence limits, not open gates:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / physical-repair case claimed
```

Gate 4 implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

Validated behavior-only product from EV-215:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

Do not invent another broad architecture-verification matrix absent a concrete contradiction.

---

## Repository Knowledge / Evidence Cleanup — COMPLETE

The documentation/knowledge audit, authority-repair pass and processed-evidence location cleanup are complete.

```text
active authorities no longer describe closed verification as pending
Step D owns EV-206–EV-214
Step E begins at EV-215
19 processed collision logs moved research/raw/ → research/archive/
19/19 archived logs retain their exact original Git blob SHA
Step-D provenance points to research/archive/
research/raw/ contains only Keep.txt
```

Evidence migration commits:

```text
c366c5147d5128b7e53e47b57731b498a0ac1602
a3eb460d323a8590444d950b3a60a8e0db5c7083
87e3ffc24ca0bf604ffb6314248e4ab0b4d3ce39
```

Known unrelated local file remains outside this cleanup and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Temporary Branch Inspection — COMPLETE

Temporary branch:

```text
temp/second-pass-rewrite-publish
```

It has 10 temp-only staging commits after merge base:

```text
0aa6d19a6815934a3158715070320020bac64292
```

Decisive preservation fact:

```text
temp head:
515d73fab14e7a66d94f3f19b0843072bbf70ef3

temp head tree:
f303ba47624fc904dd4bc3f64aadfab43cd536d6

accepted active rewrite:
4eeb701725e8b77d8850116d408155653ff4ad36

accepted rewrite tree:
f303ba47624fc904dd4bc3f64aadfab43cd536d6
```

Therefore temp contains no unique final file content needing rescue. Its only unique value is intermediate staging chronology. Do not merge it into the active branch.

---

## Stable `main` Promotion — VERIFIED

Old main head:

```text
76703d362a0aef0a749fc30626eb2b75a3d5fec3
```

Its only main-only change was the superseded Collaboration Rules v0.1. The active branch already contains the evolved project authority v1.8.

Protected `main` was promoted without force through history-preserving merge commit:

```text
84a00d206bb6b939dccce06d7d4fe680c10d5cc3
```

Promotion commit facts:

```text
parent 1 = 76703d362a0aef0a749fc30626eb2b75a3d5fec3  old main
parent 2 = 50cf676046e305e2646c5ed47a4188a5ba863dc5  cleaned active checkpoint
tree     = c19473642354f207914ca6d0ada03dde0ffbfcf6  exact active tree
```

Post-promotion comparison:

```text
main ahead of active checkpoint: 2 commits
main behind active checkpoint: 0
file differences: 0
```

Main remains protected. Its active ruleset forbids deletion and non-fast-forward updates.

---

## Current Technical Responsibility — Retire Proven-Redundant Temp Branch

`temp/second-pass-rewrite-publish` is now safe to delete because:

```text
its final staging tree is already preserved exactly by 4eeb701...
main promotion is verified
both old-main and active histories are reachable from main
```

The current connector cannot delete a branch ref. The next repository operation is therefore a single explicit User/local deletion of only:

```text
temp/second-pass-rewrite-publish
```

After deletion, verify that the intended normal branch model is restored:

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research
```

Do not delete either of those two branches.

---

## Next Engineering Responsibility — Equipped-Melee Marker Expansion Planning

After temp retirement is confirmed, return to the active branch and plan the next marker expansion. Do not begin implementation before one exact mechanism/family responsibility is frozen.

Known deliberate review item from EV-211:

```text
Dual P1 Quick tested asset authored marker = RIGHT
older native-source evidence for tested Dual P1 Quick = LEFT
```

Treat that as an authoring/source-map review question for expansion planning, not as evidence that closed lifecycle or Gate-4 behavior is wrong.

Keep these later responsibilities separate:

```text
Fist source-adapter investigation
AttackContinuationProtection
New Balance/Jackydima compatibility gate
Raise + speed + config migration/redesign
```

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
