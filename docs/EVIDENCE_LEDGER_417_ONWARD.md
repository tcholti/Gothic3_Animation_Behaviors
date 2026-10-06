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


### EV-427 — Normal AddRaise direction runtime acceptance

Scope:
- reviewed EV-426 source was synchronized, built and deployed by the User on the authoritative local Gothic 3 environment;
- focused runtime validation followed the frozen EV-424 implementation matrix;
- no new source change was introduced between EV-426 review and this runtime result.

User runtime result:
- local production build: **PASS**;
- deployment: **PASS**;
- Normal AddRaise direction continuation: **PASS**;
- the previously failing Left/Right continuation now remains directionally correct through Raise -> Hit;
- frozen Normal Fwd/Left/Right matrix and requested 1H/dual-wield/control/interruption coverage were reported working;
- Quick and Whirl controls showed no reported regression;
- no contradictory behavior was observed.

Proven production behavior:
```text
Normal Fwd   -> Fwd Raise   -> Fwd Hit
Normal Left  -> Left Raise  -> Left Hit
Normal Right -> Right Raise -> Right Hit
```

Evidence precision:
- the User reported successful build and deployment in compact form;
- exact built/live SHA256 values were not transcribed into Chat for this EV and are therefore not asserted here.

Disposition:
- **PASS — EV-423 DIRECTIONAL CONTINUATION DEFECT CLOSED.**
- **PASS — EV-424 MINIMAL GOTHIC-NATIVE DIRECTION CARRY RUNTIME-ACCEPTED.**
- **Quick/Whirl/Speed/Hack/Collision protected behavior remains accepted absent contrary evidence.**
- **RAISE_NORMAL_DIRECTION_CONTINUATION_IMPLEMENTATION task may close/archive.**


### EV-428 — EV-427 scope clarification and staged Raise validation

User clarification:
- the EV-427 phrase "all works" means **all behavior exercised in that local test worked**;
- it does **not** mean every possible Gothic 3 animation set/attack route has a Raise asset or has been runtime-tested;
- exhaustive Raise coverage is constrained by asset availability: many Normal/Quick routes need matching Raise animations authored before the engine path can be exercised.

Exact latest tested coverage:
- Hero dual-wield / `1H_1H`: AddRaise worked on every attack where it was enabled in the test;
- rule-derived Normal Fwd Raise assets for ordinary P0/P1 were selected and played;
- rule-derived ordinary P0/P1 `QuickAttackR` / `QuickAttackL` Raise assets were selected and played;
- native dual Normal Left/Right Raise assets were enabled and now continue into the matching directional Hit after the EV-424 correction;
- the same dual fixtures worked at their native timing;
- with authored attack speed reduced to `0.1`, the added/generated Raise phases inherited the changed speed as intended;
- 2H Normal, Quick and Whirl AddRaise controls were re-tested and continued to work as before;
- ordinary combat against a Golem using both 2H and dual `1H_1H` completed without an observed Raise regression.

EV-427 precision correction:
- EV-427 remains valid for the direction defect closure and the tested local result;
- its shorthand reference to the previously handed-off "frozen ... controls" must not be read as proof that every listed theoretical route or every Gothic animation family was individually exercised in that run;
- this EV-428 entry is the authoritative scope statement for what the User actually exercised.

Pre-release Raise validation still desired by the User:
```text
1. human Fist Normal
2. Sabretooth
3. Troll
```

Release-validation strategy:
- these three fixtures are the remaining representative Raise tests before the User considers the Raise implementation sufficiently tested for the initial Animation Behaviors release;
- do **not** block release on authoring and testing Raise assets for every possible attack/animation set in Gothic 3;
- broader coverage is intentionally staged with the User's later redesign of the Gothic 3 Animations Redone combat animation mods;
- as each Normal/Quick family receives authored Raise assets during that redesign, use it as additional real-world compatibility/coverage testing;
- post-release user reports remain a valid source of contradictory fixtures and should trigger focused fixes rather than speculative pre-release expansion.

Disposition:
- **EV-423/EV-424 direction defect remains CLOSED/PASS.**
- **Raise production mechanism is accepted on the tested routes; universal animation-set coverage is NOT claimed.**
- **NEXT PRE-RELEASE RAISE VALIDATION: human Fist Normal, Sabretooth, Troll.**


### EV-429 — Representative AddRaise type coverage closure

User runtime fixture:
- authoritative local Gothic 3 runtime;
- existing production Raise implementation unchanged;
- existing INI profiles used for Hero Fist, Sabretooth, Troll and Staff;
- newly authored Troll/Sabretooth Raise resources from the frozen pre-release asset plan;
- Human Fist used native Raise resources;
- Staff used an already-available Raise resource; exact Staff filename/action was not transcribed into Chat and is therefore not asserted here.

Runtime observations:
- Human Fist Normal AddRaise: PASS in and out of combat;
- Sabretooth Normal + Quick R/L AddRaise: PASS in and out of combat;
- Troll Normal + Quick R/L AddRaise: PASS in and out of combat;
- Staff AddRaise control: PASS in combat;
- after setting the tested attack speeds to `0.1`, all tested Raise phases followed the new configured speed;
- no continuation, combat-state or obvious collision regression was observed.

Newly runtime-proven authored names:
```text
Troll_Stand_Fist_Fist_P0_Attack_Raise_N_Fwd_00_%_00_P0_0
Troll_Stand_Fist_Fist_P0_QuickAttackR_Raise_N_Fwd_00_%_00_P0_0
Troll_Stand_Fist_Fist_P0_QuickAttackL_Raise_N_Fwd_00_%_00_P0_0
Sabertooth_Stand_None_Fist_P0_Attack_Raise_N_Fwd_00_%_00_P0_0
Sabertooth_Stand_None_Fist_P0_QuickAttackR_Raise_N_Fwd_00_%_00_P0_0_R
Sabertooth_Stand_None_Fist_P0_QuickAttackL_Raise_N_Fwd_00_%_00_P0_0_L
```

Representative type-coverage conclusion:
- the public additive-Raise surface contains only `Normal_AddRaise`, `Quick_AddRaise` and `Whirl_AddRaise`;
- Normal has now been exercised as ordinary Fwd and native directional Left/Right continuation;
- Quick has now been exercised in both factual `QuickAttackR` and `QuickAttackL` forms;
- full Whirl has already been runtime-accepted on the supported route;
- tested profiles now span human weapon, dual, human bare Fist, nonhuman `None+Fist`, and Troll `Fist+Fist` animation structures;
- both native Raise assets and rule-derived/user-authored Raise assets are represented;
- configured-speed inheritance has been repeatedly validated, including extreme `0.1` controls.

