# Gothic 3 Animation Behaviors — Evidence Ledger

**Status:** Canonical evidence ledger  
**Date:** 2026-08-22

## 1. Purpose

This ledger prevents hypotheses becoming facts by repetition, design preferences being confused with engine behavior, and old prototype limitations being mistaken for architecture limits.

Statuses:

- **CONFIRMED**
- **STRONGLY SUPPORTED**
- **WORKING HYPOTHESIS**
- **UNKNOWN**
- **DESIGN DECISION**

## 2. Ledger

| ID | Statement | Status | Provenance / note | Engineering consequence |
|---|---|---|---|---|
| EV-001 | CombatMove carries Self, Target, Action, PhaseName, and AniSpeedScale. | CONFIRMED | SDK + runtime logger | Core phase/speed/target diagnostic layer. |
| EV-002 | 2H normal Attack originally requests Hit at 0.700 without Raise. | CONFIRMED | controlled logger | Raise must be inserted if desired. |
| EV-003 | 1H normal Attack Hit was observed at 0.600. | CONFIRMED | controlled logger | Stock weapon families have different timing. |
| EV-004 | QuickAttack Hit was observed at 1.000. | CONFIRMED | controlled logger | Quick baseline differs from normal Attack. |
| EV-005 | PowerAttack uses native Raise before Hit; tested Raise 1.500, Hit 1.000. | CONFIRMED | controlled logger | Native PowerAttack is a reference sequence. |
| EV-006 | `PREPEND_BREAK_BLOCK` can insert an asynchronous Raise before original PS_Melee_Attack. | CONFIRMED | controlled prototype | Proven Raise architecture. |
| EV-007 | Engine resolves correct P0/P1 Raise automatically after action+phase request. | CONFIRMED | controlled prototype | Avoid exact filename construction. |
| EV-008 | Ordinary Recover visibly plays without appearing as a normal separate external CombatMove request in the original logger. | CONFIRMED | runtime | Recover can be internally initiated. |
| EV-009 | Controlled Recover should follow effective Hit speed. | DESIGN DECISION | project design | No planned user-facing RecoverSpeed tuning key. |
| EV-010 | `GetAnimationSpeedModifier` hook at Script_Game + 0x42A0 can observe/override action/phase speed. | CONFIRMED | prototype/source | Speed control feasible; compatibility still open. |
| EV-011 | Current upstream speed hook conflicts with NewBalance when both own the same path. | CONFIRMED | integration test | Production speed authority should not rely on unsafe hook competition. |
| EV-012 | Custom Blender frame-effect strings survive export into `.xmot`. | CONFIRMED | controlled frame-effect logger | Animation-authored marker channel is viable. |
| EV-013 | `UpdateFrameEffects` dispatches authored effects through `StartEffect`. | CONFIRMED | reverse engineering + runtime | Marker callback can execute code at authored frame. |
| EV-014 | `eSFrameEffect` tested layout is stride 8, frame at +0x00, name at +0x04. | CONFIRMED | runtime/reverse engineering | Used by current prototype; build-specific. |
| EV-015 | Exact current motion's frame-effect list can be inspected before marker fires. | CONFIRMED | v0.4/v0.5 prototype | Enables pre-marker ownership decision. |
| EV-016 | Marker presence can suppress native timed Normal activation for that exact execution. | CONFIRMED | v0.5 | Prevents native collision from activating before marker. |
| EV-017 | Marker firing can activate right weapon collision and clear triggered list. | CONFIRMED | v0.5 | Causal authored-frame collision proof. |
| EV-018 | Collision ownership follows marker presence rather than P0/P1. | CONFIRMED | reversal test | Do not encode pose as ownership. |
| EV-019 | Weapon collision naturally resets Item_Attack 7 -> Item_Equipped 5 at Hit -> Recover. | CONFIRMED | SetCollisionGroup hook | Normal single-hit attacks do not require end marker. |
| EV-020 | Marker timing remains synchronized to authored frame under playback-speed change. | CONFIRMED | slow/1.0 speed tests | Frame collision works with later speed tuning. |
| EV-021 | Marker-to-collision operation delay measured about 0.02–0.03 ms in tested path. | CONFIRMED | runtime logging | Callback latency is negligible relative to animation frame timing. |
| EV-022 | For tested 12-frame 2H normal attack, marker frame 8 felt better than frame 9 where first plausible contact occurred. | CONFIRMED FOR TESTED ATTACK | controlled animation test | Useful authoring guideline only for that attack. |
| EV-023 | Collision should always start one frame before contact. | UNKNOWN | no broad test | Do not generalize frame-8 result globally. |
| EV-024 | Staff normal marker-controlled collision works on player. | CONFIRMED | v0.6 | Source resolver can support Staff item path. |
| EV-025 | Staff normal marker-controlled collision works on human NPC's own halberd. | CONFIRMED | v0.6 NPC test | System is not inherently player-only. |
| EV-026 | QuickAttack markers fire on Staff Quick animations. | CONFIRMED | runtime | Marker channel itself works for Quick. |
| EV-027 | v0.6 rejects Quick ownership because of Normal-specific `_Attack_Hit_` eligibility. | CONFIRMED | runtime/prototype logic | Replace filename-only eligibility with callback + exact action + Hit phase + exact-motion marker. |
| EV-028 | `OnAI_QuickAttack` is the relevant callback family for QuickAttackR/L variants. | CONFIRMED | Jackydima source/runtime action values | v0.7 should handle this callback. |
| EV-029 | Marked Fist tests can damage via left leg, right leg, right hand, and left hand with native timed activation suppressed. | CONFIRMED | controlled tests | Physical contact is not tied to a literal right-hand weapon. |
| EV-030 | Logical right-slot Fist entity remains collision group 0 when SetCollisionGroup(Item_Attack) is called. | CONFIRMED | runtime logging | Fist does not behave like normal weapon collision group. |
| EV-031 | Fist `SetCollisionGroup` is unnecessary for damage. | WORKING HYPOTHESIS | not yet isolated | Test by removing only group call while keeping ClearTriggeredList. |
| EV-032 | Triggered-list clearing is the critical Fist rearm operation. | STRONGLY SUPPORTED | current observations | Needs dedicated causal isolation. |
| EV-033 | Repeated multi-hit strikes need rearming/triggered-list clearing. | STRONGLY SUPPORTED | dual-power/whirl source + behavior | Production multi-hit helper should support repeated rearm. |
| EV-034 | `RIGHT / LEFT / BOTH / OFF` are final marker names. | UNKNOWN / PROPOSAL | current preferred design direction only | Keep generic source markers as candidates; do not mass-author yet. |
| EV-035 | Same-function hooks from independent DLLs chain safely. | UNKNOWN | hook implementation not fully validated | Do not rely on load order. |
| EV-036 | Human actors share Hero-family animations despite different body/armature object names. | STRONGLY SUPPORTED | extensive animation modding + NPC test | Hero must not be treated as player-only. |
| EV-037 | Composite Pxx pose labels are meaningful and must be preserved. | STRONGLY SUPPORTED | repeated asset/runtime behavior | Do not simplify pose identifiers. |
| EV-038 | Destination pose token controls/participates in resulting stance. | STRONGLY SUPPORTED | repeated renaming/mod tests | Preserve destination pose semantics. |
| EV-039 | Final `L/R` filename token is exact physical collision-source selector. | UNKNOWN | source says likely attack direction | Do not use as collision ownership authority. |
| EV-040 | `_00_%_00_` has a defined known gameplay meaning. | UNKNOWN | no established evidence | Treat as opaque. |
| EV-041 | Movement numeric suffixes are literal blend weights. | WORKING HYPOTHESIS | source speculation | Do not encode as confirmed engine rule. |
| EV-042 | Raw `gEUseType` must be normalized to animation tokens for animation-profile matching. | CONFIRMED AS MAPPING REQUIREMENT | supplied mapping + asset names | Axis of INI/runtime profile matching. |
| EV-043 | Missing configuration should leave native behavior untouched. | DESIGN DECISION | project safety principle | Required production fallback. |
| EV-044 | Unmarked animation should leave legacy/native collision ownership untouched. | DESIGN DECISION + PROVEN PROTOTYPE PATTERN | v0.5/v0.6 | Required frame-collision opt-in behavior. |
| EV-045 | Jackydima current WhirlAttack path sets `PropertyResetOnUntouch = GETrue`. | CONFIRMED | commit `da61a791...` | Relevant to repeated-contact Whirl behavior. |
| EV-046 | Exact Quick/QuickR/QuickL action values are required by the current stateless v0.7 marker path. | DESIGN DECISION | `OnAI_QuickAttack` scopes suppression earlier, but global `StartEffect` later lacks callback identity | Use exact action + Hit phase + exact marker to correlate the global marker; avoid per-execution state until needed. |
| EV-047 | Dual P0 Normal uses the left weapon as collision source. | STRONGLY SUPPORTED | animation-author empirical evidence + current third-party source behavior | Preserve when source-explicit markers/general resolver replace the right-hand prototype. |
| EV-048 | Dual P1 Quick uses the left weapon as collision source. | STRONGLY SUPPORTED | animation-author empirical evidence + current third-party source behavior | Left-source Quick support is required before marking this animation. |
| EV-049 | A Dual P3 Quick animation file exists and visually represents a left-weapon attack. | STRONGLY SUPPORTED | animation-author file/animation evidence | Catalog the exact file when the animation list is added. |
| EV-050 | Gothic 3 normally resolves/uses the Dual P3 Quick animation file in gameplay. | UNKNOWN | runtime use not confirmed | Do not claim native runtime use until observed. |
| EV-051 | Torch+1H P1 and P3 Quick attacks use the left torch as collision source. | STRONGLY SUPPORTED | animation-author empirical evidence; P1 also converges with third-party source | Left-source marker/resolver must cover both poses before marking these animations. |
| EV-052 | Some Torch+1H P0 Normal attacks natively activate left-torch collision, but that is unintended for those animations. | STRONGLY SUPPORTED | animation-author empirical evidence | Do not preserve the erroneous native left-source behavior as intended design. |
| EV-053 | Jackydima routes regular Torch+1H Normal collision to the right weapon. | CONFIRMED | current `Script_AttackCollision` source/comment | Useful correction/reference behavior for future source handling. |
| EV-054 | Dual P1 Pierce uses the left weapon as collision source. | STRONGLY SUPPORTED | animation-author empirical evidence + current third-party source behavior | Required future Pierce source case. |
| EV-055 | Jackydima's Dual Power path activates both equipped weapons and rearms both for later contact. | CONFIRMED | current `Script_AttackCollision` source | Good reference for eventual BOTH marker and multi-hit rearm. |
| EV-056 | Native Dual P0 Power may use the left weapon. | WORKING HYPOTHESIS | user recollection; not isolated | Keep separate from confirmed desired BOTH behavior. |
| EV-057 | One Dual finishing animation may visually contact with both weapons while only one source damages; the exact native source is not yet known. | UNKNOWN | animation-author recollection not yet isolated | One damaging source is acceptable for that specific animation, but do not generalize. |
| EV-058 | `gCScriptRoutine_PS` exposes a two-valued `HitDirection` property (`Left`, `Right`). | CONFIRMED | official SDK enum + property-set declaration | Logical left/right combat state exists independently of physical collision geometry. |
| EV-059 | Attack/reaction R/L is a physical right-hand/left-hand collision-source selector. | CONTRADICTED | Torch+1H and Dual empirical source cases; both QuickAttackR/L can use the same left source | Never resolve collision hand from action R/L or final filename R/L. |
| EV-060 | Final attack R/L and R/L action variants correlate with logical attack/hit direction. | STRONGLY SUPPORTED | complete 5,991-name inventory; SDK `HitDirection`; Jackydima's disabled Normal pose mapping | Preserve as direction metadata for later analysis, not as current runtime authority. |
| EV-061 | The exact causal pipeline from action/final R/L through `Routine.HitDirection` to victim `StumbleR/L` is known. | UNKNOWN | correlation only; no controlled property-forcing test or native reaction source trace | No current plan depends on it; test only if a later feature needs it. |
| EV-062 | Hero QuickStumble is a systematic non-R/L family. | CONFIRMED AS INVENTORY OBSERVATION | 104 native Hero entries; P0/P1/P2/P3 patterns across 1H, Staff, Shield+1H, Torch+1H | A large visual lean or stance change does not imply an R/L reaction action. |
| EV-063 | Visible weapon travel determines Gothic 3's logical left/right hit direction at contact time. | CONTRADICTED | animation-author controlled visual reversal retained gameplay behavior | Treat direction as authored/selected combat state, not physics-derived motion analysis. |
| EV-064 | CombatMoveLogger v0.4 currently records `Routine.HitDirection`. | CONTRADICTED | current logger source audit | Optional future diagnostic: add HitDirection only if direction becomes relevant to implementation. |
| EV-065 | Native filenames contain `LightStumble`, but the SDK declares a separate `gEAction_LightStumble`. | CONTRADICTED | inventory + official `gEAction` enum | Do not assume every serialized action token is a 1:1 enum spelling; exact LightStumble mapping remains open. |
| EV-066 | FrameCollision v0.7 candidate implements marked Quick/QuickR/QuickL ownership through `OnAI_QuickAttack`, Hit phase, exact-motion marker, and the unchanged right-hand source resolver. | CONFIRMED AS SOURCE IMPLEMENTATION AND BUILD; RUNTIME FAILED | commit `04d12f8`; standalone build; controlled player Staff Quick log, 2026-08-22 | Initial QuickR/L activation waits for the marker, but post-Hit native reactivation prevents promotion. |
| EV-067 | FrameCollision v0.7 preserves marked player Staff Normal P0/P1 behavior: each execution suppressed the native callback, activated the right-hand Staff only at authored marker frame 5, cleared the triggered list, and naturally reset 7 -> 5. | CONFIRMED | controlled v0.7 runtime log, 2026-08-22; both executions were `Action: 1` and `_Attack_Hit_` | Normal regression path passed; this run does not validate Quick ownership. |
| EV-068 | For marked player Staff QuickAttackR (`Action: 4`) and QuickAttackL (`Action: 5`), v0.7 suppressed pre-marker native activation and accepted marker frame 6, but immediately after each natural 7 -> 5 reset the Staff was switched 5 -> 7 again without another marker. | CONFIRMED | controlled v0.7 runtime log, 2026-08-22 | v0.7 Quick ownership is incomplete and leaves collision active between attacks; do not ship or expand it. |
| EV-069 | The post-Hit Quick reactivation occurs because marker ownership leaves `Routine.PropertyStatePosition` at 0, allowing the original Quick callback to perform its one-shot timed activation later. | STRONGLY SUPPORTED | marker log shows `StatePosition: 0`; Jackydima `OnAI_QuickAttack` gates activation on 0 and sets 1 after activation; exact native callback trace not yet captured | Smallest next candidate: set StatePosition to 1 only when an accepted Quick marker performs activation, then retest. |
| EV-070 | The attempted moving Staff Quick selected P0 QuickAttackR/action 4 again rather than generic Quick/action 3. | CONFIRMED FOR TESTED INPUT | third execution in controlled v0.7 log | Generic Quick/action 3 remains runtime-untested; do not infer that moving always selects a separate action. |
| EV-071 | FrameCollision v0.8 sets `Routine.PropertyStatePosition` to 1 only when an accepted Quick marker activates/rearms collision, and logs its before/after values; Normal marker behavior is not mutated. | CONFIRMED AS SOURCE IMPLEMENTATION, BUILD, AND PLAYER RUNTIME | commit `f4d2946`; standalone Win32 Release build; controlled v0.8 player Staff log, 2026-08-22 | The narrow bookkeeping completion fixes the tested v0.7 Quick post-reset reactivation without regressing marked Normal behavior. |
| EV-072 | For marked player Staff QuickAttackR (`Action: 4`) and QuickAttackL (`Action: 5`), v0.8 accepted marker frame 6 with `StatePosition` 0 -> 1, performed the only 5 -> 7 activation, and naturally reset 7 -> 5 without a later unmarked reactivation. | CONFIRMED | controlled v0.8 runtime log, 2026-08-22 | Player QuickR/L regression is passed; proceed to NPC Staff Quick validation before expanding callback families or source meaning. |
| EV-073 | FrameCollision v0.8 preserves marked player Staff Normal behavior: marker frame 5 performs 5 -> 7 activation and the engine naturally resets 7 -> 5. | CONFIRMED | controlled v0.8 runtime log, 2026-08-22; `Action: 1` | Shared activation/reset core remains compatible with the separate Normal callback adapter. |
| EV-074 | FrameCollision v0.8 marker-controls human NPC Staff Quick attacks on the NPC's own equipped source: `OutNovice_01` produced two QuickAttackR/action 4 and five QuickAttackL/action 5 executions using `It_Halberd_01`; every marker changed StatePosition 0 -> 1, activated 5 -> 7, and naturally reset 7 -> 5 without immediate reactivation. | CONFIRMED | controlled v0.8 NPC runtime log, 2026-08-22 | QuickR/L ownership and the narrow bookkeeping fix are not player-specific; the right-hand prototype source resolves against the current actor. |
| EV-075 | Generic Quick/action 3 did not occur in the controlled v0.8 NPC Staff session. | CONFIRMED FOR TESTED SESSION | 16 accepted markers included Normal/action 1, QuickR/action 4, and QuickL/action 5 only | Generic Quick/action 3 remains unvalidated; do not infer support from QuickR/L results alone. |
| EV-076 | The official SDK declares raw `gEUseType_Fist = 8` and `gEUseType_PhysicalFist = 55`. | CONFIRMED | pinned official SDK `GameEnum.h` at `90bfd344...` | These raw UseTypes can scope the Fist-only causal branch without using animation names or collision group 0 as identity. |
| EV-077 | The initial FrameCollision v0.9 source attempted to call `GetUseType()` directly on the script-layer `Entity` wrapper. | CONFIRMED BUILD FAILURE | commit `89f36d8`; MSVC C2039 at all wrapper calls, 2026-08-22 | `Entity` does not expose `GetUseType()`; do not repeat this access pattern. The installed validated v0.8 DLL was not replaced. |
| EV-078 | The first v0.9 accessor correction called `GetUseType()` as an `eCEntity` member after `Entity.GetInstance()`. | CONFIRMED BUILD FAILURE | commit `9b4a73c`; MSVC C2039 on `eCEntity::GetUseType`, 2026-08-22 | `GetUseType()` is not an `eCEntity` member; it belongs to game-layer `gCEntity`. The installed v0.8 DLL remained untouched. |
| EV-079 | The second v0.9 correction passes the `eCEntity*` from `Entity.GetInstance()` to the SDK-declared static `gCEntity::GetUseType(eCEntity*)`, preserving the Fist-only skip and unconditional triggered-list clearing. | CONFIRMED AS SOURCE IMPLEMENTATION AND BUILD; RUNTIME PENDING | commit `11f2a1b`; pinned `gCEntity` SDK declaration; successful Win32 Release build; installed build hash `16B2F35D...F3140` matched, 2026-08-22 | Run the separate-launch Fist contact matrix; Fist causality still depends on observed damage plus logs. |

## 3. Evidence Promotion Rule

A finding may move upward only when a new source or controlled test justifies it.

Design decisions never become engine facts merely because they are implemented.

## 4. Regression Rule

If a later code revision contradicts an earlier confirmed result:

1. reproduce using the known-good baseline if available;
2. determine whether the engine/build changed or the new code regressed;
3. update this ledger with the new evidence;
4. do not silently delete the old result.
