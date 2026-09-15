# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-285 CORRECTED; RAW55 ARCHITECTURE SYNTHESIS PAUSED FOR TWO CAUSAL CLOSURES + NEW BALANCE 0.7.0 BUNDLE RUNTIME COEXISTENCE

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence is through **EV-285**.

No permanent raw55 implementation is authorized yet.  
No new Work/source task is currently frozen.

The two-FIST runtime supplied architecture-relevant evidence before permanent promotion, so architecture synthesis remains paused until the newly exposed Normal pre-state and non-Quick repeated-FIST boundaries are closed. New Balance 0.7.0 source-level compatibility passes EV-284. EV-285 has been corrected against the already-canonical EV-035/EV-150/EV-242 runtime evidence: bundled `Script_AttackCollision` overlaps our callback responsibility but has demonstrably coexisted with marked Whirl and Pierce in the tested installation/load order. Final New Balance 0.7.0 compatibility validation must therefore use the bundle as actually shipped, with AttackCollision active when bundled.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. EVIDENCE_LEDGER_283_ONWARD.md — EV-283 through corrected EV-285
4. EVIDENCE_LEDGER.md — EV-035, EV-047–EV-055, EV-148–EV-150
5. EVIDENCE_LEDGER_232_ONWARD.md — EV-242
6. EVIDENCE_LEDGER_269_ONWARD.md — EV-269, EV-270 and EV-273
7. EVIDENCE_LEDGER_274_ONWARD.md — EV-274 through EV-279 only as needed
8. EVIDENCE_LEDGER_280_ONWARD.md — EV-280 through EV-282 only as needed
9. FEATURE_DEVELOPMENT_METHOD.md before freezing a new probe or permanent module
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

Freeze only one causal intervention at a time.

---

## EV-284 — New Balance 0.7.0 Compatibility Preflight

Current source authority:

```text
https://github.com/Jackydima/gothic3sdk/tree/master/scripts/Script_NewBalance
master = a9f736603bb42c40b6e1556619051b57f9f525b6
master date = 2026-09-14
Script_NewBalance.rc = 0.7.0.0
```

Active Fist-specific 0.7.0 behavior is animation-speed policy at `Script_Game +0x42A0`: Human Fist Attack `0.70`, Human Fist PowerAttack `0.80`. The former Fist friendly/current-target byte patch is commented out. New Balance's dual-1H triggered-list fix and combat-move scaling are separate from raw55 marker ownership. Source-level compatibility is PASS.

---

## EV-285 — Corrected AttackCollision Compatibility Boundary

`Script_AttackCollision` is a separate DLL target but, per the User's distribution knowledge, is bundled with New Balance. Separate build target does **not** mean absent from the shipped bundle.

Its source genuinely overlaps this project's equipped collision callbacks and uses fixed timers, direct `SetCollisionGroup(Item_Attack)`, `ClearTriggeredList()` and `StatePosition` writes. That overlap requires compatibility validation, but the earlier conclusion that the systems are mutually exclusive was wrong because controlled combined runtime already exists.

Historical combined evidence:

```text
EV-035 / EV-150
New Balance + AttackCollision + FrameCollision v0.19
marked player 2H Whirl
RIGHT -> OFF -> RIGHT remained authoritative
no extra timer-owned activation
interruptions cleaned safely

EV-242
New Balance bad-skip prevention + AttackCollision loaded
20 Pierce executions
1H / Torch+1H / Shield+1H / Dual P0/P1
expected marker activation/cleanup and generation bookkeeping PASS
```

Therefore current status is:

```text
ATTACKCOLLISION SOURCE RESPONSIBILITY OVERLAP = YES
COEXISTENCE IN TESTED BUNDLE/LOAD ORDER = CONFIRMED
ARBITRARY LOAD ORDER / EVERY FAMILY / EVERY MARKER TIMING = NOT YET CERTIFIED
MUTUAL-EXCLUSION CLAIM = SUPERSEDED
```

### Torch+1H correction

LEFT is not inherently wrong for Torch+1H. Gothic has real torch strikes.

Canonical source evidence:

```text
EV-051  Torch+1H P1/P3 Quick attacks genuinely use LEFT torch collision
EV-052  some P0 Normal native left-torch activations are unintended for those animations
EV-053  AttackCollision regular Torch+1H Normal routes to RIGHT weapon
```

This project's authored slot markers are deliberately exact:

```text
LEFT  = exact equipped left source (including torch when the torch really strikes)
RIGHT = exact equipped right source
BOTH  = both
OFF   = neither
```

Current resolver takes the factual left/right equipped entities without a weapon-type prohibition, so authored LEFT supports a torch strike directly.

### Final compatibility posture

Do **not** remove AttackCollision from the New Balance bundle for final validation. Test the bundle as users actually receive it. The representative matrix should cover marked Normal/Quick/Power/Pierce/SimpleWhirl/Whirl/Hack across applicable 1H, Torch+1H, Dual, 2H and Staff fixtures, plus raw8/raw55 Fist. The critical failure signals are premature AttackCollision timer opening before a marker, extra triggered-list clears, wrong-source activation, or cleanup divergence.

---

## Still Paused

```text
NO permanent raw55 architecture freeze yet
NO production PhysicalFistCollision implementation
NO promotion/copy of PhysicalFistProbe scaffolding
NO assumption that non-Quick repeat FIST needs or does not need ClearTriggeredList
NO ignoring Normal SP0 marker delivery
NO blanket New Balance 0.7.0 full-family runtime compatibility claim yet
NO assumption that AttackCollision must be removed from bundled New Balance
NO broad native-creature certification continuation
NO Axe/Rapier compatibility sequence
NO AttackContinuationProtection work
```
