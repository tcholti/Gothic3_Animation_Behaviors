add_library(Script_SpeedCalibrationProbe SHARED)

target_link_libraries(Script_SpeedCalibrationProbe PRIVATE g3sdk::SDK)

target_gothic_script_options(Script_SpeedCalibrationProbe)

target_sources(
    Script_SpeedCalibrationProbe
    PRIVATE
        Script_SpeedCalibrationProbe.cpp
)
