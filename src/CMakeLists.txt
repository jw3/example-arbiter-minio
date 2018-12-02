add_library(${PLUGIN_IMPL} SHARED arbiter_example.hpp arbiter_example.cpp)
target_include_directories(${PLUGIN_IMPL} PRIVATE ${CONAN_INCLUDE_DIRS} ${PDAL_INCLUDE_DIRS})
target_link_libraries(${PLUGIN_IMPL} PRIVATE ${PDAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ${PLUGIN_IMPL}
        LIBRARY DESTINATION lib)

set_target_properties(${PLUGIN_IMPL} PROPERTIES
    VERSION ${FULL_VERSION_STRING}
    SOVERSION ${VERSION_MAJOR}
    CLEAN_DIRECT_OUTPUT 1)
