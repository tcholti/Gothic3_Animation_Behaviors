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

### EV-392 — Speed v2 Quick provenance and exact caller-set static closure

Observed:
- The generic Quick combat routine at `Script_Game+0x48340` uses `GetPrimaryPoseExt(Action3, Hit)` as a Quick selector/request, then explicitly writes `PSRoutine::PropertyAction = Action4` or `Action5` according to the combat branch. Before `Script_Game+0x48677`, the routine reads `PropertyAction()` back into EAX and therefore calls `GetAnimationSpeedModifier` with factual Action4/5, not Action3.
- Generic `gEAction_QuickAttack` / Action3 therefore does not require its own speed-consumer hook on this proven route. ADR-0007 may continue to normalize the user-facing family as Quick while the engine-facing playback action remains factual 4/5.
- The part-13 `100FFEA8` carrier uses helper `Script_Game+0x3A2D0` to store an explicit constructor argument into object field `+0x158`. Static constructor routes pass Action4 and Action5 into that exact field. The consumers at `+0x38E9D`, `+0x38F22`, `+0x3937D`, and `+0x39402` load that same `+0x158` field into EAX immediately before calling `+0x42A0`; both branch variants supply `gEPhase_Hit` (`1`). These four sites are therefore genuine Quick-capable factual-action consumers.
- `Script_Game+0x38A8B` is a different lineage and is excluded. Its source object `+0x158` is populated by helper `+0x37E20` from the integer result of `PSRoutine::GetStateTime()`; the later `100FFEA0` copy helper `+0x3A330` propagates that scalar into the new object's `+0x158`. A numeric `4` or `5` at `+0x38A8B` is thus not proof of Quick action identity. Hooking this site as an action consumer would create false-positive classification.
- Other previously inspected dynamic consumers are also excluded from Normal/Quick production scope: `+0x4AC6F` concretely constructs action `27/28`, and the `+0x4C6FA` route is tied to Action6.
- The smallest exact tested-build production caller set is therefore six call sites:

```text
Script_Game+0x383F0  Action1 / Normal / Hit
Script_Game+0x38E9D  factual FEA8 action carrier / Hit
Script_Game+0x38F22  factual FEA8 action carrier / Hit
Script_Game+0x3937D  factual FEA8 action carrier / Hit
Script_Game+0x39402  factual FEA8 action carrier / Hit
Script_Game+0x48677  generic Quick route after Action3 -> Action4/5 / Hit
```

- The pinned SDK `mCCallHook` can redirect these exact CALL instructions without taking ownership of the `+0x42A0` function entry. Its register-argument builder can pass incoming EAX as an explicit thunk argument. A bridge thunk can then invoke the **live** `Script_Game+0x42A0` address with the captured action restored in EAX, allowing the current owner (including New Balance) to compute `B*M` exactly once before G3AB applies `C/B`.
- `EngineBridge.cpp` is already the production DLL's sole low-level hook owner, so Speed's six call hooks belong there. `AttackSpeed` remains feature policy/composition only.
- The selected downstream mechanism technically requires factual base `B`. ADR-0004 already permits evidence-bounded base facts where the chosen mechanism requires them. The production design therefore keeps `B` as a small immutable technical fact lookup keyed by exact runtime facts, not a copied multiplier table and not user-facing INI policy.
- Pinned New Balance source corroborates the first production facts: Normal raw hand combinations None+1H, Shield+1H, Torch+1H and 1H+1H use `0.6*M`; None+2H, None+Axe, None+Staff and None+Halberd use `0.7*M`; QuickAttackR/L use `1.0*M`. Direct runtime evidence already includes 1H Normal `0.600`, 2H Normal `0.700`, and QuickAttackL `1.000` on tested routes.
- Normal human Fist is deliberately excluded from this first composition table because current New Balance returns its special `0.7` directly rather than through the ordinary `B*M` path. Unknown/unproven raw combinations and non-Hero families remain native/fail-closed.

Implementation consequence:
- No diagnostics-only probe is required before production source implementation.
- Production transport is six bridge-owned `mCCallHook`s plus one common thunk that passes factual EAX action explicitly, calls live `+0x42A0` exactly once, and delegates only the `C/B` composition decision to `AttackSpeed`.
- Runtime profile matching continues to use ADR-0007 normalized identity; technical `B` lookup must retain factual **raw** UseTypes separately because different raw UseTypes can normalize to the same animation token while having different compatible base policy.
- The bounded production implementation contract is `docs/work/active/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`.

Scope / limits:
- This is static proof and design freeze, not source implementation, build acceptance, or runtime acceptance.
- The six RVAs are current-tested-build specific.
- New Balance is the primary runtime compatibility environment. Native-only sanity remains a later runtime gate after source implementation and primary composition validation.
- Unsupported/future routes must remain untouched until their exact factual base/composition contract is proven.

Provenance:
- Gothic3_Binary_Reference `part_0013.txt`, `part_0014.txt`, `part_0017.txt`, `part_0018.txt` and `imports.txt`, pinned current-tested reference `c9d12cb5f0dcb4f96af6a82c02138c1c15e981b6`;
- SDK hook implementation/API at `georgeto/gothic3sdk@90bfd344de4510dda7ac9da7461cc7f1eac911f7`;
- pinned New Balance `FunctionHook.cpp` at `Jackydima/gothic3sdk@316d32406a133f8884e7e302752c35f66b4f54fc`;
- ADR-0004, ADR-0005, ADR-0007;
- static inspection completed 2026-09-28.

Disposition:
- **PASS — GENERIC QUICK/ACTION3 PROVENANCE CLOSED.**
- **PASS — SMALLEST EXACT NORMAL+QUICK CALLER SET FROZEN AT SIX CALL SITES.**
- **NO SPEED DIAGNOSTIC PROBE REQUIRED BEFORE IMPLEMENTATION.**
- Next gate: bounded source-only production implementation under `SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md`; build/run remain separate later validation work.

### EV-393 — Speed runtime animation-family source: Hero control PASS

Observed:
- The refreshed standalone `Script_SpeedIdentityProbe.dll` built and deployed with matching built/live SHA256 `DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`.
- The player used ordinary right-hand 1H with empty left hand and exercised Normal Action1 plus Quick Action4/5, all requested as Hit.
- `Animation.GetResourceName()` remained `G3_Hero_Skeleton`, which is not the ADR-0007 author-facing family token.
- `Animation.GetSkeletonName(...)` succeeded on every observation and returned exactly `Hero`.
- `Entity.GetSkeletonName()` independently returned exactly `Hero` on every observation.
- `NPC.GetCurrentMovementAni()` was not reliably the newly requested Hit animation at this observation point. It could still report `HoldRight_End`, `Attack_Recover`, `Ambient_Loop`, or `Parade_Begin` motions while the CombatMove request was already Normal/Quick Hit.
- The existing production `BehaviorProfiles` key still used the raw resource identity and therefore produced `Key.AnimationFamily=g3_hero_skeleton` / `ProfileMatch=false`; this was expected because production behavior source remained frozen during the probe.

Interpretation:
- Current-motion filename parsing is rejected as the Speed runtime family source at `Game+0x16B065`; the motion can be stale relative to the attack request.
- `Animation.GetResourceName()` is rejected as the user-facing family source for this route because its factual value is a resource-style name rather than the schema token.
- `Animation.GetSkeletonName(...)` is the preferred generic family-source candidate: it belongs to the animation property set, returned the exact schema token `Hero`, and exposes explicit success/failure for fail-closed handling.
- `Entity.GetSkeletonName()` corroborates the same Hero token.

Scope / limits:
- This runtime control proves the family-source decision for the tested Hero human route only.
- One bounded non-Hero control remains before promoting `Animation.GetSkeletonName(...)` as the generic production `AnimationFamily` source.
- No production Speed, Raise, collision, or profile-matching behavior was changed by this probe.

Provenance:
- probe built/live SHA256: `DE9039372E9CA2C2D0FBB6DA581613E47628724249AF35C54E47DAE68B14470F`;
- user-pushed runtime source commit: `765e3ee948f0169f827fe207dab975decdef7f73`;
- processed log: `research/archive/2026.09.28_SpeedIdentityProbetest_2.log`;
- active bounded task at the time: `docs/work/active/SPEED_RUNTIME_FAMILY_SOURCE_PROBE.md`.

Disposition:
- **PASS — HERO FAMILY SOURCE RESOLVED.**
- **PREFERRED CANDIDATE: `Animation.GetSkeletonName(...)`.**
- Next gate: one transformed/non-Hero Normal/Quick control; if the skeleton APIs agree on a stable non-Hero family token, close the probe and refactor production profile identity generically.

### EV-394 — Speed runtime animation-family source: Sabretooth generalization control PASS

Observed:
- The already-built/deployed diagnostics-only identity probe was reused without source changes.
- The player transformed into Sabretooth and exercised multiple Normal Action1 plus Quick Action4/5 Hit requests.
- Every recorded observation reported:

```text
AnimationSkeletonNameAvailable=true
AnimationSkeletonName=Sabertooth
EntitySkeletonName=Sabertooth
```

