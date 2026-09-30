# Repository Health and Authority Audit Result

**Status:** ACTIVE — WORK RESULT PENDING NORMAL CHAT REVIEW

## 1. POP-10 preflight

Preflight completed before substantive evaluation on 2026-09-30. This is the frozen preservation-biased repository-health audit, not a cleanup or implementation task.

Governing hierarchy: CAM constitutional collaboration layer → `docs/README.md` §0 project charter → parallel specialist current authorities/references → conventions/procedures/bounded active tasks → evidence/provenance → archive/history. Root `README.md` is the discoverable front door, not the charter. Recency, size and similar wording do not determine authority. Evidence decides factual disputes; it does not silently decide product intent.

| Major target class | Intended use / owner | Review criteria |
|---|---|---|
| Startup and current state | Root README owns first hop; SESSION_ENTRYPOINT owns gate; BETWEEN_CHATS owns transient handoff | Correct branch and immediate responsibility; small pointers; recovery route discoverable |
| Project intent and collaboration | docs/README charter; COLLABORATION_RULES implements CAM locally | Preserve purpose, scope, user decisions and participant allocation; no CAM change |
| Architecture and technical references | DESIGN; release architecture; collision lifecycle/raw8/raw55/diagnostics/test authorities; SOURCE_HOOK_GUIDE and animation references | Compare within delegated responsibility; distinguish intended architecture, source facts and acceptance state |
| Conventions, procedures and lifecycle | PROJECT_PIPELINE; POPs; WORK_IMPLEMENTATION_PROTOCOL; FEATURE_DEVELOPMENT_METHOD; KNOWLEDGE_REGISTRY/MAINTENANCE | Stable ownership and triggers; canonical sequences; safe publication and preservation |
| Active work | Frozen audit and Speed contracts under docs/work/active | Unresolved responsibility vs implemented but awaiting acceptance; promote facts before any archival proposal |
| Evidence and provenance | EVIDENCE_INDEX, active ledger, archived ledgers, migrations, research artifacts | Range integrity, traceability, qualified conclusions, intact sources; bounded retrieval |
| Decisions and history | Accepted ADRs, archived investigations | Preserve rationale and unique proof; historical duplication is legitimate |
| Implementation and products | Production src, standalone diagnostics, root/target CMake, tools | Static agreement with frozen semantics and release/diagnostic separation; no runtime claim from source alone |

Scope: all eight areas A–H of the frozen task, including startup, authority health, Speed/Raise/collision, evidence, every active work item, tooling shape, reusable engine knowledge and context retrieval. Preserve configurable/native fallback, compatibility, diagnostics-free production, independent review, deep reusable Gothic knowledge and provenance. This audit cannot redefine charter/CAM, accepted semantics, architecture, source, build products, evidence or lifecycle. Only this result file may change. Any uncertain preservation classification remains **KEEP / NEEDS NORMAL CHAT REVIEW**. Recommendations are proposals for Normal Chat, not accepted corrections.

## 2. Exact audited repository/branch/HEAD

- Repository: `https://github.com/tcholti/Gothic3_Animation_Behaviors`
- Branch: `development`; required and observed remote HEAD: `85badb35c33e87743b3b6bfcab9999a0597d0295`.
- Read-only `git ls-remote` confirmed exact equality before evaluation; local checkout HEAD equals that SHA and began clean.
- No submodules initialized; no build, deployment or runtime execution authorized or attempted.

## 3. Knowledge-state validation result

Canonical command: `python tools/knowledge/validate_knowledge_state.py`.

Exact output:

```text
Knowledge-state validation FAILED:
  ERROR: active temporary document lacks '**Status:** ACTIVE': docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md
```

The script returns exit code **1**. The failing header exists in the audited commit; it reads `**Status:** SOURCE IMPLEMENTED / STATIC REVIEW PASS / LOCAL BUILD PASS / CALIBRATION SUB-GATE ACTIVE`. The new result's required ACTIVE header does not cause this failure. No validator or existing file was changed. POP-12 makes this a documentation-state stop condition for ordinary continuation. The frozen audit specifically authorizes diagnosis/reporting of failures, so read-only assessment and publication of this result continue; calibration, new Work and runtime progression remain gated.

