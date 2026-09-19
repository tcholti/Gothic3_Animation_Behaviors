# Research Source Intake and Provenance Map

**Status:** Current research-layer usage map  
**Updated:** 2026-09-18

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

Do not use `research/raw/` as a project-history folder. Once an artifact is processed and no longer needed for an active comparison, POP-06 disposition applies and the unchanged source belongs in `research/archive/`.

---

## 2. Evidence / Processing Workflow

Operational evidence closure is owned by POP-05/POP-06 in `docs/PROJECT_OPERATING_PROCEDURES.md`.

Normal runtime/source flow:

```text
freeze test / expected artifact(s)
→ preserve produced source unchanged in research/raw
→ publish one test or small intentional batch
→ Normal Chat interprets EVERY uploaded artifact against frozen test + User observation
→ represent every completed test/run in canonical Evidence Ledger evidence
→ update EVIDENCE_INDEX only when retrieval changes
→ perform smallest-owner technical/current-state maintenance
→ assign explicit artifact disposition to every uploaded artifact
→ archive each processed artifact unchanged when no active comparison needs raw intake
→ verify research/raw + current-state pointers
→ only then begin the next runtime batch
```

Uploading two or three related logs together is normal. It changes only the publication unit, not the closure rule: the entire uploaded batch must be processed and cleaned before the next batch starts.

Do not leave a completed investigation with its result existing only in Chat, a derived checkpoint, this README, or an index.

---

## 3. Canonical Processing / Retrieval Owners

Use these instead of maintaining a per-log historical table here:

| Need | Authority |
|---|---|
| exact factual conclusion / evidence status | `docs/EVIDENCE_INDEX.md` → canonical Evidence Ledger |
| evidence-ledger storage ranges | `docs/EVIDENCE_INDEX.md` plus the ledger continuation header |
| deliberate raw/archive path move | `docs/EVIDENCE_PATH_MIGRATIONS.md` |
| evidence closure / archive procedure | POP-06 in `docs/PROJECT_OPERATING_PROCEDURES.md` |
| knowledge owner/update trigger after a result | `docs/KNOWLEDGE_MAINTENANCE.md` + `docs/KNOWLEDGE_REGISTRY.md` |
| large-log deterministic reduction | POP-07 + `tools/log_evidence/README.md` |
| old documentation wording / old processing-table detail | Git history |

The previous long per-artifact Processing Index is intentionally retired from the active file. Its historical rows remain recoverable in Git history, while current factual conclusions and provenance are routed by the canonical evidence system above.

This avoids creating another independently stale chronology that fresh Chats must read in addition to the Evidence Ledger and Evidence Index.

---

## 4. Current Intake State

Latest processed collision evidence checkpoint:

```text
EV-299 — Golem 1H regression PASS
EV-300 — Golem 1H+torch regression PASS
EV-301 — Golem dual-1H regression PASS
EV-302 — Golem 2H regression PASS
EV-303 — Golem Staff regression PASS
EV-304 — Golem human raw8 Fist single-marker/native-fallback PASS
EV-305 — Golem human raw8 Fist double-marker repeated-contact PASS
```

The first two standalone-regression batches have been processed and archived byte-identically. Current expected active-intake baseline is:

```text
research/raw/Keep.txt
```

That baseline has been verified again after closure of the EV-302–EV-305 batch.

A future artifact belongs in raw only while it is genuinely unprocessed or intentionally retained as an active comparison. After each uploaded test batch, POP-06 requires processed artifacts to be archived before the next batch is requested.

Migration details/provenance:

```text
docs/EVIDENCE_PATH_MIGRATIONS.md
```

For large archived logs, routine retrieval should begin with the canonical EV and committed `research/derived/` package when one exists. Small CORE logs may be read directly from archive. The archive is opened only when exact source verification is needed beyond maintained evidence.

---

## 5. Archive Interpretation

`research/archive/` is deep provenance, not dead material.

Open archived sources when:

- an EV wording needs exact verification;
- a current interpretation is challenged;
- a future responsibility needs a source fact not represented canonically;
- a contradiction requires reconstructing the original run/source material.

Do not read the archive as normal project chronology and do not treat archive age/path as evidence rank.

Historical ledger rows may still spell the raw intake path that was correct when the EV was written. Resolve deliberate storage moves through `docs/EVIDENCE_PATH_MIGRATIONS.md` rather than treating the old path as evidence loss.

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

For large logs, prefer the derived package for routine orientation and targeted retrieval. Do not scan a directory of full archived logs merely to reconstruct current state.

---

## 7. Maintenance Rule

Update this README only when the **research-layer workflow or retrieval role changes**.

Do not update it for every new log, every EV, every archive move, or every test result. Those belong to their actual owners.

If repeated use shows that a new research-layer responsibility is genuinely distinct, first check `docs/KNOWLEDGE_REGISTRY.md` before creating another document.
