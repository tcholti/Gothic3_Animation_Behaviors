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


### EV-419 — EV-418 Hack compatibility implementation independent source review PASS

Reviewed production source:
- implementation commit `41ed80c6420e5236d13fc037cb5923b946cb8ccc`;
- base `1d4f73dbf3a519fe97dd15d7bf5d6253b9059015`;
- exactly one source commit; exactly three changed files: `AttackSpeed.cpp`, `AttackSpeed.h`, `EngineBridge.cpp`.

Implementation result:
- `AttackSpeed::TryComposeHackCombatMoveSpeed` accepts only factual Action14 with physical phase string `Raise`, `Hit` or `Recover`;
- it delegates to existing `ComposeCompatibleSpeed(actor, Hack, Hit, request.AniSpeedScale)`, preserving the existing Hack Hit-profile identity and `C/B` algebra;
- `EngineBridge::InvokeCombatMove_WithHackSpeed` passes FullStop/null args/null SPU unchanged, otherwise copies eligible requests locally and changes only `AniSpeedScale`;
- the caller-owned request is not mutated;
- the adapter delegates directly to the existing original-function Collision transport and cannot recurse through the public CombatMove hook;
- no extra `GetAnimationSpeedModifier` call, Speed state, cache or already-composed marker exists.

Hook/static checks:
- the three old Hack speed hook declarations/installations `+0x42FF4`, `+0x431B4`, `+0x432EB` are absent;
- remaining Speed registrations are exactly the previous set minus those three: 12 Hit callers plus Power Raise `+0x47D51` = 13 registrations;
- exactly one physical G3AB `sAICombatMoveInstr` hook remains;
- `AttackRaise.cpp` blob SHA is byte-identical before/after the implementation;
- the complete `InvokeCombatMove_FrameCollisionTest` Collision wrapper body is text-identical before/after the implementation;
- no Collision module or lifecycle owner changed.

Exactly-once / compatibility result:
- native Hack's original three speed calls now reach the live Gothic/New Balance owner normally and place the uncomposed live result into the CombatMove request;
- pinned AttackCollision replacement Hack does the same through its own helper;
- both routes converge on the one factual Action14 request adapter, which applies `C/B` once;
- null resumes bypass the adapter;
- factual Finishing / Action15 is rejected before profile composition;
- New Balance remains the sole live `+0x42A0` policy owner and its contextual result/side effects are not reproduced or repeated.

Arithmetic fail-closed:
- after existing finite-result validation, positive incoming compatible speed that composes to a non-positive value now falls back to the original compatible value;
- no clamp or configuration semantic change was introduced.

Engineering review:
- simplicity PASS: three route-specific Hack hooks removed; no new physical hook;
- modularity PASS: AttackSpeed owns eligibility/composition; EngineBridge owns thin transport; AttackRaise/Collision ownership unchanged;
- performance PASS: one bounded Action14 request check at the existing CombatMove boundary; no polling/scanning/additional speed-owner call.

Independent disposition:
- BLOCKER = 0;
- MAJOR = 0;
- MINOR = 0;
- **PASS — SOURCE READY FOR USER-LOCAL BUILD / DEPLOY / FOCUSED RUNTIME ACCEPTANCE.**

Runtime remains required for both the EV-415 Raise phase-speed correction and the EV-418 native + pinned AttackCollision Hack compatibility route.


### EV-420 — Current production native build/deploy + Raise/Hack runtime PASS

Fixture:
- production source: `41ed80c6420e5236d13fc037cb5923b946cb8ccc`;
- documentation/head at local synchronization: `467f5656b7dbaebb81b93c52ae0499da94b9dc41`;
- User-local Release build of `Script_G3AnimationBehaviors`;
- native-only runtime fixture: `Script_NewBalance.dll` and `Script_AttackCollision.dll` absent;
- temporary user-facing speed contrast: tested authored attack speeds at `0.1` and `1.0`.

Build/deployment:
```text
Built SHA256 = 3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
Live  SHA256 = 3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
live selected G3AB product = Script_G3AnimationBehaviors.dll
length = 462336 bytes
POP-03 production deployment = PASS
```

