# Project Scope Context

**Project:** Gothic3_Animation_Behaviors  
**Purpose:** Provide concise factual context for technical Chat/Work prompts when engine-facing game-modding terminology could otherwise be ambiguous.

## Gothic 3 scope

> Context: authorized offline modding/reverse-engineering of the 2006 single-player game Gothic 3 using community SDK tooling. The target is the user's local game installation and our own mod DLL.

The project studies and modifies Gothic 3 animation/gameplay behavior for compatibility and modding purposes, including animation playback, CombatMove behavior, collision timing/source ownership, native action semantics, and related engine integration.

The work may legitimately use terms such as DLL hooks, RVAs, disassembly, call stacks, Win32 stack capture, binary inspection, call-site probes, and code patches. In this project those terms refer to the user's local copy of Gothic 3 and the project's own mod/research DLLs.

## Prompt rule

For Work or other technical prompts that involve binary inspection, disassembly, hooks, call-site tracing, stack capture, or patch-level engine research, place the Gothic 3 scope sentence near the beginning of the prompt when useful.

Do not replace accurate engineering terminology with euphemisms. The scope sentence exists to state the real context clearly, not to alter the technical task or bypass any safety rule.

For any **frozen Work implementation task**, Work must also read and follow `docs/FROZEN_WORK_TASK_RULES.md` before editing. A frozen task is implementation-only: missing semantic or architectural decisions must be returned to Normal Chat rather than invented in Work.

## Reuse in other projects

If another legitimate project later develops a similar ambiguity, create a short project-specific context statement for that project rather than copying Gothic 3-specific wording blindly. For example, UAA or future game-design/engine projects should describe their own actual artifacts, permissions, and targets.

Keep these context statements short and factual so they improve understanding without bloating routine prompts.
