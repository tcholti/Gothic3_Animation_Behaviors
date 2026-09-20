# Permanent raw8 Fist Architecture

**Status:** Frozen production architecture — behavior implementation promoted/static-reviewed; diagnostics correction + focused runtime acceptance pending  
**Updated:** 2026-09-20

## Purpose

Define the permanent diagnostics-independent behavior for factual `gEUseType_Fist` / raw8 after the EV-346–EV-354 causal and pre-Work sentinel closure.

Ordinary factual lookup: `COLLISION_REFERENCE.md`.  
Exact proof: `EVIDENCE_INDEX.md` → EV-346–EV-354.

---

## 1. Proven scope

Supported marked raw8 families remain Normal, Quick, true Power and Sprint-origin.

Applicability is factual: exact current Fist/raw8 source, supported factual attack family, valid current C1 generation, and a resolved marked Hit containing authored FIST. No species/name rule and no filename-derived family ownership. Unmarked raw8 remains native.

## 2. Permanent owner

`Raw8FistCollision` is the sole permanent owner of raw8 marker behavior/state. `EngineBridge` remains the sole physical hook owner and transports only exact native facts/delegations. `CollisionLifecycleGuard` remains the generic C1-generation authority and does not own raw8 opportunity policy.

The temporary `Raw8FistPersistentOpportunityProbe` is research scaffolding and must be deleted from the production candidate.

## 3. Author-facing semantic

```text
marked raw8 C1 begins -> native raw8 opportunity CLOSED
accepted FIST -> one authored target-directed opportunity OPEN
native miss while OPEN -> opportunity remains OPEN; restore Gothic one-shot eligibility
first exact native raw8 contact-resolution dispatch -> opportunity CONSUMED
later FIST in same C1 -> one opportunity OPEN again, never stacked
exact C1 finalization/replacement -> unused opportunity CLOSED
unmarked raw8 -> native
```

No raw8 `FIST_OFF` is part of the production design.

## 4. Permanent execution state

Reuse and extend the existing per-actor `Raw8FistMarkerExecution` in `Raw8FistCollision`. The execution record remains bound to actor instance, exact C1 generation, exact raw8 Fist source and exact SPU. It additionally owns a pending-opportunity bit/state and a separate timing-persistence substate.

Action/family/phase/motion are not terminal lifetime authority. The logical opportunity may survive same-C1 transport, including the proven Sprint-origin `Action9 / SPRINT -> Action2 / POWER`. In the tested raw8 Sabretooth route, Sprint is a factual Action9 state/origin that uses the same PowerAttack-named motion as Power; this is an action/family transition inside one motion/C1, not a Sprint-animation -> Power-animation asset transition. Animation/timing identity may retire only the timing helper without consuming the logical opportunity.

## 5. Marker-time behavior

Existing marked-C1 ownership remains: first factual marked raw8 ownership in the C1 writes `SPU+0x164 = 1` and creates the execution record with opportunity CLOSED.

`FrameCollisionMarkers` keeps the existing accepted-FIST latch transport: exact raw8 latch `-> 0` with confirmed readback.

After confirmed accepted FIST, `Raw8FistCollision` requires exact actor/C1/source/SPU execution identity, opens or refreshes one pending opportunity, retires any previous timing substate, and arms persistent pre-threshold timing only when the exact timing identity supports it.

Opening the logical opportunity must not require an immutable animation name. Animation identity governs timing only.

## 6. Persistent timing permission

Current one-shot marker timing becomes persistent only while the exact opportunity remains pending. For the exact primary `Game+0x16E180` timing call, matching actor/C1/source/SPU plus matching timing actor/motion and real play time below the stored forced value returns the same threshold+epsilon value already proven by raw8 timing research.

Do not mutate the real animation clock. Retire timing persistence once real time reaches/passes the stored forced value, on timing identity change, contact consumption, later-FIST refresh, C1 finalization/replacement, or factual actor/source/SPU invalidation. Timing retirement alone never consumes the logical opportunity.

## 7. Native miss persistence

`EngineBridge` wraps the existing `AICombatMoveInstr` original with a narrow permanent `Raw8FistCollision` invocation scope.

After native original, if the same exact opportunity is still pending, no exact contact dispatch consumed it, and native latch is `1`, write `1 -> 0`, verify readback, and keep the opportunity OPEN. No pending opportunity means no miss rearm. `FullStop` is not terminal authority.

## 8. Contact consumption boundary

The already-proven `gCEntity::OnDamage` hook becomes behavior-required pass-through transport. Consume before Gothic original only when: caller return is `Game.dll + 0x0016E348`; an exact raw8 invocation scope is active; Arg1 is the exact owned Fist source; Arg2 is the exact owned actor; actor/C1/source/SPU/current generation still match; source remains raw8; and opportunity is pending.

On exact dispatch entry: mark opportunity CONSUMED, retire timing, then call Gothic original exactly once with unchanged arguments.

Do **not** erase the C1 execution record on contact. A later FIST in the same C1 must be able to reopen another opportunity.

The API is named `OnDamage`, but production policy uses only exact native dispatch entry as the contact-resolution fact. Never inspect native result, HP delta, Parade/block, immunity, reaction or knockdown/get-up outcome. EV-349 is the policy-neutrality proof.

