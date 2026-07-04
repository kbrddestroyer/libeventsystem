project (eventsystem_unit_tests LANGUAGES CXX) 

list_all_sources(_SOURCES)
add_executable(${PROJECT_NAME}_target ${_SOURCES})
target_link_libraries(${PROJECT_NAME}_target PRIVATE eventsystem GTest::gtest GTest::gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND $<TARGET_FILE:${PROJECT_NAME}_target>)
