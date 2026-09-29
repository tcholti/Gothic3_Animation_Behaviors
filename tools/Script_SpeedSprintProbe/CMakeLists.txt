add_library(Script_SpeedSprintProbe SHARED)

target_link_libraries(Script_SpeedSprintProbe PRIVATE g3sdk::SDK)

target_gothic_script_options(Script_SpeedSprintProbe)

target_sources(
    Script_SpeedSprintProbe
    PRIVATE
        Script_SpeedSprintProbe.cpp
)
