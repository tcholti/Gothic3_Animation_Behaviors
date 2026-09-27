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
