cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)
project (libeventsystem)

if (POLICY CMP0140)
    cmake_policy(SET CMP0140 NEW)
endif()

include (cmake/build-utils.cmake)

include_directories("${CMAKE_HOME_DIRECTORY}/source")
include_directories(include)

add_all_subdirs()
