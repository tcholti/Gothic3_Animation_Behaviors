function(add_badblock_research_target target_name protection_mode)
    add_library(${target_name} SHARED)

    target_link_libraries(
        ${target_name}
        PRIVATE
            g3sdk::SDK
    )

    target_compile_definitions(
        ${target_name}
        PRIVATE
            G3AB_BADBLOCK_PROTECTION_MODE=${protection_mode}
    )

    target_gothic_script_options(
        ${target_name}
    )

    target_tree_sources(
        ${target_name}
        PRIVATE
            Script_G3AB_BadBlockResearch.cpp
            BadBlockProtectionResearch.cpp
            BadBlockProtectionResearch.h
    )
endfunction()

# Same hook/classifier/logger source for a strict A/B comparison.
# CONTROL preserves raw; PROTECTION returns 2500 only for the frozen predicate.
add_badblock_research_target(Script_G3AB_BadBlockResearch_Control 0)
add_badblock_research_target(Script_G3AB_BadBlockResearch 1)


add_library(Script_G3AB_BadBlockExclusionProbe SHARED)

target_link_libraries(
    Script_G3AB_BadBlockExclusionProbe
    PRIVATE
        g3sdk::SDK
)

target_compile_definitions(
    Script_G3AB_BadBlockExclusionProbe
    PRIVATE
        G3AB_BADBLOCK_PROTECTION_MODE=0
        G3AB_BADBLOCK_EXCLUSION_PROBE=1
)

target_gothic_script_options(
    Script_G3AB_BadBlockExclusionProbe
)

target_tree_sources(
    Script_G3AB_BadBlockExclusionProbe
    PRIVATE
        Script_G3AB_BadBlockResearch.cpp
        BadBlockProtectionResearch.cpp
        BadBlockProtectionResearch.h
)
