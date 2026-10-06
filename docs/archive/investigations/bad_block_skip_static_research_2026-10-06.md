# Bad block skip: static research and architecture recommendation

Research date: 2026-10-06. Scope: the frozen read-only task at development commit 185989059519e09782755ec9faa4644517975567.

**Verdict: NOT CLEAN ENOUGH FOR FIRST RELEASE for the requested exact remaining-time pause.**

The exact player intervention seam is now recovered. NPC parade also has a proven timeout, but it uses a different actor/SPU clock and a different branch. One narrow player call-site hook can defer the destructive player branch. It cannot mathematically pause the timer or cover the NPC branch. A single later observation probe is justified to settle NPC attack overlap; that probe alone would not establish exact pause/resume ownership.

## Concise architecture result

| Requested item | Finding / recommendation |
|---|---|
| Existing timer owner | No G3AB bad-block countdown exists. Player: engine CharacterControl DurationPressedMSecs, consumed by Script_Game. NPC: native per-actor Routine/SPU StateTime, consumed by OnAI_Parade. |
| Existing lifecycle | Player condition is held Use2, native melee/parade gates, duration strictly greater than 2500 ms; the branch clears parade bookkeeping, FullStops the instruction, then SetStates PS_Melee_Loop. NPC condition is Alternative AI, non-player actor, StatePosition 1, StateTime strictly greater than 2.0 seconds; it calls StopAIGoto then SetState ZS_Attack_Loop. |
| Attack-active signal | Read the same resolved actor's factual Routine.Action and current animation phase at the seam. Ordinary melee attack families; Raise, Hit and Recover should all be protected. Existing collision Hit classification and configured AttackRaise continuation records are unsuitable lifetime owners. |
| Pause mechanism candidate | Exact pause would need a branch-local virtual elapsed clock: native elapsed minus elapsed belonging to protected attack intervals within the same timer episode. This is a new stateful responsibility, with boundaries not yet proven. |
| New hook required? | Yes: one narrow Script_Game call-site hook for the player deferral candidate. Existing production hooks occur too late to prevent both destructive operations without broader suppression. NPC intervention, if justified, would need its separate branch seam; the player call site never feeds it. |
| New persistent state required? | Deferral: no actor/timer state, only the hook object. Exact pause: yes; at least live actor/SPU identity plus timer-episode identity, native elapsed/reset tracking, accumulated excluded duration and open attack-interval tracking. Their authoritative lifecycle cannot yet be frozen. |
| Multi-actor safety | Stateless call-site policy reads its own actor and shares no timer data. Exact pause cannot use a global paused clock, raw pointer as durable episode identity, or collision generation as timer ownership. Death, removal and episode reset retirement remain prerequisites. |
| Compatibility | Preserve the original getter once, unchanged receiver; alter only this call's effective result. Leave CharacterControl, New Balance input handling, native reactions and accepted collision lifecycle intact. Compatibility is supported statically, not runtime-certified. |
| Blockers / uncertainties | Exact held-input episode/reset and attack interval boundaries; relation of native input time to QPC; NPC timeout overlapping a factual active attack under the tested mod stack; special attack-family scope. |
| Recommended smallest implementation | No production implementation is frozen for exact pause. If the contract explicitly changes to “defer this destructive player branch until the attack finishes,” use one stateless duration-call adapter at Script_Game +0x633BF. Keep policy in a dedicated feature owner and transport in EngineBridge. Do not silently substitute this behavior for pause/resume. |
| First-release disposition | Retain the stable fallback / existing behavior while exact pause remains unresolved. Do not expand into global timer mutation or two generic FullStop/SetState hooks. |

## Repository and tested-binary authority

The remote refs were verified again at conclusion:

- development: 185989059519e09782755ec9faa4644517975567.
- main: e899f37092706a9846312b93d6b52b34e715b53d.

Production source was inspected from the detached checkout at the required development commit. The Windows repository copy was older (dd5c30003bb3d165c143d44621755500c41e093f); it was not updated or used as the current production authority. Its official SDK and New Balance reference checkouts matched the pinned reference commits.

The actual tested installation was identified from LOCAL_WORKSTATION_PATHS.md and filesystem metadata, rather than the separate Modkit/editor copies:

    E:\SteamLibrary\steamapps\common\Gothic 3
    E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_Game.dll

