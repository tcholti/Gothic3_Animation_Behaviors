# Bad block skip attack protection — advisory static research and options

Date: 2026-10-07. Decision authority: advisory only.

Required development HEAD verified: 779488fc82c0233875ef3cdd73f362d0efd5dfa2.
Stable main verified: e899f37092706a9846312b93d6b52b34e715b53d.

The strongest minimal player candidate is a branch-local, stateless duration adapter. It is technically viable under ADR-0012. It does not preserve remaining block time, which this contract explicitly does not require. Neither release disposition nor integrated-versus-optional packaging is decided here.

The NPC timeout is separate. Static inspection establishes the callback lifetime and timeout condition, but does not establish a same-actor attack entry that preserves that callback. NPC overlap is unresolved, not disproved.

## Scope and evidence limits

Read at the required commit: root README, SESSION_ENTRYPOINT, BETWEEN_CHATS, active BAD_BLOCK_SKIP_ATTACK_PROTECTION_OPTIONS task, ADR-0012, WORK_IMPLEMENTATION_PROTOCOL, SOURCE_HOOK_GUIDE §6, the isolated research target, and the relevant EV-185–198/EV-448 evidence. FEATURE_DEVELOPMENT_METHOD was read as routed by the protocol.

The research target contains startup/unload logging and no hooks. Production source is unchanged between the preceding research checkpoint and this required HEAD.

Desktop Commander reported the authorized workstation offline. This session re-disassembled retained binary slices from the preceding read-only inspection; it did not freshly read or hash the installed DLLs. Therefore installed/live binary and New Balance versions are not newly certified.

EV-448 associates the tested Script_Game.dll with SHA256:
4D29189281EC26EAC7C704FA67ED323DF5C090D50B068626CF600AECF4262A24.

Retained slice provenance used here:

| Slice | Start RVA | SHA256 |
|---|---:|---|
| use2.bin | Script_Game +0x62FF0 | 28685b982aff5a79dc94472c72395c270eb6331f24b20e1259fa8813cdffdfdf |
| slice_0x46d80.bin | Script_Game +0x46D80 | 1f577afa67152ae0ebd526a5495af26d7a33e4287a48e5f50f264b98d40bdb2b |
| slice_0x46810.bin | Script_Game +0x46810 | 4afcd7f24b6615d175954742392a95253ec696473b053afa47d29c64539b0234 |
| slice_0x17c00.bin | Script_Game +0x17C00 | 4f21bba80ba4ee471c27789118f92d2fb1eb4a238c89c31bde8a707b44930eac |
| game_0x16ee40.bin | Game +0x16EE40 | f89735afd5e344096fcddb7690636e75e97bcd4499f2a73d7e9c39e478ef0789 |

No repository source, research-target source, or documentation was edited. No hooks/probes were created. No build, deployment, game execution, debugger attachment, runtime logging, or binary patching occurred.

## PLAYER DEFERRAL

### Exact seam and ABI

Retained x86 instructions confirm:

~~~text
Script_Game +0x633BB  lea ecx,[esp+0x58]
            +0x633BF  FF 15 90 49 0E 10
                        call [Script_Game IAT +0xE4990]
            +0x633C5  cmp eax,2500
            +0x633CA  jbe +0x63586
otherwise:
            +0x633F1  call PSRoutine::FullStop
            +0x63409  call PSRoutine::SetState("PS_Melee_Loop")
~~~

The getter is PSCharacterControl::PropertyDurationPressedMSecs::operator unsigned long() const. On this Win32 ABI it is a zero-explicit-argument __thiscall, with the property receiver in ECX and an unsigned 32-bit result in EAX. There is no floating-point return or hidden result buffer.

The six-byte indirect call must be replaced as a whole. The SDK mCCallHook decoder obtains the instruction's actual size; this call requires no relocation of the following comparison. Normal continuation is +0x633C5. EAX carries the adapter's effective value into the existing unsigned comparison. The comparison establishes its own flags; the adapter need not preserve getter-produced flags. Preserve normal callee-saved registers and stack balance.

### Receiver and exact actor identity — correction to the earlier report

The receiver is the CharacterControl wrapper embedded in the helper's resolved Self Entity. The helper constructs that local Entity at stack +0x18; its CharacterControl member is +0x40 within Entity, hence the receiver at +0x58.

