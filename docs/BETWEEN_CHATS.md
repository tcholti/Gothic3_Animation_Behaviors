# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-21

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Current state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Latest completed runtime evidence: **EV-355 — broad production-candidate diagnostic smoke PASS**.

Permanent raw8 architecture:
`docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`

Current production source candidate:
`7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd`

Tested checkout before runtime smoke:
`95e8a24800dae778166788de36a31818933e3ff1`
(all commits after the source candidate were documentation-only).

Diagnostic DLL SHA256:
`D257DEA36BFF74BFBCF00D54BD36E08769D19DCA794E96CCA93AD48169D0023A`

Independent/static gates:
- permanent raw8 behavior/state-machine promotion: PASS;
- diagnostics-only correction: PASS;
- both twins built from same checkout: PASS;
- diagnostic POP-03 deploy/hash/sole-live: PASS;
- diagnostic POP-04 startup/hooks/clean unload: PASS;
- broad diagnostic smoke: PASS — EV-355.

EV-355 covered:
- marked Sabretooth raw8 + transformed-player symmetry;
- unmarked Wolf native fallback + transformed-player symmetry;
- marked Wolf raw8 + transformed-player symmetry;
- Troll/raw55 Normal/Quick/Power/Sprint coexistence + player marked weapon routes;
- broad marked player weapon coverage against Golem;
- previously untested T-Rex/Snorting-monster target fixture, with its own raw8 remaining unmarked/native and player 1H+shield markers healthy.

Important provenance note:
`2026-09-21_raw8prod_smoke_Troll_marked_single_fist.log` contains the Golem fixture despite its filename. Preserve the filename; the EV-355 record identifies the actual content.

## Next gate

Run a **minimal diagnostics-free behavior-twin smoke** from the already-built same-source binary. No diagnostic log is expected.

If behavior smoke passes:
1. freeze a bounded **read-only** final code-quality/modularity audit for Work;
2. Work reports findings only — no edits/refactor during the audit;
3. Normal Chat decides which, if any, cleanup is justified;
4. any source change requires rebuild + small re-smoke;
5. once source is frozen, run focused permanent raw8 acceptance and then the remaining full collision regression.

Do not begin the full acceptance matrix before the audit/cleanup decision is closed.

`research/raw/` should contain only `Keep.txt` after EV-355 archival.
