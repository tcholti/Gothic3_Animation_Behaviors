# Session Entry Point

**Purpose:** Minimal durable current-state pointer for Gothic 3 Animation Behaviors work. The repository-level startup front door is root `README.md` **Start Here**.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-19

> **INTERRUPTED-CHAT ENTRY RULE:** If the previous Chat failed, hit max context, or became unusable, start at the repository root `README.md` **Start Here** recovery block. In that situation this file is a clue, not unquestioned truth, until POP-11 recovery reconciles it with the newest durable state.

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is the diagnostic twin. Permanent collision behavior must also compile in diagnostics-free `Script_FrameCollisionBehaviorTest`. Final migration into `src/Script_G3AnimationBehaviors` occurs only after focused acceptance and standalone collision regression.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and committed derived packages for large-log retrieval. Processed source evidence moves unchanged to `research/archive/` after evidence closure.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Permanent raw55 contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Astra audit result/disposition: `docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`  
Latest canonical evidence: **EV-308** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick repeated-FIST CLOSED/PASS — EV-273
raw55 Normal repeated-FIST CLOSED/PASS — EV-292
raw55 true Power repeated-FIST CLOSED/PASS — EV-293
raw55 Sprint-origin repeated-FIST CLOSED/PASS — EV-294

PERMANENT RAW55 IMPLEMENTATION 21853392... SOURCE REVIEW PASS
BOTH RELEASE TARGETS BUILD PASS
BEHAVIOR-ONLY FUNCTIONAL/RELEASE-PURITY SMOKE PASS
DIAGNOSTIC DEPLOYMENT + STARTUP PASS
PERMANENT RAW55 FOUR-FAMILY BEHAVIOR CORE ACCEPTANCE PASS

CORE OWNERSHIP CLASSIFIER CORRECTION 314f284d...:
- Work static audit PASS
- Normal Chat independent source review PASS
- runtime control PASS — EV-295
- legitimate raw55 ownership is ROUTINE; false CORE ATTACK OWNERSHIP ANOMALY count = 0

CALLBACK IDENTITY DIAGNOSTIC SURFACING 6795377f...:
- Astra implementation/static audit PASS
- Normal Chat independent source review PASS
- exactly one source file, +27/-0
- diagnostics-only under FRAME_COLLISION_DIAGNOSTICS
- legitimate control produced no contradiction, as expected
- source-contract correction remains PASS

FOCUSED SENTINELS:
- equipped authored-marker sentinel PASS — EV-295
- unmarked raw55 native fallback PASS — EV-296
- raw8 FIST coexistence PASS — EV-297
- focused permanent raw55 acceptance CLOSED/PASS — EV-298

ASTRA PERMANENT RAW55 AUDIT:
PASS WITH NON-BLOCKING FINDINGS
- no confirmed release-behavior defect
- F1 nested marker/callback attribution = defensible risk, no change
- F2 callback-entry identity contradiction surfacing = corrected by 6795377f...
```

## Permanent core acceptance evidence

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
research/derived/2026.09.17_troll_raw55_permanent_acceptance_large_log/
upload commit 6ae7dcc315e0859ab8ff061f1576d52206d21008
SHA256 AA866E70BF2DB42CF7CE73607040443A9F8725F05CCFDDB01116E582956DA6A7
blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b
150110 bytes / 1011 lines
```

Representative Quick, Normal, true-Power and Sprint-origin two-FIST routes all show intended first-marker behavior, clear-only marker2 rearm, two native damage opportunities, native exact RIGHT `7 -> 5` cleanup and outstanding-zero finalization.

The focused permanent-acceptance transaction is CLOSED/PASS at EV-298. Its processed runtime sources have been archived byte-identically; do not rerun the focused raw55 matrix without concrete contradictory evidence.

## Independent Astra audit disposition

Saved full project disposition:

`docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`

### F1 — nested marker inside active callback scope

Source makes the hypothetical suppression collision logically possible, but accepted runtime evidence demonstrates it does not occur in the supported tested first-marker routes. Do **not** add speculative release behavior.

### F2 — callback identity contradiction surfacing

The diagnostics-only contract omission is now source-corrected by:

```text
6795377f2a827a8c06a531006a56a87b457e8642
```

Changed only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

The new helper is compiled only under `FRAME_COLLISION_DIAGNOSTICS` and emits:

```text
CORE RAW55_PHYSICAL_FIST_IDENTITY_CONTRADICTION
```

using the already-computed callback-entry contradiction. Behavior still returns without raw55 intervention exactly as before.

Normal Chat independent source review: **PASS**.

## Current responsibility — STANDALONE REGRESSION PHASE 1: GOLEM ATTACK/SETUP MATRIX

Focused permanent raw55 acceptance is now **CLOSED/PASS — EV-298**.

Final raw8 sentinel EV-297 proves the established raw8 mechanism remains healthy under the permanent raw55 source state:

```text
47 accepted FIST markers with Fist / Raw8UseType=8
native Sabertooth -> PC_Hero damage = 11
transformed Sabertooth -> native Sabertooth damage = 13
native + transformed C1 finalizations = 47 clean
raw55 intervention in raw8 route = 0
ownership anomaly / invariant / repair / divergence = 0
```