The wrapper's stored pointer is an engine property-set pointer. Obtain the owning actor through eCEntityPropertySet::GetEntity(). Do not cast that stored word directly to eCEntity*.

This distinction is supported by:
- Entity's PS member layout;
- EntityPropertySet::m_pEngineEntityPropertySet;
- GetProperty's reinterpretation of the existing PS wrapper;
- eCEntityPropertySet's public GetEntity accessor;
- the existing production use of actor.Routine.m_pEngineEntityPropertySet -> GetSPU;
- pinned New Balance's active SetLastHit wrapper using PSNpc's engine property set -> GetEntity.

The property macro base uses the confusing protected name m_pEngineEntity; that name is not a reason to bypass the PS wrapper's actual stored-property-set representation. The earlier report's suggestion of treating the receiver word directly as an actor must be corrected before implementation.

The helper accepts explicit Self or resolves SPU Self. The adapter must use the receiver's owning actor. It must not substitute a global player or blindly use the helper's SPU Self. For a player-only policy, resolve this actor first, then check that this actor is the player.

### One mCCallHook can preserve the native operation exactly once

Use the SDK's stack-argument transport for ECX (AddThisArg / AddRegArg(Ecx)) and a __stdcall adapter accepting that receiver. Call the getter through a correctly typed __thiscall function pointer, which supplies the same receiver back in ECX.

Important SDK detail: mCCallHook does not infer or capture the original function target. Its default original pointer is null. It is not sufficient to call GetOriginalFunction after Prepare without supplying the target.

Two viable original-call transports:

1. Explicitly supply OriginalFunction using the resolved live IAT target before installation, then invoke it with a native __thiscall type and the original receiver. This is small, but assumes the IAT target will not change later.
2. Preferably read the existing IAT slot +0xE4990 on each adapter invocation, and call that current target exactly once with the original receiver. This preserves the original indirect-call semantics even if another DLL changes the getter's IAT target later.

Neither transport writes or hooks the shared IAT slot. The second avoids an unnecessary initialization-order assumption and does not need an additional hook, mCCaller, global receiver cache, or per-actor state.

Using AddThisArg passes ECX as a stack argument; it does not by itself call the original thiscall operation. The adapter's explicit native call performs that responsibility. Avoid shared GetSelf/register-storage hook modes.

### Smallest factual classifier and proposed scope

Read the resolved actor's current Routine.Action and GetCurrentAniPhase. This responsibility needs its own small predicate; do not reuse collision's Hit-only predicate or BehaviorProfiles.

Proposed ordinary-melee set:

| Actions | Values |
|---|---|
| Normal | 1 |
| Power | 2 |
| Quick / QuickR / QuickL | 3 / 4 / 5 |
| SimpleWhirl | 6 |
| Sprint | 9 |
| Full Whirl | 10 |
| Pierce | 11 |
| Hack | 14 |

Protect Raise (0), Hit (1), and Recover (3). Missing Raise assets do not prevent Hit protection. Do not narrow protection to currently armed collision or marked motions.

Sprint is factual Action9 even on a shared Power-named route. Both Action2 and Action9 are included; no profile/name translation is needed.

Use an explicit set, not an action-number range: TurnLeft/TurnRight at 7/8 must remain excluded. Parade, reactions, death, AbortAttack, locomotion, ranged and magic actions remain outside this proposed melee predicate.

JumpAttack (12), RamAttack (13), FinishingAttack (15), and GetUpAttack (30) are additional technically viable scope choices. They must be stated explicitly rather than silently excluded from a claim of protecting every factual attack. The same adapter can include them in Raise/Hit/Recover without new hooks/state, but eligibility at this seam and any special phases need evidence. This report recommends the ordinary set for the first mechanism experiment, not a final product exclusion of the special attacks.

### Effective result and expected behavior

~~~text
raw = call current native IAT getter exactly once

if raw > 2500
   and receiver resolves to the intended player
   and factual action/phase is protected:
       effective = 2500
else:
       effective = raw
~~~

Only this call's return value changes. The native duration property remains untouched.