## 4. Executive summary

The repository has a coherent authority topology and preserves substantial reusable engine knowledge. The canonical startup route correctly reaches the audit on development, with main frozen, collision closed, broad Speed calibration paused and Raise deferred. Current production Speed source agrees with DESIGN/ADR-0008/ADR-0009. No production behavior correction is established by this audit.

There is **one BLOCKER**, the pre-existing validator failure, and **two HIGH findings**, concerning stale raw8 transport semantics and incomplete canonical runtime product exclusion. Several MEDIUM findings concern stale configuration authority, supersession visibility, collision progress statements and intake lifecycle. These are specific discrepancies, not grounds for broad cleanup. No deletion or consolidation is recommended. Both Speed tasks remain genuinely unresolved; no pre-existing active task is ready to archive now.

Evidence numbering and derived provenance are structurally healthy: 396 distinct EV definitions, no gaps or duplicates, exactly one current ledger, and 27/27 derived-package manifests matching their preserved canonical source hashes. This is not a revalidation of every runtime interpretation. The 5,991-name inventory and historical investigations must be retained.

Normal Chat should independently verify the findings, restore the documentation validation gate and resolve the high-risk procedural/reference drift before ordinary continuation. Work has implemented **none** of these proposals.

## 5. Findings table

Severity follows the frozen meanings: BLOCKER unsafe ordinary continuation; HIGH material authority/evidence/source contradiction; MEDIUM meaningful stale routing/ownership/lifecycle; LOW bounded retrieval/hygiene; INFO healthy/no-action context. Confidence describes the static finding, not runtime certification.

