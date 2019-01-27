set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(arbiter STATIC arbiter.hpp arbiter.cpp)
target_link_libraries(arbiter PRIVATE ${CMAKE_THREAD_LIBS_INIT} curl)
target_compile_definitions(arbiter PRIVATE ARBITER_CURL=1)

# ------------------------------

set(reader_name pdal_plugin_filter_arbiter_reader)
add_library(${reader_name} SHARED arbiter_reader.hpp arbiter_reader.cpp)
target_include_directories(${reader_name} PRIVATE ${CONAN_INCLUDE_DIRS} ${PDAL_INCLUDE_DIRS})
target_link_libraries(${reader_name} PRIVATE ${PDAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} arbiter)

install(TARGETS ${reader_name}
        LIBRARY DESTINATION lib)

set_target_properties(${reader_name} PROPERTIES
    VERSION ${FULL_VERSION_STRING}
    SOVERSION ${VERSION_MAJOR}
    CLEAN_DIRECT_OUTPUT 1)

# ------------------------------

set(writer_name pdal_plugin_filter_arbiter_writer)
add_library(${writer_name} SHARED arbiter_writer.hpp arbiter_writer.cpp)
target_include_directories(${writer_name} PRIVATE ${CONAN_INCLUDE_DIRS} ${PDAL_INCLUDE_DIRS})
target_link_libraries(${writer_name} PRIVATE ${PDAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} arbiter)

install(TARGETS ${writer_name}
        LIBRARY DESTINATION lib)

set_target_properties(${writer_name} PROPERTIES
                      VERSION ${FULL_VERSION_STRING}
                      SOVERSION ${VERSION_MAJOR}
                      CLEAN_DIRECT_OUTPUT 1)
