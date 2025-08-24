add_library(mps mps.cpp)

target_include_directories(mps
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(mps PUBLIC cxx_std_17)