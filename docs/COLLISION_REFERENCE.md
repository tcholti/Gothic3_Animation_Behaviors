# Collision Reference

**Status:** Current factual reference  
**Updated:** 2026-09-27  
**Purpose:** Compact projection of established Gothic 3 collision facts. Read this before opening evidence ledgers for an already-researched collision question.

> This file states **what is currently established**. It is not the proof record. Each claim routes to EV evidence; open the ledger/raw source only when exact provenance, qualification, contradiction, or re-interpretation matters.

## Retrieval rule

```text
ordinary collision question
-> COLLISION_REFERENCE.md
-> owning architecture/reference only when needed
-> EVIDENCE_INDEX.md
-> exact EV ledger entry
-> archived raw/derived source only for verification or contradiction
```

Do not reconstruct settled behavior from chronological evidence by default.

## 1. Core identities

| Fact | Current established meaning | Evidence |
|---|---|---|
| Attack execution identity | Collision marker occurrence/dedupe and equipped-source obligations use monotonic C1 generation as durable plugin execution identity. | EV-167, EV-206–EV-207, EV-213–EV-215 |
| Native action identity | Factual runtime action identity outranks animation filename naming. A PowerAttack-named motion may be factual SprintAttack. | EV-250–EV-251 |
| Equipped source sides | RIGHT/LEFT mean Gothic equipped slots, not filename R/L metadata. | EV-090–EV-094, EV-143–EV-144 |
| Collision groups | Proven equipped/raw55 offensive transition is Item_Equipped(5) -> Item_Attack(7); ordinary cleanup returns exact source to 5. | EV-019–EV-023, EV-206–EV-207 |
| Damage ownership | Authored collision owns physical/native opportunity timing; target selection/contact/damage remain Gothic-owned unless separately proven. | EV-241–EV-244, EV-304–EV-308, EV-381–EV-382 |

## 2. Equipped marker model

Current equipped vocabulary:

```text
G3AB_COL_RIGHT -> exact desired active set {RIGHT}; RIGHT rearmed
G3AB_COL_LEFT  -> exact desired active set {LEFT}; LEFT rearmed
G3AB_COL_BOTH  -> exact desired active set {RIGHT, LEFT}; both rearmed
G3AB_COL_OFF   -> exact desired active set {}
```

Repeated RIGHT/LEFT/BOTH later in the same Hit can author another contact by rearming the selected source through `ClearTriggeredList()`. OFF creates an intra-Hit inactive gap; it is not terminal cleanup.

Supported/proven equipped scope includes Normal, Quick, full Whirl, Power, Pierce, SimpleWhirl, tested 2H/Staff Hack, and factual equipped Sprint under permanent `EquippedSprintCollision` policy. EV-383 additionally proves a four-marker `BOTH -> single side -> OFF -> BOTH` pattern forming three independently controlled offensive windows in representative dual-1H Normal/Quick/SimpleWhirl/Pierce executions.

Evidence: EV-106–EV-116, EV-143–EV-147, EV-217–EV-220, EV-241–EV-244, EV-299–EV-306, EV-309–EV-314, EV-318, EV-370–EV-375, EV-377, EV-383.

## 3. Equipped lifecycle / terminal repair

Gothic receives its ordinary cleanup opportunity first. `CollisionLifecycleGuard` tracks only exact source obligations created by the current C1 generation.

Terminal repair is fail-safe, not ordinary attack semantics:

```text
exact outstanding equipped source
+ exact current equipped-side identity proves liveness
+ actual group remains Item_Attack(7)
-> SetCollisionGroup(Item_Equipped) once
-> no ClearTriggeredList()
-> verify group5
```

If native cleanup already fulfilled the obligation, repair does nothing. LEFT/RIGHT obligations remain independent. EV-384 broad New Balance stress evidence includes single- and dual-source bounded repairs converging exact outstanding group7 sources to group5 without sampled repair divergence.