Boundary:
- this is **representative structural/type coverage**, not exhaustive testing of every individual animation asset, pose, actor family or INI profile;
- `SimpleWhirl` is a separate Speed-supported action and is not part of the public AddRaise surface;
- broader per-asset coverage remains naturally staged with future animation redesigns and post-release contradictory reports.

Disposition:
- **PASS — PRE-RELEASE REPRESENTATIVE RAISE VALIDATION COMPLETE.**
- **PASS — NORMAL / QUICK R+L / FULL WHIRL ADDRAISE TYPE COVERAGE COMPLETE AT REPRESENTATIVE LEVEL.**
- **RAISE_PRE_RELEASE_VALIDATION may close/archive.**


### EV-430 — Shield pose-changing Quick partial-Raise coverage acceptance

Purpose:
- final sanity check after EV-429 representative closure;
- exercise pose-changing Quick attacks rather than only same-pose Quick routes;
- verify a Quick profile can have `Quick_AddRaise=On` while only some factual Quick assets have matching Raise resources.

Fixture:
- profile: Hero Shield+1H Quick;
- exact native pose-changing Hits:
```text
Hero_Stand_Shield_1H_P1_QuickAttackL_Hit_N_Fwd_00_%_00_P50_100_L
Hero_Stand_Shield_1H_P3_QuickAttackL_Hit_N_Fwd_00_%_00_P70_100_L
```
- user-authored/tested Raises:
```text
Hero_Stand_Shield_1H_P1_QuickAttackL_Raise_N_Fwd_00_%_00_P1_0_L
Hero_Stand_Shield_1H_P3_QuickAttackL_Raise_N_Fwd_00_%_00_P3_0_L
```
- other Shield+1H Quick routes intentionally remained without Raise resources;
- User had previously authored matching Recover resources for the pose-changing Hit routes according to Gothic naming rules.

Runtime observations:
- both new pose-preserving Raises were selected and played correctly;
- their following pose-changing Quick Hits executed correctly;
- Shield+1H Quick attacks without matching Raise resources still executed normally with `Quick_AddRaise=On`;
- behavior passed both in and out of combat;
- after setting Shield+1H Quick speed to `0.1`, all Quick attacks continued to work and the two new Raise animations also ran at `0.1`;
- no regression or contradiction was observed.

Interpretation:
- pose-changing Quick Hit destinations do not require the preceding Raise to target the Hit destination pose; the tested Raise remains pose-preserving at the source pose;
- partial Raise-resource coverage inside one enabled Quick profile is runtime-tolerated in this tested Shield+1H fixture;
- exact engine-internal reason for the missing-resource fallback was not instrumented in this run, so do not infer a specific native return code/path beyond the observed behavior;
- a profile therefore does not need every factual Quick animation to have a Raise resource merely to enable AddRaise for the subset that does.

Disposition:
- **PASS — POSE-CHANGING QUICK RAISE ROUTE ACCEPTED.**
- **PASS — PARTIAL QUICK RAISE ASSET COVERAGE ACCEPTED IN TESTED SHIELD+1H PROFILE.**
- **PASS — SPEED 0.1 COMPOSITION RETAINED ACROSS BOTH RAISE-PRESENT AND RAISE-ABSENT QUICK ROUTES.**
- **RAISE MODULE = CLOSED/PASS / WELL TESTED FOR INITIAL RELEASE.**


### EV-431 — Final independent Speed + Raise source review

Review mode:
- bounded read-only independent source review;
- remote review handoff HEAD `deee36c5af66e4ebc4da09729428f07c4f0f0c49`;
- production source reviewed: `d642f30bcb6b564deaaffed26fd11b763da88163`;
- comparison baseline for the prior large Astra audit: `d5d829e07eb2bfe8de428aa2ad148ba1f2d3835c`;
- POP-10 preflight completed;
- no source/docs/build/deploy/runtime/probe/commit changes made by the reviewer.

Findings:
```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    1
```

The NOTE preserves the EV-430 evidence boundary: tested partial Raise-resource coverage is accepted behavior, but it does not prove universal asset coverage or a specific uninstrumented native fallback mechanism. No new C++ asset policy is warranted.

Explicit verdicts:
```text
correctness                        PASS
New Balance compatibility          PASS
AttackCollision compatibility      PASS
Collision non-interference         PASS
simplicity                         PASS
modularity                         PASS
performance                        PASS (source assessment; no benchmark)
configuration/profile architecture PASS
hook architecture                  PASS
release-checkpoint readiness       PASS
```

Decisive checks:
- factual Action14 Hack Raise/Hit/Recover composition applies the configured ratio to the supplied live compatible scale without an additional speed-owner query;
- null-argument resumes bypass recomposition; former caller-specific Hack hooks remain retired; Action15 remains excluded;
- non-finite and positive-compatible-scale underflow fail closed to the compatible value;
- Normal direction carry remains continuation-owned and one-shot through the exact `Game+0x16B056` GetAniName boundary;
- Win32 ABI/original-function transport to `Game+0x16F840` is consistent with the pinned SDK;
- FullStop/state cancellation and shared ownership preserve lifecycle without replay;
- resolved request-time animation identity, Quick Action4/5 grouping, Sprint/Power inheritance, custom Raise Hit-scale reuse and native Power Raise phase-relative composition remain coherent;
- shared Collision invocation lifecycle remains unchanged.

External compatibility:
- project-pinned Jackydima New Balance / AttackCollision boundary was checked;
- reviewer additionally checked upstream Jackydima commit `bbe769075bc896085a620a0ceb3491192c5beb61`, one commit beyond the repository pin;
- this additional observation does **not** change the repository's pinned external authority.

Disposition:
- **PASS — READY FOR REPOSITORY RELEASE AUDIT / MAIN PROMOTION CHECKPOINT.**

### EV-432 — Quick repository release / authority health audit

POP-10 hierarchy:
```text
CAM
-> docs/README.md project charter
-> specialist authorities / references
-> procedures / temporary work
-> evidence / archive provenance
```

Review scope:
- release-checkpoint repository health only;
- authority topology, current-state hygiene, active-work lifecycle, evidence/raw hygiene, mechanical size signals, branch promotion shape and validator readiness;
- no broad technical re-review and no archive cleanup for cosmetic differences.

