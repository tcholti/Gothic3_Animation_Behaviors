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
        Script_FrameCollisionTest.cpp
)
