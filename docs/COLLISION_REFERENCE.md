# Collision Reference

**Status:** Current factual reference  
**Updated:** 2026-09-20  
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

Evidence: EV-106–EV-116, EV-143–EV-147, EV-217–EV-220, EV-241–EV-244, EV-299–EV-306, EV-309–EV-314, EV-318.

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

Evidence: EV-180–EV-191, EV-197–EV-215, EV-299–EV-306.  
Architecture: `COLLISION_LIFECYCLE.md`.

## 4. Raw8 Fist

Factual `gEUseType_Fist` / raw8 is a native body-contact mechanism, not an equipped hand weapon.

Supported/proven marked families:

```text
Normal + Power + Quick + Sprint
```

Current behavior:

```text
unmarked raw8 Fist
-> completely native

marked supported raw8 execution
-> close SPU+0x164 opportunity once for the C1 before first FIST

each accepted G3AB_COL_FIST
-> SPU+0x164 1 -> 0
-> when needed, arm one exact bounded early timing permission
-> native Gothic path owns contact/target/damage
-> native attempt closes the latch to 1 whether or not damage succeeds
```

A later FIST in the same C1 can rearm another native contact opportunity. The marked raw8 mechanism is proven across human, Sabretooth/transformed Sabretooth, Wolf/transformed Wolf, Orc, Minecrawler, Bloodfly, Boar and Bison fixtures; it is source/mechanism behavior, not a human/species special case. EV-340 pairs the marked Wolf proof with an unmarked Wolf control showing factual Fist/raw8 remains completely native when no FIST marker is authored. EV-342–EV-345 further broaden native-creature coverage while preserving the same factual Fist/UseType8 rule.

There is no production `FIST_OFF`, no raw8 equipped-source window, no raw8 `ClearTriggeredList()` mechanism, and no direct/custom raw8 damage.

EV-346–EV-347 expose an active design correction: an early synthetic attempt can miss before the moving body reaches its target, and EV-347 proves the latch still closes on that miss. The agreed future author-facing semantic is therefore a persistent target-directed opportunity from FIST until successful contact or C1 termination; the mechanism remains under bounded causal research and is not yet production behavior.

Evidence: EV-221–EV-251, EV-257, EV-263, EV-297, EV-304–EV-305, EV-307, EV-309, EV-316, EV-337–EV-347.

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

Evidence: EV-262–EV-298, EV-317, EV-341.  
Architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.

### Audit disposition

Independent audit found no confirmed release-behavior defect. One hypothetical nested marker/callback attribution risk remains evidence-bounded with no source change; one diagnostics-only callback-identity surfacing omission was corrected without behavior change.

Evidence/current closure: EV-295–EV-298. Historical audit/probe documents are archived and are not ordinary retrieval material.

## 6. Sprint transport

SprintAttack is factual `gEAction_SprintAttack = 9`.

For the supported raw8 FIST path, Sprint arrives through the existing physical `OnAI_PowerAttack` transport while factual actor action is already Sprint at callback entry. The Power-named transport/motion does not redefine Sprint as Power.

The permanent raw55 path also supports Sprint-origin PhysicalFist/raw55 FIST behavior. Its immutable origin remains Sprint across the proven same-C1 factual `Action9 -> Action2` transition; later current Action2/POWER state does not transfer ownership to a true-Power execution.

Equipped Sprint RIGHT/LEFT/BOTH/OFF is now permanent supported behavior through `EquippedSprintCollision`.

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

Production acceptance is complete. EV-326 proves RIGHT->OFF->RIGHT across seven complete Goblin Sprint C1s on the permanent module; EV-327 proves missing-LEFT BOTH remains fail-closed with native fallback; EV-328 proves ordinary true Power remains isolated from Sprint ownership; EV-329 closes the diagnostics-free behavior-only product smoke. EV-325 is retained only as a safe mixed fixture that did not exercise its filename/intended RIGHT->OFF case.

Architecture decision: ADR-0003. Permanent owner: `EquippedSprintCollision`. The former `EquippedSprintProbe` was research scaffolding and is no longer active source.

Evidence: raw8 Sprint EV-250–EV-251 and protected sentinel EV-316; raw55 Sprint-origin EV-280–EV-285, EV-294, EV-298 and protected sentinel EV-317; equipped Sprint causal/promotion evidence EV-311, EV-315, EV-320–EV-329.

## 7. Shield / raw9 boundary

A factual LEFT shield/raw9 can be selected by `G3AB_COL_LEFT`, transition 5 -> 7, rearm, and later cleanly return 7 -> 5.

That physical activation **does not itself create a native shield-bash damage route**. In the tested Quick shield-bash fixture, nine accepted LEFT activations produced zero ONDAMAGE events.

Therefore current collision authoring does not claim shield-bash damage support. A future shield-bash feature requires separate damage-eligibility/dispatch research.

Evidence: EV-306, EV-308.

## 8. Key engine / hook facts

| Surface | Established role | Evidence / owner |
|---|---|---|
| `EngineBridge` | Sole physical owner of shared Gothic hooks/call-site transports; delegates semantic decisions to feature owners. | architecture through EV-215; `DESIGN.md` |
| `Game +0x16E180` motion-0 GetPlayTime call site | Exact bounded timing-permission transport used by production raw8 Fist; not a global GetPlayTime policy. | EV-221–EV-240; `SOURCE_HOOK_GUIDE.md` |
| `Game +0x16E348` | Observed native raw8 damage-dispatch caller return in tested path. | EV-221–EV-240 |
| `SPU+0x164` | Native raw8 contact-opportunity latch used by the proven marker mechanism. | EV-224–EV-240, EV-247–EV-251 |
| `SetCollisionGroup` transport | Physical collision-group mutation surface used by equipped/raw55 mechanisms; semantic ownership stays in feature/lifecycle modules. | EV-206–EV-207, EV-265–EV-298 |
| `eCTrigger_PS::ClearTriggeredList()` | Contact-bookkeeping rearm primitive; equipped repeated contacts and raw55 repeated-contact research use it under different ownership rules. | EV-106–EV-116, EV-266–EV-294 |

