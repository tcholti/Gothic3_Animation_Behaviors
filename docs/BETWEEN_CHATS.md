# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-283 CLOSED; RAW55 ARCHITECTURE SYNTHESIS PAUSED FOR TWO CAUSAL CLOSURES + NEW BALANCE 0.7.0 COMPATIBILITY

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-283**.

No permanent raw55 implementation is authorized yet.  
No new Work/source task is currently frozen.

The two-FIST runtime supplied architecture-relevant evidence before permanent promotion, so the prior architecture-synthesis step is temporarily paused. Normal Chat must first close the newly exposed Normal pre-state and non-Quick repeated-FIST boundaries, and separately verify compatibility with New Balance 0.7.0.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. EVIDENCE_LEDGER_283_ONWARD.md — EV-283
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

A second marker is a second contact opportunity, not guaranteed damage if geometry does not contact.

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

## New Balance 0.7.0 Compatibility — Current Preflight

Compatibility with New Balance remains a product requirement.

Current public release evidence:

```text
Nexus version = 0.7.0
Nexus last updated = 2026-09-14
```

Public source repository inspected:

```text
https://github.com/Jackydima/G3Script_NewBalance
public master = 6f527c103d08708e89a80fc4fc8954546e1b93b1
public master date = 2024-11-27
```

Therefore the linked GitHub source is **not the source of the current 0.7.0 release** and cannot by itself certify 0.7.0 compatibility.

The public repository's Fist-specific patch was introduced by:

```text
2a82f9cb604262ee6ce24aceeffc81e674224e8c
codepatch for fixing transformed attacks on friendly NPCs
```

It patches `Script_Game +0xAA5E6..+0xAA5EB` to remove a current/friendly-target limitation for Fist attacks, especially transformed `PC_Hero`.

Current raw55/marker surfaces used by this project are physically separate, including:

```text
Script_Game attack callback hooks such as _AI_Attack/_AI_QuickAttack/_AI_PowerAttack
Game UpdateFrameEffects transport
Game raw8 timing path
Engine SetCollisionGroup transport
```

No direct static address/function collision has been identified in the old linked source. That makes historical/public-source static overlap risk **LOW**, but says nothing conclusive about unpublished 0.7.0 code changes.

Required status:

```text
OLD PUBLIC SOURCE STATIC PREFLIGHT = NO IDENTIFIED DIRECT OVERLAP / LOW RISK
NEW BALANCE 0.7.0 STATIC CODE CERTIFICATION = UNAVAILABLE FROM LINKED GITHUB SOURCE
NEW BALANCE 0.7.0 RUNTIME COMPATIBILITY = REQUIRED / NOT YET CERTIFIED
```

Before final raw55 promotion, test New Balance 0.7.0 together with our behavior. Compatibility validation must include actual Fist/raw55 behavior and not merely successful DLL load.

---

## Still Paused

```text
NO permanent raw55 architecture freeze yet
NO production PhysicalFistCollision implementation
NO promotion/copy of PhysicalFistProbe scaffolding
NO assumption that non-Quick repeat FIST needs or does not need ClearTriggeredList
NO assumption that Normal SP0 can be ignored
NO blanket New Balance 0.7.0 compatibility claim from stale GitHub source
NO broad native-creature certification continuation
NO Axe/Rapier compatibility sequence
NO AttackContinuationProtection work
```