- `Animation.GetResourceName()` was consistently the implementation-resource identity `G3_Sabertooth_Body_01`, not the author-facing family token.
- `CurrentMovementAni()` remained `Sabertooth_..._Ambient_Loop_...` while factual Normal/Quick Hit requests were observed, independently reinforcing that current motion is not the requested-attack authority at this request boundary.

Interpretation:
- The non-Hero control generalizes the Hero result: `Animation.GetSkeletonName(...)` returns the stable Gothic family token needed by ADR-0007 on two materially different families.
- `Entity.GetSkeletonName()` independently corroborates the same token.
- `Animation.GetResourceName()` and current-motion filename parsing remain rejected as production profile identity sources.
- Factual requested `gEAction`/`gEPhase` remain the attack/phase authority; skeleton-family identity is a separate stable profile component.

Provenance:
- user-pushed raw log commit: `f2d40c89cda314b98c640f956af003168ab7abec`;
- processed log: `research/archive/2026.09.28_SpeedIdentityProbetest_sabertooth.log`;
- closed result: `docs/archive/investigations/SPEED_RUNTIME_FAMILY_SOURCE_PROBE_RESULT.md`.

Disposition:
- **PASS — GENERIC RUNTIME `AnimationFamily` SOURCE CLOSED.**
- **PRODUCTION SOURCE: `Animation.GetSkeletonName(...)`, fail closed when unavailable/empty.**

### EV-395 — Generic profile Speed behavior and New Balance multiplier preservation PASS

Observed:
- The generic profile/calibration refactor passed static review and the production target built successfully.
- Built/live `Script_G3AnimationBehaviors.dll` SHA256 matched exactly:

```text
6DD8C9CE46E3398DC725A5F4D9C2D3D2F073707094AFDDE30C385CC32F6AEEAD
```

- The completed `Script_SpeedIdentityProbe.dll` was removed before production behavior testing.
- With Hero / empty-left / right-hand 1H Normal and Quick profiles configured at `BaseSpeed=0.40`, multiple Normal variants and multiple Quick variants visibly obeyed the configured slow speed.
- This closed the earlier runtime profile-match failure and showed that one profile applies across the tested pose/animation variants without P0/P1/P2/P3-specific policy.
- For the key New Balance compatibility control, the User configured Hero / empty-left / right-hand 2H Normal with factual `ReferenceHitBaseSpeed=0.70` and desired `BaseSpeed=1.00`. The User's 2H animations are authored around the neutral `1.0` playback baseline, making the comparison visually clear.
- At available/full stamina the configured 2H attack used the expected faster authored base. When stamina reached zero/depleted state, the same configured 2H attack visibly slowed.
- This demonstrates that configured base-speed authority does not erase the tested New Balance stamina/context multiplier.

Interpretation:
- Runtime behavior matches the ADR-0004 composition invariant:

```text
compatible = B * M
configured = (B * M) * (C / B) = C * M
```

- G3AB successfully authors `C` while the tested New Balance `M` remains effective.
- The historical same-function `Script_CombatMoveLogger` was deliberately not deployed because its `+0x42A0` hook would contaminate this caller-side compatibility test.

Scope / limits:
- This is not yet full Speed feature closure. Remaining work is the smallest final runtime acceptance/fallback matrix, including representative unconfigured fallback and native-only sanity where required.
- Staff also appeared to retain stamina slowdown, but the configured 2H control is the clearer acceptance fixture and is the basis for this evidence entry.
- Raise remains paused until Speed closes completely.

Provenance:
- production source lineage through generic calibration implementation on `development`;
- built/live SHA256 and runtime observations reported by the User on 2026-09-28;
- implementation closure: `docs/archive/investigations/SPEED_GENERIC_PROFILE_CALIBRATION_IMPLEMENTATION_RESULT.md`.

Disposition:
- **PASS — GENERIC CONFIGURED NORMAL/QUICK SPEED BEHAVIOR VALIDATED ON TESTED HERO PROFILES.**
- **PASS — KEY NEW BALANCE CONTEXTUAL-MULTIPLIER-PRESERVATION INVARIANT VALIDATED ON CONFIGURED 2H NORMAL.**
- Next gate: bounded final Speed runtime acceptance/fallback coverage; no mechanism redesign absent contradictory evidence.

### EV-396 — Reusable Speed calibration probe native control PASS

Observed:
- The standalone diagnostics-only `Script_SpeedCalibrationProbe.dll` built successfully with SHA256 `4140867626119632929D2286A173E97B3A4ACE6EDBCA4E2DBFE30AC28FE28E82`.
- For the clean native fixture, the User physically removed `Script_G3AnimationBehaviors.dll`, `Script_NewBalance.dll`, `Script_NewMagicforNPCs.dll`, and `Script_AttackCollision.dll` from Gothic 3's `scripts` folder before launch. This follows the established loader rule that renaming a DLL in place is not a reliable disable method.
- The probe returned live speed values unchanged, intercepted 55 calls, deduplicated them to 12 unique observations, and dropped zero observations.
- Native Hero / None+1H values were stable across repeated samples:
  - Normal Hit `0.600000` (15 samples);
  - QuickR Hit `1.000000` (2 samples);
  - QuickL Hit `1.000000` (3 samples);
  - Power Raise `1.500000` (5 samples);
  - Power Hit `1.000000` (4 samples).
- Native Troll / PhysicalFist+PhysicalFist values were stable:
  - Normal Hit `1.000000` (12 samples);
  - QuickR Hit `1.000000` (3 samples);
  - QuickL Hit `1.000000` (5 samples);
  - ordinary Power Raise `1.000000` and Power Hit `1.000000`;
  - factual Sprint/Action9 reached the shared Power route with caller-passed Action2 and returned `1.000000` for both observed Raise and Hit calls while `CurrentActionBefore/After` remained Sprint.

Interpretation:
- The reusable calibration-probe design is runtime-valid for broad sampling: it is observational, preserves live speed, and substantially reduces repeated traffic without losing distinct route/speed observations.
- Native Hero None+1H and Troll PhysicalFist reference facts independently confirm known values and establish a clean baseline for the broader calibration campaign.
- The Troll comparison strengthens the Speed calibration model: native Power/Sprint Hit base `B=1.0` versus previously observed New Balance live result `1.5`; New Balance's increase belongs to the compatible live result, not `ReferenceHitBaseSpeed`.
- The factual Sprint Raise observation is retained for later Raise research only; it does not authorize Raise behavior now.

Scope / limits:
- This is the first calibration control, not a complete native base-speed catalogue.
- Only the exercised Hero None+1H and Troll PhysicalFist routes are promoted as native calibration facts here.
- New Balance and other compatibility comparisons remain a later campaign; no claim is made for untested third-party speed implementations.

Provenance:
- probe source: `tools/Script_SpeedCalibrationProbe/` on `development`;
- built probe SHA256: `4140867626119632929D2286A173E97B3A4ACE6EDBCA4E2DBFE30AC28FE28E82`;
- raw control log: `research/raw/2026.09.29_speed calibration_1h_troll.log`;
- user-pushed raw-log commit: `9449e4b3f37114e104595a61355b61fd472eb873`;
- active calibration contract: `docs/work/active/SPEED_NATIVE_CALIBRATION_PROBE.md`.

Disposition:
- **PASS — CALIBRATION PROBE BUILD/RUNTIME FORMAT VALIDATED.**
- **PASS — FIRST NATIVE REFERENCE CONTROL CLOSED.**
- The raw control log remains intentionally available during the active calibration campaign as a baseline/comparison fixture; archive it when the campaign no longer needs active comparison.
- Next calibration gate: broad native human/loadout/NPC/nonhuman sampling, followed by useful New Balance comparison; expanded production Speed deployment remains deferred until calibration settles common reference values.

### EV-397 — Broad native Hero/loadout Speed calibration PASS; normalized loadout equivalence and family-specific bases observed

Observed:
- The User ran the reusable diagnostics-only Speed calibration probe in the clean native fixture with production G3AB and New Balance excluded. For this broader human calibration, the custom animation-routing DLLs `Script_Animation.dll`, `Script_RapierAnimation.dll`, and `Script_ZombieAnimation.dll` were also physically removed so the sampled routes used native Gothic animation routing.
- User-pushed source commit `60a411abb1cb351ca996df4a63816032a7fb07e0` contains:
  - `research/archive/2026.09.30_speed_calibration_human_weapon_types.log`;
  - `research/archive/2026.09.30_speed_calibration_human_weapon_types_finishing attacks.log`.
- The broad human/loadout run intercepted 219 calls, reduced them to 53 unique observations, and dropped zero rows.
- Native Hero observations established:
  - None+1H, Torch+1H, Shield+1H: Normal Hit `0.6`, Quick R/L `1.0`, Power Hit `1.0`, Pierce Hit `1.0`;
  - 1H+1H: Normal Hit `0.6`, Quick R/L `1.0`, Power Hit `0.9`, SimpleWhirl Hit `1.3`, Pierce Hit `1.0`;
  - None+Staff and raw Halberd/51 normalized to Staff: Normal Hit `0.7`, Quick R/L `1.0`, Power Hit `1.0`, Hack Hit `1.0`, Whirl Hit `1.0`;
  - None+2H and raw Axe/52 normalized to 2H: Normal Hit `0.7`, Quick R/L `1.0`, Power Hit `1.0`, Hack Hit `1.0`, Whirl Hit `1.0`;
  - all sampled Hero Power Raise observations returned `1.5`.
