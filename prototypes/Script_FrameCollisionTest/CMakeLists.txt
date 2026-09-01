option(
    FRAME_COLLISION_ENABLE_DEEP_DIAGNOSTICS
    "Enable retained deep historical probes in Script_FrameCollisionTest"
    OFF
)

set(
    FRAME_COLLISION_BEHAVIOR_SOURCES
    CollisionLifecycleGuard.cpp
    CollisionLifecycleGuard.h
    CollisionSourceOperations.cpp
    CollisionSourceOperations.h
    CollisionSources.cpp
    CollisionSources.h
    EngineBridge.cpp
    EngineBridge.h
    FrameCollisionMarkers.cpp
    FrameCollisionMarkers.h
    FrameCollisionShared.h
    RuntimeClock.cpp
    RuntimeClock.h
    Script_FrameCollisionTest.cpp
)

add_library(Script_FrameCollisionBehaviorTest SHARED)

target_link_libraries(
    Script_FrameCollisionBehaviorTest
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_FrameCollisionBehaviorTest
)

target_tree_sources(
    Script_FrameCollisionBehaviorTest
    PRIVATE
        ${FRAME_COLLISION_BEHAVIOR_SOURCES}
)

add_library(Script_FrameCollisionTest SHARED)

target_link_libraries(
    Script_FrameCollisionTest
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_FrameCollisionTest
)

target_compile_definitions(
    Script_FrameCollisionTest
    PRIVATE
        FRAME_COLLISION_DIAGNOSTICS=1
)

if(FRAME_COLLISION_ENABLE_DEEP_DIAGNOSTICS)
    target_compile_definitions(
        Script_FrameCollisionTest
        PRIVATE
            FRAME_COLLISION_DIAGNOSTICS_DEEP=1
    )
endif()

target_tree_sources(
    Script_FrameCollisionTest
    PRIVATE
        ${FRAME_COLLISION_BEHAVIOR_SOURCES}
        CollisionDiagnostics.cpp
        CollisionDiagnostics.h
        CollisionDiagnosticsDeep.cpp
        CollisionDiagnosticsDeep.h
)