| Inspected on-disk binary | SHA-256 |
|---|---|
| Script_Game.dll, 1,265,664 bytes | 4D29189281EC26EAC7C704FA67ED323DF5C090D50B068626CF600AECF4262A24 |
| Game.dll | 4728A47B244ADCB0EA2EC3501DB04994909DCFCFF338C7B8075F2B68DD8D6E00 |
| Script.dll | 03C483148D0EA88E007D2F18EAB30400A6012439EBBE4FEA6EBF837AA2ABD981 |

Static evidence below was recovered from read-only PE section/import/export/string inspection and targeted x86 disassembly of those files. Addresses are RVAs; absolute disassembly addresses used preferred image base 0x10000000. No game was launched or attached. On-disk inspection does not establish the currently loaded image or live New Balance version.

## Exact player seam

Script_Game import slot +0xE4990 resolves to:

    PSCharacterControl::PropertyDurationPressedMSecs::operator unsigned long() const

Recovered sequence:

    +633BB  8D 4C 24 58          lea ecx, [esp+58h]
    +633BF  FF 15 90 49 0E 10    call [IAT +E4990]  ; native duration getter
    +633C5  3D C4 09 00 00       cmp eax, 2500
    +633CA  0F 86 B6 01 00 00    jbe +63586         ; unsigned <= threshold
    +633D0  ...                 clear parade bookkeeping through helper +1D90
    +633F1  FF 15 EC 43 0E 10    call PSRoutine::FullStop
    +633F7  ...                 construct "PS_Melee_Loop"
    +63409  FF 15 FC 43 0E 10    call PSRoutine::SetState
    +63416  E9 A5 FB FF FF       jmp teardown helper +62FC0

The +63586 target runs the native local destruction/continuation path and continues the Use2 helper. It is not an arbitrary function return. Returning 2500 from the single getter call, only when the original duration is over threshold and this actor is factually attacking, lets the existing comparison bypass the whole harmful branch, including parade bookkeeping mutation.

The helper begins at +62FF0. Its resolved Self comes from either its supplied Entity or SPU Self; therefore the adapter must use the actor actually bound to the duration property, not assume a global player or blindly substitute SPU Self. The official property wrapper layout carries that engine Entity pointer. SDK mCCallHook supports receiver/register arguments and call-site interception; the final ABI adapter must preserve the exact receiver, native original call and EAX result contract. The native call is six bytes, not a guessed five-byte direct call.

The branch is gated before the getter by native task/input/parade/focus/Alternative-AI conditions. Consequently this seam is not a continuous observation of every attack interval or every key transition. Other duration getter call sites exist in the same DLL, including +62977, +62C2B, +62C6E, +63203, +6341B and +7D7F8. Intercepting the shared property getter or IAT slot globally would exceed the intended responsibility.

EV-185/186 establish that FullStop is real CombatMove termination and is also used by legitimate reactions. EV-187/190 establish this player caller for full Whirl and tested Quick configurations. EV-189/191 establish that the subsequent SetState destroys the suspended attack continuation. Hence suppressing only one downstream operation is insufficient. EV-192 through EV-196 concern accepted collision execution/source ownership; they do not supply a timer epoch. EV-197 is historical player timeout intent. EV-198's Raise reproduction boundary does not prove a Raise-based fix.

## Player timing owner and lifecycle limit

The official gCCharacterControl_PS property is an unsigned millisecond value at +0x28, alongside PressedKey and the pressed/before flags. In the tested Game.dll, gCCharacterControl_PS::OnAction at +0xDE480 copies incoming event data:

    Game +DE550   mov ecx, [edi+8]
    Game +DE55A   mov [esi+28h], ecx

This is input-event duration copied into generic CharacterControl state, not a plugin countdown advanced by G3AB. The same handler updates pressed-key and pressed/before fields. The inspected ClearVolatileFrameStates does not clear this duration field.

The task's active check requires held Use2 (EV-187: key 16, both flags true). Release, key changes or leaving native task/parade gates make this condition ineligible. The exact upstream hold-clock source, epoch-reset behavior and all unsampled transitions were not established by this bounded inspection. No public block-only pause/resume API was found. Writing +0x28 would not pause upstream input time and would be overwritten by later events.

