add_library(Script_G3AnimationBehaviors SHARED)

target_link_libraries(
    Script_G3AnimationBehaviors
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_G3AnimationBehaviors
)

target_tree_sources(
    Script_G3AnimationBehaviors
    PRIVATE
        Script_G3AnimationBehaviors.cpp
        AttackMotionRouting.cpp
        AttackMotionRouting.h
        AttackMovement.cpp
        AttackMovement.h
        AttackRaise.cpp
        AttackRaise.h
        AttackSpeed.cpp
        AttackSpeed.h
        BehaviorProfiles.cpp
        BehaviorProfiles.h
        CollisionLifecycleGuard.cpp
        CollisionLifecycleGuard.h
        CollisionSourceOperations.cpp
        CollisionSourceOperations.h
        CollisionSources.cpp
        CollisionSources.h
        EngineBridge.cpp
        EngineBridge.h
        EquippedSprintCollision.cpp
        EquippedSprintCollision.h
        FrameCollisionMarkers.cpp
        FrameCollisionMarkers.h
        FrameCollisionShared.h
        PhysicalFistCollision.cpp
        PhysicalFistCollision.h
        Raw8FistCollision.cpp
        Raw8FistCollision.h
        RuntimeClock.cpp
        RuntimeClock.h
)