| ID | Severity | Target(s) | Target role / owner | Finding | Evidence / reason | Smallest proposed correction | Preservation risk | Confidence |
|---|---|---|---|---|---|---|---|---|
| RH-01 | BLOCKER | Expanded-Speed active task, header | Unresolved implementation/acceptance contract; maintenance owns ACTIVE convention | Structural validation failure | Exact validator output in §3; task remains active despite implemented source | Normal Chat adds required ACTIVE prefix while retaining all source/build/calibration qualifiers; rerun unchanged validator | Low if qualifiers preserved; do not pretend acceptance is complete or archive task | High |
| RH-02 | HIGH | SOURCE_HOOK_GUIDE §4; ANIMATION_RULES §10 | Current engine transport lookup / authoring projection; permanent policy owner is raw8 architecture | Current lookup still describes one-shot timing transport | Guide says matching comparison receives forced timing then “consume once”; source ApplyTimingPermission retains timing while pending. Rules omit native-miss persistence and use “successful” opportunity closure wording | Update only current projections to persistent timing, exact contact-entry consumption and miss rearm; point to raw8 architecture §§6–8 and EV-346–EV-364 | Medium: preserve exact RVAs, negative virtual-callback evidence and no-clock-mutation rule; do not change behavior or erase earlier evidence | High for guide contradiction; medium for authoring wording impact |
| RH-03 | HIGH | POP-02/03/04; root README operations route | Canonical build/deploy/startup procedure | Product exclusion/checks lag production integration | POP-03 blocks remove only the opposite FrameCollision twin and enumerate Script_FrameCollision*. They can print PASS while G3AB production remains live. Root README directs actual validation to these exact blocks; source proves production and twins overlap hooks | Extend smallest owning procedures with exact product selection and physically excluded conflicting DLL set, including production and applicable Speed probes; retain target-specific hash/startup checks | Medium: do not replace proven twin procedures with an unreviewed generic script; preserve separate native/NB fixture requirements | High |
| RH-04 | MEDIUM | src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini comments | Shipped configuration guidance; DESIGN + native calibration facts own semantics | Stale Sprint and reference-base guidance | Comments say Sprint transport unproven/unsupported and reference is native/compatible B. ADR-0009 and current source apply Power timing to Sprint; DESIGN/EV-396 require native B | Correct comments to Power inheritance and native-only reference semantics; qualify examples by actually established route coverage | Low if limited to guidance; do not invent unmeasured B values or tune profiles during maintenance | High |
| RH-05 | MEDIUM | config/G3AnimationBehaviors.ini | Older conceptual template claiming canonical working authority | Competing current configuration surface | Header says CANONICAL WORKING CONFIGURATION TEMPLATE; old sections/Speed/RaiseSpeed/HitSpeed keys are ignored by current parser, which accepts Profile.* and grouped prefixed keys | Mark existing template explicitly historical/provisional and route to current source INI + DESIGN + ADR-0008; preserve old examples/rationale | Medium if old design notes removed; low for role label/route only. KEEP file until Normal Chat verifies any later archival | High |
| RH-06 | MEDIUM | ADR-0005/0006/0007/0008 status/forward routing | Decision rationale, not competing current architecture | Partial supersession is only discoverable from newer records | ADR-0007 still Accepted and states ActionProfile schema/ReferenceRaiseBaseSpeed. ADR-0008 explicitly supersedes those portions; ADR-0009 supersedes ADR-0008 Sprint deferral. Earlier ADRs retain historical Normal/Quick scope | Add bounded partial-supersession/qualification metadata and forward routes to old records; preserve original decisions and still-valid constraints | Medium: do not mark entire ADR-0006 obsolete or rewrite history; sequencing/config principles remain valid | High |
| RH-07 | MEDIUM | COLLISION_REFERENCE §§5/10; COLLISION_LIFECYCLE §10; raw55 architecture §9 | Current collision facts/lifecycle/raw55 architecture | Stale closure/progress projections | Reference says migration CURRENT/integration PENDING; lifecycle says raw8 implementation/acceptance pending; raw55 says migration CURRENT. EV-390, DESIGN §7 and test plan close integration; raw8 §14 closes all ten focused requirements | Replace only stale status sentences with closed checkpoint/route to test plan and session; preserve behavior invariants, proof landmarks and historical hashes | Low for status correction; high if acceptance provenance is mistaken for removable duplication | High |
| RH-08 | MEDIUM | research/README §4 | Research-layer usage map; current intake belongs to evidence/current state | Maintained map contains stale intake authority | Says latest EV-299–EV-308 and expected raw baseline Keep.txt; current raw has four logs, including explicitly retained EV-396 baseline. Its §7 says no per-log history/current processing table | Remove current-state responsibility from this map by replacing stale snapshot with canonical intake/disposition routes; preserve workflow and historical proof elsewhere | Low if surviving owners EVIDENCE_INDEX/ledger/session remain explicit; no evidence edit | High |
| RH-09 | MEDIUM | Three research/raw Sprint-probe logs | Runtime provenance; POP-06/maintenance owns disposition | Closed-probe sources lack explicit current intake reason; one source under-routed | Archived Sprint result closes probe and names Goblin + mixed log. Separate troll.log (commit 76f16c27439464f01e6a9957b64f3c1dfcd1c6e0) has five 1.0 observations but no exact docs path route found. No current authority states why all three remain active intake | KEEP / NEEDS NORMAL CHAT REVIEW: reconcile each artifact's fixture/provenance/disposition; archive unchanged only after facts and unique provenance have durable routes, or record genuine active comparison reason | High if treated as redundant: separate native/control provenance may be unique; log alone does not prove environment. See §7 | High for missing explicit disposition/route; medium for closability |
| RH-10 | LOW | EVIDENCE_INDEX §4; COLLISION_TEST_PLAN §7; release architecture §9 | Evidence routing, validation posture, product architecture | Residual status language can compete with live pointer | Index labels broad calibration “Current project gate” without audit pause; test plan labels config foundation current; release architecture says ancestor “is becoming” after integration | Prefer session route for immediate gate; qualify historical implementation landmarks. Do not update task-local NEXT on every temporary pause | Low; preserve meaningful dependency sequence | High |
| RH-11 | LOW | research/derived/README.md | Derived-artifact navigation | Broken plain-text procedure route outside validator coverage | Names docs/LARGE_LOG_EVIDENCE_PROCEDURE.md; no such tracked file exists. POP-07 + tools/log_evidence/README own current route | Replace obsolete route with existing POP-07 and Prepare-Log workflow; retain advanced generator route for advanced use | Low; derived packages/source hashes unaffected | High |
| RH-12 | LOW | SOURCE_HOOK_GUIDE §3A; calibration current owners | Reusable engine/reference knowledge | EV-396 calibration projection is incomplete outside task/evidence/current pointers | Guide already records native Troll Power/Sprint Hit but lacks compact qualified Hero None+1H and Troll Normal/Quick/Power Raise results and EV-396 route; full new values currently live in task/ledger/session | Add small evidence-bounded native control table to existing guide, including requested phase/raw-loadout limits; reference EV-396 and mark broad catalogue incomplete | Medium if generalized to untested routes; low if exact tested scope preserved | High |
| RH-13 | LOW | Charter subsystem orientation → EVIDENCE_INDEX | Retrieval map | Older Raise proof lacks fast topic route | Charter asks for Raise route in index; index only has later Sprint Raise EV-396 topic. Archived EV-001/002 and early Raise prototype evidence remain preserved | Add targeted early Raise-mechanism route after verifying exact EVs; keep Raise paused | Low; do not turn existence/old fixture into generic production acceptance | High for route gap; medium for final EV selection |
| RH-14 | INFO | Root README; SESSION_ENTRYPOINT; BETWEEN_CHATS; registry | Startup and continuity owners | Healthy canonical entry and parallel authority topology | All identify development active/main frozen/historical collision branch; session and handoff route audit and preserve recovery lock | No action; retain first-hop vs charter vs specialist distinctions | High if flattened/consolidated by similarity | High |
| RH-15 | INFO | Production/probe source and CMake | Implementation/product boundaries | Static Speed/collision agreement; inactive prototype Raise source is preserved safely | 15 production Hit sites; probe adds only 47D51; seven mappings/settings; no production entry hook; source collision parity; Raise/SharedConfig excluded | No behavior/source/build change; label old source historical in existing lookup only if retrieval needs it | High if “orphan” code removed before unique mechanism proof inventoried | High within static scope |
| RH-16 | INFO | Ledgers, derived packages, inventories, archives, specialist references | Proof history / reusable engine memory | Healthy historical duplication and preservation | 396 unique EV definitions; one active ledger; 27 hashes match; 5,991 distinct names. Responsibilities differ across reference/lifecycle/diagnostics/cleanup/catalog | KEEP; no deletion/consolidation; retrieve through indexes | Very high for proof/inventory loss; detail and age are not redundancy tests | High for measured structural facts |
| RH-17 | INFO | POPs 52,217 bytes; charter 26,603; guide/design/reference families | Rightful specialist/procedural detail | Context-size concern is addressed by retrieval model, not evidence removal | Named POP triggers/sections; current pointers 3,221/2,180 bytes; active ledger 26,437 bytes. Cold archive/provenance is most repository volume | Keep bounded section retrieval; consider scripts only if repeated friction justifies separately reviewed work | Medium/high if procedural safeguards or future-reusable facts compacted indiscriminately | High |