Observed:
- `main` at `b472e9fa4756d62c4eea986c30751e01311a3cfd` is the exact merge base / ancestor of `development`;
- `development` is ahead with no commits behind `main`; no branch divergence exists;
- the cycle matches the charter/pipeline's intended stable promotion point: Collision + Speed + Raise are all closed/accepted;
- current authority ownership remains coherent with `KNOWLEDGE_REGISTRY.md`;
- exactly one active evidence ledger remains in root docs;
- active ledger size is about 40 KiB, below the 64 KiB mechanical warning boundary;
- `SESSION_ENTRYPOINT.md` remains below its 8 KiB cap and `BETWEEN_CHATS.md` remains compact;
- `research/raw/` contains only the repository placeholder `Keep.txt`; no open runtime artifact is stranded;
- the only non-README temporary active file was the completed final Speed+Raise review task and is eligible for archive closure;
- prior source review reported current-delta `git diff --check` PASS;
- broader historical diff whitespace observations are confined to archived Markdown hard-break formatting and do not warrant archive mutation.

Finding summary:
```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    archive-only Markdown hard-break whitespace; KEEP / no action
```

Disposition:
- **PASS — REPOSITORY/KNOWLEDGE STATE IS SUITABLE FOR THE DELIBERATE DEVELOPMENT -> MAIN STABLE PROMOTION CHECKPOINT.**


### EV-433 — Stable Collision + Speed + Raise main promotion

Prerequisites:
- Collision CLOSED/PASS;
- Speed v2 CLOSED/PASS;
- Raise CLOSED/PASS / well tested through EV-430;
- final independent Speed+Raise source review PASS EV-431;
- quick repository/authority release audit PASS EV-432;
- knowledge-state validator PASS on the release-audit closure commit.

Promotion:
- `main` was fast-forwarded from `b472e9fa4756d62c4eea986c30751e01311a3cfd` to the accepted release-audit closure history;
- no divergent main-only commits existed;
- promotion therefore preserved development history without merge conflict or source rewrite;
- stable branch now represents the accepted Collision + Speed + Raise integration cycle.

Boundary:
- ordinary new feature work continues only on `development`;
- `main` remains the deliberately promoted stable baseline until another explicit checkpoint;
- attack forward displacement is the next research responsibility and is not part of this stable checkpoint.

Disposition:
- **PASS — COLLISION + SPEED + RAISE STABLE PROMOTION COMPLETED.**


### EV-434 — Attack displacement static mechanism closure

Mode:
- bounded read-only Astra static research;
- development HEAD verified at `77b53975fc13d9850a9df4268bc5146201f9632b`;
- no source/docs/build/deploy/runtime/probe/commit changes made by the researcher.

Pinned references:
```text
official SDK: thirdparty/gothic3sdk @ 90bfd344de4510dda7ac9da7461cc7f1eac911f7
New Balance / AttackCollision: references/jackydima-gothic3sdk @ 316d32406a133f8884e7e302752c35f66b4f54fc
```

Native CombatMove mechanism — PROVEN:
- `Game+0x1696E0` owns the instruction lifecycle; fresh requests enter the start path at `Game+0x16ABB0`;
- fresh start logic constructs and normalizes `SPU.m_DirectionVec`;
- after selecting the actual motion, Gothic reads filename word 13 and parses it as the movement distance;
- nominal animation duration is primary max time divided by request `AniSpeedScale`;
- native commanded velocity is therefore:
```text
T = animationMaxTime / AniSpeedScale
v_native = normalizedDirection * (D_filename / T)
```
- `Game+0x16B8A3` is the `bCVector::Scale(float)` call that applies `D_filename / T`;
- `Game+0x16B8A9` loads the CharacterMovement receiver and is New Balance's insertion point, not the native movement call;
- `Game+0x16B8B7` calls `gCCharacterMovement_PS::EnableCombatMovementFromSPU`;
- the receiver copies the vector, enables combat movement and clears vertical contribution;
- controlled translation later feeds the stored vector into velocity; target-stop/movement-validity/cleanup may shorten or suppress realized travel.

Native `GetCombatMoveLength` distinction — PROVEN:
- implementation is `Script_Game+0xAA270`;
- native Hit-path invocation at `Game+0x16B4EC` discards its return value;
- native movement distance is independently supplied by the selected animation filename;
- therefore replacing only `GetCombatMoveLength` does not replace native movement distance in the tested build.

New Balance mechanism at the project pin — PROVEN:
- `CombatMoveScale` is inserted at `Game+0x16B8A9`, after native vector scaling and before CharacterMovement receives it;
- for eligible factual Hit requests:
```text
L = New Balance GetCombatMoveLength(Self, current instruction action)
if L == -1 -> preserve native vector
T = animationMaxTime / request.AniSpeedScale
normalize existing m_DirectionVec
scale by L / T * ATTACK_REACH_MULTIPLIER
```
- the replacement callback gates on current animation phase Hit;
- it uses an action table plus combat-skill factor and integer conversion before the global reach multiplier;
- no human-only filter exists; nonhuman/NPC skill tiers are derived from level bands;
- New Balance therefore replaces compatible Hit vector magnitude rather than multiplying the native filename distance;
- Raise/Recover callback requests return `-1` and preserve native movement calculation.

Speed interaction — PROVEN algebra:
- increasing `AniSpeedScale` shortens nominal duration and proportionally increases commanded velocity;
- under uninterrupted movement for that duration, nominal distance cancels back to the chosen distance;
- actual world displacement remains conditional on the interval for which movement is permitted;
- future displacement behavior must consume the already-composed request speed and must not re-query/recompose Speed.

Animation/resource interaction:
- **PROVEN:** the serialized numeric distance field in the selected animation resource is a causal native CombatMove movement input;
- **PROVEN:** motion routing can therefore change native displacement by changing the selected resource;
- **UNKNOWN:** whether animation/root data independently contributes additional entity translation across representative assets;
- do not call this feature root-motion control.

Action policy at the New Balance pin — PROVEN callback table:
```text
Normal Action1       native callback 120 (Zombie 150) -> NB int(180*f)
QuickR Action4       native callback 60               -> NB int(70*f)
QuickL Action5       native callback 60               -> NB int(70*f)
Power Action2        native callback 180              -> NB int(240*f)
Whirl Action10       native callback 180              -> NB int(220*f)
SimpleWhirl Action6  native callback 120              -> NB int(180*f)
Pierce Action11      native callback 120              -> NB int(150*f)
Hack Action14        native callback 120              -> NB int(240*f)
Sprint Action9       native callback 180              -> NB int(240*f)
```
Native commanded distance remains the selected resource's filename field, not this callback table.

Current G3AB ordering — PROVEN:
```text
G3AB CombatMove boundary
-> AttackRaise
-> factual Hack Speed adapter
-> Collision invocation lifecycle
-> native CombatMove start
-> direction/resource resolution
-> native filename-distance scaling
-> New Balance CombatMoveScale
-> CharacterMovement receives final compatible velocity
```

