# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **Phase 4 broad regression PAUSED at raw8 FIST authoring-semantics review through EV-346.**

No active Work implementation contract.

Current diagnostic test product remains:

```text
Script_FrameCollisionTest.dll
SHA256 DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A
```

Design-discovery evidence:
- Gargoyle attacks in all four runs were factual Action2 / POWER with RIGHT Fist / UseType8; no Action9/Sprint was observed.
- native/no-marker: 7/7 attacks damaged;
- approximate frame-3 FIST: 10 accepted markers, 5/10 damage;
- frame-1 FIST: 4 accepted markers, 0/4 damage;
- frame-6 FIST: 8 accepted markers, 8/8 damage;
- frame-6 consumed at real native timing (`SyntheticApplied=0 / NATIVE_TIMING`);
- ownership, marker acceptance, finalization and diagnostics remained clean in every run.

Current interpretation:
- existing production raw8 behavior is functioning according to its frozen contract;
- each FIST is currently one native opportunity/pulse, not a persistent contact window;
- early synthetic timing can consume that opportunity before a moving body reaches the target;
- this is a material author-facing semantics question, not a Gargoyle species rule or simple regression defect.

Active review:
`docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`

Decision required before continuing broad Phase 4:
1. retain/document one-shot pulse semantics; or
2. choose persistent-window semantics in principle, then research the smallest native mechanism needed to keep an authored opportunity alive after an unsuccessful early contact attempt.

Non-negotiables for any redesign:
- unmarked raw8 remains native;
- factual source/UseType, never species/name;
- native target/contact/damage remains Gothic-owned;
- no direct/custom damage;
- no pre-first-marker leak;
- exact C1/source/animation identity and interruption safety;
- raw55/equipped behavior unchanged.

`research/raw/` should contain only `Keep.txt`.
