add_library(Script_G3AB_BadBlockProtector SHARED)

target_link_libraries(
    Script_G3AB_BadBlockProtector
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_G3AB_BadBlockProtector
)

target_tree_sources(
    Script_G3AB_BadBlockProtector
    PRIVATE
        Script_G3AB_BadBlockProtector.cpp
)