User visual/runtime observations:
- 2H Normal: tested at 0.1 and 1.0; Raise followed authored speed together with Hit;
- 2H Quick: tested at 0.1 and 1.0; Raise followed authored speed together with Hit;
- 2H Power: tested at 0.1 and 1.0; Raise followed authored speed together with Hit;
- 2H Whirl: tested at 0.1 and 1.0; Raise followed authored speed together with Hit;
- 2H Hack: tested at 0.1 and 1.0; Raise followed authored speed together with Hit;
- 1H Power: tested at 0.1 and 1.0; Raise followed authored speed together with Hit;
- 1H Pierce: tested at 0.1 and 1.0; Raise followed authored speed together with Hit.

Interpretation:
- EV-415 custom AddRaise phase-speed correction is runtime-positive on tested 2H Normal/Quick/Whirl;
- native Power phase-speed coupling is runtime-positive on tested 2H and 1H routes;
- Pierce remains a positive whole-attack control;
- EV-418 route-neutral Hack adapter is runtime-positive on the native 2H Hack route across a strong 0.1-versus-1.0 contrast;
- no evidence of ignored Hack authoring or obvious double composition was reported on the native route.

Limit:
- the observation establishes that Power Raise changes with authored Power speed; this batch does not independently quantify whether the native/live Raise-vs-Hit relative phase ratio (for example the established 1.5*M vs 1.0*M relationship) remained numerically distinct;
- pinned New Balance + AttackCollision Hack compatibility remains untested on this source and is the next required gate.

Disposition:
- **PASS — NATIVE BUILD/DEPLOY + FOCUSED PHASE-SPEED/HACK RUNTIME ACCEPTANCE.**
- **NEXT — intended New Balance + AttackCollision Hack compatibility fixture, then remaining modifier/Finishing controls as needed.**


### EV-421 — Intended New Balance + AttackCollision runtime matrix PASS

Clarification to the EV-420 runtime batch:
- the User ran the same focused 0.1-versus-1.0 authored-speed matrix twice:
  1. native fixture without New Balance / AttackCollision;
  2. intended fixture with New Balance + AttackCollision enabled;
- the User reported the **same positive result in both fixtures**.

Intended-stack observations:
- 2H Normal: Raise followed authored speed together with Hit at 0.1 and 1.0;
- 2H Quick: Raise followed authored speed together with Hit at 0.1 and 1.0;
- 2H Power: Raise followed authored speed together with Hit at 0.1 and 1.0;
- 2H Whirl: Raise followed authored speed together with Hit at 0.1 and 1.0;
- 2H Hack: Raise followed authored speed together with Hit at 0.1 and 1.0;
- 1H Power: Raise followed authored speed together with Hit at 0.1 and 1.0;
- 1H Pierce: Raise followed authored speed together with Hit at 0.1 and 1.0.

Interpretation:
- EV-415 Raise phase-speed correction is runtime-positive both native and with the intended New Balance + AttackCollision stack on the tested routes;
- the EV-417 AttackCollision Hack bypass is runtime-corrected: configured 2H Hack remains responsive under AttackCollision rather than ignoring G3AB authoring;
- the strong 0.1-versus-1.0 contrast produced no reported obvious double-scaling behavior;
- 1H Pierce remains a positive control under the intended stack.

Limits:
- this visual batch does not independently quantify Power's preserved native/live Raise-vs-Hit numerical ratio;
- it does not yet isolate one specific New Balance contextual modifier on configured Hack;
- it does not yet re-run a factual Finishing isolation control on this exact production source;
- no exact third-party DLL hash was captured in this user clarification, so the evidence establishes the User's intended installed New Balance + AttackCollision stack rather than a binary-hash identity claim.

Disposition:
- **PASS — INTENDED-STACK RAISE PHASE-SPEED + ATTACKCOLLISION HACK COMPATIBILITY.**
- **EV-417 MAJOR RUNTIME REGRESSION CLOSED on the tested 2H Hack fixture.**
- **NEXT — small modifier-preservation / Finishing-isolation / interruption sanity controls before final acceptance closure.**


