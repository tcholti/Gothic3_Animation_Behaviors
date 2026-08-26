# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

For document roles and authority, see `docs/README.md`. For the latest Chat/Work bridge, see `docs/BETWEEN_CHATS.md`.

## Active Subsystem

Frame-controlled melee collision lifecycle.

The RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is optional authored early shutoff inside a live Hit; it is not the general end-of-Hit safety mechanism.

Known native defect: offensive weapon collision can remain `Item_Attack` after a Hit is replaced/interrupted without normal cleanup. Recover is not the universal cleanup owner.

## Preferred Cleanup Model

Prefer **System 1: execution-level native cleanup guard**.

For every real attack-Hit execution that requests offensive collision, follow the exact actual Hit execution until it ends/replaces. If Gothic 3 already performed proper native cleanup, do nothing; if it did not, invoke the native cleanup Gothic 3 should have performed.

Marked and native attacks should differ primarily in activation timing. Use **System 2 source-aware cleanup only if evidence proves cleanup is genuinely source-specific or partially independent**.

Detailed architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

## Marker Rule While Hit Is Alive

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive collision set.

## Step A — VALIDATED

Implementation commit:

`325c98e725502229bf796083e52c0fa977803cc0` — `Modularize frame collision research DLL`

The research DLL remains one DLL with one owner for each hook, split into hook bridge, collision control, collision diagnostics, shared facts, and runtime timing modules.

Home-PC validation on 2026-08-26:

- MSVC Release build succeeded;
- built and installed DLL SHA-256 matched: `4CD111D0B92A562AD8831BA81FA00C6E8A29BE5EC3F66E5920D6B214F99553DD`;
- Gothic 3 loaded and ran without crash;
- smoke test covered marked Normal/Quick/Whirl across 2H, Staff, and Dual/1H+1H;
- marker ownership, collision-group logging, Quick/Whirl `StatePosition`, source resolution, and PrimaryFirst lifetime diagnostics remained present;
- the known stale-lifecycle defect remained reproducible, as expected for a parity-only refactor.

Processed logs were moved out of the active raw folder in commit:

`ed01c2e4d9489d971c0635e76114d9bf85ffc9e0` — `Archive processed collision research logs`

`research/raw/` now contains only `Keep.txt`.

## Source Research — PrimaryFirst Lifecycle Candidate

Official SDK and tested Engine/Game binary evidence now identify a promising event layer:

- `eCVisualAnimation_PS::PlayMotion` — Engine RVA `0x30860`;
- `eCVisualAnimation_PS::StopMotion` — Engine RVA `0x30980`;
- `eCVisualAnimation_PS::StopAtLoopEnd` — Engine RVA `0x309D0`;
- motion type `0` is the same PrimaryFirst slot used by the validated v0.20 probe;
- `Game.dll` imports the higher-level `eCVisualAnimation_PS::PlayMotion`, `StopMotion`, and `StopAtLoopEnd` paths;
- `eCVisualAnimation_PS::PlayMotion` delegates to `eCWrapper_emfx2Actor::PlayMotion`, whose implementation can stop an existing motion before starting its replacement;
- `StopAtLoopEnd` is **not** an end event: its wrapper implementation schedules stopping at a future loop boundary.

Therefore `PlayMotion(type 0)` is a strong candidate immediate start/replacement event, while `StopMotion(type 0)` is a useful explicit-stop event. Neither is yet proven sufficient for every natural Hit end.

`eCVisualAnimation_PS` inherits `GetEntity()`, so the high-level hooks can identify their owning actor/entity directly.

## Immediate Next Step — Step B1

Do **not** implement production cleanup yet.

The next bounded coding task is a diagnostic-only PrimaryFirst hook probe:

1. add one authoritative hook for `eCVisualAnimation_PS::PlayMotion` at Engine RVA `0x30860`;
2. add one authoritative hook for `eCVisualAnimation_PS::StopMotion` at Engine RVA `0x30980`;
3. log only motion type `0` / PrimaryFirst;
4. capture compact before/after PrimaryFirst snapshots around the original call;
5. keep the existing read-only `OnTick` lifetime probe unchanged as a temporary comparator;
6. do not hook `StopAtLoopEnd` in this first probe;
7. do not add lifecycle-control state, cleanup behavior, attack-family exceptions, or production decisions.

After Work implements and pushes this bounded probe, normal Chat/home PC will build and run only:

- one known-good lifecycle;
- one known stale Whirl or Dual Quick lifecycle.

Question to answer:

> Does every actual Hit end/replacement seen by the old PrimaryFirst comparator correlate immediately with `PlayMotion(type 0)` and/or `StopMotion(type 0)`?

If yes across controlled cases, the direct events can replace polling in a later step. If not, investigate the missing natural-end path before adding more architecture.

## Chat / Work Execution Model

```text
Chat: design / evidence / freeze one bounded code task
        ↓
Work: source implementation/refactor + targeted review + commit/push + STOP
        ↓
Chat + home PC: sync / build / runtime test / interpret logs
        ↓
Chat: update evidence/docs and choose next code task
```

Routine build verification, runtime testing, log interpretation, documentation, evidence consolidation, and next-step planning stay in Chat/local testing by default.

Keep this file short. Update it only when the active problem, validated checkpoint, or immediate next step materially changes.
