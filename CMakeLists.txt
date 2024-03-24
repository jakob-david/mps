cmake_minimum_required(VERSION 3.26)
project(mps)

set(CMAKE_CXX_STANDARD 17)


if(CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O1")

set(SOURCE_FILES main.cpp)
add_executable(mps_run ${SOURCE_FILES})

include_directories(mps_lib)
add_subdirectory(mps_lib)
target_link_libraries(mps_run mps_lib)

include_directories(ira_lib)
add_subdirectory(ira_lib)
target_link_libraries(mps_run ira_lib)

add_subdirectory(mps_tests)