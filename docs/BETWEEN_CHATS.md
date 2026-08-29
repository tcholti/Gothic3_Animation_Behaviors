# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — AIFullStop transport implemented / source-reviewed

- Universal-guard-first architecture remains authoritative; the known held-Use2 bad abandonment stays intact as a destructive stress case.
- AIFullStop recursion-safe transport implementation is published at `18ff183e05b599de9e035722b15e3bfb6cbbc034` (`Make AIFullStop hook recursion-safe`).
- Independent Normal Chat source review: **PASS**.
- Compared from frozen base `f307ca77061d82a8b3f95def2ac8b725ef979e5f`: exactly one commit, exactly the two allowed source files changed.
- AIFullStop now receives explicit per-invocation `gCScriptRoutine_PS *this`, forwards that exact pointer to the original exactly once, and installs through `.ThisCall()`.
- Existing AIFullStop diagnostics and pre-original ordering are preserved; AISetState and RunScriptFunction are unchanged.
- C1-O2 direct RunScriptFunction dispatch capture remains suspended; physical repair remains disabled.
- Immediate responsibility: User synchronizes the local branch, builds `Script_FrameCollisionTest`, then reports only build success or the smallest relevant error excerpt.
- After build success, Normal Chat gives the deploy/hash verification step; do not skip directly to runtime testing.