## 9. C1 finalization and replacement

At existing `AISetState` finalization: capture exact generation before native original; let Gothic run first; then ask `Raw8FistCollision` to finalize the captured generation before generic lifecycle record removal; recapture current generation before any raw8 latch mutation.

If current generation still equals captured generation, safely revalidate actor/SPU/source, close pending latch `-> 1`, retire timing and remove the raw8 execution record.

If generation is invalid or changed during native `AISetState`, retire only the stale old raw8 record/timing when it is still the stored old generation and perform **no latch write into the replacement generation**. This no-write branch is source-reviewed safety logic; EV-353 did not naturally execute it.

EV-353 also exercised factual generation replacement after FIST during reaction churn. Preserve the proven backup: when a stored raw8 execution is already stale before a later combat-move original, retire the old opportunity and close the exact live latch only under the same strict actor/SPU/source liveness conditions as the diagnostic probe.

Because that backup touches the shared latch after generation replacement, focused permanent acceptance must explicitly test `marked pending -> replacement/interruption -> later unmarked raw8` and prove native fallback is not suppressed. Do not invent a new Action/state-name taxonomy unless that regression exposes a contradiction.

## 10. Native ownership retained

Permanent raw8 does not own target selection, target/visited lists, contact geometry, block/parry/immunity, reactions, HP damage, custom OnDamage dispatch, `ClearTriggeredList`, collision groups, equipped windows or raw55 behavior. It restores native opportunity; it does not force contact.

## 11. Hook / bridge boundary

Behavior-required raw8 transport consists of existing attack callbacks, `StartEffect`, `AICombatMoveInstr`, `AISetState`, exact `Game+0x16E180` GetPlayTime call-site transport, and `gCEntity::OnDamage` entry filtered to exact caller `Game+0x16E348`.

`EngineBridge` owns each physical hook once. The OnDamage wrapper captures caller/arguments, delegates the exact raw8 fact to `Raw8FistCollision`, performs diagnostic logging only under `FRAME_COLLISION_DIAGNOSTICS`, and calls Gothic original exactly once unchanged. No raw8 state machine belongs in `EngineBridge`.

## 12. Release / diagnostic separation

The behavior-only twin contains the complete persistent-opportunity behavior, including the behavior-required OnDamage hook. The diagnostic twin contains the same behavior plus compact evidence. Production must not depend on `CollisionDiagnostics` or a temporary probe.

CORE should retain enough evidence for `RAW8_OPPORTUNITY_OPEN`, `RAW8_OPPORTUNITY_MISS_REARM`, `RAW8_OPPORTUNITY_CONTACT_CONSUMED` and `RAW8_OPPORTUNITY_CLOSE`. Repeated healthy timing holds may be compacted; rich threshold/address arithmetic remains diagnostic/deep.

## 13. Production exclusions

Do not add without new evidence: FIST_OFF, per-target raw8 lists, `EntitiesVisited` mutation, `ClearTriggeredList`, species/name rules, custom target selection, custom/direct damage, HP-outcome consumption logic, polling/timers, global animation-clock mutation, new Action/state-name cleanup taxonomy, raw55/equipped mechanism sharing, or new physical hooks beyond the proven transports above.

## 14. Focused acceptance before Phase 4 resumes

Focused permanent acceptance must include:

1. Gargoyle frame-3 Power: close, delayed-contact and no-contact/far cases;
2. marked human Normal and Power timing/contact;
3. later FIST in the same C1 reopening one opportunity without stacking;
4. ordinary no-contact C1 finalization;
5. post-FIST reaction/generation replacement with no old-opportunity leak;
6. marked pending -> replacement/interruption -> later **unmarked raw8** native fallback;
7. native unmarked human target-directed group control;
8. raw8 Sprint-origin same-C1 Action9 -> Action2 sentinel;
9. raw55 and equipped collision coexistence sentinels;
10. behavior-only/diagnostic behavior parity for raw8.

Only after focused permanent acceptance may Phase 4 broad creature regression resume.

## Implementation checkpoint

Production behavior was promoted in `3426cede41c0087e43edc0d81c825ff167e8e034` and independently static-reviewed by Normal Chat on 2026-09-20.

The behavior/state-machine implementation matches this architecture. A bounded diagnostics-only compaction/terminal-event correction remains open before build/runtime acceptance; it does not reopen behavior policy.

## 15. Evidence closure

The architecture is justified by EV-346–EV-354: early pulse failure, latch hit/miss behavior, successful post-miss rearm, policy-neutral contact dispatch, virtual-callback negative result, target-directed control, persistent-opportunity causal proof, and direct same-C1 Sprint Action9 -> Power Action2 token-survival proof.

EV-354 directly validates the protected Sprint-origin lifetime rule: 20 Sabretooth tokens opened under Action9/SPRINT on the PowerAttack-named motion and were consumed under Action2/POWER in the same C1; two of those tokens also survived an earlier native miss/rearm.

Unknown future contradictions return to an isolated probe under `FEATURE_DEVELOPMENT_METHOD.md`.