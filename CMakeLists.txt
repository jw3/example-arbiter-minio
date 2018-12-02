cmake_minimum_required(VERSION 3.8)
project(arbiter_example)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
string(APPEND CMAKE_SHARED_LINKER_FLAGS " -Wl,--no-undefined")

include(version)
file(WRITE ${CMAKE_BINARY_DIR}/NAME ${CMAKE_PROJECT_NAME})

option(METADATA_ONLY "Write project metadata and exit" OFF)
if (METADATA_ONLY)
    return()
endif ()

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS TARGETS)
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(PDAL_VERSION_MAJOR 1)
set(PDAL_VERSION_MINOR 6)
find_package(PDAL "${PDAL_VERSION_MAJOR}.${PDAL_VERSION_MINOR}.0" REQUIRED CONFIG)

find_package(Threads REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

include(BuildInfo)

set(PLUGIN_IMPL pdal_plugin_filter_${CMAKE_PROJECT_NAME})
set(PLUGIN_TESTS pdal_plugin_filter_${CMAKE_PROJECT_NAME}_test)

include_directories(src)

add_subdirectory(src)

option(WITH_TESTS "enable tests to build" ON)
if (WITH_TESTS)
    add_subdirectory(test)
endif ()

option(WITH_PACKAGING "enable cpack packaging" OFF)
if (WITH_PACKAGING)
    include(cpack)
endif ()
