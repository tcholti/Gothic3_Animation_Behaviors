add_library(Script_FrameCollisionTest SHARED)

target_link_libraries(
    Script_FrameCollisionTest
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_FrameCollisionTest
)

target_tree_sources(
    Script_FrameCollisionTest
    PRIVATE
        CollisionControl.cpp
        CollisionControl.h
        CollisionDiagnostics.cpp
        CollisionDiagnostics.h
        CollisionLifecycleGuard.cpp
        CollisionLifecycleGuard.h
        CollisionSources.cpp
        CollisionSources.h
        FrameCollisionShared.h
        HookBridgeRuntime.cpp
        HookBridgeRuntime.h
        Script_FrameCollisionTest.cpp
)