### EV-422 — Final Raise/Hack compatibility sanity closure PASS

Fixture:
- production source remains `41ed80c6420e5236d13fc037cb5923b946cb8ccc`;
- current production DLL identity remains the EV-420 build unless otherwise noted;
- final checks performed by the User across native and/or intended New Balance + AttackCollision conditions as described below;
- visual/gameplay observation is the primary evidence surface; no diagnostic log was required.

Observed — stamina/context behavior:
- with ordinary stamina behavior, the User let stamina reach zero and performed Hack attacks but saw little/no meaningful Hack speed change;
- removing G3AB produced the same Hack behavior;
- this was repeated with and without New Balance;
- therefore the absence of a visible ordinary zero-stamina Hack slowdown is not introduced by G3AB and is not evidence of modifier loss;
- New Balance's alternative stamina mechanics were then enabled, where attacks cannot be performed at zero stamina;
- with G3AB installed, Hack followed the same alternative zero-stamina restriction as the other attacks.

Observed — Finishing isolation:
- with unique Hack animation assets present and `Hack_BaseSpeed=0.1`, Hack was slow while factual Finishing remained fast/native-timed at approximately 1.0;
- the User then removed the unique Hack animation assets so Gothic resolved Hack through the Finishing animation asset;
- Hack remained slow at the configured 0.1 while factual Finishing remained fast/native-timed;
- therefore Speed authority remains separated by factual action identity even when Action14 Hack and Action15 Finishing share the same resolved animation asset.

Observed — interruption/transition robustness:
- the User entered combat and experienced repeated interruptions from Hack attacks and other attacks;
- all tested attacks continued to work normally;
- no stuck attack, stale Raise, speed carry-over, repeated phase, or continuation leak was observed.

Interpretation:
- the planned ordinary-stamina Hack slowdown check is not a valid positive modifier fixture because the tested compatible/native behavior itself does not materially slow Hack at zero stamina;
- the New Balance alternative-stamina control positively shows that the route-neutral Hack adapter does not bypass that compatible gameplay policy;
- EV-398/EV-399 Hack-vs-Finishing factual-action isolation is reconfirmed on the final production source, including the strongest shared-asset condition;
- EV-418/EV-419 stateless request design shows no runtime lifetime/continuation regression under repeated combat interruption.

Disposition:
- **PASS — FINAL RAISE / SPEED / HACK COMPATIBILITY RUNTIME ACCEPTANCE CLOSED.**
- **PASS — EV-417 ATTACKCOLLISION HACK REGRESSION REMAINS CLOSED.**
- **PASS — FACTUAL FINISHING / ACTION15 EXCLUSION CONFIRMED WITH UNIQUE AND SHARED ASSETS.**
- **PASS — INTERRUPTION / TRANSITION SANITY.**
- No further Raise/Speed implementation or Work task is justified absent contradictory evidence.


### EV-423 — Dual Raise asset validation + Normal directional-Hit continuation contradiction

Fixture:
- accepted production source `41ed80c6420e5236d13fc037cb5923b946cb8ccc`;
- development documentation state through `71e9b2dc5e354216462595403ec916911e2e029b`;
- User authored rule-derived Hero dual-wield Raise assets from factual Hit names and tested with AddRaise enabled.

Observed — generated Raise assets:
- generated dual-wield Fwd Normal Raise assets for P0 and P1 were selected by Gothic and played correctly;
- generated dual-wield QuickAttackR/QuickAttackL Raise assets for ordinary P0/P1 routes were selected and played correctly;
- candidate `Hero_Stand_1H_1H_P3_QuickAttackL_Raise_N_Fwd_00_%_00_P3_0_L` never occurred;
- the corresponding P3 -> P61 Quick Hit route likewise does not occur in the User's normal runtime testing; no claim is made beyond non-observation about why that native asset remains in the inventory.

