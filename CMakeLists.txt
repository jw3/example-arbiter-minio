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

find_package(PDAL REQUIRED CONFIG)

find_package(Threads REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

include(BuildInfo)

set(PLUGIN_IMPL pdal_plugin_filter_${CMAKE_PROJECT_NAME})

include_directories(src)
add_subdirectory(src)

option(WITH_PACKAGING "enable cpack packaging" OFF)
if (WITH_PACKAGING)
    include(cpack)
endif ()
