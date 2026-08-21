add_library(Script_FrameEffectLogger SHARED)

target_link_libraries(
    Script_FrameEffectLogger
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_FrameEffectLogger
)

target_tree_sources(
    Script_FrameEffectLogger
    PRIVATE
        Script_FrameEffectLogger.cpp
)
