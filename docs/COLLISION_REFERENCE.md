# Collision Reference

**Status:** Current factual reference  
**Updated:** 2026-09-25  
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
| Attack execution identity | Collision marker occurrence/dedupe and equipped-source obligations use the monotonic C1 generation as the durable plugin execution identity. | EV-167, EV-206–EV-207, EV-213–EV-215 |
| Native action identity | Factual runtime action identity outranks animation filename naming. A PowerAttack-named motion may still be factual SprintAttack. | EV-250–EV-251 |
| Equipped source sides | RIGHT/LEFT mean Gothic equipped slots, not animation filename R/L metadata. | EV-090–EV-094, EV-143–EV-144 |
| Collision groups | Proven equipped offensive transition is Item_Equipped(5) -> Item_Attack(7); native/repair cleanup returns the exact source to Item_Equipped(5). | EV-019–EV-023, EV-206–EV-207 |
| Damage ownership | Authored collision controls physical/native opportunity timing; target selection/contact/damage dispatch remain Gothic-owned unless a separate feature explicitly proves otherwise. | EV-241–EV-244, EV-304–EV-308 |

## 2. Equipped marker model

Current equipped vocabulary:

```text
G3AB_COL_RIGHT -> exact desired active set {RIGHT}; RIGHT rearmed
G3AB_COL_LEFT  -> exact desired active set {LEFT}; LEFT rearmed
G3AB_COL_BOTH  -> exact desired active set {RIGHT, LEFT}; both rearmed
G3AB_COL_OFF   -> exact desired active set {}
```

Repeated RIGHT/LEFT/BOTH later in the same Hit can author another contact by rearming the selected source through `ClearTriggeredList()`. OFF creates an intra-Hit inactive gap; it is not terminal cleanup.

Supported/proven equipped attack scope currently includes Normal, Quick, full Whirl, Power, Pierce, SimpleWhirl, tested 2H/Staff Hack routes, and factual equipped Sprint under the permanent `EquippedSprintCollision` policy. Family-specific native target/reaction behavior remains native and is not normalized merely by marker support.

Evidence: EV-106–EV-116, EV-143–EV-147, EV-217–EV-220, EV-241–EV-244, EV-299–EV-306, EV-309–EV-314, EV-318, EV-370–EV-372, EV-375, EV-377.

## 3. Equipped lifecycle / terminal repair

Gothic receives its ordinary cleanup opportunity first. CollisionLifecycleGuard tracks only exact source obligations created by the current C1 generation.

Terminal repair is a fail-safe, not ordinary attack semantics:

```text
exact outstanding equipped source
+ exact current equipped-side identity proves liveness
+ actual group remains Item_Attack(7)
-> SetCollisionGroup(Item_Equipped) once
-> no ClearTriggeredList()
-> verify group 5
```

If native cleanup already fulfilled the obligation, repair does nothing. LEFT/RIGHT obligations remain independent.

Evidence: EV-180–EV-191, EV-197–EV-215, EV-299–EV-306, EV-367, EV-373–EV-374.  
Architecture: `COLLISION_LIFECYCLE.md`.

## 4. Raw8 Fist

Factual `gEUseType_Fist` / raw8 is a native body-contact mechanism, not an equipped hand weapon.

Supported/proven marked families:

```text
Normal + Power + Quick + Sprint
```

Current permanent behavior:

```text
unmarked raw8 Fist
-> completely native

marked execution begins
-> native permission closed for the exact C1

accepted FIST
-> one target-directed authored opportunity OPEN
-> exact bounded early timing permission applied when needed

native miss
-> opportunity stays OPEN
-> native one-shot latch is rearmed

first exact native contact dispatch
-> opportunity CONSUMED

later accepted FIST in same C1
-> may open a new opportunity, never stack opportunities

exact C1 finalization/replacement
-> unused opportunity CLOSED
```

Gothic remains authoritative for target selection, block/parry, immunity, reactions, knockdown/get-up vulnerability and HP damage. A native contact resolution consumes the opportunity even when resulting damage is zero.

There is no production `FIST_OFF`, no raw8 equipped-source window, no raw8 `ClearTriggeredList()` mechanism, and no direct/custom raw8 damage.

New Balance EV-377 reconfirms the persistent-opportunity model: a marked Sabertooth Sprint opportunity survives repeated native misses, can outlive the temporary timing permission, and closes only on exact native contact or C1 finalization as designed.

