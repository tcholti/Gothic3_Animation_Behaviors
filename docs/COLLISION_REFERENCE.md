# Collision Reference

**Status:** Current factual reference  
**Updated:** 2026-09-26  
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

Supported/proven equipped scope includes Normal, Quick, full Whirl, Power, Pierce, SimpleWhirl, tested 2H/Staff Hack, and factual equipped Sprint under permanent `EquippedSprintCollision` policy.

Evidence: EV-106–EV-116, EV-143–EV-147, EV-217–EV-220, EV-241–EV-244, EV-299–EV-306, EV-309–EV-314, EV-318, EV-370–EV-372, EV-375, EV-377.

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

If native cleanup already fulfilled the obligation, repair does nothing. LEFT/RIGHT obligations remain independent.

Evidence: EV-180–EV-215, EV-299–EV-306, EV-367, EV-373–EV-374.  
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

Permanent behavior:

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

### Final family state rules

```text
QUICK
  first: evidence-backed factual Quick states
  second: current QUICK; existing repeated-contact route

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
    OR current SPRINT + explicit SP2 only
```

No generic StatePosition range expression is used.

### Normal repeated-contact semantics — EV-382

Normal has a proven exact native between-contact clear caller:

`Script_Game.dll +0x386C6`

For marked Normal, that native clear is suppressed so authored marker2 owns the second-contact rearm.

EV-382 runtime-validates the final explicit `{SP0,SP1}` second-FIST rule. The decisive route is:

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

The current New Balance frame15 fixture can still place Normal marker2 at SP0; this does not invalidate SP1. SP1 remains explicitly accepted and was runtime-proven in the earlier Normal causal campaign.

Implementation: `a31c66b97e45c27d0739b7df51252d33f490e7e1`.  
Evidence: EV-277–EV-279, EV-286–EV-292, EV-380, EV-382.

### Power/Sprint New Balance compatibility

Runtime-confirmed corrections:

```text
6eb3e3ca96da55e89127c24d5f656e05610d315f
  Power first/second SP2
  Sprint-origin later current-Power SP2

ce59e5a2bad564652eaba970e959bdef0b479d82
  Sprint-origin first current-Sprint SP2

4c85193f4efd31e789bc07d7e3c71d31a9b5326e
  Sprint-origin second current-Sprint SP2
```

EV-380 proved Sprint marker2 can land on either side of the same-C1 Action9 -> Action2 transition. EV-381 proves the final asymmetric rule accepts both factual routes without adding Sprint/SP1.

Evidence: EV-376–EV-381.

### Native misses are not marker failure

EV-381 proves correct raw55 open/rearm/cleanup can coexist with zero `ONDAMAGE`; unmarked native raw55 windows can also miss completely. Therefore a visual miss does not by itself identify a G3AB collision defect.

The User's sheath/draw-associated miss observation is not a collision-marker blocker on current evidence. Do not add custom contact/damage policy for it without a new causal need.

### Focused raw55 disposition

**Focused raw55 Normal / Quick / true-Power / Sprint-origin compatibility is CLOSED/PASS for the tested intended New Balance route through EV-382.**

No further focused raw55 source change is currently indicated.

Architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.  
Evidence: EV-262–EV-298, EV-317, EV-341, EV-366, EV-376–EV-382.

## 6. Sprint transport

SprintAttack is factual `gEAction_SprintAttack = 9`.

For raw8, Sprint may use a Power-named physical transport while factual actor action is already Sprint. Filename/transport does not redefine factual family.

For raw55, immutable Sprint-origin identity survives the legitimate same-C1 Action9 -> Action2 continuation. EV-380–EV-381 prove authored marker2 may occur before or after that transition at SP2.

Equipped Sprint RIGHT/LEFT/BOTH/OFF is permanent supported behavior through `EquippedSprintCollision`. Its bound continuation is exact-identity-only; a new ordinary true Power execution cannot inherit Sprint authorization.

Evidence: raw8 EV-250–EV-251, EV-316, EV-354, EV-377; raw55 EV-280–EV-285, EV-294, EV-298, EV-317, EV-376–EV-381; equipped Sprint EV-311, EV-315, EV-320–EV-329, EV-368, EV-377.

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
focused raw55 New Balance compatibility      CLOSED/PASS
broader New Balance full-stack gate          OPEN
standalone post-compat raw55 sentinel        PENDING after New Balance full-stack
production collision migration               PENDING
```

Latest reviewed/deployed diagnostic SHA256:
`81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`

Current validation authority: `COLLISION_TEST_PLAN.md`.

## 11. Evidence escalation rule

1. `COLLISION_REFERENCE.md` for current fact.
2. Owning architecture/reference for exact current semantics.
3. `EVIDENCE_INDEX.md` for relevant EV range.
4. Exact archived/current ledger entry for proof wording/provenance.
5. Raw/derived source only for disputed or missing details.

A settled fact should not require chronological evidence reconstruction during ordinary work.
