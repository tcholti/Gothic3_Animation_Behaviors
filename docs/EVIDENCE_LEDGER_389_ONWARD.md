# Gothic 3 Animation Behaviors — Evidence Ledger EV-389 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-27

## Purpose

Record evidence after the closed EV-384–EV-388 diagnostic/final-candidate validation volume.

This ledger is proof history, not the normal knowledge interface. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

## Entries

### EV-389 — Diagnostics-free behavior-only release-purity collision validation PASS

Observed:
- The accepted diagnostics-free `Script_FrameCollisionBehaviorTest.dll` was deployed as the sole live G3AB collision twin. Built and live SHA256 both matched `D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78`; the diagnostic twin was absent.
- Gothic 3 reached the main menu and exited normally with the behavior-only twin: startup smoke PASS.
- Run 1 used the User's long-developed/released authored animations across weapon types. The User reports that collision timing felt aligned with authored marker placement rather than the old native timings, and Hack attacks produced working offensive collision behavior, which is a strong marker-dependent positive control.
- Run 2 deliberately used attack animations with collision opportunities impossible under native Gothic timing alone. 2H attacks authored with `ON -> OFF -> ON` produced multiple distinct offensive openings. During authored OFF intervals, opponents entering the weapon did not receive a hit, directly confirming the inactive gap.
- Multi-window 1H1H/dual attacks using BOTH/single-side/OFF/BOTH authoring produced collision on the intended swings across attack types, including extra swings beyond native collision structure.
- Human Fist, Sabretooth Fist/raw8, and Troll PhysicalFist/raw55 double-marker animations could each hit twice from the two authored opportunities.
- The User tested both one-on-one and group combat and reports high confidence that the behavior-only DLL works as intended, with no observed stuck collision, persistent touch-damage, or cleanup regression.

Scope / limits:
- This is intentionally diagnostics-free observational release-purity validation. No `Script_FrameCollisionTest.log` is expected or required.
- Individual authored opportunities remain subject to Gothic-owned contact geometry, target selection, blocks/parries and downstream damage rules; acceptance is based on repeated marker-dependent behaviors that native timing cannot explain, not a requirement that every swing damage every attempt.
- This evidence validates the final pre-migration collision behavior twin. It does not itself validate the later integration of the mature collision subsystem into `src/Script_G3AnimationBehaviors`.

Provenance:
- reviewed final behavior source: `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`;
- behavior-only SHA256, built/live: `D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78`;
- diagnostic phase closure: EV-386–EV-388;
- sole-live deployment output and startup result reported by the User on 2026-09-27;
- functional Run 1 / Run 2 observations reported by the User on 2026-09-27.

Disposition:
- **PASS — BEHAVIOR-ONLY RELEASE-PURITY COLLISION VALIDATION CLOSED.**
- **MATURE COLLISION SUBSYSTEM IS READY FOR PRODUCTION MIGRATION.**
- Next gate: bounded migration into `src/Script_G3AnimationBehaviors` with diagnostics remaining separate, followed by production integration validation.

### EV-390 — Production `Script_G3AnimationBehaviors.dll` collision integration PASS

Observed:
- The production target built successfully from the reviewed production-migration source lineage on `development`.
- The deployed production DLL was the sole live G3AB/collision product among `Script_G3AnimationBehaviors.dll`, `Script_FrameCollisionTest.dll`, and `Script_FrameCollisionBehaviorTest.dll`.
- Built and live production SHA256 matched exactly:
  `12FA5819FEEB5033B2D747A9B57CA1591E588EAAC0BAC9CC386307B77C367A55`.
- The production DLL loaded far enough for a full gameplay collision run; no startup/load failure was observed.
- The User repeated essentially the same deliberately impossible-native positive controls used in EV-389 Run 2:
  - 2H double attacks with three authored markers worked;
  - 1H1H triple attacks with four authored markers worked;
  - human Fist double attacks with two markers worked;
  - Sabretooth raw8 double attacks with two markers worked;
  - Troll raw55 double attacks with two markers worked.
- These controls require authored extra collision opportunities beyond native Gothic timing and therefore provide strong causal evidence that the migrated production DLL is executing the accepted marker behavior rather than merely loading successfully.
- No collision regression was reported during the production validation run.

Scope / limits:
- This is focused production-integration validation after an exact-source migration, not a new collision-semantics campaign.
- It does not re-prove every historical family/source/native-fallback case; those remain protected by the byte-identical migration/static review plus EV-386–EV-389.
- No diagnostic log is expected because the shipping production target is intentionally diagnostics-free.

