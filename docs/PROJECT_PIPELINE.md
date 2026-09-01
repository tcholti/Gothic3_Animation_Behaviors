# Gothic 3 Project Pipeline Baseline

**Project:** Gothic3_Animation_Behaviors  
**Status:** Active operating-convention authority  
**Version:** 1.2  
**Updated:** 2026-09-01

## Purpose

Preserve recurring project conventions that must remain stable across Chat migrations, tools, research stages, and implementation cycles unless we deliberately decide to change them.

This file exists because small arbitrary changes to log names, version labels, test numbering, and similar conventions can accumulate confusion even when each local change appears harmless.

This is **not** a rigid linear project plan. Gothic 3 research and engineering remain adaptive and evidence-driven.

> **Adaptive technical work should happen inside a stable operating grammar.**

---

## 1. Convention Stability Rule

Once a convention below is accepted:

```text
use it across normal work and new Chats
→ do not change it from preference or fresh-context improvisation
→ if a real reason for change appears
→ identify the problem with the current convention
→ decide the replacement deliberately
→ define the effective boundary / migration treatment when needed
→ update this authority and affected procedure/routes
→ continue with the new convention
```

A Chat migration is never, by itself, a reason to rename, renumber, restart, or reinterpret a project convention.

Do not retroactively rename or renumber historical evidence merely to make old material cosmetically match the current convention. Preserve provenance unless a deliberate migration has a stronger benefit.

---

## 2. Branch and Project-State Meanings

Current branch model:

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active development/research branch with newest collision implementation and newest research
```

Do not reinterpret `main` as the newest working state merely because it is the default branch.

Unfinished collision implementation stays on the active branch until a deliberate stable-integration decision.

Stable documentation/knowledge may be promoted separately when it has been reviewed and is suitable for the stable baseline.

---

## 3. Technical Research / Test Gate IDs

Current research uses **hierarchical gate/probe identifiers**, not a sequence that restarts per Chat.

Examples already established:

```text
B1 ... B6 ...
C1
C1-O1
C1-O2
```

Rules:

1. An existing gate/probe ID keeps the same meaning permanently.
2. Never restart numbering because a new Chat/session begins.
3. A narrower probe derived from an existing gate should extend the owning gate ID when practical, for example `C1-O1`, `C1-O2`.
4. Repeating the same frozen test does not require inventing a new gate ID. Distinguish repetitions/configurations in the artifact filename and test description.
5. The owning technical plan/current-state authority defines what each gate means; this file owns the continuity of the identifier scheme, not the technical semantics.
6. If a future subsystem needs a different ID family, define it deliberately before use rather than improvising it midstream.

---

## 4. Evidence IDs

Canonical evidence uses the existing global monotonic form:

```text
EV-001
EV-002
...
EV-158
...
```

Rules:

- continue the global EV sequence across ledger file splits;
- never restart EV numbering for a new Chat, branch phase, subsystem, or continuation file;
- never reuse an EV ID for a different claim;
- corrected/superseded evidence keeps its original ID and status/history rather than being silently replaced by a new meaning;
- ledger splitting is storage/retrieval structure, not a new evidence namespace.

Current storage boundaries:

```text
EVIDENCE_LEDGER.md                EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md     EV-199 onward
```

The ledger files own the claims themselves.

---

## 5. Procedure IDs

Project-local operating procedures use:

```text
POP-01
POP-02
...
```

Existing POP identifiers keep their meanings.

Add a new POP number only for a genuinely distinct recurring operation. Do not renumber existing procedures when inserting, removing, or rewriting one.

`PROJECT_OPERATING_PROCEDURES.md` owns procedure content.

---

## 6. Raw Runtime Log Naming

For controlled runtime evidence, the established pattern is:

```text
research/raw/YYYY-MM-DD_<gate-or-step>_<actor-or-config>_<question>.log
```

Examples already consistent with the current project:

```text
2026-08-28_c1_shadow_core_lifecycle_matrix.log
2026-08-29_c1o1_outer_scriptfunction_identity_probe.log
```

Rules:

1. Normal Chat freezes **one exact raw filename before the run** whenever practical.
2. The gate/step token should use a compact filesystem form derived from the established gate ID. Current convention is lowercase and compact; for example `C1-O1` → `c1o1`.
3. Keep the filename descriptive enough to distinguish the actor/configuration/question without turning it into a sentence.
4. Once the filename is frozen as part of the test contract, keep it unless there is a concrete reason to change it.
5. If a test runs after midnight or later than planned, preserve the frozen filename unless the date itself would materially misidentify the evidence.
6. Do not rename historical raw logs merely to normalize older naming styles.
7. Canonical raw evidence stays unchanged in `research/raw/` until normal processing/archival rules apply.

The exact test-freezing sequence is POP-05 in `PROJECT_OPERATING_PROCEDURES.md`.

---

## 7. Derived Runtime Analysis Artifact Naming

Derived retrieval aids should preserve the raw artifact stem when practical.

Preferred suffixes already used by the project:

```text
_connector_extract.txt
_analysis_extract.txt
_summary.txt
```

Example:

```text
2026-08-29_c1o1_outer_scriptfunction_identity_probe.log
→ 2026-08-29_c1o1_outer_scriptfunction_identity_probe_connector_extract.txt
```

Derived files must identify their source raw/archive path and source SHA256/other provenance as defined by POP-07.

Derived retrieval/analysis material belongs under `research/derived/`; it does not become canonical raw evidence merely because it is committed.

The unchanged source raw/archive artifact remains canonical provenance.

---

## 8. Prototype / Build Identity and Versioning

The current collision research architecture has two mutually exclusive runtime twins built from the same behavior source set:

```text
Script_FrameCollisionBehaviorTest
= diagnostics-free collision behavior build

