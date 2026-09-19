# Collision Reference

**Status:** Current factual reference  
**Updated:** 2026-09-19  
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

Supported/proven equipped attack scope currently includes Normal, Quick, full Whirl, Power, Pierce, SimpleWhirl and tested 2H/Staff Hack routes. Family-specific native target/reaction behavior remains native and is not normalized merely by marker support.

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
-> successful opportunity self-closes latch
```

A later FIST in the same C1 can rearm another native contact opportunity. The marked raw8 mechanism is proven across human, Sabretooth/transformed Sabretooth and Orc fixtures; it is source/mechanism behavior, not a human/species special case.

There is no production `FIST_OFF`, no raw8 equipped-source window, no raw8 `ClearTriggeredList()` mechanism, and no direct/custom raw8 damage.

Evidence: EV-221–EV-251, EV-257, EV-263, EV-297, EV-304–EV-305, EV-307, EV-309, EV-316.

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

Evidence: EV-262–EV-298, EV-317.  
Architecture: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.

### Audit disposition

Independent audit found no confirmed release-behavior defect. One hypothetical nested marker/callback attribution risk remains evidence-bounded with no source change; one diagnostics-only callback-identity surfacing omission was corrected without behavior change.

Evidence/current closure: EV-295–EV-298. Historical audit/probe documents are archived and are not ordinary retrieval material.

## 6. Sprint transport

SprintAttack is factual `gEAction_SprintAttack = 9`.

For the supported raw8 FIST path, Sprint arrives through the existing physical `OnAI_PowerAttack` transport while factual actor action is already Sprint at callback entry. The Power-named transport/motion does not redefine Sprint as Power.

The permanent raw55 path also supports Sprint-origin PhysicalFist/raw55 FIST behavior. Its immutable origin remains Sprint across the proven same-C1 factual `Action9 -> Action2` transition; later current Action2/POWER state does not transfer ownership to a true-Power execution.

These FIST mechanisms do not establish equipped Sprint marker semantics. Equipped Sprint RIGHT/LEFT/BOTH/OFF remains unsupported in the current production/behavior baseline. EV-315 proves the first Goblin Action9/SPRINT RIGHT/raw2 diagnostic handoff. EV-321 additionally proves the generic complete-motion required-source gate fails closed for Sprint BOTH when LEFT is absent and preserves native fallback. EV-320 exposed an execution-identity gap when a marker-owned Sprint C1 transitioned Action9 -> Action2 before later OFF. The bounded diagnostic correction was implemented at `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86` and the exact RIGHT->OFF runtime repair passed at EV-322: later OFF remained factually Action2/POWER, was authorized as bound Sprint-origin continuation, accepted, closed the exact RIGHT source 7 -> 5 and finalized cleanly. The missing-LEFT/BOTH negative rerun passed at EV-323 and the equipped true-Power protected control passed at EV-324. The bounded diagnostic Sprint-origin continuation correction is therefore runtime-accepted. Production promotion has now been explicitly approved by ADR-0003 and is frozen in `docs/work/active/COLLISION_EQUIPPED_SPRINT_PRODUCTION_PROMOTION.md`; the current behavior-only baseline still remains unsupported until that permanent extraction is implemented, independently reviewed and runtime-accepted.

Evidence: raw8 Sprint EV-250–EV-251 and protected sentinel EV-316; raw55 Sprint-origin EV-280–EV-285, EV-294, EV-298 and protected sentinel EV-317; equipped Sprint causal/continuation evidence EV-311, EV-315, EV-320–EV-324.

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
```

Orc Phase 2 and weapon-using creature/NPC Phase 3 are CLOSED/PASS for their prepared regression scopes. Goblin/Demon/Ogre were deliberately rerun after raw55 integration and remain healthy; Stalker adds another current Axe/raw52 fixture. EV-311's equipped Sprint rejection exposed a new scope question; EV-315 passes the first diagnostic causal handoff for that Goblin fixture without changing production support.

Phase 4 is temporarily held while the approved equipped-Sprint production promotion is extracted from diagnostic research into permanent behavior. The diagnostic causal case is CLOSED/PASS through EV-324; current production support is still pending the active promotion task. Current validation plan: `COLLISION_TEST_PLAN.md`.

## 10. Evidence escalation rule

Use the evidence chain only when needed:

1. `COLLISION_REFERENCE.md` for current fact.
2. Owning architecture/reference for exact current semantics.
3. `EVIDENCE_INDEX.md` for the relevant EV range.
4. The exact archived ledger entry for proof wording/provenance.
5. Raw/derived source only for disputed or missing details.

A settled fact should not require chronological evidence reconstruction during ordinary work.