RH-02 and RH-03 are current-document/source/procedure mismatches. They do not establish a new runtime defect. RH-06 is a forward-routing problem in preserved history, not evidence that original ADR wording should be rewritten. No two permanent specialist authorities were demonstrated to own the same responsibility redundantly.

## 6. Active-work lifecycle classification

Classification covers every pre-existing file under docs/work/active plus this result.

| Item | Classification | Reason / surviving owner before eventual archival |
|---|---|---|
| README.md | Directory-role guide; not a temporary investigation | Explains ACTIVE convention and promotion-before-archive lifecycle; KEEP |
| REPOSITORY_HEALTH_AND_AUTHORITY_AUDIT.md | Genuinely active | Normal Chat has not reviewed/disposed the report. Eventual closure must preserve accepted findings in their smallest owners and archive task/report as provenance |
| SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md | Genuinely active, paused; source implementation complete, acceptance incomplete | DESIGN + source own intended/implemented grouped Speed; ADR-0008/0009 own rationale; broader calibration/deployment/runtime acceptance remain unresolved. Fix status under RH-01; do not archive |
| SPEED_NATIVE_CALIBRATION_PROBE.md | Genuinely active, paused | Tool source and EV-396 prove first control only. Broad native sampling/NB comparison and durable calibration projection remain. Source/hook guide is surviving current engine owner; no closure claim |
| REPOSITORY_HEALTH_AND_AUTHORITY_AUDIT_RESULT.md | Genuinely active result pending independent review | This file records proposals, not accepted authority. Do not implement or archive from Work |