Compatibility consequence:
- Speed supplies the final request speed consumed by native/NB duration math;
- Raise may create separate physical phase requests and must remain lifecycle-independent;
- resource routing changes the native filename-distance input;
- Collision requires no redesign;
- AttackCollision factual Hack requests reach the same downstream movement path.

Static architecture candidate — STRONGLY SUPPORTED, not frozen:
- the narrowest compatible composition seam is the CombatMove-specific call at `Game+0x16B8B7`, after New Balance has finished its magnitude policy;
- candidate composition:
```text
v_configured = k * v_compatible
```
- this preserves compatible direction/magnitude decisions, speed composition, resource selection and native stopping behavior;
- scaling earlier at `+0x16B8A3` is rejected because New Balance can subsequently normalize away that magnitude change;
- absolute final-world-distance control and Speed-style reference-distance replacement are not established contracts.

Remaining causal questions:
- exact realized displacement vs integrated commanded velocity on representative human/nonhuman attacks;
- exact enabled movement interval relative to nominal animation duration;
- whether an independent animation/root contribution materially moves the entity.

Disposition:
- **STATIC RESEARCH PARTIALLY CLOSED — ONE BOUNDED RUNTIME EVIDENCE PASS REQUIRED BEFORE PRODUCTION ARCHITECTURE IS FROZEN.**


### EV-435 — Displacement author/runtime constraints reconciled

Context:
- EV-434 statically proved the CombatMove vector path;
- the User then identified that several practical movement facts predate EV-434 and had already been established through animation authoring/runtime work;
- repository review showed only part of those facts had been preserved durably.

Established author/runtime observations:
- the numeric combat-movement field in the animation filename has long been used deliberately when authoring Gothic 3 attack animations;
- attack animations are authored in place; Gothic supplies the gameplay entity translation through CombatMove movement;
- in ordinary attack phase sets known to the User, Raise and Recover movement values are normally `0`, while Hit carries the nonzero combat movement value (for example `100`);
- movement therefore occurs during the phase/resource carrying the nonzero value, normally Hit; separate Raise/Recover requests with zero movement do not add forward entity travel;
- Gothic combat movement is constrained by navigation/world conditions: it can stop the actor near ledges or when blocked/colliding, unlike jump movement which can carry the actor off an edge;
- these stopping rules mean a configured combat movement value is not an unconditional promised world-space endpoint.

Distribution/resource constraint:
- changing the serialized animation name is not a practical runtime authoring control for this feature;
- Gothic resolves existing packed animation resources by archive/resource precedence; creating a differently named replacement does not transparently replace the packed original;
- changing filename movement values therefore requires replacing/removing/injecting the resource in the compiled animation archive/package, increasing installation complexity;
- a possible future archive-injection tool is outside the current task.

Architecture consequence:
- the displacement feature exists specifically to control CombatMove movement **without renaming/repacking animation resources**;
- EV-434's runtime probe proposal to re-prove basic Hit-duration/entity-travel ownership is unnecessary for the current product decision;
- unknown universal root-translation behavior remains outside the claim, but it does not block controlling the proven CombatMove movement mechanism;
- native ledge/obstacle/target stopping behavior should remain preserved rather than converted into exact endpoint teleport/distance semantics.

Disposition:
- **PASS — BASIC COMBAT-MOVEMENT OWNERSHIP / PHASE PRACTICAL BEHAVIOR SUFFICIENT FOR ARCHITECTURE DISCUSSION.**
- **CANCEL — ATTACK_FORWARD_DISPLACEMENT_RUNTIME_PROBE as currently scoped; do not spend a runtime probe to rediscover these established facts.**


### EV-436 — Displacement authoring semantics selected

User authoring decision:
- movement control should be available per existing BehaviorProfile / attack type, analogous to Speed's profile surface;
- configured `1.0` means the movement value authored in the **selected animation resource name**, not New Balance's replacement distance;
- a configured numeric value is a multiplier over that selected-resource authored baseline;
- inactive/Off means preserve the entire live compatible movement stack unchanged.

Examples:
```text
authored filename distance 100, K=1.0 -> authored 100 baseline
authored filename distance 100, K=1.2 -> authored-equivalent 120
authored filename distance 120, K=1.2 -> authored-equivalent 144
```

This intentionally preserves differences between differently authored attacks today. A future archive injector may normalize those authored filename values; if that happens, the same profile multiplier will then act uniformly without changing the runtime feature semantics.

Compatibility consequence:
- with New Balance active and movement configuration inactive, New Balance remains untouched;
- with movement configuration active, G3AB deliberately replaces New Balance's **magnitude ownership** with selected-animation-authored magnitude × configured multiplier;
- final compatible direction and Gothic's downstream obstacle/ledge/target stopping behavior should remain preserved;
- this is not a claim that New Balance's action-table distance equals the filename-authored value; EV-434 proves it generally does not.

Configuration consequence:
- `1.0` is an active override, not a neutral install default under New Balance;
- shipping configuration must therefore represent movement settings as inactive/missing by default, or use an explicit inactive token if keys are surfaced;
- do not populate live `1.0` movement keys everywhere merely for symmetry.

Desired attack-setting surface follows the existing `BehaviorProfiles::AttackType` set:
```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```
Sprint behavior remains evidence-routed rather than gaining a new profile slot merely for symmetry.

Disposition:
- **AUTHORING SEMANTICS FROZEN.**
- remaining research = smallest safe transport/composition architecture, not user-facing meaning.


### EV-437 — New Balance ordinary melee Hit ownership boundary

Clarification of EV-434 action scope against the pinned New Balance action table and native animation inventory.

For the complete ordinary melee attack surface currently represented by G3AB BehaviorProfiles, New Balance supplies its own Hit movement magnitude:

```text
Normal / Action1        covered
Quick selector / Action3 covered
QuickR / Action4        covered
QuickL / Action5        covered
SimpleWhirl / Action6   covered
Sprint / Action9        covered
Whirl / Action10        covered
Pierce / Action11       covered
Hack / Action14         covered
Power / Action2         covered
```

Thus, for every current G3AB movement-profile attack type, New Balance's eligible Hit path normalizes away the native filename-derived magnitude and replaces it with its own action/skill distance policy.

Special factual attack actions outside the current G3AB profile surface:
- `JumpAttack / Action12`: not present in the pinned New Balance `GetCombatMoveLength` replacement switch; native inventory contains 6 Hit assets, so its filename-derived movement survives this New Balance replacement path.
- `RamAttack / Action13`: not present in the switch; no native `RamAttack_Hit` assets are present in the project's 5,991-name inventory.
- `FinishingAttack / Action15`: not present in the switch; native inventory contains 9 Hit assets, so its filename-derived movement survives this New Balance replacement path.
- `GetUpAttack / Action30`: explicitly covered by New Balance with its own Hit movement distance.

