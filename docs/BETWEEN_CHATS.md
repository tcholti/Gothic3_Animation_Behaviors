# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-02

## Current bridge — remaining equipped-melee marker architecture

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap.

CAM is the constitutional collaboration layer; `docs/README.md` is the highest Gothic-specific project charter beneath CAM. Do not modify CAM from Gothic 3 work.

Known unrelated local file remains completely untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Closed boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
project structural/rules/product stabilization  COMPLETE
```

Do not reopen the verified C1 lifecycle/generation architecture without concrete contradicting evidence.

Branch lifecycle remains:

```text
complete collision on docs/collision-source-evidence
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from updated main
```

Do not create `feature/raise-attack-speed` early.

---

## Required marker scope

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

`GetUpAttack` is **not part of the planned development roadmap**. Current review shows legitimate offense can occur before later CombatMove and its callback also changes `AniState` to `Stand`. Do not spend further marker-engineering time on GetUp unless a future concrete requirement explicitly justifies a separate investigation.

`FinishingAttack` remains deliberately excluded/native. Fist/body contact remains a separate source-adapter responsibility.

Accepted implementation strategy:

```text
freeze shared adapter architecture
→ implement Power + Pierce + SimpleWhirl + Hack in one bounded code change
→ validate each family independently
→ combined marker/lifecycle regression afterward
```

Current callback bookkeeping:

```text
Pierce       → StatePosition 1
SimpleWhirl  → StatePosition 1
Hack         → callback-shaped native routine at Script_Game +0x433D0 ends at StatePosition 1
Power normal → StatePosition 1
Power Dual   → StatePosition 2
```

Power repeated contacts remain authored through RIGHT/LEFT/BOTH/OFF + `ClearTriggeredList()` rearm. Do not create a separate Power marker engine.

One unresolved Hack collision fact remains: prove the registered callback identity/name corresponding to `Script_Game +0x433D0`; do not guess it from proximity.

---

## HackAttack optional animation routing

Known facts:

```text
gEAction_HackAttack      = 14
gEAction_FinishingAttack = 15

GetAniName = Game +0x16F840
Game +0x16FA16 indexes the action-string table at Game +0x3F75C0
```

This explains why simply adding `_HackAttack_` assets did not make Gothic select them: runtime Hack currently serializes the shared `FinishingAttack` action family.

Preferred authored fixtures remain:

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_2H_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot

Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

`100` is animation-author metadata, not a DLL constant. Gothic remains responsible for destination pose, distance and the rest of its filename contract.

Required feature behavior:

```text
runtime action == HackAttack
→ preserve the name/namespace produced by the active animation resolver
→ derive only the corresponding HackAttack action-token variant
→ matching Hack asset exists: use it
→ matching Hack asset absent: preserve original FinishingAttack resource/path unchanged
```

Dedicated Hack assets are optional overrides, not a dependency of G3AB.

### Current preferred technical direction

Static review now identifies a narrower compatibility point than hooking `GetAniName` itself:

```text
GetAniName builds final name
→ known New Balance string work can occur around Game +0x16B065
→ CombatMove later queries the motion resource at Game +0x16B10C
```

Gothic's native path already uses `IsAnimationMissed`, `QueryMotionDataEntity` and `AddMissingAnimation`. After successful query it uses the returned resource's filename and installs the returned resource through `SetMotion`. The SDK hook framework supports callsite interposition.

Therefore the current preferred Hack-routing candidate is a **narrow CombatMove resource-query adapter at the tested query callsite**, not a global action-table patch and not exclusive ownership of `GetAniName`. It should derive the exact Hack candidate from the already-produced Finishing resource name, query the candidate through Gothic's animation resource system, and fall back to the untouched original resource when absent. This remains to be implemented/runtime-validated before being treated as closed compatibility behavior.

### Jackydima `Script_Animation` compatibility

`Script_Animation` hooks `GetAniName` and can change the serialized weapon namespace, e.g. shared `2H` to a distinct `Axe` namespace. G3AB must preserve whatever namespace that active resolver produced and change only the action token when the optional matching Hack asset exists.

Do not globally patch action 14's action-string table and do not normalize `Axe`/other external namespaces back to G3AB guesses.

---

## Useful animation-fallback observation

User observation from normal gameplay/animation authoring:

```text
when a Sprint animation is absent
→ Gothic can display/use Run as an animation fallback
→ Sprint gameplay semantics still remain active (faster movement/distance, stamina drain)

when the correctly named Sprint asset is later added
→ Gothic begins using that Sprint asset
```

Treat this as a strong design clue that gameplay action semantics and selected animation resource can remain separate and that optional more-specific animation assets can be discovered/fallback-capable. Do **not** generalize it yet into a universal action-fallback hierarchy without targeted source/runtime evidence.

---

## AttackContinuationProtection goal

The desired responsibility is:

```text
prevent the known destructive continuation/bad-skip mechanism
from terminating or advancing through a legitimately live Hit execution
```

Current preferred research direction is to identify and, if appropriate, freeze/suppress the responsible timer/continuation trigger while the Hit remains authoritatively alive. The outcome is frozen; **timer freeze is not yet frozen as the only implementation mechanism**. Prefer a cleaner native operation if research exposes one.

Keep `AttackContinuationProtection` separate from `CollisionLifecycleGuard`; retain C1-R1 underneath as the general lost-cleanup fail-safe.

---

## First public release boundary

The first public Animation Behaviors release is planned only after these framework responsibilities are mature and assembled in diagnostics-free `Script_G3AnimationBehaviors`:

```text
general marker/collision framework
+ validated AttackContinuationProtection / bad-skip prevention
+ mature Raise framework
+ general/action/profile attack-speed + configuration framework
+ required compatibility/regression
```

**Animation content in Release 1 is intentionally 2H only.** Framework completeness does not require every weapon family to have finished replacement animations before the DLL is released.

The 2H set is the first complete reference implementation. Release communication/video should explain how other animators/modders can use markers, Raise assets and speed configuration with their own animations.

After Release 1:

```text
update remaining weapon-family animations one family at a time
→ adapt them to new speed possibilities
→ add/adjust Raise animations
→ add markers
→ release each content family incrementally
```

During that long content-update period, climbing may be revisited sporadically and is not a blocker. Target-acquisition changes remain a separate future system. Additional animation-system improvements—such as allowing specific jump animations to be selected when valid assets exist—should be investigated one at a time as concrete useful cases appear rather than preplanned as one large rewrite.

---

## Immediate next step

Without the Gothic PC, continue static planning/source work only as useful.

The first fact that may genuinely require the Gothic installation is:

```text
resolve/confirm the registered AI callback identity for Script_Game +0x433D0
```

Then:

```text
freeze exact Power/Pierce/SimpleWhirl/Hack adapter + Hack optional-routing architecture with User
→ create one bounded Work implementation responsibility
→ build/deploy/test when the Gothic PC is available
```
