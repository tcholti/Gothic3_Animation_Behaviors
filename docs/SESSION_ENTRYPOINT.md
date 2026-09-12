# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current probe authority: `docs/COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md`  
Superseded unimplemented probe: `docs/COLLISION_RAW55_QUICK_EARLY_WINDOW_CONTROL_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_265_ONWARD.md` through **EV-268**; prior raw55 causal evidence EV-262–EV-264 is in `docs/EVIDENCE_LEDGER_250_ONWARD.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick pre-StatePosition FIST diagnostic implementation:

```text
commit: 0bfb2ba13ba91488570a41592504ac84428def2a
source review: PASS
local Release Script_FrameCollisionTest build: PASS
runtime diagnostic DLL: copied by User to Gothic 3/scripts
runtime test: NOT YET RUN
```

Canonical evidence therefore still stops at **EV-268**. Do not create EV-269 until the new runtime log is analyzed.

No Work implementation task is currently active. The immediate next action is local runtime validation.

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
raw55 pre-state authored activation             IMPLEMENTED/BUILT; RUNTIME OPEN
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
    later authored FIST can open 5 -> 7 and native cleanup works
    opening alone does not restore damage

EV-267:
    one ClearTriggeredList after successful delayed FIST opening restores damage on contact

EV-268:
    frame-4 FIST works because it arrives after native StatePosition reaches 1
    frame-1 FIST is transported correctly but arrives at StatePosition 0 before the EV-265 proof exists
    prior frame-1 failure is therefore a temporary probe-ordering limitation
```

Frame 0 remains unproven and must not be assumed equivalent to frame 1.

Permanent raw55 design remains intentionally unfrozen.

---

## CURRENT IMMEDIATE RESPONSIBILITY — LOCAL RUNTIME VALIDATION

Use the already-built/deployed diagnostic implementation at:

```text
0bfb2ba13ba91488570a41592504ac84428def2a
```

Keep Quick `G3AB_COL_FIST` markers at **frame 1**.

One Troll run is sufficient initially. Test several marked Quick attacks at very close range and ordinary fist-contact distance.

Expected successful shape:

```text
FIST observed at StatePosition 0
RIGHT TrollFist raw55 5 -> 7
ClearTriggeredList=1
later original Quick callback still advances StatePosition 0 -> 1
later native group7 request may appear as 7 -> 7
OnDamage occurs on contact
native cleanup returns 7 -> 5
C1 closes without repair/lifecycle issue
```

A later native `7 -> 7` can legitimately make lifecycle `Requests=2`; that does not indicate two probe-owned activations.

Commit the complete log to `research/raw/` and return to Normal Chat with only:

```text
log filename
visual observation
```

Normal Chat analyzes the GitHub log directly using POP-07 rather than asking for a large paste.

---

## Protected Boundaries

Until the runtime result is analyzed:

```text
Raw8FistCollision unchanged
FrameCollisionMarkers semantics unchanged
CollisionLifecycleGuard semantics unchanged
CollisionSources unchanged
CollisionSourceOperations unchanged
EngineBridge hook ownership unchanged
Normal/Sprint raw55 behavior unchanged
native cleanup unchanged
no species/name policy
no permanent PhysicalFistCollision
no custom/direct damage
no TriggerTarget / OnDamage
no StatePosition or SPU writes
no manual cleanup
no new native 7 -> 7 suppression
no contact-geometry/body-physics changes
no new hooks/timers/polling
```

---

## Still Paused

Until the frame-1 pre-state result closes and raw55 design is sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO Normal/Sprint raw55 production generalization
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```
