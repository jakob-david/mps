# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(./lib/googletest/include ./lib/googletest)

add_executable(mps_tests tests/mps_general.cpp
        tests/mps_calculation.cpp
        functions/functions.h
        tests/mps_comparators.cpp
        tests/mps_random.cpp
        tests/ira_general.cpp
        tests/ira_algorithms.cpp
        tests/ira_oparators.cpp)

target_link_libraries(mps_tests mps_lib)
target_link_libraries(mps_tests gtest gtest_main)