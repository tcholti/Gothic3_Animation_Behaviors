# First Release — Final Checkpoint Review

**Status:** ACTIVE  
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