Observed — directional Normal contradiction:
- dual/1H-family Normal Left and Right attack variants have native matching Raise assets;
- with `Normal_AddRaise=On`, the appropriate directional Raise activates;
- after that Raise completes, the Hit that follows resolves to the **Fwd Normal Hit**, not the originally selected Left or Right Hit;
- without this inserted continuation, Gothic has distinct native Fwd/Left/Right Normal Hit assets/routes.

Static correlation:
- `sAICombatMoveInstr_Args` contains only SelfEntity, TargetEntity, Action, PhaseName and AniSpeedScale; it carries no direction field;
- current `AttackRaise::RaiseContinuation` stores/replays exactly that request object;
- therefore storing/replaying an Action1 Hit request cannot by itself preserve the hidden Gothic state that selected Fwd vs Left vs Right;
- current source creates the synthetic Raise first and then replays the stored generic Action1 Hit, so Gothic performs a second Hit resolution after the Raise.

Interpretation:
- generated Raise filename rules are validated for the tested dual Fwd Normal and ordinary P0/P1 Quick routes;
- the Left/Right failure is **not** a filename-authoring failure;
- it is a production AddRaise continuation-selection defect: the post-Raise Hit loses factual directional identity that exists outside `sAICombatMoveInstr_Args`;
- EV-422 remains valid for its tested fixtures, but the broader first-public-scope claim for Normal AddRaise is reopened by this new contradictory directional fixture;
- Speed, Hack compatibility and Collision remain closed/protected.

Disposition:
- **CONTRADICTION — RAISE NORMAL DIRECTIONAL CONTINUATION REOPENED.**
- **NO PRODUCTION FIX YET.**
- **NEXT — bounded causal research to identify Gothic's exact Fwd/Left/Right selection state and the smallest way to preserve the already-selected Hit across an inserted Raise.**


### EV-424 — Normal AddRaise direction owner statically closed

Research fixture:
- repository `development` through EV-423;
- production behavior source unchanged at `41ed80c6420e5236d13fc037cb5923b946cb8ccc`;
- exact local Gothic `Game.dll` static inspection;
- pinned SDK `Jackydima/gothic3sdk@bbe769075bc896085a620a0ceb3491192c5beb61`.

Established native data flow:
- `sAICombatMoveInstr` enters `sAICombatMoveStart` at `Game+0x16ABB0`;
- the request action is copied to SPU `+0x154`, but `sAICombatMoveInstr_Args` contains no direction field;
- `sAICombatMoveStart` reconstructs SPU `m_DirectionVec` around `+0x16AC23..+0x16ACF2` from current entity/target geometry or the native fallback path, then normalizes it at `+0x16AD5B`;
- the animation-direction string is initialized to exact literal `Fwd` at `+0x16AEDD`;
- Action1 / Normal dispatches to the normal directional classification at `+0x16AF3C`;
- that path can replace the local string with exact `Right` at `+0x16AF61` or `Left` at `+0x16AF76`;
- local enum values are Fwd=1, Left=3, Right=4, matching SDK `gEDirection`;
- Gothic obtains the actor Navigation property set and writes the selected current-animation direction at `+0x16B00E`;
- `+0x16B056` calls `GetAniName` at `+0x16F840`, passing the freshly selected direction bCString as its fifth argument;
- `GetAniName` appends that fifth argument into the resource name at `+0x16FA61`.

Imported-function resolution confirms this classification uses native geometry/vector APIs including `eCEntity::GetWorldPosition`, `GetWorldMatrix`, `GetAtVector`, `bCVector::GetInvTranslated`, `Normalize` and `SetCrossProduct`.

Causal explanation:
- G3AB intercepts the factual Action1 Hit before `sAICombatMoveStart`, so Gothic has not serialized Fwd/Left/Right into the request;
- synthetic Raise starts first and receives one native direction classification, explaining EV-423's correct Left/Right Raise;
- after Raise completes, G3AB replays the stored generic Action1 Hit request;
- that second start recomputes direction from then-current state/geometry;
- because the request carries no direction and the previous Raise filename is not the direction authority on this path, the Hit may now resolve Fwd.

