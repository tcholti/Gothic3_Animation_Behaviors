# Research Source Intake

**Status:** Research-source workflow  
**Date:** 2026-08-22

## Purpose

This directory preserves long source documents, chat logs, notes, and other material that may contain useful project knowledge without treating that material as current authority.

Canonical engineering state remains in `docs/`, current code, configuration, and verified external references.

## Workflow

1. Add new unprocessed source material under `research/raw/`.
2. Preserve the original file unchanged.
3. Compare its claims against current code, canonical documents, and newer evidence.
4. Promote only useful current findings into the appropriate canonical files.
5. Record superseded or uncertain claims at the correct evidence level when they remain relevant.
6. Move the processed original to `research/archive/`.
7. Update the index below.

Files under `research/archive/` are provenance/history and should not be read during ordinary project continuation unless a specific unresolved question requires them.

## Processing Index

| Archived source | Processed | Result | Canonical destinations |
|---|---|---|---|
| `archive/2026-08_pre_github_animation_behaviors_chat_log.txt` | 2026-08-22 | Useful conclusions were already preserved. Native action/phase semantics, raw-UseType normalization, normalized animation-family profiles, marker ownership, and separation of action identity from physical damage source remain current. The older suggestion that the same vocabulary could broadly serve collision has been refined: collision remains exact-motion marker-driven and physical source-explicit rather than an ordinary INI profile. No code or plan change required. | `docs/DESIGN.md`, `docs/ANIMATION_RULES.md`, `docs/EVIDENCE_LEDGER.md`, `docs/RESEARCH_MAP.md`, `config/G3AnimationBehaviors.ini` |