- Within the sampled native routes, raw Axe behaved equivalently to normalized 2H and raw Halberd behaved equivalently to normalized Staff. This directly supports the existing runtime normalization rather than relying only on naming assumptions.
- The first deliberate finishing-attack run used the pre-extension probe and therefore produced no factual Action15 rows. It is preserved as provenance, not as Finishing calibration evidence.
- That same run provided useful representative Orc/Staff-family observations: Normal Hit `0.7`, Quick R/L `1.0`, Power Raise `1.0`, Power Hit `0.7`, Whirl Hit `1.0`, Hack Hit `1.0`.
- The Orc versus Hero Staff/Halberd contrast is material: Hero Power Hit was `1.0` and Power Raise `1.5`, while Orc Power Hit was `0.7` and Power Raise `1.0`.

Interpretation:
- The grouped profile identity must retain `AnimationFamily`; normalized loadout identity alone is not enough to select a native reference base.
- The current Axe -> 2H and Halberd -> Staff normalization is supported by direct sampled native Speed behavior.
- Native reference bases are route-specific. In particular, dual-1H Power `B=0.9` and SimpleWhirl `B=1.3` must not be flattened to a generic `1.0`.
- Power Raise observations remain research evidence only and do not authorize Raise implementation.

Scope / limits:
- These facts apply to the exact exercised families/loadouts/actions under the clean native fixture; they are not a complete catalogue for all NPC/nonhuman families.
- The first finishing-attempt log cannot establish Finishing speed because the probe did not yet observe Action15.

Disposition:
- **PASS — BROAD NATIVE HERO/LOADOUT CALIBRATION CHECKPOINT.**
- **PASS — AXE/2H AND HALBERD/STAFF NORMALIZATION SUPPORTED ON SAMPLED SPEED ROUTES.**
- **PASS — ANIMATION FAMILY REMAINS A REQUIRED PROFILE IDENTITY COMPONENT.**
- Both processed September 30 logs are archived byte-identically after promotion; they are no longer active raw intake.
- Next calibration work remains representative NPC/nonhuman coverage after the bounded Finishing/Hack shared-asset question is resolved.

### EV-398 — Finishing Action15 Speed observation PASS; distinct factual route from Hack

Observed:
- Static `Script_Game` analysis established three Finishing Hit speed consumers at:
  - `Script_Game+0x41551`;
  - `Script_Game+0x41680`;
  - `Script_Game+0x417F0`.
- Each site hard-passes `EAX=0x0F` / `gEAction_FinishingAttack` to the live `Script_Game+0x42A0 GetAnimationSpeedModifier` owner. These sites are distinct from the three Hack/Action14 callers.
- The diagnostics-only calibration probe was extended in commit `bcb0f056bbb153b4d42f3f84345aefc8a1f96c72` with exactly those three Action15 observation sites and readable `FinishingAttack` diagnostics; production G3AB source remained untouched.
- The focused native run was pushed in commit `8e4ba688cbe873d1e3436d07c047b892cf9bca2d` and is archived as `research/archive/2026.09.30_speed_calibration_human_weapon_types_finishing attacks2.log`.
- The extended probe startup banner reported 18 proven Hit callers including three Finishing/Action15 sites.
- The focused run intercepted 139 calls, reduced them to 17 unique observations, and dropped zero rows.
- Clean native Hero results:
  - None+2H Hack/Action14 Hit = `1.000000`;
  - None+2H Finishing/Action15 Hit = `1.000000`;
  - raw Halberd/51 normalized Staff Hack/Action14 Hit = `1.000000`;
  - raw Halberd/51 normalized Staff Finishing/Action15 Hit = `1.000000`.
- The observed Finishing rows retained `PassedAction=FinishingAttack(15)`, factual current Action15 before/after, `Phase=Hit(1)`, `NewBalance=false`, and `G3AB=false`.
- Native Gothic may use the same underlying 2H/Staff animation asset for Hack and Finishing, but the speed-consumer action transport remains factually distinct.

Interpretation:
- Shared animation-file identity does not collapse Hack/Action14 and Finishing/Action15 into one factual Speed action route.
- This observation does **not** yet prove that a configured G3AB Hack speed cannot indirectly affect a Finishing execution when both actions resolve to the same shared `.xmot`; that is the next explicit runtime question.
- Finishing remains intentionally outside the current production Speed profile set and outside the distributed INI. Native/default execution timing remains untouched. A later optional advanced Finishing configuration capability may be considered only after the shared/separated animation experiments; it is not implied by this evidence.

Scope / limits:
- The deduplicated probe does not identify which of the three static Action15 caller addresses produced a particular row. Runtime Action15 observation therefore validates the factual route but does not claim that all three sites were individually exercised.
- The exact built/live SHA256 of the extended calibration binary was not durably recorded in the repository/conversation. The distinctive 18-caller startup banner and factual Action15 observations establish that the extended probe loaded, but POP-03 exact built/live identity cannot be reconstructed for this run. Before the probe is reused for later calibration, built/live identity must be re-established and recorded.

Disposition:
- **PASS — FOCUSED FINISHING/ACTION15 OBSERVATION CLOSED.**
- **PASS — HACK AND FINISHING ARE DISTINCT FACTUAL SPEED ACTION ROUTES DESPITE SHARED NATIVE ASSET USE.**
- The focused raw log is archived byte-identically after promotion.
- **NEXT CAUSAL QUESTION:** production G3AB active, calibration probe absent, native shared Hack/Finishing assets retained, configure Hero 2H/Staff Hack deliberately slow (target `BaseSpeed=0.4` with correct native `B=1.0`) and verify whether factual Finishing remains visually/native-timed; then repeat with separated Hack assets.

### EV-399 — Hack/Finishing playback isolation PASS on shared and separated assets

Observed:
- The User restored production `Script_G3AnimationBehaviors.dll`, removed the standalone calibration probe, and used the new grouped-profile INI design.
- An initial apparent failure in which configured Hack `BaseSpeed=0.40` did not change playback was invalid fixture evidence: an older production DLL had accidentally been restored. The User rebuilt and deployed the current production DLL, after which grouped-profile Speed behavior worked normally. No mechanism conclusion is drawn from the stale-DLL run.
- With the current production DLL and Hero 2H/Staff Hack configured using native `ReferenceHitBaseSpeed=1.00` and authored `BaseSpeed=0.40`, ordinary Hack playback became visibly slow as expected.
- While Hack and Finishing still resolved to the same native animation asset, factual Finishing execution retained its normal playback speed rather than inheriting Hack's configured `0.40`.
- The User then repeated the comparison with Hack and Finishing using separated animation assets. Hack again obeyed the configured slow speed while Finishing remained independently native-timed.
- In the slowed Hack execution, the visible Raise and Recover portions also followed the slow configured Hack playback rather than retaining an independent native pace.

Interpretation:
- G3AB Speed authority is action-route based, not animation-resource based. A configured Hack/Action14 speed does not spill into Finishing/Action15 merely because both actions share the same `.xmot`.
- Separating Hack and Finishing assets remains useful for animation authoring and collision-marker semantics, but is **not required for Speed isolation**.
- The shared-asset and separated-asset results independently reinforce EV-398's static/runtime action separation.
- Existing/native Hack Raise and Recover portions follow the configured Hack playback speed. This is useful evidence for later Raise research, but it does **not** yet prove that a future G3AB-inserted custom Raise phase will inherit the same timing; that question remains under the paused Raise feature.

Scope / limits:
- This was a diagnostics-free visual runtime test reported by the User. No dedicated runtime log was expected for this production behavior comparison.
- Exact built/live SHA256 for this rebuilt production DLL was not reported in the conversation. The result is accepted as behavioral evidence from the User's corrected latest-DLL fixture, but future formal production acceptance should continue to use POP-03 exact binary-identity verification.
- Finishing remains intentionally absent from the shipped/default Speed profile set and INI.

Disposition:
- **PASS — HACK/FINISHING SHARED-ASSET SPEED ISOLATION.**
- **PASS — HACK/FINISHING SEPARATED-ASSET CONTROL.**
- **PASS — SPEED AUTHORITY FOLLOWS FACTUAL ACTION ROUTE, NOT ANIMATION FILE IDENTITY.**
- **OBSERVED — EXISTING HACK RAISE/RECOVER PLAYBACK FOLLOWS CONFIGURED HACK SPEED.**
- The bounded Finishing/Hack research detour is CLOSED.
- **NEXT:** remove production G3AB, re-establish exact identity for the extended calibration probe, and resume representative NPC/nonhuman native Speed calibration before later New Balance comparison and final expanded-production acceptance.

### EV-400 — Representative native NPC Speed calibration PASS; Goblin contextual Sprint comparison retained

