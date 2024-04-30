project(mps)

set(HEADER_FILES iras.h)
set(SOURCE_FILES iras.cpp
        iras.h)

add_library(iras_lib ${SOURCE_FILES} ${HEADER_FILES})