Returning exactly 2500 selects the existing jbe and bypasses the entire timeout consequence, including preceding parade-bookkeeping mutation, FullStop and SetState. Both attack-destroying operations are avoided together. No other FullStop, state replacement, reaction, release-input branch, or generic timer reader is intercepted.

Repeated/chained attacks are protected whenever the predicate is true at this seam. Phase/action gaps allow the native timeout to become eligible. Key release, new press, task changes and other native eligibility gates retain native ownership; no countdown or key-episode lifecycle is introduced.

After protection ends, the next eligible call returns raw. If raw is already over 2500, native teardown may occur immediately on that call. It does not automatically occur if the key was released, the native branch is no longer reachable, or another native gate prevents it.

### Cleanup opportunity and viable classifier variants

Recover protection gives the normal continuation an opportunity; phase exit alone does not prove that post-CombatMove cleanup has completed. EV-183/189/191/195/196 show that cleanup can belong to the suspended outer ScriptFunction. Therefore the minimal phase classifier is a candidate to validate, not proof of a universal cleanup-before-timeout invariant.

| Variant | Classification | Solves / limits | Hooks; actor state; cost | Evidence still needed |
|---|---|---|---|---|
| P1: action + Raise/Hit/Recover | POSSIBLE BUT IMPERFECT | Defers the proven player teardown during factual attack phases; exact cleanup tail and custom special phases are not guaranteed. | 1; none; O(1), queried only at the selected site, normally only once raw is overdue. | Receiver parity, vulnerable attack success, protection exit, reactions, chains, cleanup ordering. |
| P2: attack action regardless of phase | POSSIBLE BUT RISKY | Can cover a phase-exit gap while Action remains attack; can also defer indefinitely on a stale Action. | 1; none; O(1). | Action retirement on the tested stack. Pinned New Balance explicitly notes Action surviving across attack states, so action-only is not a reliable cleanup-completion proof. |
| P3: P1 plus a proven still-live outer attack ScriptFunction | POSSIBLE BUT IMPERFECT, stronger cleanup opportunity | Can protect the post-animation continuation until its native frame retires, without a new timer map. | 1; none; O(d) current native stack inspection, where d is live stack depth. | Exact eligible script frames, normal retirement, nested helpers/reactions, and replacement-stack behavior. EV-196 supports representative native Normal/Whirl/GetUp lifetimes, not every mod replacement. |

For P3, inspect current native context only; never persist argument/frame addresses as execution IDs. Use an explicitly evidenced active attack frame and non-null live arguments, not “some attack-named frame somewhere below a reaction.” A broad string search over old suspended frames could overprotect. It must not copy the collision guardian's acquisition/state/obligation machinery.

All three variants are removable and can use either eventual placement. Their assumptions and failure modes remain visible instead of treating unavailable ideal cleanup proof as grounds to discard the simpler candidates.

### Risks and compatibility

- Incorrect receiver interpretation could query the wrong object or crash; resolve via the engine property set.
- Wrong calling convention or five-byte handling of a six-byte call could corrupt execution.
- Stale/mismatched Action and phase can produce false protection or miss a live attack.
- P1 can release before the outer cleanup tail; P2 can hold too long; P3 can misclassify suspended/nested/modded frames.
- A timeout that destroys the continuation before this seam is reached cannot be repaired by this adapter.
- Other attack-teardown mechanisms remain native and are outside this fix.
- An unknown binary or another owner replacing these bytes requires a local unsupported/conflict result, not blind installation.
- A getter hook that depends on its original native return address will see a wrapper caller. Preserve its target and receiver, but do not promise compatibility with stack-sensitive unknown hooks.

Validate the expected call, IAT association, cmp and jbe before installation. Check the loaded build and selected seam. Existing-owner conflict should leave this intervention inactive. A module loading later can still overwrite the seam; no SDK hook can make competing patch ownership universally safe.

New state: no persistent actor/timer state. Only process-lifetime hook/slot metadata and bounded experiment logging.
New hook: exactly one player call-site hook.

## NPC OVERLAP

### Static status: unresolved

| Required proposition | Static result |
|---|---|
| OnAI_Parade can remain reachable | Established while _AI_Parade is suspended with its local callback in the live top native frame. |
| Same actor can enter a factual attack without losing/masking that callback | Not established by the inspected control flow. |
| StatePosition 1 and StateTime >2 can remain true | Established while that frame remains live; the cap is not conditioned on attack Action/phase. |
| Therefore timeout executes during a live attack | Conditional on the missing second proposition; not proven. |

