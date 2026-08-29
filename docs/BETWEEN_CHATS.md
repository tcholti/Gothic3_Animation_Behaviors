# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — AIFullStop transport runtime-stable / C1-O2 still suspended

- Universal-guard-first architecture remains authoritative; the known held-Use2 bad abandonment stays intact as a destructive stress case rather than a production classifier or balance fix.
- AIFullStop recursion-safe transport implementation: `18ff183e05b599de9e035722b15e3bfb6cbbc034` (`Make AIFullStop hook recursion-safe`). Independent Normal Chat source review: **PASS**.
- Validated deployed DLL SHA256: `89329667BF83479E419C2775965E0CC41769F2BFD247F84C95939B673292B13B`. Isolated startup/unload check: **PASS**.
- Extended-gameplay stability evidence: commit `72273ead0ae7821a0d70b2e3b168ad00a1271f1a`; canonical run `research/archive/2026-08-29_c1_aifullstop_recursion_safe_extended_gameplay_stability.log` plus connector extract in `research/archive/`.
- Runtime result: **PASS**. 127 AIFullStop calls, 71 CombatMove FullStops, 513 AISetState calls, 179 C1 finalizations, 16 actual `WOULD_REPAIR` text outcomes, normal unload, and no crash during broad gameplay / repeated bad-skip reproduction across multiple weapon configurations.
- The 11 `C1 INVARIANT WARNING` records are all the already-known `UNOWNED_PLAYER_OFFENSE_REQUEST` acquisition gap from EV-194. `C1-O2 BINDING INVARIANT`, `OUTER_RETURN_OUTSTANDING`, `LIVE_FRAME_MISMATCH`, `PRECOMBAT_GENERATION_FRAME_OVERLAP`, `OVERLAP_OUTSTANDING`, `CANDIDATE_GENERATION_CHANGED`, `FINALIZATION_GENERATION_CHANGED`, `NULL_ARGUMENTS`, and `UNRESOLVED_NOT_EQUIPPED` were all zero in the extracted counts.
- This AIFullStop result does **not** prove that the original direct `RunScriptFunction` C1-O2 dispatch-capture crash is solved. `RunScriptFunction` remains recursion-safe pure pass-through; AISetState remains its validated explicit-this `.ThisCall()` baseline; physical repair remains disabled.
- No Work task is currently frozen.
- Next Normal Chat responsibility: inspect the remaining legacy ThisCall transport that is directly on C1's core offense/cleanup observation path (`SetCollisionGroup`) against the proven explicit-this pattern. If the API/source contract supports an isolated transport-only correction without collision/lifecycle semantic changes, propose that bounded prerequisite explicitly before freezing Work. Reevaluate C1-O2 after that result rather than automatically hardening every remaining legacy hook.