No pre-existing active item is classified closed-but-not-archived or superseded. A completed implementation substep does not close its runtime acceptance task. The archived Sprint probe result legitimately retains historical next-step wording; it must not replace the maintained calibration gate.

## 7. Evidence/raw/archive health

### Ledger and routing integrity

The index's 19 ledger ranges resolve to 18 preserved closed ledger volumes plus the single active docs/EVIDENCE_LEDGER_389_ONWARD.md. The nineteenth file in archive/evidence is the pre-compression evidence index, not another active ledger. Metadata-only extraction accounts for both older table rows and newer headings: EV-001 through EV-396 occur once each, are ordered within their volumes, and have no definition gaps. The active ledger contains exactly EV-389–EV-396 and is below the maintenance warning threshold. No rotation is proposed.

EV-389/390/395 are deliberately diagnostics-free observational proof; absence of a runtime diagnostic file is not missing evidence. EV-391/392 are static source/binary evidence. Exact current inline artifact paths checked in current docs/tasks/ADRs (10 file/path pairs) exist; this check does not cover every historical free-text reference or external binary repository.

### Runtime intake dispositions

| Artifact | Current state and preservation proposal |
|---|---|
| research/raw/Keep.txt | Directory placeholder, KEEP |
| 2026.09.29_speed calibration_1h_troll.log | Explicit active comparison reason in EV-396/EVIDENCE_INDEX; intentionally retained baseline for broad calibration. KEEP in intake while comparison remains |
| 2026.09.29_sprint_probe_goblin.log | Exact source named in closed Sprint result/ADR-0009 route. No current intake reason found. KEEP pending Normal Chat disposition; candidate unchanged archival only after provenance route/migration recorded |
| 2026.09.29_sprint_probe_troll_sabertooth_zombie.log | Exact closed-probe source with multiple family controls and unique environment observations. Same conditional archival rule; not redundant with Goblin/native control |
| 2026.09.29_sprint_probe_troll.log | Separate five-event control returned 1.0 for ordinary Power and factual Sprint. Exact docs source route not found; compare commit/fixture before describing native-only status. KEEP / NEEDS NORMAL CHAT REVIEW before any archival |

For RH-09's conditional archive proposal, the surviving current fact owners are SOURCE_HOOK_GUIDE §3A and DESIGN §3; rationale is ADR-0009; exact proof remains the archived Sprint result plus preserved source and, for the separate Troll control, a newly reviewed canonical evidence/provenance route. EV-396 independently proves tested native Troll values but does not erase the separate earlier control's provenance. Normal Chat must complete the smallest missing evidence transaction before moving that source. Unique content remains recoverable as unchanged archive blobs, stable basenames, migration mapping and Git history. No source should be deleted or deemed redundant.

### Derived/archive integrity

All 27 derived directories have a manifest. Each manifest's SourceFileName resolves to exactly one canonical source in research/archive, and all 27 SHA-256 values match. Each retains an original workstation raw-path snapshot; these historical SourceInput strings are legitimate provenance, not broken current ownership. No manifest rewrite or full-source mirror compaction is proposed. The migration map explains basename-preserving archive resolution. No full_source_part sequence or large raw log was loaded into Chat.

Tracked metadata totals: research/archive 440 files / 221,734,437 bytes; research/derived 1,035 files / 63,835,625 bytes; raw five files / 43,832 bytes. These totals are context, not a deletion criterion. Hash checks cover packaged sources, not every archived source. Closed evidence remains append/history proof and must not be cosmetically corrected for historical NEXT statements or old storage names.

## 8. Source/docs/product-shape consistency

### Speed

