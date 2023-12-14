# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(./lib/googletest/include ./lib/googletest)

add_executable(mps_tests constructor_tests.cpp)

target_link_libraries(mps_tests mps_lib)
target_link_libraries(mps_tests gtest gtest_main)