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

OPTIONAL / NICE TO HAVE:
GetUpAttack
= include only if it fits the established C1/marker architecture cleanly
= defer if it requires new execution identity/lifecycle machinery or disproportionate reverse engineering

DELIBERATELY EXCLUDED FROM THIS MARKER EXPANSION:
FinishingAttack
= true downed-enemy execution path; preserve native behavior

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

## HackAttack sub-responsibility

Hack is more important than GetUp and has two related but separate requirements:

```text
1. marker ownership / native collision-timing suppression for runtime gEAction_HackAttack (14)
2. dedicated HackAttack animation resolution instead of sharing the serialized FinishingAttack asset family
```

Known runtime fact:

```text
gEAction_HackAttack       = 14
gEAction_FinishingAttack  = 15
```

They are distinct runtime/cleanup semantics even though tested 2H Hack currently reuses the serialized `FinishingAttack` animation family.

User rename test:

```text
simply providing/renaming to HackAttack-style files did not make Gothic select them in the tested case
```

Treat this as an animation-selection observation, not yet proof of the exact internal mapping mechanism.

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

Preferred Hack solution:

```text
runtime action 14 remains HackAttack
→ narrow native-compatible selection/routing change makes Gothic resolve HackAttack assets
→ Gothic continues interpreting the rest of the filename contract itself
→ Hack Hit markers then use the ordinary equipped-slot marker architecture

runtime action 15 remains FinishingAttack
→ existing execution assets/semantics remain native and unmarked
```

Do not construct full filenames in behavior code unless source evidence proves no cleaner native-resolution route exists.

---

## Immediate source questions before Work

Retrieve only enough exact source/API/static evidence to answer:

```text
PowerAttack:
- what native callback bookkeeping must marker ownership complete?

PierceAttack:
- what native callback bookkeeping must marker ownership complete?

SimpleWhirl:
- confirm separate OnAI_SimpleWhirl/action-6 adapter and bookkeeping policy

HackAttack:
- where is native action 14 collision activation owned?
- where/how is action 14 routed to the serialized FinishingAttack asset family?
- what is the narrowest way to route Hack to HackAttack assets while preserving native resolver semantics?

GetUpAttack:
- classify only whether inclusion is architecturally trivial or materially different
```

Known source/lifecycle caution:

```text
GetUpAttack can perform legitimate weapon offense before its later CombatMove.
```

Do not solve that with a GetUp-specific guessed execution identity.

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
finish the narrow Power/Pierce/SimpleWhirl/Hack/GetUp source classification
→ freeze exact adapter/bookkeeping/Hack-routing architecture with User
→ create one bounded Work implementation responsibility
→ validate new families one by one
```