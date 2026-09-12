# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md`  
Superseded unimplemented probe: `docs/COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md`  
Prior raw55 probe contracts: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_CALLBACK_BOUNDARY_PROBE.md`; `docs/COLLISION_RAW55_QUICK_GROUP_SUPPRESSION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_FIST_ACTIVATION_PROBE.md`; `docs/COLLISION_RAW55_QUICK_FIST_REARM_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_265_ONWARD.md` through **EV-268**; prior raw55 causal evidence EV-262–EV-264 is in `docs/EVIDENCE_LEDGER_250_ONWARD.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Evidence path moves: `docs/EVIDENCE_PATH_MIGRATIONS.md`  
Bounded Work execution: `docs/WORK_IMPLEMENTATION_PROTOCOL.md`  
Feature method: `docs/FEATURE_DEVELOPMENT_METHOD.md`  
Architecture: `docs/DESIGN.md`; `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Validation: `docs/COLLISION_TEST_PLAN.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Closed Collision Boundary

```text
C1-R1 lifecycle safety                         CLOSED — EV-206–EV-207
collision architecture verification            CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack             CLOSED/PASS — EV-216–EV-244
raw8 FIST shared mechanism + later controls     CLOSED/PASS through EV-263
native NPC equipped controls                    CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control               CLOSED/PASS — EV-259
fall-down logger boundary                       CLOSED — EV-260
BluntArrow/BluntBolt classification             CLOSED — EV-261
raw55 early callback causal ownership           CONFIRMED — EV-262
raw55 whole-callback suppression gate           FAILED/REJECTED — EV-262
raw55 Quick callback compound ownership         CONFIRMED/CLOSED — EV-264
raw55 Quick early-group/state separability      CONFIRMED/PASS — EV-265
raw55 Quick authored-FIST group activation      CONFIRMED/PASS — EV-266
raw55 Quick native cleanup after FIST opening   CONFIRMED/PASS — EV-266
raw55 Quick group opening without rearm         INSUFFICIENT — EV-266
raw55 Quick FIST-time triggered-list rearm      CONFIRMED/PASS FOR CONTACT — EV-267
raw55 close-range timing cause                  CONFIRMED — EV-268
raw55 frame-1 marker transport                  CONFIRMED; arrives pre-StatePosition — EV-268
raw55 pre-state authored activation             OPEN — current probe
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8.

---

## Current Raw55 State

Factual Troll/BlackTroll source:

```text
TrollFist
gEUseType_PhysicalFist / raw55
resting collision group5
```

Current Quick causal chain:

```text
EV-264:
    native Quick callback contains both StatePosition 0 -> 1 and early raw55 5 -> 7

EV-265:
    early 5 -> 7 can be suppressed while StatePosition 0 -> 1 survives

EV-266:
    post-state authored FIST can open raw55 and native cleanup works
    group opening alone does not restore damage

EV-267:
    one exact ClearTriggeredList after FIST-time 5 -> 7 restores damage when contact occurs

EV-268:
    moving FIST to frame 4 moves activation to ~StateTime 0.16 and produces native-like early/later damage
    moving FIST to frame 1 proves marker transport occurs earlier, while StatePosition is still 0
    current temporary probe ignores that frame-1 FIST because no EV-265 suppression proof exists yet and it requires StatePosition 1
```

Therefore the earlier close-range marked/native difference is timing-window-driven, not evidence of a different native source. The logs still do not identify exact damage geometry, so do not promote "fist-only" versus "whole limb/body" as a proven engine fact.

Frame 1 is now the active ordering boundary. Frame 0 remains untested and may have a distinct C1-ordering issue.

Permanent raw55 design remains intentionally unfrozen.

---

## CURRENT IMMEDIATE RESPONSIBILITY — WORK IMPLEMENTATION

The next diagnostic contract is frozen in:

```text
docs/COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md
```

The exact bounded Work task is in:

```text
docs/BETWEEN_CHATS.md
```

Single question:

> Can exact frame-1 raw55 Quick FIST, arriving with valid C1/source while StatePosition is still 0 and before native Quick's own raw55 request, immediately perform one RIGHT `5 -> 7` activation plus one `TouchDamage.ClearTriggeredList()` while preserving the later native StatePosition transition and native cleanup?

Required architecture:

```text
PhysicalFistProbe
    owns a separate exact pre-state FIST path
    does not require EV-265 suppression proof for that path
    owns actor/source/C1 one-shot identity
    performs one explicit 5 -> 7 request
    performs one clear only after verified group7
    observes later native Quick behavior without hiding it

EngineBridge
    unchanged transport owner; existing seams are sufficient

FrameCollisionMarkers
    unchanged; raw55 FIST remains stable UNSUPPORTED_MISSING_SOURCE

Raw8FistCollision / lifecycle / sources / source operations
    unchanged
```

Do not add suppression for the later native `7 -> 7` request. Do not modify lifecycle bookkeeping to hide that request. No custom damage, state writes, manual cleanup, geometry changes, or new hooks are authorized.

Build execution is **not** authorized for Work. Normal Chat reviews source first; User + Normal Chat build only after review passes.

---

## Active Comparison Evidence

Keep in `research/raw/` while pre-state FIST ordering remains open:

```text
research/raw/2026.09.12_troll_quick_fist_activation_frame_1.log
research/raw/2026.09.12_troll_quick_fist_activation_frame_4.log
research/raw/2026.09.12_troll_quick_fist_activation_3.log
research/raw/2026.09.12_black_troll_quick_fist_activation_3.log
research/raw/2026.09.12_troll_native_collision_3.log
research/raw/2026.09.12_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_black_troll_raw55_quick_fist_activation.log
```

The first two are EV-268; the next three are EV-267; the last two are EV-266.

---

## Protected Boundaries

```text
Raw8FistCollision unchanged
FrameCollisionMarkers semantics unchanged
CollisionLifecycleGuard semantics unchanged
CollisionSources unchanged
CollisionSourceOperations unchanged
equipped RIGHT/LEFT/BOTH/OFF unchanged
EngineBridge remains transport-only
PhysicalFistProbe remains temporary diagnostics-only
no species/name policy
no permanent PhysicalFistCollision yet
no custom/direct damage
no TriggerTarget / OnDamage
no StatePosition or SPU writes
no manual cleanup
no new suppression for native 7 -> 7
no contact-geometry/body-physics changes
no animation asset/marker placement changes in code
no new hooks/timers/polling
```

---

## Still Paused

Until the Quick pre-state FIST question closes and raw55 design is sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint raw55 production generalization
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
