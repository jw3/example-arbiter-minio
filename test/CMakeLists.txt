add_executable(${PLUGIN_TESTS} driver.cpp arbiter_exampleUnitTest.cpp)
target_include_directories(${PLUGIN_TESTS} PUBLIC ${CONAN_INCLUDE_DIRS} ${ROOT_DIR}/filter/src ${PDAL_INCLUDE_DIRS})
target_link_libraries(${PLUGIN_TESTS} PRIVATE CONAN_PKG::gtest ${PDAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${PLUGIN_IMPL})