Interpretation:
- colloquially, New Balance **does take ownership of all ordinary melee attack Hit movement relevant to the current G3AB attack-profile system**;
- the exceptions are special attack actions outside that current profile surface, not gaps among Normal/Quick/Power/Pierce/Hack/SimpleWhirl/Whirl/Sprint;
- future movement scope must still decide separately whether JumpAttack, FinishingAttack or other special actions should ever be exposed.

Disposition:
- **PASS — NEW BALANCE ORDINARY MELEE HIT MOVEMENT OWNERSHIP IS EFFECTIVELY COMPLETE FOR CURRENT G3AB PROFILE SCOPE.**


### EV-438 — Absolute attack movement architecture static closure

Selected product direction supersedes EV-436's authored-baseline multiplier candidate.

User-facing goal:
- provide per-profile/per-attack **absolute CombatMove distance** in the same authored units used by Gothic animation filename movement fields;
- avoid animation renaming/repacking;
- preserve native/New Balance completely when the setting is inactive;
- when active, G3AB deliberately owns Hit movement magnitude for that configured attack.

Proposed INI semantics:
```text
Normal_Movement=Off
Quick_Movement=Off
Power_Movement=Off
...

Off / missing
= no G3AB movement intervention

Movement=100
= command the Hit as an authored-style CombatMove distance of 100

Movement=0
= no CombatMove movement for that configured Hit
```

A numeric value is therefore absolute, not a multiplier and not a New Balance-relative value.

Static implementation seam — PROVEN SUITABLE:
- native CombatMove final movement call is `Game+0x16B8B7`;
- immediately before it, `ECX` is the `gCCharacterMovement_PS` receiver;
- the third stack argument is the same `SPU.m_DirectionVec` at `SPU+0xFC`;
- project-pinned New Balance inserts `CombatMoveScale` earlier at `Game+0x16B8A9`;
- pinned AttackCollision has no hook/ownership overlap at `+0x16B8A9/+0x16B8B7`.

Therefore a G3AB `mCCallHook::InsertCall` at `+0x16B8B7` can run after New Balance policy and before the untouched native CharacterMovement call. It can receive the current CombatMove args/SPU through the same EBP-relative frame (`[EBP+8]` args, `[EBP+0xC]` SPU) and must preserve the already-loaded ECX CharacterMovement receiver.

Configured algorithm:
```text
if null / non-Hit / unsupported action / no profile / Movement Off:
    return without touching m_DirectionVec

resolve existing BehaviorProfiles identity
map action -> existing attack profile
Sprint -> Power profile inheritance

T = current primary motion max time / request.AniSpeedScale

if configured distance == 0:
    set movement vector magnitude to 0
else if timing invalid or final direction vector is degenerate:
    fail closed, preserve the compatible vector
else:
    normalize the already-final compatible direction
    scale magnitude to configuredDistance / T

return
-> original Game+0x16B8B7 CharacterMovement call executes unchanged
```

Compatibility matrix:
```text
Native + Movement Off
= native filename-derived movement untouched

New Balance + Movement Off
= New Balance action/skill/reach movement untouched

Native + Movement numeric
= G3AB absolute distance ownership

New Balance + Movement numeric
= New Balance runs first normally;
  G3AB then overrides only final Hit magnitude with configured absolute distance

AttackCollision
= no direct movement hook overlap at the selected seam
```

The design requires no New Balance module detection and no hook into a third-party DLL.

Speed compatibility:
- use the request's already-composed `AniSpeedScale`;
- do not call `GetAnimationSpeedModifier`;
- do not recompose Speed;
- compute the same duration relationship used by native/NB movement, so changing Speed changes velocity as required to target the configured nominal distance rather than changing the configured distance itself.

Raise compatibility:
- gate on physical Hit request;
- Raise/Recover remain untouched;
- AddRaise may create separate requests but does not create repeated movement ownership.

Simplicity/modularity:
- one narrow physical hook in `EngineBridge`;
- proposed permanent policy owner `AttackMovement.cpp/.h`;
- existing `BehaviorProfiles` gains optional movement value per `AttackSettings`;
- no runtime state/cache/generation tracking;
- no filename parsing;
- no per-frame polling;
- no Collision change;
- no Speed/Raise policy change.

Configuration parsing:
- movement must support explicit `Off` plus a finite non-negative numeric distance;
- this needs its own parser semantics because Speed intentionally accepts only positive values while movement value `0` is meaningful;
- missing/invalid values fail closed to inactive/Off.

Zero-direction boundary:
- after native/New Balance scaling, a degenerate final vector has no direction to normalize;
- configured positive movement should fail closed rather than invent a facing/target direction;
- inventory review found the ordinary zero-distance Hit set concentrated in `Troll_Stand_None_Fist` Normal/Quick/Power assets, which are not part of the current shipping Troll `Fist_Fist` profile;
- this does not block the current profile implementation;
- future support for turning a genuinely zero-direction attack into a moving attack requires separate evidence rather than a second hook/state machine in v1.

New Balance option-3 note:
- pinned New Balance already exposes global `AttackReachMultiplier` (default 1.0);
- individual action distances remain hardcoded;
- source contains `// TODO Make config values for each reach!`;
- exposing those values in New Balance remains a plausible future collaboration, but it would remain action-wide rather than G3AB's animation-family/loadout profile control.

Disposition:
- **PASS — OPTION 2 IS STATICALLY FEASIBLE WITH A SIMPLE, MODULAR, NATIVE/NEW-BALANCE-COMPATIBLE ONE-HOOK ARCHITECTURE FOR THE CURRENT PROFILE SCOPE.**
- next gate: independent architecture/source-hook review before production implementation freeze.


### EV-439 — Troll None+Fist zero-distance route runtime non-use

User runtime/authoring observation:
- the native `Troll_Stand_None_Fist` attack set contains zero-distance Normal/Quick/Power Hit assets in the inventory;
- the User specifically attempted to make Troll use this `None+Fist` route in game and could not make it occur;
- the factual Troll combat route already used/tested by this project is `Troll_Fist_Fist`, not `Troll_None_Fist`.

Consequence:
- the known zero-distance `Troll_None_Fist` assets are not a practical blocker for the initial absolute-movement feature;
- v1 should still fail closed on a degenerate final movement direction because that is the simple safe generic rule;
- do **not** add an earlier direction-capture hook or state machine solely to support this unobserved route;
- if a future real gameplay fixture proves a used zero-direction attack needs positive configured movement, reopen that case with evidence.

Disposition:
- **PASS — NO SECOND MOVEMENT HOOK / DIRECTION STATE JUSTIFIED FOR V1.**


### EV-440 — Absolute attack movement independent architecture review PASS

