include_directories(${CMAKE_BINARY_DIR}/include)
configure_file(${CMAKE_SOURCE_DIR}/src/BuildInfo.hpp.in ${CMAKE_BINARY_DIR}/include/BuildInfo.hpp)
