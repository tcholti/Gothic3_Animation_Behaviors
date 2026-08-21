add_library(Script_CombatMoveLogger SHARED)

target_link_libraries(Script_CombatMoveLogger PRIVATE g3sdk::SDK)

target_gothic_script_options(Script_CombatMoveLogger)

target_tree_sources(Script_CombatMoveLogger
  PRIVATE
    Script_CombatMoveLogger.cpp
)