Production RuntimeClock uses QueryPerformanceCounter. Equivalence to the engine input duration domain is unproven; it must not be substituted as an “exact” held-key clock.

## NPC ownership: separate and proven

Registration in the inspected Script_Game maps _AI_Parade to +0x46810, OnAI_Parade to +0x46D80 and ZS_Attack_Parade to +0x17C00.

_AI_Parade installs OnAI_Parade as its local callback, sets factual Action Parade (16), and starts its parade CombatMove. OnAI_Parade performs its initial StatePosition progression, then has this separate cap:

    +46EDD  Alternative AI setup flag enabled
    +46EEE  Entity::GetPlayer
    +46EF9  compare Self != player
    +46F12  read StatePosition
    +46F18  cmp eax, 1
    +46F21  call PSRoutine::GetStateTime
    +46F27  fld dword [image +107518]   ; recovered float 2.0
    +46F2F  fcomip                    ; StateTime versus 2.0
    +46F33  jbe +46F57               ; bypass when <=2.0
    +46F39  call PSRoutine::StopAIGoto
    +46F42  construct "ZS_Attack_Loop"
    +46F51  call PSRoutine::SetState

There is no DurationPressedMSecs read in this NPC timeout and no explicit FullStop call in this branch. Do not transfer the player's FullStop-based causal model to NPCs without evidence.

Routine StateTime is native SPU state elapsed time in seconds, advanced by ProcessScript (+0x16F120 in tested Game.dll). Its clock is shared by native state logic; writing or freezing it globally would also affect other AI decisions. The callback's StatePosition 0-to-1 progression does not call SetStateTime to start a fresh 2-second countdown.

Game +0x16EF30 installs a local callback in the top SPU state-stack frame. Game +0x16F4A0 dispatches that top-frame callback. ZS_Attack_Parade waits for its _AI_Parade function before continuing. These facts support a parade-owned callback lifetime; they do not prove that the callback cannot overlap a later attack in the actual mod stack. The cap itself has no action/phase guard.

| Required scope classification | Conclusion |
|---|---|
| Player timeout path | Proven, including historical attack abandonment at this caller. |
| NPC block/parade timeout path | Proven: Alternative-AI non-player StatePosition 1 / StateTime >2.0 seconds. |
| Same timer mechanism | No. Held input milliseconds versus actor/SPU state seconds. |
| Same single call-site fix covers both | No. Independent call sites and clocks. A classifier could be shared later; that is not shared timer ownership. |
| NPC timeout interrupting an active attack | Not proven. Native lifetime suggests ordinary parade ownership, but static inspection does not close live mod-stack overlap. |

## Attack signal and exact pause versus deferral

For a future deferral contract, use the same actor's factual Routine.Action with GetCurrentAniPhase. Protect ordinary Normal, Power, Quick/right/left, SimpleWhirl, Sprint, full Whirl, Pierce and Hack in Raise, Hit and Recover. Exclude parade, turn, reaction, locomotion and unrelated actions. Jump/Ram/Finishing/GetUpAttack need explicit scope decisions rather than silently inheriting protection.

Sprint must remain classified by factual Sprint Action 9 even when it shares the Power route. Requested animation names, profile settings, collision ownership and Hit-only marker state are not authority for this behavior. The existing GetCombatMoveFactualAction helper is used inside its known CombatMove context; its raw SPU field cannot be assumed to be a universally valid attack-lifetime record outside that context. Routine/phase can also lag a replacement boundary, so these are seam observations, not proof of exact attack start/end timestamps.

True pause requires effective elapsed = native elapsed - accumulated protected-attack elapsed, computed within one native timer episode. A 2500-ms timer with 100 ms remaining before a 600-ms attack must still have 100 ms remaining afterwards. A stateless “return 2500 while attacking” bypass leaves native held time running; once the attack ends, a raw 3000-ms result expires immediately. That is deferral, not pause. Restarting a fresh 2500 ms would also violate the frozen requirement.

The minimum logical state for an exact virtual clock includes identity/episode, native elapsed/reset observation, excluded duration and an open interval. No current production owner provides all of them. AttackRaise's map covers only configured injected Raise continuations. OnTick/motion/FullStop deep diagnostics are not general release lifecycle feeds. Using CombatMove/RunScriptFunction/AISetState to construct a new owner would require separately proving boundaries, holding through chained attacks, retiring cancellation/death/removal and detecting a new hold even when the native timeout getter is not reached. A single intermittent call-site sample cannot prove those properties.