Evidence: EV-180–EV-215, EV-299–EV-306, EV-367, EV-373–EV-374, EV-384.  
Architecture: `COLLISION_LIFECYCLE.md`.

## 4. Raw8 Fist

Factual `gEUseType_Fist` / raw8 is a native body-contact mechanism, separate from equipped weapon and raw55 behavior.

Supported marked families:

```text
Normal + Power + Quick + Sprint
```

Permanent behavior:

```text
unmarked raw8
-> completely native

marked execution
-> native permission closed for exact C1

accepted FIST
-> one target-directed authored opportunity OPEN
-> bounded timing permission when required

native miss
-> opportunity stays OPEN
-> native one-shot latch rearmed

first exact native contact dispatch
-> opportunity CONSUMED

later accepted FIST same C1
-> may open a new opportunity; opportunities do not stack

C1 finalization/replacement
-> unused opportunity CLOSED
```

Gothic remains authoritative for target selection, block/parry, immunity, reactions and HP damage. No production `FIST_OFF`, no raw8 equipped-source window, no raw8 `ClearTriggeredList()` route and no custom raw8 damage.

EV-377 reconfirms this model under New Balance, including legitimate same-C1 Sprint Action9 -> Action2 continuation.

Evidence: EV-221–EV-251, EV-257, EV-263, EV-297, EV-304–EV-305, EV-307, EV-309, EV-316, EV-337–EV-364, EV-377.

## 5. PhysicalFist / raw55

Factual `gEUseType_PhysicalFist` / raw55 is separate from raw8 Fist and equipped weapon collision.

Supported marked families:

```text
Normal + Quick + true Power + Sprint-origin
```

Permanent mechanism:

```text
eligible marked execution
-> selectively suppress evidence-backed premature native RIGHT 5 -> 7 opening

first accepted FIST
-> exact current RIGHT raw55 5 -> 7
-> Gothic owns target/contact/damage

later accepted FIST same C1
-> ClearTriggeredList/rearm only
-> no second physical opening

end
-> Gothic native exact RIGHT 7 -> 5 cleanup first
```

Scope remains exact current RIGHT PhysicalFist/raw55, marker-owned, 1 or 2 FIST markers, no LEFT raw55 generalization, no mixed equipped+FIST authoring, no species/name/file inference and no custom damage.

### Current final-candidate family state gates

```text
QUICK
  first: evidence-backed factual Quick states
  second: current QUICK; established repeated-contact route

NORMAL
  first: current NORMAL, evidence-backed SP0/SP1 first-marker route
  second: current NORMAL + explicit SP0 OR SP1

TRUE POWER
  first: current POWER + explicit SP1 OR SP2 + earlyOpeningSuppressed
  second: current POWER + explicit SP1 OR SP2

SPRINT ORIGIN
  first: current SPRINT + explicit SP1 OR SP2 + earlyOpeningSuppressed
  second:
    current POWER  + explicit SP1 OR SP2
    OR current SPRINT + explicit SP1 OR SP2
```

No generic StatePosition range such as `>=1` is authorized.

### Normal repeated-contact semantics — EV-382

Normal has a proven exact native between-contact clear caller:

`Script_Game.dll +0x386C6`

For marked Normal, that native clear is suppressed so authored marker2 owns the second-contact rearm.

EV-382 runtime-validates explicit `{SP0,SP1}` second-FIST acceptance. The decisive route is:

```text
marker1 NORMAL/SP0 -> accepted / 5 -> 7 / initial clear
native hit1 occurs
marker2 still NORMAL/SP0 -> ACCEPTED
marker2 ClearTriggeredList=1
marker2 GroupRequested=0
RIGHT remains group7
later native hit2 may occur
native cleanup 7 -> 5 / Outstanding=0
```

Very-early marker2 before hit1 is also accepted. It may clear an empty visited list and does not guarantee two damage events. This requires no hit1 flag, visited-target check, delay, queue or timer.

