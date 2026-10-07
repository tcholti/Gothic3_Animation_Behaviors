add_library(Script_G3AB_BadBlockResearch SHARED)

target_link_libraries(
    Script_G3AB_BadBlockResearch
    PRIVATE
        g3sdk::SDK
)

target_gothic_script_options(
    Script_G3AB_BadBlockResearch
)

target_tree_sources(
    Script_G3AB_BadBlockResearch
    PRIVATE
        Script_G3AB_BadBlockResearch.cpp
        BadBlockProtectionResearch.cpp
        BadBlockProtectionResearch.h
)