Evidence: EV-221–EV-251, EV-257, EV-263, EV-297, EV-304–EV-305, EV-307, EV-309, EV-316, EV-337–EV-364, EV-377.

## 5. PhysicalFist / raw55

Factual `gEUseType_PhysicalFist` / raw55 is a separate mechanism from raw8 Fist and equipped weapon collision.

Supported/proven marked families:

```text
Normal + Quick + true Power + Sprint-origin
```

Permanent behavior summary:

```text
eligible marked raw55 execution
-> suppress the premature native RIGHT 5 -> 7 opening for the supported route

first accepted authored FIST
-> perform the authored exact RIGHT 5 -> 7 opening
-> native target/contact/damage remains Gothic-owned

later accepted FIST in same C1
-> rearm contact bookkeeping only
-> do not issue another physical group opening

end of attack
-> Gothic retains native exact RIGHT 7 -> 5 cleanup
```

The production scope is exact current RIGHT PhysicalFist/raw55, marker-owned, evidence-bounded, and supports one or two authored FIST markers. It does not generalize to LEFT raw55, mixed equipped+FIST authoring, species-name rules, or direct damage.

Normal has a proven special native between-contact ALL-clear interaction; the permanent module suppresses/replaces only the exact evidence-backed native clear needed to preserve authored repeated-contact semantics.

### New Balance / AttackCollision compatibility — current reduced state

EV-376 identified a New Balance/AttackCollision StatePosition2 incompatibility in the pre-correction raw55 Power/Sprint-origin state gate. EV-377 established healthy equipped-Sprint and raw8 controls.

The first bounded correction was implemented in:

`6eb3e3ca96da55e89127c24d5f656e05610d315f`

EV-378 runtime validates all three predicates changed by that correction:

```text
true-Power first FIST:
  current POWER + explicit {SP1, SP2} + earlyOpeningSuppressed

true-Power second FIST:
  current POWER + explicit {SP1, SP2}

Sprint-origin later FIST:
  current POWER + explicit {SP1, SP2}
```

Representative EV-378 behavior:

```text
single-FIST true Power:
  first/only FIST at POWER/SP2 -> ACCEPTED
  exact RIGHT 5 -> 7
  native damage observed when contact connects
  native 7 -> 5 cleanup / outstanding zero

double-FIST true Power:
  marker1 POWER/SP1 -> ACCEPTED/open
  marker2 POWER/SP2 -> ACCEPTED/clear-only rearm
  no second physical opening

Sprint-origin double-FIST:
  marker1 Action9/SPRINT/SP1 -> ACCEPTED/open
  same C1 becomes Action2/POWER
  marker2 POWER/SP2 -> ACCEPTED/clear-only rearm

Normal / Quick controls:
  healthy
```

EV-378 then established that Sprint-origin **first/only** FIST can remain factual `Action9 / SPRINT` and arrive at SP2. The bounded follow-up correction was implemented in:

`ce59e5a2bad564652eaba970e959bdef0b479d82`

Current Sprint-first predicate:

```text
current SPRINT / Action9
+ explicit {SP1, SP2}
+ earlyOpeningSuppressed mandatory
```

EV-379 validates that exact changed predicate at runtime. Repeated single-FIST Sprint-origin attacks remain factual `SPRINT / Action9 / SP2`, suppress the premature native opening, accept the authored FIST, open exact RIGHT raw55 `5 -> 7`, produce native damage when contact connects, and clean back `7 -> 5` with zero outstanding.

EV-379 additionally exposes a separate second-FIST timing split inside the same immutable Sprint-origin execution:

```text
proven route A:
  marker1 current SPRINT / SP1 -> ACCEPTED/open
  same C1 transitions to Action2 / POWER
  marker2 current POWER / SP2  -> ACCEPTED/clear-only rearm

newly observed route B:
  marker1 current SPRINT / SP1 -> ACCEPTED/open
  marker2 arrives before Action9 -> Action2 transition
  marker2 current SPRINT / SP2 -> currently REJECTED
  RIGHT is already group7
  native cleanup still returns 7 -> 5
```

Therefore the current unresolved compatibility question is no longer Sprint-first state acceptance. It is the complete factual state envelope for a legitimate **second** FIST under immutable Sprint origin. Current evidence proves `POWER/SP2` and proves that a legitimate marker2 can also arrive as `SPRINT/SP2`; it has not yet deliberately established whether marker2 can arrive as `SPRINT/SP1`.

