# General
######################################
cmake_minimum_required(VERSION 3.22.1)
project(mps)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
######################################

# add subdirectories
######################################
add_subdirectory(mps)
add_subdirectory(ira)
######################################

# main.cpp
######################################
add_executable(mps_run main.cpp)
target_link_libraries(mps_run PRIVATE mps ira) 
set_target_properties(mps_run PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
######################################

# Compiler Flags
######################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

target_compile_options(mps_run PRIVATE $<$<CONFIG:Debug>:-g> $<$<CONFIG:Release>:-O3>)
######################################

# Unit Tests
######################################
include(FetchContent)

# Download GoogleTest automatically if not found
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES unit_tests/*.cpp)

add_executable(mps_test ${TEST_SOURCES})

# Add unit_tests/ as an include directory
target_include_directories(mps_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests)

# Place test binary in project root
set_target_properties(mps_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_link_libraries(mps_test PRIVATE mps ira GTest::gtest_main)

if(UNIX)
    target_link_libraries(mps_test PRIVATE pthread)
endif()

add_test(NAME mps_test COMMAND mps_test)
######################################

# Pybind 11
######################################
include(FetchContent)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.11.0 # or latest stable version
)
FetchContent_MakeAvailable(pybind11)

# Bindings
add_library(mps_lib MODULE ./python_bindings.cpp)  # renamed to mps_lib
target_link_libraries(mps_lib PRIVATE mps pybind11::module)
set_target_properties(mps_lib PROPERTIES PREFIX "")  # remove 'lib' prefix for Python

target_include_directories(mps_lib PRIVATE mps_lib/include)

target_compile_features(mps_lib PRIVATE cxx_std_17)

# Optional: make sure you use PIC for shared libs
set_target_properties(mps_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Save the library in the root directory
set_target_properties(mps_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
######################################