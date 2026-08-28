# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-28

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration and reusable Gothic 3 knowledge baseline.

Document roles / Hot-Warm-Cold retrieval / Subsystem Orientation Pass: `docs/README.md`  
Latest transient Chat/Work bridge, only when relevant: `docs/BETWEEN_CHATS.md`

---

## Fresh Normal Chat Bootstrap

For a newly opened Normal Chat:

1. read this file first and treat it as the current-state authority;
2. read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent Work task or transient handoff;
3. if the active technical subsystem is not already sufficiently oriented in the current Chat context, perform the **one-time Subsystem Orientation Pass** from `docs/README.md`: use the relevant subject route and targeted index/authority sections to reconstruct a compact working model of the subsystem before drilling into the exact current step;
4. do **not** reconstruct the project from old chat history, scan the whole repository, or create another persistent subsystem-summary document;
5. retrieve only the exact deeper authority listed under **Retrieval — Only What the Question Needs** when the current question requires it;
6. continue the current Normal Chat responsibility from the repository state. The User should not need to restate project history already preserved here or in the routed authorities.

Within the same continuing subsystem context, do not rerun the orientation pass or reread unchanged authorities after every prompt.

A new Normal Chat should normally need no custom handoff document beyond this front door. `BETWEEN_CHATS.md` remains the replaceable transient bridge for exact Chat ↔ Work continuity.

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Confirmed native defect: a real offensive Hit can lose enough CombatMove/action bookkeeping that the physical Hit continues or later replaces while Gothic 3 fails to run normal collision cleanup. This defect is native and is not introduced by frame markers.

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety should be one shared invariant for marked and native attacks.

Current architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Step-B Facts Needed Now

- type-0 `eCVisualAnimation_PS::PlayMotion` gives immediate PrimaryFirst acquisition/replacement evidence, but clean successor PlayMotion can occur **before** native cleanup;
- later original attack callbacks are not one-shot completion boundaries;
- `sAICombatMoveStartRecover` is too early and can be bypassed;
- missing Recover assets are not the root cause;
- successful ordinary cleanup is action-specific inside `Script_Game.dll`;
- tested damage/reaction interruption uses a separate cleanup route at `Script_Game + 0x24AFF`;
- B5/static identification reached generic script infrastructure:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

- `Game + 0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)`;
- `sAICombatMoveInstr` itself remains too early for repair, but B6-B uses it as caller-context evidence;
- EV-174/EV-175: clean 2H Normal still has the outgoing Hit at StartRecover BEGIN but PrimaryFirst is already empty by StopMotion-hook entry;
- EV-176: all three valid clean 2H Normal StartRecover stack captures were identical: diagnostic wrapper -> `Game + 0x169772` inside `sAICombatMoveInstr` -> `Game + 0x16F240` inside `ProcessScript()`;
- the right-hand source remained `Item_Attack(7)` at capture time, and later native `7 -> 5` cleanup still occurred after StartRecover returned;
- EV-177: legitimate 2H Normal damage/reaction interruption repeatedly cleaned the weapon through `Script_Game + 0x24AFF`, then reached an already-empty Primary before StopMotion and installed Stumble/KnockDown successor motions without running the interrupted attack's own Recover;
- that B6-C path proved the original direct replacement probe insufficient because the outgoing attack Primary is already gone before the successor PlayMotion request.

These generic script functions are **not combat ownership authority**. Their current role is timing/context evidence only.

Exact evidence/RVAs: `EVIDENCE_INDEX.md` and `COLLISION_CLEANUP_CALLSITE_MAP.md`.

---

## Current Candidate

```text
exact owned offensive Hit teardown/replacement observed
→ mark that exact execution pending-finalization
→ let Gothic finish current native script dispatch
→ at one tightly gated post-script opportunity:
     native cleanup observed -> no-op
     cleanup absent          -> repair
```

A generic script layer may provide **timing only**. Exact attack execution ownership and its offensive-collision request must already exist.

This remains a hypothesis.

---

## Current Gate — B6 Cross-Path Script-Context Validation

The current diagnostic source now contains four observational paths only:

- StartRecover-BEGIN stack capture for a still-visible outgoing attack Hit;
- StopMotion stack capture when an outgoing attack Hit is still visible there;
- direct PlayMotion replacement stack capture when before/after proves the outgoing Hit was replaced/restarted;
- B6-C empty-Primary successor PlayMotion stack capture for the controlled player Normal attack context after the outgoing Primary has already disappeared.