Review mode:
- bounded read-only independent Sol 6.1 Extra High architecture/source-hook review;
- required remote development HEAD `39f39a28184c7ad14edde12a2f1a1108456c17f5`;
- POP-10 preflight completed;
- no source/docs/build/deploy/runtime/probe/commit changes made by the reviewer.

Findings:
```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    3
```

Mandatory implementation details promoted from the review notes:
1. freeze the exact `+0x16B8B7` register/stack transport;
2. compute and validate the replacement velocity as finite before mutating the movement vector;
3. retain the existing bounded profile lookup; no lookup redesign is justified.

Exact tested call-site transport:
```text
ECX       = gCCharacterMovement_PS receiver from SPU+0x12C
[ESP]     = native enable arg 1
[ESP+4]   = native local target-proxy reference
[ESP+8]   = vector reference -> SPU+0xFC
[EBP+8]   = current CombatMove request
[EBP+0xC] = current SPU
```

`Game+0x16B8B7` is the five-byte call to `Game+0xEA0C0`:
```cpp
EnableCombatMovementFromSPU(
    GEBool, eCEntityProxy const &, bCVector &);
```

Frozen safest hook transport:
```cpp
.Prepare(RVA_Game(0x16B8B7), &<movement helper>)
.InsertCall()
.AddPtrStackArgEbp(0x8)
.AddPtrStackArgEbp(0xC)
.AddPtrStackArg(0x8)
.SaveReg(mERegisterType_Ecx)
.Hook();
```

The helper is `void GE_STDCALL` and receives the CombatMove request, SPU and existing native vector reference. The pinned SDK hook builder accounts for saved-register/added-argument offsets. ECX is restored before the relocated original call; the native arguments remain intact.

Compatibility conclusions:
- New Balance replaces the six-byte receiver load at `+0x16B8A9`; G3AB inserts at the separate five-byte call `+0x16B8B7`;
- the ranges do not overlap, so either DLL installation order preserves New Balance first, G3AB second, native movement call last;
- Off returns without normalizing, scaling or assigning the vector;
- request `AniSpeedScale` is already the final composed Speed value;
- `maxTime / AniSpeedScale` is the correct duration basis;
- physical Hit gating excludes Raise/Recover and needs no continuation state;
- Sprint's proven shared route constructs an Action2 Hit request at `Script_Game+0x47FA8`, so it inherits `Power_Movement`;
- pinned AttackCollision has no movement-seam ownership; its reviewed Hack route reaches the same downstream native CombatMove seam.

Fail-closed production requirements:
- missing / Off / invalid / negative / non-finite Movement = inactive;
- numeric zero = valid and clears the vector without normalization;
- null/entity/action/physical-Hit/timing context is validated before mutation;
- positive Movement requires finite positive duration, non-degenerate final direction and a finite computed replacement;
- compute replacement locally and write only after all validation succeeds.

Explicit verdicts:
```text
hook/ABI safety               PASS
native compatibility          PASS
New Balance compatibility     PASS
AttackCollision compatibility PASS
Speed compatibility           PASS
Raise compatibility           PASS
profile architecture          PASS
simplicity                    PASS
modularity                    PASS
performance                   PASS (static)
production-freeze readiness   PASS
```

Collision ownership/lifecycle requires no changes. Native stopping/navigation/interruption remain authoritative; the setting controls nominal CombatMove distance.

Independent final result:
- **PASS WITH NON-BLOCKING NOTES**
- the notes above are mandatory production constraints, not open architecture questions.

Disposition:
- **PASS — RESEARCH / ARCHITECTURE CLOSED; READY FOR BOUNDED PRODUCTION IMPLEMENTATION.**


### EV-441 — Absolute attack movement production source review PASS

Reviewed implementation:
- production commit `7393f390f30d1981a5065b6342a684cd590fbac9`;
- parent `8a9e91deb5c6fe13d2526b322c8e67f91bcb1a6a`;
- exactly seven allowed production files changed.

Findings:
```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    0
```

Source review confirms:
- exactly one new physical hook, `Game+0x16B8B7`;
- hook transport matches EV-440 exactly:
  `.InsertCall().AddPtrStackArgEbp(0x8).AddPtrStackArgEbp(0xC).AddPtrStackArg(0x8).SaveReg(ECX)`;
- RtPatch hook-builder semantics were independently checked: EBP arguments pass the current request/SPU pointers, the ESP-relative pointer argument passes the existing native movement vector reference, ECX is restored, and the relocated native CharacterMovement call remains intact;
- `AttackMovement` is stateless and owns policy; `EngineBridge` owns transport only;
- supported factual actions are exactly Normal, QuickR/L, Power, Pierce, Hack, SimpleWhirl and Whirl;
- Sprint naturally inherits Power through its factual Action2 Hit request;
- physical phase is exact `Hit`; Raise/Recover are untouched;
- Movement missing/Off/invalid/negative/non-finite remains inactive;
- Movement=0 is active and clears the vector directly;
- positive movement consumes the already-composed request `AniSpeedScale`, obtains current primary max time, computes duration and replacement locally, validates all values, then writes once;
- no animation filename parsing, New Balance detection, AttackCollision hook, Speed query/recomposition, state/cache or per-frame work exists;
- all 27 shipping profiles were checked: 97 represented attack settings have exactly 97 `_Movement=Off` keys; no active shipping movement key exists;
- CMake adds only `AttackMovement.cpp/.h`;
- Collision, AttackSpeed and AttackRaise source are unchanged.

Official SDK compile-surface cross-check:
- required `PSAnimation` validity/property-set surfaces exist at the official Georgeto pin;
- `eCVisualAnimation_PS::HasActor/GetActor`, actor `HasMotionInstance/GetMaxTime`, request `AniSpeedScale`, and `bCVector::Clear` exist;
- implementation uses motion enum value 0 intentionally, avoiding dependency on Jackydima's named enum extension.

Compatibility verdicts:
```text
hook/ABI safety               PASS
native compatibility          PASS
New Balance compatibility     PASS
AttackCollision compatibility PASS
Speed compatibility           PASS
Raise compatibility           PASS
profile architecture          PASS
simplicity                    PASS
modularity                    PASS
performance                   PASS (static)
source readiness              PASS
```

No build was performed in review.

Disposition:
- **PASS — SOURCE READY FOR USER-LOCAL BUILD / DEPLOY / RUNTIME ACCEPTANCE.**


### EV-442 — Absolute attack movement local build PASS

User-local build result:
- production source under test: `7393f390f30d1981a5065b6342a684cd590fbac9`;
- Release Win32 build completed successfully on the User's authoritative local environment;
- no source correction was required after EV-441 source review.

