# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-13

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current raw55 diagnostic implementation: `0bfb2ba13ba91488570a41592504ac84428def2a`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_269_ONWARD.md` through **EV-271**; prior raw55 causal evidence EV-262–EV-268 is in the preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick pre-StatePosition FIST diagnostic implementation:

```text
commit: 0bfb2ba13ba91488570a41592504ac84428def2a
source review: PASS
local Release Script_FrameCollisionTest build: PASS
runtime validation: PASS for first frame-1 FIST
```

Canonical evidence is now through **EV-271**.

No Work implementation task is currently active. The next raw55 responsibility is to reconcile repeated-FIST semantics and remaining family ownership before any permanent `PhysicalFistCollision` promotion.

---

## Closed / Current Collision Boundary

```text
C1-R1 lifecycle safety                         CLOSED — EV-206–EV-207
collision architecture verification            CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack equipped   CLOSED/PASS — EV-216–EV-244
raw8 FIST shared mechanism + controls           CLOSED/PASS through EV-271
native NPC equipped controls                    CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control               CLOSED/PASS — EV-259
fall-down logger boundary                       CLOSED — EV-260
BluntArrow/BluntBolt classification             CLOSED — EV-261
raw55 early callback causal ownership           CONFIRMED — EV-262
raw55 whole-callback suppression gate           FAILED/REJECTED — EV-262
raw55 Quick callback compound ownership         CONFIRMED/CLOSED — EV-264
raw55 Quick early-group/state separability      CONFIRMED/PASS — EV-265
raw55 Quick authored-FIST group activation      CONFIRMED/PASS — EV-266
raw55 Quick group opening without rearm         INSUFFICIENT — EV-266
raw55 Quick triggered-list rearm                CONFIRMED/PASS — EV-267
raw55 close-range timing cause                  CONFIRMED — EV-268
raw55 Quick frame-1 pre-state activation        CONFIRMED/PASS — EV-269
raw55 repeated-FIST temporary one-shot limit    CONFIRMED OPEN DESIGN GAP — EV-270
equipped + raw8 frame-0/frame-1 marker support  CONFIRMED — EV-271
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Raw55 Quick Causal Chain

Factual Troll/BlackTroll source:

```text
TrollFist
gEUseType_PhysicalFist / raw55
resting collision group5
```

```text
EV-264:
    native Quick contains both StatePosition 0 -> 1 and early raw55 5 -> 7

EV-265:
    early 5 -> 7 can be suppressed while StatePosition 0 -> 1 survives

EV-266:
    authored FIST can open 5 -> 7 and native cleanup works
    opening alone does not restore damage

EV-267:
    ClearTriggeredList after FIST opening restores damage on contact

EV-268:
    prior close-range divergence was marker timing, not proven geometry
    frame-1 FIST transport was already healthy

EV-269:
    frame-1 FIST at StatePosition 0 can itself open/rearm raw55
    later native Quick still advances 0 -> 1 through natural 7 -> 7
    damage and native 7 -> 5 cleanup remain healthy

EV-270:
    later FIST delivery in the same Quick execution is visible
    current diagnostic one-shot bookkeeping prevents a second raw55 rearm
    this is not acceptable as final authored semantics
```

Permanent raw55 design remains intentionally unfrozen until repeated-marker semantics and remaining raw55 family ownership are resolved.

---

## Early Marker Authoring Boundary — EV-271

Frame indices are literal. There is **no global frame-1 minimum**.

Validated controls:

```text
2H Normal RIGHT, frame 0 -> accepted 5 -> 7 + clear + damage + native cleanup
2H Normal RIGHT, frame 1 -> same healthy result

raw8 Sabretooth Quick FIST, frame 0
-> ownership close + accepted FIST + latch rearm + timing permission + positive damage

raw8 Sabretooth Quick FIST, frame 1
-> same healthy mechanism and positive damage
```

User observed more Sabretooth misses at frame 0. The logs contain no marker rejection; frame-0 FIST is accepted and its timing permission is consumed. Interpret this as mechanism/contact timing sensitivity, not a transport failure.

Authoring authority is `ANIMATION_RULES.md`:

```text
equipped source marker = physical collision window
raw8 FIST = one native damage opportunity
```

Frame 0 is legal for both tested mechanisms, but markers should be placed for intended contact timing rather than merely as early as possible.

---

## Current Immediate Responsibility

Return to Normal Chat design before another Work implementation.

The next raw55 causal/design gap is:

```text
REPEATED QUICK FIST REARM
```

The existing frame-1 + later-FIST run proves later FIST transport reaches the raw55 diagnostic boundary, but `PhysicalFistProbe` deliberately blocks a second intervention after the first pre-state FIST.

Before permanent raw55 promotion, determine the smallest diagnostic proof that one later legitimate FIST in the same Quick C1 can rearm the already-open group7 source without another group request, custom damage, state write, or cleanup mutation.

Separate later responsibility:

```text
raw55 Power currently has no custom ownership in PhysicalFistProbe and can leak native damage despite markers.
Normal/Sprint still reflect older temporary suppression experiments.
```

Do not treat those temporary family behaviors as the production design.

---

## Protected Boundaries

Until the next raw55 probe is explicitly frozen:

```text
Raw8FistCollision unchanged
stable equipped FrameCollisionMarkers semantics unchanged
CollisionLifecycleGuard semantics unchanged
CollisionSources unchanged
CollisionSourceOperations unchanged
EngineBridge hook ownership unchanged
native cleanup unchanged
no species/name policy
no permanent PhysicalFistCollision yet
no custom/direct damage
no TriggerTarget / OnDamage
no arbitrary StatePosition or SPU writes
no manual cleanup
no new hooks/timers/polling
```

---

## Still Paused

Until raw55 repeated-marker/family semantics are sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