The next step is diagnostic evidence gathering: move marker2 earlier, keep marker1 unchanged, and determine whether `SPRINT/SP1` belongs to the legitimate second-FIST set before freezing any follow-up implementation.

This evidence does not justify `StatePosition >= 1`, authored-count special cases, a generic Sprint-family rule, species/name gates, filename inference, DLL/version detection, new hooks/state/timers, custom damage, or neighboring-system changes.

Evidence: EV-262–EV-298, EV-317, EV-341, EV-366, EV-376–EV-379.  
Architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.  
Validation/investigation: `COLLISION_TEST_PLAN.md` §4.4 and `work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_STATE_INVESTIGATION.md`.

### Audit disposition

Independent audit found no confirmed release-behavior defect in the standalone environment. EV-376–EV-379 are later external-stack compatibility discoveries and do not reverse the standalone audit result.

Historical audit/probe documents are archived and are not ordinary retrieval material.

## 6. Sprint transport

SprintAttack is factual `gEAction_SprintAttack = 9`.

For raw8 Fist, Sprint arrives through the existing physical `OnAI_PowerAttack` transport while factual actor action is already Sprint at callback entry. The Power-named transport/motion does not redefine Sprint as Power. EV-377 confirms the same exact raw8 opportunity can remain valid through legitimate same-C1 factual `Action9 -> Action2` continuation under New Balance.

The permanent raw55 path also supports Sprint-origin PhysicalFist/raw55 FIST behavior. Its immutable origin remains Sprint across the proven same-C1 factual `Action9 -> Action2` transition; later current Action2/POWER state does not transfer ownership to a true-Power execution. EV-378 validates the corrected later-current-Power SP2 marker path. EV-379 validates Sprint-first `Action9/SPRINT/SP2` and proves that marker2 itself may occur either before or after the factual `Action9 -> Action2` transition. Factual current family therefore remains authoritative at each marker; the open question is the complete legitimate second-FIST state set for the same exact Sprint-origin execution.

Equipped Sprint RIGHT/LEFT/BOTH/OFF is permanent supported behavior through `EquippedSprintCollision`.

Permanent equipped-Sprint rule:

```text
origin = factual Action9 / Sprint Hit only
complete-motion activating markers required
FIST-mixed motion excluded
all sources required by the complete-motion mask must exist
eligible Sprint callback -> suppress native early OnAI_PowerAttack timing
authored RIGHT / LEFT / BOTH / OFF -> existing generic equipped marker semantics
exact bound Sprint origin may continue across the proven same-C1 Action9 -> Action2 transition
new ordinary true Power can never create or inherit Sprint origin
target/contact/damage remain Gothic-owned
```

The bound continuation is exact-identity-only: same actor, C1 generation, motion, required-source mask, required-source availability and exact required source identities. Current Action2/POWER remains factual and observable; it is not reclassified globally as Sprint.

Architecture decision: ADR-0003. Permanent owner: `EquippedSprintCollision`.

Evidence: raw8 Sprint EV-250–EV-251 and protected sentinel EV-316/EV-354; raw55 Sprint-origin EV-280–EV-285, EV-294, EV-298, EV-317, EV-376, EV-378–EV-379; equipped Sprint causal/promotion evidence EV-311, EV-315, EV-320–EV-329; New Balance controls EV-377.

## 7. Shield / raw9 boundary

A factual LEFT shield/raw9 can be selected by `G3AB_COL_LEFT`, transition 5 -> 7, rearm, and later cleanly return 7 -> 5.

That physical activation **does not itself create a native shield-bash damage route**. In the tested Quick shield-bash fixture, nine accepted LEFT activations produced zero ONDAMAGE events.

Therefore current collision authoring does not claim shield-bash damage support. A future shield-bash feature requires separate damage-eligibility/dispatch research.

Evidence: EV-306, EV-308.

## 8. Animation-family separation compatibility

Authored collision markers are not tied to the original Gothic animation-family token.

Final-source compatibility tests establish:

```text
marker present on separated animation
-> marker is detected on that animation
-> factual actor/action/source/UseType remains authoritative
-> supported ownership is accepted
-> exact equipped source activates/rearms according to the marker
-> ordinary cleanup returns the source to group 5

separated animation has no marker
-> no authored ownership is inferred from the old/native counterpart
-> native collision behavior remains in control
```

Proven environments:

- **Zombie Separation:** `Zombie_...` assets preserve factual Fist/raw8, Axe/raw52, Staff and 1H+shield source semantics.
- **Axe Separation:** native Axe users move from shared `*_2H_*` motions to `*_Axe_*` motions while factual Axe/UseType52 sources remain unchanged.
- **Rapier Separation:** `Hero_..._Rapier_...` motions drive factual `It_1H_Epee_01 / UseType2` correctly across Normal/Quick/Power/Pierce.

No tested case showed a present authored marker on a separated animation being ignored or misapplied. Genuinely unmarked replacement assets correctly stay native.

### Zombie + Axe combined asset coverage

EV-375 verifies the User's asset-gap remedy on `BenSala_Zombie_02`:

```text
copy corresponding zombie 2H animation asset
-> rename family token 2H -> Axe
-> runtime resolves Zombie_..._Axe_...
-> factual source remains It_Pickaxe / UseType52
-> authored markers operate normally
```

Therefore Zombie Separation and Axe Separation are not treated as fundamentally incompatible; the tested problem was an animation asset-coverage/naming gap.

Evidence: EV-369–EV-372, EV-375.

## 9. Key engine / hook facts

| Surface | Established role | Evidence / owner |
|---|---|---|
| `EngineBridge` | Sole physical owner of shared Gothic hooks/call-site transports; delegates semantic decisions to feature owners. | architecture through EV-215; `DESIGN.md` |
| `Game +0x16E180` motion-0 GetPlayTime call site | Exact bounded timing-permission transport used by production raw8 Fist; not a global GetPlayTime policy. | EV-221–EV-240; `SOURCE_HOOK_GUIDE.md` |
| `Game +0x16E348` | Observed native raw8 damage-dispatch caller return in tested path. | EV-221–EV-240 |
| `SPU+0x164` | Native raw8 contact-opportunity latch used by the proven marker mechanism. | EV-224–EV-240, EV-247–EV-251 |
| `SetCollisionGroup` transport | Physical collision-group mutation surface used by equipped/raw55 mechanisms; semantic ownership stays in feature/lifecycle modules. | EV-206–EV-207, EV-265–EV-298 |
| `eCTrigger_PS::ClearTriggeredList()` | Contact-bookkeeping rearm primitive; equipped repeated contacts and raw55 repeated-contact research use it under different ownership rules. | EV-106–EV-116, EV-266–EV-294 |

For exact RVAs, call stacks, hook signatures, and build-specific source facts, use `SOURCE_HOOK_GUIDE.md` and `COLLISION_CLEANUP_CALLSITE_MAP.md` before opening ledger prose.

## 10. Validation status

Current release-candidate collision status:

```text
focused raw55 acceptance                    CLOSED/PASS EV-298
human/equipped regression matrix            CLOSED/PASS EV-299–EV-336
permanent raw8 focused acceptance           CLOSED/PASS EV-355–EV-364
final-source Stage A body-contact           CLOSED/PASS EV-365–EV-366
supplemental destructive C1-R1 stress       PASS EV-367
final-source Stage B equipped/cumulative    CLOSED/PASS EV-368
separation compatibility                    CLOSED/PASS EV-369–EV-372
mixed stress / standalone final-source      CLOSED/PASS EV-373–EV-374
Zombie+Axe asset-gap remedy                 PASS EV-375
New Balance equipped/raw8 controls          PASS EV-377
first raw55 SP2 correction                  exact predicates RUNTIME PASS EV-378
Sprint-first SP2 correction                 exact predicate RUNTIME PASS EV-379
remaining raw55 contradiction               Sprint-origin second FIST may arrive current SPRINT/SP2
second-FIST complete state envelope         OPEN / diagnostic probe required
New Balance full intended-stack gate        OPEN
```

First compatibility correction:
`6eb3e3ca96da55e89127c24d5f656e05610d315f`

Sprint-first correction:
`ce59e5a2bad564652eaba970e959bdef0b479d82`

Latest reviewed/deployed diagnostic SHA256:
`490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C`

Current validation authority: `COLLISION_TEST_PLAN.md` plus the active bounded second-FIST investigation.

## 11. Evidence escalation rule

Use the evidence chain only when needed:

1. `COLLISION_REFERENCE.md` for current fact.
2. Owning architecture/reference for exact current semantics.
3. `EVIDENCE_INDEX.md` for the relevant EV range.
4. The exact archived/current ledger entry for proof wording/provenance.
5. Raw/derived source only for disputed or missing details.

A settled fact should not require chronological evidence reconstruction during ordinary work.
