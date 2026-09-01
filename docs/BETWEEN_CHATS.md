# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-02

## Current bridge — remaining equipped-melee marker architecture review

Repository:

```text
tcholti/Gothic3_Animation_Behaviors
```

Active branch:

```text
docs/collision-source-evidence
```

Stable branch:

```text
main
```

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap.

CAM is the constitutional collaboration layer; `docs/README.md` is the highest Gothic-specific project charter beneath CAM; `COLLABORATION_RULES.md` owns participant allocation and detailed Gothic CAM operationalization. Do not modify CAM from Gothic 3 work.

Known unrelated local file remains completely untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Accepted boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
project structural/rules/product stabilization  COMPLETE
governance/planning checkpoint                  aligned to protected main before new collision implementation
```

Do not reopen the verified lifecycle/generation architecture without concrete contradicting evidence.

Accepted branch/phase plan:

```text
docs/collision-source-evidence
= sole active feature branch through completed collision work

complete collision research/implementation
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from that updated main
→ continue Raise + attack-speed + configuration work there
```

Do not create `feature/raise-attack-speed` before the collision promotion.

---

## Current responsibility

Finish the source/architecture review needed to freeze **one bounded implementation for the remaining required ordinary equipped-melee marker families**.

Accepted marker-expansion scope:

```text
REQUIRED:
PowerAttack
PierceAttack
SimpleWhirl
HackAttack

DEFERRED / NICE TO HAVE:
GetUpAttack
= source review now shows materially different behavior
= legitimate offense can occur before later CombatMove
= native callback also changes AniState to Stand
= do not contaminate the clean marker batch unless a later separate responsibility justifies it

DELIBERATELY EXCLUDED FROM THIS MARKER EXPANSION:
FinishingAttack
= true downed-enemy execution path; preserve native behavior
= User tests show execution death timing remains timer-like/contact-independent when Hit duration/contact changes

Fist/body contact
= separate source-adapter investigation after equipped-weapon coverage
```

Implementation strategy accepted by the User:

```text
review/freeze the shared architecture first
→ implement the remaining proven-compatible equipped-melee adapters in one bounded code change
→ test each newly supported family independently
→ run combined regression only after the individual family tests pass
```

Do **not** return to one implementation cycle per already-understood callback family merely for process symmetry. The shared marker/source/generation core is already proven; family-by-family causal confidence is preserved through separate validation.

---

## Callback/bookkeeping classification — current accepted result

The native callback shapes support one shared adapter architecture with family-specific completion policy:

```text
Normal
→ existing behavior; no custom StatePosition completion

Quick
→ existing marker ownership completes native collision callback at StatePosition 1

Whirl
→ existing marker ownership completes native collision callback at StatePosition 1

Pierce
→ one-stage native collision callback
→ marker ownership should complete at StatePosition 1

SimpleWhirl
→ one-stage native collision callback
→ marker ownership should complete at StatePosition 1

Hack
→ nearby native callback-shaped routine at Script_Game +0x433D0 performs Item_Attack(7), triggered-list clearing, then StatePosition 1
→ registered textual callback identity still needs one exact confirmation before Work

Power
→ native collision callback has two stages
→ ordinary/non-Dual marker-owned Power should complete the native collision stage at StatePosition 1
→ Dual 1H+1H Power has the second native collision/rearm stage and marker ownership should complete all competing native collision timing at StatePosition 2
→ repeated Dual contacts themselves remain authored through RIGHT/LEFT/BOTH/OFF + ClearTriggeredList rearm
```

Do not copy these as unrelated special-case marker engines. Use one canonical supported-family/action policy with only the minimum per-family callback-completion policy.

---

## HackAttack sub-responsibility

Hack is required and has two related but separate requirements:

```text
1. marker ownership / native collision-timing suppression for runtime gEAction_HackAttack (14)
2. optional dedicated HackAttack animation resolution instead of sharing the serialized FinishingAttack asset family
```

Known runtime facts:

```text
gEAction_HackAttack       = 14
gEAction_FinishingAttack  = 15
```

They are distinct runtime/cleanup semantics even though tested Hack currently reuses the serialized `FinishingAttack` animation family.

User rename test:

```text
simply providing/renaming to HackAttack-style files did not make Gothic select them in the tested case
```

Static engine finding now explains this strongly:

```text
gCScriptProcessingUnit::GetAniName
= Game +0x16F840
= receives native gEAction explicitly

