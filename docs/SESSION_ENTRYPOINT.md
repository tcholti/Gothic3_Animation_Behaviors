# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is the diagnostic twin. Permanent collision behavior must also compile in diagnostics-free `Script_FrameCollisionBehaviorTest`. Final migration into `src/Script_G3AnimationBehaviors` occurs only after focused acceptance and standalone collision regression.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and committed derived packages for large-log retrieval. Processed source evidence moves unchanged to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Frozen production contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Latest canonical evidence: **EV-294** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick         repeated-FIST CLOSED/PASS — EV-273
raw55 Normal        repeated-FIST CLOSED/PASS — EV-292
raw55 true Power    repeated-FIST CLOSED/PASS — EV-293
raw55 Sprint-origin repeated-FIST CLOSED/PASS — EV-294

ALL FAMILY-SPECIFIC RAW55 CAUSAL RESEARCH CLOSED
PERMANENT RAW55 ARCHITECTURE FROZEN
PERMANENT RAW55 IMPLEMENTATION PUBLISHED + INDEPENDENT SOURCE REVIEW PASS
BOTH PERMANENT LOCAL TARGETS BUILD PASS
BEHAVIOR-ONLY DEPLOYMENT + FUNCTIONAL SMOKE PASS
```

Permanent implementation commit:

```text
21853392f146febbc2d1aad4e501baa741fd65b2
```

Frozen implementation base:

```text
71a5ae377c4043677c0a8edd86801d2db697fac0
```

Independent Normal Chat source review: **PASS**.

Review confirms:

```text
exactly one implementation commit over frozen base
expected source scope only
PhysicalFistCollision.cpp/.h added as permanent behavior source
PhysicalFistProbe.cpp/.h deleted
probe removed from CMake / executable architecture
raw55 family-specific proof maps replaced by one actor/C1 execution record
origin family immutable; Sprint Action9 -> Action2 continuation preserved
premature exact RIGHT raw55 5 -> 7 suppression is selective and callback-scoped
first-FIST semantics match frozen Quick / Normal / Power / Sprint rules
second FIST is clear-only with no second collision-group request
Normal hidden ALL-clear suppression is exact trigger + Script_Game.dll+0x386C6 + one-shot
no PC_Hero / visited-array / ResetOnUntouch production policy
ActivateAttackSource and RearmTriggeredContacts split generic mutation primitives
existing ActivateOrRearm equipped semantics retained
FrameCollisionMarkers changes only expose existing family/result helpers
original native AI callbacks remain active
raw8/equipped marker paths remain established path
Gothic native damage/target/contact and final 7 -> 5 cleanup remain native
CollisionLifecycleGuard/C1-R1 unchanged
entity-specific ClearTriggeredList diagnostic hook removed
no Action / StatePosition / SPU writes, direct damage or custom cleanup
```

No material source contradiction found.

## Local build / behavior-only smoke — PASS

Both Release targets built successfully from the reviewed permanent candidate:

```text
Script_FrameCollisionBehaviorTest  PASS
Script_FrameCollisionTest          PASS
```

Behavior-only deployment identity:

```text
only live collision DLL: Script_FrameCollisionBehaviorTest.dll
length: 418304 bytes
built/live SHA256:
0EB935FCBFD5B7A2D2D56683971641EA42B9F7FF074D5B7F2EC2FD353594833A
```

The process-module enumeration attempted during the smoke returned no `Script_FrameCollision*` module and is **not** used as a pass/fail criterion; prior canonical Gate-3 behavior-only validation likewise establishes functional load/exit by isolated deployment + runtime behavior, not persistent module enumeration.

User functional smoke under the behavior-only DLL:

```text
spawned Troll
observed Troll attacks capable of damaging twice, behavior not seen before permanent raw55 support

spawned Golem
attacked with 2H, Dual 1H/1H and Staff
observed established authored marker behavior still functioning

exercised Hack attack
observed Hack behavior still functioning
```

This is functional/release-purity evidence only. It does not independently prove internal family/C1/source transitions; the diagnostic twin owns that focused acceptance.

## Immediate next responsibility — DIAGNOSTIC DEPLOY / STARTUP GATE

Do not launch Work.

Replace the behavior-only DLL with the freshly built reviewed `Script_FrameCollisionTest.dll`, verify it is the only live collision DLL, verify built/live SHA256 identity, then launch only far enough to load scripts and exit normally.

Verify startup log contains the normal diagnostic load/profile, Hack callback identity, hook installation and clean unload.

Only after diagnostic startup PASS proceed to focused permanent raw55 runtime acceptance.

## Focused permanent acceptance

The first diagnostic production acceptance must cover only the frozen permanent candidate before broad regression:

```text
Quick first/repeated FIST
Normal SP0 first FIST + marker2
true Power first/repeated FIST
Sprint-origin Action9 -> Action2 first/repeated FIST
unmarked raw55 native fallback
raw8 FIST sentinel
equipped marker sentinel
native raw55 7 -> 5 cleanup / outstanding-zero lifecycle
```

## Still paused

```text
NO new Work task during local validation
NO collision migration into src/Script_G3AnimationBehaviors yet
NO standalone broad regression before focused permanent raw55 acceptance
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
