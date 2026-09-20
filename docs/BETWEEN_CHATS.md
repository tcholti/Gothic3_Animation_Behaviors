# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **Phase 4 broad regression PAUSED at raw8 persistent-opportunity causal research through EV-347.**

Latest completed evidence: **EV-347**.

## Agreed raw8 design target

```text
marked C1 starts
-> authored raw8 opportunity CLOSED

accepted FIST
-> one target-directed native body-contact damage opportunity OPEN

unsuccessful native contact
-> opportunity remains OPEN

successful native contact
-> opportunity CONSUMED/CLOSED

later FIST
-> opportunity OPEN again

C1 / Hit termination, interruption or factual replacement
-> any unused opportunity CLOSED
```

No arbitrary timer. No authored raw8 FIST_OFF absent future evidence of a concrete unwanted-contact problem. Gothic retains target/contact/damage ownership.

Raw55 must later be checked against the same author-facing abstraction without copying raw8 mechanics into raw55.

## EV-347 closure

Reviewed observation implementation:

`4ab9a77557f9ad5057d158b7d26a3098db657b28`

Diagnostic DLL:

`Script_FrameCollisionTest.dll`  
SHA256 `3EDC9FC0B6BE0BC8B4ED3249D4CC6F99F613694FC32ECC867DF9B6396FFC5CD3`

Build/deploy/startup: PASS.

Controlled frame-3 Gargoyle raw8 Power result:
- four exact `SyntheticApplied=1` attempts;
- C1 6 miss -> post-attempt latch 1;
- C1 9 exact `Game+0x16E348` Fist/Gargoyle hit -> post-attempt latch 1;
- C1 18 miss -> post-attempt latch 1;
- C1 50 exact `Game+0x16E348` Fist/Gargoyle hit -> post-attempt latch 1;
- all exact SPU/C1/source/motion identity checks matched;
- all marked C1s finalized cleanly.

Conclusion:

> The tested native raw8 path closes the latch after the **attempt**, whether or not damage succeeds.

The observation probe is CLOSED/PASS and archived.

Canonical evidence:
`research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test.log`  
Git blob `7b2262ee2acf2d8e5da3fea4a3c5984eb849a9b8`.

## Active bounded Work task

`docs/work/active/COLLISION_RAW8_FIST_POST_MISS_LATCH_REARM_CAUSAL_PROBE.md`

Single causal question:

> After an exact marked raw8 Power synthetic attempt misses, can one exact post-original `SPU+0x164: 1 -> 0` write preserve a later native opportunity when the target is reached?

Frozen intervention:
- Power/raw8 only for this first causal probe;
- exact actor/SPU/C1/source/motion identity;
- exact synthetic permission consumed;
- exact post-attempt latch 1;
- no exact same-invocation native raw8 damage matching `Game+0x16E348` + exact fist source + exact actor;
- then write latch 1->0 once;
- do **not** rearm timing permission;
- successful early hit branch performs no write.

Architecture:
- temporary `Raw8FistWindowProbe` module;
- diagnostic twin only;
- EngineBridge remains hook owner / minimal delegation;
- no new hook;
- no timer/polling;
- no direct damage;
- no target inference;
- no FIST_OFF;
- no raw55/equipped/Sprint changes.

Work implementation `ea652e3324fffb07da013229a2fd374c4f3b1c6b` is independently source-reviewed **PASS**.

Next:
1. User builds both twins from the reviewed source state.
2. Deploy diagnostic twin only and verify sole-live-twin + SHA256 + startup.
3. Use the same frame-3 Gargoyle Power fixture.
4. Deliberately include close-range attacks that hit at the synthetic opportunity and farther attacks that miss initially but reach the player later in the same motion.
5. For close-range hits require `Decision=EXACT_NATIVE_DAMAGE_OBSERVED`, `RearmRequested=0`.
6. For far initial misses require `Decision=POST_MISS_REARM_CONFIRMED`, latch `1 -> 0`, then inspect whether a later real/native-timed raw8 opportunity damages the player.
7. This probe does not yet prove continuous eligibility between marker time and native threshold.

`research/raw/` should contain only `Keep.txt`.
