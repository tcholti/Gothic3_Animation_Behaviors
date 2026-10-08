# Research Source Intake and Provenance Map

**Status:** Current research-layer usage map  
**Updated:** 2026-10-08

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

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
= new/open deterministic retrieval/analysis packages (POP-07 output)
= never a replacement for canonical raw/archive source artifacts

research/archive/derived/
= completed derived packages preserved unchanged for targeted cold retrieval
= retrieval aids, distinct from the canonical originals in research/archive/
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
→ represent every completed test/run concisely in the single active Evidence Ledger
→ promote any changed reusable fact to current reference/architecture
→ update EVIDENCE_INDEX only when retrieval changes
→ perform smallest-owner current-state maintenance
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
| current established collision conclusion | `docs/COLLISION_REFERENCE.md` |
| exact proof / evidence status | `docs/EVIDENCE_INDEX.md` → exact current/archived Evidence Ledger |
| evidence-ledger storage ranges | `docs/EVIDENCE_INDEX.md`; exactly one active ledger remains under `docs/`, closed volumes under `docs/archive/evidence/` |
| deliberate raw/derived/archive path move | [EVIDENCE_PATH_MIGRATIONS](../docs/EVIDENCE_PATH_MIGRATIONS.md) |
| evidence closure / archive procedure | POP-06 in `docs/PROJECT_OPERATING_PROCEDURES.md` |
| knowledge owner/update trigger after a result | `docs/KNOWLEDGE_MAINTENANCE.md` + `docs/KNOWLEDGE_REGISTRY.md` |
| large-log deterministic reduction | POP-07 + `tools/log_evidence/README.md` |
| old documentation wording / old processing-table detail | Git history |

The previous long per-artifact Processing Index is intentionally retired from the active file. Its historical rows remain recoverable in Git history, while current factual conclusions and provenance are routed by the canonical evidence system above.

This avoids creating another independently stale chronology that fresh Chats must read in addition to the Evidence Ledger and Evidence Index.

---

## 4. Current Intake Routing

This README does not maintain a per-run current-intake history.

```text
current raw state
-> inspect the actual research/raw tree
-> retrieve exact disposition/current evidence through the active Evidence Ledger / EVIDENCE_INDEX
-> retrieve the immediate project gate through SESSION_ENTRYPOINT
-> apply POP-06 archive/disposition mechanics only after explicit evidence closure
```

An artifact remains in raw while unprocessed, intentionally retained for an active comparison, or explicitly KEEP RAW pending provenance/disposition reconciliation. Do not infer archive permission merely from a closed mechanism conclusion. Storage notes in `docs/EVIDENCE_INDEX.md` route explicit preservation states; deliberate later moves are traced by `docs/EVIDENCE_PATH_MIGRATIONS.md`.

For large archived logs, begin with the canonical EV and, when deeper verification is needed, the committed derived package. New/open packages use `research/derived/`; the approved completed set uses [`research/archive/derived/`](archive/derived/) with unchanged names/layout. [EVIDENCE_PATH_MIGRATIONS](../docs/EVIDENCE_PATH_MIGRATIONS.md#2026-10-08--completed-derived-evidence-archival) resolves former paths. Small CORE logs may be read directly from archive. Open canonical source only for a concrete verification need beyond the maintained evidence and package.

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

`research/derived/` holds new/open generated packages; `research/archive/derived/` preserves the completed set's manifests, timelines, indexes, extracts and source mirrors. Closed manual analysis checkpoints belong in `docs/archive/investigations/`, with their old paths recoverable through the migration map.

Requirements:

```text
derived package identifies canonical source
→ source hash/content identity remains recoverable
→ transformation/extraction is reproducible enough for verification
→ derived output is used for navigation/synthesis
→ exact disputed fact returns to canonical source
```

A derived or ad-hoc summary must not replace the EV proof record or the underlying raw/archive artifact. Current factual reference documents are a separate maintained projection of established knowledge and must point back to evidence rather than replace it.

For large logs, prefer the derived package for routine orientation and targeted retrieval. Do not scan a directory of full archived logs merely to reconstruct current state.

---

## 7. Maintenance Rule

Update this README only when the **research-layer workflow or retrieval role changes**.

Do not update it for every new log, every EV, every archive move, or every test result. Those belong to their actual owners.

If repeated use shows that a new research-layer responsibility is genuinely distinct, first check `docs/KNOWLEDGE_REGISTRY.md` before creating another document.