Provenance:
- production migration implementation: `9da92dc559d8897a675d575f8d88b3631470ed7d`;
- independent migration source review: PASS, including 21/21 migrated behavior files matching prototype Git blobs;
- production built/live SHA256: `12FA5819FEEB5033B2D747A9B57CA1591E588EAAC0BAC9CC386307B77C367A55`;
- deployment/hash output and gameplay observations reported by the User on 2026-09-27.

Disposition:
- **PASS — PRODUCTION COLLISION INTEGRATION CLOSED.**
- **COLLISION MIGRATION INTO `Script_G3AnimationBehaviors.dll` IS COMPLETE.**
- Next phase: freeze the shared generic INI/profile foundation for Speed + later Raise, then work exclusively on Speed until Speed closes.

### EV-391 — Speed v2 caller-side composition surface static proof

Observed:
- Static tracing of `Script_Game+0x42A0 GetAnimationSpeedModifier` consumers found a direct Normal/Hit consumer at `Script_Game+0x383F0`: the caller supplies `gEPhase_Hit` (`1`) and `gEAction_Attack` (`1`), receives the x87 float result, materializes it, and carries it into the existing downstream animation/state descriptor path.
- A separate combat route explicitly assigns `gEAction_QuickAttackR` (`4`) or `gEAction_QuickAttackL` (`5`) and later reaches `Script_Game+0x48677`, where `PSRoutine::PropertyAction()` supplies the action to `+0x42A0` with `gEPhase_Hit`; the returned speed is likewise materialized into the downstream descriptor.
- Additional dynamic Hit consumers in the same Script_Game combat area (`+0x38A8B`, `+0x38E9D`, `+0x38F22`, `+0x3937D`, `+0x39402`) preserve the action in the caller before invoking `+0x42A0`, showing that exact action context remains available at the consumer boundary.
- The native consumer paths therefore provide a stable-looking post-policy/pre-playback intervention class where the live `+0x42A0` implementation can first compute the compatible result `B*M`, after which G3AB can algebraically transform only configured supported profiles by `(B*M) * (C/B) = C*M`.
- This design does not require G3AB to own or trampoline the `+0x42A0` entry point; a targeted caller-side thunk/call redirection can invoke whatever implementation is live there, preserving New Balance ownership and modifier policy.
- Existing evidence/ADR-0004 already records factual bases needed for the first intended profile families: Normal 1H `0.600`, Normal 2H `0.700`, QuickAttackL `1.000`; pinned New Balance source corroborates Normal 1H-family `0.6*M`, Normal 2H/Axe/Staff/Halberd `0.7*M`, and Quick R/L `1.0*M`.

Scope / limits:
- This is static mechanism evidence, not a frozen implementation specification and not runtime acceptance.
- Direct consumer proof currently closes Normal/Attack and QuickAttackR/L Hit routes. ADR-0007 also groups generic `gEAction_QuickAttack` (`3`) into the Quick profile; its exact consumer provenance is not yet closed.
- The additional dynamic part-13 consumers are evidence of the intervention class, not yet an accepted exhaustive production call-site set.
- No new native-speed logging is justified for the currently intended first Normal/Quick profile set because the candidate mechanism's required `B` values are already evidenced/corroborated. Unsupported/future routes must remain native/fail-closed until their base facts are proven.

Provenance:
- Gothic3_Binary_Reference `builds/current_tested/modules/Script_Game/disassembly/part_0013.txt` and `part_0017.txt`, inspected 2026-09-27;
- Gothic3_Binary_Reference `builds/current_tested/modules/Script_Game/imports.txt`, inspected 2026-09-27;
- pinned New Balance source `Jackydima/gothic3sdk@316d32406a133f8884e7e302752c35f66b4f54fc`, `scripts/Script_NewBalance/FunctionHook.cpp`;
- ADR-0004 recorded runtime base observations and composition invariant.

Disposition:
- **STATIC MECHANISM CANDIDATE PROVEN IN PRINCIPLE: targeted caller-side post-`+0x42A0` composition.**
- **NO ADDITIONAL NATIVE-SPEED LOGGER RUN REQUESTED.**
- Next static gate: trace generic `gEAction_QuickAttack` / Action3 into the dynamic combat consumer family, then freeze the smallest exact Normal+Quick call-site set before any Speed v2 implementation.
