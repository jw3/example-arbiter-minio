set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(arbiter STATIC arbiter.hpp arbiter.cpp)
target_link_libraries(arbiter PRIVATE ${CMAKE_THREAD_LIBS_INIT} curl)
target_compile_definitions(arbiter PRIVATE ARBITER_CURL=1)

# ------------------------------

add_library(${PLUGIN_IMPL} SHARED arbiter_example.hpp arbiter_example.cpp)
target_include_directories(${PLUGIN_IMPL} PRIVATE ${CONAN_INCLUDE_DIRS} ${PDAL_INCLUDE_DIRS})
target_link_libraries(${PLUGIN_IMPL} PRIVATE ${PDAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} arbiter)

install(TARGETS ${PLUGIN_IMPL}
        LIBRARY DESTINATION lib)

set_target_properties(${PLUGIN_IMPL} PROPERTIES
    VERSION ${FULL_VERSION_STRING}
    SOVERSION ${VERSION_MAJOR}
    CLEAN_DIRECT_OUTPUT 1)