Game +0x16FA16
→ indexes action-string table at Game +0x3F75C0 with that action
→ appends the serialized action token into the animation name
```

For runtime action 14, Gothic currently serializes the `FinishingAttack` action family rather than automatically discovering a `_HackAttack_` asset.

Preferred dedicated Hack fixture names:

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_2H_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot

Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

These deliberately mirror the native FinishingAttack naming contract while using the distinct `HackAttack` action token and keeping the currently useful Parade P0 stance. The Hit distance `100` is the current animation-author candidate and may change with the final animation; behavior code must not depend on that numeric suffix.

Governing animation principle:

```text
native action/phase/UseType/resolved-motion facts drive behavior code
filename fields remain Gothic's serialized animation contract
our DLL must not parse/reimplement destination-pose, movement-distance or other filename semantics Gothic already handles natively
```

### Hack animation routing — accepted compatibility direction

Dedicated Hack animations are **optional overrides**, not a requirement for using G3AB.

Required behavior:

```text
normal active animation resolver produces the ordinary Hack execution name
(which may be native Gothic or modified by another compatible animation-selection mod)
        ↓
runtime action factually == HackAttack
        ↓
G3AB derives/tests only the corresponding HackAttack action-token variant
        ↓
IF matching HackAttack asset exists
    → use the dedicated HackAttack animation
ELSE
    → preserve the original FinishingAttack animation name/path unchanged
```

Therefore:

```text
G3AB + no custom Hack assets
→ Hack continues using existing FinishingAttack animations

G3AB + matching custom Hack assets
→ Hack may use dedicated HackAttack animations
```

True runtime `FinishingAttack` action 15 remains completely native/unmarked.

### Jackydima Script_Animation compatibility

User identified:

```text
https://github.com/Jackydima/Script_Animation
```

Relevant source findings:

```text
Script_Animation hooks the same native GetAniName function at Game +0x16F840.
It rebuilds the animation name and globally replaces the UseType→string table at Game +0x2BAC98.
This lets normally shared weapon UseTypes acquire new serialized namespaces, e.g. Axe-specific animation filenames.
It uses the same action-string table at Game +0x3F75C0 identified independently above.
```

This is useful external proof of the engine mechanism, but G3AB should **not** copy the broad implementation.

Compatibility requirement:

```text
G3AB Hack routing must not require exclusive ownership of Game +0x16F840 GetAniName.
Do not depend on arbitrary DLL load order or assumed same-hook chaining with Script_Animation.
Do not normalize another mod's resulting Axe/Staff/etc. filename namespace back to G3AB's guess.
Preserve the animation name produced by the active/native resolver and change only the exact FinishingAttack→HackAttack action token when the optional Hack asset is valid.
```

This allows conceptually:

```text
native/shared environment:
..._2H_..._FinishingAttack_... → optional ..._2H_..._HackAttack_...

Script_Animation Axe namespace:
..._Axe_..._FinishingAttack_... → optional ..._Axe_..._HackAttack_...
```

A global action-string-table patch `HackAttack(14): FinishingAttack → HackAttack` is rejected as too broad. The animation inventory contains no native HackAttack assets and FinishingAttack assets exist across Hero 1H/Dual/Shield/Torch/2H/Staff and Orc 2H/Staff families. Global replacement could therefore redirect unrelated action-14 executions to missing assets.

Do not use the New Balance `Game +0x16B065` interception merely because it is known; New Balance compatibility is also required. Find the narrowest downstream/result-level route that composes with both native Gothic and relevant external animation-selection mods.

---

## Immediate remaining factual questions before Work

Only two narrow architecture facts remain before the multi-family Work task can be frozen:

```text
1. Hack collision callback identity
- resolve the registered AI-callback entry/name corresponding to the native callback-shaped routine at Script_Game +0x433D0
- prefer normal callback registry resolution over a build-specific direct hook if available

2. Hack optional-animation override mechanism
- identify a safe post-name-construction / result-level interception or equivalent mechanism that does not compete for exclusive ownership of GetAniName
- determine a clean exact-animation existence/preflight mechanism so missing Hack assets preserve the original FinishingAttack name
- preserve whatever serialized weapon namespace the active resolver already produced
```

Do not broaden this into a new animation-system rewrite.

Keep separate from the immediate implementation:

```text
Fist/body source adaptation
AttackContinuationProtection
mature collision compatibility gate
production collision migration into Script_G3AnimationBehaviors
feature/raise-attack-speed creation
Raise/speed/config redesign
```

Next step in Normal Chat:

```text
resolve the two narrow Hack facts above
→ freeze exact Power/Pierce/SimpleWhirl/Hack adapter + Hack optional-routing architecture with User
→ create one bounded Work implementation responsibility
→ validate Power, Pierce, SimpleWhirl and Hack one by one
```