The empty-Primary successor diagnostic is **diagnostic correlation only**. It does not make stale action/phase/current-movement values lifetime authority and does not classify the successor as Stumble, KnockDown, Recover or another family.

Implementation commit:

```text
55ca9148b0c6f3be8e65b5d483eeabec85195a08
```

Independent Normal Chat source review: **PASS**.

Authoritative live diagnostic path after the next local build/deploy:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_FrameCollisionTest.dll
```

Expected revised runtime banner:

```text
STEP B6 HIT STARTRECOVER / STOP / REPLACEMENT / EMPTY-PRIMARY SUCCESSOR STACK PROBE
```

### B6-B result — clean completion

Valid raw evidence:

```text
research/raw/2026-08-28_b6b_player_2h_normal_clean_completion_startrecover_stack.log
```

Commit: `8abd7950ac3c5d6b4a5c66968daf3df1e33c114f`.

All three clean player 2H Normal attacks captured:

```text
attack Hit Primary / source 7
→ StartRecover BEGIN
→ HIT STARTRECOVER BEGIN STACK
     Script_FrameCollisionTest
     → Game + 0x169772  (sAICombatMoveInstr)
     → Game + 0x16F240  (ProcessScript)
→ PrimaryFirst-empty StopMotion
→ Recover PlayMotion
→ StartRecover END
→ native cleanup 7 -> 5
```

B6-B therefore **supports** the common-`ProcessScript()` timing hypothesis for clean completion. It does not prove the universal architecture and does not make StartRecover or ProcessScript ownership authority.

### B6-C result so far — legitimate reaction interruption

Valid raw evidence:

```text
research/raw/2026-08-28_b6c_player_2h_normal_legitimate_reaction_replacement_stack.log
```

Usable player 2H Normal interruptions repeatedly showed:

```text
attack Hit / weapon 7
→ legitimate reaction cleanup at Script_Game + 0x24AFF: 7 -> 5
→ outgoing attack Primary already empty before StopMotion
→ successor PlayMotion begins from empty Primary
→ Stumble / KnockDown successor installed
```

The original direct `HIT REPLACEMENT STACK` probe could not capture the successor's caller stack because its gate requires the outgoing attack Primary to still exist at PlayMotion entry.

### Immediate Normal Chat responsibility

1. fast-forward the authoritative home checkout;
2. build `Script_FrameCollisionTest` with the reviewed empty-Primary diagnostic;
3. deploy and verify the revised banner/hash;
4. repeat the controlled B6-C legitimate player 2H Normal interruption fixture;
5. inspect `HIT EMPTY-PRIMARY SUCCESSOR STACK` records and compare their caller/SPU context with EV-176's clean `sAICombatMoveInstr -> ProcessScript()` stack;
6. only after B6-C is interpreted should B6-D reproduce the known bad block-skip replacement path and compare its context.

Question:

> **Do clean Hit disappearance, legitimate reaction teardown/replacement, and bad direct replacement occur inside one useful SPU / `ProcessScript()` context so a tightly gated one-shot checkpoint can reliably run after Gothic's native cleanup opportunity?**

Exact procedure/interpretation: `COLLISION_TEST_PLAN.md` Gate B6. Diagnostic authority: `COLLISION_LOGGER_PLAN.md` §6. Canonical evidence: EV-174–EV-177.

---

## Do Not Do Yet

Until B6 answers the boundary question:

- do not implement production cleanup;
- do not hook `ProcessScript` as unconditional behavior;
- do not add family/cause-specific repair branches;
- do not add timers/polling;
- do not treat StartRecover, StopMotion, action/phase, or filename alone as universal continuing physical Hit lifetime authority;
- do not move unfinished collision implementation to `main`.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| documentation/retrieval model or subsystem orientation route | `README.md` |
| lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| diagnostics | `COLLISION_LOGGER_PLAN.md` |
| current test gates | `COLLISION_TEST_PLAN.md` |
| exact evidence | `EVIDENCE_INDEX.md` |
| cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| hook/API/symbol lookup | `SOURCE_HOOK_GUIDE.md` |
| animation semantics/assets | `ANIMATION_INDEX.md` |
| overall Raise/speed/collision architecture | `DESIGN.md` |
| older chronology | `RESEARCH_MAP.md` / archive only if needed |

Do **not** load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay possibilities such as jumping, wading and climbing when they become active goals.

If the final lifecycle uses generic script timing, later negative/no-op regression must include Fist, bow, crossbow and magic; Fist is particularly important because melee action enums alone do not imply weapon-style `Item_Attack(7)` ownership.
