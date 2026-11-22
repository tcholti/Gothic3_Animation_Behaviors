# Diagnostic-only full-production Hack transition observation twin.
# Never load together with Script_G3AnimationBehaviors.dll or other G3AB probes.
set(G3AB_PROD_SOURCE "${PROJECT_SOURCE_DIR}/src/Script_G3AnimationBehaviors")
add_library(Script_G3AB_HackTransitionProbe SHARED
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
target_include_directories(Script_G3AB_HackTransitionProbe PRIVATE "${G3AB_PROD_SOURCE}" "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Script_G3AB_HackTransitionProbe PRIVATE g3sdk::SDK)
target_gothic_script_options(Script_G3AB_HackTransitionProbe)
target_compile_definitions(Script_G3AB_HackTransitionProbe PRIVATE G3AB_HACK_TRANSITION_PROBE=1)