The four focused acceptance sources were archived byte-identically in:

```text
5700aedb2feadbde1d1a635a9538ed788836f36d
```


First two standalone-regression batches are CLOSED/PASS:

```text
EV-299  1H                         PASS
EV-300  1H+torch                   PASS
EV-301  dual 1H                    PASS
EV-302  2H                         PASS
EV-303  Staff                      PASS
EV-304  human Fist single marker   PASS
EV-305  human Fist double markers  PASS
EV-306  1H+shield                   PASS
EV-307  Sabretooth double FIST      PASS
EV-308  shield-bash LEFT/raw9        NEGATIVE CONTROL / DEFERRED
```

Newest supplemental finding:

```text
shield-bash LEFT/raw9:
  tested existing shield-bash animation in Quick slots
  first no-target, then Golem-contact exercise
  9 accepted LEFT markers
  factual LEFT shield = It_Shield_StewarkGreat / UseType9
  9 exact shield 5->7 activations
  9 exact shield 7->5 cleanups
  9 C1 cleanup fulfilled records
  zero ONDAMAGE events for the entire run
  zero ownership anomaly / invariant warning / repair divergence
  conclusion = marker/source activation works; native shield-bash damage does not
  current feature status = DEFERRED, no source change
```

Latest-batch highlights:

```text
1H+shield:
  tracked RIGHT sword raw2 + LEFT shield raw9
  authored offense = RIGHT only
  60 exact 5->7 and 60 exact 7->5 on sword
  31 Golem damage events
  deliberate bad skip -> exact RIGHT sword C1-R1 repair PASS
  shield stays group5 / zero offense / zero repair
  one late Action0 Quick marker safely rejected

Sabretooth double FIST:
  native + transformed factual raw8 Fist/UseType8
  transformed player: 20 marked C1 executions, exactly 2 FIST each
  marker1 = early permission; marker2 = NATIVE_TIMING
  18 executions land twice; 2 land once despite both rearm events
  native Sabretooth also shows two-marker same-C1 behavior
  single-marker native cases are Stumble replacements or final shutdown
  transformed -> native Sabretooth damage events = 38
  native Sabretooth -> PC_Hero damage events = 19
```

Second-batch highlights:

```text
2H:
  Normal/Quick/Power/Whirl/Hack
  RIGHT Flamberge raw3
  18 Golem damage events
  deliberate bad skip -> exact C1-R1 repair PASS
  late Action0 Whirl marker callbacks safely rejected

Staff:
  Normal/Quick/Power/Whirl/Hack
  RIGHT Wrestling Staff raw12
  22 Golem damage events
  deliberate bad-skip attempts -> cleanup reaches group5 before repair is needed
  late Action0 Whirl marker callbacks safely rejected

human raw8 Fist single marker:
  Normal + Power
  19 accepted FIST markers
  intentionally unmarked Power P1 remains native and damages through Game+0x16E348
  13 Golem damage events total

human raw8 Fist double markers:
  21 marked C1 executions
  exactly 42 accepted FIST markers = two per C1
  second FIST accepted as NATIVE_TIMING rearm
  10 target-contact executions produce two Golem damage events each
```

Across the processed regression batches through EV-308:

```text
CORE ATTACK OWNERSHIP ANOMALY = 0
C1 INVARIANT WARNING = 0
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED = 0
all PC_Hero C1 final records Outstanding=0
```

All processed regression logs through EV-308 are archived and `research/raw/` is clean except `Keep.txt`.

Current diagnostic binary remains the already-verified product:

```text
build source checkout = 8abe9c30cae5755184bb5ed22b2959998ad22d33
built/live DLL SHA256 = 68C750860ABB901B5F6E7D1291838ED7C50CC6E33D3A124E448D42C59BBD14BD
build/deploy/startup PASS
```

All repository commits after that binary build are documentation/evidence maintenance only unless a later source change is explicitly introduced.

Before the next local test, use the normal POP-01 GitHub Desktop Fetch/Pull handoff. Then continue the seven-phase standalone campaign in `COLLISION_TEST_PLAN.md` §8. Current phase remains §8.1: continue the remaining prepared Golem weapon/setup runs. Completed Golem setups already closed: 1H, 1H+torch, dual-1H, 2H, Staff, human Fist single-marker, human Fist double-marker and 1H+shield. Supplemental Sabretooth double-FIST raw8 control is PASS at EV-307. EV-308 adds a shield-bash negative control: LEFT physically activates shield/raw9 but produces no native damage, so shield-bash damage remains deliberately unsupported/deferred. Use one runtime run/log per weapon. The User may upload small batches (typically 2–3 at a time). After every uploaded batch, Normal Chat must complete POP-06 evidence/document/archive cleanup before requesting the next batch. Do not reopen raw55 family-specific probing.

## Next sequence after standalone collision regression

```text
standalone collision regression
-> New Balance 0.7 exact distributed bundle regression with AttackCollision included
-> mature collision migration into src/Script_G3AnimationBehaviors
-> later Raise/speed
```

## Still paused

```text
standalone collision regression = CURRENT GATE
current subphase = §8.1 Golem player attack/setup matrix; Golem coverage through EV-306, supplemental controls EV-307–EV-308 closed
publication cadence = small batches allowed; each batch fully closes before next
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```
