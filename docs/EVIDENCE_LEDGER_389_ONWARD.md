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
