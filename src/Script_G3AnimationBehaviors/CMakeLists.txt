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

        SharedConfig.cpp
        SharedConfig.h

        AttackRaise.cpp
        AttackRaise.h

        AttackSpeed.cpp
        AttackSpeed.h
)
