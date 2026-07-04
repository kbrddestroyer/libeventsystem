#
# libeventsystem.a CMakeLists.txt
#

project (eventsystem LANGUAGES C CXX)

list_all_sources(_SOURCES)
add_library(${PROJECT_NAME} STATIC ${_SOURCES}) 
