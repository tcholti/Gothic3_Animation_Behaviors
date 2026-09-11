# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — RAW8 SPRINT CLOSED; NATIVE EQUIPPED-NPC CONTROLS NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_TEST_PLAN.md §8.1
4. EVIDENCE_LEDGER_250_ONWARD.md
5. WORK_IMPLEMENTATION_PROTOCOL.md only if a later bounded code task is frozen
```

---

## Closed Starting Point

```text
Stage A architecture refactor                 CLOSED/PASS
Stage B diagnostic refactor                   CLOSED/PASS
Stage A/B compact equivalence sentinel        CLOSED/PASS — EV-250
Sprint transport observability probe          CLOSED/PASS — 2026-09-11
production raw8 Sprint FIST support           CLOSED/PASS — EV-251
```

Stage A implementation:
`7c5874932cd6eafa5af3414c65a4442b3d74bb73`

Stage B implementation:
`5737db32e5eda76810989ddfb5659f8405c0c458`

Sprint production implementation:
`270d98f59fd7f83ab332d7cfbfc07d243273e0ca`

Validated Sprint diagnostic built/live SHA256:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`

Processed Sprint validation evidence:

```text
research/archive/2026.09.11_sprint_raw8_production_validation.log
```

---

## EV-251 Sprint closure

The focused production validation repeatedly demonstrated:

```text
Actor=Sabertooth
Action=9
Family=SPRINT
Phase=1
Motion=...PowerAttack_Hit...
C1 valid
Raw8Fist=Fist
Raw8UseType=8
InitialClose=0->1
Marker=FIST Result=ACCEPTED
StatePosition=1
Latch=1->0 LatchConfirmed=1
OwnershipMatched=1
EARLY_PERMISSION_ARMED / EARLY_PERMISSION_USED when required
C1 final Outstanding=0 PhysicalChanged=0 NO_OP_NO_OUTSTANDING
```

Whole-log targeted checks found no `REJECTED_UNSUPPORTED_HIT`, no `LIFECYCLE_ISSUE`, no surviving `SPRINT_TRANSPORT` probe records, and the diagnostic DLL unloaded cleanly.

This run did not independently capture an `ONDAMAGE` record with native Sabretooth Sprint as attacker, so EV-251 does not claim a new positive Sprint-contact damage sample. It also produced no contradictory damage-path evidence.

Sprint remains deliberately bounded to raw8 FIST. Equipped Sprint RIGHT/LEFT/BOTH/OFF remains unsupported unless factual equipped Sprint traffic appears.

Do not continue AI/distance-selection research merely to explain how Sprint is chosen.

---

## Next validation responsibility — native equipped-NPC marker controls

Authority:

```text
docs/COLLISION_TEST_PLAN.md §8.1
```

Run three separate logs:

```text
1. Goblin -> factual 1H / raw2
2. Demon  -> factual 2H / raw3
3. Ogre   -> factual Axe / raw52
```

Question:

```text
does established equipped marker ownership follow factual equipped source/action semantics
for native NPC attackers as well as already-proven player-side cases?
```

Keep one actor per log. Use the existing compact CORE diagnostic product. Do not add new probes unless a concrete failure or unsupported path makes existing CORE insufficient.

For each actor, seek the smallest useful marked attack/control fixture rather than a broad combat matrix. Preserve and commit each complete raw log unchanged before interpretation.

Do not yet begin:

```text
additional broad actor/family matrix
2H-vs-Axe mod compatibility
1H-vs-Rapier mod compatibility
final native mixed/stress regression
AttackContinuationProtection
Raise/speed/config work
```
