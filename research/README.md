# Research Source Intake and Provenance Map

**Status:** Current research-layer usage map  
**Updated:** 2026-09-08

## Purpose

Define how non-authoritative source material and runtime/source artifacts move through `research/` without turning this directory into a competing evidence ledger, technical authority, or current-state history.

Canonical engineering meaning lives in `docs/`, current source/configuration, and verified external references. The research tree preserves source material and provenance needed to support or challenge those maintained conclusions.

---

## 1. Directory Roles

```text
research/raw/
= active intake
= unprocessed artifacts or artifacts deliberately retained for an active comparison

research/archive/
= processed durable provenance
= source artifacts whose reusable conclusions/disposition are already represented canonically

research/derived/
= deterministic retrieval/analysis aids
= never a replacement for canonical raw/archive source artifacts
```

`research/raw/Keep.txt` preserves the intake directory when no active artifact is present.

---

## 2. Evidence / Processing Workflow

Operational evidence closure is owned by POP-05/POP-06 in `docs/PROJECT_OPERATING_PROCEDURES.md`.

Normal runtime/source flow:

```text
freeze test / expected artifact
→ preserve produced source unchanged in research/raw
→ publish exact artifact
→ Normal Chat interprets against frozen question + User observation
→ promote reusable factual conclusion into canonical Evidence Ledger
→ update EVIDENCE_INDEX only when retrieval changes
→ perform smallest-owner technical/current-state maintenance if meaning changed
→ assign explicit artifact disposition
→ archive unchanged when no active comparison needs raw intake
```

Do not leave a completed investigation with its result existing only in Chat, a derived checkpoint, this README, or an index.

---

## 3. Canonical Processing / Retrieval Owners

Use these instead of maintaining a per-log historical table here:

| Need | Authority |
|---|---|
| exact factual conclusion / evidence status | `docs/EVIDENCE_INDEX.md` → canonical Evidence Ledger |
| evidence-ledger storage ranges | `docs/README.md` / `docs/KNOWLEDGE_REGISTRY.md` |
| deliberate raw/archive path move | `docs/EVIDENCE_PATH_MIGRATIONS.md` |
| evidence closure / archive procedure | POP-06 in `docs/PROJECT_OPERATING_PROCEDURES.md` |
| knowledge owner/update trigger after a result | `docs/KNOWLEDGE_MAINTENANCE.md` + `docs/KNOWLEDGE_REGISTRY.md` |
| large-log deterministic reduction | POP-07 + `tools/log_evidence/README.md` |
| old documentation wording / old processing-table detail | Git history |

The previous long per-artifact Processing Index is intentionally retired from the active file. Its historical rows remain recoverable in Git history, while current factual conclusions and provenance are routed by the canonical evidence system above.

This avoids creating another independently stale chronology that fresh Chats must read in addition to the Evidence Ledger and Evidence Index.

---

## 4. Current Intake State

At the 2026-09-07 human-Fist stable-subsystem checkpoint, the processed September 2–7 collision/Fist artifacts plus the old `ge3log10.log` crash artifact were moved unchanged to `research/archive/` after evidence closure.

Current expected active-intake baseline after that transaction:

```text
research/raw/Keep.txt
```

A future artifact belongs in raw only while it is genuinely unprocessed or intentionally active for comparison.

Migration details/provenance:

```text
docs/EVIDENCE_PATH_MIGRATIONS.md
```

---

## 5. Archive Interpretation

`research/archive/` is deep provenance, not dead material.

Open archived sources when:

- an EV wording needs exact verification;
- a current interpretation is challenged;
- a future responsibility needs a source fact not represented canonically;
- a contradiction requires reconstructing the original run/source material.

Do not read the archive as normal project chronology and do not treat archive age/path as evidence rank.

---

## 6. Derived Material

`research/derived/` may contain deterministic checkpoints, timelines, indexes or extracts for large source artifacts.

Requirements:

```text
derived package identifies canonical source
→ source hash/content identity remains recoverable
→ transformation/extraction is reproducible enough for verification
→ derived output is used for navigation/synthesis
→ exact disputed fact returns to canonical source
```

A hand-written summary must not replace the canonical Evidence Ledger or the underlying raw/archive artifact.

---

## 7. Maintenance Rule

Update this README only when the **research-layer workflow or retrieval role changes**.

Do not update it for every new log, every EV, every archive move, or every test result. Those belong to their actual owners.

If repeated use shows that a new research-layer responsibility is genuinely distinct, first check `docs/KNOWLEDGE_REGISTRY.md` before creating another document.
