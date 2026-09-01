# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-01

## Current bridge — stable main promotion

Repository:

```text
tcholti/Gothic3_Animation_Behaviors
```

Active branch:

```text
docs/collision-source-evidence
```

Stable branch:

```text
main
```

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap, then read this file. Do not reconstruct the project from old chat history and do not scan the whole repository.

---

## Accepted technical boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
Literal historical EV-131 regression       CLOSED/PASS — EV-214
Final behavior-only architecture smoke     CLOSED/PASS — EV-215

NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

Do not reopen a completed architecture gate absent concrete contradicting evidence.

---

## Repository cleanup complete

Documentation/knowledge authority repair is complete.

Processed-evidence migration is complete:

```text
19 processed collision logs moved raw → archive
19/19 archived files retain original Git blob SHA
Step D canonical paths repointed to archive
research/raw/ contains only Keep.txt
Step D contains zero research/raw/ paths
```

Migration commits:

```text
c366c5147d5128b7e53e47b57731b498a0ac1602
a3eb460d323a8590444d950b3a60a8e0db5c7083
87e3ffc24ca0bf604ffb6314248e4ab0b4d3ce39
```

Known unrelated local file to leave completely untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Temporary branch inspection complete

Temporary branch:

```text
temp/second-pass-rewrite-publish
```

At inspection:

```text
merge base: 0aa6d19a6815934a3158715070320020bac64292
temp-only commits: 10
active ahead of temp: 60
```

Those 10 commits are only the component-by-component staging history of the second-pass rewrite.

Decisive equality:

```text
temp head: 515d73fab14e7a66d94f3f19b0843072bbf70ef3
temp tree: f303ba47624fc904dd4bc3f64aadfab43cd536d6

accepted active rewrite: 4eeb701725e8b77d8850116d408155653ff4ad36
active rewrite tree: f303ba47624fc904dd4bc3f64aadfab43cd536d6
```

Therefore no unique final file content must be rescued from temp. Do not merge temp into the active branch. Retain it only until main promotion is verified, then it may be deleted safely.

---

## Main-only history inspected

Before promotion:

```text
main head: 76703d362a0aef0a749fc30626eb2b75a3d5fec3
main-only commits: 1
message: Add adaptive collaboration and usage rules
```

That commit contains old Gothic Collaboration Rules v0.1.

Current active authority:

```text
docs/COLLABORATION_RULES.md
Version: 1.8
```

The active authority explicitly routes general collaboration to CAM/current reusable authorities and states that older Gothic collaboration rules are superseded where they conflict. No main-only content needs cherry-picking.

---

## Current responsibility — stable main promotion

Main has an active ruleset protecting:

```text
deletion
non-fast-forward updates
```

No bypass is available or required.

Use a history-preserving fast-forward merge commit:

```text
tree = exact cleaned active tree
parent 1 = old main head
parent 2 = cleaned active head
```

This keeps old main history reachable while making stable content exactly the cleaned/verified active checkpoint.

Required order:

```text
create promotion merge commit
→ fast-forward main to it
→ verify main contains both histories
→ verify promoted tree identity
→ verify main protection remains active
→ only then delete temp/second-pass-rewrite-publish
```

Do not force-update main.

---

## After repository checkpoint

Normal branch model:

```text
main
= stable integration + reusable stable Gothic 3 knowledge

docs/collision-source-evidence
= active development/research
```

After main verification and temp retirement, return to engineering on the active branch.

Forward engineering order:

```text
equipped-melee marker expansion planning
→ freeze/implement/test one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature New Balance/Jackydima compatibility gate
→ Raise + speed + config redesign/migration
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```
