# 'Google_test' is the subproject name
project(Google_tests)

# 'python_tests' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(./lib/googletest/include ./lib/googletest)

add_executable(all_tests tests/mps_tests/mps_general.cpp
        functions/functions.h
        tests/mps_tests/mps_random.cpp
        tests/ira_tests/ira_general.cpp
        tests/ira_tests/ira_algorithms.cpp
        tests/ira_tests/ira_operators.cpp
        tests/mps_tests/mps_oper_assign.cpp
        tests/mps_tests/mps_oper_addition.cpp
        tests/mps_tests/mps_oper_subtraction.cpp
        tests/mps_tests/mps_oper_multiplication.cpp
        tests/mps_tests/mps_oper_division.cpp
        tests/mps_tests/mps_comp_equal.cpp
        tests/mps_tests/mps_comp_larger.cpp
        tests/mps_tests/mps_comp_smaller.cpp
        tests/ira_tests/ira_algorithms_auto.cpp
        tests/mps_tests/mps_evaluation.cpp
        tests/iras_tests/iras_all.cpp
)

target_link_libraries(all_tests mps_lib)
target_link_libraries(all_tests ira_lib)
target_link_libraries(all_tests iras_lib)
target_link_libraries(all_tests gtest gtest_main)