Evidence: EV-277–EV-279, EV-286–EV-292, EV-380, EV-382.

### Sprint-origin compatibility state — EV-381, EV-385, EV-386

New Balance compatibility evidence established:

```text
Sprint-origin first current SPRINT/SP2 is legitimate
Sprint-origin second current SPRINT/SP2 is legitimate
Sprint-origin second after same-C1 transition current POWER/SP1/SP2 is legitimate
```

EV-385 added the previously missing standalone factual state:

```text
Sprint-origin marker1 current SPRINT/SP1 -> accepted/open
Sprint-origin marker2 may still be current SPRINT/SP1 in the same C1/source/origin
```

The pre-correction source rejected that marker2 as `REJECTED_UNSUPPORTED_HIT`, while cleanup stayed safe. This froze the explicit correction:

```text
Sprint-origin second FIST:
  current POWER  -> SP1 OR SP2
  current SPRINT -> SP1 OR SP2
```

Source `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0` implements exactly that one-predicate change. Independent source review confirms the second-FIST branch remains clear-only and cannot request a second physical opening.

EV-386 runtime-validates the correction on the final candidate. Repeated standalone `1+3` Sprint-origin executions accept marker1 at `SPRINT/SP1`, then accept marker2 in the same C1 while still `SPRINT/SP1` with `GroupRequested=0` and `ClearTriggeredList=1`; ordinary cleanup returns raw55 RIGHT group7 -> group5 with `Outstanding=0`. The same batch preserves `SPRINT/SP1 -> POWER/SP1` continuation behavior and runtime-validates factual true-Power single and double marked controls.

Evidence: EV-280–EV-285, EV-294, EV-376–EV-381, EV-385–EV-386.

### Native misses are not marker failure

EV-381 proves correct raw55 open/rearm/cleanup can coexist with zero `ONDAMAGE`; unmarked native raw55 windows can also miss completely. Therefore a visual miss does not by itself identify a G3AB collision defect.

The User's sheath/draw-associated miss observation is not a collision-marker blocker on current evidence. Do not add custom contact/damage policy for it without a new causal need.

### Current raw55 disposition

Focused New Balance raw55 compatibility remains CLOSED/PASS through EV-382, and broad intended-stack New Balance compatibility is CLOSED/PASS through EV-384.

The EV-385 standalone current-SPRINT/SP1 eligibility defect is **CLOSED by EV-386**. The corrected marked standalone final-candidate matrix, including factual true-Power single/double controls, is PASS. The only unfinished standalone diagnostic sentinel item is one representative **unmarked raw55 native-fallback** control. The already-run New Balance final-candidate batch remains unpublished/unreviewed and follows after that standalone control.

Architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.  
Evidence: EV-262–EV-298, EV-317, EV-341, EV-366, EV-376–EV-386.

## 6. Sprint transport

SprintAttack is factual `gEAction_SprintAttack = 9`.

For raw8, Sprint may use a Power-named physical transport while factual actor action is already Sprint. Filename/transport does not redefine factual family.

For raw55, immutable Sprint-origin identity survives the legitimate same-C1 Action9 -> Action2 continuation. EV-380–EV-381 prove authored marker2 may occur before or after that transition under New Balance at SP2; EV-385–EV-386 prove standalone marker2 may legitimately remain Action9/SPRINT at SP1 and is now accepted by the corrected final candidate.

Equipped Sprint RIGHT/LEFT/BOTH/OFF is permanent supported behavior through `EquippedSprintCollision`. Its bound continuation is exact-identity-only; a new ordinary true Power execution cannot inherit Sprint authorization.

Evidence: raw8 EV-250–EV-251, EV-316, EV-354, EV-377; raw55 EV-280–EV-285, EV-294, EV-298, EV-317, EV-376–EV-386; equipped Sprint EV-311, EV-315, EV-320–EV-329, EV-368, EV-377.

