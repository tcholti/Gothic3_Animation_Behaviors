# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — SESSION CHECKPOINT: C1 substrate stabilized; C1-O2 reassessment next

### Completed this session

C1 finalization source-liveness safety was implemented and independently reviewed.

```text
implementation: e7d81f7b3cd08199e10ad98a5270e0cc8167c748
validated DLL SHA256: E18C35894B5C813C80F30D51DF76972BF1B10011B7A102CE29551210E54303B5
isolated evidence commit: 0e31c9b12a6df3b05d85364de0688496e826d38c
extended evidence commit: 0f663562b15c2dfc3288b4856474912ce2820e26
```

Extended evidence package:

```text
research/derived/2026-08-30_c1_finalization_source_liveness_safe_setcollisiongroup_extended_gameplay_stability_large_log/
source SHA256: D6298DA4C7C490FC84BC2A4586CC92A2F8D1A5003B54CC734EC584FECF5CE72B
356,139 source lines
13,723 indexed events
~852.7 seconds runtime
992 ENGINE SetCollisionGroup
333 C1 FINALIZATION
235 AIFULLSTOP CALLSITE
147 COMBATMOVE FULLSTOP STACK
195 NATIVE CLEANUP CALL SITE
9 C1 INVARIANT WARNING
```

All nine invariant warnings inspected were the already-known `UNOWNED_PLAYER_OFFENSE_REQUEST` acquisition-gap family. No new invariant-warning family appeared.

The final deliberate stale-state stress case reached C1 finalization with:

```text
Outcome: WOULD_REPAIR
LivenessEstablished: 1
OutstandingBeforeFinalization: 1
ActualGroup: 7
CleanupObserved: 0
StillEquipped: 1
PhysicalCollisionChanged: 0
```

The log continued afterward without a later indexed cleanup for that final source.

### Gate conclusions

- AISetState explicit-this transport: PASS for tested extended stability.
- AIFullStop explicit-this transport: PASS for tested extended stability.
- SetCollisionGroup explicit-this transport: PASS for tested extended stability.
- C1 finalization source-liveness correction: PASS for tested stability.
- Physical repair remains disabled.
- Direct C1-O2 RunScriptFunction dispatch capture remains suspended/unresolved; its earlier crash must not be treated as solved automatically.
- The `LivenessEstablished=0` outstanding branch was not positively observed in this run, so runtime coverage of that exact branch is not claimed.

### Qualified user observations

- A reaction/knockdown sequence appeared to restore the source to its equipped collision state before a later GetUpAttack reactivated it. The exact cleanup owner was not isolated.
- Holster/draw appeared to restore the stale source. Treat this as an observation only; the causal mechanism is unproven.

---

# NEXT NORMAL CHAT RESPONSIBILITY

Perform a **C1-O2 reassessment from the stabilized substrate baseline**. This is Normal Chat reasoning/evidence work first, not a frozen Work task.

Answer, in order:

1. What remains unresolved from the original direct RunScriptFunction dispatch-capture crash in EV-199?
2. Does the now-validated surrounding substrate permit a source-supported minimal nesting-safe dispatch context without repeating the failed implementation?
3. If not, what narrower alternative can bind pre-CombatMove offense to the already-proven live outer ScriptFunction lifetime without making generic RunScriptFunction combat authority?
4. What smallest source/diagnostic gate should falsify the next candidate before physical repair is considered?

### Protected state

Do not enable physical repair, restore the old C1-O2 capture by assumption, roll back SetCollisionGroup, alter marker/source semantics, mechanically convert unrelated hooks, or treat the unobserved liveness-negative branch as runtime-proven.

The known destructive abandonment remains a stress case rather than production classification authority. Existing clean, reaction, pre-activation, inherited-state, source-side and no-repair controls remain protected.

No Work task is currently frozen.