Observed:
- After EV-399, the current extended `Script_SpeedCalibrationProbe.dll` was rebuilt from `development` and deployed as the sole recognized G3AB project runtime product.
- POP-03 built/live identity matched exactly:
  `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`.
- The startup gate reported all 18 proven Hit caller hooks, including the three Finishing/Action15 sites, plus the proven Power Raise observation hook. A main-menu-only control exited with `InterceptedCalls=0`, `UniqueObservations=0`, and zero drops.
- The clean native fixture kept production G3AB, New Balance, NewMagicforNPCs, AttackCollision, and the custom Animation/Rapier/Zombie script DLLs physically outside `scripts`.
- The representative NPC run is preserved at `research/raw/2026.09.30_speed_calibration_representative_npcs.log` because one contextual Goblin comparison remains open.
- Final summary: 248 intercepted calls, 33 unique observations, zero dropped observations. The 2H player cleanup/control traffic is explicitly identified by `Player>0, NPC=0`; NPC observations are therefore separable from the User's attacks.
- NPC native observations:
  - Hero / None+1H / `MoraSul_Bandit_03`: Normal Hit `0.6`; Quick R/L Hit `1.0`; Power Raise `1.5`; Power Hit `1.0`; Pierce Hit `1.0`.
  - Hero / None+Staff / `NomadElite_01`: Normal Hit `0.7`; Quick R/L Hit `1.0`; Power Raise `1.5`; Power Hit `1.0`; Hack Hit `1.0`; Whirl Hit `1.0`.
  - Orc / raw Halberd51 -> Staff / `Montera_Orc_01`: Normal Hit `0.7`; Quick R/L Hit `1.0`; Power Raise `1.0`; Power Hit `0.7`; Hack Hit `1.0`; Whirl Hit `1.0`.
  - Goblin / None+1H / Goblin+BlackGoblin samples: Normal Hit `0.6`; Quick R/L Hit `1.0`; factual Sprint/Action9 through passed Power/Action2 returned Raise `1.5` and Hit `1.5`.
- The player's deliberate Hero None+2H cleanup traffic reproduced established controls: Normal `0.7`, Quick R/L `1.0`, Power Raise `1.5`, Power Hit `1.0`, Hack `1.0`, Whirl `1.0`, Finishing `1.0`. Those rows are control/provenance only and are not promoted as NPC facts.
- The older closed Sprint causal run on BlackGoblin recorded ordinary Power Hit `1.0` and factual Sprint Hit `1.0` in the same run. Today's factual Sprint Hit `1.5` is therefore preserved as a contextual native variation, not re-labelled as a new ordinary Goblin Power base.

Interpretation:
- Sampled Hero NPCs use the same native values already established for the corresponding Hero family/loadout routes. No player-vs-NPC Speed split was observed for those exercised routes.
- The Orc/Halberd sample strongly reproduces EV-397's family-specific Power facts: Orc Power Raise `1.0` / Hit `0.7` remains materially different from Hero Staff Power Raise `1.5` / Hit `1.0`.
- The Goblin result does not contradict the proven shared Sprint/Power transport or ADR-0009. It shows that the live native result on that route can differ across runtime contexts. Because the current run did not capture ordinary Goblin Power alongside Sprint, do not infer `ReferenceHitBaseSpeed=1.5` for Goblin Power from this run.
- The next smallest control is same-run Goblin ordinary Power plus factual Sprint. If both move together, the difference is compatible with a contextual multiplier `M`; if they diverge, investigate before promoting a Goblin Power reference.

Scope / limits:
- This checkpoint covers only the naturally exercised NPC routes above; unsupported actions were not forced.
- No SimpleWhirl or ordinary Goblin Power/Pierce/Hack observation was produced for the NPC samples.
- The current raw log remains an explicit active comparison input until the Goblin contextual repeat closes; this is intentional POP-06 retention, not stale intake.

Provenance:
- User-pushed runtime commit: `5205fb98538f07dd668164152ba3fd5a29c50383`;
- current extended probe built/live SHA256: `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`;
- current active log blob: `e800b0d0836b36e85c15a6c681415f9490a02809`;
- historical Goblin shared-Power/Sprint control: `docs/archive/investigations/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE_RESULT.md`.

Disposition:
- **PASS — EXTENDED 18-HIT-CALLER PROBE IDENTITY/STARTUP GAP CLOSED FOR CURRENT CALIBRATION.**
- **PASS — REPRESENTATIVE HERO/ORC/GOBLIN NPC CALIBRATION CHECKPOINT.**
- **CONFIRMED — HERO NPC VALUES MATCH THE CORRESPONDING ESTABLISHED HERO ROUTES IN THIS SAMPLE.**
- **CONFIRMED — ORC STAFF-FAMILY POWER DIFFERENCE REPRODUCED.**
- **OPEN BOUNDED FOLLOW-UP — GOBLIN SAME-RUN ORDINARY POWER + SPRINT CONTEXT CONTROL.**
- After that small control, continue representative nonhuman native calibration, then the useful New Balance comparison.

### EV-401 — Goblin same-run Power/Sprint context control PASS; shared-profile multiplier preservation clarified

Observed:
- The User repeated the clean-native Goblin control with the unchanged extended 18-Hit-caller calibration probe identified by SHA256 `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`.
- User-pushed source commit `974d3119a8bc331775e4682fd956cfc8cbad6ed7` added `research/raw/2026.10.01_speed_calibration_goblin.log`; after interpretation it is archived byte-identically as `research/archive/2026.10.01_speed_calibration_goblin.log`.
- Final summary: `InterceptedCalls=89`, `UniqueObservations=10`, `DroppedUniqueObservations=0`.
- BlackGoblin / None+1H repeated observations:
  - Normal Hit = `0.600000` (22 calls);
  - QuickR Hit = `1.000000` (12 calls);
  - QuickL Hit = `1.000000` (18 calls);
  - ordinary Power/Action2 Raise = `1.500000` (8 calls);
  - ordinary Power/Action2 Hit = `1.000000` (8 calls);
  - factual Sprint/Action9 through passed Power/Action2 Raise = `1.500000` (4 calls);
  - factual Sprint/Action9 through passed Power/Action2 Hit = `1.500000` (4 calls).
- The same run therefore directly separates ordinary Power Hit `1.0` from factual Sprint Hit `1.5` while both calls pass Action2 to the live speed owner.
- The earlier closed Goblin causal run observed ordinary Power Hit `1.0` and factual Sprint Hit `1.0` together. Sprint's live Hit result is therefore not a fixed second authoring base; it can vary by native runtime context while the shared Power transport remains unchanged.

Interpretation:
- Goblin None+1H ordinary Power Hit reference `B=1.0` is directly supported by same-run ordinary Power evidence.
- ADR-0009's production decision remains correct: Sprint has no separate author-facing Speed profile and continues to inherit the Power profile on the proven shared caller.
- Profile inheritance does **not** imply equal live effective playback speed. Gothic may contribute additional Sprint-context behavior inside the live compatible result even though the caller passes Power/Action2.
- Under the accepted composition model this difference belongs to the preserved compatible/contextual term: with Power `B=1.0`, live Sprint `1.5`, and configured Power base `C`, production computes `1.5 * (C / 1.0) = 1.5C` rather than flattening Sprint to `C`.
- Do not add `Sprint_BaseSpeed`, `Sprint_ReferenceHitBaseSpeed`, or rewrite Action2 to Action9. The later expanded-production runtime acceptance should include a configured Power/Sprint control to demonstrate preservation of this native differential end-to-end.
- Raise values remain observation-only evidence because Power Raise is not currently a production Speed hook and Raise behavior remains paused.

Scope / limits:
- The exact engine cause of the changing Sprint live multiplier is not identified and does not need to be copied into G3AB policy. The accepted architecture deliberately leaves that policy inside the live Gothic/compatible owner.
- This control resolves the EV-400 Goblin comparison only; broader nonhuman calibration remains open.

Provenance:
- current extended probe built/live SHA256: `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`;
- user-pushed runtime commit: `974d3119a8bc331775e4682fd956cfc8cbad6ed7`;
- archived log blob: `9859e3d5e9a77a8662fa84562f2c4f74a25f8745`;
- EV-400 comparison source blob: `e800b0d0836b36e85c15a6c681415f9490a02809`;
- historical causal result: `docs/archive/investigations/SPEED_SPRINT_SHARED_POWER_HIT_CAUSAL_PROBE_RESULT.md`;
- architecture decision: ADR-0009.

Disposition:
- **PASS — GOBLIN SAME-RUN ORDINARY POWER / SPRINT CONTEXT CONTROL CLOSED.**
- **PASS — GOBLIN ORDINARY POWER HIT REFERENCE B=1.0 SUPPORTED.**
- **CONFIRMED — POWER-PROFILE INHERITANCE DOES NOT REQUIRE EQUAL LIVE POWER/SPRINT SPEED.**
- **CONFIRMED — CURRENT C/B COMPOSITION IS THE CORRECT PRESERVATION MECHANISM FOR THE OBSERVED SPRINT DIFFERENTIAL.**
- The EV-400 representative-NPC log and this focused Goblin log no longer own an open comparison and are archived byte-identically.
- **NEXT:** representative nonhuman native calibration.

