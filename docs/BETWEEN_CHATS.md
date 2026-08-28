# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Reviewed Work result — Step B7 CombatMove full-stop stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `7b1096284f7385af5822c59735191dcf47c2e097`
**Independent Normal Chat review:** PASS

### Verified source change

- One diagnostic hook was added at tested `Game + 0x1696E0` for authoritative `sAICombatMoveInstr(GELPVoid, gCScriptProcessingUnit *, GEBool)`.
- The new diagnostic path runs only when `fullStop == GETrue`, the SPU is non-null, and SelfEntity resolves to the player.
- Caller stack and factual action/phase/StateTime/StatePosition/movement/PrimaryFirst/equipped-source context are captured before original.
- The record heading is `===== COMBATMOVE FULLSTOP STACK =====` and the startup banner identifies the B7 probe.
- Original `sAICombatMoveInstr` is called exactly once with unchanged arguments on every path and its result is returned unchanged.
- Non-full-stop calls do no new diagnostic capture before forwarding.
- Only the three frozen diagnostic source files changed.
- Existing B1–B6/B4/B5 diagnostics and all collision/marker/callback/bookkeeping/native-cleanup behavior remain unchanged.
- No production cleanup/repair, lifecycle state, persistent diagnostic state, timer, polling, scan, cache, ProcessScript/AIFullStop/AIStopCombatMove hook, offensive-request stack capture, classifier, cause gate, successor-name gate, or guessed layout was introduced.

### Next responsibility

1. Fast-forward the authoritative home checkout.
2. Build `Script_FrameCollisionTest` Release.
3. Deploy the rebuilt DLL to the authoritative Gothic 3 `scripts` path and verify one active matching DLL plus built/live SHA256 equality.
4. Load Gothic 3 and verify the B7 `COMBATMOVE FULLSTOP STACK PROBE` startup banner.
5. Only after load verification, Normal Chat freezes the controlled clean / legitimate-reaction / bad block-skip B7 runtime fixture and exact raw filename.

No runtime evidence exists yet for B7; do not promote the full-stop hypothesis from static evidence alone.