Script_FrameCollisionTest
= same collision behavior + diagnostic instrumentation
```

These are **research identities**, not the final public product names. Do not rename them merely for cosmetic cleanup while the current research/validation architecture is still active.

For controlled research builds, the primary identity is:

```text
exact Git commit
+ exact selected product/target name
+ exact deployed DLL identity/hash
+ exact startup/banner identity when that product emits one
```

For diagnostic runs, also tie the build to the active gate/probe and the expected diagnostic startup/banner label. For diagnostics-free behavior-only smoke, the absence of a diagnostic banner is intentional; product name + commit + deployed DLL hash + agreed load/functional observation are the applicable identity surface.

Historical decimal prototype labels such as `v0.xx` remain valid historical references where they already exist, but they must not be casually incremented or restarted as a substitute for the gate/commit/product identity.

From the current C1-era research onward:

- use the active gate/probe plus commit SHA and selected product identity as the authoritative diagnostic research-build identity;
- change diagnostic startup/banner text when the tested diagnostic meaning changes enough that confusing builds would invalidate a test;
- for behavior-only verification, preserve exact target/DLL/hash identity even though diagnostic strings are absent by design;
- do not create a new decimal prototype version merely because another Chat edited the code;
- do not let prototype/research numbering or temporary target names silently define the eventual public `Script_G3AnimationBehaviors` release version.

The eventual production integration target remains `Script_G3AnimationBehaviors`; collision migration into that target is a later engineering responsibility, not part of current prototype naming cleanup.

Public/stable release versioning should be decided deliberately at the stable-integration/release stage.

---

## 9. Document Versioning

Use explicit document versions only where versioned procedure/policy identity is useful.

Current rule:

```text
procedure / policy / pipeline authority
→ explicit Version when meaningful
→ increment for substantive contract/procedure/convention change

current-state / evidence / living technical plan
→ current content + Updated/date/status as appropriate
→ do not invent a new version number for every edit
```

A typo or citation correction does not automatically require a semantic version bump.

Git history remains the exact revision history.

---

## 10. Engine-Facing Validation Pipeline

The established broad validation sequence is:

```text
design/evidence question frozen
→ bounded implementation when needed
→ implementation commit/publish
→ independent Normal Chat source review
→ User/local branch synchronization
→ build only
→ deploy exact built DLL
→ verify single live DLL + SHA match
→ startup/load verification appropriate to that product
→ freeze exact runtime matrix + exact raw filename when diagnostic evidence is expected
→ User runs test
→ raw log copied unchanged into research/raw when the product emits evidence
→ raw artifact commit/push
→ Normal Chat analyzes committed evidence
→ derived extract/package only if retrieval requires it
→ knowledge-maintenance transaction
```

For diagnostics-free behavior-only smoke, the raw-log stages are omitted by design; load/exit and functional observation are the applicable evidence surface.

Do not collapse gates merely because another Chat prefers fewer steps when the separation protects causal certainty.

Detailed commands and stop/failure branches belong to `PROJECT_OPERATING_PROCEDURES.md`.

---

## 11. Evidence Artifact Flow

Current project evidence flow:

```text
controlled runtime/source investigation
→ research/raw/ for active canonical intake
→ commit/publish unchanged artifact
→ Normal Chat interpretation
→ canonical EV/result update
→ EVIDENCE_INDEX route only when retrieval changes
→ research/archive/ when the unchanged source artifact is processed and no longer active
→ research/derived/ only for deterministic retrieval/analysis aids when needed
```

The three layers are distinct:

```text
research/raw/
= active/unprocessed or intentionally still-comparative canonical evidence

research/archive/
= processed durable source/runtime provenance, preserved unchanged

research/derived/
= deterministic non-canonical retrieval/analysis material tied back to canonical provenance
```

Raw/source provenance, interpreted evidence, and derived retrieval aids must remain distinguishable.

---

## 12. Convention Change Control

A material convention change should record, proportionately:

- what convention changed;
- why the previous convention was insufficient;
- the new convention;
- the effective boundary (date, gate, commit, version, or other clear transition);
- whether old artifacts remain as-is or require migration;
- which procedures/indexes/entrypoint routes are affected.

Prefer forward continuity over cosmetic rewriting of history.

A convention change discovered during ordinary technical work should update this file only when the convention itself changes; ordinary use should not trigger edits here.

---

## 13. Fresh-Context Continuity Contract

A fresh Chat does not need to read this entire file on every start.

`SESSION_ENTRYPOINT.md` should route here when the next responsibility touches convention-sensitive work such as:

- freezing/naming a test or log;
- assigning a new gate/probe ID;
- assigning an evidence/procedure ID;
- changing prototype/build/version identity;
- changing branch/state meaning;
- changing validation/artifact flow.

When such a convention matters, retrieve the relevant section and **preserve the established convention instead of inventing a new one**.

---

## Core Rule

> **Do not let Chat migration silently change the project's identity grammar. Tests, evidence, logs, versions, procedures, branches, products, and validation stages keep their established meanings until we deliberately change them for a reason.**
