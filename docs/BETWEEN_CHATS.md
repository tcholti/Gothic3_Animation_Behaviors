# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-19

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **equipped Sprint production promotion APPROVED; permanent extraction implementation next.** Phase 4 remains held.

Active Work contract:

`docs/work/active/COLLISION_EQUIPPED_SPRINT_PRODUCTION_PROMOTION.md`

Decision rationale:

`docs/decisions/ADR-0003-promote-equipped-sprint-as-permanent-behavior.md`

Closed causal investigation:

`docs/archive/investigations/COLLISION_EQUIPPED_SPRINT_GENERIC_CAUSAL_PROBE.md`

Accepted evidence:

```text
EV-315  factual equipped Sprint RIGHT handoff                PASS
EV-322  Action9 -> same-C1 Action2 RIGHT->OFF continuation  PASS
EV-323  BOTH with LEFT missing fail-closed rerun             PASS
EV-324  ordinary true-Power protected control               PASS
```

Promotion rule: do not compile the temporary `EquippedSprintProbe` into behavior. Extract the proven policy/state into permanent `EquippedSprintCollision.cpp/.h`, include it in the shared behavior sources, let EngineBridge remain hook transport, and keep generic RIGHT/LEFT/BOTH/OFF semantics in `FrameCollisionMarkers`.

The permanent owner must preserve exact Sprint-origin identity, allow only the proven same-C1 Action9 -> Action2 continuation, fail closed on missing required sources, never create Sprint origin from true Power, and remain mechanically independent of diagnostics.

After Work publishes, Normal Chat independently reviews before any build. Required acceptance then includes both behavior-only and diagnostic twins, the compact EV-322/323/324 controls, and a diagnostics-free behavior smoke.

Latest evidence = EV-324. `research/raw/` should contain only `Keep.txt`.

Use `COLLISION_REFERENCE.md` for current facts, `DESIGN.md` for intended architecture, and `EVIDENCE_INDEX.md` for provenance.
