
# General
######################################
#cmake_minimum_required(VERSION 3.26)
cmake_minimum_required(VERSION 3.22.1)
project(mps)
set(CMAKE_CXX_STANDARD 17)
######################################

# Compiler Flags
######################################
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
######################################

# main.cpp
######################################
set(SOURCE_FILES main.cpp)
add_executable(mps_run ${SOURCE_FILES})
######################################

find_package(Python3 COMPONENTS Interpreter)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(mps_run ${PYTHON_LIBRARIES})

# Includes
######################################
include_directories(mps_lib)
add_subdirectory(mps_lib)
target_link_libraries(mps_run mps_lib)

include_directories(ira_lib)
add_subdirectory(ira_lib)
target_link_libraries(mps_run ira_lib)

include_directories(iras_lib)
add_subdirectory(iras_lib)
target_link_libraries(mps_run iras_lib)

include_directories(mpe_lib)
add_subdirectory(mpe_lib)
target_link_libraries(mps_run mpe_lib)
######################################

# Google Tests
######################################
add_subdirectory(tests)
######################################

# Pybind11
######################################
add_subdirectory(pybind11)
pybind11_add_module(mps_library python_exporter.cpp mps_lib/mps.cpp ira_lib/ira.cpp mpe_lib/mpe.cpp)
pybind11_add_module(mpe_library python_exporter.cpp mps_lib/mps.cpp ira_lib/ira.cpp mpe_lib/mpe.cpp)
######################################