## Safety and New Balance

A stateless player adapter has no per-actor map, no pointer reuse problem and no cleanup record to leak. Repeated/chained attacks remain protected while the factual classifier says active. When protection ceases, original held time applies immediately. It introduces only one original duration read plus narrow factual queries when the native site is reached, with no scan or independent per-frame polling. This describes candidate architecture, not completed acceptance testing.

For exact pause, actor removal/death, state reset, cancelled attack, input release/new press and chains need explicit episode retirement and clock rules. A global paused flag, global CharacterControl mutation or a new timer keyed solely by an engine pointer is not safe.

Pinned New Balance source was verified at **316d32406a133f8884e7e302752c35f66b4f54fc**. Its FunctionHook.cpp _AI_Parade wrapper updates block-related bookkeeping then calls the original. Its OnPlayerGameKeyPressed handling does not replace the native Use2 timeout. Its utility.cpp IsDoubleClick does read DurationPressedMSecs for other input behavior, which is a concrete reason to leave generic input timing untouched.

Only an exact native timeout-site intervention can honor the compatibility rule: if New Balance never reaches that site, do nothing; if it does, preserve all other native/input calls. The live installed New Balance DLL was not proven equivalent to the pinned reference source, and no runtime compatibility claim is made.

Accepted Collision, Raw8/Raw55/EquippedSprint, Speed, Raise, Movement, BehaviorProfiles and the shipping INI were not modified. A future timeout-deferral owner must be independent of their configuration and keep EngineBridge as transport. Existing collision safety remains responsible for legitimate termination; this candidate only prevents one selected destructive branch.

## Smallest justified later probe

One diagnostic-only observer around **Script_Game +0x46F39, the StopAIGoto call**, can answer whether the proven NPC cap is selected while a factual attack is still active.

Record before the original call: actor identity, SPU, Alternative-AI status, StatePosition, StateTime, factual Action/phase, current state, top live script/local callback, and persisted instruction/attack context. Preserve the exact original receiver, call it once, return unchanged and allow the following SetState. This location has already passed the native NPC timeout predicate and samples before either StopAIGoto or SetState can change context. An unfiltered generic SetState observer would be broader and later.

A positive record with a live attack continuation at this exact branch establishes overlap. A parade-only record is a negative control; absence of a positive record in a short run is not universal proof. This probe addresses NPC overlap only, not player key epochs or exact pause accounting. Normal Chat must freeze a later diagnostic task before creating, building or running it. No probe was created in this research task.

## Source routes and evidence links

- [Frozen task](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/185989059519e09782755ec9faa4644517975567/docs/work/active/BAD_BLOCK_SKIP_ATTACK_DEFER_TIMER_RESEARCH.md)
- [Source and hook authority](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/185989059519e09782755ec9faa4644517975567/docs/SOURCE_HOOK_GUIDE.md)
- [EV-185 through EV-198](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/185989059519e09782755ec9faa4644517975567/docs/archive/evidence/EVIDENCE_LEDGER_STEP_B.md)
- [Current EngineBridge](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/185989059519e09782755ec9faa4644517975567/src/Script_G3AnimationBehaviors/EngineBridge.cpp)
- [Current FrameCollisionMarkers](https://github.com/tcholti/Gothic3_Animation_Behaviors/blob/185989059519e09782755ec9faa4644517975567/src/Script_G3AnimationBehaviors/FrameCollisionMarkers.cpp)
- [Official SDK, pinned commit](https://github.com/Georgeto/gothic3sdk/tree/90bfd344de4510dda7ac9da7461cc7f1eac911f7)
- [New Balance FunctionHook reference](https://github.com/Jackydima/gothic3sdk/blob/316d32406a133f8884e7e302752c35f66b4f54fc/scripts/Script_NewBalance/FunctionHook.cpp)
- [New Balance utility reference](https://github.com/Jackydima/gothic3sdk/blob/316d32406a133f8884e7e302752c35f66b4f54fc/scripts/Script_NewBalance/utility.cpp)

The new static observations above are research findings, not new canonical EV entries or documentation commits. Production checkout is clean. No repository source/documentation edits, builds, deployment, binary changes, game execution, debugger attachment or runtime tests were performed.
