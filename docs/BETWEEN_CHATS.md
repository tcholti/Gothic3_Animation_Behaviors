# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Current bridge — SetCollisionGroup explicit-this transport failed extended runtime stability

- Universal-guard-first architecture remains authoritative. The held-Use2 bad abandonment remains a destructive stress case, not a production classifier, balance fix, or reason to alter Community Patch / Alternative AI / New Balance behavior.
- C1 physical repair remains **disabled**. Direct C1-O2 `RunScriptFunction` dispatch capture remains **suspended**. `RunScriptFunction` remains recursion-safe pure pass-through.
- AISetState and AIFullStop remain passed explicit-this `.ThisCall()` transport baselines.
- SetCollisionGroup implementation `fbb300065af2f9119531e06949eac59c2586a519` converted only that hook to explicit per-invocation `eCEntity *this` plus `.ThisCall()` while preserving the reviewed observation/retirement/C1/diagnostic ordering.
- That implementation passed source review, build, exact deploy/hash identity and isolated load/unload. Validated DLL SHA256: `C5D85C44A751C68BB956C2F1D6C9ABE6E889BDBB3363FDC328158F2933DA0397`.
- The extended gameplay stability gate then **crashed** after broad combat/interruption coverage. Therefore SetCollisionGroup explicit-this transport is **FAIL/CRASH**, not a validated transport baseline.

### Canonical runtime evidence

```text
research/raw/2026-08-29_c1_setcollisiongroup_recursion_safe_extended_gameplay_stability.log
SHA256: 91D15FD54A51B0DC4AC4067E776757F813B934FD236C295D0CD1F793E540DAD5
raw/crash evidence commit: c4de7f37d1b8f0844be05afc7fb2a42f09b29ce3

research/raw/ge3log9.log
research/raw/Lastlog_GE3.log

whole-run derived package:
research/derived/2026-08-29_c1_setcollisiongroup_recursion_safe_extended_gameplay_stability_large_log/
commit: 9dae0a03426101f572357f74700ed441a75b2fbb
```

Large-log retrieval is now a standard procedure. Use `docs/LARGE_LOG_EVIDENCE_PROCEDURE.md`; its project-default launcher is `tools/log_evidence/Build-LargeLogEvidencePackage.cmd`. The launcher handles process-only PowerShell execution-policy bypass and an absolute repository-derived output path.

### Whole-run result

Structured package counts include:

```text
ENGINE SetCollisionGroup: 307
C1 OFFENSE REQUEST: 130
C1 CLEANUP FULFILLED: 107
C1 FINALIZATION: 175
C1 INVARIANT WARNING: 7
AIFULLSTOP CALLSITE: 104
AISETSTATE CALLSITE: 510
COMBATMOVE FULLSTOP STACK: 60
```

There were **23 actual `WOULD_REPAIR` finalization source outcomes**. The earlier ad-hoc count of 24 included the startup banner text.

All seven C1 invariant warnings were the already-known `UNOWNED_PLAYER_OFFENSE_REQUEST` pre-CombatMove/GetUpAttack acquisition gap. No new binding/generation/null-argument invariant family was exposed by this run.

The large run preserved the established C1 classification matrix:

- clean/native cleanup paths fulfilled and did not become false repairs;
- pre-activation destructive interruptions did not become repair candidates;
- armed destructive abandonments became `WOULD_REPAIR`;
- inherited stale `7 -> 7` could be attributed to the new execution and later fulfilled by native cleanup;
- Dual Quick source ownership remained hand/source-specific — one reproduced QuickAttackL left LEFT stale/`WOULD_REPAIR` while RIGHT remained group 5/no outstanding obligation.

### Final crash sequence

The final destructive Staff Whirl used C1 generation 275 and physical source `Wrestling Staff_BBM` RIGHT.

Observed sequence:

```text
source 5 -> 7 offensive request
→ held-Use2 AIFullStop during live Whirl Hit (~2508 ms held)
→ AISetState to PS_Melee_Loop
→ C1 finalization:
   Outcome = WOULD_REPAIR
   ActualGroup = 7
   CleanupObserved = 0
   StillEquipped = 1
   PhysicalCollisionChanged = 0
→ ambient/movement resumes with the same Staff still group 7
→ no later native 7 -> 5 cleanup before log termination/crash
```

The User also directly observed that this stale armed state could damage actors by contact and collide with world objects while the weapon was simply carried during movement. Treat that world-object effect as direct runtime observation unless/until stronger engine/log evidence encodes it.

### Crash localization

Crash log:

```text
EXCEPTION_ACCESS_VIOLATION
Engine +0x225650
Script_FrameCollisionTest +0x10802
Script.dll +0x12F61
Game.dll +0x1604D3
EAX = FFFFFFFF at the fault
```

Tested Engine disassembly shows:

```text
Engine +0x225640  preceding getter-like routine begins
Engine +0x225650  mov eax,[eax+18h]   <-- crash
Engine +0x225660  SetCollisionGroup begins
```

The new SetCollisionGroup wrapper calls `a_pThis->GetCollisionGroup()` **before** invoking the native SetCollisionGroup original. Therefore current evidence strongly localizes the failure to an invocation where the explicit wrapper `this` / entity context is unsafe for that getter. This does **not yet prove** the exact calling-convention/member-hook object-context mechanism.

Canonical evidence statement: `docs/EVIDENCE_LEDGER_STEP_C.md` EV-201.

## Next Normal Chat responsibility — interpretive, not yet a frozen Work task

Resolve the SetCollisionGroup transport contradiction narrowly before any new runtime build:

1. inspect only the exact SDK/hook-builder/member-hook contract needed to explain why the reviewed explicit `eCEntity *this` transport can survive hundreds of calls yet reach an unsafe getter invocation;
2. compare against the previously runtime-stable legacy SetCollisionGroup transport and the already-passed AISetState/AIFullStop explicit-this cases;
3. decide the smallest justified transport response — likely restoration of the previously stable SetCollisionGroup transport unless a different correct explicit signature/context is concretely proven;
4. preserve every C1/marker/collision semantic and ordering invariant;
5. expose the proposed bounded correction to the User before freezing Work.

Do **not** restore C1-O2 dispatch capture, enable physical repair, alter markers, change held-Use2/2500-ms behavior, or mechanically convert StartEffect/PlayMotion/StopMotion as part of this reassessment.

No Work task is currently frozen.
