# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-284 CLOSED; RAW55 ARCHITECTURE SYNTHESIS PAUSED FOR TWO CAUSAL CLOSURES + NEW BALANCE 0.7.0 RUNTIME COEXISTENCE

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence is through **EV-284**.

No permanent raw55 implementation is authorized yet.  
No new Work/source task is currently frozen.

The two-FIST runtime supplied architecture-relevant evidence before permanent promotion, so the prior architecture-synthesis step is temporarily paused. Normal Chat must first close the newly exposed Normal pre-state and non-Quick repeated-FIST boundaries. New Balance 0.7.0 source-level compatibility now passes EV-284; one runtime coexistence validation remains before final product compatibility is certified.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. EVIDENCE_LEDGER_283_ONWARD.md — EV-283 and EV-284
4. EVIDENCE_LEDGER_269_ONWARD.md — EV-269, EV-270 and EV-273
5. EVIDENCE_LEDGER_274_ONWARD.md — EV-274 through EV-279 only as needed
6. EVIDENCE_LEDGER_280_ONWARD.md — EV-280 through EV-282 only as needed
7. FEATURE_DEVELOPMENT_METHOD.md before freezing a new probe or permanent module
```

---

## Closed Family Baseline Before EV-283

```text
Quick       CLOSED/PASS through EV-273
true Power  CLOSED/PASS through EV-276
Normal      CLOSED/PASS through EV-279
Sprint      first-contact path CLOSED/PASS through EV-282
```

Common first-contact Power/Normal/Sprint evidence remains valid:

```text
preserve native callback/state progression
suppress only premature exact RIGHT PhysicalFist/raw55 5 -> 7
authored FIST opens exact RIGHT raw55 source
ClearTriggeredList=0 for the tested first contact
native damage
native 7 -> 5 cleanup
```

Quick remains the proven special contact/rearm case and has already proven pre-state FIST plus repeated FIST rearm/double damage.

---

## EV-283 — Two-FIST Cross-Family Runtime

Canonical raw:

```text
research/raw/2026.09.15_troll_raw55_double_fist_activation.log
SHA256 3771B3A9601D5CF3A715B6B15DF39DA5B55B0881CF8A127D1E9CFE436E898E43
upload commit be2db3e8f2f8f1aa09ed02cf8aad918ae0e6a1a4
```

Derived package:

```text
research/derived/2026.09.15_troll_raw55_double_fist_activation_large_log/
```

### Quick

Positive repeated-contact proof remains healthy. Representative C1=3:

```text
FIST #1 -> raw55 opening/rearm -> native damage
FIST #2 same C1 -> DecisionFistCount=2
                     ClearTriggeredList=1
                     REPEAT_FIST_REARM=1
                  -> second native damage same C1
```

The User independently observed the Quick attacks visibly damaging twice. A second marker is a second contact opportunity, not guaranteed damage if geometry does not contact.

This agrees with EV-270/EV-273: the diagnostic one-shot rule is not final authoring semantics; each legitimate Quick FIST occurrence can be its own rearm opportunity.

### Normal

The new run exposes a real pre-state boundary. Repeated examples including C1=18, 99 and 101 receive FIST #1 while:

```text
StatePosition=0
RIGHT raw55 group5
no Normal early-suppression proof yet
```

The current Normal probe ignores that marker. FIST #2 later at SP1 becomes the first/only probe-owned 5 -> 7 activation and can damage.

Therefore the run does **not** prove Normal is one-hit-only. It proves Normal pre-state authored-FIST ownership is unresolved and must be closed before permanent design.

### Power

FIST #1 at SP1 opens/damages normally. FIST #2 is visibly delivered in the same C1 while RIGHT remains group7, but the temporary Power proof is one-shot (`activationUsed`), so it attempts no second rearm.

Therefore repeated Power hit semantics remain untested; absence of a second hit is not a negative causal result.

### Sprint-origin execution

C1=87 and C1=109 repeat:

```text
Action9 / SPRINT
FIST #1 -> exact RIGHT 5 -> 7 -> native damage
same C1 then becomes factual Action2 / POWER after contact
FIST #2 arrives while same C1/source is still active and RIGHT remains group7
no second intervention because Sprint proof is already used and no Power proof owns this C1
native 7 -> 5 cleanup later
```

The Action9 -> Action2 transition does not create a new attack execution. Repeated-marker ownership therefore cannot be modeled as a one-shot permission attached only to the current family label.

### Engineering boundary from EV-283

Do not promote the family probes' `activationUsed` bookkeeping into production.

Permanent raw55 design eventually needs C1/source/marker-occurrence semantics capable of surviving factual family-state changes inside the same execution. However the exact non-Quick repeated-contact primitive is not yet proven and must not be guessed from Quick.

---

## Current Causal Responsibilities — Normal Chat

Do not launch permanent raw55 Work yet.

Close separately:

```text
A. Normal pre-StatePosition FIST
   Can a legitimate Normal FIST arriving at SP0 own the initial exact RIGHT raw55 activation
   while the untouched native Normal callback later advances StatePosition and cleanup remains healthy?
   Determine contact/rearm requirements causally; do not copy Quick automatically.

