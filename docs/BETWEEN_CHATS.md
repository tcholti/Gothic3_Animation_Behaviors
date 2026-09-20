# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Phase 4 remains paused at raw8 FIST authoring-semantics research. Latest completed evidence: **EV-350**.

Active bounded Work task:

`docs/work/active/COLLISION_RAW8_TOUCHDAMAGE_CONTACT_BOUNDARY_OBSERVATION.md`

## Agreed ownership / terminology

```text
opportunity
= authored logical OPEN / CLOSED / rearmed state

collision/contact
= native physical/contact resolution

native hit/contact-resolution boundary
= factual Gothic boundary under research

damage
= literal Gothic API/log name or HP result only
```

The mod owns authored collision/contact opportunity and exact Hit/C1 lifetime. Gothic/behavior mods own block/parry/immunity/reactions/HP damage.

## Why this probe

Physical weapon/raw55 evidence shows native target-specific contact bookkeeping:

```text
target contacted
-> target enters visited/triggered bookkeeping
-> ClearTriggeredList rearms same-target contact
```

EV-233 proves raw8 `ClearTriggeredList()` is not its native control mechanism.

Static raw8 route:

```text
timing threshold
-> latch write at Game+0x16E1A3
-> multiple further target/contact checks
-> possible common exit Game+0x16E352
-> final gCEntity::OnDamage call returns at Game+0x16E348
```

Therefore the latch write is too early to mean accepted contact.

Candidate raw8-native TouchDamage boundaries already exist in the tested binary:

- `gCTouchDamage_PS::CanBeActivatedNow` — `Game+0x692F0`;
- `gCTouchDamage_PS::TriggerTarget` — `Game+0x693B0`.

Their participation in the raw8 combat-loop path is **not proven**. Historical N2B had `DeepDiagnostics: DISABLED`.

## Frozen observation

Implement actor-general, exact-raw8, diagnostic-only observation of those two boundaries.

No mutation:
- no latch write;
- no timing change;
- no list clear;
- no visited-state change;
- no group change;
- no suppression;
- no custom damage;
- no target change;
- no lifecycle change.

Correlate:
- frame-3 FIST;
- early timing opportunity;
- CanBeActivatedNow;
- TriggerTarget;
- read-only visited state;
- generic `CORE ONDAMAGE`;
- C1 finalization.

First runtime after review: same Gargoyle frame-3 fixture with close and far starts.

If the two TouchDamage callbacks are absent even in close cases while `CORE ONDAMAGE` occurs, rule them out for this raw8 combat-loop route and return to the `Game+0x16E1A3 -> +0x16E348` branch region.

## Current stop gate

The frozen task changed lifecycle-sensitive project state.

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require:

```text
Knowledge-state validation PASS
```

Only after PASS send the frozen task to Work.

`research/raw/` should contain only `Keep.txt`.
