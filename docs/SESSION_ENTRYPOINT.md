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

## Current Technical Responsibility — Documentation / Knowledge-System Cleanup

Architecture verification is complete. The active responsibility is now the planned documentation/knowledge audit and justified cleanup under:

```text
docs/KNOWLEDGE_MAINTENANCE.md
docs/KNOWLEDGE_REGISTRY.md
```

Current cleanup boundary:

```text
repair stale current-state/routing language
reduce bootstrap/handoff duplication
make Step-E/EV-215 discoverable
align durable authorities with accepted Gate-4 execution identity
preserve historical provenance and global EV IDs
preserve evidence-ledger splitting where it is useful retrieval/storage structure
```

Do **not** during this first cleanup pass:

```text
delete/merge evidence ledgers
rewrite evidence claims for cosmetic consistency
move processed raw evidence without updating every affected provenance path atomically
delete temporary branch history before inspecting temp-only content
promote main before the cleaned checkpoint is reviewed
begin equipped-melee expansion or another collision implementation step
```

The unrelated local untracked file may remain untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## After This Non-Destructive Cleanup Pass

```text
review cleaned authorities for contradictions
→ perform separate atomic research/raw → research/archive migration if justified
→ inspect temp/second-pass-rewrite-publish unique history/content
→ preserve anything unique that still matters
→ define stable promotion set
→ deliberately update protected main to the proven + cleaned checkpoint
→ verify main
→ retire temp branch only if safe
→ retain main + docs/collision-source-evidence as normal two-branch model
```

Only after that repository checkpoint is stable should the project resume new collision feature expansion.

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