Animation-name consequence:
- Gothic's strict filename structure remains a real engine contract for source/destination pose, action, phase, type, direction and resource identity;
- the Normal direction token specifically is a fresh input to `GetAniName`, not recovered from the previous animation filename.

Frozen correction design:
```text
pending Normal AddRaise
-> synthetic Raise enters native sAICombatMoveStart
-> at Game+0x16B056 GetAniName call:
     capture Gothic's exact native Raise direction bCString
     + matching current gEDirection
-> let Raise resolve unchanged
-> stored Action1 Hit begins
-> at same GetAniName call for that exact continuation:
     restore captured current-animation direction
     substitute only the captured native direction bCString
     call Gothic GetAniName once
-> all unrelated CombatMoves pass unchanged
```

Rejected:
- filename parsing/rewrite;
- copied Gothic geometry classifier;
- target/orientation mutation;
- restoring `m_DirectionVec` before Hit, because native start rebuilds it;
- direct PlayAni bypass;
- late motion-resource rewrite after Gothic has already built the wrong name/current direction.

Disposition:
- **PASS — DIRECTION OWNER AND EV-423 CAUSE IDENTIFIED.**
- **NO DIAGNOSTIC PROBE REQUIRED BEFORE IMPLEMENTATION.**
- **NEXT — bounded production implementation of one-shot Gothic-native direction carry.**


### EV-425 — Pre-implementation Sol review of current Raise/Speed integration

Scope:
- read-only review before EV-424 implementation;
- current production source remains byte-identical to `41ed80c6420e5236d13fc037cb5923b946cb8ccc`;
- reviewed `AttackRaise.cpp/.h`, `AttackSpeed.cpp/.h`, `BehaviorProfiles.cpp/.h`, relevant `EngineBridge.cpp`, pinned SDK call-hook/API surfaces, and the EV-424 implementation contract;
- no production source modified.

Current implementation findings:
- `AttackRaise` remains the correct semantic owner for AddRaise continuation policy/state;
- the single `std::map<SPU*, shared_ptr<RaiseContinuation>>` is sufficient; a second direction-state map would duplicate lifetime authority;
- the local `shared_ptr` retained across native transport calls is justified because FullStop/AISetState/native callbacks may erase/replace map state re-entrantly while the current invocation still needs its stored request alive;
- `CompleteRaiseInvocation` already provides the exact Raise -> stored Hit transition point and cancellation-safe lifetime needed by direction carry;
- FullStop, AISetState and request-mismatch cancellation already erase the continuation and can automatically retire added direction fields;
- custom Raise still reuses the exact stored Hit `AniSpeedScale`; no Speed change is needed;
- EngineBridge layering remains clean: AttackRaise sequencing -> Hack Speed adapter -> Collision transport -> native CombatMove;
- BehaviorProfiles and AttackSpeed require no change for EV-424.

SDK / call-site refinements:
- official build SDK exposes `Entity::GetCurrentAniDirection()` and `Entity::SetCurrentAniDirection(gEDirection)`; use these instead of raw Navigation offsets/pointers;
- `GetAniName` signature is `GetAniName(bCString &, eCEntity *, gEAction, bCString, bCString &, GEBool)`;
- disassembly at `Game+0x16B056` shows the fourth semantic argument is the original request `PhaseName` and the fifth is the freshly selected direction bCString;
- therefore the hook can distinguish the synthetic `Raise` and stored `Hit` directly from factual action + phase instead of inferring stage from animation names or unrelated engine state;
- at this call site ECX is already the current `gCScriptProcessingUnit *`, so the call-hook transport can inject only the existing this pointer; no separate EBP-derived SPU argument is required.

Frozen cleanliness constraints for implementation:
```text
extend existing RaiseContinuation only:
  bool directionCaptured
  gEDirection capturedDirection
  bCString capturedDirectionName

AttackRaise semantic seam:
  pending Action1 + Phase Raise -> capture native direction string + Entity current direction
  pending Action1 + Phase Hit   -> reuse captured string + SetCurrentAniDirection
  otherwise                     -> no decision / pass through

EngineBridge:
  one mCCallHook at Game+0x16B056
  transport factual GetAniName args into AttackRaise
  invoke Gothic GetAniName exactly once
```