## 7. Shield / raw9 boundary

A factual LEFT shield/raw9 can be selected by `G3AB_COL_LEFT`, transition 5 -> 7, rearm, and later cleanly return 7 -> 5.

Physical activation does **not** itself prove a native shield-bash damage route. The tested Quick shield-bash fixture produced accepted LEFT activations with zero ONDAMAGE.

Current collision authoring therefore does not claim shield-bash damage support.

Evidence: EV-306, EV-308.

## 8. Animation-family separation compatibility

Authored markers are not tied to original Gothic animation-family tokens.

Established rule:

```text
marker present on separated animation
-> marker detected on that animation
-> factual actor/action/source/UseType remains authoritative
-> supported ownership accepted
-> ordinary cleanup remains native

replacement animation unmarked
-> no authored ownership inferred from old/native counterpart
-> native behavior remains in control
```

Proven environments: Zombie Separation, Axe Separation, Rapier Separation, plus EV-375 Zombie+Axe copied/renamed asset-gap remedy.

Evidence: EV-369–EV-375.

## 9. Key engine / hook facts

| Surface | Established role |
|---|---|
| `EngineBridge` | Sole physical owner of shared Gothic hooks/call-site transports; semantic decisions delegated to feature owners. |
| `Game +0x16E180` motion-0 GetPlayTime call site | Exact bounded raw8 timing-permission transport; not global GetPlayTime policy. |
| `Game +0x16E348` | Observed native raw8 damage-dispatch caller return. |
| `SPU+0x164` | Native raw8 contact-opportunity latch used by proven marker mechanism. |
| `SetCollisionGroup` transport | Physical mutation surface used by equipped/raw55 mechanisms; semantic ownership remains in feature/lifecycle modules. |
| `eCTrigger_PS::ClearTriggeredList()` | Contact-bookkeeping rearm primitive used under family/feature-specific ownership rules. |
| `Script_Game.dll +0x386C6` | Exact Normal raw55 native between-contact clear caller selectively suppressed for marked Normal ownership. |

Exact RVAs/call stacks/signatures: `SOURCE_HOOK_GUIDE.md` and `COLLISION_CLEANUP_CALLSITE_MAP.md`.

## 10. Validation status

```text
focused raw55 standalone acceptance          CLOSED/PASS EV-298
human/equipped regression                    CLOSED/PASS EV-299–EV-336
permanent raw8 focused acceptance            CLOSED/PASS EV-355–EV-364
final-source standalone campaign             CLOSED/PASS EV-365–EV-374
Zombie+Axe asset-gap remedy                  PASS EV-375
New Balance equipped/raw8 controls           PASS EV-377
raw55 Power/Sprint compatibility             PASS EV-378–EV-381
raw55 Normal SP0 compatibility               PASS EV-382
focused raw55 New Balance compatibility      CLOSED/PASS EV-382
dual-1H multi-window authoring               PASS EV-383
broader New Balance full-stack gate          CLOSED/PASS EV-384
standalone Sprint/SP1 defect                 FOUND EV-385 / CLOSED EV-386
corrected marked standalone raw55 matrix     PASS EV-386
unmarked raw55 final-candidate fallback      PENDING
final-candidate New Balance regression       RUN LOCALLY / LOGS PENDING REVIEW
behavior-only release-purity validation      PENDING
production collision migration               BLOCKED
```

Final-candidate hashes:

```text
Behavior   D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78
Diagnostic AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
```

Current validation authority: `COLLISION_TEST_PLAN.md`.

## 11. Evidence escalation rule

1. `COLLISION_REFERENCE.md` for current fact.
2. Owning architecture/reference for exact current semantics.
3. `EVIDENCE_INDEX.md` for relevant EV range.
4. Exact archived/current ledger entry for proof wording/provenance.
5. Raw/derived source only for disputed or missing details.

A settled fact should not require chronological evidence reconstruction during ordinary work.