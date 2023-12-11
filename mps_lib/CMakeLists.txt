project(mps)

set(HEADER_FILES mps.h mps.h)
set(SOURCE_FILES mps.cpp mps_side.cpp)


add_library(mps_lib ${SOURCE_FILES} ${HEADER_FILES})
