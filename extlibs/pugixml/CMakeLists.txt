project(pugixml)

set(SRCS
    src/pugixml.cpp src/pugixml.hpp
    src/pugiconfig.hpp
)

add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC src)