### EV-402 — Representative nonhuman native Speed Batch 1 PASS; Sprint-context differential generalizes

Observed:
- The User ran the unchanged clean-native extended 18-Hit-caller calibration probe against Sabertooth, Wolf, Boar and Troll, with the probe still identified by SHA256 `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`.
- User-pushed source commit `f96ab812db2335f7d3a3541228a92417b5549e27` contains the runtime artifact now archived byte-identically as `research/archive/2026.10.01_speed_calibration_sabertooth_wolf_boar_troll.log`.
- Final summary: `InterceptedCalls=365`, `UniqueObservations=31`, `DroppedUniqueObservations=0`.
- Player cleanup traffic was explicitly separable through `Player>0, NPC=0` and reproduced already-established Hero values; it is not promoted as nonhuman evidence.
- Sabertooth / None+raw8 Fist:
  - Normal Hit `1.0` (16);
  - QuickR Hit `1.0` (5);
  - QuickL Hit `1.0` (18);
  - ordinary Power Raise `1.5` (8);
  - ordinary Power Hit `1.0` (8);
  - factual Sprint/Action9 through passed Power Raise `1.5` (14);
  - factual Sprint/Action9 through passed Power Hit `1.5` (14).
- Wolf / None+raw8 Fist:
  - Normal Hit `1.0` (21);
  - ordinary Power Raise `1.5` (14);
  - ordinary Power Hit `1.0` (13);
  - factual Sprint through passed Power Raise `1.5` (5);
  - factual Sprint through passed Power Hit `1.5` (4).
- Boar / None+raw8 Fist:
  - Normal Hit `1.0` (39);
  - factual Sprint through passed Power Raise `1.5` (7);
  - factual Sprint through passed Power Hit `1.5` (7);
  - no ordinary Power observation occurred naturally in this run.
- Troll / raw55 PhysicalFist+PhysicalFist:
  - Normal Hit `1.0` (20);
  - QuickR Hit `1.0` (12);
  - QuickL Hit `1.0` (20);
  - ordinary Power Raise/Hit `1.0 / 1.0` (3 each);
  - factual Sprint through passed Power Raise/Hit `1.0 / 1.0` (6 each).

Interpretation:
- EV-401's key distinction generalizes beyond Goblin. Sabertooth and Wolf both show ordinary Power Hit `B=1.0` while factual Sprint Hit returns `1.5` through the same passed Power/Action2 route.
- Troll remains a counterexample to any hard-coded universal Sprint multiplier: ordinary Power and Sprint both return `1.0` in the sampled raw55 route.
- Therefore the correct production abstraction remains:
  `Power profile/reference base` + `live compatible/contextual result`, with C/B composition preserving whatever Sprint-context differential Gothic supplies for the current family/execution.
- No Sprint-specific Speed option is justified. The evidence now spans Goblin, Sabertooth, Wolf and Troll with different live Power/Sprint relationships.
- Sabertooth and Wolf ordinary Power Hit reference `B=1.0` are directly supported. Troll raw55 Power Hit `B=1.0` is reconfirmed.
- Boar ordinary Power `B` is **not established** by this batch because only factual Sprint reached the shared Power caller. Do not promote the Sprint `1.5` live result as Boar Power `B`.

Scope / limits:
- This batch covers only naturally exercised actions. Missing actions are absence of coverage, not negative capability claims.
- Boar ordinary Power remains an optional future calibration gap if a shipped/configured Boar Power profile requires an explicit reference.
- Power Raise values remain observation-only evidence; Raise is still paused and the Raise caller is not part of production Speed composition.

Provenance:
- current probe SHA256: `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`;
- user-pushed source commit: `f96ab812db2335f7d3a3541228a92417b5549e27`;
- archived log blob: `7c9db5650e0953d56057d7974595573ccd4fe82a`;
- architecture clarification: EV-401 + ADR-0009.

Disposition:
- **PASS — REPRESENTATIVE NONHUMAN NATIVE SPEED BATCH 1.**
- **PASS — SABERTOOTH POWER HIT B=1.0; SPRINT LIVE HIT=1.5 IN THIS RUN.**
- **PASS — WOLF POWER HIT B=1.0; SPRINT LIVE HIT=1.5 IN THIS RUN.**
- **PASS — TROLL RAW55 POWER/SPRINT HIT=1.0 RECONFIRMED.**
- **BOAR POWER B REMAINS UNESTABLISHED; SPRINT LIVE HIT=1.5 OBSERVED ONLY.**
- **CONFIRMED — NO UNIVERSAL SPRINT MULTIPLIER SHOULD BE COPIED INTO G3AB; PRESERVE THE LIVE RESULT.**
- **NEXT:** representative nonhuman Batch 2, then assess whether native coverage is sufficient to move to New Balance comparison.

### EV-403 — Initial Speed calibration scope sufficient; raw alias safety blocker identified before full INI

Observed:
- The User disclosed that a gameplay mod was active during creature testing which can expose additional attack types to some creatures beyond their vanilla attack repertoire. The mod does not replace the animation-speed owner; the calibration probe still observed the live Gothic speed result for the factual action that executed.
- Therefore EV-402 remains valid as speed-route evidence for the actions that actually ran, but it must not be read as proof that every observed creature/action combination is available in unmodded Gothic.
- The User chose to stop broad creature catalogue calibration for the current Speed feature. The existing human/loadout evidence plus selected creature evidence is sufficient for an initial shipping INI; a larger creature catalogue may be built later as documentation/reference work after the main mod is further along.
- Current `BehaviorProfiles::TryGetAnimationUseTypeToken` collapses several raw UseTypes into animation-category tokens:
  - `Axe -> 2h`;
  - `Pickaxe -> 2h`;
  - `Halberd -> staff`;
  - `Broom/Rake/Shovel/Fan -> staff`;
  - `PhysicalFist -> fist`.
- EV-397 directly supports Axe behaving like 2H and Halberd behaving like Staff on sampled Speed routes.
- The pinned New Balance `GetAnimationSpeedModifier` source distinguishes the raw Normal-attack policies: None+2H, None+Axe, None+Staff and None+Halberd receive `0.7*M`, while Pickaxe/Broom/Rake/Shovel/Fan are not in those explicit branches and fall through to the generic Normal result `1.0*M`.
- Current `AttackSpeed::ComposeCompatibleSpeed` looks up only the normalized grouped profile and then uses that profile's single `ReferenceHitBaseSpeed`. Therefore an active `Hero_None_2H` Normal profile with `B=0.7` would also match raw Pickaxe under the current token collapse and could incorrectly compose a route whose compatible owner uses a different base. The same risk exists for Staff-group tool aliases.
- This is the exact concern already anticipated by EV-392: normalized authoring identity and raw technical base policy are not always interchangeable.

Interpretation:
- Broad creature calibration is no longer a blocker for Speed finalization.
- Before activating a full shipping INI, profile-token normalization must fail closed for raw aliases whose Speed base is not proven equivalent.
- The smallest accepted correction is:
  - retain `Axe -> 2h` and `Halberd -> staff`, because sampled native equivalence is proven;
  - retain `PhysicalFist -> fist` for the established creature/raw55 profile model;
  - stop collapsing `Pickaxe`, `Broom`, `Rake`, `Shovel`, and `Fan` into the calibrated 2H/Staff tokens; give them distinct profile tokens so ordinary 2H/Staff profiles cannot accidentally claim them.
- This is a fail-closed calibration-safety correction, not a return to weapon-specific Speed policy. Those raw types may be configured later through their own explicit profiles if their native references are established.
- Human bare Fist remains outside the initial full Speed INI because its native reference has not been cleanly calibrated and New Balance applies special Fist policy. This does not block the calibrated human weapon profiles.

Initial full-INI calibration set:
- Hero None+1H: Normal `0.60`, Quick `1.00`, Power `1.00`, Pierce `1.00`.
- Hero Shield+1H: same.
- Hero Torch+1H: same.
- Hero 1H+1H: Normal `0.60`, Quick `1.00`, Power `0.90`, Pierce `1.00`, SimpleWhirl `1.30`.
- Hero None+2H (also proven Axe alias): Normal `0.70`, Quick `1.00`, Power `1.00`, Hack `1.00`, Whirl `1.00`.
- Hero None+Staff (also proven Halberd alias): Normal `0.70`, Quick `1.00`, Power `1.00`, Hack `1.00`, Whirl `1.00`.
- Sabertooth None+Fist: Normal/Quick/Power `1.00`.
- Troll Fist+Fist: Normal/Quick/Power `1.00`.
- Sprint has no separate key and inherits Power authoring while preserving the live contextual differential.

