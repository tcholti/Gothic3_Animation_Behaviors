# Archived Documentation

**Status:** Historical material — not current operational or technical authority

This directory preserves superseded documentation when its causal history, exact wording, or detailed chronology may still help future research.

> **Historical does not mean irrelevant. Archive material preserves rationale and recoverability without remaining in the normal active context surface.**

Do not load archived documents during ordinary continuation or bounded implementation unless the current question genuinely needs historical detail.

---

## 1. Collaboration / Continuity Archive

### `HANDOFF_legacy_2026-08-27.md`

Large self-contained continuation/history document from earlier project stages.

Superseded operationally by:

- `../SESSION_ENTRYPOINT.md` — current durable front door;
- `../BETWEEN_CHATS.md` — transient Chat/Work bridge;
- current design/evidence/reference authorities.

### `FROZEN_WORK_TASK_RULES_2026-08-27.md`

Earlier separate frozen-task contract.

Its durable safeguards were consolidated into:

- `../WORK_IMPLEMENTATION_PROTOCOL.md`.

### `WORK_COLLABORATION_EVOLUTION_2026-08-27.md`

Earlier empirical Work-session retrospective, including positive implementation examples and the B6 semantic-gap lesson.

Current operational lessons now live in the CAM collaboration framework plus the project-specific collaboration/Work protocol.

---

## 2. Technical Information-Architecture Snapshot

Directory:

`technical_2026-08-27/`

This is a **byte-preserved snapshot of active technical documents immediately before the 2026-08-27 information-architecture cleanup**.

Files include:

- `DESIGN_pre_ia.md`
- `COLLISION_LIFECYCLE_PLAN_pre_ia.md`
- `COLLISION_LOGGER_PLAN_pre_ia.md`
- `COLLISION_TEST_PLAN_pre_ia.md`
- `SOURCE_HOOK_GUIDE_pre_ia.md`
- `RESEARCH_MAP_pre_ia.md`
- `COLLISION_CLEANUP_CALLSITE_MAP_pre_ia.md`

Why they were preserved:

- active `DESIGN.md` contained large prototype histories in addition to architecture;
- lifecycle/logger/test plans contained stale “current/next” stages after Step B had advanced;
- `SOURCE_HOOK_GUIDE.md` mixed reusable symbol/API lookup with v0.x chronology;
- `RESEARCH_MAP.md` still described old prototype versions as current state;
- the cleanup call-site map contained an earlier open question that was later resolved by static identification.

The active documents were rewritten around distinct responsibilities and targeted retrieval. No technical history needed to be discarded because these exact pre-cleanup versions remain available here, while canonical evidence/raw logs remain separately preserved.

### Retrieval rule

Use the technical snapshot only when:

- an older implementation rationale was compressed out of an active design/reference file;
- exact v0.x chronology matters;
- a newer summary appears inconsistent with historical wording and needs audit;
- evidence exists but the surrounding experimental reasoning is needed.

For ordinary technical questions, prefer:

```text
../SESSION_ENTRYPOINT.md
→ ../EVIDENCE_INDEX.md or ../ANIMATION_INDEX.md
→ exact current authority / evidence entry
→ raw source/log if verification is needed
```

---

## 3. Archive Authority Rule

Archived documents never override:

1. current source/commits for implementation truth;
2. `SESSION_ENTRYPOINT.md` for current continuation;
3. current design/lifecycle/test authorities;
4. canonical evidence ledgers for evidence status/provenance;
5. current indexes for retrieval routing.

Git history additionally preserves earlier revisions of current documents beyond these explicit snapshots.