For exact RVAs, call stacks, hook signatures, and build-specific source facts, use `SOURCE_HOOK_GUIDE.md` and `COLLISION_CLEANUP_CALLSITE_MAP.md` before opening ledger prose.

## 9. Validation status

Focused raw55 acceptance is CLOSED/PASS at EV-298.

Standalone regression has closed the human marked-attack matrix. EV-299–EV-306 used Golem as a consistent target fixture while testing the human attack routes themselves. Sabretooth marked single-marker compatibility/Quick support is established through EV-247–EV-249, and its later same-C1 double-FIST control passed at EV-307.

```text
EV-299  human 1H                    PASS
EV-300  human 1H+torch              PASS
EV-301  human dual 1H               PASS
EV-302  human 2H                    PASS
EV-303  human Staff                 PASS
EV-304  human raw8 single FIST      PASS
EV-305  human raw8 double FIST      PASS
EV-306  human 1H+shield             PASS
EV-307  Sabretooth double FIST      PASS
EV-308  shield-bash LEFT/raw9       NEGATIVE CONTROL / DEFERRED
EV-309  Orc Staff + raw8 Fist       PASS
EV-310  Orc 2H animation set        PASS
EV-311  Goblin 1H/raw2              PASS + equipped-Sprint scope deferred
EV-312  Demon 2H/raw3               PASS
EV-313  Ogre Axe/raw52              PASS
EV-314  Stalker Axe/raw52           PASS
EV-315  Goblin equipped Sprint probe  CAUSAL PASS / promotion pending
EV-316  Sabretooth raw8 Sprint sentinel PASS
EV-317  Troll raw55 Sprint sentinel      PASS
EV-318  equipped 2H true-Power sentinel  PASS
EV-319  Ogre raw52 Sprint attempt          NOT EXERCISED / regression healthy
EV-320  Goblin Sprint RIGHT->OFF            CONTINUATION GAP / correction required
EV-321  Goblin Sprint BOTH missing LEFT     NEGATIVE PASS / native fallback
EV-322  Goblin Sprint RIGHT->OFF correction  PASS
EV-323  Goblin Sprint BOTH missing LEFT rerun PASS
EV-324  equipped 2H true-Power protected control PASS
EV-325  promoted right-off-named mixed fixture      NOT EXERCISED AS NAMED / safe
EV-326  promoted Sprint RIGHT->OFF->RIGHT           PASS
EV-327  promoted Sprint BOTH missing LEFT           NEGATIVE PASS
EV-328  promoted ordinary true-Power protection     PASS
EV-329  diagnostics-free behavior-only Sprint smoke PASS
EV-330  Orc Whirl RIGHT->OFF->RIGHT + player 1H recheck PASS
EV-331  Orc repeated-RIGHT/raw8 + player 1H+torch recheck PASS
EV-332  dual-1H player vs Ogre/raw52 mixed regression PASS
EV-333  player 1H vs Orc Raider/raw52 mixed regression PASS
EV-334  player 1H+shield vs Demon/raw3 mixed regression PASS
EV-335  player 2H vs Stalker/raw52 mixed regression PASS
EV-336  player raw8 Fist vs Goblin/raw2 + Sprint mixed regression PASS
EV-337  Sabretooth native+transformed double-FIST raw8 PASS
EV-338  Sabretooth native+transformed single-FIST raw8 PASS
EV-339  Wolf native+transformed marked raw8 PASS
EV-340  Wolf native+transformed unmarked raw8 fallback PASS
EV-341  Troll raw55 single/double + player Staff mixed regression PASS
```

Orc Phase 2 and weapon-using creature/NPC Phase 3 are CLOSED/PASS for their prepared regression scopes. Goblin/Demon/Ogre were deliberately rerun after raw55 integration and remain healthy; Stalker adds another current Axe/raw52 fixture. The equipped-Sprint scope discovered at EV-311 is now CLOSED/PASS as permanent behavior through EV-329.

EV-330–EV-331 additionally corroborate the accepted current build across Orc Whirl OFF-gap/reactivation, repeated-RIGHT rearm, Orc/player raw8, ordinary player 1H and player 1H+torch source separation. EV-332–EV-336 broaden that current-build regression across player dual-1H, single 1H, 1H+shield, 2H and raw8 Fist against Ogre/raw52, Orc Raider/raw52, Demon/raw3, Stalker/raw52 and Goblin/raw2, including permanent equipped Sprint under ordinary mixed combat. These are regression confirmations, not semantic extensions.

Phase 4 non-weapon creature regression is ACTIVE. EV-337–EV-341 establish the first current-build body-contact batch: Sabretooth raw8 single/double behavior in native and transformed-player form, Wolf marked raw8 plus paired unmarked native fallback in native/transformed form, and Troll permanent raw55 single/double behavior while the player uses Staff. More creature fixtures remain planned before Phase 4 closure. Current validation plan: `COLLISION_TEST_PLAN.md`.

## 10. Evidence escalation rule

Use the evidence chain only when needed:

1. `COLLISION_REFERENCE.md` for current fact.
2. Owning architecture/reference for exact current semantics.
3. `EVIDENCE_INDEX.md` for the relevant EV range.
4. The exact archived ledger entry for proof wording/provenance.
5. Raw/derived source only for disputed or missing details.

A settled fact should not require chronological evidence reconstruction during ordinary work.
