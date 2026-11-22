# Diagnostic-only full-production Hack transition observation twin.
# Never load together with Script_G3AnimationBehaviors.dll or other G3AB probes.
set(G3AB_PROD_SOURCE "${PROJECT_SOURCE_DIR}/src/Script_G3AnimationBehaviors")
set(G3AB_HACK_TRANSITION_PROBE_SOURCES
    "${G3AB_PROD_SOURCE}/Script_G3AnimationBehaviors.cpp"
    "${G3AB_PROD_SOURCE}/AttackMotionRouting.cpp"
    "${G3AB_PROD_SOURCE}/AttackMovement.cpp"
    "${G3AB_PROD_SOURCE}/AttackRaise.cpp"
    "${G3AB_PROD_SOURCE}/AttackSpeed.cpp"
    "${G3AB_PROD_SOURCE}/BehaviorProfiles.cpp"
    "${G3AB_PROD_SOURCE}/CollisionLifecycleGuard.cpp"
    "${G3AB_PROD_SOURCE}/CollisionSourceOperations.cpp"
    "${G3AB_PROD_SOURCE}/CollisionSources.cpp"
    "${G3AB_PROD_SOURCE}/EngineBridge.cpp"
    "${G3AB_PROD_SOURCE}/EquippedSprintCollision.cpp"
    "${G3AB_PROD_SOURCE}/FrameCollisionMarkers.cpp"
    "${G3AB_PROD_SOURCE}/PhysicalFistCollision.cpp"
    "${G3AB_PROD_SOURCE}/Raw8FistCollision.cpp"
    "${G3AB_PROD_SOURCE}/RuntimeClock.cpp"
    HackTransitionProbe.cpp
    HackTransitionProbe.h
)
add_library(Script_G3AB_HackTransitionProbe SHARED ${G3AB_HACK_TRANSITION_PROBE_SOURCES})
target_include_directories(Script_G3AB_HackTransitionProbe PRIVATE "${G3AB_PROD_SOURCE}" "${CMAKE_CURRENT_SOURCE_DIR}")

# Separate, explicitly gated causal intervention twin for the verified player 2H fixture.
# Existing observation-only target above remains unchanged.
add_library(Script_G3AB_HackRecoverCausalProbe SHARED ${G3AB_HACK_TRANSITION_PROBE_SOURCES})
target_include_directories(Script_G3AB_HackRecoverCausalProbe PRIVATE "${G3AB_PROD_SOURCE}" "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Script_G3AB_HackRecoverCausalProbe PRIVATE g3sdk::SDK)
target_gothic_script_options(Script_G3AB_HackRecoverCausalProbe)
target_compile_definitions(Script_G3AB_HackRecoverCausalProbe PRIVATE G3AB_HACK_TRANSITION_PROBE=1 G3AB_HACK_RECOVER_CAUSAL_PROBE=1)

# Separate research twin: forced absence at the existing Recover resource
# callsite after a verified outgoing player 2H Hack Hit. No asset edits.
add_library(Script_G3AB_HackMissingRecoverProbe SHARED
    ${G3AB_HACK_TRANSITION_PROBE_SOURCES}
    HackMissingRecoverProbe.cpp
    HackMissingRecoverProbe.h)
target_include_directories(Script_G3AB_HackMissingRecoverProbe PRIVATE
    "${G3AB_PROD_SOURCE}" "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Script_G3AB_HackMissingRecoverProbe PRIVATE g3sdk::SDK)
target_gothic_script_options(Script_G3AB_HackMissingRecoverProbe)
target_compile_definitions(Script_G3AB_HackMissingRecoverProbe PRIVATE
    G3AB_HACK_TRANSITION_PROBE=1 G3AB_HACK_MISSING_RECOVER_PROBE=1)

target_link_libraries(Script_G3AB_HackTransitionProbe PRIVATE g3sdk::SDK)
target_gothic_script_options(Script_G3AB_HackTransitionProbe)
target_compile_definitions(Script_G3AB_HackTransitionProbe PRIVATE G3AB_HACK_TRANSITION_PROBE=1)