_AI_Parade establishes Parade Action16 and submits Parade CombatMove requests. ZS_Attack_Parade waits for that ScriptFunction. Game +0x16EF30 stores local callbacks on the top frame; +0x16F4A0 dispatches the top frame's callback. ProcessScript dispatches the local callback while an instruction remains active (+0x16F23E / +0x16F24E), and also on relevant suspended-function paths (+0x16F3DB). This proves callback persistence during parade, not attack overlap.

The timeout itself has no Action or animation-phase guard. However, absence of a guard is not proof that the violating combination is reachable. Ordinary later attacks reached through SetState clear the old stack; a newly pushed top frame also masks the old top-frame callback. Pinned New Balance's ZS_Attack_Loop chooses attack states through SetState. Its _AI_Parade wrapper updates block timestamps and calls the original. None of those inspected routes proves a retained Parade callback during a live attack.

These facts narrow the uncertainty. They do not prove universal impossibility across all native entry paths, asynchronous reactions, third-party changes, or a different installed stack.

### Exact smallest observation-only probe

One mCCallHook at Script_Game +0x46F39, immediately before the native PSRoutine::StopAIGoto import call through IAT +0xE4428.

ABI: native void __thiscall, receiver in ECX, no explicit stack arguments. ECX is the resolved Self's PSRoutine wrapper. Capture that receiver and the OnAI_Parade callback's SPU argument from EBP+0x08. Resolve actor through the receiver's engine Routine property set; obtain its GetSPU and verify it matches the captured callback SPU.

Read all evidence before StopAIGoto. Then call the current original IAT target exactly once, unchanged receiver, and continue normally to +0x46F3F, including the subsequent SetState at +0x46F51. No callback suppression, timing writes or result changes.

Location: only tools/Script_G3AB_BadBlockResearch/. No generic SetState/FullStop hook.

Minimum record:

| Field | Reason |
|---|---|
| Fixed event kind identifying +0x46F39; ordinal | Establishes selected native timeout site and log order. |
| Actor instance; callback SPU; owning SPU match | Prevents cross-actor correlation. |
| Routine Action; current phase | Records proposed factual classifier. |
| Current state; StatePosition; StateTime | Confirms the timed state and threshold. |
| Top native frame: script name, state/function flag, local callback, break block, arguments pointer | Establishes currently live callback/continuation context. Addresses are local observations, not durable IDs. |
| m_pfInstrCallback; conditional persisted CombatMove Action at SPU+0x154 | Distinguishes a real active CombatMove from an old attack-looking motion or a stale Routine Action. Read +0x154 only when the instruction is the known CombatMove callback. |

If no CombatMove is active but an attack ScriptFunction is still live in a cleanup continuation, add only that identified active frame's context needed to prove it. Do not emit full stacks, inventories, collision tables, all actors or animation catalogues.

No repeated Alternative-AI flag or global-player field is needed when installation validates the exact enclosing predicates; this site is already after those native gates. Negative/control samples should still be retained within a small cap. File handle, ordinal and cap are diagnostic process state, not gameplay state.

One positive record is sufficient for the existential overlap question if it shows this exact branch selected for the same actor with a factual live attack instruction or an evidenced live attack continuation. A raw Action/phase match without live continuation context is weaker and should not be called definitive. Static SetState semantics then establish the impending continuation destruction; visual reproduction or HP damage is not needed to establish reachability. One positive record does not certify all actors, all stacks or final patch efficacy. Zero positives in a finite run does not prove impossibility.

### Viable later NPC adapter if overlap is proven

A narrow sibling result adapter at Script_Game +0x46F21 can call the native StateTime getter once and return 2.0f only for an overdue protected NPC attack. Native floating-point comparison then takes jbe +0x46F57 and bypasses both StopAIGoto and SetState.

This is POSSIBLE BUT IMPERFECT / CONDITIONAL ON OVERLAP EVIDENCE:
- solves that separate NPC timeout, not all NPC interruptions;
- one NPC hook, zero actor timer state, O(1) with P1;
- uses a native float return in x87 ST0, not player's integer EAX ABI;
- requires receiver/return/branch parity verification and NPC protection-exit evidence;
- retains generic StateTime and other NPC decisions;
- is removable;
- shared policy is possible, shared timer/seam is not.