Do not:
- add another map/cache/lifecycle owner;
- refactor `RaiseContinuation`, `RunCombatMove`, Speed, profiles or Collision beyond the fields/seam required by direction carry;
- change exact-float request identity, historical EngineBridge naming, or other unrelated code merely for cleanup;
- parse animation names or map `gEDirection` back to strings.

Review disposition:
- **PASS — CURRENT IMPLEMENTATION IS CLEAN ENOUGH TO EXTEND DIRECTLY.**
- **BLOCKER 0 / MAJOR 0 / MINOR 0 requiring pre-implementation refactor.**
- **EV-424 correction should remain one new call-site transport plus three continuation fields and a narrow AttackRaise semantic seam.**


### EV-426 — Normal AddRaise direction continuation source review

Scope:
- fresh diff-against-contract review of the EV-424 direction correction;
- reviewed source candidate `1da12cead5acfb54c5520a34d07bccc4c32fd64f`;
- current `development` production blobs at review HEAD `cf9b8aa204be565844e719c1bebb66f03de7e58b` are byte-identical to that candidate;
- frozen contract: `docs/work/active/RAISE_NORMAL_DIRECTION_CONTINUATION_IMPLEMENTATION.md`;
- no build or runtime execution performed.

Static scope:
- only `AttackRaise.cpp`, `AttackRaise.h` and `EngineBridge.cpp` differ in production source from the pre-implementation baseline;
- `RaiseContinuation` gained exactly the frozen three fields: `directionCaptured`, `capturedDirection`, `capturedDirectionName`;
- no second map/cache/lifecycle owner was added;
- one new `mCCallHook` exists at `Game+0x16B056`;
- `EngineBridge` transports factual SPU/action/phase/direction arguments only; direction policy remains in `AttackRaise`;
- no Speed, BehaviorProfiles, Collision or INI source changed.

Semantic review:
- unrelated GetAniName traffic passes through unchanged unless the same SPU has a pending Normal AddRaise continuation and factual Action1 phase matches;
- synthetic Normal Raise captures Gothic's exact supplied direction string plus `Entity::GetCurrentAniDirection()` without modifying either before the native GetAniName call;
- stored Normal Hit restores the captured enum with `SetCurrentAniDirection`, substitutes the exact captured direction string, consumes the capture one-shot, then invokes Gothic GetAniName exactly once;
- direction state shares the existing `RaiseContinuation` lifetime;
- FullStop, AISetState and request-mismatch cancellation continue to erase the same continuation state before an invalid stored Hit can proceed;
- Quick, Whirl, Power, Hack and unrelated CombatMove actions fail the Action1 semantic gate and remain pass-through.

ABI / hook review:
- pinned SDK confirms `sAICombatMoveInstr_Args::SelfEntity` is the same `eCEntity *` type used by the GetAniName call;
- pinned SDK `mCCallHook::AddThisArg()` transports ECX;
- EV-425 established ECX at `Game+0x16B056` as the current `gCScriptProcessingUnit *`;
- the wrapper calls the real `Game+0x16F840` GetAniName through an explicit Win32 `__thiscall` function type, restoring the SPU to ECX for the native member call;
- the original native GetAniName is invoked once by the wrapper.

Protected behavior:
- no filename parsing/rewrite;
- no copied Gothic direction classifier;
- no target/facing/transform mutation;
- no `m_DirectionVec` preservation;
- no direct PlayAni replacement;
- no Speed composition or Hit AniSpeedScale change;
- no Quick/Whirl redesign;
- no Power Raise, Hack, New Balance ownership or Collision change.

Disposition:
- **PASS — EV-424/EV-425 IMPLEMENTATION CONTRACT SATISFIED.**
- **BLOCKER 0 / MAJOR 0 / MINOR 0.**
- **NO SOURCE CORRECTION REQUIRED BEFORE BUILD.**
- **NEXT — local synchronization, build/deploy verification, then the frozen focused runtime matrix.**
