# Collision Reference

**Status:** Current factual reference  
**Updated:** 2026-09-24  
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

Evidence: EV-106–EV-116, EV-143–EV-147, EV-217–EV-220, EV-241–EV-244, EV-299–EV-306, EV-309–EV-314, EV-318, EV-370–EV-372, EV-375.

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

Evidence: EV-221–EV-251, EV-257, EV-263, EV-297, EV-304–EV-305, EV-307, EV-309, EV-316, EV-337–EV-364.

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

The current production scope is exact current RIGHT PhysicalFist/raw55, marker-owned, evidence-bounded, and supports one or two authored FIST markers. It does not generalize to LEFT raw55, mixed equipped+FIST authoring, species-name rules, or direct damage.

Normal has a proven special native between-contact ALL-clear interaction; the permanent module suppresses/replaces only the exact evidence-backed native clear needed to preserve authored repeated-contact semantics.

### Open New Balance / AttackCollision compatibility exception

EV-376 establishes one current incompatibility in the otherwise frozen raw55 implementation when the User's New Balance/AttackCollision environment is live:

```text
single-FIST true Power
-> exact raw55 execution remains valid
-> authored FIST may arrive at StatePosition=2
-> current frozen Power gate rejects it

double-FIST true Power
-> marker1 at SP1 accepted / damage possible
-> marker2 at SP2 rejected instead of clear-only rearm

Sprint-origin
-> marker1 Action9 / SPRINT / SP1 accepted
-> same C1 continues Action9 -> Action2
-> marker2 current POWER / SP2 rejected
```

This is **not** evidence for generic SP2 acceptance. The no-target equipped sweep, Goblin equipped control, Sabertooth raw8 control and human raw8 control remain healthy; generic dual-1H Power markers can already operate safely at SP2. The contradiction is therefore bounded to the raw55 Power/Sprint-origin state gate.

Frozen source remains unchanged. The evidence-bounded correction is pending and must not alter Normal, Quick, raw8, generic equipped behavior, C1 identity, or native final cleanup.

Evidence: EV-262–EV-298, EV-317, EV-341, EV-366, EV-376.  
Architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.

### Audit disposition

Independent audit found no confirmed release-behavior defect in the standalone environment. One hypothetical nested marker/callback attribution risk remains evidence-bounded with no source change; one diagnostics-only callback-identity surfacing omission was corrected without behavior change. EV-376 is a later external-stack compatibility contradiction, not a reversal of the standalone audit result.

Evidence/current closure: EV-295–EV-298, EV-376. Historical audit/probe documents are archived and are not ordinary retrieval material.

## 6. Sprint transport

SprintAttack is factual `gEAction_SprintAttack = 9`.

For the supported raw8 Fist path, Sprint arrives through the existing physical `OnAI_PowerAttack` transport while factual actor action is already Sprint at callback entry. The Power-named transport/motion does not redefine Sprint as Power.

The permanent raw55 path also supports Sprint-origin PhysicalFist/raw55 FIST behavior. Its immutable origin remains Sprint across the proven same-C1 factual `Action9 -> Action2` transition; later current Action2/POWER state does not transfer ownership to a true-Power execution. EV-376 reconfirms that identity model under New Balance: the origin remains Sprint when the later marker is observed at current Power/SP2; only the frozen SP1 state gate is contradicted.

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

Evidence: raw8 Sprint EV-250–EV-251 and protected sentinel EV-316/EV-354; raw55 Sprint-origin EV-280–EV-285, EV-294, EV-298, EV-317 and EV-376; equipped Sprint causal/promotion evidence EV-311, EV-315, EV-320–EV-329.

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

The earlier combined Zombie Separation + Axe Separation problem was specific to zombie 2H/Axe animation availability, not a collision incompatibility. EV-375 verifies the User's proposed remedy on `BenSala_Zombie_02`:

```text
copy corresponding zombie 2H animation asset
-> rename family token 2H -> Axe
-> runtime resolves Zombie_..._Axe_...
-> factual source remains It_Pickaxe / UseType52
-> authored markers operate normally
```

The tested copied/renamed assets cover marked Normal, Power and Whirl; Whirl `RIGHT -> OFF -> RIGHT` works with exact Pickaxe/raw52 activation/cleanup. An unmarked copied/renamed FinishingAttack/Hack asset remains native and cleans correctly. No anomaly/divergence/warning/error was observed and the diagnostic DLL unloaded cleanly.

Therefore Zombie Separation and Axe Separation are **not** treated as fundamentally incompatible. The known issue was an animation asset-coverage/naming gap for the tested special-zombie Axe route. This does not claim every possible special-zombie Axe asset is already supplied; missing assets still require corresponding animation coverage.

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
New Balance full intended-stack gate        BLOCKED/OPEN EV-376
raw55 Power/Sprint-origin SP2 remediation   CURRENT
```

Current validation authority: `COLLISION_TEST_PLAN.md`.

## 11. Evidence escalation rule

Use the evidence chain only when needed:

1. `COLLISION_REFERENCE.md` for current fact.
2. Owning architecture/reference for exact current semantics.
3. `EVIDENCE_INDEX.md` for the relevant EV range.
4. The exact archived/current ledger entry for proof wording/provenance.
5. Raw/derived source only for disputed or missing details.

A settled fact should not require chronological evidence reconstruction during ordinary work.
