# Gothic 3 Animation Behaviors — Evidence Ledger EV-417 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-10-04

## Purpose

Record evidence after the closed EV-389–EV-416 production/Speed/Raise volume.

This ledger is proof history, not the normal knowledge interface. Established facts belong in their current reference/architecture owners; `EVIDENCE_INDEX.md` routes proof-sensitive retrieval.

## Entries


### EV-417 — Independent full Speed + Raise audit: AttackCollision Hack coverage gap

Review fixture:
- G3AB reviewed at `d5d829e07eb2bfe8de428aa2ad148ba1f2d3835c`;
- Jackydima `gothic3sdk` pinned at `bbe769075bc896085a620a0ceb3491192c5beb61`;
- read-only formal audit using current Speed/Raise authorities and protected Collision boundary.

Major finding — pinned AttackCollision Hack route bypasses G3AB caller-side Hack composition:
- G3AB composes native Hack speed only at Script_Game callers `+0x42FF4`, `+0x431B4`, `+0x432EB`;
- pinned `Script_AttackCollision` replaces `_AI_HackAttack` rather than delegating to the native state;
- its replacement calls its own helper for Raise/Hit/Recover;
- that helper calls live `Script_Game+0x42A0` directly and then supplies the result to `sAICombatMoveInstr`;
- therefore the three native caller patches are not traversed and configured `Hack_BaseSpeed` is ignored on this replacement route.

Interpretation:
- this is a Speed transport-coverage gap, not a Collision defect and not evidence against the accepted `B*M -> C*M` algebra;
- New Balance compatibility remains statically sound on the inspected routes;
- AttackCollision compatibility is not complete until Hack coverage is corrected;
- EV-399/EV-410 remain valid for their exact fixtures and do not prove execution through this pinned replacement route.

Minor finding — arithmetic fail-closed edge:
- positive finite config values can underflow the composed float to `0`;
- current composition rejects non-finite results but not a zero/non-positive result created by arithmetic underflow;
- smallest fail-closed correction is to preserve the incoming compatible value when a positive compatible speed composes to a non-positive result.

Protected results:
- no Collision redesign/change is required or authorized;
- custom Normal/Quick/Whirl Raise, Power Raise composition, Sprint inheritance, Quick factual R/L, Finishing exclusion, modularity, simplicity and performance otherwise passed the audit.

Disposition:
- **FAIL — COMPLETE COMPATIBILITY STACK NOT READY FOR BUILD/RUNTIME ACCEPTANCE.**
- **NEXT — bounded static causal design for route-neutral Hack composition, then smallest Speed-owned correction.**


### EV-418 — Route-neutral Hack Speed composition mechanism frozen

Research fixture:
- G3AB `development` source at `362fbb46f10c99953448874b4736f2ebc35282c3`;
- Jackydima `gothic3sdk` pinned at `bbe769075bc896085a620a0ceb3491192c5beb61`;
- read-only causal research following EV-417.

Native Hack data flow:
- physical Raise: speed caller `Script_Game+0x42FF4`, Action14 / queried phase Hit, then CombatMove Raise;
- physical Hit: speed caller `+0x431B4`, Action14 / queried phase Hit, then CombatMove Hit;
- physical Recover: speed caller `+0x432EB`, Action14 / queried phase Hit, then CombatMove Recover;
- in each case the live `+0x42A0` result is copied into the request `AniSpeedScale` before the request reaches `Game+0x1696E0`.

Pinned AttackCollision replacement:
- replaces `_AI_HackAttack` and does not delegate to the native state;
- its Raise / Hit / Recover requests each call its helper;
- the helper calls live `Script_Game+0x42A0` with Action14 and queried phase Hit;
- each returned value becomes that request's `AniSpeedScale`;
- the replacement reaches the same `Game+0x1696E0` CombatMove entry.

Frozen correction:
```text
existing CombatMove hook
-> AttackRaise::RunCombatMove
-> stateless Hack Speed request adapter
-> unchanged InvokeCombatMove_FrameCollisionTest
-> original CombatMove
```

Hack Speed request eligibility:
- non-null request + non-null SPU + not FullStop;
- request Action exactly `gEAction_HackAttack`;
- physical phase string exactly `Raise`, `Hit` or `Recover`.

For an eligible request:
- use `request.SelfEntity`;
- resolve the existing Hack **Hit** profile identity;
- treat incoming `request.AniSpeedScale` as the already-computed compatible value `B*M`;
- apply existing composition as Hack/Hit: `compatible * (Hack_BaseSpeed / Hack_ReferenceHitBaseSpeed)`;
- forward a local request copy with only `AniSpeedScale` changed;
- never mutate the caller-owned request;
- never call `GetAnimationSpeedModifier` again.

Exactly-once requirement:
- remove G3AB Hack caller-side hook objects/installations at `+0x42FF4`, `+0x431B4`, `+0x432EB` in the same correction;
- leave the native call instructions themselves intact so Gothic/New Balance still computes the live result once;
- native and AttackCollision routes then each arrive uncomposed at the single request adapter;
- null CombatMove resumes bypass composition;
- no Speed state/cache/"already scaled" marker is added.

Compatibility:
- New Balance remains owner of live `+0x42A0`; G3AB consumes its returned value without reconstructing multipliers or repeating side effects;
- New Balance direct Hack Recover requests with their own compatible scale are composed once by the same boundary;
- factual Finishing / Action15 is excluded before profile lookup even when Hack and Finishing share an animation asset;
- AttackRaise contains no Hack AddRaise policy and remains upstream of the adapter;
- Collision invocation/lifecycle wrapper and all Collision modules remain unchanged.

EV-417 arithmetic guard:
- include as an independent fail-closed correction in `ComposeCompatibleSpeed`;
- after the existing finite-result check, if incoming `compatibleSpeed > 0` and the composed result is non-positive, return the original compatible value;
- do not clamp or alter zero/negative incoming live values by invention.

Implementation boundary:
- `AttackSpeed.cpp`: stateless Hack request-scale helper + underflow fail-closed guard;
- `AttackSpeed.h`: helper declaration;
- `EngineBridge.cpp`: thin copy-and-forward adapter, insert as AttackRaise transport, remove the three Hack speed caller hooks/registrations;
- no BehaviorProfiles, AttackRaise, INI or Collision edit;
- no new physical hook.

Disposition:
- **PASS — PRODUCTION CORRECTION MECHANISM FROZEN.**
- **NO NEW HOOK REQUIRED.**
- **NEXT — bounded implementation, independent source review, then focused native + intended-stack runtime acceptance.**