BehaviorProfiles loads once with a guarded Load call at ScriptInit, enumerates Profile.* sections, normalizes family/left/right identity, rejects ambiguous duplicate identities, and parses independent optional settings for all seven attacks. Runtime family comes from Animation.GetSkeletonName; normalized UseTypes match the animation reference for the supported profile domain. Requested action/phase selects behavior; current filename is not profile authority.

AttackSpeed maps Normal/Power/QuickR/QuickL/SimpleWhirl/Whirl/Pierce/Hack to seven settings, requires Hit and valid profile/calibration, composes compatibleSpeed * (C/B), and rejects non-finite output. Action3 and Action9 are absent from policy mapping intentionally: factual Sprint is transported through passed Power/Action2 at the proven shared route. No weapon-specific speed-policy branch or Sprint key was found.

EngineBridge installs exactly the 15 Hit callers listed in DESIGN and SOURCE_HOOK_GUIDE. Its wrapper sends the original caller action to the live 42A0 owner exactly once before composition. 42A0 is a call target, not a production entry hook; 47D51 is absent from production hook installation. Calibration probe has the same 15 sites plus 47D51 observation, returns compatibleSpeed unchanged, caps unique observations at 2,048, flushes NEW rows and produces map-ordered summary counts. No behavior mutation/composition was found in the probe. These are static confirmations, not a substitute for expanded runtime acceptance.

The INI comment drift is RH-04; the old canonical-labeled template is RH-05. Neither justifies changing composition or filling uncalibrated profiles during this audit.

### Collision and Raise

Twenty shared collision-core files are byte-identical between current production and retained prototype: all matching behavior/header files except EngineBridge and target CMake. The complete EngineBridge comparison differs only by the Speed include, 15 hook declarations, shared caller thunk and installation block. Bootstraps/CMake deliberately differ by product. The raw55 explicit gates match current reference: Normal marker2 SP0/SP1, true Power SP1/SP2, Sprint-origin current Power OR Sprint SP1/SP2; no generic state widening. Earlier narrower historical Sprint gates are provenance, not current policy.

Raw8 persistent opportunity, separate timing retirement, native-miss rearm and exact contact consumption are implemented and match its production architecture. SOURCE_HOOK_GUIDE's older “consume once” projection does not match them (RH-02). C1 generation/finalization and native-first equipped/raw55 cleanup remain separate from raw8 contact policy.

AttackRaise and SharedConfig are tracked historical prototype source but excluded from the production target and not called by its bootstrap. Presence does not activate Raise. KEEP them: asking Gothic for Raise through its native CombatMove is reusable mechanism evidence. Do not interpret old hard-coded player/2H gates as final product architecture.

### Products and tooling

Root CMake builds production and conditionally exposes the retained FrameCollision behavior/diagnostic twins, CombatMoveLogger, SpeedIdentityProbe, SpeedSprintProbe and SpeedCalibrationProbe. Production target lists behavior/config sources without diagnostics definitions/implementations. Diagnostic/deep includes/hooks in shared source are macro-gated; current CMake does not enable them in production. Static guards preserve research separation; no binary-purity claim beyond prior evidence is newly made here.

Official build SDK pin is 90bfd344de4510dda7ac9da7461cc7f1eac911f7; reference-only Jackydima pin is 316d32406a133f8884e7e302752c35f66b4f54fc. They match maintained reference/schema routes and have distinct responsibilities. Submodules were not populated or advanced.

Root README's target inventory matches CMake. Retained diagnostic tools have legitimate reproduction/research roles; no current tool is proved deletable merely because its causal question closed. The FrameCollision twins are retained collision products, not a full diagnostic twin for expanded integrated Speed. The long-term shared diagnostic-product architecture is an intended destination, not proof of that future packaging today.

Runtime exclusivity and physical removal of excluded DLLs are correctly stated in root README, session/handoff, release architecture and calibration tasks. RH-03 is the concrete defect in canonical deploy checks, not a missing general rule. The knowledge-state workflow runs the canonical validator on relevant documentation pushes; publication of this report will retain the known failure until Normal Chat fixes its owner.

## 9. Reusable engine-knowledge preservation check

