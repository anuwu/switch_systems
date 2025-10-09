add_library(SWITCH utils.cpp label.cpp wire.cpp)
target_link_libraries(SWITCH INTERFACE ${EMP-TOOL_LIBRARIES})