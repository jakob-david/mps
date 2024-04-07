project(mpe)

set(HEADER_FILES mpe.h)
set(SOURCE_FILES mpe.cpp)

add_library(mpe_lib ${SOURCE_FILES} ${HEADER_FILES})
