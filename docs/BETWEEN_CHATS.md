# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-04

## Current bridge — SimpleWhirl StatePosition causal probe awaiting runtime test

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap. If the previous Chat failed or hit maximum context, use POP-11 before trusting stale `NEXT` wording.

CAM is the constitutional collaboration layer; `docs/README.md` is the highest Gothic-specific project charter beneath CAM. Do not modify CAM from Gothic 3 work.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Hack callback runtime identity                  CLOSED — EV-216
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl physical marker/source mechanics    PASS — EV-217 plus current evidence
```

Do not reopen C1 lifecycle/generation architecture, Power, Pierce, or the SimpleWhirl physical source mechanics without contradicting evidence.

Current semantic distinction remains:

```text
G3AB markers
= WHEN collision is offensive
+ WHICH equipped physical source set is offensive/rearmed

native/action-specific character-hit semantics
= which actor contacts are eligible to become character damage/effects for that action
```

EV-220 currently shows SimpleWhirl as substantially more target-directed than true PowerAttack under matched Power-derived Dual motion content while the intended physical source program succeeds in both cases. Strict selected-target-only is not proven.

---

## Temporary causal probe — IMPLEMENTED / SOURCE-REVIEW PASS

Published implementation:

```text
a48449fcd9e2514a6d1c1f9943eb04004a5778f3
Add temporary SimpleWhirl StatePosition causal probe
```

Parent / required pre-probe state:

```text
3067f4e7cf86d5702e2bd69ffb10507ed395c317
```

Changed file only:

```text
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
```

Exact temporary change in `GetMarkerOwnedStatePosition(...)`:

```text
AttackFamily_SimpleWhirl
StatePosition 1 -> 2
```

Independent Normal Chat review confirmed the remote diff contains only that one conceptual change. Power retains its existing Dual/non-Dual rule; Quick, Whirl, Pierce and Hack retain their previous values. No marker, source, hook, lifecycle, C1, diagnostic or Hack-routing behavior changed.

The remote branch head was verified at `a48449fcd9e2514a6d1c1f9943eb04004a5778f3`.

This is **temporary diagnostic causal scaffolding**, not a permanent SimpleWhirl semantic decision.

---

## Exact next responsibility — authoritative local build/runtime falsification

No build or runtime test has been performed for `a48449f...` yet.

When back at the authoritative home PC:

```text
sync docs/collision-source-evidence to a48449fcd9e2514a6d1c1f9943eb04004a5778f3
→ build the instrumented Script_FrameCollisionTest diagnostic twin
→ deploy using the normal one-live-twin rule
→ keep the established SimpleWhirl comparison fixture unchanged
→ run the StatePosition causal test
→ preserve the raw diagnostic artifact
→ return the runtime observation/log for interpretation
```

Keep unchanged during the causal comparison:

```text
Action 6 / SimpleWhirl
OnAI_SimpleWhirl
same Power-derived Dual motion fixture
same BOTH -> single -> OFF -> BOTH markers
same source activation/rearm behavior
same target/group setup
```

The diagnostic should confirm accepted SimpleWhirl markers now leave `StatePositionAfterMarker = 2`; that confirms the intended test variable was actually applied but does not by itself answer the actor-hit question.

Runtime interpretation:

```text
SimpleWhirl becomes Power-like in broad actor-hit eligibility
→ StatePosition participates in deeper native eligibility
→ investigate the legitimate semantic rule before any permanent normalization
→ do not immediately generalize to other families

SimpleWhirl remains substantially target-directed
→ StatePosition is likely bookkeeping/suppression only
→ revert the temporary probe
→ apply the charter's deliberate-scope decision guide
→ pursue only a bounded native eligibility trace if the result still makes that worthwhile/promising
→ otherwise close SimpleWhirl with physical-source marker control + documented native eligibility restriction
```

A documented native family restriction is a valid resolution. A deep trace is **not** automatically required if this cheap causal probe fails.

Do not move to Hack isolated marker/routing runtime validation until the SimpleWhirl result is interpreted enough to define the family/framework guarantee.
