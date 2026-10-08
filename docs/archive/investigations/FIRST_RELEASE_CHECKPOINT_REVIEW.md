# First Release — Final Checkpoint Review

**Status:** CLOSED — READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT / EV-455  
**Mode:** bounded read-only release checkpoint review  
**Frozen by:** User + Normal Chat, 2026-10-08  
**Launch base:** `development @ 26aef9fe348d53d76a8ad8654447445465c4ec37` plus EV-454 closure maintenance  
**Stable main:** `e899f37092706a9846312b93d6b52b34e715b53d`

## Purpose

Decide whether the current `development` branch is ready to become the first-release stable checkpoint.

Do not add features or redesign accepted systems during this review.

## Current first-release systems

- Collision: production-integrated and accepted.
- Speed: production-integrated and accepted.
- Raise: production-integrated and accepted.
- Movement: production-integrated and accepted.
- Bad-block protection: production-integrated and accepted through EV-454.

## Review responsibility

1. Reconcile current `development` against stable `main`.
2. Confirm only intended production/runtime files are part of the shipping surface.
3. Confirm diagnostic/research tools remain non-shipping tools.
4. Confirm default INI/help/release-facing behavior matches accepted first-release semantics.
5. Confirm repository current-state pointers and evidence routing are coherent.
6. Run repository/knowledge validation.
7. Identify any release blocker only if supported by concrete source/repository evidence.

## Non-goals

Do not:
- reopen closed Collision/Speed/Raise/Movement/bad-block research;
- add new gameplay features;
- expand bad-block scope;
- change tuning merely because another option might be preferable;
- promote `development` to `main` automatically.

## Decision output

Return one of:
- **READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT**, with exact reviewed HEAD; or
- **BLOCKED**, with the smallest concrete blocker and exact evidence.

Promotion/merge remains an explicit User + Normal Chat decision after review.


## Final result — EV-455

Reviewed checkpoint:
`development @ 99ed4ac0b4883a082340c3eee41ae67ec69cb92a`

Stable main:
`e899f37092706a9846312b93d6b52b34e715b53d`

Review findings:
- stable `main` is an exact ancestor of the reviewed `development` checkpoint;
- the only production-source delta under `src/Script_G3AnimationBehaviors` is `EngineBridge.cpp`, containing the EV-454 accepted bad-block integration;
- production INI is byte-identical in Git to stable `main`;
- no compiled binaries or release archives are tracked in the main-to-development delta;
- research/prototype targets remain developer/reproduction products; project pipeline defines `Script_G3AnimationBehaviors.dll` as the public/integration product;
- raw evidence intake contains only `research/raw/Keep.txt`;
- stale root README current-product routing found during review was corrected before this checkpoint;
- evidence ledger was rotated at the natural closed release boundary: EV-417–EV-454 archived, EV-455 onward active;
- accepted production build and live runtime still match:
  `SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`;
- knowledge-state validation PASS;
- current worktree clean.

Non-blocking notes:
- `EVIDENCE_INDEX.md` remains above the validator's 20 KiB advisory threshold; the project retrieval model already routes by topic/EV and this does not establish a release defect.
- historical main-to-development `git diff --check` reports whitespace in preserved raw logs and Markdown hard-break metadata; current worktree `git diff --check` is clean and no product source issue is indicated.

Verdict:
**READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT.**

Promotion remains an explicit User + Normal Chat decision and was not performed by this review.
