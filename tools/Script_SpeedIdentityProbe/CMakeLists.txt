add_library(Script_SpeedIdentityProbe SHARED)

target_link_libraries(Script_SpeedIdentityProbe PRIVATE g3sdk::SDK)

target_gothic_script_options(Script_SpeedIdentityProbe)

target_include_directories(
    Script_SpeedIdentityProbe
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/Script_G3AnimationBehaviors
)

target_sources(
    Script_SpeedIdentityProbe
    PRIVATE
        Script_SpeedIdentityProbe.cpp
        ${PROJECT_SOURCE_DIR}/src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
        ${PROJECT_SOURCE_DIR}/src/Script_G3AnimationBehaviors/BehaviorProfiles.h
)
