project(pugixml)

set(SRCS
    src/pugixml.cpp
)

set(PUGIXML_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pugixml.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pugiconfig.hpp
    PARENT_SCOPE
)

add_library(${PROJECT_NAME} ${SRCS} ${PUGIXML_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC src)