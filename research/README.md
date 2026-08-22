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
| `archive/2026-08-22_framecollision_v0.7_player_staff_normal_p0_p1.log` | 2026-08-22 | Intended Quick test actually produced two marked Staff Normal attacks (`Action: 1`). Both P0/P1 executions were claimed by v0.7 at marker frame 5, changed the right-hand Staff 5 -> 7 only at the marker, and naturally reset 7 -> 5. Quick support was not exercised. | `docs/EVIDENCE_LEDGER.md` EV-067, `docs/HANDOFF.md` |
| `archive/2026-08-22_framecollision_v0.7_player_staff_quick_stationary_moving.log` | 2026-08-22 | QuickAttackR/action 4 and QuickAttackL/action 5 waited for marker frame 6, but every natural 7 -> 5 reset was immediately followed by an unmarked 5 -> 7 reactivation. The moving attempt selected action 4 again; action 3 was not exercised. | `docs/EVIDENCE_LEDGER.md` EV-066, EV-068–EV-070; `docs/HANDOFF.md` |
| `archive/2026-08-22_framecollision_v0.8_player_staff_quick_r_l_normal.log` | 2026-08-22 | Player Staff QuickAttackR/action 4 and QuickAttackL/action 5 each activated only at authored marker frame 6, changed Quick StatePosition 0 -> 1, and naturally reset 7 -> 5 without the v0.7 post-reset reactivation. One marked Staff Normal/action 1 regression retained marker-frame-5 activation and natural reset. | `docs/EVIDENCE_LEDGER.md` EV-071–EV-073; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md` |
| `archive/2026-08-22_framecollision_v0.8_npc_staff_quick_r_l.log` | 2026-08-22 | Human NPC `OutNovice_01` produced two marked QuickAttackR/action 4 and five marked QuickAttackL/action 5 executions using its own `It_Halberd_01`. All seven markers changed Quick StatePosition 0 -> 1, activated 5 -> 7, and naturally reset 7 -> 5 without immediate post-reset reactivation. Other later unmarked 5 -> 7 cycles were separate native NPC attacks. | `docs/EVIDENCE_LEDGER.md` EV-074–EV-075; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_native_left_hand.log` | 2026-08-22 | Native-motion left-hand baseline damaged the target while `PC_Hero` used marked frame-controlled ownership. Eight accepted frame-3 markers resolved raw Fist UseType 8, skipped `SetCollisionGroup(Item_Attack)`, kept collision group 0 -> 0, and cleared the triggered list. The session also contained an unmarked legacy/native Boar Fist attack path. | `docs/EVIDENCE_LEDGER.md` EV-080; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md`; `docs/ANIMATION_CATALOG.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_custom_right_hand.log` | 2026-08-22 | Focused-neutral custom right-hand contact visibly damaged the target. The accepted frame-3 marker resolved Fist UseType 8, skipped the group request, kept group 0 -> 0, and cleared the triggered list. | `docs/EVIDENCE_LEDGER.md` EV-081; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md`; `docs/ANIMATION_CATALOG.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_unfocused_allied_single.log` | 2026-08-22 | Unfocused allied-human Fist session produced five accepted marked-P0 events and three unmarked P1 legacy/native callbacks without observed damage. Accepted marked events exceeded fresh frame-controlled ownership decisions 5 to 4. | `docs/EVIDENCE_LEDGER.md` EV-082–EV-083; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_unfocused_allied_many.log` | 2026-08-22 | Larger unfocused allied-human Fist session produced seven accepted marked-P0 events and five unmarked P1 legacy/native callbacks without observed damage. Accepted marked events exceeded fresh frame-controlled ownership decisions 7 to 5. | `docs/EVIDENCE_LEDGER.md` EV-082–EV-083; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md` |
| `archive/2026-08-22_framecollision_v0.9_player_2h_unfocused_allied_single.log` | 2026-08-22 | Marked 2H control against the unfocused allied setup accepted frame 7, changed the Flamberge 5 -> 7, cleared the triggered list, visibly connected, and naturally reset 7 -> 5. | `docs/EVIDENCE_LEDGER.md` EV-082; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_custom_left_leg.log` | 2026-08-22 | Focused-neutral left-leg contact visibly damaged the target. One frame-3 marker resolved Fist UseType 8, kept group 0 -> 0, skipped the group request, and cleared the list; the session unloaded immediately afterward. | `docs/EVIDENCE_LEDGER.md` EV-084–EV-085; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md`; `docs/ANIMATION_CATALOG.md`; `docs/DESIGN.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_custom_right_leg.log` | 2026-08-22 | Focused-neutral right-leg contact visibly damaged the target. The actual marker was frame 2 rather than the planned frame 3; it still resolved Fist UseType 8, kept group 0 -> 0, skipped the group request, and cleared the list before immediate unload. | `docs/EVIDENCE_LEDGER.md` EV-084–EV-085; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md`; `docs/ANIMATION_CATALOG.md`; `docs/DESIGN.md` |
| `archive/2026-08-22_framecollision_v0.9_player_fist_custom_head.log` | 2026-08-22 | Focused-neutral head contact visibly damaged the target. One frame-3 marker resolved Fist UseType 8, kept group 0 -> 0, skipped the group request, and cleared the list; the session unloaded immediately afterward. | `docs/EVIDENCE_LEDGER.md` EV-084–EV-085; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md`; `docs/ANIMATION_CATALOG.md`; `docs/DESIGN.md` |
| `archive/2026-08-22_framecollision_v0.10_player_dual_native_normal_quick_pierce_power_p0_p1.log` | 2026-08-22 | Controlled unmarked player Dual source map: P0/P1 Normal used LEFT/RIGHT; P0 QuickAttackR/L both used RIGHT; P1 QuickAttackR/L both used LEFT; P0/P1 Pierce used RIGHT/LEFT; P0 and P1 Power each activated RIGHT + LEFT. All 17 group activations had paired 7 -> 5 resets in phase 3. The test proves group source/reset, not later triggered-list rearm or full visual Recover completion. | `docs/EVIDENCE_LEDGER.md` EV-090–EV-094; `docs/HANDOFF.md`; `docs/RESEARCH_MAP.md`; `docs/ANIMATION_CATALOG.md`; `docs/DESIGN.md` |
