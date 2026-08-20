# Gothic 3 Animation Behaviors — Evidence Ledger

**Status:** Canonical evidence ledger  
**Date:** 2026-08-20

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
| EV-027 | v0.6 rejects Quick ownership because of Normal-specific `_Attack_Hit_` eligibility. | CONFIRMED | runtime/prototype logic | Replace filename-only eligibility with callback+action+phase+marker. |
| EV-028 | `OnAI_QuickAttack` is the relevant callback family for QuickAttackR/L variants. | CONFIRMED | Jackydima source/runtime action values | v0.7 should handle this callback. |
| EV-029 | Marked Fist tests can damage via left leg, right leg, right hand, and left hand with native timed activation suppressed. | CONFIRMED | controlled tests | Physical contact is not tied to a literal right-hand weapon. |
| EV-030 | Logical right-slot Fist entity remains collision group 0 when SetCollisionGroup(Item_Attack) is called. | CONFIRMED | runtime logging | Fist does not behave like normal weapon collision group. |
| EV-031 | Fist `SetCollisionGroup` is unnecessary for damage. | WORKING HYPOTHESIS | not yet isolated | Test by removing only group call while keeping ClearTriggeredList. |
| EV-032 | Triggered-list clearing is the critical Fist rearm operation. | STRONGLY SUPPORTED | current observations | Needs dedicated causal isolation. |
| EV-033 | Repeated multi-hit strikes need rearming/triggered-list clearing. | STRONGLY SUPPORTED | dual-power/whirl source + behavior | Production multi-hit helper should support repeated rearm. |
| EV-034 | `PRIMARY / SECONDARY / ALL / OFF` are final marker names. | UNKNOWN / PROPOSAL | design draft only | Do not mass-author yet. |
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

## 3. Evidence Promotion Rule

A finding may move upward only when a new source or controlled test justifies it.

Design decisions never become engine facts merely because they are implemented.

## 4. Regression Rule

If a later code revision contradicts an earlier confirmed result:

1. reproduce using the known-good baseline if available;
2. determine whether the engine/build changed or the new code regressed;
3. update this ledger with the new evidence;
4. do not silently delete the old result.