Deployment/runtime state at session end:
- deployment had **not yet been executed**;
- built/live DLL SHA256 identity had **not yet been verified**;
- source/live INI SHA256 identity had **not yet been verified**;
- runtime testing had **not yet begun**.

The previously used deployment/hash-verification PowerShell procedure was reviewed against the new movement feature and remains suitable unchanged:
- deploys `Script_G3AnimationBehaviors.dll`;
- deploys the updated shipping `G3AnimationBehaviors.ini`;
- removes old G3AB diagnostic/project DLLs only;
- leaves New Balance / AttackCollision untouched;
- verifies exactly one live G3AB project DLL;
- verifies built/live DLL SHA256 equality;
- verifies source/live INI SHA256 equality;
- reports `G3AB RELEASE DEPLOYMENT PASS` only after all checks succeed.

Next gate:
- deploy and provide the full verification output;
- then run the Off-path compatibility control before enabling any numeric Movement value.

Disposition:
- **BUILD PASS; DEPLOYMENT / HASH IDENTITY / RUNTIME PENDING.**


### EV-443 — Absolute movement deployment and 2H runtime mechanism PASS

Deployment identity:
```text
Built DLL SHA256: 3E0DFA5D4FF5DE9F3FADCABF27C7C50B887EF1E63318FF31A9B998D82714BF0D
Live  DLL SHA256: 3E0DFA5D4FF5DE9F3FADCABF27C7C50B887EF1E63318FF31A9B998D82714BF0D

Source INI SHA256: 93C9DA487DDBBA301F0D9AC7A751C0D2CC8DFE2415305E1C1BD89A37A3CC9632
Live   INI SHA256: 93C9DA487DDBBA301F0D9AC7A751C0D2CC8DFE2415305E1C1BD89A37A3CC9632

G3AB RELEASE DEPLOYMENT PASS
```

Exactly one live G3AB project DLL was present:
`Script_G3AnimationBehaviors.dll`, 466944 bytes.

User runtime test:
- profile family: Hero 2H;
- tested factual attack groups: Normal, Quick, Power, Whirl and Hack;
- tested movement settings: Off, 0, 100 and 300;
- repeated both with New Balance active and without New Balance;
- all cases worked as intended;
- every numeric step produced clearly visible movement changes;
- Off preserved the underlying native/New Balance behavior;
- no reported Speed, Raise or Collision regression.

This is direct runtime confirmation of the core compatibility contract across all five available 2H attack groups.

Post-test UX finding:
- public key name `<Attack>_Movement=Off` can be misread as disabling attack movement rather than disabling the override;
- before broader acceptance, rename the unreleased public key to `<Attack>_MovementOverride`;
- internal movement architecture/policy remains unchanged.

Disposition:
- **PASS — DEPLOYMENT IDENTITY + CORE 2H MOVEMENT MECHANISM / NEW BALANCE COMPATIBILITY.**
- broader representative acceptance remains pending after the public-key rename/rebuild sanity check.


### EV-444 — MovementOverride public INI rename

Trigger:
- EV-443 runtime mechanism testing passed across 2H Normal, Quick, Power, Whirl and Hack with Off/0/100/300, both with and without New Balance;
- User identified a public-UX ambiguity: `Power_Movement=Off` can read as though Power attack movement itself is disabled.

Accepted pre-release public rename:
```text
<Attack>_Movement
->
<Attack>_MovementOverride
```

Examples:
```ini
Normal_MovementOverride=Off
Quick_MovementOverride=Off
Power_MovementOverride=Off
Power_MovementOverride=100
```

Semantics are unchanged:
```text
Off = preserve normal native/New Balance movement
0 = no forward CombatMove translation
positive number = absolute configured forward movement distance
```

Implementation scope:
- `BehaviorProfiles.cpp`: parser suffix only, `_Movement` -> `_MovementOverride`;
- internal `hasMovement/movement` storage remains unchanged;
- `AttackMovement.cpp/.h` unchanged;
- `EngineBridge.cpp` unchanged;
- hook/ABI/runtime architecture unchanged;
- shipping INI uses 97 `_MovementOverride=Off` keys and zero legacy `_Movement=` keys;
- User's clearer INI section separators were preserved;
- movement instructions were simplified to user-facing language and no longer expose CombatMove implementation terminology unnecessarily.

Final public help:
```text
MovementOverride controls how far the character moves forward during an attack.
Off = keep the normal Gothic / New Balance movement.
0 = no forward movement.
Higher number = move farther forward.
Gothic can still stop the character at obstacles, ledges, or the target.
Sprint uses the Power_MovementOverride setting.
```

Disposition:
- **PASS — PRE-RELEASE PUBLIC CONFIGURATION CLEANUP; NO ARCHITECTURE CHANGE.**
- one rebuild/deploy + small previously-proven 2H sanity check is required before broader runtime acceptance continues.


### EV-445 — Absolute attack movement broad runtime acceptance PASS

Deployment after EV-444 public-key rename:

```text
Built DLL SHA256: 4F05583E74F0B2F49FBC3682DB244EDE86C277BA810DBFE0C985859D69A32B68
Live  DLL SHA256: 4F05583E74F0B2F49FBC3682DB244EDE86C277BA810DBFE0C985859D69A32B68

Source INI SHA256: AFD46B80BEAC942860B537030BA7AA89EECDFE1F5CD2F57F0621A1B32FB25548
Live   INI SHA256: AFD46B80BEAC942860B537030BA7AA89EECDFE1F5CD2F57F0621A1B32FB25548

G3AB RELEASE DEPLOYMENT PASS
```

Exactly one live G3AB project DLL was present:
`Script_G3AnimationBehaviors.dll`, 466944 bytes.

Broad user runtime acceptance:

Human / standard animation families:
- 1H;
- Torch+1H;
- Shield+1H;
- dual 1H+1H;
- 2H;
- Staff;
- Fist.

Across every attack available to those families, the User tested:
- Normal;
- Quick;
- Power;
- Whirl;
- SimpleWhirl;
- Hack;
- Pierce;
using `MovementOverride=Off / 0 / 100 / 300`, both with and without New Balance.

Separated/custom families:
- Axe;
- Rapier.

Across every available attack for those families, the User tested:
- Normal;
- Quick;
- Power;
- Whirl;
- SimpleWhirl;
- Hack;
- Pierce;
using `MovementOverride=Off / 0 / 500`, both with and without New Balance.

Nonhuman representative families:
- Troll;
- Sabertooth;
- Demon.

For applicable Normal / Quick / Power / Sprint routes, the User tested:
- `MovementOverride=Off`;
- `MovementOverride=500`;
both with and without New Balance.

All tests behaved as expected.

