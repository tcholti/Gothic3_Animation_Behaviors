# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-21

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Current state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Latest completed runtime evidence:
- **EV-355** — broad diagnostic production-candidate smoke PASS.
- **EV-356** — diagnostics-free behavior-twin broad functional smoke PASS.

Permanent raw8 source candidate:
`7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd`

Diagnostic DLL SHA256:
`D257DEA36BFF74BFBCF00D54BD36E08769D19DCA794E96CCA93AD48169D0023A`

Behavior-only DLL SHA256:
`14F1AFE65CBE78E75B73535E46A71E43BEA5CCC6E95BC58EFFF894EC2888B324`

Both twins built from the same source checkout and have now passed their respective smoke gates.

EV-356 behavior-only positive discriminators included:
- Hack route active;
- Troll Quick repeated/two-contact behavior active;
- 1H+torch authored RIGHT marker corrected the tested vanilla wrong-left-hand collision;
- dual-1H Power produced all three authored contacts where tested vanilla resolves only two.

These are pre-audit confidence gates, not substitutes for the later focused/full validation campaign.

## Active gate

Frozen formal audit:
`docs/work/active/COLLISION_FINAL_SOURCE_QUALITY_MODULARITY_AUDIT.md`

The audit is **read-only**:
- Work may inspect source/authority/evidence as bounded by the contract;
- Work must make no source or documentation edits;
- Work must not build;
- Work reports findings only;
- Normal Chat + User decide whether any cleanup is justified before full validation.

Required first step after this maintained state is pulled:
`python tools/knowledge/validate_knowledge_state.py`

Require exact:
`Knowledge-state validation PASS`

Then launch the read-only Work audit against the final maintained remote HEAD.

After audit:
- if no justified source cleanup exists, candidate may be frozen for focused/full validation;
- if cleanup is justified, Normal Chat freezes the smallest bounded implementation task, then rebuild + small re-smoke before full validation.

Do not begin the focused/full acceptance matrix before the audit/cleanup decision is closed.

`research/raw/` currently contains only `Keep.txt`.
