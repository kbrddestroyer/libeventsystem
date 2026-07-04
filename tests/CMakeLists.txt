project (UNIT_TESTS LANGUAGES CXX)

if (USE_UNIT_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()
    add_all_subdirs()
endif()