# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Validation authority: `docs/COLLISION_TEST_PLAN.md`  
Closed Gate 4 contract: `docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`  
Frozen architecture rewrite: `docs/SECOND_PASS_REWRITE_CONTRACT.md`  
Release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` / `docs/EVIDENCE_LEDGER_STEP_D.md`  
Local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Long-term model:

```text
shared behavior architecture
→ diagnostics-free RELEASE build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Never normally load release/behavior-only and diagnostic twins together.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact current responsibility and latest accepted boundary.
3. Treat the release-purity rule above as standing architecture.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, artifact naming, prototype/build labels or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

If the previous Chat ended unexpectedly, after bootstrap report briefly:

```text
current technical responsibility
Gate 1 / Gate 2 / Gate 3 / Gate 4 closure state
protected behavior/architecture invariants
exact next planning step
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle and modular marker architecture.**

Governing lifecycle invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision inside a live Hit. Terminal exact-source safety is a separate execution-level responsibility.

---

## Closed Foundations — Do Not Reopen

### C1-R1 lifecycle safety

Closed through EV-206–EV-207.

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

Explicit retained qualifications:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / physical-repair case claimed
```

### Closed rewrite / validation gates

```text
Gate 1 source/build separation       CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency   CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke           CLOSED/PASS — EV-212
Gate 4 marker-bookkeeping simplification CLOSED/PASS — EV-213
```

Second-pass architecture implementation:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Gate 4 implementation:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

---

## Gate 4 — CLOSED/PASS

Frozen authority and closure record:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
docs/EVIDENCE_LEDGER_STEP_D.md — EV-213
```

Accepted architecture:

> **The monotonic C1 generation is the durable marker-execution identity. Marker-local guesses based on source/motion/action/phase/state-time are no longer execution-boundary authority. Authored marker semantics remain independent.**

Preserve:

```text
exact current-motion ownership
Normal / Quick / full-Whirl eligibility
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
marker-owned current source/window mask
exact-set source switching
natural retirement of exact physical source bits
OFF as an intra-Hit inactive gap
Quick/full-Whirl StatePosition suppression
current Fist/PhysicalFist research behavior
late/dead/unsupported marker rejection
unmarked/unsupported native fallback
valid-motion-only marker caching
```

Gate 4 validation established same-generation `RIGHT -> OFF -> RIGHT`, fresh budgets across incomplete prior executions, exact physical-bit retirement, dead/late rejection and unchanged C1 terminal repair.

Authoritative Gate 4 CORE diagnostic identity:

```text
Script_FrameCollisionTest.dll
Length: 416768
SHA256: E69FB2602E3599A0905B63F2064B732D57CA9E1817CDED2BD7AB6C01C08392E9
```

Authoritative Gate 4 behavior-only follow-up identity:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

The behavior-only DLL was deployed alone, reached main menu, exited normally and then passed user-observed Staff/1H/2H combat plus repeated destructive bad-skip smoke without visible stuck collision, crash or regression.

Precision qualification from the final Gate 4 regression: the current marked 2H Normal P0 asset contains only one authored RIGHT, so it cannot literally reproduce EV-131's old two-RIGHT Normal fixture. The equivalent incomplete-execution/no-leak property was directly proven with the still-two-contact P0 full Whirl: generation 34 consumed only first RIGHT; later generation 40 on the exact same motion started with a fresh budget and accepted both genuine RIGHTs. EV-213 owns the exact claim.

---

## Current Technical Responsibility — Equipped-Melee Marker Expansion Planning

Gate 4 is finished. Do not begin another Gate 4 test matrix.

The next responsibility is **Normal Chat design/planning for equipped-melee marker expansion**, one bounded mechanism/family at a time.

First planning pass:

```text
1. classify current equipped-melee marker coverage versus unsupported candidate attack families;
2. retrieve only the source/animation evidence needed for those candidates;
3. explicitly review the known Dual P1 Quick discrepancy:
   tested authored marker = G3AB_COL_RIGHT
   older native-source evidence = LEFT
4. decide whether that discrepancy is authoring, fixture, source-map or intended-semantic work before expansion;
5. choose and freeze the first bounded expansion responsibility;
6. only then launch bounded Work implementation.
```

Do not mix this planning step with:

```text
Fist source-adapter/generalization
AttackContinuationProtection / held-Use2 prevention
C1 redesign or repair changes
Raise
speed/config redesign
New Balance / Jackydima compatibility work
production migration
target acquisition
climbing
```

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| exact current continuation | `BETWEEN_CHATS.md` |
| Gate 4 contract/closure | `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`; EV-213 |
| staged validation | `COLLISION_TEST_PLAN.md` |
| closed lifecycle safety | `COLLISION_LIFECYCLE_PLAN.md`; EV-206–EV-207 |
| post-rewrite evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-208–EV-213 |
| Dual/native physical source evidence | `EVIDENCE_INDEX.md` physical-source/Dual routes; EV-090–EV-094, EV-207, EV-211 |
| animation-family/assets | `ANIMATION_INDEX.md`; `ANIMATION_CATALOG.md`; `ANIMATION_RULES.md` |
| source/API/hook lookup | `SOURCE_HOOK_GUIDE.md` |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| local build/deploy procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |

---

## Forward Order

```text
equipped-melee marker expansion planning — NEXT
→ freeze first bounded equipped-melee expansion
→ implement/review/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature research compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