The +0x46F39 observer is not itself an adapter that suppresses only StopAIGoto: doing that would leave destructive SetState intact.

## RESEARCH DLL DESIGN

Minimum first player experiment:

| File | Responsibility |
|---|---|
| Existing Script_G3AB_BadBlockResearch.cpp | Script lifecycle, bounded log sink, native-load/seam verification, one physical player call hook, receiver/native-call transport. |
| New BadBlockProtection.h / .cpp | The small factual classifier and branch-local effective-duration policy. No hook installation, maps or collision ownership. |
| Existing CMakeLists.txt | Register those source files only. |

If the NPC observation is selected later, add a small NpcTimeoutObservation owner for evidence capture and one NPC transport adapter. Do not pre-create it solely for symmetry.

Hook ownership: this research DLL owns only its selected timeout call sites, once each. It consumes no production hook, C1 generation or profile state.
Policy ownership: BadBlockProtection; observation does not decide production semantics.
Must remain absent: Collision guardian/ownership, Raw8/Raw55/EquippedSprint policy, Speed, Raise, Movement, BehaviorProfiles, global input timing mutation, exact-pause maps, polling, broad hooks and unrelated diagnostics.

Removal means physically omitting the research DLL on a later launch. Do not promise hot unloading during gameplay. The SDK's restorable-hook mechanism does not remove the need for safe module lifetime and single ownership.

## OPTION A — later integrate into G3AB

Pros:
- one installation and one eventual hook owner;
- no second runtime DLL for users;
- independent timeout policy can live in a small permanent feature owner;
- existing diagnostics and native-load transport can be reused when appropriate.

Risks:
- a new physical hook and predicate become part of the protected production candidate;
- a stale classifier or bad ABI affects the full production DLL;
- research and production owners must never both patch +0x633BF;
- integrated release review must cover interaction with collision lifecycle and normal state transitions.

Estimated scope:
- later create BadBlockProtection.h/.cpp;
- one narrow transport/delegation in EngineBridge.cpp;
- add the source to production CMake;
- one player hook; no actor timer state for P1;
- optional second hook only if NPC evidence authorizes that responsibility;
- port no experiment logs, control modes, bootstrap or unused observers.

Existing Collision/Speed/Raise/Movement sites are physically different. Deferral prevents this selected teardown; their legitimate reaction/cleanup hooks still run normally on other paths. Compatibility is supported by separation of surfaces, not runtime-certified.

Maintenance: one build/package and one main owner, but the production regression matrix expands.

## OPTION B — later optional standalone DLL

Pros:
- G3AB remains byte/source unchanged while this fix is tested and optionally installed;
- users can independently install/remove the behavior;
- can operate with native collision behavior and does not require G3AB;
- final scope can remain one small timeout patch.

Risks:
- a second installation/version choice and explicit removal instructions;
- duplicate integrated-plus-standalone installation would conflict;
- script initialization must ensure Script_Game is loaded and bytes validated;
- unknown third-party owners at the same call site remain conflicts regardless of filename load order;
- later IAT replacements are preserved by live-slot dispatch, but later call-site replacement cannot be made safe automatically.

Compatibility:
- no same-site G3AB hook is present in the pinned production source;
- inspected pinned New Balance FunctionHook/utility routes do not replace these timeout sites; _AI_Parade is a separate function-entry hook;
- generic input and StateTime remain untouched, preserving New Balance's other readers;
- New Balance can change factual action/state timing, so classifier and exit behavior still need its fixture;
- an installed version is not assumed identical to reference source.

Users who disable the Alternative-AI behavior responsible for these native branches can omit the patch. Do not equate an unrelated New Balance parry option with disabling these timeouts. When the native site is not selected, the adapter is naturally inert.

Estimated scope: retain a lean standalone bootstrap, one transport owner, one small policy owner, selected-build/site validation and one DLL. Strip experimental logs and control policy. Same hook/state/runtime costs as Option A for the same classifier. Maintenance needs a separate version/package and compatibility matrix, but removal has no G3AB production impact.

## OPTION C — no change

