project(mps)

set(HEADER_FILES ira.h)
set(SOURCE_FILES ira.cpp)

add_library(ira_lib ${SOURCE_FILES} ${HEADER_FILES})