Zero-authored-movement boundary — runtime confirmed:
- Rapier Quick attacks are authored with movement field `0` in the animation name;
- with that authored `0`, G3AB could not create forward movement, exactly as the late-hook fail-closed architecture predicts because no usable direction survives to the final seam;
- after changing the Rapier Quick animation movement field from `0` to `100`, `MovementOverride` controlled the attack correctly;
- this was verified both with and without New Balance, including Off / 0 / 500 controls.

Interpretation:
- EV-439's generic zero-direction fail-closed rule is now directly demonstrated on a real used attack family;
- no second hook, direction cache or earlier capture is justified;
- the limitation is user-visible and is documented in the shipping INI:
  `MovementOverride cannot add movement to an attack whose animation name has movement value 0. Rapier Quick attacks are a known example.`

Compatibility result:
- Off restores/preserves native or New Balance ownership;
- numeric zero removes CombatMove translation;
- positive numeric values clearly control forward distance;
- New Balance and native operation both remain compatible;
- Sprint->Power inheritance works in representative nonhuman testing;
- no reported Speed, Raise or Collision regression across the acceptance matrix.

Disposition:
- **PASS — ABSOLUTE ATTACK MOVEMENT RUNTIME ACCEPTED.**
- feature architecture remains one-hook/stateless; no source redesign required.


### EV-446 — First-release baseline integration review PASS

Reviewed branch state:
- `development` at `dcbfd0389c6507f3a1d4168264f248b610ddde8b`;
- stable `main` before promotion at `56565a73137c799fc625c2f0b4f17cb153554bdb`;
- `development` was 85 commits ahead and 0 behind `main`;
- comparison was a pure fast-forward lineage.

Review scope:
- quick release-integration sanity review, not a new feature redesign;
- accepted Collision, Speed, Raise and Movement runtime evidence remains authoritative.

Production delta from the previous stable `main`:
```text
AttackMovement.cpp/.h        new movement policy owner
BehaviorProfiles.cpp/.h      MovementOverride configuration
EngineBridge.cpp             one Game+0x16B8B7 movement insertion
CMakeLists.txt               AttackMovement module inclusion
G3AnimationBehaviors.ini     MovementOverride public configuration/help
```

Release-hygiene findings:
- `docs/work/active/` contains only its README; no stale active investigation/task;
- production target `Script_G3AnimationBehaviors` contains no probe/logger/test source;
- exactly one movement insertion exists at `Game+0x16B8B7`;
- no hook exists at New Balance's `Game+0x16B8A9` seam;
- parser accepts only the final public `_MovementOverride` suffix;
- shipping INI contains exactly 97 `_MovementOverride=Off` keys and zero legacy `_Movement=` keys;
- Collision, Speed and Raise production ownership remain unchanged by the movement integration;
- post-EV-445 delta to current HEAD is exactly one explanatory INI comment-line change;
- EV-445 closure commit `b36804949a8b3af0ab145d16128234c313886d82` had knowledge-state validation PASS;
- the one-commit delta to `dcbfd038...` changes no executable/config semantics.

Non-blocking release-hygiene note:
- root CMake retains long-standing `G3AB_BUILD_PROTOTYPES=ON` and `G3AB_BUILD_TOOLS=ON` defaults, so a full repository build may also build diagnostics;
- the production target itself is clean and the accepted deployment procedure ships/verifies only `Script_G3AnimationBehaviors.dll` + INI and removes old G3AB diagnostic runtime products;
- do not change this build-policy surface as part of the first-release baseline unless a packaging task later requires it.

Accepted feature state:
```text
Collision = CLOSED/PASS
Speed     = CLOSED/PASS
Raise     = CLOSED/PASS
Movement  = CLOSED/PASS through EV-445
```

Disposition:
- **PASS — CURRENT DEVELOPMENT IS A CLEAN FIRST-RELEASE STABLE BASELINE CANDIDATE.**
- safe to fast-forward `main` to the reviewed development lineage before beginning the final bad-block-skip timer fix.


### EV-447 — Stable baseline promoted to main

After EV-446 release-integration review PASS, `main` was fast-forwarded from:
`56565a73137c799fc625c2f0b4f17cb153554bdb`

to:
`e899f37092706a9846312b93d6b52b34e715b53d`

Promotion properties:
- fast-forward only;
- no merge commit;
- no force update;
- `development` was 0 behind `main`;
- at the promotion moment, `main` and `development` pointed to the exact same commit.

Stable baseline now on `main`:
```text
Collision = accepted
Speed     = accepted
Raise     = accepted
Movement  = accepted through EV-445
```

This is the pre-final-fix stable checkpoint for the first public release.

Next work is intentionally isolated back on `development`:
- investigate whether the existing bad-block-skip defer timer can be paused while an attack is active;
- no other new feature work before first release.


### EV-448 — Bad block skip exact-pause static research CLOSED / deferred from v1

Mode:
- bounded read-only static research;
- Desktop Commander used only for read-only inspection/disassembly of the actual tested local binaries;
- no source edits, builds, deployment, runtime execution, debugger attachment or binary patching.

Verified authority:
- research start `development @ 185989059519e09782755ec9faa4644517975567`;
- stable fallback `main @ e899f37092706a9846312b93d6b52b34e715b53d`;
- tested `Script_Game.dll` SHA256 `4D29189281EC26EAC7C704FA67ED323DF5C090D50B068626CF600AECF4262A24`.

Player path recovered:
```text
Script_Game +0x633BF duration getter
+0x633C5 compare 2500
+0x633CA jbe +0x63586
otherwise:
+0x633F1 FullStop
+0x63409 SetState PS_Melee_Loop
```

The exact call-site can support a stateless branch-local **deferral** adapter, but that does not preserve remaining block time because native held-input duration continues advancing.

NPC timeout independently recovered:
```text
OnAI_Parade
Alternative AI
non-player
StatePosition == 1
StateTime > 2.0
-> +0x46F39 StopAIGoto
-> +0x46F51 SetState ZS_Attack_Loop
```

Player and NPC do not share one timer mechanism or one call-site fix.

NPC timeout overlap with a factual active attack remains unproven. Smallest future probe, if reopened: observation-only wrapper at `Script_Game +0x46F39`.

Exact remaining-time pause would require new stateful timer-episode/attack-interval ownership whose lifecycle is not yet proven.

Disposition:
- **NOT CLEAN ENOUGH FOR FIRST RELEASE for exact remaining-time pause.**
- do not freeze the stateless deferral candidate as if it satisfied pause/resume;
- leave first-release stable behavior unchanged;
- park exact pause / NPC-overlap investigation for post-release work.

Durable report:
`docs/archive/investigations/bad_block_skip_static_research_2026-10-06.md`.