Disposition:
- **PASS — INITIAL NATIVE CALIBRATION IS SUFFICIENT FOR SPEED FINALIZATION.**
- **BROAD CREATURE CATALOGUE CALIBRATION DEFERRED; NOT A CURRENT BLOCKER.**
- **OPEN FINALIZATION BLOCKER — FAIL-CLOSED RAW TOOL-ALIAS PROFILE SAFETY BEFORE FULL ACTIVE INI.**
- **HUMAN BARE FIST SPEED PROFILE DEFERRED UNTIL NATIVE B IS ESTABLISHED.**
- **NEXT:** bounded source correction + full active INI, then final intended-stack production runtime acceptance. No separate broad New Balance calibration campaign is required; EV-395 plus final intended-stack acceptance own compatibility closure.

### EV-404 — Late native calibration additions processed; Boar Power closed and Batch 2 recorded

Observed:
- Three User-pushed clean-native calibration artifacts were processed with the unchanged extended 18-Hit-caller probe and are archived byte-identically:
  - `research/archive/2026.10.01_speed_calibration_boar.log`;
  - `research/archive/2026.10.01_speed_calibration_nonhuman_batch2.log`;
  - `research/archive/2026.10.01_speed_calibration_shovel_pickaxe.log`.
- Boar follow-up: 38 calls / 7 unique / 0 drops; Normal Hit `1.0`; ordinary Power Raise/Hit `1.5 / 1.0`; factual Sprint through passed Power Raise/Hit `1.5 / 1.5`. This closes the EV-402 Boar gap: ordinary Power Hit reference `B=1.0`.
- Nonhuman Batch 2: 463 calls / 29 unique / 0 drops.
  - Minecrawler None+Fist: Normal `1.0`, Quick R/L `1.0`, Power Raise/Hit `1.5 / 1.0`;
  - Gargoyle None+Fist: observed Normal `1.0`, Power Raise/Hit `1.5 / 1.0`;
  - Golem None+Fist: Normal `1.0`, Power Raise/Hit `1.5 / 1.0`, Sprint Raise/Hit `1.5 / 1.5`;
  - Bison None+Fist: Normal `1.0`, Power Raise/Hit `1.5 / 1.0`, Sprint Raise/Hit `1.5 / 1.5`;
  - T-Rex was not tested.
- The User clarified that a gameplay mod can expose additional factual attack types to creatures beyond their vanilla repertoire. In particular, vanilla Gargoyle normally has only Power-attack animation coverage. The probe still records the live Gothic speed result for any factual action that executes, so these rows are valid speed-route observations but not a vanilla attack-availability catalogue.
- Tool/use-type run: 33 calls / 15 unique / 0 drops.
  - raw Axe52: Normal `0.7`, Quick R/L `1.0`, Power Raise/Hit `1.5 / 1.0`, Hack `1.0`, Whirl `1.0`;
  - raw Halberd51: corresponding Staff-shaped routes at the same values;
  - no factual melee Normal/Power/Quick/Hack/Whirl rows were produced for Pickaxe/Shovel/Fan/Broom/Rake;
  - one raw Unknown15 / Other48 / Hit `1.5` cast-like row is not evidence for a melee tool profile.
- The User reports the tested work tools generally played dedicated interaction animations and returned to inventory instead of remaining equipped as weapons; Fan could not be equipped in the tested player fixture.

Interpretation:
- Axe/Halberd independently reconfirm EV-397's sampled vanilla speed equivalence with 2H/Staff-shaped routes.
- The tool run does not establish a current player melee Speed route for Pickaxe/Shovel/Fan/Broom/Rake, and it does not prohibit a future mod from making those raw UseTypes combat-capable.
- Broad creature calibration is sufficient for current Speed development; additional species may be catalogued later for documentation/readme expansion.
- Creature rows observed under the attack-expansion mod are factual executed speed routes, not claims about vanilla attack availability.

Provenance:
- User-pushed source commit: `826cd8e49dea464661a02dd3f69b2d2b286b3cc5`;
- Boar blob: `b3db18521e0f86b1ff830ce52f8cf7f6bdc4e8ef`;
- Batch-2 blob: `c0f1be70187adc6db7ba3c69e5822b22523429c3`;
- tool/use-type blob: `3e6d62de5374e5a93eea22856d0fd0314b2bcd5b`;
- probe SHA256: `F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`.

Disposition:
- **PASS — BOAR ORDINARY POWER HIT B=1.0 CLOSED.**
- **PASS — REPRESENTATIVE NONHUMAN BATCH 2 RECORDED; T-REX NOT TESTED.**
- **PASS — AXE/HALBERD FULL SAMPLED SPEED ROUTES RECONFIRMED.**
- **NO CURRENT PLAYER MELEE SPEED ROUTE ESTABLISHED FOR THE TESTED WORK TOOLS.**
- **BROAD NATIVE CALIBRATION IS NO LONGER A SPEED-FINALIZATION BLOCKER.**

### EV-405 — Raw UseType becomes Speed profile identity; animation-token normalization remains filename-only

Observed / design correction:
- After EV-403, the User clarified the intended mod-compatibility rule: if two raw UseTypes share vanilla animation assets, their shipped Speed values may be identical; if a separation mod gives one UseType distinct animations, G3AB should allow a distinct Speed profile for that raw UseType without another C++ feature branch.
- Current `BehaviorProfiles::TryGetAnimationUseTypeToken` reuses serialized-animation normalization for profile identity, including `Axe -> 2H`, `Halberd -> Staff`, `Pickaxe -> 2H`, `Broom/Rake/Shovel/Fan -> Staff`, and `PhysicalFist -> Fist`.
- This conflates animation token normalization (correct for filename/resource interpretation under `ANIMATION_RULES.md`) with Speed/Raise profile identity (which should preserve factual raw equipment UseType).
- Current-motion/asset identity is not suitable for deciding this at the Speed request boundary because request semantics are authoritative and the current motion may be stale/outgoing.

Accepted rule (ADR-0010):
- Keep the profile key shape `AnimationFamily + LeftAnimationUseType + RightAnimationUseType`, but profile UseType fields now mean canonical raw `gEUseType` token.
- Distinct raw values remain distinct profile values, including `2H` vs `Axe` vs `Pickaxe`; `Staff` vs `Halberd` vs work-tool raw types; and `Fist` vs `PhysicalFist`.
- Vanilla/shared-animation defaults may give separate raw profiles identical calibrated values. There is no automatic inheritance requirement and no need to inspect animation filenames.
- A separation mod can change only the raw profile it separates. Example: `Hero + None + Axe` may use a different `BaseSpeed` from `Hero + None + 2H` while both ship identically by default.
- Unknown/unconfigured raw UseTypes fail closed to the live compatible result.
- This supersedes EV-403's proposed remedy of retaining Axe->2H / Halberd->Staff profile aliasing while only separating work-tool aliases. EV-403 remains valid for calibration-sufficiency and for identifying that profile identity needed review; its specific remedy is superseded.

Initial active INI consequence:
- separate `Hero_None_2H` and `Hero_None_Axe` sections with identical initial reference/default values;
- separate `Hero_None_Staff` and `Hero_None_Halberd` sections likewise;
- `Sabertooth_None_Fist` remains raw Fist;
- `Troll_PhysicalFist_PhysicalFist` uses distinct raw PhysicalFist identity;
- uncalibrated work-tool profiles remain absent;
- human bare Fist remains a separate future calibration/profile question if desired.

Runtime acceptance consequence:
- After raw-UseType identity and the full INI are implemented, the User's Axe Separation mod is an excellent bounded positive control: give 2H and Axe visibly different `BaseSpeed` values and verify raw UseType selects the profile independently of whether the asset is shared or separated.

Disposition:
- **ACCEPTED — SPEED/RAISE PROFILE USETYPE IDENTITY PRESERVES RAW USETYPE.**
- **ANIMATION_RULES FILENAME NORMALIZATION REMAINS UNCHANGED.**
- **NO AUTOMATIC SPEED PROFILE COUPLING IS INFERRED FROM SHARED ANIMATION ASSETS.**
- **NEXT — IMPLEMENT ADR-0010 + FULL RAW-USETYPE INI, THEN AXE-SEPARATION/INTENDED-STACK RUNTIME ACCEPTANCE.**

### EV-406 — Speed separation-profile identity probe PASS; resolved animation-set identity selected

Observed:
- The User ran the diagnostics-only separation identity probe built from source commit `2acde620648d05614c4970e8a0451a778baaef59`.
- Built/live probe SHA256 matched exactly:
  `76B65B57ACFB536E7B044751B3576B912ECE741F8C73480BFAA6680DDBEA7702`.
- The probe captured `ResolvedRequestedAni = Entity.GetAni(passedAction, phase)` before the live speed-owner call, retained it in observation identity/output, called the live speed owner exactly once, and returned its result unchanged.
- Five committed runs were processed:
  - native Fist/Orc/Demon control: 628 intercepted calls, 88 unique observations, 0 drops;
  - Zombie Separation: 430 / 50 / 0;
  - Axe Separation: 393 / 42 / 0;
  - Rapier Separation: 74 / 22 / 0;
  - Zombie + Axe Separation: 118 / 17 / 0.
