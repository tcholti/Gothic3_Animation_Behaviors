# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 PROBE RUNTIME RESULT PENDING LARGE-LOG CLOSURE

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

This bridge was written because the previous Normal Chat reached its context limit before the new 2.4 MB raw55 probe log could be fully analyzed and promoted.

Fresh Chat must start under:

`PROJECT_OPERATING_PROCEDURES.md` **§13 POP-11 — Normal Chat Continuity and Interrupted-Context Recovery**.

Do not begin new implementation, runtime testing, or a new Work task until the recovery closure below is complete.

---

## Fresh Chat Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. PROJECT_OPERATING_PROCEDURES.md §13 POP-11
4. PROJECT_OPERATING_PROCEDURES.md §9 POP-07
5. COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md
6. exact current raw/derived artifacts only as needed
7. EVIDENCE_LEDGER_250_ONWARD.md when promoting/closing evidence
```

Do not reread the entire project history unless a concrete contradiction requires it.

---

## Stable Starting Point

Closed evidence currently canonically reaches:

```text
EV-250 Stage A/B compact equivalence sentinel
EV-251 raw8 Sprint production support
EV-252 native Goblin/BlackGoblin 1H/raw2
EV-253 native Demon 2H/raw3
EV-254 native Ogre Axe/raw52
EV-255 Orc broad native raw52
EV-256 Orc Staff/raw51
EV-257 Orc raw8 Fist Normal/Power
EV-258 Orc Hack vs FinishingAttack separation
```

Raw8 FIST production remains unchanged and proven across Normal, Power, Quick and Sprint scope.

---

## Raw55 Discovery Baseline

Baseline artifact:

`research/raw/2026.09.12_troll_collision_test.log`

Factual baseline already frozen into the probe contract:

```text
Troll / BlackTroll
RIGHT TrollFist / UseType55 / group5
LEFT  TrollFist / UseType55 / group5
Raw8Fist=<none>

observed native bookkeeping source:
RIGHT TrollFist 5 -> 7 offense
Game.dll+0x00069484 damage when contact occurs
RIGHT TrollFist 7 -> 5 cleanup
```

Do not infer damaging limb from RIGHT. Do not infer source side from animation-name `L/R`.

---

## Diagnostic Probe Implementation State

Frozen authority:

`docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`

Implementation commit:

`b1cea4904ca2ecb14d26c1e0d23cdab6e0a07e25` — `Add raw55 callback suppression diagnostic probe`

Probe shape:

```text
PhysicalFistProbe.cpp/.h
  temporary diagnostic-only causal probe
  exact factual raw55 eligibility
  temporary callback-suppression decision
  probe logging

EngineBridge
  remains sole hook owner
  diagnostic-only delegation seam

Raw8FistCollision
  unchanged
```

Deployment/startup evidence commit:

`70334d2642148c6d17f9683d800ab2bbe8cea492`

No production raw55 support has been implemented.

---

## Current Runtime Artifact

User committed the runtime test at:

`caaaa2ea00eae3954aa92f0ce567c5ea140a8b64` — `2026.09.12_troll_and_other_marker_test`

Artifact:

`research/raw/2026.09.12_troll_and_other_marker_test.log`

Identity:

```text
blob SHA: 6f8c58f5049382ef6d6c595c16b3ecb32a835b6e
size:     2,410,630 bytes
lines:    12,900 reported by commit stats
status:   UNPROCESSED — KEEP RAW until POP-07/POP-06 closure
```

### User visual/runtime observation

```text
marked Troll attacks could not hit/damage the Player at all
marked BlackTroll attacks could not hit/damage the Player at all

after defeating them, User summoned marked-control attackers:
Sabretooth -> worked as before
Golem      -> worked as before
```

This is strong supporting observation for the suppression hypothesis, but it is **not yet canonical PASS evidence** because the oversized log still needs targeted analysis.

---

## Exact First Responsibility in the Fresh Chat

Use POP-07 rather than attempting to pull/read the full 2.4 MB artifact into Chat.

The causal-probe contract requires targeted verification of the following:

```text
1. locate RAW55_CALLBACK_SUPPRESSION_PROBE records for Troll/BlackTroll
2. correlate each suppression with actor, family, action, motion and C1 generation
3. verify the factual raw55 RIGHT source was group5 at suppression eligibility
4. verify suppressed marked raw55 executions do not receive the old pre-marker TrollFist 5 -> 7 native activation
5. verify no raw55 Troll/BlackTroll damage event contradicts suppression during those marked executions
6. verify authored FIST is still reached and remains current raw55 unsupported/missing-source behavior in the probe
7. verify animation/state/recover/next-attack progression remains healthy across later generations
8. verify Sabretooth marked raw8 control remains healthy
9. verify Golem marked control remains healthy
10. check for C1 invariant warning, repair divergence, lifecycle issue, unexpected replacement/outstanding state, or other probe-caused anomaly
```

If the connector cannot retrieve the oversized canonical log directly, follow POP-07 and use the deterministic `tools/log_evidence/` derived-package procedure. Do not modify the canonical raw.

### Decision after analysis

If the evidence supports all frozen PASS conditions:

```text
promote exact reusable result to EVIDENCE_LEDGER_250_ONWARD.md
-> give the artifact explicit disposition
-> archive it when no longer needed as active comparison
-> close any linked September 12 evidence-maintenance debt
-> then Normal Chat may freeze a permanent PhysicalFistCollision production contract
```

A PASS still does not authorize production implementation in the same step. Production must be a separate frozen Work task, and the temporary `PhysicalFistProbe` must be removed rather than normalized into production.

If suppression broke progression, lost a necessary native side effect, altered controls, or produced lifecycle contradiction, return to design. Do not patch compensating behavior into `EngineBridge` or the temporary probe by improvisation.

---

## September 12 Evidence-Maintenance Debt

Before new causal work, Recovery Lock must also check whether these already-interpreted artifacts were promoted/archived:

```text
research/raw/2026.09.12_stalker_native_markers_test.log
  prior interpretation:
  Stalker factual It_Axe_SpikedClub_01 / raw52
  marked Normal + Power healthy 5 -> 7 -> 5
  useful native baseline for later Axe-separation Stalker compatibility

research/raw/2026.09.12_fall_down_damage.log
  prior interpretation:
  did not expose unresolved Fist/PhysicalFist source classification

research/raw/2026.09.12_blunt_arrow_bolt_test.log
  prior interpretation:
  BluntArrow factual UseType4
  BluntBolt factual UseType7
  neither is raw55
```

At the time this bridge was written, `EVIDENCE_LEDGER_250_ONWARD.md` still ended at EV-258. Therefore these are a known POP-06 closure obligation, not a reason to rerun them.

---

## What Remains Paused

Until raw55 probe interpretation/disposition is durable:

```text
NO broad native-creature certification continuation
NO permanent raw55 implementation
NO new raw55 hypothesis expansion
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```

Later intended sequence after raw55 closure remains:

```text
resume prepared native creature sweep
Axe separation: Hero/humans, Orc, Demon, Ogre, Stalker
Rapier separation: Hero/humans
Zombie-specific animation family
```

---

## Context-Limit Procedure Pointer

The procedure the User could not find is already in:

`docs/PROJECT_OPERATING_PROCEDURES.md`

Use:

```text
§13 POP-11 — Normal Chat Continuity and Interrupted-Context Recovery
```

Its key rule is Recovery Lock: after an abrupt/max-context failure, do not start new implementation, new runtime experiments, new Work tasks, or blindly follow an old NEXT pointer until current branch state, raw evidence disposition, canonical evidence promotion, and front-door handoff state are reconciled.
