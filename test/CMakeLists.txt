add_executable(test_label "test_label.cpp")
target_link_libraries(test_label SWITCH)

add_executable(test_wire "test_wire.cpp")
target_link_libraries(test_wire SWITCH ${EMP-TOOL_LIBRARIES})