No new hooks, state, runtime cost, installation or compatibility burden. Stable main remains available.

Gameplay consequence: on the proven vulnerable player paths, timed block teardown can still discard the attack continuation while its animation remains visible. G3AB's collision guardian repairs stale collision; it does not recreate the abandoned hit/damage opportunity. This fallback therefore does not solve the stated gameplay goal. No-change remains a product choice rather than an inferred research decision.

## RECOMMENDED NEXT EXPERIMENT — exactly one step

Freeze one future isolated player P1 deferral experiment at +0x633BF in Script_G3AB_BadBlockResearch.dll.

The single changed variable is raw-versus-threshold return at this timeout call. Use the frozen initial CP + Alternative AI fixture, without G3AB or New Balance, with the same vulnerable Quick/full-Whirl control attacks. Keep native getter parity, receiver ownership, factual Action/phase and selected effective value observable at this seam. Verify visible attack/hit completion, overdue timeout after protection, and legitimate reaction control. No NPC intervention or extra global lifecycle hooks in that experiment.

Why: the player gameplay failure and destructive seam are already proven. This experiment directly tests the new acceptance contract with one hook and no actor timer state. It leaves both eventual product placements open. If the observed protection-exit gap matters, P3 remains a bounded refinement; it is not required to reject or obscure P1 in advance.

This is a recommendation for a later frozen task. It was not implemented or run.

## DECISION POINTS FOR USER + NORMAL CHAT

1. Whether to authorize that player P1 mechanism experiment, or prioritize the designed NPC observation instead.
2. Final protection scope: ordinary actions only versus the four named special melee actions and any evidenced special phases.
3. Whether observed P1 cleanup opportunity meets v1 acceptance, or to require the stateless live-frame extension.
4. Whether NPC evidence warrants its own adapter.
5. Final placement: integrate the minimum proven behavior, clean an optional standalone DLL, or keep no change.
6. Whether/when the accepted behavior belongs in the first release.

## Pinned source/evidence references

- [Active task](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/docs/work/active/BAD_BLOCK_SKIP_ATTACK_PROTECTION_OPTIONS.md)
- [ADR-0012](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/docs/decisions/ADR-0012-bad-block-skip-attack-protection-contract.md)
- [Source/hook guide](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/docs/SOURCE_HOOK_GUIDE.md)
- [EV-185–198](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/docs/archive/evidence/EVIDENCE_LEDGER_STEP_B.md)
- [EV-448 report](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/docs/archive/investigations/bad_block_skip_static_research_2026-10-06.md)
- [Research bootstrap](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/tools/Script_G3AB_BadBlockResearch/Script_G3AB_BadBlockResearch.cpp)
- [Production EngineBridge](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/779488fc82c0233875ef3cdd73f362d0efd5dfa2/src/Script_G3AnimationBehaviors/EngineBridge.cpp)
- [SDK Hook.h](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/util/RtPatch/include/g3sdk/util/Hook.h)
- [SDK Hook.cpp](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/util/RtPatch/src/Hook.cpp)
- [SDK property macros](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/g3/Script/include/g3sdk/Script/propertyset/gs_propertymacros.h)
- [SDK property access](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/g3/Script/include/g3sdk/Script/propertyset/gs_propertymacros.inl)
- [SDK Entity layout](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/g3/Script/include/g3sdk/Script/gs_entity.h)
- [SDK property-set owner access](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/g3/Engine/include/g3sdk/Engine/entity/ge_entitypropertyset.h)
- [SDK SPU/lifetime/instruction context](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/g3/Game/include/g3sdk/Game/script/ge_scriptprocessingunit.h)
- [SDK action/phase enums](https://github.com/Georgeto/gothic3sdk/blob/90bfd344de4510dda7ac9da7461cc7f1eac911f7/g3/Game/include/g3sdk/Game/GameEnum.h)
- [Pinned New Balance FunctionHook](https://github.com/Jackydima/gothic3sdk/blob/316d32406a133f8884e7e302752c35f66b4f54fc/scripts/Script_NewBalance/FunctionHook.cpp)
- [Pinned New Balance utility](https://github.com/Jackydima/gothic3sdk/blob/316d32406a133f8884e7e302752c35f66b4f54fc/scripts/Script_NewBalance/utility.cpp)
