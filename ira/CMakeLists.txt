add_library(ira ira.cpp)

target_include_directories(ira
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(ira PUBLIC cxx_std_17)

target_link_libraries(ira PRIVATE mps)