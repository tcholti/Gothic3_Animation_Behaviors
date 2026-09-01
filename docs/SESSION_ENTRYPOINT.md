# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-01

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Current validation authority: `docs/COLLISION_TEST_PLAN.md`  
Current lifecycle authority: `docs/COLLISION_LIFECYCLE_PLAN.md`  
Release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`  
Knowledge-maintenance/audit rules: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Branch/convention authority: `docs/PROJECT_PIPELINE.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md` → canonical evidence ledgers  
Local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

> **CAM boundary:** This Gothic 3 project may read/compare against `tcholti/Collaborative-Agency-Model` when useful, but it must not modify CAM rules, philosophy, profiles, procedures, or theory. Any CAM change belongs to a separate User-authorized CAM-focused chat/responsibility.

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
2. Read `docs/BETWEEN_CHATS.md` only when it contains an active transient responsibility.
3. Treat the release-purity rule above as standing architecture.
4. If the active subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, artifact naming, build labels, branch meanings or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
10. Do not modify the Collaborative-Agency-Model repository from Gothic 3 work; CAM evolution is a separate dedicated responsibility.

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

## Stable Repository Boundary

Repository cleanup, evidence-location cleanup, stable promotion and temporary-branch retirement are complete.

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research
```

Current stable `main` contains the verified collision architecture checkpoint. The temporary second-pass staging branch has been deleted after proving its final tree was already preserved in accepted history.

Known unrelated local file remains outside project maintenance and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Project Structural Stabilization

### Pass 1 — structural document/tool simplification: COMPLETE

Verified completed changes:

```text
- evidence storage reduced to three canonical files:
  EVIDENCE_LEDGER.md                EV-001–EV-157
  EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
  EVIDENCE_LEDGER_199_ONWARD.md     EV-199 onward

- obsolete active Script_FrameEffectLogger target/source removed
- standalone LARGE_LOG_EVIDENCE_PROCEDURE removed; POP-07 remains the recurring procedure authority
- completed second-pass and Gate-4 one-off contracts retired after durable content was absorbed by current authorities/evidence
- duplicate RESEARCH_MAP chronology router retired; EVIDENCE_INDEX + exact EV/provenance + Git history now own historical retrieval
- duplicate docs/archive documentation snapshots retired; Git history owns superseded documentation wording
- research/raw, research/archive and research/derived remain distinct evidence-lifecycle layers
- stale routes/build references found during the pass were repaired
```

No collision behavior, marker semantics or closed evidence status changed in this pass.

### Pass 2 — CURRENT: Gothic-specific rules/procedures consistency audit

Audit together rather than independently:

```text
COLLABORATION_RULES.md
WORK_IMPLEMENTATION_PROTOCOL.md
PROJECT_OPERATING_PROCEDURES.md
PROJECT_PIPELINE.md
KNOWLEDGE_MAINTENANCE.md
KNOWLEDGE_REGISTRY.md
README.md
SESSION_ENTRYPOINT.md
```

Immediate objective:

```text
one responsibility → one primary authority
no contradictory rules
no duplicated philosophy/procedure
no obsolete temporary rule
no unnecessary rereading/document churn
clear User / Normal Chat / Work / local-PC / repository allocation
explicit Gothic-project-only scope
CAM remains read/compare-only and is never modified from this responsibility
```

Perform this as a consistency/ownership audit first. Preserve distinct responsibilities and useful project-specific practice; do not broadly rewrite merely to make wording uniform.

### Pass 3 — after Pass 2

Build/product/repository-shape audit:

```text
- verify only justified current build products/tools remain
- preserve release/diagnostic twin architecture
- verify branch/dependency/build assumptions are explicit
- identify orphan prototype/build paths only if they actually exist
```

### Pass 4 — after Pass 3

Final readiness check:

```text
- fresh Chat/Work can recover the project from a small retrieval surface
- important engine facts remain routeable index → EV → provenance
- build/product model is unambiguous
- repository state has no unresolved structural ambiguity
```

Do **not** start equipped-melee marker expansion until all four stabilization passes are complete.

---

## After Stabilization

Resume engineering from the active branch in this order:

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