| Owner / domain | Coverage and disposition |
|---|---|
| SOURCE_HOOK_GUIDE | Practical API/source order, tested RVAs, explicit calling convention, request identity, Speed caller/composition and Power/Sprint route, raw8 negative callback result, raw55 source/clear surface, bad-skip route and qualified displacement surfaces. KEEP exact detail; correct RH-02 and promote RH-12 |
| COLLISION_CLEANUP_CALLSITE_MAP | Build-specific ordinary/reaction cleanup matrix, return-vs-call semantics, dispatcher identification, fullStop-too-early finding, superseded B6 candidate and untested limits. Healthy distinct scope, not duplicate lifecycle architecture. KEEP |
| ANIMATION_RULES | Native enum/phase/UseType normalization, filename vs source distinction, sampled frames, equipped vocabulary, raw8/raw55 boundaries. KEEP; qualify current raw8 persistence/contact semantics under RH-02 |
| ANIMATION_CATALOG | Concrete assets, Raise availability, dual source/visual order, SimpleWhirl restrictions, optional Hack routing and explicitly historical body-contact fixtures. Unique animator observations deserve preservation. KEEP |
| ANIMATION_INDEX / name data | Exact-data first routing, 5,991 distinct entries, author-grouped uncertain/unused assets. Keep bulk data cold. Current “final production raw8 EV-240” route is an older acceptance landmark; prefer current persistent-model route through EVIDENCE_INDEX when policy matters |
| FUTURE_INVESTIGATIONS + guide movement seed | Preserves New Balance distance/cancel starting points and qualified movement surfaces. Ownership is explicitly unproven; do not convert them into root-motion/climbing architecture or reopen them now |
| Evidence/archive + retained probes | Negative findings, early fixture limits and causal transport proof explain why current solutions exist. Preserve to prevent rediscovery; no bulk promotion from historical hints |

No missing fact should be invented from an old name/RVA. Future Raise can reuse native phase requests and Power Raise observations; future displacement/traversal can reuse CombatMove reach/movement surfaces without assuming root motion ownership; targeting can reuse native target-directed vs source-set distinctions. Their implementation remains unauthorized. The concrete maintenance gaps are qualified promotion/routing, not a need for another permanent reference document.

## 10. Context/retrieval health

The hot route is small: session 3,221 bytes and transient handoff 2,180 bytes, within validator limits. Root front door and recovery lock keep current responsibility discoverable without loading ledgers. Registry and maintenance are event/ownership tools, not mandatory recurring context. This division is healthy.

The largest current document is POPs (52,217 bytes), followed by charter (26,603), active ledger (26,437), DESIGN (22,488), experimental engineering guide (20,777) and source/hook guide (19,450). Much detail is rightful procedural/reference content. POPs provides named triggers and bounded sections; source guide supplies search terms/RVAs rather than a chronological campaign. Size alone does not establish duplication. The charter's orientation/recovery/conventions material should be read by scope; automatic whole-file startup would defeat its own retrieval rule.

Some current projections retain too much progress history (RH-07/08/10) and a few routes are stale (RH-06/11/13). Correct those at their smallest owners. A large current architecture's historical implementation checkpoints may later be qualified/routed more compactly only after Normal Chat identifies each surviving fact/provenance owner. No wholesale compaction, new manifest, merged collision mega-document or deletion is proposed.

Cold archives and derived full-source mirrors are large by design. Their value is random-access proof; their existence is not permission for sequential context loading. The index/manifest/hash/search method worked here. Future procedure automation is optional and should follow demonstrated recurring friction, not the goal of having fewer Markdown bytes.

## 11. Explicit KEEP / DO-NOT-REMOVE items

- Every raw, archive and derived source/package, including the three Sprint logs awaiting disposition. A later archive move is a preservation transaction, not a deletion recommendation.
- All closed ledgers, the pre-compression evidence index, migration map, historical investigations, accepted ADR bodies and Git provenance.
- The complete 5,991-name inventory and author-grouped notes, including uncertain/unused asset entries.
- Cleanup callsite/stacks and source/hook negative findings, raw8 virtual-callback exclusions, exact source/action/state constraints and build-specific qualifications.
- Distinct current collision lifecycle/raw8/raw55/reference/diagnostics/test owners. Topic overlap reflects delegated responsibility.
- Retained collision twins and standalone probes/log tools; old inactive Raise/SharedConfig source; the old provisional INI until its intended role is safely labeled/reviewed.
- Startup recovery lock, CAM/charter boundary, New Balance calibration distinction, native-first cleanup, physical DLL removal and independent Normal Chat review gates.

