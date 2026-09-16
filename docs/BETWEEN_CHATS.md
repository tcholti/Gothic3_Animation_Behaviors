# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-16

## Current Bridge — EV-288 CLOSED; RAW55 NORMAL TRIGGER-STATE OBSERVATION PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-288**. No permanent raw55 implementation is authorized.

Current frozen diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_TRIGGER_STATE_OBSERVATION_PROBE.md`

Read in order:

1. `SESSION_ENTRYPOINT.md`
2. this file
3. `COLLISION_RAW55_NORMAL_TRIGGER_STATE_OBSERVATION_PROBE.md`
4. `EVIDENCE_LEDGER_286_ONWARD.md` — EV-286 through EV-288
5. `FEATURE_DEVELOPMENT_METHOD.md`
6. `WORK_IMPLEMENTATION_PROTOCOL.md`

## EV-288 — closed result

Canonical runtime:

`research/raw/2026.09.16_troll_raw55_normal_native_rearm_source.log`

SHA256:

`AB8E7B8B300F08CD61B01E7338FC672E6A09DE7D57F055F4FFAFD68514628C6E`

Upload commit:

`9af56b93cafbddbe4b645bc574439758ccc2edcc`

Diagnostic implementation:

`6ca48c84e9fdf370ffdb824f9142e8ef0e267a7c`

Local build/live DLL SHA256:

`DA392693066AD9CAF3E52789E0115592DC4E08B43CAA4DBA0B4E0C55E8473784`

Representative factual Normal C1=14:

```text
frame-1 FIST at SP0 / StateTime ~= 0.064
-> exact RIGHT TrollFist raw55 5 -> 7
-> ClearTriggeredList=1 / PRESTATE_REARM=1

first ONDAMAGE around callback StateTime ~= 0.193
while StatePosition remains 0

StateTime ~= 0.253:
-> RAW55_NORMAL_NATIVE_REARM_SUPPRESSION_PROBE
-> RequestedGroup=7 / BeforeGroup=7
-> PreStateRearmProven=1
-> NATIVE_7TO7_SUPPRESS=1

same callback:
-> StatePosition 0 -> 1 survives
-> RIGHT remains group7

frame-15 FIST around ~= 0.601
-> delivered at SP1
-> no Normal marker-2 intervention

second ONDAMAGE around ~= 0.723

native exact RIGHT 7 -> 5 cleanup
clean C1 finalization
```

The User repeatedly observed both physical swings damaging during the run.

Therefore:

```text
native Normal 7 -> 7 setter as required second-rearm source = REJECTED
first marker-owned damage                                  = PASS
native SP0 -> 1 progression with setter suppressed         = PASS
second same-C1 damage with setter suppressed                = PASS
native cleanup / C1 finalization                            = PASS
```

Do **not** infer that StatePosition itself rearms the source. The state transition survived but was not independently manipulated.

## Current question

The remaining second-contact mechanism may be ordinary trigger/touch bookkeeping.

The official SDK exposes read-only trigger state on `eCTrigger_PS`:

```text
EntitiesVisited
EntitiesVisitedCount
```

and `gCTouchDamage_PS` exposes:

```text
ResetOnUntouch
```

The next probe is observation-only. Preserve the EV-288 environment, including the exact one-shot native `7 -> 7` setter suppression, and observe the exact RIGHT raw55 trigger state across:

```text
POST_PRESTATE_REARM
change-only Normal callback observations
NATIVE_7TO7_SUPPRESS_PRE
SP0_TO1_POST_CALLBACK
LATER_FIST
```

The key question is whether `PC_Hero` enters the visited state after hit 1 and is naturally removed/reset before hit 2 without any explicit marker-2 clear.

No new hook is authorized. No StatePosition write, marker-2 rearm, trigger-state mutation, direct damage, cleanup change, or permanent architecture change is authorized.

## Power observation

The User reports that prepared Power two-swing animations visibly damage on marker 1 but do not rearm for marker 2. Keep this as behavioral guidance only until Normal second-contact ownership is understood well enough to design the common authored-marker rule.

## Remaining collision order

```text
Normal read-only trigger-state observation
-> if a natural visited-state reset is observed, isolate its exact cause only if necessary
-> establish authored Normal marker-2 ownership
-> Power repeated-FIST rearm
-> Sprint repeated-FIST rearm preserving same-C1 Action9 -> Action2 continuity
-> permanent raw55 architecture / implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

New Balance 0.7 is not a current blocker. Existing combined runtime evidence remains EV-035/EV-150/EV-242, with corrected compatibility interpretation EV-285.
