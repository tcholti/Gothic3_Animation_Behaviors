# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-09

## Current Bridge — Raw-8 Quick FIST Bounded Extension Next

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `SESSION_ENTRYPOINT.md` first, then this file.

---

## Evidence State

Stable collision foundation remains closed through EV-247. New EV-248 closes the native-Sabretooth actor control and the prerequisite raw-8 Quick mechanism classification.

### Native Sabretooth NPC result

Published raw:

```text
research/raw/2026.09.09_sabertooth_npc_marked_attacks.log
source commit: 3f0661da44afed99544c139241f3b1ead5207254
```

A genuine `Actor: Sabertooth` repeatedly attacked `PC_Hero`.

Normal:

```text
5 observed marked executions
factual source = Fist / raw8 / group0
FIST ownership established
initial SPU+0x164 0 -> 1
G3AB_COL_FIST = ACCEPTED
OwnershipMatched = 1
below-threshold timing permission armed/consumed where required
damage caller = Game +0x16E348
```

Power:

```text
2 observed marked executions
same factual raw8 source
same ownership/latch/timing mechanism
FIST = ACCEPTED
damage caller = Game +0x16E348
```

This closes the native-NPC Normal/Power actor-side control for the Sabretooth fixture. Together with EV-247, the tested raw-8 FIST mechanism is not human/species/animation-family gated.

Quick-left/right:

```text
factual source = Fist / raw8 / group0
Action = 4 / 5
native damage caller = Game +0x16E348
current G3AB_COL_FIST = REJECTED_UNSUPPORTED_HIT
```

The rejection is the existing software family boundary, not a source mismatch.

### Quick mechanism classification

Tested Game.dll binary reference:

```text
sAICombatMoveItlLoop                   Game +0x16DD00
generic SPU+0x164 zero gate            Game +0x16DFB9
GetMaxTime(0)                          Game +0x16E160
GetPlayTime(0) timing call             Game +0x16E180
threshold comparison                   Game +0x16E18C..+0x16E190
native SPU+0x164 = 1 write             Game +0x16E1A3
observed OnDamage caller return        Game +0x16E348
```

The alternate timing sub-arm writes the latch at `Game +0x16E13E` and returns before the later damage dispatch. Therefore an observed Quick damage call returning at `Game +0x16E348` cannot come from that alternate arm; it necessarily traverses the same relevant generic latch/timing route used by the existing raw-8 FIST contract.

Canonical evidence: **EV-248**.

Conclusion:

> Raw-8 Quick has sufficient native-mechanism proof for bounded reuse of the existing FIST contract. No new Quick collision mechanism is justified.

---

## Current Source Audit

Existing source already provides the required generic Quick plumbing:

```text
TryGetCurrentAttackHitFamily:
QuickAttack / QuickAttackR / QuickAttackL -> AttackFamily_Quick

GetMarkerOwnedStatePosition:
AttackFamily_Quick -> 1

EngineBridge:
OnAI_QuickAttack -> EvaluateAttackCallback(AttackFamily_Quick)

FIST marker path:
ResolveFistCollisionSource(actor)
SPU+0x164 latch write
existing exact timing-permission transport
```

The deliberate FIST blockers found are the Normal/Power-only family checks:

```cpp
family == AttackFamily_Normal || family == AttackFamily_Power
```

and:

```cpp
if (markerOpcode == MarkerOpcode_Fist
    && family != AttackFamily_Normal
    && family != AttackFamily_Power)
    -> REJECTED_UNSUPPORTED_HIT
```

---

## NEXT — Frozen Implementation Responsibility

Implement ONLY the smallest raw-8 FIST Quick family-scope extension.

Required semantic change:

```text
existing supported FIST family set:
Normal + Power

becomes:
Normal + Power + Quick
```

Quick means the already-existing `AttackFamily_Quick`, covering the factual Quick/QuickR/QuickL actions already normalized by current source.

Expected implementation shape:

- admit `AttackFamily_Quick` in `UpdateHumanFistMarkerOwnership`'s existing exact marked raw-8 FIST family predicate;
- admit `AttackFamily_Quick` in `FrameCollisionMarkers`' existing FIST supported-family gate;
- preserve the existing Quick `StatePosition = 1` behavior;
- reuse the exact existing raw-8 FIST source resolver, C1-generation ownership, initial latch close, accepted-marker latch rearm and exact one-shot timing permission.

Do NOT add or change:

```text
new hooks
new marker vocabulary
species/name/animation-family checks
raw55/PhysicalFist support
another latch/timing mechanism
direct/custom damage
FIST_OFF
Fist ClearTriggeredList
equipped Item_Attack/Item_Equipped Fist windows
C1 weapon cleanup semantics
unmarked/native fallback
Normal/Power semantics
equipped weapon marker behavior
AttackContinuationProtection
Raise/speed/configuration
```

Before editing, inspect the exact surrounding functions and search for any additional FIST family restriction. If another material restriction or contradictory mechanism appears, stop and report it instead of broadening.

Work source/static audit only. **BUILD EXECUTION IS PROHIBITED** unless a later frozen task explicitly changes that rule.

After implementation/publish, Normal Chat independently reviews the diff. User then synchronizes, builds/deploys the diagnostic twin locally, and runs bounded native-Sabretooth Quick-left/right validation.

---

## Post-Change Quick Validation

Use native Sabretooth -> player.

Require at minimum:

```text
QuickR marked execution
QuickL marked execution
repeat enough for clear evidence
```

Expected:

```text
source = Fist / raw8
Family = QUICK
FIST ownership established on factual C1 generation
initial latch close 0 -> 1 once per marked execution
G3AB_COL_FIST = ACCEPTED
marker latch rearm 1 -> 0
below-threshold opportunity uses existing exact timing permission when needed
native damage occurs only after authored FIST opportunity
caller remains Game +0x16E348
unmarked/native fallback remains native
```

If this validation passes, close raw-8 Quick and move to the prepared NPC/monster family compatibility logs.

---

## Active Comparison Artifacts

Keep both in `research/raw/` until Quick validation closes:

```text
research/raw/2026.09.08_sabertooth_marked_attacks.log
research/raw/2026.09.09_sabertooth_npc_marked_attacks.log
```

Disposition: **ACTIVE COMPARISON — KEEP RAW**.

---

## Planned Sequence After Quick

```text
native equipped-NPC marker controls:
  Goblin -> 1H / raw2
  Demon  -> 2H / raw3
  Ogre   -> Axe / raw52

-> additional prepared native/modded animation-family controls
   one actor/family per log
-> separated 2H vs Axe compatibility
-> separated 1H vs Rapier compatibility
-> final native mixed/stress collision regression
-> separate AttackContinuationProtection
-> combined regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration
```

If one intermediate family fails, stop and resolve that exact failure before continuing.

---

## GitHub Desktop Handoff

Assistant evidence/current-state maintenance advances the remote branch beyond the User's local checkout.

Before the next local build/test window:

```text
open GitHub Desktop
-> select Gothic3_Animation_Behaviors
-> confirm Current branch = docs/collision-source-evidence
-> click Fetch origin
-> if offered, click Pull origin
-> verify Changes shows 0 changed files
```

The User is still a GitHub Desktop beginner; repeat these steps when needed.