None is proven redundant. No deletion or consolidation has an established all-facts surviving owner inventory. If such a proposal arises later, first identify each reusable fact, authority layer, unique proof and recoverable owner, then assess preservation risk. Default remains KEEP / NEEDS NORMAL CHAT REVIEW.

## 12. Proposed correction sequence for Normal Chat review

1. Review this report against the exact audited commit; accept/reject findings independently. Restore RH-01's ACTIVE header while preserving incomplete acceptance state, then run unchanged POP-12 validator. Do not weaken it.
2. Review RH-03 before any runtime launch: canonical procedures must select the actual production/probe/twin product, exclude conflicting live DLLs physically and verify exact hashes. No runtime test is requested by this audit.
3. Correct RH-02 at current lookup/authoring owners from existing raw8 architecture/source/proof. Preserve deep negative/static facts. Review RH-04/05's configuration guidance and role labeling without tuning or implementing behavior.
4. Add precise partial supersession routes under RH-06; update only stale current closure projections under RH-07/10. Current policy remains in DESIGN and specialist owners; original ADR/evidence history survives.
5. Reconcile raw intake under RH-08/09. Preserve EV-396 comparison fixture. For Sprint candidates, verify fixture/environment, promote missing exact provenance first, then either document an ongoing comparison reason or archive unchanged with migration routes. Work recommends no unconditional move.
6. Repair bounded retrieval gaps RH-11/12/13 in existing owners. Promote only established qualified calibration facts. Recheck numerical/fragment and practical fresh-Chat routing after edits.
7. Run the canonical validator and static sanity checks after each accepted lifecycle transaction. Close/archive audit task and result only after every finding has explicit disposition and reusable conclusions live in the correct owners. Resume broad native calibration only through the session gate after independent audit closure; Raise remains later and main remains frozen.

This sequence is a proposal, not authorization from Work to implement findings. It does not require a broad reorganization or another architecture document.

## 13. Audit limits / unresolved questions

This is a repository/static authority audit at exactly the named HEAD. It is not a new collision campaign, binary build/purity measurement, expanded Speed runtime certification, calibration completion or live-stack inspection. No compiler, CMake configure/build, deployment, SDK initialization or Gothic launch was attempted.

All registry current owners were oriented by purpose/status and inspected through relevant sections/searches; source-facing targets received direct static comparison. Archive inspection was limited to ledger definition metadata, referenced decisions/probe results, exact provenance and package manifests. The audit did not read every large log, full-source mirror, archived task narrative or external binary-reference/third-party repository. CAM's adopted relationship was verified from project authorities; no separate current-CAM compliance/evolution audit was undertaken.

The standalone Troll Sprint-control environment cannot be certified from its five observation records alone; Normal Chat must recover the exact fixture/provenance before disposition. General untested calibration values remain unproven. No exact current inline artifact route or packaged source was found missing, but this is not exhaustive proof of every historical free-text path.

No finding requires a production semantic decision or source redesign to state the discrepancy. Unresolved archival/provenance choices remain KEEP / NEEDS NORMAL CHAT REVIEW. If resolving a recommendation needs new runtime evidence, charter/CAM change or uncertain unique-knowledge removal, stop that correction and return it to its owning responsibility.

Publication/static scope checks and final remote commit identity are reported by Work with this result. The audited baseline SHA above remains authoritative for findings; the later report-only commit is not a different audited implementation state.

Final pre-publication checks: required report header and all 13 sections PASS; only this result path changed PASS; tracked baseline files unchanged PASS; staged `git diff --cached --check` PASS. Canonical validator rerun returned exit code 1 with exactly the same RH-01 failure and no additional reported error. Remote development recheck still equaled 85badb35c33e87743b3b6bfcab9999a0597d0295 immediately before commit preparation. Publication is limited to this result on development; final published SHA is supplied in the Work handoff.