- Human player bare Fist / `Hero_..._None_Fist_...`:
  - Normal Hit = `1.0` on both P0/P1 samples;
  - Power Raise = `1.5`;
  - Power Hit = `1.0`;
  - no player Quick-Fist Speed row occurred; the User clarified that native human Fist has no Quick attack animation family, so this is an intentional native absence rather than a calibration gap.
- Native zombies without separation continued to resolve ordinary human animation names. Example factual raw Axe52 resolved `Hero_..._None_2H_...`; raw Staff resolved `Hero_..._None_Staff_...`; shield+1H resolved `Hero_..._Shield_1H_...`.
- Native zombie Fist shared the `Hero + None + Fist` animation set but returned Normal live speed `1.4` while player Hero Fist returned `1.0`. Power Hit remained `1.0`. This demonstrates why the live compatible result must remain authoritative for contextual actor modifiers even when an animation-set profile is shared.
- Zombie Separation changed the request-time family and exact requested assets:
  - `Family=Zombie`;
  - examples resolve `Zombie_..._None_2H_...`, `Zombie_..._None_Staff_...`, `Zombie_..._Shield_1H_...`, and `Zombie_..._None_Fist_...`;
  - underlying factual raw weapon UseTypes remained available independently.
- Axe Separation:
  - raw Axe52 remained factual;
  - Hero player and compatible actors resolved `..._None_Axe_...` instead of the native shared `..._None_2H_...`;
  - sampled values remained Normal `0.7`, Quick `1.0`, Power Hit `1.0`, Hack `1.0`, Whirl `1.0`.
- Rapier Separation supplied the decisive counterexample to raw-UseType profile identity:
  - `Family=Hero`;
  - factual equipped right UseType remained ordinary `1H(2)`;
  - resolved requests consistently used `Hero_..._None_Rapier_...`;
  - Normal `0.6`, Quick `1.0`, Power Hit `1.0`, Pierce `1.0`;
  - therefore `AnimationFamily + raw UseTypes` cannot distinguish ordinary 1H from Rapier.
- Zombie + Axe composition:
  - `Family=Zombie`;
  - raw right source = Axe52;
  - resolved requests = `Zombie_..._None_Axe_...`;
  - sampled Normal `0.7`, Quick `1.0`, Power Hit `1.0`, Hack/Whirl `1.0`.
  - Family separation and animation-set separation therefore compose without a mod-specific branch.

Interpretation:
- The Speed profile should identify **the animation set being timed**, not the inventory/source UseType that happened to select it.
- Final grouped profile identity is:
  ```text
  AnimationFamily
  + ResolvedLeftAnimationToken
  + ResolvedRightAnimationToken
  ```
  where left/right tokens are parsed from the exact request-time string returned by `Entity.GetAni(factualAction, factualPhase)`.
- Examples:
  - vanilla Hero raw Axe -> resolved `Hero + None + 2H` -> shares the ordinary 2H profile;
  - Axe Separation -> resolved `Hero + None + Axe` -> independently configurable Axe profile;
  - Rapier Separation -> raw 1H but resolved `Hero + None + Rapier` -> independently configurable Rapier profile;
  - Zombie Separation -> `Zombie + <resolved tokens>` -> independent family profiles;
  - Zombie+Axe -> `Zombie + None + Axe` -> dimensions compose naturally.
- This matches the User's authoring rule: **if animations are shared, their Speed profile is shared; if a mod resolves distinct animations, those animations can receive a distinct profile.**
- Raw `gEUseType` remains important diagnostic/source/collision information but is not part of final Speed/Raise profile identity.
- Factual `gEAction` remains the attack-family authority. The resolved animation's serialized action name does not replace it; e.g. factual Hack may resolve a `FinishingAttack`-named asset while remaining Hack for Speed policy.
- `CurrentMovementAni()` remains observational only and is not profile identity.
- Unknown/malformed request animation identity must fail closed to the live compatible result.

Human Fist calibration consequence:
- Initial `Hero + None + Fist` profile may include Normal `B=1.0` and Power `B=1.0`.
- Do not add Quick for native human Fist: Gothic's native human Fist animation set does not provide that attack family. If a future custom/separation mod adds unique human-Fist Quick animations, calibrate that new resolved animation set before adding its Quick block.
- Native zombie Hero/Fist Normal `1.4` is preserved as live compatible context when shared with the same animation-set profile: with `B=1.0`, composition retains the `1.4` factor.

Architecture consequence:
- ADR-0010 raw-UseType profile identity is superseded by ADR-0011.
- The existing grouped profile shape remains, but its two equipment fields are renamed conceptually/user-facing to resolved animation tokens:
  `LeftAnimationToken` and `RightAnimationToken`.
- Production lookup should resolve `Entity.GetAni(action, phase)` at the exact Speed request boundary, extract the family/use-type fields from Gothic's canonical animation-name structure, and use those tokens for matching.
- No filename/current-motion polling and no Axe/Rapier/Zombie hard-coded cases are justified.

Provenance:
- User-pushed runtime commit: `d775c2d30a9823e6b9919de92037aa7084fd0fd6`;
- probe implementation: `2acde620648d05614c4970e8a0451a778baaef59`;
- probe built/live SHA256: `76B65B57ACFB536E7B044751B3576B912ECE741F8C73480BFAA6680DDBEA7702`;
- native log blob: `4c8cb5466762e8854264bcc345c385c4c40f5dd2`;
- Zombie Separation blob: `d259ea2dd4d24a85f704558ae2815d69f6226b05`;
- Axe Separation blob: `a73758f78812b521e3a9f034605234cb7597c94f`;
- Rapier Separation blob: `cfcb457361dff01ea6d7692b00da1d53c7efbfc1`;
- Zombie+Axe blob: `e168c4f06e3f1ec60c850aab7830ad7d0b4007e8`;
- prior collision compatibility controls: EV-369–EV-372.

Disposition:
- **PASS — SPEED SEPARATION PROFILE IDENTITY PROBE CLOSED.**
- **PASS — HUMAN PLAYER FIST NORMAL/POWER B=1.0 CALIBRATION CLOSED; QUICK IS NATIVE-ABSENT AND INTENTIONALLY OMITTED.**
- **SUPERSEDE ADR-0010 WITH ADR-0011 RESOLVED ANIMATION-SET PROFILE IDENTITY.**
- **NEXT — IMPLEMENT ADR-0011 + FULL ACTIVE INI, THEN INTENDED-STACK PRODUCTION RUNTIME ACCEPTANCE.**

### EV-407 — ADR-0011 production Speed native/action routing + Axe separation acceptance PASS

Fixture:
- branch `development`, source candidate `ba3e76549eff5c7fdfc2d165ec976e640ef9c24c` carried by maintained branch state;
- production `Script_G3AnimationBehaviors.dll` built locally and deployed under POP-03;
- exact built/live DLL SHA256: `D975BABFA8E5DCE3C4A49BC46D7A49D08379B7CE479C2DE143DE5458DDA5335E`;
- shipping/live INI identity before temporary acceptance edits: `41F52E182D5F873FE29BCC2B4F9E043B0DD38177D2295FC1013C6780105E0A4C`;
- native-only initial fixture: `Script_NewBalance.dll` absent; `Script_AttackCollision.dll` absent;
- POP-04 startup/load smoke reached the main menu and exited normally with no startup/load problem.

Observed production Speed controls:
- with shipped `BaseSpeed=1.00`, Hero Normal attacks were visibly faster than native timing for representative 1H, Torch+1H, dual-1H, 2H and Staff families, matching their calibrated native Normal bases;
- temporary live-INI action-isolation controls then made selected Quick/Power/Pierce/Hack/Whirl/SimpleWhirl routes visibly slow while neighboring configured/unchanged routes retained their assigned speed;
- current separated Hack and Finishing assets both obeyed the settings assigned to their own factual routes in the tested configuration, consistent with the already-proven factual-action separation and with Finishing remaining outside the production Speed profile surface unless separately reached through its native behavior.

Axe resolved-profile identity control:
- with Axe Separation absent, ordinary 2H sword and raw Axe both followed the `Hero + None + 2H` profile and both slowed when that profile was set to `0.40`;
- after installing Axe Separation without changing the relevant profile identities, ordinary 2H remained on the slowed `Hero + None + 2H` profile while Axe switched to the independently configured `Hero + None + Axe` profile at `1.00`;
- the User then inverted the configuration: all Axe attack settings were set to `0.40` while 2H settings were restored to `1.00`; with Axe Separation active, Axe and 2H again followed their independently assigned values;
- after removing Axe Separation, both Axe and 2H again followed the `Hero + None + 2H` settings.
- This is a bidirectional production acceptance of ADR-0011: shared resolved assets share a profile; separated resolved animation tokens select an independent profile without raw-weapon/mod-name branching.

Integrated collision regression observation:
- the User's authored 1H Normal attacks are only 0–8 frames long. At the new `1.00` playback they can be too short for Gothic's native collision timing to activate reliably, yet the attacks still connected at the authored contact point with current G3AB collision markers;
- dual-wield attacks initially failed to connect at `1.00`; inspection found those files still contained obsolete test markers. Replacing them with the current marker scheme restored correct contact.
- This is positive integrated regression evidence for marker-authored collision under faster Speed playback. It does not reopen collision design.