B. Non-Quick repeat FIST
   Once exact RIGHT raw55 is already group7 after FIST #1, what does FIST #2 need to create a second
   native contact opportunity for Normal/Power/Sprint-origin executions?
   Test the smallest primitive; do not assume ClearTriggeredList until proven.

C. Sprint-origin Action9 -> Action2 continuity
   Any repeat-FIST design must key to the same factual C1/source execution and must not mistake the
   post-contact Action2 state for a new Power attack.
```

Freeze only one causal responsibility at a time.

---

## EV-284 — New Balance 0.7.0 Compatibility Preflight

Compatibility with New Balance remains a product requirement.

Current source authority:

```text
https://github.com/Jackydima/gothic3sdk/tree/master/scripts/Script_NewBalance
master = a9f736603bb42c40b6e1556619051b57f9f525b6
master date = 2026-09-14
Script_NewBalance.rc = 0.7.0.0
```

Therefore this repository **does represent the current New Balance 0.7.0 source**.

Active Fist-specific 0.7.0 behavior:

```text
GetAnimationSpeedModifier
Script_Game +0x42A0
Human Fist Normal/Attack = 0.70
Human Fist PowerAttack = 0.80
```

Commit `1d09f8d177f7d18789dd55433be69703564bb0be` raised those values from `0.54` and `0.60` respectively.

The former Fist friendly/current-target patch at:

```text
Script_Game +0xAA5E6..+0xAA5EB
```

is commented out in current `CodePatch.cpp` and is not active in 0.7.0.

New Balance does call `TouchDamage.ClearTriggeredList()` at `Script_Game +0x482E7`, but only inside its dual-1H PowerAttack correction after verifying both hands are 1H. This is not the PhysicalFist/raw55 path.

New Balance also inserts combat-move scaling at:

```text
Game +0x16B8A9
```

Our project owns the enclosing `AICombatMoveInstr` entry at:

```text
Game +0x1696E0
```

and calls the original function. These are distinct sites and the New Balance movement adjustment can execute inside the original path.

Targeted current-source audit identifies no New Balance hook/patch ownership of:

```text
_AI_Attack
_AI_PowerAttack
_AI_QuickAttack
Engine +0x225660 SetCollisionGroup
Game +0x60850 marker StartEffect transport
Game +0x1696E0 AICombatMoveInstr entry
```

Status:

```text
NEW BALANCE 0.7.0 SOURCE-LEVEL COMPATIBILITY = PASS
DIRECT HOOK/ADDRESS COLLISION WITH CURRENT RAW55/MARKER MECHANISM = NONE IDENTIFIED
ACTIVE FIST CHANGE = ANIMATION SPEED, NOT COLLISION-WINDOW OWNERSHIP
RUNTIME COEXISTENCE CERTIFICATION = STILL REQUIRED
```

New Balance's speed and movement policy are external gameplay behavior that this mod should preserve, not replace. Because faster playback/movement can affect practical contact timing despite clean hook ownership, perform one coexistence runtime with New Balance 0.7.0 active before final product compatibility is certified. That runtime should verify marker delivery, raw55 opening/rearm, native damage and native cleanup.

---

## Still Paused

```text
NO permanent raw55 architecture freeze yet
NO production PhysicalFistCollision implementation
NO promotion/copy of PhysicalFistProbe scaffolding
NO assumption that non-Quick repeat FIST needs or does not need ClearTriggeredList
NO ignoring Normal SP0 marker delivery
NO blanket runtime compatibility claim before New Balance 0.7.0 coexistence test
NO broad native-creature certification continuation
NO Axe/Rapier compatibility sequence
NO AttackContinuationProtection work
```
