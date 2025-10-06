project(clipper)

set(SRCS
    include/clipper.cpp include/clipper.hpp 
)

add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)