Scope clarification:
- no ordinary Hero 2H Sprint attack fixture has been established in prior runtime work; do not manufacture one for acceptance. Sprint/Power inheritance remains owned by the previously observed factual Sprint routes and ADR-0009 evidence.

Interpretation:
- production Speed action routing works across the representative tested Hero families;
- ADR-0011 resolved animation-set identity works in production in both shared-Axe and separated-Axe directions;
- Speed changes did not regress the marker collision system in the tested short/high-speed animations.

Provenance:
- diagnostics-free visual runtime observations reported by the User on 2026-10-03;
- exact production binary identity above was established before launch under POP-03;
- temporary runtime INI edits were acceptance controls only and did not modify the repository shipping INI.

Disposition:
- **PASS — REPRESENTATIVE NATIVE PRODUCTION SPEED ACTION ROUTING.**
- **PASS — AXE SHARED/SEPARATED ADR-0011 PROFILE IDENTITY.**
- **PASS — INTEGRATED COLLISION MARKER REGRESSION CONTROL.**
- **NEXT — RAPIER SEPARATION, HUMAN FIST/CREATURE/UNCONFIGURED CONTROLS, ZOMBIE FAMILY + ZOMBIE/AXE COMPOSITION, THEN INTENDED NEW BALANCE COMPATIBILITY SANITY.**

### EV-408 — Rapier resolved-profile independence and non-leakage across other loadouts PASS

Fixture:
- same production DLL accepted in EV-407, exact SHA256 `D975BABFA8E5DCE3C4A49BC46D7A49D08379B7CE479C2DE143DE5458DDA5335E`;
- temporary live INI edits only; repository shipping INI unchanged;
- Rapier separation DLL toggled on/off between runs.

Observed:
- with Rapier separation absent and `Hero + None + 1H` set to `0.40`, both ordinary 1H and the Rapier weapon followed the shared 1H profile at `0.40`;
- with Rapier separation active and `Hero + None + Rapier` set to `1.00`, Rapier followed `1.00` while ordinary 1H remained at `0.40`;
- dual-1H was then exercised with all practical mixed combinations: ordinary 1H + ordinary 1H, Rapier + ordinary 1H, ordinary 1H + Rapier, and Rapier + Rapier. All continued to follow the `Hero + 1H + 1H` profile rather than leaking into the single-Rapier profile;
- when `Hero + 1H + 1H` was changed to `0.40`, those dual-wield combinations followed `0.40` as assigned while single-Rapier remained independently governed by its `Hero + None + Rapier` profile;
- Torch+1H was also checked with both an ordinary 1H weapon and a Rapier in the weapon hand. It followed the `Hero + Torch + 1H` profile exactly: first at `1.00`, then at `0.40`, regardless of whether the held weapon was the Rapier.
- This matches the separation mod's authored scope: it supplies a distinct single-Rapier animation set, not distinct dual-wield or torch Rapier sets.

Interpretation:
- production profile selection follows the resolved animation-set tokens, not the raw weapon identity;
- single-Rapier separation does not contaminate unrelated resolved dual-wield or torch animation sets;
- the current generic profile parser/matcher is data-driven: it reads `AnimationFamily + LeftAnimationToken + RightAnimationToken` from each `[Profile.*]` section and compares them to fields 2/3 of the exact request-time animation name. Therefore, if a future mod actually resolves distinct tokens for combinations such as `Rapier+1H`, `1H+Rapier`, `Rapier+Rapier`, or `Torch+Rapier`, corresponding INI profiles should be representable without a new mod-specific C++ branch, subject to factual runtime verification/calibration of those new routes.

Provenance:
- diagnostics-free visual runtime observations reported by the User on 2026-10-03;
- generic parser/matcher behavior confirmed from current `BehaviorProfiles.cpp`.

Disposition:
- **PASS — RAPIER SEPARATION RESOLVED-PROFILE INDEPENDENCE.**
- **PASS — NO RAPIER PROFILE LEAKAGE INTO TESTED DUAL-1H OR TORCH+1H RESOLVED SETS.**
- **NEXT — HUMAN FIST / CREATURE / UNCONFIGURED CONTROL, THEN ZOMBIE FAMILY + ZOMBIE/AXE COMPOSITION, THEN NEW BALANCE SANITY.**

### EV-409 — Human Fist / creature profiles / unconfigured fail-closed acceptance PASS

Fixture:
- same production DLL accepted in EV-407/EV-408, exact SHA256 `D975BABFA8E5DCE3C4A49BC46D7A49D08379B7CE479C2DE143DE5458DDA5335E`;
- temporary live-INI acceptance edits only; repository shipping INI unchanged.

Observed:
- `Hero + None + Fist` Normal and Power were configured to `BaseSpeed=0.40`; both human Fist routes visibly obeyed the slowdown;
- `Sabertooth + None + Fist` Normal/Quick/Power were configured to `0.40`; the tested Sabertooth attacks obeyed the configured slowdown;
- `Troll + Fist + Fist` was likewise tested at `0.40`; the tested Troll attacks obeyed the configured slowdown;
- a Wolf was spawned as an intentionally unconfigured animation family/profile control; its attacks retained native timing and showed no visible G3AB Speed intervention.

Interpretation:
- configured human bare-Fist lookup works in the final production profile system;
- configured nonhuman family profiles work for both Sabertooth and Troll;
- absence of a matching profile fails closed to the live/native compatible result, as designed.

Provenance:
- diagnostics-free visual runtime observations reported by the User on 2026-10-03;
- exact production binary identity established before launch under POP-03.

Disposition:
- **PASS — HUMAN FIST NORMAL/POWER PRODUCTION PROFILE.**
- **PASS — REPRESENTATIVE CONFIGURED CREATURE PROFILES.**
- **PASS — UNCONFIGURED WOLF FAIL-CLOSED/NATIVE CONTROL.**
- **NEXT — ZOMBIE FAMILY INDEPENDENCE + ZOMBIE/AXE COMPOSITION, THEN NEW BALANCE COMPATIBILITY SANITY.**

### EV-410 — Final Speed intended-stack runtime acceptance PASS

Fixture:
- production `Script_G3AnimationBehaviors.dll` from the accepted ADR-0011 candidate, exact built/live SHA256 established earlier in this acceptance campaign as `D975BABFA8E5DCE3C4A49BC46D7A49D08379B7CE479C2DE143DE5458DDA5335E`;
- New Balance runtime stack installed by the User together with its companion DLLs;
- all current separation animation mods used by the acceptance campaign installed for the final intended-stack sweep;
- temporary live-INI acceptance values used only for runtime controls; repository shipping INI remained the durable source copy.

Zombie family + composed token controls:
- Zombie Separation was tested with Staff and Axe at both `BaseSpeed=1.00` and `BaseSpeed=0.40`; the animations followed the assigned Zombie-family profiles;
- Axe Separation was toggled in combination with Zombie Separation and Zombie Axe behavior continued to follow the profile selected by the actually resolved animation tokens;
- this closes the family dimension and family+token composition required by ADR-0011.

Final intended-stack sweep:
- with all tested Speed profiles set to `BaseSpeed=1.00`, the User tested the weapon/loadout families, human Fist, Zombies, Sabertooth and Troll under the installed New Balance stack; all configured routes behaved according to the INI;
- the User then set the tested Speed profiles to `BaseSpeed=0.40` and repeated the same broad sweep; all configured routes again followed the assigned slowdown;
- Wolf remained unchanged/native in both the `1.00` and `0.40` sweeps because no Wolf profile is configured.
- Separation animation sets remained independently governed by their resolved profiles in the intended stack.

Interpretation:
- the final production profile mechanism works under the intended New Balance runtime stack rather than only in native-only fixtures;
- authored `BaseSpeed` changes continue to take effect while the compatible-owner stack remains present;
- resolved animation family + left/right token identity continues to select the intended profile across shared and separated animation sets;
- unconfigured identities continue to fail closed to the live compatible result;
- no further broad Speed calibration or profile-identity runtime testing is justified absent contradictory evidence.

Scope:
- this closes the **runtime acceptance** of Speed v2 / ADR-0011.
- release-facing INI wording/organization cleanup and restoration of the final shipping values remain packaging/configuration work, not a mechanism or runtime-acceptance gate.
- Raise may begin only after that final Speed packaging/configuration closure is completed and the Speed task is formally closed.

Provenance:
- diagnostics-free visual runtime observations reported by the User on 2026-10-04;
- earlier acceptance stages: EV-407 through EV-409.

Disposition:
- **PASS — ZOMBIE FAMILY PROFILE INDEPENDENCE.**
- **PASS — ZOMBIE + AXE FAMILY/TOKEN COMPOSITION.**
- **PASS — INTENDED NEW BALANCE STACK COMPATIBILITY SANITY.**
- **PASS — FINAL SPEED RUNTIME ACCEPTANCE COMPLETE.**
- **NEXT — RESTORE/REFINE RELEASE-FACING SHIPPING INI, CLOSE SPEED FORMALLY, THEN BEGIN RAISE.**

